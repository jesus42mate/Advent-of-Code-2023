# import <string.h>
# import <stdlib.h>

int askIfCurrIsNumber(int curr);

typedef enum { RED, BLUE, GREEN } CubeType;

struct CubesInBuffer {
	int reds;
	int greens;
	int blues;
};

struct Set {
	int reds;
	int greens;
	int blues;
};

void cleanSet(struct Set *set) {
	set->reds = 0;
	set->greens = 0;
	set->blues = 0;
}


struct SetSlice {
	short len;
	char text[14];
	CubeType color;
	int cube_ammount;
};

void cleanSlice(struct SetSlice *slice) {
	for (int i = 0; i < 14; ++i) {
		slice->text[i] = '\0';
	}
	slice->cube_ammount = 0;
}


void getCubeAmmountFrom(struct SetSlice *setSlice) {
	short j, i;
	j = 0;
	i = 0;
	char numsFound[2] = "";
	for (; j < setSlice->len; ++j) {
		char curr = setSlice->text[j];
		int currInt = curr - '0';
		if (currInt >= 0 && currInt <= 15) {
			numsFound[i] = currInt + '0';
			++i;
		}
		// ----------------------------
	}
	setSlice->cube_ammount = atoi(numsFound);
}

// not used (I think)
char nums[9] = "123456789";
int askIfCurrIsNumber(int curr) {
	for (int i = 9; i > 0; --i) {
		if (curr - '0' == nums[i] - '0') return 1;
	}
	return 0;
}

int checkMiniBufferCubeAmmount(struct SetSlice setSlice) {
	int n;
}


struct SetSlice checkSetSliceColor(struct SetSlice* setSlice) {
	if (strstr(setSlice->text, "red"))   setSlice->color = RED;
	if (strstr(setSlice->text, "blue"))  setSlice->color = BLUE;
	if (strstr(setSlice->text, "green")) setSlice->color = GREEN;
	return *setSlice;
}


struct Set addRedCubesToSet(struct Set set, int cubes) {
	set.reds += cubes; 
	return set;

};

struct Set addGreenCubesToSet(struct Set set, int cubes) {
	set.greens += cubes; 
	return set;

};

struct Set addBlueCubesToSet(struct Set set, int cubes) {
	set.blues += cubes; 
	return set;

};


struct CubesInBuffer readCurrentSet(struct CubesInBuffer cube) {

}





