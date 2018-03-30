/*
#include <iostream>
#include <string>

#include <algorithm>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <chrono>

using uint = unsigned int;

void PrintBits(uint hash)
{
	int bitsInUInt = sizeof(uint) * 8;
	std::cout << "Hash: (bits)";

	for (int i = bitsInUInt - 1; i >= 0; i--)
	{
		std::cout << ((hash >> i) & 1);
	}

	std::cout << ", (int)" << (unsigned int)(hash) << std::endl;
}

void gen_random(char *s, const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

char UnHashByte(uint& cH, uint pH, int desiredShift = 6)
{
	int shift = desiredShift % 7 + 1;
	int nonShift = (32 - shift);

	int salt = 17;
	int pepper = 27;

	// check if already at default hash, and return 0;
	// 	std::cout << "Current Hash: ";
	// 	PrintBits(cH);
	uint aB = cH >> nonShift; // get the bits that were added to the front
	cH <<= shift; // shift
	cH += aB; // add bits to the end
			  // 	std::cout << "Undoing previous shift: ";
			  // 	PrintBits(cH);

	cH -= pepper;
	// 	std::cout << "Undoing pepper: ";
	// 	PrintBits(cH);
	uint bI = (cH ^ pH);
	// 	std::cout << "XOR comparison: ";
	// 	PrintBits(cH);

	char b = (bI / salt);
	// 	std::cout << "Unsalting byte: ";
	// 	PrintBits(b);

	return b;
}

template <typename T>
T UnHashType(uint& cH, uint pH)
{
	T t = 0;

	int nB = sizeof(T);

	for (int i = nB; i > 0; i--)
	{
		uint cHC = cH;
		char b = UnHashByte(cH, pH, i);
		T nT = b;
		t += (nT << (i * 8));
		pH = cHC;
	}

	return t;
}

uint HashByte(char b, uint cH, bool shiftDir = true)
{
	int shift = 7; // shifting by ALMOST the whole byte, so some overlap is maintained - should make order matter more
	int nonShift = (32 - shift); // the rest of the bits are those that are not lost due to shifting

	int salt = 37; // can be any number, should be odd, ideally prime
	int pepper = 17425170; // can be any number, should be odd, ideally prime

	uint saltedB = (b * salt);

	cH ^= (saltedB); // salt the byte, then modify hash with it

					 // 	if (b != 0) // don't do anything if no relevant byte was passed in
					 // 	{
	cH += pepper; // salt the resulting hash (+ instead of * since * will cause overflow and not allow refersing the process)
				  // 	}

	uint lB = (cH << nonShift); // get the bits that would be lost by the shift

	cH >>= shift;

	cH += lB;

	return cH;
}

uint HashByte(char b)
{
	uint nH = 0;
	for (int i = 0; i < 32; i += 2)
	{
		nH += (1 << i);
	}

	return HashByte(b, nH);
}

template <typename T>
uint HashType(T& t)
{
	uint sH = HashByte(0);

	int nB = sizeof(t);

	for (int i = 0; i < nB; i++)
	{
		char b = (t >> (i * 8));

		sH = HashByte(b, sH, i % 2);
	}

	return sH;
}

struct SHP
{
	std::string S;
	// int S;
	uint H;
};

enum SHPR
{
	NE,
	SE,
	HE
};

SHPR SHPInVector(std::vector<SHP>& v, SHP nSHP)
{
	for (auto shp : v)
	{
		if (shp.S == nSHP.S)
		{
			return SHPR::SE;
		}
		else if (shp.H == nSHP.H)
		{
			std::cout << "Duplicate Hashes found: " << shp.H << " == " << nSHP.H << std::endl;
			std::cout << shp.S << " -> ";
			PrintBits(shp.H);
			return SHPR::HE;
		}
	}
	return SHPR::NE;
}

int main()
{
	std::vector<SHP> hashes;
	std::vector<double> times;
	unsigned int duplicatesFound = 0;

	for (int i = 0; i < 216553; i++)
	{
		char rW[30];
		int rWL = rand() % 28 + 1;

		gen_random(rW, rWL);

		auto start = std::chrono::high_resolution_clock::now();
		uint nH = HashByte(rW[0]);
		// int cI = i;
		// uint nH = HashType<int>(cI);

		for (int i = 1; i < rWL; i++)
		{
			nH = HashByte(rW[i], nH);
		}

		auto finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed = finish - start;
		times.push_back(elapsed.count());

		SHP nSHP = { std::string(rW), nH };
		// 		SHP nSHP = { i, nH };
		SHPR shpr = SHPInVector(hashes, nSHP);

		if (shpr == SHPR::HE)
		{
			std::cout << nSHP.S << " -> ";
			PrintBits(nSHP.H);
			duplicatesFound++;
		}
		else if (shpr == SHPR::NE)
		{
			hashes.push_back({ std::string(rW), nH });
			// 			hashes.push_back({ i, nH });
		}
	}

	double totalTime = 0.0;
	for (auto& t : times)
	{
		totalTime += t;
	}
	std::cout << "Average time: " << (totalTime / times.size()) << std::endl;

	std::cout << "Duplicates: " << duplicatesFound << std::endl;
}
*/
