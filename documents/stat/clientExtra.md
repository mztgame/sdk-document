客户端自定义接口说明
=========================

客户端自定义接口日志:

POST `http://beacon.mztgame.com/game/clientExtra`
 
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
| udid | ios的单应用下唯一设备ID，加密算法生成，卸载不变；安卓，加密算法生成，卸载改变。 |  |
| idfa | ios的idfa | 458be47d-7205-4010-bc77-dc6e551ec514 |
| adaid | ios的单一苹果开发者账号的专属ID |  |
| mac | 设备id（安卓=mac） | 7a:bb:14:99:52:2e |
| imei | 设备id（安卓=imei） | 493002407599521 |
| androidid | 设备id（安卓=androidid） | a2948e662f4b4056 |
| advertisingid | 设备id（安卓=advertisingid） | 73af65f4-a06c-44a5-8cc6-f72465ac52ac |
| openid | 用户OPENID号，全局唯一账号ID，与充值消费等数据同步 | 2-123-2412423512 |
| charid | 角色ID |  |
| eventid | 事件ID |  |
| eventname | 事件名 |  |
| remark | 备注 |  |
| kv1 | key:value结构参数1 | money:1230 |
| kv2 | key:value结构参数2 | level:29 |
| kv3 | key:value结构参数3 |  |
| kv4 | key:value结构参数4 |  |
| kv5 | key:value结构参数5 |  |
| kv6 | key:value结构参数6 |  |
| kv7 | key:value结构参数7 |  |
| kv8 | key:value结构参数8 |  |
| kv9 | key:value结构参数9 |  |
| kv10 | key:value结构参数10 |  |

### 对接参数范例

```
channel=1&appid=101&clientversion=1.2&appunid=&os=1&osversion=9.3&hardware=iphone6s&isp=1&net=1&udid=&idfa=458be47d-7205-4010-bc77-dc6e551ec514&adaid=&mac=7a:bb:14:99:52:2e&imei=493002407599521&androidid=a2948e662f4b4056&advertisingid=73af65f4-a06c-44a5-8cc6-f72465ac52ac&openid=2-123-2412423512&charid=&eventid=&eventname=&remark=&kv1=money:1230&kv2=level:29&kv3=&kv4=&kv5=&kv6=&kv7=&kv8=&kv9=&kv10=&
```
