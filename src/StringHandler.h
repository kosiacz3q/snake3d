#ifndef STRINGHANDLER_H_
#define STRINGHANDLER_H_

#include <string>
#include <iostream>
#include <sstream>

class StringHandler
{
	public:
		template<typename T>
		static std::string TToStr(const T &t)
		{
			std::ostringstream oss;
			oss << t;
			return std::string(oss.str());
		}

		static std::string padTo(std::string &str, const size_t num, const char paddingChar = ' ')
		{
			while (num > str.size())
				str += paddingChar;

			return str;
		}
	private:
		StringHandler();
};

#endif /* STRINGHANDLER_H_ */
