

#include <string>
#include <algorithm>

namespace  Codi_BinaryGap {

	using namespace std;
	string nToRevString(int N)
	{
		string s;
		while (N > 0)
		{
			int newN = N / 2;
			if (newN * 2 - N == 0)
				s += "0";
			else
				s += "1";
			N = newN;
		}
		return s;
	}

	int solution(int N) {
		// write your code in C++14 (g++ 6.2.0)
		if (N == 0)
			return 0;

		auto s = nToRevString(N);
		//number always start from 1 unless 0. 
		//needn't consider minus here.
		auto gap = 0;
		auto maxGap = 0;
		for (auto it = s.end() - 2; it >= s.begin(); it--)
		{
			if (*it == '0')
				gap++;
			else
			{
				//recount
				maxGap = max(maxGap, gap);
				gap = 0;
			}
		}

		return maxGap;
	}

}