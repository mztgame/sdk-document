登陆登出接口说明
=========================

登陆登出接口日志:

POST `http://beacon.mztgame.com/game/login`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道（数字代表，来源渠道配置表） | 1 |
| appid | 游戏APPID（不重复） | 101 |
| clientversion | 客户端版本 | 1.2 |
| appunid | 用户唯一APPID（首次启动按加密算法生成） |  |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3） | 1 |
| osversion | 移动终端操作系统版本 | 9.3 |
| hardware | 移动终端机型 | iphone6s |
| isp | 运营商（移动 1/联通 2/电信 3） | 1 |
| net | WIFI 1/2G 2/3G 3/4G 4 | 1 |
| screenwidth | 显示屏宽度（分辨率） | 1334 |
| screenhight | 显示屏高度（分辨率） | 750 |
| ppi | 像素密度 | 488 |
| cpu | cpu类型|频率|核数 | A9|1.8|2 |
| memory | 内存信息单位m | 2048 |
| glrender | opengl render信息 |  |
| glversion | opengl版本信息 | 2.0 |
| udid | ios的单应用下唯一设备ID，加密算法生成，卸载不变；安卓，加密算法生成，卸载改变。 |  |
| idfa | ios的idfa | 458be47d-7205-4010-bc77-dc6e551ec514 |
| adaid | ios的单一苹果开发者账号的专属ID |  |
| mac | 设备id（安卓=mac） | 7a:bb:14:99:52:2e |
| imei | 设备id（安卓=imei） | 493002407599521 |
| androidid | 设备id（安卓=androidid） | a2948e662f4b4056 |
| advertisingid | 设备id（安卓=advertisingid） | 73af65f4-a06c-44a5-8cc6-f72465ac52ac |
| status | 状态（组合码。千位：默认 1；百位：默认 0 /角色登录 1 / 角色登录报错 2 / 角色登出 3；十位：默认 0 / 账号游戏登录 1 /游戏登录报错 2 / 账号登出 3；个位：默认 0） |  |
| remark | 备注，账号登录报错、角色登录报错等，错误类型与信息描述 |  |
| openid | 用户OPENID号，全局唯一账号ID，与充值消费等数据同步 | 2-123-2412423512 |
| account | 用户账号信息，也区分游客、手机号注册等 | _80_m__m15588651899@6428 |
| badid | 封包手法的广告ID | 123456 |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 | 1312 |
| svrid | 服务器编号 | 23141 |
| charid | 角色ID |  |
| charname | 角色名 |  |
| onlinetime | 在线时长增量（秒）（安卓后台运行30秒内，算在线时长增量，超过则相当于退出，不计入在线时长） |  |



### 对接参数范例

```
channel=1&appid=101&clientversion=1.2&appunid=&os=1&osversion=9.3&hardware=iphone6s&isp=1&net=1&screenwidth=1334&screenhight=750&ppi=488&cpu=A9|1.8|2&memory=2048&glrender=&glversion=2.0&udid=&idfa=458be47d-7205-4010-bc77-dc6e551ec514&adaid=&mac=7a:bb:14:99:52:2e&imei=493002407599521&androidid=a2948e662f4b4056&advertisingid=73af65f4-a06c-44a5-8cc6-f72465ac52ac&status=&remark=&openid=1-1111&account=_80_m__m15588651899@6428&badid=123456&zoneid=1312&svrid=23141&charid=&charname=&onlinetime=50
```
