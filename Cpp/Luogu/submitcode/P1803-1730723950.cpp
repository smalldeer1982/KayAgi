#include<bits/stdc++.h>
using namespace std;
int n,sum=0,c=1;
double ans=0;
struct student{
	int b,e;
}stu[1000005];
bool cmp(student x,student y){
	if(x.e<y.e){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>stu[i].b>>stu[i].e;
	}
	sort(stu+1,stu+n+1,cmp);
	int end=stu[1].e;
	for(int i=2;i<=n;i++){
		if(stu[i].b>=end){
			c++;
			end=stu[i].e;
		}
	}
	cout<<c;
	return 0;
}