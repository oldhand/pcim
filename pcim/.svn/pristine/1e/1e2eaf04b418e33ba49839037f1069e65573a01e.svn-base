#pragma once

#include <json/json.h>  

namespace Rest
{
	class Profile
	{
	private:
		std::string escape(std::string str);
	public:
		std::string id;
		std::string xn_type;
		std::string application;
		std::string fullname;
		std::string published;
		std::string updated;
		std::string tag;
		bool status;
		std::string mobile;
		std::string email;
		std::string givenname;
		std::string link;
		std::string type;
		std::string uuid;
		int identifier;
		std::string regioncode;
		std::string region;
		std::string country;
		std::string gender;
		std::string browser;
		std::string system;
		std::string reg_ip;
		std::string identitycard;
		std::string realname;
		std::string city;
		std::string province;
		std::string birthdate;
		std::string password;

		Profile();
		static Profile* fromJson(const Json::Value json);
		std::string toString();
		std::string toJson();
		bool save();
		bool save(std::string tag);
	};


	class XN_Profile
	{
	public:
		static Profile load(std::string profileid, std::string tag);
		static Profile load(std::string profileid);

		static std::list<Profile> loadMany(std::list<std::string> profileids, std::string tag);
		static std::list<Profile> loadMany(std::list<std::string> profileids);
		static bool signin(std::string profileid, std::string password);
	};

}