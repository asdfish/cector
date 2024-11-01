CC ?= cc
C_FLAGS := -std=c99 $\
					 -O2 -march=native -pipe $\
					 -Wall -Wextra -Wpedantic $\
					 -I.

PROCESSED_HEADER_FILES := $(subst .h,$\
														$(if $(findstring clang,${CC}),$\
															.h.pch,$\
															.h.gch),$\
														$(shell find -name '*.h' -not -path './tests/*'))

TEST_OBJECT_FILES := $(patsubst tests/src/%.c,$\
											 tests/build/%.o,$\
											 $(shell find tests/src -name '*.c'))
TEST_PROCESSED_HEADER_FILES := $(subst .h,$\
																 $(if $(findstring clang,${CC}),$\
																	 .h.pch,$\
																	 .h.gch),$\
																 $(shell find tests -name '*.h'))

define REMOVE_LIST
	$(foreach ITEM,$\
		$(1),$\
		$(if $(wildcard ${ITEM}),$\
			$(shell rm ${ITEM})))

endef

all: ${PROCESSED_HEADER_FILES} # tests/test

tests/build/%.o: tests/src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

tests/test: ${TEST_PROCESSED_HEADER_FILES} ${TEST_OBJECT_FILES}

%.gch: %
	${CC} -c $< ${C_FLAGS}

%.pch: %
	${CC} -c $< ${C_FLAGS}

clean:
	$(call REMOVE_LIST,$\
		${PROCESSED_HEADER_FILES})
	$(call REMOVE_LIST,$\
		${TEST_PROCESSED_HEADER_FILES})
	$(call REMOVE_LIST,$\
		${TEST_OBJECT_FILES})
ifneq (,$(wildcard tests/test))
	rm tests/test
endif

.PHONY: all clean
