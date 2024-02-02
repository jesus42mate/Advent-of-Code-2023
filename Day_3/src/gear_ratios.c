# include <stdio.h>
# import "../../src/arrays.c"

int main(int argc, char* argv[]) {
	printf("Please enter your puzzle line: \n");
	char line[300];
	FILE* fptr = fopen("line.txt", "r");
	// ----------------------

	while (fgets(line, sizeof(line), fptr)) {
		printf("%s\n", line);
	}

	// ----------------------
	fclose(fptr);
}

