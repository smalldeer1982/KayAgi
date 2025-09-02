# 「TERRA-OI R1」神，不惧死亡

## 题目背景

战斗已经到了白热化阶段，你已经精疲力竭，手臂因承受不住手中巨剑重量不住地发抖，噬神者的紫色外壳已经脱落大半，似乎再承受几次重击就会碎落一地。天空中紫色的迷雾开始变得暗淡，空间由于被不断撕裂而逐渐扭曲。在你的身前，噬神者最后一次撕开裂缝，用最原始的方式向你发起最后一击。你握紧手中的巨剑，准备迎接这最后一击，即使你清楚这是神明吞噬者最后的倔强，可你依然不敢放松一分一毫。最后一击过后，远处响起了钟声，战斗终将落下帷幕......

## 题目描述

李子要在一个长度为 $n$ 的序列 $a$ 上玩游戏，他每次会把下标在 $[l,r]$ 范围内，且取值在 $[p,q]$ 范围内的所有数全部找出来，每次他可以选择其中两个相同的值，并进行**抵消**操作，将这两个数从数列中删除。当且仅当一个原本存在的值被消除掉后，所有值小于这个数的每个值全部要被删除一次（例如数列中原本有三个 $2$，进行一次删除后将会仅剩两个 $2$），并且这个游戏将会立即停止。

李子会不止一次的玩这个游戏，并且每次取的区间都不相同，而且，为了加大游戏难度，李子会时不时的修改序列中某个数的值。

现在李子想让剩下的数列中的最小值尽可能大，需要请你针对每次游戏，输出这个最大的最小值。特别地，如果这个游戏无法停止或者存在一种方案可以消除整个数列，输出 $-1$。

## 说明/提示

#### 【样例解释 #1】

第一个询问对应的数列为 $[1,1,4,5,1,4]$，我们将两个 $1$ 先抵消，再抵消两个 $4$，此时比 $4$ 小的 $1$ 将会删除一次，整个序列只剩一个 $5$。

第二个询问针对前 $4$ 个数，且由于 $5$ 不属于 $[1,4]$ 值域范围，所以数列为 $[1,1,4]$，将两个 $1$ 抵消后游戏直接结束，答案为 $4$。

第三次修改将 $a_1$ 加 $1$，修改后数列为 $[2,1,4,5,1,4]$。

第四次询问对应的数列为 $[2,1,4]$，所有数据都只出现一次，没办法进行抵消操作，游戏无法停止所以输出 $-1$。

第五次询问的数列为 $[1,4,5,1,4]$，我们选择将两个 $1$ 抵消，由于数列中不再有 $1$，游戏结束，最小为 $4$。你也可以抵消两个 $4$，但这样答案为 $1$，比 $4$ 要小。


------------

#### 【数据范围】

**本题采用捆绑测试。**

| Subtask | Score | $n,m\le$ | limit |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ | $10^3$ | 无 |
| $2$ | $20$ | $10^5$ | 保证不存在操作 $1$ |
| $3$ | $30$ | $10^5$ | 保证对于每个操作 $2$ ，$p=1,q=n$ |
| $4$ | $40$ | $10^5$ | 无 |

对于 $100\%$ 的数据，$1\le n,m\le10^5$，对于任何时刻 $\forall i,a_i\in[1,n]$。

对于每个操作 $1$，$1\le p\le n$，$-n+1\le x\le n-1$ 并且 $-a_p<x\le n-a_p$。

对于每个询问 $2$，$1\le l \le r \le n$，$1\le p \le q \le n$。


## 样例 #1

### 输入

```
6 5
1 1 4 5 1 4
2 1 6 1 5
2 1 4 1 4
1 1 1
2 1 4 1 4
2 2 6 1 5```

### 输出

```
5
4
-1
4```

## 样例 #2

### 输入

```
12 12
10 2 8 12 12 3 3 12 1 10 7 2
2 3 4 1 11
2 3 4 5 12
2 1 3 1 3
2 2 10 2 10
2 8 10 5 10
2 5 5 8 11
2 10 12 7 10
2 1 5 4 9
1 12 6
1 1 -6
2 5 8 5 12
2 5 8 2 12```

### 输出

```
-1
-1
-1
8
-1
-1
-1
-1
-1
12```

# 题解

## 作者：Kuristina (赞：14)

问题概述：

本题中，给定长度为 $n$ 的序列 $a$，进行 $q$ 次操作，分为两种：

1. 查询操作：对于查询操作，需要在区间 $[l,r]$ 内找到值在 $[a,b]$ 范围内出现次数为偶数的最大数的后继。
2. 修改操作：对于修改操作，需要将 $a_i$ 的值修改为 $x$。

解题思路：

本题需要实现查询和修改两种操作，其中查询操作需要找到值在指定区间内出现次数为偶数的最大数的后继。因此，可以采用带修莫队算法和值域分块的思想来解决这个问题。

具体的实现细节如下：

- 首先，将序列 $a$ 分成 $B$ 个块，每个块的大小为 $n/B$。
- 对于每个块，需要记录区间内每个元素的出现次数，并统计出现次数为偶数的最大值。
- 对于查询操作，可以采用带修莫队算法。具体来说，可以先将所有的查询操作按照左端点所在块的编号排序，对于同一个块内的查询操作，按照右端点排序。这样，可以保证同一个块内的查询操作按照右端点的顺序依次处理。
- 在处理每个查询操作时，需要先将修改操作同步到当前查询操作的时间戳。然后，可以采用类似于普通莫队算法的方式，在块内和块之间进行查询。
- 在块内查询时，可以直接遍历该块内的所有元素，并统计出现次数为偶数的最大值。
- 在块之间查询时，需要统计出现次数为偶数的最大值，并找到值最大的元素。这个过程可以通过预处理每个块的出现次数为偶数的最大值来完成。
- 对于修改操作，需要在块内进行修改，并更新块的出现次数为偶数的最大值。

取 $B = \sqrt n$，带修莫队 $O(n^{5/3})$。至此，我们用非常波特的方式解决了这道波特题目。


---

## 作者：MCRS_lizi (赞：3)

个人感觉是后三题最清新的了，一道显而易见的数据结构题。

前置知识：[带修改莫队](https://oi-wiki.org/misc/modifiable-mo-algo/)、[值域分块](https://oi-wiki.org/ds/block-array/) ~~（选手：不是说数据结构吗怎么是离线算法）~~

接下来就不具体介绍每个算法了，直接讲解思路。

根据一通分析，我们可以知道，这题要询问的是最小的出现次数为偶数次的数的后继。我们只要把这个数之前的数全部抵消成只出现一次（都是奇数），然后再消除掉这个数就可以了。

所以，我们先要找出出现偶数次的数，我们发现 $a_i\le n$，所以我们可以用计数的方式进行 ~~（看，没让你离散化，我多么善良）~~，你自然可以用分块计数完成，但我认为莫队更加方便。区间移动时进行计数即可。然后再枚举值域区间就可以得到答案。

but，当你提交上去会发现......10pts?

直接枚举值域区间理论最大复杂度很大，稍微hack一下就挂了，所以，我们要想办法优化这个查询，所以我们需要一个数据结构来维护。你可以尝试线段树之类的，但是实现困难并且修改有 $O(\log n)$，思来想去，还是分块最方便。分块不仅可以方便查询，还只有 $O(1)$ 的修改复杂度。

所以，我们需要对值域进行分块，块内维护偶数的个数与这个值域的总和。这样找偶数时直接找有偶数的，找后继就直接找里面有元素的，很显然，查询复杂度为 $O(\sqrt n)$，因为只要对块内进行查询一定可以找到对应答案，也就是 $O(\sqrt n)$，再加上一共只有 $\sqrt n$ 个块，枚举一共就 $O(\sqrt n)$，散块处理也是一样的。

总体时间复杂度为 $O(n^{\frac{5}{3}})$，证明见上方链接，这里不多赘述。（虽然这个复杂度很大，但我没去卡极限复杂度，而且这个极限值也是卡不到的）

还有疑问见代码及注释。

**CODE：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int n,m,a[N],num[N],id[N],blk1,blk2,l,r,tot1,tot2,tot,tim,ans[N];
struct node//分块
{
	int l,r,cnt1,cnt2;//cnt1 偶数的个数，cnt2 一共有几个数
}b[1050];
struct que//查询操作
{
	int l,r,p,q,t,xh;
}c[N];
struct upd//修改操作
{
	int p,x;
}d[N];
bool cmp(que u,que v)//排序方式，理由不多叙述，可见oiwiki（实在不行背下来）
{
	return u.l/blk1<v.l/blk1||u.l/blk1==v.l/blk1&&u.r/blk1<v.r/blk1||u.l/blk1==v.l/blk1&&u.r/blk1==v.r/blk1&&u.t<v.t;
}
void move(int x,int op)
{
	if(op==-2)//时间轴前移
	{
		int p=d[x].p,val=d[x].x;
		if(p>=l&&p<=r)//注意，只有坐标在当前区间内才修改num数组
		{
			num[a[p]]--,b[id[a[p]]].cnt2--;
			if(num[a[p]]%2==1)//这里及下方注意num为0的情况，这个时候0不能算作偶数
			{
				b[id[a[p]]].cnt1--;
			}
			else if(num[a[p]])
			{
				b[id[a[p]]].cnt1++;
			}
		}
		a[p]-=val;
		if(p>=l&&p<=r)
		{
			num[a[p]]++,b[id[a[p]]].cnt2++;
			if(num[a[p]]%2==1&&num[a[p]]!=1)
			{
				b[id[a[p]]].cnt1--;
			}
			else if(num[a[p]]%2!=1)
			{
				b[id[a[p]]].cnt1++;
			}
		}
	}
	else if(op==0)//时间轴后移，内部操作同上
	{
		int p=d[x].p,val=d[x].x;
		if(p>=l&&p<=r)
		{
			num[a[p]]--,b[id[a[p]]].cnt2--;
			if(num[a[p]]%2==1)
			{
				b[id[a[p]]].cnt1--;
			}
			else if(num[a[p]])
			{
				b[id[a[p]]].cnt1++;
			}
		}
		a[p]+=val;
		if(p>=l&&p<=r)
		{
			num[a[p]]++,b[id[a[p]]].cnt2++;
			if(num[a[p]]%2==1&&num[a[p]]!=1)
			{
				b[id[a[p]]].cnt1--;
			}
			else if(num[a[p]]%2!=1)
			{
				b[id[a[p]]].cnt1++;
			}
		}
	}
	else if(op==1)//扩展区间
	{
		num[a[x]]++;
		if(num[a[x]]%2==1&&num[a[x]]!=1)
		{
			b[id[a[x]]].cnt1--;
		}
		else if(num[a[x]]%2!=1)
		{
			b[id[a[x]]].cnt1++;
		}
		b[id[a[x]]].cnt2++;
	}
	else//缩减区间
	{
		num[a[x]]--;
		if(num[a[x]]%2==1)
		{
			b[id[a[x]]].cnt1--;
		}
		else if(num[a[x]])
		{
			b[id[a[x]]].cnt1++;
		}
		b[id[a[x]]].cnt2--;
	}
}
int query(int l,int r)//值域分块
{
	if(id[r]-id[l]<=1)
	{
		bool flag=0;
		for(int i=l;i<=r;i++)//散块处理
		{
			if(flag&&num[i])
			{
				return i;
			}
			else if(num[i]%2==0&&num[i])
			{
				flag=1;
			}
		}
	}
	else
	{
		bool flag=0;
		for(int i=l;i<=b[id[l]].r;i++)//散块处理
		{
			if(flag&&num[i])
			{
				return i;
			}
			else if(num[i]%2==0&&num[i])
			{
				flag=1;
			}
		}
		for(int i=id[l]+1;i<id[r];i++)
		{
			if(b[i].cnt1&&!flag||flag&&b[i].cnt2)//如果有偶数次的且还未找到偶数次的，或者已经找到偶数次的且里面有元素，就进入块内枚举
			{
				bool check=0;
				for(int j=b[i].l;j<=b[i].r;j++)
				{
					if(flag&&num[j])
					{
						return j;
					}
					else if(num[j]%2==0&&num[j])
					{
						flag=1;
					}
				}
			}
		}
		for(int i=b[id[r]].l;i<=r;i++)//散块处理
		{
			if(flag&&num[i])
			{
				return i;
			}
			else if(num[i]%2==0&&num[i])
			{
				flag=1;
			}
		}
	}
	return -1;//无解
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	blk1=ceil(pow(n,0.6666666));
	blk2=sqrt(n);
	if(blk2==1)
	{
		blk2++;
	}
	for(int i=1;i<=m;i++)
	{
		int op;
		scanf("%d",&op);
		
		if(op==1)
		{
			tot2++;
			scanf("%d%d",&d[tot2].p,&d[tot2].x);
			tim++;
		}
		else
		{
			tot1++;
			scanf("%d%d%d%d",&c[tot1].l,&c[tot1].r,&c[tot1].p,&c[tot1].q);
			c[tot1].t=tim,c[tot1].xh=tot1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(i%blk2==1)
		{
			b[++tot].l=i;
		}
		else if(i%blk2==0)
		{
			b[tot].r=i;
		}
		id[i]=tot;
	}
	sort(c+1,c+tot1+1,cmp);//离线处理，先排序
	l=1,r=1,num[a[1]]=1,b[id[a[1]]].cnt2++,tim=0;
	for(int i=1;i<=tot1;i++)
	{
		while(l>c[i].l)//莫队移动，带修改有三个维度（注意，这里的顺序比较重要，因为左端点到右端点右边的话统计会出错，所以必须先扩张区间再收缩区间）
		{
			move(--l,1);
		}
		while(r>c[i].r)
		{
			move(r--,-1);
		}
		while(l<c[i].l)
		{
			move(l++,-1);
		}
		while(r<c[i].r)
		{
			move(++r,1);
		}
		while(tim<c[i].t)
		{
			move(++tim,0);
		}
		while(tim>c[i].t)
		{
			move(tim--,-2);
		}
		ans[c[i].xh]=query(c[i].p,c[i].q);
	}
	for(int i=1;i<=tot1;i++)
	{
		printf("%d\n",ans[i]);
	}
 	return 0;
}//抄题解是不好的习惯哦
```


---

## 作者：yizhiming (赞：1)

## 题目大意

维护一个序列，单点加，区间查询...

[$Link$](https://www.luogu.com.cn/problem/P8931)

区间查询太麻烦了，就放链接了，如果直接给简易题面这道题就是一眼题了。

## 题目分析

首先发现要维护区间，单点修改，且修改单次 $O(1)$，$n\leq 10^5$，且支持离线，还跟值域有关，看到这么多条件，我们可以直接猜一个带修莫队维护值域分块，我们可以通过这种方法维护当前区间所有值的出现次数（这东西不会的话建议先去学完再写这道题）。

注意到我们每次可以将一个数的出现次数减掉 $2$，而不影响最终答案，所以我们可以将所有的数的出现次数都减到 $1,2$。

所以就将原本值域区间 $[p,q]$ 转换成了出现次数仅包含 $1,2$ 的区间，对于已经为 $1$ 的值，我们只能通过后面的 $2$ 对其进行修改。

考虑现在删除一个出现次数为 $2$ 的值 $x$，如果存在一个 $y$，使得 $y$ 的出现次数为 $2$，且 $y<x$，那么一定会导致删除 $x$ 后，$y$ 仍然存在，而删掉 $y$ 答案则会变成 $y$ 的后继，所以删掉 $y$ 要优于 $x$，不难看出，问题现在转换成了查询原值域序列上出现次数为非零偶数的最小值的后继。

考虑维护以下数组 $sum_i,cnt_i,num_i$ 分别表示第 $i$ 个值域块内有多少个数出现次数为非零偶数，值 $i$ 的出现次数，第 $i$ 个值域块有多少个数吗，这些都可以在莫队移动的时候方便的求出来。

查询的时候直接值域分块即可。

具体来讲就是先按左零散块，整块，右零散块的顺序先找到出现次数为非零偶数的最小值，再查询其后继，复杂度单次 $\sqrt{n}$。

带修莫队块长取 $n^{\frac{2}{3}}$，总复杂度 $O(n^{\frac{5}{3}})$。

## Code

注意点细节，查询后继的时候，要查询的区间左端点可能大于 $n$，从而导致查找所在块的时候遍历了一遍全部区间（也可能只有我这么写）。

值域分块的时候块长取 $\sqrt{n}$ 的话还能卡，但没必要。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5+5;
int bel[N],L[N],R[N],tot1,tot2;
int pla[N],val[N];
int sum[N],cnt[N],num[N];
struct bb{
	int l,r,x,y,id,t;
	bool operator<(const bb&a)const{
		if(bel[l]==bel[a.l]){
			if(bel[r]==bel[a.r]){
				return t<a.t;
			}else{
				return bel[r]<bel[a.r];
			}
		}else{
			return bel[l]<bel[a.l];
		}
	}
}node[N];
int a[N],n,m;
void add(int val){
	if(cnt[val]){
		if(cnt[val]&1){
			sum[bel[val]]++;
		}else{
			sum[bel[val]]--;
		}
	}
	num[bel[val]]++;
	cnt[val]++;
}
void del(int val){
	if(cnt[val]!=1){
		if(cnt[val]&1){
			sum[bel[val]]++;
		}else{
			sum[bel[val]]--;
		}
	}
	num[bel[val]]--;
	cnt[val]--;
}
int ask(int l,int r){
	int u = -1;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			if(cnt[i]&&cnt[i]%2==0){
				u = i;
				break;
			}
		}
	}else{
		for(int i=l;i<=R[bel[l]];i++){
			if(cnt[i]&&cnt[i]%2==0){
				u = i;
				break;
			}
		}
		for(int i=bel[l]+1;i<bel[r];i++){
			if(u!=-1){
				break;
			}
			if(sum[i]){
				for(int j=L[i];j<=R[i];j++){
					if(cnt[j]&&cnt[j]%2==0){
						u = j;
						break;
					}
				}
			}
		}
		for(int i=L[bel[r]];i<=r;i++){
			if(u!=-1){
				break;
			}
			if(cnt[i]&&cnt[i]%2==0){
				u = i;
				break;
			}
		}
	}
	
	if(u==-1){
		return -1;
	}
	l = u+1;
	if(l>r){
		return -1;
	}
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			if(cnt[i]){
				return i;
			}
		}
		return -1;
	}
	for(int i=l;i<=R[bel[l]];i++){
		if(cnt[i]){
			return i;
		}
	}
	for(int i=bel[l]+1;i<bel[r];i++){
		if(num[i]){
			for(int j=L[i];j<=R[i];j++){
				if(cnt[j]){
					return j;
				}
			}
		}
	}
	for(int i=L[bel[r]];i<=r;i++){
		if(cnt[i]){
			return i;
		}
	}
	return -1;
}
int ans[N];
int main(){
	n = read();m = read();
	int siz = pow(n,0.6667);
	for(int i=1;i<=n;i++){
		a[i] = read();
		bel[i] = (i-1)/siz+1;
		if(!L[bel[i]]){
			L[bel[i]] = i;
		}
		R[bel[i]] = i;
	}
	int op,l,r,x,y;
	for(int i=1;i<=m;i++){
		op = read();
		if(op==1){
			x = read();y = read();
			pla[++tot1] = x;val[tot1] = y;
		}else{
			l = read();r = read();x = read();y = read();
			node[++tot2].l = l;node[tot2].r = r;
			node[tot2].x = x;node[tot2].y = y;
			node[tot2].t = tot1;node[tot2].id = tot2;
		}
	}
	sort(node+1,node+1+tot2);
	int lx=1,rx=0,tx=0,t;
	for(int i=1;i<=tot2;i++){
		l = node[i].l;r = node[i].r;
		x = node[i].x;y = node[i].y;
		t = node[i].t;
		while(lx>l){
			add(a[--lx]);
		}
		while(rx<r){
			add(a[++rx]);
		}
		while(lx<l){
			del(a[lx++]);
		}
		while(rx>r){
			del(a[rx--]);
		}
		while(tx<t){
			tx++;
			if(pla[tx]>=l&&pla[tx]<=r){
				del(a[pla[tx]]);
				add(a[pla[tx]]+val[tx]);
			}
			a[pla[tx]]+=val[tx];
			val[tx]*=-1;
		}
		while(tx>t){
			if(pla[tx]>=l&&pla[tx]<=r){
				del(a[pla[tx]]);
				add(a[pla[tx]]+val[tx]);
			}
			a[pla[tx]]+=val[tx];
			val[tx]*=-1;
			tx--;
		}
		ans[node[i].id] = ask(x,y);
	}
	for(int i=1;i<=tot2;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}


```

水讨论的时候看见出题人推荐的，就来水一发题解。

然而莫队忘记分讨调了一上午（

---

