#include <immintrin.h>
#include <vector>
#include <bits/stl_numeric.h>

static inline float simdFloatInnerProduct3(std::vector<float>::const_iterator a1, std::vector<float>::const_iterator a2, std::vector<float>::const_iterator b, float add)
{
	float sum = add;
	std::size_t size = a2 - a1;
	if (size >=8)
	{
		__m256 sumab = _mm256_set1_ps(0), aa, bb, mul;
		for (std::size_t i = 0; i < size-8; i+=8)
		{
			aa = _mm256_loadu_ps(a1.operator->()+i);
			bb = _mm256_loadu_ps(b.operator->()+i);
			mul = _mm256_mul_ps(bb, aa);
			sumab = _mm256_add_ps(sumab, mul);
		}
		float sumabArr[8] __attribute__((aligned (32)));
		_mm256_store_ps(sumabArr, sumab);
		for (std::size_t i = 0; i<8 ;++i)
			sum+=sumabArr[i];
	}
	auto pos = size - size%8;
	if (pos != size)
		return std::inner_product(a1+pos, a2, b+pos, sum);
	return sum;
}
