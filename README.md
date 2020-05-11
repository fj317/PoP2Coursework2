# Principles of Programming 2 Coursework 2. 
8 programs in C &amp; Java to solve some simple problems:

'Built in methods used' excludes using output functions or any methods that are used for inputting the files used for testing (as these were not part of the original task itself).
Note: as length (of an array) is a property rather than method in Java it is not included.

### Q1
Language: **C**  
Creates a list of pseudo-random numbers by using a simple random number generator (shown in lecture - starts with 1111 as seed, squares it and then takes digits 3-7 as the seed for the next number). Then sorts these numbers using the cocktail shaker algorithm.  
Built in methods used: None  
Own implementation methods: strlen, stringToInt (rough reimplementation of strtol), pow, intToString (reimplementation of sprintf), createRand (rather than using rand).  

### Q2
Language: **Java**  
Reads the txt file containing names. Sorts these names into alphabetical order using the quicksort algorithm. Outputs the sorted names into the console for the user to use.  
Built in methods used: toCharArray  
Own implementation methods: getChar  

### Q3
Language: **C**  
Adds all names from the names.txt file to the hash table, then searches to see if the name 'MARY' is in the table, it then attempts to remove 'MARY' from the table and searches again to see if it is still there. 
Use the following methods to search, add and remove a new name value from the hash table:  
`search(unsigned char name[], struct dataItem* hashArray, unsigned long maxTableSize)` - where `name` is the data to add to the table, `hashArray` is the hash table itself, and `maxTableSize` is the hash table's current size.  
`addName(unsigned char name[], struct dataItem *hashArray, unsigned long *tableSize)` - same as above.  
`removeName(unsigned char name[], struct dataItem* hashArray, unsigned long tableSize)` - same as above.  
Built in methods used: malloc, realloc, sizeOf  
Own implementation methods: strlen (& created own boolean type)  

### Q4
Language: **Java**  
Reads the names in from names.txt. Adds every single name into the XOR linked list in order of the names.txt file (i.e. each is placed 1 item before the end). Contains some testing code that adds two values (one before and one after a name) as well as removes two values (one before and one after a name). This testing data changes elements at the start of the XOR list to help debug as it can be quickly found.  
Syntax for creating new nodes, and inserting & removing these nodes:
`Node name = new Node(String datavalue, int pointer)` where name dictates the name of the new node object, `datavalue` is the string data (i.e. "Mary") and `pointer` should be intialised to 0.  
`insertAfter(String after, Node newobj, Node[] linkedList)` - where `after` is the datavalue to place the `newobj` after in the list, `newobj` is the new node item to add into the list, and `linkedList` is the list itself.  
`insertBefore(String before, Node newobj, Node[] linkedList)` - same as above except `before` is the datavalue to place the `newobj` before in the list.  
`removeAfter(Stirng after, Node[] linkedList)` - where `after` is the datavalue which is 1 node before the node to remove and `linkedList` is the linked list itself.  
`removeBefore(Stirng before, Node[] linkedList)` - where `before` is the datavalue which is 1 node after the node to remove. `linkedList` is the list itself again.  
Built in methods used: toCharArray, equals  
Own implementation methods: getChar, length  

### Q5
Language: **C**  
Program is able to read from the two text files and inputs the files and redacts the text from the redact file with any occurances that occur in the txt file. If you want to change the input data then change the data that is contained within the debate.txt and redact.txt files as these files are read for the input to redact.  
Built in methods used: malloc, sizeOf, realloc  
Own implementation methods: strlen, toUpper (& created own boolean type).  

### Q6
Language: **Java**  
The program has been tested on the entire book and worked as intended however due to the book's length it took a large amount of time, so I have add another file which stores chapter 1's text. This file is then read by the program as it is quicker and still shows the program's functionality. However, all code for file reading is left so that it is possible to change this to redact the entire book rather than one chapter if wanted. This is controlled by line 6.  
The redacted text output is outputted to a txt file named redactedOutput which is placed in Files/Q6 with the other files relating to this question.  
Built in methods used: toCharArray, substring  
Own implementation methods: getChar, (string) length  

### Q7
Language: **C**  
Encrypts the contents of the file text.txt with the key that is written in the code. To change the key change what the char array 'key' stores on line 124 to a different value. Program outputs the contents of the encrypted message to the console for the user to read and do with as they please.  
Built in methods used: None  
Own implementation methods: strlen, toUpper  

### Q8
Language: **Java**  
Program calculates the number of Tuesdays that land on the 1st and outputs the result to the console. The calculated result was **171** Tuesdays since 1st January 1901 to 31st December 2000.  
Built in methods used: None  
Own implementation methods: mod  