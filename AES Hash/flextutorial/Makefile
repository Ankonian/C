.PHONY: linux mac clean error


linux: lex.yy.o flextutorial.o
	cc  -o flextutorial flextutorial.o lex.yy.o -lfl || make error

mac: lex.yy.o flextutorial.o
	cc  -o flextutorial flextutorial.o lex.yy.o -ll

lex.yy.o : lex.yy.c
	cc -c lex.yy.c

flextutorial.o : flextutorial.c
	cc -c flextutorial.c

lex.yy.c: scanner.l
	flex scanner.l


platformerror := " \n Unable to compile. \n If you are on a mac, and the above error message contains \n  'ld: library not found for -lfl'\n use\n   make mac \n instead of just \n   make\n "
error:
	echo $(platformerror)

clean:
	rm -f flextutorial lex.yy.o lex.yy.c flextutorial.o
