#include <stdio.h>

int main()
{
	char *string = "36bbe50ed96841d10443bcb670d6554f0a34b761be67ec9c4a8ad2c0c44ca42c";
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