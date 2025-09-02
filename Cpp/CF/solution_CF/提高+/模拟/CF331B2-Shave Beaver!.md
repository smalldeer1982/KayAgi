# Shave Beaver!

## 题目描述

The Smart Beaver has recently designed and built an innovative nanotechnologic all-purpose beaver mass shaving machine, "Beavershave 5000". Beavershave 5000 can shave beavers by families! How does it work? Very easily!

There are $ n $ beavers, each of them has a unique id from 1 to $ n $ . Consider a permutation $ a_{1},a_{2},...,a_{n} $ of $ n $ these beavers. Beavershave 5000 needs one session to shave beavers with ids from $ x $ to $ y $ (inclusive) if and only if there are such indices $ i_{1}<i_{2}<...<i_{k} $ , that $ a_{i1}=x $ , $ a_{i2}=x+1 $ , ..., $ a_{ik-1}=y-1 $ , $ a_{ik}=y $ . And that is really convenient. For example, it needs one session to shave a permutation of beavers $ 1,2,3,...,n $ .

If we can't shave beavers from $ x $ to $ y $ in one session, then we can split these beavers into groups $ [x,p_{1}] $ , $ [p_{1}+1,p_{2}] $ , ..., $ [p_{m}+1,y] $ $ (x<=p_{1}<p_{2}<...<p_{m}<y) $ , in such a way that the machine can shave beavers in each group in one session. But then Beavershave 5000 needs $ m+1 $ working sessions to shave beavers from $ x $ to $ y $ .

All beavers are restless and they keep trying to swap. So if we consider the problem more formally, we can consider queries of two types:

- what is the minimum number of sessions that Beavershave 5000 needs to shave beavers with ids from $ x $ to $ y $ , inclusive?
- two beavers on positions $ x $ and $ y $ (the beavers $ a_{x} $ and $ a_{y} $ ) swapped.

You can assume that any beaver can be shaved any number of times.

## 样例 #1

### 输入

```
5
1 3 4 2 5
6
1 1 5
1 3 4
2 2 3
1 1 5
2 1 5
1 1 5
```

### 输出

```
2
1
3
5
```

# 题解

## 作者：WYZ20030051 (赞：0)

题意如翻译所说，但是要注意不要读错题了。这里的操作一指的是求值域在 $[x,y]$ 之间的数组成的序列中有多少连续子序列，操作二的交换操作指的是交换下标所对应的数字。

------------

对于一次查询，实际上我们要找的是该子序列中的“转折点”的数量，转折点即满足 $a_i>a_{i+1}$ 的点 $i$，且转折点将询问给的子序列分隔成了若干个上升子序列段。

为了方便起见，假设每个上升子序列段的最右侧都是转折点，那么除了最后一段子序列外其他子序列的转折点都是很好处理的，接下来看最后一段子序列的转折点如何处理。由于每次查询给定的序列是值域在 $[x,y]$ 的数字构成的子序列，所以我们所定义的转折点可能会大于最后一段子序列的右端点，但是如果最后一段子序列的转折点就是 $y$，那么该转折点对答案仍是有贡献的，这里需要特判一下。

修改操作很简单，不难发现当 $x$ 的位置发生变化时，仅对 $x-1$，$x$ 和 $x+1$ 三个数有影响，本质上是单点修改。

上述操作只需要能支持区间查询单点修改的数据结构维护就可以了。

------------

### CODE
```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
#define lowbit(x) x&(-x)
int read()
{
    ll now = 0, nev = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            nev = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        now = (now << 1) + (now << 3) + (c & 15);
        c = getchar();
    }
    return now * nev;
}
const int MAXN = 1e6 + 10;
const int mod = 998244353;
int n,m;
int a[MAXN],id[MAXN];
int c[MAXN];
void add(int x,int v)
{
	while(x<=n)
	{
		c[x]+=v;
		x+=lowbit(x);
	}
}
int ask(int x)
{
	int res=0;
	while(x)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int query(int x,int y)
{
	return ask(y)-ask(x-1);
}
void modefy(int x,int y)
{
	if(x<1 || y>n)
		return;
	if(query(x,x))
	{
		if(id[x]<id[y])
			add(x,-1);
	}
	else
	{
		if(id[x]>id[y])
			add(x,1);
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),id[a[i]]=i;
	for(int i=1;i<=n;i++) 
	{
		if(id[i]>id[i+1])
			add(i,1);
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		int op=read(),x=read(),y=read();
		if(op==1)
		{
			int ans=query(x,y);
			if(!query(y,y))
				ans++;
			printf("%lld\n",ans);
		}
		if(op==2)
		{
			swap(id[a[x]],id[a[y]]);
			swap(a[x],a[y]);
			modefy(a[x]-1,a[x]);modefy(a[x],a[x]+1);
			modefy(a[y]-1,a[y]);modefy(a[y],a[y]+1);
		}
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

区间连续上升子段划分，考虑枚举断点，当 $a_i$ 的位置大于 $a_i+1$ 的位置时，一定会出现一个新段。交换两个元素便维护变化量，树状数组即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,q;
int a[300005];
int p[300005];
struct BIT{
	int tree[300005];
	int lowbit(int i){return i&-i;}
	void add(int pos,int val){
		for(int i=pos;i<=n;i+=lowbit(i))tree[i]+=val;
	}
	int ask(int l,int r){
		int ans=0;
		for(int i=r;i;i-=lowbit(i))ans+=tree[i];
		for(int i=l-1;i;i-=lowbit(i))ans-=tree[i];
		return ans;
	}
}T;
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),p[a[i]]=i;
	for(int i=1;i<n;i++)if(p[i]>=p[i+1])T.add(i,1);
	a[n+1]=n+1;
	p[n+1]=n+1;
	q=read();
	while(q--){
		int opt=read();
		if(opt==2){
			int x=read(),y=read();
			if(a[x]>a[y])swap(x,y);
			if(p[a[x]]>=p[a[x]+1])T.add(a[x],-1);
			if(p[a[x]-1]>=p[a[x]])T.add(a[x]-1,-1);
			if(p[a[y]]>=p[a[y]+1])T.add(a[y],-1);
			if(a[y]-1!=a[x]&&p[a[y]-1]>=p[a[y]])T.add(a[y]-1,-1);
			swap(p[a[x]],p[a[y]]);
			swap(a[x],a[y]);
			swap(x,y);
			if(p[a[x]]>=p[a[x]+1])T.add(a[x],1);
			if(p[a[x]-1]>=p[a[x]])T.add(a[x]-1,1);
			if(p[a[y]]>=p[a[y]+1])T.add(a[y],1);
			if(a[y]-1!=a[x]&&p[a[y]-1]>=p[a[y]])T.add(a[y]-1,1);
		}else{
			int l=read(),r=read();
			cout<<T.ask(l,r-1)+1<<"\n";
		}
	}
} 
```

---

## 作者：qinhuanmma (赞：0)

由于给出的是一个排列，选考虑把每个数的位置记下来，设 $pos_{a_i}=i$。  
容易注意到询问 $[l,r]$ 的答案就是 $pos_l$ 到 $pos_{r-1}$ 中 $pos_i>pos_{i+1}$ 的个数 $+1$。  
注意到是单点修改，预处理完用线段树维护一下变化量即可。  
code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300010;
namespace cza{
	struct Segment_Tree{
		int t[N << 2];
		#define ls(p) (p << 1)
		#define rs(p) (p << 1 | 1)
		void push_up(int p){
			t[p] = t[ls(p)] + t[rs(p)];
		}
		void upd(int p, int l, int r, int x, int v){
			t[p] = v;
			if(l == r) return ;
			int mid = (l + r) >> 1;
			if(x <= mid) upd(ls(p), l, mid, x, v);
			else upd(rs(p), mid + 1, r, x, v);
			push_up(p);
		}
		int find(int p, int l, int r, int nl, int nr){
			if(nr < nl) return 0;
			if(nl <= l and r <= nr) return t[p];
			int mid = (l + r) >> 1, ret = 0;
			if(nl <= mid) ret += find(ls(p), l, mid, nl, nr);
			if(mid < nr) ret += find(rs(p), mid + 1, r, nl, nr);
			return ret;
		}
	}t;
	int n, m;
	int a[N];
	int pos[N];
	void init(){
		for(int i = 1; i <= n - 1; i++){
			if(pos[i] > pos[i + 1]) t. upd(1, 1, n, i, 1);
		}
	}
	int main(){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			pos[a[i]] = i;
		}
		init();
		scanf("%d", &m);
		for(int i = 1, op, x, y; i <= m; i++){
			scanf("%d%d%d", &op, &x, &y);
			if(op == 1){
				printf("%d\n", t. find(1, 1, n, x, y - 1) + 1);
			}else{
				t. upd(1, 1, n, a[x] - 1, 0);
				t. upd(1, 1, n, a[x], 0);
				t. upd(1, 1, n, a[y] - 1, 0);
				t. upd(1, 1, n, a[y], 0);
				swap(pos[a[x]], pos[a[y]]);
				swap(a[x], a[y]);
				if(a[x] - 1 >= 1 and pos[a[x] - 1] > pos[a[x]]) t. upd(1, 1, n, a[x] - 1, 1);
				if(a[x] + 1 <= n and pos[a[x]] > pos[a[x] + 1]) t. upd(1, 1, n, a[x], 1);
				if(a[y] - 1 >= 1 and pos[a[y] - 1] > pos[a[y]]) t. upd(1, 1, n, a[y] - 1, 1);
				if(a[y] + 1 <= n and pos[a[y]] > pos[a[y] + 1]) t. upd(1, 1, n, a[y], 1);
			}
		}
		return 0;
	}
}
int main(){
	return cza::main();
}
```

---

