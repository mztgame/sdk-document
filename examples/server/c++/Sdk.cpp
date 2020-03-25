#include "Sdk.h"
#include <json/json.h>
#include <curl/curl.h>
#include <algorithm>
#include <string>
#include <sstream> 
#include <time.h>
#include <stdlib.h>
#include <memory>
namespace  Sdk
{

#define  SAFE_DELETE(X) { if( (X) != NULL){ delete (X); (X)=NULL;} }
#define  ENTER_FUNCTION   try{
#define  LEAVE_FUNCTION   }catch(...){return false;}
	std::string  buildReqDataFromEntity( std::map<std::string,std::string> & entity, std::map<std::string,std::string> &retData);
	std::string  implodeMapValue(std::map<std::string,std::string> &postData);
	std::string  curl(std::string url,std::map<std::string,std::string>data, std::string method);
	std::string  buildQueryUrl(std::map<std::string,std::string> &queryData);
	size_t curlWriteFunction(void *ptr, size_t size, size_t nmemb, void *data);
	bool  parseEntifyAndSign(const std::string  &jsonobj, std::map<std::string,std::string> & entify_out, std::string &sign_out);
	bool 	parseHttpResponse(const std::string  & jsonobj);


	bool  loginVerify(const std::string &publicKey , const std::string &jsonobj, int expire ,std::map<std::string,std::string > &retData) 
	{
		ENTER_FUNCTION
		//decode entity and sign
		std::string  sign;
		std::map<std::string,std::string>  entity;
		if( !parseEntifyAndSign(jsonobj,entity,sign))
		{
			return false;
		}

		std::string reqData = buildReqDataFromEntity(entity,retData);	
		EVP_PKEY* pkey = CryptHelper::getKeyByPKCS1(publicKey, 0);
		if( !pkey)
		{
			return false;
		}
		if (!CryptHelper::verifySha1WithRsa(reqData, sign, pkey))
		{
			return false;
		}
		//check expire time
		//
		time_t  _verifyTm=  strtoull( retData["time"].c_str(), NULL, 10);
		time_t  _now = time(NULL);
		if (_verifyTm + expire < _now)
		{
			return false;
		}
		
		return true;
		LEAVE_FUNCTION
	}


	bool paymentVerify(const std::string &publicKey, const std::map<std::string,std::string> &paramData)
	{
		ENTER_FUNCTION
		//copy the post data
		std::map<std::string,std::string> postData=paramData;

		std::map<std::string,std::string>::iterator _sign_itr = postData.find("sign");
		if( _sign_itr == postData.end())
		{
			return false;
		}
		std::string reqSign = postData["sign"];
		postData.erase(_sign_itr);
		std::string reqData = implodeMapValue(postData);
		//验签
		EVP_PKEY* pkey = CryptHelper::getKeyByPKCS1(publicKey, 0);
		if(!pkey)
		{
			return false;
		}

		if(CryptHelper::verifySha1WithRsa(reqData, reqSign, pkey))
		{
			return true;
		}
		return false;
		LEAVE_FUNCTION
	}


	bool  gameOnline(const std::string &loginkeys,const std::map<std::string,std::string> &datas)
	{
		ENTER_FUNCTION
		std::map<std::string,std::string> _onlineData=datas;	
		std::ostringstream os;
		os<<_onlineData["game_id"]<<"&"<<_onlineData["number"]<<"&"<<_onlineData["zone_id"]<<"&"<<loginkeys;
		_onlineData["sign"] = CryptHelper::md5( os.str());			
		std::string url = 	"http://apis.sdk.mobileztgame.com/sdk-plugins/game/online";

		std::string _respData = curl(url,_onlineData,"get");
		if( _respData == "")
		{
			return false;
		}

		return parseHttpResponse( _respData);
		LEAVE_FUNCTION
	}

	bool loginLogs(const std::string &loginkeys, const std::map<std::string, std::string> &datas)
	{
		ENTER_FUNCTION
		std::map<std::string,std::string> _queryData = datas;
		std::string _signData = implodeMapValue(_queryData);
		_signData += loginkeys;
		_queryData["sign"] = CryptHelper::md5(_signData);

		std::string url = "http://beacon.ztgame.com/game/login-logs";
		std::string _respData = curl(url,_queryData,"post");
		if( _respData == "")
		{
			return false;
		}
		return parseHttpResponse( _respData);
		LEAVE_FUNCTION
	}


	bool push(const std::string & loginkeys, const std::map<std::string,std::string> &datas)
	{
		ENTER_FUNCTION
		std::map<std::string,std::string> _onlineData=datas;	
		std::ostringstream os;
		os<<_onlineData["game_id"]<<"&"<<_onlineData["channel_id"]<<"&"<<_onlineData["message_type"]<<"&"<<_onlineData["title"]<<"&"<<_onlineData["content"]<<"&"<<_onlineData["audience_type"]<<"&"<<loginkeys;
		_onlineData["sign"] = CryptHelper::md5( os.str());			
		std::string url = "http://apis.sdk.mobileztgame.com/gapush/api/push";

		std::string _respData = curl(url,_onlineData,"post");
		if( _respData == "")
		{
			return false;
		}
		return parseHttpResponse( _respData);
		LEAVE_FUNCTION

	}



	std::string  buildReqDataFromEntity( std::map<std::string,std::string> & entity,std::map<std::string,std::string> &retData)
	{
		std::string  retReq;
		std::vector<std::string>  _keyArr;
		for (std::map<std::string,std::string>::iterator itr = entity.begin(); itr != entity.end(); itr ++)
		{  
			_keyArr.push_back(itr->first);
		}
		std::sort(_keyArr.begin(),_keyArr.end());
		unsigned int params_len=_keyArr.size();
		unsigned int i=0;
		for(i=0 ; i< params_len ; i++)
		{
			retData[_keyArr[i].c_str()] = entity[_keyArr[i]];
			retReq += _keyArr[i];
			retReq += "=";
			retReq += entity[_keyArr[i]];
			if( i +1 < params_len){
				retReq+="&";	
			}
		}
		return retReq;
	}


	std::string  implodeMapValue(std::map<std::string,std::string> &postData)
	{
		std::string _retStr;
		std::vector<std::string>  _keyArr;
		for ( std::map<std::string,std::string>::iterator itr=postData.begin(); itr != postData.end(); itr++)
		{  
			_keyArr.push_back(itr->first);
		}
		std::sort(_keyArr.begin(),_keyArr.end());
		unsigned int _params_len=_keyArr.size();
		unsigned int i=0;
		for(i=0 ; i< _params_len ; i++)
		{
			_retStr+=postData[_keyArr[i]];	
		}
		return _retStr;
	}



	std::string  buildQueryUrl(std::map<std::string,std::string> &queryData)
	{
		std::string _retStr;
		for( std::map<std::string,std::string>::iterator itr =queryData.begin(); itr != queryData.end(); itr++)
		{
			if( _retStr != ""){
				_retStr += "&";
			}	
			_retStr += itr->first;
			_retStr += "=";
			_retStr += itr->second;
		}
		return _retStr;
	}

	std::string  curl(std::string  url,std::map<std::string,std::string>data, std::string method="post")
	{
		std::string _retData ;
		std::string _queryStr = buildQueryUrl( data);
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
		CURL * pcurl=NULL;
		pcurl = curl_easy_init();    // 初始化
		if (pcurl)
		{
			curl_easy_setopt(pcurl, CURLOPT_TIMEOUT, 5L);//请求超时时长
			curl_easy_setopt(pcurl, CURLOPT_CONNECTTIMEOUT, 5L); //连接超时时长 
			curl_easy_setopt(pcurl, CURLOPT_NOSIGNAL, 1L); //关闭中断信号响应
			curl_easy_setopt(pcurl, CURLOPT_HTTPHEADER, headers);// 改协议头
			curl_easy_setopt(pcurl, CURLOPT_WRITEFUNCTION, curlWriteFunction);  //得到请求结果后的回调函数
			curl_easy_setopt(pcurl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(pcurl, CURLOPT_WRITEDATA,&_retData); //写的地址
			if ( method != "post")
			{
				std::string _getUrl = url + "?";
				_getUrl += _queryStr;
				curl_easy_setopt(pcurl, CURLOPT_URL,_getUrl.c_str());
			}
			else
			{
				curl_easy_setopt(pcurl,CURLOPT_URL,url.c_str());
				curl_easy_setopt(pcurl,CURLOPT_POSTFIELDS,_queryStr.c_str());
			}
			curl_easy_perform(pcurl);   // 执行
			curl_slist_free_all(headers);
			curl_easy_cleanup(pcurl);
		}
		return _retData;
	}

	size_t curlWriteFunction(void *ptr, size_t size, size_t nmemb, void *data)
	{
		int _retLen = 0;
		if( data == NULL)
		{
			return _retLen;
		}	
		_retLen = size * nmemb;	
		std::string * str = (std::string *)data;
		str->append( (char *)ptr, _retLen);
		return _retLen;
	}


	bool  parseEntifyAndSign(const std::string  &jsonobj, std::map<std::string,std::string> & entity_out, std::string &sign_out)
	{
		int nLen = jsonobj.length();
		Json::Value root;
		Json::CharReaderBuilder jsreader;
		Json::CharReader  * reader=jsreader.newCharReader();
		const char *pStart = jsonobj.c_str();
		std::string err;
		if(reader == NULL)
		{
			return false;
		}
		if (!reader->parse(pStart, pStart + nLen, &root, &err))
		{
			SAFE_DELETE(reader)
			return false;
		}
		SAFE_DELETE(reader)
		
		Json::Value _entity_v= root["entity"];
		Json::Value _sign_v = root["sign"];
		if( _entity_v.isNull() || _sign_v.isNull())
		{
			return false;
		}
		sign_out = _sign_v.asString();

		std::vector<std::string>  _keyArr;
		Json::Value::Members members = root["entity"].getMemberNames(); // 获取所有key的值
		//for (Json::Value::Members::iterator iterMember = members.begin(); iterMember != members.end(); iterMember++) // 遍历每个key
		for (Json::Value::Members::iterator strKey=members.begin(); strKey!=members.end(); strKey++)
		{  
			std::string value = root["entity"][*strKey ].asString();
			entity_out[*strKey] = value;
		}
		sign_out = root["sign"].asString();
		return true;
	}
	bool 	parseHttpResponse(const std::string  & jsonobj)
	{
		int nLen = jsonobj.length();
		Json::Value root;
		Json::CharReaderBuilder jsreader;
		Json::CharReader  * reader=jsreader.newCharReader();
		if(reader == NULL)
			return false;
		//std::unique_ptr<Json::CharReader> const reader(jsreader.newCharReader());
		const char *pStart = jsonobj.c_str();
		std::string err;
		if (!reader->parse(pStart, pStart + nLen, &root, &err))
		{
			SAFE_DELETE(reader)
			return false;
		}
		SAFE_DELETE(reader)
		Json::Value code_v = root["code"];
		if(code_v.isNull() || code_v.asInt() != 0)
		{
			return false;
		}
		return true;
	}

	
}
