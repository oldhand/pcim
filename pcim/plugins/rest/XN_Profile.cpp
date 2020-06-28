#include "stdafx.h"
#include "XN_Profile.h"
#include "base/util/base64.h"
#include "base/util/string_util.h"


namespace Rest
{
	Profile::Profile()
	{
		id = "";
		xn_type = "profile";
		application = XN_Rest::application;
		fullname = "";
		published = "";
		updated = "";
		tag = "";
		status = false;
		mobile = "";
		email = "";
		givenname = "";
		link = "";
		type = "";
		uuid = "";
		identifier = 0;
		regioncode = "";
		region = "";
		country = "";
		gender = "";
		browser = "";
		system = "";
		reg_ip = "";
		identitycard = "";
		realname = "";
		city = "";
		province = "";
		birthdate = "";
		password = "";
	}

	Profile* Profile::fromJson(const Json::Value json){
		Profile* newcontent = new Profile();
		newcontent->id = json["id"].asString();
		newcontent->application = json["xn_application"].asString();
		newcontent->type = json["xn_type"].asString();
		newcontent->published = json["published"].asString();
		newcontent->updated = json["updated"].asString();

		newcontent->fullname = json["title"].asString();
		newcontent->mobile = json["mobile"].asString();
		 
		newcontent->status = json["status"].asString().compare("true") == 0 ? true : false;
		newcontent->email = json["email"].asString();
		newcontent->givenname = json["givenname"].asString();
		newcontent->link = json["link"].asString();
		newcontent->type = json["type"].asString();
		newcontent->uuid = json["uuid"].asString();
		newcontent->identifier = std::atoi(json["identifier"].asString().c_str());
		newcontent->regioncode = json["regioncode"].asString();
		newcontent->region = json["region"].asString();
		newcontent->country = json["country"].asString();
		newcontent->gender = json["gender"].asString();
		newcontent->browser = json["browser"].asString();
		newcontent->system = json["system"].asString();
		newcontent->reg_ip = json["reg_ip"].asString();
		newcontent->identitycard = json["identitycard"].asString();
		newcontent->realname = json["realname"].asString();
		newcontent->city = json["city"].asString();
		newcontent->province = json["province"].asString();
		newcontent->birthdate = json["birthdate"].asString(); 
		return newcontent;
	}
	std::string Profile::escape(std::string str) {
		if (str.size() > 0 && str.find('"') != std::string::npos) {
			std::string output = str;
			nbase::StringReplaceAll("\"", "\\\"", output);
			return output;
		}
		return str;
	}
	std::string Profile::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("application:\"").append(application.c_str()).append("\",");
		sb.append("type:\"").append(type.c_str()).append("\",");
		sb.append("published:\"").append(published.c_str()).append("\",");
		sb.append("updated:\"").append(updated.c_str()).append("\",");
		 
	 
		sb.append("}");
		return sb.tostring();
	}
	std::string Profile::toJson() {
		StringBuilder<char> sb;
		sb.append("{").append("\"id\":\"").append(id.c_str()).append("\",");
		sb.append("\"xn_id\":\"").append(id.c_str()).append("\",");
		sb.append("\"xn_application\":\"").append(application.c_str()).append("\",");
		sb.append("\"xn_type\":\"").append(type.c_str()).append("\",");
		sb.append("\"published\":\"").append(published.c_str()).append("\",");
		sb.append("\"updated\":\"").append(updated.c_str()).append("\",");
		 
		sb.append("}");
		return sb.tostring();
	}
	bool Profile::save(){
		return save("");
	}
	bool Profile::save(std::string tag){
		try
		{
			/*	std::string url = XN_Profile::transdatatype(datatype);
				if (url == "") {
				throw(std::exception("XN_Profile.save() datatype parameter error"));
				}
				std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
				if (tag != "")
				{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
				}
				url.append("?xn_out=json");
				std::string access_token = XN_Credential::get();
				std::map <std::string, std::string> response;
				std::string sendbody;
				sendbody = "{\"size\":1,\"entry\":[" + toJson() + "]}";
				#ifdef _DEBUG
				printf_s("XN_Profile::save(%s) : %s\n", id.c_str(), sendbody.c_str());
				#endif
				try
				{
				if (id == "") {
				response = XN_Rest::post(url, access_token, headers, sendbody);
				}
				else {
				response = XN_Rest::put(url, access_token, headers, sendbody);
				}
				}
				catch (std::exception& errorMsg) {
				if (strcmp(errorMsg.what(), "AccessToken check failed") == 0) {
				access_token = XN_Credential::flush();
				try
				{
				if (id == "") {
				response = XN_Rest::post(url, access_token, headers, sendbody);
				}
				else {
				response = XN_Rest::put(url, access_token, headers, sendbody);
				}
				}
				catch (std::exception& nexterrorMsg) {
				throw(nexterrorMsg);
				}
				}
				else {
				throw(errorMsg);
				}
				}
				if (response.at("code").compare("200") == 0) {
				std::string cipher = response.at("cipher");
				std::string publickey = XN_Credential::getPublicKey();
				std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, publickey);
				if (decryptbody.at("code").compare("200") == 0) {
				Json::Value json = decryptbody.at("message");
				int size = json["size"].asInt();
				if (size == 1) {
				const Json::Value entrys = json["entry"];
				const Json::Value json = entrys[0];
				id = json["id"].asString();
				application = json["xn_application"].asString();
				type = json["xn_type"].asString();
				title = json["title"].asString();
				published = json["published"].asString();
				updated = json["updated"].asString();
				author = json["author"].asString();
				my.clear();
				Json::Value::Members members = json.getMemberNames();
				for (auto iter = members.begin(); iter != members.end(); iter++) {
				std::string key = *iter;
				if (key.compare("id") != 0 && key.compare("xn_id") != 0 && key.compare("xn_application") != 0 &&
				key.compare("xn_type") != 0 && key.compare("title") != 0 && key.compare("published") != 0 &&
				key.compare("updated") != 0 && key.compare("author") != 0) {
				my.insert(std::pair<std::string, std::string>(key, json[key].asString()));
				}
				}
				#ifdef _DEBUG
				printf_s("XN_Profile::save(%s) result : %s\n", id.c_str(), toString().c_str());
				#endif
				return true;
				}
				}
				}*/
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return false;
	}





	Profile XN_Profile::load(std::string profileid){
		return load(profileid, "");
	}
	Profile XN_Profile::load(std::string profileid, std::string tag){
#ifdef _DEBUG
		printf_s("XN_Profile::load(id:%s,tag:%s)\n", profileid.c_str(), tag.c_str());
#endif
		try
		{
			if (profileid.empty()) {
				throw(std::exception("XN_Profile::load profileid cannot be empty"));
			}
			std::string url = "/profile";
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
			}
			url.append("(id='" + profileid + "')");
			url.append("?xn_out=json");
			std::string access_token = XN_Credential::get();
			std::map <std::string, std::string> response;
			try
			{
				response = XN_Rest::get(url, access_token, headers);
			}
			catch (std::exception& errorMsg) {
				if (strcmp(errorMsg.what(), "AccessToken check failed") == 0) {
					access_token = XN_Credential::flush();
					try
					{
						response = XN_Rest::get(url, access_token, headers);
					}
					catch (std::exception& nexterrorMsg) {
						throw(nexterrorMsg);
					}
				}
				else {
					throw(errorMsg);
				}
			}
			if (response.at("code").compare("200") == 0) {
				std::string cipher = response.at("cipher");
				std::string publickey = XN_Credential::getPublicKey();
				std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, publickey);
				if (decryptbody.at("code").compare("200") == 0) {
					Json::Value json = decryptbody.at("message");
					int size = json["size"].asInt();
					if (size == 1) {
						const Json::Value entrys = json["entry"];
						const Json::Value entry = entrys[0];
						Profile *profile = Profile::fromJson(entry);
#ifdef _DEBUG
						printf_s("XN_Profile::load(%s) : %s\n", profileid.c_str(), profile->toString().c_str());
#endif
						return *profile;
					}
				}
			}
			throw(std::exception("XN_Profile::load failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return Profile();
	}


	std::list<Profile> XN_Profile::loadMany(std::list<std::string> profileids){
		return loadMany(profileids, "");
	}
	std::list<Profile> XN_Profile::loadMany(std::list<std::string> profileids, std::string tag){ 
		std::list<Profile> lists;
		try
		{
			if (profileids.size() == 0) {
				throw(std::exception("XN_Profile::loadMany profileid cannot be empty"));
			}
			std::string ids_string = nbase::join(profileids, "','");
#ifdef _DEBUG
			printf_s("XN_Profile::loadMany(ids:['%s'],tag:%s)\n", ids_string.c_str(), tag.c_str());
#endif
			std::string url = "/profile";
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
			}
			url.append("(id in ['" + ids_string + "'])");
			url.append("?xn_out=json");
			std::string access_token = XN_Credential::get();
			std::map <std::string, std::string> response;
			try
			{
				response = XN_Rest::get(url, access_token, headers);
			}
			catch (std::exception& errorMsg) {
				if (strcmp(errorMsg.what(), "AccessToken check failed") == 0) {
					access_token = XN_Credential::flush();
					try
					{
						response = XN_Rest::get(url, access_token, headers);
					}
					catch (std::exception& nexterrorMsg) {
						throw(nexterrorMsg);
					}
				}
				else {
					throw(errorMsg);
				}
			}
			if (response.at("code").compare("200") == 0) {
				std::string cipher = response.at("cipher");
				std::string publickey = XN_Credential::getPublicKey();
				std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, publickey);
				if (decryptbody.at("code").compare("200") == 0) {
					Json::Value json = decryptbody.at("message");
					int size = json["size"].asInt();
					if (size > 0) {
#ifdef _DEBUG
						std::string profiles;
#endif
						const Json::Value entrys = json["entry"];
						for (int i = 0; i < (int)entrys.size(); i++){
							const Json::Value entry = entrys[i];
							Profile *profile = Profile::fromJson(entry);
							lists.push_back(*profile); 
#ifdef _DEBUG
							profiles.append("\n");
							profiles.append(profile->toString());
#endif
						}
#ifdef _DEBUG
						printf_s("XN_Profile::loadMany(%d) : [%s]\n", size, profiles.c_str());
#endif
						return lists;
					}
				}
			}
			throw(std::exception("XN_Profile::loadMany failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return lists;
	}

	bool XN_Profile::signin(std::string profileid, std::string password)
	{
#ifdef _DEBUG
		printf_s("XN_Profile::signin(profileid:%s,tag:%s)\n", profileid.c_str(), password.c_str());
#endif
		try
		{
			if (profileid.empty()) {
				throw(std::exception("XN_Profile::signin profileid cannot be empty"));
			}
			if (password.empty()) {
				throw(std::exception("XN_Profile::signin password cannot be empty"));
			}
			std::string url = "/profile";

			std::string authorization;
			nbase::Base64Encode(profileid + ":" + password, &authorization);
#ifdef _DEBUG
			printf_s("authorization => %s\n", authorization.c_str());
#endif
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application }, { "Authorization", "Basic " + authorization } };
			url.append("(id=" + profileid + ")/signin");
			url.append("?xn_out=json");
			std::string access_token = XN_Credential::get();
			std::map <std::string, std::string> response;
			try
			{
				response = XN_Rest::post(url, access_token, headers, "");
			}
			catch (std::exception& errorMsg) {
				if (strcmp(errorMsg.what(), "AccessToken check failed") == 0) {
					access_token = XN_Credential::flush();
					try
					{
						response = XN_Rest::post(url, access_token, headers, "");
					}
					catch (std::exception& nexterrorMsg) {
						throw(nexterrorMsg);
					}
				}
				else {
					throw(errorMsg);
				}
			}
			if (response.at("code").compare("200") == 0) {
				std::string cipher = response.at("cipher");
				std::string publickey = XN_Credential::getPublicKey();
				std::map <std::string, Json::Value> decryptbody = XN_Rest::restDecrypt(cipher, publickey);
				if (decryptbody.at("code").compare("200") == 0) {
					Json::Value json = decryptbody.at("message");
					std::string code = json["code"].asString();
#ifdef _DEBUG
					printf_s("XN_Profile::signin, code => %s\n", code.c_str());
#endif
					if (code.compare("0") == 0) {
						return true;
					}
				}
			}
			return false;
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
}