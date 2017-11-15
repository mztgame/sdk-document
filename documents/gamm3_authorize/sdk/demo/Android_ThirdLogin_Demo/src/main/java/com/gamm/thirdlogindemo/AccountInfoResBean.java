package com.gamm.thirdlogindemo;

import com.gamm.assistlib.network.response.ZTHttpBaseBean;

/**
 * Created by panda on 2017/11/14.
 */

public class AccountInfoResBean extends ZTHttpBaseBean {
    public int code;
    public String msg;
    public AccountData data;

    public class AccountData {
        public String account;
        public String nickname;
        public String sex;
        public String birth;
    }
}
