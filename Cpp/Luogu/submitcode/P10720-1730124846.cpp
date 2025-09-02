#include <bits/stdc++.h>
using namespace std;
int lucky(int sum) {//函数处理是否为幸运数 
	int ans=0;
	int a=sum;
	for(int i=2; i*i<=a; i++) {
		if(sum%i==0) {
			ans++;
			while(sum%i==0) {
				sum/=i;
			}
		}

	}
	if(sum>1) {
		ans++;
	}
	if(ans==2) {
		return 1;
	} else {
		return 0;
	}
}
int main() {
	int n;
	cin>>n;
	int a;
	while(n--) {
		scanf("%d",&a);
		cout<<lucky(a)<<endl;
	}
	return 0;
}