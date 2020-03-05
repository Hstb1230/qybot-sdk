#pragma once
/* 
 * Normal String
 * For support string, wstring and other string_type in the feture
 * by demo
*/

class nstring {
	private:
		static const int STRING_TYPE_NULL = NULL;
		static const int STRING_TYPE_CSTRING = 1;
		static const int STRING_TYPE_WSTRING = 2;
		static const int STRING_TYPE_U8STRING = 3;

		int stringType;
		string cString;
		wstring wString;
		string u8String;

	public:
		nstring();
		nstring(const char * _nstring, const bool isUTF8 = false);
		nstring(const string _nstring, const bool isUTF8 = false);
		nstring(const wchar_t * _nstring);
		nstring(const wstring _nstring);
		nstring(const nstring & _nstring);
		nstring(const nstring * _nstring);
		nstring(const BYTES &);

		static const nstring transform(const nstring _nstring, const int to_type);

		operator const char *() ;
		operator const string() const ;
		operator const wchar_t *();
		operator const wstring() const;

		const char * cStr();
		const wchar_t * wStr();
		const char * u8Str();

		static const char * cStr(const nstring & _nstring);
		static const wchar_t * wStr(const nstring & _nstring);
		static const char * u8Str(const nstring & _nstring);

		const nstring operator+(const nstring & _nstring);
		const nstring operator+(const char * _cstring);
		const nstring operator+(const string & _cstring);
		friend const nstring operator+(const nstring _nstring, nstring & _nstring2);
		friend const nstring operator+(const nstring _nstring, string & _cstring);
		friend const nstring operator+(string & _cstring, const nstring _nstring);
		const nstring operator+(const wchar_t * _wstring);
		const nstring operator+(const wstring & _wstring);
		friend const nstring operator+(const wstring & _wstring, const nstring _nstring);

		const nstring & operator=(const nstring & _nstring);

		const nstring & operator+=(const nstring & _nstring);
		const nstring & operator+=(const char * _cstring);
		const nstring & operator+=(const string & _cstring);
		friend const string & operator+=(string & _cstring, const nstring & _nstring);
		nstring & operator+=(const wchar_t * _wstring);
		nstring & operator+=(const wstring _wstring);
		friend const wstring & operator+=(wstring & _wstring, const nstring _nstring);

		nstring operator*(const int _repeatCount);
		bool operator==(const nstring & _nstring);
		bool operator==(const char * _cstring);
		bool operator==(const string & _cstring);
		bool operator==(const wchar_t * _wstring);
		bool operator==(const wstring & _wstring);
};
