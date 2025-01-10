#define _CRT_SECURE_NO_WARNINGS
#include"CustomerOrder.h"

using namespace std;

namespace seneca {

	size_t CustomerOrder::m_widthField = 0;



	CustomerOrder::CustomerOrder()
		: m_name(""),m_product(""),m_cntItem(0),m_lstItem(nullptr)
	{
	}

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		Utilities myUtil;
		size_t next_pos = 0;
		bool more = true;

		m_name = myUtil.extractToken(record, next_pos, more);
		m_product = myUtil.extractToken(record, next_pos, more);

		vector<string> tempItems;
		while (more) {
			tempItems.push_back(myUtil.extractToken(record, next_pos, more));
		}

		if (tempItems.empty()) {
			m_cntItem = 0;
			m_lstItem = nullptr;
		}
		else {
			m_cntItem = tempItems.size();
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(tempItems[i]);
			}

		}
		if (myUtil.getFieldWidth() > m_widthField) {
			m_widthField = myUtil.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		throw ("ERROR: Cannot make copies.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		m_name = move(other.m_name);
		m_product = move(other.m_product);
		m_cntItem = other.m_cntItem;
		m_lstItem = other.m_lstItem;

		other.m_cntItem = 0;
		other.m_lstItem = nullptr;
		//*this = move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		// TODO: insert return statement here
		if (this != &other) {
			if(m_lstItem){
				for (size_t i = 0; i < m_cntItem; i++) {
					
						delete m_lstItem[i];
					
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;
			}

			m_name = move(other.m_name);
			m_product = move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = move(other.m_lstItem);

			other.m_cntItem = 0;
			other.m_lstItem = nullptr;

		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName==itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {

				//checking for if order contains item or not
				if (m_lstItem[i]->m_isFilled) {
					continue;
				}
				if (station.getQuantity() > 0) {
					//updates inventory
					station.updateQuantity();

					// updates Item::m_serialNumber and Item::m_isFilled
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					// display the order is filled
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					break;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;

				}
			}
		 }
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] "
				<< setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - "
				<< ((m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED") << endl;
		}
	}







}