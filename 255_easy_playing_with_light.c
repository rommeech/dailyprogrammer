#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const unsigned short size = 8 * sizeof(long);
const unsigned long mask = ~0;

int main()
{
	// Bitwise implementation.
	// One long number is 64 (usually) bits, or 64 bulbs 
	unsigned int bulbs_num, bulbs_min, bulbs_max;
	unsigned short longs_num, longs_min, longs_max;
	unsigned short bits_min, bits_max;

	// Get bulbs number;
	scanf("%d", &bulbs_num);
	longs_num = ceil(bulbs_num / (float)size);

	// Build longs array
	unsigned long* data = (unsigned long*) malloc(longs_num * sizeof(long));

	// Debug output
	printf("size=%i, bulbs_num=%i, longs_num=%i\n",
		size, bulbs_num, longs_num);

	*(data+0) = 0;

	// Read number pairs
	while(scanf("%d", &bulbs_min) != EOF && scanf("%d", &bulbs_max) != EOF)
	{
		if (bulbs_min > bulbs_max) {
			bulbs_min += bulbs_max;
			bulbs_max = bulbs_min - bulbs_max;
			bulbs_min -= bulbs_max;
		}

		// Ok, now we should invert all bits between bulbs_min and bulbs_max
		longs_min = bulbs_min / size;
		longs_max = bulbs_max / size;

		// Debug output
		printf("bulbs_min=%i, bulbs_max=%i\n", bulbs_min, bulbs_max);
		printf("longs_min=%i, longs_max=%i\n", longs_min, longs_max);

		// Invert
		if (longs_min == longs_max) {
			unsigned short p = bulbs_max % size;
			unsigned short n = bulbs_max - bulbs_min + 1;
			*(data+0) = n == size ? *(data+0) ^ mask
			                      : *(data+0) ^ (~(mask << n) << (p - n + 1));
			printf("res=%lu\n", *(data+0));
		}
	}

	return 1;
}
