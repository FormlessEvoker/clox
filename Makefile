all: clean compile

compile: 
	# Create the dist directory if it doesn't exist
	mkdir -p dist

	# Compile the C source files into an executable named clox in the dist directory
	gcc -o dist/clox \
		src/main.c \
		src/chunk.c \
		src/debug.c \
		src/memory.c \
		src/value.c \
		src/vm.c 

clean:
	rm -rf dist