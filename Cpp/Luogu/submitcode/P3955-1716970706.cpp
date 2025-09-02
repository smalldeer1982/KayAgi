#include <iostream>
#include <cstdio>
#include <algorithm>//各种常见函数的算法库，比如sort，max，min等
using namespace std;
const int S=1005;
long long b[S],x[S],tmp[S],xc[S]; //x：需求码，xc：x的长度，b：书的编码，tmp后面会用
int n,q;
int main(){
    cin>>n>>q;
    for (int i=1;i<=S;i++)
        tmp[i]=1;
    for (int i=1;i<=n;i++)
        cin>>b[i];
    sort(b,b+n+1);//偷懒，使用STL库排序，+1不能忘
    for (int i=1;i<=q;i++){
        cin>>xc[i]>>x[i];
        for (int j=1;j<=xc[i];j++)
            tmp[i]*=10;//这里先做了一个暂存数组，方便后面取几位
    }
    for (int i=1;i<=q;i++){
        for (int j=1;j<=n;j++)
            if (b[j]%tmp[i]==x[i]){//这里if判断很核心：b[j]%tmp[i]表示取此编码的末xc位
                cout<<b[j]<<endl;
                break;
            }
            else if (j==n){
                cout<<"-1"<<endl;
                break;
            }    
    }
}