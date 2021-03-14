#include "block.h"

void Block::AddRoundKey(unsigned short round_number)
{
	std::bitset<32> mask(0b11111111000000000000000000000000);
	for (unsigned short c = 0; c < nb; c++)
	{
		for (unsigned short i = 0; i < nb; i++)
		{
			mState[i][c] ^= std::bitset<8>(((mpExpandedKey[round_number * nb + c] & (mask >> i * 8) ) >> (3 - i) * 8).to_ulong());
		}
	}
}

Block::Block(std::bitset<32>* p_expanded_key, unsigned short nr) : mpExpandedKey(p_expanded_key), mNr(nr)
{
	std::bitset<8> input[nb * nb] = { std::bitset<8>(50), std::bitset<8>(67), std::bitset<8>(246), std::bitset<8>(168),
									std::bitset<8>(136), std::bitset<8>(90), std::bitset<8>(48), std::bitset<8>(141),
									std::bitset<8>(49), std::bitset<8>(49), std::bitset<8>(152), std::bitset<8>(162),
									std::bitset<8>(224), std::bitset<8>(55), std::bitset<8>(7), std::bitset<8>(52) };

	FillState(input);
	Encrypt();
	Decrypt();
}

void Block::Decrypt()
{
	AddRoundKey(mNr);

	for (unsigned short i = mNr - 1; i > 0; i--)
	{
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(i);
		InvMixColumns();
	}

	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	PrintState();
}

void Block::Encrypt()
{
	AddRoundKey(0);

	for (unsigned short i = 1; i < mNr; i++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(i);
	}

	SubBytes();
	ShiftRows();
	AddRoundKey(mNr);

	PrintState();
}

void Block::FillState(std::bitset<8> input[])
{
	for (unsigned short i = 0; i < nb; i++)
	{
		for (unsigned short j = 0; j < nb; j++)
		{
			mState[j][i] = input[nb * i + j];
		}
	}
}

void Block::InvMixColumns()
{
	for (unsigned short c = 0; c < nb; c++)
	{
		std::bitset<8> temp_column[nb];
		for (unsigned short r = 0; r < nb; r++)
		{
			temp_column[r] = Multiply(mState[r % nb][c], std::bitset<8>(0xe)) ^ Multiply(mState[(r + 1) % 4][c], std::bitset<8>(0xb)) ^ 
				Multiply(mState[(r + 2) % 4][c], std::bitset<8>(0xd)) ^ Multiply(mState[(r + 3) % 4][c], std::bitset<8>(0x9));
		}
		for (unsigned short i = 0; i < nb; i++)
		{
			mState[i][c] = temp_column[i];
		}
	}
}

void Block::InvShiftRows()
{
	std::bitset<8> temp;
	temp = mState[1][3];
	mState[1][3] = mState[1][2];
	mState[1][2] = mState[1][1];
	mState[1][1] = mState[1][0];
	mState[1][0] = temp;

	temp = mState[2][0];
	mState[2][0] = mState[2][2];
	mState[2][2] = temp;
	temp = mState[2][1];
	mState[2][1] = mState[2][3];
	mState[2][3] = temp;

	temp = mState[3][0];
	mState[3][0] = mState[3][1];
	mState[3][1] = mState[3][2];
	mState[3][2] = mState[3][3];
	mState[3][3] = temp;
}

void Block::InvSubBytes()
{
	for (unsigned short i = 0; i < nb; i++)
	{
		for (unsigned short j = 0; j < nb; j++)
		{
			mState[i][j] = InvSubByte(mState[i][j]);
		}
	}
}

void Block::MixColumns()
{
	for (unsigned short c = 0; c < nb; c++)
	{
		std::bitset<8> temp_column[nb];
		for (unsigned short r = 0; r < nb; r++)
		{
			temp_column[r] = Multiply(mState[r % nb][c], std::bitset<8>(0x2)) ^ Multiply(mState[(r + 1) % 4][c], std::bitset<8>(0x3)) ^ mState[(r + 2) % 4][c] ^ mState[(r + 3) % 4][c];
		}
		for (unsigned short i = 0; i < nb; i++)
		{
			mState[i][c] = temp_column[i];
		}
	}
}

void Block::PrintState()
{

	for (unsigned short i = 0; i < nb; i++)
	{
		for (unsigned short c = 0; c < nb; c++)
		{
			std::cout << mState[i][c].to_ulong() << "  ";
		}
		std::cout << std::endl;
	}
}

void Block::ShiftRows()
{
	std::bitset<8> temp;
	temp = mState[1][0];
	mState[1][0] = mState[1][1];
	mState[1][1] = mState[1][2];
	mState[1][2] = mState[1][3];
	mState[1][3] = temp;

	temp = mState[2][0];
	mState[2][0] = mState[2][2];
	mState[2][2] = temp;
	temp = mState[2][1];
	mState[2][1] = mState[2][3];
	mState[2][3] = temp;

	temp = mState[3][3];
	mState[3][3] = mState[3][2];
	mState[3][2] = mState[3][1];
	mState[3][1] = mState[3][0];
	mState[3][0] = temp;
}

void Block::SubBytes()
{
	for (unsigned short i = 0; i < nb; i++)
	{
		for (unsigned short j = 0; j < nb; j++)
		{
			mState[i][j] = SubByte(mState[i][j]);
		}
	}
}