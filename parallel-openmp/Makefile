FLAGS=-O3 -lssl -lcrypto -I /usr/local/opt/openssl/include -L /usr/local/opt/openssl/lib -I/usr/local/opt/llvm/include -fopenmp -L/usr/local/opt/llvm/lib

CC=/usr/local/bin/gcc-10

RM=rm -f

EXEC=password_bf

NUM_OF_THREADS=4

all: $(EXEC)

## password bf cracking commands

build:
	$(CC) $(FLAGS) password_bf.c -c -o password_bf.o
	$(CC) password_bf.o -o $(EXEC) $(FLAGS)

exec:
	export OMP_NUM_THREADS=${NUM_OF_THREADS} && ./${EXEC} < password.in

rerun:
	make clean && make build && make exec

## general commands

clean:
	$(RM) password_bf.o $(EXEC)
