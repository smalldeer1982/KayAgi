# [ARC044B] 最短路問題

## 题目描述

一个图有 $n$ 个顶点，每条边长度为 $1$，没有重边，满足从顶点 $1$ 到顶点 $i$ 的最短距离为 $A_i$。

计算符合条件的图总数。

------------

## 样例 #1

### 输入

```
4
0 1 1 2```

### 输出

```
6```

## 样例 #2

### 输入

```
4
0 1 2 0```

### 输出

```
0```

## 样例 #3

### 输入

```
3
1 1 2```

### 输出

```
0```

## 样例 #4

### 输入

```
17
0 1 1 2 2 4 3 2 4 5 3 3 2 1 5 4 2```

### 输出

```
855391686```

# 题解

## 作者：dapingguo8 (赞：1)

### 题意

给定一个长度为 $n$ 的数组 $a$，计算包含 $n$ 个点且满足以下条件的无向无边权简单图的个数，对 $10^9+7$ 取模：

- $1$ 号点至 $i$ 号点的最短路长度为 $a_i$。

$1\le n \le 10^5,0\le a_i \le n-1$

#### Solution

由于没有边权，考虑类似 bfs 的分层。令第 $i$ 个点位于第 $a_i$ 层，定义层数最深的节点位于第 $mx$ 层。

对于连边，不难得出以下规则：

- 一条边连接的两个点只能位于同一层或相邻层。（否则不满足 bfs 的规则）

- 同一层的节点间连边没有限制。
- 位于第 $i$ $(i\ge1)$ 层的点需要与至少一个第 $i-1$ 层的节点连边。

定义 $cnt_i$ 为第 $i$ 层包含的节点个数。我们分别计算同层节点连边的方案数和相邻层节点连边的方案数：

- 同层连边：第 $i$ 层的 $cnt_i$ 个节点间共有 $\dfrac{cnt_i\times (cnt_i-1)}{2}$ 条不同的边，每条边可以选择连或不连，共 $2^\frac{cnt_i\times (cnt_i-1)}{2}$ 种方案。所有层的同层节点连边方案总数为 $\prod\limits_{i=0}^{mx}2^{\frac{cnt_i\times (cnt_i-1)}{2}}$。

- 相邻层连边：第 $i$ $(i\ge1)$ 层每个节点需要与第 $i-1$ 层的 $cnt_{i-1}$ 个节点中的至少一个节点连边，单个节点连边方案数为 $2^{cnt_{i-1}}-1$，那么 $cnt_i$ 个节点连边的总方案数为 $(2^{cnt_{i-1}}-1)^{cnt_i}$。所有层的相邻层节点连边总方案数为 $\prod\limits_{i=1}^{mx}(2^{cnt_{i-1}}-1)^{cnt_i}$

总方案数为两种连边方案数的乘积，即 $\prod\limits_{i=0}^{mx}2^{\frac{cnt_i\times (cnt_i-1)}{2}}\prod\limits_{i=1}^{mx}(2^{cnt_{i-1}}-1)^{cnt_i}$。

当然需要将以下情况的答案特判为 $0$：

- $a_1>0$。（显然 $1$ 号点至 $1$ 号点的距离必须为 $0$。）
- 存在 $a_i=0$ 且 $i>1$。（显然 $1$ 号点至其他点的距离至少为 $1$。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;

struct mint{
	int v;
	mint qpow(mint p,int k){
		mint ans=1,b=p;
		while(k){
			if(k&1){
				ans*=b;
			}
			b*=b;
			k>>=1;
		}
		return ans;
	}
	mint inv(mint p){
		return qpow(p,mod-2);
	}
	mint(int V=0){
		v=V;
	}
	void operator =(int p){
		v=p%mod;
	}
	mint operator +(int p){
		return mint{(v+p)%mod};
	}
	mint operator +(mint p){
		return mint{(v+p.v)%mod};
	}
	mint operator -(int p){
		p%=mod;
		return mint{(v+mod-p)%mod};
	}
	mint operator -(mint p){
		return mint{(v+mod-p.v)%mod};
	}
	mint operator *(int p){
		p%=mod;
		return mint{(v*p)%mod};
	}
	mint operator *(mint p){
		return mint{(v*p.v)%mod};
	}
	mint operator /(int p){
		mint w=p;
		return inv(w)*v;
	}
	mint operator /(mint p){
		return inv(p)*v;
	}
	void operator +=(int p){
		v=(v+p)%mod;
	}
	void operator +=(mint p){
		v=(v+p.v)%mod;
	}
	void operator -=(int p){
		p%=mod;
		v=(v+mod-p)%mod;
	}
	void operator -=(mint p){
		v=(v+mod-p.v)%mod;
	}
	void operator *=(int p){
		p%=mod;
		v=(v*p)%mod;
	}
	void operator *=(mint p){
		v=(v*p.v)%mod;
	}
	void operator /=(int p){
		mint w=v,q=p;
		v=(w/q).v;
	}
	void operator /=(mint p){
		mint w=v;
		v=(w/p).v;
	}
	void output(bool line){
		cout<<v<<' ';
		if(line)cout<<endl;
	}
};
mint qpow(mint p,int k){
		mint ans=1,b=p;
		while(k){
			if(k&1){
				ans*=b;
			}
			b*=b;
			k>>=1;
		}
		return ans;
	}
mint ans=1;
int n,a[100005],cnt[100005],mx;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i>1 and !a[i]){
			cout<<0<<endl;
			return 0;
		}
		cnt[a[i]]++;
		mx=max(mx,a[i]);
	}
	if(a[1]){
		cout<<0<<endl;
		return 0;
	}
	for(int i=1;i<=mx;i++){
		ans*=(qpow(qpow(mint(2),cnt[i-1])-1,cnt[i])*(qpow(mint(2),cnt[i]*(cnt[i]-1)/2)));
	}
	cout<<ans.v<<endl;
}
```



---

## 作者：_Kenma_ (赞：0)

# arc044_b 解题报告

## 前言

因为没有输出换行被控了。

看起来题解中并没有容斥的做法。

## 思路分析

可以想象建立最短路树。

设 $f_i$ 表示最短路树到第 $i$ 层，所有图的个数。

发现最短路树的同层之间可以随便连边，不同层之间只有相邻层可以连边，并且连边会有限制。

设 $cnt_i$ 表示第 $i$ 层的节点个数，$g_i$ 表示 $i-1$ 层向第 $i$ 层连边的合法方案数，则有：

$$f_i=f_{i-1} \cdot 2^{\frac{cnt_i \cdot (cnt_i-1)}{2}} \cdot g_i$$

考虑怎样计算 $g_i$。

注意到一个方案合法，当且仅当第 $i$ 层的全部点都和 $i-1$ 点有连边。

发现可以容斥解决这个问题。

具体地，合法方案数为：第 $i$ 层全部和 $i-1$ 层连边 - 至少有一个没有和 $i-1$ 层连边 + 至少有两个和 $i-1$ 层连边……

至少有 $j$ 个点没有和上一层连边的方案，我们可以先指定这 $j$ 个点不连，然后其他的点随便连。

这样就可以列出柿子：

$$g_i =\sum_{j=0}^{cnt_i} (-1)^j \cdot \binom{cnt_i}{j}\cdot 2^{cnt_{i-1}\cdot(cnt_i-j)}$$

然后就做完了，使用快速幂和预处理阶乘，复杂度为 $O(n\log v)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,d,maxn,cnt[100005],f[100005],g[100005],fac[100005];
int binpow(int a,int b){
	if(b==0) return 1;
	int res=binpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod;
}
int C(int n,int m){
	return fac[n]*binpow(fac[n-m],mod-2)%mod*binpow(fac[m],mod-2)%mod; 
}
signed main(){
	//freopen("data.in","r",stdin);
	//freopen("WA.out","w",stdout); 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	for(int i=1;i<=n;i++){
		cin>>d;
		if(i==1 && d){
			cout<<0<<endl;
			return 0;
		}
		cnt[d]++;
		maxn=max(maxn,d);
	}
	if(cnt[0]>1){
		cout<<0<<endl;
		return 0;
	}
	for(int i=1;i<=maxn;i++){
		for(int j=0;j<=cnt[i];j++){
			g[i]=(g[i]+(j&1?-1:1)*C(cnt[i],j)*binpow(2,cnt[i-1]*(cnt[i]-j))+mod)%mod;
		}
	}
	f[0]=1;
	for(int i=1;i<=maxn;i++){
		f[i]=f[i-1]*binpow(2,cnt[i]*(cnt[i]-1)/2)%mod*g[i]%mod;
	} 
	cout<<f[maxn]<<endl;
	return 0;
}

```

主要注意特判无解的情况。

## 后记

一道锻炼推柿子的好题。

---

## 作者：Crosser (赞：0)

## [ARC044B] 最短路問題

### Preface

那我缺的英文题面这块谁给我补啊。

$\text{*1400, Comb.}$

### Solution

样例二，三表示了两种平凡的判 $0$ 条件。

显然考虑分层图。如果第 $i$ 层有 $a_i$ 个点，我们只能连接两种边，一种是同层互联边，这就有 $\frac12a_i(a_i-1)$ 条可以任意选择连或者不连，另外一种是连到上一层的，注意每个点都必须连到上一层，所以不能选空集，因此有 $(2^{a_{i-1}}-1)^{a_i}$ 种。

全部乘起来就行了，复杂度是 $\mathcal O(n\log^2P)$。

代码自己写。

---

