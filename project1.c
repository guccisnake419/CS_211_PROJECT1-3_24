/*
          Victor Savage
          CS 211
          Project 1: 24
          Instructor: Ellen Kidane 
*/
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct NODE{
  char value;
  struct NODE* pnext;
};
void populateStack(char char1, struct NODE* head){
  struct NODE*pTemp = malloc(sizeof(struct NODE));
  pTemp->value= char1;
  pTemp->pnext=NULL;
  if(head==NULL){
    head=pTemp;
  }
  else{
    pTemp->pnext=head;
    head = pTemp;

  }
}

void compute(int numbers[], char char1[], bool mode, bool debug, bool easy,
             int **ptr, int arr[][4]) {//this function takes an integer and array, and an operation array, to see if it equals 23
             //(mode) is true only when we want to print out each operation step
   double total = 0;
  int i;
  for (i = 0; i < 3; i++) {//goes through the array of operations in orer
    if (char1[i] == 43) {//checks if operation is addition
      // add
      if (i == 0) {//checks if its the first operation 
        total = numbers[0] + numbers[1];
        if (mode)//this line checks if the calculation is for the regular game mode or debug mode, and if for the regular print each operations
          printf("%d + %d = %d.\n", numbers[0], numbers[1], (int)total);
      }
      if (i == 1) {//checks if its the second operation
        int total1 = total;
        total = total + numbers[2];
        if (mode)
          printf("%d + %d = %d.\n", total1, numbers[2], (int)total);
      }
      if (i == 2) {//check if its the third operation
        int total1 = total;
        total = total + numbers[3];
        if (mode)
          printf("%d + %d = %d.\n", total1, numbers[3], (int)total);
      }
    }
    if (char1[i] == 45) {//checks if operation is subtraction
      // subtract
      if (i == 0) {

        total = numbers[0] - numbers[1];
        if (mode)
          printf("%d - %d = %d.\n", numbers[0], numbers[1], (int)total);
      }
      if (i == 1) {
        int total1 = total;
        total = total - numbers[2];
        if (mode)
          printf("%d - %d = %d.\n", total1, numbers[2], (int)total);
      }
      if (i == 2) {
        int total1 = total;
        total = total - numbers[3];
        if (mode)
          printf("%d - %d = %d.\n", total1, numbers[3], (int)total);
      }
    }
    if (char1[i] == 42) {//checks if operation is multiplication
      // multiply;
      if (i == 0) {
        total = numbers[0] * (numbers[1] + 0.0);
        if (mode)
          printf("%d * %d = %d.\n", numbers[0], numbers[1], (int)total);
      }
      if (i == 1) {
        int total1 = total;
        total = total * (numbers[2] + 0.0);
        if (mode){
          total = total1 * (numbers[2] + 0.0);
          printf("%d * %d = %d.\n", total1, numbers[2], (int)total);
        }
        
      }
      if (i == 2) { 
        int total1 = total;
        total = total * (numbers[3] + 0.0);
        if (mode){
        total = total1 * (numbers[3] + 0.0);
          printf("%d * %d = %d.\n", total1, numbers[3], (int)total);
        }
      }
    }
    if (char1[i] == 47) {//checks if operation is division
      // divide
      if (i == 0) {
        total = numbers[0] / (numbers[1] + 0.0);
        if (mode){
          total=(int)total;
          printf("%d / %d = %d.\n", numbers[0], numbers[1], (int)total);
        }
      }
      if (i == 1) {
        int total1 = total;
        total = total / (numbers[2] + 0.0);
        if (mode)
          printf("%d / %d = %d.\n", total1, numbers[2], (int)total);
      }
      if (i == 2) {
        int total1 = total;
        total = total / (numbers[3] + 0.0);
        if (mode)
          printf("%d / %d = %d.\n", total1, numbers[3], (int)total);
      }
    }
  }
  if (mode) {//checks if its the regular game mode 
    if (((total - 24) > -0.01 && (total - 24) < 0.01)) {//check if the solution is in the range of +-0.01 about 24
      printf("Well done! You are a math genius.\n");
    } else {
      printf("Sorry. Your solution did not evaluate to 24.\n");
    }
  } else {//if its not in the regular game mode, we have two options, do we want to use the values or not 

    if (((total - 24) > -0.01 && (total - 24) < 0.01)) {
      if (debug) {//if debug mode is active, print of the combination of numbers and operations in 1+2+3 format
        printf("%d. %d%c%d%c%d%c%d\n", **ptr, numbers[0], char1[0], numbers[1],
               char1[1], numbers[2], char1[2], numbers[3]);
      }
      if (!easy) {//if easy mode is not active, we want to use the values, this condition checks and puts the solutions in our array
        arr[(**ptr) - 1][0] = numbers[0];
        arr[(**ptr) - 1][1] = numbers[1];
        arr[(**ptr) - 1][2] = numbers[2];
        arr[(**ptr) - 1][3] = numbers[3];
      }
      **ptr = **ptr + 1;
    }
  }
}

void sum24(int target, bool debugmode, bool easymode, int arr[][4]) {
  // this function finds two numbers equal to a sum
  int arrnum[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  char operation[4] = {'+', '-', '*', '/'};
  char operations[64][3];
  int outcount = 0;
  int *ptr = malloc(sizeof(int));//pointer for counter to debug mode
  *ptr = 1;

  for (int i = 0; i < 4; i++) {//this statements find all possible combination of operations and puts it in an array
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        operations[outcount][0] = operation[i];
        operations[outcount][1] = operation[j];
        operations[outcount][2] = operation[k];
        outcount++;
      }
    }
  }
  
  for (int i = 0; i < 9; i++) {//this statements find all possible 4 combinations of numbers 1-9
    for (int j = 0; j < 9; j++) {

      for (int k = 0; k < 9; k++) {

        for (int m = 0; m < 9; m++) {
          int num[4] = {arrnum[i], arrnum[j], arrnum[k], arrnum[m]};
          for (int n = 0; n < 64; n++) {
            compute(num, operations[n], false, debugmode, easymode, &ptr, arr);
          }
        }
      }
    }
  }
}

void displaygame(int easyarr[][4], int size) {//this function is where our game play occurs
  char input;
  int num;
  do {//a do-while loop that stops only when input is N
    printf("\nThe numbers to use are: ");
    num = rand() % size;//generates positions from 0 to arraysize-1
    
    
    printf("%d, %d, %d, %d.\n", easyarr[num][0], easyarr[num][1],
           easyarr[num][2], easyarr[num][3]);

    char char1[3] = {0, 0, 0};
    char str[32];
    int i;
    int *ptr;
    bool goodinput = true;
    bool oppcorrect = true;
    fflush(stdin);
    printf("Enter the three operators to be used, in order (+,-,*, or /): ");
    scanf("%s", str);
    if ((int)strlen(str) != 3) {//if more or less than 3 operators are entered
      printf("Error! The number of operators is incorrect. Please try again. \n");
      continue;
      oppcorrect = false;
    }
    if (oppcorrect) {//if we have 3 operators, check if the operators are correct
      for (int i = 0; i < 3; i++) {
        if (str[i] != 43 && str[i] != 45 && str[i] != 42 && str[i] != 47) {
          printf("Error! Invalid operator entered. Please try again.\n");
          goodinput = false;
          break;
          
          
        }
        char1[i] = str[i];
      }
      if (goodinput) {//check if earlier conditon passes and calculates if they equal 24
        

        compute(easyarr[num], char1, true, 0, 0, &ptr, easyarr);
      }
      else{
        continue;
      }
      
    }
    fflush(stdin);//clears the buffer before a new input

    printf("\nWould you like to play again? Enter N for no and any other "
           "character for yes. ");
    scanf(" %c", &input);

    fflush(stdin);

  } while (input != 'N');
  printf("\nThanks for playing!");
}

int main(int argc, char *argv[]) {
  srand(1);
  printf("Welcome to the game of TwentyFour.\n");
  printf("Use each of the four numbers shown below exactly once, \ncombining "
         "them somehow with the basic mathematical operators (+,-,*,/) \nto "
         "yield the value twenty-four.\n");

  int easyarr[10][4] = {{3, 9, 4, 1}, {8, 5, 8, 1}, {6, 1, 5, 1}, {2, 8, 7, 8},
                        {5, 2, 9, 2}, {2, 6, 8, 4}, {5, 5, 4, 3}, {6, 6, 2, 6},
                        {8, 4, 2, 6}, {6, 2, 8, 1}};

  int allans[3188][4];
  if (argc == 5) {//if we have 5 command line arguements
    if (argv[2][0] == '1' && argv[4][0] == '1') {//if debug mode and easy mode are both active
      int arr[1][4];
      printf("\n");
      sum24(24, 1, 1, arr);
      
      displaygame(easyarr, 10);
    }
    if (argv[2][0] == '0' && argv[4][0] == '0') {//if debug mode and easy more are not active

      sum24(24, 0, 0, allans);
      displaygame(allans, 3188);
    }
    if (argv[2][0] == '1' && argv[4][0] == '0') {//if debug mode is active and easy mode is not active
      sum24(24, 1, 0, allans);
      displaygame(allans, 3188);
    }
    
    // if(argv[2]==)
  } else {//any other length of command line arguments

    displaygame(easyarr, 10);
  }

  return 0;
}
