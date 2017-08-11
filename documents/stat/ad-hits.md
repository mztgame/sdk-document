媒体合作广告点击调用接口说明
=========================
 本广告点击统计对接分为两种方式:

* Server to server
* 客户端302跳转

## Server to server 接口说明

### 点击接口地址

`http://beacon.ztgame.com/stat/s2sHits`
 
### 接口参数
 
| 参数名 | 说明 | 必填 |
|------|------|------|
| aid | 广告位ID(巨人提供) | 是 |
| m_id | 媒体ID(巨人提供) | 是 |
| s_mid | 媒体子渠道ID(按业务需求选填) | 否 | 
| game_id | 巨人游戏应用 id(巨人提供) | 是|
| idfa | IOS IDFA | 否 |
| imei | 设备IMEI(Android)  | 否 |
| mac | IOS 或Android Mac | 否 |
| ua | 用户若是通过网页点击的， 为浏览器的 User-Agent 信息 | 是 |
| ip | 用户IP(取媒体方客户端真实IP) | 是 |
| os | 用户操作系统，取值 1 ios 2 安卓 3 windows/wp | 是 |
| tid | tid=2，用于展示监控。tid=5，用于点击广告素材进入外媒页面。 | 是 |
| dnm |  素材名 tid=5时，必填，其他不填 | 否 |
| pr |  价格 | 否 |
 
### 对接地址范例

```
http://beacon.ztgame.com/stat/s2sHits?aid=2000001&m_id=1&game_id=5012&idfa=ABCD-EFG-HIJKLM&ip=1.1.1.1&ua==(ua)&s_mid=&tid=8&dnm=y_x_x_x&pr=500&os=1
```

### 响应说明

HTTP 响应状态码为 204，无响应内容

## 客户端302跳转接口说明

### 点击接口地址

`http://beacon.ztgame.com/stat/clientHits`

### 接口参数
 
| 参数名 | 说明 | 必填 |
|------|------|------|
| aid | 广告位ID(巨人提供) | 是 |
| m_id | 媒体ID(巨人提供) | 是 |
| s_mid | 媒体子渠道ID(按业务需求选填) | 否 |
| game_id | 巨人游戏应用 id(巨人提供) | 是|
| idfa | IOS IDFA | 否 |
| imei | 设备IMEI(Android)  | 否 |
| mac | IOS 或Android Mac | 否 |
| default_url | 默认跳转URL|  是 |
| ios_url | 程序识别 IOS UA 跳转URL|  否 |
| android_url | 程序识别 Android UA跳转URL |  否 |
| ua | 为浏览器的 User-Agent 信息 | 否 |
| os | 用户操作系统，取值 1 ios 2 安卓 3 windows/wp | 否 |
| callback |  广告商追踪使用url，启动(激活）时会回调 |  否 |
| tid | tid=2，用于展示监控。tid=5，用于点击广告素材进入外媒页面。tid=8，代表点击跳转下载包或公司统一下载页 | 是 |
| dnm |  素材名 tid=5时，必填，其他不填 | 否 |
| pr |  价格(单位 分) | 否 |

> 注：以上参数 `default_url`, `ios_url`, `android_url` 
限制域名：`*.[m]ztgame.com`, `itunes.apple.com`,`*.[m]ztgame.com.cn`,`[m]ztgame.com.cn`
 
### 对接地址范例

* 客户端跳转方式

```
http://beacon.ztgame.com/stat/clientHits?aid=2000001&m_id=1&game_id=5012idfa=ABCD-EFG-HIJKLM&default_url=https://itunes.apple.com&ios_url=&android_url=&callback=&s_mid=&tid=8&dnm=y_x_x_x&pr=500
```
 
### 响应说明

HTTP 响应状态码为 302，跳转地址是 `default_url`, `ios_url`, `android_url` 参数传入值。

## 附录

* SDK中IOS获取User-Agent示例

```
+(NSString *)getUserAgent {
    NSMutableString *userAgent = [NSMutableString stringWithString:[[UIWebView new] stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"]];
    return userAgent;
}
```

* SDK中Android获取User-Agent示例

```
WebView webView = new WebView(ctx);
	WebSettings settings = webView.getSettings();
String ua = settings.getUserAgentString()；
```
