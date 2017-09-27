#include "YVTool.h"
#include "YVRespondFactory.h"
namespace YVSDK
{
	//================================================================================
	//线程之间传递的消息结构
	struct YVMsgData
	{
		unsigned int cmdid;
		YaYaRespondBase* r;
	};

	//消息回调结构
	struct YAYACallBackObj
	{
		virtual ~YAYACallBackObj(){}
		virtual long getObjAddr() = 0;
		virtual void call(YaYaRespondBase* request) = 0;
	};

	template<typename T>
	struct YAYACallBackSlot :
		public YAYACallBackObj
	{
		T* t;
		typedef void (T::*SEL_DataEvent)(YaYaRespondBase* request);
		SEL_DataEvent f;

		YAYACallBackSlot(T* obj, SEL_DataEvent func)
		{
			t = obj;
			f = func;
		}

		long getObjAddr()
		{
			return (*reinterpret_cast<long*>(t));
		}

		void call(YaYaRespondBase* request)
		{
			(t->*f)(request);
		}
	};
	//=================================================================================
	static CYVSyncQueue<YVMsgData> s_msgQueue;
	YVTool* YVTool::_shareHandler = NULL;
	YaYaMsgMap* YVTool::_msgCallBackMap = NULL;

	static void _stdcall myYVCallBack(enum CmdChannel type, unsigned int cmdid, YV_PARSER parser, unsigned long context)
	{
		YVMsgData data;
		data.cmdid = cmdid;
		data.r = YVRespondFactory::getSingletonPtr()->getRepsond(cmdid);
		if (data.r == NULL)
		{
			printf("YVRespondFactory not find: 0x%x ", cmdid);
			return;
		}

		data.r->decode(parser);
		s_msgQueue.AddElement(data);
	}

	YVTool::YVTool(void)
	{
		_isPlaying = false;
		_isSDKInit = false;
		_isUsedSchedule = false;
		_isLoginSuccess = false;
		_isRecording = false;
		_lockInit = false;

		_msgCallBackMap = new YaYaMsgMap();
	}


	YVTool::~YVTool(void)
	{
		if (_isSDKInit)
			releaseSDK();
		_isSDKInit = false;

		/*if(_isUsedSchedule)
		{
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(YVTool::dispatchMsg), this);
		_isUsedSchedule = false;
		}*/

		if (_msgCallBackMap)
		{
			for (YaYaMsgMap::iterator it = _msgCallBackMap->begin(); it != _msgCallBackMap->end(); ++it)
			{
				for (YaYaMsgCallFuncList::iterator its = it->second.begin(); its != it->second.end(); ++its)
				{
					delete *its;
				}
				it->second.clear();
			}
			_msgCallBackMap->clear();
			delete _msgCallBackMap;
			_msgCallBackMap = NULL;
		}

		if (_shareHandler)
		{
			delete _shareHandler;
			_shareHandler = NULL;
		}
	}

	YVTool* YVTool::getInstance()
	{
		if (_shareHandler == NULL)
		{
			_shareHandler = new YVTool();
		}
		return _shareHandler;
	}

	void YVTool::initSDK(unsigned long appId, std::string tempPath, bool isDebug)
	{
		if (_lockInit || _isSDKInit) return;
		_lockInit = true;
		auto ret = YVIM_Init(myYVCallBack, 0, appId, tempPath.c_str(), isDebug);
		_lockInit = false; //防止执行两次初始化

		if (ret == 0)
		{
			_isSDKInit = true;
			printf("YVIM_Init: Success.");
			registerMsgCallBack();
		}
		else
		{
			_isSDKInit = false;
			printf("YVIM_Init: Fail.");
		}
	}

	bool YVTool::sendRequeset(YaYaRequestBase* request)
	{
		if (!_isSDKInit)
		{
			printf("YVSDK not Init.");
			return false;
		}

		auto ret = YVIM_SendCmd(request->m_requestChannel, request->m_requestCmd, request->encode());

		if (ret == 0)
		{
			printf("YVIM_SendCmd: 0x%x Success.", request->m_requestCmd);
			return true;
		}
		else
		{
			printf("YVIM_SendCmd: 0x%xFail.", request->m_requestCmd);
			return false;
		}
	}

	void YVTool::cpLogin(std::string nickname, std::string uid)
	{
		CPLoginRequest r;
		r.tt.append("{\"nickname\":\"");
		r.tt.append(nickname);
		r.tt.append("\",\"uid\":\"");
		r.tt.append(uid);
		r.tt.append("\"}");

		sendRequeset(&r);
	}

	void YVTool::cpLogout()
	{
		printf("request cp logout.");

		CPLogoutRequest r;
		sendRequeset(&r);
	}

	void YVTool::releaseSDK()
	{
		unRegisterMsgCallBack();
		YVIM_Release();
	}

	void YVTool::registerMsgCallBack()
	{
		/*绑定相关消息处理*/
		registerMsg(IM_THIRD_LOGIN_RESP, this, &YVTool::cpLoginRespond);
		registerMsg(IM_RECONNECTION_NOTIFY, this, &YVTool::reconnectionNotify);
		registerMsg(IM_RECORD_STOP_RESP, this, &YVTool::stopRecordRespond);
		registerMsg(IM_RECORD_FINISHPLAY_RESP, this, &YVTool::finishPlayRespond);
		registerMsg(IM_SPEECH_STOP_RESP, this, &YVTool::finishSpeechRespond);
		registerMsg(IM_UPLOAD_FILE_RESP, this, &YVTool::upLoadFileRespond);
		registerMsg(IM_DOWNLOAD_FILE_RESP, this, &YVTool::downLoadFileRespond);
		registerMsg(IM_NET_STATE_NOTIFY, this, &YVTool::netWorkStateRespond);
		registerMsg(IM_RECORD_VOLUME_NOTIFY, this, &YVTool::recordVoiceRespond);
		registerMsg(IM_GET_THIRDBINDINFO_RESP, this, &YVTool::cpUserInfoRespond);
		registerMsg(IM_RECORD_PLAY_PERCENT_NOTIFY, this, &YVTool::downloadVoiceRespond);
	}

	void YVTool::unRegisterMsgCallBack()
	{
		unRegisterMsg(IM_THIRD_LOGIN_RESP, this);
		unRegisterMsg(IM_RECONNECTION_NOTIFY, this);
		unRegisterMsg(IM_RECORD_STOP_RESP, this);
		unRegisterMsg(IM_RECORD_FINISHPLAY_RESP, this);
		unRegisterMsg(IM_SPEECH_STOP_RESP, this);
		unRegisterMsg(IM_UPLOAD_FILE_RESP, this);
		unRegisterMsg(IM_DOWNLOAD_FILE_RESP, this);
		unRegisterMsg(IM_NET_STATE_NOTIFY, this);
		unRegisterMsg(IM_RECORD_VOLUME_NOTIFY, this);
		unRegisterMsg(IM_GET_THIRDBINDINFO_RESP, this);
		unRegisterMsg(IM_RECORD_PLAY_PERCENT_NOTIFY, this);
	}


	void YVTool::getCPUserInfo(uint32 appid, std::string uid)
	{
		GetCPUserInfoRequest q;
		q.appid = appid;
		q.uid.append(uid);
		sendRequeset(&q);
	}

	void YVTool::setRecord(unsigned int timeNum, bool isGetVolume)
	{
		SetRecordRequest q;
		q.times = timeNum;
		q.volume = isGetVolume ? 1 : 0;
		sendRequeset(&q);
	}

	bool YVTool::startRecord(std::string savePath, uint8 speech, std::string ext)
	{
		if (_isRecording)
		{
			printf("isRecording");
			return false;
		}
			
		_isRecording = true;
		StartRecordRequest q;
		q.strFilePath.append(savePath);
		q.ext.append(ext);
		q.speech = speech;
		if (sendRequeset(&q) == false)
		{
			_isRecording = false;
		}
		return _isRecording;
	}

	void YVTool::stopRecord()
	{
		if (!_isRecording) return;
		StopRecordRequest q;
		sendRequeset(&q);
		_isPlaying = false;
	}

	bool YVTool::playRecord(std::string Url, std::string path, std::string ext)
	{
		if (_isPlaying)
		{
			printf("isPlaying");
			return false;
		}
			
		_isPlaying = true;
		StartPlayVoiceRequest q;
		q.strUrl.append(Url);
		q.strfilepath.append(path);

		q.ext.append(ext);
		if(sendRequeset(&q) == false)
		_isPlaying = false;

		return _isPlaying;
	}

	void YVTool::playFromUrl(std::string url, std::string ext)
	{
		if (_isPlaying) return;
		StartPlayVoiceRequest q;
		q.strUrl.append(url);
		q.ext.append(ext);
		if(sendRequeset(&q))
		_isPlaying = true;
	}

	void YVTool::stopPlay()
	{
		if (!_isPlaying) return;
		StopPlayVoiceRequest q;
		sendRequeset(&q);
	}

	void YVTool::setSpeechType(yvimspeech_language inType, yvimspeech_outlanguage outType)
	{
		SpeechSetRequest q;
		q.inLanguage = (yvimspeech_language)inType;
		q.outLanguage = outType;
		sendRequeset(&q);
	}

	void YVTool::speechVoice(std::string path, std::string ext, bool isUpLoad)
	{
		SpeechStartRequest q;
		q.strfilepath.append(path);
		q.ext.append(ext);
	
		q.type = isUpLoad ? speech_file_and_url : speech_file;

		sendRequeset(&q);
	}

	void YVTool::speechUrl(std::string url, std::string ext )
	{
		SpeechStartRequest q;
		q.strfilepath.append(url);
		q.ext.append(ext);
		q.type = speech_url;
		sendRequeset(&q);
	}

	void YVTool::upLoadFile(std::string path, std::string fileid)
	{
		UpLoadFileRequest q;
		q.filename.append(path);
		q.fileid.append(fileid);
		sendRequeset(&q);
	}

	void YVTool::downLoadFile(std::string url, std::string savePath, std::string fileid)
	{
		DownLoadFileRequest q;
		q.url.append(url);
		q.filename.append(savePath);
		q.fileid.append(fileid);
		sendRequeset(&q);
	}


	//void  YVTool::setDeviceInfo(std::string imsi, std::string imei, std::string mac,
	//	std::string appVersion, std::string networkType)
	//{
	//	SetDeviceInfoReqeust q;
	//	q.imsi.append(imsi);
	//	q.imei.append(imei);
	//	q.mac.append(mac);
	//	q.appVersion.append(appVersion);
	//	q.networkType.append(networkType);

	//	sendRequeset(&q);
	//}


	template<typename T>
	void YVTool::registerMsg(int cmdid, T* obj, void (T::*func)(YaYaRespondBase*))
	{
		YAYACallBackSlot<T>* callObj = new YAYACallBackSlot<T>(obj, func);

		YaYaMsgMap::iterator it = _msgCallBackMap->find(cmdid);
		if (it != _msgCallBackMap->end())
		{
			it->second.push_back(callObj);
		}
		else
		{
			YaYaMsgCallFuncList callFuncList;
			callFuncList.push_back(callObj);
			_msgCallBackMap->insert(make_pair(cmdid, callFuncList));
		}
	}

	template<typename T>
	void YVTool::unRegisterMsg(int cmdid, T* obj)
	{
		YaYaMsgMap::iterator it = _msgCallBackMap->find(cmdid);
		if (it == _msgCallBackMap->end())
		{
			return;
		}

		YaYaMsgCallFuncList& funcList = it->second;
		long objAddr = *reinterpret_cast<long *>(obj);

		for (YaYaMsgCallFuncList::iterator its = funcList.begin();
			its != funcList.end(); ++its)
		{
			if ((*its)->getObjAddr() == objAddr)
			{
				delete *its;
				funcList.erase(its);
				break;
			}
		}

		if (funcList.size() == 0)
		{
			_msgCallBackMap->erase(it);
		}
	}

	void YVTool::dispatchMsg(float t)
	{
		static YVMsgData msgData;
		if (!s_msgQueue.PopElement(msgData))
		{
			return;
		}
		unsigned int cmdid = msgData.cmdid;
		YaYaMsgMap::iterator it = _msgCallBackMap->find(cmdid);

		if (it != _msgCallBackMap->end())
		{
			YaYaMsgCallFuncList& funcList = it->second;
			for (YaYaMsgCallFuncList::iterator its = funcList.begin();
				its != funcList.end(); ++its)
			{
				(*its)->call(msgData.r);
			}
		}
		else
		{
			printf("CallBackFunc not find: 0x%x ", cmdid);
		}
		msgData.r->release();
	}

	void YVTool::cpLoginRespond(YaYaRespondBase* respond)
	{
		CPLoginResponce* r = static_cast<CPLoginResponce*>(respond);
		callLoginListern(r);

		if (r->result == 0)
		{
			printf("YunVa CP Login Success.");

			YVTool::getInstance()->setSpeechType(im_speech_en, im_speechout_simplified);
		}
		else
		{
			printf("YunVa CP Login Failed：%s", r->msg.c_str());
		}

		_isLoginSuccess = r->result == 0;
	}

	void YVTool::reconnectionNotify(YaYaRespondBase* respond)
	{
		ReconnectionNotify* r = static_cast<ReconnectionNotify*>(respond);
		callReConnectListern(r);
	}

	void YVTool::stopRecordRespond(YaYaRespondBase* respond)
	{
		_isRecording = false;
		RecordStopNotify* r = static_cast<RecordStopNotify*>(respond);
		callStopRecordListern(r);
	}

	void YVTool::finishPlayRespond(YaYaRespondBase* respond)
	{
		StartPlayVoiceRespond* r = static_cast<StartPlayVoiceRespond*>(respond);
		_isPlaying = false;
		callFinishPlayListern(r);
	}

	void YVTool::finishSpeechRespond(YaYaRespondBase* respond)
	{
		SpeechStopRespond* r = static_cast<SpeechStopRespond*>(respond);
		callFinishSpeechListern(r);
	}

	void YVTool::upLoadFileRespond(YaYaRespondBase* respond)
	{
		UpLoadFileRespond* r = static_cast<UpLoadFileRespond*>(respond);
		callUpLoadFileListern(r);
	}

	void YVTool::downLoadFileRespond(YaYaRespondBase* respond)
	{
		DownLoadFileRespond* r = static_cast<DownLoadFileRespond*>(respond);
		callDownLoadFileListern(r);
	}

	void YVTool::netWorkStateRespond(YaYaRespondBase* respond)
	{
		NetWorkStateNotify* r = static_cast<NetWorkStateNotify*>(respond);
		callNetWorkSateListern(r);
	}

	void YVTool::recordVoiceRespond(YaYaRespondBase* respond)
	{
		RecordVoiceNotify* r = static_cast<RecordVoiceNotify*>(respond);
		callRecordVoiceListern(r);
	}

	void YVTool::cpUserInfoRespond(YaYaRespondBase* respond)
	{
		GetCPUserInfoRespond* r = static_cast<GetCPUserInfoRespond*>(respond);
		callCPUserInfoListern(r);
	}

	void YVTool::downloadVoiceRespond(YaYaRespondBase* respond)
	{
		DownloadVoiceRespond* r = static_cast<DownloadVoiceRespond*>(respond);
		callDownloadVoiceListern(r);
	}
}