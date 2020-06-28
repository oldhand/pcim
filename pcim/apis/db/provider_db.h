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
		* ��ȡ���ݿ����
		* @return ndb::SQLiteDB& ���ݿ����
		*/
		ndb::SQLiteDB* GetSQLiteDB();
		/**
		* �ر����ݿ�
		* @return void	�޷���ֵ
		*/
		void Close();
	    void initdb();
		void initindex();
		bool tableexists(std::string tablename);
	};
}

