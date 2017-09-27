#include "YVRespondFactory.h"
#include "YVTypeDef.h"
namespace YVSDK
{
	YVRespondFactory* YVRespondFactory::m_respondFactoryPtr = NULL;

	//云娃帐号登录
	AutoRegisterRespond(IM_THIRD_LOGIN_RESP, CPLoginResponce);

	//录音结束地址通知
	AutoRegisterRespond(IM_RECORD_STOP_RESP, RecordStopNotify);

	//播放语音完成	
	AutoRegisterRespond(IM_RECORD_FINISHPLAY_RESP, StartPlayVoiceRespond);

	//停止语音识别回应
	AutoRegisterRespond(IM_SPEECH_STOP_RESP, SpeechStopRespond);

	//上传文件回应
	AutoRegisterRespond(IM_UPLOAD_FILE_RESP, UpLoadFileRespond);

	//下载文件回应
	AutoRegisterRespond(IM_DOWNLOAD_FILE_RESP, DownLoadFileRespond);

	//重连通知
	AutoRegisterRespond(IM_RECONNECTION_NOTIFY, ReconnectionNotify);

	//网络状态
	AutoRegisterRespond(IM_NET_STATE_NOTIFY, NetWorkStateNotify);

	//录音时候音量通知
	AutoRegisterRespond(IM_RECORD_VOLUME_NOTIFY, RecordVoiceNotify);

	//用户信息
	AutoRegisterRespond(IM_GET_THIRDBINDINFO_RESP, GetCPUserInfoRespond);

	//云播放文件下载进度
	AutoRegisterRespond(IM_RECORD_PLAY_PERCENT_NOTIFY, DownloadVoiceRespond);

};