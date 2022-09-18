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
 * updating mallocd, and/or adding a new address),
 * call mallocd_adds(NULL, NULL).
 * The mallocd_t struct instance whose address is
 * saved should be declared in the program's main
 * function; this is so that the address remains
 * allocated till program end as main() only returns then.
 * The addresses stored by this program should only be
 * freed using the program's free_mallocd(), instead of
 * the library's free(). Using free() on addresses stored
 * here would result in invalid free when you
 * call free_mallocd() except the said address(es) have been removed.
 * Return: address of the currently stored mallocd_t structure.
 */
mallocd_t *mallocd_adds(mallocd_t *mallocd, char *type, ...)
{
	static mallocd_t *ptmt;
	int i, j, n, *pti = NULL;
	mallocd_t *ptmt2;
	va_list ap;
	char *ptc = NULL, **pptc = NULL;
	static  int saved_ci = -1, saved_ii = -1, saved_pi = -1;

	ptmt2 = mallocd;
	if (ptmt2) /* a new object to store */
	{
		ptmt = ptmt2;
		ptmt->ci = 0;
		ptmt->ii = 0;
		ptmt->pi = 0;
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
		if (type[i] == '+' || type[i] == '-')
		{
			i++; /* move to the directive character index */
		}
		switch (type[i])
		{
			case 'c':
				if (type[i - 1] == '-')
				{
					if (saved_ci != -1)
					{
						ptmt->ptc[saved_ci] = NULL;
						saved_ci = -1; /* reset the saved index */
						break; /* leave the switch statement */
					}
				}
				/* ptmt->ci can be reset on this comment line */
				for (j = 0; ptmt->ci < 128; j++)
				{
					if (!ptmt->ptc[ptmt->ci] && (ptmt->ci < 128))
					{
						if (type[i - 1] == '+')
						{
							saved_ci = ptmt->ci; /* save the index */
						}
						ptc = va_arg(ap, char *);
						ptmt->ptc[ptmt->ci] = ptc;
						ptmt->ci++;
						break;
					}
					ptmt->ci++;
				}

				if (ptmt->ci > 127)
				{
					fprintf(stderr, "mallocd: ptc: Array full\n");
				}
				break;
			case 'i':
				if (type[i - 1] == '-')
				{
					if (saved_ii != -1)
					{
						ptmt->ptc[saved_ii] = NULL;
						saved_ii = -1; /* reset the saved index */
						break; /* leave the switch statement */
					}
				}
				for (j = 0; ptmt->ii < 128; j++)
				{
					if (!ptmt->pti[ptmt->ii] && (ptmt->ii < 128))
					{
						if (type[i - 1] == '+')
						{
							saved_ii = ptmt->ii; /* save the index */
						}
						pti = va_arg(ap, int *);
						ptmt->pti[ptmt->ii] = pti;
						ptmt->ii++;
						break;
					}
					ptmt->ii++;
				}

				if (ptmt->ii > 127)
				{
					fprintf(stderr, "mallocd: pti: Array full\n");
				}
				break;
			case 'p':
				if (type[i - 1] == '-')
				{
					if (saved_pi != -1)
					{
						ptmt->ptc[saved_pi] = NULL;
						saved_pi = -1; /* reset the saved index */
						break; /* leave the switch statement */
					}
				}
				for (j = 0; ptmt->pi < 128; j++)
				{
					if (!ptmt->pptc[ptmt->pi] && (ptmt->pi < 128))
					{
						if (type[i - 1] == '+')
						{
							saved_pi = ptmt->pi; /* save the index */
						}
						pptc = va_arg(ap, char **);
						ptmt->pptc[ptmt->pi] = pptc;
						ptmt->pi++;
						break;
					}
					ptmt->pi++;
				}

				if (ptmt->pi > 127)
				{
					fprintf(stderr, "mallocd: pptc: Array full\n");
				}
		}
	}

	handle_dup_ptrs(ptmt);

	va_end(ap);

	return (ptmt);
}
