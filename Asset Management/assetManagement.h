# include<stdio.h>
# include<stdlib.h>
# include<conio.h>
# include<string.h>
# define LEN sizeof(struct commodity)
# define FORMAT "%-8d%-15s%-12lf%-12.1lf%-12.1lf\n"
# define DATA comm[i].num,comm[i].name,comm[i].count,comm[i].total

struct commodity
{
        int num; //Asset Number
        char name[15];  //Asset name
        double price; //asset price
        double count; //amount of asset
        double total; //total cost of assets
};
struct commodity comm[50] //different types of assets storedi
void in();
void show();
void order();
void del();
void modify();
void menu();
void insert();
void total();
void search();
