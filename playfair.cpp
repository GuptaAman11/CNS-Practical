#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class PlayfairCipher {
private:
    int length = 0;
    std::vector<std::vector<char>> table;

public:
    PlayfairCipher() {
        std::string key = "";

        // Prompts the user for the keyword to use for encoding & creates tables
        std::cout << "Enter the key for Playfair cipher: ";
        key = parseString();
        while (key.empty())
            key = parseString();
        table = cipherTable(key);

        int choice = 0;
        while (choice != 3) {
            std::cout << "Choose an option:" << std::endl;
            std::cout << "1. Encrypt" << std::endl;
            std::cout << "2. Decrypt" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // Consume the newline character

            switch (choice) {
                case 1: {
                    // Print the Playfair matrix
                    keyTable(table);

                    // Prompts the user for the message to be encrypted
                    std::string input;
                    std::cout << "Enter the plaintext to be encipher: ";
                    input = parseString();
                    while (input.empty())
                        input = parseString();

                    // Encrypts the input and prints the result
                    std::string encryptedMessage = cipher(input);
                    std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
                    break;
                }
                case 2: {
                    // Prompts the user for the message to be decrypted
                    std::string cipherText;
                    std::cout << "Enter the ciphertext to be decipher: ";
                    cipherText = parseString();
                    while (cipherText.empty())
                        cipherText = parseString();

                    // Decrypts the ciphertext and prints the result
                    std::string decryptedMessage = decode(cipherText);
                    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
                    break;
                }
                case 3:
                    std::cout << "Exiting the program." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
            }
        }
    }

    std::string parseString() {
        std::string parse;
        std::getline(std::cin, parse);

        std::transform(parse.begin(), parse.end(), parse.begin(), ::toupper);
        parse.erase(std::remove_if(parse.begin(), parse.end(), [](char c) {
            return !std::isalpha(c);
        }), parse.end());

        size_t pos;
        while ((pos = parse.find('J')) != std::string::npos)
            parse.replace(pos, 1, "I");

        return parse;
    }

    std::vector<std::vector<char>> cipherTable(const std::string& key) {
        std::vector<std::vector<char>> playfairTable(5, std::vector<char>(5));
        std::string keyString = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ";

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                playfairTable[i][j] = ' ';
            }
        }

        int k = 0;
        for (char c : keyString) {
            bool repeat = false;
            bool used = false;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (playfairTable[i][j] == c) {
                        repeat = true;
                    } else if (playfairTable[i][j] == ' ' && !repeat && !used) {
                        playfairTable[i][j] = c;
                        used = true;
                    }
                }
            }
        }
        return playfairTable;
    }

    std::string cipher(const std::string& in) {
        length = static_cast<int>(in.length()) / 2 + in.length() % 2;

        std::string updatedInput = in;

        for (int i = 0; i < (length - 1); i++) {
            if (updatedInput[2 * i] == updatedInput[2 * i + 1]) {
                updatedInput.insert(2 * i + 1, "X");
                length = static_cast<int>(updatedInput.length()) / 2 + updatedInput.length() % 2;
            }
        }

        std::vector<std::string> digraph(length);
        for (int j = 0; j < length; j++) {
            if (j == (length - 1) && updatedInput.length() / 2 == (length - 1))
                updatedInput += "X";
            digraph[j] = updatedInput.substr(2 * j, 2);
        }

        std::string out = "";
        std::vector<std::string> encDigraphs = encodeDigraph(digraph);
        for (int k = 0; k < length; k++)
            out += encDigraphs[k];
        return out;
    }

    std::vector<std::string> encodeDigraph(const std::vector<std::string>& di) {
        std::vector<std::string> encipher(length);
        for (int i = 0; i < length; i++) {
            char a = di[i][0];
            char b = di[i][1];
            int r1, r2, c1, c2;

            getPoint(a, r1, c1);
            getPoint(b, r2, c2);

            if (r1 == r2) {
                c1 = (c1 + 1) % 5;
                c2 = (c2 + 1) % 5;
            } else if (c1 == c2) {
                r1 = (r1 + 1) % 5;
                r2 = (r2 + 1) % 5;
            } else {
                int temp = c1;
                c1 = c2;
                c2 = temp;
            }
            encipher[i] = std::string(1, table[r1][c1]) + std::string(1, table[r2][c2]);
        }
        return encipher;
    }

    std::string decode(const std::string& out) {
        std::string decoded = "";
        for (int i = 0; i < static_cast<int>(out.length()) / 2; i++) {
            char a = out[2 * i];
            char b = out[2 * i + 1];

            if (a != 'X') {
                int r1, r2, c1, c2;

                getPoint(a, r1, c1);
                getPoint(b, r2, c2);

                if (r1 == r2) {
                    c1 = (c1 + 4) % 5;
                    c2 = (c2 + 4) % 5;
                } else if (c1 == c2) {
                    r1 = (r1 + 4) % 5;
                    r2 = (r2 + 4) % 5;
                } else {
                    int temp = c1;
                    c1 = c2;
                    c2 = temp;
                }
                decoded += std::string(1, table[r1][c1]) + std::string(1, table[r2][c2]);
            }
        }
        return decoded;
    }

    void getPoint(char c, int& r, int& col) {
        r = -1;
        col = -1;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (c == table[i][j]) {
                    r = i;
                    col = j;
                }
            }
        }
    }

    void keyTable(const std::vector<std::vector<char>>& printTable) {
        std::cout << "Playfair Cipher Key Matrix:" << std::endl << std::endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                std::cout << printTable[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main() {
    PlayfairCipher playfair;
    return 0;
}

