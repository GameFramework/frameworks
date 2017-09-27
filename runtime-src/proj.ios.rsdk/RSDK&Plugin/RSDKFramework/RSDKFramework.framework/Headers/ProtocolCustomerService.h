//
//  ProtocolCustomerService.h
//  RSDKFramework
//
//  Created by 邹明明 on 16/11/21.
//

#ifndef ProtocolCustomerService_h
#define ProtocolCustomerService_h

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace rsdk { namespace framework {
    /// typedef LogEventParamMap.
    typedef std::map< std::string, std::string >    CustomerServiceParamMap;
    /** @brief Plugin_type enum, with inline docs */
    //预留回调接口代码
//    typedef enum
//    {
//        showCustomerServiceSuccess = 0,/**value is callback of show customer service is success . */
//        showCustomerServiceFail = 0,/**value is callback of show customer service is fail . */
//        
//    }CustomerServiceActionResultCode;
    class ProtocolCustomerService;
    /**
      *@class  PushActionListener
     *@brief the interface of Push callback
     */
    //预留回调接口代码
//    class CustomerServiceListener
//    {
//    public:
//        /**
//         *@brief the interface of Push callback
//         *@param the adatper of plugin
//         *@param the id of callback
//         *@param the information of callback
//         */
//        virtual void onActionResult(ProtocolCustomerService* pPlugin, CustomerServiceActionResultCode code, const char* msg) = 0;
//    };
    /**
      *  @class  ProtocolPush
     */
    class ProtocolCustomerService : public PluginProtocol
    {
    public:
        
        
        /**
         *@brief 显示客服中心
         *@return void
         */
        void showCustomerService(CustomerServiceParamMap* Param);
        
        
        /**
         *@brief 显示联系我们
         *@return void
         */
        void showContactus(CustomerServiceParamMap* Param);
        
        
        /**
         *@brief 显示帮助
         *@return void
         */
        void showHelpe(CustomerServiceParamMap* Param);
        
        /**
         *@brief show FAQ
         *@return void
         */
        void showFAQ(CustomerServiceParamMap* Param);
        
        //预留回调接口代码
        /**
         @brief set the result listener
         @param pListener The callback object for customer service result
         */
        //void setListener(CustomerServiceListener* listener);
        
        /**
         @brief get pListener The callback object for customer service result
         @return the listener
         */
        //CustomerServiceListener* getListener();
        
        std::string getPluginId();
        
    };
    
}} // namespace rsdk { namespace framework {

#endif /* ProtocolCustomerService_h */
