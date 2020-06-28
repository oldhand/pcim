#pragma once

namespace Db
{
	class Sql
	{
	private: 
		static nbase::NLock lock;
	public:
		static void execute(std::string sql);
		static std::list<std::map<std::string, std::string>> rawexecute(std::string sql);
		static std::list<std::map<std::string, std::string>> query(std::string tablename, std::map<std::string, std::string> conditions);
		static std::list<std::map<std::string, std::string>> query(std::string tablename, std::string where);
		static void erase(std::string tablename, std::map<std::string, std::string> conditions);
		static bool exist(std::string tablename, std::map<std::string, std::string> conditions);
		static bool exist(std::string tablename, std::string conditions);
		static int count(std::string tablename, std::map<std::string, std::string> conditions);
		static void insert(std::string tablename, std::map<std::string, std::string> values);
		static void update(std::string tablename, std::map<std::string, std::string> values, std::map<std::string, std::string> conditions);
		static void update(std::string tablename, std::map<std::string, std::string> values, std::string conditions);
	};
}

