/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). TillÃ¥telse ges fÃ¶r anvÃ¤ndning 
 * pÃ¥ kurserna i Datastrukturer och algoritmer vid UmeÃ¥ Universitet. All annan 
 * anvÃ¤ndning krÃ¤ver fÃ¶rfattarens tillstÃ¥nd.
 */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 20000
#endif
#include <stdbool.h>
#include "table.h"
#include "array.h"
#include <string.h>








/* Creates a table.
 *  compare_function - Pointer to a function that is called for comparing
 *                     two keys. The function should return <0 if the left
 *                     parameter is smaller than the right parameter, 0 if
 *                     the parameters are equal, and >0 if the left
 *                     parameter is larger than the right item.
 * Returns: A pointer to the table. NULL if creation of the table failed. */
Table *table_create(CompareFunction *compare_function){
    MyTable *t = calloc(sizeof (MyTable),1);
    if (!t)
        return NULL;
    t->values=array_create(1, 0, ARRAY_SIZE);
    array_setMemHandler(t->values, free);
    t->cf = compare_function;
    return t;
}

/* Install a memory handling function responsible for removing a key when removed from the table
 *  table - Pointer to the table.
 *  freeFunc- Pointer to a function that is called for  freeing all
 *                     the memory used by keys inserted into the table*/
void table_setKeyMemHandler(Table *table, KeyFreeFunc *freeFunc){
    MyTable *t = (MyTable*)table;
    t->keyFree=freeFunc;
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

    // get loop boundaries for array
    array *aHigh = array_high(t->values);
    array *aLow  = array_low(t->values);

    int high = *((int*)array_inspectValue(aHigh,0));
    int low = *((int*)array_inspectValue(aLow,0));
    array_free(aHigh);
    array_free(aLow);

    for ( int pos = low; pos < high; pos++){
        if(array_hasValue(t->values, pos)){
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
    TableElement *e=malloc(sizeof(TableElement));
    e->key = key;
    e->value = value;

    // table element to work on
    TableElement *i;

    // get loop boundaries for array
    array *aHigh = array_high(t->values);
    array *aLow  = array_low(t->values);

    int high = *((int*)array_inspectValue(aHigh,0));
    int low = *((int*)array_inspectValue(aLow,0));
    array_free(aHigh);
    array_free(aLow);

    // loop through the table/array until either the same key found
    // or an emtpy space found
    for ( int pos = low; pos < high; pos++){

        // get TableElement of current array pos
        i = array_inspectValue(t->values,pos);

        // if current array pos is empty, put in new element and break
        if(i == NULL){
            array_setValue(t->values,e,pos);
            break;
        }

        // if the key of the current table element is the same as the new
        // put the new element in place of the old and break
        if (t->cf(i->key,key)==0){
            array_setValue(t->values,e,pos);
            break;
        }


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

    // get loop boundaries for array
    array *aHigh = array_high(t->values);
    array *aLow  = array_low(t->values);

    int high = *((int*)array_inspectValue(aHigh,0));
    int low = *((int*)array_inspectValue(aLow,0));
    array_free(aHigh);
    array_free(aLow);

    // table element to work on
    TableElement *i;

    // loop through the table/array until the same key found
    // or end of array reached
    for ( int pos = low; pos < high; pos++) {

        // get TableElement of current array pos
        i = array_inspectValue(t->values, pos);

        // if current array pos is empty, put in new element and break
        if (i == NULL) {
            continue;
        }

        // if the key of the current table element is the same as the
        // lookup key, return the value
        if (t->cf(i->key, key) == 0) {
            return i->value;
        }

    }

    return NULL;
}




/* Removes an item from the table given its key.
 *  table - Pointer to the table.
 *  key   - Pointer to the item's key.
 */
void table_remove(Table *table, KEY key){
    MyTable *t = (MyTable*)table;

    // table element to work on
    TableElement *i;

    // get loop boundaries for array
    array *aHigh = array_high(t->values);
    array *aLow  = array_low(t->values);

    int high = *((int*)array_inspectValue(aHigh,0));
    int low = *((int*)array_inspectValue(aLow,0));
    array_free(aHigh);
    array_free(aLow);


    // loop through the table/array until all keys found
    // or all positions visited
    for ( int pos = low; pos < high; pos++){

        // get TableElement of current array pos
        i = array_inspectValue(t->values,pos);

        // if current array pos is empty, skip to next
        if(i == NULL){
            continue;
        }

        // if the key of the current table element is the same as the one
        // one to remove, set to NULL and go on
        if (t->cf(i->key,key)==0){

            array_setValue(t->values, NULL, pos);
        }

    }


}






/* Destroys a table, deallocating all the memory it uses.
 *  table - Pointer to the table. After the function completes this pointer
 *          will be invalid for further use. */
void table_free(Table *table){
    MyTable *t = (MyTable*)table;
    TableElement *i;

    // get loop boundaries for array
    array *aHigh = array_high(t->values);
    array *aLow  = array_low(t->values);

    int high = *((int*)array_inspectValue(aHigh,0));
    int low = *((int*)array_inspectValue(aLow,0));
    array_free(aHigh);
    array_free(aLow);

    for (int pos = low; pos < high; pos++){
        i = array_inspectValue(t->values, pos);

        if(array_hasValue(t->values, pos)){
            if(t->keyFree!=NULL) {
                t->keyFree(i->key);
            }
            if(t->valueFree!=NULL) {
                t->valueFree(i->value);
            }
        }
    }

    array_free(t->values);
    free(t);
}
