#pragma once
 

namespace Api
{
	class ContactApi
	{
	private:


	public:
		static std::list<Rest::Content> getContacts(std::string supplierid, std::string profileid);
		static std::list<Db::Contact> getContactsFromDb(std::string profileid);

	};
}  // namespace nbase


