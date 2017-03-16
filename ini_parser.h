/**
 * @author : xiaozhuai
 * @date   : 17/3/16
 */

#ifndef EZERFILESERVER_INI_READER_H_H
#define EZERFILESERVER_INI_READER_H_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE          1024          // max chars in line
#define MAX_KEY_SIZE           60            // max key chars
#define MAX_VALUE_SIZE         60            // max value chars

typedef struct ini_item {
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
}INI_ITEM;

typedef struct ini_items {
    int size;
    INI_ITEM items[1];
}INI_ITEMS;




/**
 * alloc a container for items
 *
 * @param max_item_size  max size of items
 */
INI_ITEMS* alloc_ini_items(int max_item_size);


/**
 * free items
 *
 * @param items container
 */
void free_ini_items(INI_ITEMS* items);



/**
 * Parse a configuration file
 *
 * @param   items container
 * @param	fileName The name of the file to parse
 * @return	true on success or false on failure
 */
bool ini_parse(INI_ITEMS *items, char *file_name);


/**
 * Get value by key
 *
 * @param	items container
 * @param	char *key The key of the config item
 * @return	value, if not exist will return NULL
 */
char* ini_get(INI_ITEMS* items, char* key);




#endif //EZERFILESERVER_INI_READER_H_H

