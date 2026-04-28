all: chess_static chess_dynamic

%.o: %.c
	gcc -c $< -fPIC
chessrules.o: chessrules.h
chessUI.o: chessUI.h
chessio.o: chessio.h

libchess.a : chessrules.o chessUI.o chessio.o
	ar rcs libchess.a chessrules.o chessUI.o chessio.o
libchess.so:chessrules.o chessUI.o chessio.o
	gcc -shared -o libchess.so chessrules.o chessio.o chessUI.o -lncurses
chess_static: main.c libchess.a
	gcc main.c libchess.a -lncurses -o $@
chess_dynamic: main.c libchess.so
	gcc main.c -L. -lchess -lncurses -o $@
clean :
	rm -f *.o *.so *.a chess_static chess_dynamic
