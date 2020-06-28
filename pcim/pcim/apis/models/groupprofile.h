#pragma once

#include "apis/ProfileApi.h" 

namespace Db
{
	class GroupProfile
	{
	public:
		std::string id;
		std::string profileid;
		std::string groupchatid;
		std::string source;
		std::string colormark;
		std::string myalias;
		int mute;
		int block;
		int sequence;
		int stickyontop;  
		int savetocontacts;
		int onscreennames; 

		GroupProfile();
		GroupProfile(Rest::Content content);
		std::string toString();
		void saveCache();
	};
}

 