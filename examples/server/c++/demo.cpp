#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{

	std::string public_key="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+BoWf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuewv7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+OKUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPREs78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m0QIDAQAB";
	// --登录验证

	std::string loginEntity = "{\"openid\":\"1-123123\",\"account\":\"test\",\"time\":1482313093}";
	std::string	 loginSign = "m7JTn/y3IpB084vyeqoR9ysZ5/GeowcsO3KDrDsaa8Fof2Xjq4gKdk5eDLh0nTRxZslfbet5AWs+p1M0rtF8Jan8T2VxCW/czoCkrj4o/xnYtb3wdenCXAT7LUoydjTmd+cf0I9kw0DjkPDurrT9kNqxzw6dq1A6EFZAts4f0/H5+7kn81rzPq1RkWOM6OGm8R2D2WW/jHfqZDo1mvfZvIzkA/F0M62z2VsUK821BUkgoT23dByCdeqgx4hauJTHlnvg2/MplDYMDONHai6gTFWb4FQgY2wJq1BIWCyXgDuid6n9Ck0m6paJEfOffbK7BgwH3ssaF7xYGD2sjEuCFw==";
	int expire = 200;
	std::map<std::string,std::string>  retData;
	bool ret=Sdk::loginVerify( public_key, loginEntity, loginSign,expire,retData);
	if (ret)
	{
		std::cout<<"login ok "<<std::endl;
		for( std::map<std::string,std::string>::iterator itr = retData.begin(); itr != retData.end(); itr++)
		{
			std::cout<<"ret user data key="<<itr->first<<",value="<<itr->second<<std::endl;
		}
	}
	else
	{
		std::cout<<"login verify error"<<std::endl;
	}

	// --充值回调验证
	std::map<std::string, std::string > paymentPost;
	paymentPost["account"]="abcd";
	paymentPost["amount"]="6.00";
	paymentPost["black_desc"]="";
	paymentPost["channel"]="1";
	paymentPost["currency"]="";
	paymentPost["extra"]="123";
	paymentPost["game_id"]="GMG001";
	paymentPost["is_black"]="0";
	paymentPost["is_cancel"]="0";
	paymentPost["is_recovery"]="0";
	paymentPost["is_test"]="0";
	paymentPost["memo"]="";
	paymentPost["openid"]="1-1234";
	paymentPost["order_id"]="1399633295037630";
	paymentPost["order_type"]="0";
	paymentPost["original_purchase_orderid"]="";
	paymentPost["product_id"]="HWDPID0006";
	paymentPost["time"]="1404975144";
	paymentPost["transaction_id"]="1000000110081354";
	paymentPost["version"]="8.0";
	paymentPost["zone_id"]="1";
	paymentPost["sign"]="MT/Wp3jz8l8HV62/OrpXdDIdEF9BGw8zCtwu8VZNaxCi52QXCC7RO2Q5yLRsQy8SmZMk0h0hsxUOXSZ8zZysUL+r/ATVknUs76zveaHROAfqhwo4sBqNA3jvnkCtbV/x9vF46vmNB7tDJcG6UDrJM5a/9Bn3Xq0ctlfSJpqJskr4dqyIlvCbQyi2YtnW2f5aNWATyNUntWtzakXYxZ7mPVT7hhspREo/3v/YcygmUHJJsJ2NnqkyWH7kV3nTTtvTQirjbzgeqnFd+KZBBHuBxOXDZInNLcaTnOQLskRddt0sYJ9/L8aDx9AvZtMe8kgQJhlNq13JOLFbCoMAEHD4Gg==";

	std::map<std::string,std::string> gameOrder;
	gameOrder["product_id"]="HWDPID0006";
	gameOrder["amount"]="6.00";

	if( !Sdk::paymentVerify(public_key,paymentPost))
	{ //验证失败了
		std::cout<<"payment verify error"<<std::endl;
		return 0;
	}	

	std::cout<<"payment verify success"<<std::endl;

	//发送玩家在线数据
	std::string  loginKey = "111111";
	std::map<std::string, std::string > online_data ;
	online_data["game_id"]="1000";
	online_data["zone_id"]="1";
	online_data["number"]="99";
	if (Sdk::gameOnline(loginKey, online_data))
	{
		std::cout<<"game online ok"<<std::endl;
	}
	else
	{
		std::cout<<"game online failed"<<std::endl;
	}

	//发送登录数据
	std::map<std::string,std::string> loginLogs;		
	loginLogs["game_id"] = "1000";
	loginLogs["channel_id"] = "1";
	loginLogs["ip"] = "192.168.100.1";
	loginLogs["openid"] = "1-123456";
	loginLogs["device_udid"] = "860529036567763";
	loginLogs["device_type"]= "vivo Y51";
	loginLogs["os"]= "android";
	if( Sdk::loginLogs(loginKey,loginLogs))
	{
		std::cout<<"send login logs success"<<std::endl;
	}
	else
	{
		std::cout<<"send login logs failed"<<std::endl;
	}

	// 向客户端push消息测试
	std::map<std::string,std::string> pushData;	
	pushData["game_id"]= "1000";
	pushData["channel_id"]= "1";
	pushData["environment"]= "product";
	pushData["audience_type"]= "account";
	pushData["audience_list"]= "1-123456";
	pushData["message_type"]= "notify";
	pushData["title"]= "test";
	pushData["content"]= "test";

	if( Sdk::push(loginKey,pushData))
	{
		std::cout<<"push success"<<std::endl;
	}
	else
	{
		std::cout<<"push failed"<<std::endl;
	}
	return 0;

}
