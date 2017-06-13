# GASDK接口参数列表 #
### 创建时间 ：2017年6月9日 ###
### 更新时间 ：2017年6月12日 ###
### 说明 : 该文档接口以Android为基础，iOS核对，具体差异在文档中已经列出

## 一.对外接口部分

### 1. IZTListener 回调接口 ###
	private IZTListener mListener = new IZTListener() {
		@Override
		public void onFinished(int what, int errcode, JSONObject json_obj) {
		}
	};

### 2. 初始化接口 ###
	boolean newInstance(Activity ac)

	void initZTGame(String gameId, String appName, boolean isLandScape, IZTListener listener)

### 3. 正常登录接口 ###
	void loginZTGame(String zoneId, String zoneName, boolean isAutoLogin)

### 4.扫码登录接口 ###
	void scanCodeLogin()

### 5.判定用户是否已登录 ###
	boolean isLogined()

### 6.获取已登录用户信息 ###
	public GiantUserInfo getLoginUserInfo()

	//调用方式
	GiantUserInfo mGiantUserInfo = IZTLibBase.getInstance().getLoginUserInfo();

### 7.用户中心 ###
	//官方版本默认返回true
	boolean isHasCenterZTGame（）

	//游戏调用接口
	void enterCenterZTGame()

### 8.切换账号 ###
	//官方版本默认返回true
	boolean isHasSwitchAccountZTGame（）

	//游戏调用接口
	void switchAccountZTGame()

### 9.悬浮窗 ###
	//显示悬浮窗，默认不显示
	void toolBarZTGame()

	//隐藏悬浮窗，默认不显示
	void hideToolBar()

	//生命周期接口--接入悬浮窗必须增加
	onStopZTGame()
	onResumeZTGame()
	destroyZTGame()

### 10.支付 ###
	void payZTGame(ZTPayInfo payInfo)

	ZTPayInfo payInfo = new ZTPayInfo();
	payInfo.setAmount(100);  //设置金额, 单位(分) *必传参数
	payInfo.setProductName("test item"); //设置商品名称 *必传参数
	payInfo.setMoneyName("元宝");//设置货币 *必传参数
	payInfo.setProductId("1001"); // 设置商品ID *必传参数
	payInfo.setZoneId("1");//设置区服 *必传参数
	payInfo.setExtra("1"); //设置游戏订单扩展信息 可选参数
	IZTLibBase.getInstance().payZTGame(payInfo);

### 11.断线重连 ###
	void offlineLogin()

### 12.实名认证 ###
	void realNameAuth()

### 13.是否有断线重连功能 ###
	//默认返回false，官方返回true
	boolean isHasOfflineLogin()

### 14.是否有实名认证功能 ###
	//默认返回false，官方返回true
	boolean isHasRealNameAuth()


## 二.消息类型
|	消息说明        |	消息值            		  | 	消息返回code说明	|
| -------------    |  -------------               | -----         		|
| 	初始化     	   |	ZTConsts.ZTGAME_INIT 	  			| 0-成功、其他-失败 |
|	正常登录        |	ZTConsts.ZTGAME_LOGIN               |   0-成功、其他-失败	|
|	扫码登录        |	ZTConsts.ZTGAME_SCANCODE_LOGIN      |   0-成功、其他-失败 |
| 	切换账号        |	ZTConsts.ZTGAME_LOGOUT     			|    只有0	|
| 	退出登录        |	ZTConsts.ZTGAME_LOGOUT     			|    只有0 	|
| 	退出游戏        |	ZTConsts.ZTGAME_QUIT      			|    0-成功、其他-失败 |
| 	创建订单号	   |    ZTConsts.ZTGAME_CREATE_ORDER                    |    0-成功、其他-失败 |
| 	支付        	   |	ZTConsts.ZTGAME_PAY      			|   0-支付成功、1-支付确认中、其他-失败	|
| 	断线重连        |	ZTConsts.ZTGAME_OFFLINE_LOGIN      	|   只有0	|
| 	实名认证        |	ZTConsts.ZTGAME_REALNAME_AUTH      	|   只有0	|
| 	账号绑定        |	ZTConsts.ZTGAME_ACCOUNT_BIND      	|   只有0	|


## 三.接口返回给游戏的数据 ##
### 1.登录成功返回数据(游客、手机、通行证) ###
    {
    "account":"_q_727aqbppv",
    "token":"ud1cbfae581a228c3c0b169c40or63p4",
    "accid":"1-1280057781",
    "channel":1,
    "mobile_type":"HTC+A9w",
    "device_type":"HTC+A9w",
    "imei":"000000000000000",
    "ip":"192.168.207.55",
    "mac":"80:01:84:2E:BB:38",
    "type":0,
    "entity":{
        "openid":"1-1280057781",
        "account":"_q_727aqbppv",
        "account_type":0,
        "type":0,
        "time":1496822584
    },
    "sign":"IjhTNR28G1yuHhRmvLAvKM69YhYbDYqZ8WEfSeTbgMeilUy7XseOwzmwzPZwxRQA1SsMuUp28ywxsrDWinLGA7WexmlR6LPZPTXWbd5jmmS+Ca9D41T80DfjRWQXFCTiqEzFRK3ujVg22qatXHtz0lBV7O9iph5rfE5zDM1bt0jjXTp5i0xx6LZJco4sCWdbJSntxqB2O62vC4T8afm9pX+UvoU6A7/r+Ma2P4nj6klqjNOoskEoGfRJ96ee7gKYLMFUdlnfjcDDR9MHUU197nTkKcmeXvDzCrYzebbU3WCOZ+D2YCorAtRPtxUlPeLV5/U4qcXCF4uMiSLeatSIeQ==",
    "gaplaySign":"9b58a1b4477ea651a560b3afb1048f6a",
    "viewName":"游客727aqbppv"
	}

### 2.获取单个用户信息数据：getLoginUserInfo ###
     GiantUserInfo giantUserInfo = IZTLibBase.getInstance().getLoginUserInfo();
     String sign = giantUserInfo.getSign();
     String accid = giantUserInfo.getAccid();
     String channel = giantUserInfo.getChannel();
     String entity = giantUserInfo.getEntity();
     String token = giantUserInfo.getToken();

## 四.请求头数据 ##

#### 1. 参数列表 ####
|	参数名称        |	参数说明            		  
| -------------    |  -------------                
| 	Content-Type   |	内容类型 	  			 
|	X-GAME-ID      |	游戏ID                
|	Accept         |	响应内容类型        
| 	X-Client-Info  |	json-object类型的标识数据     			  
| 	Authentication |	auth_code 传递，格式: Code {auth_code}

#### 2. X-Client-Info参数说明 			  
    {
    "sdk_version":"1.0.1_2017060612", //SDK版本号
    "device_udid":"000000000000000", //设备唯一标识
    "os_version":"android/7.0", //系统版本
    "device_type":"HTC A9w", //设备类型
    "mac":"80:01:84:2E:BB:38" //mac地址
	}


## 五.Android & iOS 内容差异 ##

### 1.接口差异 ###
##### <font color=green >接口由iOS-蒋紫薇统一修改为Android接口名</font> #####
|	接口描述           |	 Android                   |	iOS             | 备注 		  
| -----------------   |  -------------             | ----               |
| 	 初始化接口	      |	 newInstance               | ---                |  <font color=red >Android独有
| 	 初始化接口	      |	 initZTGame                | initZTGameWithID   |  <font color=green >已统一  
| 	 正常登录接口	      |	 loginZTGame               | loginZTGame 	    |  <font color=green >已统一   
| 	是否有用户中心功能  |	 isHasCenterZTGame         | isHasUserCenter    |  <font color=green >已统一
|	用户中心接口  	  |	 enterCenterZTGame         | userCenterZTGame   |  <font color=green >已统一             
|	是否有切换账号功能  |	 isHasSwitchAccountZTGame  | isHasSwitchAccount |  <font color=green >已统一      
| 	显示悬浮窗         |	 toolBarZTGame             | showToolbarZTGame  | <font color=green >已统一,Android会增加生命周期
| 	隐藏悬浮窗         |	 hideToolBar               | hideToolbarZTGame  | <font color=green >已统一,Android会增加生命周期
| 	获取平台ID(渠道ID) |	 getPlatform               | getPlatformID      | <font color=green >已统一,文档都未对外
| 	获取平台name(渠道名称) |	 getAdapter            | getPlatformAdapter | <font color=green >已统一,文档都未对外


### 2.获取单个用户信息数据差异：getLoginUserInfo ###
##### <font color=green >参数由iOS-蒋紫薇统一修改为Android对应参数</font> #####
|	 Android数据                               |	 iOS数据    | 备注 	
| -----------------                           |  --------  | ----     |
| String sign = giantUserInfo.getSign();      |  sign      | ---      |
| String entity = giantUserInfo.getEntity();  |  entity    | ---      |
| String channel = giantUserInfo.getChannel();|  ---       | <font color=green >iOS增加   |
| String accid = giantUserInfo.getAccid();    |  ---       | <font color=green >iOS增加   |
| String token = giantUserInfo.getToken();    |  ---       | <font color=green >iOS增加   |

### 3.最终返回给游戏的参数 ###
##### <font color=red >1. Android由于历史版本，多一个参数：mobile_type，其它参数一致</font> #####
##### <font color=red >2. entity的获取 ： Android直接从参数中获取，iOS通过[ZTSDKInfo instance].entityDic获取</font> #####



    {
    "account":"_q_727aqbppv",
    "token":"ud1cbfae581a228c3c0b169c40or63p4",
    "accid":"1-1280057781",
    "channel":1,
    "mobile_type":"HTC+A9w",
    "device_type":"HTC+A9w",
    "imei":"000000000000000",
    "ip":"192.168.207.55",
    "mac":"80:01:84:2E:BB:38",
    "type":0,
    "entity":{
        "openid":"1-1280057781",
        "account":"_q_727aqbppv",
        "account_type":0,
        "type":0,
        "time":1496822584
    },
    "sign":"IjhTNR28G1yuHhRmvLAvKM69YhYbDYqZ8WEfSeTbgMeilUy7XseOwzmwzPZwxRQA1SsMuUp28ywxsrDWinLGA7WexmlR6LPZPTXWbd5jmmS+Ca9D41T80DfjRWQXFCTiqEzFRK3ujVg22qatXHtz0lBV7O9iph5rfE5zDM1bt0jjXTp5i0xx6LZJco4sCWdbJSntxqB2O62vC4T8afm9pX+UvoU6A7/r+Ma2P4nj6klqjNOoskEoGfRJ96ee7gKYLMFUdlnfjcDDR9MHUU197nTkKcmeXvDzCrYzebbU3WCOZ+D2YCorAtRPtxUlPeLV5/U4qcXCF4uMiSLeatSIeQ==",
    "gaplaySign":"9b58a1b4477ea651a560b3afb1048f6a",
    "viewName":"游客727aqbppv"
	}

#### 4.消息对比 ####
|	消息说明        |	消息值              | 	消息返回code说明	| 备注
| -------------    |  -------------        | -----         		| --- |
| 	初始化     	   | ZTGAME_INIT 	  	   | 0-成功、其他-失败    |
|	正常登录        | ZTGAME_LOGIN          |   0-成功、其他-失败	|
|	扫码登录        | ZTGAME_SCANCODE_LOGIN |   0-成功、其他-失败  |
| 	切换账号        | ZTGAME_LOGOUT     	   |    只有0	        |
| 	退出登录        | ZTGAME_LOGOUT     	   |    只有0 	        |
| 	退出游戏        | ZTGAME_QUIT      	   |    0-成功、其他-失败 |
| 	创建订单号	   | ZTGAME_CREATE_ORDER   |    0-成功、其他-失败 |  
| 	支付        	   | ZTGAME_PAY      	   |   0-支付成功、1-支付确认中、其他-失败	| <font color=red >iOS 0-成功，其他-失败
| 	断线重连        | ZTGAME_OFFLINE_LOGIN  |   只有0	|
| 	实名认证        | ZTGAME_REALNAME_AUTH  |   只有0          	|
| 	账号绑定        | ZTGAME_ACCOUNT_BIND   |   只有0	| <font color=green >游客绑定手机、通行证发送
| 	窗口关闭        | ZTGAME_CLOSE          |   只有0  	| <font color=red >Android不发送该消息，iOS发送



## 六.服务端接口 ##
#### 1.服务端接口地址：[http://192.168.39.18:3000/documents/66](http://192.168.39.18:3000/documents/66 "服务端接口地址") ####

## 七.激活插件部分 ##
#### 1. IZTActiveListener回调接口 ####
    IZTActiveListener mListener = new IZTActiveListener() {
    		@Override
    		public void onActiveFinished(int what, int code, String response) {
			
			}
	}

#### 2. 初始化 ####
    void initWithGameId(Activity ctx, String gameId, boolean isLandscape, String userId, String channelId,
	 String account, IZTActiveListener listener)

#### 3.检查激活状态 ####
    void checkActived()

#### 4.显示激活窗口 ####
    void showActiveView()

#### 5.关闭激活窗口 ####
    void closeActiveView()

#### 6.回调消息 ####
|	消息说明         |	消息值            		 | 	消息返回code说明	           |
| -------------     |  -------------             | -----         		       |
| 	初始化   	    |	ZTGAME_ACTIVE_INIT 	  	 | 0-成功、其他-失败             |
| 	检查激活状态     	|	ZTGAME_NEED_ACTIVE_CHECK | 0-需要激活、其他-不需要激活    |
| 	用户激活操作     |	ZTGAME_ACTIVE_RESULT 	 | 0-激活成功 |
| 	用户点击关闭按钮  |	ZTGAME_ACTIVE_CLOSED 	 | 默认值0(关闭消息不需要判断code)|

## 八.更新说明 ##
2017年6月12日---吴杜
>1.iOS根据Android同步接口，实现接口统一(蒋紫薇);
>
>2.断线重连、实名认证、账号绑定都只发送0-成功，不发送失败;
>
>3.取消getPlatform接口对外，会增加新的文档统一对外;
>
>4.增加是否有断线重连、实名认证的两个接口

