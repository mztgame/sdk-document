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
		String currency = "";
		String extra = "123";
		String game_id = "GMG001";
		String is_black = "0";
		String is_cancel = "0";
		String is_recovery = "0";
		String is_test = "0";
		String memo = "";
		String openid = "1-1234";
		String order_id = "1399633295037630";
		String order_type = "0";
		String original_purchase_orderid = "";
		String product_id = "HWDPID0006";
		String time = "1404975144";
		String transaction_id = "1000000110081354";
		String version = "8.0";
		String zone_id = "1";

		String signString = account + amount + black_desc + channel + currency + extra + game_id
				+ is_black + is_cancel + is_recovery + is_test + memo + openid + order_id + order_type
				+ original_purchase_orderid + product_id + time + transaction_id
				+ version + zone_id;
		String sign = "MT/Wp3jz8l8HV62/OrpXdDIdEF9BGw8zCtwu8VZNaxCi52QXCC7RO2Q5yLRsQy8SmZMk0h0hsxUOXSZ8zZysUL+r/ATVknUs76zveaHROAfqhwo4sBqNA3jvnkCtbV/x9vF46vmNB7tDJcG6UDrJM5a/9Bn3Xq0ctlfSJpqJskr4dqyIlvCbQyi2YtnW2f5aNWATyNUntWtzakXYxZ7mPVT7hhspREo/3v/YcygmUHJJsJ2NnqkyWH7kV3nTTtvTQirjbzgeqnFd+KZBBHuBxOXDZInNLcaTnOQLskRddt0sYJ9/L8aDx9AvZtMe8kgQJhlNq13JOLFbCoMAEHD4Gg==";
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
