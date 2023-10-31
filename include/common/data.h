#ifndef __DATA_H__
#define __DATA_H__
#include <stdint.h>

/**
 * @brief Convert data from a standard integer type into an ASCII string.
 * 
 * This function converts a signed integer (up to 32-bits) into an ASCII string (terminated with a \0)
 * converted to the desired base (2 to 16 are supported) and returns the digit length of the converted
 * string.
 * 
 * @param data Data to convert to ASCII
 * @param ptr Pointer where the resulting string is stored
 * @param base Base convert the integer to
 * 
 * @return Number of digits of the resulting string
*/
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 * @brief Convert data back from an ASCII represented string into an integer type.
 * 
 * This function converts an ASCII string back into a signed integer, taking in the provided string
 * base (2 to 16 are supported) returning the resulting signed integer.
 * 
 * @param ptr Pointer to the ASCII string
 * @param digits Number of digits of the string 
 * @param base Base of the ASCII string
 * 
 * @return The signed integer number
*/
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

/**
 * @brief Get the result a power operation
 * 
 * This function gts the result of a power operation without using the proper pow() function
 * of the math library.
 * 
 * @param base Base nummber
 * @param exponnt Exponent value
 * 
 * @return Result of the operation
*/
uint32_t my_pow(uint8_t base, uint8_t exponent);

#endif /* __DATA_H__ */