#include "table.h"
#include <stdio.h>

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
    table_insert(table, 12, value1);
    table_insert(table, 3, value2);
    table_insert(table, 3, value3);
    table_remove(table, 12);
    table_insert(table, 12, value2);
    printf("%s\n", (char*)(table_lookup(table, 12)));
    printf("%s\n", (char*)(table_lookup(table, 3)));
    if(table_lookup(table, 3)){
        printf("there is a value\n");
    } else {
        printf("is empty\n");
    }
    table_free(table);
    return 0;
}
