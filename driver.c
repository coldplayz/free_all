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

void test(void);

int main(void)
{
	mallocd_t mallocd;
	int *pti;
	char *ptc, **pptc;

	mallocd_adds(&mallocd, NULL);

	pti = malloc(8);
	mallocd_adds(NULL, "i", pti);

	ptc = malloc(2);
	mallocd_adds(NULL, "c", ptc);
	mallocd_adds(NULL, "c", ptc);

	pptc = malloc(16);
	mallocd_adds(NULL, "p", pptc);

	test();
	free_mallocd(NULL);

	return (0);
}

void test(void)
{
	char *ptc;

	ptc = malloc(1024);
	mallocd_adds(NULL, "c", ptc);
	ptc[0] = 's';
	free_mallocd(NULL);
}
