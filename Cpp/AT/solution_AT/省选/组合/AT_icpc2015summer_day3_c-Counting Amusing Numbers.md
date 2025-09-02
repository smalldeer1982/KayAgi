# Counting Amusing Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2015summer-day3/tasks/icpc2015summer_day3_c



# 题解

## 作者：Le0Chan (赞：0)

某人搬的 NOIp 模拟赛 T3。

基础生成函数练习题？

考察一个数是否是好的显然只关心每个数位的出现次数，令其为 $a_{0\sim 9}$。如何判定 $a$ 是否合法？

观察一下数 $x,y$ 的加法过程容易看出：如果 $x+y=10^n$，则一定能分为三段，第一段 $x_i+y_i=9$，第二段只有一个数 $x_j+y_j=10$，第三段 $x_k=y_k=0$，证明简单。

令最终填好的数位的出现次数为 $b$，最初的为 $a$，则这个方案的贡献是 $\frac{m!}{\prod(b_i-a_i)!}$。

首先肯定有 $b_i\ge a_i$。对 $b$ 合法性的判定，可以先枚举后缀 $0$ 的个数 $k$ 和第二段的两个数为 $(x,y)$，先把这些东西的出现次数减去，则剩下的数一定要满足 $\forall i+j=9,b_i=b_j$。

$(x,y)$ 只有 $5$ 对，直接暴力枚举。为什么不会算重？考虑一个引理是：任意一个好数 $X$ 的拆分中，和为 $10$ 的无序对 $(x_j,y_j)$ 是唯一的，证明也很简单。类似的还有后缀 $0$ 的个数是唯一的。则和 $0$ 没有关系的数对都已知他们的差。只需要确定其中任意一个即可算出另一个。设其中一对的生成函数为 $f_z(x)=\sum\limits_{i=0}\dfrac{1}{i!j!}x^{i+j}$。这个阶乘就是上面说的对方案的贡献。和 $0$ 有关系的就是 $9$，设最初有 $a_0$ 个 $0$，$a_9$ 个 $9$，问号中有 $c_0$ 个 $0$，$c_9$ 个 $9$。则要满足 $c_0+a_0\ge c_9+a_9,c_0+a_0\equiv c_9+a_9\pmod 2$。

令 $(0,9)$ 的生成函数为 $g(x)=\sum\limits_{i=0}x^i\sum\limits_{c_0=0}\sum\limits_{c_9=0}[?]\dfrac{c_0!}{c_9!}$，$?$ 就是上一段末的合法语句。$g(x)$ 的前 $m$ 次项系数显然可以 $O(m^2)$ 求出。

最后把这五个生成函数乘起来取 $m$ 次项系数即可。暴力做就是 $O(m^2)$ 的了。可能能通过一些方式降低复杂度？但是我不会多项式，尝试无果。


```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
#define LL long long
#define db double
#define _int __int128
#define vi vector<int>
#define tii tuple<int,int,int>
#define pii pair<int,int>
#define fi first 
#define se second
#define pb push_back
const int N=1e3+5,mod=1e9+7;
int n,m,tot,rs;
int ct[10],tg[10],fac[N],ifac[N];
int f[5][N],g[N],tm[N];
string s;
pii a[5]={{0,9},{1,8},{2,7},{3,6},{4,5}};
pii b[5]={{1,9},{2,8},{3,7},{4,6},{5,5}};
void md(int &x){if(x>=mod) x-=mod;}
int qp(int a,int b){
    int as=1;
    while(b){
        if(b&1) as=1ll*as*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }return as;
}
void mul(int *A,int *B,int tot){
    for(int i=0;i<=tot;i++) tm[i]=0;
    for(int i=0;i<=tot;i++){
        for(int j=0;j+i<=tot;j++){
            md(tm[i+j]+=1ll*A[i]*B[j]%mod);
        }
    }
    for(int i=0;i<=tot;i++) A[i]=tm[i];
}
int cal(int op){
    for(int i=0;i<5;i++) for(int j=0;j<=m;j++) f[i][j]=0;
    for(int i=0;i<10;i++) tg[i]=0;
    auto [xx,yy]=b[op];tg[xx]++;tg[yy]++;
    for(int i=1;i<5;i++){
        auto [x,y]=a[i];
        for(int j=0;j<=m;j++){
            int v=ct[x]+j-tg[x];
            if(v<0) continue;
            int k=v-ct[y]+tg[y];
            if(k>=0&&k+j<=m){
                md(f[i][j+k]+=1ll*ifac[j]*ifac[k]%mod);
            }
        }
    }
    for(int i=0;i<=m;i++){
        for(int j=0;j<=m&&i+j<=m;j++){
            int v=ct[0]+i-tg[0],v2=ct[9]+j-tg[9];
            if(v>=0&&v2>=0&&v>=v2){
                if((v-v2)%2==0){
                    md(f[0][i+j]+=1ll*ifac[i]*ifac[j]%mod);
                }
            }
        }
    }
    g[0]=1;
    for(int i=1;i<=m;i++) g[i]=0;
    for(int i=0;i<5;i++) mul(g,f[i],m);
    return 1ll*fac[m]*g[m]%mod;
}
void sv(){
    for(int i=0;i<10;i++)ct[i]=0;
    cin>>s;n=s.size();s=" "+s;
    if(n&1){cout<<"0\n";return;}
    for(int i=1;i<=n;i++){
        int z=(s[i]-'0');
        if(z>=0&&z<=9) ct[z]++;
        else m++;
    }
    int as=0;
    for(int i=0;i<5;i++){
        int v=cal(i);
        md(as+=v);
    }
    cout<<as<<'\n';
}
void init(int mx){
    fac[0]=ifac[0]=1;
    for(int i=1;i<=mx;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[mx]=qp(fac[mx],mod-2);
    for(int i=mx-1;i>=1;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int main(){
    init(1e3);
    // int _T;cin>>_T;
    // while(_T--){
        sv();
    // }
    return 0;
}
}
int main(){
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    #endif 
    // freopen("digit.in","r",stdin);
    // freopen("digit.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    return Le0::main();
}
```

---

