#pragma once

#include <string>
#include <unordered_map>
#include "UserInfo.h"
#include "funciones_hash.h"

class HashSTD {
private:
	std::unordered_map<std::string, UserInfo> username_table;
	std::unordered_map<std::string, UserInfo> id_table;

public:
	void insert(const std::string& key_id, const std::string& key_username, const UserInfo& value) {
		username_table[key_username] = value;
		id_table[key_id] = value;
	}

	void remove_from_id(const std::string& key) {
		id_table.erase(key);
	}

	void remove_from_username(const std::string& key) {
		username_table.erase(key);
	}

	UserInfo get_from_id(const std::string& key) {
		return id_table[key];
	}

	UserInfo get_from_username(const std::string& key) {
		return username_table[key];
	}
	
};
