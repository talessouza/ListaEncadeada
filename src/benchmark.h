/*
 * benchmark.h
 *
 *  Created on: 14 de mar de 2016
 *      Author: Thiago
 */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_

struct bm {
	unsigned long int nC;
	unsigned long int nA;
}typedef BM;

void startBenchmark();
void endBenchmark();

#endif /* BENCHMARK_H_ */
