#include <iostream> 
#include <vector> 

#define STRUCTEDGET 1 

#if STRUCTEDGET 
struct edge_t 
{
	unsigned short home; 
	unsigned short away; 
}; 
#else 
using edge_t = unsigned short[2]; 
#endif // STRUCTEDGET 


int main(int agrc, char* argv[])
{
	using factor_t = std::vector<edge_t>; 

	std::vector<factor_t> vectorFactors; 

	unsigned uN; 
	std::cout << "count of teams :\t"; 
	std::cin >> uN; 

	 
	if (uN & 1) // if uN is odd 
	{
		++uN; // inc uN 
	}

	vectorFactors.clear();
	unsigned uColorCount = uN - 1;

	// step 1 
	{
		unsigned uK = uN / 2; 
		unsigned uLast = uN - 1; 
		for (unsigned i = 0; i < uColorCount; ++i) 
		{
			factor_t factorFi; 

			{
				edge_t edgeEni; 
#if STRUCTEDGET 
				edgeEni.home = uLast; 
				edgeEni.away = i; 
#else 
				edgeEni[0] = uLast; 
				edgeEni[1] = i; 
#endif // STRUCTEDGET 

				factorFi.push_back(edgeEni); 
			}

			for (unsigned k = 1; k < uK; ++k) 
			{
				edge_t edgeEik; 
#if STRUCTEDGET 
				edgeEik.home = (i + k + uLast) % uLast; 
				edgeEik.away = (i - k + uLast) % uLast; 
#else 
				edgeEik[0] = (i + k + uLast) % uLast; 
				edgeEik[1] = (i - k + uLast) % uLast; 
#endif // STRUCTEDGET 

				factorFi.push_back(edgeEik); 
			}

			vectorFactors.push_back(factorFi);
		}
	}

	// step 2 
	{
		unsigned uK = uN / 2;
		for (unsigned i = 0; i < uColorCount; ++i)
		{
			{
				edge_t& edgeEni = vectorFactors[i][0];
				if (i & 1) // if i is odd 
				{
#if STRUCTEDGET 
					std::swap(edgeEni.home, edgeEni.away); 
#else 
					std::swap(edgeEni[0], edgeEni[1]); 
#endif // STRUCTEDGET 
				}
				else
				{
					// do nothing 
				}
			}

			for (unsigned k = 1; k < uK; ++k)
			{
				edge_t& edgeEik = vectorFactors[i][k];
				if (k & 1) // if k is odd 
				{
#if STRUCTEDGET 
					std::swap(edgeEik.home, edgeEik.away);
#else 
					std::swap(edgeEik[0], edgeEik[1]);
#endif // STRUCTEDGET 
				}
				else 
				{
					// do nothing 
				} 
			}
		}
	}

	// step 3 
	for (auto fi = vectorFactors.begin(); fi != vectorFactors.end(); ++fi)
	{
		factor_t& factorFi = *fi;
		for (auto ei = factorFi.begin(); ei != factorFi.end(); ++ei)
		{
			edge_t& edgeEi = *ei;
			std::cout << ' ' << edgeEi.home << " -> " << edgeEi.away << ";\t";
		}
		std::cout << std::endl;
	}

	return 0;
}