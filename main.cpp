#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tomcrypt.h>

int main() {
    unsigned char key[16] = "mysecretkey1234";  // Cheia de criptare
    unsigned char plaintext[16] = "Hello123";    // Textul de criptat
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];
    symmetric_key blowfish_key;
    int err;

    // Inițializare biblioteca
    if (register_cipher(&blowfish_desc) == -1) {
        printf("Error registering Blowfish\n");
        return -1;
    }

    // Setați cheia de criptare
    if ((err = blowfish_setup(key, 16, 0, &blowfish_key)) != CRYPT_OK) {
        printf("Blowfish setup error: %s\n", error_to_string(err));
        return -1;
    }

    // Criptare
    for (int i = 0; i < 16; i += 8) {  // Blowfish criptează blocuri de 8 octeți
        if ((err = blowfish_ecb_encrypt(plaintext + i, ciphertext + i, &blowfish_key)) != CRYPT_OK) {
            printf("Blowfish encryption error: %s\n", error_to_string(err));
            return -1;
        }
    }

    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decriptare
    for (int i = 0; i < 16; i += 8) {
        if ((err = blowfish_ecb_decrypt(ciphertext + i, decryptedtext + i, &blowfish_key)) != CRYPT_OK) {
            printf("Blowfish decryption error: %s\n", error_to_string(err));
            return -1;
        }
    }

    decryptedtext[15] = '\0';  // Adăugăm terminatorul de șir
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
