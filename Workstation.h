#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include<deque>
#include<iostream>
#include<string>
#include"Station.h"
#include"CustomerOrder.h"

namespace seneca {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;


	class Workstation : public Station{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{nullptr};

	public:
		Workstation(const std::string& record);

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		void display(std::ostream& os) const;
		
		Workstation* getNextStation() const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		// restricted as Workstation object is single location on assembly line
		// for filling customer orders with items
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;


	};

}

#endif // !SENECA_WORKSTATION_H
