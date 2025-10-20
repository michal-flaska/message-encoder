# XOR Cipher Tool

Simple command-line tool for encoding and decoding messages using XOR cipher with Base64 encoding.

## Features

- Encodes/decodes any text with XOR cipher
- Supports all characters (Unicode, emojis, special chars)
- Base64 output for safe storage and transmission
- Key can be stored in file or entered manually
- Binary-safe file I/O

## Setup

### Visual Studio 2022
1. Clone this repository
2. Build the project in release mode
3. Start the .exe file

## Usage

### Encoding
1. Put your message in `input.txt`
2. (Optional) Put your key in `key.txt`, or leave empty to type it
3. Run program, select `[1] Encode`
4. Encoded message appears in `output.txt`

### Decoding
1. Put Base64 encoded text in `input.txt`
2. Use the same key from encoding
3. Run program, select `[2] Decode`
4. Original message appears in `output.txt`

## How It Works

1. **XOR Cipher** - Message is XORed with the key (byte by byte, key repeats if shorter)
2. **Base64 Encoding** - Result is converted to Base64 for safe text representation
3. **Binary I/O** - Files are read/written in binary mode to preserve all characters

## Security Note

XOR cipher is NOT secure for real-world encryption. This is a learning project. For actual security, use established libraries like OpenSSL.
