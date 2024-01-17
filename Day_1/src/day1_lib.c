# include <stdbool.h>

char int_to_char(int x);

char int_to_char(int x) {
	union {
		char a[2];
		int b;
	} temp;
	temp.b = x;
	return temp.a;
}

void two_ints_to_char_array(int x, int y, char a[]) {
	a[0] = x;
	a[1] = y;
}


