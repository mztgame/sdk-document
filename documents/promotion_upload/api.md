# 对 AMT 提供的接口文档。

## 统一说明

主机：```http://up.ztgame.com```

统一参数：<br>
```time``` 当前时间戳。<br>
```sign```  md5签名。

> 签名算法
```
1. 将所有参数(包含time)，按照 key 进行字典排序。
2. 序列化成url参数模式(a=b&c=d)
3. md5一次
4. 拼接上秘钥
5. 再 md5 一次

举例：
参数有 {a: '11', m: '2', b: '3', time: 1234567891}
秘钥为：abc
1. 排序后：{a: '11', b: '3', m: '2', time: 1234567891}
2. 序列化后 a=11&b=3&m=2&time=1234567891
3. md5一次： eefe8f50ba446d9e5b335b8628924820
4. 拼上秘钥： eefe8f50ba446d9e5b335b8628924820abc
5. 再次md5：e976956f26a0eed8a6d865833c62b4ba

```

返回格式：<br>
错误码 0 是成功，非0是失败，错误信息是msg；有业务数据放在 data 里。
```
{
    code: 0,
    msg: "",
    data: {}
}
```


## 接口文档

### 审核失败

地址：```/index/api/rollback```

| 参数名 | 类型 | 是否必须 | 说明 |
| --- | --- | --- |--- |
| flow_id | int | 是 | amt流程id |
| time | int | 是 | 当前时间戳 |
| sign | string | 是 | 签名 |

### 审核通过

地址： ```/index/api/approve```

| 参数名 | 类型 | 是否必须 | 说明 |
| --- | --- | --- |--- |
| flow_id | int | 是 | amt流程id |
| time | int | 是 | 当前时间戳 |
| sign | string | 是 | 签名 |
















