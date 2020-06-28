#include "stdafx.h"
#include "XN_Content.h"
#include "base/util/string_util.h"

namespace Rest
{
	Content::Content()
	{
		id = "";
		type = "";
		application = XN_Rest::application;
		title = "";
		published = "";
		updated = "";
		author = XN_Rest::viewer;
		datatype = 0;
		tag = "";
	}

	Content* Content::fromJson(const Json::Value json){
		Content* newcontent = new Content();
		newcontent->id = json["id"].asString();
		newcontent->application = json["xn_application"].asString();
		newcontent->type = json["xn_type"].asString();
		newcontent->title = json["title"].asString();
		newcontent->published = json["published"].asString();
		newcontent->updated = json["updated"].asString();
		newcontent->author = json["author"].asString();

		Json::Value::Members members = json.getMemberNames();
		for (auto iter = members.begin(); iter != members.end(); iter++) {
			std::string key = *iter;
			if (key.compare("id") != 0 && key.compare("xn_id") != 0 && key.compare("xn_application") != 0 &&
				key.compare("xn_type") != 0 && key.compare("title") != 0 && key.compare("published") != 0 &&
				key.compare("updated") != 0 && key.compare("author") != 0) {
				newcontent->my.insert(std::pair<std::string, std::string>(key, json[key].asString()));
			}
		}
		return newcontent;
	}
	std::string Content::escape(std::string str) {
		if (str.size() > 0 && str.find('"') != std::string::npos) {
			std::string output = str;
			nbase::StringReplaceAll("\"", "\\\"", output);
			return output;
		}
		return str;
	}
	std::string Content::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("application:\"").append(application.c_str()).append("\",");
		sb.append("type:\"").append(type.c_str()).append("\",");
		sb.append("title:\"").append(title.c_str()).append("\",");
		sb.append("published:\"").append(published.c_str()).append("\",");
		sb.append("updated:\"").append(updated.c_str()).append("\",");
		sb.append("author:\"").append(author.c_str()).append("\",");
		sb.append("datatype:").append(std::to_string(datatype)).append(",");
		sb.append("my:[");
		for (auto item = my.begin(); item != my.end(); item++) {
			std::string key = item->first;
			std::string value = item->second;
			if (item != my.begin()) {
				sb.append(",");
			}
			sb.append("{").append(key).append(":\"").append(value).append("\"}");
		}
		sb.append("]}");
		return sb.tostring();
	}
	std::string Content::toJson() {
		StringBuilder<char> sb;
		sb.append("{").append("\"id\":\"").append(id.c_str()).append("\",");
		sb.append("\"xn_id\":\"").append(id.c_str()).append("\",");
		sb.append("\"xn_application\":\"").append(application.c_str()).append("\",");
		sb.append("\"xn_type\":\"").append(type.c_str()).append("\",");
		sb.append("\"title\":\"").append(escape(title).c_str()).append("\",");
		sb.append("\"published\":\"").append(published.c_str()).append("\",");
		sb.append("\"updated\":\"").append(updated.c_str()).append("\",");
		sb.append("\"author\":\"").append(author.c_str()).append("\",");
		for (auto item = my.begin(); item != my.end(); item++) {
			std::string key = item->first;
			std::string value = item->second;
			if (item != my.begin()) {
				sb.append(",");
			}
			sb.append("\"").append(key).append("\":\"").append(escape(value)).append("\"");
		}
		sb.append("}");
		return sb.tostring();
	}
	bool Content::save(){
		return save("");
	}
	bool Content::save(std::string tag){
		try
		{
			std::string url = XN_Content::transdatatype(datatype);
			if (url == "") {
				throw(std::exception("XN_Content.save() datatype parameter error"));
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
			printf_s("XN_Content::save(%s) : %s\n", id.c_str(), sendbody.c_str());
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
						printf_s("XN_Content::save(%s) result : %s\n", id.c_str(), toString().c_str());
#endif
						return true;
					}
				}
			}
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return false;
	}
	bool Content::erase(std::string tag){
		try
		{
			std::string url = XN_Content::transdatatype(datatype);
			if (url.empty()) {
				throw(std::exception("XN_Content.erase() datatype parameter error"));
			}
			if (id.empty()) {
				throw(std::exception("XN_Content.erase() id parameter error"));
			}
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (!tag.empty())
			{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
			}
			url.append("(id=");
			url.append(id);
			url.append(")");
			url.append("?xn_out=json");
			std::string access_token = XN_Credential::get();
			std::map <std::string, std::string> response;
			try
			{
				response = XN_Rest::erase(url, access_token, headers);
			}
			catch (std::exception& errorMsg) {
				if (strcmp(errorMsg.what(), "AccessToken check failed") == 0) {
					access_token = XN_Credential::flush();
					try
					{
						response = XN_Rest::erase(url, access_token, headers);
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
					if (json["code"].asInt() == 0) {
						return true;
					}
					else if (json["code"].asInt() == 1) {
						std::string errormessage = json["error"].asString();
						throw(std::exception(errormessage.c_str()));
					}
					else {
						throw(std::exception("XN_Content.erase() unknown error reason"));
					}
				}
			}
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return false;
	}

	std::string XN_Content::transdatatype(int datatype){
		if (datatype == 0)
		{
			return  "/content";
		}
		else if (datatype == 1)
		{
			return "/bigcontent";
		}
		else if (datatype == 2)
		{
			return "/mq";
		}
		else if (datatype == 4)
		{
			return "/maincontent";
		}
		else if (datatype == 5)
		{
			return "/schedule";
		}
		else if (datatype == 6)
		{
			return "/message";
		}
		else if (datatype == 7)
		{
			return "/yearcontent";
		}
		else if (datatype == 9)
		{
			return "/yearmonthcontent";
		}
		return "";
	}
	Content XN_Content::create(std::string xn_type, std::string title, bool anonymous){
		return create(xn_type, title, anonymous, 0);
	}
	Content XN_Content::create(std::string xn_type, std::string title, bool anonymous, int datatype){
		if (xn_type == "") {
			throw(std::exception("XN_Content.create() xn_type cannot be empty"));
		}
		Content content;
		content.type = xn_type;
		content.title = title;
		content.application = XN_Rest::application;
		content.datatype = datatype;
		if (!anonymous) {
			content.author = XN_Rest::viewer;
		}
		return content;
	}


	Content XN_Content::load(int id, std::string tag, int datatype){
		return load(std::to_string(id), tag, datatype);
	}
	Content XN_Content::load(int id, std::string tag){
		return load(std::to_string(id), tag, 0);
	}
	Content XN_Content::load(int id){
		return load(std::to_string(id), "", 0);
	}
	Content XN_Content::load(std::string id){
		return load(id, "", 0);
	}
	Content XN_Content::load(std::string id, std::string tag){
		return load(id, tag, 0);
	}
	Content XN_Content::load(std::string id, std::string tag, int datatype){
#ifdef _DEBUG
		printf_s("XN_Content::load(id:%s,tag:%s,datatype:%d)\n", id.c_str(), tag.c_str(), datatype);
#endif
		try
		{
			if (id == "") {
				throw(std::exception("XN_Content.load record id cannot be empty"));
			}
			std::string url = transdatatype(datatype);
			if (url == "") {
				throw(std::exception("XN_Content.load datatype parameter error"));
			}
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
			}
			url.append("(id=" + id + ")");
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
						Content *content = Content::fromJson(entry);
#ifdef _DEBUG
						printf_s("XN_Content::load(%s) : %s\n", id.c_str(), content->toString().c_str());
#endif
						return *content;
					}
				}
			}
			throw(std::exception("XN_Content::load failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return Content();
	}


	std::list<Content> XN_Content::loadMany(std::list<int> ids, std::string tag, int datatype){
		return loadMany(nbase::listIntToString(ids), tag, datatype);
	}
	std::list<Content> XN_Content::loadMany(std::list<int> ids, std::string tag){
		return loadMany(nbase::listIntToString(ids), tag, 0);
	}
	std::list<Content> XN_Content::loadMany(std::list<int> ids){
		return loadMany(nbase::listIntToString(ids), "", 0);
	}
	std::list<Content> XN_Content::loadMany(std::list<std::string> ids){
		return loadMany(ids, "", 0);
	}
	std::list<Content> XN_Content::loadMany(std::list<std::string> ids, std::string tag){
		return loadMany(ids, tag, 0);
	}
	std::list<Content> XN_Content::loadMany(std::list<std::string> ids, std::string tag, int datatype){
		std::list<Content> lists;
		try
		{
			if (ids.size() == 0) {
				throw(std::exception("XN_Content.loadMany record id cannot be empty"));
			}
			std::string url = transdatatype(datatype);
			if (url == "") {
				throw(std::exception("XN_Content.loadMany datatype parameter error"));
			}
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", tag));
			}
			std::string ids_string = nbase::join(ids, ",");
#ifdef _DEBUG
			printf_s("XN_Content::loadMany(ids:[%s],tag:%s,datatype:%d)\n", ids_string.c_str(), tag.c_str(), datatype);
#endif
			url.append("(id in [" + ids_string + "])");
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
#ifdef _DEBUG
					std::string contents;
#endif
					if (size > 0) {
						const Json::Value entrys = json["entry"];
						for (int i = 0; i < (int)entrys.size(); i++){
							const Json::Value entry = entrys[i];
							Content *content = Content::fromJson(entry);
							lists.push_back(*content);
#ifdef _DEBUG
							contents.append("\n");
							contents.append(content->toString());
#endif
						}
					}
#ifdef _DEBUG
					printf_s("XN_Content::loadMany(%d) : [%s]\n", size, contents.c_str());
#endif
					return lists;
				}
			}
			throw(std::exception("XN_Content::loadMany failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return lists;
	}

}