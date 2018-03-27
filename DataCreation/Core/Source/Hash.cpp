#include "Core/Headers/Hash.h"

namespace Core
{

	Hash HashValue(String s)
	{
		Hash newHash;

		HashValue(s, newHash);

		return newHash;
	}

	void HashValue(String s, Hash& existingHash)
	{
		for (int i = 0; i < s.length(); i++)
		{
			HashValue(s.c_str()[i], existingHash);
		}
	}

	Hash HashValue(char b)
	{
		Hash newHash;

		HashValue(b, newHash);

		return newHash;
	}

	void HashValue(char b, Hash& existingHash)
	{
		int shift = 7; // shifting by ALMOST the whole byte, so some overlap is maintained - should make order matter more
		int nonShift = (32 - shift); // the rest of the bits are those that are not lost due to shifting

		int salt = 37; // can be any number, should be odd, ideally prime
		int pepper = 27; // can be any number, should be odd, ideally prime

		uint saltedB = (b * salt);
		existingHash.H ^= (saltedB); // salt the byte, then modify hash with it

		existingHash.H += pepper; // salt the resulting hash (+ instead of * since * would cause overflow and lose data more often (this may not even be needed)

		uint lB = (existingHash.H << nonShift); // get the bits that would be lost by the shift

		existingHash.H >>= shift; // shift bits

		existingHash.H += lB; // add the missing bits back
	}

	// SEE HEADER
	/*
	char UnHashValue(Hash& currentHash, Hash& previousHash)
	{
		int shift = 7;
		int nonShift = (32 - shift);

		int salt = 37;
		int pepper = 27;

		uint aB = cH >> nonShift; // get the bits that were added to the front

		cH <<= shift; // shift

		cH += aB; // add bits to the end

		cH -= pepper;
		uint bI = (cH ^ pH);

		char b = (bI / salt);

		return b;
	}
	*/
}