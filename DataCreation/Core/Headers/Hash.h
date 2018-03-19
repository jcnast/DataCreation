#pragma once

#include "CoreDefs.h"
#include "TemplateDefs.h"

namespace Core
{
	const uint StartHashValue = 1431655765; // Bits: 01010101010101010101010101010101

	struct Hash
	{
		uint H;

		constexpr Hash();
		constexpr Hash(const Hash& h);

		template <typename T>
		constexpr Hash(T&& t)
		{
			H = HashValue(Forward<T>(t));
		}

		constexpr operator uint()
		{
			return H;
		}
	};

	void HashValue(char b, Hash& existingHash);
		
	template <typename T>
	void HashValue(T&& type, Hash& existingHash)
	{
		int numBytes = sizeof(type);

		for (int i = 0; i < numBytes; i++)
		{
			char byte = (type >> (i * 8));

			HashValue(byte, existingHash);
		}
	}

	template <typename T>
	Hash HashValue(T&& type)
	{
		Hash newHash;

		HashValue(type, newHash);

		return newHash;
	}

	/*
		POSSIBLE!!

		But would we ever need to deconstruct a hash?
		If we need to ensure a starting condition was used, just reconstruct the hash
	*/
	// char UnHashValue(Hash& currentHash, Hash& previousHash);

	/*
		NOT POSSIBLE!!
		
		Since we do not know the true 'previous hash'.
		
		We would need the hashing of the type to return the second last result from the hashing process
		(and unhash both ? ) as we go back, and 'bunny-hop' them to the final result).
	*/
	/*
	template <typename T>
	T UnHashValue(Hash& currentHash, Hash& previousHash)
	{
		T t = 0;

		int numBytes = sizeof(T);

		for (int i = numBytes; i > 0; i--)
		{
			Hash currentHashCopy = currentHash;
			char b = UnHashValue(currentHash, previousHash);
			T newType = b;
			t += (newType << (i * 8));
			previousHash = currentHashCopy;
		}

		return t;
	}
	*/
}
