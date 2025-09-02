# [GCJ 2021 #3] Binary Search Game

## 题目描述

**Alice** 和 **Bob** 将要玩一个名为二分搜索的游戏。游戏在一个由 $2^{\mathbf{L}}$ 个格子组成的单行棋盘上进行。每个格子中包含一个介于 1 到 $\mathbf{N}$ 之间的整数（包括 1 和 $\mathbf{N}$）。此外，还有编号为 1 到 $\mathbf{N}$ 的 $\mathbf{N}$ 张卡片。在游戏开始前，裁判会以 $\mathbf{M}^{\mathbf{N}}$ 种可能的分配方式之一，在每张卡片上写下一个介于 1 到 $\mathbf{M}$ 之间的整数（包括 1 和 $\mathbf{M}$）。**Alice** 和 **Bob** 在游戏开始前知道棋盘上每个格子的整数以及每张卡片上的数字。

游戏以轮流进行的方式展开，**Alice** 先手。总共有 $\mathbf{L}$ 轮，这意味着 **Alice** 会进行 $\lceil \mathbf{L}/2 \rceil$ 轮，而 **Bob** 会进行 $\lfloor \mathbf{L}/2 \rfloor$ 轮。在每一轮中，玩家可以选择消除剩余格子中最左侧的一半或最右侧的一半。例如，假设棋盘上的数字为 $[2, 4, 1, 1, 4, 5, 2, 5]$。在 **Alice** 的第一轮中，她必须选择消除其中一半，留下 $[2, 4, 1, 1]$ 或 $[4, 5, 2, 5]$。如果她选择消除最左侧的一半并留下 $[4, 5, 2, 5]$，那么 **Bob** 必须在下一轮中选择留下 $[4, 5]$ 或 $[2, 5]$。如果他选择留下 $[2, 5]$，那么在最后一轮中，**Alice** 将需要在 $[2]$ 和 $[5]$ 之间做出选择。

游戏结束时，他们查看唯一剩下的格子中的数字 $X$。游戏的分数就是编号为 $X$ 的卡片上所写的整数。在上述例子中，如果 **Alice** 在最后一轮中消除 $[5]$ 并留下 $[2]$，那么游戏的分数就是裁判在编号为 2 的卡片上写的数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/l71ofi6o.png)

**Alice** 会采取最优策略以最大化游戏分数，而 **Bob** 则会采取最优策略以最小化分数。他们在一个固定的棋盘上进行游戏，棋盘上的格子中分别写着整数 $\mathbf{A}_1$, $\mathbf{A}_2$, …, $\mathbf{A}_{2^{\mathbf{L}}}$。为了确保最大限度的公平性，他们会进行 $\mathbf{M}^{\mathbf{N}}$ 局游戏，每局游戏中裁判会以不同的方式在卡片上写数字。这意味着对于每一种可能的卡片分配方式，**Alice** 和 **Bob** 都会恰好进行一局游戏。给定游戏参数和固定的棋盘内容，请计算所有游戏的分数之和。由于输出可能是一个非常大的数字，我们只要求你输出结果对质数 $10^9 + 7$（即 $1000000007$）取模后的余数。

## 说明/提示

**样例解释**

在样例 #1 中，有 4 种卡片分配方式：$[1, 1]$、$[1, 2]$、$[2, 1]$ 和 $[2, 2]$。在前两种分配方式中，无论 **Alice** 在首轮如何选择，**Bob** 总能使得最终剩下的格子中的数字为 1，而卡片 1 上的数字为 1，因此这两局游戏的分数均为 1。在后两种分配方式中，**Alice** 可以通过在首轮消除棋盘最左侧的一半，留下 $[1, 1]$，此时 **Bob** 别无选择，只能留下 $[1]$。由于在这两种分配方式中卡片 1 上的数字为 2，因此这两局游戏的分数均为 2。所有分数的总和为 $1 + 1 + 2 + 2 = 6$。

**数据范围**

- $1 \leq \text{T} \leq 12$。
- $1 \leq \text{L} \leq 5$。
- 对于所有 $i$，满足 $1 \leq \text{A}_i \leq \text{N}$。

**测试集 1（9 分，可见判定结果）**

- $1 \leq \text{N} \leq 8$。
- $1 \leq \text{M} \leq 100$。

**测试集 2（26 分，隐藏判定结果）**

- $1 \leq \text{N} \leq 32$。
- $1 \leq \text{M} \leq 10^9$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
2 2 2
2 1 1 1
4 3 2
3 1 1 4
5 100 3
2 4 1 1 4 5 2 5```

### 输出

```
Case #1: 6
Case #2: 144
Case #3: 991661422```

# 题解

## 作者：_LiWenX_ (赞：1)

感觉这个题缝合了一堆算法。。。

首先把这个博弈论给做了，容易设计一个 dp，博弈的决策是一个线段树一样的东西，对于树上的节点 $x$，如果先手操作，$f_x=\max(f_{ls},f_{rs})$，否则 $f_x=\min(f_{ls},f_{rs})$。

为了计数我们希望 dp 套 dp，但是状态怎么看都太大了，使用一个经典的 trick，$x=\sum_{i} [i\le x] $，然后把大于等于 $i$ 的数字视为 $1$，小于 $i$ 的视为 $0$，枚举所有的 $i$，然后都做一遍这个事情，最后根节点为 $1$ 的方案数加起来就是答案。

所以现在考虑只有 0/1 且任意位置随便放怎么做，设 $f_{i,0/1}$ 表示做完 $i$ 的子树，$i$ 节点为 $0/1$ 的方案数，那么显然可以转移。

但是考虑到还有一点，$a$ 相同的位置得是一样的，这就麻烦了，不过稍加观察就可以发现，如果给 $a$ 相同的点之间两两连边，那么大小大于二的联通块数量至多 $2^{L-1}=16$ 个，我们可以直接枚举这些联通块放了什么，而其他没有限制的子树，可以直接预处理 dp 的答案。

不过如果要考虑还原答案的话，我们需要枚举 $i$，$1$ 这个数字有 $m-i+1$ 种放法，$0$ 有 $i$ 种放法，如果对每一个 $i$ 都去做一遍的话，得到一个 $O(m2^{2^{L-1}}2^L)$ 的复杂度的做法，可以通过第一个包。

现在的问题变成了去掉 $m$，容易观察发现，答案必然是一个关于 $m$ 的 $O(2^L)$ 次多项式，因为假如枚举 $1$ 的个数，此时就是这个常数乘上了一个 $O(2^L)$ 次多项式。

所以启发我们使用拉格朗日插值，求出 $m$ 在 $1\sim O(2^L)$ 范围内的答案，并且在 dp 种额外记录 $1$ 的个数，那么直接转移即可，因为每一次转移都要卷积一次，复杂度看似是 $O(2^{2^{L-1}}2^{3L})$，但事实上，只有根节点的卷积跑满，两个儿子卷积的代价加起来都没根节点多。总复杂度是 $O(2^{2^{L-1}}2^{2L})$，可以通过，实际上跑得超级快，我没做任何卡常都只跑了 $1.2$ 秒，不知道开 $30$ 秒在干什么。

实际实现还有若干的细节。

代码写的有点复杂。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int quickpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }return ret;
}
int C[33][33];
int inv[114514];
void init(int n=32){
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    for(int i=1;i<=100000;i++) inv[i]=quickpow(i,mod-2);
}
#define poly vector<int>
poly operator*(poly A,poly B){
    if(A.size()*B.size()==0) return {};
    poly ret;ret.resize(A.size()+B.size()-1);
    for(int i=0;i<A.size();i++){
        for(int j=0;j<B.size();j++){
            ret[i+j]=(ret[i+j]+A[i]*B[j])%mod;
        }
    }return ret;
}
poly operator+(poly A,poly B){
    if(A.size()<B.size()) swap(A,B);
    for(int i=0;i<B.size();i++) A[i]=(A[i]+B[i])%mod;
    return A;
}
poly operator-(poly A,poly B){
    for(int &u:B) u=mod-u;return A+B;
}

int N,M,L;
int cnt[32],a[32];
int n,tid;
int dep[128],flag[128],tot;
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
void build(int now,int l,int r){
    flag[now]=0;
    if(l==r) return ;
    dep[ls]=dep[rs]=dep[now]+1;
    build(ls,l,mid),build(rs,mid+1,r);
}
void add(int now,int l,int r,int x){
    flag[now]=1;
    if(l==r) return ;
    if(mid>=x) add(ls,l,mid,x);
    else add(rs,mid+1,r,x);
}
poly g[7][2],f[128][2];
int S;
void dp(int now,int l,int r){
    f[now][0].clear(),f[now][1].clear();
    if(!flag[now]){
        f[now][0]=g[dep[now]][0];
        f[now][1]=g[dep[now]][1];
        return ;
    }
    if(l==r){
        if((S>>a[l])&1) f[now][1]={1};
        else f[now][0]={1};
        return ;
    }
    dp(ls,l,mid);
    dp(rs,mid+1,r);
    if(dep[now]&1){
        f[now][0]=(f[ls][1]+f[ls][0])*(f[rs][1]+f[rs][0])-f[ls][1]*f[rs][1];
        f[now][1]=f[ls][1]*f[rs][1];
    }
    else{
        f[now][1]=(f[ls][1]+f[ls][0])*(f[rs][1]+f[rs][0])-f[ls][0]*f[rs][0];
        f[now][0]=f[ls][0]*f[rs][0];
    }
}
#undef ls
#undef rs
#undef mid
int lag(vector<pair<int,int> > vec,int x){
    int ret=0;
    for(int i=0;i<vec.size();i++){
        int s=1;
        for(int j=0;j<vec.size();j++){
            if(i==j) continue;
            int d=vec[i].first-vec[j].first;
            if(d>0) s=s*(x-vec[j].first)%mod*inv[d]%mod;
            else s=s*(x-vec[j].first)%mod*inv[-d]%mod,s=mod-s;
        }s%=mod;
        ret+=s*vec[i].second%mod;
    }ret%=mod;
    return ret;
}
void solve(){
    memset(cnt,0,sizeof(cnt));
    memset(dep,0,sizeof(dep));
    memset(flag,0,sizeof(flag));
    cin>>N>>M>>L;
    n=1<<L;for(int i=0;i<n;i++) cin>>a[i],a[i]--,cnt[a[i]]++;
    int lf=0;for(int i=0;i<N;i++) if(!cnt[i]) lf++;
    build(1,0,n-1);
    map<int,int> ma;
    tot=0;
    for(int i=0;i<n;i++){
        if(cnt[a[i]]==1){
            a[i]=-1;
            continue;
        }
        if(ma.find(a[i])==ma.end()) ma[a[i]]=tot++;
        a[i]=ma[a[i]];add(1,0,n-1,i);
    }
    for(int i=1;i<=L+1;i++) for(int j=0;j<2;j++) g[i][j].clear();
    g[L][0]={1};
    g[L][1]={0,1};
    for(int i=L-1;~i;i--){
        if(i&1){
            g[i][0]=(g[i+1][1]+g[i+1][0])*(g[i+1][1]+g[i+1][0])-g[i+1][1]*g[i+1][1];
            g[i][1]=g[i+1][1]*g[i+1][1];
        }
        else{
            g[i][1]=(g[i+1][1]+g[i+1][0])*(g[i+1][1]+g[i+1][0])-g[i+1][0]*g[i+1][0];
            g[i][0]=g[i+1][0]*g[i+1][0];
        }
    }
    poly ans;
    for(S=0;S<(1<<tot);S++){
        dp(1,0,n-1);
        poly now=f[1][1];
        int num=__builtin_popcount(S);
        while(num--) now.insert(now.begin(),0);
        ans=ans+now;
    }
    poly lfxxx;lfxxx.resize(lf+1);for(int i=0;i<=lf;i++) lfxxx[i]=C[lf][i];
    ans=ans*lfxxx;
    // for(int u:ans) cout<<u<<' ';cout<<'\n';
    ans.resize(N+1);
    auto F=[&](int m){
        int Ans=0;
        for(int i=0;i<=N;i++){
            for(int j=0;j<m;j++){
                Ans+=ans[i]*quickpow(m-j,i)%mod*quickpow(j,N-i)%mod;
            }
        }Ans%=mod;
        return Ans;
    };
    cout<<"Case #"<<++tid<<": ";
    if(M<=100){
        cout<<F(M)<<'\n';
        return ;
    }
    vector<pair<int,int> > vec;
    for(int i=1;i<=50;i++) vec.push_back({i,F(i)});
    cout<<lag(vec,M)<<'\n';
}
signed main(){
    init();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tt;cin>>tt;
    while(tt--) solve();
}
```

---

## 作者：gdf_yhm (赞：0)

[P13042](https://www.luogu.com.cn/problem/P13042)

### 思路

博弈是在线段树上，按照深度，$g_{nd}=\max(g_{ls},g_{rs})$ 或 $g_{nd}=\min(g_{ls},g_{rs})$。 

转 $0/1$。枚举 $v\in[1,m]$，设 $f_v$ 表示结果 $\ge v$ 的情况数，设 $g_{nd,0/1}$ 表示线段树节点 $nd$ 上是否 $\ge v$ 的方案数。$ans=\sum v\times(f_{v}-f_{v+1})=\sum f_v$。

要求一些节点有相同的数值，状压 $2^n$ 记录初始状态。初始为 $0$ 有 $v-1$ 种选择，初始为 $1$ 有 $m-v+1$ 种选择。复杂度 $O(m2^n2^l)$。

如果没有要求一些节点有相同的数值，可以在线段树叶子节点令 $g_{nd,0}=v-1,g_{nd,1}=m-v+1$，不用状压。有要求多个节点相同的不超过 $\frac{2^l}{2}=16$ 个，可以只状压这部分。复杂度 $O(m2^{2^{l-1}}2^l)$。

对于每个 $v$，都是枚举 $s$，系数为常数乘 $(v-1)^{n-|S|}\times (m-v+1)^{|S|}$，$f_v$ 是关于 $v$ 不超过 $n$ 次多项式。则 $ans_m=\sum_{i=1}^m f_m$，是关于 $m$ 不超过 $n+1$ 次多项式。弄 $n+2$ 个点值插值即可。复杂度 $O(n2^{2^{l-1}}2^l)$。

### code

```cpp
int n,m,l,a[maxn];
int siz[maxn],rnk[maxn];
vector<int> id;
int f[maxn],ans;
int g[maxn<<2][2];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int calc(int v){
    int ans=0;
    for(int s=0;s<(1<<id.size());s++){
        auto dfs=[&](auto &&self,int nd,int l,int r,int d)->void{
            if(l==r){
                g[nd][0]=g[nd][1]=0;
                if(~rnk[a[l]]){
                    if(s&(1<<rnk[a[l]]))g[nd][1]=1;
                    else g[nd][0]=1;
                }
                else g[nd][0]=v-1,g[nd][1]=m-v+1;
                return ;
            }
            self(self,ls,l,mid,d+1),self(self,rs,mid+1,r,d+1);
            if(d&1)g[nd][1]=(g[ls][0]*g[rs][1]+g[ls][1]*g[rs][0]+g[ls][1]*g[rs][1])%mod,g[nd][0]=g[ls][0]*g[rs][0]%mod;
            else g[nd][0]=(g[ls][0]*g[rs][0]+g[ls][0]*g[rs][1]+g[ls][1]*g[rs][0])%mod,g[nd][1]=g[ls][1]*g[rs][1]%mod;
        };
        dfs(dfs,1,0,(1<<l)-1,1);
        (ans+=ksm(v-1,id.size()-__builtin_popcount(s))*ksm(m-v+1,__builtin_popcount(s))%mod*g[1][1])%=mod;
    }
    return ans;
}
void work(){
    n=read();m=read();l=read();ans=0;
    for(int i=0;i<(1<<l);i++)a[i]=read();
    for(int i=1;i<=n;i++)siz[i]=0,rnk[i]=-1;
    for(int i=0;i<(1<<l);i++)siz[a[i]]++;
    id.clear();
    for(int i=1;i<=n;i++)if(siz[i]>1)id.pb(i),rnk[i]=id.size()-1;
    int num=0;for(int i=1;i<=n;i++)if(!siz[i])++num;
    for(int i=1;i<=n+2;i++)f[i]=calc(i);
    for(int i=1;i<=n+2;i++)(f[i]+=f[i-1])%=mod;
    if(m<=n+2){printf("%lld\n",f[m]*ksm(m,num)%mod);return ;}
	for(int i=1;i<=n+2;i++){
		int mul=f[i];
		for(int j=1;j<=n+2;j++)if(i!=j)mul=mul*(m-j+mod)%mod*ksm(i-j+mod)%mod;
		(ans+=mul)%=mod;
	}
    printf("%lld\n",ans*ksm(m,num)%mod);
}
```

---

