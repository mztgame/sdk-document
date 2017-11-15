package com.gamm.thirdlogindemo;

import android.app.Application;

import com.gamm.assistlib.network.ZTHttpService;
import com.gamm.thirdlogin.GammApiFactory;

import okhttp3.OkHttpClient;

/**
 * Created by panda on 2017/11/6.
 */
public class App extends Application {
    public static String appId = "fdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsf";
    public static String appKey = "fdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfds";

    @Override
    public void onCreate() {
        super.onCreate();
        GammApiFactory.createSDKApi(this, appId);
        GammApiFactory.getGammSDKApi().setGammDebug(BuildConfig.DEBUG);

        OkHttpClient okHttpClient = new OkHttpClient.Builder().build();
        ZTHttpService.initZtHttpClient(okHttpClient, this);
    }
}
