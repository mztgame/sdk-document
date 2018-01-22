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
	channel        = "1"
	extra          = "123"
	game_id        = "GMG001"
	openid         = "1-1234"
	order_id       = "1399633295037630"
	product_id     = "HWDPID0006"
	time           = "1404975144"
	transaction_id = "1000000110081354"
	version        = "3.0"
	zone_id        = "1"
	sign           = "m2S0nl5i/bNqUqPMH8+qL3f4PgG/bINqDafdxo1pzVP/oXiItT4hKNkuXVXbBOlCrsG3wDkIMfWgBeo3JHrDqlS4wF6MPNVscc8JnaHn2IzeYnbew8r+dyLB0XDBkugUcEQHlO4Aat82PRWoRWFRDbdBK9mClbBsgEObW7+kcAMFoJlpxedjzk7LzDcPf8qXfLmr0HfU70RRj6/fhlKA3ZA+PL7bzluKg53v3HARRV5MPm90U92iWuL8zecyZ1M775k3pEswW8IllQNc4EuihY5zUJozUxeRmoqLxgZJI3aECy/dKlDWcHwWg083TGX3/nynYF6JlCj5tZ6WE3zuUQ=="
)

func main() {
	//签名内容
	data := fmt.Sprintf("%s%s%s%s%s%s%s%s%s%s%s%s", account, amount, channel, extra, game_id, openid, order_id, product_id, time, transaction_id, version, zone_id)
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
