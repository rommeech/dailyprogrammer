#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const unsigned short size = 8 * sizeof(long);
const unsigned long mask = ~0;

short debug = 0;

unsigned long invert(unsigned long num, unsigned short p, unsigned short n);

int main()
{
	// Bitwise implementation.
	// One long number is 64 (usually) bits, or 64 bulbs 
	unsigned int bulbs_num, bulbs_min, bulbs_max;
	unsigned int longs_num, longs_min, longs_max;
	unsigned short bits_min, bits_max;
	int i;
	unsigned short f, t;
	unsigned long res;

	// Get bulbs number;
	scanf("%d", &bulbs_num);
	longs_num = ceil(bulbs_num / (float)size);

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

		// Ok, now we should invert all bits between bulbs_min and bulbs_max
		longs_min = bulbs_min / size;
		longs_max = bulbs_max / size;

		//// Debug output
		//if (debug) {
		//	printf("bulbs_min=%i, bulbs_max=%i\n", bulbs_min, bulbs_max);
		//	printf("longs_min=%i, longs_max=%i\n", longs_min, longs_max);
		//}

		// Invert
		if (longs_min == longs_max) {
			
			// Invert bytes in one word from F to T
			f = bulbs_min % size;
			t = bulbs_max % size;
			*(data+longs_min) = invert(*(data+longs_min), f, t);
			
			// Debut output
			if (debug)
				printf("res%i=%lu / f=%i t=%i\n",
					longs_min, *(data+longs_min), f, t);
		}

		else {

			f = bulbs_min % size;
			t = bulbs_max % size;

			// Invert last F bytes in longs_min
			*(data+longs_min) = invert(*(data+longs_min), f, size-1);

			//// Debug output
			//if (debug)
			//	printf("res%i=%lu / f=%i t=%i\n",
			//		longs_min, *(data+longs_min), f, size-1);

			// Invert all bites between longs_min and longs_max
			if (longs_max - longs_min > 1) {
				for (i = longs_min + 1; i < longs_max; i++);
					//*(data+i) = *(data+i) ^ mask;
					
					//// Debug output
					//if (debug)
					//	printf("res%i=%lu\n", i, *(data+i));
			}

			// Invers first N bytes in longs_max
			*(data+longs_max) = invert(*(data+longs_max), 0, t);

			//// Debug output
			//if (debug)
			//	printf("res%i=%lu / p=%i n=%i\n",
			//		longs_max, *(data+longs_max), 0, t);
		}

	}

	printf("done...%lu\n", tmp);

	// Done, calc 1-bits in all numbers
	res = 0;
	for (i = 0; i < longs_num; i++)
		while (*(data+i) > 0) {
			if ((*(data+i) & 1) == 1)
				res++;
			*(data+i) >>= 1;
		}

	printf("res=%lu\n", res);

	return 1;
}

unsigned long invert(unsigned long num, unsigned short from, unsigned short to)
{
	return to - from == size - 1
		? num ^ mask
		: num ^ (~(mask << (to - from + 1)) << from);
}
