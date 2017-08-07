Url: `http://beacon.ztgame.com/data/collect`

请求方式：POST

Header：Content-Type:application/x-www-form-urlencoded

### 请求参数

| 参数名   | 说明   | 类型   | 必填 |
|----------|--------|--------|------|
| event_type   | 事件类型，保留事件1001 应用启动,其他待定 | string | 是   |
| base_data   | 客户端参数控制是否传递,需urlencode | json | 否   |
| extra_data   | 事件相关数据，json格式,需urlencode | json | 是   |
| sign | 算法同appunid，但是时间是当前时间,每次都变 ||

### base_data参数内容(最终为json形式)

|参数|描述|样例|
|---|---|---|
|eventtime|事件时间, 格式 datetime|2016/5/1 12:23:36|
|package|包名.ios填bundleid|com.ztgame.zt|
|clientversion|客户端版本|1.2|
|os|移动终端操作系统（ios 1 /android 2 /wp 3）|1|
|osversion|移动终端操作系统版本|9.3|
|hardware|移动终端机型（是否有多种抓取方式？机型转化配置表是否事后转换？）|iphone6s|
|isp|运营商| 中国移动 |
|net|WIFI 1/2G 2/3G 3/4G 4|1|
|screenwidth|显示屏宽度（长边分辨率）|1334|
|screenhight|显示屏高度（短边分辨率）|750|
|ppi|像素密度|488|
|cpu|cpu类型|频率|核数|A9|1.8|2|
|memory|内存信息单位m|2048|
|glrender|opengl render信息||
|glversion|opengl版本信息|2.0|
|udid|ios的单应用下唯一设备ID，加密算法生成，卸载不变；安卓，加密算法生成，卸载改变。（mztgame_udid接口所得）||
|idfa|ios的idfa|458be47d-7205-4010-bc77-dc6e551ec514|
|adaid|ios的单一苹果开发者账号的专属ID||
|mac|设备id（安卓=mac）|7a:bb:14:99:52:2e|
|imei|设备id（安卓=imei）|493002407599521|
|androidid|设备id（安卓=androidid）|a2948e662f4b4056|
|advertisingid|设备id（安卓=advertisingid）|73af65f4-a06c-44a5-8cc6-f72465ac52ac|
|ua|浏览器UA|mozilla/5.0 (iphone; cpu iphone os 8_4 like mac os x) applewebkit/600.1.4 (khtml, like gecko) version/8.0 mobile/12h143 safari/600.1.4|
|adid|广告ID|123456|
|ip|ip|220.183.34.35|
|badid|取不到可不传值，字段保留|123456|
|bssid|WIFI的bssid mac地址（以下4个为WIFI相关，可根据实际情况索取）|00:87:36:05:5d:ea|
|mcc|WIFI国家代码|460|
|mnc|WIFI运营商代码|1|
|lac|WIFI小区代码lac(nid)|4301|
|cellid|基站ID cellid(bid)（是否三个基站？）|20986|
|bsss|基站信号强度||
|appunid|ios的单应用下唯一设备ID，加密算法生成，卸载不变；安卓，加密算法生成，卸载改变。(客户端生成)||
|key|如果有缓存文件，置为1，没缓存文件，置为0(目前只有1001事件会有这个字段，其他可以不传键值)| 0,1|

### extra_data必填参数内容(最终为json形式)

|参数|描述|样例|
|---|---|---|
|channel|渠道（数字代表，来源渠道配置表）|1|
|appid|游戏APPID（不重复）|101|
|openid|用户OPENID号，全局唯一账号ID，与充值消费等数据同步|2-123-2412423512|
|account|用户账号信息，也区分游客、手机号注册等|_80_m__m15588651899@6428|
|longitude|经度（是否有多颗卫星， GPS 和 GLONASS ？）|111.727168|
|latitudes|纬度|29.056504|
|zoneid|游戏区Id||
|serid|游戏服Id||

返回与示例：

{"code":0,"msg":"OK"}

### 响应参数
Header：Content-Type:application/json


| 参数名    | 说明         | 类型   |
|-----------|--------------|--------|
| code      | 错误码(0: 成功； 大于0：失败) | int |
| msg      | 错误信息 | string |



