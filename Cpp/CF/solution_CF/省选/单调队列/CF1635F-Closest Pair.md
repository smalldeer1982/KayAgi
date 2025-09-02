# Closest Pair

## 题目描述

There are $ n $ weighted points on the $ OX $ -axis. The coordinate and the weight of the $ i $ -th point is $ x_i $ and $ w_i $ , respectively. All points have distinct coordinates and positive weights. Also, $ x_i < x_{i + 1} $ holds for any $ 1 \leq i < n $ .

The weighted distance between $ i $ -th point and $ j $ -th point is defined as $ |x_i - x_j| \cdot (w_i + w_j) $ , where $ |val| $ denotes the absolute value of $ val $ .

You should answer $ q $ queries, where the $ i $ -th query asks the following: Find the minimum weighted distance among all pairs of distinct points among the points in subarray $ [l_i,r_i] $ .

## 说明/提示

For the first query, the minimum weighted distance is between points $ 1 $ and $ 3 $ , which is equal to $ |x_1 - x_3| \cdot (w_1 + w_3) = |-2 - 1| \cdot (2 + 1) = 9 $ .

For the second query, the minimum weighted distance is between points $ 2 $ and $ 3 $ , which is equal to $ |x_2 - x_3| \cdot (w_2 + w_3) = |0 - 1| \cdot (10 + 1) = 11 $ .

For the fourth query, the minimum weighted distance is between points $ 3 $ and $ 4 $ , which is equal to $ |x_3 - x_4| \cdot (w_3 + w_4) = |1 - 9| \cdot (1 + 2) = 24 $ .

## 样例 #1

### 输入

```
5 5
-2 2
0 10
1 1
9 2
12 7
1 3
2 3
1 5
3 5
2 4```

### 输出

```
9
11
9
24
11```

# 题解

## 作者：I_am_Accepted (赞：16)

### Preface

嘿，虽然我差了这道 F，但你想不想 AK 这场 Div 2？

### Analysis

首先有一个至关重要的结论：

**设**

$$\begin{aligned}
L_i&=\max\{j\ |\ j<i\ \land\ w_j\le w_i\}
\\
R_i&=\min\{j\ |\ i<j\ \land\ w_j\le w_i\}
\end{aligned}$$

**则最终答案选取的两个数一定是 $(i,R_i)$ 或 $(L_i,i)$ 的形式。**

**Proof**

若最优答案为取 $(i,j)$，且 $R_i\ne j\ \land\ L_j\ne i$，我们证明一定有更优解，以证明原命题。

若 $w_i\le w_j$，则 $L_j>i$，得到 $|x_{L_j}-x_i|<|x_j-x_i|$ 且 $w_i+w_{L_j}\le w_i+w_j$，所以 $(i,L_j)$ 是一组更优解。

$w_i>w_j$ 的情况与上文类似，不再赘述。$\blacksquare$

也就是说，我们把问题转化成：

**有 $2n$ 个数轴上的已知区间 $[l_i,r_i]$，分别带权 $c_i$。每次询问一个区间 $[ql,qr]$，求 $\min\{c_x\ |\ ql\le l_x\ \land\ r_x\le qr\}$。**

我们把询问**离线**下来，就可以用**树状数组**轻松维护了。

具体地，在每一个 $l_i$ 上挂一个 $(r_i,c_i)$ 的标记，在每一个 $ql$ 上挂一个 $(qr,id)$ 的标记。从后往前扫，树状数组维护最小值即可。

时间 $O((n+q)\log n)$。

### Code

[Link](https://codeforces.com/contest/1635/submission/147165337)

---

## 作者：GaryH (赞：12)

## CF1635F 题解

**Upd in 3/13/2022 : 修改了一个笔误**

感觉这个题的性质不是很好想，本人在考场上就没想到，

现在来发一个能比较自然的推出性质，而不是直接给出性质后证明的题解。

题意就不讲了，洛谷翻译讲的很清楚。

**做法**：

我们先想只有一组询问时怎么做。

看到计算所有二元组的信息，首先就可以想到枚举一维并快速计算一维。

记 $calc(l,r)=|x_r-x_l|\cdot(w_l+w_r)$，

考虑枚举 $r$，我们需要快速计算 $\min\limits_{l}(calc(l,r))$ 的值。

首先，上式等于 $\min(\min\limits_{l<r}(calc(l,r)),\min\limits_{l>r}(calc(l,r)))$，

我们只需要讨论 $l<r$ 的情况，因为 $l>r$ 的情况是类似的，只需要翻转序列即可。

当然，看上去这个计算其实是没必要的，因为 $l<r$ 和 $l>r$ 的元素对是重复的，

但为了我们后续做法的方便性，所以我们会将两者都算一遍，也就是说：

对于元素对 $(l,r)$，我们分别在枚举 $l$ 和枚举 $r$ 时考虑了一遍，

而 $w_l\le w_r,w_r\le w_l$ 两个不等式至少一个成立，

那么我们枚举端点 $y$ 时，就可以只考虑所有 $w_x<w_y$ 的 $x$。

显然，如果存在 $l_1,l_2<r$，满足 $x_{l_1}<x_{l_2},w_{l_1}>w_{l_2}$，则 $l_2$ 必然比 $l_1$ 更优，

也就是说，所有可能成为最优决策的 $l$，一定满足 $x$ 值单增，$w$ 值也单增的关系。

那么，我们顺序遍历所有元素，就保证了 $x$ 值单增；

我们再在顺序遍历元素的同时，对所有元素的 $w$ 值建立单增的单调栈，

记 $s(i)$ 为遍历到第 $i$ 个元素时单调栈内的元素集合，

则能成为最优决策的元素对 $(l,r)$，一定满足 $l\in s(r)$。

一般来说，接下来的套路应该是考查单调栈内元素的单调性，来快速确定最优决策点的位置，

但在这道题里，单调栈内的元素并没有单调性，看上去每个元素都可能与 $i$ 成为一对当前的最优解，

感觉问题就变得比较棘手，本人场上就卡在了这里，

而实际上，虽然没有单调性，但我们需要考虑的元素仍然是不多的。

那么，我们考虑如果有两个在单调栈中的元素，下标分别是 $j,k(j<k<i)$，

此时显然有 $x_j<x_k<x_i$，以及 $w_j<w_k<w_i$。那么此时我们说，元素对 $(i,k)$ 一定不是最优解。

为什么？因为 $x_j<x_k<x_i,w_j<w_k<w_i$，故 $|x_k-x_j|<|x_i-x_k|,w_k+w_j<w_i+w_k$，

即 $|x_k-x_j|(w_k+w_j)<|x_i-x_k|(w_i+w_k)$，即 $calc(i,k)<calc(k,j)$，

而 $calc(k,j)$ 在枚举到 $r=k$，计算 $\min\limits_{l>r}(calc(l,r))$ 时已经计算过了，故此时只有 $(j,i)$ 有用。 

上面的性质还可以推广：对于任何 $r$，只有 $calc(l',r)$ 是需要计算的，其中 $l'$ 是栈 $s(r)$ 的栈顶元素。

当然，还有 $l>r$ 的情况，那么我们还需要将元素序列翻转后做一次同样的操作。

也就是说，整个序列中的答案，只可能在 $O(n)$ 对元素对中出现，这 $O(n)$ 对元素对分别是：

$\forall r \in[1,n]$，记 $x$ 为 $i$ 左边离 $i$ 最近且满足 $w_x<w_i$ 的元素下标，

类似的，记 $y$ 为 $i$ 右边离 $i$ 最近且满足 $w_y<w_i$ 的元素下标，则 $(x,r)$ 和 $(r,y)$ 是有用的。

那么，我们现在已经解决了一组询问的情况，我们接下来就需要快速维护一段区间内的答案。

实际上，区间 $[l,r]$ 的答案就等价于以下式子的值：$\min\limits_{l\le i<j\le r} calc(i,j)$，且满足 $(i,j)$ 是有用的元素对。

那么，在使用单调栈预处理出所有有用的元素对后，问题就转化为：

给 $O(n)$ 个三元组 $(x_i,y_i,c_i)(1\le x_i<y_i\le n)$ 和 $q$ 次询问，每次询问给出区间 $[l,r]$，

询问中需要求出所有满足 $x_i,y_i$ 都在区间内的三元组的 $c_i$ 的最大值，而这个问题就不难了。

一个在线的做法是把三元组按 $x_i$ 排序后，以 $y_i$ 这维建主席树并维护答案，

但也有很方便的离线询问后扫描线树状数组的做法，具体流程如下：

我们维护一个数据结构，数据结构维护了一个长 $n$ 的序列的信息。

我们顺序遍历 $i$，每次对所有 $y_j=i$ 的三元组 $j$，把数据结构上位置 $x_j$ 的值与 $c_j$ 取最小值，

然后处理所有右端点为 $i$ 的询问 $[l,i]$，考虑该询问答案等价于求数据结构上区间 $[l,i]$ 的最小值，

因为此时的区间 $[l,i]$ 存储了所有满足 $l\le x_j\le y_j\le i$ 的三元组的 $c_j$ 的最小值。

更进一步，此时查询后缀 $[l,n]$ 的最小值也是等价的，因为遍历到 $i$ 时，$i$ 后面位置没有过任何操作。

那么，这个数据结构需要支持的操作是，单点与某个值取 $\min$，以及查询一段后缀的最小值，

这个可以使用树状数组实现，时间复杂度是 $O(n\log n)$，空间复杂度是 $O(n)$。

代码非常好些且没有什么容易写错的地方，就不放了。

---

## 作者：Tyyyyyy (赞：10)

## CF1635F

### 题意简述
给定 $n$ 个物品，每个物品有属性 $x_i,w_i$。$q$ 次询问，每次给定一个区间 $[l,r]$，求 $\displaystyle\min_{l\leq i<j\leq r}\{|x_i-x_j|\times (w_i+w_j)\}$。

$1\leq n,q\leq 3\times 10^5,1\leq w\leq 10^9,|x_i|\leq 10^9,x_i<x_{i+1}$。

### 题目分析
设 $L_i$ 表示最大的满足 $j<i,w_j\leq w_i$ 的 $j$，$R_i$ 表示最小的满足 $j>i,w_j\leq w_i$ 的 $j$。

有结论：最优的决策要么是 $(L_i,i)$，要么是 $(i,R_i)$。

证明：

设最优决策为 $(i,j)(i<j)$，分类讨论：

若 $w_i\leq w_j$，则 $i=L_j$。否则，$(i,L_j)$ 显然更优，因为若 $i\ne L_j$，则根据 $L_j$ 的定义可知 $i<L_j$，所以 $i<L_j<j$，则 $|x_i-x_{L_j}|<|x_i-x_j|$，而 $w_i+w_{L_j}\leq w_i+w_j$，所以 $(i,L_j)$ 更优。

若 $w_i>w_j$，则 $j=R_i$。否则，$(j,R_i)$ 显然更优，原因同上。

所以我们的问题变为：有 $2n$ 个点对 $(x_i,y_i)$，权值为 $v_i$。每次给定一个区间 $[l,r]$，求 $\displaystyle\min_{l\leq x_i,y_i\leq r}v_i$。这个问题非常经典，转化为二维数点即可解决，这里不多赘述。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+10;
int n,m,x[N],w[N],stk[N],top;
vector<int>p[N];
vector<pair<int,int> >q[N];
struct BIT
{
	ll c[N];
	void upd(int x,ll y){for(;x;x-=x&(-x))c[x]=min(c[x],y);}
	ll ask(int x)
	{
		ll res=9e18;
		for(;x<=n;x+=x&(-x))res=min(res,c[x]);
		return res;
	}
}t;
ll ans[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&w[i]);
	for(int i=1;i<=n;i++)
	{
		while(top&&w[stk[top]]>w[i])top--;
		if(top)p[i].push_back(stk[top]);
		stk[++top]=i;
	}
	top=0;
	for(int i=n;i;i--)
	{
		while(top&&w[stk[top]]>w[i])top--;
		if(top)p[stk[top]].push_back(i);
		stk[++top]=i;
	}
	for(int i=1,l,r;i<=m;i++)scanf("%d%d",&l,&r),q[r].push_back({l,i});
	memset(t.c,0x3f,sizeof(t.c));
	for(int r=1;r<=n;r++)
	{
		for(auto l:p[r])
			t.upd(l,1ll*(x[r]-x[l])*(w[r]+w[l]));
		for(auto que:q[r])ans[que.second]=t.ask(que.first);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：pomelo_nene (赞：8)

考虑到题目的特殊性，我们先钦定一个匹配的顺序，也就是对于 $i,j$，如果 $w_i\geq w_j$，就只考虑 $i$ 匹配 $j$，反之亦然。

注意到样例中不同的数数量非常少，我们猜测能作为答案的匹配并不多。假设现在有 $i$ 可以匹配 $j,k(i<j<k)$，那么 $i$ 匹配哪个优？

匹配 $(i,j)$ 自然是最优的。可以考虑增量 $\Delta x \times w_i$，因为 $w_i \geq \max(w_j,w_k)$，因此匹配 $j$ 更优秀。

注意到我们这样会忽略掉 $w_j\geq w_i$ 的方案，我们用一样的方法证明，对于 $k < j < i,w_i \geq \max(w_j,w_k)$，匹配 $(i,j)$ 更优。

这样的话可能作为答案的匹配只有 $O(n)$ 个。我们要找到 $L_i,R_i$ 表示 $i$ 能匹配的最大的编号小于 $i$ 的数和能匹配的最小的编号大于 $i$ 的数，这个工作并不难，线段树或者树状数组都可以做。

最后是类似于一个二维数点的问题，只不过是求矩阵内点的最小值。将查询看作是查询左下角为 $(L,L)$ 右上角为 $(R,R)$ 的矩形内所有点的最小值，将一个可能作为答案的区间 $[l,r]$ 看作平面上的点 $(l,r)$，其有权值，见题目定义。

这是一个经典问题，可以离线之后树状数组或者线段树做。下面用的是线段树。

```cpp
LL n,q,w[300005],b[300005],len,L[300005],R[300005];
struct SegmentTree{
	LL minn[1200005],maxn[1200005];
	#define lc(x) (x<<1)
	#define rc(x) (lc(x)|1)
	#define Mm LL mid=(l+r)>>1
	void push_up(LL now){minn[now]=min(minn[lc(now)],minn[rc(now)]),maxn[now]=max(maxn[lc(now)],maxn[rc(now)]);}
	void build(LL l,LL r,LL now)
	{
		maxn[now]=0;
		minn[now]=8e18;
		if(l==r)	return ;
		Mm;
		build(l,mid,lc(now)),build(mid+1,r,rc(now));
	}
	void modify(LL l,LL r,LL now,LL x,LL v)
	{
		if(l==r)
		{
			minn[now]=min(minn[now],v);
			maxn[now]=max(maxn[now],v);
			return ;
		}
		Mm;
		if(x<=mid)	modify(l,mid,lc(now),x,v);
		else	modify(mid+1,r,rc(now),x,v);
		push_up(now);
	}
	LL queryMin(LL l,LL r,LL now,LL x,LL y)
	{
		if(x<=l && r<=y)	return minn[now];
		Mm,ans=8e18;
		if(x<=mid)	ans=min(ans,queryMin(l,mid,lc(now),x,y));
		if(mid<y)	ans=min(ans,queryMin(mid+1,r,rc(now),x,y));
		return ans;
	}
	LL queryMax(LL l,LL r,LL now,LL x,LL y)
	{
		if(x<=l && r<=y)	return maxn[now];
		Mm,ans=0;
		if(x<=mid)	ans=max(ans,queryMax(l,mid,lc(now),x,y));
		if(mid<y)	ans=max(ans,queryMax(mid+1,r,rc(now),x,y));
		return ans;
	}
	#undef lc
	#undef rc
	#undef Mm
}tr;
struct node{
	LL r,v;
	node(LL RR=0,LL V=0){r=RR,v=V;}
};
vector<node> Seg[300005],Que[300005];
LL ans[300005],x[300005];
int main(){
	n=read(),q=read();
	for(LL i=1;i<=n;++i)	x[i]=read(),b[i]=w[i]=read();
	sort(b+1,b+1+n);
	len=unique(b+1,b+1+n)-b-1;
	for(LL i=1;i<=n;++i)	w[i]=lower_bound(b+1,b+1+len,w[i])-b;
	tr.build(1,len,1);
	for(LL i=1;i<=n;++i)
	{
		L[i]=tr.queryMax(1,len,1,1,w[i]);
		tr.modify(1,len,1,w[i],i);
	}
	tr.build(1,len,1);
	for(LL i=n;i;--i)
	{
		R[i]=tr.queryMin(1,len,1,1,w[i]);
		tr.modify(1,len,1,w[i],i);
	}
	for(LL i=1;i<=n;++i)
	{
		if(L[i])	Seg[L[i]].push_back(node(i,(b[w[i]]+b[w[L[i]]])*(x[i]-x[L[i]])));
		if(R[i]<=n)	Seg[i].push_back(node(R[i],(b[w[i]]+b[w[R[i]]])*(x[R[i]]-x[i])));
	}
	for(LL i=1;i<=q;++i)
	{
		LL l=read(),r=read();
		Que[l].push_back(node(r,i));
	}
	tr.build(1,n,1);
	tr.modify(1,n,1,n,8e18);
	for(LL i=n-1;i;--i)
	{
		for(auto st:Seg[i])
		{
			LL r=st.r,v=st.v;
			tr.modify(1,n,1,r,v);
		}
		for(auto st:Que[i])
		{
			LL l=i,r=st.r,id=st.v;
			ans[id]=tr.queryMin(1,n,1,l,r);
		}
	}
	for(LL i=1;i<=q;++i)	write(ans[i]),puts("");
	return 0;
}
```

---

## 作者：dead_X (赞：7)

## 前言
一般通过结论题。
## 思路
静态离线区间询问，难以快速加入单点信息，考虑离线下来扫描线。

考虑哪些 $(i,j)$ 是不优的。

如果存在 $p,q$，使得 $x_p<x_q,w_p>w_q$，那么 $q$ 作为 $i$ 一定比 $p$ 优。且更优的决策区间在更劣的决策内，因此较劣的决策没有意义。

如果存在 $p,q$，使得 $x_p<x_q,w_p<w_q$，那么 $p$ 作为 $j$ 一定比 $q$ 优，且更优的决策区间在更劣的决策内，因此较劣的决策没有意义。

因此，我们可以维护一个单调栈，其中 $x,w$ 均递增，显然只有单调栈内的元素能和新元素产生最优的贡献。

考虑新元素 $g$ 在单调栈中插入的位置。对于这个位置下面的位置 $t$，显然 $t$ 下面的元素和 $t$ 的加权距离一定比这些元素和 $g$ 的加权距离小。

于是我们只通过观察性质就找出了一个 $O((n+m)\log n)$ 的算法：

直接扫描线扫右端点，维护上文中的单调栈，每次只对插入位置往上和插入位置正下方更新答案，查询就是单点修改区间 RMQ，使用线段树即可。
## 代码
懒得写了贺了 YanZhuoZLY 的代码。

```cpp
// Problem: F. Closest Pair 
// Contest: Codeforces Round #772 (Div. 2)
// URL: https://codeforces.com/contest/1635/problem/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int ans[1200003];
void update(int l,int r,int x,int id,int val)
{
	if(l==r) 
	{
		ans[id]=min(ans[id],val);
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(l,mid,x,id<<1,val);
	else update(mid+1,r,x,(id<<1)+1,val);
	ans[id]=min(ans[(id<<1)],ans[(id<<1)+1]);
	return ;
}
int query(int l,int r,int L,int R,int id)
{
	if(L<=l && r<=R) return ans[id];
	int mid=(l+r)>>1;
	int res=0x3f3f3f3f3f3f3f3f;
	if(L<=mid) res=min(res,query(l,mid,L,R,id<<1));
	if(R>=mid+1) res=min(res,query(mid+1,r,L,R,(id<<1)+1));
	return res;
}
struct node
{
	int l,id;
};
vector<node> e[300003];
int Ans[300003],a[300003],w[300003];
signed main()
{
	memset(ans,0x3f,sizeof(ans));
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) a[i]=read(),w[i]=read();
	for(int i=1; i<=m; ++i)
	{
		int l=read(),r=read();
		e[r].push_back((node){l,i});
	}
	stack<int> stk;
	for(int i=1; i<=n; ++i)
	{
		while(!stk.empty())
		{
			int A=stk.top();
			update(1,n,A,1,(a[i]-a[A])*(w[i]+w[A]));
			if(w[A]>w[i])//i更优
				stk.pop();
			else break;
		}
		stk.push(i);
		for(node j:e[i])
			Ans[j.id]=query(1,n,j.l,i,1);
	}
	for(int i=1; i<=m; ++i) printf("%lld\n",Ans[i]);
	return 0;
}
```

---

## 作者：orz_z (赞：3)

### CF1635F Closest Pair

$x$ 递增，考虑维护 $w$。

考虑匹配，由 $w$ 大的匹配 $w$ 小的。

显然，单调，若 $i\leq j\leq k$，若 $w_k>w_j$，那么最优的匹配一定不是 $(i,k)$。

故考虑维护每个点 $i$，记录左右边第一个满足 $w_j<w_i$ 的 $j$，分别记作 $L_i$ 和 $R_i$，单调栈经典操作。

此时，答案匹配只能是区间中所有 $(L_i,i)$ 和 $(i,R_i)$ 中最小的了，匹配方案 $\mathcal O(n)$。

然后将询问按照右端点排序，维护左端点，线段树查询最小值即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(ll x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 3e5 + 10;
const ll inf = LLONG_MAX;

int n, m, w[_], x[_], L[_], R[_], t, q[_];

ll as[_], tr[_ << 2];

vector<int> d[_];

vector<pair<int, int>> qr[_];

void build(int o, int l, int r)
{
	tr[o] = inf;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
}

void upd(int o, int l, int r, int p, ll v)
{
	if(l == r) return tr[o] = min(tr[o], v), void();
	int mid = (l + r) >> 1;
	if(p <= mid) upd(o << 1, l, mid, p, v);
	else upd(o << 1 | 1, mid + 1, r, p, v);
	tr[o] = min(tr[o << 1], tr[o << 1 | 1]);
}

ll qry(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tr[o];
	int mid = (l + r) >> 1; ll res = inf;
	if(L <= mid) res = qry(o << 1, l, mid, L, R);
	if(R > mid) res = min(res, qry(o << 1 | 1, mid + 1, r, L, R));
	return res;
}

signed main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) x[i] = read(), w[i] = read();
	t = 0;
	for(int i = 1; i <= n; ++i)
	{
		while(t && w[q[t]] > w[i]) t--;
		L[i] = q[t];
		q[++t] = i;
	}
	t = 0;
	for(int i = n; i >= 1; --i)
	{
		while(t && w[q[t]] > w[i]) t--;
		R[i] = q[t];
		q[++t] = i;
	}
	for(int i = 1, l, r; i <= m; ++i)
	{
		l = read(), r = read();
		qr[r].push_back({l, i});
	}
	for(int i = 1; i <= n; ++i)
	{
		if(L[i]) d[i].push_back(L[i]);
		if(R[i]) d[R[i]].push_back(i);
	}
	build(1, 1, n);
	for(int i = 1; i <= n; ++i)
	{
		for(int j : d[i]) upd(1, 1, n, j, 1ll * abs(x[i] - x[j]) * (w[i] + w[j]));
		for(pair<int, int> j : qr[i]) as[j.second] = qry(1, 1, n, j.first, i);
	}
	for(int i = 1; i <= m; ++i) write(as[i]), he;
	return 0;
}
```



---

## 作者：yzy1 (赞：3)

## 题目大意

- 给定 $n(2 \le n \le 3\times 10^5)$ 个二元组 $(x_i,w_i)$，其中 $|x_i|,|w_i| \le 10^9$。
- 输入中二元组按照 $x_i$ 严格递增排序给出。
- 给出 $q(1\le q \le 3\times 10^5)$ 次询问，每次询问给出 $l,r(1\le l<r \le n)$，你需要输出：

$$
\min_{l\le i<j\le r} |x_i-x_j| \cdot (w_i+w_j)
$$

## 做法简介

首先我们发现可能成为答案的 $(i,j)$ 数对只有 $O(n)$ 个：考虑下标为 $i$ 的点，可能成为答案的点只有它左右两边离它最近的 $w_i$ 比它小的点。证明如下：

- 假设 $i<j<k$，$w_i<w_j<w_k$，且 $(i,k)$ 数对可能成为答案。则有 $|x_i-x_j| \cdot (w_i+w_j) < |x_i-x_k| \cdot (w_i+w_k)$，且 $[i,j]\subseteq[i,k]$，故 $(i,k)$ 显然劣于 $(i,j)$，与假设矛盾。
- 右侧与左侧同理。

先用单调栈预处理出所有可能成为答案的数对，按照 $j$ 排序。询问离线，按照 $r$ 排序。扫描线扫 $l$，线段树维护区间最小值即可。

注意这题答案最大是 $10^{18}$ 级别的，注意设大上界并选用合适的变量类型。

## 代码参考

```cpp
const int N=2e6+9;
struct Node{int l,r;ll x;};
struct Q{int id,l,r;}q[N];
int n,X[N],Y[N],sta[N],m;
ll Ans[N];
vector<Node> a;

struct Seg{
  ll mn[N];
  inline void Up(int u){mn[u]=min(mn[u<<1],mn[u<<1|1]);}
  void Build(int u,int l,int r){
    if(l==r)return mn[u]=6e18,void();
    int mid=(l+r)/2;
    Build(u<<1,l,mid),Build(u<<1|1,mid+1,r);
    Up(u);
  }
  void Add(int p,ll x,int u,int l,int r){
    if(l==r)return down(mn[u],x),void();
    int mid=(l+r)/2;
    if(p<=mid)Add(p,x,u<<1,l,mid);
    else Add(p,x,u<<1|1,mid+1,r);
    Up(u);
  }
  ll Ask(int L,int R,int u,int l,int r){
    if(L<=l&&r<=R)return mn[u];
    int mid=(l+r)/2;
    if(R<=mid)return Ask(L,R,u<<1,l,mid);
    if(mid+1<=L) return Ask(L,R,u<<1|1,mid+1,r);
    return min(Ask(L,R,u<<1,l,mid),Ask(L,R,u<<1|1,mid+1,r));
  }
}seg;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin>>n>>m;re(i,n)cin>>X[i]>>Y[i];
  re(i,m)cin>>q[i].l>>q[i].r,q[i].id=i;
  sort(q+1,q+m+1,[](Q a,Q b){return a.r<b.r;});
  re(i,n){
    while(sta[0]&&Y[sta[sta[0]]]>Y[i])--sta[0];
    if(sta[sta[0]])a.push_back({sta[sta[0]],i,1ll*llabs(X[i]-X[sta[sta[0]]])*(Y[i]+Y[sta[sta[0]]])});
    sta[++sta[0]]=i;
  }
  sta[0]=0;
  per(i,n,1){
    while(sta[0]&&Y[sta[sta[0]]]>Y[i])--sta[0];
    if(sta[sta[0]])a.push_back({i,sta[sta[0]],1ll*llabs(X[i]-X[sta[sta[0]]])*(Y[i]+Y[sta[sta[0]]])});
    sta[++sta[0]]=i;
  }
  sort(a.begin(),a.end(),[](Node x,Node y){return x.r<y.r;});
  int qid=1;auto it=a.begin();
  seg.Build(1,1,n);
  re(i,n){
    while(it!=a.end()&&it->r<=i)seg.Add(it->l,it->x,1,1,n),++it;
    while(qid<=m&&q[qid].r<=i)Ans[q[qid].id]=seg.Ask(q[qid].l,n,1,1,n),++qid;
  }
  re(i,m)cout<<Ans[i]<<'\n';
  return 0;
}
```



---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF1635F)。

$x$ 有一个作差，去绝对值后发现对于每个位置找找前驱后继可能会有思路。而有定理：

> 对于位置 $p$，与它能产生最大答案的位置 $q$ 一定来自于 $[L_p,p]$ 和 $[p,R_p]$，其中 $L_p,R_p$ 分别是 $w$ 值 $\le w_p$ 且尽量从前驱/后继两个方向逼近 $p$

证明（反证）：

设存在 $i,j$ 使得 $i\le R_i\le j$ 且 $w_i\le w_{R_i}\le w_j$，观察到 $(i,R_i)$ 显然优于 $(i,j)$，当然另一侧是一样的。

知道这个就很简单了。单调栈求 $L,R$ 是常规套路，然后把这 $2n$ 个询问按右端点排序，线段树维护答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define Rep(i,a,b) for(int i = (a);i >= (b);--i)

using ll = long long;

const int N = 3e5 + 5;
const ll INF = 5e18;

int n,m,stk[N],top,X[N],W[N],L[N],R[N]; ll ans[N];
vector<pair<int,int> > Q[N]; vector<int> P[N];

namespace ST{
	ll v[N << 2];
	
	#define lc (i << 1)
	#define rc (i << 1 | 1)
	#define mid ((L + R) >> 1)
	#define ls lc,L,mid
	#define rs rc,mid + 1,R
	#define id int i = 1,int L = 1,int R = n
	
	#define psu v[i] = min(v[lc],v[rc])
	
	void build(){ fill(begin(v),end(v),INF); }
	
	void upd(int p,ll x,id){
		if(L == R) return void(v[i] = min(v[i],x));
		p <= mid ? upd(p,x,ls) : upd(p,x,rs); psu;
	}
	
	ll qry(int l,int r,id){
		if(l <= L && R <= r) return v[i];
		ll Rt = INF;
		if(l <= mid) Rt = qry(l,r,ls);
		if(r > mid) Rt = min(Rt,qry(l,r,rs));
		return Rt;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d%d",X + i,W + i);
	rep(i,1,n){
		while(top && W[stk[top]] > W[i]) --top;
		L[i] = stk[top]; stk[++top] = i;
	} top = 0;
	Rep(i,n,1){
		while(top && W[stk[top]] > W[i]) --top;
		R[i] = stk[top]; stk[++top] = i;
	}
	rep(i,1,n){
		if(L[i]) P[i].push_back(L[i]);
		if(R[i]) P[R[i]].push_back(i);
	}
	rep(i,1,m){
		int l,r;
		scanf("%d%d",&l,&r);
		Q[r].emplace_back(l,i);
	}
	ST::build();
	rep(i,1,n){
		for(int j : P[i]) ST::upd(j,1ll * abs(X[i] - X[j]) * (W[i] + W[j]));
		for(auto[j,k] : Q[i]) ans[k] = ST::qry(j,i);
	}
	rep(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：渔歌 (赞：1)

###  PART 0 思路
~~最开始以为 $x_i$ 是无序的，愣是不知道怎么做~~

$x_i$是有序的那这绝对值就很好拆开 。

如果我们对于每个点 $i$ 枚举其它所有的点 $j$，正确性是有的，但枚举的次数是 $n^2$ 快乐 $TLE$ 级别。

思考有没有一种方式，让每个点只需要枚举少量较优点，而答案只产生于这些点对中。

别说，还真有。~~不然怎么会有这篇题解~~

定义 $L_i$ 为满足 $L_i<i,w_{L_i}\leq w_i$ 的最靠近 $i$ 的点。

 类似地定义 $R_i$ 为满足 $R_i<i,w_{R_i}\leq w_i$ 的最靠近 $i$ 的点。

有的同学可能会有下图的疑惑：

![](https://cdn.luogu.com.cn/upload/image_hosting/akrorics.png)


但是发现，相比 $i$ 与 $j$ 配对还有更优的：$L_i$ 与 $j$ 配对。而 $L_j$ 与 $j$ 相隔更近，所以最优答案一定会被我们记录下来。（ $R_i$ 与 $i$ 同理可得）

同时，由于$L_i$与$R_i$ 都是离 $i$ 最近的，所以区间询问会很好解决： $L_i$ 与 $i$ 或$R_i$ 与 $i$ 是否都在询问区间内便可产生贡献。

### PART 1 求 $L_i,R_i$

我们现在已经证到了正确性，接下来考虑怎么在规定时间内找 $L_i$ 与 $R_i$ 。

再回去看看定义，一个小于号一个小于等于号是不是像极了二维偏序？是不是像极了扫描线？

（这里我只会树状数组呜呜呜，有没有大佬教教单调栈的做法）

### PART 2 计算答案

这些区间没有强制在线我们便可以将其离线，并进行排序。

我们构想的是，排序之后所有同时包含 $i$ 与 $L_i$ 或 $i$ 与 $R_i$ 的区间能得到其贡献。

为了表示两个点都在区间内，我想的方法是其中一个点循环枚举，另一个点作为更新的位置。

我选择了将其分成两种情况： $i$ 与 $L_i$ ，$i$ 与 $R_i$ 分别处理。

对于 $i$ 与 $L_i$ ，$i$ 正序枚举，将询问区间按右端点排序，查询其左端点的后缀最小值。

对于 $i$ 与 $R_i$，$i$ 倒序枚举，将询问区间按左端点排序，查询其右端点的前缀最小值。

（这个地方可以只用一棵树状数组，但我只会两棵嘤嘤嘤）

### PART 3 总结

时间复杂度 $O((n+q)\log n)$

一棵树状数组的事我居然用了四颗···

太弱小了，没有力量~

### Code（奇丑无比）

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define N 300000+10
#define int long long
using namespace std;
int n,q;
int p[N],w[N];
map<int,int>mp;
int lsh[N],l[N],r[N];
struct BIT{
	int bit[N],m;
	void mem(int x){m=x;memset(bit,0x3f,sizeof(bit));}
	inline int ask(int x){int ret=0x3f3f3f3f3f3f3f3fll;for(;x;x-=x&-x)ret=min(ret,bit[x]);return ret;}
	inline void add(int x,int va){
		for(;x<=m;x+=x&-x)
			bit[x]=min(bit[x],va);
	}
}lp,rp,ls,rs;
struct ak{
	int l,r,id;
}e[N];
bool cmpl(ak x,ak y){
	return x.l>y.l;
}
bool cmpr(ak x,ak y){
	return x.r<y.r;
}
int ans[N];
inline void scan(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i],&w[i]);
	for(int i=1;i<=q;i++)
		scanf("%lld%lld",&e[i].l,&e[i].r),e[i].id=i;
}
inline void pre(){
	int name=0;
	for(int i=1;i<=n;i++)lsh[i]=w[i];
	sort(lsh+1,lsh+n+1);
	for(int i=1;i<=n;i++)if(mp.find(lsh[i])==mp.end())mp[lsh[i]]=++name;
	lp.mem(name);rp.mem(name);
	for(int i=1;i<=n;i++){
		int x=mp[w[i]];
		l[i]=-lp.ask(x);
		lp.add(x,-i);
	}
	for(int i=n;i>=1;i--){
		int x=mp[w[i]];
		r[i]=rp.ask(x);
		rp.add(x,i);
	}
}
inline void suan(){
	memset(ans,0x3f,sizeof(ans));
	sort(e+1,e+q+1,cmpr);
	ls.mem(n);rs.mem(n);
	for(int i=1,j=1;i<=n&&j<=q;i++){
		if(l[i]>0)ls.add(n-l[i]+1,(p[i]-p[l[i]])*(w[i]+w[l[i]]));
		while(e[j].r==i){
			ans[e[j].id]=min(ans[e[j].id],ls.ask(n-e[j].l+1));
			j++;
		}
	}
	sort(e+1,e+q+1,cmpl);
	for(int i=n,j=1;i>=1&&j<=q;i--){
		if(r[i]<=n)rs.add(r[i],(p[r[i]]-p[i])*(w[i]+w[r[i]]));
		while(e[j].l==i){
			ans[e[j].id]=min(ans[e[j].id],rs.ask(e[j].r));
			j++;
		}
	}
}
inline void print(){
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}
signed main(){
	scan();
	pre();
	suan();
	print();
	return 0;
}
```


---

