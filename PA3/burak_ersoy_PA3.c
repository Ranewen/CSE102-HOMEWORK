#include<stdio.h> 	/* Defines fopen, fclose, fscanf, fprintf and EOF */

#define MAX 1000 	/* The maximum length of the input sequence */
#define p1 0.5 		/* p1 is a pre-defined variable as constant */
#define p2 20 		/* p2 is a pre-defined variable as constant */

/* Global variables */
int i, j;

double average_of_chunk(double input_array[], int index1, int index2) /* This function calculates average of chunk by using index value and return average_chunk */
{
	int k = index1;
	double average_chunk = 0.0;
	
	while(k <= index2) /* This loop sums the numbers in the two index ranges coming to the function. */
	{
		average_chunk += input_array[k];
		k++;
	}
	average_chunk /= (index2-index1+1); /* Chunk average calculation process */ 
	return average_chunk;
}

void sort_average_chunk(double arr_avg_chunk[], int index[][2], int coordinate) /* This function sorts averages and index values. */
{
	double temp_average;
	int minimum,
		temp_index1,
		temp_index2;
	
	for(i=0; i<coordinate-1; i++)
	{	
		minimum=i;
		
		for(j=i+1; j<coordinate; j++)
		{
			if(arr_avg_chunk[j]<arr_avg_chunk[minimum]) 
			{
				minimum=j;
			}
		}
		/* The section of the code, this function where the average of chunks and indexes are sorted from least to most. */
		temp_average = arr_avg_chunk[i];
		arr_avg_chunk[i] = arr_avg_chunk[minimum];
		arr_avg_chunk[minimum] = temp_average;
		
		temp_index1 = index[i][0];
		index[i][0] = index[minimum][0];
		index[minimum][0] = temp_index1;
		
		temp_index2 = index[i][1];
		index[i][1] = index[minimum][1];
		index[minimum][1] = temp_index2;
	}
}

void write_to_file(double input_numbers[], int index_chunk[][2], int coord) /* This function writes chunks ordered as stacked lines based on the calculated average of each. and the chunk with the smallest average is on the first */
{
	/* Access to file.txt is provided for writing. */
	FILE *outp = fopen("output.txt","w");
	for(i=0; i<coord; i++) /* The loop writes chunks ordered as stacked lines based on the calculated average of each. */
	{
		for(j=index_chunk[i][0]; j<=index_chunk[i][1]; j++)
		{			
			fprintf(outp,"%.4lf ",input_numbers[j]);
		}
		fprintf(outp,"\n");		
	}
	fclose(outp); /* Closing the file */
}

int main(void)
{
	/* Access to file.txt is provided for reading. */
	FILE *inp = fopen("input.txt","r");
	
	int index_of_chunk[100][2],					/* Hold the indexes of the chunk */
		count = 1,                          	/* Variable that holds the amount of numbers in the file */
		coordinate = 0,							/* index of index_of_chunk array */
		status,									/* File status variable */
		condition;								/* State condition */		
	double input_numbers[MAX],					/* Maximum length of the input sequence */
		   avg_of_chunk[100],					/* Maximum number of chunks */
		   a,								
		   b,
		   n;
	
	/* File Check operation */
    if (inp == NULL)
	{  
        printf("File not found");  
    }	   
	else
	{
		status = fscanf(inp,"%lf",&input_numbers[0]);	/* If the first number in the file is double, status will be 1, otherwise status will be 0. */	
		i = 1;
		while(status == 1 && status != EOF) /* The while loop is used to assign all numbers in the input.txt file to the array "input_file[]" */
		{
			status=fscanf(inp,"%lf",&input_numbers[i]); 
			
			if(status != 1 || status == EOF ) /* The condition of whether the number is double or not */
			{
				break; /* If the number is not a double or the end of the file is reached, the loop ends. */
			}
			count++;
			i++;
		}
	}
	
	i=0;
	j=1;
	while(j < count+1)  /*This loop finds the indexes of chunks */
	{
		if(j == count) /* If j value is non-index, the loop is finished */
		{
			index_of_chunk[coordinate][0] = i;	  
			index_of_chunk[coordinate][1] = j-1;  
			coordinate += 1;
			break;		
		}
		
		n = input_numbers[j]; 	/* j is index of n (added number)*/	
		a = average_of_chunk(input_numbers,i,j-1);	/* average (not include n) */
		b = average_of_chunk(input_numbers,i,j);	/* average (include n) */
		condition = !((b>a*(1+p1)) || (b<a*(1-p1)) || (a>n*p2) || (a<n/p2)); /* Condition for adding n to the chunk */
		
		if(!condition) /*If condition is false, j-1 value is saved.*/
		{
			index_of_chunk[coordinate][0] = i;  /* Save the i value */
			index_of_chunk[coordinate][1] = j-1; /* Save the j-1 value */
			coordinate += 1;
			i = j;
		}
		j++;
	}
	
	j=0;
	for(i=0; i<coordinate; i++) /* This loop uses the index i in the chunk index and sends it to the average_of_chunk function and finds the average of the chunk and writes it to avg_of chunk */
	{
		avg_of_chunk[j] = average_of_chunk(input_numbers,index_of_chunk[i][0],index_of_chunk[i][1]);  /* Finds array which includes averages of chunks by using average function */	
		j++;
	}
	
	sort_average_chunk(avg_of_chunk, index_of_chunk, coordinate);/* This function sorts the average and indexes of chunks */
	write_to_file(input_numbers, index_of_chunk, coordinate); /* This function writes chunks to file */ 
	
	/* Closing the files */		
	fclose(inp);
	
	return 0;
}
