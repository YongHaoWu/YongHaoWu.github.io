---
layout: post
title: 表达式计算器
---
  恰好数据结构老师讲到栈了，找回以前高三写的表达式计算器来看了看，复习一遍， 容我自大，觉得高三写出这个水平的代码是挺好的了（除了代码风格不是很好），而且当时是用笔写在纸上，大脑做编译器！！！竟然在一个月一次放假一天回家时编译没有多少错误。这种就像你一次性写出完全没语法错误和bug的代码，无错编译的感觉太爽了2333333333333现在的C++水平也好不了多少吧，都在用c了。

  代码中所用的stack.h也是自己用C++ template写的，以前把数据结构和算法都亲自按自己的想法用template实现了一遍。

    #include "function.h"

    bool IsNumber( char a )
    {
    	if( a=='.' || (a>='0' && a<='9') ) //a=='0' ||  a=='1' ||  a=='2' ||  a=='3' ||  a=='4' ||  a=='5' ||  a=='6' ||  a=='7' ||  a=='8' ||  a=='9'
    		return true;
    	else
    		return false;
    }

    bool IsOperator(char a)
    {
    	if ( a=='+' || a=='-' || a=='*' || a=='/')
    		return true;
    	else
    		return false;
    }

    bool OperatersAnalyse( MyStack<string> &postfix_expression, MyStack<char> &operaters , char Oper )
    {
    	char temp;
    	//static bool flag=1;
    	if( Oper==')' )
    	{
    	//	flag = 1;
    		temp =  operaters.pop();
    		while( temp != '(' )
    		{
    			char *p = &temp;
    			string a(p);
    			postfix_expression.pushme( a );
    			temp =  operaters.pop();
    		}
    	}
    	else if( Oper=='*' || Oper=='/' )
    	{
    		if( operaters.Top()!=0 && (operaters[ operaters.Top()-1 ] == '*' || operaters[ operaters.Top()-1 ] == '/') )//Stack[0]保留  && flag 
    		{
    			while( operaters.Top()!=0 && operaters[ operaters.Top()-1 ]!='(' )
    			{
    				temp = operaters.pop();
    				char *p = &temp;
    				string a(p);
    				postfix_expression.pushme( a );
    		 	if (operaters.Top()>=1)
    					if (operaters[operaters.Top()-1] =='+' || operaters[operaters.Top()-1] == '-')
    						break;
    			}
    		}
    		operaters.pushme(Oper);
    	}
    	else//+ -
    	{
    		while( operaters.Top()!=0 && Oper!='(' && operaters[ operaters.Top()-1 ]!='(')// && flag
    		{
    			temp = operaters.pop();
    			char *p = &temp;
    			string a(p);
    			postfix_expression.pushme( a );
    		}
    		operaters.pushme(Oper);
    	}
    	return true;
    }

    double Calculate( MyStack<string> postfix_expression )
    {
    	MyStack<double> numbers;
    	int length = postfix_expression.Top();
    	for(int i=0; i!=length; ++i)
    	{
    		if (IsOperator(postfix_expression[i][0])==false)//is number
    		{
    			double number =  atof(postfix_expression[i].c_str());
    			numbers.pushme(number);
    		}
    		else
    		{
    			double b = numbers.pop();
    			double a = numbers.pop();
    			double c = simple_caculate(a, postfix_expression[i][0], b);
    			numbers.pushme(c);
    		}
    	}
    	return numbers.pop();
    }

    double simple_caculate( double a, char oper, double b )
    {
    	double  result = 0;
    	switch( oper )
    	{
    	case '+':
    		result = a+b;
    		break;
    	case '-':
    		result = a-b;
    		break;
    	case '*':
    		result = a*b;
    		break;
    	case '/':
    		result = a/b;
    		break;
    	}
    	return result;
    }

file2:

    #include "MyStack.h"
    #include "function.h"
    int main()
    {
    	while(1)
    	{
    		string nifix_expression, numbers;
    		cin>>nifix_expression;
    		MyStack<string> postfix_expression;
    		MyStack<char> operaters;
    		double result;

    		for(unsigned int i=0; i<nifix_expression.length(); i++ )
    		{
    			if( IsNumber( nifix_expression[i] ) )
    				numbers += nifix_expression[i];
    			else
    			{
    				if( numbers !="" )
    					postfix_expression.pushme( numbers );//  et: 1033+12;
    				if( nifix_expression[i]=='/' && i+1<nifix_expression.length() &&nifix_expression[i+1]=='0' )   
    				{
    					cout<<"Error /0"<<endl;
    					system("pause");
    					return 0;
    				}
    				else if( i==0 )
    					operaters.pushme( nifix_expression[0] );//et: (11+3)+2
    				else
    					OperatersAnalyse( postfix_expression, operaters, nifix_expression[i] );
    				numbers = "";
    			}
    		}

    		if( numbers !="" )
    			postfix_expression.pushme( numbers ); 
    		while( operaters.Top() !=0 )
    		{
    			char temp = operaters.pop();
    			char *p = &temp;
    			string a(p);
    			postfix_expression.pushme( a );
    		}	
    		//while( postfix_expression.Top()!=0 )
    		//{
    		//	string temp = postfix_expression.pop();
    		//	temp = temp+"\0";
    		//	cout<<temp<<endl;
    		//}
    		result = Calculate( postfix_expression );
    		cout<<result<<endl;
    	}
    	system("pause");
    }
