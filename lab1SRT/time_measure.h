#ifndef _TIME_MEASURE_H_
#define _TIME_MEASURE_H_

#include <Windows.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <limits>

class TimeMeasure {
	std::vector<std::vector<double> > ticks;
	__int64 freq;
	__int64 tmp_start;
	int max_size;

public:
	//n - number of blocks
	//m - number of measures for every block
	TimeMeasure(int n, int m, int time_modifier) : max_size(m) {
		for (int i = 0; i < n; ++i) {
			std::vector<double> tmp_vec;
			ticks.push_back(tmp_vec);
		}

		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		freq /= time_modifier;

		SetThreadAffinityMask(GetCurrentThread(), 1);
		SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	}

	~TimeMeasure() {
		int block_num = 0;
		for (std::vector<std::vector<double> >::iterator it = ticks.begin(); it != ticks.end(); it++) {
			std::cout << "Block #" << block_num << std::endl;
			double avg = 0;
			for (std::vector<double>::iterator inner_it = it->begin(); inner_it != it->end(); inner_it++) {
				std::cout << *inner_it << "  ";
				avg += *inner_it;
			}

			std::cout << std::endl << "Average time: " << avg / it->size() << std::endl << std::endl;
			++block_num;
		}
	}

	void Start() {
		QueryPerformanceCounter((LARGE_INTEGER*)&tmp_start);
	}

	void Save(int n) {
		if (ticks[n].size() >= max_size) return;

		__int64 end;
		QueryPerformanceCounter((LARGE_INTEGER*)&end);
		double new_time = (double)(end - tmp_start) / freq;
		ticks[n].push_back(new_time);
	}
};

#endif
