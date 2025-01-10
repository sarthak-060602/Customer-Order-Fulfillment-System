# Customer-Order-Fulfillment-System

Description
This project implements an assembly line order management system designed to simulate and manage the flow of customer orders through a production line. The system efficiently tracks customer orders, manages workstations, and updates inventory at each stage of the production process.

Working
The system models a production line with multiple workstations, each responsible for fulfilling a specific part of an order. The main components of the system include:

Workstations: Each workstation is responsible for filling specific items in customer orders. The system allows each workstation to be connected to the next, forming an assembly line.
Customer Orders: Orders are filled as they pass through the workstations. Each workstation fills the item associated with the order until it’s complete.
Order Management: The system tracks pending orders, completed orders, and incomplete orders. Orders that are successfully filled at all workstations are moved to the completed orders list.
Inventory Management: At each workstation, inventory is updated as items are used to fulfill customer orders. The system ensures that the available quantity of items is always accurate.
Workflow:
Initialization: The system begins by reading a configuration file that defines the assembly line's workstations and their relationships (i.e., the order in which they are connected).
Order Processing: Orders are added to the system and passed through each workstation.
Order Fulfillment: Each workstation fills the relevant items of a customer order. The workstation either processes the order or passes it along to the next station in the line.
Finalization: Once an order is complete, it is either marked as "completed" or "incomplete" based on whether all items were successfully filled.
Features
Dynamic Workstation Management: The ability to reorder workstations as per the requirements of the production line.
Order Handling: Tracks customer orders and moves them between pending, completed, or incomplete statuses.
Inventory Updates: Automatically adjusts inventory counts when items are used to fulfill orders.
User-friendly Output: Provides clear outputs for each iteration of order processing, displaying the state of workstations and customer orders.
Key Classes
LineManager: This class is responsible for managing the entire assembly line process, including reordering workstations and processing customer orders.
Workstation: Represents a single station on the production line. Each workstation handles the filling of orders for a specific item.
Station: A base class representing the general structure of a workstation, containing information such as item name, description, serial number, and quantity.
CustomerOrder: Represents a customer order, containing the items needed for the order and whether those items have been filled.
Utilities: Provides helper functions for managing input, extracting tokens from strings, and handling delimiters for data parsing.
Use Cases
Manufacturing: This system can be used by manufacturing companies to track the progress of customer orders through various production stages, ensuring efficient management of workstations and inventory.
Order Fulfillment: Ideal for environments where products pass through multiple stages of production or assembly, and customer orders need to be tracked from start to finish.
Inventory Management: Useful for businesses looking to track item quantities as they are used in production, ensuring accurate inventory records and reducing the risk of shortages.
How It Works
The system starts by reading a configuration file that defines the sequence of workstations. This file specifies the names of workstations and their connections (i.e., which workstation feeds into the next).
Customer orders are processed by the system. Each order moves through the sequence of workstations until it is complete.
As orders pass through workstations, inventory is updated, and items are marked as filled.
Once all items in an order are filled, the order is moved to the "completed" list. If any item is unavailable or incomplete, the order is moved to the "incomplete" list.
File Structure
LineManager.h / LineManager.cpp: Handles the overall management of the assembly line, including reordering stations and processing orders.
Workstation.h / Workstation.cpp: Defines the behavior of individual workstations, handling order fulfillment and passing orders to the next station.
Station.h / Station.cpp: Defines the basic properties and functionality of a station, such as item name, serial number, and quantity.
CustomerOrder.h / CustomerOrder.cpp: Manages customer orders, tracking items and their status (filled or unfilled).
Utilities.h / Utilities.cpp: Contains helper functions for parsing and extracting tokens from input strings.
