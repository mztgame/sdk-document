## 登录验证和支付验证 C++ SDK

SDK包含了如下几个功能：
- 登录数据签名验证
- 支付数据签名验证
- 上报在线人数
- 上报游戏登录数据
- 消息推送

### 使用方法

1. 引入SDK：
```c++
#include "Sdk.h"

```

2. 调用相应方法

- 登录数据签名验证

 方法说明
```c++
/**
 * 登录验证
 *
 * @param string publicKey 公钥
 * @param string loginEntity sdk客户端登录成功返回的entity，JSON字符串
 * @param string loginSign sdk客户端登录成功返回的sign
 * @param int expire 登录有效期，单位秒，如果登录信息超过此有效期，则登录失败
 * @param map<string,string> retData 验证成功后，返回entity的登录信息
 *
 * @return bool 验证失败返回false，验证成功返回true
 */
Sdk::loginVerify(publicKey, loginEntity, loginSign, expire, retData)
```

 示例
```c++
#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{

	// 公钥
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
}
```

- 支付数据签名验证
 
 方法说明
```c++
/**
 * 支付验证
 *
 * @param string publicKey 公钥
 * @param map<string,string> paymentPost sdk支付系统 HTTP POST方式通知游戏服务端，游戏服务端接收到的POST内容
 *
 * @return bool 验证失败返回false，验证成功返回true
 */
Sdk::paymentVerify(publicKey,paymentPost)
```

 示例
```c++
#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{

	// 公钥
	std::string public_key="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+BoWf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuewv7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+OKUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPREs78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m0QIDAQAB";
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
}
```
 
- 上报在线人数
	
 方法说明
```c++
/**
 * 上报实时游戏在线人数
 *
 * @param string loginKey 秘钥
 * @param map<string,string> onlineData 游戏数据，需要包含以下字段
 * [
 * "game_id" => "游戏ID",   //必填
 * "channel_id" => "渠道ID",  //可选
 * "zone_id" => "区ID",    //必填
 * "number" => "人数",  //必填
 * ]
 *
 * @return bool
 *
 */
Sdk::gameOnline(loginKey, onlineData)
```

 示例
```c++
#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{
	//  密钥
	std::string  loginKey = "111111";
	// 构造测试数据
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
}
```

- 上报游戏登录数据
	
 方法说明
```c++
/**
 * 游戏登录数据上报
 *
 * @param string loginKey 秘钥
 * @param map<string,string> loginData 游戏数据，需要包含以下字段
 * [
 * "game_id" => "游戏ID",   //必填
 * "channel_id" => "渠道ID",  //必填
 * "ip" => "客户端用户IP地址",  //必填
 * "openid" => "用户ID",  //必填
 * "device_udid" => "设备标识码",  //必填
 * "device_type" => "设备型号",    //必填
 * "os" => "设备系统类型，例如ios、android" ,  //必填
 * "ad_id" => "广告ID",  //选填
 * "zone_id" => "区服ID",  //选填
 * "zone_name" => "区服名称",  //选填
 * "char_id" => "角色ID",  //选填
 * "char_name" => "角色名称",  //选填
 * "level" => "等级or段位",  //选填
 * "sync" => "同步数据到beacon 1010",  //选填
 * "log_type" => "日志类型,默认2 (1:账号登录,2:游戏区登录,3:账号+游戏区登录)",  //选填
 * ]
 *
 * @return bool
 *
 */
Sdk::loginLogs(loginKey, loginData)
```

 示例
```c++
#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{
	//  密钥
	std::string  loginKey = "111111";
	// 构造测试数据
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
}
```

- 消息推送
	
 方法说明
```c++
/**
 * 推送消息
 *
 * @param string loginKey 秘钥
 * @param map<string,string> pushData 推送内容，需要包含以下字段
 * [
 * "game_id" => "游戏ID",   //必填
 * "channel_id" => "渠道ID",  //必填
 * "environment" => "推送环境(仅IOS，默认生产环境)，生产环境:product 开发环境:dev",  //选填
 * "message_type" => "消息类型，通知消息:notify 透传消息:message",  //必填
 * "title" => "消息标题",  //必填
 * "content" => "消息内容",    //必填
 * "audience_type" => "推送目标，全量推送:all 单账号推送:account 账号列表推送:account_list" ,  //必填
 * "audience_list" => "账号列表，当audience_type等于account时必须填写单个账号openid；当audience_type等于account_list时必须填写多个openid，以逗号分隔",  //选填
 * "custom_content" => "定义的键值对，json格式如：{"key1":"value1","key2":"value2"}",  //选填
 * "send_time" => "指定推送时间，格式为yyyy-MM-DD HH:MM:SS",  //选填
 * "loop_times" => "循环任务重复次数，建议取值[1, 15]",  //选填
 * "loop_interval" => "循环执行消息下发的间隔，必须配合loop_times使用，以天为单位，取值[1, 14]",  //选填
 * ]
 *
 * @return bool
 *
 */
Sdk::push(loginKey, pushData)

```

 示例
```c++
#include <iostream>
#include <string.h>
#include "Sdk.h"
#include <map>

int main(int argc, char ** argv)
{
	//  密钥
	std::string  loginKey = "111111";
	//构造测试数据
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
}
```

