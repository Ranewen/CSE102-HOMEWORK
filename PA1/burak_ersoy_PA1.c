#include<stdio.h>
#define NUMBER 10 /* This macro determines the number of inputs to be received from the user */
#define EPSILON 0.00001 /* Using this macro eliminates the possibility of division by zero. */

/* Functions */
double conline_slope(double average_x2, double average_x1, double average_y2, double average_y1);
double calc_midpointx(double average_x2, double average_x1);
double calc_midpointy(double average_y2, double average_y1);
double test_point_function(double average_x2, double average_x1, double average_y2, double average_y1, double midpoint_x, double midpoint_y, double sepline_slope);

int main()
{
	/* Variables */
	int i;
	double coo_x, coo_y, temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0; /* coo = coordinate */
	double average_x1, average_y1, average_x2, average_y2, connecting_line_slope, seperating_line_slope, midpoint_x, midpoint_y;

	for(i=0; i<NUMBER; i++) /* This loop takes the x and y coordinates from the user, assigns them to temp1 and temp2 variables and sums them  fýr Class 1*/
	{
		scanf("%lf %lf",&coo_x,&coo_y);	/*read number of points for Class 1*/ 	
		temp1 += coo_x;
		temp2 += coo_y;
	}
	
	average_x1 = temp1 / NUMBER;  /* average points x1 calculated for Class 1 */
	average_y1 = temp2 / NUMBER;  /* average points y1 calculated for Class 1 */
	
	for(i=0; i<NUMBER ;i++) /* This loop takes the x and y coordinates from the user, assigns them to temp3 and temp4 variables and sums them for Class 2 */
	{
		scanf("%lf %lf",&coo_x,&coo_y); /* read number of points for Class 2 */ 	
		temp3 += coo_x;
		temp4 += coo_y;
	}
	
	average_x2 = temp3 / NUMBER; /* average points x2 calculated for Class 2 */
	average_y2 = temp4 / NUMBER; /* average points y2 calculated for Class 2 */
	
	if(average_x2 - average_x1 == 0) 
	{
		average_x2 += EPSILON; /*when calculating the slope of the connection line, the probability of divide by zero is canceled*/
		connecting_line_slope = conline_slope(average_x2,average_x1,average_y2,average_y1);
	}
	else
		connecting_line_slope = conline_slope(average_x2,average_x1,average_y2,average_y1);

	
	midpoint_x = calc_midpointx(average_x2,average_x1); /* midpoint's coordinate x calculated */
	midpoint_y = calc_midpointy(average_y2,average_y1); /* midpoint's coordinate y calculated */
	
	if(connecting_line_slope == 0) 
	{
		connecting_line_slope += EPSILON; /* when calculating the slope of the separating line, the probability of divide by zero is canceled */
	}
		
	seperating_line_slope = -1 / connecting_line_slope; /* seperating line's slope calculated.*/
	test_point_function(average_x2,average_x1,average_y1,average_y2, midpoint_x, midpoint_y,seperating_line_slope);
	 
	return 0;	
}
/* This function finds and returns the slope of the connecting line */
double conline_slope(double average_x2, double average_x1, double average_y2, double average_y1)
{
	return (average_y2 - average_y1) / (average_x2 - average_x1);	
}
/* This function finds and returns the midpoint x coordinates */
double calc_midpointx(double average_x2, double average_x1)
{
	return ((average_x1 + average_x2) / 2);
}
/* This function finds and returns the midpoint y coordinates */
double calc_midpointy(double average_y2, double average_y1)
{
	return ((average_y1 + average_y2) / 2);
}
/* This function takes 2 values from the user and compares these values with the average coordinates x1, x2, y1, y2 and returns which class they belong to as a result of this comparison. */
double test_point_function(double average_x2, double average_x1, double average_y2, double average_y1,double midpoint_x, double midpoint_y,double seperating_line_slope)
{
	double testpoint_x,testpoint_y; 
	
	while(scanf("%lf %lf",&testpoint_x,&testpoint_y)) /*get test points and exit status set when character is entered*/
	{	
		if(average_y1>average_y2 || average_x1>average_x2)
		{
			if((testpoint_y-midpoint_y)>(seperating_line_slope*(testpoint_x-midpoint_x)))
			{
				return printf("class 1\n");
			}
			else if((testpoint_y-midpoint_y)<(seperating_line_slope*(testpoint_x-midpoint_x)))
			{
				return printf("class 2\n");
			}
		}
	/*according to the equation of the separating line, which test point belongs to which class.*/
		if(average_y2>average_y1 || average_x2>average_x1)
		{
			if((testpoint_y-midpoint_y)<(seperating_line_slope*(testpoint_x-midpoint_x)))
			{
				return printf("class 1\n");
			}
			else if((testpoint_y-midpoint_y)>(seperating_line_slope*(testpoint_x-midpoint_x))){
				return printf("class 2\n");
			}
		}
	}
}
