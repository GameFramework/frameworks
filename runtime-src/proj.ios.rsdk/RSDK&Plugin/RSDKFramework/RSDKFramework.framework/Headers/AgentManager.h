/** @file AgentManager.h
 */


#ifndef __CCX_AGENTMANAGER_H__
#define __CCX_AGENTMANAGER_H__

#include "PluginManager.h"
#include "ProtocolIAP.h"
#include "ProtocolAnalytics.h"
#include "ProtocolShare.h"
#include "ProtocolAds.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "ProtocolPush.h"
#include "ProtocolInit.h"
#include "ProtocolCustomerService.h"
#include <map>
#include <string>
namespace rsdk { namespace framework {

/**   
 *  @class  AgentManager  
 */
class AgentManager
{
public:
	virtual ~AgentManager();
    /**
     @brief Get singleton of AgentManager
     */

    static AgentManager* getInstance();
    /**
     @brief Destory the instance of AgentManager
     */
    static void end();
    
    /**
    @breif the init of AgentManager
    @param the appKey of plugin-x
    @param the appSecret of plugin-x
    @param the privateKey of plugin-x
    @param the url of oauthLoginServer
    @warning Must invoke this interface before loadALLPlugin
    */
    void init(std::string appKey,std::string appSecret,std::string privateKey,std::string oauthLoginServer);

    /**
     @brief load the plugins
     */
    void loadALLPlugin();
    /**
     @brief unload the plugins
     */
    void unloadALLPlugin();

    /**
     @brief Get User plugin
     @return  if User plugin exist ,return value is User plugin.
     	 	  else return value is null pointer.
     */
    //ProtocolUser* getUserPlugin(){return _pUser;};
    
    std::map<std::string , ProtocolUser*>* getUserPlugin(){return &_pluginsUserMap;};

    /**
     @brief Get IAP plugin
     @return  if IAP plugin exist ,return value is IAP plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolIAP*>* getIAPPlugin(){return &_pluginsIAPMap;};

    /**
     @brief Get Share plugin
     @return  if Share plugin exist ,return value is Share plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolShare*>* getSharePlugin(){return &_pluginsShareMap;};

    /**
     @brief Get Social plugin
     @return  if Social plugin exist ,return value is Social plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolSocial*>* getSocialPlugin(){return &_pluginsSocialMap;};

    /**
     @brief Get Ads plugin
     @return  if Ads plugin exist ,return value is Ads plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolAds*>* getAdsPlugin(){return &_pluginsAdsMap;};
    
    /**
     @brief Get Push plugin
     @return  if Push plugin exist ,return value is Push plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolPush*>* getPushPlugin(){return &_pluginsPushMap;};
    
    std::map<std::string , ProtocolAnalytics*>* getAnalyticsPlugin(){return &_pluginsAnalyticsMap;};
    
    std::map<std::string , ProtocolCustomerService*>* getCustomerServicePlugin(){return &_pluginsCustomerServiceMap;};

    /**
     @brief Get channel ID
     @return  return value is channel ID.
     */
    std::string getChannelId();

    /**
     @brief Get custom param
     @return  return value is custom param for channel.
     */
    std::string getCustomParam();
    
    void setIsAnaylticsEnabled(bool value){bIsAnaylticsEnabled = value;};
    bool isAnaylticsEnabled(){return bIsAnaylticsEnabled;};

    void setDebugMode(bool flag);
    
protected:
    
    std::string getFileData(const char* pFileName);
    void loadPlugin(const char* nodeName,int type);
    std::map<std::string, std::string> getPluginConfigure();

private:
    AgentManager(void);
    
    // Analytics plugins
    ProtocolAnalytics* _pAnalytics;

    // user plugins
    //ProtocolUser* _pUser;
    std::map<std::string , ProtocolUser*> _pluginsUserMap;

    // IAP plugins
    //    ProtocolIAP* _pIAP;
    std::map<std::string , ProtocolIAP*> _pluginsIAPMap;

    // Share plugins
    std::map<std::string , ProtocolShare*> _pluginsShareMap;

    // Social plugins
    std::map<std::string , ProtocolSocial*> _pluginsSocialMap;

    // Ads plugins
    std::map<std::string , ProtocolAds*> _pluginsAdsMap;
    
    // Push plugins
    std::map<std::string , ProtocolPush*> _pluginsPushMap;
    
    //Anayltics Plugins
    std::map<std::string , ProtocolAnalytics*> _pluginsAnalyticsMap;
    
    //CustomerService Plugins
    std::map<std::string , ProtocolCustomerService*> _pluginsCustomerServiceMap;

    bool bIsAnaylticsEnabled;

};

}} //namespace rsdk { namespace framework {

#endif /* __CCX_AGENTMANAGER_H__ */
