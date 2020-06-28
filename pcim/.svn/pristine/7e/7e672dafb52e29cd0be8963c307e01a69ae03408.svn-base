// Copyright (c) 2011, NetEase Inc. All rights reserved.
//
// Author: rl
// Date: 2011/6/14
//
// Base64 encode/decode

#include "stdafx.h"
#include "md5.h" 
#include "base/encrypt/encrypt_impl.h"

namespace nbase
{
	std::string md5(const std::string input){
		return nbase::md5((unsigned char *)input.c_str(), input.length());
	}
	std::string md5(const unsigned char *sdata, size_t ssize)
	{
		const EVP_MD *md = EVP_md5();
		if (!md)
			return std::string("");
		EVP_MD_CTX mdctx;
		EVP_MD_CTX_init(&mdctx);
		if (!EVP_DigestInit_ex(&mdctx, md, NULL))
		{
			EVP_MD_CTX_cleanup(&mdctx);
			return std::string("");
		}
		if (!EVP_DigestUpdate(&mdctx, (const unsigned char *)sdata, ssize))
		{
			EVP_MD_CTX_cleanup(&mdctx);
			return std::string("");
		}
		unsigned char     obuf[16];
		unsigned int      olen;

		if (!EVP_DigestFinal_ex(&mdctx, obuf, &olen))
		{
			EVP_MD_CTX_cleanup(&mdctx);
			return std::string("");
		}
		char buf[33] = { 0 };

		for (int i = 0; i < 16; i++) {
			sprintf(buf + i * 2, "%02x", obuf[i]);
		}

		EVP_MD_CTX_cleanup(&mdctx);

		return std::string(buf);
	}
}  // namespace nbase