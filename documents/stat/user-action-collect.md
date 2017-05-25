手游登录上报事件接口
=========================

## 1.启动游戏事件数据接口

POST  `http://beacon.mztgame.com/service/loginGameStart`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1
```

#### 响应说明

HTTP 
application/json 
{"code":0}



## 2.sdk登陆事件数据接口

POST  `http://beacon.mztgame.com/service/loginSdkClient`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0
```

#### 响应说明

HTTP 
application/json 
{"code":0}


## 3.拉取区服列表事件数据接口

POST  `http://beacon.mztgame.com/service/loginSelectServer`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0
```

#### 响应说明

HTTP 
application/json 
{"code":0}


## 4.加载角色事件(新建或者获取已有角色)事件数据接口

POST  `http://beacon.mztgame.com/service/loginLoadRole`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
| type | 新建角色：1，加载已有角色：2 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}&type=1
```

#### 响应说明

HTTP 
application/json 
{"code":0}


## 5.登录到大厅事件数据接口

POST  `http://beacon.mztgame.com/service/loginInLobby`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}
```

#### 响应说明

HTTP 
application/json 
{"code":0}


## 6.加载角色事件(新建或者获取已有角色)事件数据接口

POST  `http://beacon.mztgame.com/service/loginEnterGame`
 
#### 接口参数
 
| 参数名 | 说明 | 备注 |
|------|------|------|
| errorCode | 成功:0,失败错误码参考备注| 游戏自定义(字符串型） |
| errorMsg | 错误信息,可选 |  |
| appid | 游戏APPID | |
| openid | 玩家唯一的标识，若无填空 |  |
| totaltime | 检查更新耗时,单位：ms  |  |
| platform | 登录平台（取值：1 ios 2 android 3 wp 9 other） |  |
| zoneid | 分区分服，填小服ID；全区全服填0；若无填-1 |  |
| role_list | 角色列表, 上报格式规范：{"角色id":"角色名"}，例如:{"1001":"test1","1002":"test2"}，若无填0 |  |
 
#### 对接地址参数范例

```
errorCode=92001&errorMsg=连接版本更新服务器失败&appid=5012&openid=1-11122&totaltime=50&platform=1&zoneid=0&role_list={"1001":"test1","1002":"test2"}
```

#### 响应说明

HTTP 
application/json 
{"code":0}
