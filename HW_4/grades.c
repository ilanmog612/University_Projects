#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked-list.h"
#include "grades.h"
#define SUCCESS 0
#define FAIL 1
#define AVG_FAIL -1
#define MAX_GRADE 100
#define MIN_GRADE 0

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init();

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades);

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id);

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist 
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade);

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out);

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id);

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades);

/* Inner functions block */

/**
 * @brief clones "student" to "output".
 * @return Returns 0 on success.
 */
static int student_clone (void *student, void **output);

/**
 * @brief clones "course" to "output".
 * @return Returns 0 on success.
 */
static int course_clone (void *course, void **output);

/**
 * @brief destroys "student".
 * @return Returns SUCCESS - always succeed.
 */
static void student_destroy (void *student);

/**
 * @brief destroys "course".
 * @return Returns SUCCESS - always succeed.
 */
static void course_destroy (void *course);



/**
 * @brief Searches for a student with a given id
 * @returns Iterator for student with given id in list
 * @note Fails if student_list is invalid or if student was not found
 * @note Fail value is NULL
 */
static struct iterator* find_student (struct list *student_list, int id);

/**
 * @brief Searches for a course with a given name
 * @returns Iterator for course with given name
 * @note Fails if student_courses is invalid or if course was not found
 * @note Fail value is NULL
 */
static struct iterator* find_course (struct list *student_courses,
				 const char *course_name);


/* structs definition block */

typedef struct grades {
	struct list *student_list;

}grades_t;

typedef struct student {
	char *student_name;
	int student_id;
	struct list *student_courses;

}student_t;


typedef struct course {
	char *course_name;
	int grade;

}course_t;




static int student_clone (void *element, void **output) {
	student_t *elem_student = (student_t*)element;
	student_t *cloned_student = (student_t*)malloc(sizeof(student_t));
	if(cloned_student == NULL) {
		 return FAIL;
	}

	/* Creating courses list */
	cloned_student->student_courses = list_init (course_clone, course_destroy );
	cloned_student->student_name =
                    malloc(sizeof(char)*(strlen(elem_student->student_name)+1));
	if(cloned_student->student_name == NULL) {
		free(cloned_student);
		return FAIL;
	}
	/* Copying data */
	strcpy(cloned_student->student_name, elem_student->student_name);
	cloned_student->student_id = elem_student->student_id;
	*output=(void**)cloned_student;
	return SUCCESS;
}


static void student_destroy (void *element) {
	student_t *elem_student = (student_t*)element;
	list_destroy(elem_student->student_courses);
	free(elem_student->student_name);
	free(elem_student);
}

static int course_clone (void *element, void **output) {
	course_t *elem_course = (course_t*)element;
	course_t *cloned_course = (course_t*)malloc(sizeof(course_t));
	if(cloned_course==NULL) {
		 return FAIL;
	}

    /* Creating courses list */
	cloned_course->course_name=
                    malloc(sizeof(char)*(strlen(elem_course->course_name)+1));
	if(cloned_course->course_name==NULL) {
		free(cloned_course);
		return FAIL;
	}
	/* Copying data */
	strcpy(cloned_course->course_name, elem_course->course_name);
	cloned_course->grade = elem_course->grade;
	*output=(void**)cloned_course;
	return 0;
}

static void course_destroy (void *element) {
	course_t *elem_course = (course_t*)element;
	free(elem_course->course_name);
	free(elem_course);
}

static struct iterator* find_student (struct list *student_list,
                                      int student_id) {
	if(student_list == NULL) {
		return NULL;
	}
	struct iterator *it = list_begin (student_list);
	for ( ;it != NULL; it=list_next(it)){
		student_t *elem_student = (student_t*)list_get(it);
		if(elem_student->student_id == student_id){
            /* student with id exists in list */
			return it;
		}
	}
	/* student with id was not found in list */
	return NULL;
}

static struct iterator* find_course (struct list *student_courses,
                                     const char *course_name){
	if(student_courses == NULL) {
		return NULL;
	}
	struct iterator *it = list_begin (student_courses);
	for ( ;it != NULL; it = list_next(it)){
		course_t *elem_course = (course_t*)list_get(it);
		if(strcmp(elem_course->course_name, course_name) == SUCCESS){
			/* course with course_name is in list */
			return it;
		}
	}
	/* course with name was not found in list */
	return NULL;
}


struct grades* grades_init() {
	grades_t *grades= (grades_t*)malloc(sizeof(grades_t));
	if(grades == NULL) {
		return NULL;
	}
	/* creating student element list */
	grades->student_list = list_init (student_clone, student_destroy);
    if (grades->student_list == NULL){
        free(grades);
        return NULL;
    }
	return grades;
}

void grades_destroy(struct grades *grades) {
	list_destroy (grades->student_list);
	free(grades);
}



int grades_add_student (struct grades *grades, const char *name, int id){
	if(grades == NULL) {
		return FAIL;
	}
	/* Searching student by id */
	struct iterator *it = find_student(grades->student_list, id);
	if(it != NULL){
        /* If student with id exists in list */
		 return FAIL;
	}
	/* Create a struct student element */
	student_t *temp=(student_t*)malloc(sizeof(student_t));
	if(temp == NULL) {
		return FAIL;
	}
	int name_length = strlen(name)+1;
	temp->student_name = malloc(sizeof(char)*name_length);
	if((temp->student_name)==NULL) {
	    free(temp);
        return FAIL;
	}
	strcpy(temp->student_name, name);
	temp->student_id = id;
	/* creating empty list for courses */
	temp->student_courses = list_init (course_clone, course_destroy );

    /* pushing student elem to grades->student_list */
	int insert_res = list_push_back(grades->student_list, (void*)temp);
	student_destroy((void*)temp);

	/* checking if push_back was successful */
	if(insert_res != SUCCESS){
        return FAIL;
	}
	return SUCCESS;

}


int grades_add_grade(struct grades *grades,  const char *name, int id,
                     int grade) {
	/* Checks if function parameters are valid */
	if(grades == NULL || grade > MAX_GRADE || grade < MIN_GRADE) {
		return FAIL;
	}

	struct iterator *student_it = find_student(grades->student_list, id);
	if(student_it == NULL){
        /* student with id was not found in list */
		return FAIL;
	}
	struct iterator *course_it = find_course(((student_t*)
                                  list_get(student_it))->student_courses, name);
	if(course_it != NULL){
        /* course with name is in list */
		return FAIL;
	}
	course_t *course_temp = (course_t*)malloc(sizeof(course_t));
	if(course_temp == NULL) {
		return FAIL;
	}
	int name_length = strlen(name)+1;
	course_temp->course_name = malloc(sizeof(char)*name_length);
	if((course_temp->course_name) == NULL) {
	    free(course_temp);
		return FAIL;
	}
	strcpy(course_temp->course_name, name);
	course_temp->grade = grade;
	 /* pushing student elem to grades->student_list */
	struct student *elem_student =(student_t*)list_get(student_it);
	int insert_res = list_push_back(elem_student->student_courses,
									     (void*)course_temp);
	course_destroy((void*)course_temp);

	/* checking if push_back was successful */
	if(insert_res != SUCCESS){
        return FAIL;
	}
	return SUCCESS;

}



float grades_calc_avg(struct grades *grades, int id, char **out){
	if(grades == NULL) {
		*out = NULL;
		return AVG_FAIL;
	}
	/* Searching student by id */
	struct iterator *student_it = find_student(grades->student_list, id);
	if(student_it == NULL){
        /* Student was not found in list */
		*out = NULL;
		return AVG_FAIL;
	}
	student_t *elem_student = (student_t*)list_get(student_it);


	*out=(char*)malloc(sizeof(char)*(strlen(elem_student->student_name)+1));
	if(*out == NULL) {
		return AVG_FAIL;
	}
	strcpy(*out, elem_student->student_name);
	float sum=0, avg=0;
	float num_of_courses= (float)list_size(elem_student->student_courses);
	if(num_of_courses == 0) {
        /* no courses in list*/
		return avg;
	}

	struct iterator *course_iterator = list_begin(elem_student->
                                                        student_courses);
	while( course_iterator != NULL ){

		sum += ((course_t*)(list_get(course_iterator)))->grade;
		course_iterator = list_next(course_iterator);
	}

	avg=(sum / num_of_courses);
	return avg;

}

int grades_print_student(struct grades *grades, int id){
	if(grades == NULL) {
		return FAIL;
	}
	struct iterator *student_iterator = find_student(grades->student_list, id);
	if(student_iterator == NULL){
		 return FAIL;
	}
	/* Print name and id of student */
	student_t *student_temp  = (student_t*)(list_get(student_iterator));
	printf("%s %d:",student_temp->student_name, student_temp->student_id);

	/* Printing student courses from courses list */
	struct iterator *course_iterator=list_begin(student_temp->student_courses);
	if(course_iterator == NULL) {
        /* courses list is empty */
		printf("\n");
		return SUCCESS;
	}
	course_t *course_temp = (course_t*)list_get(course_iterator);
	printf(" %s %d" , course_temp->course_name, course_temp->grade);
	course_iterator = list_next(course_iterator);

	// Continue print of student's courses (used for print settings):
	while( course_iterator != NULL ) {

		course_temp = (course_t*)(list_get(course_iterator));
		printf(", %s %d" , course_temp->course_name, course_temp->grade);
		course_iterator = list_next(course_iterator);
	}
	printf("\n");
	return SUCCESS;
}

int grades_print_all(struct grades *grades){
	if(grades == NULL) {
		return FAIL;
	}
	struct iterator *it = list_begin(grades->student_list);
	/* Going through student list*/
	for (; it != NULL; it = list_next(it)) {
		student_t *elem_student = (student_t*)(list_get(it));
		grades_print_student(grades, elem_student->student_id);
	}
	return SUCCESS;
}


int main(){

	return 0;
}
