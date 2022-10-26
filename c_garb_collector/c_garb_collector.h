#ifndef C_GARB_COLLECTOR_H
#define C_GARB_COLLECTOR_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * struct addr_node_s - hash table linked list node type.
 * @addr: malloc'd address to manage.
 * @next: the next node in the list.
 */
typedef struct addr_node_s
{
	void *addr;
	struct addr_node_s *next;
} addr_node_t;


void mallocd_adds(void **ptv);
int hash(void *addr);
void insert(addr_node_t **list_head_addr, addr_node_t *new_node);
addr_node_t **supply_hash_table(addr_node_t **ht);
void free_adds(void **exclusion_list);
int list_len(void **arr);
void reset_head(addr_node_t **list_head, addr_node_t *excluded_node);

#endif /* C_GARB_COLLECTOR_H */
