/**
 * @author : xiaozhuai
 * @date   : 17/3/16
 */

#include "ini_parser.h"

INI_ITEMS* alloc_ini_items(int max_item_size){
    if(max_item_size <= 0) return NULL;  // no items?
    else
        return (INI_ITEMS*)malloc(
                sizeof(INI_ITEMS) +                      // the items list, it has at least one item
                sizeof(INI_ITEM) * (max_item_size-1)     // more items
        );
}

void free_ini_items(INI_ITEMS* items){
    if(items != NULL) free(items);
}

bool ini_parse(INI_ITEMS *items, char *file_name) {
    char buf[MAX_LINE_SIZE];
    char tmpKey[MAX_LINE_SIZE];
    char tmpValue[MAX_LINE_SIZE];

    items->size = 0;

    FILE* fp;

    if ((fp = fopen(file_name, "r")) == NULL) return false;

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        if (sscanf(buf, "%s = %s", tmpKey, tmpValue) == 2) {
            
            if(strlen(tmpKey)>MAX_KEY_SIZE-1 || strlen(tmpValue)>MAX_VALUE_SIZE-1){
                fclose(fp);
                return false;
            }

            strcpy(items->items[items->size].key,   tmpKey);
            strcpy(items->items[items->size].value, tmpValue);
            ++items->size;
        }
    }

    fclose(fp);
    return true;
}

char* ini_get(INI_ITEMS* items, char* key)
{
    //Check to see if items exist
    if (items->size == 0)
        return NULL;

    for (int i = 0; i < items->size; ++i)
        if (strcmp(key, items->items[i].key) == 0)
            return items->items[i].value;

    return NULL;
}