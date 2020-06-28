#pragma once
#include "json/json.h"
#include "../cpp_wrapper_util/include/nim_json_util.h"
namespace shared
{
	namespace tools 
	{
		Json::Value NimCppWrapperJsonValueToJsonValue(const nim_cpp_wrapper_util::Json::Value& param);
		nim_cpp_wrapper_util::Json::Value JsonValueToNimCppWrapperJsonValue(const Json::Value& param);
	}
}
