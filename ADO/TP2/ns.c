#include <stdio.h>
#include <string.h>

unsigned bitCount(unsigned n) {
    unsigned res = 0;
    while (n > 0) {
        res += n & 1;
        n = n >> 1;
    }
    return res;
}

unsigned char forDigit(unsigned n) {
    char res = n + '0';
    if (n > 9) {
        res = res - '0' + 'A' - 10;
    }
    return res;
}

unsigned digit(unsigned char n) {
    unsigned res = n - '0';
    if (n >= 'A' && n <= 'F') {
        res = res + 10;
    }
    return res;
}

void reverseString(char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    int left = 0;
    int right = len - 1;

    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

void toHexString(unsigned n, char *s) {
    int index = 0;
    int hasNonZeroDigit = 0;

    for (int i = 28; i >= 0; i -= 4) {
        unsigned digit = (n >> i) & 0xF;
        if (digit != 0 || hasNonZeroDigit) {
            s[index++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
            hasNonZeroDigit = 1;
        }
    }

    if (!hasNonZeroDigit) {
        s[index++] = '0';
    }

    s[index] = '\0';
}

void toBinString(unsigned n, char *s) {
    int index = 0;
    int hasNonZeroBit = 0;

    for (int i = 31; i >= 0; i--) {
        unsigned bit = (n >> i) & 1;
        if (bit != 0 || hasNonZeroBit) {
            s[index++] = '0' + bit;
            hasNonZeroBit = 1;
        }

        if (i % 4 == 0 && i != 0) {
            s[index++] = ' ';
        }
    }

    if (!hasNonZeroBit) {
        s[index++] = '0';
    }

    s[index] = '\0';
}

void toUnsignedStringBase(unsigned n, char *s, unsigned base) {
    int index = 0;

    if (n == 0) {
        s[index++] = '0';
    } else {
        while (n > 0) {
            unsigned digit = n % base;
            s[index++] = '0' + digit;
            n /= base;

            if (index % 3 == 0 && n != 0) {
                s[index++] = ' ';
            }
        }
    }

    s[index] = '\0';
    reverseString(s);
}

void toStringUnsigned(unsigned n, char *s, unsigned base) {
    if (base == 16) {
        toHexString(n, s);
    } else if (base == 2) {
        toBinString(n, s);
    } else {
        toUnsignedStringBase(n, s, base);
    }
}

unsigned parseHex(char *s) {
    unsigned result = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            continue;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            result = result * 16 + (s[i] - '0');
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            result = result * 16 + (s[i] - 'A' + 10);
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            result = result * 16 + (s[i] - 'a' + 10);
        } else {
            break;
        }
    }

    return result;
}

unsigned parseBin(char *s) {
    unsigned result = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            continue;
        }

        if (s[i] == '0' || s[i] == '1') {
            result = result * 2 + (s[i] - '0');
        } else {
            break;
        }
    }

    return result;
}

unsigned parseBase(char *s, unsigned base) {
    unsigned result = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            continue;
        }

        unsigned digit;
        if (s[i] >= '0' && s[i] <= '9') {
            digit = s[i] - '0';
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            digit = s[i] - 'A' + 10;  // Ajout de 10 pour 'A' à 'F'
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            digit = s[i] - 'a' + 10;  // Ajout de 10 pour 'a' à 'f'
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }

        result = result * base + digit;
    }

    return result;
}

unsigned parseUnsigned(char *s, unsigned base) {
    if (base == 16) {
        return parseBase(s, base);  // Utilisez parseBase pour la base 16
    } else if (base == 2) {
        return parseBin(s);
    } else {
        return parseBase(s, base);
    }
}

int main() {
    printf("%u \n", bitCount(0xF0F0F0F0));
    printf("%c \n", forDigit(9)); // affiche 9
    printf("%c \n", forDigit(10)); // affiche 0xA
    printf("%u \n", digit('9')); // affiche 9
    printf("0x%x \n", digit('A')); // affiche 0xA

    char s[33];

    printf("fonction toHexString \n");
    toHexString(0x123, s);
    printf("%s \n", s);
    toHexString(0, s);
    printf("%s \n", s);
    toHexString(0xABCDE123, s);
    printf("%s \n", s);

    printf("fonction toBinString \n");
    toBinString(0x123, s); // => *s="0001 0010 0011\0"
    printf("%s \n", s);
    toBinString(0, s); // => *s="0\0"
    printf("%s \n", s);
    toBinString(0x123, s); // => *s="0001 0010 0011\0"
    printf("%s \n", s);

    printf("fonction toUnsignedStringBase \n");
    toUnsignedStringBase(0, s, 10); // => *s="0\0"
    printf("%s \n", s);
    toUnsignedStringBase(0x123, s, 10); // => *s="291\0"
    printf("%s \n", s);
    toUnsignedStringBase(0x123, s, 10); // => *s="291\0"
    printf("%s \n", s);
    toUnsignedStringBase(0x123, s, 16); // => *s"123\0"
    printf("%s \n", s);
    toUnsignedStringBase(0xFFFF, s, 10); // => *s="65 535\0"
    printf("%s \n", s);

    printf("fonction parseBase \n");
    unsigned n;
    n = parseBase("123", 10); // => retourne 123;
    printf("%u \n", n);
    n = parseBase("123", 16); // => retourne 291;
    printf("%u \n", n);
    n = parseBase("123", 2); // => retourne 7;
    printf("%u \n", n);

    printf("fonction parseUnsigned \n");
    n = parseUnsigned("123", 10); // => retourne 123
    printf("%u \n", n);
    n = parseUnsigned("123", 16); // => retourne 291
    printf("%u \n", n);
    n = parseUnsigned("123", 2); // => retourne 7
    printf("%u \n", n);

    printf("fonction parseHex \n");
    n = parseHex("123"); // => retourne 291
    printf("%u \n", n);

    printf("fonction parseBin \n");
    n = parseBin("1010 1010"); // => retourne 170
    printf("%u \n", n);
    n = parseBin("1 1001"); // => retourne 25
    printf("%u \n", n);

    return 0;
}
