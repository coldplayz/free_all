# Personal Project: C Program to Efficiently Free Dynamically Allocated Memory
---

## Description
---
   This program collects a list of all malloc'd/calloc'd
   addresses (hereafter collectively referred to as malloc'd addresses)
   supplied to it and safely free's them all together when the user chooses to.

## Syntax
---
```C
mallocd_t *mallocd_adds(mallocd_t *mall_adds, char *type, ...); /* Collects and stores malloc'd pointers */
void free_mallocd(char *skip, ...); /* frees malloc'd addresses supplied to mallocd_adds() */
```

## Usage
---

*To be compiled with a C program. I would love any feedbacks, suggestions and bug report(s).*
*These can be sent to my [email](greenbel.chibuike@gmail.com) at greenbel.chibuike@gmail.com*

1. Create an instance of a struct of type mallocd_t in your program's `main()` function. For example:
   `mallocd_t mall_adds;`
2. Still in main, supply it's address to the program like so: `mallocd_adds(&mall_adds, type);`

   where mall_adds is a struct of type mallocd_t, and 'type' is a string whose
   characters point to the type of malloc'd pointers supplied as optional
   arguments, if any. For this step, 'type' should be NULL (except you want to save a malloc'd address already).

   The characters in 'type' must be one or more of:
   * 'c' indicating a pointer to char
   * 'i' indicating a pointer to int
   * 'p' indicating a pointer to pointer to char.

   The optional parameters expect pointers of one or more of the three types
   listed above. If no pointers are supplied, 'type' must be NULL.
3. Anytime an address is malloc'd, it should be supplied to the program like so:
   `mallocd_adds(NULL, type, [addresses])` where 'addresses' is one or more acceptable
   pointer to be stored. For example, to store a pointer to char named 'ptc', the function would
   be called like so: `mallocd_adds(NULL, "c", ptc);`. And to store a pointer to char,
   pointer to int and pointer-to-pointer to char named 'ptc', 'pti', and 'pptc' respectively,
   we go: `mallocd_adds(NULL, "cip", ptc, pti, pptc);`.
   
4. When the user is ready to free addresses, the user calls free_mallocd() like so:
   `free_mallocd(skip, [addresses]);` where 'skip' is a string whose characters point
   to the type of malloc'd pointers supplied as optional arguments, if any.
   The character convention for 'skip' is as described for 'type'.
   These pointers, if any, represent malloc'd addresses to skip freeing;
   and 'addresses' is one or more pointers of acceptable type to skip freeing. For example:
   * to free all saved addresses except one stored in a pointer to char 'ptc', the
     function would be called like so: `free_mallocd("c", ptc);`
   * if we had a pointer to int, 'pti', to skip freeing in addition to 'ptc',
     the function would be called like so: `free_mallocd("ci", ptc, pti);` or
     `free_mallocd("ic", pti, ptc);`
   * to free all saved addresses without skipping any, the function would be called like so:
     `free_mallocd(NULL);`

## Note:
---

This program should not be used for addresses that would be free'd using the standard's `free()`.
This includes memory allocated by the standard's `realloc()`. Supplying addresses that would be free'd
using `free()` to `mallocd_adds()` would result in invalid free as seen during the use of valgrind's mem check.

The total number of addresses, of each currently supported pointer type, that can be stored is 128 at the moment.
When the storage buffer for any of the types gets full (of 'unfreed' addresses), a warning will be sent to stderr
to indicate this. I'm currently working on improving that limit in a way that doesn't adversely affect program speed.

Combining the use of smart positioning of `free_mallocd()` and its pointer-skipping feature can help mitigate the
negative effects of the current limit. Once `free_mallocd()` is called, buffer space is also freed to accomodate more pointers.

This program handles duplicate pointers (from passing an address more than once to `mallocd_adds()`) and multiple calls to
`free_mallocd()`, provided the restriction on the use of the standard's `free()` is honoured.

Despite the handling of duplicate pointers, it is adviced to perform malloc()/calloc() and `malloc_adds()` calls atomically. That
means, once a call to `malloc()` or `calloc()` is successfull, the returned address should immediately be supplied to `mallocd_adds()`.
