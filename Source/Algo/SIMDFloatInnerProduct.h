#include <immintrin.h>
#include <vector>
#include <bits/stl_numeric.h>

#ifdef __AVX2__
static inline float simdFloatInnerProduct(std::vector<float>::const_iterator a1, std::vector<float>::const_iterator a2, std::vector<float>::const_iterator b, float add)
{
	float sum = add;
	std::size_t size = a2 - a1;
	if (size >= 8)
	{
		__m256 sumab = _mm256_set1_ps(0), aa, bb_or_mul;
		for (std::size_t i = 0; i <= size-8; i+=8)
		{
			aa = _mm256_loadu_ps(a1.operator->()+i);
			bb_or_mul = _mm256_loadu_ps(b.operator->()+i);
			bb_or_mul = _mm256_mul_ps(aa, bb_or_mul);
			sumab = _mm256_add_ps(sumab, bb_or_mul);
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
#elif defined(__SSE2__)
static inline float simdFloatInnerProduct(std::vector<float>::const_iterator a1, std::vector<float>::const_iterator a2, std::vector<float>::const_iterator b, float add)
{
	float sum = add;
	std::size_t size = a2 - a1;
	if (size >=4)
	{
		__m128 sumab = _mm_set1_ps(0), aa, bb, mul;
		for (std::size_t i = 0; i <= size-4; i+=4)
		{
			aa = _mm_loadu_ps(a1.operator->()+i);
			bb = _mm_loadu_ps(b.operator->()+i);
			mul = _mm_mul_ps(bb, aa);
			sumab = _mm_add_ps(sumab, mul);
		}
		float sumabArr[4] __attribute__((aligned (16)));
		_mm_store_ps(sumabArr, sumab);
		for (std::size_t i = 0; i<4 ;++i)
			sum+=sumabArr[i];
	}
	auto pos = size - size%4;
	if (pos != size)
		return std::inner_product(a1+pos, a2, b+pos, sum);
	return sum;
}
#else
static inline float simdFloatInnerProduct(std::vector<float>::const_iterator a1, std::vector<float>::const_iterator a2, std::vector<float>::const_iterator b, float add)
{
	return std::inner_product(a1, a2, b, add);
}
#endif
