#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>

typedef unsigned char byte;

void print_digest(byte *hash)
{
  int x;
  printf("hash: ");
  for (x = 0; x < MD5_DIGEST_LENGTH; x++)
    printf("%02x", hash[x]);
  printf("\n");
}

int main(int argc, char **argv)
{
  int r;
  char str[99];
  byte hash[MD5_DIGEST_LENGTH];

  r = scanf("%s", str);

  printf("input: %s \n", str);

  MD5((byte *)str, strlen(str), hash);

  print_digest(hash);
}
