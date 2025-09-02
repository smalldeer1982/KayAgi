# Ksenia and Combinatorics

## 题目描述

Ksenia has her winter exams. Today she is learning combinatorics. Here's one of the problems she needs to learn to solve.

How many distinct trees are there consisting of $ n $ vertices, each with the following properties:

- the tree is marked, that is, the vertices of the tree are numbered from 1 to $ n $ ;
- each vertex of the tree is connected with at most three other vertices, and at the same moment the vertex with number 1 is connected with at most two other vertices;
- the size of the tree's maximum matching equals $ k $ .

Two trees are considered distinct if there are such two vertices $ u $ and $ v $ , that in one tree they are connected by an edge and in the other tree they are not.

Help Ksenia solve the problem for the given $ n $ and $ k $ . As the answer to the problem can be very huge you should output it modulo $ 1000000007 (10^{9}+7) $ .

## 说明/提示

If you aren't familiar with matchings, please, read the following link: http://en.wikipedia.org/wiki/Matching\_(graph\_theory).

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
4 2
```

### 输出

```
12
```

# 题解

## 作者：MatrixCascade (赞：9)

首先，树的最大匹配做法是贪心删叶子，然后从下往上去做。

于是我们就可以设计出状态 $dp_{i,j,0/1}$ 表示 $i$ 个节点的树，有 $j$ 个匹配，根是否被匹配的方案树。

注意这个同构的定义是相连节点的集合相同，于是我们需要钦定左儿子的 $siz$ 比右儿子的小，特别的，如果左右儿子 $siz$ 相等的话要 $\div 2$ 。

转移的时候枚举一个儿子的 $siz$ 和匹配数，另一个儿子的可以通过第一个儿子来算出来，由于是带标号的，每次转移的时候要乘上 $\binom{sizl+sizr}{sizl}*(sizl+sizr+1)$ （选一个做根，选 $sizl$ 个做左子树）、

由于题目规定了 $1$ 是根，最后统计答案的时候要 $\div n$ 。

代码（用的记忆化搜索，还挺好写的）：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
#define pb push_back
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
void chkmin(int &x,int y)
{
	if(x>y)x=y;
}
void chkmax(int &x,int y)
{
	if(x<y)x=y;
}
const int mod=1e9+7;
const int maxn=2020;
int fac[maxn+10],ifac[maxn+10];
int qpow(int a,int b=mod-2)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int inv(int k)
{
    return qpow(k,mod-2);
}
void pre()
{
    fac[0]=1;
    for(int i=1;i<=maxn;++i)
        fac[i]=fac[i-1]*i%mod;
    ifac[maxn]=inv(fac[maxn]);
    for (int i=maxn-1;i>=0;--i)
        ifac[i]=ifac[i+1]*(i+1)%mod;
}
int C(int nn,int mm)
{
    if(nn<0||nn-mm<0)return 0;
    return fac[nn]*ifac[mm]%mod*ifac[nn-mm]%mod;
}
int invC(int nn,int mm)
{
    if(nn<0||nn-mm<0)return 0;
    return ifac[nn]*fac[mm]%mod*fac[nn-mm]%mod;
}
int dp[55][55][2];int i2=qpow(2);
int dfs(int n,int m,int fl)
{
	
	if(n==0&&m==0&&fl==1)return 1;
	else if(n==0)return 0;
	if(n==1)
	{
		if(m==0&&fl==0)return 1;
		else return 0;
	}
	if(~dp[n][m][fl])return dp[n][m][fl];
	int ans=0;
	up(ln,0,n-1)
	{
		int rn=n-ln-1;
		if(ln>rn)break;
		up(lm,0,ln/2)
		{
			int rm=m-lm-1;
			up(lf,0,1)
			{
				up(rf,0,1)
				{
					int ff=lf&rf;
					ff=1-ff;
					if(lm+rm+ff!=m)continue;
					if(ff!=fl)continue;
					int val=dfs(ln,lm,lf)*dfs(rn,rm,rf)%mod*C(ln+rn,rn)%mod*(ln+rn+1)%mod;
					if(ln==rn)val*=i2,val%=mod;
					ans+=val;ans%=mod;
				}
			}
			rm=m-lm;
			if(rm<0)continue;
			up(lf,0,1)
			{
				up(rf,0,1)
				{
					int ff=lf&rf;
					ff=1-ff;
					if(lm+rm+ff!=m)continue;
					if(ff!=fl)continue;
					int val=dfs(ln,lm,lf)*dfs(rn,rm,rf)%mod*C(ln+rn,rn)%mod*(ln+rn+1)%mod;
					if(ln==rn)val*=i2,val%=mod;
					ans+=val;ans%=mod;
				}
			}
		}
	}
	dp[n][m][fl]=ans;
	return ans;
}
signed main()
{
	pre();
	int T=1;
	while(T--)
	{
		rdn;rdk;
		memset(dp,-1,sizeof(dp));
		int val1=dfs(n,k,1);
		int val0=dfs(n,k,0);
		int w=val0+val1;w%=mod;w*=qpow(n);w%=mod;
		cout<<w;
	}
}
```


---

## 作者：ywy_c_asm (赞：2)

首先有个比较显然的结论是，在树上自底向上贪心的能匹配就匹配一定会搞出来最大匹配。

那这题的$dp$就比较显然了，$dp[i][j][0/1]$表示$i$个点以1号点为根，最大匹配是$j$，根是否匹配过的方案数。

转移的时候我们枚举左右儿子的大小，如果有一个儿子没匹配过就贪心的匹配上，另外还要乘上儿子的size，因为儿子的根可以是任意的，再乘上组合数即可转移。$O(n^4)$。

另外这题的“不同”是指的一个点连向的点不同，所以不能有左右儿子交换的情况，所以我们需要钦定左儿子大小不能超过右儿子的大小，而且还要在二者相等的时候除个2去掉交换的情况。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy {
	ll dp[65][65][2], c[55][55];
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	void ywymain() {
	    int n, k;
	    cin >> n >> k;
	    dp[1][0][0] = 1;
	    c[0][0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        c[i][0] = 1;
	        for (register int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
	    }
	    ll inv2 = mi(2, p - 2);
	    for (register int i = 2; i <= n; i++) {
	        for (register int j = 1; j < i - 1; j++) {
	            if (j > i - 1 - j)
	                break;
	            for (register int a = 0; a < j && a <= k; a++) {
	                if (!dp[j][a][0] && !dp[j][a][1])
	                    continue;
	                for (register int b = 0; b < i - 1 - j && b <= k; b++) {
	                    if (!dp[i - 1 - j][b][0] && !dp[i - 1 - j][b][1])
	                        continue;
	                    ll cjr = (dp[j][a][0] * dp[i - 1 - j][b][0]) % p;
	                    cjr = (cjr * j) % p;
	                    cjr = cjr * (i - 1 - j) % p;
	                    cjr = (cjr * c[i - 1][j]) % p;
	                    if (j == i - 1 - j)
	                        cjr = (cjr * inv2) % p;
	                    dp[i][a + b + 1][1] = (dp[i][a + b + 1][1] + cjr) % p;
	                    cjr = (dp[j][a][1] * dp[i - 1 - j][b][0]) % p;
	                    cjr = (cjr * j) % p;
	                    cjr = cjr * (i - 1 - j) % p;
	                    cjr = (cjr * c[i - 1][j]) % p;
	                    if (j == i - 1 - j)
	                        cjr = (cjr * inv2) % p;
	                    dp[i][a + b + 1][1] = (dp[i][a + b + 1][1] + cjr) % p;
	                    cjr = (dp[j][a][0] * dp[i - 1 - j][b][1]) % p;
	                    cjr = (cjr * j) % p;
	                    cjr = cjr * (i - 1 - j) % p;
	                    cjr = (cjr * c[i - 1][j]) % p;
	                    if (j == i - 1 - j)
	                        cjr = (cjr * inv2) % p;
	                    dp[i][a + b + 1][1] = (dp[i][a + b + 1][1] + cjr) % p;
	                    cjr = (dp[j][a][1] * dp[i - 1 - j][b][1]) % p;
	                    cjr = (cjr * j) % p;
	                    cjr = cjr * (i - 1 - j) % p;
	                    cjr = (cjr * c[i - 1][j]) % p;
	                    if (j == i - 1 - j)
	                        cjr = (cjr * inv2) % p;
	                    dp[i][a + b][0] = (dp[i][a + b][0] + cjr) % p;
	                }
	            }
	        }
	        for (register int j = 0; j < i - 1; j++) {
	            dp[i][j + 1][1] = (dp[i][j + 1][1] + dp[i - 1][j][0] * (i - 1)) % p;
	            dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][1] * (i - 1)) % p;
	        }
	    }
	    cout << (dp[n][k][0] + dp[n][k][1]) % p << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Inui_Sana (赞：0)

orz sinsop90/bx

~~乌龟和 sinsop 结芬！！！~~

题意即数最大匹配为 $k$ 的二叉树个数。数树问题，考虑不断加入子树 dp。但是这题是二叉树，所以可以直接每次将两个并作一个转移。

考虑怎么设计状态：子树 $siz$ 肯定是要记的，然后最大匹配数也是。发现只记这两个不好转移，于是再记录当前子树根有没有选的 $0/1$ 状态。

于是设 $dp_{i,j,0/1}$ 为当前子树大小为 $i$，最大匹配为 $j$，根是/否被选。

考虑转移，首先枚举两棵子树大小 $i,p$ 及分别的最大匹配 $j,q$。先考虑合并后根没有被选，则两棵子树根都已经被选，即：

$$dp_{i+p+1,j+q,0}:=dp_{i+p+1,j+q,0}+dp_{i,j,1}\times dp_{p,q,1}\times\binom{i+p+1}{i}\times\binom{p+1}{p}$$

后面两个组合数是选定点的标号的方案数。

否则根没有被选，则两个子树至少有一个根没被选。则类似地，有：

$$dp_{i+p+1,j+q+1,1}:=dp_{i+p+1,j+q,1}+dp_{i,j,0/1}\times dp_{p,q,0/1}\times\binom{i+p+1}{i}\times\binom{p+1}{p}$$

两边不同时为 $1$。

还有一点小问题，当 $i=p$ 时会算重，此时在转移时乘上 $\dfrac{1}{2}$ 即可。

初始值为 $dp_{0,0,1}=dp_{1,0,0}=1$，$ans=\dfrac{1}{n}(dp_{n,m,0}+dp_{n,m,1})$ 因为根为 $1$。时间复杂度 $O(n^4)$。

code：

```cpp
int n,m,fac[N],ifac[N],dp[N][N][2];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int binom(int x,int y){return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	fac[0]=1;
	rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	drep(i,n-1,0)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	dp[0][0][1]=dp[1][0][0]=1;
	const int iv2=qpow(2,mod-2);
	rep(i,1,n-1)rep(j,0,i/2){
		rep(p,0,min(n-i,i))rep(q,0,p/2){//I love turtles(It's written by sinsop90!)
			int x=i==p?iv2:1;
			dp[i+p+1][j+q][0]=Mod(dp[i+p+1][j+q][0],1ll*dp[i][j][1]*dp[p][q][1]%mod*binom(i+p+1,i)%mod*binom(p+1,p)%mod*x%mod);
			dp[i+p+1][j+q+1][1]=Mod(dp[i+p+1][j+q+1][1],1ll*dp[i][j][0]*dp[p][q][0]%mod*binom(i+p+1,i)%mod*binom(p+1,p)%mod*x%mod);
			dp[i+p+1][j+q+1][1]=Mod(dp[i+p+1][j+q+1][1],1ll*dp[i][j][0]*dp[p][q][1]%mod*binom(i+p+1,i)%mod*binom(p+1,p)%mod*x%mod);
			dp[i+p+1][j+q+1][1]=Mod(dp[i+p+1][j+q+1][1],1ll*dp[i][j][1]*dp[p][q][0]%mod*binom(i+p+1,i)%mod*binom(p+1,p)%mod*x%mod);
		}
	}
	printf("%lld\n",1ll*Mod(dp[n][m][0],dp[n][m][1])*qpow(n,mod-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

