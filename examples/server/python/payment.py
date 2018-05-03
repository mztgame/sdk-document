# -*- coding: utf-8 -*-
# Python 3
# pip install rsa
import rsa
import base64

pubPem = '''-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo
Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew
v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O
KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg
9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE
s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m
0QIDAQAB
-----END PUBLIC KEY-----'''

account = "abcd";
amount = "6.00";
black_desc = "";
channel = "1";
extra = "123";
game_id = "GMG001";
is_black = "0";
is_recovery = "0";
is_test = "0";
openid = "1-1234";
order_id = "1399633295037630";
original_purchase_orderid = "";
product_id = "HWDPID0006";
time = "1404975144";
transaction_id = "1000000110081354";
version = "6.0";
zone_id = "1";

data = account + amount + black_desc + channel + extra + game_id + is_black + is_recovery + is_test + openid + order_id + original_purchase_orderid + product_id + time + transaction_id + version + zone_id;

sign = "739dLJZycZKkTq4DFhR7S+rMv2a5pMCCnjSe5+Rm/QgMyjrikZISpEIgS8SXkzCs0kh2OlKP8numISgFDeNIMR0V6iFTLbL5yzKMCLU05RTbZyij/fVoyTI96R89xU6oytDvRSJKjvCuWcMhd+jb82k7GVgAmjgSTD0egKzRGupzf5LCRg20j0DZZxjsP82kBu0BQmKOT1OmVGBiQGtc/ccWsgncrOfJ/jTbcbFn+wuo5Dno+fjGpHBtdiWicniAVTdisP9eoKWRBvehRDPEoSYeo9IuR/OZYvenn17EAgMzVTGGzMWejSZ0rgHhqi2F1/BhuFEeL2NEe+om6WuAeg=="
pubKey = rsa.PublicKey.load_pkcs1_openssl_pem(pubPem);
sign = base64.b64decode(sign);

print(rsa.verify(data.encode("utf-8"), sign, pubKey));
