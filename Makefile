# Build and test the K&R exercises. Each exercise is its own
# self-contained translation unit; VPATH lets the generic pattern rule
# below find chapterN/exN_MM.c regardless of which exercise is asked
# for.

CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror -pedantic
BUILD ?= build

VPATH = chapter1:chapter2:chapter3:chapter5

EXERCISES = ex1_02 ex1_04 ex1_06 ex1_13 ex1_24 \
            ex2_01 ex2_02 ex2_03 ex2_04 ex2_10 \
            ex3_01 ex3_02 ex3_03 \
            ex5_01

BINARIES = $(addprefix $(BUILD)/,$(EXERCISES))

.PHONY: all test test-asan clean

all: $(BINARIES) $(BUILD)/unit_tests

$(BUILD):
	mkdir -p $(BUILD)

# ex1_02's whole point is printing an escape sequence (\c) the language
# doesn't define; the "unknown escape sequence" warning that produces
# is the exercise, not a mistake, so this one target drops -Werror
# (and, with it, any other -W flags not already on by default) rather
# than silence the warning. Every other exercise builds clean with the
# full warning set.
$(BUILD)/ex1_02: ex1_02.c | $(BUILD)
	$(CC) $(filter-out -Werror,$(CFLAGS)) -o $@ $<

$(BUILD)/%: %.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD)/unit_tests: tests/unit_tests.c \
                      chapter2/ex2_03.c chapter2/ex2_04.c chapter2/ex2_10.c \
                      chapter3/ex3_01.c chapter3/ex3_02.c chapter3/ex3_03.c \
                      chapter5/ex5_01.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ tests/unit_tests.c

test: all
	./$(BUILD)/unit_tests
	BUILD=$(BUILD) ./tests/run_golden.sh

# Separate sanitizer pass: rebuilds everything into build-asan/ with
# AddressSanitizer and UndefinedBehaviorSanitizer enabled and runs the
# same tests against it.
test-asan:
	$(MAKE) CC=$(CC) BUILD=build-asan \
	    CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic -fsanitize=address,undefined -g" \
	    test

clean:
	rm -rf build build-asan
