#include "stdafx.h"
#include "rsa.h"

namespace nbase
{
	//RSA算法填充类型,前后台要统一
	static int kRSAPaddingType = RSA_PKCS1_PADDING;
	//解密长度,前后台要统一
	static int kDecryptionLength = 128;
	//加密长度,前后台要统一
	static int kEncryptionLength = 117;

	RSA* rsa::loadPublicKey(std::string publickey){
		try
		{
			BIO *bufio;
			if (publickey.length() == 0) {
				return NULL;
			}
			bufio = BIO_new_mem_buf((void*)publickey.c_str(), (int)publickey.length());
			if (bufio == NULL)
			{
				return NULL;
			}
			RSA *rsa = PEM_read_bio_RSA_PUBKEY(bufio, NULL, NULL, NULL);
			BIO_set_close(bufio, BIO_CLOSE);
			BIO_free(bufio);
			if (rsa == NULL)
			{
				return NULL;
			}
			return rsa;
		}
		catch (...) { 
		}
		return NULL;
	}
	RSA* rsa::loadPrivateKey(std::string privatekey){
		RSA *rsa = RSA_new();
		try
		{
			BIO *bufio;
			if (privatekey.length() == 0) {
				return NULL;
			}
			bufio = BIO_new_mem_buf((void*)privatekey.c_str(), (int)privatekey.length());
			if (bufio == NULL)
			{
				return NULL;
			}
			rsa = PEM_read_bio_RSAPrivateKey(bufio, &rsa, 0, NULL);
			BIO_set_close(bufio, BIO_CLOSE);
			BIO_free(bufio);
			if (rsa == NULL)
			{
				return NULL;
			}
			return rsa;
		}
		catch (char *errorMsg) {
			RSA_free(rsa);
		}
		return NULL;
	}

	std::string rsa::decryptByPublicKey(std::string ciphertext, std::string publickey){
		std::string sumData = "";
		if (ciphertext.length() > 0 && publickey.length() > 0) {
			RSA *rsa = loadPublicKey(publickey);
			if (rsa == NULL)
			{
				return "";
			}
			int planSubLength = kDecryptionLength;
			//数据总长度
			int sumLength = (int)ciphertext.length();
			//分段数
			int blockCount = sumLength / planSubLength + ((sumLength%planSubLength) ? 1 : 0); 
			unsigned char encryptedArr[1024] = {0};
			unsigned char expressArr[1024] = {0};
			for (int i = 0; i < blockCount; i++)
			{
				//实际分段的长度,注意最后一段不够的情况
				int realSubLength = planSubLength;
				if (planSubLength > sumLength - i*planSubLength) {
					realSubLength = sumLength - i*planSubLength;
				} 
				memset(encryptedArr, 0, planSubLength + 1);
				//将待解密的data数据存放入encryptedArr数组中
				memcpy(encryptedArr, ciphertext.c_str() + i*planSubLength, realSubLength);  
				memset(expressArr, 0, realSubLength + 1);
				int length = RSA_public_decrypt(realSubLength, encryptedArr, expressArr, rsa, (int)kRSAPaddingType);
				if (length == -1)
				{ 
					RSA_free(rsa);
					return "";
				}
				sumData.append((const char *)expressArr, length);
			}
			RSA_free(rsa);
		}
		return sumData;
	}
	std::string rsa::decryptByPrivateKey(std::string ciphertext, std::string privatekey){
		return "";
	}

	std::string rsa::encryptByPublicKey(std::string plaintext, std::string publickey){
		std::string sumData = "";
		if (plaintext.length() > 0 && publickey.length() > 0) {
			RSA *rsa = loadPublicKey(publickey);
			if (rsa == NULL)
			{
				return "";
			}
			//计划分段加密长度
			int planSubLength = kEncryptionLength;
			//数据总长度
			int sumLength = (int)plaintext.length();
			//分段数
			int blockCount = sumLength / planSubLength + ((sumLength%planSubLength) ? 1 : 0);
			unsigned char expressArr[1024] = {0};
			unsigned char encryptedArr[1024] = {0};
			for (int i = 0; i < blockCount; i++)
			{
				//实际分段的长度,注意最后一段不够的情况
				int realSubLength = planSubLength;
				if (planSubLength > sumLength - i*planSubLength) {
					realSubLength = sumLength - i*planSubLength;
				}
				//定义放置待加密数据的数组, 因为要按128进行拼接, 所以长度为 128 
				memset(expressArr, 0, kDecryptionLength+1);
				//在expressArr中放入目标要加密的数据
				memcpy(expressArr, plaintext.c_str() + i*planSubLength, realSubLength);
				//定义存放加密后数据的数组,因为明文长度不得大于密文长度,所以这里的长度为计划长度(密文,较长)  
				memset(encryptedArr, 0, planSubLength+1);
				int length = RSA_public_encrypt(realSubLength, expressArr, encryptedArr, rsa, (int)kRSAPaddingType);
				if (length == -1)
				{
					delete expressArr;
					delete encryptedArr;
					RSA_free(rsa);
					return "";
				}
				sumData.append((const char *)encryptedArr, length);  
			}
			RSA_free(rsa);
		}
		return sumData;
	}
	std::string rsa::encryptByPrivateKey(std::string plaintext, std::string privatekey){
		return "";
	}
}
