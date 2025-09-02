# [ICPC 2021 WF] Splitstream

## 题目描述

### 题意
有一个有 $n$ 个节点的传输数字序列的网络，其中有两种节点：拆分节点和合并节点。拆分节点会将输入序列中的数字交替插入两个输出序列中，合并节点会交替将两个输入序列中的数字插入输出序列中。例如：

$\{1,2,3,4,5\}$ 拆分得 $\{1,3,5\}$ 和 $\{2,4\}$。

$\{2,4\}$ 和 $\{1,3,5\}$ 合并得 $\{2,1,4,3,5\}$。

在网络中，除 $1$ 号外每一个结点的每一个输入端都连接着另一个节点的输出端,$1$ 号节点的输入端为总输入端，每一个输出端不一定连接着另一个节点的输入端。每一个输出端都有着从 $2$ 开始的正整数编号。

将一个数字序列 $\{1,2,\cdots,m\}$ 从 $1$ 号节点的输入端输入网络，你需要求出编号为  $x$ 的输出端输出的序列中的第 $k$ 个数字。

## 样例 #1

### 输入

```
200 2 2
S 1 2 3
M 3 2 4
4 99
4 100
```

### 输出

```
100
99
```

## 样例 #2

### 输入

```
100 3 6
S 1 4 2
S 2 3 5
M 3 4 6
6 48
6 49
6 50
6 51
6 52
5 25
```

### 输出

```
47
98
49
51
53
100
```

## 样例 #3

### 输入

```
2 3 3
S 1 2 3
S 3 4 5
M 5 2 6
3 1
5 1
6 2
```

### 输出

```
2
none
none
```

# 题解

## 作者：iyaang (赞：4)

[心动的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17576363.html)

[题目链接](https://www.luogu.com.cn/problem/P9448)

这场里面较为简单的题，直接模拟即可。

首先按照题意建出整张流程图，同时存一下反图，这样方便查询时倒推，注意到题目保证一定是无环结构，所以可以直接拓扑排序算出每个点的流量有多少。对于查询，直接根据分流节点还是汇流节点（这个可以根据正图的后继节点数量判断）求出在前一个点的编号是多少，分讨一下就好。如果遍历途中出现了在这个点的编号大于了这个点的流量，则输出 `none`，否则一直回溯到 $1$ 号点输出其编号。对于每次询问我们可能回溯整张流程图的每个节点，于是做到了 $\mathcal O(nq)$，足以通过。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    static const int top=100000;
    int n,m,q,x,y,z,k;
    int deg[MAX],flow[MAX];
    vector<int> G[MAX],T[MAX];
    char c;

    inline void lmy_forever()
    {
    	auto add=[&](int x,int y)->void
    	{
    		G[x].eb(y),T[y].eb(x),++deg[y];
		};
    	auto tpsort=[&]()->void
    	{
    		queue<int> Q;
    		flow[1]=m;
    		for(int i=1;i<=n+top;++i) if(!deg[i]) Q.push(i);
    		while(!Q.empty())
    		{
    			int now=Q.front(); Q.pop();
    			if(((int)G[now].size())==2) flow[G[now][0]]+=(flow[now]+1)/2,flow[G[now][1]]+=flow[now]/2;
    			else if(((int)G[now].size())==1) flow[G[now][0]]+=flow[now];
    			for(auto to:G[now]) if(!--deg[to]) Q.push(to);
			}
		};
		auto dfs=[&](auto dfs,int now,int kth)
		{
			if(flow[now]<kth) return puts("none"),void();
			else if(now==1) return write(kth,'\n');
			int to=T[now][0];
			if(((int)T[now].size())==2)
			{
				int _to=T[now][1],mix=min(flow[to],flow[_to]);
				if(mix*2<kth) kth-=mix,to=flow[to]>flow[_to]?to:_to;
				else if(kth&1) kth=kth/2+1;
				else kth/=2,to=_to;
			}
			if(((int)G[to].size())==2) kth=kth*2-(G[to][0]==now);
			dfs(dfs,to,kth);
		};
		
    	read(m,n,q);
    	for(int i=1;i<=n;++i)
    	{
    		do c=getchar(); while(c!='S'&&c!='M'); read(x,y,z);
    		if(c=='S') add(x,i+top),add(i+top,y),add(i+top,z);
    		if(c=='M') add(x,i+top),add(y,i+top),add(i+top,z);
		}
		tpsort();
		while(q--) read(x,k),dfs(dfs,x,k);
        return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

