等级接口说明
=========================

等级接口日志:
```
     上报等级变化情况的日志
```
POST `http://beacon.ztgame.com/game/level`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道 | 1 |
| appid | 游戏APPID | 101 |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3） | 1 |
| svrid | 服务器编号 | 23141 |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 | 1312 |
| openid | 用户OPENID号 | 2-123-2412423512 |
| charid | 玩家角色ID | 1211423 |
| groupid | 用于关联一次事件产生多条不同类型的日志 | 298178237 |
| expchange | 经验变化 | 1253 |
| beforelevel | 事件前等级 | 15 |
| afterlevel | 事件后等级 | 16 |
| event | 一级事件 | 家族篝火 |
| subevent | 二级事件 |  |
| upgradetime | 升级在线时长(秒）（仅升级时） | 902 |


### 对接参数范例

```
channel=1&appid=101&os=1&svrid=23141&zoneid=1312&openid=1-111&charid=1211423&groupid=298178237&expchange=1253&beforelevel=15&afterlevel=16&event=家族篝火&subevent=&upgradetime=902
```
