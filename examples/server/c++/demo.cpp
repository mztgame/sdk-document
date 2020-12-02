#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{

	std::string public_key="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+BoWf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuewv7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+OKUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPREs78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m0QIDAQAB";

	/**********************************************************
	 * 登录验证
	 **********************************************************/
	//构造测试数据,客户端sdk返回的整个json包
	std::string jsonobj= "{\"entity\":{\"openid\":\"1-123123\",\"account\":\"test\",\"time\":1482313093},\"sign\":\"m7JTn/y3IpB084vyeqoR9ysZ5/GeowcsO3KDrDsaa8Fof2Xjq4gKdk5eDLh0nTRxZslfbet5AWs+p1M0rtF8Jan8T2VxCW/czoCkrj4o/xnYtb3wdenCXAT7LUoydjTmd+cf0I9kw0DjkPDurrT9kNqxzw6dq1A6EFZAts4f0/H5+7kn81rzPq1RkWOM6OGm8R2D2WW/jHfqZDo1mvfZvIzkA/F0M62z2VsUK821BUkgoT23dByCdeqgx4hauJTHlnvg2/MplDYMDONHai6gTFWb4FQgY2wJq1BIWCyXgDuid6n9Ck0m6paJEfOffbK7BgwH3ssaF7xYGD2sjEuCFw==\"}";

	std::cout<<jsonobj.c_str()<<std::endl;
	int expire = 200;
	//返回的登录数据
	std::map<std::string,std::string>  retData;

	//处理过程
	bool ret=Sdk::loginVerify( public_key, jsonobj, expire,retData);
	if (ret)
	{
		std::cout<<"login ok "<<std::endl;
		for( std::map<std::string,std::string>::iterator itr = retData.begin(); itr != retData.end(); itr++)
		{
			std::cout<<"ret user data key="<<itr->first.c_str()<<",value="<<itr->second.c_str()<<std::endl;
		}
	}
	else
	{
		std::cout<<"login verify error"<<std::endl;
	}
	/**********************************************************
	 * 充值回调验证
	 **********************************************************/
	// 构造测试数据
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
	// 测试订单数据
	std::map<std::string,std::string> gameOrder;
	gameOrder["product_id"]="HWDPID0006";
	gameOrder["amount"]="6.00";

	//处理过程
	//返回给充值平台的消息内容,返回json给调用接口的链接
	std::string  retString="{\"code\":2,\"msg\":\"签名验证失败\"}";

	if( !Sdk::paymentVerify(public_key,paymentPost))
	{ //验证失败了
		retString="{\"code\":2,\"msg\":\"签名验证失败\"}";
		return 0;
	}	
	else
	{
		//游戏服务端根据order_id判断订单是否已经处理过，游戏服务端自行实现
		//测试订单，如果游戏不允许测试订单通知，则返回echo '{"code":2,"msg":"不允许测试订单通知"}';
		if (paymentPost["is_test"] == "1" ) 
		{
			retString="{\"code\":2,\"msg\":\"不允许测试订单通知\"}";
			return 0;
		}
		//风控拦截订单，游戏不能发货，游戏接收到此类订单通知时，可以通过邮件或其他方式告诉用户充值不到账原因和如何解决问题;
		if (paymentPost["is_black"] == "1") {
			retString="{\"code\":0,\"msg\":\"风控拦截订单通知\"}";
			return 0;
		}

		//恢复购买订单，仅苹果、谷歌支付非消耗型商品才能恢复购买操作，游戏接收到此类订单通知时，请特殊标识，以与正常支付订单区分
		if (paymentPost["is_recovery"] == "1") {
			retString="{\"code\":0,\"msg\":\"恢复购买订单通知\"}";
			return 0;
		}

		//取消购买订单，仅自动续订订阅型商品才有取消购买操作，游戏接收到此类订单通知时，请撤消之前的订单购买状态，并标识原订阅商品不可用
		if (paymentPost["is_cancel"]=="1") {
			retString="{\"code\":0,\"msg\":\"取消购买订单通知\"}";
			return 0;
		}

		//验证product_id和金额是否匹配
		if (gameOrder["product_id"] != paymentPost["product_id"]) {
			retString="{\"code\":2,\"msg\":\"商品不存在\"}";
			return 0;
		}
		//验证金额是否正确
		if (gameOrder["amount"] != paymentPost["amount"]) {
			retString="{\"code\":2,\"msg\":\"金额错误\"}";
			return 0;
		}

		//游戏发货

		//发货成功，返回：echo '{"code":0,"msg":"成功"}';
		retString="{\"code\":0,\"msg\":\"成功\"}";

		//游戏发货失败，需要再次通知，返回
		//retString="{\"code\":1,\"msg\":\"数据库错误\"}";

	}


	/**********************************************************
	 * 在线人数实时统计
	 **********************************************************/
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

	/**********************************************************
	 * 游戏登录数据上报
	 **********************************************************/
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

	/**********************************************************
	 * 推送消息
	 **********************************************************/
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

	/**********************************************************
     * 兑换礼包码
     **********************************************************/
    std::map<std::string,std::string> giftData;
    giftData["game_id"]= "1000";
    giftData["channel_id"]= "1";
    giftData["plat"]= "android";
    giftData["area"]= "0";
    giftData["partition"]= "1";
    giftData["uid"]= "1-123456";
    giftData["char_id"]= "78910";
    giftData["from"]= "";
    giftData["gakey"]= "8B8CM5VP";

    if( Sdk::giftUse(loginKey,giftData))
    {
        std::cout<<"gift use success"<<std::endl;
    }
    else
    {
        std::cout<<"gift use failed"<<std::endl;
    }

	return 0;

}
