#include "cipher.h"

Cipher::Cipher()
{
	KeyExpansion(mExpandedKey);
	Block block(mExpandedKey, nr);
}

std::bitset<32> Cipher::GetRcon(unsigned short i)
{
	std::bitset<8> top_byte(1);
	for (unsigned short j = 0; j < i - 1; j++)
	{
		top_byte = ModularLeftShift(top_byte);
	}
	return std::bitset<32>(top_byte.to_string() + "000000000000000000000000");
}

void Cipher::KeyExpansion(std::bitset<32> expanded_key[])
{
	std::bitset<8> key[4 * nk] = {std::bitset<8>(43), std::bitset<8>(126), std::bitset<8>(21), std::bitset<8>(22),
								std::bitset<8>(40), std::bitset<8>(174), std::bitset<8>(210), std::bitset<8>(166),
								std::bitset<8>(171), std::bitset<8>(247), std::bitset<8>(21), std::bitset<8>(136),
								std::bitset<8>(9), std::bitset<8>(207), std::bitset<8>(79), std::bitset<8>(60) };

	unsigned short i = 0;

	while (i < nk)
	{
		expanded_key[i] = std::bitset<32>(key[4 * i].to_string() + key[4 * i + 1].to_string() + key[4 * i + 2].to_string() + key[4 * i + 3].to_string());
		i++;
	}

	std::bitset<32> temp;
	while (i < nb * (nr + 1))
	{
		temp = expanded_key[i - 1];
		if (i % nk == 0)
		{
			temp = SubWord(RotWord(temp)) ^ GetRcon(i / nk);
		}
		else if (nk > 6 && i % nk == 4)
		{
			temp = SubWord(temp);
		}
		expanded_key[i] = expanded_key[i - nk] ^ temp;
		i++;
	}
}

std::bitset<32> Cipher::RotWord(std::bitset<32> word)
{
	std::bitset<32> new_word = word << 8;
	for (unsigned short i = 0; i < 8; i++)
	{
		new_word.set(i, word[24 + i]);
	}
	return new_word;

}

std::bitset<32> Cipher::SubWord(std::bitset<32> word)
{
	std::string word_string = word.to_string();
	std::bitset<8> subbed_bytes[4];
	for (unsigned short i = 0; i < 4; i++)
	{
		subbed_bytes[i] = SubByte(std::bitset<8>(word_string.substr(i * 8, 8)));
	}
	return std::bitset<32>(subbed_bytes[0].to_string() + subbed_bytes[1].to_string() + subbed_bytes[2].to_string() + subbed_bytes[3].to_string());
}