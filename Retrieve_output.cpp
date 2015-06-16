#include<iostream>
#include <cstdlib>
#include<stdlib.h>
#include<fstream>
using namespace std;
main(){
	char ab[255];
	int numOfTestcase;
	system("ls klee-out-0/| wc -l > temp");
	ifstream read;
	read.open("temp");
	read.getline(ab,255);
	numOfTestcase=(atoi(ab)-6)/2;
	read.close();
	for(int i=1;i<=numOfTestcase;i++){	
	int val=0;
	sprintf(ab,"ktest-tool --write-ints klee-out-0/test00000%d.ktest > result",i);
	system(ab);
	read.open("result");
	while(!read.eof()){
	for(int k=0;k<6;k++)
	read.getline(ab,255);
	int count=0,j=0;
	while(ab[j]!='\0'){
		if(ab[j]==':')
			count++;
		if(count==2){
			if((ab[j]>='0')&&(ab[j]<='9'))
				val=val*10+(ab[j]-'0');
		}
		j++;
	}
	}
cout <<val <<"\n";
read.close();
}
	return 0;
}
