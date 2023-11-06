import java.awt.Point;
import java.util.Scanner;

public class PlayfairCipher {
    private int length = 0;
    private String[][] table;

    public static void main(String[] args) {
        new PlayfairCipher();
    }

    private PlayfairCipher() {
        Scanner sc = new Scanner(System.in);
        String key = "";

        // Prompts the user for the keyword to use for encoding & creates tables
        System.out.print("Enter the key for Playfair cipher: ");
        key = parseString(sc);
        while (key.equals(""))
            key = parseString(sc);
        table = this.cipherTable(key);

        int choice = 0;
        while (choice != 3) {
            System.out.println("Choose an option:");
            System.out.println("1. Encrypt");
            System.out.println("2. Decrypt");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // Consume the newline character

            switch (choice) {
                case 1:
                    // Print the Playfair matrix
                    keyTable(table);

                    // Prompts the user for the message to be encrypted
                    System.out.print("Enter the plaintext to be encipher: ");
                    String input = parseString(sc);
                    while (input.equals(""))
                        input = parseString(sc);

                    // Encrypts the input and prints the result
                    String encryptedMessage = cipher(input);
                    System.out.println("Encrypted Message: " + encryptedMessage);
                    break;
                case 2:
                    // Prompts the user for the message to be decrypted
                    System.out.print("Enter the ciphertext to be decipher: ");
                    String cipherText = parseString(sc);
                    while (cipherText.equals(""))
                        cipherText = parseString(sc);

                    // Decrypts the ciphertext and prints the result
                    String decryptedMessage = decode(cipherText);
                    System.out.println("Decrypted Message: " + decryptedMessage);
                    break;
                case 3:
                    System.out.println("Exiting the program.");
                    break;
                default:
                    System.out.println("Invalid choice. Please enter 1, 2, or 3.");
            }
        }
    }

    private String parseString(Scanner sc) {
        String parse = sc.nextLine();
        parse = parse.toUpperCase();
        parse = parse.replaceAll("[^A-Z]", "");
        parse = parse.replace("J", "I");
        return parse;
    }

    private String[][] cipherTable(String key) {
        String[][] playfairTable = new String[5][5];
        String keyString = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ";

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                playfairTable[i][j] = "";
            }
        }

        for (int k = 0; k < keyString.length(); k++) {
            boolean repeat = false;
            boolean used = false;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (playfairTable[i][j].equals("" + keyString.charAt(k))) {
                        repeat = true;
                    } else if (playfairTable[i][j].equals("") && !repeat && !used) {
                        playfairTable[i][j] = "" + keyString.charAt(k);
                        used = true;
                    }
                }
            }
        }
        return playfairTable;
    }

    private String cipher(String in) {
        length = (int) in.length() / 2 + in.length() % 2;

        for (int i = 0; i < (length - 1); i++) {
            if (in.charAt(2 * i) == in.charAt(2 * i + 1)) {
                in = new StringBuffer(in).insert(2 * i + 1, 'X').toString();
                length = (int) in.length() / 2 + in.length() % 2;
            }
        }

        String[] digraph = new String[length];
        for (int j = 0; j < length; j++) {
            if (j == (length - 1) && in.length() / 2 == (length - 1))
                in = in + "X";
            digraph[j] = in.charAt(2 * j) + "" + in.charAt(2 * j + 1);
        }

        String out = "";
        String[] encDigraphs = new String[length];
        encDigraphs = encodeDigraph(digraph);
        for (int k = 0; k < length; k++)
            out = out + encDigraphs[k];
        return out;
    }

    private String[] encodeDigraph(String[] di) {
        String[] encipher = new String[length];
        for (int i = 0; i < length; i++) {
            char a = di[i].charAt(0);
            char b = di[i].charAt(1);
            int r1 = (int) getPoint(a).getX();
            int r2 = (int) getPoint(b).getX();
            int c1 = (int) getPoint(a).getY();
            int c2 = (int) getPoint(b).getY();

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
            encipher[i] = table[r1][c1] + "" + table[r2][c2];
        }
        return encipher;
    }

    private String decode(String out) {
        String decoded = "";
        for (int i = 0; i < out.length() / 2; i++) {
            char a = out.charAt(2 * i);
            char b = out.charAt(2 * i + 1);

            if (a != 'X') {
                int r1 = (int) getPoint(a).getX();
                int r2 = (int) getPoint(b).getX();
                int c1 = (int) getPoint(a).getY();
                int c2 = (int) getPoint(b).getY();

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
                decoded = decoded + table[r1][c1] + table[r2][c2];
            }
        }
        return decoded;
    }

    private Point getPoint(char c) {
        Point pt = new Point(0, 0);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (c == table[i][j].charAt(0)) {
                    pt = new Point(i, j);
                }
            }
        }
        return pt;
    }

    private void keyTable(String[][] printTable) {
        System.out.println("Playfair Cipher Key Matrix: ");
        System.out.println();
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                System.out.print(printTable[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
}
