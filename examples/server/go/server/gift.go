package server

import "fmt"

/**
 * 使用礼包码
 *
 * @param string 秘钥
 * @param map[string]interface{} 兑换礼包码，需要包含以下字段
 * {
 * "game_id" : 游戏ID,   //必填
 * "channel_id" : 渠道ID,  //必填
 * "plat" : 平台名称,  //选填
 * "area" : 大区号，没有填0  //选填
 * "partition" : 小区号,  //必填
 * "uid" : 用户ID,    //必填
 * "char_id" : 角色ID ,  //选填
 * "gakey" : 礼包码,  //必填
 * }
 *
 * @return bool
 *
 */
func GiftUse(loginKey string, data map[string]interface{}) bool {
	data["sign"] = MD5(fmt.Sprintf("%d&%d&%d&%s&%s&%s",
		data["game_id"].(int),
		data["channel_id"].(int),
		data["partition"].(int),
		data["uid"].(string),
		data["gakey"].(string),
		loginKey))
	header:= map[string]string{
		"Content-Type": "application/x-www-form-urlencoded",
	}
	response, err := httpRequest("GET", "http://apis.sdk.mobileztgame.com/sdk-plugins/api/gift-use", data, header, "")
	if err != nil {
		return  false
	}
	fmt.Println(response)
	result, err := jsonDecode(response)
	if err != nil {
		return false
	}
	if _, ok := result["code"]; !ok {
		return false
	}
	if int(result["code"].(float64)) == 0 {
		return true
	}
	return false
}
