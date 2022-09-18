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


mallocd_t *mallocd_adds(mallocd_t *mallocd, char *type, ...);
void init_mallocd(mallocd_t *mallocd);
void handle_dup_ptrs(mallocd_t *mallocd);
void free_mallocd(char *skip, ...);
void freeptc(char **ptc);
void freepti(int **pti);
void freepptc(char ***pptc);



/**
 * free_mallocd - free [malloc'd] addresses in a mallocd_t struct.
 * @skip: directive characters for supplied optional pointers to skip freeing.
 *
 * Notes: the characters of skip must follow this order in writing them: "cip".
 * This is to enable the function call va_arg() at the rigth time.
 */
void free_mallocd(char *skip, ...)
{
	va_list ap;
	int i, *pti[10];
	char *ptc[10], **pptc[10];

	for (i = 0; i < 10; i++) /* initialize exclusion arrays */
	{
		pti[i] = NULL;
		ptc[i] = NULL;
		pptc[i] = NULL;
	}

	va_start(ap, skip);
	if (skip)
	{
		for (i = 0; *skip; i++) /* populate ptc exclusion list/array */
		{
			if (*skip == 'c')
			{
				skip++;
				ptc[i] = va_arg(ap, char *);
			}
			else
			{
				break;
			}
		}

		for (i = 0; *skip; i++) /* populate pti exclusion list/array */
		{
			if (*skip == 'i')
			{
				skip++;
				pti[i] = va_arg(ap, int *);
			}
			else
			{
				break;
			}
		}

		for (i = 0; *skip; i++) /* populate pptc exclusion list/array */
		{
			if (*skip == 'p')
			{
				skip++;
				pptc[i] = va_arg(ap, char **);
			}
			else
			{
				break;
			}
		}
	}

	va_end(ap);

	freepti(pti);
	freeptc(ptc);
	freepptc(pptc);

	/* reset pointer indices */
	mallocd_adds(NULL, NULL)->ci = 0;
	mallocd_adds(NULL, NULL)->ii = 0;
	mallocd_adds(NULL, NULL)->pi = 0;
}
