#include "stdafx.h"
#include "tripledes.h"
#include <time.h>
#include <random>
#include <iostream>
#include <openssl/des.h>

namespace nbase
{
	std::string tripledes::encrypt(const std::string data, std::string  k)
	{
		int data_len;
		int data_rest;
		unsigned char *src = NULL; /* 补齐后的明文 */
		unsigned char *dst = NULL; /* 解密后的明文 */
		int len;
		unsigned char tmp[8];
		unsigned char in[8];
		unsigned char out[8];
		int key_len;
		int count;
		int i;
		unsigned char block_key[9];
		unsigned char keybuff[30] = { 0 };
		DES_key_schedule ks, ks2, ks3;

		key_len = (int)k.size();
		if (key_len > LEN_OF_KEY) {
			strncpy((char *)keybuff, k.c_str(), LEN_OF_KEY);
		}
		else {
			strcpy((char *)keybuff, k.c_str());
			for (int i = 0; i < LEN_OF_KEY - key_len; i++) {
				strcat((char *)keybuff, "0");
			}
		}
		data_len = (int)data.size();//原始数据长度
		data_rest = data_len % 8;
		len = data_len + (8 - data_rest);
		src = (unsigned char *)malloc(len+9);
		dst = (unsigned char *)malloc(len+9);
		memset(dst, 0, len+9);

		/* 构造补齐后的加密内容 */
		memset(src, 0, len);
		memcpy(src, data.c_str(), data_len);
		memset(src + data_len, 0, 8 - data_rest);

		/* 密钥置换 */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, keybuff + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, keybuff + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, keybuff + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);
		/* 循环加密/解密，每8字节一次 */
		count = len / 8;
		for (i = 0; i < count; i++)
		{
			memset(tmp, 0, 8);
			memset(in, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* 加密 */
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)in, &ks, &ks2, &ks3, DES_ENCRYPT);
			memcpy(dst + 8 * i, in, 8);
		}
		free(src);
		//存放加密后的数据
		std::string result = std::string((char *)dst, len);
		free(dst);
		return result;
	}

	std::string tripledes::decrypt(const std::string data, std::string k)
	{
		int data_len;
		int data_rest;
		unsigned char *src = NULL; /* 补齐后的明文 */
		unsigned char *dst = NULL; /* 解密后的明文 */
		int len;
		unsigned char tmp[8];
		unsigned char out[8];
		int key_len;
		int count;
		int i;
		unsigned char block_key[9];
		unsigned char keybuff[30] = { 0 };
		DES_key_schedule ks, ks2, ks3;

		key_len = (int)k.size();
		if (key_len > LEN_OF_KEY) {
			strncpy((char *)keybuff, k.c_str(), LEN_OF_KEY);
		}
		else {
			strcpy((char *)keybuff, k.c_str());
			for (int i = 0; i < LEN_OF_KEY - key_len; i++) {
				strcat((char *)keybuff, "0");
			}
		}
		data_len = (int)data.size();//原始数据长度
		data_rest = data_len % 8;
		if (data_rest != 0) {
			len = data_len + (8 - data_rest);
		}
		else {
			len = data_len;
		}
		src = (unsigned char *)malloc(len + 9);
		dst = (unsigned char *)malloc(len + 9);
		memset(dst, 0, len + 9);


		/* 构造补齐后的加密内容 */
		memset(src, 0, len + 1);
		memcpy(src, data.c_str(), data_len);
		memset(src + data_len, 0, 8 - data_rest);

		/* 密钥置换 */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, keybuff + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, keybuff + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, keybuff + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);
		/* 循环加密/解密，每8字节一次 */
		count = len / 8;
		for (i = 0; i < count; i++)
		{
			memset(tmp, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* 解密 */
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)out, &ks, &ks2, &ks3, DES_DECRYPT);
			/* 将解密的内容拷贝到解密后的明文 */
			memcpy((dst + 8 * i), out, 8);
		}
		free(src);
		//存放解密后的数据
		for (i = 0; i < len; i++)
		{
			if (*(dst + i) == 0) {
				len = i;
				break;
			}
		}
		*(dst + len + 1) = 0;
		std::string result = std::string((char *)dst, len);
		free(dst);
		return result;
	}

}
