#pragma once

#include "apis/ProfileApi.h" 

namespace Db
{
	class ProfileSetting
	{
	public:
		std::string id;
		std::string profileid;
		std::string findmobilecontacts;
		std::string sound;
		std::string vibrate;
		std::string messagepush;
		std::string language;
		std::string momentsbanner;
		std::string roamingmessage;
		std::string roamingdays; 

		ProfileSetting();
		ProfileSetting(Rest::Content content);
		std::string toString();
		void saveCache();
	};
}

 