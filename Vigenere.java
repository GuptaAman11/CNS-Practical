import java.util.Scanner;

public class Vigenere {

    static String generateKey(String str, String key) {
        int x = str.length();

        for (int i = 0;; i++) {
            if (x == i)
                i = 0;
            if (key.length() == str.length())
                break;
            key += (key.charAt(i));
        }
        return key;
    }

    static String cipherText(String str, String key) {
        String cipher_text = "";

        for (int i = 0; i < str.length(); i++) {
            int x = (str.charAt(i) + key.charAt(i)) % 26;
            x += 'A';
            cipher_text += (char) (x);
        }
        return cipher_text;
    }

    static String originalText(String cipher_text, String key) {
        String orig_text = "";

        for (int i = 0; i < cipher_text.length() && i < key.length(); i++) {
            int x = (cipher_text.charAt(i) - key.charAt(i) + 26) % 26;
            x += 'A';
            orig_text += (char) (x);
        }
        return orig_text;
    }

    static String LowerToUpper(String s) {
        StringBuffer str = new StringBuffer(s);
        for (int i = 0; i < s.length(); i++) {
            if (Character.isLowerCase(s.charAt(i))) {
                str.setCharAt(i, Character.toUpperCase(s.charAt(i)));
            }
        }
        s = str.toString();
        return s;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str, keyword, key, cipher_text, original_text;

        while (true) {
            System.out.println("Vigenere Cipher Menu:");
            System.out.println("1. Encrypt a string");
            System.out.println("2. Decrypt a string");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.println("Enter a string:");
                    sc.nextLine(); // Consume the newline character
                    str = sc.nextLine();
                    System.out.println("Enter a keyword:");
                    keyword = sc.nextLine();
                    str = LowerToUpper(str);
                    keyword = LowerToUpper(keyword);
                    key = generateKey(str, keyword);
                    cipher_text = cipherText(str, key);
                    System.out.println("Ciphertext: " + cipher_text + "\n");
                    break;
                case 2:
                    System.out.println("Enter the ciphertext:");
                    sc.nextLine(); // Consume the newline character
                    cipher_text = sc.nextLine();
                    System.out.println("Enter the keyword:");
                    keyword = sc.nextLine();
                    cipher_text = LowerToUpper(cipher_text);
                    keyword = LowerToUpper(keyword);
                    key = generateKey(cipher_text, keyword);
                    original_text = originalText(cipher_text, key);
                    System.out.println("Original/Decrypted Text: " + original_text);
                    break;
                case 3:
                    System.out.println("Exiting the Vigenere Cipher program.");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
            }
        }
    }
}

