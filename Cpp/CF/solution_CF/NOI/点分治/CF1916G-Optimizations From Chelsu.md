# Optimizations From Chelsu

## 题目描述

给定一棵包含 $n$ 个节点的树，节点编号从 $1$ 到 $n$。每条边标有一个整数权值 $w_i$。

定义 $len(u, v)$ 为节点 $u$ 到 $v$ 的简单路径上的边数，$g(u, v)$ 为 $u$ 到 $v$ 的简单路径上所有边权值的最大公约数。特别地，对于任意 $1 \leq u \leq n$，规定 $len(u, u) = 0$ 且 $g(u, u) = 0$。

请计算所有节点对 $(u, v)$ 中 $len(u, v) \cdot g(u, v)$ 的最大值。

## 样例 #1

### 输入

```
4
2
1 2 1000000000000
4
3 2 6
2 1 10
2 4 6
8
1 2 12
2 3 9
3 4 9
4 5 6
5 6 12
6 7 4
7 8 9
12
1 2 12
2 3 12
2 4 6
2 5 9
5 6 6
1 7 4
4 8 12
8 9 4
8 10 12
2 11 9
7 12 9```

### 输出

```
1000000000000
12
18
24```

# 题解

## 作者：honglan0301 (赞：25)

## 题目做法

描述一下官方题解的做法：路径问题考虑点分。首先只考虑每个分治重心直上直下的链算一遍答案 $ans_0$，由 $\min\{\gcd(rt,u),\gcd(rt,v)\}\ge \gcd(u,v)$ 可以知道 $ans\leq 2ans_0$。

然后据此再点分一遍，只考虑 $2\times len(rt,u)\times \gcd(rt,u)\ge ans_0$ 的链即可，注意到能更新答案的两条链（不妨设 $len(rt,u)\leq len(rt,v)$）一定满足：

1. $\gcd(rt,v)\mid\gcd(rt,u)$（否则只保留较长者不劣）。

2. $\gcd(rt,u)\leq len(rt,u)\times\gcd(rt,u)$（否则只保留 $\gcd$ 大者不劣）。

那么 std 声称，对每种 $\gcd=g$ 的链保留最大与次大（不同子树）的 $len$，若其有可能更新答案，则依次枚举另一条 $\gcd\in \{g,2g,\dots,len\times g\}$ 的最长链更新答案就能通过本题。

## 复杂度分析

谴责一下：赛前分析不出来 std 的复杂度就敢出题实在太逆天了。

赛后官方题解给出了 $O(n\sqrt n\log n)$ 的巨大上界，但事实上有人教我了如何分析出 $O(n\log^2 n)$ 的优秀时间复杂度，即下面我们要证明每层点分的枚举量为 $O(n\log n)$。

对于一个 $size=sz$ 的点分重心 $rt$，记 $dep_u=len(rt,u),mdep_u=\max \{dep_v|v\in subtree_u\}$。我们把所有满足 $dep_i=2^k,mdep_i\ge 2^{k+1}$的点称作关键点，并将每个点 $i$ 按照其祖先中 $dep=2^{\lfloor\log_2(dep_i)\rfloor-1}$ 的关键点 $u$ 分为若干组，每组点记作 $S(u,dep_u,\gcd(rt,u))$。

此时容易发现每个点都恰属于一组，且形如 $S(u,2^k,g)$ 的组不超过 $\dfrac{s}{2^k}$ 个。

又对于每个 $i\in S(u,2^k,g)$，其只有当 $\gcd(rt,i)> \dfrac{g}{4}$ 时才需要被枚举（否则取 $u$ 作为链的端点不劣，因为 $dep_u>\dfrac{dep_i}{4}$）——而这意味着每组内需要被枚举的点只有 $O(1)$ 个。故每个 $S(u,2^k,g)$ 只会造成枚举 $O(d)$ 的枚举量，故由前文可知每种 $k$ 仅会造成 $O(n)$ 的枚举量，于是每层总枚举量 $O(n\log n)$，这与预处理 $\gcd$ 的时间复杂度相同。

于是得到总时间复杂度 $O(n\log^2n)$，可以通过本题。

---

## 作者：ForgotMe (赞：2)

本题解仅为高赞题解的详细介绍，想看简述版的请移步高赞题解。

非常神奇的点分治题目。

初看这题如果直接点分治根本做不了，边权太大了，直接枚举 $\gcd$，复杂度直接爆掉。

考虑一个非常神奇的想法，设点分治的分治重心为 $rt$，先只求出所有 $len(rt,u)\times \gcd(rt,u)$ 的最大值，设其为 $mx$。

显然最优解是两条链的拼接，不如设拼接的两条链的 $len,\gcd$ 分别是 $l_1,g_1$，$l_2,g_2$，并强制令 $l_1g_1\ge l_2g_2$。

- 性质 $1$：在最优解中，一定有 $g_1\mid g_2$，$l_2\le l_1$，或者 $g_2\mid g_1$，$l_1\le l_2$。

Proof：

分类讨论一下。

如果 $g_1>g_2$，当 $g_2\nmid g_1$ 时，由最大公约数的性质可知 $\gcd(g_2,g_1)\le \dfrac{g_2}{2}$，那么 $(l_1+l_2)\gcd(g_2,g_1)\le \dfrac{l_1g_1}{2}+\dfrac{l_2g_2}{2}\le l_1g_1$，也就是说这个时候拼接后只会变得更劣。当 $g_2\mid g_1$ 时，$(l_1+l_2)\gcd(g_2,g_1)=(l_1+l_2)g_2\le (l_1+l_2)\dfrac{g_1}{2}$，如果 $l_2<l_1$，那么会有 $(l_1+l_2)\dfrac{g_1}{2}\le l_1g_1$，同样得出拼接后只会变得更劣。

如果 $g_1\le g_2$，当 $g_1\nmid g_2$ 时，类比上面的情况同样可以得出拼接后更劣的结论。$g_1|g_2$ 的情况证明也是相似的。

- 性质 $2$：在最优解中，如果 $g_1|g_2,l_2\le l_1$，那么一定有 $l_1g_1\ge \frac{mx}{2}$，如果 $g_2|g_1,l_1\le l_2$，那么一定有 $l_2g_2\ge \frac{mx}{2}$。

Proof：两种情况是相似的，只说 $g_1|g_2,l_2\le l_1$ 的情况，注意到 $(l_1+l_2)\gcd(g_1,g_2)= l_1g_1+l_2g_1\le 2l_1g_1$，如果 $l_1g_1<\dfrac{mx}{2}$，那么拼起来的链的权值肯定比 $mx$ 小，不可能成为答案。

有了这两个性质，就有了官方题解的做法。

考虑在点分治时，对于每个 $v$ 保留 $\gcd=v$ 的最长链，次长链（要求不同子树），然后直接枚举其最长链/次长链做为 $l_1,g_1$（必须满足 $l_1g_1\ge \frac{mx}{2}$），暴力枚举 $g_1$ 的倍数 $kg_1(k\le l_1)$ 作为 $g_2$，更新答案即可。

时间复杂度见高赞题解，写得非常详细，可以证明这个算法的复杂度是 $\mathcal{O}(n\log^2 n)$（实际上如果用 map 的话是 $\mathcal{O}(n\log^3 n)$ 的，但是也能过）。

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<int,LL>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	Invn[0]=Invn[1]=1;
	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int n,maxs[100005],siz[100005];
LL mx,res;
struct node{
	int to;LL w;
};
vector<node>G[100005];
bool vis[100005];
inline void getroot(int u,int fa,int &rt,int Size){
	siz[u]=1,maxs[u]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		getroot(v,u,rt,Size);
		siz[u]+=siz[v];
		maxs[u]=max(maxs[u],siz[v]);
	}
	maxs[u]=max(maxs[u],Size-siz[u]);
	if(maxs[u]<maxs[rt])rt=u;
}
inline void GetSize(int u,int fa,int &Size){
	Size++;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		GetSize(v,u,Size);
	}
}
inline void dfs2(int u,int fa,int len,LL val){
	mx=max(mx,1ll*val*len);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		dfs2(v,u,len+1,__gcd(val,G[u][i].w));
	}
}
inline void dfs(int u){
	dfs2(u,0,0,0);
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(vis[v])continue;
		int rt=0,Size=0;
		GetSize(v,u,Size);
		getroot(v,u,rt,Size);
		dfs(rt);
	}
}
map<LL,pp>H[2];
map<LL,int>buc;
inline void redfs2(int u,int fa,int len,LL val){
	buc[val]=max(buc[val],len);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		redfs2(v,u,len+1,__gcd(val,G[u][i].w));
	}
}

inline void ins(LL x,int y,int v){
	if(y>H[0][x].first){
		H[1][x]=H[0][x];
		H[0][x]=pp(y,v);
	}else if(y>H[1][x].first)H[1][x]=pp(y,v);
}
inline void calc_ans(int u){
	H[0].clear(),H[1].clear();
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(vis[v])continue;
		buc.clear();
		redfs2(v,u,1,G[u][i].w);
		for(auto it:buc)
			ins(it.first,it.second,v);
	}
	for(auto it:H[0]){
		LL x=it.first;
		pp v=it.second;
		if(1ll*x*v.first>=mx/2){
			for(int j=1;j<=v.first;j++){
				LL now=1ll*j*x;
				if(H[0][now].second==v.second)res=max(res,1ll*x*(v.first+H[1][now].first));
				else res=max(res,1ll*x*(v.first+H[0][now].first));
			}
		}
	}
	for(auto it:H[1]){
		LL x=it.first;
		pp v=it.second;
		if(1ll*x*v.first>=mx/2){
			for(int j=1;j<=v.first;j++){
				LL now=1ll*j*x;
				if(H[0][now].second==v.second)res=max(res,1ll*x*(v.first+H[1][now].first));
				else res=max(res,1ll*x*(v.first+H[0][now].first));
			}
		}
	}
}
inline void redfs(int u){
	calc_ans(u);
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(vis[v])continue;
		int rt=0,Size=0;
		GetSize(v,u,Size);
		getroot(v,u,rt,Size);
		redfs(rt);
	}
}
inline void solve(){
	res=mx=0;
	gi(n);
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=1;i<n;i++){
		int u,v;LL w;
		gi(u),gi(v),gi(w);
		G[u].push_back(node{v,w});
		G[v].push_back(node{u,w});
	}
	maxs[0]=1e9;
	for(int i=1;i<=n;i++)vis[i]=0;
	dfs(1);
	res=mx;
	for(int i=1;i<=n;i++)vis[i]=0;
	redfs(1);
	pi(res);
}
signed main(){
	int t;
	gi(t);
	while(t--)solve();
	return 0;
}
```

---

