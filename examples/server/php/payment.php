<?php

//示例POST
$_POST = array(
	'account' => 'abcd',
	'amount' => '6.00',
	'black_desc' => '',
	'channel' => '1',
	'extra' => '123',
	'game_id' => 'GMG001',
    'is_black' => '0',
	'is_recovery' => '0',
    'is_test' => '0',
	'openid' => '1-1234',
	'order_id' => '1399633295037630',
	'original_purchase_orderid' => '',
	'product_id' => 'HWDPID0006',
	'time' => '1404975144',
	'transaction_id' => '1000000110081354',
	'version' => '6.0',
	'zone_id' => '1',
	'sign' => '739dLJZycZKkTq4DFhR7S+rMv2a5pMCCnjSe5+Rm/QgMyjrikZISpEIgS8SXkzCs0kh2OlKP8numISgFDeNIMR0V6iFTLbL5yzKMCLU05RTbZyij/fVoyTI96R89xU6oytDvRSJKjvCuWcMhd+jb82k7GVgAmjgSTD0egKzRGupzf5LCRg20j0DZZxjsP82kBu0BQmKOT1OmVGBiQGtc/ccWsgncrOfJ/jTbcbFn+wuo5Dno+fjGpHBtdiWicniAVTdisP9eoKWRBvehRDPEoSYeo9IuR/OZYvenn17EAgMzVTGGzMWejSZ0rgHhqi2F1/BhuFEeL2NEe+om6WuAeg==',
);

//示例公钥
$publicKey = <<<EOT
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo
Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew
v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O
KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg
9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE
s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m
0QIDAQAB
-----END PUBLIC KEY-----
EOT;

//示例验证签名
$params = $_POST;
$sign = base64_decode($params['sign']);
unset($params['sign']);
ksort($params); //可忽略, 参数传递时已经排序
$signData = implode($params);
$keySource = openssl_pkey_get_public($publicKey); 

if (openssl_verify($signData, $sign, $keySource) === 1) {

	//示例订单数据
	$gameOrder = array(
		'product_id' => 'HWDPID0006',
		'amount' => '6.00',
		'status' => 1, //1已完成, 0未完成
	);

    //IOS充值 product_id 验证
	if ($gameOrder['product_id'] != $params['product_id']) {
	    echo '{"code":2}'; 
		return ;
	}
 
	//金额验证
	if ($gameOrder['amount'] != $params['amount']) {
	    echo '{"code":2}';
		return ;
	}
 
	//订单已支付完成的
	if ($gameOrder['status']) {
	    echo '{"code":0}';
		return ;
	}
 
	//程序连接数据库异常 或 游戏异常等导致无法给用户添加游戏币.
	if (false) {
	    echo '{"code":1}';
		return ;
	}
 
	//todo success
	echo '{"code":0}';

} else { 
	echo '{"code":2}'; //签名验证失败返回
}
