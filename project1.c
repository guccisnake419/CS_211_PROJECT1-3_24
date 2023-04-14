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
void push(char char1, struct NODE**head){
  struct NODE* pTemp= (struct NODE*)malloc (sizeof(struct NODE));
  pTemp->value= char1;
  pTemp->pnext=NULL;
  if(*head==NULL){
    *head=pTemp;
  }
  else{
    pTemp->pnext=*head;
    *head = pTemp;

  }
}

char pop(struct NODE**head){
  if(*head !=NULL){
    struct NODE * ptemp = *head;
    char tempchar = ptemp->value;
    *head = (*head)->pnext;
    free(ptemp);
    return tempchar;
  }
  return NULL;
  
}

int solve(const int *val1, const char *operand, const int *val2 ){
  int result;
  switch(*operand){
    case '+':
      result = *val1 + *val2;
      break;
    case '-':
      result = *val2 - *val1;
      break;
    case '/':
      result = *val2 / *val1;
      break;
    case '*':
      result = *val1 * *val2;
      break;

  }

  return result;
}
int processstr(char *c, struct NODE**stack){
  int result=NULL;
  while(*c != '\0'){
      if(*c ==')' || *c =='}' || *c ==']'){
        int value1=(int)pop(&(*stack))-48;
        int value2;
        char operand=' ';
        char w=pop(&(*stack));
        if(w!=43 && w!=45 && w!=47 && w!=42 ){
             printf("There are too many values in the expression\n");
             return -1;
          }
        //  }
        while(w != 40 && w != 91 && w !=123){//while no opening brace is found yet
          
          if(w==43 || w==45 || w==47 || w==42){
            operand= w;
          }
          
          else{
            value2=(int)w-48;
            
           if(operand !=' '){
              printf("%d %c %d = ", value1, operand, value2);
              value1= solve(&value1, &operand, &value2);
              printf("%d\n",value1);
            }
            else{
              printf("There are too many values in the expression\n");
            }
          }
  
          w=pop(&(*stack));
        }
       
        push(value1 +48, &(*stack));
      }
      else{
        
          if((*stack !=NULL)&&((*stack)->value=='*' || (*stack)->value=='/')){
            int value1=(int)*c-48;
            char operand=pop(&(*stack));
            int value2=(int)pop(&(*stack));
            value2=value2-48;
            printf("%d %c %d = ", value1, operand, value2);
            value1= solve(&value1, &operand, &value2);
            printf("%d\n",value1);
            push(value1 +48, &(*stack));
          
          }
        else if(*c != ' ' && *c !='\n'){
          push(*c, &(*stack));
        }
        
        
      }
      c++;
      
    }
    //after everything has been put in
    while(*stack !=NULL){
        int value1=(int)pop(&(*stack))-48;
        int value2;
        char operand=' ';
        char w=pop(&(*stack));
        if(w!=43 && w!=45 && w!=47 && w!=42 ){
             printf("There are too many values in the expression\n");
             return -1;
          }
        while(w != NULL){
          if(w==43 || w==45 || w==47 || w==42 ){
            operand= w;
          }
          else {
            value2=(int)w-48;
            
            if(operand !=' '){
              printf("%d %c %d = ", value1, operand, value2);
              value1= solve(&value1, &operand, &value2);
              printf("%d\n",value1);
            }
            else{
              printf("There are too many values in the expression\n");
            }
            
          }
        
        w=pop(&(*stack));
        result = value1;
    }   
     
  }
  return result; 
}
int displaygame(int easyarr[][4], int size) {//this function is where our game play occurs
  char input;
  int num;
  do {//a do-while loop that stops only when input is N
    printf("The numbers to use are: ");
    num = rand() % size;//generates positions from 0 to arraysize-1
    
    
    printf("%d, %d, %d, %d.\n", easyarr[num][0], easyarr[num][1],
           easyarr[num][2], easyarr[num][3]);
    printf("Enter your solution: ");
    char solution[81];
    fflush(stdin);
    fgets(solution, 80, stdin);
    // scanf("%s", solution);
    
    char *c = solution;
    struct NODE *stack=NULL;
    int sol=processstr(c, &stack);
    if(sol==24){
      printf("Well done! You are a math genius.\n");
    }
    else{
      printf("Sorry. Your solution did not evaluate to 24.\n");
    }
    
    printf("Enter: \t1 to play again,\n");
    printf("\t2 to change the difficulty level and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");

  
    scanf("%c", &input);
    if(input =='1'){
      continue;
    }
    else if(input=='2'){
      return 2;
    }
    else if(input =='3'){
      return 1;
    }
  } while (input != 'N');
  
  return 1;
}
void fileread(){
  
}
int main(int argc, char *argv[]) {
  srand(1);
   printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once, \ncombining "
          "them somehow with the basic mathematical operators (+,-,*,/) \nto "
          "yield the value twenty-four.\n");

    int easyarr[12][4] = {{2, 6, 1, 9}, {2, 4, 8, 8}, {1, 1, 4, 8}, {1, 1, 5, 6},
                          {3, 6, 6, 9}, {3, 4, 5, 5}, {1, 5, 5, 9}, {4, 4, 8, 8},
                          {1, 1, 4, 7}, {5, 5, 7, 7},{1,3,3,4},{4,6,6,8}};

    int mediumarr[24][4]={{2,4,6,7},{2,5,6,8},{4,5,8,9},{1,3,4,7},{5,6,6,8},{1,1,6,9},{1,6,7,9},{2,2,7,8},
                          {3,8,8,9},{2,3,4,7},{1,3,3,7},{4,7,8,8},{1,4,5,7},{1,2,4,9},{5,6,7,8},{1,3,6,6},
                          {3,3,4,5},{2,4,4,5},{2,3,4,5},{2,2,6,7},{7,8,8,9},{2,2,4,7},{2,6,7,8},{4,5,6,8}};

    int hardarr[11][4] ={{4,4,7,8}, {2,2,6,9},{2,4,7,9},{2,2,5,8},{2,2,3,5},{1,3,8,8},
                          {2,3,5,7},{2,5,5,8},{3,3,6,8},{2,6,8,9},{3,3,5,7}};
  int n=0;
  do{
   
    char input;
    printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
    printf("Your choice --> ");
    scanf(" %c", &input);
    if(input == 'E'){
      n=displaygame(easyarr,12);
    }
    else if(input =='M'){
      n=displaygame(mediumarr, 24);

    }
    else if(input =='H'){
      n=displaygame(hardarr, 11);
    }
    if(n==2){
      continue;
    }
    if(n==1){
      n=0;
    }


  }while(n!=0);
  
  printf("\nThanks for playing!\n");
	printf("Exiting...\n");
  return 0;
}
