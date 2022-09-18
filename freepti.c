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
 * freepti - frees addresses stored in the
 * pointer to int array stored in a mallocd_t struct.
 * @ptc: an array of pointers to int.
 */
void freepti(int **pti)
{
	int i, j, flag = 0;

	for (i = 0; i < 128; i++)
	{
		for (j = 0; pti[j]; j++) /* see if pointer from struct is to be excluded */
		{
			if (pti[j] == mallocd_adds(NULL, NULL)->pti[i])
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
			if (mallocd_adds(NULL, NULL)->pti[i])
			{
				/* free only if not NULL */
				free(mallocd_adds(NULL, NULL)->pti[i]);
				mallocd_adds(NULL, NULL)->pti[i] = NULL; /* then set to NULL */
			}
		}
	}
}
