游戏场次数据接口说明
=========================

POST `https://beacon.ztgame.com/game/player-online`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| game_id | 游戏id | 5012 |
| openid | open_id | 101 |
| time_begin | 统计周期开始时间（秒单位时间戳） | 1451375641 |
| time_end | 统计周期结束时间（秒单位时间戳） | 1451375641 |
| user_ip | 用户IP（user_ip） | 127.0.0.1 |
| type | 根据游戏选择（按场次 1，按经验值 2） | 1 |
| mztgame_udid | mztgame_udid(ios特有) | 2323232323 |
| role_id | 角色ID | 1211423 |
| exp | 游戏数值变化（经验值、比赛次数等） | 123 |
| idfa | IDFA(IOS特有) | XXXXXXXXXX |
| imei | imei(安卓特有) | XXXXXXXXXX |
| mac | mac(安卓特有) | XXXXXXXXXX |
| channel_id | 渠道id | 2 |
| sign | 签名 | 目前可不传 |


## 签名规则

    所有显式上传的字段值 按照字典排序后+约定的`key`后MD5.`key`每个appid不同
    
    举例：
    
```    
game_id=5012&openid=101&time_begin=1451375641&time_end=1451375641&user_ip=127.0.0.1&mztgame_udid=2323232323&role_id=1211423&exp=123&idfa=XXXX-XXXX-XXXXXXXX&type=1
```    
    md5("1235012XXXX-XXXX-XXXXXXXX23232323231011211423145137564114513756411127.0.0.1abcde")
    
    结果：sign = c05bd52f5700677aec3b02e829a3152d

### 对接参数范例

```
game_id=5012&openid=101&time_begin=1451375641&time_end=1451375641&user_ip=127.0.0.1&mztgame_udid=2323232323&role_id=1211423&exp=123&idfa=XXXX-XXXX-XXXXXXXX&sign=c05bd52f5700677aec3b02e829a3152d
```

## 备注
### MZTGAME_UDID获取方式

```
Id(mztgame_udid)的获取，ios客户端代码中加入下列代码可以获取
NSString *ztgameUdid = [[ZTLibBase getInstance]getZTGameUDID];

```
