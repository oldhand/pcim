// Base64 encode/decode

#ifndef BASE_MD5_H_
#define BASE_MD5_H_

#include <string>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include "base/base_export.h"

namespace nbase
{
	BASE_EXPORT std::string md5(const std::string input);
	BASE_EXPORT std::string md5(const unsigned char *sdata, size_t ssize);
}  // namespace nbase

#endif  // BASE_MD5_H_
