#include<bits/stdc++.h>
using namespace std;
struct student{
    double m,v,x; 
}stu[105];
int n;
double sum=0,c=0;
bool cmp(student a,student b){
    if(a.x>b.x){
		return true;
	}
	return false;
}
int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>stu[i].m>>stu[i].v;
        stu[i].x=stu[i].v/stu[i].m; 
    }
    sort(stu+1,stu+n+1,cmp); 
    for(int i=1;i<=n;i++){
		if(c>=stu[i].m){
		    c-=stu[i].m;
		    sum+=stu[i].v;
		}
		else{
		    sum+=c*stu[i].x;
		    break;
		}
	}
    printf("%.2f",sum);
	return 0; 
}