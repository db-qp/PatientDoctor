

// CSE240 Spring 2019 HW 7 & 8
// Dawson Black
// Write the compiler used: Visual studio

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of patient information.
// The global linked list 'list' is a list of patients with each node being struct 'patientList'.
// 'patientList' consists of struct 'patient' which has: patient name, room number, and a linked list of 'doctors'.
// The linked list of doctors has each node containing simply the name of the doctor.
// HW7 ignores the 'doctors' linked list since there is no operation/manipulation to be done on 'doctors' list in HW7.
// HW8 has operations/manipulations to be done with 'doctors' list like add a doctor, display last added doctor.

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// Yyou are not allowed to modify main ().
// You can use string library functions.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****
// ***** Before implementing any function, see how it is called in executeAction() *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio

#define MAX_NAME 30

// global linked list 'list' contains the list of patients (pointers of patient node and next)
struct patientList {
	struct patient *patient;
	struct patientList *next;
} *list = NULL;				// currently empty list

// structure "patient" contains the patient's name, room number and linked list of doctors
struct patient {
	char name[MAX_NAME];
	unsigned int roomNumber;
	struct doctor *doctors;		// linked list 'doctors' contains names of doctors
};

//  structure 'doctor' contains doctor's name and next pointer
struct doctor {
	char name[MAX_NAME];
	struct doctor *next;
};

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
// HW 7
void addPatient(char* patientNameInput, unsigned int roomNumInput); // 15 points
void displayPatientList(struct patientList* tempList);								  // 10 points
struct patient* searchPatient(char* patientNameInput);	  // 10 points
void removePatient(char* patientNameInput);				  // 15 points
//HW 8
void addDoctor(char* patientNameInput, char* doctorNameInput);	// 15 points
char* lastDoctor(char* patientNameInput);					// 15 points
void displayPatientAndDoctorList(struct patientList* tempList);							// 10 points
// edit removePatient()										// 10 points

int main()
{
	char selection = 'a';		// initialized to a dummy value
	do
	{
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new patient to the list\n");
		printf("\t d: display patient list (no doctors)\n");
		printf("\t r: remove a patient\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a doctor of a patient\n");
		printf("\t l: display last added doctor of a patient\n");
		printf("\t b: display patient list including doctors\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char patientNameInput[MAX_NAME], doctorNameInput[MAX_NAME];
	unsigned int roomNumInput;
	struct patient* searchResult = NULL;

	switch (c)
	{
	case 'a':	// add patient
				// input patient details from user
		printf("\nPlease enter patient's name: ");
		fgets(patientNameInput, sizeof(patientNameInput), stdin);
		patientNameInput[strlen(patientNameInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumInput);
		flushStdIn();

		if (searchPatient(patientNameInput) == NULL)	// un-comment this line after implementing searchPatient()					
		//if (1)									// comment out this line after implementing searchPatient()
		{
			addPatient(patientNameInput, roomNumInput);
			printf("\nPatient successfully added to the list!\n");
		}
		else
			printf("\nThat patient is already on the list!\n");
		break;

	case 'd':		// display the list
		displayPatientList(list);
		break;

	case 'r':		// remove patient
		printf("\nPlease enter patient's name: ");
		fgets(patientNameInput, sizeof(patientNameInput), stdin);
		patientNameInput[strlen(patientNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchPatient(patientNameInput) == NULL)	// un-comment this line after implementing searchPatient()					
		//if (0)									// comment out this line after implementing searchPatient()
			printf("\nPatient name does not exist or the list is empty! \n\n");
		else
		{
			removePatient(patientNameInput);
			printf("\nPatient successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add doctor
		printf("\nPlease enter patient's name: ");
		fgets(patientNameInput, sizeof(patientNameInput), stdin);
		patientNameInput[strlen(patientNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchPatient(patientNameInput) == NULL)	// un-comment this line after implementing searchPatient()					
		//if (0)										// comment out this line after implementing searchPatient()
			printf("\nPatient name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter doctor's name: ");
			fgets(doctorNameInput, sizeof(doctorNameInput), stdin);
			doctorNameInput[strlen(doctorNameInput) - 1] = '\0';	// discard the trailing '\n' char

			addDoctor(patientNameInput, doctorNameInput);
			printf("\nDoctor added! \n\n");
		}
		break;

	case 'l':		// last doctor
		printf("\nPlease enter patient's name: ");
		fgets(patientNameInput, sizeof(patientNameInput), stdin);
		patientNameInput[strlen(patientNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchPatient(patientNameInput) == NULL)	// un-comment this line after implementing searchPatient()					
		//if (0)										// comment out this line after implementing searchPatient()
			printf("\nPatient name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nLast doctor added: %s\n\n", lastDoctor(patientNameInput));
		}
		break;

	case 'b':		// display patient details along with doctor list
		displayPatientAndDoctorList(list);
		break;

	case 'q':		// quit
		break;

	default: printf("%c is invalid input!\n", c);
	}
}

// HW7 Q1: addPatient (15 points)
// This function is used to insert a new patient in the linked list. 
// You must insert the new patient to the head of linked list 'list'.
// You need NOT check if the patient already exists in the list because that is taken care by searchPatient() called in executeAction(). Look at how this function is used in executeAction().
// Don't bother to check how to implement searchPatient() while implementing this function. Simply assume that patient does not exist in the list while implementing this function.
// NOTE: The function needs to add the patient to the head of the list.
// NOTE: This function does not add doctors to the patient info. There is another function addDoctor() in HW8 for that.
// Hint: In this question, no doctors means NULL doctors.

void addPatient(char* patientNameInput, unsigned int roomNumInput)
{
	// creating nodes for the patientList and patient
	struct patientList* newNode = (struct patientList*)malloc(sizeof(struct patientList));
	struct patient* newPatient = (struct patient*)malloc(sizeof(struct patient));
	
	// putting the input of the parameters into the patient
	strcpy(newPatient->name, patientNameInput);
	newPatient->roomNumber = roomNumInput;
	newPatient->doctors = NULL;

	// parameters for the node linking to that patient
	newNode->next = NULL;
	newNode->patient = newPatient;

	// puts the newNode at the head of the linked list
	if (list == NULL)
	{
		list = newNode;
	}
	else
	{
		newNode->next = list;
		list = newNode;
	}

}

// HW7 Q2: displayPatientList (10 points)
// This function displays the patient details (struct elements) of each patient.
// Parse through the linked list 'list' and print the patient details ( name and room number) one after the other. See expected output screenshots in homework question file.
// You should not display doctor names (because they are not added in HW7).
// You MUST use recursion in the function to get full points. Notice that 'list' is passed to the function argument. Use recursion to keep calling this function till end of list.

void displayPatientList(struct patientList* tempList)
{
	// stopping condition for recursive function
	if (tempList == NULL)
	{
		return;
	}
	else
	{
		// prints the patient's information
		printf("\nPatient name: %s\nRoom number: %d\n", tempList->patient->name, tempList->patient->roomNumber);

		// recursive call 
		displayPatientList(tempList->next);
	}
}

// HW7 Q3: searchPatient (10 points)
// This function searches the 'list' to check if the given patient exists in the list. Search by patient name.
// If it exists then return that 'patient' node of the list. Notice the return type of this function.
// If the patient does not exist in the list, then return NULL.
// NOTE: After implementing this fucntion, go to executeAction() to comment and un-comment the lines mentioned there which use searchPatient()
//       in case 'a', case 'r', case 'b', case 'l' (total 4 places)
struct patient* searchPatient(char* patientNameInput)
{
	// creates a copy of the list
	struct patientList* temp = list;

	// checks if patients are in the list
	if (temp != NULL)
	{
		while (temp)
		{
			// compares input name to name of patients
			if (strcmp(temp->patient->name, patientNameInput) == 0)
			{
				// returns that patient if found
				return temp->patient;
			}
			
			// moves to next patient
			temp = temp->next;
		}
	}

	// if the patient wasn't found, NULL is returned
	return NULL;	
}

// HW7 Q4: removePatient (15 points)
// This function removes a patient from the list.
// Parse the list to locate the patient and delete that 'patient' node.
// You need not check if the patient exists because that is done in executeAction()
// NOTE: In HW 8, you will need to add code to this function to remove docotrs of that patient as well, when you remove the patient.

void removePatient(char* patientNameInput)
{
	struct patientList* tempList = list;	// work on a copy of 'list'

	if (tempList != NULL)
	{
		// if the node to be removed is the first node in the linked list
		if (strcmp(tempList->patient->name, patientNameInput) == 0)
		{
			// creates a pointer to traverse the doctor's linked list
			struct doctor* docList = tempList->patient->doctors;

			// deletes each doctor in the list 
			while (docList)
			{
				docList = NULL;
				free(docList);

				docList = docList->next;
			}

			// checks if there is one patient in the list
			if (tempList->next == NULL)
			{
				// deletes whole linked list b/c only one patient
				list = NULL;
				free(tempList->patient);
				return;
			}
			else
			{
				// deletes first patient and links the rest of the linked list to list
				list = tempList->next;
				free(tempList->patient);
				return;
			}
		}

		// creates two pointers to traverse the list
		struct patientList* previousPatient = list;
		struct patientList* currentPatient = list->next;

		// loops until currentPatient is NULL
		while (currentPatient)
		{
			// checks if currentPatient name is equal to the input name
			if (strcmp(currentPatient->patient->name, patientNameInput) == 0)
			{
				break;
			}
			else
			{
				// moves to the next patient
				previousPatient = currentPatient;
				currentPatient = currentPatient->next;
			}
		}
		
		// checks if pointer reached the end of the list
		if (currentPatient == NULL)
		{
			printf("\nPatient was not found.\n");
		}
		else
		{
			// creates a pointer to traverse the doctor's linked list
			struct doctor* docList = currentPatient->patient->doctors;

			// deletes each doctor in the list 
			while (docList)
			{
				docList = NULL;
				free(docList);

				docList = docList->next;
			}

			// deletes patient
			previousPatient->next = currentPatient->next;
			free(currentPatient->patient);
		}
		
	}

}

// HW8 Q1: addDoctor (15 points)
// This function adds doctor's name to a patient node.
// Parse the list to locate the patient and add the doctor to that patient's 'doctors' linked list. No need to check if the patient name exists on the list. That is done in executeAction().
// If the 'doctors' list is empty, then add the doctor. If the patient has existing doctors, then you may add the new doctor to the head or the tail of the 'doctors' list.
// You can assume that the same doctor name does not exist. So no need to check for existing doctor names, like we do when we add new patient.
// NOTE: Make note of whether you add the doctor to the head or tail of 'doctors' list. You will need that info when you implement lastDoctor()
//       (Sample solution has doctor added to the tail of 'doctors' list. You are free to add new docotr to head or tail of 'doctors' list.)

void addDoctor(char* patientNameInput, char* doctorNameInput)
{
	struct patientList* tempList = list;          // work on a copy of 'list'

	// creates the new doctor
	struct doctor* newDoctor = (struct doctor*)malloc(sizeof(struct doctor));
	strcpy(newDoctor->name, doctorNameInput);
	newDoctor->next = NULL;

	if (tempList != NULL)
	{
		while (tempList)
		{
			// checks if the patient assigned to the docotor is the patient in the list
			if (strcmp(tempList->patient->name, patientNameInput) == 0)
			{
				// checks if there are any doctors in the linked list
				if (tempList->patient->doctors == NULL)
				{
					tempList->patient->doctors = newDoctor;
				}
				else
				{
					// inserts new doctor at head of linked list
					newDoctor->next = tempList->patient->doctors;
					tempList->patient->doctors = newDoctor;
				}

				return;
			}

			// moves to the next patient
			tempList = tempList->next;
		}
	}
}

// HW8 Q2: lastDoctor (15 points)
// This function returns the name of the last (most recently) added doctor of a patient.
// Parse the list to locate the patient. No need to check if the patient name exists in the list. That is done in executeAction().
// Then parse the doctor names to return the most recently added doctor.
// NOTE: Last doctor does not necessarily mean the tail of 'doctors' list. It means the most recently added doctor. 
//       If you are adding doctor to the head of the list in addDoctor(), then you should return that doctor accordingly.

char* lastDoctor(char* patientNameInput)
{

	struct patientList* tempList = list;		// work on a copy of 'list'
	
	if (tempList != NULL)
	{
		while (tempList)
		{
			// checks if patient in list is the patient in the input
			if (strcmp(tempList->patient->name, patientNameInput) == 0)
			{
				// no doctors returns NULL
				if (tempList->patient->doctors == NULL)
				{
					return NULL;
				}
				else
				{
					// returns the first doctor in the linked list
					return tempList->patient->doctors->name;
				}

				break;
			}

			// moves to next patient
			tempList = tempList->next;
		}
	}
}

// HW8 Q3: displayPatientAndDoctorList (10 points)
// This function displays every detail of each patient, including doctors.
// Parse through the linked list passed as parameter and print the patient details ( name, room number, doctor names) one after the other. See expected output screenshots in homework question file.
// NOTE: This does not have to be a recursive fucntion. You may re-use HW7 Q2 displayPatientList(list) code here.

void displayPatientAndDoctorList(struct patientList* tempList)
{
	// stopping condition for recursive function
	if (tempList == NULL)
	{
		return;
	}
	else
	{
		// prints the patient's information including doctors
		printf("\nPatient name: %s\nRoom number: %d\n", tempList->patient->name, tempList->patient->roomNumber);
		
		// creates pointer to traverse doctor's linked list
		struct doctor* moreDoctors = tempList->patient->doctors;

		// checks if there are doctors in the doctor's linked list
		if (moreDoctors == NULL)
		{
			printf("Doctors: none\n");
		}
		else
		{
			printf("Doctors: ");

			while (moreDoctors)
			{
				// prints doctor's name
				printf("%s\n", moreDoctors->name);

				// moves to next doctor
				moreDoctors = moreDoctors->next;
			}
		}

		// recursive call 
		displayPatientAndDoctorList(tempList->next);
	}
}

