/*
	This is a repo to solve the current Jane Street Puzzel for Jan 2020
	Puzzel: Jane received 78 figurines as gifts this holiday season:  12 drummers drumming, 11 pipers piping, 10 lords a-leaping, etc., down to 1 partridge in a pear tree.   They are all mixed together in a big bag.  She agrees with her friend Alex that this seems like too many figurines for one person to have, so she decides to give some of her figurines to Alex.   Jane will uniformly randomly pull figurines out of the bag one at a time until she pulls out the partridge in a pear tree, and will give Alex all of the figurines she pulled out of the bag (except the partridge, that’s Jane’s favorite).   
	If n is the maximum number of any one type of ornament that Alex gets, what is the expected value of n, to seven significant figures?
	
	Aman Sawhney
	Jan 11, 2020
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>  
#include <pthread.h>

pthread_mutex_t lock;

int pick_random_el() {
	int num = rand() % 78;
	return num;
}

int get_max(int item_counts[]) {
	int max = 0;
	for(int i = 0; i < 12; i++) {
		if (item_counts[i] > max) {
			max = item_counts[i];
		}
	}
	return max;
}

void *run_exp(void *args) {
	int *n_runs_ptr = (int *) args;
	int n_runs = *n_runs_ptr; 
	long double *avg = (long double *) malloc(sizeof(long double));
        for(int i = 0; i < n_runs; i++) {
                int items[78] = {0}, item_counts[12] = {0}, max = 0, curr = 0;
                curr = 78;
                while(curr != 0) {
                        int cond = 0;
                        while(cond != 1) {
                                curr = pick_random_el();
                                if(items[curr] == 0) {
                                        items[curr] = 1;
                                        if (curr < 12) {
                                                item_counts[0] += 1;
                                        }
                                        else if (curr < 23) {
                                                item_counts[1] += 1;
                                        }
                                        else if (curr < 33) {
                                                item_counts[2] += 1;
                                        }
                                        else if (curr < 42) {
                                                item_counts[3] += 1;
                                        }
                                        else if (curr < 50) {
                                                item_counts[4] += 1;
                                        }
                                        else if (curr < 57) {
                                                item_counts[5] += 1;
                                        }
                                        else if (curr < 63) {
                                                item_counts[6] += 1;
                                        }
                                        else if (curr < 68) {
                                                item_counts[7] += 1;
                                        }
                                        else if (curr < 72) {
                                                item_counts[8] += 1;
                                        }
                                        else if (curr < 75) {
                                                item_counts[9] += 1;
                                        }
                                        else if (curr < 77) {
                                                item_counts[10] += 1;
                                        }
                                        else {
                                                item_counts[11] += 1;
                                        }
                                        cond = 1;
                                }

                        }

                }

                max = get_max(item_counts);
                *avg += (1.0*max)/n_runs;
        }
	return avg;
}

int main() {
	srand(time(NULL));
	int n_runs_per_thread = 500000, n_threads = 4;
	long double avg = 0;
	pthread_t threads[n_threads];
	for(int i = 0; i < n_threads; i++) {
		pthread_create(&threads[i], NULL, run_exp, &n_runs_per_thread);
	}
	for(int i = 0; i < n_threads; i++) {
        	void *new_avg = NULL;
	        pthread_join(threads[i], &new_avg);
		avg += 1.0/n_threads * (*(long double *) new_avg);

	}
	printf("The expected number of max repeat elements is %Lf \n", avg);	
	return 0;

}	
