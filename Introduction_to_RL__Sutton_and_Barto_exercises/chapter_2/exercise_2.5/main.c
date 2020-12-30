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
	// This funciton will use CLT to generate a standard normal
	double normal = 0;
	for(int i =0; i < number_of_iterations; i++) {
		normal += get_uniform_random();
	}
	return (normal - number_of_iterations/2.0) / sqrt( number_of_iterations / 12.0) ;
}

double sample_from_normal(double mean, double var) {
	return (generate_standard_normal(100)*var + mean);	
}

bool explore() {
	return (get_uniform_random() < EPSILON) ? true : false;
}

int get_max_index(double *q) {
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
	int action;
	if(explore()) {
		return (int)(get_uniform_random()*10);
	}
	else {
		return get_max_index(q);
	}
}

void update_q(double *q) {
	for(int j = 0; j < 10; j++) {
		q[j] += sample_from_normal(0, 0.01);
	}
}

double reward_for_action(double *q, int action) {
	return generate_standard_normal(100) + q[action];
}

int main() {
	srand(time(NULL));
	double q[10] = {0}, constant_step_q[10] = {0}, standard_q[10] = {0}, acc_standard = 0.0, acc_constant = 0.0;
	int standard_action, constant_action, best_action;
	for(int i = 0; i < 5000000; i++) {
		update_q(q);
		standard_action = pick_action(standard_q);
		standard_q[standard_action] = standard_q[standard_action] + (reward_for_action(q, standard_action) - standard_q[standard_action]) / (i+1);
		constant_action = pick_action(constant_step_q);
		constant_step_q[constant_action] =  constant_step_q[constant_action] + ALPHA * (reward_for_action(q, constant_action) - constant_step_q[constant_action]);
		best_action = get_max_index(q);
		if(standard_action == best_action) { acc_standard++; }
		if(constant_action == best_action) { acc_constant++; }
		if(i % 10000 == 0) { printf("The standard acc is %lf and the const acc is %lf \n", acc_standard/i, acc_constant/i); }
	}
	return 0;
}
