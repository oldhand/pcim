#include "stdafx.h"
#include "XN_Query.h"
#include "XN_Filter.h"
#include "base/util/string_util.h"

namespace Rest
{
	XN_Query::XN_Query(std::string subject)
	{
		_subject = subject;
		_subject = subject.empty() ? "Content" : subject;
		_tag = "";
		_begin = 0;
		_end = 100;
		_datatype = 0;
		_isrollup = false;
		_orders.clear();
		_filters.clear();
		_rollups.clear();
		_groups.clear();
		_size = 0;
	}

	XN_Query* XN_Query::create(std::string subject)
	{
		return new XN_Query(subject);
	}

	XN_Query* XN_Query::begin(int value) {
		_begin = value;
		return this;
	}

	XN_Query* XN_Query::end(int value) {
		_end = value;
		return this;
	}

	XN_Query* XN_Query::tag(std::string value) {
		_tag = value;
		return this;
	}


	XN_Query* XN_Query::order(std::string field, std::string type) {
		if (!field.empty()) {
			if (type.compare("desc") == 0 ||
				type.compare("DESC") == 0 ||
				type.compare("d") == 0 ||
				type.compare("D") == 0) {
				_orders.push_back("order=" + field + "@D");
				return this;
			}
			if (type.compare("asc") == 0 ||
				type.compare("ASC") == 0 ||
				type.compare("a") == 0 ||
				type.compare("A") == 0) {
				_orders.push_back("order=" + field + "@A");
				return this;
			}
			if (type.compare("desc_number") == 0 ||
				type.compare("DESC_NUMBER") == 0 ||
				type.compare("d_n") == 0 ||
				type.compare("D_N") == 0) {
				_orders.push_back("order=" + field + "@D_N");
				return this;
			}
			if (type.compare("asc_number") == 0 ||
				type.compare("ASC_NUMBER") == 0 ||
				type.compare("a_n") == 0 ||
				type.compare("A_N") == 0) {
				_orders.push_back("order=" + field + "@A_N");
				return this;
			}
		}
		return this;
	}
	XN_Query* XN_Query::rollup() {
		_rollups.clear();
		_isrollup = true;
		return this;
	}
	XN_Query* XN_Query::rollup(std::string field) {
		if (!field.empty()) {
			_rollups.push_back("field = '" + field + "'");
			_isrollup = true;
		}
		else {
			_rollups.clear();
			_isrollup = true;
		}
		return this;
	}

	XN_Query* XN_Query::group(std::string field) {
		if (!field.empty()) {
			_groups.push_back("field = '" + field + "'");
			_isrollup = true;
		}
		return this;
	}
	XN_Query* XN_Query::filter(std::string value)
	{
		_filters.push_back(value);
		return this;
	}

	XN_Query* XN_Query::filter(std::string field, std::string oper, std::string value)
	{
		_filters.push_back(field + " " + oper + " '" + value + "'");
		return this;
	}
	XN_Query* XN_Query::filter(std::string field, std::string oper, int value)
	{
		_filters.push_back(field + " " + oper + " '" + std::to_string(value) + "'");
		return this;
	}
	XN_Query* XN_Query::filter(std::string field, std::string oper, std::list<std::string> value)
	{
		if (value.size() == 0) return this;
		_filters.push_back(field + " " + oper + " ['" + nbase::join(value, "','") + "']");
		return this;
	}
	XN_Query* XN_Query::filter(std::string field, std::string oper, std::list<int> value)
	{
		if (value.size() == 0) return this;
		_filters.push_back(field + " " + oper + " [" + nbase::join(value, ",") + "]");
		return this;
	}

	std::list<Content> XN_Query::execute(){
		std::list<Content> lists;
		try
		{
			std::string url = "";
			transform(_subject.begin(), _subject.end(), _subject.begin(), ::tolower);

			if (_subject.compare("content") == 0) {
				_datatype = 0;
				url = "/content(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("content_count") == 0) {
				_datatype = -1;
				url = "/content(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("bigcontent") == 0) {
				_datatype = 1;
				url = "/bigcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("mq") == 0) {
				_datatype = 2;
				url = "/mq(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("maincontent") == 0) {
				_datatype = 4;
				url = "/maincontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("maincontent_count") == 0) {
				_datatype = -1;
				url = "/maincontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("schedule") == 0) {
				_datatype = 5;
				url = "/schedule(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("message_count") == 0) {
				_datatype = -1;
				url = "/message(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("message") == 0) {
				_datatype = 6;
				url = "/message(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearcontent") == 0) {
				_datatype = 7;
				url = "/yearcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearcontent_count") == 0) {
				_datatype = -1;
				url = "/yearcontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("yearmonthcontent") == 0) {
				_datatype = 9;
				url = "/yearmonthcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearmonthcontent_count") == 0) {
				_datatype = -1;
				url = "/yearmonthcontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("profile") == 0) {
				_datatype = 9;
				url = "/profile(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("profile_count") == 0) {
				_datatype = -1;
				url = "/profile(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else {
				throw(std::exception("XN_Query.execute datatype parameter error"));
			}
			url += "?from=" + std::to_string(_begin) + "&to=" + std::to_string(_end);
			if (_orders.size() > 0) {
				url += "&" + nbase::join(_orders, "&");
			}
			url += "&xn_out=json";
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (_tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", _tag));
			}
#ifdef _DEBUG
			printf_s("XN_Query::execute(%s)\n", url);
#endif
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
					printf_s("XN_Query::execute(%d) : [%s]\n", size, contents.c_str());
#endif
					return lists;
				}
			}
			throw(std::exception("XN_Query::execute failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return lists;
	}


	std::list<Profile> XN_Query::executeByProfile(){
		std::list<Profile> lists;
		try
		{
			std::string url = "";
			transform(_subject.begin(), _subject.end(), _subject.begin(), ::tolower);

			if (_subject.compare("content") == 0) {
				_datatype = 0;
				url = "/content(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("content_count") == 0) {
				_datatype = -1;
				url = "/content(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("bigcontent") == 0) {
				_datatype = 1;
				url = "/bigcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("mq") == 0) {
				_datatype = 2;
				url = "/mq(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("maincontent") == 0) {
				_datatype = 4;
				url = "/maincontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("maincontent_count") == 0) {
				_datatype = -1;
				url = "/maincontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("schedule") == 0) {
				_datatype = 5;
				url = "/schedule(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("message_count") == 0) {
				_datatype = -1;
				url = "/message(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("message") == 0) {
				_datatype = 6;
				url = "/message(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearcontent") == 0) {
				_datatype = 7;
				url = "/yearcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearcontent_count") == 0) {
				_datatype = -1;
				url = "/yearcontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("yearmonthcontent") == 0) {
				_datatype = 9;
				url = "/yearmonthcontent(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("yearmonthcontent_count") == 0) {
				_datatype = -1;
				url = "/yearmonthcontent(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else if (_subject.compare("profile") == 0) {
				_datatype = 9;
				url = "/profile(" + nbase::join(_filters, "&") + ")";
			}
			else if (_subject.compare("profile_count") == 0) {
				_datatype = -1;
				url = "/profile(" + nbase::join(_filters, "&") + ")";
				if (_isrollup) {
					url += "/rollup(" + nbase::join(_rollups, "&") + ")";
					url += "/group(" + nbase::join(_groups, "&") + ")";
				}
			}
			else {
				throw(std::exception("XN_Query.execute datatype parameter error"));
			}
			url += "?from=" + std::to_string(_begin) + "&to=" + std::to_string(_end);
			if (_orders.size() > 0) {
				url += "&" + nbase::join(_orders, "&");
			}
			url += "&xn_out=json";
			std::map <std::string, std::string> headers = { { "domain", XN_Rest::application } };
			if (_tag != "")
			{
				headers.insert(std::pair<std::string, std::string>("tag", _tag));
			}
#ifdef _DEBUG
			printf_s("XN_Query::execute(%s)\n", url);
#endif
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
							Profile *profile = Profile::fromJson(entry);
							lists.push_back(*profile);
#ifdef _DEBUG
							contents.append("\n");
							contents.append(profile->toString());
#endif
						}
					}
#ifdef _DEBUG
					printf_s("XN_Query::execute(%d) : [%s]\n", size, contents.c_str());
#endif
					return lists;
				}
			}
			throw(std::exception("XN_Query::execute failed"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
		return lists;
	}
}