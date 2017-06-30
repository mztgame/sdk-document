道具接口说明
=========================

道具接口日志:
```
     上报道具变化情况的日志
```
POST `http://beacon.ztgame.com/game/item`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道 |  |
| appid | 游戏APPID |  |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3） |  |
| svrid | 服务器编号 |  |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 |  |
| openid | 用户OPENID号 |  |
| charid | 玩家角色ID |  |
| groupid | 用于关联一次事件产生多条不同类型的日志 |  |
| objid | 道具ID（包括货币） |  |
| afternum | 事件后的物品存量 |  |
| num | 事件涉及的物品数量 |  |
| event | 一级事件 |  |
| subevent | 二级事件 |  |
| changetype | 增加 1 / 减少 2 |  |


### 对接参数范例

```
channel=1&appid=1001&os=1&svrid=1&zoneid=1&openid=1-111&charid=1&groupid=1&objid=1&afternum=1&num=22&event=11&subevent=22&changetype=1
```
