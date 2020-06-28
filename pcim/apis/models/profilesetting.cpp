#include "stdafx.h"
#include "profilesetting.h"
#include "../db/sql.h"

namespace Db
{ 
	ProfileSetting::ProfileSetting()
	{
		id = ""; 
		profileid = ""; 
		findmobilecontacts = "";
		sound = "";
		vibrate = "";
		messagepush = "";
		language = "";
		momentsbanner = "";
		roamingmessage = "";
		roamingdays = "";  
	}

	ProfileSetting::ProfileSetting(Rest::Content content) {
		id = "";
		profileid = content.my.at("profileid");
		findmobilecontacts = content.my.at("findmobilecontacts");
		sound = content.my.at("sound");
		vibrate = content.my.at("vibrate");
		messagepush = content.my.at("messagepush");
		language = content.my.at("language");
		momentsbanner = content.my.at("momentsbanner");
		roamingmessage = content.my.at("roamingmessage");
		roamingdays = content.my.at("roamingdays");
	}
	std::string ProfileSetting::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("profileid:\"").append(profileid.c_str()).append("\",");
		sb.append("findmobilecontacts:\"").append(findmobilecontacts.c_str()).append("\",");
		sb.append("sound:\"").append(sound.c_str()).append("\",");
		sb.append("vibrate:\"").append(vibrate.c_str()).append("\",");
		sb.append("messagepush:\"").append(messagepush.c_str()).append("\",");
		sb.append("language:\"").append(language.c_str()).append("\",");
		sb.append("momentsbanner:\"").append(momentsbanner.c_str()).append("\",");
		sb.append("roamingmessage:\"").append(roamingmessage.c_str()).append("\",");
		sb.append("roamingdays:\"").append(roamingdays.c_str()).append("\"");
		sb.append("}");
		return sb.tostring();
	}

	void ProfileSetting::saveCache() {
		const std::map <std::string, std::string> values =
		{ 
			{ "profileid", profileid },
			{ "findmobilecontacts", findmobilecontacts },
			{ "sound", sound },
			{ "vibrate", vibrate },
			{ "messagepush", messagepush },
			{ "language", language },
			{ "momentsbanner", momentsbanner },
			{ "roamingmessage", roamingmessage },
			{ "roamingdays", roamingdays }
		};
		if (id.compare("") == 0) { 
			if (!Db::Sql::exist("profilesetting", "profileid = '" + profileid + "'")) {
				Db::Sql::insert("profilesetting", values);
			}
			else {
				Db::Sql::update("profilesetting", values, "profileid = '" + profileid + "'");
			}
		}
		else {
			if (!Db::Sql::exist("profilesetting","id = " + id)) {
				Db::Sql::insert("profilesetting", values);
			}
			else {
				Db::Sql::update("profilesetting", values, "id = " + id);
			}
		}
	}
	
}
 