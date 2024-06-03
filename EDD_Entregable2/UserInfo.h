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

	void print() {
		std::cout << "University: " << university << std::endl;
		std::cout << "User ID: " << user_id << std::endl;
		std::cout << "User Name: " << user_name << std::endl;
		std::cout << "Number of Tweets: " << number_tweets << std::endl;
		std::cout << "Friends Count: " << friends_count << std::endl;
		std::cout << "Followers Count: " << followers_count << std::endl;
		std::cout << "Created At: " << created_at << std::endl;
	}
};