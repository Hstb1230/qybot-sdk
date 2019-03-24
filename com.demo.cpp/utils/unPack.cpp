#include "../stdafx.h"
#include "bins.h"
#include "unPack.h"

void UnPack::Empty()
{
	this->m_bin.clear();
}

BYTES & UnPack::GetAll()
{
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + (this->m_bin.size() - this->location + 1);
	BYTES bin(from, to);
	return bin;
}

BYTES UnPack::GetBin(INT32 len)
{
	if(len <= 0) return BYTES();
	//BYTES bin;
	//bin.assign(this->m_bin[this->location - 1], this->m_bin[this->location - 1 + len]);
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + len;
	BYTES bin(from, to);
	this->location += bin.size();
	return bin;
}

BYTE UnPack::GetByte()
{
	//BYTES bin;
	//bin.assign(this->m_bin[this->location - 1], this->m_bin[this->location - 1 + sizeof(BYTE)]);
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + sizeof(BYTE);
	BYTES bin(from, to);
	this->location += bin.size();
	return Bin2Byte(bin);
}

INT32 UnPack::GetInt()
{
	/*
	BYTES bin;
	bin.assign(this->m_bin[this->location - 1], this->m_bin[this->location - 1 + sizeof(INT32)]);
	*/
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + sizeof(INT32);
	BYTES bin(from, to);
	//BYTES bin(this->m_bin[this->location], this->m_bin[this->location + (int)sizeof(INT32)]);
	this->location += bin.size();
	//MessageBox(NULL, std::to_wstring(location).c_str(), L"location", 0);
	return Bin2Int(bin);
}

INT64 UnPack::GetLong()
{
	//BYTES bin;
	//bin.assign(this->m_bin[this->location - 1], this->m_bin[this->location - 1 + sizeof(INT64)]);
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + sizeof(INT64);
	BYTES bin(from, to);
	this->location += bin.size();
	return Bin2Long(bin);
}

INT16 UnPack::GetShort()
{
	//BYTES bin;
	//bin.assign(this->m_bin[this->location - 1], this->m_bin[this->location - 1 + sizeof(INT16)]);
	BYTES::const_iterator from = this->m_bin.cbegin() + this->location;
	BYTES::const_iterator to = from + sizeof(INT16);
	BYTES bin(from, to);
	this->location += bin.size();
	return Bin2Short(bin);
}

string UnPack::GetLenStr()
{
	BYTES bin = this->GetLenBin();
	string str;
	for(size_t i = 0; i < bin.size(); i++)
		str.push_back(bin[i]);
	return str;
}

BYTES UnPack::GetLenBin()
{
	INT32 len = this->GetShort();
	return this->GetBin(len);
}

BYTES UnPack::GetToken()
{
	return this->GetLenBin();
}

INT32 UnPack::Len()
{
	return this->m_bin.size() - this->location + 1;
}

void UnPack::SetData(BYTES bin)
{
	this->m_bin = bin;
	this->location = 0;
}
