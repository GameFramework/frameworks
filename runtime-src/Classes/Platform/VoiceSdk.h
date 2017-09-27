//
//  VoiceSdk.h
//  tdht
//
//  Created by hucanhua on 16/9/12.
//
//

#ifndef VoiceSdk_h
#define VoiceSdk_h

#include "cocos2d.h"
#include "../YunVaSDK/YVTool.h"
using namespace YVSDK;

class VoiceSdk: cocos2d::Ref,
	public  YVListern::YVDownLoadFileListern,
	public  YVListern::YVUpLoadFileListern,
	public  YVListern::YVFinishPlayListern,
	public  YVListern::YVFinishSpeechListern,
	public  YVListern::YVStopRecordListern,
	public  YVListern::YVReConnectListern,
	public  YVListern::YVLoginListern,
	public 	YVListern::YVRecordVoiceListern
{
public:
    VoiceSdk();
    virtual ~VoiceSdk();
    static VoiceSdk* getInstance();
    void destroyInstance();
public:
    void initSdk();
    void updateMsg(float dt);
    void eventTracking(const char* eventtype, const char* params);
    void addListern();

	virtual void onLoginListern(CPLoginResponce* r) ;

	virtual void onReConnectListern(ReconnectionNotify* r);

	virtual void onStopRecordListern(RecordStopNotify* r) ;

	virtual void onFinishSpeechListern(SpeechStopRespond* r);

	virtual void onFinishPlayListern(StartPlayVoiceRespond* r);

	virtual void onUpLoadFileListern(UpLoadFileRespond* r);

	virtual void onDownLoadFileListern(DownLoadFileRespond* r);

	virtual void onRecordVoiceListern(RecordVoiceNotify* r);
private:
	std::string url;
	std::string httpurl;
	bool isCancel = false;
    static VoiceSdk*      s_VoiceSdk;
};

#endif /* VoiceSdk_h */
