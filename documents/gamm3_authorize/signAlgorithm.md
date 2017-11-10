
## 账号管家签名算法

1. 将所有需要的参数(还没有sign参数)数组按照 Asics码倒序排列。
2. 将倒序后的数组拼接成http的query串
3. 执行一次md5，得到一个md5串
4. 将第一次得到的md5串，拼接上app_key
5. 再次md5，得到签名 sign。


示例：
```
参数数组为：
$params = ['appid' => 'afdsFdEWFjjkJ3kjK', 'openid' => 'NJJkkkjHdic3kDFDDd', 'access_token' => 'ajKDJtf4eikKjf234FJj'];
app_key的值为：
$app_key = 'NKFDJONFODJr434FDJLFJ435FDJL';

1. 排序后得到参数数组为： 
$sortedParams = ['openid' => 'NJJkkkjHdic3kDFDDd', 'appid' => 'afdsFdEWFjjkJ3kjK', 'access_token' => 'ajKDJtf4eikKjf234FJj'];

2. 拼接成query串后得到：
$queryStr = 'openid=NJJkkkjHdic3kDFDDd&appid=afdsFdEWFjjkJ3kjK&access_token=ajKDJtf4eikKjf234FJj';

3. md5后得到：
$foo = '8835a6adc86888661b7b6df55496d5a5';

4. 拼接上app_key后得到：
$bar = '8835a6adc86888661b7b6df55496d5a5&app_key=NKFDJONFODJr434FDJLFJ435FDJL';

5. 第二次md5后得到sign：
$sign = '3ec4d96c6663e8a0880179db4a94cd3f';
``` 
