FLAGS=-O3 -lssl -lcrypto -I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib

CC=gcc

RM=rm -f

EXEC=password_bf

all: $(EXEC)

## password bf cracking commands

build:
	$(CC) $(FLAGS) password_bf.c -c -o password_bf.o
	$(CC) password_bf.o -o $(EXEC) $(FLAGS)

exec:
	./${EXEC} < password.in

rerun:
	make clean && make build && make exec

## general commands

clean:
	$(RM) password_bf.o $(EXEC)
