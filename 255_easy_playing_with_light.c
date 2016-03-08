#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	unsigned short size = 8 * sizeof(long);
	unsigned int bulbs_num;
	unsigned short words_num;

	// Get bulbs number;
	scanf("%d", &bulbs_num);
	words_num = ceil(bulbs_num / (float)size);

	// Debug output
	printf("size=%i\n", size);
	printf("bulbs_num=%i\n", bulbs_num);
	printf("words_num=%i\n", words_num);

	// Build worlds array
	unsigned long* data = (unsigned long*) malloc(words_num * size);

	

	return 1;
}
