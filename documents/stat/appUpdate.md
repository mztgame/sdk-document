应用更新日志调用接口说明
=========================

应用更新日志:

POST `http://beacon.mztgame.com/game/appUpdate`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道 | 1 |
| appid | 游戏APPID | 101 |
| clientversion | 客户端版本 | 1.2 |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3） | 1 |
| osversion | 移动终端操作系统版本 | 9.3 |
| hardware | 移动终端机型 | iphone6s |
| isp | 运营商 | 1 |
| net | WIFI 1/2G 2/3G 3/4G 4 | 1 |
| appunid | 用户唯一APPID（首次启动按加密算法生成） |  |
| udid | ios的单应用下唯一设备ID，加密算法生成，卸载不变；安卓，加密算法生成，卸载改变。 |  |
| idfa | ios的idfa | 458be47d-7205-4010-bc77-dc6e551ec514 |
| adaid | ios的单一苹果开发者账号的专属ID |  |
| mac | 设备id（安卓=mac） | 7a:bb:14:99:52:2e |
| imei | 设备id（安卓=imei） | 493002407599521 |
| androidid | 设备id（安卓=androidid） | a2948e662f4b4056 |
| advertisingid | 设备id（安卓=advertisingid） | 73af65f4-a06c-44a5-8cc6-f72465ac52ac |
| svrid | 服务器编号 |  |
| updatetype | 更新类型（下载开始 1/ 下载完成 2/ 下载失败 3/ 加载开始 11/ 加载完成 12/ 加载失败 13） | 3 |
| updatedes | 更新描述 | 网络连接失败 |
| updateobj | 更新目标名 | x版本1包 |
| updatevol | 更新容量，单位k | 2162.12 |


### 对接参数范例

```
channel=1&appid=101&clientversion=1.2&os=1&osversion=9.3&hardware=iphone6s&isp=1&net=1&appunid=&udid=&idfa=458be47d-7205-4010-bc77-dc6e551ec514&adaid=&mac=7a:bb:14:99:52:2e&imei=493002407599521&androidid=a2948e662f4b4056&advertisingid=73af65f4-a06c-44a5-8cc6-f72465ac52ac&svrid=&updatetype=3&updatedes=网络连接失败&updateobj=x版本1包&updatevol=2162.12
```
