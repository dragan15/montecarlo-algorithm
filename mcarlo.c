#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int  npoints = 0; //USER INPUT
int  hit_count = 0;

 double random_double()//generates random numbers
  {
   return random() / ((double)RAND_MAX + 1);
  }

void *count(void *x)
 { 
   int i;
  // checks for points in circle
   for ( i = 0; i < npoints; i++)// generate random numbers between -1.0 and +1.0 (exclusive) 
   {
     double x = random_double() * 2.0 - 1.0;
     double y = random_double() * 2.0 - 1.0;
     if (sqrt(x*x + y*y) < 1.0 )
     ++hit_count;
   }
    return NULL;
 }

int main(int argc, char *argv[])
 {
   pthread_t tid; /* the thread identifier */
   pthread_attr_t attr; /* set of attributes for the thread */
      
   npoints = atof(argv[1]); //converts user input to double

   if (argc != 2) //if user does not put correct input[aka there isn't 2 arguements], put error 
    {
      fprintf(stderr,"usage: a.out <integer value>\n");
      /*exit(1);*/
      return -1;
    }

   if (npoints < 0) //if user input AKA the integer converted of the string is less than 0, then int value is a negative value, and that's not allowed
     {
       fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
       /*exit(1);*/
       return -1;
     } 

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tid,&attr,&count,argv[1]);
         
        /* now wait for the thread to exit */
	pthread_join(tid,NULL);


    double points = 4.0 * hit_count;
    double pi = points/ npoints;
    printf("value of pi is %f\n",pi);
    return 0;
}



