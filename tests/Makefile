CC ?= cc
C_FLAGS := -std=c99 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -I.. -Iinclude
OBJECT_FILES := build/main.o build/int_vector.o
DIRECTORIES := build

all: ${DIRECTORIES} test

clean:
	$(foreach DIRECTORY,$\
		${DIRECTORIES},$\
		$(if $(wildcard ${DIRECTORY}),$\
			$(shell rm -r ${DIRECTORY})$\
		)$\
	)

${DIRECTORIES}:
	$(foreach DIRECTORY,$\
		${DIRECTORIES},$\
		$(if $(wildcard ${DIRECTORY}),,$\
			$(shell mkdir ${DIRECTORY})$\
		)$\
	)

test: ${OBJECT_FILES}
	${CC} ${OBJECT_FILES} -o test

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

.PHONY: all clean
