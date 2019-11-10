#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <random>
#include <tuple>

//MIT License.

template<class it,class T>
std::tuple<bool, it> BinarySearch(it A, it B, const T& V) {

	if (A == B) { return { *A == V,A }; }

	B--;

	if (A == B) { return { *A == V,A }; }

	if (*A > * B) {
		std::swap(A, B);
	}

	if (*A == V) { return { *A == V,A }; }
	if (*B == V) { return { *B == V,B }; }
	std::int64_t c = std::distance(A, B) / 2;
	if (*(A + c) == V) { return { *(A + c) == V, A + c };}
	if (c == 0) { return { *A == V,A }; }

	it a = A;
	it b = B;

	do {
		c = std::distance(a, b) / 2;
		if (*(a + c) < V) {
			a += c;
			if (*a == V) { return { *a == V,a }; }
		}
		else {
			b -= c;
			if (*b == V) { return { *b == V, b }; }
		}
	} while (c > 0);

	return { *a == V,a };
}
template<class it,class T>
std::tuple<bool, it> RatioSearch(it A, it B, const T& V, std::size_t Div=7) {

	if (A == B) { return { *A == V,A }; }

	B--;

	if (A == B) { return { *A == V,A }; }

	if (*A > * B) {
		std::swap(A, B);
	}

	std::size_t dis = std::distance(A, B) / 2;

	if (Div < dis) { Div = dis; }

	auto a = A;
	auto b = B;

	std::size_t c = Div / 2;
	do {
	std::size_t d = (dis / Div) * c;
	c /= 2;
	if (*(a + d) < V) {
		a += d;
		if (*a == V) { return { *a == V, a }; }
	}
	else {
		b -= d;
		if (*b == V) { return { *b == V,b }; }
	}
	} while (c > 0);

 	return BinarySearch(a, b, V);


}

std::vector<std::uint64_t> MakeRandomVector(std::size_t N, unsigned int S=0) {
	std::mt19937 mt(S);
	std::uniform_int_distribution<std::uint64_t> ui(0, N);

	std::vector<std::uint64_t> R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mt));
	}
	std::sort(R.begin(), R.end());

	return R;
}

int main() {

	auto R = MakeRandomVector(16);

	//auto A = BinarySearch(R.begin(), R.end(),17);//need sorted conatiner.
	auto A = RatioSearch(R.begin(), R.end(),7);//need sorted conatiner. little slow on conputer but real.

	std::cout << (std::get<0>(A) ? 'T' : 'F') << ",value:" << *std::get<1>(A) << ",Distance:" << std::distance(R.begin(), std::get<1>(A)) << std::endl;

	return 0;
}