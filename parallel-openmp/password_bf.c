#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <time.h>
#include <omp.h>

// MD5_DIGEST_LENGTH = 16

#define MAX 6 // max size of password

char letters[] = "ABCDEFGHIJKLMNOPQRS1234567890";

typedef unsigned char byte;

/*
 * Print a digest of MD5 hash.
*/
void print_digest(byte *hash)
{
	int x;

	for (x = 0; x < MD5_DIGEST_LENGTH; x++)
		printf("%02x", hash[x]);
	printf("\n");
}

/*
 * This procedure generate all combinations of possible letters
*/
void iterate(byte *hash1, byte *hash2, char *str, int idx, int *ok)
{
	int c;

	// if idx reached MAX search length, computation is over;
	if (idx == MAX)
		return;

	// 'ok' determines when the algorithm matches.
	if (*ok)
		return;

	// Iterate for all letter combination.
	for (c = 0; c < strlen(letters) && *ok == 0; ++c)
	{
		str[idx] = letters[c];
		// check if password matches
		MD5((byte *)str, idx + 1, hash2);
		if (strncmp((char *)hash1, (char *)hash2, MD5_DIGEST_LENGTH) == 0)
		{
			str[idx + 1] = 0;

			printf("found: %s\n", str);
			print_digest(hash2);
			#pragma omp critical
			*ok = 1;
		}
		// Recursive call
		iterate(hash1, hash2, str, idx + 1, ok);
	}
}

/*
 * Convert hexadecimal string to hash byte.
*/
void strHex_to_byte(char *str, byte *hash)
{
	char *pos = str;
	int i;

	for (i = 0; i < MD5_DIGEST_LENGTH / sizeof *hash; i++)
	{
		sscanf(pos, "%2hhx", &hash[i]);
		pos += 2;
	}
}

int main(int argc, char **argv)
{
	double time1 = omp_get_wtime();

	int ok = 0, r;
	char hash1_str[2 * MD5_DIGEST_LENGTH + 1];
	byte hash1[MD5_DIGEST_LENGTH]; // password hash

	// Input:
	r = scanf("%s", hash1_str);

	// Check input.
	if (r == EOF || r == 0)
	{
		fprintf(stderr, "Error!\n");
		exit(1);
	}

	// Convert hexadecimal string to hash byte.
	strHex_to_byte(hash1_str, hash1);

	print_digest(hash1);

	int c;

	#pragma omp parallel shared(ok, hash1)
	{
		byte hash2[MD5_DIGEST_LENGTH]; // string hashes
		memset(hash2, 0, MD5_DIGEST_LENGTH);

		char str[MAX + 1];
		memset(str, 0, MAX + 1);

		#pragma omp for
		for (c = 0; c < strlen(letters); ++c)
		{
			if (ok == 0) {
				str[0] = letters[c];
				// check if password matches
				MD5((byte *)str, 1, hash2);
				if (strncmp((char *)hash1, (char *)hash2, MD5_DIGEST_LENGTH) == 0)
				{
					str[1] = 0;

					printf("found: %s\n", str);
					print_digest(hash2);
					#pragma omp critical
						ok = 1;
				}
			}
			// Recursive call
			iterate(hash1, hash2, str, 1, &ok);
		}
	}

	double time2 = omp_get_wtime();
	double totalTime = time2 - time1;

	printf("Time to execute: %f seconds", totalTime);
}
