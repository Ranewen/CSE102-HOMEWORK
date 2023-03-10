#include <stdio.h>  /* Defines fopen, fclose, fscanf, fprintf and EOF */ 
#define MAX 100     /* This macro determines the maximum capacity of the array. */

int main()
{
	/* Access to file.txt is provided for reading and writing. */
	FILE *inp = fopen("input.txt","r+");
	FILE *out = fopen("output.txt","w+");
	
	int input_numbers[MAX];				/* Assigning the data from the input.txt file to an array */
	int repeat_numbers[MAX];			/* The array that will get the number of repeats from the text file */
	int nums[MAX];						/* The array, where each of the integers from the input.txt file will be entered once. */
	
	int number_count = 0,				/* Number amount in input.txt file */
		number_count2 = 0,				/* The variable that holds more than 100 repeated numbers in the file */ 
    	index1_numbers = 0,             /* This variable is used to determine the index number of the numbers to operate on in the array.*/
	 	index2_numbers = 0,             /* This variable is used to determine the index numbers of the numbers to operate in the arrays. */
		number_of_elements = 0,	        /* The variable that defines the number of elements in the array nums[]. */
	 	count = 0,                      /* Variable that temporarily holds the amount of repeated numbers */
		temp_number,                    /* We assign the numbers that we will process in the input_numbers array, in order */
		file_numbers;					/* A number assigning variable for the input.txt file */
		
    int i, j, k, l, m,                  /* For Loop control variables */
    	a=0 , b=0, c=0;					/* While Loop control variables */
    
    int temp1, temp2, temp3;			/* Variables that temporarily holds array numbers */


	/* File Check operation */
    if (inp == NULL)
	{  
        printf("File not found");  
    }
    else
    {
    	while(!feof(inp)) /*  The while loop is used to assign all numbers in the input.txt file to the variable "input_numbers[]" and the integer amount in the file to the variable "number_count." */
		{	
			fscanf(inp,"%d",&file_numbers); /* Their numbers in the file are assigned to the file_numbers variable */
			
			if(number_count < 100)
			{
				input_numbers[number_count] = file_numbers;
				number_count++;
			}
			else if(number_count >= 100)
			{	
				number_count2++;
			}
		
		}
	}
    
	/* For loop used to write the numbers in the input.txt file once and
	   The index1_numbers and index2_numbers variables navigate through the input_numbers array, 
	   comparing the numbers with each other and writing them to nums[] array once.
	*/
	for( ; index1_numbers < number_count; index1_numbers++)
	{
		temp_number = input_numbers[index1_numbers];
		
		for( ; index2_numbers < number_count; index2_numbers++)
		{
			if(temp_number == nums[index2_numbers])
			{
				count++;
			}
		}
		index2_numbers = 0;

		if(count < 1)
		{
			nums[number_of_elements] = input_numbers[index1_numbers];
			number_of_elements++;
		}
		count =0;
	}
	/* The part where we will print the numbers in the nums array, where we take each number once, from least to greatest. */
	for(i=1; i<number_of_elements; i++)
	{
		for(j=0; j<number_of_elements-1; j++)
		{
			if(nums[j] > nums[j+1])
			{
				temp1 = nums[j];
				nums[j] = nums[j+1];
				nums[j+1 ]= temp1;
			}
		}
	}
	/* The part of the code where we find how many times the numbers in the input.txt file are repeated */	
	for(a=0; a<number_of_elements; a++)
	{
		for(b=0; b<number_count; b++)
		{
			if(nums[a] == input_numbers[b])
			{
				c++;
			}
		}
		repeat_numbers[a] = c;
		c=0;
		b=0;
	}
	/* If a number is repeated more than 100 times, the condition that finds the amount of repetition correct. */
	if(number_of_elements == 1 && number_count2 > 0)
	{
		repeat_numbers[0] += number_count2;
	}

	/* The section of the code where the repeating integers are sorted from least to most. */
	for(k=1; k<number_of_elements-1; k++)
	{
		for(l=0; l<number_of_elements-1; l++)
		{
			if(repeat_numbers[l] > repeat_numbers[l+1])
			{
				temp2 = repeat_numbers[l];
				repeat_numbers[l] = repeat_numbers[l+1];
				repeat_numbers[l+1 ]= temp2;

				temp3 = nums[l];
				nums[l] = nums[l+1];
				nums[l+1 ]= temp3;
			}
		}	
	}

	/* The loop print the repetitions of integers and the counted values to the output.txt file */
	for(m=0; m<number_of_elements ;m++) 
	{
		fprintf(out, "%d  : %d\n",nums[m],repeat_numbers[m]);
	}

/* Closing the files */
fclose(inp);
fclose(out);

return 0;
}
