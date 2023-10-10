#include <stdio.h>
#include <string.h>
unsigned bitCount(unsigned n){
	unsigned res = 0;
	while(n > 0){
		res += n & 1;
		n = n >> 1;
	}
	return res;
}



unsigned char forDigit(unsigned n){
	char res = n + '0';
	if (n > 9){
		res = res-'0' + 'A' - 10;
	}
	return res;
}


unsigned digit(unsigned char n){
	unsigned res = n - '0';
	if(n > '9'){
		res = res +'0' - 'A' + 10;
	}
	return res;
}

void toHexString(unsigned n, char *s){
	int pos = 0;
	int lz = 1;
	if (n == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}
	for (int i = 28; i >= 0; i -= 4) {
		unsigned digit = (n >> i) & 0xF;
		if (digit > 0 || !lz) {
			s[pos++] = forDigit(digit);
			lz = 0;
		}
		if ((pos % 5) == 4) {
			s[pos++] = ' ';
		}
	}
	s[pos] = '\0';

}

void toBinString(unsigned n,char *s){
	int j = 0;
	int fd = 1;
	if ( n == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}
	for(int i = 31;i >=0;i--){
		int dig = (n>>i)& 1;

		if(dig || !fd){
			s[j++]=dig +'0';
			fd = 0;
		}
		if(i%4==0 && i!=0){
			s[j++] = ' ';
		}
	}
	s[j]='\0';
}

void reverseString(char *str) {

}

void toUnsignedStringBase(unsigned n, char *s, unsigned base) {
	if (n == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}

	int position = 0;
	while (n > 0) {
		unsigned digit = n % base;
		s[position++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
		n /= base;
		if ((position % 4) == 3) {
			s[position++] = ' ';
		}
	}
	s[position] = '\0';

	int length = strlen(s);
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}





int main(){
	printf("%u \n", bitCount(0xF0F0F0F0));
	printf("%c \n",forDigit(9)); // affiche 9
	printf("%c \n",forDigit(10)); // affiche 0xA
	printf("%u \n",digit('9')); // affiche 9
	printf("0x%x \n",digit('A')); // affiche 0xA
	char s[33];


	toHexString(0x123,s);
	printf("%s \n",s );
	toHexString(0,s);
	printf("%s \n",s );
	toHexString(0xABCDE123,s);
	printf("%s \n",s );


	toBinString(0x123,s);
	printf("%s \n",s );
	toBinString(0,s);
	printf("%s \n",s );
	toBinString(0x123,s);
	printf("%s \n",s );

	toUnsignedStringBase(0,s,10); // => *s="0\0"
	printf("%s \n",s );
	toUnsignedStringBase(0x123,s,10); // => *s="291\0"
	printf("%s \n",s );
	toUnsignedStringBase(0x123,s,10); // => *s="291\0"
	printf("%s \n",s );
	toUnsignedStringBase(0x123,s,16); // => *s"123\0"
	printf("%s \n",s );
	toUnsignedStringBase(0xFFFF,s,10); // => *s="65 535\0"
	printf("%s \n",s );
	return 0;
}
