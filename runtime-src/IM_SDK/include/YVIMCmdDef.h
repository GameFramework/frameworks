#ifndef _YVIM_CMDDEF_H__
#define _YVIM_CMDDEF_H__





/*******************************登录模块********************************
*
*			              模块类型: IM_LOGIN
*
***********************************************************************/

//云娃登录请求
#define IM_LOGIN_REQ                   0x11000
namespace x11000{
	enum{
		/*uint32*/	 userid				= 1, //用户ID
		/*string*/	 pwd				= 2, //用户密码
		/*string*/	 pgameServiceID		= 3, //游戏服务ID
	};
}

//云娃登录返回
#define IM_LOGIN_RESP	               0x11001
namespace x11001 {
	enum {
		/*uint32*/ result		= 1, //返回结果 不为0即为失败
		/*string*/ msg			= 2, //错误描述
		/*string*/ nickname		= 4, //用户昵称
		/*uint32*/ userId		= 5, //用户ID
		/*string*/ iconurl		= 6, //用户图像地址
	};
}


//cp账号登录请求
#define IM_THIRD_LOGIN_REQ				0x11002
namespace x11002{
	enum{
		/*string*/	 tt					= 1, //cp登录凭证
		/*string*/	 pgameServiceID		= 2, //游戏服务ID
	};
}

//cp账号登录返回
#define IM_THIRD_LOGIN_RESP				 0x11003
namespace x11003 {
	enum {
		/*uint32*/ result			= 1, //返回结果 不为0即为失败
		/*string*/ msg				= 2, //错误描述
		/*uint32*/ userid			= 3, //云娃ID
		/*string*/ nickName			= 4, //用户昵称
		/*string*/ iconUrl			= 5, //用户图像地址
		/*string*/ thirdUserId		= 6, //第三方用户ID
		/*string*/ thirdUserName	= 7, //第三方用户名
	};

}

//注销
#define IM_LOGOUT_REQ	                  0x11004
namespace x11004
{
}




//重连成功通知
#define IM_RECONNECTION_NOTIFY              0x11013
namespace x11013 {
	enum {
		/*uint32*/ userid        = 1,
	};
}

//获取第三方账号信息
#define IM_GET_THIRDBINDINFO_REQ            0x11014
namespace x11014 {
	enum {
		/*uint32*/ appid        = 1,   
		/*string*/ uid          = 2,
	};
}

#define IM_GET_THIRDBINDINFO_RESP           0x11015
namespace x11015 {
	enum {
		/*uint32*/ result		= 1, 
		/*string*/ msg			= 2, 
		/*uint32*/ yunvaid      = 3,   
		/*string*/ nickname     = 4,
		/*string*/ iconUrl      = 5,
		/*string*/ level        = 6,
		/*string*/ vip          = 7,
		/*string*/ ext          = 8,
	};
}

enum yv_net
{
	yv_net_disconnect = 0,
	yv_net_connect = 1,
};

//网络状态通知
#define IM_NET_STATE_NOTIFY                   0x11016
namespace x11016 {
	enum {
		/*uint8*/ state           = 1,       //yv_net
	};
}

//获取sdk信息
#define IM_GET_SDKINFO_REQ                    0x11017
namespace x11017 {
}

#define IM_GET_SDKINFO_RESP                   0x11018
namespace x11018 {
	enum {
		/*string*/ versions        = 1,     //版本号
		/*uint8*/  netstate        = 2,     //网络状态
	};
}


/*******************************附加工具模块********************************
*
*			              模块类型: IM_TOOLS
*
***************************************************************************/

//开始录音(最长60秒)  
#define	IM_RECORD_STRART_REQ	        0x19000
namespace x19000{
	enum{
		/*string*/		strfilepath	   = 1,  //录音文件保存路径(.amr), 为空则自动生成  
		/*string*/      ext            = 2,  //扩展标记     
		/*uint8*/       speech         = 3,  //1:录音完成自动识别
	};
}



//停止录音请求  回调返回录音文件路径名
#define	IM_RECORD_STOP_REQ		         0x19001


//停止录音返回  回调返回录音文件路径名
#define	IM_RECORD_STOP_RESP		         0x19002
namespace x19002{
	enum{
		/*uint32*/		time		     = 1,  //录音时长
		/*string*/		strfilepath      = 2,  //录音保存文件路径名
		/*string*/      ext              = 3,  //扩展标记
		/*uint32*/      result           = 4,  //0:成功， 非0失败
	};
}

//播放录音请求
#define	IM_RECORD_STARTPLAY_REQ		     0x19003
namespace x19003{
	enum{
		/*string*/		strUrl		= 1, //录音url
		/*string*/		strfilepath	= 2, //录音文件路径, 为空则自动生成  
		/*string*/      ext         = 3,  //扩展标记

	};
}

//播放语音完成
#define	IM_RECORD_FINISHPLAY_RESP	     0x19004
namespace x19004{
	enum{
		/*uint32*/     result      = 1, //播放结果，0：成功
		/*string*/     describe	   = 2, //描述
		/*string*/     ext         = 3, //扩展标记
	};
}

//播放URL下载进度
#define	IM_RECORD_PLAY_PERCENT_NOTIFY     0x19016
namespace x19016{
	enum{
		/*uint8*/      percent     = 1, //播放URL，下载进度百分比
		/*string*/     ext         = 2, //扩展标记

	};
}



//停止播放语音
#define	IM_RECORD_STOPPLAY_REQ		    0x19005
namespace x190005
{
}

enum yvspeech
{
	speech_file = 0,              //文件识别
	speech_file_and_url = 1,      //文件识别返回url
	speech_url = 2,               //url识别
	speech_live = 3,              //实时语音识别(未完成)
};

//开始语音识别
#define IM_SPEECH_START_REQ		        0x19006
namespace x19006{
	enum{
		/*string*/	  strfilepath	= 1,  //语音文件
		/*string*/    ext           = 2,  //扩展标记
		/*uint8*/     type          = 3,  //识别类型 yvspeech
		/*string*/    url           = 4,  //识别URL
	};
}


//语音识别完成返回
#define IM_SPEECH_STOP_RESP				0x19009
namespace x19009{
	enum{
		/*uint32*/		err_id     = 1,  //0为成功
		/*string*/		err_msg    = 2,  //返回的错误描述
		/*string*/		result	   = 3,  //结果
		/*string*/      ext        = 4,  //扩展标记
		/*string*/      url        = 5,  //文件上传返回URL
	};

}


//设置语音识别语言
#define IM_SPEECH_SETLANGUAGE_REQ	     0x19008
namespace x19008{
	enum{
		/*uint8*/	inlanguage     = 1,     //yvimspeech_language
		/*uint8*/   outlanguage    = 2,     //yvimspeech_outlanguage
	};
}

//语音识别类型
enum yvimspeech_language
{
	im_speech_zn = 1, //中文
	im_speech_ct = 2, //粤语
	im_speech_en = 3, //英语
};

//语音识别返回语言类型
enum yvimspeech_outlanguage
{
	im_speechout_simplified       = 0,  //简体中文
	im_speechout_traditional      = 1,  //繁体中文
};


//上传文件
#define IM_UPLOAD_FILE_REQ				  0x19010
namespace x19010{
	enum{
		/*string*/		filename   = 1,   //文件路径
		/*string*/      fileid     = 2,   //文件ID(文件返回标示)
	};
}

//上传文件回应
#define IM_UPLOAD_FILE_RESP		          0x19011
namespace x19011{
	enum{
		/*uint32*/		result	    = 1,   //结果
		/*string*/      msg         = 2,   //错误描述
		/*string*/      fileid      = 3,   //文件ID
		/*string*/      fileurl     = 4,   //返回文件地址
		/*uint32*/      percent     = 5,   //完成百分比
	};
}


//下载文件请求 
#define IM_DOWNLOAD_FILE_REQ              0x19012
namespace x19012 {
	enum {
		/*string*/      url         = 1,   //下载地址
		/*string*/      filename    = 2,   //文件路径, 为空则自动生成
		/*string*/      fileid      = 3,   //文件ID
	};
}

//下载文件回应
#define IM_DOWNLOAD_FILE_RESP             0x19013
namespace x19013 {
	enum {
		/*uint32*/		result	     = 1,   //结果
		/*string*/      msg          = 2,   //错误描述
		/*string*/      filename     = 3,   //文件名   
		/*string*/      fileid       = 4,   //文件ID
		/*uint32*/      percent      = 5,   //完成百分比
	};
}

//设置录音信息
#define	IM_RECORD_SETINFO_REQ	           0x19014
namespace x19014{
	enum{
		/*uint32*/		times	      = 1,   //录音最大时长(秒)， 默认60s
		/*uint8*/       volume        = 2,   //录音音量回调， 1：开启， 0：关闭
		/*uint8*/		rate		  = 3,	 //录音码率，0:低 1：中 2：高， 默认为2
	};
}

//录音声音大小通知
#define	IM_RECORD_VOLUME_NOTIFY	           0x19015
namespace x19015{
	enum{
		/*string*/      ext           = 1,  //扩展标记
		/*uint8*/       volume        = 2,  //音量大小(0-100)
	};
}


//判断URL文件是否存在  
#define IM_TOOL_HAS_CACHE_FILE              0x19017
namespace x19017{
	enum
	{
		/*string*/      url             = 1, 
	};
}

//获取URL对应的文件路径
#define IM_GET_CACHE_FILE_REQ               0x19018  
namespace x19018{
	enum
	{
		/*string*/      url             = 1, 
	};
}

#define IM_GET_CACHE_FILE_RESP               0x19019 
namespace x19019{
	enum
	{
		/*uint32*/		result			= 1,   //结果
		/*string*/      msg				= 2,   //错误描述
		/*string*/      url             = 3, 
		/*string*/      filepath        = 4,   //获取返回文件
	};
}

//清除所以缓存
#define IM_CACHE_CLEAR                        0x19020
namespace x19020{

}


#endif



