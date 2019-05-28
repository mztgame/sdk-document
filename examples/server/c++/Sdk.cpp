#include "Sdk.h"
#include <json/json.h>
#include <curl/curl.h>
#include <algorithm>
#include <string>
#include <sstream> 
#include <time.h>
#include <stdlib.h>
namespace  Sdk
{

#define  ENTER_FUNCTION   try{
#define  LEAVE_FUNCTION   }catch(...){return false;}
	std::string  buildReqDataFromEntity( std::map<std::string,std::string> & entity, std::map<std::string,std::string> &retData);
	std::string  implodeMapValue(std::map<std::string,std::string> &postData);
	std::string  curl(std::string url,std::map<std::string,std::string>data, std::string method);
	std::string  buildQueryUrl(std::map<std::string,std::string> &queryData);
	size_t curlWriteFunction(void *ptr, size_t size, size_t nmemb, void *data);
	bool  parseEntifyAndSign(const std::string  &jsonobj, std::map<std::string,std::string> & entify_out, std::string &sign_out);


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
		std::string url = 	"http://stat.mztgame.com/game/online";

		std::string _respData = curl(url,_onlineData,"get");
		if( _respData == "")
		{
			return false;
		}

		Json::Reader reader; 
		Json::Value root; 
		Json::Value::Members  members;
		std::string  retReq;
		if (!reader.parse(_respData.c_str(), root))   
		{ 
			return false;
		}
		int _retcode=root["code"].asInt();
		if (_retcode != 0)
		{
			return false;
		}

		return true;
		LEAVE_FUNCTION
	}

	bool loginLogs(const std::string &loginkeys, const std::map<std::string, std::string> &datas)
	{
		ENTER_FUNCTION
		std::map<std::string,std::string> _queryData = datas;
		std::string _signData = implodeMapValue(_queryData);
		_signData += loginkeys;
		_queryData["sign"] = CryptHelper::md5(_signData);

		std::string url = "https://beacon.ztgame.com/game/login-logs";
		std::string _respData = curl(url,_queryData,"post");
		if( _respData == "")
		{
			return false;
		}

		Json::Reader reader; 
		Json::Value root; 
		Json::Value::Members  members;
		std::string  retReq;
		if (!reader.parse(_respData.c_str(), root))   
		{ 
			return false;
		}
		int _retcode=root["code"].asInt();
		if (_retcode != 0)
		{
			return false;
		}

		return true;
		LEAVE_FUNCTION
	}


	bool push(const std::string & loginkeys, const std::map<std::string,std::string> &datas)
	{
		ENTER_FUNCTION
		std::map<std::string,std::string> _onlineData=datas;	
		std::ostringstream os;
		os<<_onlineData["game_id"]<<"&"<<_onlineData["channel_id"]<<"&"<<_onlineData["message_type"]<<"&"<<_onlineData["title"]<<"&"<<_onlineData["content"]<<"&"<<_onlineData["audience_type"]<<"&"<<loginkeys;
		_onlineData["sign"] = CryptHelper::md5( os.str());			
		std::string url = "https://gapush.sdk.mobileztgame.com/api/push"; 

		std::string _respData = curl(url,_onlineData,"post");
		if( _respData == "")
		{
			return false;
		}

		Json::Reader reader; 
		Json::Value root; 
		Json::Value::Members  members;
		std::string  retReq;
		if (!reader.parse(_respData.c_str(), root))   
		{ 
			return false;
		}
		int _retcode=root["code"].asInt();
		if (_retcode != 0)
		{
			return false;
		}

		return true;
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
		Json::Reader reader;
		Json::Value root;
		Json::Value::Members  members;
		try{
			if (!reader.parse(jsonobj.c_str(), root))
			{
				return false;
			}
			if( root["entity"].isNull() || root["sign"].isNull())
			{
				return false;
			}

			std::vector<std::string>  _keyArr;
			members = root["entity"].getMemberNames(); // 获取所有key的值
			for (Json::Value::Members::iterator iterMember = members.begin(); iterMember != members.end(); iterMember++) // 遍历每个key
			{  
				std::string strKey = *iterMember; 
				std::string value = root["entity"][strKey ].asString();
				entity_out[strKey] = value;
			}
			sign_out = root["sign"].asString();
			return true;
		}catch(...){
			return false;
		}
	}
	
}
