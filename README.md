# APPProject
This is a Fleet Management System for Machinery Management Ltd. built in C. It helps manage machinery details, generate reports, and track breakdown statistics.

# Features
Admin Login (Password protected with **** masking)
Add/View/Edit/Delete machines
Generate Statistics (Breakdowns by machine type)
Save/Load Data (Stores machine details in fleet.txt)
Print Reports (Saves to report.txt)

# How It Works
Login (Username & password from login.txt)
# Main Menu:
1️ Add Machine → Enter details (Chassis No. must be unique)
2️ View All Machines → Displays full list
3️ Search Machine → Find by Chassis No.
4️ Edit Machine → Update details
5️ Delete Machine → Remove by Chassis No.
6️ Generate Stats → Breakdown % per machine type
7️ List by Valuation → Sorted from lowest to highest
-1️ Exit → Saves changes automatically

# Files Used
login.txt	- Stores usernames & passwords
fleet.txt	- Stores all machine data
report.txt - Generated report of machines & stats

# Data Structure
Linked List stores machines (sorted by Chassis No.)
Each machine has:
Chassis No., Make, Model, Year, Cost, Owner details, etc.
Machine Type (Tractor, Excavator, etc.)
Breakdown history (Never, <3 times, <5 times, >5 times)



# Sample Workflow
Login → Enter admin credentials
Add 2-3 machines (Test with different types)
Generate Report → Check report.txt
Exit → Confirm data saved to fleet.txt
