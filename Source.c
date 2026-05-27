#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILE_NAME "trainings.dat"

typedef enum
{
	CREATE_TRAINING = 1,
	READ_TRAININGS,
	UPDATE_TRAINING,
	DELETE_TRAINING,
	EXIT_PROGRAM

} MenuOption;

typedef struct
{
	int id;
	char traineeName[MAX_NAME_LENGTH];
	int duration;
	float caloriesBurned;

} Training;

/* GLOBALNA VARIJABLA */

int globalTrainingCounter = 0;

/* PROTOTIPI */

void showMenu();
void clearInputBuffer();

void saveToFile(const Training* trainings, int count);
void loadFromFile(Training** trainings, int* count);

void createTraining(Training** trainings, int* count);
void readTrainings(const Training* trainings, int count);
void updateTraining(Training* trainings, int count);
void deleteTraining(Training** trainings, int* count);

int findTrainingIndex(const Training* trainings, int count, int id);

/* MAIN */

int main()
{
	/* FIX ZA VISUAL STUDIO KONZOLU */
	setvbuf(stdout, NULL, _IONBF, 0);

	Training* trainings = NULL;
	int trainingCount = 0;
	int option = 0;

	loadFromFile(&trainings, &trainingCount);

	do
	{
		showMenu();

		if (scanf("%d", &option) != 1)
		{
			printf("\nPogresan unos!\n");
			clearInputBuffer();
			continue;
		}

		clearInputBuffer();

		switch (option)
		{
		case CREATE_TRAINING:

			createTraining(&trainings, &trainingCount);
			break;

		case READ_TRAININGS:

			readTrainings(trainings, trainingCount);
			break;

		case UPDATE_TRAINING:

			updateTraining(trainings, trainingCount);
			break;

		case DELETE_TRAINING:

			deleteTraining(&trainings, &trainingCount);
			break;

		case EXIT_PROGRAM:

			printf("\nGasenje programa...\n");
			break;

		default:

			printf("\nPogresna opcija!\n");
		}

	} while (option != EXIT_PROGRAM);

	/* FREE MEMORY */

	if (trainings != NULL)
	{
		free(trainings);
		trainings = NULL;
	}

	return 0;
}

/* CLEAR BUFFER */

void clearInputBuffer()
{
	while (getchar() != '\n');
}

/* MENU */

void showMenu()
{
	printf("\n=============================\n");
	printf(" FITNESS MANAGEMENT SYSTEM\n");
	printf("=============================\n");

	printf("1. Dodaj trening\n");
	printf("2. Prikazi treninge\n");
	printf("3. Azuriraj trening\n");
	printf("4. Obrisi trening\n");
	printf("5. Izlaz\n");

	printf("=============================\n");
	printf("Odabir: ");
}

/* SAVE FILE */

void saveToFile(const Training* trainings, int count)
{
	FILE* file = fopen(FILE_NAME, "wb");

	if (file == NULL)
	{
		printf("\nGreska kod datoteke!\n");
		return;
	}

	fwrite(&count, sizeof(int), 1, file);

	if (count > 0)
	{
		fwrite(trainings, sizeof(Training), count, file);
	}

	fclose(file);
}

/* LOAD FILE */

void loadFromFile(Training** trainings, int* count)
{
	FILE* file = fopen(FILE_NAME, "rb");

	if (file == NULL)
	{
		*count = 0;
		return;
	}

	fread(count, sizeof(int), 1, file);

	if (*count > 0)
	{
		*trainings = (Training*)calloc(*count, sizeof(Training));

		if (*trainings == NULL)
		{
			fclose(file);
			return;
		}

		fread(*trainings, sizeof(Training), *count, file);

		for (int i = 0; i < *count; i++)
		{
			if ((*trainings)[i].id > globalTrainingCounter)
			{
				globalTrainingCounter = (*trainings)[i].id;
			}
		}
	}

	fclose(file);
}

/* FIND */

int findTrainingIndex(const Training* trainings, int count, int id)
{
	if (trainings == NULL)
	{
		return -1;
	}

	for (int i = 0; i < count; i++)
	{
		if (trainings[i].id == id)
		{
			return i;
		}
	}

	return -1;
}

/* CREATE */

void createTraining(Training** trainings, int* count)
{
	Training* temp = NULL;
	Training* newTraining = NULL;

	if (trainings == NULL || count == NULL)
	{
		return;
	}

	temp = (Training*)realloc(
		*trainings,
		(*count + 1) * sizeof(Training)
	);

	if (temp == NULL)
	{
		printf("\nGreska kod memorije!\n");
		return;
	}

	*trainings = temp;

	newTraining = &((*trainings)[*count]);

	newTraining->id = ++globalTrainingCounter;

	printf("\nIme vjezbaca: ");
	fgets(newTraining->traineeName, MAX_NAME_LENGTH, stdin);

	newTraining->traineeName[
		strcspn(newTraining->traineeName, "\n")
	] = '\0';

	printf("Trajanje treninga (min): ");

	if (scanf("%d", &newTraining->duration) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	printf("Potrosene kalorije: ");

	if (scanf("%f", &newTraining->caloriesBurned) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	(*count)++;

	saveToFile(*trainings, *count);

	printf("\nTrening uspjesno dodan!\n");
}

/* READ */

void readTrainings(const Training* trainings, int count)
{
	if (trainings == NULL || count == 0)
	{
		printf("\nNema treninga!\n");
		return;
	}

	printf("\n===== LISTA TRENINGA =====\n");

	for (int i = 0; i < count; i++)
	{
		printf("\n--------------------------\n");

		printf("ID: %d\n", trainings[i].id);
		printf("Ime: %s\n", trainings[i].traineeName);
		printf("Trajanje: %d min\n", trainings[i].duration);
		printf("Kalorije: %.2f\n", trainings[i].caloriesBurned);
	}
}

/* UPDATE */

void updateTraining(Training* trainings, int count)
{
	int id = 0;
	int index = 0;

	if (trainings == NULL || count == 0)
	{
		printf("\nNema treninga!\n");
		return;
	}

	printf("\nUnesite ID treninga: ");

	if (scanf("%d", &id) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	index = findTrainingIndex(trainings, count, id);

	if (index == -1)
	{
		printf("\nTrening nije pronaden!\n");
		return;
	}

	printf("Novo ime: ");

	fgets(trainings[index].traineeName, MAX_NAME_LENGTH, stdin);

	trainings[index].traineeName[
		strcspn(trainings[index].traineeName, "\n")
	] = '\0';

	printf("Novo trajanje: ");

	if (scanf("%d", &trainings[index].duration) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	printf("Nove kalorije: ");

	if (scanf("%f", &trainings[index].caloriesBurned) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	saveToFile(trainings, count);

	printf("\nTrening uspjesno azuriran!\n");
}

/* DELETE */

void deleteTraining(Training** trainings, int* count)
{
	int id = 0;
	int index = 0;

	if (trainings == NULL || *trainings == NULL || *count == 0)
	{
		printf("\nNema treninga!\n");
		return;
	}

	printf("\nUnesite ID za brisanje: ");

	if (scanf("%d", &id) != 1)
	{
		printf("\nPogresan unos!\n");
		clearInputBuffer();
		return;
	}

	clearInputBuffer();

	index = findTrainingIndex(*trainings, *count, id);

	if (index == -1)
	{
		printf("\nTrening nije pronaden!\n");
		return;
	}

	for (int i = index; i < *count - 1; i++)
	{
		(*trainings)[i] = (*trainings)[i + 1];
	}

	(*count)--;

	if (*count == 0)
	{
		free(*trainings);
		*trainings = NULL;
	}
	else
	{
		Training* temp = (Training*)realloc(
			*trainings,
			(*count) * sizeof(Training)
		);

		if (temp != NULL)
		{
			*trainings = temp;
		}
	}

	saveToFile(*trainings, *count);

	printf("\nTrening uspjesno obrisan!\n");
}