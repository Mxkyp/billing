CC=gcc
CFLAGS= -g -Wall -Wextra  -Wno-unused-parameter -fsanitize=address -fsanitize=undefined -static-libasan
SRC=./src/
LIBS=-lncurses -lmenu
DATA_FILE_LOC=./src/shop_data.txt
#-Werror#
main.o: $(SRC)main.c interface.h shop.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)main.c

shop.o: $(SRC)shop.c shop.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)shop.c

interface.o: $(SRC)interface.c interface.h cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)interface.c

cleanup.o: $(SRC)cleanup.c cleanup.h
	$(CC) $(CFLAGS) -c $(SRC)cleanup.c

test.o: $(SRC)test.c shop.h
	$(CC) $(CFLAGS) -c $(SRC)test.c
#=====================================================

billing: main.o customer.o product.o
	$(CC) $(CFLAGS) -o billing.x main.o customer.o product.o && ./billing

bill: main.o interface.o cleanup.o  shop.o
	$(CC) $(CFLAGS) -o bill.x main.o interface.o cleanup.o shop.o $(LIBS) && ./bill.x $(DATA_FILE_LOC)

test: test.o shop.o cleanup.o
	$(CC) $(CFLAGS) -o test.x test.o shop.o cleanup.o $(LIBS) && ./test.x $(DATA_FILE_LOC)
clean:
	rm *.o *.a *.x
