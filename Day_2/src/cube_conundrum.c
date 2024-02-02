# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# import "arrays.c"
# import "./day2_lib.c"

# define MAXREDS   12
# define MAXGREENS 13
# define MAXBLUES  14

// DAY 2 --- CUBE CONUNDRUM
//
// Currently the program is set to solve the second part of the Day 2.
// The solution to the first part is archieved by breaking the loop 
// when the current set has more cubes than it should.

int main(int argc, char **args) {
	FILE *fptr;
	fptr = fopen("input.txt", "r");
	char buffer[160];
	char nums[9] = "123456789";
	int total = 0;
	int powerTotal = 0;
	// ------------

	int gameID = 0;
	while(fgets(buffer, sizeof(buffer), fptr)) {
		++gameID;
		printf("GameID: %d\n", gameID);
		printf("buffer: %s\n", buffer);
		// -------------
		
		// for the current game
		int minReds = 0;   // minimum needed cubes (max number of cubes seen per color)
		int minGreens = 0;
		int minBlues = 0;

		struct Set currentSet			 = { 0, 0, 0 };
		struct SetSlice setSlice   = { RED, "",  0, 14 };
		struct CubesInBuffer cubes = { 0, 0, 0 };

		int p = 0;
		bool started = false;
		int buffer_length = get_buffer_length(buffer, sizeof(buffer));
		//printf("buffer_length: %d\n", buffer_length);

		for (int i = 1; i < buffer_length; ++i) {
			printf("buffer[%d]: %c\n", i, buffer[i]);
			if (buffer[i - 1] == ':') started = true;
			if (!started)	continue;
			char curr = buffer[i];
			if (p > 14) p = 0;
			//--------------------

			setSlice.text[p] = curr;
			++p;

			if (curr == '\0') {
				printf("curr: %c\n", curr);
				printf("prev: %c\n", buffer[i - 1]);
			}

			if (curr == ',' || i == buffer_length - 1) {
				//printf("\tSetSlice: %s\n", setSlice.text);
				setSlice.len = p;
				p = 0;

				checkSetSliceColor(&setSlice);	
				getCubeAmmountFrom(&setSlice);

				//printf(" --> ammount: %d\n", setSlice.cube_ammount);

				if (setSlice.color == RED) {
					//printf(" -> color: red\n");
					// check if the ammount is the biggest we have seen so far
					if (setSlice.cube_ammount > minReds) minReds = setSlice.cube_ammount;
				}  

				if (setSlice.color == BLUE) {
					//printf(" -> color: blue\n");
					if (setSlice.cube_ammount > minBlues) minBlues = setSlice.cube_ammount;
				}  

				if (setSlice.color == GREEN) {
					//printf(" -> color: green\n");
					if (setSlice.cube_ammount > minGreens) minGreens = setSlice.cube_ammount;
				}


				if (setSlice.color == RED) {
					//if (setSlice.cube_ammount > MAXREDS) break;
					currentSet.reds += setSlice.cube_ammount;

				} else if (setSlice.color == BLUE) {
					//if (setSlice.cube_ammount > MAXBLUES) break;
					currentSet.blues += setSlice.cube_ammount;
					
				} else if (setSlice.color == GREEN) {
					//if (setSlice.cube_ammount > MAXGREENS) break;
					currentSet.greens += setSlice.cube_ammount;

				}
				//printf(" -> reds: %d\n", currentSet.reds);
				//printf(" -> blues: %d\n", currentSet.blues);
				//printf(" -> greens: %d\n", currentSet.greens);

				cleanSlice(&setSlice);

				if (currentSet.reds > MAXREDS ||
					currentSet.blues > MAXBLUES ||
					currentSet.greens > MAXGREENS)
				{
					printf("OVERFLOW\n");
				}
			}

			if (curr == ';' || i == buffer_length - 1) {
				printf("SetSlice so far: %s\n", setSlice.text);
				setSlice.len = p;
				p = 0;
				// before we clean the setSlice, we want to check
				// if the set has more cubes than it should
				// we have to sum all the same colored cubes in the 
				// current set

				checkSetSliceColor(&setSlice);	
				getCubeAmmountFrom(&setSlice);

				//printf(" --> ammount: %d\n", setSlice.cube_ammount);

				if (setSlice.color == RED) {
					//printf(" -> color: red\n");
					// check if the ammount is the biggest we have seen so far
					if (setSlice.cube_ammount > minReds) minReds = setSlice.cube_ammount;
					printf("minReds: %d\n", minReds);
				}  

				if (setSlice.color == BLUE) {
					//printf(" -> color: blue\n");
					if (setSlice.cube_ammount > minBlues) minBlues = setSlice.cube_ammount;
					printf("minBlues: %d\n", minBlues);
				}  

				if (setSlice.color == GREEN) {
					//printf(" -> color: green\n");
					if (setSlice.cube_ammount > minGreens) minGreens = setSlice.cube_ammount;
					printf("minGreens: %d\n", minGreens);
				}

				if (setSlice.color == RED) {
					printf("setSlice.cube_amount: %d\n", setSlice.cube_ammount);
					//if (setSlice.cube_ammount > MAXREDS) break;
					currentSet.reds += setSlice.cube_ammount;

				} else if (setSlice.color == BLUE) {
					printf("setSlice.cube_amount: %d\n", setSlice.cube_ammount);
					//if (setSlice.cube_ammount > MAXBLUES) break;
					currentSet.blues += setSlice.cube_ammount;

				} else if (setSlice.color == GREEN) {
					printf("setSlice.cube_amount: %d\n", setSlice.cube_ammount);
					//if (setSlice.cube_ammount > MAXGREENS) break;
					currentSet.greens += setSlice.cube_ammount;

				}
				//printf(" -> reds: %d\n", currentSet.reds);
				//printf(" -> blues: %d\n", currentSet.blues);
				//printf(" -> greens: %d\n", currentSet.greens);

				cleanSlice(&setSlice);
				cleanSet(&currentSet);
			}
			if (i == buffer_length - 1) {
				//printf("%d + %d = %d\n", total, gameID, total + gameID);
				total += gameID;
			}
		}

		printf("minReds %d, minBlues: %d, minGreens: %d\n", minReds, minBlues, minGreens);
		powerTotal += minReds * minBlues * minGreens;

		printf("powerTotal: %d\n", powerTotal);
		//printf("total: %d\n", total);
	}
	// ------------
	fclose(fptr);
	return 0;
}
