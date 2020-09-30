FLAGS=-O3 -lssl -lcrypto -I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib

CC=gcc

RM=rm -f

EXEC=password_bf

EXEC_HASH=generate_hash

all: $(EXEC)

## password bf cracking commands

build:
	$(CC) $(FLAGS) password_bf.c -c -o password_bf.o
	$(CC) password_bf.o -o $(EXEC) $(FLAGS)

exec:
	./${EXEC} < password.in

rerun:
	make clean && make build && make exec

## hash helper commands

build-hash:
	${CC} ${FLAGS} generate_hash.c -c -o generate_hash.o
	${CC} generate_hash.o -o ${EXEC_HASH} ${FLAGS}

exec-hash:
	./${EXEC_HASH}

## general commands

clean:
	$(RM) password_bf.o $(EXEC) generate_hash.o ${EXEC_HASH}
