package main

import (
	"crypto"
	"crypto/rsa"
	"crypto/sha1"
	"crypto/x509"
	"encoding/base64"
	"encoding/json"
	"encoding/pem"
	"fmt"
	URL "net/url"
	"strconv"
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
	//登录用户信息
	params = `{"entity":{"openid":"1-123123","account":"test","time":1482313093},"sign":"m7JTn\/y3IpB084vyeqoR9ysZ5\/GeowcsO3KDrDsaa8Fof2Xjq4gKdk5eDLh0nTRxZslfbet5AWs+p1M0rtF8Jan8T2VxCW\/czoCkrj4o\/xnYtb3wdenCXAT7LUoydjTmd+cf0I9kw0DjkPDurrT9kNqxzw6dq1A6EFZAts4f0\/H5+7kn81rzPq1RkWOM6OGm8R2D2WW\/jHfqZDo1mvfZvIzkA\/F0M62z2VsUK821BUkgoT23dByCdeqgx4hauJTHlnvg2\/MplDYMDONHai6gTFWb4FQgY2wJq1BIWCyXgDuid6n9Ck0m6paJEfOffbK7BgwH3ssaF7xYGD2sjEuCFw=="}`
	//json解析对像
	jsonParams interface{}
)

//拼接验签字符串，并key正序排序，格式如：key1=value1&key2=value2&key3=value3
func HttpBuildQuery(params map[string]interface{}) string {
	c := URL.Values{}
	for k, v := range params {
		str := ""
		switch v.(type) {
		case int:
			str = strconv.Itoa(v.(int))
		case string:
			str = v.(string)
		case float32:
		case float64:
			str = strconv.Itoa(int(v.(float64)))
		}
		c.Add(k, str)
	}
	return c.Encode()
}

func main() {
	err := json.Unmarshal([]byte(params), &jsonParams)
	if err != nil {
		fmt.Println("json unmarshal error")
		return
	}
	data, ok := jsonParams.(map[string]interface{})
	if !ok {
		fmt.Println("json data error")
		return
	}

	sign, _ := base64.StdEncoding.DecodeString(data["sign"].(string))

	entity := data["entity"].(map[string]interface{})
	query := HttpBuildQuery(entity)
	//fmt.Println(query, data["sign"].(string))

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
	h.Write([]byte(query))
	digest := h.Sum(nil)
	err = rsa.VerifyPKCS1v15(pub, crypto.SHA1, digest, sign)
	if err == nil {
		fmt.Println("签名验证到成功")
		return
	}
	fmt.Println("签名验证失败")
}
