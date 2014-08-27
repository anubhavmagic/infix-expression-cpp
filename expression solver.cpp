#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#define LENGTH 1001

// using namespace std;
long val[501];
char op[501];
long op_ptr = -1, val_ptr = -1;

void push_val(long a)
{
	val_ptr++;
	val[val_ptr] = a;
}
void push_op(char a)
{
	op_ptr++;
	op[op_ptr] = a;
}

long pop_val()
{
	val_ptr--;
	return val[val_ptr+1];
}
char pop_op()
{
	op_ptr--;
	return op[op_ptr+1];
}


long isEmpty_val()
{
	if (val_ptr == -1)
	{
		return 1;
	}
	return 0;
}
long isEmpty_op()
{
	if (op_ptr == -1)
	{
		return 1;
	}
	return 0;
}
long eval(char*);
void runOp();
long calculate(long,long,char);
bool Order(char,char);
long OpOrder(char);
long brac;
int main(){
	char exp[LENGTH];
	long result,i=0,len;
	// No prompt for input because the input is rigidly defined by checking software.
	scanf("%s",exp);

	if(exp[0]=='+'||exp[0]=='-'||exp[0]=='*'||exp[0]=='/'||exp[0]=='%')
	{
		printf("Input Error\n");
		exit(1);
	}

	len=strlen(exp);
	while(i<len)
	{
		if(exp[i]=='(')
			{brac++;}
		else if(exp[i]==')')
			{brac--;}
		i++;
	}

if(brac>0)
{
	printf("Input Error\n");
	exit(1);
}

	result = eval(exp);
	// Gives output result for expression.

	printf("%d\n",result);
	return 0;
}

long eval(char *exp)
{
	long length,num,tmp,i,j;
	if(!exp)
		return -1;
	//stack<char> op;
	//stack<long> val;
	length = strlen(exp);
	i=0;
	while(i<length)
	{
		char character=exp[i];
		if(character=='(')
		{
			if((exp[i+1]==')'||exp[i+1]=='\0') || !((exp[i+1]>='0' && exp[i+1]<='9') || exp[i+1]=='('))
			{
				printf("Input Error\n");
				exit(1);
			}
			push_op(character);
			brac++;
		}
		else if(character<='9' && character>='0' )
		{
			num=0;
			j=i;
			while(exp[j]<='9' && exp[j]>='0')
			{
				num *= 10;
				num += exp[j]-'0';
				tmp=j;
				i=tmp;
				j++;
			}
			if(exp[i+1]=='(')
				{push_op('*');}
			push_val(num);
		}
		else if(character == ')')
		{

			if(brac>0)
			{
				brac--;
			}
			else
			{
			printf("Input Error\n");
			exit(1);
			}
			while(!isEmpty_op() && op[op_ptr] != '(')
			{
				if(isEmpty_val() && !isEmpty_op())
					{printf("Input Error\n");exit(1);}
				runOp();
			}
			pop_op();
			if(exp[i+1]<='9' && exp[i+1]>='0' )
			{
				push_op('*');
			}
		}
		else if(character == '+' || character == '-' || character == '*' || character == '/' || character == '%')
		{
			if(exp[i+1]=='\0'||exp[i+1]=='+'||exp[i+1]=='-'||exp[i+1]=='*'||exp[i+1]=='/'||exp[i+1]=='%')
			{printf("Input Error\n");exit(1);}
			while(!isEmpty_op() && Order(op[op_ptr],character))
			{
				runOp();
			}
			push_op(character);
		}
		else
		{
			printf("Input Error\n");
			exit(1);
		}
		i++;
	}
	while(!isEmpty_op())
	{
		runOp();
	}
	return val[val_ptr];
}

void runOp()
{
	long num1,num2,intermediate;
	char oper;
	num1=pop_val();
	num2=pop_val();
	oper = pop_op();
	intermediate = calculate(num2,num1,oper);
	push_val(intermediate);
	return;
}

long calculate(long num1,long num2,char op){
	if(op == '/')
	{
		if(num2==0)
		{
			printf("Input Error\n");
			exit(1);
		}
		return num1/num2;
	}
	else if(op == '*')
	{
		return num1*num2;
	}
	else if(op == '+')
	{
		return num1+num2;
	}
	else if(op == '-')
	{
		return num1-num2;
	}
	else if(op == '%')
	{
		if(num2==0)
		{
			printf("Input Error\n");
			exit(1);
		}
		return num1 % num2;
	}
	else
	{return 0;}
}

bool Order(char char1,char char2)
{
	long result;
	result = OpOrder(char2)<=OpOrder(char1);
	return result;
}

long OpOrder(char character)
{
	if(character == '(' || character == ')')
	{
		return 0;
	}
	else if(character == '+' || character == '-')
	{
		return 1;
	}
	else if(character == '*')
	{
		return 2;
	}
	else if(character == '/' || character == '%')
	{
		return 3;
	}
	else
	{return 0;}
}



