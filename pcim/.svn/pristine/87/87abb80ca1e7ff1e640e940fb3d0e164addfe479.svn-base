#pragma once

#include "apis/ProfileApi.h" 

namespace Db
{
	class Group
	{
	public:
		std::string id;
		std::string groupchatid;
		std::string contactids;
		std::string name;
		std::string link;
		std::string owner;
		std::string notice;
		int grouptype;
		int maxindex;
		int burnafterreading;
		int forbidde;
		int openinviadion;
		int shownotice;

		Group();
		Group(Rest::Content content);
		std::string toString();
		void saveCache(std::string profileid);
	};
}

 