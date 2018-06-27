# include<stdio.h>
# include<stdlib.h>
# include<curse.h>
# include<string.h>
# include<assetManagement.h>
# define LEN sizeof(struct commodity)
# define FORMAT "%-8d%-15s%-12lf%-12.1lf%-12.1lf\n"
# define DATA comm[i].num,comm[i].name,comm[i].count,comm[i].total

void main()
{
	int n; //user choice
	menu(); //display menu
	scanf("%d", &n);
	while(n)
	{
		switch(n)
		{
			case 1:
				in();
				break;
			case 2:
				search();
				break;
			case 3:
				del();
				break;
			case 4:
				modify();
				break;
			case 5:
				insert();
				break;
			case 6:
				order();
				break;
			case 7:
				total();
				break;

			default:
				break;
		}
		getchu();
		menu();
		scanf("%d", &n);
	}
}
void menu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|--------------------Asset Management-------------------|\n");
	printf("\t\t| 0. Exit																								|\n");
	printf("\t\t| 1. New Asset																					|\n");
	printf("\t\t| 2. Search																							|\n");
	printf("\t\t| 3. Delete																							|\n");
	printf("\t\t| 4. Modify																							|\n");
	printf("\t\t| 5. Insert																							|\n");
	printf("\t\t| 6. Order																							|\n");
	printf("\t\t| 7. Total																							|\n");
	printf("\t\t|-------------------------------------------------------|\n");
}
void in()
{
	int i, m = 0;
	char ch[2];
	FILE *fp;
	if((fp = fopen("data", "ab+")) == NULL)
	{
		printf("Error opening file\n");
		return;
	}
	/*
	*The while loop loops through data to see which cell is occupied with asset information
	*To find how many assets are recorded
	*/
	while(!feof(fp))
	{
		if(fread(&comm[m], LEN, 1, fp) == 1)
		{
			m++;
		}
		fclose(fp);
		//if there is nothing logged in file
		if(m == 0)
		{
			printf("Nothing found!");
		}
		//if there is something in file, clear screen and show log
		else
		{
			system("cls");
			show();
		}
		/*
		 error handling, if file cannot create a new file to update
		 exit in() operation
		*/
		if((fp = fopen("data", "wb")) == NULL)
		{
			printf("Cannot open file");
			return;
		}
		for(i = 0; i < m; i++)
		{
			fwrite(&comm[i], LEN, 1, fp);
		}
		printf("Enter new asset: ");
		scanf("%s", ch);
		while(strcmp(ch, "Y") == 0 || strcmp(ch, "y")) //ask user if want to enter new asset
		{
			printf("Enter asset Number: ");
			scanf("%d\n", &comm[m].num);
			/*
				look through asset lists to check if entered asset number already exist
				If yes, show that asset no. already exist exit in() operation
			*/
			for(i = 0; i < m; i++)
			{
				if(comm[i].num == comm[m].num)
				{
					printf("Asset number already exist, press any key to continue ");
					getch();
					fclose(fp);
					return;
				}
			}
			printf("Enter new asset name: ");
			scanf("%s\n", &comm[m].name);
			printf("Enter new asset unit price: ");
			scanf("%s\n", &comm[m].price);
			printf("Enter new asset quantity: ");
			scanf("%s\n", &comm[m].count);
			comm[m].total = comm[m].price * comm[m].count;
			if((fwrite(&comm[m], LEN, 1, fp)) != 1)
			{
				printf("Unable to save\n");
				getch();
			}
			else
			{
				printf("%s already saved\n", comm[m].name);
				m++;
			}
			fclose(fp);
			scanf("%s", ch);
		}
		fclose(fp);
		printf("OK\n");
	}
}
