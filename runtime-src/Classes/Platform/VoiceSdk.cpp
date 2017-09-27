//
//  VoiceSdk.cpp
//  tdht
//
//  Created by hucanhua on 16/9/12.
//
//

#include "VoiceSdk.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include <sstream>
#include "audio/include/AudioEngine.h"


using namespace cocos2d;
VoiceSdk* VoiceSdk::s_VoiceSdk = nullptr;

#define RECODEPATH (FileUtils::getInstance()->getWritablePath() + "tdht.amr")
#define DOWNPATH (FileUtils::getInstance()->getWritablePath() + "http.amr")
USING_NS_CC;
using namespace experimental;

VoiceSdk::VoiceSdk()
{
}

VoiceSdk::~VoiceSdk()
{
}

VoiceSdk* VoiceSdk::getInstance()
{
    if (s_VoiceSdk == nullptr)
    {
        s_VoiceSdk = new VoiceSdk();
    }
    return s_VoiceSdk;
}

void VoiceSdk::destroyInstance()
{
    if (s_VoiceSdk)
    {
        delete s_VoiceSdk;
        s_VoiceSdk = nullptr;
    }

    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->unscheduleAllForTarget(this);
}

void VoiceSdk::initSdk()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->schedule(CC_SCHEDULE_SELECTOR(VoiceSdk::updateMsg), this, 0.0f, false);
    sched->pauseTarget(this);
    
	YVTool::getInstance()->initSDK(1000541, FileUtils::getInstance()->getWritablePath(),false);
    this->addListern();
}

void VoiceSdk::updateMsg(float dt)
{
    YVTool::getInstance()->dispatchMsg(dt);
}

//触发平台相关事件
void VoiceSdk::eventTracking(const char* eventtype, const char* params)
{   
    isCancel = false;
    if (Director::getInstance()->getScheduler()->isTargetPaused(this))
    {
        Director::getInstance()->getScheduler()->resumeTarget(this);
    }
    if (strcmp(params, "close") == 0)
    {
        Director::getInstance()->getScheduler()->pauseTarget(this);
        YVTool::getInstance()->stopPlay();
        YVTool::getInstance()->stopRecord();
        isCancel = true;
        AudioEngine::resumeAll();
    }
	if (strcmp(params, "InitLogin") == 0)
    {
        YVTool::getInstance()->cpLogin(eventtype, eventtype);
    }

	if (strcmp(params, "Record") == 0)
    {
        AudioEngine::pauseAll();
        YVTool::getInstance()->startRecord(RECODEPATH);
    }

	if (strcmp(params, "StopRecord") == 0 )
    {
        YVTool::getInstance()->stopRecord();
        if (strcmp(eventtype, "cancel") == 0)
        {
            isCancel = true;
        }
    }
    
	if (strcmp(params, "Play") == 0 )
    {
        AudioEngine::pauseAll();
        YVTool::getInstance()->playRecord(url,RECODEPATH);
    }
    
	if (strcmp(params,"StopPlay") == 0)
    {
        YVTool::getInstance()->stopPlay();
    }

	if (strcmp(params, "Upload") == 0 )
    {
        YVTool::getInstance()->upLoadFile(RECODEPATH);
    }

	if (strcmp(params, "Download") == 0)
    {   
        url = "";
        url.append(eventtype);
        //CCLOG(">>>>>>>>>>>>>>>>>>>>>>>>>>down:%s",eventtype);
        if (url != "")
        {
            YVTool::getInstance()->downLoadFile(url, DOWNPATH);
        }
        
    }

	if (strcmp(params,"Recognizes") == 0 )
    {
        YVTool::getInstance()->speechVoice(RECODEPATH, "", true);
    }

	if (strcmp(params, "StopRecognizes") == 0)
    {
        //YVTool::getInstance()->stopSpeech();
    }

	if (strcmp(params, "PlayDownload") == 0)
    {
        AudioEngine::pauseAll();
        YVTool::getInstance()->playRecord(url, "", "");   //只云播放
    }

	if (strcmp(params, "getUserInfo") == 0)
    {
        YVTool::getInstance()->getCPUserInfo(300000, "123456");
    }
}

void VoiceSdk::addListern()
{
    YVTool::getInstance()->addDownLoadFileListern(this);
    YVTool::getInstance()->addFinishPlayListern(this);
    YVTool::getInstance()->addFinishSpeechListern(this);
    YVTool::getInstance()->addLoginListern(this);
    YVTool::getInstance()->addReConnectListern(this);
    YVTool::getInstance()->addStopRecordListern(this);
    YVTool::getInstance()->addUpLoadFileListern(this);
    YVTool::getInstance()->addRecordVoiceListern(this);
}

void VoiceSdk::onLoginListern(CPLoginResponce* r )
{   
    std::string str;
    if (r->result != 0)
    {
        str.append("login Error:");
        str.append(r->msg);
    }
    else
    {
        YVTool::getInstance()->setRecord(60, true);
        std::stringstream ss;
        ss << "login succeed" << "UId:";
        ss << r->userid;
        str.append(ss.str());
    }
}

void VoiceSdk::onReConnectListern(ReconnectionNotify* r)
{
    std::stringstream ss;
    ss << "ReConnect, UI:";
    ss << r->userid;
}

void VoiceSdk::onStopRecordListern(RecordStopNotify* r)
{
    std::stringstream ss;
    std::string str;
    ss << " time:" << r->time << " \npath:" << r->strfilepath;
    AudioEngine::resumeAll();
    ss>>str;
    std::cout << str << std::endl;
    
    if (isCancel)
    {
        return;
    }
    this->eventTracking("1", "Upload");
}

void VoiceSdk::onFinishSpeechListern(SpeechStopRespond* r)
{
    std::stringstream ss;    
    std::string str;
    ss << "<FinishSpeech>" << "\n err_id:" << r->err_id << "\n Erro msg:" << r->err_msg 
        << "\n result:" << r->result;
    
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    int top = lua_gettop(L);
    lua_getglobal(L,"voiceEventHandlerLua");
    lua_pushstring(L, httpurl.c_str());
    lua_pushstring(L, r->result.c_str());
    lua_pcall(L,2,0,0);
    lua_settop(L,top);
}

void VoiceSdk::onFinishPlayListern(StartPlayVoiceRespond* r)
{
    std::stringstream ss;
    ss << "<Finish Play>";
    AudioEngine::resumeAll();
}

void VoiceSdk::onUpLoadFileListern(UpLoadFileRespond* r)
{   httpurl = "";
    std::stringstream ss;
    ss << "<UpLoad File>" << " result id:" << r->result
        << " erro Msg:" << r->msg << " url:"
        << r->fileurl << " \n percent:" << r->percent;
    if (r->result == 0)
    {
        url.clear();
        url.append(r->fileurl);
    }
    
    httpurl.append(r->fileurl);
    this->eventTracking("1", "Recognizes");
}

void VoiceSdk::onDownLoadFileListern(DownLoadFileRespond* r)
{
    std::stringstream ss;
    ss << "<DownLoad File>" << " result id:" << r->result
        << "  erro Msg:" << r->msg << " \npath:"
        << r->filename << "\n percent:" << r->percent;
    
    this->eventTracking("1", "PlayDownload");
}

void VoiceSdk::onRecordVoiceListern(RecordVoiceNotify* r)
{
}
