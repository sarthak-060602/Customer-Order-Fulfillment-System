#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Utilities.h"

using namespace std;

namespace seneca {
	char Utilities::m_delimiter = ',';

	

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		// looking if it is end of string or not 
		if (next_pos>=str.length()) {
			more = false;
			return "";
		}


		size_t location = str.find(m_delimiter, next_pos);
		string token;
		if (location != string::npos) {
			token = str.substr(next_pos, location - next_pos);
			next_pos = location + 1;
			
		}
		else {

			token = str.substr(next_pos);
			next_pos = str.length();
			more = false;
		}

		trim(token);
		if (token.empty() && next_pos != str.length() + 1) {
			more = false;
			throw runtime_error("No More data left to extract");
		}


		more = (next_pos < str.length());

		if (token.length() > m_widthField) {
			m_widthField = token.length();

		}

		//string data = str;
		//string one = data.substr(0, data.find(next_pos));
		//data.erase(0, data.find(next_pos));

		//more = (one.empty()) ? true : false;

		//if (str[0] == ' ') {

		//}


		return token;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}