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
	char machineType[50];
	int breakdown;
}MachineT;

// function prototypes
void addMachine(MachineT** top);
void displayToScreen(MachineT* top);
void displayMachineDetails(MachineT* top);
void updateMachine(MachineT* top);
void deleteMachine(MachineT** top);
void generateStatistics(MachineT* top);
void saveToFile(MachineT* top);
void listMachines(MachineT* top);
int menu();

int main()
{
	// variables
	MachineT* top = NULL; 
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
	} while (choice != -1); // do-ehile
} // main

void addMachine(MachineT** top)
{

} // addMachine

void displayToScreen(MachineT* top)
{

} // displayToScreen

void displayMachineDetails(MachineT* top)
{

} // displayMachineDetails

void updateMachine(MachineT* top)
{

} // updateMachine

void deleteMachine(MachineT** top)
{

} // deleteMachine

void generateStatistics(MachineT* top)
{

} // genearteStatistics

void saveToFile(MachineT* top)
{

} // saveToFile

void listMachines(MachineT* top)
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