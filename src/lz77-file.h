#pragma once

#ifndef LZ_77_FILE__HH_DEF1001
#define LZ_77_FILE__HH_DEF1001

#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

//  Class for Lz77 file . Declaration
class Lz77File
{
	int handle;
	unsigned char buff_char, mask;
public:
	void assign_read(int h);
	void assign_write(int h);
	void flush();

	void putbit(bool val);
	bool getbit();

	void putbits(int val, int n);
	int getbits(int n);
};

#endif  //LZ_77_FILE__HH_DEF1001
