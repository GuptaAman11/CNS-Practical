def generate_key(str, key):
    x = len(str)
    i = 0
    while True:
        if x == i:
            i = 0
        if len(key) == len(str):
            break
        key += key[i]
        i += 1
    return key

def cipher_text(str, key):
    cipher_text = ""
    for i in range(len(str)):
        x = (ord(str[i]) + ord(key[i])) % 26
        x += ord('A')
        cipher_text += chr(x)
    return cipher_text

def original_text(cipher_text, key):
    orig_text = ""
    for i in range(min(len(cipher_text), len(key))):
        x = (ord(cipher_text[i]) - ord(key[i]) + 26) % 26
        x += ord('A')
        orig_text += chr(x)
    return orig_text

def lower_to_upper(s):
    result = ""
    for char in s:
        if char.islower():
            result += char.upper()
        else:
            result += char
    return result

while True:
    print("Vigenere Cipher Menu:")
    print("1. Encrypt a string")
    print("2. Decrypt a string")
    print("3. Exit")
    choice = input("Enter your choice: ")

    if choice == "1":
        str = input("Enter a string:\n")
        keyword = input("Enter a keyword:\n")
        str = lower_to_upper(str)
        keyword = lower_to_upper(keyword)
        key = generate_key(str, keyword)
        cipher_text = cipher_text(str, key)
        print("Ciphertext:", cipher_text, "\n")

    elif choice == "2":
        cipher_text = input("Enter the ciphertext:\n")
        keyword = input("Enter the keyword:\n")
        cipher_text = lower_to_upper(cipher_text)
        keyword = lower_to_upper(keyword)
        key = generate_key(cipher_text, keyword)
        original_text = original_text(cipher_text, key)
        print("Original/Decrypted Text:", original_text)

    elif choice == "3":
        print("Exiting the Vigenere Cipher program.")
        break

    else:
        print("Invalid choice. Please select a valid option.")
