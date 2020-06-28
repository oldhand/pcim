// Copyright (c) 2011, NetEase Inc. All rights reserved.
//
// Author: rl
// Date: 2011/6/14
//
// Base64 encode/decode

#include "stdafx.h"
#include "lists.h" 
 

namespace nbase
{
	std::list<std::list<std::string>> chunk(std::list<std::string> lists, int size) {
		std::list<std::list<std::string>> result;
		if (lists.size() == 0){
			return result;
		}
		int pos = 0;
		std::list<std::string> temp;
		int count = 0;
		for (std::string  &item : lists) { 
			count++;
			if (count == lists.size()) {
				temp.push_back(item);
				result.push_back(temp); 
			}
			else {
				if (pos < size - 1) {
					temp.push_back(item);
					pos++; 
				}
				else {
					temp.push_back(item);
					result.push_back(temp);
					temp.clear();
					pos = 0;
				}
			} 
		} 
		return result;
	}
	 
}  // namespace nbase