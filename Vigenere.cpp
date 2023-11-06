#include <iostream>
#include <string>
using namespace std;

string generateKey(string str, string key) {
    int x = str.length();

    for (int i = 0;; i++) {
        if (x == i)
            i = 0;
        if (key.length() == str.length())
            break;
        key += (key[i]);
    }
    return key;
}

string cipherText(string str, string key) {
    string cipher_text = "";

    for (int i = 0; i < str.length(); i++) {
        int x = (str[i] + key[i]) % 26;
        x += 'A';
        cipher_text += static_cast<char>(x);
    }
    return cipher_text;
}

string originalText(string cipher_text, string key) {
    string orig_text = "";

    for (int i = 0; i < cipher_text.length() && i < key.length(); i++) {
        int x = (cipher_text[i] - key[i] + 26) % 26;
        x += 'A';
        orig_text += static_cast<char>(x);
    }
    return orig_text;
}

string LowerToUpper(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (islower(s[i])) {
            s[i] = toupper(s[i]);
        }
    }
    return s;
}

int main() {
    string str, keyword, key, cipher_text, original_text;

    while (true) {
        cout << "Vigenere Cipher Menu:" << endl;
        cout << "1. Encrypt a string" << endl;
        cout << "2. Decrypt a string" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a string:" << endl;
                cin.ignore(); // Consume the newline character
                getline(cin, str);
                cout << "Enter a keyword:" << endl;
                getline(cin, keyword);
                str = LowerToUpper(str);
                keyword = LowerToUpper(keyword);
                key = generateKey(str, keyword);
                cipher_text = cipherText(str, key);
                cout << "Ciphertext: " << cipher_text << endl;
                break;
            case 2:
                cout << "Enter the ciphertext:" << endl;
                cin.ignore(); // Consume the newline character
                getline(cin, cipher_text);
                cout << "Enter the keyword:" << endl;
                getline(cin, keyword);
                cipher_text = LowerToUpper(cipher_text);
                keyword = LowerToUpper(keyword);
                key = generateKey(cipher_text, keyword);
                original_text = originalText(cipher_text, key);
                cout << "Original/Decrypted Text: " << original_text << endl;
                break;
            case 3:
                cout << "Exiting the Vigenere Cipher program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
