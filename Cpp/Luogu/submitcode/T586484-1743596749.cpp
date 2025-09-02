#include<bits/stdc++.h>
using namespace std;
long long n,x;
long long a[100005];
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	long long cnt=0;
	for(int i=1;i<=n;i++){
        // 替换为标准库的二分查找统计
		cnt += upper_bound(a+1,a+n+1,a[i]+x) - lower_bound(a+1,a+n+1,a[i]+x);
	}
	cout<<cnt;
	return 0;
}
