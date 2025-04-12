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
void addMachine(machineT** top);
void displayToScreen(machineT* top);
void displayMachineDetails(machineT* top);
void updateMachine(machineT* top);
void deleteMachine(machineT** top);
void generateStatistics(machineT* top);
void saveToFile(machineT* top);
void listMachines(machineT* top);
int menu();

int main()
{
	// variables
	machineT* top = NULL; 
	int choice;

	do {
		choice = menu();
		switch (choice)
		{
			case 1:
				addMachine(&top);
				break;
			case 2:
				displayToScreen(top);
				break;
			case 3:
				displayMachineDetails(top);
				break;
			case 4:
				updateMachine(top);
				break;
			case 5:
				deleteMachine(top);
				break;
			case 6:
				generateStatistics(top);
				break;
			case 7:
				saveToFile(top);
				break;
			case 8:
				listMachines(top);
				break;
			case -1:
				printf("Exiting...\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		} // switch
	} while (choice != -1); // do-while
} // main

void addMachine(machineT** top)
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

void displayToScreen(machineT* top)
{

} // displayToScreen

void displayMachineDetails(machineT* top)
{

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