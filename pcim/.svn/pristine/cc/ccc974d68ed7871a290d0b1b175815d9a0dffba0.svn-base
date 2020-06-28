#include "stdafx.h"
#include "ProfileApi.h" 
#include "utils/strings.h"

namespace Api
{
	Rest::Profile ProfileApi::get_mobile_profile_info(std::string regioncode, std::string mobile)
	{
		try
		{
			nbase::strings::str_replace(regioncode, "+", "");
			std::list<Rest::Profile> lists = Rest::XN_Query::create("profile")
				->tag("profile")
				->filter("type", "=", "im")
				->filter("mobile", "=", mobile)
				->filter("regioncode", "=", regioncode)
				->executeByProfile();
			if (lists.size() > 0) {
				Rest::Profile profile_info = lists.front();
				return profile_info;
			} 
			throw(std::exception("no Profile"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
	Rest::Profile ProfileApi::load(std::string profileid)
	{
		try
		{
			Rest::Profile profile_info = Rest::XN_Profile::load(profileid, "profile");
			return profile_info;
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
	std::list<Rest::Profile> ProfileApi::loadMany(std::list<std::string> ids){
		try
		{
			std::list<Rest::Profile> lists = Rest::XN_Profile::loadMany(ids, "profile");
			return lists;
		}
		catch (std::exception& errorMsg) {
			//throw(errorMsg);
			std::list<Rest::Profile> lists;
			return lists;
		}
	}

	bool ProfileApi::signin(std::string profileid, std::string password)
	{
		try
		{
			return Rest::XN_Profile::signin(profileid, password);
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
	Rest::Content ProfileApi::get_profilesetting_info(std::string profileid){
		try
		{
			std::list<Rest::Content> lists = Rest::XN_Query::create("Content")
				->tag("im_profilesettings")
				->filter("type", "eic", "im_profilesettings")
				->filter("my.deleted", "=", "0")
				->filter("my.profileid", "=", profileid)
				->begin(0)
				->end(1)
				->execute();
			if (lists.size() > 0) {
				return lists.front();
			}
			throw(std::exception("no im_profilesettings"));
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
	std::list<Db::Profile> ProfileApi::get_ProfilesFromDb(const std::list<std::string> ids) {
		std::list<Db::Profile> lists; 
		if (ids.size() == 0) {
			return lists;
		}
		std::list<std::map<std::string, std::string>> results = Db::Sql::query("profiles", "profileid in ('" + nbase::join(ids,"','") + "')");
		for (std::map<std::string, std::string> &info : results) {
			Db::Profile profile;
			profile.id = info.at("id"); 
			profile.profileid = info.at("profileid");
			profile.givenname = info.at("givenname");
			profile.fullname = info.at("fullname");
			profile.mobile = info.at("mobile");
			profile.region = info.at("region");
			profile.regioncode = info.at("regioncode");
			profile.birthdate = info.at("birthdate");
			profile.gender = info.at("gender");
			profile.link = info.at("link");
			profile.province = info.at("province");
			profile.city = info.at("city");
			profile.pinyin = info.at("pinyin"); 
			lists.push_back(profile);
		}
		return lists;
	}
}

