游戏场次数据接口说明
=========================

POST `http://beacon.ztgame.com/game/player-online`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| game_id | 游戏id | 5012 |
| openid | open_id | 101 |
| time_begin | 统计周期开始时间（秒单位时间戳） | 1451375641 |
| time_end | 统计周期结束时间（秒单位时间戳） | 1451375641 |
| user_ip | 用户IP（user_ip） | 127.0.0.1 |
| mztgame_udid | mztgame_udid | 2323232323 |
| role_id | 角色ID | 1211423 |
| exp | 游戏数值变化（经验值、比赛次数等） | 123 |
| idfa | IDFA(idfa) | XXXXXXXXXX |

## 签名规则

    所有显式上传的字段值 按照字典排序后+约定的key后MD5.key每个appid不同
    
    举例：
    
```    
game_id=5012&openid=101&time_begin=1451375641&time_end=1451375641&user_ip=127.0.0.1&mztgame_udid=2323232323&role_id=1211423&exp=123&idfa=XXXX-XXXX-XXXXXXXX
```    
    md5("1011231211423127.0.0.15012145137564114513756412323232323XXXX-XXXX-XXXXXXXXabcde"")
    
    结果：sign = 5caf1d45729155a9abf9c75af956342e

### 对接参数范例

```
game_id=5012&openid=101&time_begin=1451375641&time_end=1451375641&user_ip=127.0.0.1&mztgame_udid=2323232323&role_id=1211423&exp=123&idfa=XXXX-XXXX-XXXXXXXX&sign=5caf1d45729155a9abf9c75af956342e
```

## 备注
### MZTGAME_UDID获取方式

```
Id(mztgame_udid)的获取，ios客户端代码中加入下列代码可以获取
NSString *ztgameUdid = [[ZTLibBase getInstance]getZTGameUDID];

```
