# ini_parser

[[中文文档](README_CN.md)] [[English README](README.md)]

一个用C写的超级快的ini parser

作者 : xiaozhuai

邮箱 : 798047000@qq.com

# 例子

你可以在 `example.c` 当中找到它

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

# 构建

``` bash
$ cd /path/to/ini_parser
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./ini_parser ../example.ini
```

现在, 开始享受吧!     : )

# 它如何工作

是的，它是一个很简单的代码。 但是我将要说的是这个项目里面的一个小把戏。

让我们来看一下 `ini_parser.h` 里面的代码

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

为什么 `struct ini_items` 有一个叫作 `INI_ITEM items[1]` 的成员而不是叫 `INI_ITEM items*` ?

继续看 `ini_parser.h` 里的代码

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

如果我们使用 `INI_ITEM items*`的话, 代码将会是：

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

现在就很清晰了. 两种方式的差异在于存储空间的不同。

使用`INI_ITEM items[1]`总是会分配连续的存储空间，它将会更加有效率，而另外一种方式则不是这样.


