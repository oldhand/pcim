// Base64 encode/decode

#ifndef BASE_MD5_H_
#define BASE_MD5_H_

#include <string>
#include "base/base_export.h"

namespace nbase
{
	/**
	*
	* @param lists 要拆分的list
	* @param size 每次拆分的大小
	* @param <T>
	* @return
	*/
	BASE_EXPORT std::list<std::list<std::string>> chunk(std::list<std::string> lists, int size);
}  // namespace nbase

#endif  // BASE_MD5_H_
