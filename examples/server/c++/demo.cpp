#include <iostream>
#include <string.h>
#include "CryptHelper.h"

int main(int argc, char ** argv)
{
    //应用公钥
    const std::string cpPkey="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+BoWf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuewv7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+OKUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPREs78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m0QIDAQAB";

    //签名内容
    const std::string reqData = "abcd6.001123GMG00100001-123413996332950376300HWDPID0006140497514410000001100813548.01";

    //签名
    std::string reqSign = "MT/Wp3jz8l8HV62/OrpXdDIdEF9BGw8zCtwu8VZNaxCi52QXCC7RO2Q5yLRsQy8SmZMk0h0hsxUOXSZ8zZysUL+r/ATVknUs76zveaHROAfqhwo4sBqNA3jvnkCtbV/x9vF46vmNB7tDJcG6UDrJM5a/9Bn3Xq0ctlfSJpqJskr4dqyIlvCbQyi2YtnW2f5aNWATyNUntWtzakXYxZ7mPVT7hhspREo/3v/YcygmUHJJsJ2NnqkyWH7kV3nTTtvTQirjbzgeqnFd+KZBBHuBxOXDZInNLcaTnOQLskRddt0sYJ9/L8aDx9AvZtMe8kgQJhlNq13JOLFbCoMAEHD4Gg==";

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
