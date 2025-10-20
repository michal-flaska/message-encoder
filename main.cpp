#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// base64 encoding table
const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// base64 encode
std::string base64_encode(const std::string& input) {
	std::string result;
	int val = 0;
	int bits = -6;

	for (unsigned char c : input) {
		val = (val << 8) + c;
		bits += 8;
		while (bits >= 0) {
			result.push_back(base64_chars[(val >> bits) & 0x3F]);
			bits -= 6;
		}
	}

	if (bits > -6) {
		result.push_back(base64_chars[((val << 8) >> (bits + 8)) & 0x3F]);
	}

	while (result.size() % 4) {
		result.push_back('=');
	}

	return result;
}

// base64 decode
std::string base64_decode(const std::string& input) {
	std::string result;
	std::vector<int> table(256, -1);

	for (int i = 0; i < 64; i++) {
		table[base64_chars[i]] = i;
	}

	int val = 0;
	int bits = -8;

	for (unsigned char c : input) {
		if (table[c] == -1) break;
		val = (val << 6) + table[c];
		bits += 6;

		if (bits >= 0) {
			result.push_back(char((val >> bits) & 0xFF));
			bits -= 8;
		}
	}

	return result;
}

// XOR cipher (works for both encode and decode)
std::string xor_cipher(const std::string& text, const std::string& key) {
	std::string result = text;

	for (size_t i = 0; i < text.length(); i++) {
		result[i] = text[i] ^ key[i % key.length()];
	}

	return result;
}

// read entire file
std::string read_file(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		return "";
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

// write to file
bool write_file(const std::string& filename, const std::string& content) {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		return false;
	}

	file << content;
	file.close();
	return true;
}

// get key from file or console
std::string get_key() {
	std::string key = read_file("key.txt");

	// remove whitespace/newlines
	key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());

	if (!key.empty()) {
		std::cout << "Using key from key.txt" << '\n';
		return key;
	}

	std::cout << "Enter key: ";
	getline(std::cin, key);
	return key;
}

int main() {
	while (true) {
		std::cout << "\n=== XOR Cipher Tool ===" << '\n';
		std::cout << "[1] Encode" << '\n';
		std::cout << "[2] Decode" << '\n';
		std::cout << "[3] Exit" << '\n';
		std::cout << "Choice: ";

		int choice;
		std::cin >> choice;
		std::cin.ignore();

		if (choice == 3) {
			std::cout << "Bye!" << '\n';
			break;
		}

		if (choice != 1 && choice != 2) {
			std::cout << "Invalid choice" << '\n';
			continue;
		}

		// read input
		std::string input = read_file("input.txt");
		if (input.empty()) {
			std::cout << "Error: input.txt is empty or doesn't exist" << '\n';
			continue;
		}

		// get key
		std::string key = get_key();
		if (key.empty()) {
			std::cout << "Error: key cannot be empty" << '\n';
			continue;
		}

		std::string output;

		if (choice == 1) {
			// encode
			std::string xored = xor_cipher(input, key);
			output = base64_encode(xored);
			std::cout << "Message encoded successfully" << '\n';
		}
		else {
			// decode
			std::string decoded_base64 = base64_decode(input);
			output = xor_cipher(decoded_base64, key);
			std::cout << "Message decoded successfully" << '\n';
		}

		// write output
		if (write_file("output.txt", output)) {
			std::cout << "Result written to output.txt" << '\n';
		}
		else {
			std::cout << "Error: couldn't write to output.txt" << '\n';
		}
	}

	return 0;
}
