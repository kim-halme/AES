#pragma once

#include <bitset>

const std::bitset<8> IRREDUCIBLE_POLYNOMIAL(27);
const unsigned short nb = 4;

std::bitset<8> AffineTransformation(std::bitset<8> set);
void FillSboxes();
std::bitset<8> InvSubByte(std::bitset<8> byte);
std::bitset<8> ModularLeftShift(std::bitset<8> set);
std::bitset<8> MultiplicativeInverse(std::bitset<8> set);
std::bitset<8> Multiply(std::bitset<8> set1, std::bitset<8> set2);
std::bitset<8> SubByte(std::bitset<8> byte);
