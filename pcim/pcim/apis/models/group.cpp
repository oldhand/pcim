#include "stdafx.h"
#include "group.h"
#include "../db/sql.h"

namespace Db
{ 
	Group::Group()
	{
		id = ""; 
		groupchatid = "";
		contactids = "";
		name = "";
		link = "";
		owner = "";
		notice = "";   
		grouptype = 0;
		maxindex = 0;
		burnafterreading = 0;
		forbidde = 0;
		openinviadion = 0; 
		shownotice = 0;
	}

	Group::Group(Rest::Content content) {
		id = "";
		groupchatid = content.id;
		contactids = content.my.at("contactids");
		name = content.my.at("name");
		link = content.my.at("link");
		owner = content.my.at("owner");
		if (content.my.find("notice") != content.my.end()) {
			notice = content.my.at("notice");
		} 
		else {
			notice = "";
		}
		grouptype = 0;
		maxindex = 0;
		burnafterreading = 0;
		forbidde = 0;
		openinviadion = 0;
		shownotice = 0;
		if (content.my.find("grouptype") != content.my.end()) {
			grouptype = std::atoi(content.my.at("grouptype").c_str());
		}
		if (content.my.find("maxindex") != content.my.end()) {
			maxindex = std::atoi(content.my.at("maxindex").c_str());
		}
		if (content.my.find("burnafterreading") != content.my.end()) {
			burnafterreading = std::atoi(content.my.at("burnafterreading").c_str());
		}
		if (content.my.find("forbidde") != content.my.end()) {
			forbidde = std::atoi(content.my.at("forbidde").c_str());
		} 
		if (content.my.find("openinviadion") != content.my.end()) {
			openinviadion = std::atoi(content.my.at("openinviadion").c_str());
		}
		if (content.my.find("shownotice") != content.my.end()) {
			shownotice = std::atoi(content.my.at("shownotice").c_str());
		}
	}
	std::string Group::toString() {
		StringBuilder<char> sb;
		sb.append("{").append("id:").append(id.c_str()).append(",");
		sb.append("groupchatid:\"").append(groupchatid.c_str()).append("\",");
		sb.append("contactids:\"").append(contactids.c_str()).append("\",");
		sb.append("name:\"").append(name.c_str()).append("\",");
		sb.append("link:\"").append(link.c_str()).append("\",");
		sb.append("owner:\"").append(owner.c_str()).append("\",");
		sb.append("notice:\"").append(notice.c_str()).append("\",");
		sb.append("grouptype:").append(grouptype).append(",");
		sb.append("maxindex:").append(maxindex).append(",");
		sb.append("burnafterreading:").append(burnafterreading).append(",");
		sb.append("forbidde:").append(forbidde).append(",");
		sb.append("openinviadion:").append(openinviadion).append(","); 
		sb.append("shownotice:").append(shownotice);
		sb.append("}");
		return sb.tostring();
	}

	void Group::saveCache(std::string profileid) {
		const std::map <std::string, std::string> values =
		{ 
			{ "profileid", profileid },
			{ "groupchatid", groupchatid },
			{ "contactids", contactids },
			{ "name", name },
			{ "link", link },
			{ "owner", owner },
			{ "notice", notice },
			{ "grouptype", std::to_string(grouptype) },
			{ "maxindex", std::to_string(maxindex) },
			{ "burnafterreading", std::to_string(burnafterreading) },
			{ "forbidde", std::to_string(forbidde) },
			{ "openinviadion", std::to_string(openinviadion) },
			{ "shownotice", std::to_string(shownotice) }
		};
		if (id.compare("") == 0) { 
			if (!Db::Sql::exist("groups", "profileid = '" + profileid + "' and groupchatid = '" + groupchatid + "'")) {
				Db::Sql::insert("groups", values);
			}
			else {
				Db::Sql::update("groups", values, "profileid = '" + profileid + "' and groupchatid = '" + groupchatid + "'");
			}
		}
		else {
			if (!Db::Sql::exist("groups","id = " + id)) {
				Db::Sql::insert("groups", values);
			}
			else {
				Db::Sql::update("groups", values, "id = " + id);
			}
		}
	}
	
}
 