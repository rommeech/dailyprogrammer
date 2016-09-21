#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int i, j, is_ok;

	FILE *dict= fopen(DICT_FILE, "r");

	while (scanf("%s", swype) != EOF)
	{
		printf("Input: %s\n", swype);

		// Prepare
		swype_len = strlen(swype);

		// Build simple hash of swype word for performance.
		// Actually this is long number, but we need only 26 bites
		// for 26 letters.
		// Each bite containt 1 if char exists in word, 0 - if not.
		for (i = 0; i < swype_len; i++)
			swype_hash |= (1UL << (swype[i] - 'a'));

		//printf("Hash: %lu\n", swype_hash); return 0;

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

				//printf("Found=%s, dict_len=%d\n", found, dict_len);

				// We do not need too short
				// And last chars should be equal
				if (dict_len >= DICT_WORD_MIN_LEN &&
					swype[swype_len-1] == found[dict_len-1]
				) {
					/*
					printf(
						"Maybe: %s | %d %c | %d %c\n",
						found,
						swype_len,
						swype[swype_len-1],
						dict_len,
						found[dict_len-1]
					);
					*/

					// Ok, lets check, may be this is out word
					// We know that first and last letters are equal
					// and don't need check it
					
					/*
					is_ok = 1;
					for(i = 1; is_ok && i < dict_len-1; i++) {
						is_ok = 0;
						for (j = i-1; !is_ok && j < swype_len-1; j++) {
							printf("Check: i=%d/%c j=%d/%c\n", i, found[i], j, swype[j]);
							is_ok = found[i] == swype[j] ? 1 : 0;
						}
					}
					*/

					i = 1;
					for (j = 1; i < dict_len-1 && j < swype_len-1; j++) {
						//printf("Check: i=%d/%c j=%d/%c\n", i, found[i], j, swype[j]);
						if (found[i] == swype[j] || found[i] == swype[j-1]) {
							i++;
						}
					} 

					//printf("Out word: %s => %d|%d\n--------------------\n", found, i, swype_len);
					
					// Got it?
					if (i >= dict_len-1)
						printf("%s ", found);
				}
				
				// Reset for next dictionary word iteration
				dict_len = 0;
			}
			
			// This is letter and inside of suitable word
			else if (c >= 'a' && c <= 'z' && dict_len >= 0)
			{
				// First char of suitable word
				if (dict_len == 0)
				{
					if (c == *swype) {
						//printf("First letter: %c\n", c);
						found[dict_len++] = c;
					}

					// We checked all words id dictionary, can stop
					else if (c > *swype) {
						//printf("First letter: %c, break\n", c);
						break;
					}

					// Dictionary word starts with other char
					else
						dict_len = -1;
				}
				
				// Inside of suitable word
				else
				{
					if (swype_hash & (1UL << (c - 'a'))) {
						//printf("Letter number %i: %c\n", dict_len+1, c);
						found[dict_len++] = c;
					}
					else
						dict_len = -1;
				}
			}
		}
		while (c != EOF);

		printf("----------------\n");
		printf("Intut another one SWYPE string or Ctrl+D for exit\n");
	}

	// Close descriptors
	fclose(dict);

	return 0;
}

