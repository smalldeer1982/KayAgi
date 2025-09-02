# Cheops and a Contest (Hard Version)

## 题目描述

这是该问题的困难版本。不同之处在于本版本中 $m$ 可以为任意值。只有在你解决了所有版本的问题后，才能 hack。

古埃及正在举行一场解题比赛，有 $n$ 名参赛者，编号从 $1$ 到 $n$。每位参赛者来自某个城市，城市编号从 $1$ 到 $m$。每个城市至少有一名参赛者。

第 $i$ 位参赛者有力量 $a_i$、专长 $s_i$ 和智慧 $b_i$，满足 $b_i \ge a_i$。比赛中的每道题目都有难度 $d$ 和唯一的话题 $t$。第 $i$ 位参赛者会解出这道题目，当且仅当：

- $a_i \ge d$，即他的力量不小于题目的难度，或者
- $s_i = t$ 且 $b_i \ge d$，即他的专长与题目的话题相同，且智慧不小于题目的难度。

Cheops 想要选择题目，使得对于所有 $i < j$，来自城市 $i$ 的每位参赛者解出的题目数量都严格多于来自城市 $j$ 的每位参赛者。

请你找出最多 $5n$ 道题目的集合，使得所有题目的话题互不相同，并满足 Cheops 的要求；或者说明这是不可能的。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 2
5 7 1
6 7 2
3 9 2
5 10 3
4 4 1
2 1 2
3 3 4 5
2 2
1 2 1
1 2 1
1 2
1 1```

### 输出

```
7
6 4
6 5
5 6
5 7
4 8
4 9
7 1
-1```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2046E2)

**题目大意**

> 给定 $n$ 个人，有属性 $(a_i,b_i,s_i)$，对于一个题目 $(d,t)$，他能做出来当且仅当 $a_i+[s_i=t](b_i-a_i)\ge d$。
>
> 已知 $n$ 个人属于 $m$ 个队，构造 $\le 5n$ 个 $t$ 不相等的题目，使得第 $i-1$ 队的每个人做出的题目数量严格大于第 $i$ 队的每个人。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

先从 $m=2$ 的情况出发。

假设第 $i$ 个队列的人的 $a$ 最小最大值为 $l_i,r_i$。

如果 $l_1>r_2$ 肯定解决了。否则我们要想办法让 $[l_1,r_2]$ 范围内第一队的人多通过一些题，这就要通过 $s_i=t$ 来实现。

此时每个人只能多通过一个题，因此 $r_2$ 不能比 $l_1$ 多过题，首先一个题目如果难度在 $(l_1,r_2]$ 范围，就会导致 $r_2$ 比 $l_1$ 多做出一题。

其次如果有一个 $[l_1,r_2]$ 范围内的第二队的人 $s_i$，那么 $t=s_i$ 的题不能使得 $d\in (l_1,b_i]$，否则这个人也会比 $l_1$ 多做出一题。

为了尽可能合法，这部分的题目肯定选择最大的合法难度。

然后我们在 $l_1,r_2+1$ 的位置分别放足够多的题（$t$ 不与任何 $s$ 相等），使得其他的人不受影响（可以证明 $2$ 题就足够完成区分）。

这样就完成了 $m=2$ 的构造。

一般的情况完全一样，只不过要求变成所有 $(l_{i-1},r_i]$ 范围内不能有题目，以及颜色为 $s_i$ 题目难度不能在 $(l_x,b_i]$ 范围内（$i$ 属于 $x+1$ 组且 $l_x\le a_i$）。

依然类似上面的过程，找到所有能放题目的位置贪心地放，最后检验是否合法即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
inline void chkmin(int &x,const int &y) { x=y<x?y:x; }
inline void chkmax(int &x,const int &y) { x=y>x?y:x; }
const int MAXN=3e5+5,inf=2e9;
int n,m,a[MAXN],b[MAXN],ty[MAXN],bl[MAXN];
int L[MAXN],R[MAXN],id[MAXN];
vector <int> g[MAXN];
void shrk(vector<array<int,2>>&vc) {
	sort(vc.begin(),vc.end());
	vector<array<int,2>> nw;
	for(auto i:vc) if(i[0]<=i[1]) {
		if(nw.empty()||i[0]>nw.back()[1]+1) nw.push_back(i);
		else chkmax(nw.back()[1],i[1]);
	}
	vc.swap(nw);
}
bool chk(const vector<array<int,2>>&vc,int &x) {
	int i=lower_bound(vc.begin(),vc.end(),array<int,2>{x+1,x+1})-vc.begin()-1;
	if(i>=0&&x<=vc[i][1]) return x=vc[i][0]-1,true;
	return false;
}
int lc[MAXN],rc[MAXN],mn[MAXN],mx[MAXN];
void solve() {
	cin>>n>>m;
	gp_hash_table <int,bool> uty;
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i]>>ty[i],uty[ty[i]]=1,id[i]=i;
	vector <array<int,2>> ban,wys;
	for(int i=1,x;i<=m;++i) {
		cin>>x,g[i].resize(x),L[i]=inf,R[i]=-inf;
		for(int &j:g[i]) cin>>j,bl[j]=i,chkmin(L[i],a[j]),chkmax(R[i],a[j]);
		if(i>1&&R[i]>L[i-1]) ban.push_back({L[i-1]+1,R[i]});
	}
	shrk(ban);
	sort(id+1,id+n+1,[&](int i,int j){ return a[i]<a[j]; });
	lc[0]=m+1,rc[n+1]=0;
	for(int i=1;i<=n;++i) lc[i]=min(lc[i-1],bl[id[i]]);
	for(int i=n;i>=1;--i) rc[i]=max(rc[i+1],bl[id[i]]);
	for(int i=2,x=0;i<=n;++i) if(a[id[i-1]]<a[id[i]]&&rc[i]<=lc[i-1]) {
		for(int o=0;o<2;++o) {
			while(uty.find(++x)!=uty.end());
			wys.push_back({a[id[i]],x});
		}
	}
	gp_hash_table <int,int> d;
	gp_hash_table <int,vector<array<int,2>>> banc;
	for(int i=1;i<m;++i) for(int j:g[i]) {
		if(a[j]<=R[i+1]) {
			if(d.find(ty[j])==d.end()) d[ty[j]]=b[j];
			else chkmin(d[ty[j]],b[j]);
		}
	}
	for(int i=2;i<=m;++i) for(int j:g[i]) {
		if(a[j]>=L[i-1]) banc[ty[j]].push_back({L[i-1]+1,b[j]});
	}
	for(auto &it:d) {
		auto &cb=banc[it.first];
		int &x=it.second; shrk(cb);
		while(chk(ban,x)||chk(cb,x));
		wys.push_back({x,it.first});
	}
	sort(wys.begin(),wys.end());
	for(int i=1;i<=m;++i) mn[i]=inf,mx[i]=-inf;
	for(int i=1;i<=n;++i) {
		int vl=lower_bound(wys.begin(),wys.end(),array<int,2>{a[i]+1,-1})-wys.begin();
		if(d.find(ty[i])!=d.end()&&a[i]<d[ty[i]]&&d[ty[i]]<=b[i]) ++vl;
		chkmin(mn[bl[i]],vl),chkmax(mx[bl[i]],vl);
	}
	bool ok=true;
	for(int i=1;i<m;++i) ok&=mn[i]>mx[i+1];
	if(!ok) cout<<"-1\n";
	else {
		cout<<wys.size()<<"\n";
		for(auto z:wys) cout<<z[0]<<" "<<z[1]<<"\n";
	}
	for(int i=1;i<=m;++i) g[i].clear();
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

