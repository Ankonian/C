//Inserting part of this program was given by Darrell Long in his pdf instructions
# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	int * array = malloc (sizeof(int) * 8);
	int size = 8;
	int length = 0;
	char userInput;
	int numberInput = 0;
	printf("Action? (Insert, Print, or Quit) ");
	scanf(" %c", &userInput);
	while(userInput != 'Q')
	{
		if(userInput == 'I')
		{
			printf("Enter an Integer: "); //Ask user for integer input
			scanf("%d", &numberInput); //record the user integer input
			array [length++] = numberInput; //insert the integer to the end of the array
			if (length == size) //if the array is full
			{
				size += 8; //expand the size by 8
				array = realloc(array, sizeof(int) * size); //reallocate more memory for the array
			}
		}
		if(userInput == 'P')
		{
			printf("Length = %d: ", length); //print out the length of the array
			for(int i = 0; i < length; i++) //loop through the length of the array and print each element in the array
			{
				printf(" %d ", array[i]);
			}
		}
		printf("\n");
		printf("Action? (Insert, Print, or Quit) "); //ask the user for further actions
		scanf(" %c", &userInput);
	}
	free(array); //when user quits the program, free the space allocated for the array
	return 0;
}
