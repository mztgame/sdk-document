手游登录行为上报事件接口
=========================

#### 描述

    1、业务不涉及到的登录环节，则可以不上报。
    2、如果service/loginInLobby和service/loginEnterGame重复，则只上报一个事件。
    3、service/loginCheckAppUpdate和Service/downloadEvent在下载服务化中描述了上报需求，本文不再说明。


#### 参考流程图

<img src="http://cdn.mztgame.ztgame.com.cn/data/user-action-collect.png">

## 接入备注

    所有指定请求字段可没有值，但是要保留字段名。自定义参数如果不用，可不填。
    所有字段必须字段值都必须urlencode后传递.
    
## 公共参数

    除去指定参数以外，每个接口还提供若干自定义参数供项目差别化使用，格式 extra开头+数字,目前预留了8个。

| 参数名 | 说明 | 备注 |
|------|------|------|
| imei | 安卓IMEI| 安卓必填 |
| mac | 安卓mac| 安卓必填 |
| androidid | 安卓id | 安卓必填 |
| idfa | IOS设备号 | ios必填 |
| extra1 | 自定义参数| 游戏自定义(字符串型） |
| extra2 | 自定义参数| 游戏自定义(字符串型） |
| extra3 | 自定义参数| 游戏自定义(字符串型） |
| extra4 | 自定义参数 | 游戏自定义(字符串型） |
| extra5 | 自定义参数  | 游戏自定义(字符串型） |
| extra6 |  自定义参数 | 游戏自定义(字符串型） |
| extra7 | 自定义参数 | 游戏自定义(字符串型） |
| extra8 | 自定义参数 | 游戏自定义(字符串型） |
| sign | 签名 | 签名规则，见后文 |
| ... | ... | .. |

##签名规则

    所有显式上传的字段值 按照字典排序后+约定的key后MD5.key每个appid不同
    
    举例：
    
```    
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&ver_addr=www.update.com&version=1.0.1&build=100&resultCode=1&updateType=1&versionType=1&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&extra1=test1|test2
```    
    md5("11111-111221.0.15010012323-22250122222222223920012232323test1|test2www.update.com连接版本更新服务器失败&abcde"")
    
    结果：sign = 1c13d8a96fc2a4e4d5eb567bc4bb7d67

## 1.启动游戏事件数据接口

POST  `http://beacon.ztgame.com/service/loginGameStart`

#### 接口参数

| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 启动客户端耗时,单位：ms  | 初始化时间：即从点击图标开始，到加载资源完成的时间） |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP  application/json 
    {"code":0}



## 2.sdk登陆事件数据接口

POST  `http://beacon.ztgame.com/service/loginSdkClient`

#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | SDK登陆耗时,单位：ms  | 从客户端发起SDK登录请求，到收到SDK的返回数据 |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP  application/json 
    {"code":0}


## 3.拉取区服列表事件数据接口

POST  `http://beacon.ztgame.com/service/loginSelectServer`

#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid| 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 拉取列表耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP  application/json 
    {"code":0}


## 4.加载角色事件(新建或者获取已有角色)事件数据接口

POST  `http://beacon.ztgame.com/service/loginLoadRole`

#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 新建或者加载角色耗时时间,单位：ms  |  |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
| type | 新建角色：1，加载已有角色：2 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}&type=1&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP  application/json 
    {"code":0}


## 5.登录到大厅事件数据接口

POST  `http://beacon.ztgame.com/service/loginInLobby`

#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 登陆大厅耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP  application/json 
    {"code":0}


## 6.加载角色事件(新建或者获取已有角色)事件数据接口

POST  `http://beacon.ztgame.com/service/loginEnterGame`

#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 加载角色耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2

```

#### 响应说明

    HTTP  application/json 
    {"code":0}
