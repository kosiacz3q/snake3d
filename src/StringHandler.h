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

	private:
		StringHandler();
};

#endif /* STRINGHANDLER_H_ */
