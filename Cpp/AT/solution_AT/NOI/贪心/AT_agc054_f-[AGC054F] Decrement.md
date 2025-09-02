# [AGC054F] Decrement

## 题目描述

给长度为 $N$ 和 $N-1$ 的正整数序列 $A$ 和 $B$，你可以进行以下操作任意次。

* 选择整数 $i$ 和 $j$($1\le i<j\le N$)，将 $A_i,A_j,B_i,B_{i+1}...B_{j-1}$ 减一。需要保证操作后不会出现负数。

令 $m$ 为可以执行的操作的次数的最大值，求出 $m$ 次操作后有多少种本质不同的序列 $A$（对 998244353 取模）。

* $1\le n\le 2\times 10^5$
* $1\le A_i\le 10^9$
* $1\le B_i\le 10^9$

## 样例 #1

### 输入

```
3
1 2 2
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 1 1 1
2 2 2```

### 输出

```
1```

## 样例 #3

### 输入

```
4
2 2 3 4
3 1 4```

### 输出

```
3```

# 题解

## 作者：UltiMadow (赞：1)

记 $a_i$ 为 $A_i$ 最终删除了多少，$b_i$ 为 $B_i$ 最终删除了多少，不妨设 $a_0=b_0=a_{n+1}=b_n=0$

结论：数列 $a,b$ 合法当且仅当对于任意 $i$ 有 $2| a_i+b_i+b_{i-1}$ 且 $\max\{a_i,b_i,b_{i-1}\}\le \frac{a_i+b_i+b_{i-1}}{2}$

证明：先证必要性，显然一次操作 $[l,r]$ 会把 $a_l,b_l$ 减去 $1$，$a_r,b_{r-1}$ 减去 $1$，$b_i,b_{i-1}(i\in(l,r))$ 减去 $1$，即一次操作会对 $[l,r]$ 中所有位置的 $a_i,b_i,b_{i-1}$ 中的两个减去 $1$，显然需要满足上述条件

下证充分性，考虑构造出一组合法的操作，每次选出一对相邻的满足 $a_i=b_i+b_{i-1}$ 的位置操作，显然操作之后仍然合法，由于序列两端一定满足条件，所以一定可以选出这样的一对位置

回到原题，考虑先调整一下 $A_i$ 和 $B_i$

若 $B_i>A_i+B_{i-1}$ 则可以令 $B_i=A_{i}+B_{i-1}$，显然这不会影响答案，对 $B_{i-1}$ 同理

这一步可以用最短路在 $\mathcal O(n\log n)$ 的时间内解决

若 $A_i\ge B_i+B_{i-1}$，则可以把原问题分成 $[1,i]$ 和 $[i,n]$ 两个子问题，前一个子问题中令 $A_i=B_{i-1}$，后一个子问题中令 $A_i=B_i$，这也不会影响答案

此时只需要考虑 $|B_{i}-B_{i-1}|\le A_i<B_i+B_{i-1}$ 的情况，我们想要最大化 $\sum a_i$

记 $f_i$ 为 $a_1,\dots,a_i$ 全部取 $A_1,\dots,A_i$ 时 $b_i$ 的取值范围，假设我们确定了 $b_{i-1}$，则此时 $f_{i}=\{x|x\in[|A_i-b_{i-1}|,\min\{A_i+b_{i-1},B_i\}],x\equiv A_i+b_{i-1}\pmod 2\}$

不难发现 $f_i$ 一定是一个区间限制和一个奇偶性限制的形式，且区间右端点为 $B_i$，那么很容易可以通过 $f_{i-1}$ 推到 $f_i$

由于在序列右端点有 $B_i=0,A_i=B_{i-1}$，所以 $f_n$ 的区间限制为 $[0,0]$，此时若 $2|\sum A_i$ 则有 $f_n$ 的奇偶性限制也为 $0$，即 $a_1,\dots,a_n$ 取 $A_1,\dots,A_n$ 是合法的；否则 $a_1,\dots,a_n$ 取 $A_1,\dots,A_{n-1},A_n-1$ 也是合法的

综上，$2|\sum A_i$ 时 $\sum a_i$ 最大取到 $\sum A_i$，方案数为 $1$；$2\not|\sum A_i$ 时 $\sum a_i$ 最大取到 $(\sum A_i)-1$，我们只需要求出此时有多少个位置 $i$ 取 $A_i-1$ 时合法

记 $g_i$ 为 $a_i,\dots,a_n$ 全部取 $A_i,\dots,A_n$ 时 $b_{i-1}$ 的取值范围，我们可以用和 $f$ 一样的方式从 $g_{i+1}$ 推到 $g_i$

此时对于一个位置 $i$，我们可以通过同样的转移方法合并 $f_{i-1}$ 和 $g_{i+1}$ 得到 $a_1,\dots,a_{i-1},a_{i+1},\dots,a_{n}$ 全部取 $A_1,\dots,A_{i-1},A_{i+1},\dots,A_n$ 时 $a_i$ 的取值范围，现在只需要判断 $A_i-1$ 是否在这个取值范围内即可

时间复杂度 $\mathcal O(n\log n)$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
#define p 998244353
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
int n,a[MAXN],b[MAXN];
priority_queue<pii>Q;
int vis[MAXN];
void dijkstra(){
	for(int i=0;i<=n;i++)Q.push(mp(-b[i],i));
	while(!Q.empty()){
		int u=Q.top().se;Q.pop();
		if(vis[u])continue;vis[u]=1;
		if(b[u-1]>a[u]+b[u])b[u-1]=a[u]+b[u],Q.push(mp(-b[u-1],u-1));
		if(b[u+1]>a[u+1]+b[u])b[u+1]=a[u+1]+b[u],Q.push(mp(-b[u+1],u+1));
	}
}
struct qnode{
	int l,r,par;
	qnode(int ql=0,int qr=0,int x=0){l=ql;r=qr;par=x;}
	void check(){if((l&1)^par)l++;if((r&1)^par)r--;}
}f[MAXN],g[MAXN];
qnode operator+(qnode a,qnode b){
	qnode ret;ret.r=a.r+b.r;ret.par=a.par^b.par;
	if(max(a.l,b.l)<=min(a.r,b.r))ret.l=ret.par;
	else ret.l=min(abs(a.l-b.r),abs(a.r-b.l));
	return ret;
}
int solve(int l,int r){
	int sum=0;
	for(int i=l;i<=r;i++)sum^=(a[i]&1);
	if(!sum)return 1;
	f[l-1]=qnode(0,0,0);
	for(int i=l;i<=r;i++){
		f[i]=f[i-1]+qnode(a[i],a[i],a[i]&1);
		f[i].r=min(f[i].r,b[i]);f[i].check();
	}
	g[r+1]=qnode(0,0,0);
	for(int i=r;i>=l;i--){
		g[i]=g[i+1]+qnode(a[i],a[i],a[i]&1);
		g[i].r=min(g[i].r,b[i-1]);g[i].check();
	}int ret=0;
	for(int i=l;i<=r;i++){
		auto now=f[i-1]+g[i+1];
		if(((a[i]&1)^now.par)&&now.l<=a[i]-1&&a[i]-1<=now.r)ret++;
	}return ret;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<n;i++)scanf("%lld",&b[i]);
	dijkstra();int ans=1;
	for(int i=1,pre=1;i<=n;i++){
		if(a[i]<b[i-1]+b[i])continue;
		a[i]=b[i-1];ans=ans*solve(pre,i)%p;
		a[i]=b[i];pre=i;
	}
	printf("%lld",ans);
	return 0;
}
```

---

