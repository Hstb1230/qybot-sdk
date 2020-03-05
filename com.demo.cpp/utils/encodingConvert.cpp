#include "stdafx.h"
#include <string>
#include <codecvt>
#include <locale>
#include "encodingConvert.h"

/* 
    wstring与string互转参考
    https://gist.github.com/pezy/8571764
*/
/* wstring转string */
std::string wstringToAnsi(std::wstring wText)
{
    int aLen = WideCharToMultiByte(CP_ACP, 0, &wText[0], -1, NULL, 0, NULL, NULL);
    if(aLen == NULL) 
        return "";
    std::string aText(aLen, 0);
    WideCharToMultiByte(CP_ACP, 0, &wText[0], wText.size(), &aText[0], aLen, NULL, NULL);
    return aText;
}

/* string转wstring */
std::wstring ansiToWstring(std::string cText)
{
    int wLen = MultiByteToWideChar(CP_ACP, 0, &cText[0], cText.size(), NULL, 0);
    if(wLen == NULL)
        return L"";
    std::wstring wText(wLen, 0);
    MultiByteToWideChar(CP_ACP, 0, &cText[0], cText.size(), &wText[0], wLen);
    return wText;
}

/*************************************************************/
/* RFC 3629 defines the mapping as follows :
 *
 * Char. number range  |        UTF-8 octet sequence
 *    (hexadecimal)    |              (binary)
 * --------------------+---------------------------------------------
 * 0000 0000-0000 007F | 0xxxxxxx
 * 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
 * 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
 * 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Encoding a character to UTF-8 proceeds as follows:
 *
 * 1.  Determine the number of octets required from the character number
 *     and the first column of the table above.  It is important to note
 *     that the rows of the table are mutually exclusive, i.e., there is
 *     only one valid way to encode a given character.
 *
 * 2.  Prepare the high-order bits of the octets as per the second
 *     column of the table.
 *
 * 3.  Fill in the bits marked x from the bits of the character number,
 *     expressed in binary.  Start by putting the lowest-order bit of
 *     the character number in the lowest-order position of the last
 *     octet of the sequence, then put the next higher-order bit of the
 *     character number in the next higher-order position of that octet,
 *     etc.  When the x bits of the last octet are filled in, move on to
 *     the next to last octet, then to the preceding one, etc. until all
 *     x bits are filled in.
 *
 * The definition of UTF-8 prohibits encoding character numbers between
 * U+D800 and U+DFFF,...
 */

#include <locale>
#include <codecvt>

 /* wstring转UTF-8 */
std::string wstringToUtf8(const std::wstring& str)
{
	std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.to_bytes(str);
}

/* UTF-8转wstring */
std::wstring utf8ToWstring(const std::string& str)
{
	std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.from_bytes(str);
}

/* string转UTF-8 */
std::string stringToUtf8(const std::string& str) {
	// 先转wstring, 再转UTF-8
	return wstringToUtf8(ansiToWstring(str));
}

/* UTF-8转string */
std::string utf8ToString(const std::string& str) {
	// 先转wstring, 再转string
	return wstringToAnsi(utf8ToWstring(str));
}
