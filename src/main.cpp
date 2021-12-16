// main.cpp. Calls lz77 function. This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lz77-file.h"
#include "lz77.h"

int main(int argc, char *argv[])
{
	std::cout << "lz77!\n";
	std::cout << argc << std::endl;
	std::cout << argv[0] << std::endl;
	if (argc < 4)
	{
		printf("Usage:\nLZ77 e in out - encode in to out\nLZ77 d in out - decode in to out\n");
		return -1;
	}

	int in_file;  // input file
	int out_file; // output file
	Lz77File lz77f;

	// open in, out files
	in_file = _open(argv[2], _O_BINARY | _O_RDWR,
		_S_IREAD | _S_IWRITE);
	out_file = _open(argv[3], _O_BINARY | _O_WRONLY | _O_CREAT
		| _O_TRUNC, _S_IREAD | _S_IWRITE);

	lz77Alg lz77meth(in_file, out_file, lz77f);

	if (_stricmp(argv[1], "-e") == 0) // compress
	{
		lz77f.assign_write(out_file);
		lz77meth.encode();
	}
	else if (_stricmp(argv[1], "-d") == 0) //  decompress
	{
		lz77f.assign_read(in_file);
		lz77meth.decode();
	}
	else printf("Nothing to do\n");

	_close(in_file);
	_close(out_file);

	system("pause");
	return 0;


}
