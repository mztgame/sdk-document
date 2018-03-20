#include <iostream>
#include <string.h>
#include "CryptHelper.h"

int main(int argc, char ** argv)
{
    //应用公钥
    const std::string cpPkey="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+BoWf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuewv7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+OKUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPREs78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m0QIDAQAB";

    //签名内容
    const std::string reqData = "abcd6.001123GMG001001-12341399633295037630HWDPID0006140497514410000001100813545.01";

    //签名
    std::string reqSign = "fV3swPV0kEALBRE3fLj10CjDloXkTuw33K4p9ZFpTdR8nD5nGrXC4pbml3bfjJOUtfbqUWyeN9h18k1+SmAZ+Dqosaus2wFCiKEmGJjItr2HScwyiZX8OIVbWKinjUxl+EiJpsoApgH1+I1gjhr9Vy2zsw9tMrGX28XId4nZztluA9yens9q5rgwE4+HBj/+6QreYDi5XmKiihTuRHycHuEwQ3xvWs5Q3Si2nKxxOf5CUnPKIsKPuOPXMfFSTKv+GZ9hhEHcRAPUxMCZAOZfLwYLNsRIa+Xvr275yKxNak0ZWuv/gxck/EWO02hdpIOwhy1cPv/ZeodOvp3MgPcHbg==";

    //验签
    EVP_PKEY* pkey = UTILS::CryptHelper::getKeyByPKCS1(cpPkey, 0);
    if(!pkey)
    {
        std::cout<<"getKeyByPKCS1 error"<<std::endl;
    }

    if(UTILS::CryptHelper::verifySha1WithRsa(reqData, reqSign, pkey))
    {
        std::cout<<"verify sign success"<<std::endl;
    }
    else
    {
        std::cout<<"verify sign error"<<std::endl;
    }

    return 0;

}
