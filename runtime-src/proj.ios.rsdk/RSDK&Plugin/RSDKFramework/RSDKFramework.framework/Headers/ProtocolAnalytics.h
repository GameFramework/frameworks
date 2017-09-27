/** @file ProtocolAnalytics.h
 */
#ifndef __CCX_PROTOCOL_ANALYTICS_H__
#define __CCX_PROTOCOL_ANALYTICS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace rsdk { namespace framework {
/// \typedef std::map<std::string, std::string> LogEventParamPair
/// typedef LogEventParamPair.
typedef std::pair< std::string, std::string >   LogEventParamPair;
/// \typedef std::map<std::string, std::string> LogEventParamMap
/// typedef LogEventParamMap.
typedef std::map< std::string, std::string >    LogEventParamMap;
typedef enum {
    /*
     注册/创建角色
     */
    ANA_REGISTED=1,
    /*
     登录
     */
    ANA_LOGINED=2,
    /*
     创建订单
     */
    ANA_CREATEORDER=3,
    /*
     添加商品
     */
    ANA_ADDPRODUCT=4,
    /*
     支付成功
     */
    ANA_PAYSUCCESS=5,
    /*
     创建订单成功
     */
    ANA_CREATEORDERSUCCESS=6,
    /*
     
     */
    ANA_UNKNOW=7,
    /*
     完成任务
     */
    ANA_TASKFINISH=8,
    /*
     任务失败
     */
    ANA_TASKFAILED=9,
    /*
     设置年龄
     */
    ANA_SETAGE=10,
    /*
     设置性别
     */
    ANA_SETSEX=11,
    /*
     角色升级
     */
    ANA_UPLEVEL=12,
    /*
     统计安装
     */
    ANA_INSTALLED=13,
    /*
     新手引导结束
     */
    ANA_USERGUIDEFINISH=14
} AnalyticsType;
/**   
 *@class  ProtocolAnalytics
 *@brief the interface of Analytics
 */
class ProtocolAnalytics : public PluginProtocol
{
public:

	/**
     @brief Start a new session.
     @param appKey The identity of the application.
     */
	void startSession();
    
	/**
     @brief Stop a session.
     @warning This interface only worked on android
     */
	void stopSession();

    /**
     @brief Set the timeout for expiring a session.
     @param millis In milliseconds as the unit of time.
     @note It must be invoked before calling startSession.
     */
	void setSessionContinueMillis(long millis);

    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     */
	void logError(const char* errorId, const char* message);
    
	/**
     @brief log an event.
     @param eventId The identity of event
     @param paramMap Extern parameters of the event, use NULL if not needed.
     */
	void logEvent(LogEventParamMap* paramMap = NULL);

    /**
     @brief Track an event begin.
     @param eventId The identity of event
     */
	void logTimedEventBegin(const char* eventId);

    /**
     @brief Track an event end.
     @param eventId The identity of event
     */
	void logTimedEventEnd(const char* eventId);

	/**
     @brief Whether to catch uncaught exceptions to server.
     @warning This interface only worked on android.
     */
	void setCaptureUncaughtException(bool enabled);
    
    std::string getPluginId();
};

}} // namespace rsdk { namespace framework {


#endif /* __CCX_PROTOCOL_ANALYTICS_H__ */
