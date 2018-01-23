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
	"sort"
	"strconv"
	"strings"
)

var (
	//公钥
	pubPem = `-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2aVhd+cDlvdel8x2jWL1
Gct39umu5xxeQ2M6HheiMkawbO7klT/2Nc2Ro3Xq6qp69Q7zwCeFo8egQDiZsCPu
04RdasgwKPNQN4vsUPvpk1OTO+pa8zzx/YwhdYChrjeKpSxMoFJujzO6qh+Pc81A
nMOgVwISXF3WuM49Bkob+vvTOynApBaYBZndBmomVWTezQIU8X2+TmgvQaqxLc/6
lQW+OVp+gUcILg0fVebTpE1ZghMVrihq0/DvQ4IOYC18gINzNBqxnSv0ggl59A60
7nYFZZYOMh05m7bgjOOCGIVTKTurM7++VqD4suptBXWU1G/PGN/26CgFumj28oGZ
wQIDAQAB
-----END PUBLIC KEY-----`
	//登录用户信息
	params = `{"entity":{"openid":"1-2330056908","account":"_80_m_tfghm@163.com","account_type":24,"type":1,"time":1516673192},"sign":"CGFsUW+TLKoQOxZdbY0OlptZN4OcM0vlAz6ocfuSO/Op8MO728miG+eN/+1AeMkn53w3Fo1j3hdFspDhUUN1FDrsRSnjENmHGDus9zc4H3nkxL+Viv8rHQRsbsDPOF5Qfj7tLGAzt9CvNSh6bJfP02PZrA1VzUlaA9M68EtqUXNKzyLfw0bnW1MVPdLfY9edtmo/9WwbwXlgUsOuOB4LYHQd0H84JSfq1ify7Y9KPi1U+Z8caleygKf8rp8pQXP36a5lMXNyU9Md97yCVZurhzBihlM33O/A+SLz/1piFASV2TujtQ2ltWLOSDCU+NnX34SnNPchBxYV366BUh5RmQ=="}`
	//json解析对像
	jsonParams interface{}
)

//拼接验签字符串，并key正序排序，格式如：key1=value1&key2=value2&key3=value3
func HttpBuildQuery(params map[string]interface{}) string {
	var keys []string
	for k := range params {
		keys = append(keys, k)
	}
	sort.Strings(keys)

	var query []string
	for _, k := range keys {
		v := params[k]
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
		query = append(query, fmt.Sprintf("%s=%s", k, str))
	}
	return strings.Join(query, "&")

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
	fmt.Println(query, data["sign"].(string))

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
