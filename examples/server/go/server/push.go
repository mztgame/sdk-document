package server

import "fmt"

/**
 * 推送消息
 *
 * @param string 秘钥
 * @param map[string]interface{} 推送内容，需要包含以下字段
 * {
 * "game_id" : 游戏ID,   //必填
 * "channel_id" : 渠道ID,  //必填
 * "environment" : 推送环境(仅IOS，默认生产环境)，生产环境:product 开发环境:dev,  //选填
 * "message_type" : 消息类型，通知消息:notify 透传消息:message,  //必填
 * "title" : 消息标题,  //必填
 * "content" : 消息内容,    //必填
 * "audience_type" : 推送目标，全量推送:all 单账号推送:account 账号列表推送:account_list ,  //必填
 * "audience_list" : 账号列表，当audience_type等于account时必须填写单个账号openid；当audience_type等于account_list时必须填写多个openid，以逗号分隔,  //选填
 * "custom_content" : 自定义的键值对，json格式如：{"key1":"value1","key2":"value2"},  //选填
 * "send_time" : 指定推送时间，格式为yyyy-MM-DD HH:MM:SS,  //选填
 * "loop_times" : 循环任务重复次数，建议取值[1, 15],  //选填
 * "loop_interval" : 循环执行消息下发的间隔，必须配合loop_times使用，以天为单位，取值[1, 14],  //选填
 * }
 *
 * @return bool
 *
 */
func Push(loginKey string, data map[string]interface{}) bool {
	data["sign"] = MD5(fmt.Sprintf("%d&%d&%s&%s&%s&%s&%s",
		data["game_id"].(int),
		data["channel_id"].(int),
		data["message_type"].(string),
		data["title"].(string),
		data["content"].(string),
		data["audience_type"].(string),
		loginKey))
	header:= map[string]string{
		"Content-Type": "application/x-www-form-urlencoded",
	}
	response, err := httpRequest("POST", "http://apis.sdk.mobileztgame.com/gapush/api/push", data, header, "")
	if err != nil {
		return  false
	}
	result, err := jsonDecode(response)
	if err != nil {
		return false
	}
	//fmt.Println(result)
	if _, ok := result["code"]; !ok {
		return false
	}
	if int(result["code"].(float64)) == 0 {
		return true
	}
	return false
}
