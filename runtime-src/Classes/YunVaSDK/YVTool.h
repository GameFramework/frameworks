#ifndef YunVaSDKUtils_h__
#define YunVaSDKUtils_h__

/************************************************************************/
/* 云娃语音接入单元                                                     */
/************************************************************************/
#include <map>
#include <vector>
#include "YVTypeDef.h"
#include "CYVSyncQueue.h"
#include "yvListern.h"
namespace YVSDK
{
	//消息回调结构
	struct YAYACallBackObj;

	typedef std::vector<YAYACallBackObj*> YaYaMsgCallFuncList;
	typedef std::map<int, YaYaMsgCallFuncList> YaYaMsgMap;

	class YVTool
	{
	public:
		virtual ~YVTool(void);
		static YVTool* getInstance();

		/*初始化SDK*/
		void initSDK(unsigned long appId, std::string tempPath, bool isDebug = true);

		/*CP登录*/
		void cpLogin(std::string nickname = "1" , std::string uid = "1" );

		/*注销登录*/
		void cpLogout();

		/*获取用户资料 */
		void getCPUserInfo(uint32 appid, std::string uid);

		/*注册相关处理函数*/
		void registerMsgCallBack();
		void unRegisterMsgCallBack();

		/*释放SDK*/
		void releaseSDK();

		/*设置录音,第一个参数为录音的时长单位为秒,默认是60秒
		第二个参数为是否获取录音时回调；注意这个接口只有登录成功后才能生效
		*/
		void setRecord(unsigned int timeNum, bool isGetVolume);

		//开始录音, speech：0关闭录音时上传语音识别，1打开录音时上传语音完成识别
		bool startRecord(std::string savePath, uint8 speech = 0, std::string ext = "");

		/*结束录音*/
		void stopRecord();

		/*播放录音*/  
		bool playRecord(std::string path, std::string Url, std::string ext = "");

		/*播放在线录音,注意云播放有二个回调，
		一个是DownloadVoice(用于做UI上的显示，如菊花) 
		一个是播放结束的回调，坑爹啊*/
		void playFromUrl(std::string url, std::string ext = "");

		/*结束播放*/
		void stopPlay();

		/*设置语音识别类型*/
		void setSpeechType(yvimspeech_language inType, yvimspeech_outlanguage outType);

		/*语音识别,默认识别本地记录的, isUpLoad 是否将本地文件上传至服务器*/
		void speechVoice(std::string path, std::string ext = "", bool isUpLoad = false);

		/*通过url来进行识别*/
		void speechUrl(std::string url,  std::string ext = "");

		/*请求上传文件*/
		void upLoadFile(std::string path, std::string fileid = "");

		/*请求下载文件*/
		void downLoadFile(std::string url, std::string savePath, std::string fileid = "");

		////设置设备信息
		//void setDeviceInfo(std::string imsi, std::string imei, std::string mac,
		//	std::string appVersion, std::string networkType);

		/*注册消息处理回调*/
		template<typename T>
		void registerMsg(int cmdid, T* obj, void (T::*func)(YaYaRespondBase*));

		//请在定时器运行
		void dispatchMsg(float t);

		/*反注册*/
		template<typename T>
		void unRegisterMsg(int cmdid, T* obj);

		inline bool isInitSDK(){ return _isSDKInit; };
	protected:
		YVTool(void);

		InitListern(Login, CPLoginResponce);
		InitListern(ReConnect, ReconnectionNotify);
		InitListern(StopRecord, RecordStopNotify);
		InitListern(FinishSpeech, SpeechStopRespond);
		InitListern(FinishPlay, StartPlayVoiceRespond);
		InitListern(UpLoadFile, UpLoadFileRespond);
		InitListern(DownLoadFile, DownLoadFileRespond);
		InitListern(NetWorkSate, NetWorkStateNotify); 
		InitListern(RecordVoice, RecordVoiceNotify);
		InitListern(CPUserInfo, GetCPUserInfoRespond);
		InitListern(DownloadVoice, DownloadVoiceRespond);
	private:
		static YVTool* _shareHandler;
		bool _isSDKInit;  //SDK是否初始化完成
		bool _isLoginSuccess; //CP登录是否成功
		bool _isRecording; //正在录音
		bool _isPlaying;  //是否正在播放
		bool _isUsedSchedule;
		bool _lockInit;

		static YaYaMsgMap* _msgCallBackMap;

	private:
		bool sendRequeset(YaYaRequestBase* request);

		/*相关消息返回*/
		void cpLoginRespond(YaYaRespondBase* respond);

		/*重连成功通知*/
		void reconnectionNotify(YaYaRespondBase* respond);

		/*停止录音返回*/
		void stopRecordRespond(YaYaRespondBase* respond);

		/*播放录音完成返回*/
		void finishPlayRespond(YaYaRespondBase* respond);

		/*语音识别完成返回*/
		void finishSpeechRespond(YaYaRespondBase* respond);

		/*上传文件请求返回*/
		void upLoadFileRespond(YaYaRespondBase* respond);

		/*下载文件请求返回*/
		void downLoadFileRespond(YaYaRespondBase* respond);

		/*网络状态通知*/
		void netWorkStateRespond(YaYaRespondBase* respond);

		/*录音音量通知*/
		void recordVoiceRespond(YaYaRespondBase* respond);

		/*用户信息*/
		void cpUserInfoRespond(YaYaRespondBase* respond);

		//云播放及云识别文件下载
		void downloadVoiceRespond(YaYaRespondBase* respond);
	};
}
#endif // YunVaSDKUtils_h__

