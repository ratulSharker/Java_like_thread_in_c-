#include <pthread.h>
//here some of the macro defination will do our work
 
//renaming the "pthread_mutex_t" to SYNCHRONIZER
#define UNCONTROLLED_SYNCHRONIZER pthread_mutex_t
 
//renaming the initializer for the SYNCHRONIZER
#define GET_A_NEW_UNCONTROLLED_SYNCHRONIZER  PTHREAD_MUTEX_INITIALIZER
 
#define ENABLE_SYNCHRONIZATION_FOR_UNCONTROLLED_SYNCHRONIZER(syncher) pthread_mutex_lock( &syncher )
 
#define DISABLE_SYNCHRONIZATION_FOR_UNCONTROLLED_SYNCHRONIZER(syncher) pthread_mutex_unlock ( &syncher )