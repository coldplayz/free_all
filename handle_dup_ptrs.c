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
 * handle_dup_ptrs - sets duplicate pointers to NULL.
 * @mallocd: a struct object of type mallocd_t.
 */
void handle_dup_ptrs(mallocd_t *mallocd)
{
	int i, j;

	for (i = 0; i < 128; i++)
	{
		for (j = 0; j < 128; j++)
		{
			if (j != i) /* skips checking value at index 'i' */
			{
				if (mallocd->ptc[i] == mallocd->ptc[j])
				{
					mallocd->ptc[j] = NULL; /* set duplicate values to NULL */
				}

				if (mallocd->pti[i] == mallocd->pti[j])
				{
					mallocd->pti[j] = NULL; /* set duplicate values to NULL */
				}

				if (mallocd->pptc[i] == mallocd->pptc[j])
				{
					mallocd->pptc[j] = NULL; /* set duplicate values to NULL */
				}
			}
		}
	}
}
