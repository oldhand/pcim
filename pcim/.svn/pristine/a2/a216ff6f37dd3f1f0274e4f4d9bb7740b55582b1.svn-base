#pragma once

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include "base/util/string_util.h"


namespace nbase
{
	class rsa
	{
		private:
			static RSA* loadPublicKey(std::string publickey);
			static RSA* loadPrivateKey(std::string privatekey);

		public:
			static std::string decryptByPublicKey(std::string ciphertext, std::string publickey); 
			static std::string decryptByPrivateKey(std::string ciphertext, std::string privatekey);

			static std::string encryptByPublicKey(std::string plaintext, std::string publickey);
			static std::string encryptByPrivateKey(std::string plaintext, std::string privatekey);
		
	};
}  // namespace nbase

