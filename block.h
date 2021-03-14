#pragma once

#include "helpers.h"

#include <iostream>

struct Block
{
public:
	Block(std::bitset<32>* p_expanded_key, unsigned short nr);
	void Decrypt();
	void Encrypt();

private:
	void AddRoundKey(unsigned short round_number);
	void FillState(std::bitset<8> input[]);
	void InvMixColumns();
	void InvShiftRows();
	void InvSubBytes();
	void MixColumns();
	void PrintState();
	void ShiftRows();
	void SubBytes();

private:
	std::bitset<8> mState[nb][nb];
	std::bitset<32>* mpExpandedKey;
	unsigned short mNr;
};