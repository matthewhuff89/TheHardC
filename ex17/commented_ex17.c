// Include standard i/o library header file
#include <stdio.h>
// Include assert macro header file
#include <assert.h>
// Include and define the integer variable errno, which is set by system calls and some library functions in th event of an error to indicate what went wrong. 
#include <errno.h>
// Include standard library header file so we can perform memory allocation and other stuff.
#include <stdlib.h>
// Include string function header file so we can manipulate and perform ops on strings.
#include <string.h>

// Define a constant named MAX_DATA and set the value to 512
#define MAX_DATA 512
// Define a constant named MAX_ROWS and set the value to 100
#define MAX_ROWS 100

// Define a struct named Address and give it properties of id, set, name, and email, and uses the constants defined earlier to give a fixed size
struct Address {
    // declare a variable of type int named id
    int id;
    // declare a variable of type int named set
    int set;
    // declare a variable of type char with a fixed size of 512 bytes
    char name[MAX_DATA];
    // Declare a variable of type char with a fixed size of 512 bytes
    char email[MAX_DATA];
};

// Define a struct named Database
struct Database {
    // Declare a property of the Database struct named rows of type struct Address with a fixed size of 100
    struct Address rows[MAX_ROWS];
};

// Define a struct named Connection 
struct Connection {
    // Declare a pointer of type FILE named file
    FILE *file;
    // Declare a pointer of type 'struct Database' named db
    struct Database *db;
};

// Define a function named die of type void that takes an argument of a pointer of type char named message with a const modifier
void die(const char *message) {
    // Start an if statement that checks if errno is true/exists
    if(errno) {
        // Print an error message 
        perror(message);
      // Create an else branch of an if statement
    } else {
        // Print a message anyway even if errno hasn't been set
        printf("ERROR: %s\n", message);
    }
    // Exit the function, close all streams, shut down the process 
    exit(1);
}

// Declare a function of type void named Address_print
// Takes as an argument a pointer of type 'struct Address' named 
void Address_print(struct Address *addr) {
    // Print the passed in address's id, name, and email (all of which are being dereferenced from the address pointer
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
};

// Declare a function of type void named Database_load
// It's argument is a pointer of type 'struct Connection' named conn
void Database_load(struct Connection *conn) {
    // Declare a variable of type int named rc and assign it the value of 
    // fread, which takes in a pointer to tell it where to store data (conn->db), a size (the size of our DB struct), a number of items to read, and where to get the file from, or the stream, in this case conn->file, and finally returns the number of objects read 
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    // If fread only returned a 0, or somehow read more than one object
    if(rc != 1)
        // Print an error message and kill the process, stating that we failed to load the database
        die("Failed to load database.");
}

// Declare a pointer to a function of type 'struct Connection' named Database_open
// It takes a pointer of type char, modified to be a constant, named filename
// And a variable of type char named mode
struct Connection *Database_open(const char *filename, char mode){
    // Declare a pointer of type 'struct Connection' named conn
    // Set to the address of a memory block allocated for the sizeof a Connection struct
    struct Connection *conn = malloc(sizeof(struct Connection));
    // If the pointer is invalid or doesn't exist
    if(!conn)
        // Kill the process and print an error
        die("Memory error");
    // Otherwise, dereference and access conn's db property and set it equal to the address of an allocated memory block for a Database struct
    conn->db = malloc(sizeof(struct Database));
    // If the conn->db pointer is invalid/falsy
    if(!conn->db)
        // Kill the process and print a memory error 
        die("Memory error");
    // if the mode argument equals 'c'
    if(mode == 'c') {
        // Dereference and access conn's file property and set it equal to
        // a pointer of type FILE and create a file for writing and position the stream at the beginning of the file
        conn->file = fopen(filename, "w");
        // Start an else branch
    } else {
        // Dereference and access conn's file property
        // Set it equal to a pointer of type FILE returned from fopen()
        // Open the file stream for reading and writing and set the stream at the beginning of the file
        conn->file = fopen(filename, "r+");
        // If conn->file is a valid pointer/exists/truthy
        if(conn->file) {
            // Call Database_load and pass in the conn pointer
            Database_load(conn);
        }
    }
    // If conn->file pointer is falsy/invalid
    if(!conn->file)
        // Kill the process, print error message
        die("Failed to open the file");
    // Return conn pointer and exit function
    return conn;
};

// declare a function of type void named Database_close
// That takes in a pointer of type 'struct Connection' named conn 
void Database_close(struct Connection *conn) {
    // If conn is valid/truthy/exists
    if(conn){
        // And conn->file is truthy/exists/valid
        if(conn->file)
            // Call fclose(), pass in pointer, close file stream
            fclose(conn->file);
        // If conn->db is valid/exists/truthy
        if(conn->db)
            // Dellocate memory that conn->db points to
            free(conn->db);
        // Deallocate memory that conn points to
        free(conn);
    }
}
// Declare a function of type void named Database_write
// That takes in a pointer of type 'struct Connection' named conn
void Database_write(struct Connection *conn) {
    // Set the file position indicator for the stream
    // to the beginning of the file. This returns no value
    rewind(conn->file);
    
    // Declare a variable of type int and set it equal to the returned int value of frwrite() which takes in a conn->db pointer to write from, the size of a struct Database to know how big each item is, the number of objects being written, and the stream to write to (conn->file)
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

    // If rc doesn't equal one because nothing was written
    if(rc != 1) 
        // Kill process and print error message
        die("Failed to write database.");
    // Set rc equal to 0 on succesful completion of fflush()
    // Which forces a write of all buffered data to conn->file 
    rc = fflush(conn->file);
    // If rc doesn't equal one because nothing was written
    if(rc == -1)
        // Kill process and print error message
        die("Cannot flush database.");
 
}

// Declare a function of type void
// Takes in a pointer of type 'struct Connection' named conn
void Database_create(struct Connection *conn) {
    // Declare a variable of type int named i and assign it a value of 0
    int i = 0;
    // Start a for loop, set i equal to zero, runs while i is less than MAX_ROWS
    // On each iteration increment i 
    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        // Declare a variable of type struct Address named addr 
        // Set it's id property equal to i, and it's set property to zero
        struct Address addr = { .id = i, .set = 0 };
        // Get the i element of struct Address rows, in db, in conn and set it equal to addr
        conn->db->rows[i] = addr;
    }
}

// Declare a function of type void named Database_set
// Arguments: a pointer of type 'struct Connection' named conn, a variable of type int named id, a pointer of type char named name and modified to be constant, a pointer of type char named email and also a constant
void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    // A pointer of type 'struct Address' named addr set to the address of rows[id] inside of the db object inside of the conn object
    struct Address *addr = &conn->db->rows[id];
    // If addr->set has a value
    if (addr->set)
        // Kill the process, print error message
        die("Already set, delete it first");
    // Set addr->set equal to 1
    addr->set = 1;

    // WARNING: bug, read the "How To Break It" and fix this
    // Declare a pointer of type char named res and point it to the address
    // returned by strncpy (addr->name).
    // Arguments for strncpy are a pointer to return, the address of a character (name), and the size of the character string
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    // If res is not valid
    if(!res)
        // Kill process and print out error
        die("Name copy failed");
    // Set res equal to the pointer to the terminating \0 char of the first argument returned from strncpy(), copying the value of the email char pointer
    res = strncpy(addr->email, email, MAX_DATA);
    // If res is falsy/invalid
    if(!res)
        // Kill the process and print error message
        die("Email copy failed");
}

// Declare a function of type void
// Arguments: A pointer of type 'struct Connection' named conn
// A variable of type int named id
void Database_get(struct Connection *conn, int id) {
    // Declare a pointer of type 'struct Address' named addr 
    // And point it at the address of the rows property of db of conn
    struct Address *addr = &conn->db->rows[id];
    // If addr->set is truthy/valid
    if(addr->set) {
        // Call Address_print and pass in the pointer addr as an argument
        Address_print(addr);
      // Declare an else branch
    } else {
        // Kill the process and print error message
        die("ID is not set");
    }
}

// Declare a function of type void named Database_delete
// Takes arguments: A pointer of type 'struct Connection' named conn
// And a variable of type int named id
void Database_delete(struct Connection *conn, int id) {
    // Declare a variable of type struct Address
    // Apparently this is a temprorary local address (in Zed's words a prototype)
    // This exists on the stack so of course it's temporary
    // Initialize its id and set fields
    struct Address addr = { .id = id, .set = 0 };
    // Copy addr into rows array at id
    // This makes sure all fields except id and set are init to zeroes
    conn->db->rows[id] = addr;
}

// Declare a function of type void named Database_list
// Arguments: A pointer of type 'struct Connection' named conn
void Database_list(struct Connection *conn) {
    // Declare an int variable and set equal to zero
    int i = 0;
    // Declare a pointer of type 'struct Database' named db
    // And point it at conn->db
    struct Database *db = conn->db;
    // Start a for loop, init i at zero, run while i < MAX_ROWS, increment i
    for(i = 0; i < MAX_ROWS; i++) {
        // Declare a pointer of type 'struct Address' named cur
        // Set it equal to the address of db's rows property at [i] 
        struct Address *cur = &db->rows[i];
        // if cur->set is truthy
        if(cur->set) {
            // Call Address_print and pass cur pointer as argument
            Address_print(cur);
        }
    }
}

// Declare a variable of type int named main
// Arguments: variable of type int named argc, array pointer of type char named argv
int main(int argc, char *argv[]) {
    // If less than 3 arguments are passed in
    if(argc < 3)
        // Kill process and print error message
        die("USAGE: ex17 <dbfile> <action> [action params]");
    // Declare a pointer of type char named filename
    // Point it at location of argv[3]
    char *filename = argv[1];
    // Declare a variable of type char named action 
    // and set equal to first element of the third element of argv
    char action = argv[2][0];
    
    // Declare a pointer of type 'struct Connection' named conn
    // Set it equal to returned address of called function Database_open
    // Which takes in the filename pointer and action character
    struct Connection *conn = Database_open(filename, action);

    // Set id variable to zero
    int id = 0;
    
    // If more than 3 arguments were passed in
    // Set id to returned value of atoi(), which converts fourth element (an ASCII string) of argv to an integer
    if(argc > 3) id = atoi(argv[3]);
    // If id's new value is greater than MAX_ROWS' value, 
    // kill process and print error message
    if(id >= MAX_ROWS) die("There's not that many records.");
    
    // Start a switch statement and pass in the action character as operand
    switch(action) {
        // Start a case branch and pass 'c' as it's constant
        case 'c':
            // If action == 'c', call Database_create with conn pointer
            Database_create(conn);
            // Call Database_write with conn pointer
            Database_write(conn);
            // Exit out of switch
            break;
        // Case branch looking for 'g' 
        case 'g':
            // If arguments do not equal 4
            if (argc != 4)
                // Kill process and print error message
                die("Need an id to get");
            // Call Database_get() with conn pointer and id value
            Database_get(conn, id);
            // Exit out of switch
            break;
        // Set case branch to look for 's' action
        case 's':
            // If argc doesn't equal 6
            if(argc != 6)
                // Kill process and print error message
                die("Need id, name, email to set");
            // Call Database_set() with conn pointer, id value, and name and email strings
            Database_set(conn, id, argv[4], argv[5]);
            // Call Database_write() with conn pointer
            Database_write(conn);
            // Exit out of switch
            break;
        // If action is equal to 'd'
        case 'd':
            // If argc doesn't equal 4
            if(argc != 4)
                // Exit process and print error message
                die("Need id to delete");
            // Call Database_delete() with conn pointer and id
            Database_delete(conn, id);
            // Call Database_write() with conn pointer
            Database_write(conn);
            // Exit out of switch
            break;
        // If action is equal to 'l'
        case 'l':
            // Call Database_list() with connection pointer
            Database_list(conn);
            // Exit out of switch
            break;
        // If user doesn't pass a valid action or pass arguments at all
        default:
            // Exit process and print error message
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }
    
    // Call Database_close() with conn pointer
    Database_close(conn);
    // Return out of function
    return 0;
}
