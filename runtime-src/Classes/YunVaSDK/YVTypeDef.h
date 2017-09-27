#ifndef YVTypeDef_h__
#define YVTypeDef_h__

#include <string>
#include <iostream>
#include <vector>
#include "../../IM_SDK/include/IMSDK.h"
#include "../../IM_SDK/include/YVIMCmdDef.h"
#include "yvpacket_overloaded.h"
#include <time.h>
#define  YVSDK_Version "1.0.0"

namespace YVSDK
{
	typedef unsigned int uint32;
	typedef unsigned int uint8;

	class ARef
	{
	public:
		ARef(){ _refCount = 1; }
		virtual ~ARef(){};
		void addRef(){ ++_refCount; };
		void release(){ if ((--_refCount) <= 0)delete this; }
	private:
		unsigned int _refCount;
	};

	struct YaYaRequestBase :public  ARef
	{
		virtual ~YaYaRequestBase(){};
		CmdChannel m_requestChannel;
		uint32 m_requestCmd;
		YaYaRequestBase(CmdChannel channel, uint32 cmd)
		{
			m_requestChannel = channel;
			m_requestCmd = cmd;
		}

		virtual YV_PARSER encode(){ return  yvpacket_get_parser(); }
	};

	struct YaYaRespondBase :public ARef
	{
		virtual ~YaYaRespondBase(){};
		virtual void decode(YV_PARSER parser){}
	};

	//云娃登陆请求响应 IM_LOGIN_RESP
	struct LoginResponse :YaYaRespondBase
	{
		uint32 result; //返回结果 不为0即为失败
		std::string msg; //错误描述
		std::string nickname; //用户昵称
		uint32 userId; //用户ID
		std::string iconurl; //用户图像地址
		void decode(YV_PARSER parser)
		{
			result = parser_get_uint32(parser, x11001::result);
			msg = parser_get_string(parser, x11001::msg);
			nickname = parser_get_string(parser, x11001::nickname);
			userId = parser_get_uint32(parser, x11001::userId);
			iconurl = parser_get_string(parser, x11001::iconurl);
		}
	};

	//CP账号登陆请求
	struct CPLoginRequest : public YaYaRequestBase
	{
		CPLoginRequest()
		:YaYaRequestBase(IM_LOGIN, IM_THIRD_LOGIN_REQ)
		{

		}
		std::string tt;  //cp登录凭证
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x11002::tt, tt.c_str());
			return parser;
		}
	};

	struct CPLoginResponce : public YaYaRespondBase
	{
		uint32 result; //返回结果 不为0即为失败
		std::string msg; //错误描述
		uint32 userid;//云娃ID
		std::string nickName;//用户昵称
		std::string iconUrl; //用户图像地址
		uint32 thirdUserId; //第三方用户ID
		std::string thirdUserName; //第三方用户名
		void decode(YV_PARSER parser)
		{
			this->result = parser_get_uint32(parser, x11003::result);
			this->msg = parser_get_string(parser, x11003::msg);
			this->userid = parser_get_uint32(parser, x11003::userid);
			this->nickName = parser_get_string(parser, x11003::nickName);
			this->iconUrl = parser_get_string(parser, x11003::iconUrl);
			this->thirdUserId = parser_get_uint32(parser, x11003::thirdUserId);
			this->thirdUserName = parser_get_string(parser, x11003::thirdUserName);
		}
	};

	//注销登录 IM_LOGOUT_REQ
	struct CPLogoutRequest :YaYaRequestBase
	{
		CPLogoutRequest()
		:YaYaRequestBase(IM_LOGIN, IM_LOGOUT_REQ)
		{

		}

		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			return parser;
		}
	};

	//重连通知 IM_RECONNECTION_NOTIFY
	struct ReconnectionNotify : YaYaRespondBase
	{
		uint32	userid;
		void decode(YV_PARSER parser)
		{
			userid = parser_get_uint32(parser, x11013::userid);
		}
	};

	//获取好友信息
	struct GetCPUserInfoRequest:YaYaRequestBase
	{
		uint32 appid;
		std::string uid;

		GetCPUserInfoRequest()
		:YaYaRequestBase(IM_LOGIN, IM_GET_THIRDBINDINFO_REQ)
		{

		}

		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_uint32(parser, x11014::appid, appid);
			parser_set_cstring(parser, x11014::uid, uid.c_str());
			return parser;
		}
	};

	//获取信息回应 IM_GET_THIRDBINDINFO_RESP
	struct GetCPUserInfoRespond 
		: public YaYaRespondBase
	{
		uint32 result;
		std::string msg;
		uint32 yunvaid;
		std::string nickname;
		std::string iconUrl;
		std::string level;
		std::string vip;
		std::string ext;
		
		GetCPUserInfoRespond()
			:YaYaRespondBase()
		{

		}

		void decode(YV_PARSER parser)
		{
			result = parser_get_uint32(parser, x11015::result);
			msg = parser_get_string(parser, x11015::msg);
			yunvaid = parser_get_uint32(parser, x11015::yunvaid);
			nickname = parser_get_string(parser, x11015::nickname);
			iconUrl = parser_get_string(parser, x11015::iconUrl);
			level = parser_get_string(parser, x11015::level);
			vip = parser_get_string(parser, x11015::vip);
			ext = parser_get_string(parser, x11015::ext);
		}
	};

	/****************************频道结束***************************/

	/****************************工具开始***************************/
	//网络状态通知IM_NET_STATE_NOTIFY
	struct NetWorkStateNotify :YaYaRespondBase
	{
		yv_net state;
		void decode(YV_PARSER parser)
		{
			state = (yv_net)parser_get_uint8(parser, x11016::state);
		}
	};

	//设置录音时长 IM_RECORD_SETINFO_REQ
	struct SetRecordRequest :YaYaRequestBase
	{
		uint32 times;
		uint8 volume;
		SetRecordRequest()
			:YaYaRequestBase(IM_TOOLS, IM_RECORD_SETINFO_REQ)
		{

		}

		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_uint32(parser, x19014::times, times);
			parser_set_uint8(parser, x19014::volume, volume);
			return parser;
		}
	};
	
	//开始录音(最长60秒)  IM_CHANNEL_VOICEMSG_REQ	
	struct StartRecordRequest :YaYaRequestBase
	{
		std::string strFilePath;
		std::string  ext;
		uint8 speech;
		StartRecordRequest()
			:YaYaRequestBase(IM_TOOLS, IM_RECORD_STRART_REQ)
		{

		}

		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x19000::strfilepath, strFilePath.c_str());
			parser_set_cstring(parser, x19000::ext, ext.c_str());
			parser_set_uint8(parser, x19000::speech, speech);
			return parser;
		}
	};

	//结束录音(最长60秒)  IM_RECORD_STOP_REQ
	struct StopRecordRequest :YaYaRequestBase
	{
		StopRecordRequest()
		:YaYaRequestBase(IM_TOOLS, IM_RECORD_STOP_REQ)
		{
		}

		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			return parser;
		}
	};

	//停止录音返回  回调返回录音文件路径名  IM_RECORD_STOP_RESP
	struct RecordStopNotify :YaYaRespondBase
	{
		uint32	time; //录音时长
		std::string	strfilepath; //录音保存文件路径名
		std::string ext;
		void decode(YV_PARSER parser)
		{
			time = parser_get_uint32(parser, x19002::time);
			strfilepath = parser_get_string(parser, x19002::strfilepath);
			ext = parser_get_string(parser, x19002::ext);
		}
	};

	//录音音量大小通知 IM_RECORD_VOLUME_NOTIFY
	struct RecordVoiceNotify 
		:YaYaRespondBase
	{
		std::string ext;  //扩展标记
		uint8       volume;  //音量大小(0-100)
		void decode(YV_PARSER parser)
		{
			volume = parser_get_uint8(parser, x19015::volume);
			ext = parser_get_string(parser, x19015::ext);
		}
	};

	//播放录音请求	IM_RECORD_STARTPLAY_REQ	
	struct StartPlayVoiceRequest :YaYaRequestBase
	{
		StartPlayVoiceRequest()
		:YaYaRequestBase(IM_TOOLS, IM_RECORD_STARTPLAY_REQ)
		{
		}
		std::string	strUrl;      // 录音url	
		std::string	strfilepath;  //录音文件
		std::string ext;
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x19003::strUrl, strUrl.c_str());
			parser_set_cstring(parser, x19003::strfilepath, strfilepath.c_str());
			parser_set_cstring(parser, x19003::ext, ext.c_str());
			return parser;
		}
	};

	//播放语音完成	IM_RECORD_FINISHPLAY_RESP
	struct StartPlayVoiceRespond :YaYaRespondBase
	{
		uint32    result; //播放完成为 0， 失败为1
		std::string    describe; //描述
		std::string  ext;
		void decode(YV_PARSER parser)
		{
			result = parser_get_uint32(parser, x19004::result);
			describe = parser_get_string(parser, x19004::describe);
			ext = parser_get_string(parser, x19004::ext);
		}
	};

	//停止播放语音  IM_RECORD_STOPPLAY_REQ
	struct StopPlayVoiceRequest :YaYaRequestBase
	{
		StopPlayVoiceRequest()
		:YaYaRequestBase(IM_TOOLS, IM_RECORD_STOPPLAY_REQ)
		{
		}
	};

	//语音识别设置 IM_SPEECH_SETLANGUAGE_REQ
	struct SpeechSetRequest :YaYaRequestBase
	{
		SpeechSetRequest()
		:YaYaRequestBase(IM_TOOLS, IM_SPEECH_SETLANGUAGE_REQ)
		{
		}
		yvimspeech_language inLanguage;
		yvimspeech_outlanguage outLanguage;
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_uint8(parser, x19008::inlanguage, inLanguage);
			parser_set_uint8(parser, x19008::outlanguage, outLanguage);
			return parser;
		}
	};

	//开始语音识别 IM_SPEECH_START_REQ	
	struct SpeechStartRequest :YaYaRequestBase
	{
		SpeechStartRequest()
		:YaYaRequestBase(IM_TOOLS, IM_SPEECH_START_REQ)
		{
		}
		std::string strfilepath;
		std::string ext;
		yvspeech   type;
		std::string    url;
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x19006::strfilepath, strfilepath.c_str());
			parser_set_cstring(parser, x19006::ext, ext.c_str());
			parser_set_uint8(parser, x19006::type, type);
			parser_set_cstring(parser, x19006::url, url.c_str());
			return parser;
		}
	};

	//停止语音识别请求 IM_SPEECH_STOP_REQ
	/*struct SpeechStopRequest :YaYaRequestBase
	{
	SpeechStopRequest()
	:YaYaRequestBase(IM_TOOLS, IM_SPEECH_STOP_REQ)
	{
	}
	YV_PARSER encode()
	{
	YV_PARSER parser = yvpacket_get_parser();
	return parser;
	}
	};*/

	//停止语音识别回应 IM_SPEECH_STOP_RESP	
	struct SpeechStopRespond :YaYaRespondBase
	{
		uint32		err_id;   //0为成功
		std::string		err_msg;  //返回的错误描述
		std::string		result;   //结果
		std::string ext;
		std::string url;    //识别时使用了上传功能，这个会返回url
		void decode(YV_PARSER parser)
		{
			err_id = parser_get_uint32(parser, x19009::err_id);
			err_msg = parser_get_string(parser, x19009::err_msg);
			result = parser_get_string(parser, x19009::result);
			ext = parser_get_string(parser, x19009::ext);
			url = parser_get_string(parser, x19009::url);
		}
	};

	//请求上传文件  IM_UPLOAD_FILE_REQ 
	struct UpLoadFileRequest :YaYaRequestBase
	{
		UpLoadFileRequest()
		:YaYaRequestBase(IM_TOOLS, IM_UPLOAD_FILE_REQ)
		{
		}
		std::string filename;
		std::string fileid;
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x19010::filename, filename.c_str());
			parser_set_cstring(parser, x19010::fileid, fileid.c_str());
			return parser;
		}
	};

	//上传文件请求回应 IM_UPLOAD_FILE_RESP
	struct UpLoadFileRespond :YaYaRespondBase
	{
		uint32	result;
		std::string  msg;        //错误描述
		std::string  fileid;     //文件ID
		std::string  fileurl;    //返回文件地址
		uint32  percent;    //完成百分比

		void decode(YV_PARSER parser)
		{
			result = parser_get_uint32(parser, x19011::result);
			msg = parser_get_string(parser, x19011::msg);
			fileid = parser_get_string(parser, x19011::fileid);
			fileurl = parser_get_string(parser, x19011::fileurl);
			percent = parser_get_uint32(parser, x19011::percent);
		}
	};

	//请求下载文件  IM_DOWNLOAD_FILE_REQ 
	struct DownLoadFileRequest :YaYaRequestBase
	{
		DownLoadFileRequest()
		:YaYaRequestBase(IM_TOOLS, IM_DOWNLOAD_FILE_REQ)
		{
		}
		std::string url;
		std::string filename;
		std::string fileid;
		YV_PARSER encode()
		{
			YV_PARSER parser = yvpacket_get_parser();
			parser_set_cstring(parser, x19012::url, url.c_str());
			parser_set_cstring(parser, x19012::filename, filename.c_str());
			parser_set_cstring(parser, x19012::fileid, fileid.c_str());
			return parser;
		}
	};

	//下载文件回应 IM_DOWNLOAD_FILE_RESP 
	struct DownLoadFileRespond :YaYaRespondBase
	{
		uint32	result;     //返回码 0：成功，其他失败
		std::string  msg;        //错误描述
		std::string  filename;   //文件名
		std::string  fileid;     //文件ID
		uint32  percent;    //完成百分比

		void decode(YV_PARSER parser)
		{
			result = parser_get_uint32(parser, x19013::result);
			msg = parser_get_string(parser, x19013::msg);
			filename = parser_get_string(parser, x19013::filename);
			fileid = parser_get_string(parser, x19013::fileid);
			percent = parser_get_uint32(parser, x19013::percent);
		}
	};

	//云播放时，进度事件IM_RECORD_PLAY_PERCENT_NOTIFY
	struct DownloadVoiceRespond 
		: public YaYaRespondBase
	{
		uint8      percent;
		std::string     ext;

		void decode(YV_PARSER parser)
		{
			percent = parser_get_uint32(parser, x19016::percent);
			ext = parser_get_string(parser, x19016::ext);
		}
	};

	////设备号等操作IM_DEVICE_SETINFO
	//struct SetDeviceInfoReqeust : YaYaRequestBase
	//{

	//	SetDeviceInfoReqeust()
	//	:YaYaRequestBase(IM_LOGIN, IM_DEVICE_SETINFO)
	//	{
	//	}
	//	std::string imsi;
	//	std::string imei;
	//	std::string mac;
	//	std::string appVersion;
	//	std::string networkType;

	//	YV_PARSER encode()
	//	{
	//		YV_PARSER parser = yvpacket_get_parser();
	//		parser_set_cstring(parser, x11012::imsi, imsi.c_str());
	//		parser_set_cstring(parser, x11012::imei, imei.c_str());
	//		parser_set_cstring(parser, x11012::mac, mac.c_str());
	//		parser_set_cstring(parser, x11012::appVersion, appVersion.c_str());
	//		parser_set_cstring(parser, x11012::networkType, networkType.c_str());
	//		return parser;
	//	}
	//};

	/****************************工具结束***************************/
}
#endif // YVTypeDef_h__