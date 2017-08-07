Url: `http://beacon.ztgame.com/data/collect`

请求方式：POST

Header：Content-Type:application/x-www-form-urlencoded

### 请求参数

| 参数名   | 说明   | 类型   | 必填 |
|----------|--------|--------|------|
| event_type   | 接入方需要传入约定的事件类型，已有类型见附件 | string | 是 |
| base_data   | sdk自带基础数据封装，接入方不必额外实现 | json | 否  |
| extra_data   | 事件相关数据,接入方需要实现部分 | json | 是 |


<style type="text/css">
table.zyhovertable {
    font-family: 
    verdana,arial,sans-serif;
    font-size:12px;
    color:#333333;
    border-width: 1px;
    border-color: #999999;
    border-collapse: collapse;
	width:70%;
}

table.zyhovertable th {
    background-color:#C3DDE0;
    border-width: 1px;
    padding: 8px;
    border-style: solid;
    border-color: #999999;
}

table.zyhovertable tr {
    background-color:#E7E7E7;
}

table.zyhovertable td {
    border-width: 1px;
    padding: 8px;
    border-style: solid;
    border-color: #999999;
}
</style>

<table class="zyhovertable">
<tr> 
<th>事件编号</th><th>事件名称</th><th>埋点时机</th><th>备注</th>
</tr>

<tr><td>1</td><td>1001</td><td> 应用启动</td><td>gasdk初始化后即可调用</td> 需要确保已经联网,广告监控使用</tr>
<tr><td>2</td><td>1010</td><td>角色登陆</td><td>游戏内角色登陆后调用</td>广告监控使用</tr>
</table>

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



