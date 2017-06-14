应用状态日志调用接口说明
=========================

应用状态日志:

POST `http://beacon.mztgame.com/game/appStatus`
 
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
| status | 状态（1001：应用启动；1002：首次启动；1003:应用关闭;1004:切换后台运行;1005:切换前台运行;1010：账号游戏登录；） |
| openid | 用户OPENID号，全局唯一账号ID，与充值消费等数据同步 | 2-123-2412423512 |
| account | 用户账号信息，也区分游客、手机号注册等 | _80_m__m15588651899@6428 |
| badid | 封包手法的广告ID | 123456 |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 | 1312 |
| svrid | 服务器编号 | 23141 |
| longitude | 经度（是否有多颗卫星， GPS 和 GLONASS ？） | 111.727168 |
| latitudes | 纬度 | 29.056504 |
| bssid | WIFI的bssid mac地址（以下4个为WIFI相关，可根据实际情况索取） | 00:87:36:05:5d:ea |
| mcc | WIFI国家代码 | 460 |
| mnc | WIFI运营商代码 | 1 |
| lac | WIFI小区代码lac(nid) | 4301 |
| cellid | 基站ID cellid(bid)（是否三个基站？） | 20986 |
| bsss | 基站信号强度 |  |
| charid | 角色ID |  |
| charname | 角色名 |  |
| oltime | 在线时长增量（秒）（安卓后台运行30秒内，算在线时长增量，超过则相当于退出，不计入在线时长） | 532 |

### 对接参数范例

```
channel=1&appid=101&clientversion=1.2&appunid=&os=1&osversion=9.3&hardware=iphone6s&isp=1&net=1&screenwidth=1334&screenhight=750&ppi=488&cpu=A9|1.8|2&memory=2048&glrender=&glversion=2.0&udid=&idfa=458be47d-7205-4010-bc77-dc6e551ec514&adaid=&mac=7a:bb:14:99:52:2e&imei=493002407599521&androidid=a2948e662f4b4056&advertisingid=73af65f4-a06c-44a5-8cc6-f72465ac52ac&status=1002&openid=2-123-2412423512&account=_80_m__m15588651899@6428&badid=123456&zoneid=1312&svrid=23141&longitude=111.727168&latitudes=29.056504&bssid=00:87:36:05:5d:ea&mcc=460&mnc=1&lac=4301&cellid=20986&bsss=&charid=&charname=&oltime=532
```

### appunid生成规则

一、ios加密算法步骤
 ```
1. 组合信息
1+idfa+日期时间（unixtime+6位微秒级，转化为32进制）

例：
一台ios设备启动时间为 2017-01-20 10:10:10.123456

idfa--- 458be47d-7205-4010-bc77-dc6e551ec514（如果为空或非法，则固定为：458be47d-7205-4010-bc77-dc6e551ec514）
日期时间 格式  yyyyMMddHHmmssSSSSS 转化为(32进制)

组合后 1458be47d-7205-4010-bc77-dc6e551ec5141A6GFDDPPM0
去掉-，即为：1458be47d72054010bc77dc6e551ec5141A6GFDDPPM0

2. 反转字符串 0MPPDDFG6A1415ce155e6cd77cb01045027d74eb8541
 
3. 将第5位-第15位的字符串移到字符串头部 DDFG6A1415c0MPPe155e6cd77cb01045027d74eb8541
 ```
 
二、android加密算法步骤

```
1、 组合信息（优先mac，无或空或非法则imei，均无或空或非法，则用默认的固定mac，即为：7abb1499522e）：
2+mac+日期时间
3+imei+日期时间
 
mac--7a:bb:14:99:52:2e（去掉“:”，变为7abb1499522e）
imei--443567421776722
 
日期时间格式，同IOS
 
mac即为：27abb1499522e1A6GFDDPPM0
 
Imei即为：34435674217767221A6GFDDPPM0

2、 反转字符串 规则同IOS

3、 将第5位-第15位的字符串移到字符串头部 规则同IOS

```
