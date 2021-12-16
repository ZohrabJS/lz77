#pragma once

#ifndef DEFINES_H_HH_DEF1002
#define DEFINES_H_HH_DEF1002

//=========================================================
const unsigned short OFFS_LN	= 8;
const unsigned short LEN_LN		= 4;
const unsigned short BYTE_LN	= 8;

//#define BUF_LEN 15
const unsigned short  BUF_LEN = ((1 << LEN_LN) - 1);
//#define DICT_LEN 256
const unsigned short DICT_LEN = ((1 << OFFS_LN) - 1);

#endif  //DEFINES_H_HH_DEF1002
