# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../../../C/libs/arrays.c"
# include "./day1_lib.c"
# include "./structs.c"

int main(int argv, char** args) {
	// file
	FILE *fptr;
	fptr = fopen("input.txt", "r");
	
	// buffer to store lines
	char line_contents[100];

	int total = 0;
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char* numbersWritten[] = {
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};
	// repeats for each line in file ptr 
	while(fgets(line_contents, 100, fptr)) {
		int line_length = get_buffer_length(line_contents, sizeof(line_contents));
		printf("\n>>> current line: %s", line_contents);
	
		// where we store our found words
		struct FoundWord first = { 0, 0 }; // (int) position | (int) value    
		struct FoundWord last = { 0, 0 };	  
		struct TupleOfFoundWords foundWords = { first, last };

		struct TupleOfFoundWords* ptr = &foundWords; // useful ? Idk tbh
		
		// check for each number (e.g "one", then "two" inside numbersWritten)
		for (int i = 0; i <= sizeof(*numbersWritten); ++i) {
			char* result = strstr(line_contents, numbersWritten[i]);
			while (result != NULL) {
				int offset = result - line_contents;
				if (offset < ptr->first.position || (ptr->first.position == 0 && ptr->first.value == 0)) {
					ptr->first.position = offset;
					ptr->first.value = word_to_int(numbersWritten[i]);
				}
				if (offset > ptr->last.position) {
					ptr->last.position = offset;
					ptr->last.value = word_to_int(numbersWritten[i]);
				}
				// we are checking for additional instances of the number to find the first and last one
				result = strstr(result + 1, numbersWritten[i]);
			}
		}
		// foundWords should have gotten updated (if some number was found)

		for (int i = 0; i < line_length; ++i) {
			int wasNumberFound = char_exists_in_array(line_contents[i] - '0', numbers, sizeof(numbers));
			if (wasNumberFound == -1) {
				continue;
			}
			int current_char = line_contents[i] - '0';
			if (i < ptr->first.position || (ptr->first.position == 0 && ptr->first.value == 0)) {
				ptr->first.value = line_contents[i] - '0';	
				ptr->first.position = i;
				continue;
			} else if (i > ptr->last.position) {
				ptr->last.value = line_contents[i] - '0';
				ptr->last.position = i;
				continue;
			}
		}
		if (ptr->last.value == 0) {
			ptr->last.value = ptr->first.value;
		}
		char a[2];
		char b[2];
		sprintf(a, "%d", foundWords.first.value);
		sprintf(b, "%d", foundWords.last.value);
		char *ab = strcat(a, b);
		printf("ab: %s\n", ab);
		int curr = atoi(ab);
		total = total + curr;
		printf("total: %d\n", total);
	}
	printf("total: %d\n", total);


	fclose(fptr);
	return 0;
}
