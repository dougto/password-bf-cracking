FLAGS=-O3 -lssl -lcrypto -I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib

CC=gcc

RM=rm -f

EXEC=password_bf

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) password_bf.c -c -o password_bf.o
	$(CC) password_bf.o -o $(EXEC) $(FLAGS)

run:
	./$(EXEC)

clean:
	$(RM) password_bf.o $(EXEC)

exec:
	./password_bf < password.in

rerun:
	make clean && make && make run

rerun-in:
	make clean && make && make exec