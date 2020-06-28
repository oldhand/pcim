#pragma once

#include <json/json.h>  

namespace Rest
{
	class XN_Rest
	{
	private:
		static std::string publicKey;
		static std::string encryptbody(std::string access_token, std::string sendbody);
		static std::map <std::string, std::string> getRestToken(std::string url, std::string public_key);
		static std::map <std::string, std::string> fetch(std::string method, std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody);
	public:
		static std::string application;
		static std::string viewer;
		static std::string baseUrl;
		static std::string appid;
		static std::string secret;
		static void init();
		static std::map <std::string, Json::Value> restDecrypt(std::string ciphertext, std::string public_key);
		static std::string restEncrypt(std::string plaintext, std::string public_key);
		static std::map <std::string, std::string> get(std::string url, std::string access_token, std::map <std::string, std::string> headers);
		static std::map <std::string, std::string> put(std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody);
		static std::map <std::string, std::string> post(std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody);
		static std::map <std::string, std::string> erase(std::string url, std::string access_token, std::map <std::string, std::string> headers);
	};

}