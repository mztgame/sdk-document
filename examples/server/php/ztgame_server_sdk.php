<?php

/**
 * Class ZtgameServerSdk
 * gasdk登录和支付服务端验证类库
 *
 * @date 2019-05-15
 * @version 1.0.0
 */
class ZtgameServerSdk
{
    /**
     * 登录验证
     *
     * @param string $publicKey 公钥
     * @param string $entity sdk客户端登录成功返回的entity，JSON字符串
     * @param string $sign sdk客户端登录成功返回的sign
     * @param int $expire 登录有效期，单位秒，默认300秒，如果登录信息超过此有效期，则登录失败
     *
     * @return boolean|array 验证失败返回false，验证成功返回entity信息
     */
    public static function loginVerify($publicKey, $entity, $sign, $expire = 300)
    {
        if (empty($publicKey) || empty($entity) || empty($sign)) {
            return false;
        }
        $data = json_decode($entity, true);
        if (empty($data)) {
            return false;
        }
        ksort($data);
        $signData = urldecode(http_build_query($data));
        $sign = base64_decode($sign);
        $keySource = openssl_pkey_get_public($publicKey);
        if (openssl_verify($signData, $sign, $keySource) === 1) {
            if ($data['time'] < (time() - $expire)) {
                return false;
            }
            return $data;
        }
        return false;
    }

    /**
     * 支付验证
     *
     * @param string $publicKey 公钥
     * @param array $postData sdk支付系统 HTTP POST方式通知游戏服务端，游戏服务端接收到的POST内容
     *
     * @return boolean 验证失败返回false，验证成功返回true
     */
    public static function paymentVerify($publicKey, $postData)
    {
        if (empty($publicKey) || empty($postData) ) {
            return false;
        }
        $sign = base64_decode($postData['sign']);
        unset($postData['sign']);
        ksort($postData);
        $signData = implode($postData);
        $keySource = openssl_pkey_get_public($publicKey);
        if (openssl_verify($signData, $sign, $keySource) === 1) {
            return true;
        }
        return false;
    }

    /**
     * 上报实时游戏在线人数
     *
     * @param string $loginKey 秘钥
     * @param array $data 游戏数据，需要包含以下字段
     * [
     * 'game_id' => 游戏ID,   //必填
     * 'channel_id' => 渠道ID,  //可选
     * 'zone_id' => 区ID,    //必填
     * 'number' => 人数,  //必填
     * ]
     *
     * @return boolean
     *
     */
    public static function gameOnline($loginKey, $data)
    {
        if (empty($loginKey) || empty($data['game_id']) || !isset($data['zone_id']) || !isset($data['number'])) {
            return false;
        }
        $data['sign'] = md5($data['game_id'].'&'.$data['number'].'&'.$data['zone_id'].'&'.$loginKey);
        $response = self::httpRequest(
            'https://apis.sdk.mobileztgame.com/sdk-plugins/game/online',
            $data
        );
        if (!$response) {
            return false;
        }
        $result = self::jsonDecode($response);
        if (isset($result['code']) && $result['code'] == 0) {
            return true;
        }
        return false;
    }

    /**
     * 游戏登录数据上报
     *
     * @param string $loginKey 秘钥
     * @param array $data 游戏数据，需要包含以下字段
     * [
     * 'game_id' => 游戏ID,   //必填
     * 'channel_id' => 渠道ID,  //必填
     * 'ip' => 客户端用户IP地址,  //必填
     * 'openid' => 用户ID,  //必填
     * 'device_udid' => 设备标识码,  //必填
     * 'device_type' => 设备型号,    //必填
     * 'os' => 设备系统类型，例如ios、android ,  //必填
     * 'ad_id' => 广告ID,  //选填
     * 'zone_id' => 区服ID,  //选填
     * 'zone_name' => 区服名称,  //选填
     * 'char_id' => 角色ID,  //选填
     * 'char_name' => 角色名称,  //选填
     * 'level' => 等级or段位,  //选填
     * 'sync' => 同步数据到beacon 1010,  //选填
     * 'log_type' => 日志类型,默认2 (1:账号登录,2:游戏区登录,3:账号+游戏区登录),  //选填
     * ]
     *
     * @return boolean
     *
     */
    public static function loginLogs($loginKey, $data)
    {
        if (empty($loginKey) || empty($data['game_id']) || empty($data['channel_id']) || empty($data['ip'])
            || empty($data['openid']) || empty($data['device_udid']) || empty($data['device_type']) || empty($data['os'])
        ) {
            return false;
        }
        ksort($data);
        $signData = implode($data);
        $data['sign'] = md5($signData.$loginKey);
        $response = self::httpRequest(
            'https://beacon.ztgame.com/game/login-logs',
            $data,
            'post'
        );
        if (!$response) {
            return false;
        }
        $result = self::jsonDecode($response);
        if (isset($result['code']) && $result['code'] == 0) {
            return true;
        }
        return false;
    }

    /**
     * 推送消息
     *
     * @param string $loginKey 秘钥
     * @param array $data 推送内容，需要包含以下字段
     * [
     * 'game_id' => 游戏ID,   //必填
     * 'channel_id' => 渠道ID,  //必填
     * 'environment' => 推送环境(仅IOS，默认生产环境)，生产环境:product 开发环境:dev,  //选填
     * 'message_type' => 消息类型，通知消息:notify 透传消息:message,  //必填
     * 'title' => 消息标题,  //必填
     * 'content' => 消息内容,    //必填
     * 'audience_type' => 推送目标，全量推送:all 单账号推送:account 账号列表推送:account_list ,  //必填
     * 'audience_list' => 账号列表，当audience_type等于account时必须填写单个账号openid；当audience_type等于account_list时必须填写多个openid，以逗号分隔,  //选填
     * 'custom_content' => 自定义的键值对，json格式如：{"key1":"value1","key2":"value2"},  //选填
     * 'send_time' => 指定推送时间，格式为yyyy-MM-DD HH:MM:SS,  //选填
     * 'loop_times' => 循环任务重复次数，建议取值[1, 15],  //选填
     * 'loop_interval' => 循环执行消息下发的间隔，必须配合loop_times使用，以天为单位，取值[1, 14],  //选填
     * ]
     *
     * @return boolean
     *
     */
    public static function push($loginKey, $data)
    {
        if (empty($loginKey) || empty($data['game_id']) || empty($data['channel_id']) || empty($data['message_type'])
            || empty($data['title']) || empty($data['content']) || empty($data['audience_type'])
        ) {
            return false;
        }
        $data['sign'] = md5($data['game_id'].'&'.$data['channel_id'].'&'.$data['message_type'].'&'.$data['title']
            .'&'.$data['content'].'&'.$data['audience_type'].'&'.$loginKey);
        $response = self::httpRequest(
            'https://apis.sdk.mobileztgame.com/gapush/api/push',
            $data,
            'post'
        );
        if (!$response) {
            return false;
        }
        $result = self::jsonDecode($response);
        if (isset($result['code']) && $result['code'] == 0) {
            return true;
        }
        //var_dump($result);
        return false;
    }

    /**
     * 兑换礼包码
     *
     * @param string $loginKey 秘钥
     * @param array $data 礼包码内容，需要包含以下字段
     * [
     * 'game_id' => 游戏ID,   //必填
     * 'channel_id' => 渠道ID,  //必填
     * 'plat' => 平台名称,  //选填
     * 'area' => 大区号，没有填0,  //选填
     * 'partition' => 小区号,  //必填
     * 'uid' => 用户ID,    //必填
     * 'char_id' => 角色ID ,  //选填
     * 'from' => 来源 ,  //选填
     * 'gakey' => 礼包码,  //必填
     * ]
     *
     * @return boolean|array
     *
     */
    public static function giftUse($loginKey, $data)
    {
        if (empty($loginKey) || empty($data['game_id']) || empty($data['channel_id']) || empty($data['uid'])
            || empty($data['gakey']) || empty($data['partition'])
        ) {
            return false;
        }
        $data['sign'] = md5($data['game_id'].'&'.$data['channel_id'].'&'.$data['partition'].'&'.$data['uid']
            .'&'.$data['gakey'].'&'.$loginKey);
        $response = self::httpRequest(
            'http://apis.sdk.mobileztgame.com/sdk-plugins/api/gift-use',
            $data,
            'post'
        );
        if (!$response) {
            return false;
        }
        $result = self::jsonDecode($response);
        //var_dump($result);
        return $result;
    }

    /**
     * HTTP请求
     *
     * @param $gateway
     * @param $params
     * @param string $method
     * @param array $headers
     * @param null $body
     * @param array $resolve
     * @return bool|mixed
     */
    protected static function httpRequest(
        $gateway,
        $params,
        $method = 'get',
        $headers = [],
        $body = null,
        $resolve = []
    ) {
        $curl = curl_init();
        curl_setopt($curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 10);
        curl_setopt($curl, CURLOPT_TIMEOUT, 10);
        curl_setopt($curl, CURLOPT_HEADER, 0);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);

        curl_setopt($curl, CURLOPT_FORBID_REUSE, false);
        $headers = array_merge($headers, [
            'Connection: Keep-Alive',
            'Keep-Alive: 300'
        ]);
        curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
        if (!empty($resolve)) {
            curl_setopt($curl, CURLOPT_RESOLVE, $resolve);
        }
        if (strtolower($method) == 'post') {
            curl_setopt($curl, CURLOPT_POST, true);
            if (!empty($params)) {
                curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($params));
            }
            if (!empty($body)) {
                curl_setopt($curl, CURLOPT_POSTFIELDS, $body);
            }
            curl_setopt($curl, CURLOPT_URL, $gateway);
        } else {
            if (!empty($params)) {
                curl_setopt($curl, CURLOPT_URL, $gateway . '?' . http_build_query($params));
            } else {
                curl_setopt($curl, CURLOPT_URL, $gateway);
            }
        }

        $result = false;
        try {
            $ret = curl_exec($curl);
            if (false == $ret) {
                throw new \RuntimeException("cURL Error: " . curl_error($curl));
            } else {
                $rsp = curl_getinfo($curl, CURLINFO_HTTP_CODE);
                if (200 != $rsp && 403 != $rsp) {
                    throw new \RuntimeException("http code Error: " . $rsp);
                } else {
                    $result = $ret;
                }
            }

        } catch (\Exception $ex) {
            return false;
        }

        curl_close($curl);
        return $result;
    }

    /**
     * json_decode
     *
     * @param $data
     * @return mixed
     */
    protected static function jsonDecode($data)
    {
        return json_decode($data, true);
    }
}