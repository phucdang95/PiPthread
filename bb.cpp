#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <math.h>

using namespace std;

int getargs(int argc, char *argv[]){
    char* strOne="";
    if (argc<1){
        }
    if (argc>1) {
                // note argv[0] is the program name
                strOne=argv[1];  
                printf("Argument One: %s \n", strOne);
        }
    int intArg=0;
    if (argc>2) {
                // use function atoi() to convert char* to integer
                intArg=atoi(argv[2]);  
                printf("Argument Two: %d \n", intArg);
        }
    system("PAUSE"); // Windows pause command
    return EXIT_SUCCESS;
}
// global variables
double total;  //the answer
double width;     // Width of each rectangle
double steps;   // total number of rectangles
int numthreads;  //
double interval;    // size of the total interval
pthread_mutex_t lock;
// function prototypes
double f(double n);  // Our Curve
void * work(void *t);   // our worker function for child threads

int main(int argc, char *argv[])
{
    int critical;
    pthread_t tid[20];
    total=0;
    double start=0,stop=2;
    numthreads=8;
    steps=10000;
    int i;
    interval=stop-start;
    width=interval/steps;
    cout<<"Variables - Width: "<<width << " Interval: "<< interval << "\n" ;
    if (pthread_mutex_init(&lock, NULL) != 0)
{
    cout<<"\n Mutex init has failed\n";
return 1;
}
    for(i=0;i<numthreads;i++){
        critical = pthread_create(&(tid[i]), NULL, &work, (void *)i);
        if (critical != 0)
            cout<<"\n Unable to create thread";
    }
    for (i=0;i<numthreads;i++){
        pthread_join(tid[i], NULL);
}
    //Destroy mutex object referenced by mutex
    pthread_mutex_destroy(&lock);
    cout <<"The value of Pi is = " << total << "\n";
return EXIT_SUCCESS;
}
void * work(void *t){
    long tid= (long)t;
    double locsum=0;
    double start=tid*interval/numthreads;
    double stop=(tid+1)*interval/numthreads;
    double i=0;
    for(i=start; i<stop; i+=width){
        locsum+=f(i)*width;
}
    //Locking mutex
    pthread_mutex_lock(&lock);
    total+=locsum;
    //Unlocking mutex
    pthread_mutex_unlock(&lock);
    cout<< "Thread: "<<i<<" Local Sum: "<< locsum<<" Total: "<< total<< "\n";
}
double f(double n){
	double h=0;
	h=sqrt(4-n*n);
	return h;

}
  

