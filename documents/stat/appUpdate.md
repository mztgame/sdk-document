应用更新日志调用接口说明
=========================

应用更新日志:
     
     `用于 获取应用更新及下载日志（/ 下载开始 / 下载完成 / 下载失败 / 加载开始 / 加载完成 / 加载失败）
     
POST `http://beacon.ztgame.com/game/appUpdate`
 
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
### appunid生成规则

一、ios加密算法步骤
 ```
1. 组合信息

  1+idfa+日期时间（unixtime+6位微秒级，转化为32进制）

  例：一台ios设备启动时间为 2017-01-20 10:10:10.123456

  idfa--- 458be47d-7205-4010-bc77-dc6e551ec514（如果为空或非法，则固定为：458be47d-7205-4010-bc77-dc6e551ec514）

  日期时间--- 1484907010123456--1A6GFDDPPM0(32进制)

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
 
    日期时间 格式  yyyyMMddHHmmssSSSSS 转化为(32进制)

2、 反转字符串 规则同IOS

3、 将第5位-第15位的字符串移到字符串头部 规则同IOS

```
