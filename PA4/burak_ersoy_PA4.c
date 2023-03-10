#include<stdio.h> 		/* Defines fopen, fclose, fscanf, fprintf and EOF */
#define WORD_SIZE 10 	/* Maximum word length of  input1.txt */
#define ROW 100 		/* Maximum row of input2.txt */
#define COLUMN 250		/* Maximum column of input2.txt */

void searching (int mx_row, int mx_column, char matrix[ROW][COLUMN]) /* This function saves the words in the input1 file to the array and finds that word in the matrix array. */
{	
	/* Access to file.txt is provided for reading and writing. */
	FILE *inp1 = fopen("input1.txt","r"),
		 *outp = fopen("output.txt","w");
	
	char input1_word[WORD_SIZE]; 		   /* Array holding words in input1 */
	
	int	status_2 = 1,					   /* Input1 File status variable */
		length_of_str = 0,				   /* Length of string variable */
		control_hori, control_vert,
		temp_hori, temp_vert,
		i, j, k, m, n, t, a;			   /* For loop variables */
		
	while(status_2 != EOF) /* The loop continues until all of word in file is read */
	{
		status_2 = fscanf(inp1, "%s", input1_word);
		
		if(status_2 == EOF) /* If the end of the file is reached, the loop ends. */
		{
			break;
		}	
		for(i=0; input1_word[i]!=0; i++) /* This loop finds the length of word */
		{
			length_of_str++;
		}
		/* This part is horizantal searching */
		for(i=0; i<mx_row+1; i++) 
		{	
			for(j=0; matrix[i][j+(length_of_str-1)]!=0; j++) 
			{
				temp_hori=j;
				for(k=0; k<length_of_str; k++) /* Loop checks the word array and matris*/
				{
					if(matrix[i][j]==input1_word[k]) /* This condition checks for each character*/
					{
						control_hori++;
					}
					j++;
				}	
				if(control_hori==length_of_str) /* If all checkings is success,the coordinate is writed to file */
				{
					fprintf(outp,"%s (%d,%d) %s\n",input1_word,i+1,temp_hori+1,"E");
				}	
				j=temp_hori;	
				control_hori=0;
			}
		}
		/* This part is vertical searching */
		for(m=0; m<mx_column; m++) 
		{
			for(n=0; n<mx_row+length_of_str-1; n++)
			{
				temp_vert=n;
				for(t=0; t<length_of_str; t++) /* Loop checks the word array and matris */
				{
					if(matrix[n][m]==input1_word[t]) /* This condition checks for each character */
					{
						control_vert++;
					}	
					n++;
				}	
				if(control_vert == length_of_str) /* If all checkings is success,the coordinate is writed to file */
				{
					fprintf(outp,"%s (%d,%d) %s\n",input1_word,temp_vert+1,m+1,"S");
				}
				n=temp_vert;
				control_vert=0;		
			}
		}
		length_of_str=0;
		
		for(a=0; input1_word[a]!=0; a++) /* Clearing the word array */
		{
			input1_word[a]=0;
		}
	}
	/* Closing the files */   
    fclose(inp1);
    fclose(outp);
}

int main()
{
	FILE  *inp2 = fopen("input2.txt","r"); /* Access to file.txt is provided for reading */
	
	char search_matrix[ROW][COLUMN]={0},   /* Word array and matris (2d-array of input2.txt file) */
		 ch; 										
	int status_1 = 1,					   /* File input2 status variable */ 
		max_row,
		i = 0, j = 0; 					   /* i is value of row, j is value of column */
	
	while(status_1 != EOF) /* This loop reads the characters from the input2.txt file and takes them in a matrix. */
	{
		status_1 = fscanf(inp2, "%c", &ch); /* If the first in the file is character, status will be 1, otherwise status will be 0. */
		
		if(status_1 == EOF) /* If the end of the file is reached, the loop ends. */
		{
			if(max_row<j) /* This condition finds row which is the longest */
			{
				max_row=j;
			}
			break;
		}
		if(ch == '\n') 	/* If fscanf reads '\n' character,values start to take under row by increasing j value */
		{ 
			i++;
			if(max_row<j) 	/* This condition finds row which is the longest */
			{
				max_row=j;
			}
			j=0;
		}
		if(ch != '\n') /* Saves the characters from the input2 file to the matrix. */
		{
			search_matrix[i][j]=ch;
			j++;
		}	
	}
	searching(i,j,search_matrix); /* Sending array of rows, columns and matrices to the searching function. */
	
	/* Closing the file */ 
    fclose(inp2);
    
	return 0;
}
