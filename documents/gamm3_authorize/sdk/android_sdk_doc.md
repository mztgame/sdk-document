# 第三方登录账号管家的接入文档

## Android端

### 资源

Android端提供2种接入资源：

* **jar包 + 对应的资源**
* **aar包**

jar包的方案可以在eclipse和AS上使用，aar包只能在AS上使用。如果是AS作为开发IDE的，建议使用aar包的方式。

如果以jar方式接入，需要在自己的AndroidManifest.xml里加入：

```xml
<uses-permission android:name="android.permission.INTERNET" />

<activity android:name="com.gamm.thirdlogin.ui.GammDownloadActivity"
                  android:theme="@android:style/Theme.NoTitleBar"
                  android:screenOrientation="portrait" />
```

### 接入流程

#### 1、初始化api

实例工厂模式，提供3个接口：

```java
	/**
     * 创建GammSDKApi对象
     *
     * @param context 上下文
     * @return 返回GammSDKApi对象
     */
    public static GammSDKApi createSDKApi(Context context) 
    
    /**
     * 创建GammSDKApi对象
     *
     * @param context  上下文
     * @param appId  注册的appId
     * @return  返回GammSDKApi对象
     */
    public static GammSDKApi createSDKApi(Context context, String appId)
    
    /**
     * 获取实例，调用之前请先实例化
     *
     * @return
     */
    public static GammSDKApi getGammSDKApi()
```

调用示例（仅供参考）：

```java
/**
 * Created by panda on 2017/11/6.
 */
public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        GammApiFactory.createSDKApi(this, appId);
		GammApiFactory.getGammSDKApi().setGammDebug(BuildConfig.DEBUG);
    }
}
```

#### 2、sdk提供的API接口

```java
	/**
     * 发起具体的请求操作
     *
     * @param req
     */
    public void gammSendReq(GammBaseReq req, Handler handler);

    /**
     * 判断账号管家是否安装
     *
     * @return
     */
    public boolean isGammInstalled();

    /**
     * 设置sdk是否是debug状态
     *
     * @param isDebug
     */
    public void setGammDebug(boolean isDebug);

    /**
     * 完成时的回调第三方
     *
     * @param intent
     * @param respListener
     */
    public void handleIntent(Intent intent, GammRespListener respListener);

    /**
     * SDK的版本号
     *
     * @return
     */
    public String gammVersion();
```

登录调用示例（仅供参考）：

```java
/**
 * Created by panda on 2017/11/6.
 */
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        findViewById(R.id.login).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                GammLoginReq req = new GammLoginReq();
                req.packageName = "com.gamm.thirdlogindemo";
                // 可不传，不传的话sdk会随机生成
                req.state = "1234";
                GammApiFactory.getGammSDKApi().gammSendReq(req);
            }
        });
    }
}
```

#### 3、处理回调

对于回调类，第三方app的接收回调类必须以`.gamm.GammCallbackActivity`结尾，并且继承`GammRespListener`接口。

`GammCallbackActivity `的示例如下：

```java
**
 *
 * Created by panda on 2017/11/7.
 */
public class GammCallbackActivity extends Activity implements GammRespListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GammApiFactory.getGammSDKApi().handleIntent(getIntent(), this);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        GammApiFactory.getGammSDKApi().handleIntent(getIntent(), this);
    }

    @Override
    public void onResp(GammBaseResp resp) {
        // 第三方根据需要处理业务需要
    }
}
```

并且在AndroidManifest.xml里定义：

```xml
<activity
     android:name=".gamm.GammCallbackActivity"
     android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen"
     android:exported="true">
</activity>
```

#### 4、结构体定义
请求的结构体`GammBaseReq`

```java
	/**
     * 请求类型
     */
    public int type;
    /**
     * 用于保持请求和回调的状态，授权完成后带回给第三方。主要是防止CRSF攻击
     */
    public String state;
```

特殊的，各个业务的响应结构体基于`GammBaseReq `定义，如登录需要的

```java
	/**
     * app的包名
     */
    public String packageName;
```

响应的结构体`GammBaseResp`
	
```java
    /**
     * 请求完后，对应的错误码
     */
    public int errCode = 0;
    /**
     * 具体的错误信息
     */
    public String errMsg = "success";
    /**
     * 请求时的类型
     */
    public int type;
    /**
     * 用于保持请求和回调的状态，授权完成后带回给第三方。主要是防止CRSF攻击
     */
    public String state;
```	

特殊的，各个业务的响应结构体基于`GammBaseResp`定义，如登录需要的`GammLoginResp`：

```java
	/**
     * auth code
     */
    public String authCode;
```	

####特殊要求
第三方APP需要在清单文件的<application>标签里加上：

> android:taskAffinity="gamm.thirdlogin.attached.stack"

加这个的目的是为了将打开的账号管家的用于第三方登录的activity转移到第三方的任务栈中。

#### 5、错误码和相应的信息
状态码         | 描述           |
--------------------|------------------|
0      | 成功   | 
-1     | 普通错误类型  |
-2     | 用户点击取消并返回      |
-3     | 发送失败      |
-4     | 用户拒绝授权或授权失败      |
-5     | 巨人账号管家不支持      |

####完整demo
[android demo download](./demo/Android_ThirdLogin_Demo.zip)
[android demo 源码](./demo/Android_ThirdLogin_Demo)


