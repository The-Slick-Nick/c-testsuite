/*
strlist.h

Provides a definition of a linked list where each
element has both a title and content.

Used by TestSuite for tracking error messages along
with the functions that generated that error.
*/

#include <stdlib.h>

#ifndef INCLUDE_GUARD_STRLIST
#define INCLUDE_GUARD_STRLIST

// Single element in a linked list
typedef struct ListItem {
    char* title;
    char* content;
    struct ListItem* next;
} _listitem;

// Linked list of character arrays (strings)
typedef struct StrList {
    _listitem* head;
    _listitem* tail;
    int size;
} StrList;

_listitem* _listitem_init(char* title, char* content)
// Allocate and return a ListItem struct
{
    _listitem* li = (_listitem*)malloc(sizeof(_listitem));
    li->title = title;
    li->content = content;
    li->next = NULL;
    return li;
}

StrList* StrList_init()
// Allocate and return a StrList struct
{
    StrList* list = (StrList*)malloc(sizeof(StrList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Frees a ListItem's char arrays then frees ListItem
void _listitem_deconstruct(_listitem* li)
{
    free(li->title);
    free(li->content);
    free(li);
}

// Frees StrList and all referenced character strings and _listitem structs
void StrList_deconstruct(StrList* list)
{
    _listitem* hold = NULL;
    _listitem* current = list->head;

    while(current != NULL)
    {
        // Store temp ref to current
        hold = current;

        // Move to next item in list
        current = current->next;

        // Free _listitem considered this round
        _listitem_deconstruct(hold);
    }
    // Finally, free StrList handler struct 
    free(list);
}

// Add a new entry to left side of list
void StrList_insert(StrList* list, char* title, char* content)
{
    _listitem* new_item = _listitem_init(title, content);
    if(list->head == NULL && list->tail == NULL)
    // Implies size == 0
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else
    {
        new_item->next = list->head;
        list->head = new_item;
    }
    list->size++;
}

// Add a new entry to right side of list
void StrList_append(StrList* list, char* title, char* content)
{
    _listitem* new_item = _listitem_init(title, content);
    if(list->head == NULL && list->tail == NULL)
    // Implies size == 0
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else
    {
        list->tail->next = new_item;
        list->tail = new_item;
    }
    list->size++;
}

#endif