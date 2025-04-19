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
int login(loginT* data);
int menu();

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
				printf("Exiting...\n");
				break;

			default:
				printf("Invalid choice. Please try again.\n");
		} // switch
		// keep repeating unit option is not -1
	} while (option != -1); // do-while
	
	saveToFile(headPtr); // calling the save method
} // main

// custom method
int login(loginT* data)
{
	// variables
	FILE* fp;
	char adminPass[20];
	char adminUsername[7];
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

		return found; 

		fclose(fp); // close login.txt
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

	switch (newMachine->machineType)
	{
		case 1:
			printf("Tractor\n");
			break;

		case 2:
			printf("Excavator\n");
			break;

		case 3:
			printf("Roller\n");
			break;

		case 4:
			printf("Crane\n");
			break;

		case 5:
			printf("Mixer\n");
			break;

		default:
			printf("Invalid machine type\n");
			break;
	} // switch

	printf("Enter breakdown (1 for Never, 2 for Less than three times, 3 for Less than five times, 4 for More than five times): ");
	scanf("%d", &newMachine->breakdown);

	switch (newMachine->breakdown)
	{
		case 1:
			printf("Breakdown: Never\n");
			break;

		case 2:
			printf("Breakdown: Less than three times\n");
			break;

		case 3:
			printf("Breakdown: Less than five times\n");
			break;

		case 4:
			printf("Breakdown: More than five times\n");
			break;

		default:
			printf("Invalid breakdown\n");
			break;
	} // switch

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

	printf("Machines in the fleet:\n");
	
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
		printf("Machine Type: %d\n", top->machineType);
		printf("Breakdown: %d\n", top->breakdown);	

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
			printf("Machine Type: %d\n", top->machineType);
			printf("Breakdown: %d\n\n", top->breakdown);

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

			switch (current->machineType)
			{
				case 1:
					printf("Tractor\n");
					break;

				case 2:
					printf("Excavator\n");
					break;

				case 3:
					printf("Roller\n");
					break;

				case 4:
					printf("Crane\n");
					break;

				case 5:
					printf("Mixer\n");
					break;

				default:
					printf("Invalid machine type\n");
					break;
			} // switch

			printf("Enter new breakdown (1 for Never, 2 for Less than three times, 3 for Less than five times, 4 for More than five times): ");
			scanf("%d", &current->breakdown);

			switch (current->breakdown)
			{
				case 1:
					printf("Breakdown: Never\n");
					break;

				case 2:
					printf("Breakdown: Less than three times\n");
					break;

				case 3:
					printf("Breakdown: Less than five times\n");
					break;

				case 4:
					printf("Breakdown: More than five times\n");
					break;

				default:
					printf("Invalid breakdown\n");
					break;
			} // switch

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

	if (top == NULL)
	{
		printf("No machines to generate statistics\n\n");
		return;
	} // if

	current = top;

	while (current != NULL)
	{
		switch (current->machineType)
		{
			case 1: // tractor
				totalTractor++;
				if (current->breakdown == 1) tractor[0]++;
				else if (current->breakdown == 2) tractor[1]++;
				else if (current->breakdown == 3) tractor[2]++;
				else if (current->breakdown == 4) tractor[3]++;
				break;

			case 2: // excavator
				totalExcavator++;
				if (current->breakdown == 1) excavator[0]++;
				else if (current->breakdown == 2) excavator[1]++;
				else if (current->breakdown == 3) excavator[2]++;
				else if (current->breakdown == 4) excavator[3]++;
				break;

			case 3: // roller
				totalRoller++;
				if (current->breakdown == 1) roller[0]++;
				else if (current->breakdown == 2) roller[1]++;
				else if (current->breakdown == 3) roller[2]++;
				else if (current->breakdown == 4) roller[3]++;
				break;

			case 4: // crane
				totalCrane++;
				if (current->breakdown == 1) crane[0]++;
				else if (current->breakdown == 2) crane[1]++;
				else if (current->breakdown == 3) crane[2]++;
				else if (current->breakdown == 4) crane[3]++;
				break;

			case 5: // mixer
				totalMixer++;
				if (current->breakdown == 1) mixer[0]++;
				else if (current->breakdown == 2) mixer[1]++;
				else if (current->breakdown == 3) mixer[2]++;
				else if (current->breakdown == 4) mixer[3]++;
				break;
		} // switch
		current = current->NEXT; 
	} // while

	// printing statistics
	printf("Statistics:\n");
	
	if (totalTractor > 0)
	{
		printf("Tractors:\n");
		printf("Never: %d\n", tractor[0]);
		printf("Less than three times: %d\n", tractor[1]);
		printf("Less than five times: %d\n", tractor[2]);
		printf("More than five times: %d\n\n", tractor[3]);
	} // if

	if (totalExcavator > 0)
	{
		printf("Excavators:\n");
		printf("Never: %d\n", excavator[0]);
		printf("Less than three times: %d\n", excavator[1]);
		printf("Less than five times: %d\n", excavator[2]);
		printf("More than five times: %d\n\n", excavator[3]);
	} // if

	if (totalRoller > 0)
	{
		printf("Rollers:\n");
		printf("Never: %d\n", roller[0]);
		printf("Less than three times: %d\n", roller[1]);
		printf("Less than five times: %d\n", roller[2]);
		printf("More than five times: %d\n\n", roller[3]);
	} // if

	if (totalCrane > 0)
	{
		printf("Cranes:\n");
		printf("Never: %d\n", crane[0]);
		printf("Less than three times: %d\n", crane[1]);
		printf("Less than five times: %d\n", crane[2]);
		printf("More than five times: %d\n\n", crane[3]);
	} // if

	if (totalMixer > 0)
	{
		printf("Mixers:\n");
		printf("Never: %d\n", mixer[0]);
		printf("Less than three times: %d\n", mixer[1]);
		printf("Less than five times: %d\n", mixer[2]);
		printf("More than five times: %d\n\n", mixer[3]);
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
		fprintf(fp, "Fleet Manager Report\n");
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
			fprintf(fp, "Machine Type: %d\n", current->machineType);
			fprintf(fp, "Breakdown: %d\n\n", current->breakdown);

			switch (current->machineType)
			{
				case 1:
					totalTractor++;
					tractor[current->breakdown - 1]++;
					break;

				case 2:
					totalExcavator++;
					excavator[current->breakdown - 1]++;
					break;

				case 3:
					totalRoller++;
					roller[current->breakdown - 1]++;
					break;

				case 4:
					totalCrane++;
					crane[current->breakdown - 1]++;
					break;

				case 5:
					totalMixer++;
					mixer[current->breakdown - 1]++;
					break;
			} // switch
			current = current->NEXT; 
		} // while

		fprintf(fp, "\nStatistics:\n");
		if (totalTractor > 0)
		{
			fprintf(fp, "Tractors:\n");
			fprintf(fp, "Never: %d\n", tractor[0]);
			fprintf(fp, "Less than three times: %d\n", tractor[1]);
			fprintf(fp, "Less than five times: %d\n", tractor[2]);
			fprintf(fp, "More than five times: %d\n\n", tractor[3]);
		} // if

		if (totalExcavator > 0)
		{
			fprintf(fp, "Excavators:\n");
			fprintf(fp, "Never: %d\n", excavator[0]);
			fprintf(fp, "Less than three times: %d\n", excavator[1]);
			fprintf(fp, "Less than five times: %d\n", excavator[2]);
			fprintf(fp, "More than five times: %d\n\n", excavator[3]);
		} // if

		if (totalRoller > 0)
		{
			fprintf(fp, "Rollers:\n");
			fprintf(fp, "Never: %d\n", roller[0]);
			fprintf(fp, "Less than three times: %d\n", roller[1]);
			fprintf(fp, "Less than five times: %d\n", roller[2]);
			fprintf(fp, "More than five times: %d\n\n", roller[3]);
		} // if

		if (totalCrane > 0)
		{
			fprintf(fp, "Cranes:\n");
			fprintf(fp, "Never: %d\n", crane[0]);
			fprintf(fp, "Less than three times: %d\n", crane[1]);
			fprintf(fp, "Less than five times: %d\n", crane[2]);
			fprintf(fp, "More than five times: %d\n\n", crane[3]);
		} // if

		if (totalMixer > 0)
		{
			fprintf(fp, "Mixers:\n");
			fprintf(fp, "Never: %d\n", mixer[0]);
			fprintf(fp, "Less than three times: %d\n", mixer[1]);
			fprintf(fp, "Less than five times: %d\n", mixer[2]);
			fprintf(fp, "More than five times: %d\n\n", mixer[3]);
		} // if

		fclose(fp); // close file
		printf("Data saved to report.txt\n\n");
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
		printf("Machine Type: %d\n", list[i].machineType);
		printf("Breakdown: %d\n\n", list[i].breakdown);
	} // for
	free(list); // free memory
} // listMachines


int menu()
{
	int choice;
	printf("1. Add machine\n");
	printf("2. Display all machines to screen\n");
	printf("3. Display machine details\n");
	printf("4. Update machine\n");
	printf("5. Delete Machine\n");
	printf("6. Generate Statistics\n");
	printf("7. Save to File\n");
	printf("8. List Machines in order of valuation\n");
	printf("-1. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	return choice;
} // menu