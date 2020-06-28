#pragma once

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include "base/util/string_util.h"

#define LEN_OF_KEY 24

namespace nbase
{
	class tripledes
	{
		public:
			static std::string  encrypt(const std::string data, std::string  k);
			static std::string  decrypt(const std::string data, std::string k);
		
	};
}  // namespace nbase

