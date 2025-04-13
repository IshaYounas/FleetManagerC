// warnings
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> // malloc
#include<string.h> // strings

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

// function prototypes
void addMachine(machineT** top); // option 1
void displayToScreen(machineT* top); // option 2
void displayMachineDetails(machineT* top); // option 3
void updateMachine(machineT* top); // option 4
void deleteMachine(machineT** top); // option 5
void generateStatistics(machineT* top); // option 6
void saveToFile(machineT* top); 
void listMachines(machineT* top); // option 7
int menu();

int main()
{
	// variables
	machineT* headPtr = NULL; 
	int option;

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
				displayMachineDetails(headPtr);
				break;
			case 4:
				updateMachine(headPtr);
				break;
			case 5:
				deleteMachine(headPtr);
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
	
	//saveToFile(headPtr); // calling the save method
} // main

// custom method
void addMachine(machineT** top) // adding machinery 
{
	// variables
	machineT* newMachine;
	machineT* current;
	machineT* prev = NULL;
	char newChassis[50];

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
	printf("Enter owner email: ");
	scanf("%s", newMachine->ownerEmail);
	printf("Enter owner phone: ");
	scanf("%s", newMachine->ownerPhone);
	printf("Enter machine type: ");
	scanf("%d", &newMachine->machineType);
	printf("Enter breakdown (1 for yes, 0 for no): ");
	scanf("%d", &newMachine->breakdown);

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
		printf("Chassis number: %s", top->chassisNum);
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
			printf("Enter new machine type: ");
			scanf("%d", &current->machineType);
			printf("Enter new breakdown (1 for yes, 0 for no): ");
			scanf("%d", &current->breakdown);


			printf("Machine updated successfully\n\n");
			return;
		} // if
		current = current->NEXT; // next machine
	} // while

	printf("Machine with chassis number %s not found\n\n", searchNum);
} // updateMachine

void deleteMachine(machineT** top)
{

} // deleteMachine

void generateStatistics(machineT* top)
{

} // genearteStatistics

void saveToFile(machineT* top)
{

} // saveToFile

void listMachines(machineT* top)
{

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