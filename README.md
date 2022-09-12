# Personal Project: C Program to Efficiently Free Dynamically Allocated Memory
---

## Description
---
   This program collects a list of all malloc'd/calloc'd/realloc'd
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

*To be compiled with a C program. I'll be grateful for any bug report(s) sent to greenbel.chibuike@gmail.com*

1. Create an instance of a stuct of type mallocd_t. For example:
   `mallocd_t mall_adds;`
2. Supply this address to the program like so: `mallocd_adds(&mall_adds, type);`

   where mall_adds is a struct of type mallocd_t, and 'type' is a string whose
   characters point to the type of malloc'd pointers supplied as optional
   arguments, if any.

   The characters in 'type' must be one or more of:
   * 'c' indicating a pointer to char
   * 'i' indicating a pointer to int
   * 'p' indicating a pointer to pointer to char.

   The optional parameters expect pointers of one or more of the three types
   listed above. If no pointers are supplied, 'type' must be NULL.
3. Anytime an address is malloc'd, it should be supplied to the program like so:
   `mallocd_t(NULL, type, [addresses])` where 'addresses' is one or more acceptable
   pointer to be stored.
4. When the user is ready to free addresses:
   * if all tracked addresses are to be freed, the user calls free_mallocd() like so:
     `free_mallocd(skip, [addresses]);` where 'skip' is a string whose characters point
     to the type of malloc'd pointers supplied as optional arguments, if any.
     The character convention is as described for 'type'.
     These pointers, if any, represent malloc'd addresses to skip freeing;
     and 'addresses' is one or more pointers of acceptable type to skip freeing.
   * for example:
     a. to free all saved addresses except one stored in a pointer to char 'ptc', the
     function would be called like so: `free_mallocd("c", ptc);`
     b. if we had a pointer to int, 'pti', to skip freeing in addition to 'ptc',
     the function would be called like so: `free_mallocd("ci", ptc, pti);` or
     `free_mallocd("ic", pti, ptc);`
     c. to free all saved addresses without skipping any, the function would be called like so:
     `free_mallocd(NULL);`

## No
