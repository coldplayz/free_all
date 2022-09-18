#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include "main.h"

#define ex (execve("/bin/ls", args, NULL) == (-1))
#define ps(x) (printf("%s\n", (x)))
#define pd(x) (printf("%d\n", (x)))
#define plu(x) (printf("%lu\n", (x)))


/**
 * freepptc - frees addresses stored in the
 * pointer to pointer to char array stored in a mallocd_t struct.
 * @pptc: an array of pointers to pointers to  char.
 */
void freepptc(char ***pptc)
{
	int i, j, flag = 0;

	for (i = 0; i < 128; i++)
	{
		for (j = 0; pptc[j]; j++) /* see if pointer from struct is to be excluded */
		{
			if (pptc[j] == mallocd_adds(NULL, NULL)->pptc[i])
			{
				flag = 1;
			}
		}

		if (flag)
		{
			flag = 0;
			continue; /* do not free */
		}
		else
		{
			if (mallocd_adds(NULL, NULL)->pptc[i])
			{
				/* free only if not NULL */
				free(mallocd_adds(NULL, NULL)->pptc[i]);
				mallocd_adds(NULL, NULL)->pptc[i] = NULL; /* then set to NULL */
			}
		}
	}
}
