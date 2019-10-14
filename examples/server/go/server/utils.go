package server

import (
	"crypto/md5"
	"crypto/rsa"
	"crypto/tls"
	"crypto/x509"
	"encoding/json"
	"encoding/pem"
	"fmt"
	"io/ioutil"
	"net/http"
	"sort"
	"strconv"
	"strings"
	"time"
	"errors"
	URL "net/url"
	"bytes"
)

/**
 * http请求
 *
 * @param string 请求方法
 * @param string 请求地址
 * @param map[string]interface{} 请求参数
 * @param map[string]string header头
 * @param string 请求body体内容，如果有内容会覆盖params内容
 *
 * @return string, error 返回内容,错误信息
 */
func httpRequest(method string, url string, params map[string]interface{}, header map[string]string, body string) (string, error) {
	//跳过证书验证
	tr := &http.Transport{
		TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
	}
	client := &http.Client{
		Timeout:   5 * time.Second,
		Transport: tr,
	}
	method = strings.ToUpper(method)
	var paramsStr string
	var req *http.Request
	var reqErr error

	if len(params) > 0 {
		paramsStr = httpBuildQuery(params)
	}

	if method == "GET" {
		if len(params) > 0 {
			url = url + "?" + paramsStr
		}
		req, reqErr = http.NewRequest(method, url, nil)
	} else {
		if body == "" {
			body = paramsStr
		}
		//生成请求
		req, reqErr = http.NewRequest(method, url, bytes.NewBuffer([]byte(body)))
	}

	if reqErr != nil {
		return "", reqErr
	}
	//设置header
	for headerK, headerV := range header {
		req.Header.Set(headerK, headerV)
	}

	resp, respErr := client.Do(req)
	if respErr != nil {
		return "", respErr
	}
	defer resp.Body.Close()

	result, readErr := ioutil.ReadAll(resp.Body)
	if readErr != nil {
		return "", readErr
	}

	return string(result), nil
}

/**
 * URL参数编码
 *
 * @param map[string]interface{} URL参数
 *
 * @return string
 *
 */
func httpBuildQuery(params map[string]interface{}) string {
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
		default:
			str = fmt.Sprintf("%v", v)
		}
		c.Add(k, str)
	}
	return c.Encode()
}

//拼接验签字符串，并key正序排序，格式如：key1=value1&key2=value2&key3=value3
func buildParamsSort(params map[string]interface{}) string {
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
		default:
			str = fmt.Sprintf("%v", v)
		}
		query = append(query, fmt.Sprintf("%s=%s", k, str))
	}
	return strings.Join(query, "&")

}

//拼接验签字符串，并key正序排序，格式如：value1value2value3
func implodeParamsSort(params map[string]interface{}) string {
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
		default:
			str = fmt.Sprintf("%v", v)
		}
		query = append(query, str)
	}
	//fmt.Println(strings.Join(query, ""))
	return strings.Join(query, "")

}

//md5封装
func MD5(str string) string {
	return fmt.Sprintf("%x", md5.Sum([]byte(str)))
}

//根据publickey字符串获得*rsa.PublicKey
func parsePublicKey(publicKey string) (*rsa.PublicKey, error) {
	publicBlock, _ := pem.Decode([]byte(publicKey))
	if publicBlock == nil {
		return nil, errors.New("public key error")
	}
	pki, err := x509.ParsePKIXPublicKey(publicBlock.Bytes)
	if err != nil {
		return nil, err
	}
	pub := pki.(*rsa.PublicKey)
	return pub, nil
}

//解析JSON字符串
func jsonDecode(data string) (map[string] interface{}, error) {
	var entity interface{}
	err := json.Unmarshal([]byte(data), &entity)
	if err != nil {
		return nil, err
	}
	return entity.(map[string]interface{}), nil
}

//map[string]string 转换成 map[string]interface{}
func convertMapToInterface(m map[string]string) map[string]interface{} {
	convertMap := make(map[string]interface{})
	for key, value := range m {
		convertMap[key] = interface{}(value)
	}
	return convertMap
}
