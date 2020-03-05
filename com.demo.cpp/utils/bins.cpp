#include "../stdafx.h"
#include "bins.h"
#include <cmath>
#include <algorithm>



string Dec2Hex(int dec) {
	static const char * hex = "0123456789ABCDEF";
	string hexs("0");
	while(dec > 0) {
		hexs.push_back(hex[dec % 16]);
		dec /= 16;
	} 
	return hex;
}

BYTE Bin2Byte(BYTES bin) {
	return bin[0];
}

string Bin2Hex(BYTES bin) {
	size_t len = bin.size();
	string hex, byte;
	for(size_t i = 0; i < len; i++) {
		byte = Dec2Hex((int)bin[i]);
		if(byte.length() < 2) byte = "0" + byte;
		hex += byte + " ";
	}
	return hex;
}

INT32 Bin2Int(BYTES bin) {
	INT32 result = 0;
	for(int i = 0; i < sizeof(INT32); i++) {
		result += (INT32)(bin[bin.size() - 1 - i]) * (INT32)pow(256, i);
	}
	return result;
}

INT64 Bin2Long(BYTES bin) {
	INT64 result = 0;
	for(int i = 0; i < sizeof(INT64); i++) {
		result += (INT64)(bin[bin.size() - 1 - i]) * (INT64)pow(256, i);
	}
	return result;
}

INT16 Bin2Short(BYTES bin) {
	INT16 result = 0;
	for(int i = 0; i < sizeof(INT16); i++) {
		result += (INT16)(bin[bin.size() - 1 - i]) * (INT16)pow(256, i);
	}
	return result;
}

BYTES Byte2Bin(BYTE byte) {
	BYTES bin(1, byte);
	return bin;
}

BYTES Int2Bin(INT32 _int_32) {
	BYTES bin(sizeof(INT32), 0);
	UINT32 u = (unsigned)_int_32;
	for(int i = 0; i < sizeof(INT32); i++) {
		bin[i] = u % 256;
		u /= 256;
	}
	reverse(bin.begin(), bin.end());
	return bin;
}

BYTES Long2Bin(INT64 _int_64) {
	BYTES bin(sizeof(INT64), 0);
	UINT64 u = (unsigned)_int_64;
	for(int i = 0; i < sizeof(INT64); i++) {
		bin[i] = u % 256;
		u /= 256;
	}
	reverse(bin.begin(), bin.end());
	return bin;
}

BYTES Short2Bin(INT16 _int_16) {
	BYTES bin(sizeof(INT16), 0);
	UINT16 u = (unsigned)_int_16;
	for(int i = 0; i < sizeof(INT16); i++) {
		bin[i] = u % 256;
		u /= 256;
	}
	reverse(bin.begin(), bin.end());
	return bin;
}
