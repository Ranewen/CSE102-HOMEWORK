#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARB_CAL_1G 4 /* Number of calories in 1g carbohydrate */
#define PROTEIN_CAL_1G 4 /* Number of calories in 1g protein */
#define FAT_CAL_1G 9 /* Number of calories in 1g fat */
#define WATER_CAL_1G 0 /* Number of calories in 1g water */

struct parents 
{	   
	   double nums;
	   char *name; 
};

int parser(char *skey, struct parents nParent[])
{	
	
	int i = 0;
	double number;
	char *temp;

	temp = strtok (skey, ", ");		
	while(temp!=NULL)
	{
		nParent[i].nums = number;		
		nParent[i].name = (char*)malloc(sizeof(char)*strlen(temp)+1);
		strcpy(nParent[i].name,temp); 	
		temp = strtok (NULL, ", ");
		i++;
	}
	return i;							
}

float recursive_function(char *object, char *parentObject,double total)
{ 	
	char *temp1, tmp , *temp2,answer[100], answer2[100], check[100];
	struct parents nParent[20];
	double value, number;
	int i = 0,flag = 0, count;

	printf("What is %s?:\n",object);
	scanf("%c",&tmp);
	scanf("%[^\n]",answer);	
	strcpy(check,answer); 
	temp1 = strtok (check, "( ");
	temp2 = strtok (NULL, "g");
	if(atoi(temp2))
	{
		number = atof(temp2);
		printf("List the amount macro nutrients in %s:\n",object);
		scanf("%[^\n]",answer2);
		
	}
	if(temp1 == NULL)				
		return value;
	else
	{							
		count = parser(answer,nParent);
		while(i < count){			

			value = recursive_function(nParent[i].name,object,total);
			total += value*nParent[i].nums;
			i++;
		}
		return total;
	}
}

int main(void)
{
	char  nameObjet[100];
	char * temp,tmp;
	double number = 1.00, result = 0.00;
	
	printf("What is the meal:\n");	
	scanf("%[^\n]",nameObjet);			

	temp = strtok(nameObjet, " ");	
	if(atoi(temp))
	{
		number = atof(temp);
		temp = strtok (NULL, " ");
	}
	result = recursive_function(temp,temp,result);	
}
