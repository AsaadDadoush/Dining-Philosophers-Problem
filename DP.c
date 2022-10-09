/*
* this programm is wrriten implementing the solution to the Dining Philosopher
* Problem. The Dining Philosopher Problem states that there are five philosophers
* which do two thinks: think and eat. They share a table having a chair for each
* one of them. In the center of the table there is a bowl of rice and the table is
* laid with N single chopsticks
*
* Author: Asaad W. Daadouch
* Version 1.00 2022/10/09
*/

//      ======================================================
//      |                   import libaries                  |
//      ======================================================
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "DiningTable.h"
#include <stdlib.h>

// make the array of Semaphores
sem_t chopstick[5];



//      ======================================================
//      |                   structure                        |
//      ======================================================

// passing the data to the threads by creating a structure
struct arg{
	int N, i;	// N number of philosophers, i = philosopher
	float d;	//  delay time
};


//      ======================================================
//      |                   philos function                  |
//      ======================================================

// this function that will be applied by thread
// which is expressed the live of philosophers
void *philos(void *param){
		struct arg *state;
		state = (struct arg *)param;
                int left;	        // for taking the left Chopstick
                _Bool right_first;	// take the right or the left Chopstick first

		int N = state->N;        //  number of philosophers
		float d = state->d;      //  delay time
                int i = state->i;        //  philosopher

                if (i == 0)              // start with first philosophers
                        left = N - 1;
                else
                        left = (i-1)%N;

                if (i%2 == 0)
                        right_first = 1;
                else
                        right_first = 0;

        while (1){
                hungry(i);                      // philosopher is hungry

                if (right_first){
                        sem_wait(&chopstick[i]);    // let the semaphore wait for the chopstick
                        takeChopstick(i, 'r');      // move it right
                        sem_wait(&chopstick[left]); // let the left chopstick waits
                        takeChopstick(left, 'l');   // move the left chopstick
                }
                else {
                        sem_wait(&chopstick[left]); // let the left chopstick waits
                        takeChopstick(left, 'l');   // move the left chopstick
                        sem_wait(&chopstick[i]);    // let the semaphore wait for the chopstick
                        takeChopstick(i, 'r');      // move it right
                }

                eat(i);				    // 
                sleep(d);

                if (right_first){
                        putChopstick(i);
                        sem_post(&chopstick[i]);
                        putChopstick(left);
                        sem_post(&chopstick[left]);
                }
                else {
                        putChopstick(left);
                        sem_post(&chopstick[left]);
                        putChopstick(i);
                        sem_post(&chopstick[i]);
                }

                think(i);
                sleep(d);
        }
}

//      ======================================================
//      |                   main function                  |
//      ======================================================
//
// In the main() function there are three for loops. The first loop is used to initialize each
// semaphore variable with initial value to 1. The second for loop is used to create five threads
// which will act as the five philosophers. The third for loop uses the pthread_join  function which makes
// the parent program wait for each of the thread to finish.
int main(int argc, char *argv[]){

	if (argc < 3){
	printf("ERROR: please enter the number of philosophers and the speed of the simulations (delay).");
	exit(0);
	}

        int N = atoi(argv[1]);		        // number of philosophers
	float d = atof(argv[2])/10.0;	        // time simulation speed 
        int i;				        // philosopher member
        struct arg param[N];		        // argument of threads
        pthread_t philosopher[N];	        // generate threads for philosophers
        init(N);			        // initialize the programm

        for (i = 0; i < N; i++)                 // initialize the semaphore variables
                 sem_init(&chopstick[i], 0, 1); // the first param for the semaphore variable, 0 for no sharing amoung the process,
                                                // 1 the initial valute of semaphore variable

        for (i = 0; i < N; i++){                // Creating N threads
		param[i].N = N;
       		param[i].d = d;
		param[i].i = i;
                pthread_create(& philosopher[i], NULL, philos,(void *) &param[i]); // function for creating threads
        }


         for (i = 0; i < N; i++)       // join all threads 
                pthread_join(philosopher[i], NULL);

        finish();			// terminate the program

}





