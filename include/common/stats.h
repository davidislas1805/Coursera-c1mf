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
 * @file <Add File Name> 
 * @brief <Add Brief Description Here >
 *
 * <Add Extended Description Here>
 *
 * @author <Add FirsName LastName>
 * @date <Add date >
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

/**
 * @brief Print the statistics of a given array (minmum, maximum, mean and median).
 * 
 * This function prints the minmum, maximum, mean and median of the given array by calling
 * the find_mean(), find_median(), find_maximum() and find_minimum() functions respectively
 * and printing the results into the terminal.
 * 
 * @param data_array_ptr Pointer to the array to be analyzed.
 * @param array_size Size of the array.
 */
void print_statistics(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Print the given array into the terminal
 * 
 * This function prints the array into the terminal formatted with spaces and line breaks
 * 
 * @param data_array_ptr Pointer to the array to be printed.
 * @param array_size Size of the array.
*/
void print_array(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Compute the mean of a given array.
 * 
 * This function returns the mean of the data of a given array. The mean is rounded to the
 * nearest integer.
 * 
 * @param data_array_ptr Pointer to the array.
 * @param array_size Size of the array.
 * 
 * @return mean of the array
*/
unsigned char find_mean(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Get the median of a given array.
 * 
 * This function returns the median of the data of a given array first by sorting the array
 * from smallest to largest and returning the median data or the mean if the array contains
 * an even number of elements.
 * 
 * @param data_array_ptr Pointer to the array.
 * @param array_size Size of the array.
 * 
 *  @return median of the array
*/
unsigned char find_median(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Get the largest element of a given array
 * 
 * This function returns the largest element from the given array.
 * 
 * @param data_array_ptr Pointer to the array.
 * @param array_size Size of the array.
 * 
 * @return largest element
*/
unsigned char find_maximum(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Get the smallest element of a given array.
 * 
 * This function returns the smallest element from the given array.
 * 
 * @param data_array_ptr Pointer to the array.
 * @param array_size Size of the array.
 * 
 * @return smallest element
*/
unsigned char find_minimum(unsigned char * data_array_ptr, unsigned int array_size);

/** 
 * @brief Sort the given array as desired.
 * 
 * This function sorts the array either from smallest to largest or vice versa depending on the value passed
 * to the sort_type param. The result is stored in the sorted_array_ptr buffer to be later used,
 * hence the original array is not overwritten.
 * 
 * @param data_array_ptr Pointer to the array to be sorted.
 * @param sorted_array_ptr Pointer to the buffer where the sorted array will be stored.
 * @param array_size Size of the array.
 * @param sort_type Type of sort to be applied to the array, with 1 meaning ascending order and 0 descending.
*/
void sort_array(unsigned char * data_array_ptr, unsigned char * sorted_array_ptr, unsigned int array_size, unsigned char sort_type);

/** 
 * @brief Check whether the array is sorted as desired.
 * 
 * This function checks if the array is sorted as desired either descending or ascending order,
 * depending on the value passed to the check_type param, with 0 meaning that the array is to be checked whether it is sorted in descending order
 * or 1 if ascending one.
 * This function is to be used inside the sort_array() function as to break from the sorting cycle once the array is sorted.
 * 
 * @param data_array_ptr Pointer to the array to be checked.
 * @param array_size Size of the array.
 * @param check_type Type of check to be applied on the array. 
 * 
 * @return 0 if the array is not sorted and 1 if so.
*/
unsigned char check_array(unsigned char * data_array_ptr, unsigned int array_size, unsigned char check_type);


#endif /* __STATS_H__ */
