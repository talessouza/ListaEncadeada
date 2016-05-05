/*
 * benchmark.c
 *
 *  Created on: 14 de mar de 2016
 *      Author: Thiago
 */

#include <time.h>

#include "benchmark.h"

clock_t begin, end;
double time_spent;

void startBenchmark() {
	begin = clock();
}

void endBenchmark(BM bm) {
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\ntempo de execucao do processo: %.2fs.\n", time_spent);
	printf("\n comparacoes: %lu.\n", bm.nC);
	printf("\n atribuicoes: %lu.\n", bm.nA);
	system("pause");
}

