#include<z3++.h>
#include<iostream>
#include<vector>
#include<cstring>
#include<map>
#include<fstream>
#include<cstdlib>
using namespace std;
using namespace z3;


class binaryComponent {
	public :
		char name;
		int argument1,argument2,result,v_argument1,v_argument2,v_result;
		static int binCount;
		binaryComponent(){
			argument1 = argument2 = result = -1;
			binCount++;
		}
};

class unaryComponent {
	public :
		char name;
		int argument1,result,v_argument1,v_result;
		static int unCount;
		unaryComponent(){
			argument1 = result = -1;
			unCount++;
		}	
};

class argument{
	public:
		int value,locVal;
};

int binaryComponent::binCount = 0;
int unaryComponent::unCount = 0;

main(){
	binaryComponent a[2]  ;
	unaryComponent b[1];
	argument parameter[3];
	a[0].name='+';
	a[1].name='-';
	b[0].name='r';
	int numArgument = 3 , maxLoc,loc_value ,input[3]={1,2,3};
	char buffer[40];
	string loc_symbol;
	fstream temp;
	map< string , int > value; 
	maxLoc = binaryComponent::binCount + unaryComponent::unCount + numArgument - 1;
	context c , d ;
	solver s(c) ;
	vector<expr> P,Pu,R,arg,VP,VPu,VR;
	expr qi = d.int_const("a");

	/* Constraint for Argument of component  */
	for(int i=0;i<numArgument;i++){
		sprintf(buffer,"Argu%d",i);
		qi = c.int_const(buffer);
		arg.push_back(qi);
		s.add(arg[i] ==i);
		parameter[i].locVal=i;
		parameter[i].value=input[i];
	}
	/* Constraint for Input of binary component*/
	for(int i=0;i<2*binaryComponent::binCount ;i++){
		sprintf(buffer,"BComp%d_1",i/2);
		qi = c.int_const(buffer);
		P.push_back(qi);
		s.add(P[i] >=0);
		s.add(P[i] <=maxLoc);
		cout << "Value=" << BComp0_1 <<"\n";
		i++;
		sprintf(buffer,"BComp%d_2",i/2);
		qi = c.int_const(buffer);
		P.push_back(qi);
		s.add(P[i] >=0);
		s.add(P[i] <=maxLoc);
	}
	/*Constraint for input of unary component*/
	for(int i=0;i<unaryComponent::unCount ;i++){
		sprintf(buffer,"UComp%d",i);
		qi = c.int_const(buffer);
		Pu.push_back(qi);
		s.add(Pu[i] >=0);
		s.add(Pu[i] <=maxLoc);
	}
	/*Location variable for return value of component*/
	for(int i=0;i<binaryComponent::binCount;i++){
		sprintf(buffer,"CBret%d",i);
		qi = c.int_const(buffer);
		R.push_back(qi);
		s.add(R[i] >= numArgument);
		s.add(R[i] <= maxLoc);
	}
	for(int i=0;i<unaryComponent::unCount;i++){
		sprintf(buffer,"CUret%d",i);
		qi = c.int_const(buffer);
		R.push_back(qi);
		s.add(R[i+binaryComponent::binCount] >= numArgument);
		s.add(R[i+binaryComponent::binCount] <= maxLoc);
	}

	/*Consistency Constraint */
	for(int i=0;i<R.size();i++){
		for(int j=i+1;j<R.size();j++)
			s.add(R[i] != R[j]);
	}

	/*Acyclic Constraint*/
	int j=0;
	for(int i=0;i<2*binaryComponent::binCount;i++){
		s.add(P[i]< R[j]);
		i++;
		s.add(P[i] < R[j]);
		cout << a[j].name << "\n";
		if(a[j].name=='+')
			s.add(P[i]
		j++;
		//cout << P[i++] <<"\t" << P[i] << "\t"<< R[j++];
	}
	j=binaryComponent::binCount;
	for(int i=0;i<unaryComponent::unCount;i++){
		s.add(Pu[i]< R[j]);
		i++;
		s.add(P[i] < R[j]);
		j++;
		//cout << P[i++] <<"\t" << P[i] << "\t"<< R[j++];
	}


	std::cout << s.check() << "\n";
	model m = s.get_model();
	for (unsigned i = 0; i < m.size(); i++) {
		func_decl v = m[i];
		assert(v.arity() == 0); 
		temp.open("temp", std::fstream::in | std::fstream::out | std::fstream::app);
		temp << v.name() << " " <<  m.get_const_interp(v) <<"\n";
		temp.close();
	}

	temp.open("temp",std::fstream::in);
	int i=m.size();
	while(i--){
		temp >> loc_symbol >> loc_value; 
		value.insert( pair<string,int>(loc_symbol,loc_value));
	}
	temp.close();

	system("rm temp");

	for(map<string,int >::iterator it=value.begin();it!=value.end();it++){
		//cout << it->first << "  :  "<< it->second <<"\n";
		if(it->first[0]=='B'){
			i=5;j=0;
			while(it->first[i]!='_'){
				j=j*10+(it->first[i]-'0');
				i++;
			}
			i++;
			if(it->first[i]=='1')
				a[j].argument1=it->second;
			else
				a[j].argument2=it->second;
		}
		else if(it->first[0]=='U'){                     
			i=5;j=0;
			while(it->first[i]!='\0'){
				j=j*10+(it->first[i]-'0');
				i++;
			}
			b[j].argument1=it->second;
		}
		else if (it->first[0]=='C'){
			i=5;j=0;
			while(it->first[i]!='\0'){
				j=j*10+(it->first[i]-'0');
				i++;
			}
			if(it->first[1]=='B')
				a[j].result=it->second;
			else
				b[j].result=it->second;
		}
	}
	std::map<int,int> mymap;
	for(int i=0;i<3;i++){

	}
	cout << "Binary Component\nArgunent1\tArgument2\tresult\n";
	for(int i=0;i<binaryComponent::binCount;i++){
		cout << a[i].argument1 << "\t\t" << a[i].argument2 << "\t\t" <<a[i].result << "\n";
	}
	cout << "Unary Component\nArgument1\tResult\n";
	for(int i=0;i<Pu.size();i++){
		cout << b[i].argument1 << "\t\t" <<b[i].result << "\n";
	}
	cout << "Parameter\nLocValue\tvalue\n";
	for(int i=0;i<3;i++){
		cout << parameter[i].locVal << "\t\t" << parameter[i].value <<"\n";
	}
}
