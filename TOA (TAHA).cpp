#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class node;


class node
{
	public:
		char X[25];
		string type;
		node *next;
		
	node()
	{	for(int i=0;i<25;i++)
		X[i]=0;
		next=NULL;
	}
};


char A[]={"i prefer a morning flight"};


node *head=NULL;
node *curr=NULL;

void match(string);
///productions///
void S(void);
void NP(void);
void NOMINAL(void);
void NOMINALd(void);
void VP(void);
void VPd(void);
void VPdd(void);
void PP(void);
///productions///

//other filing functions//

bool isverb(string);
bool ispreposition(string);
bool ispronoun(string);
bool isdeterminer(string);

//other filing functions//

bool isnoun(string key)
{
	string myText;

	ifstream noun("noun.txt");

	while (getline (noun, myText)) 
	{

  	if(key==myText)
  	return true;

	}
	return false;

	noun.close();
	
}

//productions//
void PP(void)
{
	if(curr->type=="preposition")
	{
		match("preposition");
		NP();
	}
}


void VPdd(void)
{
	if(curr->type=="preposition")
	PP();
	else 
	return;
}



void VPd(void)
{
	if(curr->type=="noun")
	{
	NP();
	VPdd();	
	}
	else if(curr->type=="preposition")
	{
		PP();
	}
	else
	return;
	
	
}


void VP(void)
{
	if(curr->type=="verb")
	{
		match("verb");
		VPd();
	}
}

void NOMINALd(void)
{
	if(curr->type=="noun")
	NOMINAL();
	else 
	return;
}

void NOMINAL(void)
{
	if(curr->type=="noun")
	{
		match("noun");
		NOMINALd();
	}
}

void NP(void)
{
	if(curr->type=="pronoun")
	{
		match("pronoun");
	}
	else if(curr->type=="propernoun")
	{
		match("propernoun");
	}
	else if(curr->type=="determiner")
	{
		match("determiner");
		NOMINAL();
	}
	else{
	}
	
}

void S(void)
{
	NP();
	VP();
}


//productions//

void match(string t)
{
	if(curr->type==t)
	curr=curr->next;
	else
	cout<<"Error...\n";
}



void tokenize(void)
{
	
	int i=0,j=0;
	node *p=head;
	while(A[i]!='\0')
	{
		while(A[i]!=' ' && A[i]!='\0')
		{
			
			p->X[j++]=A[i];
			i++;
		}
		p->X[i]='\0';
		
		if(A[i]!='\0')
		{
		node *temp=new node;
		p->next=temp;
		p=p->next;
		j=0;	
		}
		
		i++;
	}
//words entered into linked list
//now identify them

node *q=head;
while(q)
{///make these filing funcs , only noun made yet
if(isnoun(q->X))
{q->type="noun";}
//else if(isverb(q->X))
//{q->type="verb";}
//else if(ispreposition(q->X))
//{q->type="preposition";}
//else if(ispronoun(q->X))
//{q->type="pronoun";}
//else if(isdeterminer(q->X))
//{q->type="determiner";}
else
{q->type="";}


q=q->next;	
}








}

void display(node *t)
{
	node *t2=t;
	while(t)
	{
	cout<<t->X<<" ";
	t=t->next;
	
	}
	
	cout<<endl;
	while(t2)
	{
	cout<<t2->type<<"    ";
	t2=t2->next;
	
	}
}


main()
{
	head=new node;
	curr=head;
	tokenize();
	
	
	S();
	if(curr==NULL)
	cout<<"Parsing Success...\n";
	else////just for fun
	cout<<"Error...\n";///just for fun
	
	display(head);
}
