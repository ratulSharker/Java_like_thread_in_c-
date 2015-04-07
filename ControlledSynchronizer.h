#ifndef	UNCONTROLLED_SYNCHRONIZER_h
#define UNCONTROLLED_SYNCHRONIZER_h

#include <pthread.h>

struct controlled_synchronizer_stuct
{
	pthread_mutex_t mutex;
	pthread_cond_t	cond_var;
};

#define CONTROLLED_SYNCHRONIZER	struct controlled_synchronizer_stuct

#define INITIALIZE_THE_CONTROLLED_SYNCHRONIZER( cond_sync ) cond_sync.mutex = PTHREAD_MUTEX_INITIALIZER; \
															cond_sync.cond_var = PTHREAD_COND_INITIALIZER

#define ENABLE_CONDITIONAL_SYNCHRONIZER( cond_sync ) pthread_mutex_lock( &cond_sync.mutex )

#define DISABLE_CONDITIONAL_SYNCHORNIZER( cond_sync ) pthread_mutex_unlock( &cond_sync.mutex )

#define WAIT( cond_sync ) pthread_cond_wait( &cond_sync.cond_var, &cond_sync.mutex )

#define STOP_WAITED( cond_sync ) pthread_cond_signal( &cond_sync.cond_var );

#endif