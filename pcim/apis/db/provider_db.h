#pragma once

#include "base/synchronization/lock.h"
#include "base/memory/singleton.h"
#include "base/file/file_util.h"
#include "plugins/db/db_sqlite3.h"

namespace Db
{
	class ProviderDb
	{
	private:
		ndb::SQLiteDB   db;
		nbase::NLock    lock;
		std::string		db_encrypt_key;
	public:
		SINGLETON_DEFINE(ProviderDb);
		ProviderDb();
		virtual ~ProviderDb();

	private:
		bool CreateDBFile();
		std::list<std::string> getFieldsByName(std::string tablename);
	public:
		/**
		* 获取数据库对象
		* @return ndb::SQLiteDB& 数据库对象
		*/
		ndb::SQLiteDB* GetSQLiteDB();
		/**
		* 关闭数据库
		* @return void	无返回值
		*/
		void Close();
	    void initdb();
		void initindex();
		bool tableexists(std::string tablename);
	};
}

