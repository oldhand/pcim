#ifndef NBASE_STRING_UTIL_H_
#define NBASE_STRING_UTIL_H_

namespace nbase
{
	class strings
	{ 
	public:
		static void str_replace(std::string & str, const std::string & src, const std::string &dst);
		static std::string utf8_to_bbk(const std::string strUTF8);
		static std::string gbk_to_utf8(const std::string strGBK);
		static std::string WStringToString(const std::wstring& ws);
		static std::wstring StringToWString(const std::string &str);
		static std::vector<std::string> SpiteStringCharacter(std::string context);
		static bool IsChineseChar(std::wstring value);
		static int GetStringChineseCharCount(std::string context);
	};
}

#endif // NBASE_STRING_UTIL_H_
