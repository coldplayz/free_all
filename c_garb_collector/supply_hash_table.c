#include "c_garb_collector.h"


/**
 * supply_hash_table - yields the saved addr_node_t hash table.
 * @ht: the hash table to yield.
 *
 * Note: if ht is NULL, the hash table,
 * saved as ht_cpy, is not updated before being returned.
 * Return: the saved hash table.
 */
addr_node_t **supply_hash_table(addr_node_t **ht)
{
	static addr_node_t **ht_cpy;
	static int n = 0;

	if (n == 0)
	{
		ht_cpy = NULL;
		n = 1;
	}

	if (ht)
	{
		/* Save/update mode */
		ht_cpy = ht;
	}

	return (ht_cpy);
}
