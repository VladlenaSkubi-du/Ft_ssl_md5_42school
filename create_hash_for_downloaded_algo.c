#include <stdio.h>

int main()
{
	char *string = "e3b7e381115535349b6eb7b36dd8e52496fefff6547c9472c531371c3ebdda53";
	printf("{");
	int i = 0;
	while (i < 64)
	{
		if (i == 62)
			printf("0x%c%c", string[i], string[i + 1]);
		else
			printf("0x%c%c, ", string[i], string[i + 1]);
		i += 2;
		if (i == 32)
			printf("\n");
	}
	printf("}\n");
	return (0);
}