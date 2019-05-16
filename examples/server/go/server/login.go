package server

import (
	"crypto"
	"crypto/rsa"
	"crypto/sha1"
	"encoding/base64"
	"encoding/json"
)

/**
 * 登录验证
 *
 * @param string 公钥
 * @param string sdk客户端登录成功返回的entity，JSON字符串
 * @param string sdk客户端登录成功返回的sign
 * @param int 登录有效期，单位秒，如果登录信息超过此有效期，测登录失败
 *
 * @return (map[string]interface{}, error) 验证成功返回entity信息
 */
func LoginVerify(publicKey string, entity string, sign string, expire int) (map[string]interface{}, error) {
	//json解析对像
	var jsonEntity interface{}
	err := json.Unmarshal([]byte(entity), &jsonEntity)
	if err != nil {
		return nil, err
	}
	loginEntity := jsonEntity.(map[string]interface{})
	signData, _ := base64.StdEncoding.DecodeString(sign)
	query := buildParamsSort(loginEntity)

	pub, err := parsePublicKey(publicKey)
	if err != nil {
		return nil, err
	}
	h := sha1.New()
	h.Write([]byte(query))
	digest := h.Sum(nil)
	err = rsa.VerifyPKCS1v15(pub, crypto.SHA1, digest, signData)
	if err != nil {
		return nil, err
	}
	return loginEntity, nil
}
