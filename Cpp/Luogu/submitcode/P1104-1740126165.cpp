#include<bits/stdc++.h>
using namespace std;
int n;
struct student{
	string name;
	int year,month,day,num;
}a[105];
bool cmp(student x,student y){
	if(x.year<y.year){
		return true;
	}
	if(x.year==y.year&&x.month<y.month){
		return true;
	}
	if(x.year==y.year&&x.month==y.month&&x.day<y.day){
		return true;
	}
	if(x.year==y.year&&x.month==y.month&&x.day==y.day&&x.num>y.num){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].name>>a[i].year>>a[i].month>>a[i].day;
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		cout<<a[i].name<<endl;
	}
	return 0;
}