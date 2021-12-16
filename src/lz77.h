#pragma once

#ifndef LZ_77_HH_DEF1003
#define LZ_77_HH_DEF1003

#include "defines.h"
#include "lz77-file.h"

class lz77Alg
{
private:
	lz77Alg();

	int strpos(char* src, int len, char* sub, int sub_len);
	void add_dict(char c);
	void find_match();

private:
	char buffer[BUF_LEN + 1], dict[DICT_LEN];
	int match_pos, match_len, unmatched;
	int dict_pos ;

	Lz77File& archive;
	int in_file, out_file;
public:
	lz77Alg(int InFile, int OutFile, Lz77File& arch);

	void encode();
	void decode();

};


#endif  //LZ_77_HH_DEF1003


