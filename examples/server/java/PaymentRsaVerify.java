import java.security.KeyFactory;
import java.security.PublicKey;
import java.security.Signature;
import java.security.spec.X509EncodedKeySpec;
import java.util.Base64;

/**
 * 
 * JDK 1.8 以上, 否则请修改Base64方式
 */
public class PaymentRsaVerify {

	private static final String PUBLIC_KEY = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo"
			+ "Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew"
			+ "v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O"
			+ "KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg"
			+ "9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE"
			+ "s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m"
			+ "0QIDAQAB";

	public static void main(String[] args) {

		String account = "abcd";
		String amount = "6.00";
		String black_desc = "";
		String channel = "1";
		String extra = "123";
		String game_id = "GMG001";
		String is_black = "0";
		String is_test = "0";
		String openid = "1-1234";
		String order_id = "1399633295037630";
		String product_id = "HWDPID0006";
		String time = "1404975144";
		String transaction_id = "1000000110081354";
		String version = "5.0";
		String zone_id = "1";

		String signString = account + amount + black_desc + channel + extra + game_id
				+ is_black + is_test + openid + order_id + product_id + time + transaction_id
				+ version + zone_id;
		String sign = "fV3swPV0kEALBRE3fLj10CjDloXkTuw33K4p9ZFpTdR8nD5nGrXC4pbml3bfjJOUtfbqUWyeN9h18k1+SmAZ+Dqosaus2wFCiKEmGJjItr2HScwyiZX8OIVbWKinjUxl+EiJpsoApgH1+I1gjhr9Vy2zsw9tMrGX28XId4nZztluA9yens9q5rgwE4+HBj/+6QreYDi5XmKiihTuRHycHuEwQ3xvWs5Q3Si2nKxxOf5CUnPKIsKPuOPXMfFSTKv+GZ9hhEHcRAPUxMCZAOZfLwYLNsRIa+Xvr275yKxNak0ZWuv/gxck/EWO02hdpIOwhy1cPv/ZeodOvp3MgPcHbg==";
System.out.println(PUBLIC_KEY);
		System.out.println(signString);
		System.out.println(rsaVerify(signString, sign));
	}

	public static boolean rsaVerify(String data, String sign) {

		// 解密由base64编码的公钥
		byte[] keyBytes = Base64.getDecoder().decode(PUBLIC_KEY);

		// 构造X509EncodedKeySpec对象
		X509EncodedKeySpec keySpec = new X509EncodedKeySpec(keyBytes);

		try {
			// KEY_ALGORITHM 指定的加密算法
			KeyFactory keyFactory = KeyFactory.getInstance("RSA");

			// 取公钥匙对象
			PublicKey pubKey = keyFactory.generatePublic(keySpec);

			Signature signature = Signature.getInstance("SHA1withRSA");
			signature.initVerify(pubKey);
			signature.update(data.getBytes());

			// 验证签名是否正常
			return signature.verify(Base64.getDecoder().decode(sign));
		} catch (Exception e) {
			System.out.println("Error:" + e.getMessage());
			return false;
		}
	}
}
