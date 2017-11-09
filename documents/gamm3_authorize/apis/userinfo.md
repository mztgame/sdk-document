# 获取用户基本信息

接口地址：

> https://gamm3.ztgame.com/sns/account/userinfo

调用方式：   
**post**

参数：

| 参数         |  是否必须 | 说明   |
| ---         |  --- | ---       |
| access_token | 是      | 接口调用凭证 |
| openid       | 是      | 用户对应应用唯一标识|
| sign         | 是      | 签名串，见[签名算法](../signAlgorithm.md)|


正确返回示例：

```
{
    code: 0,
    msg: '成功',
    data: {
        'account': 'bigWame',
        'nickname': '大肚子',
        'sex': '1',
        'birth": '2005-03-28'
    }
}
```

**返回参数说明：**

| account | 说明  |
| ---     | ---    |
| account | 巨人通行证账号 |
| nickname | 昵称 |
| sex | 性别 
| birth | 生日 |

**错误示例**

```
{
    code: '31003',
    msg: '签名错误',
    data:{}
}
```