# [JRKSJ R9] ZYPRESSEN

## 题目背景

大气层越发清澈澄明\
无声的丝柏冲天而立

![](https://free.picui.cn/free/2025/04/03/67ee77d569fef.png)

耀眼的大气下\
哀怨依然青深\
柏木静静摇曳\
鸟儿再次划破青空\
此处已无真心话语\
阿修罗泪如雨落土

## 题目描述

已经完全是秋季了。

即使如此，丝柏（ZYPRESSEN）也是一如既往的黢黑吧。

给你一个长度为 $n$ 的序列 $a$，共有 $q$ 次询问，每次询问如下：

* 给你一个区间 $[l,r]$，对于所有的 $i,j,k$ 满足 $l\le i<j<k\le r$ 且三边长度分别为 $a_i,a_j,a_k$ 的三角形存在，你需要求出 $a_i+a_j+a_k$ 的最小值。

三边长度分别为 $a,b,c(a\le b\le c)$ 时，能构成三角形当且仅当 $a+b>c$。

## 说明/提示

### 样例解释 1

对于区间 $[3,5]$，因为 $1+5<12$，所以不存在合法的三角形。

对于区间 $[2,5]$ 和 $[2,6]$，选取 $a_i=11,a_j=5,a_k=12$。

对于区间 $[1,7]$，选取 $a_i=3,a_j=11,a_k=10$。

### 数据规模与约定

**本题采用捆绑测试。**

| $\mathrm{Subtask}$ | $n\le$ | $q\le$ | 特殊性质 |分数 | 
| :-----: | :-----: | :-----: | :-----: | :-----: | 
| $1$ | $5\times 10^3$ | $5\times 10^3$ | |$10$ | 
| $2$ | $5\times 10^4$ | $5\times 10^4$ | |$25$ | 
| $3$ | $2.5\times 10^5$ | $5\times 10^5$ | $\checkmark$|$10$ | 
| $4$ | $2.5\times 10^5$ | $5\times 10^5$ | |$55$ | 

特殊性质：保证 $a_i$ 在范围内等概率随机生成。

对于所有数据，保证 $1\le n\le 2.5\times 10^5$，$1\le q\le 5\times 10^5$，$1\le a_i\le 10^7$，$1\le l\le r\le n$。

## 样例 #1

### 输入

```
7 6
3 11 1 5 12 19 10
1 1
3 5
2 5
1 7
2 6
1 4```

### 输出

```
yumi!
yumi!
28
24
28
yumi!```

## 样例 #2

### 输入

```
20 20
26 17 11 89 56 33 72 73 43 77 80 87 97 17 43 74 72 91 49 69
10 19
2 4
3 5
2 11
1 12
10 19
3 5
8 15
8 12
14 20
5 11
13 18
2 18
17 19
1 9
5 8
9 12
1 11
4 13
3 18```

### 输出

```
109
yumi!
yumi!
87
54
109
yumi!
103
193
109
132
163
45
212
54
161
200
54
132
87```

# 题解

## 作者：critnos (赞：9)

首先把值域按照 $[2^k,2^{k+1})$ 分块。

然后从小到大扫描每个块，如果这个块中有 $\ge 3$ 个数在区间中就停下来，记这个块是 $t$。

首先可知，存在一个方案是这个块内前三小值的和。这就说明，其他的方案至少包含一个 $<t$ 的块中的数。

接下来考虑所有 $<t$ 的块中的数，只有 $O(\log v)$ 个。

如果答案包含这其中的 $\ge 2$ 个数，这个是容易计算的。可以发现，答案的最大、次大值在排序数组中相邻。那么只需要取出 $<t$ 的块中的数和块 $t$ 中的最小值计算这些数的答案。

对于已经排序的数组，可以线性计算答案。小到大枚举合法的 $i,a_i-a_{i-1}<a_{i-2}$ 的时候，只有 $a_i-a_{i-1}$ 的前缀最小值才是有用的，可以双指针。

接下来考虑包含一个 $<t$ 的数，和两个 $\ge t$ 的数。

而且可以发现，一个最小值（$<t$ 的数）要能有用，必须满足区间包含了这块中的不超过 $2$ 个数。那么我们枚举最小值，对应的区间总长度是 $O(n\log v)$ 的。

### 算法 1

这是暴力。

显然这两个数只能在块 $t$ 和 $t+1$ 中，不妨判掉一个在 $t$ 一个在 $t+1$ 中的情况。然后需要解决的就是最大值和次大值同块的情形。

可以发现，如是在做这样一个事情：找到一个最小的 $x$，使得区间中存在两个数 $a_i,a_j\le x$，满足 $|a_i-a_j|<t$。

那么把块中的数排序，从小到大加入。类似区间最近点对，考虑加入一个 $a_p$ 带来的有贡献的对子，不妨设 $i<j<p$，如果 $(i,p)$ 和 $(j,p)$ 都有贡献，那么 $a_i>\frac {a_j+a_p} 2$。那么加入一个 $a_p$ 会带来 $O(\log v)$ 个新对子。找这个对子可以 $O(n\log n\log v)$ 线段树二分。

然后枚举最小值，找到这个最小值区间中的对子，可以发现这样找到了 $O(n\log^2 v)$ 个支配三元组。

然后用迭代分块进行二维数点。时间复杂度 $O(n\log^2 v+qn^{\epsilon})$，常数较小。

### 算法 2

**可以证明，支配三元组数量是 $O(n\log v)$ 的**（proved by ZhouKangyang）：

记枚举的最小值是 $x$，考虑这个最小值的区间，记 $b_i=\lfloor a_i/x\rfloor$，那么如果 $b_i=b_j$，那么 $a_i,a_j,x$ 必然是合法三角形。那么对于每类 $b_i$，相当于最小化区间 $a_i+a_j$，这非常经典，直接单调栈求出即可。另一类情况是 $|b_i-b_j|=1$，那么只需要对每个 $b_i$ 求出其前面和后面第一个 $b_j=b_i-1$（显然如果有 $k<j<i$ 使得 $b_k=b_j=b_i-1$ 那么 $(j,k)$ 更优）。

所以，支配三元组数正比于区间长度。

那么时间复杂度为 $O(n\log v\log n+q\log v)$（利用 veb 数点并 $O(n\log v)$ 求支配三元组可以更优，找支配三元组精细实现可以不用 hash），非常接近区间最近点对。常数较大。

十分遗憾地，根据我的实现，两种做法均可通过，但算法 1 的运行速度更快。

---

## 作者：DaiRuiChen007 (赞：6)

[Problem Link](https://www.luogu.com.cn/problem/P10882)

**题目大意**

> 给定 $a_1\sim a_n$，$q$ 次询问 $l,r$，找出一组 $l\le i<j<k\le r$ 满足存在三角形以 $a_i,a_j,a_k$ 为三边边长，并最小化 $a_i+a_j+a_k$。
>
> 数据范围：$n\le2.5\times 10^5,q\le5\times 10^5,V\le 10^7$。

**思路分析**

考虑对值域倍增分块。

对于每个块 $B_k=[2^k,2^{k+1})$，处理每个询问 $l,r$，如果区间 $[l,r]$ 中有 $\ge 3$ 个 $B_k$ 中的元素，那么取出任意三个都能构成三角形，我们只要取出最小的三个即可。

对每个 $[l,r]$ 我们找出最小的 $k$，更新答案后弹出，如果其他情况想要更优，一定至少包含一个 $<2^k$ 的元素。

我们发现，对于 $i\in [0,k)$，$[l,r]$ 中至多有 $2$ 个 $B_i$ 中的元素，因此 $[l,r]$ 中 $<2^k$ 的元素数量是 $\mathcal O(\log V)$ 级别的。

我们考虑最终的三角形中有多少个元素 $<2^k$。

如果有 $\ge 2$ 个元素 $<2^k$，那么我们可以枚举中间的数，显然最大的数没有下界，一定是越小越好。

因此三角形最长的两条边排序后一定是相邻的，因此最长边的范围也在 $[0,2^k)$ 间，或者是 $B_k$ 在 $[l,r]$ 中的最小元素。

那么我们只要考虑 $\mathcal O(\log V)$ 个元素，设他们从小到大排序之后为 $t_1\sim t_m$，枚举 $i$，找到最小的 $t_j>t_{i+1}-t_i$，那么 $(t_i,t_{i+1},t_j)$ 构成三角形。

注意到 $i$ 变大时，若 $t_{i+1}-t_i$ 也变大，那么 $t_j$ 也变大，三条边都不优，所以我们只要考虑 $t_{i+1}-t_i$ 的前缀最小值，可以双指针线性维护。

实现代码的时候我们可以按 $k$ 从小到大扫描，前缀和计算区间中有多少 $\in B_k$ 的数，如果 $\ge 3$ 个就要求区间前三小值，可以线段树维护，由于每个区间询问后直接弹出，这部分复杂度 $\mathcal O(n\log V+q\log n)$。

这样的数如果 $\le 2$ 个，那么我们要把他们全找出来，找出 $\ge l$ 的最小的一个，和 $\le r$ 最大的一个，一定能找出所有的数，先加入较小值，最终的序列就已经有序了。

这部分总的复杂度为 $\mathcal O((n+q)\log V)$。

然后考虑 $<2^k$ 的元素恰好有一个的情况，显然此时这个元素是最小值。

不妨设这个元素为 $a_x$，我们枚举这个 $a_x$ ，反向考虑什么样的区间会枚举到 $x$。

设 $a_x $属于 $B_i$，容易发现如果某个询问区间 $[l,r]$ 经过 $B_i$ 时没有找到 $\ge 3$ 个数，$a_x$ 才会 $<2^k$。

因此对每个 $a_x$，找出他左边和右边第二个和 $a_x$ 同属 $B_i$ 的元素 $a_L,a_R$，一个询问区间 $[l,r]$ 会枚举到 $a_x$，那么一定满足 $L<l\le r<R$，所以对于 $a_x$，只要考虑 $[L,R]$ 这个区间即可。

对每个块 $B_i$ 逐块处理，容易发现对于同一个块，每个 $a_x$ 对应的区间大小总和是 $\mathcal O(n)$ 级别的。

因此所有 $a_x$ 对应的区间大小总和是 $\mathcal O(n\log V)$ 级别的。

对于每个 $a_x$，我们就是要在 $[L,R]$ 中选出两个 $>a_x$ 的数 $a_i,a_j$，满足 $|a_i-a_j|<a_x$，然后把 $(i,j,x)$ 看成一组支配对，最后从左到右扫描线一遍维护每个询问区间里面的最小支配对即可。

那么现在我们只需要将支配对数量优化到一个可以接受的量级，我们设 $b_i=\left\lfloor\dfrac {a_i}{a_x}\right\rfloor$，那么 $|a_i-a_j|<a_x$ 的必要条件是 $|b_i-b_j|\le 1$。

如果 $b_i=b_j$，此时任意的一对 $a_i,a_j$ 都是满足限制的，相当于最小的 $a_i+a_j$，这是经典支配对结论，我们对每个 $b_i$ 维护后缀最小值单调栈。

考虑插入 $a_i$ 时，栈内每个元素 $a_j$ 是否会与 $a_i$ 形成支配对，如果 $a_j\ge a_i$，那么 $a_j$ 会被 $a_i$ 弹出，可以把他们视为支配对，这样的支配对总数和区间长度成线性。

然后考虑所有 $a_j<a_i$ 的点，由于他们在单调栈上，因此 $a_j<a_k<a_i$ 时也有 $j<k<i$，那么 $(i,j)$ 显然不如 $(j,k)$。

因此只有 $a_j<a_i$ 且 $j$ 最大的 $a_j$ 可以与 $a_i$ 形成支配对，这就是弹栈后剩余的栈顶，这样的支配对总数和区间长度也成线性。

然后考虑 $|b_i-b_j|=1$ 的情况。

还是考虑支配对，不妨设 $j<i$ 且 $b_j=b_i-1$，剩余的情况可以翻转区间 $[L,R]$ 做。

那么如果有两个 $j,k$ 同时满足 $b_j=b_k=b_i-1$，那么 $a_j,a_k$ 一定合法且更优。

因此支配对一定是 $[L,i)$ 中第一个 $b_j=b_i-1$ 的 $j$ 对应的 $a_j$。

这部分支配对总数和区间长度依然成线性。

因此所有支配对数量的总和是 $\mathcal O(n\log V)$ 级别的，树状数组维护扫描线即可。

时间复杂度 $\mathcal O(n\log V\log n+q\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef array<int,3> info;
const int MAXN=2.5e5+5,MAXQ=5e5+5,MAXV=1e7+5,inf=1e9;
const void chkmin(int &x,const int &y) { x=x<y?x:y; }
info operator +(info f,info g) {
	for(int x:f) for(int &y:g) if(y>x) swap(x,y);
	return g;
}
int n,q,a[MAXN],bl[MAXN],ql[MAXQ],qr[MAXQ],ans[MAXQ],cnt[MAXN],pre[MAXN],nxt[MAXN];
bool vis[MAXQ];
vector <int> arr[MAXQ];
struct zkwSegt {
	static const int N=1<<18;
	info tr[N<<1];
	void init(int k) {
		for(int i=0;i<N;++i) tr[i+N].fill(inf);
		for(int i=1;i<=n;++i) if(bl[i]==k) tr[i+N][0]=a[i];
		for(int i=N-1;i;--i) tr[i]=tr[i<<1]+tr[i<<1|1];
	}
	info qry(int l,int r) {
		info s{inf,inf,inf};
		for(l+=N-1,r+=N+1;l^r^1;l>>=1,r>>=1) {
			if(~l&1) s=s+tr[l^1];
			if(r&1) s=s+tr[r^1];
		}
		return s;
	}
}	S;
void calc(int &s,const vector<int>&w) {
	int k=w.size(),i=1;
	while(i+1<k&&w[i-1]+w[i]<=w[i+1]) ++i;
	if(i+1>=k) return ;
	int j=i-1,lst=w[i+1]-w[i];
	while(j>0&&w[j-1]>lst) --j;
	chkmin(s,w[j]+w[i]+w[i+1]);
	for(++i;i+1<k;++i) if(w[i+1]-w[i]<lst) {
		for(lst=w[i+1]-w[i];j>0&&w[j-1]>lst;--j);
		chkmin(s,w[j]+w[i]+w[i+1]);
	}
}
vector <array<int,2>> M[MAXN],Q[MAXN];
void ins(int x,int y,int z)	{ M[max({x,y,z})].push_back({min({x,y,z}),a[x]+a[y]+a[z]}); }
vector <int> stk[MAXV];
int b[MAXN],pos[MAXV];
void gen(int id,int l,int r) {
	int x=a[id];
	for(int i=l;i<=r;++i) if(a[i]>x) b[i]=a[i]/x,stk[b[i]].clear();
	for(int i=l;i<=r;++i) if(a[i]>x) {
		vector<int>&s=stk[b[i]];
		while(s.size()&&a[s.back()]>=a[i]) ins(s.back(),id,i),s.pop_back();
		if(s.size()) ins(s.back(),id,i);
		s.push_back(i);
	}
	for(int i=l;i<=r;++i) if(a[i]>x) pos[b[i]]=pos[b[i]-1]=0;
	for(int i=l;i<=r;++i) if(a[i]>x) {
		int j=pos[b[i]-1];
		if(j&&x+a[j]>a[i]) ins(id,j,i);
		pos[b[i]]=i;
	}
	for(int i=l;i<=r;++i) if(a[i]>x) pos[b[i]]=pos[b[i]-1]=0;
	for(int i=r;i>=l;--i) if(a[i]>x) {
		int j=pos[b[i]-1];
		if(j&&x+a[j]>a[i]) ins(id,j,i);
		pos[b[i]]=i;
	}
}
struct FenwickTree {
	int tr[MAXN],s;
	void init() { fill(tr,tr+n+1,inf); }
	void upd(int x,int v) { for(;x;x&=x-1) tr[x]=min(tr[x],v); }
	int qry(int x) { for(s=inf;x<=n;x+=x&-x) s=min(s,tr[x]); return s; }
}	T;
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i],bl[i]=__lg(a[i]);
	for(int i=1;i<=q;++i) cin>>ql[i]>>qr[i],ans[i]=inf;
	for(int k=0;k<24;++k) {
		vector <int> idx;
		S.init(k),memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;++i) if(bl[i]==k) cnt[i]=1,idx.push_back(i);;
		for(int i=1;i<=n;++i) pre[i]=(bl[i]==k?i:pre[i-1]);
		for(int i=n;i>=1;--i) nxt[i]=(bl[i]==k?i:nxt[i+1]);
		for(int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
		for(int i=1;i<=q;++i) if(!vis[i]) {
			int w=cnt[qr[i]]-cnt[ql[i]-1];
			if(w<3) {
				if(w>1) {
					int x=nxt[ql[i]],y=pre[qr[i]];
					if(a[x]>a[y]) swap(x,y);
					arr[i].push_back(a[x]),arr[i].push_back(a[y]);
				} else if(w) arr[i].push_back(a[nxt[ql[i]]]);
			} else {
				info z=S.qry(ql[i],qr[i]);
				arr[i].push_back(z[0]),vis[i]=true;
				chkmin(ans[i],z[0]+z[1]+z[2]);
			}
		}
		int m=idx.size();
		for(int i=0;i<m;++i) gen(idx[i],i>1?idx[i-2]+1:1,i+2<m?idx[i+2]-1:n);
	}
	for(int i=1;i<=q;++i) calc(ans[i],arr[i]),Q[qr[i]].push_back({ql[i],i});
	T.init();
	for(int i=1;i<=n;++i) {
		for(auto z:M[i]) T.upd(z[0],z[1]);
		for(auto z:Q[i]) chkmin(ans[z[1]],T.qry(z[0]));
	}
	for(int i=1;i<=q;++i) {
		if(ans[i]==inf) cout<<"yumi!\n";
		else cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：lalaouye (赞：2)

首先发现若序列是有序的，那么我们让最大值和次大值相邻一定是最优的。

但是问题仍然不好做，而问题唯一的限制是 $a_i+a_j>a_k$，这里钦定了 $a_i<a_j<a_k$。这启发我们使用倍增分块，我们发现这样分块之后，块内的任意三个值都可以成为答案，并且隔块的贡献形式更加简单了。我们知道一共只有 $\log V$ 个块，我们每次可以找到最小的有三个元素的块，将前三小值算入答案，其它答案必须要有一个元素在更小的块中，然而更小的块中的元素总量只有 $\mathcal{O}(\log V)$ 级别，明示我们枚举这个更小的值。

但是这里有两种不同的情况，一个是较好处理的，即有两个元素都在前半部分。我们直接枚举次大值和最大值，最小值可以双指针处理，因为如果次大值和最大值在变大，要想答案更优显然最小值需要变小。

还有一种情况比较棘手，即只有最小值在前半部分，我们考虑枚举这个最小值，但是直接维护好像是不好维护的，反过来考虑最小值什么时候有贡献，显然对于每个最小值所在的块中元素小于等于 $2$，即只会包含它的前一个或后一个同块元素，设某个块包含的元素的位置为 $p_1,\cdots,p_k$，那么对于 $p_i$ 位置上的元素只会在 $(p_{i-2},p_{i+2})$ 这个区间中的区间产生贡献，我们发现所有元素的这些区间长度加起来也只是 $\mathcal{O}(n\log V)$ 级别的，不妨考虑先处理出一些有效的预选答案，也就是支配对，然后再做扫描。

然而我们发现支配对个数与区间长度呈正比关系。现在我们来从统计过程方面给出证明。首先限制为 $a_i+a_j>a_k$，我们设 $b_j=\frac {a_j} {a_i}$，那么对于 $a_i$ 满足条件的 $j,k$ 要么 $b_j=b_k$ 要么 $b_j+1=b_k$。先处理前面的情况，我们发现前者的条件是充分的。我们考虑用单调栈维护相同 $b_j$ 的后缀最小值，那么在加入 $a_j$ 的时候，所有出栈的 $k$ 显然都要算如答案，然而对于没有出栈的元素我们发现我们只需要与栈顶配对即可，这样下来支配对个数就控制在线性了。

接下来考虑后者。首要的问题是思考从枚举大的入手还是小的入手，发现如果枚举小的的话是不好限制的，于是我们枚举 $a_k$，我们发现对于 $a_k$ 只会与左边第一个 $a_j$ 和右边第一个 $a_j$ 配对，这样下来支配对个数仍然控制在线性。

最后树状数组加扫描线维护即可，时间复杂度 $\mathcal{O}(n\log n\log V)$。这题可能会有些卡常，如果你使用了 ``vector`` 维护栈操作，这边建议你改成 ``basic_string``，是好心的出题人告诉我的，但具体原理我不清楚，如果有巨佬知道可以在评论区解答一下，具体实现可以看我的代码：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 1000000000
#define ls (p << 1)
#define rs (ls | 1)
constexpr int N = 2.5e5 + 5, B = 1e8 + 1, P = 998244353;
typedef long long ll;
typedef array<int, 3> info; 
int n, m;
int a[N];
int pre[N], nxt[N];
namespace sgt {
  int mn[N];
  void init () {
    rep (i, 0, N - 1) mn[i] = inf;
  }
  int lb (int x) { return x & -x; }
  void upd (int x, int k) {
    for (; x; x -= lb (x)) mn[x] = min (mn[x], k);
  }
  int qry (int x) {
    int ret (inf);
    for (; x <= n; x += lb (x)) ret = min (ret, mn[x]);
    return ret;
  }
}
class node {
  public:
  int l, r, id;
} q[N << 1];
int ans[N << 1], lg, b[N];
bool vis[N << 1];
info mn[N << 2], I;
info merge (info f, info g) {
  for (auto u : f) if (u < inf) { for (auto &v : g) if (v > u) swap (u, v); } else break;
  return g;
}
void Merge (info f, info &g) {
  for (auto u : f) if (u < inf) { for (auto &v : g) if (v > u) swap (u, v); } else break;
}
void build (int p, int l, int r) {
  if (l == r) {
    mn[p][0] = mn[p][1] = mn[p][2] = inf;
    if (__lg (a[l]) == lg) mn[p][0] = a[l];
    return ;
  } int mid (l + r >> 1);
  build (ls, l, mid), build (rs, mid + 1, r);
  if (mn[ls][0] == inf && mn[rs][0] == inf) mn[p] = I;
  else
  mn[p] = merge (mn[ls], mn[rs]);
}
info ret;
void qry (int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) return Merge (mn[p], ret);
  int mid (l + r >> 1); 
  if (L <= mid) qry (ls, l, mid, L, R);
  if (R > mid) qry (rs, mid + 1, r, L, R);
}
vector <int> vec[N << 1];
basic_string <int> stk[10000005];
int lst[10000005];
vector <pii> vc[N];
int sum[N];
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  I[0] = I[1] = I[2] = inf;
  n = rd (), m = rd ();
  rep (i, 1, n) a[i] = rd ();
  rep (i, 1, m) {
    ans[i] = inf;
    q[i].l = rd (), q[i].r = rd (), q[i].id = i;
  }
  rep (k, 0, 24) {
    memset (nxt, 0, sizeof nxt);
    memset (pre, 0, sizeof pre);
    lg = k; build (1, 1, n);
    rep (i, 1, n) sum[i] = sum[i - 1] + (__lg (a[i]) == k);
    rep (i, 1, n) if (__lg (a[i]) == k) nxt[i] = pre[i] = i;
    rep (i, 1, n) if (! pre[i]) pre[i] = pre[i - 1];
    nxt[n + 1] = nxt[n + 2] = n + 1;
    rrp (i, 1, n) if (! nxt[i]) nxt[i] = nxt[i + 1];
    rep (i, 1, m) if (! vis[i]) {
      int l (q[i].l), r (q[i].r);
      if (sum[r] - sum[l - 1] <= 2) {
        int p (nxt[l]);
        if (p <= r) vec[i].eb (a[p]);
        p = nxt[p + 1];
        if (p <= r) vec[i].eb (a[p]);
      } else {
        ret = I;
        qry (1, 1, n, l, r);
        vec[i].eb (ret[0]);
        ans[i] = ret[0] + ret[1] + ret[2];
        vis[i] = 1;
      }
    }
    rep (i, 1, n) {
      if (__lg (a[i]) == k) {
        int x (a[i]);
        int L = pre[i - 1], R = nxt[i + 1];
        if (L) L = pre[L - 1];
        R = nxt[R + 1];
        ++ L, -- R;
        rrp (j, L, R) {
          if (a[j] <= x) continue;
          b[j] = a[j] / x;
          basic_string <int> &s = stk[b[j]];
          while (! s.empty () && a[s.back ()] >= a[j]) {
            int l (min (i, j)), r (max (i, s.back ()));
            vc[r].eb (pii (l, x + a[j] + a[s.back ()]));
            s.pop_back ();
          }
          if (! s.empty ()) {
            int l (min (i, j)), r (max (i, s.back ()));
            if (sum[r] - sum[l - 1] < 3)
            vc[r].eb (pii (l, x + a[j] + a[s.back ()]));
            else s.clear ();
          }
          s.push_back (j);
          lst[b[j]] = j;
          if (! lst[b[j] - 1]) continue;
          int Ls (lst[b[j] - 1]);
          if (x + a[Ls] > a[j]) vc[max (i, Ls)].eb (pii (min (i, j), x + a[j] + a[Ls]));
        }
        rep (j, L, R) if (a[j] >= x) lst[b[j]] = 0;
        rep (j, L, R) {
          if (a[j] <= x) continue;
          lst[b[j]] = j;
          if (! lst[b[j] - 1]) continue;
          int Ls (lst[b[j] - 1]);
          if (x + a[Ls] > a[j]) vc[max (i, j)].eb (pii (min (i, Ls), x + a[j] + a[Ls]));
        }
        rep (j, L, R) if (a[j] >= x) stk[b[j]].clear (), lst[b[j]] = 0;
      } 
    }
  }
  rep (i, 1, m) {
    sort (vec[i].begin (), vec[i].end ());
    int p (0); bool fl (0);
    for (int j (1); j + 1 < vec[i].size (); ++ j) {
      if (! fl) {
        p = j - 1;
        if (vec[i][p] + vec[i][j] > vec[i][j + 1]) fl = 1;
      }
      if (fl) {
        while (p > 0 && vec[i][p - 1] + vec[i][j] > vec[i][j + 1]) -- p;
      }
      if (vec[i][p] + vec[i][j] > vec[i][j + 1]) ans[i] = min (ans[i], vec[i][p] + vec[i][j] + vec[i][j + 1]);//,cout<<i<<" "<<j<<" "<<p<<" "<<vec[i][p]<<" "<<vec[i][j]<<" "<<vec[i][j + 1] <<endl;
    }
    vc[q[i].r].eb (- q[i].l, i);
  }
  sgt::init ();
  rep (i, 1, n) {
    for (auto p : vc[i]) {
      if (p.first > 0) sgt::upd (p.first, p.second);
    }
    for (auto p : vc[i]) {
      if (p.first < 0) ans[p.second] = min (ans[p.second], sgt::qry (- p.first));
    }
  }
  rep (i, 1, m) {
    if (ans[i] < inf) printf ("%d\n", ans[i]); else puts ("yumi!");
  }
}
```

---

## 作者：wwwwwza (赞：0)

很厉害的一道题，[加强版](https://www.luogu.com.cn/problem/P12084)。

先将值域按 $[2^k,2^{k+1})$ 分块。

显然，在一个块内，怎么取都是满足三角形三遍关系的。所以对于每一个询问，找到最小的块满足在询问区间中含有至少 $3$ 个数。线段树维护即可，因为询问比较多，所以要用前缀和找出满足条件的块。

- 如果有两个或三个元素 $<2^k$。

假设这三个元素是 $(a,b,c)$，那么 $b$ 和 $c$ 一定是相邻的，若 $b<p<c$，那么选 $(a,b,p)$ 一定更优。

因为对于每个 $i<k$ 在值域 $[2^i,2^{i+1})$ 中最多含有两个数，不然 $k$ 还能更小。

那么在值域 $[1,2^k)$ 中的数的个数是 $\log V$ 级别的。

因为较长边和最长边长度相邻，所以直接枚举较长边在哪。当 $i<j$ 时 $(a,lst_i,lst_{i+1})$ 比 $(b,lst_j,lst_{j+1})$ 更优，那么 $a>b$，换句话说就是 $lst_{i+1}-lst_{i}>lst_{j+1}-lst_j$，直接单调栈维护就可以了。

最长边的数值可以 $\ge 2^k$，不要忘记处理。

- 如果有一个元素 $<2^k$。

那么这个元素一定是最小值，令这个元素为 $a_x$。

正着算不太好做，考虑在询问区间是什么时能取到最短边为 $a_x$ 的情况。

显然，询问区间不能包含三个即以上个与 $a_x$ 所在值域块相同的值（包含 $a_x$），这个区间可以预处理出来。显然，所有区间的长度和是 $n\log V$ 级别的。

将所有 $>a_x$ 的数拿出来处理。

设 $b_i=\left \lfloor \frac{a_i}{a_x} \right \rfloor $，当 $(a_i,a_j,a_x)$ 满足条件时，$\left | b_i-b_j \right | \le 1$ 也一定满足。

当 $\left | b_i-b_j \right | =0$ 时。

所有 $(a_i,a_j,a_x)$ 都满足条件，但是有些区间被支配了，其实是没有用的。

考虑用一个单调栈，每加入一个数 $a_i$，就将 $\ge a_i$ 的数弹出，这些数与 $a_i$ 不会被支配。除此之外， $a_i$ 与栈顶的元素也会形成一个支配对。（至于为什么可以画下图）。

注意一下要开 $V$ 个单调栈。

支配对数量是线性的。

当 $\left | b_i-b_j \right | =1$ 时。

显然 $j$ 一定在 $i$ 左边或右边第一个满足 $b_j=b_i-1$ 的位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/pa6ld7ld.png)

这个的支配对数量也是线性的。

总的支配对数量是 $n\log V$ 级别的，树状数组和扫描线维护。

总时间复杂度为 $O(n\log V\log n+q\log V)$。

这里的代码通过不了 Ynoi 那题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+1;
const int V=1e7+1; 
const int inf=1e8;
int n,m,a[N],ans[N<<1];
int id[N],pre[N][24],nxt[N][24],lst[N];
struct ques{
	int l,r,bl,mn,id;
	bool operator <(const ques &b)const{
		return l>b.l;
	}
}q[N<<1];
vector<int>cur[24];
struct Tree{
	int a,b,c;
}tree[N<<2];
int _[8];
inline Tree pushup(Tree x,Tree y){
	_[0]=x.a,_[1]=x.b,_[2]=x.c;
	_[3]=y.a,_[4]=y.b,_[5]=y.c;
	sort(_,_+6);
	return (Tree){_[0],_[1],_[2]};
}
inline void build(int rt,int l,int r,int j){
	tree[rt]={inf,inf,inf};
	if(l==r){
		if(id[l]==j)tree[rt].a=a[l];
		return;
	}
	int mid=l+r>>1;
	build(rt<<1,l,mid,j),build(rt<<1|1,mid+1,r,j);
	tree[rt]=pushup(tree[rt<<1],tree[rt<<1|1]);
}
inline Tree query(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[rt];
	int mid=l+r>>1;
	Tree res={inf,inf,inf};
	if(x<=mid)res=pushup(res,query(rt<<1,l,mid,x,y));
	if(y>mid)res=pushup(res,query(rt<<1|1,mid+1,r,x,y));
	return res;
}
int tr[N],id_[V];
vector<int>B[V];
struct node{
	int r,x;
};
vector<node>line[N];
inline void pls(int x,int d){
	while(x<=n){
		tr[x]=min(tr[x],d);
		x+=x&(-x);
	}
}
inline int ask(int x){
	int res=inf;
	while(x){
		res=min(res,tr[x]);
		x-=x&(-x);
	}
	return res;
}
inline void solve(){
	for(int i=0;i<=n;i++)tr[i]=inf;
	for(int i=1,j=n;i<=m;i++){
		while(j&&j>=q[i].l){
			for(int k=0;k<line[j].size();k++)pls(line[j][k].r,line[j][k].x);
			j--;
		}
		ans[q[i].id]=min(ans[q[i].id],ask(q[i].r));
	}
}
inline void add(int i,int j,int k){
	if(2*max(max(a[i],a[j]),a[k])<a[i]+a[j]+a[k]){
		line[min(min(i,j),k)].push_back({max(max(i,j),k),a[i]+a[j]+a[k]});
	}
}
inline void calc(int l,int r,int pos){
	for(int i=l;i<=r;i++)if(a[i]>a[pos])lst[i]=a[i]/a[pos];
	
	for(int i=l;i<=r;i++)if(a[i]>a[pos]){
		lst[i]=a[i]/a[pos];
		while(!B[lst[i]].empty()&&a[B[lst[i]].back()]>=a[i]){
			add(B[lst[i]].back(),i,pos);
			B[lst[i]].pop_back();
		}
		if(!B[lst[i]].empty())add(B[lst[i]].back(),i,pos);
		B[lst[i]].push_back(i);
	}
	for(int i=l;i<=r;i++)if(a[i]>a[pos])B[lst[i]].clear();
	
	for(int i=l;i<=r;i++)if(a[i]>a[pos]){
		if(id_[lst[i]-1])add(id_[lst[i]-1],i,pos);
		id_[lst[i]]=i;
	}
	for(int i=l;i<=r;i++)if(a[i]>a[pos])id_[lst[i]]=0;
	
	for(int i=r;i>=l;i--)if(a[i]>a[pos]){
		if(id_[lst[i]-1])add(id_[lst[i]-1],i,pos);
		id_[lst[i]]=i;
	}
	for(int i=l;i<=r;i++)if(a[i]>a[pos])id_[lst[i]]=0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n>>m;
	for(int i=1;i<=n;i++){
		cin >>a[i];
		for(int j=0;j<24;j++){
			if((1<<j)<=a[i])id[i]=j;
			else break;
		}
	}
	for(int i=1;i<=n;i++){
		pre[i][id[i]]++;
		for(int j=0;j<24;j++)pre[i][j]+=pre[i-1][j];
	}
	for(int i=1;i<=m;i++){
		cin >>q[i].l>>q[i].r;
		ans[i]=inf,q[i].bl=24,q[i].mn=inf,q[i].id=i;
		for(int j=0;j<24;j++){
			if(pre[q[i].r][j]-pre[q[i].l-1][j]>=3){
				cur[j].push_back(i),q[i].bl=j;
				break;
			}
		}
	}
	for(int j=0;j<24;j++){
		build(1,1,n,j);
		for(int i=0;i<cur[j].size();i++){
			int t=cur[j][i];
			Tree res=query(1,1,n,q[t].l,q[t].r);
			ans[t]=res.a+res.b+res.c;
			q[t].mn=res.a;
		}
	}
	for(int i=0;i<24;i++)lst[i]=0;
	for(int i=1;i<=n;i++){
		lst[id[i]]=i;
		for(int j=0;j<24;j++)pre[i][j]=lst[j];
	}
	for(int i=0;i<24;i++)lst[i]=n+1;
	for(int i=n;i>=1;i--){
		lst[id[i]]=i;
		for(int j=0;j<24;j++)nxt[i][j]=lst[j];
	}
	for(int i=0;i<24;i++)pre[0][i]=0,nxt[n+1][i]=n+1;
	
	for(int i=1;i<=m;i++){
		int tot=0;
		for(int j=0;j<q[i].bl;j++){
			int x=pre[q[i].r][j],y=pre[x-1][j];
			if(x<q[i].l)continue;
			x=a[x];
			if(y<q[i].l)y=inf,lst[++tot]=x;
			else{
				y=a[y];
				if(x>y)swap(x,y);
				lst[++tot]=x,lst[++tot]=y;
			}
		}
		lst[++tot]=q[i].mn;
		for(int j=2,flag=0,opt=0;j<tot;j++){
			if(lst[j-1]+lst[j]>lst[j+1]&&!flag)flag=1,opt=j-1;
			while(opt>1&&lst[opt-1]+lst[j]>lst[j+1])opt--;
			if(flag&&opt&&lst[opt]+lst[j]>lst[j+1]){
				ans[i]=min(ans[i],lst[j]+lst[j+1]+lst[opt]);
			}
		}
	}
	sort(q+1,q+1+m);
	
	for(int i=1;i<=n;i++){
		int lpos=pre[i-1][id[i]],rpos=nxt[i+1][id[i]];
		if(lpos!=0)lpos=pre[lpos-1][id[i]];
		if(rpos!=n+1)rpos=nxt[rpos+1][id[i]];
		calc(lpos+1,rpos-1,i);
	}
	solve();
	for(int i=1;i<=m;i++){
		if(ans[i]==inf)cout <<"yumi!\n";
		else cout <<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：0)

**[P10882 [JRKSJ R9] ZYPRESSEN](https://www.luogu.com.cn/problem/P10882)**

咕了一个月后来补题解。

第一眼支配对，然后没有第二眼了。

> - 给出序列 $(a_1,\dots,a_n)$。$q$ 次询问 $l,r$，求 $l\le i<j<k\le r$ 且存在以 $a_i,a_j,a_k$ 为三边长度的三角形的三元组 $(i,j,k)$ 的 $a_i+a_j+a_k$ 最小值。
> - $n\le 2.5\times 10^5$，$q\le 5\times 10^5$，$a_i\le 10^7$。

考虑按照二进制最高位将值域划分成若干个块，记 $B_m=[2^m,2^{m+1})$。设值域为 $V$。

显然不用考虑 $(i,j,k)$ 之间的大小关系，只要求她们不同且都在区间里面就一定可以将三元组写成递增的形式。注意到同块中任意三个元素均能作为三角形边长，因此对于每个询问，考虑找到最小的 $m$ 使得 $(a_l,\dots,a_r)$ 在 $B_m$ 中有 $\ge3$ 个元素。此时选取前三小值即可。线段树维护之，合并可以看成左右儿子信息归并。

这里可以考虑从小到大枚举每个块，再枚举询问，更新所有未被标记且在她中有 $\ge 3$ 个元素的询问，然后标记这个询问。每个询问至多被标记一次，这时才会触发查询，因此时间复杂度为 $\mathcal{O}(q\log n)$。

对于剩下的方案，如果想要更优，则必须至少存在一个 $<2^k$ 的元素。判断区间中某块内的元素个数可以先预处理该块内元素的前缀出现次数然后前缀相减。枚举每个块时都要处理一次，时间复杂度为 $\mathcal{O}(n\log |V|)$。

- 若存在 $2$ 个 $<2^m$ 的元素

  注意到找到的是最小的 $m$ 使得 $(a_l,\dots,a_r)$ 在 $B_m$ 中有 $\ge3$ 个元素，因此对于编号为 $[1,m)$ 的块，$(a_l,\dots,a_r)$ 中的元素在其中的出现次数 $\le 2$，即前 $m-1$ 个块总共只有 $\mathcal{O}(\log |V|)$ 个元素。先把她们全部找出来。可以考虑维护每个位置前 / 后（包含这个位置）第一个块内元素（前驱 / 后继），然后找 $l$ 的后继和 $r$ 的前驱即可。注意仅有 $1$ 个元素时不要重复找。可以对于每个询问维护一个容器，枚举到每个块时，若 $(a_l,\dots,a_r)$ 中的元素在其中的出现次数 $\le 2$，就找出 $\mathcal{O}(1)$ 个元素插入对应询问的容器里。还需要有序。但是从小到大枚举值域块已经保证块间的顺序了，只要在插入 $\mathcal{O}(1)$ 个元素时判断大小关系即可。

  不妨认为 $a_i\le a_j\le a_k$，则 $a_i\le a_j<2^m$。若 $(i,j,k)$ 能产生贡献，则区间中一定不存在 $(a_j,a_k)$ 内的元素，不然最长边更换成她一定更优。换言之 $k$ 一定是区间中除了 $a_i,a_j$ 以外最小的 $\ge a_j$ 的元素。那么 $a_k$ 一定在找出来的 $\mathcal{O}(\log |V|)$ 个元素中或者在 $(a_l,\dots,a_r)$ 内 $B_k$ 中最小的元素。若 $(a_l,\dots,a_r)$ 内没有 $B_k$ 中的元素则不用考虑，因为 $k$ 以后的块中的元素是无法和 $a_i,a_j$ 产生贡献的。

  记找出来的元素集合非降排序后为 $(s_1,\dots,s_t)$，枚举 $s_u$ 作为 $a_j$，则 $a_k=s_{u+1}$。此时需要找到最小的 $v$ 使得 $s_v>s_{u+1}-s_u$。注意到 $u$ 递增时若 $s_{u+1}-s_u$ 也递增，则 $a_j,a_k$ 两条边长度变大，$a_i$ 这条边的限制也变大，一定不优。因此只要考虑 $s_{u+1}-s_u$ 为前缀最小值的情况，此时她单调递减，因此 $s_v$ 也单调不升，用双指针维护即可。

  每个询问仅在找到对应的 $m$ 后才会触发双指针统计，因此时间复杂度为 $\mathcal{O}(q\log |V|)$。

- 若仅有 $1$ 个 $<2^m$ 的元素。

  此时 $a_i$ 是最短边。考虑枚举这个元素 $a_i$ 在第 $w$ 块。可以在枚举每一块的时候处理其中的所有元素。记 $i$ 前第 $x$ 个与 $a_i$ 同块的元素位置为 $\text{pre}_x$，$i$ 后第 $x$ 个同块元素位置为 $\text{nxt}_x$，则仅需要考虑 $(\text{pre}_2,\text{nxt}_2)$ 内的 $j,k$，否则若一个询问需要用到这之外的 $j,k$ 构成的 $(i,j,k)$ 的询问，则至少包含 $\text{pre}_2,\text{pre}_1,i$ 或 $i,\text{nxt}_1,\text{nxt}_2$ 这三个 $B_w$ 内的元素。而 $a_i$ 已经是最短边了，所以 $a_j,a_k\ge 2^w$。则此时 $(i,j,k)$ 这个三元组一定不如 $B_w$ 块内前三小值优。而满足在询问区间中有至少三个元素的块 $b$ 一定 $\le w$。因此 $(i,j,k)$ 就没有贡献了。

  而对于 $B_w$ 内的元素而言 $|(\text{pre}_2,\text{nxt}_2)|$ 的总和是 $\mathcal{O}(n)$ 的，考虑每对相邻的同块元素的间距只会在 $\mathcal{O}(1)$ 个区间中产生贡献。而间距的总和是 $\mathcal{O}(n)$ 的。那么对于所有块，区间长度总和就是 $\mathcal{O}(n\log |V|)$。

  这时就可以直接枚举区间内大于 $a_i$ 的元素了。钦定 $a_k$ 为 $a_j,a_k$ 中较大元素，若 $a_j=a_k$，则钦定 $a_k$ 为靠右的元素。令 $e_x=\left\lfloor\dfrac{a_x}{a_i}\right\rfloor$，则 $(i,j,k)$ 合法的 **必要条件** 是 $e_k-e_j\le 1$。

  若 $e_k=e_j$，则任意 $(i,j,k)$ 都可行。直接把所有点对找出来不可接受，考虑找支配对。对于两个 **本质不同** 的点对，称 $(i,j_1,k_1)$ 支配了 $(i,j_2,k_2)$ 当且仅当 $\min\{j_2,k_2\}\le \min\{j_1,k_1\}\le \max\{j_1,k_1\}\le \max\{j_2,k_2\}$ 且 $a_i+a_{j_1}+a_{k_1}\le a_{i}+a_{j_2}+a_{k_2}$。容易发现若一个点对被支配，则她对任何一个询问都没有贡献，因为若她在询问的区间内，则支配她的点对也在询问的区间内，且和更小。我们发现**有贡献的点对一定满足在大于 $a_i$ 且 $e_k=e_j$ 的位置中，$a_j$ 是 $k$ 左边第一个 $\le a_k$ 的元素，或 $k$ 右边第一个 $<a_k$ 的元素**。给出前者的证明：

  假使存在 $j<p<k$ 使得 $a_i<a_j,a_p\le a_k$，若 $a_p<a_j$，则 $(i,p,k)$ 支配了 $(i,j,k)$；否则 $(i,j,p)$ 支配了 $(i,j,k)$。后者的证明类似。

  那么就可以枚举 $k$，然后对于每种 $e_k$ 维护单调栈就可以得到 $j$ 的位置了。

  若 $e_k=e_j+1$，则有贡献的点对一定满足 $j$ 一定是 $k$ 左 / 右第一个 $e_j=e_k-1$ 的位置。给出在左边情况的证明：假使存在 $j<p<k$ 使得 $e_j=e_p=e_k-1$，则 $(i,j,p)$ 支配了 $(i,j,k)$，右边的情况类似。

  此时，我们发现对于每个 $a_i$ 的区间内的位置 $k$，都找出了关于她的 $\mathcal{O}(1)$ 个可能有贡献的点对，因此总共有 $\mathcal{O}(n\log |V|)$ 个点对。对于一次询问只需要考虑这些点对即可，相当于查询 $\min\{i,j,k\}\ge l,\max\{i,j,k\}\le r$ 的点对中 $a_i+a_j+a_k$ 的最小值，直接扫描线配合树状数组维护即可。

到这里基本结束了。时间复杂度为 $\mathcal{O}((n\log |V|+q)\log |V|)$，空间复杂度为 $\mathcal{O}(q\log |V|+|V|)$。如果扫描线时使用高级点的数据结构可以做到更优时间复杂度。空间带 $|V|$ 的原因是对于每种 $e_k$ 开了单调栈，如果离散化可以做到更优。

然后我的实现被卡常了，加了指令集也会不时被卡。联系出题人要求时限增大 $0.5\text{ s}$ 未果。建议被卡常的找个夜深人静的时候多交几发试试。

[AC Link](https://www.luogu.com.cn/record/182366286)
 / [Code](https://www.luogu.com.cn/paste/yg7t2bnd)

---

