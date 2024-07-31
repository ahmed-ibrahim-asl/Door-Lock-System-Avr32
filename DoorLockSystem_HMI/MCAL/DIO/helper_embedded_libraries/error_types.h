#ifndef error_types_
#define error_types_


/*** Include Section Start ***/
#include <stddef.h>
/**
 * Notice:
 *  1. NULL is defined inside that library
 * 
 *  2. why not just define NULL?
 *      - common practice, many libraries rely on standard definition of NULL, and including this library 
*/
/*** Include Section end ***/




/*** Data Type Deceleration Section Start ***/


/*** Enum for error status  **/
typedef enum {                
    ERROR_STATUS_FAILURE,                  
    ERROR_STATUS_OK,           
    ERROR_STATUS_MEMORY_ALLOCATION_FAILED,            
    ERROR_STATUS_NULL_POINTER,
	ERROR_OUT_OF_RANGE
}ErrorStatus_t;               
/*****************************/
/*** Data Type Deceleration Section end ***/


/**
 * notice:
 * > why i am using enum not directly using macros ?!
 *  1. simplify error handling by grouping related error states in one place. we can write switch sattements
 *     to handle each error based on its corresponding enum value.  
 *  
 *  2. Naming Conflict Prevention: Enums have their own scope, ensuring their names don't clash with other variables
 *     or macros, reducing potential naming issues.
*/





#endif
