#pragma once

#include "apis/ProfileApi.h" 

namespace Db
{
	class Contact
	{
	public:
		std::string id;
		std::string profileid;
		std::string contactid;
		std::string remarks;
		std::string colormark;
		std::string source;
		std::string background;
		int hidemymoments;
		int hidehismoments;
		int block;
		int status;
		int mute;
		int burnafterreading;
		int stickyontop;

		Contact();
		Contact(Rest::Content content);
		std::string toString();
		void saveCache();
	};
}

 