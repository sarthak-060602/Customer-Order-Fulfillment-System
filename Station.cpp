#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include"Station.h"
#include"Utilities.h"

using namespace std;

namespace seneca {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(const string& record) {
	
		Utilities myUtil;
		size_t next_pos = 0;
		bool more = true;

		m_id = ++Station::id_generator;

		try {
			m_itemName = myUtil.extractToken(record, next_pos, more);
			m_serialNumber = stoi(myUtil.extractToken(record, next_pos, more));
			m_quantity = stoi(myUtil.extractToken(record, next_pos, more));
			if (myUtil.getFieldWidth() > Station::m_widthField) {
				m_widthField = myUtil.getFieldWidth();
				
			}
			m_itemDesc = myUtil.extractToken(record, next_pos, more);
		}
		catch (...) {
			throw runtime_error("Failed to read data in Station module!!!\n\n\n");
		}
		
		//if (record.empty()) {

		//}
		//else {
		//	m_itemName = myUtil.extractToken(record, next_pos, more);

		//	if (more) {
		//		= myUtil.extractToken(record, next_pos, more);
		//		//convert its its native typed
		//	}
		//	if (more) {

		//	}
		//	if(fields)
		//}

	}

	const std::string& Station::getItemName() const
	{
		// TODO: insert return statement here
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		m_quantity = (m_quantity > 0) ? m_quantity - 1 : m_quantity;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::setfill('0') << right << m_id << " | "
			<< std::setw(m_widthField) << setfill(' ') << std::left << m_itemName << " | "
			<< std::setw(6) <<  setfill('0') << std::right << m_serialNumber << " | ";

		if (full) {
			os << std::setw(4) << setfill(' ') << m_quantity << " | " << m_itemDesc;
		}

		os << std::endl;
	}


	
}