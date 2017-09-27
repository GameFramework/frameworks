/** @file PluginProtocol.h
 */
#ifndef __CCX_IPLUGIN_H__
#define __CCX_IPLUGIN_H__

#include "PluginParam.h"
#include <vector>

namespace rsdk { namespace framework {

/**
 * 	@class PluginProtocol
 *	@brief	The super class for all plugins.
 */
class PluginProtocol
{
public:
    virtual ~PluginProtocol();
    /**
     *@brief set plugin name
     *@param the name of plugin
    */
	void setPluginName(const char* name);
    /**
     *@brief get plugin name
     *@return the name of plugin
    */
	const char* getPluginName();

    /**
     *@brief get the version of plugin
     *@return the version of plugin
    */
	std::string getPluginVersion();
    /**
     *@brief get the version of sdk
     *@return the version of sdk
    */
	std::string getSDKVersion();

    /**
     *@brief switch debug plug-in on/off
     *@param the value of on/off
    */
	void setDebugMode(bool bDebug);

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return void
     */
	void callFuncWithParam(const char* funcName, PluginParam* param, ...);
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return void
     */
	void callFuncWithParam(const char* funcName, std::vector<PluginParam*> params);
    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return string
     */
	std::string callStringFuncWithParam(const char* funcName, PluginParam* param, ...);
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return string
     */
	std::string callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return int
     */
	int callIntFuncWithParam(const char* funcName, PluginParam* param, ...);
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return int
     */
	int callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return bool
     */
	bool callBoolFuncWithParam(const char* funcName, PluginParam* param, ...);
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return bool
     */
	bool callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return float
     */
	float callFloatFuncWithParam(const char* funcName, PluginParam* param, ...);
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return float
     */
	float callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params);
    bool isFunctionSupported(const char* functionName);

};

}} //namespace rsdk { namespace framework {

#endif /* __CCX_IPLUGIN_H__ */
