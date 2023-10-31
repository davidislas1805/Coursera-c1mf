#include "data.h"
#include "memory.h"
#include "platform.h"
#include <stdlib.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base){
    if ( ptr == NULL || base == 0 || base < 2 || base > 16 ) return 0;
    
    char temp_data = 0, neg_data = 0;
    uint8_t length;
    if ( data < 0 ){
        *ptr = (char)45;
        data *= -1;
        neg_data = 1;
        length = 1;
    }
    for (uint8_t i = neg_data; i < 32; i++)
    {
        if((data % base) < 10){
            temp_data = (char)((data % base) + 48);
        }else{
            temp_data = (char)((data % base) + 55);
        }
        data /= base;
        *(ptr+i) = temp_data;
        length += 1;

        if(data == 0){
            *(ptr+i+1) = '\0';
            break;
        }

    }
    my_reverse( (neg_data ? ptr + 1 : ptr) , (neg_data ? length - 1 : length));
    return length;
};

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){
    if ( ptr == NULL || base == 0 || base < 2 || base > 16 ) return 0;

    char neg_data = 0, temp_digit;
    int32_t number = 0;
    
    if( *ptr == (char)45 ) neg_data = 1;
    
    for ( uint8_t i = neg_data; i < digits; i++ ){
        temp_digit = *(ptr + i);
        if (temp_digit < 58 ) number += (temp_digit - 48) * (my_pow(base, digits - i + -1));
        else number += (temp_digit - 55) * (my_pow(base, digits - i + -1));
    }

    if (neg_data) number *= -1;

    return number;
};

uint32_t my_pow(uint8_t base, uint8_t exponent){
    uint32_t result = 1;
    for ( uint8_t i = 0; i < exponent; i++ ) result *= base;
    return result;
};