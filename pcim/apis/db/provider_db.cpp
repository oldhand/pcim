#include "stdafx.h"
#include "provider_db.h"

namespace Db
{ 
	#define APP_DB_FILE		"app.db"
	static const std::map <std::string, std::list<std::map<std::string, std::string>>> _tables =
	{
		{ "chats", { 
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "msgid" }, { "type", "text" } },
				{ { "name", "msgtype" }, { "type", "integer" } },
				{ { "name", "msgbar" }, { "type", "integer" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "contactid" }, { "type", "text" } },
				{ { "name", "profileid_from" }, { "type", "text" } },
				{ { "name", "profileid_to" }, { "type", "text" } },
				{ { "name", "sendtime" }, { "type", "integer" } },
				{ { "name", "receivetime" }, { "type", "integer" } },
				{ { "name", "status" }, { "type", "integer" } },
				{ { "name", "block" }, { "type", "integer" } },
				{ { "name", "deleted" }, { "type", "integer" } },
				{ { "name", "body" }, { "type", "text" } }
			}
		},
		{ "profiles", {
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "givenname" }, { "type", "text" } },
				{ { "name", "fullname" }, { "type", "text" } },
				{ { "name", "mobile" }, { "type", "text" } },
				{ { "name", "region" }, { "type", "text" } },
				{ { "name", "regioncode" }, { "type", "text" } },
				{ { "name", "birthdate" }, { "type", "text" } },
				{ { "name", "gender" }, { "type", "text" } },
				{ { "name", "link" }, { "type", "text" } },
				{ { "name", "province" }, { "type", "text" } },
				{ { "name", "city" }, { "type", "text" } },
				{ { "name", "pinyin" }, { "type", "text" } },
				{ { "name", "timestamp" }, { "type", "integer" } }
			}
		},
		{ "profilesetting", {
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "findmobilecontacts" }, { "type", "text" } },
				{ { "name", "sound" }, { "type", "text" } },
				{ { "name", "vibrate" }, { "type", "text" } },
				{ { "name", "messagepush" }, { "type", "text" } },
				{ { "name", "language" }, { "type", "text" } },
				{ { "name", "momentsbanner" }, { "type", "text" } },
				{ { "name", "roamingmessage" }, { "type", "text" } },
				{ { "name", "roamingdays" }, { "type", "text" } } 
			}
		},
		{ "contacts", {
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "contactid" }, { "type", "text" } },
				{ { "name", "remarks" }, { "type", "text" } },
				{ { "name", "colormark" }, { "type", "text" } },
				{ { "name", "source" }, { "type", "text" } },
				{ { "name", "background" }, { "type", "text" } },
				{ { "name", "hidemymoments" }, { "type", "integer" } },
				{ { "name", "hidehismoments" }, { "type", "integer" } },
				{ { "name", "stickyontop" }, { "type", "integer" } },
				{ { "name", "block" }, { "type", "integer" } },
				{ { "name", "mute" }, { "type", "integer" } },
				{ { "name", "burnafterreading" }, { "type", "integer" } },
				{ { "name", "status" }, { "type", "integer" } }
			}
		},
		{ "groupchatprofiles", {
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "groupchatid" }, { "type", "text" } },
				{ { "name", "source" }, { "type", "text" } },
				{ { "name", "colormark" }, { "type", "text" } },
				{ { "name", "myalias" }, { "type", "text" } }, 
				{ { "name", "mute" }, { "type", "text" } },
				{ { "name", "block" }, { "type", "integer" } },
				{ { "name", "sequence" }, { "type", "integer" } },
				{ { "name", "stickyontop" }, { "type", "integer" } },
				{ { "name", "savetocontacts" }, { "type", "integer" } },
				{ { "name", "onscreennames" }, { "type", "integer" } }
			}
		},
		{ "groups", {
				{ { "name", "id" }, { "autoincrement", "1" } },
				{ { "name", "profileid" }, { "type", "text" } },
				{ { "name", "groupchatid" }, { "type", "text" } },
				{ { "name", "contactids" }, { "type", "text" } },
				{ { "name", "name" }, { "type", "text" } },
				{ { "name", "link" }, { "type", "text" } },
				{ { "name", "owner" }, { "type", "text" } },
				{ { "name", "notice" }, { "type", "text" } },
				{ { "name", "grouptype" }, { "type", "integer" } },
				{ { "name", "maxindex" }, { "type", "integer" } },
				{ { "name", "burnafterreading" }, { "type", "integer" } },
				{ { "name", "forbidde" }, { "type", "integer" } },
				{ { "name", "openinviadion" }, { "type", "integer" } },
				{ { "name", "shownotice" }, { "type", "integer" } }
			}
		},


	};
	static std::list<std::map<std::string, std::string>> _indexs = {
		{ { "name", "im_chats_profileid_contactid_deleted" }, { "tablename", "chats" }, { "isunique", "false" }, { "fields", "profileid,contactid,deleted" } } 
	};


	ProviderDb::ProviderDb()
	{
		db_encrypt_key = "1234560247a0619f07548fb1b8abcedf";//注意：只支持最多32个字符的加密密钥！
		this->CreateDBFile();
	}
	ProviderDb::~ProviderDb()
	{
		this->Close();
	}
	ndb::SQLiteDB* ProviderDb::GetSQLiteDB()
	{
		if (!db.IsValid())
		{
			throw(std::exception("db not valid"));
		}
		return &db;
	}
	void ProviderDb::Close()
	{
		db.Close();
	}  
	void ProviderDb::initdb(){
		for (auto it = _tables.begin(); it != _tables.end(); ++it){
			std::string tablename = it->first;
			std::list<std::map<std::string, std::string>> fields = it->second;
			if (tableexists(tablename)) {
				std::list<std::string> hasfields = getFieldsByName(tablename);
				for (std::map<std::string, std::string> &field : fields) {
					std::string fieldname = field.at("name");
					std::list<std::string>::iterator iter = std::find(hasfields.begin(), hasfields.end(), fieldname);
					if (iter == hasfields.end())
					{
						std::string type = field.at("type");
						std::string sql = "alter table " + tablename + " add column " + fieldname + " " + type + ";";
						db.Query(sql.c_str());
					}
				}
			}
			else {
				std::string sql = "create table ";
				sql.append(tablename);
				sql.append(" (");
				bool isFirst = true;
				for (std::map<std::string, std::string> &field : fields) {
					std::string fieldname = field.at("name");
					if (field.find("autoincrement") != field.end() && field.at("autoincrement").compare("1") == 0) { 
						if (isFirst) {
							sql.append(fieldname + " integer primary key not null unique");
							isFirst = false;
						}
						else {
							sql.append("," + fieldname + " integer primary key not null unique");
						}
					}
					else {
						std::string type = field.at("type");
						if (isFirst) {
							sql.append(fieldname + " " + type);
							isFirst = false;
						}
						else {
							sql.append("," + fieldname + " " + type);
						}
					} 
				}
				sql.append(");");
				db.Query(sql.c_str());
			}
		}
	}
	void ProviderDb::initindex(){
		for (std::map<std::string, std::string> &info : _indexs) {
			std::string tablename = info.at("tablename");
			std::string name = info.at("name");
			std::string isunique = info.at("isunique");
			std::string fields = info.at("fields");
			if (!db.DoesIndexExist(name.c_str())) {
				if (isunique.compare("true") == 0) {
					std::string sql = "create unique index " + name + " on " + tablename + " (" + fields + ");";
					db.Query(sql.c_str());
				}
				else {
					std::string sql = "create index " + name + " on " + tablename + " (" + fields + ");";
					db.Query(sql.c_str());
				}
			}
		}
	}
	bool ProviderDb::tableexists(std::string tablename){
		if (!db.IsValid())
		{
			throw(std::exception("db not valid"));
		}
		return db.DoesTableExist(tablename.c_str());
	}
	std::list<std::string> ProviderDb::getFieldsByName(std::string tablename) {
		if (!db.IsValid())
		{
			throw(std::exception("db not valid"));
		}
		nbase::NAutoLock auto_lock(&lock);
		ndb::SQLiteStatement stmt;
		std::string sql = "PRAGMA  table_info([" + tablename + "]);";
		db.Query(stmt, sql.c_str());
		if (!stmt.IsValid())
		{
			throw(std::exception("stmt not valid"));
		} 
		int32_t result = stmt.NextRow();
		std::list<std::string> fields;
		while (result == SQLITE_ROW)
		{
			std::string fieldname = stmt.GetTextField(1);
			fields.push_back(fieldname);
			result = stmt.NextRow();
		}
		return fields;
	}
	bool ProviderDb::CreateDBFile()
	{
		if (db.IsValid())
			return true;
		bool result = false;
		std::wstring appdir = QPath::GetNimAppDataDir(L"");
		if (false == nbase::FilePathIsExist(appdir, true)) {
			nbase::CreateDirectory(appdir.c_str());
		}
		UTF8String dirctory = nbase::UTF16ToUTF8(appdir);
		UTF8String dbfile = dirctory + APP_DB_FILE;
		result = db.Open(dbfile.c_str(),db_encrypt_key,ndb::SQLiteDB::modeReadWrite | ndb::SQLiteDB::modeCreate | ndb::SQLiteDB::modeSerialized); 
		return result;
	}
}