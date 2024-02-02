# include <string.h>

int get_buffer_length(char* buffer, size_t buffer_size) {
	int buffer_length = 0;
	for (int i = 0; i < buffer_size; ++i) {
		if (buffer[i] == '\0') break;
		++buffer_length;
	}
	return buffer_length;
}
