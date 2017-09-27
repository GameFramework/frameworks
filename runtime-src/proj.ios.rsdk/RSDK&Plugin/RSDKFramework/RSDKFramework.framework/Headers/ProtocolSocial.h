/** @file ProtocolSocial.h
 */
#ifndef  __CCX_PROTOCOL_SOCIAL_H__
#define  __CCX_PROTOCOL_SOCIAL_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace rsdk { namespace framework {
/// \typedef std::map<std::string, std::string> TSocialDeveloperInfo
/// typedef TSocialDeveloperInfo.
typedef std::map<std::string, std::string> TSocialDeveloperInfo;
/// \typedef std::map<std::string, std::string> TAchievementInfo
/// typedef TAchievementInfo.
typedef std::map<std::string, std::string> TAchievementInfo;

typedef std::map<std::string, std::string> TInviteDataInfo;
    
typedef std::map<std::string, std::string> TGetMyInfoDataInfo;
    
typedef std::map<std::string, std::string> TGetFriendDataInfo;
/** @brief SocialRetCode enum, with inline docs */
typedef enum
{
    // code for leaderboard feature
	kScoreSubmitSucceed =1,/**< enum value is callback of succeeding in submiting. */
    kScoreSubmitfail,/**< enum value is callback of failing to submit . */

    // code for achievement feature
    kAchUnlockSucceed,/**< enum value is callback of succeeding in unlocking. */
    kAchUnlockFail,/**< enum value is callback of failing to  unlock. */

    kSocialSignInSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignInFail,/**< enum value is callback of failing to  login. */

    kSocialSignOutSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignOutFail,/**< enum value is callback of failing to  login. */

    kSocialGetMyInfoSucceed,
    kSocialGetMyInfoFailed,
    
    kSocialGetFriendSucceed,
    kSocialGetFriendFailed,
    
    kSocialInviteSucceed,
    kSocialInviteFailed,
    kSocialInviteCanceled,
    kSocialInviteRefuse,
    
    kSocialDeepLinkData,
} SocialRetCode;
/**   
 *@class  SocialListener
 *@brief the interface of social callback  
 */
class SocialListener
{
public:
	/**   
	 *@brief the interface of social callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onSocialResult(SocialRetCode code, const char* msg) = 0;
};

/**   
 *@class  ProtocolSocial
 *@brief the interface of social  
 */
class ProtocolSocial : public PluginProtocol
{
public:

    /**
     @brief user signIn
     */
	void signIn();

    /**
     @brief user signOut
     */
	void signOut();

    /**
     @brief submit the score
     @param leaderboardID
     @param the score
     */
	void submitScore(const char* leadboardID, long score);
     /**
      @brief show the id of Leaderboard page
      @param leaderboardID
      */
	void showLeaderboard(const char* leaderboardID);

    /**
     @brief methods of achievement feature
     @param the info of achievement
     */
    void unlockAchievement(TAchievementInfo achInfo);
    /**
     @brief show the page of achievements
     */
    void showAchievements();
    /**
     @brief set pListener The callback object for user result
     @param the listener
     */
    void setListener(SocialListener* listener);
    /**
     @brief get pListener The callback object for social result
     @return the listener
     */
    void invite(TInviteDataInfo info);
    
    void getMyInfo(TGetMyInfoDataInfo info);
    
    void getFriend(TGetFriendDataInfo info);
    
    SocialListener* getListener();
    
    std::string getPluginId();

};

}} // namespace rsdk { namespace framework {

#endif   /* ----- #ifndef __CCX_PROTOCOL_SOCIAL_H__ ----- */
