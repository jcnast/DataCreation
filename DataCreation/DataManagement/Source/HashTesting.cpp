#include "DataManagement\Headers\HashTesting.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/IO/Headers/IOUtils.h"
#include "Core/IO/Headers/File.h"

#include <iostream>

using namespace Core;
using namespace Core::IO;

void TestHashes()
{
	String filePath = GetCWD() + "/DataManagement/Headers/";

	{
		File AllWords(FilePath{ filePath, "EnglishWords.txt" });
		AllWords.Open();

		File HashedWords(FilePath{ filePath, "HashedEnglishWords.txt" });
		HashedWords.Open();
		HashedWords.Clear();

		uint wordCount = 0;

		/*
		NOTE: there is an issue with the below, occasionally prints out doubles, and also has a random single number near the bottom of the file
		*/

		String word;
		while (AllWords.Read(word))
		{
			AllWords.MoveToNextLine();

			auto start = std::chrono::high_resolution_clock::now();

			Hash hashedWord = HashValue(word);

			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> elapsed = (end - start);
			double dt = elapsed.count();

			HashedWords.Write(word, " ", hashedWord.H, " ", dt);
			HashedWords.CreateNewLine();

			wordCount++;
		}
		std::cout << "Done hashing words" << std::endl;
		HashedWords.GoToPosition(0);

		double wordAverageTime = 0;
		uint numWordCollisions = 0;

		String wordThatWasHashed;
		uint hashedWord;
		double time;
		uint wordPosition = 0;
		while (HashedWords.Read(wordThatWasHashed, hashedWord, time))
		{
			HashedWords.MoveToNextLine();
			wordPosition = HashedWords.GetPosition();

			// use time to keep finding average
			wordAverageTime += time;

			// go through file to determine hash collisions
			String word;
			uint hashedWordCompare;
			String previousWord = "";
			uint previousHashedWordCompare = 0;
			while (HashedWords.Read(word, hashedWordCompare))
			{
				if (previousHashedWordCompare == hashedWordCompare)
				{
					std::cout << "Two exact hashes (except for end of file due to bug); Previous Info: " << previousWord << ", " << previousHashedWordCompare;
					std::cout << ", CurrentInfo: " << word << ", " << hashedWordCompare << std::endl;
				}

				HashedWords.MoveToNextLine();

				if (hashedWord == hashedWordCompare)
				{
					numWordCollisions++;
				}

				previousWord = word;
				previousHashedWordCompare = hashedWordCompare;
			}

			HashedWords.GoToPosition(wordPosition);
		}
		wordAverageTime /= wordCount;

		// return result (# collisions and average time)
		std::cout << "Collisions: " << numWordCollisions << ", Average Time: " << wordAverageTime << std::endl;
	}

	{
		// do the same with all numbers in uint
		File HashedUints(FilePath{ filePath, "HashedUintss.txt" });
		HashedUints.Open();
		HashedUints.Clear();

		for (uint i = 1; i > 0; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();

			Hash hashedUint = HashValue(i);

			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> elapsed = (end - start);
			double dt = elapsed.count();

			HashedUints.Write(hashedUint.H, " ", dt);
			HashedUints.CreateNewLine();
		}
		std::cout << "Done hashing uints" << std::endl;

		double uintAverageTime = 0;
		uint numUintCollisions = 0;

		uint hashedUint;
		double time;
		uint uintPosition = 0;
		while (HashedUints.Read(hashedUint))
		{
			HashedUints.Read(time);

			HashedUints.MoveToNextLine();
			uintPosition = HashedUints.GetPosition();

			// use time to keep finding average
			uintAverageTime += time;

			// go through file to determine hash collisions
			uint hashedUintCompare;

			while (HashedUints.Read(hashedUintCompare))
			{
				HashedUints.MoveToNextLine();

				if (hashedUint == hashedUintCompare)
				{
					numUintCollisions++;
				}
			}

			HashedUints.GoToPosition(uintPosition);
		}
		uintAverageTime /= uint(-1);

		// return result (# collisions and average time)
		std::cout << "Collisions: " << numUintCollisions << ", Average Time: " << uintAverageTime << std::endl;
	}
}