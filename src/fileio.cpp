#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

std::string read_file(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		return "";
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

bool write_file(const std::string& filename, const std::string& content) {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		return false;
	}

	file << content;
	file.close();
	return true;
}

std::string get_key() {
	std::string key = read_file("key.txt");

	// remove whitespace/newlines
	key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

	if (!key.empty()) {
		std::cout << "Using key from key.txt" << '\n';
		return key;
	}

	std::cout << "Enter key: ";
	std::getline(std::cin, key);
	return key;
}
