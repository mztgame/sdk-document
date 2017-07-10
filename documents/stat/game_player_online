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
| mztgame_udid | mztgame_udid | 2-123-2412423512 |
| role_id | 角色ID | 1211423 |
| exp | 游戏数值变化（经验值、比赛次数等） | 123 |
| idfa | IDFA(idfa) | XXXXXXXXXX |

### 对接参数范例

```
channel=1&appid=101&os=1&svrid=23141&zoneid=1312&openid=1-1111&charid=1211423&groupid=298178237&taskid=253521&taskstate=2&subtaskid=312&teamstate=1&teamnumber=3&tasktime=123
```

### mztgame_udid获取方式

```
Id(mztgame_udid)的获取，ios客户端代码中加入下列代码可以获取
NSString *ztgameUdid = [[ZTLibBase getInstance]getZTGameUDID];

```
