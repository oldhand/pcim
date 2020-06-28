#pragma once
 

namespace Api
{
	class GroupApi
	{
	private:


	public:
		static std::list<Rest::Content> getGroupchatProfiles(std::string supplierid, std::string profileid);
		static std::list<Rest::Content> getGroupchats(std::list<std::string> ids);

	};
}  // namespace nbase


