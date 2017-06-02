广告监控插件接入说明文档
==========================

更新日期: 2017-06-02 

# 1.1. 流程图示

![渠道登录流程图](http://cdn.mztgame.ztgame.com.cn/ad/ad_flow.png)

# 1.2. 流程说明
> * 申请广告  项目->媒体中心->联系项管分配广告ID

> * 接入联调  媒体中心->平台中心->数据中心

> * 数据查看  项目->数据中心提供报表

# 1.3. 客户端sdk及文档下载地址

* [安卓](http://docs.mztgame.com/files/Android/plugin/DataPluginSdk1.1.9.zip)
* [IOS](http://docs.mztgame.com/files/iOS/plugin/ZTDataLib.zip)

# 1.4. FAQ

*  **如何进行广告插件的初始化？**

    gasdk初始化-> 广告插件初始化(否则取不到channel参数）

* **channel参数如何传入？**

    （1）安卓   
    
            `调用gasdk IZTLibBase.getInstance().getPlatform()`;
    
    （2）IOS     
            
            只有一个渠道，插件中已写死，不必另作处理。

* **adid参数如何传入？**

    （1）安卓  
           
           方法一(建议):`调用gasdk IZTLibBase.getUserInfo().get("config.ad_id")`; 
           方法二:从 assets/ztsdk_config.properties 文件获取 config.ad_id=*****(CPS打包工具写入或者自行修改）;
    
    （2）IOS   
    
            没有CPS的概念，填入0或者填空即可.
    
*  **openid及account填什么？**

    调用gasdk登陆接口之后，从返回的Entity中获取openid及account（注意：是平台的openid不是游戏的）填入。

*  **如果广告插件需要更新怎么办？**

    插件是独立于gasdk之外的，所以只要替换插件部分即可，不用动gasdk版本。
