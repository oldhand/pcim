#include "stdafx.h"
#include "GroupApi.h"

#include "utils/strings.h"

namespace Api
{
	std::list<Rest::Content> GroupApi::getGroupchatProfiles(std::string supplierid, std::string profileid){
		try
		{
			std::list<Rest::Content> lists = Rest::XN_Query::create("Content")
				->tag("im_groupchatprofiles")
				->filter("type", "eic", "im_groupchatprofiles")
				->filter("my.deleted", "=", "0")
				->filter("my.supplierid", "=", supplierid)
				->filter("my.profileid", "=", profileid)
				->begin(0)
				->end(-1)
				->execute();
			return lists;
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
	std::list<Rest::Content> GroupApi::getGroupchats(std::list<std::string> ids) {
		try
		{
			return Rest::XN_Content::loadMany(ids,"im_groupchats");
		}
		catch (std::exception& errorMsg) {
			throw(errorMsg);
		}
	}
}
 