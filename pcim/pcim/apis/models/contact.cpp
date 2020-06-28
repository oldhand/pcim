#include "stdafx.h"
#include "contact.h"
#include "../db/sql.h"

namespace Db
{ 
	Contact::Contact()
	{
		id = ""; 
		profileid = ""; 
		contactid = "";
		remarks = "";
		colormark = "";
		source = "";
		background = "";
		hidemymoments = 0;
		hidehismoments = 0;
		block = 0;
		status = 0;
		mute = 0;
		burnafterreading = 0;
		stickyontop = 0; 
	}

	Contact::Contact(Rest::Content content) {
		id = "";
		profileid = content.my.at("profileid");
		contactid = content.my.at("contactid");
		remarks = content.my.at("remarks");
		colormark = content.my.at("colormark");
		source = content.my.at("source"); 
		if (content.my.find("background") != content.my.end()) {
			background = content.my.at("background");
		} 
		else {
			background = "";
		}
		hidemymoments = 0;
		hidehismoments = 0;
		block = 0;
		status = 0;
		mute = 0;
		burnafterreading = 0;
		stickyontop = 0;
		if (content.my.find("hidemymoments") != content.my.end()) {
			hidemymoments = std::atoi(content.my.at("hidemymoments").c_str());
		}
		if (content.my.find("hidehismoments") != content.my.end()) {
			hidehismoments = std::atoi(content.my.at("hidehismoments").c_str());
		}
		if (content.my.find("block") != content.my.end()) {
			hidemymoments = std::atoi(content.my.at("block").c_str());
		}
		if (content.my.find("status") != content.my.end()) {
			status = std::atoi(content.my.at("status").c_str());
		}
		if (content.my.find("mute") != content.my.end()) {
			mute = std::atoi(content.my.at("mute").c_str());
		}
		if (content.my.find("hidemymoments") != content.my.end()) {
			hidemymoments = std::atoi(content.my.at("hidemymoments").c_str());
		}
		if (content.my.find("burnafterreading") != content.my.end()) {
			burnafterreading = std::atoi(content.my.at("burnafterreading").c_str());
		}
		if (content.my.find("stickyontop") != content.my.end()) {
			stickyontop = std::atoi(content.my.at("stickyontop").c_str());
		} 
	}
	std::string Contact::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("profileid:\"").append(profileid.c_str()).append("\",");
		sb.append("contactid:\"").append(contactid.c_str()).append("\",");
		sb.append("remarks:\"").append(remarks.c_str()).append("\",");
		sb.append("colormark:\"").append(colormark.c_str()).append("\",");
		sb.append("source:\"").append(source.c_str()).append("\",");
		sb.append("background:\"").append(background.c_str()).append("\",");
		sb.append("hidemymoments:").append(hidemymoments).append(",");
		sb.append("hidehismoments:").append(hidehismoments).append(",");
		sb.append("block:").append(block);
		sb.append("status:").append(status).append(",");
		sb.append("mute:").append(mute).append(",");
		sb.append("burnafterreading:").append(burnafterreading).append(",");
		sb.append("stickyontop:").append(stickyontop);
		sb.append("}");
		return sb.tostring();
	}

	void Contact::saveCache() {
		const std::map <std::string, std::string> values =
		{ 
			{ "profileid", profileid },
			{ "contactid", contactid },
			{ "remarks", remarks },
			{ "colormark", colormark },
			{ "source", source },
			{ "background", background },
			{ "hidemymoments", std::to_string(hidemymoments) },
			{ "hidehismoments", std::to_string(hidehismoments) },
			{ "block", std::to_string(block) },
			{ "status", std::to_string(status) },
			{ "mute", std::to_string(mute) },
			{ "burnafterreading", std::to_string(burnafterreading) },
			{ "stickyontop", std::to_string(stickyontop) }
		};
		if (id.compare("") == 0) { 
			if (!Db::Sql::exist("contacts", "profileid = '" + profileid + "' and contactid = '" + contactid + "'")) {
				Db::Sql::insert("contacts", values);
			}
			else {
				Db::Sql::update("contacts", values, "profileid = '" + profileid + "' and contactid = '" + contactid + "'");
			}
		}
		else {
			if (!Db::Sql::exist("contacts","id = " + id)) {
				Db::Sql::insert("contacts", values);
			}
			else {
				Db::Sql::update("contacts", values, "id = " + id);
			}
		}
	}
	
}
 