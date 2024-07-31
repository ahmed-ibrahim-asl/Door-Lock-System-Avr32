#ifndef STD_TYPES_H_
#define STD_TYPES_H_




/*********              section start              *********/
#define CPU_TYPE_8                                  8               
#define CPU_TYPE_16                                 16
#define CPU_TYPE_32                                 32
#define CPU_TYPE_64                                 64


#define CPU_TYPE                               (CPU_TYPE_32)
/***********************************************************/


/* syntax:  typedef     OldDataTypes    NewDataTypes    */


#if (CPU_TYPE == CPU_TYPE_64)
/********************* unsigned data Types *****************/
typedef unsigned char                             uint8_t;                  // 8-bit  unsigned integer				
typedef unsigned short int                        uint16_t;	                // 16-bit unsigned integer			
typedef unsigned long int                         uint32_t;                 // 32-bit unsigned integer	        
typedef unsigned long long int                    uint64_t;                 // 64-bit unsigned integer	
/***********************************************************/


/********************* signed data Types *******************/
typedef signed char                               sint8_t;                  // 8-bit  signed integer
typedef signed short int                          sint16_t;                 // 16-bit signed integer
typedef signed long int                           sint32_t;                 // 32-bit signed integer
typedef signed long long int                      sint64_t;                 // 64-bit signed integer
typedef float                                     float32;                  // 32-bit floating-point     
typedef double                                    float64;                  // 64-bit floating-point
/***********************************************************/


#elif (CPU_TYPE == CPU_TYPE_32)
/********************* unsigned data Types *****************/
typedef unsigned char                             uint8_t;                  // 8-bit   unsigned integer			

//! can we add checker or something to check if it declared or not
typedef unsigned short int                        uint16;                 // 16-bit  unsigned integer


typedef unsigned long int                         uint32_t;                 // 32-bit  unsigned integer	              
typedef unsigned long long int                    uint64_t;                 // 64-bit  unsigned integer
/***********************************************************/


/********************* signed data Types *******************/
typedef signed char                               sint8_t;
typedef signed short int                          sint16_t;
typedef signed long int                           sint32_t;
typedef signed long long int                      sint64_t;
typedef float                                     float32;
typedef double                                    float64;
/***********************************************************/


#elif (CPU_TYPE == CPU_TYPE_16)
/********************* unsigned data Types *****************/
typedef unsigned char                             uint8_t;				
typedef unsigned short int                        uint16_t;				
typedef unsigned long int                         uint32_t;              
typedef unsigned long long int                    uint64_t;
/***********************************************************/


/********************* signed data Types *******************/
typedef signed short                              sint8_t;
typedef signed long                               sint16_t;
typedef signed long long                          sint64_t;
typedef float                                     float32;
typedef double                                    float64;
/***********************************************************/


#elif (CPU_TYPE == CPU_TYPE_8)
/********************* unsigned data Types *****************/
typedef unsigned char                             uint8_t;				
typedef unsigned short int                        uint16_t;				
typedef unsigned long int                         uint32_t;              
/***********************************************************/


/********************* signed data Types *******************/
typedef signed char                               sint8_t;
typedef signed short                              sint16_t;
typedef signed long                               sint64_t;
typedef float                                     float32;
typedef double                                    float64;
/***********************************************************/

#endif
/*********              section end               *********/
#endif
