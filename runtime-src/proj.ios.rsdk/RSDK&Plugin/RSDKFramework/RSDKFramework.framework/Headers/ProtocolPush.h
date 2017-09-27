/** @file PluginFactory.h
 */
#ifndef __CCX_PROTOCOL_PUSH_H__
#define __CCX_PROTOCOL_PUSH_H__

#include "PluginProtocol.h"
#include <map>
#include <list>
#include <string>
using namespace std;

namespace rsdk { namespace framework {
/** @brief Plugin_type enum, with inline docs */
typedef enum
{
	kPushReceiveMessage = 0,/**value is callback of Receiving Message . */


} PushActionResultCode;
class ProtocolPush;
/**   
 *@class  PushActionListener
 *@brief the interface of Push callback  
 */
class PushActionListener
{
public:
	/**   
	 *@brief the interface of Push callback 
	 *@param the adatper of plugin
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg) = 0;
};
/**   
 *  @class  ProtocolPush  
 */
class ProtocolPush : public PluginProtocol
{
public:


    /**
     *@brief start/register  Push services
     *@return void
     */
    void startPush();


    /**
     *@brief close Push services
     *@return void
     */
    void closePush();


    /**
     *@brief set alias
     *@param tags
     *@return void
     */
    void setAlias(string alias);

    /**
     *@brief del alias
     *@param tags
     *@return void
     */
    void delAlias(string alias);

    /**
     *@brief set tag
     *@param tags
     *@return void
     */
    void setTags(list<string> tags);

    /**
     *@brief delete tag
     *@param tags
     *@return void
     */
    void delTags(list<string> tags);

    /**
     @brief set the result listener
     @param pListener The callback object for push result
     */
    void setListener(PushActionListener* listener);

    /**
     @brief get pListener The callback object for Push result
     @return the listener
     */
    PushActionListener* getListener();

    std::string getPluginId();

};

}} // namespace rsdk { namespace framework {

#endif /* __CCX_PROTOCOL_PUSH_H__ */
