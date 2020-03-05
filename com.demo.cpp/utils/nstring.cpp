#include "stdafx.h"
#include "nstring.h"
#include <string.h>
#include <wchar.h>
#include "utils/encodingConvert.h"

nstring::nstring()
{
	this->stringType = STRING_TYPE_NULL;
}

nstring::nstring(const char * _nstring, const bool isUTF8)
{
	if(isUTF8) {
		this->u8String.assign(_nstring);
		this->stringType = STRING_TYPE_U8STRING;
	} else {
		this->cString.assign(_nstring);
		this->stringType = STRING_TYPE_CSTRING;
	}
}

nstring::nstring(const string _nstring, const bool isUTF8)
{
	if(isUTF8) {
		this->u8String.assign(_nstring);
		this->stringType = STRING_TYPE_U8STRING;
	} else {
		this->cString.assign(_nstring);
		this->stringType = STRING_TYPE_CSTRING;
	}
}

nstring::nstring(const wchar_t * _nstring)
{
	this->wString.assign(_nstring);
	this->stringType = STRING_TYPE_WSTRING;
}

nstring::nstring(const wstring _nstring)
{
	this->wString.assign(_nstring);
	this->stringType = STRING_TYPE_WSTRING;
}

nstring::nstring(const nstring & _nstring)
{
	this->stringType = _nstring.stringType;
	if(this->stringType == STRING_TYPE_NULL)
		return;
	else if(_nstring.stringType == STRING_TYPE_CSTRING)
		this->cString.assign(_nstring.cString);
	else if(_nstring.stringType == STRING_TYPE_WSTRING)
		this->wString.assign(_nstring.wString);
	else if(_nstring.stringType == STRING_TYPE_U8STRING)
		this->u8String.assign(_nstring.u8String);
}

nstring::nstring(const nstring * _nstring)
{
	this->stringType = _nstring->stringType;
	if(this->stringType == STRING_TYPE_NULL)
		return;
	else if(this->stringType == STRING_TYPE_CSTRING)
		this->cString.assign(_nstring->cString);
	else if(this->stringType == STRING_TYPE_WSTRING)
		this->wString.assign(_nstring->wString);
	else if(this->stringType == STRING_TYPE_U8STRING)
		this->u8String.assign(_nstring->u8String);
}

nstring::nstring(const BYTES & _bytes)
{
	this->u8String.assign(_bytes.begin(), _bytes.end());
	this->u8String.push_back('\0');
	this->stringType = nstring::STRING_TYPE_U8STRING;
}

const nstring nstring::transform(const nstring _nstring, const int to_type)
{
	nstring _trans_nstring(_nstring);
	if(to_type == STRING_TYPE_NULL) {
		_trans_nstring.stringType = STRING_TYPE_NULL;
	} else if(to_type == STRING_TYPE_CSTRING) {
		if(_trans_nstring.stringType == STRING_TYPE_WSTRING)
			_trans_nstring.cString = wstringToAnsi(_trans_nstring.wString);
		else if(_trans_nstring.stringType == STRING_TYPE_U8STRING)
			_trans_nstring.cString = utf8ToString(_trans_nstring.u8String);
	} else if(to_type == STRING_TYPE_WSTRING) {
		if(_trans_nstring.stringType == STRING_TYPE_CSTRING)
			_trans_nstring.wString = ansiToWstring(_trans_nstring.cString);
		else if(_trans_nstring.stringType == STRING_TYPE_U8STRING)
			_trans_nstring.wString = utf8ToWstring(_trans_nstring.u8String);
	} else if(to_type == STRING_TYPE_U8STRING) {
		if(_trans_nstring.stringType == STRING_TYPE_CSTRING)
			_trans_nstring.u8String = stringToUtf8(_trans_nstring.cString);
		else if(_trans_nstring.stringType == STRING_TYPE_WSTRING)
			_trans_nstring.u8String = wstringToUtf8(_trans_nstring.wString);
	}
	return _trans_nstring;
}

nstring::operator const char*()
{
	if(this->stringType == nstring::STRING_TYPE_NULL)
		return "";
	nstring _trans_nstring(nstring::transform(*this, nstring::STRING_TYPE_CSTRING));
	this->cString = _trans_nstring.cString;
	return this->cString.c_str();
}

nstring::operator const string() const
{
	if(this->stringType == nstring::STRING_TYPE_NULL)
		return "";
	nstring _trans_nstring = nstring::transform(*this, nstring::STRING_TYPE_CSTRING);
	return _trans_nstring.cString;
}

nstring::operator const wchar_t*()
{
	if(this->stringType == nstring::STRING_TYPE_NULL)
		return L"";
	nstring _trans_nstring = nstring::transform(*this, nstring::STRING_TYPE_WSTRING);
	this->wString = _trans_nstring.wString;
	return this->wString.c_str();
}

nstring::operator const wstring() const
{
	if(this->stringType == nstring::STRING_TYPE_NULL)
		return L"";
	nstring _trans_nstring = nstring::transform(*this, nstring::STRING_TYPE_WSTRING);
	return _trans_nstring.wString.c_str();
}

const char * nstring::cStr()
{
	return nstring::cStr(this);
}

const char * nstring::cStr(const nstring & _nstring)
{
	if(_nstring.stringType == nstring::STRING_TYPE_NULL)
		return "";
	else if(_nstring.stringType == nstring::STRING_TYPE_CSTRING)
		return _nstring.cString.c_str();
	nstring _trans_nstring = nstring::transform(_nstring, nstring::STRING_TYPE_CSTRING);
	return _trans_nstring.cString.c_str();
}

const wchar_t * nstring::wStr()
{
	return nstring::wStr(this);
}

const wchar_t * nstring::wStr(const nstring & _nstring)
{
	if(_nstring.stringType == nstring::STRING_TYPE_NULL)
		return L"";
	else if(_nstring.stringType == nstring::STRING_TYPE_WSTRING)
		return _nstring.wString.c_str();
	nstring _trans_nstring = nstring::transform(_nstring, nstring::STRING_TYPE_WSTRING);
	return _trans_nstring.wString.c_str();
}

const char * nstring::u8Str()
{
	return nstring::u8Str(*this);
}

const char * nstring::u8Str(const nstring & _nstring)
{
	if(_nstring.stringType == nstring::STRING_TYPE_NULL)
		return u8"";
	else if(_nstring.stringType == nstring::STRING_TYPE_U8STRING)
		return _nstring.u8String.c_str(); 
	nstring _trans_nstring = nstring::transform(_nstring, nstring::STRING_TYPE_U8STRING);
	return _trans_nstring.u8String.c_str();
}


const nstring nstring::operator+(const nstring & _nstring)
{
	nstring _result_nstring(this);
	if(this->stringType == STRING_TYPE_NULL) 
		_result_nstring.stringType = _nstring.stringType;
	nstring _trans_nstring = nstring::transform(_nstring, this->stringType);
	if(this->stringType == STRING_TYPE_CSTRING) {
		_result_nstring.cString += _trans_nstring.cString;
	} else if(this->stringType == STRING_TYPE_WSTRING) {
		_result_nstring.wString += _trans_nstring.wString;
	}
	return _result_nstring;
}

const nstring nstring::operator+(const char * _cstring)
{
	nstring _nstring(_cstring);
	return *this + _nstring;
}

const nstring & nstring::operator=(const nstring & _nstring)
{
	this->stringType = _nstring.stringType;
	if(this->stringType == STRING_TYPE_CSTRING)
		this->cString = _nstring.cString;
	else if(this->stringType == STRING_TYPE_WSTRING)
		this->wString = _nstring.wString;
	else if(this->stringType == STRING_TYPE_U8STRING)
		this->u8String = _nstring.u8String;
	return *this;
}

const nstring & nstring::operator+=(const nstring & _nstring)
{
	if(this->stringType == STRING_TYPE_NULL) {
		this->stringType = _nstring.stringType;
	}
	nstring _trans_nstring = nstring::transform(_nstring, this->stringType);
	if(this->stringType == STRING_TYPE_CSTRING) {
		this->cString += _trans_nstring.cString;
	} else if(this->stringType == STRING_TYPE_WSTRING) {
		this->wString += _trans_nstring.wString;
	}
	return *this;
}

const nstring & nstring::operator+=(const char * _cstring)
{
	nstring _nstring(_cstring);
	*this += _nstring;
	return *this;
}

const nstring & nstring::operator+=(const string & _cstring)
{
	nstring _nstring(_cstring);
	*this += _nstring;
	return *this;
}

nstring & nstring::operator+=(const wchar_t * _wstring)
{
	nstring _nstring(_wstring);
	*this += _nstring;
	return *this;
}

nstring & nstring::operator+=(const wstring _wstring)
{
	nstring _nstring(_wstring);
	*this += _nstring;
	return *this;
}

const nstring nstring::operator+(const string & _cstring)
{
	nstring _nstring(_cstring);
	return *this + _nstring;
}

const nstring nstring::operator+(const wchar_t * _wstring)
{
	nstring _nstring(_wstring);
	return *this + _nstring;
}

const nstring nstring::operator+(const wstring & _wstring)
{
	nstring _nstring(_wstring);
	return *this + _nstring;
}

nstring nstring::operator*(const int _repeatCount)
{
	nstring _result_nstring(this);
	if(_repeatCount < 0) {
		// 不合法的数据
	} else if(_repeatCount == 0) {
		// 清空
		this->stringType = STRING_TYPE_NULL;
	} else if(this->stringType == STRING_TYPE_NULL) {
		// 空串, 无法操作
	} else if(this->stringType == STRING_TYPE_CSTRING) {
		auto _repeatCString = _result_nstring.cString.c_str();
		auto len = _result_nstring.cString.length();
		char * _resultCString = new char[len * _repeatCount + 1];
		memset(_resultCString, 0, (len * _repeatCount + 1) * sizeof(char));
		for(int i = 0; i < _repeatCount; i++) {
			strcpy_s((_resultCString + i * len), _repeatCount, _repeatCString);
		}
		_result_nstring.stringType = STRING_TYPE_CSTRING;
		_result_nstring.cString.assign(_resultCString);
		delete [] _resultCString;
	} else if(this->stringType == STRING_TYPE_WSTRING) {
		auto _repeatWString = _result_nstring.wString.c_str();
		auto len = _result_nstring.wString.length();
		wchar_t * _resultWString = new wchar_t[len * _repeatCount + 1];
		memset(_resultWString, 0, (len * _repeatCount + 1) * sizeof(wchar_t));
		for(int i = 0; i < _repeatCount; i++) {
			wcscpy_s((_resultWString + i * len), _repeatCount, _repeatWString);
		}
		_result_nstring.stringType = STRING_TYPE_WSTRING;
		_result_nstring.wString.assign(_resultWString);
		delete [] _resultWString;
	} else if(this->stringType == STRING_TYPE_U8STRING) {
		auto _repeatU8String = _result_nstring.u8String.c_str();
		auto len = _result_nstring.u8String.length();
		char * _resultU8String = new char[len * _repeatCount + 1];
		memset(_resultU8String, 0, (len * _repeatCount + 1) * sizeof(char));
		for(int i = 0; i < _repeatCount; i++) {
			strcpy_s((_resultU8String + i * len), _repeatCount, _repeatU8String);
		}
		_result_nstring.stringType = STRING_TYPE_U8STRING;
		_result_nstring.u8String.assign(_resultU8String);
		delete[] _resultU8String;
	}
	return _result_nstring;
}

bool nstring::operator==(const nstring & _nstring)
{
	if(this->stringType != _nstring.stringType)
		return false;
	else if(this->stringType == STRING_TYPE_NULL)
		return true;
	else if(this->stringType == STRING_TYPE_CSTRING)
		return this->cString == _nstring.cString;
	else if(this->stringType == STRING_TYPE_WSTRING)
		return this->wString == _nstring.wString;
	else
		return false;
}

bool nstring::operator==(const char * _cstring)
{
	if(this->stringType != STRING_TYPE_CSTRING)
		return false;
	return this->cString == _cstring;
}

bool nstring::operator==(const string & _cstring)
{
	if(this->stringType != STRING_TYPE_CSTRING)
		return false;
	return this->cString == _cstring;
}

bool nstring::operator==(const wchar_t * _wstring)
{
	if(this->stringType != STRING_TYPE_WSTRING)
		return false;
	return this->wString == _wstring;
}

bool nstring::operator==(const wstring & _wstring)
{
	if(this->stringType != STRING_TYPE_WSTRING)
		return false;
	return this->wString == _wstring;
}

const nstring operator+(const nstring _nstring, nstring & _nstring2)
{
	nstring _result_nstring(_nstring);
	_result_nstring += _nstring2;
	return _result_nstring;
}

const nstring operator+(const nstring _nstring, string & _cstring)
{
	nstring _result_nstring(_nstring);
	_result_nstring += _cstring;
	return _result_nstring;
}

const nstring operator+(string & _cstring, const nstring _nstring)
{
	nstring _result_nstring(_cstring);
	_result_nstring += _nstring;
	return _result_nstring;
}

const nstring operator+(const char * _cstring, const nstring _nstring)
{
	nstring _result_nstring(_cstring);
	_result_nstring += _nstring;
	return _result_nstring;
}

const nstring operator+(const wstring & _wstring, const nstring _nstring) 
{
	nstring _result_nstring(_wstring);
	_result_nstring += _nstring;
	return _result_nstring;
}

const string & operator+=(string & _cstring, const nstring & _nstring)
{
	nstring _trans_nstring = nstring::transform(_nstring, nstring::STRING_TYPE_CSTRING);
	_cstring.append(_trans_nstring.cStr());
	return _cstring;
}

const wstring & operator+=(wstring & _wstring, const nstring _nstring)
{
	nstring _trans_nstring = nstring::transform(_nstring, nstring::STRING_TYPE_WSTRING);
	_wstring.append(_trans_nstring.wStr());
	return _wstring;
}
