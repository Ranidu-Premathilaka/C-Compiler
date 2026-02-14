CC=gcc
SOURCES=executor.c lexer.c lexerDFA.c parseTree.c parser.c symbolTable.c main.c
HEADERS=tokenType.h lexerDFA.h lexer.h parseTree.h parser.h symbolTable.h executor.h
EXEC=a.out

all:
	$(CC) $(SOURCES) -o $(EXEC)

combine:
	> combined_headers.h; \
	for f in $(HEADERS); do \
		cat "$$f" >> combined_headers.h; \
		echo >> combined_headers.h; \
	done

	> combined_source.c; \
	for f in combined_headers.h $(SOURCES); do \
		cat "$$f" >> combined_source.c; \
		echo >> combined_source.c; \
	done

	# remove any lines containing #include " from combined_source.c
	grep -v '#include "' combined_source.c > combined_source.tmp; \
	mv combined_source.tmp combined_source.c

	rm combined_headers.h