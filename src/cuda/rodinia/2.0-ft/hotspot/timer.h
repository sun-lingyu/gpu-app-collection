
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>


/*----------- using cycle counter ------------*/
     __inline__ uint64_t rdtsc() 
     {
          uint64_t cntvct;
          asm volatile ("mrs %0, cntvct_el0; " : "=r"(cntvct) :: "memory");
          return cntvct;
     }

unsigned long long start_cycles;
#define startCycle() (start_cycles = rdtsc())
#define stopCycle(cycles) (cycles = rdtsc()-start_cycles)

/*--------- using gettimeofday ------------*/

#include <sys/time.h>

struct timeval starttime;
struct timeval endtime;

#define startTime() \
{ \
  gettimeofday(&starttime, 0); \
}
#define stopTime(valusecs) \
{ \
  gettimeofday(&endtime, 0); \
  valusecs = (endtime.tv_sec-starttime.tv_sec)*1000000+endtime.tv_usec-starttime.tv_usec; \
}
