#include "stdafx.h"
#include "profile.h"
#include "../db/sql.h"

namespace Db
{ 
	Profile::Profile()
	{
		id = ""; 
		profileid = "";
		givenname = ""; 
		fullname = ""; 
		mobile = ""; 
		region = ""; 
		regioncode = ""; 
		birthdate = ""; 
		gender = ""; 
		link = ""; 
		province = ""; 
		city = ""; 
		pinyin = ""; 
		timestamp = 0;
	}

	Profile::Profile(Rest::Profile profile) {
		id = "";
		profileid = profile.id;
		givenname = profile.givenname;
		fullname = profile.fullname;
		mobile = profile.mobile;
		region = profile.region;
		regioncode = profile.regioncode;
		birthdate = profile.birthdate;
		gender = profile.gender;
		link = profile.link;
		province = profile.province;
		city = profile.city;
		pinyin = "";
		timestamp = 0;
	}
	std::string Profile::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("profileid:\"").append(profileid.c_str()).append("\",");
		sb.append("givenname:\"").append(givenname.c_str()).append("\",");
		sb.append("fullname:\"").append(fullname.c_str()).append("\",");
		sb.append("mobile:\"").append(mobile.c_str()).append("\",");
		sb.append("region:\"").append(region.c_str()).append("\",");
		sb.append("regioncode:\"").append(regioncode.c_str()).append("\",");
		sb.append("birthdate:\"").append(birthdate.c_str()).append("\",");
		sb.append("gender:\"").append(gender.c_str()).append("\",");
		sb.append("link:\"").append(link.c_str()).append("\",");
		sb.append("province:\"").append(province.c_str()).append("\",");
		sb.append("city:\"").append(city.c_str()).append("\",");
		sb.append("pinyin:\"").append(pinyin.c_str()).append("\",");
		sb.append("timestamp:").append(std::to_string(timestamp)); 
		sb.append("}");
		return sb.tostring();
	}

	void Profile::saveCache() {
		const std::map <std::string, std::string> values =
		{ 
			{ "profileid", profileid },
			{ "givenname", givenname },
			{ "fullname", fullname },
			{ "mobile", mobile },
			{ "region", region },
			{ "regioncode", regioncode },
			{ "birthdate", birthdate },
			{ "gender", gender },
			{ "link", link },
			{ "province", province },
			{ "city", city },
			{ "pinyin", pinyin },
			{ "timestamp", std::to_string(timestamp) }
		};
		if (id.compare("") == 0) { 
			if (!Db::Sql::exist("profiles", "profileid = '" + profileid + "'")) {
				Db::Sql::insert("profiles", values);
			}
			else {
				Db::Sql::update("profiles", values, "profileid = '" + profileid + "'");
			}
		}
		else {
			if (!Db::Sql::exist("profiles","id = " + id)) {
				Db::Sql::insert("profiles", values);
			}
			else {
				Db::Sql::update("profiles", values, "id = " + id);
			}
		}
	}
	
}
 