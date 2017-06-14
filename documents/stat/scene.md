页面场景调用接口说明
=========================

页面场景日志:

POST `http://beacon.mztgame.com/game/scene`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道 | 1 |
| appid | 游戏APPID | 5011 |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3） | 1 |
| svrid | 服务器编号 | 1 |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 | 0 |
| openid | 用户OPENID号 | 1-1111 |
| charid | 玩家角色ID | 111 |
| groupid | 用于关联一次事件产生多条不同类型的日志 | 111 |
| sceneidbefore | 前一场景页面ID | 1233 |
| sceneidafter | 后一场景页面ID | 1235 |
| scenestate | 场景页面切换状态（切换申请 1/ 切换完成 2/ 切换失败 3），页面只记录切换申请 | 2 |


### 对接参数范例

```
channel=1&appid=5011&os=1&svrid=1&zoneid=1&openid=1-1111&charid=2323&groupid=1&sceneidbefore=1233&sceneidafter=1235&scenestate=2
```
