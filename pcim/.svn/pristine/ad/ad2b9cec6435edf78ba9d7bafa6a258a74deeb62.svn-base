#pragma once

#include <json/json.h>  

namespace Rest
{
	class Credential
	{
	public:
		std::string access_token;
		std::string public_key;
		int timestamp;
		int localtime;
	public:
		Credential();
		Credential* fromJson(std::map<std::string, std::string> json);
		std::string toString();
	};

	class XN_Credential
	{
	private:
		static Credential* credential;
		static std::map <std::string, std::string> getRestCredential();
	public:
		static std::string get();
		static std::string flush();
		static std::string getPublicKey();

	};
}
