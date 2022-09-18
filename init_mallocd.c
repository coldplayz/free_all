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
 * init_mallocd - initialzes elements/pointers
 * of the pointer array fields in mallocd to NULL.
 * @mallocd: a struct of type mallocd_t.
 */
void init_mallocd(mallocd_t *mallocd)
{
	int i;

	for (i = 0; i < 128; i++)
	{
		mallocd->ptc[i] = NULL;
		mallocd->pti[i] = NULL;
		mallocd->pptc[i] = NULL;
	}
}
