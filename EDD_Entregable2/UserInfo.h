#pragma once

#include <string>

struct UserInfo {
	std::string university;
	std::string user_id;
	std::string user_name;
	size_t number_tweets;
	size_t friends_count;
	size_t followers_count;
	std::string created_at;
};