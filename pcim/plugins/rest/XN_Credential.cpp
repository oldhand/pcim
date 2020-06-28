#include "stdafx.h"
#include "XN_Credential.h"
#include "base/time/time.h"
#include "base/util/string_util.h"
#include "base/network/network_util.h"
#include "utils/md5.h"

namespace Rest
{
	Credential::Credential()
	{
		access_token = "";
		public_key = "";
		timestamp = 0;
		localtime = 0;
	}

	Credential* Credential::fromJson(std::map<std::string, std::string> json){
		Credential* newcredential = new Credential();
		return newcredential;
	}

	std::string Credential::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("access_token:\"").append(access_token.c_str()).append("\",");
		sb.append("public_key:\"").append(access_token.c_str()).append("\",");
		sb.append("timestamp:").append(std::to_string(timestamp)).append(",");
		sb.append("localtime:").append(std::to_string(localtime)).append("}");
		return sb.tostring();
	}

	Credential* XN_Credential::credential = new Credential();

	std::string XN_Credential::getPublicKey(){
		return credential->public_key;
	}
	std::map <std::string, std::string>  XN_Credential::getRestCredential(){
		std::string appid = XN_Rest::appid;
		std::string localsecret = XN_Rest::secret;
		int time_stamp = nbase::Time::timestamp();
		std::string timestamp = nbase::StringPrintf("%d", time_stamp);
		std::string mac_address;
		nbase::GetMacAddress(mac_address);
		std::string uniqueid = nbase::md5(mac_address);
		StringBuilder<char> sb;
		sb.append(appid.c_str());
		sb.append(uniqueid.c_str());
		sb.append(localsecret.c_str());
		sb.append(timestamp.c_str());
		std::string secret = nbase::md5(sb.tostring());

		std::map <std::string, std::string> result = {
			{ "uniqueid", uniqueid },
			{ "packagename", "pcim" },
			{ "appid", appid },
			{ "secret", secret },
			{ "timestamp", timestamp }
		};
		return result;
	}

	std::string XN_Credential::get()
	{
		try
		{
			if (credential->access_token == "") {
				std::map <std::string, std::string> result = getRestCredential();
				std::string appid = result.at("appid");
				std::string secret = result.at("secret");
				std::string uniqueid = result.at("uniqueid");
				std::string timestamp = result.at("timestamp");
				StringBuilder<char> url;
				url.append("/credential(appid=").append(appid)
					.append("&secret=").append(secret)
					.append("&uniqueid=").append(uniqueid)
					.append("&timestamp=").append(timestamp).append(")").append("?xn_out=json");
				std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
				std::map <std::string, std::string> response = XN_Rest::get(url.tostring(), "", headers);
				if (response.at("code").compare("200") == 0) {
					std::string cipher = response.at("cipher");
					std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, "");
					if (decryptbody.at("code").compare("200") == 0) {
						Json::Value json = decryptbody.at("message");
						Json::Value::Members members = json.getMemberNames();
						if (json["size"].isInt()) {
							int size = json["size"].asInt();
							if (size == 1) {
								const Json::Value entrys = json["entry"];
								const Json::Value entry = entrys[0];
								int crypto = atoi(entry["crypto"].asString().c_str());
								if (crypto == 1) {
									std::string  access_token = entry["id"].asString();
									std::string timestamp = entry["timestamp"].asString();
									std::string publickey = entry["publickey"].asString();
									credential->access_token = access_token;
									credential->timestamp = atoi(timestamp.c_str());
									credential->public_key = publickey;
									credential->localtime = nbase::Time::timestamp();
								}
								else {
									credential->access_token = "close";
								}
#ifdef _DEBUG
								printf_s("XN_Credential::get() : %s\n", credential->toString().c_str());
#endif
								return credential->access_token;
							}
						}
						else if (json["error"].isString()) {
							throw(std::exception(json["error"].asString().c_str()));
						}
						else {
							throw(std::exception("XN_Credential::get() failed"));
						}
					}
				}
			}
			else {
				return credential->access_token;
			}
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return "";
	}

	std::string XN_Credential::flush()
	{
		try
		{
			std::map <std::string, std::string> result = getRestCredential();
			std::string appid = result.at("appid");
			std::string secret = result.at("secret");
			std::string uniqueid = result.at("uniqueid");
			std::string timestamp = result.at("timestamp");
			StringBuilder<char> url;
			url.append("/credential(appid=").append(appid)
				.append("&secret=").append(secret)
				.append("&uniqueid=").append(uniqueid)
				.append("&timestamp=").append(timestamp).append(")").append("?xn_out=json");
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			std::map <std::string, std::string> response = XN_Rest::get(url.tostring(), "", headers);
			if (response.at("code").compare("200") == 0) {
				std::string cipher = response.at("cipher");
				std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, "");
				if (decryptbody.at("code").compare("200") == 0) {
					Json::Value json = decryptbody.at("message");
					int size = json["size"].asInt();
					if (size == 1) {
						const Json::Value entrys = json["entry"];
						const Json::Value entry = entrys[0];
						int crypto = atoi(entry["crypto"].asString().c_str());
						if (crypto == 1) {
							std::string  access_token = entry["id"].asString();
							std::string timestamp = entry["timestamp"].asString();
							std::string publickey = entry["publickey"].asString();
							credential->access_token = access_token;
							credential->timestamp = atoi(timestamp.c_str());
							credential->public_key = publickey;
							credential->localtime = nbase::Time::timestamp();
						}
						else {
							credential->access_token = "close";
						}
#ifdef _DEBUG
						printf_s("XN_Credential.get(%s)\n", credential->toString().c_str());
#endif
						return credential->access_token;
					}
				}
			}
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return "";
	}

}