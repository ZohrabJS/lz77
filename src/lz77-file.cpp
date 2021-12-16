#include "lz77-file.h"


//---------------------------------------------------------
// writes 0s
void Lz77File::flush()
{
	for (int i = 0; i < 7; i++) putbit(0);
}
//---------------------------------------------------------
// read mode
void Lz77File::assign_write(int h)
{
	handle = h;
	buff_char = 0;
	mask = 128;
}
//---------------------------------------------------------
// write mode
void Lz77File::assign_read(int h)
{
	handle = h;
	buff_char = 0;
	mask = 0;
}
//---------------------------------------------------------
// read bit
bool Lz77File::getbit()
{
	if ((mask >>= 1) == 0)
	{
		_read(handle, &buff_char, 1);
		mask = 128;//binary 10000000
	}
	return (buff_char & mask) != 0;
}
//---------------------------------------------------------
// write bit
void Lz77File::putbit(bool val)
{
	if (val) buff_char |= mask;
	if ((mask >>= 1) == 0)
	{
		_write(handle, &buff_char, 1);
		buff_char = 0;
		mask = 128;//binary 10000000
	}
}
//---------------------------------------------------------
// write bits
void Lz77File::putbits(int val, int n)
{
	int m = 1;
	for (int i = 0; i < n; i++)
	{
		putbit((val & m) != 0);
		m <<= 1;
	}
}
//---------------------------------------------------------
// read bits
int Lz77File::getbits(int n)
{
	int result = 0;
	for (int i = 0; i < n; i++)
		result |= getbit() << i;
	return result;
}
//=========================================================
