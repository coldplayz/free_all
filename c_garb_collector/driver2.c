#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *str;
	void *str2;

	str = malloc(sizeof(char) * 7);
	str2 = (void *)str;
	free(str2);

	return (0);
}
