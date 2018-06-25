# include<stdio.h>
# include<stdlib.h>
# include<conio.h>
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

