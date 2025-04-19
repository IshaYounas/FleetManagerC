// warnings
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> // malloc
#include<string.h> // strings
#include<conio.h> // hiding the password

// constants
#define MAX_LOGIN_RECORDS 3
#define PASSWORD_LENGTH 7

// structure for linked list
typedef struct node
{
	// variables for the stuct
	struct node* NEXT;

	char chassisNum[50];
	char make[50];
	char model[50];
	int year;
	float cost;
	float valuation;
	int mileage;
	int nextServiceMileage;
	char ownerName[50];
	char ownerEmail[50];
	char ownerPhone[50];
	int machineType;
	int breakdown;
}machineT;

// structure for login
typedef struct 
{
	// variables for the stuct
	char username[20];
	char password[PASSWORD_LENGTH];
}loginT;

// function prototypes
void addMachine(machineT** top); // option 1
void displayToScreen(machineT* top); // option 2
void displayMachineDetails(machineT* top); // option 3
void updateMachine(machineT* top); // option 4
void deleteMachine(machineT** top); // option 5
void generateStatistics(machineT* top); // option 6
void saveToFile(machineT* top); 
void listMachines(machineT* top); // option 7
void saveToFleetFile(machineT* top);
void loadFleetFile(machineT** top);
int login(loginT data[]);
int menu();

const char* getMachineType(int type)
{
	switch (type)
	{
		case 1: return "Tractor";
		case 2: return "Excavator";
		case 3: return "Roller";
		case 4: return "Crane";
		case 5: return "Mixer";
		default: return "Unknown";
	} // switch
} // getMachineType

const char* getBreakdownStatus(int breakdown)
{
	switch (breakdown)
	{
		case 1: return "Never";
		case 2: return "Less than three times";
		case 3: return "Less than five times";
		case 4: return "More than five times";
		default: return "Unknown";
	} // switch
} // getBreakdownStatus

int main()
{
	// variables
	machineT* headPtr = NULL;
	int option;
	int user;
	int adminOption;
	FILE* fp;
	loginT* data[3];
	int i;

	for (i = 0; i < MAX_LOGIN_RECORDS; i++)
	{
		data[i] = (loginT*)malloc(sizeof(loginT));
	} // for

	fp = fopen("login.txt", "r");

	if (fp == NULL) // file no open
	{
		printf("login.txt cannot be opened for reading\n");
	} // if

	else // file open
	{
		for (i = 0; i < MAX_LOGIN_RECORDS; i++)
		{
			fscanf(fp, "%s %s", data[i]->username, data[i]->password);
		} // for
		fclose(fp);
	} // else

	// prompting the user for input
	printf("PLease enter 1 for admin or 0 for guest\n");
	scanf("%d", &user);

	if (user == 1) // admin
	{
		if (login(data) == 1) // passwords match 
		{
			printf("Admin login successful\n");
		} // if

		else // passwords NO match
		{
			printf("Incorrect password. Proceeding as Guest\n");
		} // else
	} // if

	else if (user == 0) // user
	{
		printf("User is guest\n");
	} // else if

	loadFleetFile(&headPtr); // loading the fleet file

	do 
	{
		option = menu();
		switch (option)
		{
			case 1:
				addMachine(&headPtr);
				break;

			case 2:
				displayToScreen(headPtr);
				break;

			case 3:
				if (user == 1) // admin
				{
					displayMachineDetails(headPtr);
				} // if

				else if (user == 0) // guest
				{
					printf("Only admin have permission to display the machine!\n");
				} // else if
				break;
				
			case 4:
				if (user == 1) // admin
				{
					updateMachine(headPtr);
				} // if

				else if (user == 0) // guest
				{
					printf("Only admin have permission to edit the machine!\n");
				} // else if
				break;

			case 5:
				if (user == 0) // guest
				{
					deleteMachine(headPtr);
				} // if

				else if (user == 1) // admin
				{
					printf("Only guest have permission to delete the machine!\n");
				} // else if
				break;

			case 6:
				generateStatistics(headPtr);
				break;

			case 7:
				listMachines(headPtr);
				break;

			case -1:
				printf("Exiting the program...\n");
				break;

			default:
				printf("Invalid choice. Please try again.\n");
		} // switch

		// keep repeating unit option is not -1
	} while (option != -1); // do-while
	
	saveToFile(headPtr); // calling the save method
	saveToFleetFile(headPtr); 
} // main

// custom method
int login(loginT data[])
{
	// variables
	FILE* fp;
	char adminPass[20];
	char adminUsername[20];
	int found = 0;
	char ch;
	int i = 0;

	fp = fopen("login.txt", "r");

	if (fp == NULL) // file no open
	{
		printf("login.txt cannot be opened for reading\n");
	} // if

	else
	{
		fscanf(fp, "%s %s", data->username, data->password);
		fclose(fp);

		// prompting the admin for the password
		printf("Enter Admin Username\n");
		scanf("%s", adminUsername);

		printf("Enter Admin Password\n");

		while ((ch = _getch()) != '\r') // until enter is pressed
		{
			if (ch != 13) // no enter key
			{
				adminPass[i] = ch; // store the character
				i++;
				printf("*"); // print asterisk
			} // if
		} // while

		adminPass[i] = '\0';
		printf("\n");

		for (i = 0; i < 3; i++)
		{
			if (strcmp(data[i].username, adminUsername) == 0 && strcmp(data[i].password, adminPass) == 0) // username and password match
			{
				found = 1; // found
				break;
			} // if
		} // for
		fclose(fp); // close login.txt
		return found; 
	} // else
} // login

void addMachine(machineT** top) // adding machinery 
{
	// variables
	machineT* newMachine;
	machineT* current;
	machineT* prev = NULL;
	char newChassis[50];
	int validEmail = 0;

	current = *top;

	printf("Enter chassis number: ");
	scanf("%s", newChassis);

	// checking if the chassis number is unique or not
	while (current != NULL)
	{
		if (strcmp(current->chassisNum, newChassis) == 0)
		{
			printf("Sorry the chassis number %s already exists\n\n", newChassis);
			return;
		} // if
		current = current->NEXT; // next machine
	} // while

	newMachine = (machineT*)malloc(sizeof(machineT));
	if (newMachine == NULL)
	{
		printf("Memory allocation failed\n\n");
		return;
	} // if
	
	strcpy(newMachine->chassisNum, newChassis); // string copy

	// prompting the user for input
	printf("Enter make: ");
	scanf("%s", newMachine->make);
	printf("Enter model: ");
	scanf("%s", newMachine->model);
	printf("Enter year: ");
	scanf("%d", &newMachine->year);
	printf("Enter cost: ");
	scanf("%f", &newMachine->cost);
	printf("Enter valuation: ");
	scanf("%f", &newMachine->valuation);
	printf("Enter mileage: ");
	scanf("%d", &newMachine->mileage);
	printf("Enter next service mileage: ");
	scanf("%d", &newMachine->nextServiceMileage);
	printf("Enter owner name: ");
	scanf("%s", newMachine->ownerName);

	// validating the email
	do
	{
		printf("Enter owner email (must contain an @, a full stop and a .com): ");
		scanf("%s", newMachine->ownerEmail);

		// checking if the email is valid
		if (strstr(newMachine->ownerEmail, "@") != NULL && strstr(newMachine->ownerEmail, ".") != NULL && strstr(newMachine->ownerEmail, ".com") != NULL)
		{
			validEmail = 1; // valid email
		} // if
		else
		{
			printf("Invalid email. Please enter a valid email address.\n");
			validEmail = 0; // invalid email
		} // else
	} while (!validEmail); // do - while


	printf("Enter owner phone: ");
	scanf("%s", newMachine->ownerPhone);


	printf("Enter machine type (1 for Tractor, 2 for Excavator, 3 for Roller, 4 for Crane, 5 for Mixer): ");
	scanf("%d", &newMachine->machineType);
	printf("Machine Type: %s\n", getMachineType(newMachine->machineType));

	printf("Enter breakdown (1 for Never, 2 for Less than three times, 3 for Less than five times, 4 for More than five times): ");
	scanf("%d", &newMachine->breakdown);
	printf("Breakdown: %s\n", getBreakdownStatus(newMachine->breakdown));

	newMachine->NEXT = NULL; 

	// inserting in a sorted order by the chassis number
	if (*top == NULL || strcmp(newMachine->chassisNum, (*top)->chassisNum) < 0)
	{
		newMachine->NEXT = *top; // adding to linked list
		*top = newMachine; // update top pointer
		printf("Machine added successfully\n\n");
		return;
	} // if
	
	else
	{
		prev = *top;

		while (prev->NEXT != NULL && strcmp(prev->NEXT->chassisNum, newMachine->chassisNum) < 0)
		{
			prev = prev->NEXT; // next machine
		} // while

		newMachine->NEXT = prev->NEXT; // adding to linked list
		prev->NEXT = newMachine; // update top pointer
	}
	printf("Machine added successfully\n\n");
} // addMachine

void displayToScreen(machineT* top) // displaying all the machinery
{
	if (top == NULL)
	{
		printf("No machines to display\n\n");
		return;
	} // if

	printf("\nMachines in the fleet:\n");
	
	while (top != NULL)
	{
		printf("Chassis number: %s\n", top->chassisNum);
		printf("Make: %s\n", top->make);
		printf("Model: %s\n", top->model);
		printf("Year: %d\n", top->year);
		printf("Cost: %.2f\n", top->cost);
		printf("Valuation: %.2f\n", top->valuation);
		printf("Mileage: %d\n", top->mileage);
		printf("Next Service Mileage: %d\n", top->nextServiceMileage);
		printf("Owner Name: %s\n", top->ownerName);
		printf("Owner Email: %s\n", top->ownerEmail);
		printf("Owner Phone: %s\n", top->ownerPhone);
		printf("Machine Type: %s\n", getMachineType(top->machineType));
		printf("Breakdown: %s\n", getBreakdownStatus(top->breakdown));	

		top = top->NEXT; // next machine
	} // while
	printf("End of list\n\n");
} // displayToScreen

void displayMachineDetails(machineT* top) // asking user for a specific machine to display
{
	char displayChassis[50];
	int found = 0; // default not found

	printf("Enter chassis number to display details: ");
	scanf("%s", displayChassis);

	while (top != NULL)
	{
		if (strcmp(top->chassisNum, displayChassis) == 0) // comparing the string
		{
			printf("Chassis Number: %s\n", top->chassisNum);
			printf("Make: %s\n", top->make);
			printf("Model: %s\n", top->model);
			printf("Year: %d\n", top->year);
			printf("Cost: %.2f\n", top->cost);
			printf("Valuation: %.2f\n", top->valuation);
			printf("Mileage: %d\n", top->mileage);
			printf("Next Service Mileage: %d\n", top->nextServiceMileage);
			printf("Owner Name: %s\n", top->ownerName);
			printf("Owner Email: %s\n", top->ownerEmail);
			printf("Owner Phone: %s\n", top->ownerPhone);
			printf("Machine Type: %s\n", getMachineType(top->machineType));
			printf("Breakdown: %s\n", getBreakdownStatus(top->breakdown));

			found = 1;
			break;
		} // if

		top = top->NEXT; // next machine
	} // while

	if (found == 0)
	{
		printf("Machine with chassis number %s not found\n\n", displayChassis);
	} // if
} // displayMachineDetails

void updateMachine(machineT* top)
{
	machineT* current = top;
	char searchNum[50];

	printf("Enter chassis number of the machine to update: ");
	scanf("%s", searchNum);

	while (current != NULL)
	{
		if (strcmp(current->chassisNum, searchNum) == 0) // comparing the strings
		{
			printf("Machine found.\n");

			printf("Enter new make: ");
			scanf("%s", current->make);
			printf("Enter new model: ");
			scanf("%s", current->model);
			printf("Enter new year: ");
			scanf("%d", &current->year);
			printf("Enter new cost: ");
			scanf("%f", &current->cost);
			printf("Enter new valuation: ");
			scanf("%f", &current->valuation);
			printf("Enter new mileage: ");
			scanf("%d", &current->mileage);
			printf("Enter new next service mileage: ");
			scanf("%d", &current->nextServiceMileage);
			printf("Enter new owner name: ");
			scanf("%s", current->ownerName);
			printf("Enter new owner email: ");
			scanf("%s", current->ownerEmail);
			printf("Enter new owner phone: ");
			scanf("%s", current->ownerPhone);


			printf("Enter new machine type (1 for Tractor, 2 for Excavator, 3 for Roller, 4 for Crane, 5 for Mixer): ");
			scanf("%d", &current->machineType);
			printf("Machine Type: %d\n", getMachineType(current->machineType));

			printf("Enter new breakdown (1 for Never, 2 for Less than three times, 3 for Less than five times, 4 for More than five times): ");
			scanf("%d", &current->breakdown);
			printf("Breakdown: %d\n", getBreakdownStatus(current->breakdown));

			printf("Machine updated successfully\n\n");
			return;
		} // if
		current = current->NEXT; // next machine
	} // while
	printf("Machine with chassis number %s not found\n\n", searchNum);
} // updateMachine

void deleteMachine(machineT** top)
{
	char searchNum[50];
	machineT* current = *top;
	machineT* prev = NULL;

	printf("Enter chassis number of the machine to delete: ");
	scanf("%s", searchNum);

	while (current != NULL)
	{
		if (strcmp(current->chassisNum, searchNum) == 0) // comparing the strings
		{
			// machine found
			if (prev == NULL)
			{
				*top = current->NEXT;
			} // if

			else
			{
				prev->NEXT = current->NEXT;
			} // else

			free(current); // free memory
			printf("Machine with chassis number %s deleted successfully\n\n", searchNum);
			return;
		} // if

		prev = current; // updating prev ptr
		current = current->NEXT;
	} // while
	printf("Machine with chassis number %s not found\n\n", searchNum);
} // deleteMachine

void generateStatistics(machineT* top)
{
	// variables
	machineT* current;
	int tractor[4] = { 0 };
	int excavator[4] = { 0 };
	int roller[4] = { 0 };
	int crane[4] = { 0 };
	int mixer[4] = { 0 };

	int totalTractor = 0;
	int totalExcavator = 0;
	int totalRoller = 0;
	int totalCrane = 0;
	int totalMixer = 0;
	int totalMachines = 0;

	if (top == NULL)
	{
		printf("No machines to generate statistics\n\n");
		return;
	} // if

	current = top;

	while (current != NULL)
	{
		totalMachines++; // total machines

		switch (current->machineType)
		{
			case 1: // tractor
				totalTractor++;
				tractor[current->breakdown - 1]++;
				break;

			case 2: // excavator
				totalExcavator++;
				excavator[current->breakdown - 1]++;
				break;

			case 3:	// roller
				totalRoller++;
				roller[current->breakdown - 1]++;
				break;

			case 4: // crane
				totalCrane++;
				crane[current->breakdown - 1]++;
				break;

			case 5: // mixer
				totalMixer++;
				mixer[current->breakdown - 1]++;
				break;
		} // switch
	} // while

	// printing statistics - percentages
	printf("Statistics:\n");
	
	if (totalTractor > 0)
	{
		printf("Tractors - %d:\n", totalTractor);
		printf("A. Never: %.2f%%\n", (float)tractor[0] / totalTractor * 100);
		printf("B. Less than three times: %.2f%%\n", (float)tractor[1] / totalTractor * 100);
		printf("C. Less than five times: %.2f%%\n", (float)tractor[2] / totalTractor * 100);
		printf("D. More than five times: %.2f%%\n\n", (float)tractor[3] / totalTractor * 100);
	} // if

	if (totalExcavator > 0)
	{
		printf("Excavators - %d:\n", totalExcavator);
		printf("A. Never: %.2f%%\n", (float)excavator[0] / totalExcavator * 100);
		printf("B. Less than three times: %.2f%%\n", (float)excavator[1] / totalExcavator * 100);
		printf("C. Less than five times: %.2f%%\n", (float)excavator[2] / totalExcavator * 100);
		printf("D. More than five times: %.2f%%\n\n", (float)excavator[3] / totalExcavator * 100);
	} // if

	if (totalRoller > 0)
	{
		printf("Rollers - %d:\n", totalRoller);
		printf("A. Never: %.2f%%\n", (float)roller[0] / totalRoller * 100);
		printf("B. Less than three times: %.2f%%\n", (float)roller[1] / totalRoller * 100);
		printf("C. Less than five times: %.2f%%\n", (float)roller[2] / totalRoller * 100);
		printf("D. More than five times: %.2f%%\n\n", (float)roller[3] / totalRoller * 100);
	} // if

	if (totalCrane > 0)
	{
		printf("Cranes - %d:\n", totalCrane);
		printf("A. Never: %.2f%%\n", (float)crane[0] / totalCrane * 100);
		printf("B. Less than three times: %.2f%%\n", (float)crane[1] / totalCrane * 100);
		printf("C. Less than five times: %.2f%%\n", (float)crane[2] / totalCrane * 100);
		printf("D. More than five times: %.2f%%\n\n", (float)crane[3] / totalCrane * 100);
	} // if

	if (totalMixer > 0)
	{
		printf("Mixers - %d:\n", totalMixer);
		printf("A. Never: %.2f%%\n", (float)mixer[0] / totalMixer * 100);
		printf("B. Less than three times: %.2f%%\n", (float)mixer[1] / totalMixer * 100);
		printf("C. Less than five times: %.2f%%\n", (float)mixer[2] / totalMixer * 100);
		printf("D. More than five times: %.2f%%\n\n", (float)mixer[3] / totalMixer * 100);
	} // if
} // genearteStatistics

void saveToFile(machineT* top)
{
	// variables
	machineT* current;
	FILE* fp;

	int tractor[4] = { 0 };
	int excavator[4] = { 0 };
	int roller[4] = { 0 };
	int crane[4] = { 0 };
	int mixer[4] = { 0 };

	int totalTractor = 0;
	int totalExcavator = 0;
	int totalRoller = 0;
	int totalCrane = 0;
	int totalMixer = 0;

	current = top;
	fp = fopen("report.txt", "w"); // write mode

	if (fp == NULL) //  file no open
	{
		printf("report.txt cannot be opened for writing\n"); 
		return;
	} // if

	else // file open
	{
		// writing to the file
		fprintf(fp, "Fleet Management Report\n");
		while (current != NULL)
		{
			fprintf(fp, "Chassis Number: %s\n", current->chassisNum);
			fprintf(fp, "Make: %s\n", current->make);
			fprintf(fp, "Model: %s\n", current->model);
			fprintf(fp, "Year: %d\n", current->year);
			fprintf(fp, "Cost: %.2f\n", current->cost);
			fprintf(fp, "Valuation: %.2f\n", current->valuation);
			fprintf(fp, "Mileage: %d\n", current->mileage);
			fprintf(fp, "Next Service Mileage: %d\n", current->nextServiceMileage);
			fprintf(fp, "Owner Name: %s\n", current->ownerName);
			fprintf(fp, "Owner Email: %s\n", current->ownerEmail);
			fprintf(fp, "Owner Phone: %s\n", current->ownerPhone);
			fprintf(fp, "Machine Type: %s\n", getMachineType(current->machineType));
			fprintf(fp, "Breakdown: %s\n\n", getBreakdownStatus(current->breakdown));

			current = current->NEXT; 
		} // while

		fprintf(fp, "\nStatistics:\n");
		if (totalTractor > 0)
		{
			fprintf(fp, "Tractors - %d:\n", totalTractor);
			fprintf(fp, "A. Never: %.2f%%\n", (float)tractor[0] / totalTractor * 100);
			fprintf(fp, "B. Less than three times: %.2f%%\n", (float)tractor[1] / totalTractor * 100);
			fprintf(fp, "C. Less than five times: %.2f%%\n", (float)tractor[2] / totalTractor * 100);
			fprintf(fp, "D. More than five times: %.2f%%\n\n", (float)tractor[3] / totalTractor * 100);
		} // if

		if (totalExcavator > 0)
		{
			fprintf(fp, "Excavators - %d:\n", totalExcavator);
			fprintf(fp, "A. Never: %.2f%%\n", (float)excavator[0] / totalExcavator * 100);
			fprintf(fp, "B. Less than three times: %.2f%%\n", (float)excavator[1] / totalExcavator * 100);
			fprintf(fp, "C. Less than five times: %.2f%%\n", (float)excavator[2] / totalExcavator * 100);
			fprintf(fp, "D. More than five times: %.2f%%\n\n", (float)excavator[3] / totalExcavator * 100);
		} // if

		if (totalRoller > 0)
		{
			fprintf("Rollers - %d:\n", totalRoller);
			fprintf(fp, "A. Never: %.2f%%\n", (float)roller[0] / totalRoller * 100);
			fprintf(fp, "B. Less than three times: %.2f%%\n", (float)roller[1] / totalRoller * 100);
			fprintf(fp, "C. Less than five times: %.2f%%\n", (float)roller[2] / totalRoller * 100);
			fprintf(fp, "D. More than five times: %.2f%%\n\n", (float)roller[3] / totalRoller * 100);
		} // if

		if (totalCrane > 0)
		{
			fprintf(fp, "Cranes - %d:\n", totalCrane);
			fprintf(fp, "A. Never: %.2f%%\n", (float)crane[0] / totalCrane * 100);
			fprintf(fp, "B. Less than three times: %.2f%%\n", (float)crane[1] / totalCrane * 100);
			fprintf(fp, "C. Less than five times: %.2f%%\n", (float)crane[2] / totalCrane * 100);
			fprintf(fp, "D. More than five times: %.2f%%\n\n", (float)crane[3] / totalCrane * 100);
		} // if

		if (totalMixer > 0)
		{
			fprintf(fp, "Mixers - %d:\n", totalMixer);
			fprintf(fp, "A. Never: %.2f%%\n", (float)mixer[0] / totalMixer * 100);
			fprintf(fp, "B. Less than three times: %.2f%%\n", (float)mixer[1] / totalMixer * 100);
			fprintf(fp, "C. Less than five times: %.2f%%\n", (float)mixer[2] / totalMixer * 100);
			fprintf(fp, "D. More than five times: %.2f%%\n\n", (float)mixer[3] / totalMixer * 100);
		} // if

		fclose(fp); // close file
		printf("Data saved to report.txt\n");
	} // else
} // saveToFile

void listMachines(machineT* top)
{
	// variables
	machineT* temp;
	machineT* list;
	int count = 0;
	int i;
	int j;

	if (top == NULL)
	{
		printf("No machines to display\n\n");
		return;
	} // if

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT; // next machine
	} // while

	list = (machineT*)malloc(count * sizeof(machineT));
	if (list == NULL)
	{
		printf("Memory allocation failed\n\n");
		return;
	} // if

	temp = top;
	for (i = 0; i < count; i++)
	{
		list[i] = *temp; // copying the data
		temp = temp->NEXT; // next machine
	} // for

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (list[j].valuation > list[j + 1].valuation)
			{
				machineT tempMachine = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tempMachine;
			} // if
		} // for (j)
	} // for (i)

	printf("Machines in order of valuation:\n");
	for (int i = 0; i < count; i++)
	{
		printf("Chassis Number: %s\n", list[i].chassisNum);
		printf("Make: %s\n", list[i].make);
		printf("Model: %s\n", list[i].model);
		printf("Year: %d\n", list[i].year);
		printf("Cost: %.2f\n", list[i].cost);
		printf("Valuation: %.2f\n", list[i].valuation);
		printf("Mileage: %d\n", list[i].mileage);
		printf("Next Service Mileage: %d\n", list[i].nextServiceMileage);
		printf("Owner Name: %s\n", list[i].ownerName);
		printf("Owner Email: %s\n", list[i].ownerEmail);
		printf("Owner Phone: %s\n", list[i].ownerPhone);
		printf("Machine Type: %s\n", getMachineType(list[i].machineType));
		printf("Breakdown: %s\n", getBreakdownStatus(list[i].breakdown));
	} // for
	free(list); // free memory
} // listMachines

void saveToFleetFile(machineT* top)
{
	// variables
	FILE* fp;
	fp = fopen("fleet.txt", "w"); // write mode

	if (fp == NULL) // file no open
	{
		printf("fleet.txt cannot be opened for writing\n");
		return;
	} // if

	
	machineT* current = top;
	while (current != NULL)
	{
		// writing to the file
		fprintf(fp, "%s %s %s %d %.2f %.2f %d %d %s %s %s %d %d\n", current->chassisNum, current->make, current->model, current->year, current->cost, current->valuation, current->mileage, current->nextServiceMileage, current->ownerName, current->ownerEmail, current->ownerPhone, current->machineType, current->breakdown);
		
		current = current->NEXT; // next machine
	} // while
	fclose(fp); // close file
	printf("Data saved to fleet.txt\n");
} // saveToFleetFile

void loadFleetFile(machineT** top)
{
	// variables
	FILE* fp;
	int numInputs;
	machineT* current;

	fp = fopen("fleet.txt", "r"); // read mode

	if (fp == NULL) // file can't open
	{
		printf("fleet.txt cannot be opened for reading\n");
	} // if

	while (!feof(fp))
	{
		current = (machineT*)malloc(sizeof(machineT)); // allocating memory
	
		if (current == NULL)
		{
			printf("Memory allocation failed\n");
			return;
		} // if

		numInputs = fscanf(fp, "%s %s %s %d %f %f %d %d %s %s %s %d %d\n", current->chassisNum, current->make, current->model, &current->year, &current->cost, &current->valuation, &current->mileage, &current->nextServiceMileage, current->ownerName, current->ownerEmail, current->ownerPhone, &current->machineType, &current->breakdown);

		if (numInputs == 13)
		{
			printf("Chassis Number: %s\n", current->chassisNum);
			printf("Make: %s\n", current->make);
			printf("Model: %s\n", current->model);
			printf("Year: %d\n", current->year);
			printf("Cost: %.2f\n", current->cost);
			printf("Valuation: %.2f\n", current->valuation);
			printf("Mileage: %d\n", current->mileage);
			printf("Next Service Mileage: %d\n", current->nextServiceMileage);
			printf("Owner Name: %s\n", current->ownerName);
			printf("Owner Email: %s\n", current->ownerEmail);
			printf("Owner Phone: %s\n", current->ownerPhone);
			printf("Machine Type: %s\n", getMachineType(current->machineType));
			printf("Breakdown: %s\n", getBreakdownStatus(current->breakdown));

			current->NEXT = *top; 
			*top = current; 

			if (*top == NULL || strcmp(current->chassisNum, (*top)->chassisNum) < 0)
			{
				current->NEXT = *top;
				*top = current;
			} // if		

			else
			{
				machineT* prev = *top;
				while (prev->NEXT != NULL && strcmp(prev->NEXT->chassisNum, current->chassisNum) < 0)
				{
					prev = prev->NEXT; // next machine
				} // while
				current->NEXT = prev->NEXT;
				prev->NEXT = current;
			} // else
		} // if

		else
		{
			printf("Error reading data from file\n");
			free(current); // free memory
			break;
		} // else
	}// while
	fclose(fp); // closing the file
} // loadFleetFile

int menu()
{
	int choice;
	printf("1. Add machine\n");
	printf("2. Display all machines to screen\n");
	printf("3. Display machine details\n");
	printf("4. Update machine\n");
	printf("5. Delete Machine\n");
	printf("6. Generate Statistics\n");
	printf("7. List Machines in order of valuation\n");
	printf("-1. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	return choice;
} // menu