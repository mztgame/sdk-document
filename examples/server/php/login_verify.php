<?php

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

$data = json_decode('{"entity":{"openid":"1-123123","account":"test","time":1482313093},"sign": "m7JTn\/y3IpB084vyeqoR9ysZ5\/GeowcsO3KDrDsaa8Fof2Xjq4gKdk5eDLh0nTRxZslfbet5AWs+p1M0rtF8Jan8T2VxCW\/czoCkrj4o\/xnYtb3wdenCXAT7LUoydjTmd+cf0I9kw0DjkPDurrT9kNqxzw6dq1A6EFZAts4f0\/H5+7kn81rzPq1RkWOM6OGm8R2D2WW\/jHfqZDo1mvfZvIzkA\/F0M62z2VsUK821BUkgoT23dByCdeqgx4hauJTHlnvg2\/MplDYMDONHai6gTFWb4FQgY2wJq1BIWCyXgDuid6n9Ck0m6paJEfOffbK7BgwH3ssaF7xYGD2sjEuCFw=="}', true);

$signData = genSignStr($data['entity']);
echo $signData , "\n";

//$pkeyid = openssl_pkey_get_private(file_get_contents(__DIR__ . '/../example_private_key.txt'));
//openssl_sign($signData, $signature, $pkeyid);
// free the key from memory
//openssl_free_key($pkeyid);
//echo base64_encode($signature);exit;

$keySource = openssl_pkey_get_public($publicKey); 
$sign = base64_decode($data['sign']);
if (openssl_verify($signData, $sign, $keySource) === 1) {

    if ($data['entity']['time'] < time() - 43200) {
        echo "登录认证过期";
    } else {
        echo '签名验证到成功, openid: ' . $data['entity']['openid'];
    }

} else { 
    echo '签名验证失败'; //签名验证失败返回
}

function genSignStr(array $entity) {

    $signStrs = [];
    ksort($entity);
    foreach ($entity as $k => $v) {
        $signStrs[] = $k . '=' . $v;
    }

    return implode('&', $signStrs);
}
