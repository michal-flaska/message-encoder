#include <string>
#include <vector>

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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
