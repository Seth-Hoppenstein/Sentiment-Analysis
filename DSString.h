#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString {
private:
    char* data;
    size_t length;

public:
    DSString(); // Default constructor
    DSString(const char* str); // Constructor from C-string
    DSString(const DSString& other); // Copy constructor
    ~DSString(); // Destructor
    DSString& operator=(const DSString& other); // Assignment operator

    size_t getLength() const; // Get length of the string
    const char* c_str() const; // Get C-string representation
    void append(const char* str); // Append to the string
    void clear(); // Clear the string
};

#endif // DSSTRING_H
