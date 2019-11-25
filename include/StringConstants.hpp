#ifndef STRINGCONSTANTS_H
#define STRINGCONSTANTS_H

#include <string>

template <typename T>
class StringConstants {};

template<>
class StringConstants<std::wstring> {
public:
	const wchar_t newline_ = L'\n';
  const wchar_t user_continuation_ = L'\r';
  const wchar_t auto_continuation_ = L'\a';
  const std::wstring empty_ = L"";
};

template<>
class StringConstants<std::string> {
public:
	const char newline_ = '\n';
  const char user_continuation_ = '\r';
  const char auto_continuation_ = '\a';
  const std::string empty_ = "";
};

#endif // STRINGCONSTANTS_H
