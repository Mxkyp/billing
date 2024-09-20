CC=gcc
CFLAGS= -Wall -Wextra #-fsanitize=address -fsanitize=undefined
SRC=./src/
LIBS=-lncurses -lmenu

main.o: $(SRC)main.c customer.h product.h my_menus.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)main.c

customer.o: $(SRC)customer.c customer.h product.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)customer.c

product.o: $(SRC)product.c product.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)product.c

interface.o: $(SRC)interface.c interface.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)interface.c

my_menus.o: $(SRC)my_menus.c my_menus.h interface.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)my_menus.c

cleanup.o: $(SRC)cleanup.c cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)cleanup.c

test.o: $(SRC)test.c
	$(CC) $(CFLAGS) -c $(SRC)test.c
#=====================================================

billing: main.o customer.o product.o
	$(CC) $(CFLAGS) -o billing.x main.o customer.o product.o && ./billing

bill: main.o interface.o my_menus.o cleanup.o
	$(CC) $(CFLAGS) -o bill.x main.o interface.o my_menus.o cleanup.o $(LIBS)

test: test.o
	$(CC) $(CFLAGS) -o test.x test.o $(LIBS)
clean:
	rm *.o *.a *.x
