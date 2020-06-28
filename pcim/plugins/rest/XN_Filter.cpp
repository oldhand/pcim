#include "stdafx.h"
#include "XN_Filter.h"
#include "base/util/string_util.h"

namespace Rest
{
	std::string XN_Filter::filter(std::string field, std::string oper, std::string value)
	{
		return field + " " + oper + " '" + value + "'";
	}
	std::string XN_Filter::filter(std::string field, std::string oper, int value)
	{
		return field + " " + oper + " '" + std::to_string(value) + "'";
	}
	std::string XN_Filter::filter(std::string field, std::string oper, std::list<std::string> value)
	{
		if (value.size() == 0) return "";
		return field + " " + oper + " ['" + nbase::join(value, "','") + "']";
	}
	std::string XN_Filter::filter(std::string field, std::string oper, std::list<int> value)
	{
		if (value.size() == 0) return "";
		return field + " " + oper + " [" + nbase::join(value, ",") + "]";
	}


	std::string XN_Filter::all(std::string filter, std::string filter1)
	{
		return all(filter, filter1, "", "", "", "", "");
	}
	std::string XN_Filter::all(std::string filter, std::string filter1, std::string filter2)
	{
		return all(filter, filter1, filter2, "", "", "", "");
	}
	std::string XN_Filter::all(std::string filter, std::string filter1, std::string filter2, std::string filter3)
	{
		return all(filter, filter1, filter2, filter3, "", "", "");
	}
	std::string XN_Filter::all(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4)
	{
		return all(filter, filter1, filter2, filter3, filter4, "", "");
	}
	std::string XN_Filter::all(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4, std::string filter5)
	{
		return all(filter, filter1, filter2, filter3, filter4, filter5, "");
	}

	std::string XN_Filter::all(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4, std::string filter5, std::string filter6)
	{
		StringBuilder<char> sb;
		if (!filter.empty()) {
			sb.append(" & ");
			sb.append(filter);
		}
		if (!filter1.empty()) {
			sb.append(" & ");
			sb.append(filter1);
		}
		if (!filter2.empty()) {
			sb.append(" & ");
			sb.append(filter2);
		}
		if (!filter3.empty()) {
			sb.append(" & ");
			sb.append(filter3);
		}
		if (!filter4.empty()) {
			sb.append(" & ");
			sb.append(filter4);
		}
		if (!filter5.empty()) {
			sb.append(" & ");
			sb.append(filter5);
		}
		if (!filter6.empty()) {
			sb.append(" & ");
			sb.append(filter6);
		}
		return sb.tostring();
	}



	std::string XN_Filter::any(std::string filter, std::string filter1)
	{
		return any(filter, filter1, "", "", "", "", "");
	}
	std::string XN_Filter::any(std::string filter, std::string filter1, std::string filter2)
	{
		return any(filter, filter1, filter2, "", "", "", "");
	}
	std::string XN_Filter::any(std::string filter, std::string filter1, std::string filter2, std::string filter3)
	{
		return any(filter, filter1, filter2, filter3, "", "", "");
	}
	std::string XN_Filter::any(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4)
	{
		return any(filter, filter1, filter2, filter3, filter4, "", "");
	}
	std::string XN_Filter::any(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4, std::string filter5)
	{
		return any(filter, filter1, filter2, filter3, filter4, filter5, "");
	}

	std::string XN_Filter::any(std::string filter, std::string filter1, std::string filter2, std::string filter3, std::string filter4, std::string filter5, std::string filter6)
	{
		StringBuilder<char> sb;
		if (!filter.empty()) {
			sb.append(" & ");
			sb.append(filter);
		}
		if (!filter1.empty()) {
			sb.append(" & ");
			sb.append(filter1);
		}
		if (!filter2.empty()) {
			sb.append(" & ");
			sb.append(filter2);
		}
		if (!filter3.empty()) {
			sb.append(" & ");
			sb.append(filter3);
		}
		if (!filter4.empty()) {
			sb.append(" & ");
			sb.append(filter4);
		}
		if (!filter5.empty()) {
			sb.append(" & ");
			sb.append(filter5);
		}
		if (!filter6.empty()) {
			sb.append(" & ");
			sb.append(filter6);
		}
		return sb.tostring();
	}

}