#pragma once
 
#include "models/profile.h"

namespace Api
{
	class ProfileApi
	{
	private:
	 

	public:
		static Rest::Profile load(std::string profileid);
		static std::list<Rest::Profile> loadMany(std::list<std::string> ids);
		static Rest::Profile get_mobile_profile_info(std::string regioncode, std::string mobile);
		static bool signin(std::string profileid, std::string password);
		static Rest::Content get_profilesetting_info(std::string profileid);
		static std::list<Db::Profile> get_ProfilesFromDb(const std::list<std::string> ids);
	};
}  // namespace nbase


