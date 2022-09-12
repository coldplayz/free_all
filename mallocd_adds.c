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
 * mallocd_adds - stores a pointer to a
 * mallocd_t object and modifies the addresses it stores.
 * @mallocd: pointer to the mallocd_t struct to store and/or modify.
 * @type: string consisting of directive characters
 * that indicate the type of the optional pointers supplied, where:
 * 'c' indicates pointer to char type;
 * 'i' indicates pointer to int type;
 * 'p' indicates pointer to pointer to char type; and
 * NULL signifies no pointer to add/store.
 *
 * Note: to just access the stored pointer (i.e. you do not intend
 * updating mallocd, and/or adding a new address), call mallocd_adds(NULL, NULL).
 * Return: address of the currently stored mallocd_t structure.
 */
mallocd_t *mallocd_adds(mallocd_t *mallocd, char *type, ...)
{
	static mallocd_t *ptmt;
	int i, j, n, *pti = NULL;
	mallocd_t *ptmt2;
	va_list ap;
	char *ptc = NULL, **pptc = NULL;
	static int ci, ii, pi;

	ptmt2 = mallocd;
	if (ptmt2) /* a new object to store */
	{
		ptmt = ptmt2;
		ci = 0;
		ii = 0;
		pi = 0;
		init_mallocd(ptmt);
	}

	if (!type)
	{
		return (ptmt);
	}
	n = _strlen(type);

	va_start(ap, type);
	for (i = 0; i < n; i++)
	{
		switch (type[i])
		{
			case 'c':
				for (j = 0; ci <= 99; i++)
				{
					if (!ptmt->ptc[ci] && (ci <= 99))
					{
						ptc = va_arg(ap, char *);
						ptmt->ptc[ci] = ptc;
						ci++;
						break;
					}
					ci++;
				}

				if (ci > 99)
				{
					fprintf(stderr, "mallocd: ptc: Array full\n");
				}
				break;
			case 'i':
				for (j = 0; ii <= 99; i++)
				{
					if (!ptmt->pti[ii] && (ii <= 99))
					{
						pti = va_arg(ap, int *);
						ptmt->pti[ii] = pti;
						ii++;
						break;
					}
					ii++;
				}

				if (ii > 99)
				{
					fprintf(stderr, "mallocd: pti: Array full\n");
				}
				break;
			case 'p':
				for (j = 0; pi <= 99; i++)
				{
					if (!ptmt->pptc[pi] && (pi <= 99))
					{
						pptc = va_arg(ap, char **);
						ptmt->pptc[pi] = pptc;
						pi++;
						break;
					}
					pi++;
				}

				if (pi > 99)
				{
					fprintf(stderr, "mallocd: pptc: Array full\n");
				}
		}
	}

	handle_dup_ptrs(ptmt);

	va_end(ap);

	return (ptmt);
}


/**
 * init_mallocd - initialzes elements/pointers
 * of the pointer array fields in mallocd to NULL.
 * @mallocd: a struct of type mallocd_t.
 */
void init_mallocd(mallocd_t *mallocd)
{
	int i;

	for (i = 0; i < 100; i++)
	{
		mallocd->ptc[i] = NULL;
		mallocd->pti[i] = NULL;
		mallocd->pptc[i] = NULL;
	}
}


/**
 * handle_dup_ptrs - sets duplicate pointers to NULL.
 * @mallocd: a struct object of type mallocd_t.
 */
void handle_dup_ptrs(mallocd_t *mallocd)
{
	int i, j;

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++)
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
	int i, n, *pti[10], flag = 0;
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
}


/**
 * freeptc - frees addresses stored in the
 * pointer to char array stored in a mallocd_t struct.
 * @ptc: an array of pointers to char.
 */
void freeptc(char **ptc)
{
	int i, j, flag = 0;

	for (i = 0; i < 100; i++)
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



/**
 * freepti - frees addresses stored in the
 * pointer to int array stored in a mallocd_t struct.
 * @ptc: an array of pointers to int.
 */
void freepti(int **pti)
{
	int i, j, flag = 0;

	for (i = 0; i < 100; i++)
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


/**
 * freepptc - frees addresses stored in the
 * pointer to pointer to char array stored in a mallocd_t struct.
 * @pptc: an array of pointers to pointers to  char.
 */
void freepptc(char ***pptc)
{
	int i, j, flag = 0;

	for (i = 0; i < 100; i++)
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
