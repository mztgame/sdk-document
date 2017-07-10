下载服务化(手游)上报接口
=========================

#### 描述

    1.启动游戏后,会检查是否有更新(app或资源文件更新),这个逻辑增加上报service/loginCheckAppUpdate的事件。
    2.如果用户进入下载逻辑,在完成下载后(不管成功还是失败)上报service/downloadEvent事件。

#### 参考流程图

<img src="http://cdn.mztgame.ztgame.com.cn/data/update-collect.png">

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

## 签名规则

    所有显式上传的字段值 按照字典排序后+约定的key后MD5.key每个appid不同
    
    举例：
    
```    
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&ver_addr=www.update.com&version=1.0.1&build=100&resultCode=1&updateType=1&versionType=1&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&extra1=test1|test2
```    
    md5("11111-111221.0.15010012323-22250122222222223920012232323test1|test2www.update.com连接版本更新服务器失败&abcde"")
    
    结果：sign = 2da8c86a68ef5df87b3b36ae9056275e

## 1.检查版本更新事件数据接口

POST  `http://beacon.ztgame.com/service/checkAppUpdate`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| appid | 手游平台分配的appid | |
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform |  登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| ver_addr | 版本服务器域名或者ip |  |
| version | 要下载的版本号 |  |
| build | build版本,若无填空 |  |
| resultCode | 有更新：1；无更新：0 | |
| updateType | 在有更新情况下，用户主动选择更新：1；强制更新：2；用户忽略更新：0 | |
| versionType | 更新类型，区分app更新和资源更新方式 |取值0：appstore；1：下载apk；2：资源文件更新 |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&ver_addr=www.update.com&version=1.0.1&build=100&resultCode=1&updateType=1&versionType=1&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2
```

#### 响应说明

    HTTP application/json 
    {"code":0}



## 2.版本更新事件数据接口

POST  `http://beacon.ztgame.com/service/downloadEvent`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| openid | sdk登陆后entity中的openid | 玩家唯一的标识，如果是第1次登录，因取不到值则填0；以后登录则需要填写实际的值。 |
| appid | 手游平台分配的appid | |
| platform |  登录平台（取值：1 ios, 2 android, 3 wp, 9 other） |  |
| begintime | 操作开始时间 |精确到秒yyyy-mm-dd hh:mm:ss (PRC) |
| version | 下载的版本号 |  |
| build | 下载的build号，若无填空  |  |
| oldversion | 当前版本号 |  |
| oldbuild | 当前build号 |  |
| resultCode | 下载结果 |0成功，1失败 |
| errorCode | 成功:0,失败错误码自定义| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 | 例："init failed" |
| totaltime | 下载总耗时(单位：ms) | 这个耗时是指用户从开始下载到下载结束的总耗时,不管是否成功。|
| filesize | 已下载的总大小(单位：字节） | 这个字节数是指用户从开始下载到下载结束的总字节数,不管是否成功。 |
| url | 下载的url | 多包下载可上报最后一个文件的url |
| final_url | 下载的最终url | 经过域名解析得到明确ip或经过302跳转后最后的带ip的url |
| versionType | 更新类型，区分app更新和资源更新方式 | 取值0：appstore；1：下载apk；2：资源文件更新 |
| totalfilesize | 需要下载的总大小（单位：字节） | |
 
#### 对接地址参数范例

```
oepnid=1-11122&appid=5012&platform=1&begintime=2017-05-14 10:00:00&version=1.0.1&build=100&oldversion=1.0.1&oldbuild=100&resultCode=1&errorCode=1&errorMsg=下载过程未知错误&totaltime=50&filesize=100&url=http://www.update.com&final_url=http://111.222.33&versionType=1&totalfilesize=200&imei=22222&mac=22223&idfa=12323-222&androidid=2232323&EXTRA1=test1|test2&sign=abadwadwdaw
```

#### 响应说明

    HTTP application/json 
    {"code":0}
