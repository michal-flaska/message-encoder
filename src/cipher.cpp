#include <string>

std::string xor_cipher(const std::string& text, const std::string& key) {
	std::string result = text;

	for (size_t i = 0; i < text.length(); i++) {
		result[i] = text[i] ^ key[i % key.length()];
	}

	return result;
}
