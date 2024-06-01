#include "libc/string.h"
#include "libc/stddef.h"

static char* endOfIntegerConversion;


size_t strlen(const char* str) {
    size_t len = 0;

    // as long as there is a character in the string, increment the length
    while (*str++) len++;
    return len;
}

// inspired by: https://wiki.osdev.org/Printing_To_Screen
char* itoa(int num, char* buf, int base) {
    if (base < 2 || base > 36)
        return '\0';

    char characters[] = "0123456789abcdefghijklmnopqrstuvwxyz"; 

    // just to quickly return a string with a single digit is entered (base 10)
    if (base == 10 && num < 10 && num >= 0){
        buf[0] = '0' + num;
        buf[1] = '\0';
        endOfIntegerConversion = buf+1;
        return buf;
    }


    char *startOfBuffer = buf;
    char *currentCharacter = buf;


    // if the number is negative we add a minus sign
    if (num < 0){
        num = -num;
        *currentCharacter++ = '-';
    }

    // then we convert the number to a string by dividing it by 10 and adding the remainder to the buffer
    while (num) { // '0' pluss the value of the single digit is the same as the ascii value of that digit
        *currentCharacter++ = characters[num % base]; 
        num /= base; 
    }

    // we save the pointer to the end of the string so we can use it in the dtoa function later (if needed).
    endOfIntegerConversion = currentCharacter;

    // adding the null character at the end of the string (-- is to go back to the last digit of the number, so we can reverse it)
    *currentCharacter-- = '\0'; 

    // declare a temporary pointer to the start of the string
    char *tempStart = startOfBuffer;
    if (*startOfBuffer == '-')
        tempStart++;


    // then we reverse the string/number
    while (tempStart < currentCharacter){
        char tempChar = *currentCharacter;
        *currentCharacter-- = *tempStart;
        *tempStart++ = tempChar;
    }

    return startOfBuffer;
}




int atoi(const char* str){
    int num = 0;
    // while the character is a number we add it to a number variable times 10 to get the correct position
    while (*str >= '0' && *str <= '9'){
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}



char* dtoa(double num, char* buf, int precision){ // double to ascii
    // bufferstart is to keep track of the start to the string we shall return
    char *bufferStart = buf;

    // currentchar is for the char we are currently making
    char *currentChar = buf;

    if (num < 0){
        *currentChar++ = '-';
        num = -num;
        buf = buf+1; // we add one so the minus sign doesn't get overwritten later when converting int to string
    }

    //extract the integer part of the float
    int BeforePeriod = (int)num;
    //extract the float part of the float
    double AfterPeriod = num - BeforePeriod;

    // add the integer part (before the period) to the string
    buf = itoa((int)num, buf, 10); 

    // retrieve the pointer to the end of the integer part
    currentChar = endOfIntegerConversion;

    //then we add the period between the int part and the float part
    *currentChar++ = '.';

    // to keep track of how many digits we have printed
    short i=0;
    //then we convert the float part to a string
    while (AfterPeriod > 0 && i++ < precision){ 
        AfterPeriod *= 10;
        *currentChar++ = '0' + (int)AfterPeriod;
        AfterPeriod -= (int)AfterPeriod;
    }

    // finally we add the terminating null character before returning
    *currentChar = '\0'; 
    return bufferStart;       
}



char* itoh(unsigned num, char* buf){
    return itoa(num, buf, 16);
}



bool isInt(char c){
    return (c <= '9' && c >= '0'); // if c is a number
}

int strcmp(const char* str1, const char* str2){
    while (*str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    return *str1 - *str2;
}