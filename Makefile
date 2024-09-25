CC=gcc
CFLAGS= -g -Wall -Wextra -Werror -Wno-unused-parameter -fsanitize=address -fsanitize=undefined -static-libasan
SRC=./src/
LIBS=-lncurses -lmenu
DATA_FILE_LOC=./src/shop_data.txt

main.o: $(SRC)main.c customer.h my_menus.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)main.c

shop.o: $(SRC)shop.c shop.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)shop.c

customer.o: $(SRC)customer.c customer.h shop.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)customer.c

interface.o: $(SRC)interface.c interface.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)interface.c

my_menus.o: $(SRC)my_menus.c my_menus.h interface.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)my_menus.c

cleanup.o: $(SRC)cleanup.c cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)cleanup.c

test.o: $(SRC)test.c my_menus.h shop.h
	$(CC) $(CFLAGS) -c $(SRC)test.c
#=====================================================

billing: main.o customer.o product.o
	$(CC) $(CFLAGS) -o billing.x main.o customer.o product.o && ./billing

bill: main.o interface.o my_menus.o cleanup.o customer.o shop.o
	$(CC) $(CFLAGS) -o bill.x main.o interface.o my_menus.o customer.o cleanup.o shop.o $(LIBS) && ./bill.x $(DATA_FILE_LOC)

test: test.o shop.o my_menus.o cleanup.o
	$(CC) $(CFLAGS) -o test.x test.o shop.o my_menus.o cleanup.o $(LIBS) && ./test.x $(DATA_FILE_LOC)
clean:
	rm *.o *.a *.x
