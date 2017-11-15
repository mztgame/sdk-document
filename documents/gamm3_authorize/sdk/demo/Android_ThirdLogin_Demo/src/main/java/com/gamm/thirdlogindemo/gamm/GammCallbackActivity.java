package com.gamm.thirdlogindemo.gamm;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.gamm.thirdlogin.GammApiFactory;
import com.gamm.thirdlogin.model.GammBaseResp;
import com.gamm.thirdlogin.GammRespListener;
import com.gamm.thirdlogin.model.GammLoginResp;
import com.google.gson.Gson;

/**
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
    public void onResp(GammBaseResp resp, Handler handler) {
        if (resp instanceof GammLoginResp) {
            GammLoginResp loginResp = (GammLoginResp) resp;
            Log.e("111", loginResp.toString());
            if (handler != null) {
                Message message = Message.obtain();
                message.what = 1000;
                message.obj = new Gson().toJson(loginResp);
                handler.sendMessage(message);
            }
        }
        finish();
    }
}
