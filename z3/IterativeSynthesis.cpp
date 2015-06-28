#include<iostream>
#include<z3++.h>
#include<vector>
#include<map>
#include<string>

int main(){
	map<vector<string>, int > E;

	while(1){
		L=T_SAT(Behave(L));
		if(L==NULL){
			cout << Component Insufficient;
			return 0;
		}
		alpha=T_SAT(Distinct(I));
		if(alpha==NULL){
			P=Lval2Prog(L);
			if(V(P))
				return P;
			else
				cout<<"Component Insufficient";
		}
	}
	return 0;
}

