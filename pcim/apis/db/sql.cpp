#include "stdafx.h"
#include "sql.h"
#include "provider_db.h"
#include "base/synchronization/lock.h"
#include "base/memory/singleton.h"
#include "base/file/file_util.h"
#include "plugins/db/db_sqlite3.h"

namespace Db
{
	 nbase::NLock Sql::lock =  nbase::NLock();

	void Sql::execute(std::string sql) {
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		db->Query(sql.c_str());
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::execute failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
	}
	std::list<std::map<std::string, std::string>> Sql::rawexecute(std::string sql) { 
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteResultTable rt;
		db->Query( sql.c_str(), rt);
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::rawexecute failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;
		if (rt.IsEmpty()) {
			return records;
		}
		for (int row = 0; row < rt.GetRowCount();  row++) {
			std::map<std::string, std::string> record;
			for (int col = 0; col < rt.GetColumnCount(); col++) {
				std::string fieldname = rt.GetColumnName(col);
				std::string value = rt.GetValue(row, col);
				record.insert(std::pair<std::string, std::string>(fieldname, value));
			}
			records.push_back(record);
		}
		return records;
	}
	std::list<std::map<std::string, std::string>> Sql::query(std::string tablename, std::map<std::string, std::string> conditions){
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "select * from " + tablename;

		if (conditions.size() > 0) {
			sql.append (" where ");
			for (auto it = conditions.begin(); it != conditions.end(); ++it){
				std::string key = it->first;
				std::string value = it->second;
				if (it != conditions.begin()) {
					sql.append(" and ");
				}
				sql.append(key + " = '" + value + "'");
			}
		}
		sql.append(";");

		ndb::SQLiteResultTable rt;
		db->Query(sql.c_str(), rt);

		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::query not valid! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;
		if (rt.IsEmpty()) {
			return records;
		}
		for (int row = 0; row < rt.GetRowCount(); row++) {
			std::map<std::string, std::string> record;
			for (int col = 0; col < rt.GetColumnCount(); col++) {
				std::string fieldname = rt.GetColumnName(col);
				std::string value = rt.GetValue(row, col);
				record.insert(std::pair<std::string, std::string>(fieldname, value));
			}
			records.push_back(record);
		}
		return records;
	}
	std::list<std::map<std::string, std::string>> Sql::query(std::string tablename, std::string where) {
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "select * from " + tablename;

		if (sql.compare("") != 0) {
			sql.append(" where ");
			sql.append(where);
		}

		ndb::SQLiteResultTable rt;
		db->Query(sql.c_str(), rt);

		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::query not valid! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;
		if (rt.IsEmpty()) {
			return records;
		}
		for (int row = 0; row < rt.GetRowCount(); row++) {
			std::map<std::string, std::string> record;
			for (int col = 0; col < rt.GetColumnCount(); col++) {
				std::string fieldname = rt.GetColumnName(col);
				std::string value = rt.GetValue(row, col);
				record.insert(std::pair<std::string, std::string>(fieldname, value));
			}
			records.push_back(record);
		}
		return records;
	}
	void Sql::erase(std::string tablename, std::map<std::string, std::string> conditions){
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		std::string sql = "delete  from " + tablename;

		if (conditions.size() > 0) {
			sql.append(" where ");
			for (auto it = conditions.begin(); it != conditions.end(); ++it){
				std::string key = it->first;
				std::string value = it->second;
				if (it != conditions.begin()) {
					sql.append(" and ");
				}
				sql.append(key + " = '" + value + "'");
			}
		}
		sql.append(";");

		db->Query(sql.c_str());
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::erase failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
	}
	bool Sql::exist(std::string tablename, std::map<std::string, std::string> conditions){
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "select count(*) from " + tablename;

		if (conditions.size() > 0) {
			sql.append(" where ");
			for (auto it = conditions.begin(); it != conditions.end(); ++it){
				std::string key = it->first;
				std::string value = it->second;
				if (it != conditions.begin()) {
					sql.append(" and ");
				}
				sql.append(key + " = '" + value + "'");
			}
		}
		sql.append(";");

		db->Query(stmt, sql.c_str());
		if (!stmt.IsValid())
		{
			std::stringstream  errormsg;
			errormsg << "Sql::exist stmt not valid! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;

		int32_t result = stmt.NextRow();
		if  (result == SQLITE_ROW)
		{
			int count = stmt.GetIntField(0);
			if (count > 1) return true;
		}
		return false;
	}
	bool Sql::exist(std::string tablename, std::string conditions){
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "select count(*) from " + tablename + " where " + conditions + ";";

		db->Query(stmt, sql.c_str());
		if (!stmt.IsValid())
		{ 
			std::stringstream  errormsg;
			errormsg << "Sql::exist stmt not valid! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;

		int32_t result = stmt.NextRow();
		if (result == SQLITE_ROW)
		{
			int count = stmt.GetIntField(0);
			if (count > 0) return true;
		}
		return false;
	}
	int Sql::count(std::string tablename, std::map<std::string, std::string> conditions){
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "select count(*) from " + tablename;

		if (conditions.size() > 0) {
			sql.append(" where ");
			for (auto it = conditions.begin(); it != conditions.end(); ++it){
				std::string key = it->first;
				std::string value = it->second;
				if (it != conditions.begin()) {
					sql.append(" and ");
				}
				sql.append(key + " = '" + value + "'");
			}
		}
		sql.append(";");

		db->Query(stmt, sql.c_str());
		if (!stmt.IsValid())
		{
			std::stringstream  errormsg;
			errormsg << "Sql::count stmt not valid! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
		std::list<std::map<std::string, std::string>> records;

		int32_t result = stmt.NextRow();
		if (result == SQLITE_ROW)
		{
			int count = stmt.GetIntField(0);
			return count;
		}
		return 0;
	}
	void Sql::insert(std::string tablename, std::map<std::string, std::string> values){
		if (values.size() == 0) {
			throw(std::exception("sql insert values is empty"));
		}
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt; 

		std::string fields = "";
		std::string fieldvalues = "";
	
		for (auto it = values.begin(); it != values.end(); ++it){
			std::string fieldnname = it->first;
			std::string value = it->second;
			if (it != values.begin()) {
				fields.append("," + fieldnname);
				fieldvalues.append(",'" + value + "'");
			}
			else {
				fields.append(fieldnname);
				fieldvalues.append("'" + value + "'");
			} 
		} 
		std::string sql = "insert into " + tablename + "(" + fields + ") values (" + fieldvalues + ");";
		db->Query(sql.c_str());
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::insert failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
	}
	void Sql::update(std::string tablename, std::map<std::string, std::string> values, std::map<std::string, std::string> conditions){
		if (values.size() == 0) {
			throw(std::exception("sql update values is empty"));
		}
		if (conditions.size() == 0) {
			throw(std::exception("sql update conditions is empty"));
		}
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock); 
		std::string sql = "update " + tablename + " set";
		for (auto it = values.begin(); it != values.end(); ++it){
			std::string fieldnname = it->first;
			std::string value = it->second;
			if (it != values.begin()) {
				sql.append("," + fieldnname + " = '" + value + "'"); 
			}
			else {
				sql.append(" " + fieldnname + " = '" + value + "'");
			}
		} 
		if (conditions.size() > 0) {
			sql.append(" where ");
			for (auto it = conditions.begin(); it != conditions.end(); ++it){
				std::string key = it->first;
				std::string value = it->second;
				if (it != conditions.begin()) {
					sql.append(" and ");
				}
				sql.append(key + " = '" + value + "'");
			}
		}
		sql.append(";");
		db->Query(sql.c_str());
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::update failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
	}

	void Sql::update(std::string tablename, std::map<std::string, std::string> values, std::string conditions){
		if (values.size() == 0) {
			throw(std::exception("sql update values is empty"));
		}
		if (conditions.size() == 0) {
			throw(std::exception("sql update conditions is empty"));
		}
		ndb::SQLiteDB* db = Db::ProviderDb::GetInstance()->GetSQLiteDB();
		nbase::NAutoLock auto_lock(&lock);
		std::string sql = "update " + tablename + " set";
		for (auto it = values.begin(); it != values.end(); ++it){
			std::string fieldnname = it->first;
			std::string value = it->second;
			if (it != values.begin()) {
				sql.append("," + fieldnname + " = '" + value + "'");
			}
			else {
				sql.append(" " + fieldnname + " = '" + value + "'");
			}
		} 
		sql.append(" where " + conditions + ";");  
		db->Query(sql.c_str());
		if (db->GetLastErrorCode() != 0)
		{
			std::stringstream  errormsg;
			errormsg << "Sql::update failed! [" << db->GetLastErrorMessage() << "]\n";
			throw(std::exception(errormsg.str().c_str()));
		}
	}

}
