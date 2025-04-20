#include <cmath>

int main()
{
	const int size = 256;
	double sinTable[size];

	#pragma omp target teams distribute parallel for map(from:sinTable[0:256])
	for (int n = 0; n < size; ++n)
		sinTable[n] = std::sin(2 * M_PI * n / size);
}
//g++ -fopenmp -foffload=nvptx-none -o init_tab_paral_mult_thread_GPU init_tab_paral_mult_thread_GPU.cpp
//lspci | grep -i nvidia