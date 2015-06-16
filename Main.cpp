#include<iostream>
#include<queue>
#include<string>
#include<set>
#include<vector>
#include<fstream>
#include<priority_queue>
using namespace std;

string Synthesis(string C,int level){
}

set<int> add(set<int> suite,set<int> failedTestcase){
set<int>::iterator it;
for( it = failedTestcase.begin(); it != failedTestcase.end(); it++) {
	suite.insert(*it);  
  }
return suite;
}

set<int> ExtractFailedTests(char *program,char *expected_op, char *testCase){
	char buffer[300],line1[300],line2[300];
	sprintf(buffer, "gcc %s.c  ", program);
	system(buffer);
	sprintf(buffer, "./a.out < %s > output  ", testCase );
	system(buffer);
	ifstream expected,output;
	expected.open(expected_op);
	if(!expected)
		cout<<"Can't open\n";
	output.open("output");
	if(!output)
		cout<<"Can't open";
	int lineNumber=0;
	set<int> failedSet;
	while(!expected.eof()||!output.eof()){
		lineNumber++;
		expected.getline(line1,300);
		output.getline(line2,300);
		if(atoi(line1)!=atoi(line2))
			failedSet.insert(linenumber);
	}
return failedSet;
}

void ApplyRepair(string P, string new_repair,int n){
	ofstream temp ("Duplicate.txt");
	string line;
	ifstream re (P.c_str());
	if (re.is_open() && temp.is_open())
		{
		    while ( getline (re,line) )
    			{
     				 if(line.find("what")!=string::npos)//don't know what to find
					temp <<new_repair<<";\n";
				else
					temp << line<<'\n';
   			 }
		    rename("duplicate.txt",P.c_str());
    	            re.close();
	            temp.close();
  }
}

set<int> extract(char *P,char *E, char *T){
	char buffer[300],line1[300],line2[300];
	sprintf(buffer, "gcc %s.c  ", P);
	system(buffer);
	sprintf(buffer, "./a.out < %s > output  ", T );
	system(buffer);
	ifstream expected,output;
	expected.open(E);
	if(!expected)
		cout<<"Can't open\n";
	output.open("output");
	if(!output)
		cout<<"Can't open";
	int i=0;
	set<int> s;
	while(!expected.eof()||!output.eof()){
		i++;
		expected.getline(line1,300);
		output.getline(line2,300);
		if(atoi(line1)!=atoi(line2))
			s.insert(i);
	}
return s;
}


string GenerateRepairConstraint(char *program, char *expected, char *testCase){
P=argv[1];
E=argv[2];
T=argv[3];
failedTestCase=extract(program,expected,testCase);

}

string Repair(string program, set<int> suite ,priority_queue<int> rc)
{
	constraint= GenerateRepairConstraint(program,expected,testCase);
	level=1;
	new_repair=synthesis(constraint,level);
	while((new_repair==NULL)&&(level<=MAX_LEVEL))
	{
		level++;
		new_repair=Synthesis(C,level);
	}
	return new_repair;
}

int main(int argc , char *argv[])
{
	if(argc!=5){
	cout<< "Usages : ./a.out program testcase expected_output ranklist"
	return 0;
	}
	set<vector<int> > suite;
	set<int> failedTestCase;
	priority_queue<int > RC;
	failedTestCase=ExtractFailedTests(argv[1],argv[3],argv[2]);
	while(!failedTestCase.Empty())
	{
		suite=add(suite,failedTestCase);
		rc=RC.pop();	
		new_repair=Repair(argv[1],suite,rc);
		if(new_repair==NULL)
			break;
		ApplyRepair(program,new_repair,n);// apply repair in nth line
		failedTestCase=ExtractFailedTests(program,expected_op,testCase);
	}
	if(new_reapir!=NULL)
		cout<<"PROGRAM CORRECTED\n";
	return 0;
}
