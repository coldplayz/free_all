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
 * freeptc - frees addresses stored in the
 * pointer to char array stored in a mallocd_t struct.
 * @ptc: an array of pointers to char.
 */
void freeptc(char **ptc)
{
	int i, j, flag = 0;

	for (i = 0; i < 128; i++)
	{
		for (j = 0; ptc[j]; j++) /* see if pointer from struct is to be excluded */
		{
			if (ptc[j] == mallocd_adds(NULL, NULL)->ptc[i])
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
			if (mallocd_adds(NULL, NULL)->ptc[i])
			{
				/* free only if not NULL */
				free(mallocd_adds(NULL, NULL)->ptc[i]);
				mallocd_adds(NULL, NULL)->ptc[i] = NULL; /* then set to NULL */
			}
		}
	}
}
