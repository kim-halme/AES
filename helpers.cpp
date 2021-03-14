#include "helpers.h"

const std::bitset<8> AFFINE_CONSTANT(0x63);
std::bitset<8> Sbox[256];
std::bitset<8> InvSbox[256];

std::bitset<8> AffineTransformation(std::bitset<8> set)
{
	std::bitset<8> result;
	for (unsigned short i = 0; i < 8; i++)
	{
		result[i] = set[i] ^ set[(i + 4) % 8] ^ set[(i + 5) % 8] ^ set[(i + 6) % 8] ^ set[(i + 7) % 8] ^ AFFINE_CONSTANT[i];
	}

	return result;
}

void FillSboxes()
{
	for (unsigned short i = 0; i < 256; i++)
	{
		Sbox[i] = AffineTransformation(MultiplicativeInverse(std::bitset<8>(i)));
		InvSbox[Sbox[i].to_ulong()] = i;
	}
} 

std::bitset<8> InvSubByte(std::bitset<8> byte)
{
	return InvSbox[byte.to_ulong()];
}


std::bitset<8> ModularLeftShift(std::bitset<8> set)
{
	if (set[7] == 1)
	{
		set <<= 1;
		return set ^ IRREDUCIBLE_POLYNOMIAL;
	}
	else
	{
		set <<= 1;
		return set;
	}
}

std::bitset<8> MultiplicativeInverse(std::bitset<8> set)
{
	if (set == std::bitset<8>(0))
	{
		return set;
	}

	for (unsigned short i = 1; i < 256; i++)
	{
		if (Multiply(set, std::bitset<8>(i)) == std::bitset<8>(1))
		{
			return std::bitset<8>(i);
		}
	}
}



std::bitset<8> Multiply(std::bitset<8> set1, std::bitset<8> set2)
{
	std::bitset<8> result;

	if (set1[0] == 1)
	{
		result = result ^ set2;
	}

	for (unsigned short i = 1; i < 8; i++)
	{
		if (set2[7] == 1)
		{
			set2 <<= 1;
			set2 = set2 ^ IRREDUCIBLE_POLYNOMIAL;
		}
		else
		{
			set2 <<= 1;
		}

		if (set1[i] == 1)
		{
			result = result ^ set2;
		}
	}
	return result;
}

std::bitset<8> SubByte(std::bitset<8> byte)
{
	return Sbox[byte.to_ulong()];
}
