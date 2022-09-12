#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>

#define BUFSIZE 512

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;


/**
 * struct shell - a data structure for variables whose values
 * need to be accessed and/or modified at different stack levels.
 * @exstat: exit status of last launched program/command.
 * @alias: array of strings representing the alias list.
 * @loop_cnt: keeps record of the number of
 * times the shell's main loop has been run.
 * @name: the program name.
 * @pti: array of two integers storing
 * return values from printfext2() function calls.
 * @fd: file descriptor of the file to write to.
 * @quick_exit: int determining whether to exit the shell loop (0) or not (1).
 * @null_term: int determining whether to
 * null-terminate read input to be parsed by EOF_handler.
 * @quote: an int determining whether to tokenize quoted strings (0) or not (1)
 * @free0: an int determining whether to free str_ar[0] or not (0).
 * @bltin_nm: array of strings storing the names of built-in shell commands.
 * @content: a message string about the struct contents.
 */
typedef struct shell
{
	int exstat;
	char **alias;
	unsigned long int loop_cnt;
	char *name;
	int pti[2];
	int fd;
	int quick_exit;
	int null_term;
	int quote;
	int free0;
	char *bltin_nm[7];
	char *content;
} shell_t;

/**
 * struct mallocd - structure storing static
 * arrays of pointers to malloc'd addresses.
 * @ptc: static array of pointers to char.
 * @pti: static array of pointers to int.
 * @pptc: static array of pointers to pointers to char.
 */
typedef struct mallocd
{
	char *ptc[100];
	int *pti[100];
	char **pptc[100];
} mallocd_t;



char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *_strpbrk(char *s, char *accept);
char *_strstr(char *haystack, char *needle);
char *after_asterisk(char *s2);
char *cap_string(char *);
char *infinite_add(char *n1, char *n2, char *r, int size_r);
char *leet(char *s);
char *next_non_asterisk(char *s1, char c);
char *rot13(char *s);
char *str_adder(char *s1, char *s2, int size_r);
char *string_toupper(char *s);
int _abs(int n);
int _atoi(char *s);
int _is_prime(int dividend, int divisor);
int _isalpha(int c);
int _isdigit(int c);
int _islower(int c);
int _isupper(int c);
int _pow_recursion(int x, int y);
int _putchar(char c);
int _sqrt(int dividend, int divisor);
int _sqrt_recursion(int n);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int str_arrlen(char **arr);
void sort_str(int ac, char *av[]);
void swap_arr(char *arr[], int i, int j);
int _strlen_recursion(char *s);
int add(int a, int b);
int factorial(int n);
int find_sign(char *s);
int idx_num_starts(char *s);
int is_it_palindrome(char *s1, char *s2, int n, int len);
int is_palindrome(char *s);
int is_prime_number(int n);
int mul(int a, int b);
int print_last_digit(int n);
int print_sign(int n);
int pwr(int base, int index);
int strnum_int(char c);
int strnumsum2int(char c1, char c2);
int w_separator(char c);
int wildcmp(char *s1, char *s2);
unsigned int _strspn(char *s, char *accept);
void _print_rev_recursion(char *s);
void _puts(char *str);
void _puts_recursion(char *s);
void jack_bauer(void);
void leet_map(char *c);
void more_numbers(void);
void print_alphabet(void);
void print_alphabet_x10(void);
void print_array(int *a, int n);
void print_chessboard(char (*a)[8]);
void print_diagonal(int n);
void print_diagsums(int *a, int size);
void print_line(int n);
void print_most_numbers(void);
void print_negative(int n);
void print_number(int n);
void print_numbers(void);
void print_positive(int n);
void print_rev(char *s);
void print_square(int size);
void print_times_table(int n);
void print_to_98(int n);
void print_triangle(int size);
void puts2(char *str);
void puts_half(char *str);
void reset_to_98(int *n);
void rev_string(char *s);
void reverse_array(int *a, int n);
void rot13_map(char *c);
void set_string(char **s, char *to);
void swap_int(int *a, int *b);
void times_table(void);
char *create_array(unsigned int size, char c);
char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
int **alloc_grid(int width, int height);
void free_grid(int **grid, int height);
char *argstostr(int ac, char **av);
char **strtow(char *str);
void *malloc_checked(unsigned int b);
char *string_nconcat(char *s1, char *s2, unsigned int n);
void *_calloc(unsigned int nmemb, unsigned int size);
int *array_range(int min, int max);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _memncpy(void *dest, void *src, unsigned int n);
char *add_rev_str(char *str1, char *str2, int len1);
int _atoi2(char c);
char *strdup2(char *str);
char *rev_add_rev(char *s1, char *s2, int revs1, int revs2);
char **mult_rev_str(char *s1, char *s2, int s1eln, int s2len);
char *rev_mult_rev(char *s1, char *s2);

/* Bit manipulation */
unsigned int binary_to_uint(const char *b);
unsigned int str2bin(const char *b);
void print_binary(unsigned long int n);
int get_bit(unsigned long int n, unsigned int index);
int set_bit(unsigned long int *n, unsigned int index);
int clear_bit(unsigned long int *n, unsigned int index);
unsigned int flip_bits(unsigned long int n, unsigned long int m);
int get_endianness(void);

/* File i/o */
ssize_t read_textfile(const char *filename, size_t letters);
int create_file(const char *filename, char *text_content);
int append_text_to_file(const char *filename, char *text_content);
void handle_args(int ac, char *av0);
void handle_close(int fd);
void handle_rdwr(int fdrd, int fdwr, char *buff, char *av1, char *av2);
char *relf(char *av1);
int exitstat(void);
void handle_fd(int fd);
void handle_rderr(int nr);
void handle_wrerr(int nw);
void handle_args2(int ac);
ssize_t getline2(char **line, size_t *n, FILE *stream);

/* printf */
char *c2s(char c, int i, int flag);
int print_posint(int n);
int print_negint(int n);
int _printf(const char *format, ...);
int fprintf2(int fd, const char *format, ...);
int printbin(unsigned int n);
int printc(char arg);
int *prints(char *s);
int printp(void);
int printid(int n);
int printcp(char c);
int printu(unsigned int n);
int printo(unsigned int n);
int printx(unsigned int n);
int printX(unsigned int n);
int printfext1(va_list ap, char c);
int *printfext2(va_list ap, char c);
int *printS(char *s);
int pah(unsigned int n);
int *printptr(void *p);
int num_len(int n);

/* dynamic memory allocation and freeing project */
mallocd_t *mallocd_adds(mallocd_t *mallocd, char *type, ...);
void init_mallocd(mallocd_t *mallocd);
void handle_dup_ptrs(mallocd_t *mallocd);
void free_mallocd(char *skip, ...);
void freeptc(char **ptc);
void freepti(int **pti);
void freepptc(char ***pptc);


/* string operations */
int str2posint(char *str);
void tr2(char **str, char delim);


/* simple shell */
char **str_arr(char *str, const char *delim);
char *strtok2(char *str, const char *delim, int quote);
void handle_realloc(char ***str_ar, int i, int bsize, int *bsize_total);
void handle_realloc2(char **buff,
		unsigned int *old_bsize, unsigned int *bsize, char *line);
size_t handle_strlen(char *str, size_t len, int i, int n);
char *strconcatl(int n, ...);
char *isinPATH(char *cmd_name);
char *isinPATH2(char *cmd_name, char **envp);
char *getenv2(const char *name);
char *getenv3(const char *name, char **envp);
int rellocate_env(const char *name, const char *val,
		int edit_idx, int cflag, char ***envp, int *free);
int handle_dpmall(char **buff);
void handle_dpfree(char ***sarr);
void handle_free(char *type, int flag, ...);
int edit_env(char *env, const char *value, int edit_idx);
int handle_name_val(const char *name, const char *val);
int setenv2(char **sarr, char ***envp,
		int *status __attribute__((unused)), int *free);
int del_env(const char *name, int edit_idx, char ***envp, int *free);
int unsetenv2(char **sarr, char ***envp,
		int *status __attribute__((unused)), int *free);
void abs_srch(char ***sarr, char **envp);
int rel_srch(char *cmd);
char **in_parser(char *line, char *envp[], char **bltin_nm, int *n);
int launch_builtins(char **sarr, char ***envp, int n, int *status, int *free);
int launch_other(char **sarr, char **envp);
int launcher(char **str_ar, char ***envp,
		char *bltin_nm[], int *status, int *free);
ssize_t getline3(char **line, size_t *n,
		FILE *stream __attribute__((unused)));
int val_line(char **input);
int exit2(char **sarr, char ***envp __attribute__((unused)),
		int *status, int *free __attribute__((unused)));
typedef void (*sighandler_t)(int);
void sigint_handler(int signum);
int cd2(char **sarr, char ***envp, int *status, int *free);
int char_srch(char *str, char xter);
int parser_launcher(char *line, char ***envp,
		char **bltin_nm, int *b, int *status, int *_free, char *shell_nm);
int _printenv(char **sarr, char ***envp, int *status, int *free);
int alias2(char **sarr, char ***envp __attribute__((unused)),
		int *status __attribute__((unused)), int *free __attribute__((unused)));
int upd_alias_val(char **sarr, char ***alias);
int upd_alias_noval(char **sarr, char ***alias);
int print_alias(char **sarr, char ***alias);
void find_quote(char **ptc, int *n);
void init_shell(shell_t *shell, char *av0);
shell_t *shstruct(shell_t *shell);
int iscmd(char *cmd_name, char **envp);
int mclTTY2(char *shell_nm, int *b, char ***envp,
		int *status, int *_free, char **bltin_nm, char *line);
void psarr(char **sarr, char c);
int handle_mall(void *buff);
void pipe_parser(char *line, char **envp);
void pstr(char *str, char c);
int isscript(char *buff, char *sh);
int is_binsh(char *filename);
int isexec(struct stat *st, char *filename);
int handle_strlen2(char *str);
int is_mult_cmd(char *line);
int is_ORAND(char *str);
int mult_cmd_launcherORAND(char *shell_nm, int *b, char ***envp,
		int *status, int *_free, char **bltin_nm, char *line);



#endif /* MAIN_H */
