#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define LINESIZE 6
#define M 100
#define MATRIXSIZE 10

    /**
 * @brief a function that finds max number in array.
 * @return return max valued number in arr.
 */
int maxVal (int arr[], int n){
	int max_val = arr[0];
	for(int i = 1; i < n; i++){
		max_val = (max_val < arr[i]) ? arr[i] : max_val;
	}
	return max_val;
}

/**
 * @brief a function that finds min number in array.
 * @return return min valued number in arr.
 */
int minVal (int arr[], int n){
	int min_val = arr[0];
	for(int i = 1; i < n; i++){
		min_val = (min_val < arr[i]) ? min_val: arr[i];
	}
	return min_val;
}

/**
* @brief a function that finds average for all values in array.
* @return return average in float type.
*/
float avgVal (int arr[], int n){
	float avg_val = arr[0];
	for(int i = 1; i < n; i++){
		avg_val +=  (float)arr[i];
	}
	return (float)(avg_val/n);
}
/**
 * @brief a function that finds the percentage of passed grades.
 * @return return the pass percentage in float type.
 */
float passPerc (int arr[], int n){
	int cnt = 0;
	for(int i = 0; i < n; i++){
		if (arr[i] >= 55){
			cnt++;
		}
	}
	return (float)(cnt*100)/(float)(n);
}

/**
* @brief a function that swap values for to int pointers.
*/
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
* @brief a function to sort array using bubble sort.
* @return return sorted array.
*/
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

/**
* @brief a function that finds the median for all values in array.
           function uses bubble sort as a sub-routine to sort the array.
* @return return median for all values in array.
*/
int medianVal (int arr[], int n){
	//call to sort func
	bubbleSort(arr,n);
	int index = (n+1)/2;
	return arr[index];
}



int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    FILE *fp1 , *fp2;
    fp1 = fopen ( "course_statistics.txt" ,"w");
    fp2 = fopen("grades.txt", "r");

    //importing number of student as a parameter from bash script
    int num_of_students = atoi(argv[2])-1;
    int arr_of_grades[num_of_students];
    //scanning fp2 line by line and filling arr_of_grades
    for (int i=0; i<num_of_students; i++)
    {
    arr_of_grades[i]=0;
    char grade;
	fgets(&grade,LINESIZE,fp2);
	 arr_of_grades[i]=atoi(&grade);
    }


    //printing results to fp1
     fprintf(fp1,"num of students = %d\n" , num_of_students);
     fprintf(fp1,"avg = %.3f\n" , avgVal (arr_of_grades,num_of_students));
     fprintf(fp1,"the median is - %d\n" ,
    		 medianVal (arr_of_grades,num_of_students));
     fprintf(fp1,"max grade = %d, min grade = %d\n" ,
    		 maxVal (arr_of_grades,num_of_students),
			 minVal (arr_of_grades,num_of_students));
     fprintf(fp1,"pass rate = %.2f%%\n" ,
    		 passPerc(arr_of_grades,num_of_students));

     int *hist = malloc(sizeof(int)*M);

	 for(int i = 0; i<num_of_students; i++){
		hist[arr_of_grades[i]-1]++;
	 }

	 for(int i = 0; i < MATRIXSIZE; i++){
		for(int j = 0; j < MATRIXSIZE; j++){
			fprintf(fp1,"%d", hist[i*MATRIXSIZE+j]);
			if (j != MATRIXSIZE-1){
				fprintf(fp1," ");
			}
		}
		fprintf(fp1,"\n");
	 }

    fclose (fp1);
    fclose (fp2);

    return 0;
}
