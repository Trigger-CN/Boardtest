#include "pi_test.h"
#include "cpuinfo.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

double calculate_pi(unsigned long num_steps) {
    double step = 1.0 / num_steps;
    double x, pi, sum = 0.0;

    for (unsigned long i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * step;
    return pi;
}

int pi_test_once(unsigned long num_steps) {
    double pi;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    pi = calculate_pi(num_steps);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("pi = : %f\n", pi);
    printf("calculate steps = : %ld  time: %f 秒\n",num_steps, cpu_time_used);

    return 0;
}

int pi_test_single_core(void)
{
    pi_test_once(100000);
    pi_test_once(1000000);
    pi_test_once(10000000);
    pi_test_once(100000000);
    pi_test_once(1000000000);

    return 0;
}

int pi_test_multi_core() {
    unsigned long num_steps = 1000000000;  // 要计算的步数
    double step = 1.0 / num_steps;
    double pi = 0.0;
    double start, end;
    double cpu_time_used;

    int cores_count = get_cores_count();
    printf("cpu cores count : %d\n", cores_count);

    start = omp_get_wtime();

    #pragma omp parallel num_threads(cores_count)
    {
        double sum = 0.0;

        #pragma omp for
        for (unsigned long i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        pi += sum;
    }


    end = omp_get_wtime();
    pi = pi * step;
    cpu_time_used = end - start;

    printf("pi = : %f\n", pi);
    printf("calculate steps = : %ld  time: %f 秒\n",num_steps, cpu_time_used);

    return 0;
}

int pi_test_main(void)
{
    
    printf("\npi_test single core:\n");
    pi_test_single_core();
    
    printf("\npi_test multi core:\n");
    pi_test_multi_core();
    return 0;
}
