using System;
using System.Text;
using System.IO;
using System.Security.Cryptography;


namespace RsaCryptoExample
{
  static class Program
  {
    static void Main()
    {
        string publicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/VweA5KME/PR7QIwe+Bo"
                         + "Wf+yM5tRVpaXWOZC7S4SeLT5zyd1gNzKjLHCxAIhsxYUnXHRCdsC+cnKTVfCBuew"
                         + "v7N2kZCKF+/gMiqSdfiJo3XE7lmrxpIKO6YnWt7Itq/VvMJoTO7g0KkjF/irzI+O"
                         + "KUj5DSZORHwulA6OXNjUJbGeMdIGX7VHgbk7dv8oqx+FE0bAQ4APtOiSs5agBRdg"
                         + "9De92tURcj15jztYtPvaRVn5O8ozTEui4Kh2Cmf1fPFKbv5yQyNhHaqMdI2tGPRE"
                         + "s78wGIiHT1yOmCMeKHCVgElwwgmFnmxKYsBD9XZ9GM6wzt/95M53jh/aNp/+9Y1m"
                         + "0QIDAQAB";

        string sign = "fV3swPV0kEALBRE3fLj10CjDloXkTuw33K4p9ZFpTdR8nD5nGrXC4pbml3bfjJOUtfbqUWyeN9h18k1+SmAZ+Dqosaus2wFCiKEmGJjItr2HScwyiZX8OIVbWKinjUxl+EiJpsoApgH1+I1gjhr9Vy2zsw9tMrGX28XId4nZztluA9yens9q5rgwE4+HBj/+6QreYDi5XmKiihTuRHycHuEwQ3xvWs5Q3Si2nKxxOf5CUnPKIsKPuOPXMfFSTKv+GZ9hhEHcRAPUxMCZAOZfLwYLNsRIa+Xvr275yKxNak0ZWuv/gxck/EWO02hdpIOwhy1cPv/ZeodOvp3MgPcHbg==";
        
        string content = "abcd6.001123GMG001001-12341399633295037630HWDPID0006140497514410000001100813545.01"; 

        Console.WriteLine(verify(content, sign, publicKey));
    }


    public static bool verify(string content, string signedString, string publicKey)
    {
        byte[] bPublicKey  = Convert.FromBase64String(publicKey);
        byte[] bSigned     = Convert.FromBase64String(signedString);
        byte[] bContent    = Encoding.UTF8.GetBytes(content);

        RSACryptoServiceProvider rsaCSP = DecodeX509PublicKey(bPublicKey);

        if (rsaCSP is RSACryptoServiceProvider) {
            return rsaCSP.VerifyData(bContent, CryptoConfig.MapNameToOID("SHA1"), bSigned);
        } else {
            return false;
        }
    }


    //------- Parses binary asn.1 X509 SubjectPublicKeyInfo; returns RSACryptoServiceProvider ---
    public static RSACryptoServiceProvider DecodeX509PublicKey(byte[] x509key)
    {
        // encoded OID sequence for  PKCS #1 rsaEncryption szOID_RSA_RSA = "1.2.840.113549.1.1.1"
        byte[] SeqOID = {0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00} ;
        byte[] seq = new byte[15];
        // ---------  Set up stream to read the asn.1 encoded SubjectPublicKeyInfo blob  ------
        MemoryStream  mem = new MemoryStream(x509key) ;
        BinaryReader binr = new BinaryReader(mem) ;    //wrap Memory Stream with BinaryReader for easy reading
        byte bt = 0;
        ushort twobytes = 0;

        try {
            twobytes = binr.ReadUInt16();
            if(twobytes == 0x8130)	//data read as little endian order (actual data order for Sequence is 30 81)
                binr.ReadByte();	//advance 1 byte
            else if(twobytes == 0x8230)
                binr.ReadInt16();	//advance 2 bytes
            else
                return null;

            seq = binr.ReadBytes(15);		//read the Sequence OID
            if(!CompareBytearrays(seq, SeqOID))	//make sure Sequence for OID is correct
                return null;

            twobytes = binr.ReadUInt16();
            if(twobytes == 0x8103)	//data read as little endian order (actual data order for Bit String is 03 81)
                binr.ReadByte();	//advance 1 byte
            else if(twobytes == 0x8203)
                binr.ReadInt16();	//advance 2 bytes
            else
                return null;

            bt = binr.ReadByte();
            if(bt != 0x00)		//expect null byte next
                return null;

            twobytes = binr.ReadUInt16();
            if(twobytes == 0x8130)	//data read as little endian order (actual data order for Sequence is 30 81)
                binr.ReadByte();	//advance 1 byte
            else if(twobytes == 0x8230)
                binr.ReadInt16();	//advance 2 bytes
            else
                return null;

            twobytes = binr.ReadUInt16();
            byte lowbyte = 0x00;
            byte highbyte = 0x00;

            if(twobytes == 0x8102)	//data read as little endian order (actual data order for Integer is 02 81)
                lowbyte = binr.ReadByte();	// read next bytes which is bytes in modulus
            else if(twobytes == 0x8202) {
                highbyte = binr.ReadByte();	//advance 2 bytes
                lowbyte = binr.ReadByte();
            } else
                return null;
            byte[] modint = {lowbyte, highbyte, 0x00, 0x00} ;   //reverse byte order since asn.1 key uses big endian order
            int modsize = BitConverter.ToInt32(modint, 0) ;

            byte firstbyte = binr.ReadByte();
            binr.BaseStream.Seek(-1, SeekOrigin.Current);

            if(firstbyte == 0x00)	{	//if first byte (highest order) of modulus is zero, don't include it
                binr.ReadByte();	//skip this null byte
                modsize -=1  ;	//reduce modulus buffer size by 1
            }

            byte[] modulus = binr.ReadBytes(modsize);	//read the modulus bytes

            if(binr.ReadByte() != 0x02)			//expect an Integer for the exponent data
                return null;
            int expbytes = (int) binr.ReadByte() ;		// should only need one byte for actual exponent data (for all useful values)
            byte[] exponent = binr.ReadBytes(expbytes);


            // ------- create RSACryptoServiceProvider instance and initialize with public key -----
            RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
            RSAParameters RSAKeyInfo = new RSAParameters();
            RSAKeyInfo.Modulus = modulus;
            RSAKeyInfo.Exponent = exponent;
            RSA.ImportParameters(RSAKeyInfo);
            return RSA;
        } catch(Exception) {
            return null; 
        }

        finally { binr.Close(); }
    }

    private static bool CompareBytearrays(byte [] a, byte[] b)
    {
        if(a.Length != b.Length)
            return false;

        int i =0;
        foreach(byte c in a)
        {
            if(c != b[i] ) 
            return false;
            i++;
        }
        return true;
    }
  }
}