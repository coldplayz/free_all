#include "c_garb_collector.h"


/**
 * mallocd_adds - collects and saves malloc'd/calloc'd addresses for freeing.
 * @ptv: a NULL-terminated array of addresses.
 *
 * Note: ptv must be NULL-terminated. It is the caller's
 * responsility to ensure that tha addresses are not actually NULL.
 */
void mallocd_adds(void **ptv)
{
	static addr_node_t *arr[128] = {NULL};
	int i, idx;
	addr_node_t *new_node;

	for (i = 0; ptv[i]; i++)
	{
		idx = hash(ptv[i]);
		new_node = malloc(sizeof(addr_node_t));
		if (!new_node)
		{
			perror("mallocd_adds-malloc");
			exit(EXIT_FAILURE);
		}
		new_node->addr = (void *)ptv[i];

		if (arr[idx] == NULL)
		{
			/* Empty list; add as first item */
			new_node->next = NULL;
			arr[idx] = new_node; /* new node now head of list */
			return;
		}
		else
		{
			/* Linked kist at index position; insert at beginning */
			insert(&arr[idx], new_node);
		}
	}

	supply_hash_table(arr);
}




/**
 * insert - inserts a new node at the start of the linked list.
 * @list_head_addr: the address of the head of the list.
 * @new_node: pointer to the new node.
 *
 * Note: this function handles duplicate addresses.
 */
void insert(addr_node_t **list_head_addr, addr_node_t *new_node)
{
	addr_node_t *tmp;

	tmp = *list_head_addr;
	while (tmp)
	{
		/* Search for duplicate node/address */
		if (tmp->addr == new_node->addr)
		{
			free(new_node);
			return;
		}
		tmp = tmp->next;
	}

	/* Address has not been previously added; now add at start of list */
	new_node->next = *list_head_addr;
	*list_head_addr = new_node; /* new node now head of list */
}


/**
 * hash - returns an index into the hash table, given an address.
 * @addr: the address to be digested into an index.
 *
 * Return: the result of hash digestion - an index.
 */
int hash(void *addr)
{
	int digest;
	unsigned long int ul;

	ul = (unsigned long int)addr;
	digest = ul % 128;

	return (digest);
}
