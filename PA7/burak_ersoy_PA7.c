#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 200	
#define LENGT 20	/* size of gate or input names*/

struct gates{		/* Defination struct of gates*/
	
	char gname[LENGT];
	int type;
	char input1[LENGT], input2[LENGT];
	int in1, in2;
	int out;
	int memory;				/* i have some problem to store memory if the circuit has more than one FLIPFLOP */
	struct gates * inp1;	/* i confused myself about how to solve but i couldn't it */
	struct gates * inp2;
};

int getSize(FILE * circuitFile, int *numOfInput){	/* i read "circuit.txt" to calculate number of inputs and gates*/
	

	char input[LENGT];
	char comp[] ="INPUT";
	char comp2[] = "GATE";
	int counter = 0;	
		while(!feof(circuitFile)){			/* i counted number of spaces on first line to find number of inputs*/
		fscanf(circuitFile, "%s",input);
		if(strcmp(input,comp)==0)
		counter++;
	}
	*numOfInput = counter;
	counter = 0;
	
	while(!feof(circuitFile)){			/* i counted number of newlines to find number of gates */
		fscanf(circuitFile, "%s",input);
		if(strcmp(input,comp2)==0)
		counter++;
	}	
	fclose(circuitFile);
	return (counter-4);
}

int findLasGate(struct gates *g, int numOfGates,int numOfInput){	/* i foud the last output gate */

	int i = 0, j = 0, flag = 0;					/* i searched non-repeated gate name in struct array */

	while(i < (numOfInput+numOfGates)){			/* i compare gate names - gate inputs to find non-repeated*/
		while(j < (numOfInput+numOfGates)){
			if((strcmp(g[i].gname,g[j].input1) == 0 ) || (strcmp(g[i].gname,g[j].input2) == 0)){
				flag = 1;
			}j++;
		}
		if(flag == 0)
			break;
		else
			flag = 0;
		i++; j = 0;
	}
	return i;		/* be returned array of last gate is that otput gate*/
	
}
void fillArrayStruct(struct gates *g,char *line,int nextcell){ 	/* firts look readAndFill() function */
																/* to stored in array of struct each line */
	char type[LENGT];											/* from read the file one-bye-one */

	sscanf(line, "%s",type);	/* to check type of gate --- AND = 1 , OR = 2 , NOT = 3 , FLIPFLOP = 4 */

	if(strcmp(type, "GATE AND") == 0){ /* If type is AND i stored name input1 input2 and type number*/
		
		sscanf(line, "%s%s",type,g[nextcell].gname);
		g[nextcell].type = 1;		
	}
	
	if(strcmp(type, "GATE OR") == 0){	/* If type is OR i stored name input1 input2 and type number*/
		
		sscanf(line, "%s%s",type,g[nextcell].gname);
		g[nextcell].type = 2;
	}
	
	if(strcmp(type, "GATE NOT") == 0){	/* If type is NOT i stored name and only input1 and type number*/
	
		sscanf(line, "%s%s",type,g[nextcell].gname);
		g[nextcell].type = 3;
	}
	
	if(strcmp(type, "GATE FLIPFLOP") == 0){	/* If type is FLIPFLOP i stored name input1 type number */
		
		sscanf(line, "%s%s%s",type,g[nextcell].gname,g[nextcell].input1);		
		g[nextcell].memory = 0;		/* initial value is 0 */
		g[nextcell].type = 4;	
	}		
}

void readAndFill(FILE *circuitFile, int numOfGates,int numOfInput, struct gates *g){/* i read "circuit.txt" and stored all inputs */
																					/* and gates in array of struct g */
	char line[SIZE], chr[LENGT];
	int i = numOfInput, j = 0;
	char cmp[] = "INPUT";
	fscanf(circuitFile,"%s",chr);		
	while(j<numOfInput && !feof(circuitFile) ){
		if(strcmp(chr,cmp)==0)
		{
			fscanf(circuitFile,"%s",g[j].gname);
			g[j].type = 0;
			j++;
		}
		fscanf(circuitFile,"%s",chr);
	}

	fgets(line,sizeof(line),circuitFile);/* i read the other lines and i sent fillArrayStruct function to store next array of struct */
	while(!feof(circuitFile)){
				
		fgets(line,sizeof(line),circuitFile);
		fillArrayStruct(g,line,i);
		i++;
	}
	fclose(circuitFile);
}

void connectSruct(int numOfGates,int numOfInput, struct gates *linkedgate, struct gates *g){/* to creat connection between the gates*/
																							/* using by recursive function */
	int i = 0;

	while(i < (numOfGates+numOfInput)){	

			if(strcmp(linkedgate->input1,g[i].gname) == 0 ){	/* i compared inputs and names if same stored adress of array*/
				linkedgate->inp1 = &g[i];
				connectSruct(numOfGates,numOfInput,&g[i],g);	/* maka same thigs recursive *inp1*/
			}
			if(linkedgate->type == 1 || linkedgate->type == 2){ /* if gate is AND or OR i have to connect inp2 */
				if(strcmp(linkedgate->input2,g[i].gname) == 0){
					linkedgate->inp2 = &g[i];
					connectSruct(numOfGates,numOfInput,&g[i],g);
				}
		}
		i++;
	}
}

int evaluate(struct gates *linkedgate){	/* to evaluate output using by recursive function*/
	
	if(linkedgate->type == 0){	/* BASE CASE*/
		
		return linkedgate->out;
	}
	
	if(linkedgate->type == 1){ /* AND GATE */
		
		int i1 = evaluate(linkedgate->inp1);
		int i2 = evaluate(linkedgate->inp2);
		
		return i1 && i2;
	}
	if(linkedgate->type == 2){ /* OR GATE */
		
		int i1 = evaluate(linkedgate->inp1);
		int i2 = evaluate(linkedgate->inp2);
		
		return i1 || i2;
	}
	if(linkedgate->type == 3){ /* NOT GATE */
	
		int i1 = evaluate(linkedgate->inp1);
		
		return !i1;
	}
	if(linkedgate->type == 4){ /* FLIPFLOP GATE */
		
		int i1 = evaluate(linkedgate->inp1);
		int i2 = linkedgate->memory;
		linkedgate->memory = (i1 || i2); /* to store new memory */
		
		if(i1 && i2)
		return 0;
		else
		return i1 || i2;
	}
}
	/* to read input file after evaluate output value and store output file */
void readInputFile(FILE* outputFile, FILE* inputFile, int numOfInput, struct gates *linkedgate, struct gates* g){

	int i = 0, in;

	while(!feof(inputFile)){
		i=0;
		while(i < numOfInput){
			fscanf(inputFile,"%d",&g[i].out);	/* i read every inputs one by one and strore adress of struct array of input*/
			i++;								/* until "i" reach number of input*/
		}
		fprintf(outputFile,"%d",evaluate(linkedgate));	/* to calculate output after the every line using evaluate() function*/
		if(!feof(inputFile))	/* to not to switch to new line when reach last line*/
		fprintf(outputFile,"\n");
	}
}

int main(){
	
	int numOfGates, numOfInput,lastOfStruct;	/* gate number , input number and store lastgate */
	struct gates *g;							/* array of struct to store circuit.txt */
	struct gates *linkedgate;					/* data struct to connect gates and inputs*/
	
	/* File Operations */
	FILE * input= fopen("input.txt","r");
	FILE * circuit = fopen("circuit.txt","r");
	FILE * output = fopen("output.txt","w");

	numOfGates = getSize(circuit,&numOfInput); 		/* to calculate number of gates and number of inputs */
	
	g = (struct gates*)malloc(sizeof(struct gates)*(numOfGates+numOfInput));	/* to allocate size of array of struct*/
	linkedgate = (struct gates*)malloc(sizeof(struct gates));				

	circuit = fopen("circuit.txt","r");
	readAndFill(circuit,numOfGates,numOfInput,g);			

	lastOfStruct = findLasGate(g,numOfGates,numOfInput);	
	linkedgate = &g[lastOfStruct];						

	connectSruct(numOfGates,numOfInput,linkedgate,g);		
	readInputFile(output,input,numOfInput,linkedgate,g);	

	free(g);
}
