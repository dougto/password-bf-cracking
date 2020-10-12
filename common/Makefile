FLAGS=-O3 -lssl -lcrypto -I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib

CC=gcc

RM=rm -f

EXEC=generate_hash

all: $(EXEC)

## hash helper commands

build-hash:
	${CC} ${FLAGS} generate_hash.c -c -o generate_hash.o
	${CC} generate_hash.o -o ${EXEC} ${FLAGS}

exec-hash:
	./${EXEC}

## general commands

clean:
	$(RM) generate_hash.o ${EXEC}
