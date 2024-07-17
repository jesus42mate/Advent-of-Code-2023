#!/bin/sh

compile_and_run() {
	echo "File $FILE has been modified."

	# Compile the C file
	clang -o runnable "./src/gear_ratios_alternative.c"

	# Check if compilation was sucessful
	if [ $? -eq 0 ]; then
		# Run the compiled program
		./runnable
	else
		echo "Compilation failed."
	fi
}

# Initial compile and run
compile_and_run

# Watch for file changes
inotifywait -m "./src" -e modify | while read -r filename event; do
	compile_and_run
done
