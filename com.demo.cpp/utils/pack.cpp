#include "../stdafx.h"
#include "bins.h"
#include "pack.h"

void Pack::Empty()
{
	this->m_bin.clear();
}

BYTES Pack::GetAll()
{
	return this->m_bin;
}

size_t Pack::Len()
{
	return this->m_bin.size();
}

void Pack::SetBin(BYTES bin)
{
	this->m_bin.insert(this->m_bin.end(), bin.begin(), bin.end());
}

void Pack::SetByte(BYTE byte)
{
	this->m_bin.push_back(byte);
}

void Pack::SetData(BYTES bin)
{
	this->m_bin = bin;
}

void Pack::SetInt(INT32 _int_32)
{
	this->SetBin(Int2Bin(_int_32));
}

void Pack::SetShort(INT16 _int_16)
{
	this->SetBin(Short2Bin(_int_16));
}

void Pack::SetLong(INT64 _int_64)
{
	this->SetBin(Long2Bin(_int_64));
}

void Pack::SetStr(string str)
{
	BYTES bin(str.cbegin(), str.cend());
	this->SetBin(bin);
}

void Pack::SetLenStr(string str)
{
	BYTES bin(str.cbegin(), str.cend());
	this->SetToken(bin);
}

void Pack::SetToken(BYTES bin)
{
	this->SetShort((INT16)bin.size());
	this->SetBin(bin);
}
