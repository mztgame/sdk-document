package server

import (
	"crypto"
	"crypto/rsa"
	"crypto/sha1"
	"encoding/base64"
)

/**
 * 支付验证
 *
 * @param string 公钥
 * @param map[string]string sdk支付系统 HTTP POST方式通知游戏服务端，游戏服务端接收到的POST内容
 *
 * @return bool 验证失败返回false，验证成功返回true
 */
func PaymentVerify(publicKey string, postData map[string]string) bool  {
	//拼接签名原始字符串
	/*data := fmt.Sprintf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		postData["account"],
		postData["amount"],
		postData["black_desc"],
		postData["channel"],
		postData["currency"],
		postData["extra"],
		postData["game_id"],
		postData["is_black"],
		postData["is_cancel"],
		postData["is_recovery"],
		postData["is_test"],
		postData["memo"],
		postData["openid"],
		postData["order_id"],
		postData["order_type"],
		postData["original_purchase_orderid"],
		postData["product_id"],
		postData["time"],
		postData["transaction_id"],
		postData["version"],
		postData["zone_id"])*/
	sign := postData["sign"]
	delete(postData, "sign")
	data := implodeParamsSort(convertMapToInterface(postData))

	signData, _ := base64.StdEncoding.DecodeString(sign)
	pub, err := parsePublicKey(publicKey)
	if err != nil {
		return false
	}
	h := sha1.New()
	h.Write([]byte(data))
	digest := h.Sum(nil)
	err = rsa.VerifyPKCS1v15(pub, crypto.SHA1, digest, signData)
	if err != nil {
		return false
	}
	return true
}
