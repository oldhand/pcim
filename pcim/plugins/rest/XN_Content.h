#pragma once

#include <json/json.h>  
namespace Rest
{
	class Content
	{
	private:
		std::string escape(std::string str);
	public:
		std::string id;
		std::string type;
		std::string application;
		std::string title;
		std::string published;
		std::string updated;
		std::string author;
		int datatype;
		std::string tag;
		std::map <std::string, std::string> my;

		Content();
		static Content* fromJson(const Json::Value json);
		std::string toString();
		std::string toJson();
		bool save();
		bool save(std::string tag);
		bool erase(std::string tag);
	};

	class XN_Content
	{
	public:
		static std::string transdatatype(int datatype);

		static Content load(int id, std::string tag, int datatype);
		static Content load(int id, std::string tag);
		static Content load(int id);

		static Content load(std::string id, std::string tag, int datatype);
		static Content load(std::string id, std::string tag);
		static Content load(std::string id);

		static std::list<Content> loadMany(std::list<std::string> ids, std::string tag, int datatype);
		static std::list<Content> loadMany(std::list<std::string> ids, std::string tag);
		static std::list<Content> loadMany(std::list<std::string> ids);

		static std::list<Content> loadMany(std::list<int> ids, std::string tag, int datatype);
		static std::list<Content> loadMany(std::list<int> ids, std::string tag);
		static std::list<Content> loadMany(std::list<int> ids);

		static Content create(std::string xn_type, std::string title, bool anonymous, int datatype);
		static Content create(std::string xn_type, std::string title, bool anonymous);
	};

}