package com.gamm.thirdlogindemo;

import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.TextView;

import com.gamm.assistlib.network.ZTHttpService;
import com.gamm.assistlib.network.callback.ZTDefaultAsynCallback;
import com.gamm.thirdlogin.GammApiFactory;
import com.gamm.thirdlogin.model.GammLoginReq;
import com.gamm.thirdlogin.model.GammLoginResp;
import com.google.gson.Gson;

import java.util.HashMap;
import java.util.Map;

import okhttp3.Request;

/**
 * Created by panda on 2017/11/6.
 */
public class MainActivity extends Activity {
    public TextView infor;
    ProgressDialog progressDialog;

    public Handler loginHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            progressDialog = ProgressDialog.show(MainActivity.this, "Loading...", "Please wait...", false, true);

            if (msg.what == 1000) {
                GammLoginResp resp = new Gson().fromJson(msg.obj.toString(), GammLoginResp.class);
                if (resp.errCode.equals("0")) {
                    getCode(resp);
                } else {
                    progressDialog.cancel();
                    progressDialog = null;
                    infor.setText(resp.toString());
                }
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        infor = (TextView) findViewById(R.id.infor);
        findViewById(R.id.login).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                GammLoginReq req = new GammLoginReq();
                req.packageName = "com.gamm.thirdlogindemo";
                // 可不传，不传的话sdk会随机生成
                req.state = "1234";
                GammApiFactory.getGammSDKApi().gammSendReq(req, loginHandler);
            }
        });
    }

    /**
     * 获取code
     *
     * @param gammBaseResp
     */
    public void getCode(GammLoginResp gammBaseResp) {
        Map<String, Object> params = new HashMap<>();
        params.put("app_id", App.appId);
        params.put("code", gammBaseResp.authCode);
        String sign = Md5Demo.md5BySort(params);
        params.put("sign", sign);
        ZTHttpService
                .post()
                .addParams(params)
                .url("http://gamm3.dev.ztgame.com/sns/oauth2/access_token")
                .enqueue(new ZTDefaultAsynCallback<CodeResBean>() {
                    @Override
                    public boolean onSuccess(Request request, CodeResBean codeResBean) {
                        if (codeResBean != null) {
                            infor.setText(codeResBean.msg + "(" + codeResBean.code + ")");
                        }

                        if (codeResBean != null && codeResBean.code == 0 && codeResBean.data != null) {
                            getAccountInfor(codeResBean.data.access_token, codeResBean.data.openid);
                            return true;
                        }
                        return false;
                    }
                });
    }

    /**
     * 获取用户信息
     *
     * @param token
     * @param openId
     */
    public void getAccountInfor(String token, String openId) {
        Map<String, Object> params = new HashMap<>();
        params.put("access_token", token);
        params.put("openid", openId);
        String sign = Md5Demo.md5BySort(params);
        params.put("sign", sign);
        ZTHttpService
                .post()
                .addParams(params)
                .url("http://gamm3.dev.ztgame.com/sns/account/userinfo")
                .enqueue(new ZTDefaultAsynCallback<AccountInfoResBean>() {
                    @Override
                    public boolean onSuccess(Request request, AccountInfoResBean codeResBean) {
                        progressDialog.cancel();
                        progressDialog = null;
                        if (codeResBean != null) {
                            infor.setText(codeResBean.msg + "(" + codeResBean.code + ")");
                        }

                        if (codeResBean != null && codeResBean.code == 0 && codeResBean.data != null) {
                            infor.setText("登录成功：\n\n" + "account: " + codeResBean.data.account
                                    + "\n" + "nickname: " + codeResBean.data.nickname
                                    + "\n" + "sex: " + codeResBean.data.sex
                                    + "\n" + "birth: " + codeResBean.data.birth);
                            return true;
                        }
                        return false;
                    }
                });
    }
}
