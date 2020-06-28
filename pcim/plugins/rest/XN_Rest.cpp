#include "stdafx.h"
#include <algorithm>
#include "XN_Rest.h"
#include "base/util/base64.h"
#include "curl/curl.h"
#include "base/time/time.h"
#include "base/util/string_util.h"
#include "utils/md5.h"
#include "utils/rsa.h"
#include "utils/tripledes.h"
#include "utils/strings.h"

std::string Rest::XN_Rest::application = "admin";
std::string Rest::XN_Rest::viewer = "";
std::string Rest::XN_Rest::baseUrl = "http://127.0.0.1:8000";

std::string Rest::XN_Rest::appid = "";
std::string Rest::XN_Rest::secret = "";

std::string Rest::XN_Rest::publicKey = "-----BEGIN PUBLIC KEY-----\n\
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDI6dGvkKSHB6Q3TE6TKGFR4Nyt\n\
6XH3gc7/LAzvW0aDNGZjkoA7jrMTBd/T0N/R4miBK7XNMI+4Z/gd8OgS0wShPwyq\n\
Fwv8Q54goPr6dAXAQifzwK+eOs+Avu9rrVfT31i8wJeIzpk1aySoYB40ozasTdXg\n\
Q2AHZH0AqU/Rne5GuQIDAQAB\n\
-----END PUBLIC KEY-----";//默认公钥
namespace Rest {
	void XN_Rest::init(){
		curl_global_init(CURL_GLOBAL_ALL);
	}

	std::map <std::string, std::string> XN_Rest::getRestToken(std::string url, std::string public_key){
		int time_stamp = nbase::Time::timestamp();
		std::string timestamp = nbase::StringPrintf("%d", time_stamp);
		StringBuilder<char> sb;
		sb.append(url.c_str());
		sb.append(timestamp.c_str());
		std::string md5 = nbase::md5(sb.tostring());
		std::string pkey = public_key;
		if (pkey.compare("") == 0)
		{
			pkey = publicKey;
		}
		std::string ciphertext = nbase::rsa::encryptByPublicKey(md5, pkey);
		if (ciphertext.empty()) {
			throw(std::exception("encryptByPublicKey failed"));
		}
		std::string cipher;
		nbase::Base64Encode(ciphertext, &cipher);
		std::map <std::string, std::string> result = {
			{ "token", cipher },
			{ "timestamp", timestamp }
		};
		return result;
	}
	std::string XN_Rest::restEncrypt(std::string plaintext, std::string public_key){
		try
		{
			std::string gzip = "";
			std::string pkey = public_key;
			if (pkey.compare("") == 0)
			{
				pkey = publicKey;
			}
			std::string deskey = nbase::md5(pkey);
			std::string ciphertext = nbase::tripledes::encrypt(plaintext, deskey);
			if (ciphertext.empty()) {
				throw(std::exception("tripledes::encrypt failed"));
			}
			std::string cipher;
			nbase::Base64Encode(ciphertext, &cipher);
			nbase::strings::str_replace(cipher, "\n", "");
			return std::string("{\"cipher\": \"" + cipher + "\"}");
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		catch (...) {
			throw(std::exception("unknown error reason"));
		}
	}
	std::map <std::string, Json::Value> XN_Rest::restDecrypt(std::string ciphertext, std::string public_key){
		std::map <std::string, Json::Value> result;
		try
		{
			std::string rsacipher = "";
			nbase::Base64Decode(ciphertext, &rsacipher);
			std::string pkey = public_key;
			if (pkey.compare("") == 0)
			{
				pkey = publicKey;
			}
			std::string deskey = nbase::md5(pkey);
			std::string plaintext = nbase::tripledes::decrypt(rsacipher, deskey);
			if (plaintext.empty()) {
				throw(std::exception("tripledes::decrypt failed"));
			}
			printf_s("_______restDecrypt__________%s___________\n", plaintext.c_str());

			Json::Reader reader;
			Json::Value root;
			if (reader.parse(plaintext, root)) {
				result.insert(std::pair<std::string, std::string>("code", "200"));
				result.insert(std::pair<std::string, Json::Value>("message", root));
				return result;
			}
			throw(std::exception("restDecrypt failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		catch (...) {
			throw(std::exception("unknown error reason"));
		}
		return result;
	}


	std::map <std::string, std::string> XN_Rest::get(std::string url, std::string access_token, std::map <std::string, std::string> headers){
		return XN_Rest::fetch("GET", url, access_token, headers, "");
	}
	std::map <std::string, std::string> XN_Rest::put(std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody) {
		return XN_Rest::fetch("PUT", url, access_token, headers, sendbody);
	}
	std::map <std::string, std::string> XN_Rest::post(std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody) {
		return XN_Rest::fetch("POST", url, access_token, headers, sendbody);
	}
	std::map <std::string, std::string> XN_Rest::erase(std::string url, std::string access_token, std::map <std::string, std::string> headers) {
		return XN_Rest::fetch("DELETE", url, access_token, headers, "");
	}

	size_t req_reply(void *ptr, size_t size, size_t nmemb, std::string *buffer)
	{
		if (buffer == NULL || ptr == NULL || size == 0) return 0;
		size_t realsize = size * nmemb;
		if (buffer != NULL){
			buffer->append((const char *)ptr, realsize);
		}
		return realsize;
	}
	std::string XN_Rest::encryptbody(std::string access_token, std::string sendbody) {
		if (access_token.compare("") == 0 || access_token.compare("closed") == 0) {
			return sendbody;
		}
		else {
			std::string publickey = XN_Credential::getPublicKey();
			return restEncrypt(sendbody, publickey);
		}
	}



	std::map <std::string, std::string> XN_Rest::fetch(std::string method, std::string url, std::string access_token, std::map <std::string, std::string> headers, std::string sendbody) {
		std::map <std::string, std::string> result;
		try
		{
			CURL *curl;
			CURLcode res;
			std::string response = "";

			std::string body = "";
			if (method.compare("POST") == 0 || method.compare("PUT") == 0) {
				body = encryptbody(access_token, sendbody);
			}

			std::string rest_url = "/xn/rest/1.0" + url;
#ifdef _DEBUG
			printf_s("XN_Rest[%s][%s]: %s\n", method.c_str(), access_token.c_str(), rest_url.c_str());
#endif 
			std::string publickey = "";
			if (access_token.compare("") != 0) {
				publickey = XN_Credential::getPublicKey();
			}
			std::map <std::string, std::string> info = XN_Rest::getRestToken(rest_url, publickey);
			std::string token = info.at("token");
			std::string timestamp = info.at("timestamp");
			struct curl_slist *curlheaders = NULL;
			curlheaders = curl_slist_append(curlheaders, nbase::StringPrintf("token: %s", token.c_str()).c_str());
			curlheaders = curl_slist_append(curlheaders, nbase::StringPrintf("accesstoken: %s", access_token.c_str()).c_str());
			curlheaders = curl_slist_append(curlheaders, nbase::StringPrintf("timestamp: %s", timestamp.c_str()).c_str());
			curlheaders = curl_slist_append(curlheaders, "Content-Type:application/json;charset=UTF-8");
			for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
			{
				std::string header = nbase::StringPrintf("%s: %s", it->first.c_str(), it->second.c_str());
				curlheaders = curl_slist_append(curlheaders, header.c_str());
			}
			std::string base64code = "";
			nbase::Base64Encode(rest_url, &base64code);
			std::string fullurl = baseUrl + "/base64/" + base64code;
			curl = curl_easy_init();
			if (curl)
			{
				if (method.compare("POST") == 0) {
					curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
					curl_easy_setopt(curl, CURLOPT_POST, 1);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.data());
					curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
				}
				else if (method.compare("PUT") == 0) {
					curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
					curl_easy_setopt(curl, CURLOPT_POST, 1);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.data());
					curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
				}
				else if (method.compare("DELETE") == 0) {
					curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
					curl_easy_setopt(curl, CURLOPT_POST, 0);
				}
				else {
					curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
					curl_easy_setopt(curl, CURLOPT_POST, 0);
				}
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlheaders);// 改协议头
				curl_easy_setopt(curl, CURLOPT_URL, fullurl.c_str());
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
				curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
				curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5000); // 5秒 
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60000);// 1分钟
				res = curl_easy_perform(curl);   // 执行
				if (res != 0) {
					const char *errorMsg = curl_easy_strerror(res);
					printf_s("curl error: [%d] %s\n", res, errorMsg);
					curl_slist_free_all(curlheaders);
					curl_easy_cleanup(curl);
					throw(std::exception(errorMsg));
				}
				curl_slist_free_all(curlheaders);
				curl_easy_cleanup(curl);
#ifdef _DEBUG
				//printf_s("response: %s\n", response.c_str());
#endif 
				Json::Reader reader;
				Json::Value root;
				if (reader.parse(response, root)) {
					int code = root["code"].asInt();
					std::string cipher = root["cipher"].asString();
					if (code == 0) {
						result.insert(std::pair<std::string, std::string>("code", "200"));
						result.insert(std::pair<std::string, std::string>("cipher", cipher.c_str()));
						return result;
					}
					else if (code == 2) {
						std::string errorMsg = root["error"].asString();
						throw(std::exception(errorMsg.c_str()));
					}
				}
				throw(std::exception("response parsing error"));
			}
			else {
				throw(std::exception("curl init failed"));
			}
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		catch (...) {
			throw(std::exception("unknown error reason"));
		}
		return result;
	}

}