#include "c_garb_collector.h"


/**
 * free_adds - frees all saved addresses not in exclusion_list.
 * @exclusion_list: an array of memory addresses to skip freeing.
 *
 * Note: the exclusion list must be NULL-terminated. It is the
 * caller's responsility to ensure that the addresses are not actually NULL.
 * If there is no address to skip, then the caller should pass NULL to free all
 */
void free_adds(void **exclusion_list)
{
	int i, j, do_free = 1, listlen = list_len(exclusion_list);
	addr_node_t *tmp, *tmp2, **ht;

	ht = supply_hash_table(NULL);
	for (i = 0; i < 128; i++)
	{
		/* Traverse hash table */
		if (ht[i] == NULL)
		{
			/* Empty list */
			continue;
		}

		tmp = ht[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			if (listlen)
			{
				for (j = 0; exclusion_list[i]; j++)
				{
					if (tmp->addr == exclusion_list[j])
					{
						do_free = 0;
						listlen--;
						reset_head(&ht[i], tmp);
						break;
					}
				}
			}

			if (do_free)
			{
				free(tmp->addr);
				free(tmp);
			}
			do_free = 1; /* reset the flag if it was last set to 0 */

			tmp = tmp2;
		}
	}
}



/**
 * list_len - computes the length of a NULL-terminated array.
 * @arr: the array to compute the length of.
 *
 * Return: the number of elements in arr.
 */
int list_len(void **arr)
{
	int i, len = 0;

	if (!arr)
	{
		return (len);
	}

	for (i = 0; arr[i]; i++)
	{
		len++;
	}

	return (len);
}


/**
 * reset_head - recreates the linked list when performing exclusion freeing.
 * @list_head: address of hash table index containing list head.
 * @excluded_node: a node to skip freeing. To be used in
 * re-constituting a new list since not all addresses are freed.
 */
void reset_head(addr_node_t **list_head, addr_node_t *excluded_node)
{
	excluded_node->next = *list_head;
	*list_head = excluded_node;
}
