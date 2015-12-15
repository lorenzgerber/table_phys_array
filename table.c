/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). TillÃ¥telse ges fÃ¶r anvÃ¤ndning 
 * pÃ¥ kurserna i Datastrukturer och algoritmer vid UmeÃ¥ Universitet. All annan 
 * anvÃ¤ndning krÃ¤ver fÃ¶rfattarens tillstÃ¥nd.
 */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 1000
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table.h"







/* Creates a table.
 *  compare_function - Pointer to a function that is called for comparing
 *                     two keys. The function should return <0 if the left
 *                     parameter is smaller than the right parameter, 0 if
 *                     the parameters are equal, and >0 if the left
 *                     parameter is larger than the right item.
 * Returns: A pointer to the table. NULL if creation of the table failed. */
Table *table_create(){
    MyTable *t = calloc(sizeof (MyTable),1);
    if (!t)
        return NULL;
    // assign array
    t->values=calloc(ARRAY_SIZE,sizeof(void *));
    return t;
}



/* Install a memory handling function responsible for removing a value when removed from the table
 *  table - Pointer to the table.
 *  freeFunc- Pointer to a function that is called for  freeing all
 *                     the memory used by values inserted into the table*/
void table_setValueMemHandler(Table *table,ValueFreeFunc *freeFunc){
    MyTable *t = (MyTable*)table;
    t->valueFree=freeFunc;
}

/* Determines if the table is empty.
 *  table - Pointer to the table.
 * Returns: false if the table is not empty, true if it is. */
bool table_isEmpty(Table *table){

    //loop through the whole array and check if all Null pointers
    MyTable *t = (MyTable*)table;

    for ( int pos = 0; pos < ARRAY_SIZE; pos++){
        if(*(t->values + pos)){
            return 0;
        }
    }
    return 1;
}



/* Inserts a key and value pair into the table. If memhandlers are set the table takes
 * ownership of the key and value pointers and is responsible for 
 * deallocating them when they are removed.
 *  table - Pointer to the table.
 *  key   - Pointer to the key.
 *  value - Pointer to the value.
 */
void table_insert(Table *table, KEY key, VALUE value){
    MyTable *t = (MyTable*)table;

    // make a new table element
    VALUE *e=malloc(sizeof(VALUE));
    e = value;

    // check if key <= ARRAY_SIZE
    if(key <= ARRAY_SIZE){
        // check if there is already a value at key
        if(*(t->values + key)){
            if(t->valueFree!=NULL){
                t->valueFree(*(t->values + key));
            }
            printf("is not empty\n");
        }
        // set element at index = key
        t->values[key] = e;
    } else {
        printf("key out of array index range\n");
    }
}




/* Finds a value given its key.
 *  table - Pointer to the table.
 *  key   - Pointer to the item's key.
 * Returns: Pointer to the item's value if the lookup succeded. NULL if the
 *          lookup failed. The pointer is owned by the table type, and the
 *          user should not attempt to deallocate it. It will remain valid
 *          until the item is removed from the table, or the table is
 *          destroyed. */
VALUE table_lookup(Table *table, KEY key){
    MyTable *t = (MyTable*)table;

    // table element to work on
    VALUE *i;

    i = *(t->values + key);

    // if pos[key] is NULL return NULL, else, return value
    if (i == NULL) {
        return NULL;
    } else {
        return i;
    }
}




/* Removes an item from the table given its key.
 *  table - Pointer to the table.
 *  key   - Pointer to the item's key.
 */
void table_remove(Table *table, KEY key){
    MyTable *t = (MyTable*)table;

    // if current array pos is empty, skip to next
    if(*(t->values + key)){
        if(t->valueFree!=NULL){
            t->valueFree(*(t->values + key));
        }
        *(t->values + key) = NULL;
    }
}






/* Destroys a table, deallocating all the memory it uses.
 *  table - Pointer to the table. After the function completes this pointer
 *          will be invalid for further use. */
void table_free(Table *table){
    MyTable *t = (MyTable*)table;

    for ( int pos = 0; pos < ARRAY_SIZE; pos++){
        if(*(t->values + pos)){
            if(t->valueFree!=NULL){
                t->valueFree(*(t->values + pos));
            };
        }
    }

    free(t->values);
    free(t);
}
