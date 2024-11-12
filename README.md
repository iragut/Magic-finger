### Project Description

On an infinitely long tape to the right (and finitely long to the left),
specific information (a character, with the base character being `"#"`) is always stored.
To know where we are on the tape, we will have an index pointer,
which initially points to the character `"#"`. 
The following commands have been implemented to work with the tape:

- **MOVE_RIGHT**: Moves the pointer one step to the right—if the pointer reaches the end, a new `"#"` element is added.
- **MOVE_LEFT**: Moves the pointer one step to the left—if the pointer is at the beginning, nothing happens.
- **WRITE n**: Inserts character `n` at the position indicated by the pointer.
- **INSERT_RIGHT n**: Inserts a new node with character `n` to the right of the pointer.
- **INSERT_LEFT n**: Inserts a new node with character `n` to the left of the pointer. 
If the pointer is at the beginning, it will display: `ERROR`.
- **MOVE_RIGHT_CHAR n**: Moves the pointer to the right until it reaches `n`. 
If the pointer reaches the end, a new `"#"` element is added.
- **MOVE_LEFT_CHAR n**: Moves the pointer to the left until it reaches `n`. 
If the pointer reaches the beginning, it will display: `ERROR`.
- **SHOW**: Displays the entire tape with all its information.
- **SHOW_CURRENT**: Displays the information at the current pointer position.
- **UNDO**: Reverts the last MOVE_RIGHT or MOVE_LEFT command.
- **REDO**: Re-applies the last undone MOVE_RIGHT or MOVE_LEFT command.
- **EXECUTE**: Executes commands; does not apply to SHOW, SHOW_CURRENT, UNDO, or REDO.

### Project Implementation

Each command read that requires EXECUTE is added to a queue, 
implemented as a singly linked list. Upon encountering the EXECUTE command,
the first command in the queue is retrieved and executed. 
(Commands are stored in the queue as numbers, and upon reading, they are converted.)

UNDO and REDO functionalities are implemented using stacks created with a doubly linked list.
When either of these commands is encountered, the current pointer is added to the REDO or UNDO stack,
and the pointer is updated to the stored position in REDO or UNDO.

The **Magic_finger** is implemented as a doubly linked list with a sentinel node
(it does not exist on the tape as a character). Commands are read,
and output is handled through input and output files.

### How to Execute

1. Create a `.txt` file.
2. Write the number of commands (n) on the first line.
3. Then, write the n commands, each on a new line.
4. Run the program.
