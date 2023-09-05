CC 		= gcc
WATCH 	= watchexec

NAME 	= fvm
TNAME 	= t.$(NAME)

MAIN 	= \
		src/main.c

SRC 	= \
		src/vm_end.c\
		src/vm_new.c\
		src/vm_load.c\
		src/vm_exec.c\
		src/ld.c\

TSRC 	= \
		tests/tests.c\

MAINOBJ		= $(MAIN:.c=.o)
OBJ 		= $(SRC:.c=.o)
TOBJ 		= $(TSRC:.c=.o)

CFLAGS 		+= -Wextra -Wall
CPPFLAGS 	+= -iquote./include
LDFLAGS		+=
WFLAGS		+= -e c -e h

#-#-#-#-#-#-#-#-#

.PHONY: $(NAME) all

$(NAME): $(OBJ) $(MAINOBJ)
	$(CC) -o $(NAME) $(MAINOBJ) $(OBJ) $(LDFLAGS)
	@echo -e "[\e\x5b34;1mMaked\e\x5bm]"

all: $(NAME)

#-#-#-#-#-#-#-#-#

.PHONY: clean fclean

clean:
	$(RM) $(OBJ)
	$(RM) $(TOBJ)
	$(RM) $(MAINOBJ)
	find . -name '*.gc*' -exec $(RM) {} \;

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TNAME)

#-#-#-#-#-#-#-#-#

.PHONY: wt wtr

wt:
	$(WATCH) $(WFLAGS) $(MAKE) $(WCMD)

wtr: WCMD += debug
wtr: watch

#-#-#-#-#-#-#-#-#

.PHONY: debug cov test-build test lint

debug: CFLAGS += -g3
debug: $(NAME)

cov: LDFLAGS += -lgcov
cov: CFLAGS += -fprofile-arcs -ftest-coverage
cov: $(NAME)

test-build: LDFLAGS += -lcriterion
test-build: $(TOBJ) $(OBJ)
	$(CC) -o $(TNAME) $(TOBJ) $(OBJ) $(LDFLAGS)

test: test-build
	./$(TNAME)

lint: fclean
	clint . .

#-#-#-#-#-#-#-#-#

.PHONY: re red recov retest

re: fclean all
retest: fclean test
recov: fclean cov
red: fclean debug

#-#-#-#-#-#-#-#-#
