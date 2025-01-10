#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
namespace seneca {

	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimiter;
		static void trim(std::string& str)
		{
			size_t i = 0u;
			for (i = 0u; i < str.length() && str[i] == ' '; ++i);
			str = str.substr(i);

			for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
			str = str.substr(0, i);
		}
	public:
		void setFieldWidth(size_t newWidth);
		
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();


	};
}
#endif // !SENECA_UTILIES_H