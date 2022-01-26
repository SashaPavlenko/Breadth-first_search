#pragma once
#include <exception>
#include <string>

class MyFileExceprion : public std::exception
{
private:
	std::string m_error;

public:
	MyFileExceprion(std::string error): m_error(error) {}

	// ¬озвращаем std::string в качестве константной строки C-style
	const char* what() const noexcept { return m_error.c_str(); } // C++11 и выше
};
