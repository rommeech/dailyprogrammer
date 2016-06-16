    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <time.h>

    const unsigned short size = 8 * sizeof(long);

    int main()
    {
        // Bitwise implementation.
        // One long number is 64 (usually) bits, or 64 bulbs 
        unsigned int bulbs_num, bulbs_min, bulbs_max;
        unsigned int longs_num, longs_min, longs_max;
        unsigned short bits_min, bits_max, bit;
        int i, j;
        unsigned long res, cnt;
        clock_t tstart = clock();

        // Get bulbs number;
        scanf("%d", &bulbs_num);

        // Get number of longs numbers
        longs_num = ceil((bulbs_num+1) / (float)size);

        // Build longs array
        unsigned long* data = (unsigned long*) malloc(longs_num * sizeof(long));
        for (i = 0; i < longs_num; i++)
            *(data+i) = 0;

        // Read number pairs
        while(scanf("%d", &bulbs_min) != EOF && scanf("%d", &bulbs_max) != EOF)
        {
            // Sort they
            if (bulbs_min > bulbs_max) {
                bulbs_min += bulbs_max;
                bulbs_max = bulbs_min - bulbs_max;
                bulbs_min -= bulbs_max;
            }

            bulbs_max++;

            // Set up limits
            longs_min = bulbs_min / size;
            bits_min  = bulbs_min % size;
            *(data+longs_min) ^= (1UL << bits_min);

            longs_max = bulbs_max / size;
            bits_max  = bulbs_max % size;
            *(data+longs_max) ^= (1UL << bits_max);
        }

        // Done, calc bits
        bit = cnt = res = 0;
        for (i = 0; i < longs_num; i++)
            for (j = 0; j < size && cnt++ < bulbs_num; j++) {
                if (*(data+i) & 1) {
                    bit ^= 1;
                }
                res += bit;
                *(data+i) >>= 1;
            }

        free(data);

        // Output, benchmark
        printf("res=%lu (%f sec.)\n", res, (double)(clock() - tstart) / CLOCKS_PER_SEC);

        return 1;
    }
