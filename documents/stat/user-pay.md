征途2实时充值金额查询接口说明
=========================

POST `https://beacon.ztgame.com/service/user-pay`
 
### 接口参数
 
| 参数名 | 说明 | 范例 | 必填 |
|------|------|------|------|
| game_id | 游戏id | 5174 | 是 |
| openid | open_id | 1-12345 | 是 |
| begin | 开始时间(yyyy-mm-dd HH:ii:ss) | 2018-08-23 10:00:00 | 否
| end | 结束时间(yyyy-mm-dd HH:ii:ss) | 2018-08-23 11:00:00 | 否
| sign | 签名 |  | 是 |

### 返回值

```
content-type:application/json;charset=utf-8

{"code":0,"msg":"ok","data":1234}
```
| 参数名 | 说明 | 范例 |
|------|------|------|
| code | 错误码 | -1 |
| msg | 错误描述 | sign error |
| data | 总充值金额(元) | 1234 |

