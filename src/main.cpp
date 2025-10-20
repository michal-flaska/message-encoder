#include <iostream>
#include <string>

// function declarations
std::string xor_cipher(const std::string& text, const std::string& key);
std::string base64_encode(const std::string& input);
std::string base64_decode(const std::string& input);
std::string read_file(const std::string& filename);
bool write_file(const std::string& filename, const std::string& content);
std::string get_key();

int main() {
	while (true) {
		std::cout << "\nXOR Cipher Tool" << '\n';
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

		// Read input
		std::string input = read_file("input.txt");
		if (input.empty()) {
			std::cout << "Error: input.txt is empty or doesn't exist" << '\n';
			continue;
		}

		// Get key
		std::string key = get_key();
		if (key.empty()) {
			std::cout << "Error: key cannot be empty" << '\n';
			continue;
		}

		std::string output;

		if (choice == 1) {
			// Encode
			std::string xored = xor_cipher(input, key);
			output = base64_encode(xored);
			std::cout << "Message encoded successfully" << '\n';
		}
		else {
			// Decode
			std::string decoded_base64 = base64_decode(input);
			output = xor_cipher(decoded_base64, key);
			std::cout << "Message decoded successfully" << '\n';
		}

		// Write output
		if (write_file("output.txt", output)) {
			std::cout << "Result written to output.txt" << '\n';
		}
		else {
			std::cout << "Error: couldn't write to output.txt" << '\n';
		}
	}

	return 0;
}
