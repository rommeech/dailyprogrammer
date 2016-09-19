#include <stdio.h>
#include <ctype.h>

/*
Simple anagram detector, see:
https://www.reddit.com/r/dailyprogrammer/comments/52enht/20160912_challenge_283_easy_anagram_detector/

This version is not corresponding with requirements (see output format)
and should be refactored.
*/

#define LETTERS_CNT 26

int main()
{
	char c;
	int i;
	int input[LETTERS_CNT], output[LETTERS_CNT];
	int is_out;
	int is_ang;

	// Init
	is_out = 0;
	is_ang = 0;
	for (i = 0; i < LETTERS_CNT; i++) {
		input[i] = 0;
		output[i] = 0;
	}

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			is_ang = 1;
			for (i = 0; i < LETTERS_CNT; i++)
				if (input[i] != output[i])
					is_ang = 0;

			if (is_ang)
				printf(" ... is an anagram\n");
			else
				printf(" ... is NOT an anagram\n");

			for (i = 0; i < LETTERS_CNT; i++) printf("%i", input[i]);
			printf("\n");
			for (i = 0; i < LETTERS_CNT; i++) printf("%i", output[i]);
			printf("\n");

			// Re-init for next couple of words (or phrases)
			is_out = 0;
			is_ang = 0;
			for (i = 0; i < LETTERS_CNT; i++) {
				input[i] = 0;
				output[i] = 0;
			}
		}
		else
		{
			if(c >= 'A' && c <= 'Z')
				c = tolower(c);

			if(c >= 'a' && c <= 'z') {
				if (is_out)
					output[c-'a']++;
				else
					input[c-'a']++;
			}
			else if (c == '?')
				is_out = 1;
		}
	}

	return 0;
}

