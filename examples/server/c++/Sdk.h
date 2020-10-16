#ifndef  _SDK_H__
#define  _SDK_H__


#include "CryptHelper.h"

namespace Sdk
{
	bool loginVerify(const std::string &publicKey , const std::string &jsonobj,int expire , std::map<std::string,std::string> & retData) ;
	bool paymentVerify(const std::string &publicKey, const std::map<std::string,std::string> &postData);
	//游戏在线人数上报，http请求会阻塞
	bool gameOnline(const std::string &loginkeys,const std::map<std::string,std::string> &datas);
	// 上报登录日志记录, http请求会阻塞
	bool loginLogs(const std::string &loginkeys,const std::map<std::string,std::string> & datas);
	// push消息, http请求会阻塞
	bool push(const std::string & loginkeys, const std::map<std::string,std::string> &datas);
	// 兑换礼包码, http请求会阻塞
    bool giftUse(const std::string & loginkeys, const std::map<std::string,std::string> &datas);
}



#endif


