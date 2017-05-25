下载服务化(手游)上报接口
=========================

## 1.检查版本更新事件数据接口

POST  `http://beacon.mztgame.com/service/checkAppUpdate`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| ver_addr | 版本服务器域名或者ip |  |
| version | 要下载的版本号 |  |
| build | build版本,若无填空 |  |
| resultCode |  有更新：1；无更新：0 | 否 |
| updateType |  在有更新情况下，用户主动选择更新：1；强制更新：2；用户忽略更新：0 |  |
| versionType |  更新类型，区分app更新和资源更新方式 | 取值0：appstore；1：下载apk；2：资源文件更新 |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&ver_addr=www.update.com&version=1.0.1&build=100&resultCode=1&updateType=1&versionType=1
```

#### 响应说明

HTTP 
application/json 
{"code":0}



## 2.版本更新事件数据接口

POST  `http://beacon.mztgame.com/service/downloadEvent`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| oepnid | 玩家唯一的标识，若无填空 |  |
| appid | 游戏APPID | |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| begintime | 操作开始时间 |精确到秒yyyy-mm-dd hh:mm:ss (PRC) |
| version | 下载的版本号 |  |
| build | 下载的build号，若无填空  |  |
| oldversion | 当前版本号 |  |
| oldbuild | 当前build号 |  |
| resultCode | 下载结果 |0成功，1失败 |
| errorCode | 错误码 | 游戏自定义(字符串型）  |
| errorMsg | 错误原因 |  |
| totaltime |  下载总耗时(单位：ms) |这个耗时是指用户从开始下载到下载结束的总耗时,不管是否成功。|
| filesize |  已下载的总大小(单位：字节） | 这个字节数是指用户从开始下载到下载结束的总字节数,不管是否成功。 |
| url |  下载的url | 多包下载可上报最后一个文件的url |
| final_url |  下载的最终url | 经过域名解析得到明确ip或经过302跳转后最后的带ip的url |
| versionType |  更新类型，区分app更新和资源更新方式 | 取值0：appstore；1：下载apk；2：资源文件更新 |
| totalfilesize |  需要下载的总大小（单位：字节） | |
 
#### 对接地址参数范例

```
oepnid=1-11122&appid=5012&platform=1&begintime=2017-05-14 10:00:00&version=1.0.1&build=100&oldversion=1.0.1&oldbuild=100&resultCode=1&errorCode=1&errorMsg=下载过程未知错误&totaltime=50&filesize=100&url=http://www.update.com&final_url=http://111.222.33&versionType=1&totalfilesize=200
```

#### 响应说明

HTTP 
application/json 
{"code":0}
