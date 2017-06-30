关卡接口说明
=========================

关卡接口日志:
```
   上报关卡数据变化
```
POST `http://beacon.ztgame.com/game/stage`
 
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
| groupid | 用于关联一次事件产生多条不同类型的日志（每个app每个服务器每个区自增，次日清零） | 298178237 |
| taskid | 关卡ID/任务ID | 253521 |
| taskstate | 任务操作状态（开始 1/完成 2/取消 3） | 2 |
| subtaskid | 子关卡ID/子任务ID | 312 |
| teamstate | 是否组队，没有 0/组队 1 | 1 |
| teamnumber | 队伍人数 | 3 |
| tasktime | 任务完成在线时长(秒）（仅taskstate完成与取消时） | 123 |


### 对接参数范例

```
channel=1&appid=101&os=1&svrid=23141&zoneid=1312&openid=1-1111&charid=1211423&groupid=298178237&taskid=253521&taskstate=2&subtaskid=312&teamstate=1&teamnumber=3&tasktime=123
```
