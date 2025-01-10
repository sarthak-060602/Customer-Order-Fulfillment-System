#define _CRT_SECURE_NO_WARNINGS
#include"Workstation.h"

using namespace std;

namespace seneca {
	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;


	Workstation::Workstation(const std::string& record): Station(record)
	{	}

	void Workstation::fill(std::ostream & os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{	 
		bool flag = false;
		if (!m_orders.empty()) {
			CustomerOrder& tempOrder = m_orders.front();

			if (tempOrder.isItemFilled(getItemName()) || getQuantity()==0) {

				if (m_pNextStation != nullptr) {
					*m_pNextStation += move(tempOrder);
				}
				else if(tempOrder.isOrderFilled()){
					g_completed.push_back(move(tempOrder));
				}
				else {
					g_incomplete.push_back(move(tempOrder));
				}
				m_orders.pop_front();
				flag = true;
			}
		}
		return flag;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation!=nullptr) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";

		}
		
		os << endl;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		// TODO: insert return statement here
		m_orders.push_back(move(newOrder));
		return *this;
	}





}

