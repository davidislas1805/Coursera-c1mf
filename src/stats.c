/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c 
 * @brief Code for the first week assessment.
 *
 * This code belongs the first weekly assessment for the Introduction to Embedded
 * Systems Software and Development Environments course. In this file, a data array
 * is manipulated, printing into the terminal different statistics from the array
 * like the mean, median, smallest and largest element as well as providing the sorted
 * version of the data.
 *
 * @author David Islas
 * @date 14th October 2023
 */

#include "stats.h"
#include "stdio.h"
#include "platform.h"

/* Size of the Data Set */
// #define SIZE (40)

// void main(int argc, char *argv[]) {

//   unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
//                               114, 88,   45,  76, 123,  87,  25,  23,
//                               200, 122, 150, 90,   92,  87, 177, 244,
//                               201,   6,  12,  60,   8,   2,   5,  67,
//                                 7,  87, 250, 230,  99,   3, 100,  90};

//   unsigned char sorted_test[SIZE];
//   /* Statistics and Printing Functions Go Here */
//   #ifdef VERBOSE
//   PRINTF("\nShowing the given array: \n\n");
//   print_array(test, SIZE);
//   print_statistics(test, SIZE);
//   #endif
  
//   sort_array(test, sorted_test, SIZE, 0);
//   #ifdef VERBOSE
//   PRINTF("\nShowing the sorted array: \n\n");
//   print_array(sorted_test, SIZE);
//   #endif
// }

/* Add other Implementation File Code Here */

void print_array(unsigned char * data_array_ptr, unsigned int array_size){
  #ifdef VERBOSE
  for(unsigned char i = 0; i < array_size; i++){
    if( data_array_ptr[i] < 10 ) PRINTF("  %i ", data_array_ptr[i]);
    else if ( data_array_ptr[i] < 100 ) PRINTF(" %i ", data_array_ptr[i]);
    else PRINTF("%i ", data_array_ptr[i]);
    
    if( (i + 1) % 8 == 0 ) PRINTF("\n");
  }
  #endif
};

void print_statistics(unsigned char * data_array_ptr, unsigned int array_size){
  unsigned char array_mean, array_median, array_minimum, array_maximum;
  
  array_mean = find_mean(data_array_ptr, array_size);
  array_median = find_median(data_array_ptr, array_size);
  array_minimum = find_minimum(data_array_ptr, array_size);
  array_maximum = find_maximum(data_array_ptr, array_size);
  printf("\nRounded mean: %d \n\nRounded Median: %d \n\nMaximum: %d \n\nMinimum: %d \n", array_mean, array_median, array_maximum, array_minimum);
  PRINTF("\nRounded mean: %d \n\nRounded Median: %d \n\nMaximum: %d \n\nMinimum: %d \n", array_mean, array_median, array_maximum, array_minimum);
};

unsigned char find_mean(unsigned char * data_array_ptr, unsigned int array_size){
  unsigned char mean = 0;

  for(unsigned char i = 0; i < array_size; i++){
    mean += data_array_ptr[i];
  };

  mean /= array_size;
  return mean;
};

unsigned char find_median(unsigned char * data_array_ptr, unsigned int array_size){
  unsigned char median_point = array_size / 2, sorted_array[array_size];
  
  sort_array(data_array_ptr, sorted_array, array_size, 1);
  
  if ( array_size % 2 == 0 ){
    return (sorted_array[median_point - 1] + sorted_array[median_point]) / 2;
  } else{
    return sorted_array[median_point - 1];
  };
};

unsigned char check_array(unsigned char * data_array_ptr, unsigned int array_size, unsigned char check_type){
  unsigned char check_promise = 0;
  for (unsigned char i = 0; i < array_size - 1; i++){
    if ( check_type ) check_promise = ((data_array_ptr[i] < data_array_ptr[i + 1] || data_array_ptr[i] == data_array_ptr[i + 1]) ? 1 : 0);
    else check_promise = ((data_array_ptr[i] > data_array_ptr[i + 1] || data_array_ptr[i] == data_array_ptr[i + 1]) ? 1 : 0); 
    
    if(check_promise == 0) break;
  }
  return check_promise;
};

unsigned char find_maximum(unsigned char * data_array_ptr, unsigned int array_size){
  unsigned char maximum_number = data_array_ptr[0];
  for(unsigned char i = 0; i < array_size; i++){
    if ( data_array_ptr[i] > maximum_number ) maximum_number = data_array_ptr[i];
  };
  return maximum_number;
};

unsigned char find_minimum(unsigned char * data_array_ptr, unsigned int array_size){
  unsigned char minimum_number = data_array_ptr[0];
  for(unsigned char i = 0; i < array_size; i++){
    if ( data_array_ptr[i] < minimum_number ) minimum_number = data_array_ptr[i];
  };
  return minimum_number;
};

void sort_array(unsigned char * data_array_ptr, unsigned char * sorted_array_ptr, unsigned int array_size, unsigned char sort_type){
  unsigned char check_status = 0, temp_array_element;
  for (unsigned char i = 0; i < array_size; i++) sorted_array_ptr[i] = data_array_ptr[i];
  while (check_status == 0)
  {
    for (unsigned char i = 0; i < array_size - 1; i++){
      if ( sort_type ){
        if ( sorted_array_ptr[i] > sorted_array_ptr[i + 1] ){
          temp_array_element = sorted_array_ptr[i];
          sorted_array_ptr[i] = sorted_array_ptr[i + 1];
          sorted_array_ptr[i + 1] = temp_array_element;
        };
      } else {
        if ( sorted_array_ptr[i] < sorted_array_ptr[i + 1] ){
          temp_array_element = sorted_array_ptr[i];
          sorted_array_ptr[i] = sorted_array_ptr[i + 1];
          sorted_array_ptr[i + 1] = temp_array_element;
        };
      };
    };
    check_status = check_array(sorted_array_ptr, array_size, sort_type);
  };
};