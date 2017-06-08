#include <iostream> 
#include <vector> 


struct edge_t 
{
	unsigned short home; 
	unsigned short away; 
}; 


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
				edgeEni.home = uLast; 
				edgeEni.away = i; 

				factorFi.push_back(edgeEni); 
			}

			for (unsigned k = 1; k < uK; ++k) 
			{
				edge_t edgeEik; 
				edgeEik.home = (i + k + uLast) % uLast; 
				edgeEik.away = (i - k + uLast) % uLast; 

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
					std::swap(edgeEni.home, edgeEni.away); 
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
					std::swap(edgeEik.home, edgeEik.away); 
				}
				else 
				{
					// do nothing 
				} 
			}
		}
	}

	// step 3 
	{
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
	}

	return 0;
}