# ini_parser

A super fast ini parser writen in C


author : xiaozhuai

email : 798047000@qq.com

# example

you can find this in example.c

``` c
#include <stdio.h>
#include "ini_parser.h"

int main(int argc, char** argv) {

    if(argc <= 1){
        printf(
            "please define the param of ini file path\n"
            "usage: ini_parse [path]\n"
        );
        return 1;
    }

    char* path = argv[1];

    /**
     * alloc a container for items
     */
    INI_ITEMS* items = alloc_ini_items(20);

    /**
     * parse ini file
     */
    if(ini_parse(items, path)){

        /**
         * go through all the key-value
         */
        for(int i = 0; i < items->size; ++i){
            printf("%s : %s\n", items->items[i].key, items->items[i].value);
        }

        /**
         * get value by key
         */
        printf("name is: %s\n", ini_get(items, "name"));

    }else{
        printf("parse ini file err, maybe file not found or something else\n");
    }


    /**
     * do not forget to free the items, use free_ini_items(INI_ITEMS*) or just use free(void*)
     */
    free_ini_items(items);

    return 0;
}
```

# Build

``` bash
$ cd /path/to/ini_parser
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./ini_parser ../example.ini
```

Now, enjoy!     : )

# How it works

Yes, it's such an easy code. But what I am to talk about is a trick in this project.

Think about these code in `ini_parser.h`

``` c

typedef struct ini_item {
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
}INI_ITEM;

typedef struct ini_items {
    int size;
    INI_ITEM items[1];
}INI_ITEMS;

```

Why the `struct ini_items` has a member `INI_ITEM items[1]` but not `INI_ITEM items*` ?

Let's find some thing more in `ini_parser.c`

``` c
INI_ITEMS* alloc_ini_items(int max_item_size){
    if(max_item_size <= 0) return NULL;  // no items?
    else
        return (INI_ITEMS*)malloc(
                sizeof(INI_ITEMS) +                      // the items list, it has at least one item
                sizeof(INI_ITEM) * (max_item_size-1)     // more items
        );
}
```

If we use `INI_ITEM items*`, the code will be

``` c
INI_ITEMS* alloc_ini_items(int max_item_size){
    if(max_item_size <= 0) return NULL;
    else{
        INI_ITEMS* items = (INI_ITEMS*) malloc(sizeof(INI_ITEMS));
        items->items = (INI_ITEM*) malloc(sizeof(INI_ITEM)*max_item_size);
        return items;
    }
}
```

Ok, it's clear. The diffrences between two way is about memery space.

The `INI_ITEM items[1]` way will always alloc a contiguous memory space, but the other not.

That will be more efficient.