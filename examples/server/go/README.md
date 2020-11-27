## GO SDK

SDK包含了如下几个功能：
- 登录数据签名验证
- 支付数据签名验证
- 上报在线人数
- 上报游戏登录数据
- 消息推送
- 兑换礼包码

### 使用方法

1. 引入SDK：
```go
import (
	"./server"
)

```

2. 调用相应方法

- 登录数据签名验证

 方法说明
```go
/**
 * 登录验证
 *
 * @param string 公钥
 * @param string sdk客户端登录成功返回的entity，JSON字符串
 * @param string sdk客户端登录成功返回的sign
 * @param int 登录有效期，单位秒，如果登录信息超过此有效期，则登录失败
 *
 * @return (map[string]interface{}, error) 验证成功返回entity信息, 验证错误
 */
server.LoginVerify(publicKey, loginEntity, loginSign, 300)
```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//公钥
	publicKey = `-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo
Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew
v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O
KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg
9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE
s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m
0QIDAQAB
-----END PUBLIC KEY-----`
)

func main()  {

	//登录验证
	loginEntity := `{"openid":"1-123123","account":"test","time":1482313093}`
    loginSign := "m7JTn/y3IpB084vyeqoR9ysZ5/GeowcsO3KDrDsaa8Fof2Xjq4gKdk5eDLh0nTRxZslfbet5AWs+p1M0rtF8Jan8T2VxCW/czoCkrj4o/xnYtb3wdenCXAT7LUoydjTmd+cf0I9kw0DjkPDurrT9kNqxzw6dq1A6EFZAts4f0/H5+7kn81rzPq1RkWOM6OGm8R2D2WW/jHfqZDo1mvfZvIzkA/F0M62z2VsUK821BUkgoT23dByCdeqgx4hauJTHlnvg2/MplDYMDONHai6gTFWb4FQgY2wJq1BIWCyXgDuid6n9Ck0m6paJEfOffbK7BgwH3ssaF7xYGD2sjEuCFw=="
    userInfo, err := server.LoginVerify(publicKey, loginEntity, loginSign, 300)
	if (err != nil) {
		fmt.Printf("签名验证失败或登录已过期: %s", err.Error())
	} else {
		fmt.Printf("签名验证到成功, openid: %s", userInfo["openid"])
	}
}
```
 
- 支付数据签名验证
 
 方法说明
```go
/**
 * 支付验证
 *
 * @param string 公钥
 * @param map[string]string sdk支付系统 HTTP POST方式通知游戏服务端，游戏服务端接收到的POST内容
 *
 * @return bool 验证失败返回false，验证成功返回true
 */
server.PaymentVerify(publicKey, paymentPost)
```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//公钥
	publicKey = `-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo
Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew
v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O
KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg
9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE
s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m
0QIDAQAB
-----END PUBLIC KEY-----`
)

func main()  {

	//支付验证
    //接收到的http post内容
    paymentPost := map[string]string{
        "account":"abcd",
        "amount":"6.00",
        "black_desc":"",
        "channel":"1",
        "currency":"",
        "extra":"123",
        "game_id":"GMG001",
        "is_black":"0",
        "is_cancel":"0",
        "is_recovery":"0",
        "is_test":"0",
        "memo":"",
        "openid":"1-1234",
        "order_id":"1399633295037630",
        "order_type":"0",
        "original_purchase_orderid":"",
        "product_id":"HWDPID0006",
        "time":"1404975144",
        "transaction_id":"1000000110081354",
        "version":"8.0",
        "zone_id":"1",
        "sign":"MT/Wp3jz8l8HV62/OrpXdDIdEF9BGw8zCtwu8VZNaxCi52QXCC7RO2Q5yLRsQy8SmZMk0h0hsxUOXSZ8zZysUL+r/ATVknUs76zveaHROAfqhwo4sBqNA3jvnkCtbV/x9vF46vmNB7tDJcG6UDrJM5a/9Bn3Xq0ctlfSJpqJskr4dqyIlvCbQyi2YtnW2f5aNWATyNUntWtzakXYxZ7mPVT7hhspREo/3v/YcygmUHJJsJ2NnqkyWH7kV3nTTtvTQirjbzgeqnFd+KZBBHuBxOXDZInNLcaTnOQLskRddt0sYJ9/L8aDx9AvZtMe8kgQJhlNq13JOLFbCoMAEHD4Gg==",
    }
    //示例游戏商品数据
    gameOrder := map[string]string{
        "product_id":"HWDPID0006",
        "amount":"6.00",
    }
    //验证签名一致
    if (server.PaymentVerify(publicKey, paymentPost)) {
        //游戏服务端根据order_id判断订单是否已经处理过，游戏服务端自行实现，并响应`{"code":0,"msg":"成功"}`

        //测试订单，如果游戏不允许测试订单通知，则返回`{"code":2,"msg":"不允许测试订单通知"}`
        if (paymentPost["is_test"] == "1") {
            fmt.Println(`{"code":2,"msg":"不允许测试订单通知"}`)
            return
        }

        //风控拦截订单，游戏不能发货，游戏接收到此类订单通知时，可以通过邮件或其他方式告诉用户充值不到账原因和如何解决问题;
        if (paymentPost["is_black"] == "1") {
            fmt.Println(`{"code":0,"msg":"风控拦截订单通知"}`)
            return
        }

        //恢复购买订单，仅苹果、谷歌支付非消耗型商品才能恢复购买操作，游戏接收到此类订单通知时，请特殊标识，以与正常支付订单区分
        if (paymentPost["is_recovery"] == "1") {
            fmt.Println(`{"code":0,"msg":"恢复购买订单通知"}`)
            return
        }

        //取消购买订单，仅自动续订订阅型商品才有取消购买操作，游戏接收到此类订单通知时，请撤消之前的订单购买状态，并标识原订阅商品不可用
        if (paymentPost["is_cancel"] == "1") {
            fmt.Println(`{"code":0,"msg":"取消购买订单通知"}`)
            return
        }

        //验证product_id和金额是否匹配
        if (gameOrder["product_id"] != paymentPost["product_id"]) {
            fmt.Println(`{"code":2,"msg":"商品不存在"}`)
            return
        }
        //验证金额是否正确
        if (gameOrder["amount"] != paymentPost["amount"]) {
            fmt.Println(`{"code":2,"msg":"金额错误"}`)
            return
        }

        //游戏发货

        //发货成功，返回：`{"code":0,"msg":"成功"}`;

        //游戏发货失败，需要再次通知，返回：`{"code":1,"msg":"数据库错误"}`;

        //成功
        fmt.Println(`{"code":0,"msg":"成功"}`)
    } else {
        //签名验证失败返回
        fmt.Println(`{"code":2, "msg":"签名验证失败"}`)
    }
}
```

- 上报在线人数
	
 方法说明
```go
/**
 * 上报实时游戏在线人数
 *
 * @param string 秘钥
 * @param map[string]interface{} 游戏数据，需要包含以下字段
 * {
 * "game_id": 游戏ID,   //必填
 * "channel_id": 渠道ID,  //可选
 * "zone_id": 区ID,    //必填
 * "number": 人数,  //必填
 * }
 *
 * @return bool
 *
 */
server.GameOnline(loginKey, onlineData)
```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//示例login_key
	loginKey = "11111111"
)

func main()  {
    //在线人数实时统计
	onlineData := map[string]interface{}{
		"game_id" : 1000,
		"zone_id" : 1,
		"number": 99,
	}
	if server.GameOnline(loginKey, onlineData) {
		fmt.Println("上报在线人数成功")
	} else {
		fmt.Println("上报在线人数失败")
	}
}
```

- 上报游戏登录数据
	
 方法说明
```go
/**
 * 游戏登录数据上报
 *
 * @param string 秘钥
 * @param map[string]interface{} 游戏数据，需要包含以下字段
 * {
 * "game_id": 游戏ID,   //必填
 * "channel_id": 渠道ID,  //必填
 * "ip": 客户端用户IP地址,  //必填
 * "openid": 用户ID,  //必填
 * "device_udid": 设备标识码,  //必填
 * "device_type": 设备型号,    //必填
 * "os": 设备系统类型，例如ios、android ,  //必填
 * "ad_id": 广告ID,  //选填
 * "zone_id": 区服ID,  //选填
 * "zone_name": 区服名称,  //选填
 * "char_id": 角色ID,  //选填
 * "char_name": 角色名称,  //选填
 * "level": 等级or段位,  //选填
 * "sync": 同步数据到beacon 1010,  //选填
 * "log_type": 日志类型,默认2 (1:账号登录,2:游戏区登录,3:账号+游戏区登录),  //选填
 * }
 *
 * @return bool
 *
 */
server.LoginLogs(loginKey, loginData)
```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//示例login_key
	loginKey = "11111111"
)

func main()  {
    //游戏登录数据上报
	loginData := map[string]interface{}{
		"game_id" : 1000,
		"channel_id" : 1,
		"ip" : "192.168.100.1",
		"openid" : "1-123456",
		"device_udid" : "860529036567763",
		"device_type": "vivo Y51",
		"os": "android",
	}
	if server.LoginLogs(loginKey, loginData) {
		fmt.Println("上报游戏登录数据成功")
	} else {
		fmt.Println("上报游戏登录数据失败")
	}
}
```
 
- 消息推送
	
 方法说明
```go
/**
 * 推送消息
 *
 * @param string 秘钥
 * @param map[string]interface{} 推送内容，需要包含以下字段
 * {
 * "game_id" : 游戏ID,   //必填
 * "channel_id" : 渠道ID,  //必填
 * "environment" : 推送环境(仅IOS，默认生产环境)，生产环境:product 开发环境:dev,  //选填
 * "message_type" : 消息类型，通知消息:notify 透传消息:message,  //必填
 * "title" : 消息标题,  //必填
 * "content" : 消息内容,    //必填
 * "audience_type" : 推送目标，全量推送:all 单账号推送:account 账号列表推送:account_list ,  //必填
 * "audience_list" : 账号列表，当audience_type等于account时必须填写单个账号openid；当audience_type等于account_list时必须填写多个openid，以逗号分隔,  //选填
 * "custom_content" : 自定义的键值对，json格式如：{"key1":"value1","key2":"value2"},  //选填
 * "send_time" : 指定推送时间，格式为yyyy-MM-DD HH:MM:SS,  //选填
 * "loop_times" : 循环任务重复次数，建议取值[1, 15],  //选填
 * "loop_interval" : 循环执行消息下发的间隔，必须配合loop_times使用，以天为单位，取值[1, 14],  //选填
 * }
 *
 * @return bool
 *
 */
server.Push(loginKey, pushData)

```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//示例login_key
	loginKey = "11111111"
)

func main()  {
    //推送消息
	pushData := map[string]interface{}{
		"game_id": 1000,
		"channel_id": 1,
		"environment": "product",
		"audience_type": "account",
		"audience_list": "1-123456",
		"message_type": "notify",
		"title": "test",
		"content": "test",
	}
	if server.Push(loginKey, pushData) {
		fmt.Println("推送消息成功")
	} else {
		fmt.Println("推送消息失败")
	}
}
```

 
- 兑换礼包码
	
 方法说明
```go
/**
 * 使用礼包码
 *
 * @param string 秘钥
 * @param map[string]interface{} 兑换礼包码，需要包含以下字段
 * {
 * "game_id" : 游戏ID,   //必填
 * "channel_id" : 渠道ID,  //必填
 * "plat" : 平台名称,  //选填
 * "area" : 大区号，没有填0  //选填
 * "partition" : 小区号,  //必填
 * "uid" : 用户ID,    //必填
 * "char_id" : 角色ID ,  //选填
 * "gakey" : 礼包码,  //必填
 * }
 *
 * @return bool
 *
 */
server.GiftUse(loginKey, giftUseData)

```

 示例
```go
package main

import (
	"./server"
	"fmt"
)

var (
	//示例login_key
	loginKey = "11111111"
)

func main()  {
    //兑换礼包码
	giftUseData := map[string]interface{}{
		"game_id": 1000,
		"channel_id": 1,
		"plat": "android",
		"area": 0,
		"partition": 1,
		"uid": "1-123456",
		"char_id": "78910",
		"gakey": "8B8CM5VP",
	}
	if server.GiftUse(loginKey, giftUseData) {
		fmt.Println("兑换成功")
	} else {
		fmt.Println("兑换失败")
	}
}
```