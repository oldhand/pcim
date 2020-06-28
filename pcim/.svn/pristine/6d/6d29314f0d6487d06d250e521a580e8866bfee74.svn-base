#include "stdafx.h"
#include "ContactApi.h"

#include "utils/strings.h"

namespace Api
{
	std::list<Rest::Content> ContactApi::getContacts(std::string supplierid, std::string profileid){
		try
		{
			std::list<Rest::Content> lists = Rest::XN_Query::create("Content")
				->tag("im_contacts")
				->filter("type", "eic", "im_contacts")
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
	std::list<Db::Contact> ContactApi::getContactsFromDb(std::string profileid) {
		std::list<std::map<std::string, std::string>> results = Db::Sql::query("contacts", { { "profileid", profileid } });
		std::list<Db::Contact> lists;
		for (std::map<std::string, std::string> &info : results) {
			Db::Contact contact;
			contact.id = info.at("id");
			contact.profileid = profileid;
			contact.contactid = info.at("contactid");
			contact.remarks = info.at("remarks");
			contact.colormark = info.at("colormark");
			contact.source = info.at("source");
			contact.background = info.at("background");
			contact.hidemymoments = std::atoi(info.at("hidemymoments").c_str());
			contact.hidehismoments = std::atoi(info.at("hidehismoments").c_str());
			contact.block = std::atoi(info.at("block").c_str());
			contact.status = std::atoi(info.at("status").c_str());
			contact.mute = std::atoi(info.at("mute").c_str());
			contact.burnafterreading = std::atoi(info.at("burnafterreading").c_str());
			contact.stickyontop = std::atoi(info.at("stickyontop").c_str());
			lists.push_back(contact);
		}
		return lists;
	}
}
 