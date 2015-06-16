#include<stdio.h>
int is_upward_preferred(int inhibit,int up_sep,int down_sep){
	int bias;
	if(inhibit)
		//bias = down_sep;
		klee_make_symbolic(&bias, sizeof(bias), "bias");
	else
		bias=up_sep;
	if(bias>down_sep)
		return 1;
	else
		return 0;
}
int main(int argc, char *argv[]){
	int answer,inhibit=1,up_sep=0,down_sep=100;
	FILE *fp;
	//scanf("%d%d%d",&inhibit,&up_sep,&down_sep);
	fp=fopen("all_output","w");
	answer=is_upward_preferred(inhibit,up_sep,down_sep);	
	fprintf(fp,"%d\n",answer);
	close(fp);	
	return 0;
}
