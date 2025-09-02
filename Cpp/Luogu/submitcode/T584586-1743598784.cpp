#include<bits/stdc++.h>
using namespace std;

int n;
vector<pair<long long,long long>> ans;

void fj(int n){
    long long nn = 1LL*n*n;  // 避免溢出
    for(long long i=1;i*i<=nn;i++){  // 注意 i*i <= nn
        if(nn%i==0){
            long long a=i,b=nn/i;
            ans.push_back({a+n,b+n});
            if(a!=b) ans.push_back({b+n,a+n});
        }
    }
    sort(ans.begin(), ans.end());
}

int main(){
    cin>>n;
    fj(n);
    for(auto &p:ans)
        cout<<p.first<<" "<<p.second<<endl;
    return 0;
}
