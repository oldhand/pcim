 
#include "stdafx.h"
#include "strings.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <random> 

namespace nbase
{
	void  strings::str_replace(std::string & str, const std::string & src, const std::string &dst)
	{
		std::string::size_type pos = 0;//位置
		std::string::size_type srclen = src.size();//要替换的字符串大小
		std::string::size_type dstlen = dst.size();//目标字符串大小
		while ((pos = str.find(src, pos)) != std::string::npos)
		{
			str.replace(pos, srclen, dst);
			pos += dstlen;
		}
	}
	/*
	UTF-8 转 GBK
	*/
	std::string strings::utf8_to_bbk(const std::string strUTF8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
		wchar_t* wszGBK = new wchar_t[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
		char* szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
		std::string strTemp(szGBK);

		if (wszGBK) delete[] wszGBK;
		if (szGBK) delete[] szGBK;

		return strTemp;
	}


	/*
	GBK 转 UTF-8
	*/
	std::string strings::gbk_to_utf8(const std::string strGBK)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		std::string strTemp = str;

		if (wstr) delete[] wstr;
		if (str) delete[] str;

		return strTemp;
	}

	std::string strings::WStringToString(const std::wstring& ws)
	{
		std::string strLocale = setlocale(LC_ALL, "");
		const wchar_t* wchSrc = ws.c_str();
		size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
		char *chDest = new char[nDestSize];
		memset(chDest, 0, nDestSize);
		wcstombs(chDest, wchSrc, nDestSize);
		std::string strResult = chDest;
		delete[]chDest;
		setlocale(LC_ALL, strLocale.c_str());
		return strResult;
	}

	std::wstring strings::StringToWString(const std::string &str)
	{
		std::wstring wContext = L"";
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), NULL, 0);
		WCHAR* buffer = new WCHAR[len + 1];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), buffer, len);
		buffer[len] = '\0';
		wContext.append(buffer);
		delete[] buffer;

		return wContext;
	}

	std::vector<std::string> strings::SpiteStringCharacter(std::string context)
	{
		std::vector<std::string> res;

		std::wstring wContext = StringToWString(context);
		for (int i = 0; i < wContext.length(); ++i)
		{
			std::wstring tmp = wContext.substr(i, 1);
			res.push_back(WStringToString(tmp));
		}

		return res;
	}

	bool strings::IsChineseChar(std::wstring value)
	{
		if (value.size() == 1)
		{
			unsigned char* pCh = (unsigned char*)&value[0];
			if (((*pCh >= 0) && (*pCh <= 0xff)) && (*(pCh + 1) >= 0x4e && *(pCh + 1) <= 0x9f))
			{
				return true;
			}
		}

		return false;
	}

	int strings::GetStringChineseCharCount(std::string context)
	{
		std::wstring wContext = StringToWString(context);

		int chineseCharCount = 0;
		for (int i = 0; i < wContext.length(); ++i)
		{
			if (IsChineseChar(wContext.substr(i, 1)))
			{
				++chineseCharCount;
			}
		}

		return chineseCharCount;
	}

} // namespace nbase
