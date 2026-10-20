# Text Editor Using Stack in C

## 1. Project Description
This project is a simple text editor developed using the C programming language. It uses the Stack data structure implemented with arrays to perform Undo and Redo operations. Users can enter, edit, clear, and save text.

## 2. Features
- Enter and edit text
- Undo previous changes
- Redo undone changes
- Clear the document
- Save text to a file
- Menu-driven interface

## 3. Technologies Used
- Programming Language: C
- Data Structure: Stack using Arrays
- File Handling: C file operations
- Header Files: `stdio.h` and `string.h`

## 4. Data Structures
Two stacks are used:
- **Undo Stack:** Stores previous versions of the text.
- **Redo Stack:** Stores versions of the text that were undone.

Both stacks follow the LIFO (Last In, First Out) principle.

## 5. How to Run
1. Open a C compiler such as GCC, Code::Blocks, or Turbo C++.
2. Create a new C source file.
3. Copy the project code into the file.
4. Compile and run the program.
5. Select an option from the displayed menu.

## 6. Output
The program displays the current document and a menu of available operations. The user can manage text and save it in a file named `text.txt`.

## 7. Time Complexity
The main text operations take O(n) time, where n is the length of the text, because text versions are copied or saved.

## 8. Applications
- Understanding stack operations
- Demonstrating Undo and Redo functionality
- Learning basic file handling
- Understanding data structures in text-editing applications

## 9. Conclusion
This project demonstrates the practical use of stacks in a text editor. It helps develop an understanding of arrays, stack operations, file handling, and basic programming concepts in C.
