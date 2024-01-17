
struct FoundWord {
	int position;
	int value;
};

struct FoundWord newWord() {
	struct FoundWord result;
	return result;
};

struct FoundWord setPosition(struct FoundWord in, int position) {
	in.position = position;
	return in;
};

struct FoundWord setValue(struct FoundWord in, int value) {
	in.value = value;
	return in;
};

struct TupleOfFoundWords {
	struct FoundWord first;
	struct FoundWord last;
};

struct TupleOfFoundWords newTuple() {
	struct TupleOfFoundWords result;
	return result;
};


