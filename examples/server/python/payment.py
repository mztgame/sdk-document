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
is_test = "0";
openid = "1-1234";
order_id = "1399633295037630";
product_id = "HWDPID0006";
time = "1404975144";
transaction_id = "1000000110081354";
version = "5.0";
zone_id = "1";

data = account + amount + black_desc + channel + extra + game_id + is_black + is_test + openid + order_id + product_id + time + transaction_id + version + zone_id;

sign = "fV3swPV0kEALBRE3fLj10CjDloXkTuw33K4p9ZFpTdR8nD5nGrXC4pbml3bfjJOUtfbqUWyeN9h18k1+SmAZ+Dqosaus2wFCiKEmGJjItr2HScwyiZX8OIVbWKinjUxl+EiJpsoApgH1+I1gjhr9Vy2zsw9tMrGX28XId4nZztluA9yens9q5rgwE4+HBj/+6QreYDi5XmKiihTuRHycHuEwQ3xvWs5Q3Si2nKxxOf5CUnPKIsKPuOPXMfFSTKv+GZ9hhEHcRAPUxMCZAOZfLwYLNsRIa+Xvr275yKxNak0ZWuv/gxck/EWO02hdpIOwhy1cPv/ZeodOvp3MgPcHbg=="
pubKey = rsa.PublicKey.load_pkcs1_openssl_pem(pubPem);
sign = base64.b64decode(sign);

print(rsa.verify(data.encode("utf-8"), sign, pubKey));
