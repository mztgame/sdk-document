游戏在线人数统计接口
====================

## 接口说明>

应用协议: `HTTP`

请求方式: `GET` / `POST`

参数传递方式(Content-Type): `application/x-www-form-urlencoded`

接口地址: `http://stat.mztgame.com/game/online`

响应内容类型: `JSON`

接口请求频率: 每分钟一次

## 参数说明

| 名称 | 类型 | 必须 |  说明 |
| ---- | ---- | ---- |---- |
| game_id | int | 是 | 游戏ID |
| channel_id | int | 否 | 渠道ID |
| zone_id | int | 是 | 区ID |
| number | int | 是 | 在线人数 |
| sign | string | 是 | `md5(game_id+"&"+number+"&"+zone_id+"&"+key)`  , 其中 key为登录使用的 login_key |

## 响应说明

| 名称 | 类型 | 说明 |
| ---- | ---- | ---- |
| code | int | 执行结果,  0: 成功; 其它失败 |
| msg  | string | 错误消息 |

## 举例说明

~~~
http://stat.mztgame.com/game/online?game_id=5012&channel_id=1&zone_id=1&number=123&sign=abcdef
~~~
