#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_SIZE 100
typedef struct
{ 
int top;
char items[MAX_SIZE]; 
} Stack;
void push(Stack *s, char c);
char pop(Stack *s);
int precedence(char c);
void infixToPostfix(char *expression, char *postfix);
void generateThreeAddressCode(char *postfix);
int main()
{ 
char expression[MAX_SIZE];
char postfix[MAX_SIZE];
char name[20];
char rollno[20];
printf("Enter an arithmetic expression: "); 
fgets(expression, sizeof(expression), stdin);
printf("\nenter name of the student:");
scanf("%s",name);
printf("\nenter rollno of the student:");
scanf("%s",rollno);
printf("\nthe name of the student  is :%s",name);
printf("\n\nthe rollno of the student is :%s",rollno);
expression[strcspn(expression, "\n")] = '\0';
infixToPostfix(expression, postfix);
generateThreeAddressCode(postfix); 
return 0; 
}
void push(Stack *s, char c)
{
 if (s->top == MAX_SIZE - 1)
 { 
   printf("Stack Overflow\n"); 
   exit(1);
 } 
s->items[++(s->top)] = c;
} 
char pop(Stack *s)
{
 if (s->top == -1)
 { 
   printf("Stack Underflow\n");
   exit(1);
 } 
return s->items[(s->top)--];
}
int precedence(char c)
{
 if (c == '+' || c == '-')
 { 
  return 1;
 } 
else 
if (c == '*' || c == '/')
 {
  return 2;
 } 
else
{
return 0;
}
}
void infixToPostfix(char *expression, char *postfix)
{
 Stack stack;
 stack.top = -1;
 int i = 0, j = 0;
 while (expression[i] != '\0')
 {
 char c = expression[i];
 if (isalpha(c))
 { 
  postfix[j++] = c;
 }
 else if (c == '(')
 {
 push(&stack, c);
 }
else if (c == ')')
{
while(stack.items[stack.top]!='(')
{
postfix[j++]=pop(&stack);
}
pop(&stack);
}
else
{
 while (stack.top != -1 && precedence(stack.items[stack.top]) >= precedence(c))
 {
 postfix[j++] = pop(&stack);
 }
 push(&stack,c);
 }
i++;
}
while(stack.top!=-1)
{
postfix[j++]=pop(&stack);
}
postfix[j]='\0';
}
 void generateThreeAddressCode(char *postfix)
 {
 Stack stack;
 stack.top = -1;
 int temp_count = 1;
 int i = 0;
 printf("Three Address Code:\n");
 while (postfix[i] != '\0')
 { 
  char c = postfix[i];
  if (isalpha(c))
  { 
   push(&stack, c);
  }
  else
  { 
   char operand2 = pop(&stack);
   char operand1 = pop(&stack);
   char temp_var[10];
   sprintf(temp_var,"temp%d",temp_count++);
   if(isdigit(operand2) && isdigit(operand1))
   {
        printf("%s = temp%c %c temp%c\n", temp_var, operand1, c, operand2);
        push(&stack, temp_var[4]);
   }
   else if(isdigit(operand1))
   {
       printf("%s = temp%c %c %c\n", temp_var, operand1, c, operand2);
        push(&stack, temp_var[4]);
   }
   else if(isdigit(operand2))
   {
       printf("%s = %c %c temp%c\n", temp_var, operand1, c, operand2);
        push(&stack, temp_var[4]);
   }
   else
   {
       printf("%s = %c %c %c\n", temp_var, operand1, c, operand2);
       push(&stack, temp_var[4]);
   }
  }
 i++;
 }
 }
