#include <stdlib.h>

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
    _listitem* to_return = (_listitem*)malloc(sizeof(_listitem));
    to_return->title = title;
    to_return->content = content;
    to_return->next = NULL;
    return to_return;
}

StrList* StrList_init()
// Allocate and return a StrList struct
{
    StrList* to_return = (StrList*)malloc(sizeof(StrList));
    to_return->head = NULL;
    to_return->tail = NULL;
    to_return->size = 0;
    return to_return;
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