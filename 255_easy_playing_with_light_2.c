#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const unsigned short size = 8 * sizeof(long);

short debug = 0;

int main(int argc, char *argv[])
{
	if (argc > 1)
		debug = 1;

	// Bitwise implementation.
	// One long number is 64 (usually) bits, or 64 bulbs 
	unsigned int bulbs_num, bulbs_min, bulbs_max;
	unsigned int longs_num, longs_min, longs_max;
	unsigned short bits_min, bits_max, bit;
	int i, j;
	unsigned long res, cnt;

	// Get bulbs number;
	scanf("%d", &bulbs_num);
	longs_num = ceil((bulbs_num+1) / (float)size);

	// Build longs array
	unsigned long* data = (unsigned long*) malloc(longs_num * sizeof(long));

	// Debug output
	if (debug)
		printf("size=%i, bulbs_num=%i, longs_num=%i\n",
			size, bulbs_num, longs_num);

	for (i = 0; i < longs_num; i++)
		*(data+i) = 0;

	// Read number pairs
	while(scanf("%d", &bulbs_min) != EOF && scanf("%d", &bulbs_max) != EOF)
	{
		if (bulbs_min > bulbs_max) {
			bulbs_min += bulbs_max;
			bulbs_max = bulbs_min - bulbs_max;
			bulbs_min -= bulbs_max;
		}

		bulbs_max++;

		longs_min = bulbs_min / size;
		bits_min  = bulbs_min % size;
		*(data+longs_min) ^= (1UL << bits_min);

		longs_max = bulbs_max / size;
		bits_max  = bulbs_max % size;
		*(data+longs_max) ^= (1UL << bits_max);

		// Debug output
		if (debug) {
			printf("res%i=%lu (bits=%i)\n",
				longs_min, *(data+longs_min), bits_min);
			printf("res%i=%lu (bits=%i)\n",
				longs_max, *(data+longs_max), bits_max);
		}
	}

	printf("done...\n");

	// Calc bits
	bit = 0;
	cnt = 0;
	res = 0;
	for (i = 0; i < longs_num; i++)
		for (j = 0; j < size && cnt++ < bulbs_num; j++) {
			if (*(data+i) & 1) {
				bit ^= 1;
			}
			res += bit;
			*(data+i) >>= 1;
		}

	printf("res=%lu\n", res);

	return 1;
}
