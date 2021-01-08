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
 * "area" : 自定义ID，没有填0  //选填
 * "partition" : 区ID,  //必填
 * "uid" : 用户ID,    //必填
 * "char_id" : 角色ID ,  //选填
 * "from" : 来源 ,  //选填
 * "gakey" : 礼包码,  //必填
 * }
 *
 * @return map[string]interface{}
 *
 */
func GiftUse(loginKey string, data map[string]interface{}) (map[string]interface{}, error) {
	params := mapCopy(data)
	params["sign"] = MD5(fmt.Sprintf("%d&%d&%d&%s&%s&%s",
		params["game_id"].(int),
		params["channel_id"].(int),
		params["partition"].(int),
		params["uid"].(string),
		params["gakey"].(string),
		loginKey))
	header:= map[string]string{
		"Content-Type": "application/x-www-form-urlencoded",
	}
	response, err := httpRequest("GET", "http://apis.sdk.mobileztgame.com/sdk-plugins/api/gift-use", params, header, "")
	if err != nil {
		return  nil, err
	}
	fmt.Println(response)
	result, err := jsonDecode(response)
	if err != nil {
		return  nil, err
	}
	return result, nil
}
