#include "cipher.h"
#include "timer.h"

int main()
{
	FillSboxes();
	std::cout << std::hex;
	{
		Timer timer;
		Cipher cipher;
	}
}
