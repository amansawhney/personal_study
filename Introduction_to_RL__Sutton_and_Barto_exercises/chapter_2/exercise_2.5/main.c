/*
	This is a program to solve exercise 2.5. It will preform an experiment involving a non-stationary k-banditis problem. 
	We will have a 10-armed bandit problem where q_*(a) start out equal and then each take a random walk. We will use 
	two methods: sample averaging and one where the step size is fixed to alpha=0.1. In addition, we will use epsilon=0.1. 
	Aman Sawhney
	12/30/20
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define EPSILON 0.2
#define ALPHA 0.1

double get_uniform_random() {
	return ((double) rand() / (double) RAND_MAX);
}

double generate_standard_normal(int number_of_iterations) {
	// Uses CLT to generate a standard normal
	double normal = 0;
	for(int i =0; i < number_of_iterations; i++) {
		normal += get_uniform_random();
	}
	return (normal - number_of_iterations/2.0) / sqrt( number_of_iterations / 12.0) ;
}

double sample_from_normal(double mean, double var) {
	return (generate_standard_normal(12)*var + mean);	
}

bool explore() {
	// Samples from a uniform to determine if one should explore or exploit the current policy
	return (get_uniform_random() < EPSILON) ? true : false;
}

int get_max_index(double *q) {
	// Finds largest index of array of doubles
	int index = 0;
	double max = q[0];
	for(int i = 0; i < 10; i++) {
		if(q[i] > max) {
			max = q[i];
			index = i;
		}
	}
	return index;
}

int pick_action(double *q) {
	// Given a value function, this picks an explotive or explorative action
	return (explore()) ? (int)(get_uniform_random()*10) : get_max_index(q);
}

void update_q(double *q) {
	// Progresses q along the random walk for the value, where the steps are sampled from N(0, 0.01)
	for(int j = 0; j < 10; j++) {
		q[j] += sample_from_normal(0, 0.01);
	}
}

double reward_for_action(double *q, int action) {
	// Gets the reward for any action with a noise of N(0,1)
	return generate_standard_normal(12) + q[action];
}

void run_one_trial(int steps, double * acc_array) {
	// Runs one experiment of s steps
	double q[10] = {0}, constant_step_q[10] = {0}, standard_q[10] = {0};
	int standard_action, constant_action, best_action;
	for(int i = 0; i < steps; i++) {
                update_q(q);
                standard_action = pick_action(standard_q);
                standard_q[standard_action] = standard_q[standard_action] + (reward_for_action(q, standard_action) - standard_q[standard_action]) / (i+1);
                constant_action = pick_action(constant_step_q);
                constant_step_q[constant_action] =  constant_step_q[constant_action] + ALPHA * (reward_for_action(q, constant_action) - constant_step_q[constant_action]);
                best_action = get_max_index(q);
                if(standard_action == best_action) { acc_array[0] += 1.0/steps; }
                if(constant_action == best_action) { acc_array[1] += 1.0/steps; }
        }

}

int main() {
	srand(time(NULL));
	int num_of_runs = 100;
	for(int s = 0; s <= 10000; s += 100) {
		// Iterates through each possible number of steps
		double acc_accray[2] = {0};
		// Runs a seperate experiement for the inputed number of indp runs
		for(int b = 0; b < num_of_runs; b++) {
			double trail_acc[2] = {0};
			run_one_trial(s, trail_acc);
			acc_accray[0] += trail_acc[0] / (num_of_runs);
			acc_accray[1] += trail_acc[1] / (num_of_runs);
		} 
		printf("After %d steps we have a standard acc of %lf and a const acc of %lf \n", s, acc_accray[0], acc_accray[1]);

	}
	return 0;
}
