#ifndef SRC_GUI_STRINGDRAWER_H_
#define SRC_GUI_STRINGDRAWER_H_

#include <string>

STATIC class StringDrawer
{
	public:
		static void drawString(const std::string text, const float x, const float y, const float z, void* font = nullptr,const float* color = nullptr);
		static void strokeString(const std::string text, const float x, const float y, const float z, void* font = nullptr,const float* color = nullptr);
	private:
		StringDrawer();
		virtual ~StringDrawer();


};

#endif /* SRC_GUI_STRINGDRAWER_H_ */
