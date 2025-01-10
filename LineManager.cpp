#define _CRT_SECURE_NO_WARNINGS

#include<fstream>
#include"LineManager.h"
#include"Utilities.h"

using namespace std;

namespace seneca {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		Utilities myUtil;
		ifstream dataFile(file);
		if (!dataFile) {
			throw "Error: Unable to open file.";
		}

		string data, wsName="", nextWsName = "";

		while (getline(dataFile, data)) {
			size_t next_pos = 0;
			bool more = true;

			
			myUtil.setDelimiter('|');
			wsName = myUtil.extractToken(data, next_pos, more);
			
			if (more) {
				nextWsName = myUtil.extractToken(data, next_pos, more);
			}
			else {
				nextWsName = "";
			}

			auto curStation = find_if(stations.begin(), stations.end(),
				[&wsName](Workstation* rhs) {
					return rhs->getItemName() == wsName;
				});

			auto nextStation = find_if(stations.begin(), stations.end(),
				[&nextWsName](Workstation* rhs) {
					return rhs->getItemName() == nextWsName;
				});


			if (curStation != stations.end()) {
				(*curStation)->setNextStation(nextStation != stations.end() ? *nextStation : nullptr);
				m_activeLine.push_back(*curStation);
			}


			m_firstStation =  *find_if(stations.begin(), stations.end(),
				[&stations](Workstation* rhs) {
					
					for (auto* other : stations) {
						if (other->getNextStation() == rhs) {
							return false;
						}
					}
					return true;
				});

			//m_activeLine = stations;
			m_cntCustomerOrder = g_pending.size();

		}
		;
	}
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> reorderedLine;
		Workstation* current = m_firstStation;

		while (current) {
			reorderedLine.push_back(current);
			current = current->getNextStation();
		}

		m_activeLine = move(reorderedLine);
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t iteration = 0;
		os << "Line Manager Iteration: " << ++iteration << endl;

		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* rhs) {
			rhs->fill(os);
			});

		bool allOrdersFilled = true;
		for_each(m_activeLine.begin(), m_activeLine.end(), [&allOrdersFilled](Workstation* rhs) {
			if (rhs->attemptToMoveOrder()) {
				allOrdersFilled = false;
			}
		});

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
		//return g_pending.empty() && allOrdersFilled;


		
	}
	void LineManager::display(std::ostream& os) const
	{
		for (const auto& station : m_activeLine) {
			station->display(os);
		}
	}
}