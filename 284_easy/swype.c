#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DICT_FILE "enable1.txt"
#define MAX_WORD_LEN 80
#define DICT_WORD_MIN_LEN 5

int main()
{
	char *swype;
	int swype_len;
	unsigned long swype_hash = 0UL;
	
	char *found = (char *)malloc(MAX_WORD_LEN * sizeof(char));
	
	char c;
	int dict_len;
	int i, j;

	clock_t tstart;

	FILE *dict= fopen(DICT_FILE, "r");

	printf("Input SWYPE string or Ctrl+D for exit:\n");
	while (scanf("%s", swype) != EOF)
	{
		// Prepare
		tstart = clock();
		swype_len = strlen(swype);

		// Build simple hash of swype word for performance.
		// Actually this is long number, but we need only 26 bites
		// for 26 letters.
		// Each bite containt 1 if char exists in swype, 0 - if not.
		for (i = 0; i < swype_len; i++)
			swype_hash |= (1UL << (swype[i] - 'a'));

		// Reset dictionary file
		fseek(dict, 0, SEEK_SET);
		
		// Dictionary word position or -1 for not suitable words
		dict_len = 0;

		do
		{
			c = getc(dict);

			// End of the current dictionary word
			if (c == '\n' || c == EOF)
			{
				found[dict_len] = '\0';

				// We read dictionary word, check it
				// We do not need too short
				// And last chars should be equal
				if (dict_len >= DICT_WORD_MIN_LEN &&
					swype[swype_len-1] == found[dict_len-1]
				) {
					i = 1;
					for (j = 1; i < dict_len-1 && j < swype_len-1; j++)
						if (found[i] == swype[j] || found[i] == swype[j-1])
							i++;
					
					// Got it?
					if (i >= dict_len-1)
						printf("%s ", found);
				}
				
				// Reset for next dictionary word iteration
				dict_len = 0;
			}
			
			// This is letter and inside of suitable dictionary word
			else if (c >= 'a' && c <= 'z' && dict_len >= 0)
			{
				// First char of suitable dictionary word
				if (dict_len == 0)
				{
					if (c == *swype)
						found[dict_len++] = c;

					// We checked all words in dictionary,
					// which started with the same letter, can stop
					else if (c > *swype)
						break;

					// Dictionary word starts with other letter
					else
						dict_len = -1;
				}
				
				// Inside of suitable dictionary word
				else
				{
					// Just ckeck, does exists this char in swype?
					if (swype_hash & (1UL << (c - 'a')))
						found[dict_len++] = c;
					else
						dict_len = -1;
				}
			}
		}
		while (c != EOF);

		printf("(%f sec)", (double)(clock() - tstart) / CLOCKS_PER_SEC);
		printf("\nInput another one SWYPE string or Ctrl+D for exit:\n");
	}

	// Close dictionary file
	fclose(dict);

	return 0;
}

