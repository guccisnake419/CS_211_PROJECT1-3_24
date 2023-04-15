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
void reverse(struct NODE**head)
    {
        // Initialize current, previous and next pointers
        struct NODE* current = *head;
        struct NODE *prev = NULL;
        struct NODE  *next = NULL;
 
        while (current != NULL) {
            // Store next
            next = current->pnext;
            // Reverse current node's pointer
            current->pnext = prev;
            // Move pointers one position ahead.
            prev = current;
            current = next;
        }
        *head = prev;
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
        
        if(w == '('){
          push(value1 +48, &(*stack));
          c++;
          continue;
        }
        if(w!=43 && w!=45 && w!=47 && w!=42 ){
             printf("There are too many values in the expression\n");
             return -1;
        }
        while(w != 40 && w != 91 && w !=123){//while no opening brace is found yet
          
          if(w==43 || w==45 || w==47 || w==42){
            operand= w;
          }
          
          else{
            value2=(int)w-48;
            
           if(operand !=' '){
              printf("%d %c %d = ", value2, operand, value1);
              value1= solve(&value1, &operand, &value2);
              printf("%d.\n",value1);
            }
            else{
              printf("There are too many values in the expression\n");
            }
          }
  
          w=pop(&(*stack));
          if(*stack ==NULL){
            printf("Error! Too many closing parentheses in the expression.");
            return -1;
          }
        }
        if(*c != '(' && (*stack !=NULL)&&((*stack)->value=='*' || (*stack)->value=='/')){
            char operand=pop(&(*stack));
            int value2=(int)pop(&(*stack));
            value2=value2-48;
            printf("%d %c %d = ", value1, operand, value2);
            value1= solve(&value1, &operand, &value2);
            printf("%d.\n",value1);
            push(value1 +48, &(*stack));
          
          }
          else{
            push(value1 +48, &(*stack));
          }
        
      }
      else{
        
          
        if(*c != ' ' && *c !='\n'){
          if(*c != '(' && (*stack !=NULL)&&((*stack)->value=='*' || (*stack)->value=='/')){
            int value1=(int)*c-48;
            char operand=pop(&(*stack));
            int value2=(int)pop(&(*stack));
            value2=value2-48;
            printf("%d %c %d = ", value2, operand, value1);
            value1= solve(&value1, &operand, &value2);
            printf("%d.\n",value1);
            push(value1 +48, &(*stack));
          
          }
          else{
            push(*c, &(*stack));
          }
          
        }
        
        
      }
      c++;
      
    }
    //after everything has been put in
    reverse(&(*stack));
    while(*stack !=NULL){
        int value1=(int)pop(&(*stack))-48;
        int value2;
        char operand=' ';
        if(*stack ==NULL){
          return value1;
        }
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
              value1= solve(&value2, &operand, &value1);
              printf("%d.\n",value1);
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
int checkinput(char solution[], int ourarr[]){
  char * c= solution;
  int checker[]= {0, 0, 0, 0};
  while(*c != '\0'){
    if(*c>=48 && *c<=57){
      int w = *c -'0';
      for(int i=0;i<4;i++){
        if(w==ourarr[i] && checker[i]==0){
          checker[i]=1;
          break;
        }
      }
    }
    else if(*c!=' ' && *c != '(' && *c != ')' && *c!='+'&& *c!='-'&& *c!='/'&& *c!='*' && *c !='\n'){
      printf("Error! Invalid symbol entered. Please try again.\n\n");
      return -1;
    }
    c++;
  }
  for(int i=0; i<4;i++){
    if(checker[i]==0){
      printf("Error! You must use all four numbers, and use each one only once. Please try again.");
      return -1;
    }
  }

return 1;

}
int displaygame(int easyarr[][4], int size) {//this function is where our game play occurs
  
  fflush(stdin);
  char input;
  int num;
  do {//a do-while loop that stops only when input is N
    printf("The numbers to use are: ");
    num = rand() % size;//generates positions from 0 to arraysize-1
   
    
    printf("%d, %d, %d, %d.\n", easyarr[num][0], easyarr[num][1],
           easyarr[num][2], easyarr[num][3]);
    int ourarr[]={ easyarr[num][0], easyarr[num][1],
           easyarr[num][2], easyarr[num][3] };
    fflush(stdin);
    printf("Enter your solution: ");
    char solution[81];
    
    fflush(stdin);
    fgets(solution, 80, stdin);
    if(checkinput(solution, ourarr)==-1){
      continue;
    }
    // printf("solution: %s", solution);
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
    printf("\n");
    printf("Enter: \t1 to play again,\n");
    printf("\t2 to change the difficulty level and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");

  
    scanf(" %c", &input);
    char garbage[81];
    fflush(stdin);
    fgets(garbage, 80, stdin);
    if(input =='1'){
      continue;
    }
    else if(input=='2'){
      return 2;
    }
    else if(input =='3'){
      return 1;
    }
    input ='N';
  } while (input != 'N');
  
  return 1;
}
int  fileread(char filename[], int ourarr[][4]){
  FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading
	
	// Check that the file was able to be opened
	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}
	//Read each word from file, and print them one by one
	char inputString[ 81];
	int i=0;
	while(fgets(inputString, 10, filePtr)) {
    char * line= inputString;
    int j=0;
    
		while(*line != '\0'){

      if(*line >=48 && *line <=57){
        ourarr[i][j]= *line -'0';
        // printf("%d %d\n", i, j);
        j++;
      }
      
      line++;
    }
		
		

		// printf("%s\n", inputString);
   i++;
	}
  
	// Close the file
	fclose(filePtr);
  return i;
}
int main(int argc, char *argv[]) {
  srand(1);
   printf("Welcome to the game of TwentyFour Part Two!\n");
    printf("Use each of the four numbers shown exactly once, \ncombining "
          "them somehow with the basic mathematical operators (+,-,*,/) \nto "
          "yield the value twenty-four.\n");

    int ourarr[100][4];
  int n=0;
  do{
   
    char input;
    printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
    printf("Your choice --> ");
   
    scanf(" %c", &input);
  
    char solution[81];
    fgets(solution, 80, stdin);
   
    if(input == 'E'){
      char filename[] = "easy.txt";
      int size= fileread(filename, ourarr);
  
      n=displaygame(ourarr,size);
     
    }
    else if(input =='M'){
      char filename[] = "medium.txt";
      int size= fileread(filename, ourarr);
      n=displaygame(ourarr,size);

    }
    else if(input =='H'){
      char filename[] = "hard.txt";
      int size= fileread(filename, ourarr);
      n=displaygame(ourarr,size);
    }
    else{
      char filename[] = "easy.txt";
      int size= fileread(filename, ourarr);
  
      n=displaygame(ourarr,size);
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
