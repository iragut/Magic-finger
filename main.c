#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Defining each structure for Banda_Magica, stack, and queue
typedef struct TList{
    struct node *first;
    struct node *last;
    struct node *finger_position;
} TList;

typedef struct node{
    char character;
    struct node *next;
    struct node *prev;
} node;

typedef struct node_Queue{
    int code;
    char symbol;
    struct node_Queue *next;
} node_Queue;

typedef struct node_Stack{
    struct node *previous_position;
    struct node_Stack *next;
    struct node_Stack *prev;
} node_Stack;

// Printing the list with all the data in it
void print_list(TList *list, FILE *file){
    node *current = list->first;
    current = current->next;

    while (current != NULL)
    {
        if (current == list->finger_position)
        {
            fprintf(file, "|%c|", current->character);
        }
        else
        {
            fprintf(file, "%c", current->character);
        }
        current = current->next;
    }
    fprintf(file, "%c", '\n');
}

// Adding to Banda_Magica at the end on the right side
void add_to_list(TList *list, char character, int aux){
    node *New_list = (node *)malloc(sizeof(node));
    node *current = list->first;

    New_list->character = character;
    New_list->next = NULL;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = New_list;
    New_list->prev = current;
    list->last = New_list;

    if (aux == 1)
    {
        list->finger_position = New_list;
    }
}

// Inserts a new node on the right or left with the desired character
void Insert(TList *list, char character, int path){
    node *New_list = (node *)malloc(sizeof(node));

    New_list->character = character;

    if (path == 1) // On the right of the finger
    {
        New_list->next = list->finger_position->next;
        list->finger_position->next = New_list;

        New_list->prev = list->finger_position;
        New_list->next->prev = New_list;
    }
    else // On the left of the finger
    {
        list->finger_position->prev->next = New_list;
        New_list->prev = list->finger_position->prev;
        New_list->next = list->finger_position;

        list->finger_position->prev = New_list;
    }
    list->finger_position = New_list;
}

// Adding commands to the queue
void add_to_queue(node_Queue *head, int code, char symbol){
    if (head->code == 0)
    {
        head->code = code;
        head->symbol = symbol;
    }
    else
    {
        node_Queue *New_queue = (node_Queue*)malloc(sizeof(node_Queue));
        node_Queue *current = head;

        New_queue->next = NULL;
        New_queue->code = code;
        New_queue->symbol = symbol;

        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = New_queue;
    }
}

// Searching for the requested character and placing the finger on it, search is done on the right side
void MOVE_RIGHT_CHAR(TList *list, char character){
    node *current = list->finger_position;

    while (current != NULL)
    {
        if (current->character == character)
        {
            list->finger_position = current;
            return;
        }
        current = current->next;
    }
    // If the requested letter is not present, a new node with the character '#' is added
    add_to_list(list, '#', 1);
}

// Searching for the requested character and placing the finger on it, search is done on the left side
// If the requested letter is not present, it will return zero, which is ERROR
int MOVE_LEFT_CHAR(TList *list, char character){
    node *current = list->finger_position;

    while (current != NULL)
    {
        if (current->character == character)
        {
            list->finger_position = current;
            return 1;
        }
        else if (current->character == 0)
        {
            return 0;
        }
        current = current->prev;
    }
    return -1;
}

// Adding the finger's position to the stack for UNDO or REDO
void add_to_stack(node *finger_position, node_Stack *last){
    if (last->previous_position == NULL)
    {
        last->previous_position = finger_position;
    }
    else
    {
        node_Stack *current = (node_Stack*)malloc(sizeof(node_Stack));
        current->previous_position = finger_position;
        current->prev = last;
        current->next = NULL;
        last->next = current;
    }
}

int main(){
    // Dynamic allocation of the magic tape, creating the sentinel
    TList *Magic_Tape = (TList*)malloc(sizeof(node));
    Magic_Tape->first = (node*)malloc(sizeof(node));

    Magic_Tape->first->character = 0;
    Magic_Tape->first->prev = NULL;
    Magic_Tape->first->next = NULL;

    // Dynamic allocation of the queue, writing the first element, and the finger's position
    node_Queue *head_Queue = (node_Queue*)malloc(sizeof(node_Queue));
    head_Queue->code = 0;
    head_Queue->next = NULL;

    add_to_list(Magic_Tape, '#', 0);
    Magic_Tape->finger_position = Magic_Tape->last;
    
    // Dynamic allocation of the UNDO and REDO stacks and opening files
    node_Stack *last_stack_UNDO = (node_Stack*)malloc(sizeof(node_Stack)); 
    last_stack_UNDO->prev = NULL;
    last_stack_UNDO->next = NULL;
    last_stack_UNDO->previous_position = NULL;

    node_Stack *last_stack_REDO = (node_Stack*)malloc(sizeof(node_Stack));
    last_stack_REDO->prev = NULL;
    last_stack_REDO->next = NULL;
    last_stack_REDO->previous_position = NULL;

    FILE *file1, *file2;
    file1 = fopen("tema1.in", "r");
    file2 = fopen("tema1.out", "w");

    int i;
    int command_count, queue_index = 0;
    char command[20], character;

    // Reading the number of commands, the type of command, and adding it to the queue if it's of type UPDATE
    fscanf(file1, "%d\n", &command_count);
    while (command_count != 0)
    {
        fscanf(file1, "%[^\n]%*c", command);
        if (strcmp(command, "SHOW") == 0)
        {
            print_list(Magic_Tape, file2);
        }
        else if (strcmp(command, "SHOW_CURRENT") == 0)
        {
            fprintf(file2 ,"%c\n", Magic_Tape->finger_position->character);
        }
        else if (strncmp(command, "WRITE", 5) == 0) // WRITE = 1 
        {
            character = command[6];
            add_to_queue(head_Queue, 1, character);
        }
        else if (strncmp(command, "INSERT_LEFT", 11) == 0) // INSERT_LEFT = 2
        {
            character = command[12];
            add_to_queue(head_Queue, 2, character);
        }
        else if (strncmp(command, "INSERT_RIGHT", 12) == 0) // INSERT_RIGHT = 3
        {
            character = command[13];
            add_to_queue(head_Queue, 3, character);
        }
        else if (strcmp(command, "MOVE_LEFT") == 0) // MOVE_LEFT = 4
        {
            add_to_queue(head_Queue, 4, character);
        }
        else if (strcmp(command, "MOVE_RIGHT") == 0) // MOVE_RIGHT = 5
        {
            add_to_queue(head_Queue, 5, character);
        }
        else if (strncmp(command, "MOVE_RIGHT_CHAR", 15) == 0) // MOVE_RIGHT_CHAR = 6
        {
            character = command[16];
            add_to_queue(head_Queue, 6, character);
        }
        else if (strncmp(command, "MOVE_LEFT_CHAR", 14) == 0) // MOVE_LEFT_CHAR = 7
        {
            character = command[15];
            add_to_queue(head_Queue, 7, character);
        }
        // Removing the finger's position from UNDO or REDO;
        else if (strcmp(command, "UNDO") == 0)
        {
            if (last_stack_REDO->previous_position == NULL){
                add_to_stack(Magic_Tape->finger_position, last_stack_REDO);
            }
            else{
                add_to_stack(Magic_Tape->finger_position, last_stack_REDO);
                last_stack_REDO = last_stack_REDO->next;
            }

            Magic_Tape->finger_position = last_stack_UNDO->previous_position;
            if (last_stack_UNDO->prev != NULL)
            {
                last_stack_UNDO = last_stack_UNDO->prev;
                free(last_stack_UNDO->next);
            }

        }
        else if (strcmp(command, "REDO") == 0)
        {
            if (last_stack_UNDO->previous_position == NULL){
                add_to_stack(Magic_Tape->finger_position, last_stack_UNDO);
            }
            else{
                add_to_stack(Magic_Tape->finger_position, last_stack_UNDO);
                last_stack_UNDO = last_stack_UNDO->next;
            }

            Magic_Tape->finger_position = last_stack_REDO->previous_position;
            if (last_stack_REDO->prev != NULL)
            {
                last_stack_REDO = last_stack_REDO->prev;
                free(last_stack_REDO->next);
            }
        }
        command_count--;
    }

    // Closing files
    fclose(file1);
    fclose(file2);
}
