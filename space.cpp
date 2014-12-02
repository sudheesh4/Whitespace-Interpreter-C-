#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
bool flag=true;
string s;int c=0;
vector<int> stack;
struct labl{ string l;int st;int ls;};
vector<labl> label;
//imp-space
int convno(string t)
{int no=0,k=0;
	for(int i=t.length()-1;i>0;i--)
		{
		if(t.at(i)=='s')k=0;
        else k=1;
        no+=(k*(pow(2,i-t.length()+1)));
        }
        if(t.at(0)=='-')
        	no=(no*-1);
        return no;
}
void pus(int &y)
{y++;
	string temp="";
	if(y>=s.length()-3)
		{cout<<"ERROR1";flag=false;}
	else 
	{
		if((s.at(y)=='l')||(s.at(y)==';'))
			{cout<<"ERROR2";flag=false;}
		else if((s.at(y+1)=='l'))
			{cout<<"ERROR3";flag=false;}
		else{
			  
			  if(s.at(y)=='t')
			  temp+="+";
			else temp+="-";
			for(y=y+1;(s.at(y)!='l')&&(s.at(y)!=';')&&y<s.length();y++)
		       {  
		       if(s.at(y)=='s')
		       	temp+="0";
		       else if (s.at(y)=='t')
		       	temp+="1";
		       }
		       if(s.at(y)=='l')
		       	{  if(y+1>s.length()-1)
		       	    	{cout<<"ERROR4";flag=false;}
		       	 else if(s.at(y+1)==';')
		       		{stack.push_back(convno(temp));cout<<"pushed!";c++;}
		       	    else if((s.at(y+1)=='s')||(s.at(y+1)=='t'))
		       	    	{cout<<"ERROR-unexpected token";flag=false;}
		       	}
		       else 
		       	{cout<<"ERROR-L expected!";flag=false;}
		   }
		
	}
}
void dupl(int &j)
{
	switch(s.at(++j))
	{    case ';':
		if(c>=1)
			{stack.push_back(stack.at(stack.size()-1));c++;cout<<"duplicated!";//j++;
	        }
		else
			{cout<<"ERROR-less members";flag=false;}break;
		case 't':
		case 's':
		case 'l':
		cout<<"ERROR-unexpected token";flag=false;
		break;
		case '\0':
		cout<<"ERROR-; expected";flag=false;break;
		default:break;
	}
}
void swap(int &j)
{
	
	switch(s.at(++j))
	{
		case ';' :
		if(c>=2)
			{
			stack.at(stack.size()-1)=stack.at(stack.size()-1)+stack.at(stack.size()-2);
			stack.at(stack.size()-2)=stack.at(stack.size()-1)-stack.at(stack.size()-2);
			stack.at(stack.size()-1)=stack.at(stack.size()-1)-stack.at(stack.size()-2);
			cout<<"swapped!";//j++;
	        }
		else
			{cout<<"ERROR-less members";flag=false;}break;
		case 't':
		case 's':
		case 'l':
		cout<<"ERROR-unexpected token";flag=false;
		break;
		case '\0':
		cout<<"ERROR-; expected";flag=false;break;
		default:break;
	}
}
void discard(int &j)
{
	switch(s.at(++j))
	{
		case ';' :
		if(c>=1)
			{cout<<"discarded!";c--;//j++;
	        } 
		else
			{cout<<"ERROR-less members";flag=false;}break;
		case 't':
		case 's':
		case 'l':
		cout<<"ERROR-unexpected token";flag=false;
		break;
		case '\0':
		cout<<"ERROR-; expected";flag=false;break;
		default:break;
	}
}
//to get note of all labels
void lbl()
{
	labl temp;
	string ts="";
	int i,j,k;
	for(i=0;i<s.length();i++)
	{ts="";
		if(s.at(i)=='l')
		{
			 if((s.at(i+1)=='s')&&(s.at(i+2)=='s'))
			 	{     temp.st=i+3;
			 	 for(i=i+3;s.at(i)!=';';i++)
			 	 {
			 	 	if(s.at(i)=='s')
			 	 		ts+="0";
			 	 	else if(s.at(i)=='t')
			 	 		ts+="1";
			 	 }
			 	 temp.l=ts;
			 	 temp.ls=i;
			 	 label.push_back(temp);
			 	}
		}
	}
}
//jump  un condi
void jump_unc(int &u)
{
	u++;
	labl tr;
	if(u>=s.length())
		{cout<<"ERROR";flag=false;}
	else
	{   bool fg=false;
		string ts="";
		int j;
		for(;s.at(u)!=';';u++)
			{if(s.at(u)=='s')
			 	 		ts+="0";
			 else if(s.at(u)=='t')
			 	 		ts+="1";
			}
		for( j=0;j<label.size();j++)
			{  tr=label.at(j);
				if(tr.l==ts){fg=true;;break;}}
		if(fg)u=tr.ls;
		else {cout<<"ERROR-LABEL NOT FOUND";flag=false;}
	}
}
//arith
void arith(int &y,char o)
{
	if(c<2)
		{cout<<"ERROR-Less members";flag=false;}
	else
	{int o1,o2;o1=stack.at(stack.size()-1);
		o2=stack.at(stack.size()-2);
		stack.erase(stack.begin()+stack.size()-1);
		switch(o)
		{
			case '+':
			stack.at(stack.size()-1)=(o1+o2);
			cout<<"added!";break;
			case '-':
			stack.at(stack.size()-1)=(o1-o2);
			cout<<"substracted!";break;
			case '*':
			stack.at(stack.size()-1)=(o1*o2);
			cout<<"multiplied!";break;
			case '/':
			stack.at(stack.size()-1)=(o1/o2);
			cout<<"divided!";break;
			case '%':
			stack.at(stack.size()-1)=(o1%o2);
			cout<<"moduloed!";break;
	}
	c--;
	}
}
void yo_tch(int &u,char p)
{int i;
	switch(p)
	{
		case 'i':
		cin>>i;
		stack.push_back(i);
		cout<<"input taken!";break;
		case 'o':
		if(true)
			{cout<<"output given!";;break;}
		else 
			{cout<<"ERROR-less members!";flag=false;break;}
	}
}
void yo_tn(int &u,char p)
{int i;
	switch(p)
	{
		case 'i':
		cin>>i;
		stack.push_back(i);
		cout<<"input taken!";break;
		case 'o':
		if(c>0)
			{cout<<stack.at(stack.size()-1);stack.erase(stack.begin()+stack.size()-1);cout<<"output given!";c--;break;}
		else 
			{cout<<"ERROR-less members!";flag=false;break;}
	}
}
int main(int argc, char const *argv[])
{
	
	cin>>s;
	int i=0;
	i=0;
	lbl();
	char op;
	for(;i<s.length()&&flag;i++)
	{
		if(s.at(i)=='s')
	     {  i++;
	     	if(i>=s.length())
	    		{cout<<"ERROR!";flag=false;}
		   else if(s.at(i)=='s')
		    {
			pus(i);
		    }
		    else if(s.at(i)=='l')
		    {
			if(i+1>=s.length())
				{cout<<"ERROR";flag=false;}
			else 
			{i++;
				if(s.at(i)=='s')
					dupl(i);
				else if( s.at(i)=='t')
					swap(i);
				else if(s.at(i)=='l')
					discard(i);
				else 
					{cout<<"ERROR-unkown code";flag=false;}
			}
		    }
	     }
	    else if(s.at(i)=='l')
	    {
          i++;
          if(i>=s.length())
	    	{cout<<"ERROR!";flag=false;}
          else if(s.at(i)=='s')
          {i++;
          	if(i>=s.length())
	    	{cout<<"ERROR!";flag=false;}
          	else if(s.at(i)=='s')
          		continue;
          	else if(s.at(i)=='l')
          		jump_unc(i);
          }
          else if(s.at(i)=='t')
          {
          	i++;
          	if(i>=s.length())
	    	{cout<<"ERROR!";flag=false;}
          	else if(s.at(i)=='s')
          		;if(stack.at(stack.size()-1)==0)jump_unc(i);//jump_tp(i);
          	else if(s.at(i)=='t')
          		;if(stack.at(stack.size()-1)<0)jump_unc(i);//jump_top(i);
          }
          else if(s.at(i)=='l')
          {
          	i++;
          	if(i>=s.length())
	    		{cout<<"ERROR!";flag=false;}
          	else if(s.at(i)=='l')
          		;cout<<"end";return 1;//end
          }
	    }
	    else if((s.at(i)=='t'))
	    {
	    	i++;
	    	if(i>=s.length())
	    		{cout<<"ERROR!";flag=false;}
	    	else if(s.at(i)=='s')
	    	{
	    		i++;
	    		if(i>=s.length())
	    			{cout<<"ERROR!";flag=false;}
	    		else if(s.at(i)=='s')
	    		{
	    			i++;
	    			if(i+1>=s.length())
	    				{cout<<"ERROR!";flag=false;}
	    			else if(s.at(i+1)==';')
	    			{
	    			 if(s.at(i)=='s')
	    				arith(i,'+');
	    			else if(s.at(i)=='t')
	    				arith(i,'-');
	    			else if(s.at(i)=='l')
	    				arith(i,'*');
	    		    }
	    		    else {cout<<"ERROR-unexpected token!";flag=false;}
	    		}
	    		else if(s.at(i)=='t')
	    		{
	    			i++;
	    			if(i+1>=s.length())
	    				{cout<<"ERROR!";flag=false;}
	    			else if(s.at(i+1)==';')
	    			{ if(s.at(i)=='s')
	    				arith(i,'/');
	    			else if(s.at(i)=='t')
	    				arith(i,'%');
	    		    }
	    			else {cout<<"ERROR-unexpected token!";flag=false;}
	    		}
	    	}
	    	if(s.at(i)=='l')
	    	{
	    		i++;
	    		if(i+1>=s.length())
	    				{cout<<"ERROR!";flag=false;}
	    		else if(s.at(i)=='s')
	    		{i++;
	    		if(i+1>=s.length())
	    				{cout<<"ERROR!";flag=false;}
	    			else if(s.at(i+1)==';')
	    		    {
	    			 if(s.at(i)=='s')
	    				yo_tch(i,'o');
	    			else if(s.at(i)=='t')
	    				yo_tn(i,'o');
	    			else 
	    				{cout<<"ERROR-unkown";flag=false;}
	    			}
	    			else {cout<<"ERROR-unexpected token!";flag=false;}
	    		}
	    		else if(s.at(i)=='t')
	    		{i++;
	    		if(i+1>=s.length())
	    				{cout<<"ERROR!";flag=false;}
	    			else if(s.at(i+1)==';')
	    		    {
	    			 if(s.at(i)=='s')
	    				yo_tch(i,'i');
	    			else if(s.at(i)=='t')
	    				yo_tn(i,'i');
	    			else 
	    				{cout<<"ERROR-unkown";flag=false;}
	    			}
	    			else {cout<<"ERROR-unexpected token!";flag=false;}
	    		}
	    	}
	    }
		else if(s.at(i)==';')
		;
	}
	char t;
	cin>>t;
	return 0;
}