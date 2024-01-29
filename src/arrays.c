# include <stdio.h>
# include <stdbool.h>
# include <string.h>

# define TRUE  1
# define MAX_INPUT_LENGTH = 1000;

int read_line(char array[], int max_length); 
int char_exists_in_array(char digit, char* array, size_t array_length);
void get_first_and_last_word_from(char string[], char needle[], struct TupleOfFoundWords words);

int word_to_int(char word[]) {
	if (strcmp(word, "one") == 0) {
		return 1;
	} else if (strcmp(word, "two") == 0)   {
		return 2;
	} else if (strcmp(word, "three") == 0) {
		return 3;
	} else if (strcmp(word, "four") == 0)  {
		return 4;
	} else if (strcmp(word, "five") == 0)  {
		return 5;
	} else if (strcmp(word, "six") == 0)   {
		return 6;
	} else if (strcmp(word, "seven") == 0) {
		return 7;
	} else if (strcmp(word, "eight") == 0) {
		return 8;
	} else if (strcmp(word, "nine") == 0)  {
		return 9;
	}

	return 0;
}

// returns the actual length (without the extra spaces)
int get_buffer_length(char array[], size_t array_len) {
	int i = 0;
	for (; i < array_len && array[i] != '\n' && array[i] != '\0'; ++i) {
	}
	return i;
}

int char_exists_in_array(char digit, char* array, size_t array_length) {
	for(int i = 0; i < array_length; ++i) {
		if (digit == array[i]) {
			return digit;
		}
	}
	return -1;
}

int read_input(char rray[], size_t input_buffer_length, char message[]) {
	read_line(rray, input_buffer_length);
	printf(">> You entered: %s\n", rray);
	printf(">> %s\n", message);
	return TRUE;
}

void tabs_into_spaces(char from[], size_t size, char to[]) {
	int i = 0;
	int j = 0;
	printf(">> The array entered has a size of: %lu\n", size);
	for (i = 0; from[i] != '\0'; ++i) {
		printf(">> At index %d we found: %c\n", i, from[i]);
	}
	for (i = j = 0; from[i] != '\0'; ++i, ++j) {
		if (from[i] == '\t') {
			to[j] = '-';
			j += 1;
			to[j] = '-';
			j += 1;
			to[j] = '-';
			j += 1;
			to[j] = '-';
			continue;
		}
		to[j] = from[i] ;
	}
}

int read_line(char array[], int max_length) {
	int i = 0;
	int c = 0;
	while((c = getchar()) != EOF && c != '\n' && i < max_length - 1) {
		array[i] = c;
		if (c == '\n') {
			printf("Found a newline.\n");
			array[i] = c;
			++i;
		}
		++i;
	}
	array[i] = '\0';
	return i;
}

void print_array(char *array, size_t len) {
	for (int i = 0; i < len; ++i) {
	printf("[");
	printf(" %d ", array[i]);
	printf("]\n");
	}
}

void reverse_arrayy(char array[], size_t len) {
	int first = 0;
	int last = len - 1;
	int current;
	while (first <= last) {
		if (first == last) {
			printf("The array's length is not par.\n");
			return;
		}
		current = array[first];
		array[first] = array[last];
		array[last] = current;
		--last;
		++first;
	}
}


