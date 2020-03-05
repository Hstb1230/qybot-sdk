#pragma once

/* wstring转string */
std::string wstringToAnsi(std::wstring wText);

/* string转wstring */
std::wstring ansiToWstring(std::string cText);

/* wstring转UTF-8 */
std::string wstringToUtf8(const std::wstring & str);

/* UTF-8转wstring */
std::wstring utf8ToWstring(const std::string & str);

/* string转UTF-8 */
std::string stringToUtf8(const std::string & str);

/* UTF-8转string */
std::string utf8ToString(const std::string & str);
