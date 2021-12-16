#include "lz77.h"

#include <io.h>
#include <fcntl.h>
#include <cstring>

// Returns pos from the end of src. Vals [1,len] 

int lz77Alg::strpos(char* src, int len, char* sub, int sub_len)
{
	for (int i = 0; i <= len - sub_len; i++)
		if (memcmp(src + i, sub, sub_len) == 0) return len - i;
	return 0;

}


//  Add char c to the dict
void lz77Alg::add_dict(char c)
{
	if (dict_pos == (DICT_LEN - 1))
	{
		memcpy(dict, dict + 1, DICT_LEN - 1);
		dict[dict_pos - 1] = c;
	}
	else
	{
		dict[dict_pos] = c;
		dict_pos++;
	}
}

// Find match in dict
void lz77Alg::find_match()
{
	match_len = 0;
	match_pos = 1;
	while (match_len < BUF_LEN)
	{
		_read(in_file, &buffer[match_len], 1);
		if (_eof(in_file)) break;
		int pos1 = strpos(dict, dict_pos, buffer, match_len + 1);
		if (pos1 == 0) break;
		match_pos = pos1;
		match_len++;
	}
	unmatched = buffer[match_len];
}

lz77Alg::lz77Alg(int InFile, int OutFile, Lz77File& arch) : in_file(InFile) , out_file(OutFile) , archive(arch)
{
	match_pos = match_len =  unmatched = dict_pos = 0;

}


//---------------------------------------------------------
//
void lz77Alg::encode()
{
	while (!_eof(in_file))
	{
		find_match();
		archive.putbits(match_pos, OFFS_LN);
		archive.putbits(match_len, LEN_LN);
		if (match_len < BUF_LEN)
			archive.putbits(unmatched, BYTE_LN);

		for (int i = 0; i < match_len; i++)
			add_dict(buffer[i]);
		if (match_len < BUF_LEN)
			add_dict(unmatched);
	}
	archive.putbits(0, BYTE_LN);
	archive.flush();
}
//---------------------------------------------------------
//
void lz77Alg::decode()
{
	char c;
	int i;
	for (;;)
	{
		match_pos = archive.getbits(OFFS_LN);
		if (match_pos == 0) break;
		match_len = archive.getbits(LEN_LN);
		memcpy(buffer, dict + dict_pos - match_pos, match_len);
		_write(out_file, buffer, match_len);
		for (i = 0; i < match_len; i++)
			add_dict(buffer[i]);
		if (match_len < BUF_LEN)
		{
			c = archive.getbits(BYTE_LN);
			add_dict(c);
			_write(out_file, &c, 1);
		}
	}
}
//---------------------------------------------------------
