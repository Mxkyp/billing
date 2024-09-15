CC=gcc
CFLAGS= -Wall -Wextra
SRC=./src/
LIBS=-lncurses -lmenu

main.o: $(SRC)main.c customer.h product.h my_menus.h
	$(CC) $(CFLAGS) -c $(SRC)main.c

customer.o: $(SRC)customer.c customer.h product.h
	$(CC) $(CFLAGS) -c $(SRC)customer.c

product.o: $(SRC)product.c product.h
	$(CC) $(CFLAGS) -c $(SRC)product.c

interface.o: $(SRC)interface.c interface.h
	$(CC) $(CFLAGS) -c $(SRC)interface.c

my_menus.o: $(SRC)my_menus.c my_menus.h interface.h
	$(CC) $(CFLAGS) -c $(SRC)my_menus.c

test.o: $(SRC)test.c
	$(CC) $(CFLAGS) -c $(SRC)test.c
#=====================================================

billing: main.o customer.o product.o
	$(CC) $(CFLAGS) -o billing.x main.o customer.o product.o && ./billing

bill: main.o interface.o my_menus.o
	$(CC) $(CFLAGS) -o bill.x main.o interface.o my_menus.o $(LIBS)

test: test.o
	$(CC) $(CFLAGS) -o test.x test.o $(LIBS)
clean:
	rm *.o *.a *.x
