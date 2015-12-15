#include "table.h"
#include <stdio.h>
#include <stdlib.h>


int *intPtrFromInt(int i){
    int *ip=malloc(sizeof(int));
    *ip=i;
    return ip;
}

int main() {

    Table *table = table_create();
    //table_setValueMemHandler(table, free);
    if(table_isEmpty(table)){
        printf("newly created table is empty\n");
    } else {
        printf("something wrong\n");
    }
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    int *key1 = intPtrFromInt(3);
    int *key2 = intPtrFromInt(12);
    int *key3 = intPtrFromInt(4);
    table_insert(table, key1, value1);
    table_insert(table, key2, value2);
    table_insert(table, key2, value3);
    table_remove(table, key1);
    table_insert(table, key3, value2);
    printf("%s\n", (char*)(table_lookup(table, key1)));
    printf("%s\n", (char*)(table_lookup(table, key3)));
    if(table_lookup(table, key2)){
        printf("there is a value\n");
    } else {
        printf("is empty\n");
    }
    table_free(table);
    return 0;
}

