package com.gamm.thirdlogindemo;

import com.gamm.assistlib.network.response.ZTHttpBaseBean;

/**
 * Created by panda on 2017/11/14.
 */

public class CodeResBean extends ZTHttpBaseBean {
    public int code;
    public String msg;
    public CodeData data;

    public class CodeData {
        public String openid;
        public String access_token;
        public String refresh_token;
        public int expires_in;
        public int expires_in_refresh;
    }
}
