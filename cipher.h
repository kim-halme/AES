#pragma once

#include "helpers.h"
#include "block.h"

#include <bitset>
#include <iostream>

const unsigned short nk = 4;
const unsigned short nr = nk + 6;

struct Cipher
{
public:
	Cipher();

private:
	std::bitset<32> GetRcon(unsigned short i);
	void KeyExpansion(std::bitset<32> expanded_key[]);
	std::bitset<32> RotWord(std::bitset<32> word);
	std::bitset<32> SubWord(std::bitset<32> word);

private:
	std::bitset<32> mExpandedKey[nb * (nr + 1)];
};