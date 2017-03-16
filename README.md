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


