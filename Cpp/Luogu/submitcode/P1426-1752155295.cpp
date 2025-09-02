#include<bits/stdc++.h>
using namespace std;
#define int long long
double s,x,v=7,sum=0;
bool flag=0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>s>>x;
    while(true){
        if(flag==1){
            if(sum>s+x){
                 cout<<'n';
                 return 0;
            }
            else{
                cout<<'y';
                return 0;
            }
        }
        if(sum>s-x){
            flag=1;
        }
        sum+=v;
        v*=0.98;
    }
	return 0;
}
