package main

import (
	"crypto"
	"crypto/rsa"
	"crypto/sha1"
	"crypto/x509"
	"encoding/base64"
	"encoding/pem"
	"fmt"
)

var (
	//公钥
	pubPem = `-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo
Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew
v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O
KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg
9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE
s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m
0QIDAQAB
-----END PUBLIC KEY-----`

	//http post 内容
	account        = "abcd"
	amount         = "6.00"
	black_desc     = ""
	channel        = "1"
	currency        = ""
	extra          = "123"
	game_id        = "GMG001"
	is_black 	   = "0"
	is_cancel 	   = "0"
	is_recovery    = "0";
	is_test 	   = "0"
	memo 	   = ""
	openid         = "1-1234"
	order_id       = "1399633295037630"
	order_type       = "0"
	original_purchase_orderid       = ""
	product_id     = "HWDPID0006"
	time           = "1404975144"
	transaction_id = "1000000110081354"
	version        = "8.0"
	zone_id        = "1"
	sign           = "MT/Wp3jz8l8HV62/OrpXdDIdEF9BGw8zCtwu8VZNaxCi52QXCC7RO2Q5yLRsQy8SmZMk0h0hsxUOXSZ8zZysUL+r/ATVknUs76zveaHROAfqhwo4sBqNA3jvnkCtbV/x9vF46vmNB7tDJcG6UDrJM5a/9Bn3Xq0ctlfSJpqJskr4dqyIlvCbQyi2YtnW2f5aNWATyNUntWtzakXYxZ7mPVT7hhspREo/3v/YcygmUHJJsJ2NnqkyWH7kV3nTTtvTQirjbzgeqnFd+KZBBHuBxOXDZInNLcaTnOQLskRddt0sYJ9/L8aDx9AvZtMe8kgQJhlNq13JOLFbCoMAEHD4Gg=="
)

func main() {
	//签名内容
	data := fmt.Sprintf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", account, amount, black_desc, channel, currency, extra, game_id, is_black, is_cancel, is_recovery, is_test, memo, openid, order_id, order_type, original_purchase_orderid, product_id, time, transaction_id, version, zone_id)
	sign, _ := base64.StdEncoding.DecodeString(sign)
	//验签
	block, _ := pem.Decode([]byte(pubPem))
	if block == nil {
		fmt.Println("public key error")
		return
	}
	pubInterface, err := x509.ParsePKIXPublicKey(block.Bytes)
	if err != nil {
		fmt.Println("public key error")
		return
	}
	pub := pubInterface.(*rsa.PublicKey)
	h := sha1.New()
	h.Write([]byte(data))
	digest := h.Sum(nil)
	err = rsa.VerifyPKCS1v15(pub, crypto.SHA1, digest, sign)
	if err == nil {
		//签名验证到成功

		//游戏业务处理

		fmt.Println(`{"code":0}`)
		return
	}
	//签名验证到失败
	fmt.Println(`{"code":2}`)
}
