// warnings
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> // malloc
#include<string.h> // strings

// structure for linked list
typedef struct machine
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
	machineT* newMachine;
	newMachine = (machineT*)malloc(sizeof(machineT));
	if (newMachine == NULL)
	{
		printf("Memory allocation failed\n");
		return;
	} // if

	// prompting the user for input
	printf("Enter chassis number: ");
	scanf("%s", newMachine->chassisNum);
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

	newMachine->NEXT = *top; // adding to linked list
	*top = newMachine; // update top pointer

	printf("Machine added successfully\n");

} // addMachine

void displayToScreen(machineT* top) // displaying all the machinery
{
	if (top == NULL)
	{
		printf("No machines to display\n");
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
	printf("End of list\n");
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
			printf("Breakdown: %d\n", top->breakdown);

			found = 1;
			break;
		} // if

		top = top->NEXT; // next machine
	} // while

	if (found == 0)
	{
		printf("Machine with chassis number %s not found\n", displayChassis);
	} // if
} // displayMachineDetails

void updateMachine(machineT* top)
{

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