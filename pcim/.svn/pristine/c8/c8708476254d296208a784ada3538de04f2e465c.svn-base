#include "stdafx.h"
#include "groupprofile.h"
#include "../db/sql.h"

namespace Db
{ 
	GroupProfile::GroupProfile()
	{
		id = ""; 
		profileid = ""; 
		groupchatid = "";
		source = "";
		colormark = "";
		myalias = ""; 
		sequence = 0;
		mute = 0;
		block = 0; 
		stickyontop = 0;
		savetocontacts = 0;
		onscreennames = 0;  
	}

	GroupProfile::GroupProfile(Rest::Content content) {
		id = "";
		profileid = content.my.at("profileid");
		groupchatid = content.my.at("groupchatid"); 
		if (content.my.find("colormark") != content.my.end()) {
			colormark = content.my.at("colormark");
		}
		else {
			colormark = "";
		}
		if (content.my.find("source") != content.my.end()) {
			source = content.my.at("source");
		}
		else {
			source = "";
		}
		if (content.my.find("myalias") != content.my.end()) {
			myalias = content.my.at("myalias");
		} 
		else {
			myalias = "";
		}
		sequence = 0;
		mute = 0;
		block = 0;
		stickyontop = 0;
		savetocontacts = 0;
		onscreennames = 0;
		if (content.my.find("sequence") != content.my.end()) {
			mute = std::atoi(content.my.at("sequence").c_str());
		}
		if (content.my.find("mute") != content.my.end()) {
			mute = std::atoi(content.my.at("mute").c_str());
		}
		if (content.my.find("block") != content.my.end()) {
			block = std::atoi(content.my.at("block").c_str());
		}
		if (content.my.find("stickyontop") != content.my.end()) {
			stickyontop = std::atoi(content.my.at("stickyontop").c_str());
		}
		if (content.my.find("savetocontacts") != content.my.end()) {
			savetocontacts = std::atoi(content.my.at("savetocontacts").c_str());
		}
		if (content.my.find("onscreennames") != content.my.end()) {
			onscreennames = std::atoi(content.my.at("onscreennames").c_str());
		}
	}
	std::string GroupProfile::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("profileid:\"").append(profileid.c_str()).append("\",");
		sb.append("groupchatid:\"").append(groupchatid.c_str()).append("\","); 
		sb.append("colormark:\"").append(colormark.c_str()).append("\",");
		sb.append("source:\"").append(source.c_str()).append("\",");
		sb.append("myalias:\"").append(myalias.c_str()).append("\",");
		sb.append("sequence:").append(sequence).append(",");
		sb.append("mute:").append(mute).append(",");
		sb.append("block:").append(block).append(",");
		sb.append("stickyontop:").append(stickyontop);
		sb.append("savetocontacts:").append(savetocontacts).append(",");
		sb.append("onscreennames:").append(onscreennames);
		sb.append("}");
		return sb.tostring();
	}

	void GroupProfile::saveCache() {
		const std::map <std::string, std::string> values =
		{ 
			{ "profileid", profileid },
			{ "groupchatid", groupchatid }, 
			{ "colormark", colormark },
			{ "source", source },
			{ "myalias", myalias },
			{ "sequence", std::to_string(sequence) },
			{ "mute", std::to_string(mute) },
			{ "block", std::to_string(block) },
			{ "stickyontop", std::to_string(stickyontop) },
			{ "savetocontacts", std::to_string(savetocontacts) },
			{ "onscreennames", std::to_string(onscreennames) }
		};
		if (id.compare("") == 0) { 
			if (!Db::Sql::exist("groupchatprofiles", "profileid = '" + profileid + "' and groupchatid = '" + groupchatid + "'")) {
				Db::Sql::insert("groupchatprofiles", values);
			}
			else {
				Db::Sql::update("groupchatprofiles", values, "profileid = '" + profileid + "' and groupchatid = '" + groupchatid + "'");
			}
		}
		else {
			if (!Db::Sql::exist("groupchatprofiles","id = " + id)) {
				Db::Sql::insert("groupchatprofiles", values);
			}
			else {
				Db::Sql::update("groupchatprofiles", values, "id = " + id);
			}
		}
	}
	
}
 