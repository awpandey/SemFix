#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
void genCons(){
	ifstream all_op,path,testCase,expect;
	ofstream constraint,temp;
	int expected =0,j,k=0;
	char op[255],buffer[40];


	testCase.open("TestCase");
	expect.open("Expected_output");


	while(testCase.getline(op,255)){
		j=0;
		temp.open("temp");
		temp << op <<"\n";
		temp.close();
		expect.getline(op,255);
		expected= atoi(op);
		system("klee -write-pcs traffic.bc temp ");
		//cout <<"expected is "<< expected <<"\n";
		all_op.open("all_output");


		while (all_op.getline(op,16)){
			j++;
			if(atoi(op)==expected){
				sprintf(buffer,"CONSTRAINT%d",k);
				constraint.open(buffer, std::fstream::app);
				constraint << "(declare-const bias Int)\n";
				constraint.close();
				sprintf(buffer,"cat klee-out-0/test00000%d.pc >> CONSTRAINT%d",j,k);
				system(buffer);
				k++;
			}
		}
		temp.close();
		all_op.close();
		system("rm temp all_output");
		system("rm -r klee-*");
	}
		testCase.close();
		expect.close();
}
main(){
	genCons();
	return 0;
}

