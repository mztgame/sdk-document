package server

import (
	"fmt"
)

/**
 * 上报实时游戏在线人数
 *
 * @param string 秘钥
 * @param map[string]interface{} 游戏数据，需要包含以下字段
 * {
 * "game_id": 游戏ID,   //必填
 * "channel_id": 渠道ID,  //可选
 * "zone_id": 区ID,    //必填
 * "number": 人数,  //必填
 * }
 *
 * @return bool
 *
 */
func GameOnline(loginKey string, data map[string]interface{}) bool {
	data["sign"] = MD5(fmt.Sprintf("%d&%d&%d&%s",
		data["game_id"].(int),
		data["number"].(int),
		data["zone_id"].(int),
		loginKey))
	response, err := httpRequest("GET", "https://stat.sdk.mobileztgame.com/game/online", data, nil, "")
	if err != nil {
		return  false
	}
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

/**
 * 游戏登录数据上报
 *
 * @param string 秘钥
 * @param map[string]interface{} 游戏数据，需要包含以下字段
 * {
 * "game_id": 游戏ID,   //必填
 * "channel_id": 渠道ID,  //必填
 * "ip": 客户端用户IP地址,  //必填
 * "openid": 用户ID,  //必填
 * "device_udid": 设备标识码,  //必填
 * "device_type": 设备型号,    //必填
 * "os": 设备系统类型，例如ios、android ,  //必填
 * "ad_id": 广告ID,  //选填
 * "zone_id": 区服ID,  //选填
 * "zone_name": 区服名称,  //选填
 * "char_id": 角色ID,  //选填
 * "char_name": 角色名称,  //选填
 * "level": 等级or段位,  //选填
 * "sync": 同步数据到beacon 1010,  //选填
 * "log_type": 日志类型,默认2 (1:账号登录,2:游戏区登录,3:账号+游戏区登录),  //选填
 * }
 *
 * @return bool
 *
 */
func LoginLogs(loginKey string, data map[string]interface{}) bool {
	signData := implodeParamsSort(data)
	data["sign"] = MD5(fmt.Sprintf("%s%s", signData, loginKey))
	header:= map[string]string{
		"Content-Type": "application/x-www-form-urlencoded",
	}
	response, err := httpRequest("POST", "https://beacon.ztgame.com/game/login-logs", data, header, "")
	if err != nil {
		return  false
	}
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


