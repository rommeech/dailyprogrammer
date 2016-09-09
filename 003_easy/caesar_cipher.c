#include <stdio.h>
#include <unistd.h>

void usage(char *program_name);
void caesar_cipher_encode(char *in, char *out);
void caesar_cipher_decode(char *in, char *out);

int main(int argc, char **argv)
{
	// Init
	int flg_encode = 0;
	int flg_decode = 0;
	char res[256];
	int c;

	// Parse arguments
	while ((c = getopt(argc, argv, "ed")) != -1)
		switch (c) {
			case 'e':
				flg_encode = 1;
				break;
			case 'd':
				flg_decode = 1;
				break;
			case '?':
				usage(argv[0]);
				return 1;
				break;
		}

	// Check argumets
	if ((flg_decode ^ flg_encode) == 0 || argc - optind != 1) {
		usage(argv[0]);
		return 2;
	}

	// Done

	if (flg_encode) {
		caesar_cipher_encode(argv[optind], res);
		printf("Encoded string: %s\n", res);
	}
	else {
		caesar_cipher_decode(argv[optind], res);
		printf("Decoded string: %s\n", res);
	}

	return 0;
}

void caesar_cipher_encode(char *in, char *out)
{
	printf("Source string: %s\n", in);
	while (*in != '\0')
	{
		if (*in >= 'a' && *in <= 'z') {
			*out = 'a' + ((*in) + 2 - 'a') % ('z' - 'a' + 1);
		}
		else if (*in >= 'A' && *in <= 'Z') {
			*out = 'a' + ((*in) + 2 - 'A') % ('z' - 'a' + 1);
		}
		else {
			*out = *in;
		}

		out++;
		in++;
	}
	*out++ = '\0';
}

void caesar_cipher_decode(char *in, char *out)
{
	printf("Source string: %s\n", in);
	while (*in != '\0')
	{
		if (*in >= 'a' && *in <= 'z') {
			*out = 'z' - ('z' - (*in) + 2) % ('z' - 'a' + 1);
		}
		else if (*in >= 'A' && *in <= 'Z') {
			*out = 'z' - ('Z' - (*in) + 2) % ('z' - 'a' + 1);
		}
		else {
			*out = *in;
		}

		out++;
		in++;
	}
	*out++ = '\0';
}

void usage(char *program_name)
{
	printf("Usage: %s <-d|-e> <text>\n", program_name);
}

