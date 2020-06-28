#pragma once

#include "apis/ProfileApi.h" 

namespace Db
{
	class Profile
	{
	public:
		std::string id;
		std::string profileid;
		std::string givenname;
		std::string fullname;
		std::string mobile;
		std::string region;
		std::string regioncode;
		std::string birthdate;
		std::string gender;
		std::string link;
		std::string province;
		std::string city;
		std::string pinyin;
		int timestamp;

		Profile();
		Profile(Rest::Profile profile);
		std::string toString();
		void saveCache();
	};
}

 