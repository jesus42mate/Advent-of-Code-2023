# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# import "../../../C/libs/arrays.c"
# import "./day2_lib.c"

# define MAXREDS   12
# define MAXGREENS 13
# define MAXBLUES  14

int main(int argc, char **args) {
	FILE *fptr;
	fptr = fopen("input.txt", "r");
	char buffer[160];
	char nums[9] = "123456789";
	// ------------

	int gameID = 0;
	while(fgets(buffer, sizeof(buffer), fptr)) {
		++gameID;
		// -------------
		if (!strstr(buffer, "15")) printf("%s", buffer);
		else continue;

		struct SetSlice setSlice   = { RED, "",  0, 14 };
		struct Set currentSet			 = { 0, 0, 0 };
		struct CubesInBuffer cubes = { 0, 0, 0 };

		int p = 0;
		bool started = false;
		int buffer_length = get_buffer_length(buffer, sizeof(buffer));

		for (int i = 1; i < buffer_length; ++i) {
			if (buffer[i - 1] == ':') started = true;
			if (!started)	continue;
			char curr = buffer[i];
			if (p > 14) p = 0;
			//--------------------

			setSlice.text[p] = curr;
			++p;
			printf("SetSlice so far: %s\n", setSlice.text);

			if (curr == ',' || i == buffer_length - 1) {
				setSlice.len = p;
				p = 0;
				
				// here we check the color of the setSlice
				checkSetSliceColor(&setSlice);
				if (setSlice.color == RED)   printf(" -> color: red\n");
				if (setSlice.color == BLUE)  printf(" -> color: blue\n"); 
				if (setSlice.color == GREEN) printf(" -> color: green\n");

				// here we check the cube ammount of the setSlice
				getCubeAmmountFrom(&setSlice);
				printf(" -> ammount: %d\n", setSlice.cube_ammount);
				if (setSlice.color == RED) {
					currentSet.reds += setSlice.cube_ammount;
				} else if (setSlice.color == BLUE) {
					currentSet.blues += setSlice.cube_ammount;
				} else if (setSlice.color == GREEN) {
					currentSet.greens += setSlice.cube_ammount;
				}
				printf(" -> reds: %d\n", currentSet.reds);
				printf(" -> blues: %d\n", currentSet.blues);
				printf(" -> greens: %d\n", currentSet.greens);
				cleanSlice(&setSlice);
			}

			if (curr == ';') {
				p = 0;
				// before we clean the setSlice, we want to check
				// if the set has more cubes than it should
				// we have to sum all the same colored cubes in the 
				// current set
				
				// here we check the color of the setSlice
				checkSetSliceColor(&setSlice);
				if (setSlice.color == RED)   printf(" -> color: red\n");
				if (setSlice.color == BLUE)  printf(" -> color: blue\n"); 
				if (setSlice.color == GREEN) printf(" -> color: green\n");

				// here we check the cube ammount of the setSlice
				getCubeAmmountFrom(&setSlice);
				printf(" -> ammount: %d\n", setSlice.cube_ammount);
				// ---------------
				if (setSlice.color == RED) {
					currentSet.reds += setSlice.cube_ammount;
				} else if (setSlice.color == BLUE) {
					currentSet.blues += setSlice.cube_ammount;
				} else if (setSlice.color == GREEN) {
					currentSet.greens += setSlice.cube_ammount;
				}
				printf(" -> reds: %d\n", currentSet.reds);
				printf(" -> blues: %d\n", currentSet.blues);
				printf(" -> greens: %d\n", currentSet.greens);
				// ---------------
				cleanSlice(&setSlice);
				cleanSet(&currentSet);
			}
		}
		//printf("%s", buffer);
		//printf("game ID: %d\n", j);
	}
	// ------------
	fclose(fptr);
	return 0;
}
