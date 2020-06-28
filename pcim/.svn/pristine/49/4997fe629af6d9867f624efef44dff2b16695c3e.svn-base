#pragma once

#include <json/json.h>  
#include "XN_Content.h"
#include "XN_Profile.h"

namespace Rest
{
	class XN_Query
	{
	private:
		std::string _subject;
		std::string _tag;
		int _begin;
		int _end;
		int _datatype;
		bool _isrollup;
		std::list<std::string> _orders;
		std::list<std::string> _filters;
		std::list<std::string> _rollups;
		std::list<std::string> _groups;
		int _size;
	public:
		int size();
		XN_Query(std::string subject);
		static XN_Query* create(std::string subject);
		XN_Query* begin(int value);
		XN_Query* end(int value);
		XN_Query* tag(std::string value);
		XN_Query* order(std::string field, std::string type);
		XN_Query* rollup(std::string field);
		XN_Query* rollup();
		XN_Query* group(std::string field);
		XN_Query* filter(std::string value);
		XN_Query* filter(std::string field, std::string oper, int value);
		XN_Query* filter(std::string field, std::string oper, std::string value);
		XN_Query* filter(std::string field, std::string oper, std::list<std::string> value);
		XN_Query* filter(std::string field, std::string oper, std::list<int> value);

		std::list<Content> execute();
		std::list<Profile> executeByProfile();
	};

}