在线接口说明
=========================

在线接口日志:

POST `http://beacon.mztgame.com/game/online`
 
### 接口参数
 
| 参数名 | 说明 | 范例 |
|------|------|------|
| channel | 渠道（不区分请填写0） |  |
| appid | 游戏APPID |  |
| os | 移动终端操作系统（ios 1 /android 2 /wp 3；不区分请填写0） |  |
| zoneid | 针对分区分服的游戏填写分区id，用来唯一标示一个区；非分区分服游戏请填写0 |  |
| onlinenum | 同时在线人数 |  |

### 对接参数范例

```
channel=1&appid=5011&os=1&zoneid=1&onlinenum=222
```
