# 题目信息

# Sereja and Array

## 题目描述

Sereja has got an array, consisting of $ n $ integers, $ a_{1},a_{2},...,a_{n} $ . Sereja is an active boy, so he is now going to complete $ m $ operations. Each operation will have one of the three forms:

1. Make $ v_{i} $ -th array element equal to $ x_{i} $ . In other words, perform the assignment $ a_{vi}=x_{i} $ .
2. Increase each array element by $ y_{i} $ . In other words, perform $ n $ assignments $ a_{i}=a_{i}+y_{i} $ $ (1<=i<=n) $ .
3. Take a piece of paper and write out the $ q_{i} $ -th array element. That is, the element $ a_{qi} $ .

Help Sereja, complete all his operations.

## 样例 #1

### 输入

```
10 11
1 2 3 4 5 6 7 8 9 10
3 2
3 9
2 10
3 1
3 10
1 1 10
2 10
2 10
3 1
3 10
3 9
```

### 输出

```
2
9
11
20
30
40
39
```

# AI分析结果

### 题目内容
# Sereja和数组

## 题目描述
Sereja有一个由$n$个整数组成的数组$a_{1},a_{2},...,a_{n}$ 。Sereja是个活跃的男孩，所以他现在要完成$m$次操作。每次操作将有以下三种形式之一：
1. 使第$v_{i}$个数组元素等于$x_{i}$。换句话说，执行赋值$a_{vi}=x_{i}$。
2. 将每个数组元素增加$y_{i}$。换句话说，执行$n$次赋值$a_{i}=a_{i}+y_{i}$  ($1\leq i\leq n$)。
3. 拿出一张纸，写出第$q_{i}$个数组元素。即元素$a_{qi}$ 。
帮助Sereja完成他所有的操作。

## 样例 #1
### 输入
```
10 11
1 2 3 4 5 6 7 8 9 10
3 2
3 9
2 10
3 1
3 10
1 1 10
2 10
2 10
3 1
3 10
3 9
```
### 输出
```
2
9
11
20
30
40
39
```
### 算法分类
模拟

### 综合分析与结论
这些题解主要有两种思路，一种是暴力模拟结合优化，另一种是使用线段树、树状数组等数据结构。暴力模拟优化思路是用一个变量记录整体增加的值，修改时减去该值，查询时加上该值，降低时间复杂度。使用线段树、树状数组则利用数据结构特性，在$O(log n)$时间内完成区间修改和单点查询。暴力模拟优化实现简单，代码可读性好；线段树、树状数组适合大数据量，时间复杂度更优，但代码复杂。

### 所选的题解
 - **作者：幽界の冥神 (5星)**
    - **关键亮点**：思路清晰简洁，代码短小精悍，通过记录整体增加量优化暴力模拟，有效降低时间复杂度，代码可读性高。
    - **重点代码**：
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

#define N 100005

using namespace std;

int n, m;
long long a[N], pos;

int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf ("%lld", a + i);
	for (int i = 1, opt, v, x; i <= m; ++i) {
		scanf ("%d", &opt);
		switch (opt) {
			case 1 : scanf ("%d%d", &v, &x); a[v] = x - pos; break;
			case 2 : scanf ("%d", &x); pos += x; break;
			case 3 : scanf ("%d", &x); printf ("%lld\n", a[x] + pos); break;
		}
	}
	return 0;
}
```
    - **核心实现思想**：根据操作类型进行处理，操作1修改值时减去pos，操作2累加pos，操作3输出值时加上pos。

 - **作者：Transparent (4星)**
    - **关键亮点**：详细阐述线段树原理及本题应用，代码实现完整规范，利用线段树处理区间修改和单点查询，时间复杂度为$O(log n)$，适合大数据量。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll sum[400004],num[100001],add[400004],n,m;
void build(ll k,ll l,ll r)
{
	if(l==r)
	{
		sum[k]=num[l];
		return;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline void Add(ll k,ll l,ll r,ll v)
{
	add[k]+=v;
	sum[k]+=v*(r-l+1);
}
inline void pushdown(ll k,ll l,ll r,ll mid)
{
	if(add[k]==0)
	return;
	Add(k<<1,l,mid,add[k]);
	Add(k<<1|1,mid+1,r,add[k]);
	add[k]=0;
}
ll query(ll k,ll l,ll r,ll x,ll y)
{
	if(l>=x&&r<=y)
	return sum[k];
	ll mid=(l+r)>>1;
	ll res=0;
	pushdown(k,l,r,mid);
	if(x<=mid)res+=query(k<<1,l,mid,x,y);
	if(mid<y)res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
void change(ll k,ll l,ll r,ll x,ll v)
{
	if(r<x||l>x)
		return;
	if(l==r&&l==x)
	{
		sum[k]=v;
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(k,l,r,mid);
	change(k<<1,l,mid,x,v);
	change(k<<1|1,mid+1,r,x,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
void modify(ll k,ll l,ll r,ll x,ll y,ll v)
{
	if(l>=x&&r<=y)
	{
		Add(k,l,r,v);
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(k,l,r,mid);
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
	scanf("%lld",num+i);
	build(1,1,n);
	while(m--)
	{
		ll s,i,x;
		scanf("%lld",&s);
		if(s==1)
		{
			scanf("%lld%lld",&i,&x);
			change(1,1,n,i,x);
		}
		if(s==2)
		{
			scanf("%lld",&x);
			modify(1,1,n,1,n,x);
		}
		if(s==3)
		{
			scanf("%lld",&x);
			printf("%lld\n",query(1,1,n,x,x));
		}
	}
	return 0;
}
```
    - **核心实现思想**：通过线段树节点维护区间信息，利用Lazy - Tag标记下传实现高效区间修改，单点查询时通过递归查询对应节点值。

 - **作者：fjy666 (4星)**
    - **关键亮点**：提出用树状数组解决问题，将单点赋值转化为区间加法，思路新颖，时间复杂度为$\Theta(m\times\log n)$且常数极小。
    - **重点代码**：
```cpp
#include <cstdio>
#include <cstdlib>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 100005;
ll arr[kMaxn];
int n,m,ID,IsHaveTypeI,IsHaveTypeII;
struct query
{
	int id;
	ll a,b;
	void Scan(void)
	{
		scanf("%d",&id);
		if(id==1)scanf("%lld%lld",&a,&b);
		else scanf("%lld",&a);
	}
}q[kMaxn];

void Init(void)
{
	scanf("%d%d",&n,&m);
	fo(i,1,n)
		scanf("%lld",arr+i);
	fo(i,1,m)
	{
		q[i].Scan();
		if(q[i].id==1)
			IsHaveTypeI = 1;
		if(q[i].id==2)
			IsHaveTypeII = 1;
	}
}

namespace SubtaskIII
{
#define lowbit(x) (x&-x)
	ll c[kMaxn];
	void Add(int ind,ll add)
	{
		for(;ind<=n;ind+=lowbit(ind))
			c[ind]+=add;
		}
	ll Query(int x)
	{
		ll sum=0;
		for(;x;x-=lowbit(x))
			sum+=c[x];
		rtn sum;
	}
	void Solve(void)
	{
		fo(i,1,n)
			Add(i,arr[i]-arr[i-1]);
		fo(i,1,m)
		{
			if(q[i].id==1)
			{
				ll T = q[i].b - Query(q[i].a);
				Add(q[i].a,T);
				Add(q[i].a+1,-T);
			}
			if(q[i].id==2)Add(1,q[i].a);
			if(q[i].id==3)printf("%lld\n",Query(q[i].a));
		}
	}
}

int main()
{
// 	freopen("array.in","r",stdin);
// 	freopen("array.out","w",stdout);
	Init();
	if((n<=1000&&m<=1000) || (IsHaveTypeII == 0))
		SubtaskI::Solve();
	else if(IsHaveTypeI == 0)
		SubtaskII::Solve(); 
	else
		SubtaskIII::Solve();
    rtn 0;
}
```
    - **核心实现思想**：利用树状数组的特性，通过Add函数更新数组，Query函数查询值，将单点赋值转化为区间加法操作实现题目要求。

### 最优关键思路或技巧
用一个变量记录整体增加量，在修改和查询操作时进行相应处理，这种优化的暴力模拟方法简单高效，实现难度低。线段树和树状数组则利用数据结构优势，在大数据量下有更好的时间复杂度，但实现相对复杂。

### 拓展
同类型题常涉及数组的多种操作及优化，类似算法套路如利用数据结构优化区间操作，或通过记录某些量避免重复计算。

### 推荐题目
 - [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
 - [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
 - [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)

### 个人心得
 - **幽界の冥神**：一开始想到线段树但不会，最终采用优化暴力方法解决。心得是在面对问题时，若复杂算法不会，可从简单思路出发寻找优化点。 

---
处理用时：124.79秒