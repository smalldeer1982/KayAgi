# Recursive Queries

## 题目描述

有一个长度为$n$的排列$p_1,p_2,\dots,p_n$，还有$q$次询问，每次询问一段区间$[l_i, r_i]$，你需要计算出$f(l_i, r_i)$。

定义$m_{l, r}$表示$p_l, p_{l+1}, \dots, p_r$这一段数列的最大值的出现位置，则

$$f(l, r) =\begin{cases}(r-l+1)+f(l,m_{l,r}-1)+f(m_{l,r}+1,r)&\text{if $l<=r$}\\0&\text{else}\end{cases}$$

## 样例 #1

### 输入

```
4 5
3 1 4 2
2 1 1 2 1
2 3 4 4 1
```

### 输出

```
1 6 8 5 1 
```

# 题解

## 作者：chen_03 (赞：12)

因为我比较菜，所以我用的是笛卡尔树。

观察 $f(l,r)$ 的式子，可以发现它就是把区间 $[l,r]$ 中的数拿出来建笛卡尔树，树上所有节点的深度之和。

显然我们不能对于每次询问都建一棵笛卡尔树，所以我们尝试在整个数组的笛卡尔树上做些文章。但如果我们把一个区间在整个数组的笛卡尔树上表示出来，区间中的节点可能非常分散，不好处理。那该怎么办呢 qwq

观察[线性构建笛卡尔树的算法](https://www.luogu.com.cn/problem/P5854)，它是一个在线算法。也就是说，我们可以得到所有区间 $[1,r]\ (1\le r\le n)$ 的笛卡尔树。我们尝试把区间 $[l,r]$ 在 $[1,r]$ 的笛卡尔树上表示出来。

记区间 $[l,r]$ 中最大值的出现位置为 $m$，则对于区间 $[l,r]$ 的笛卡尔树，$m$ 是它的根节点，根节点的右子树是区间 $[m+1,r]$ 的笛卡尔树。

考虑另一种构建笛卡尔树的算法：每次取出当前区间的最大值，然后递归处理左右区间。那么对于区间 $[1,r]$ 的笛卡尔树，$m$ 一定是 $[l,r]$ 中最先被取出的，即 $m$ 的深度是 $[l,r]$ 中最小的。$m$ 被取出后，$[m+1,r]$ 就成为了它的右区间，即 $m$ 的右子树是区间 $[m+1,r]$ 的笛卡尔树。

可以发现，我们可以在区间 $[1,r]$ 的笛卡尔树上得到区间 $[m+1,r]$ 的笛卡尔树。对于区间 $[l,m-1]$ 的笛卡尔树，可以把整个数组翻转，用同样的方法得到。它们合起来就是区间 $[l,r]$ 的笛卡尔树。

那么我们在构建笛卡尔树时，要动态修改每个节点的深度，并查询区间 $[m+1,r]$ 中所有节点的深度之和以及 $m$ 的深度（由于 $m$ 的深度不一定为 $1$，要注意减掉 $m$ 的深度带来的影响）。这是一个区间加、区间求和的问题，用树状数组或线段树维护即可。

还有一个问题就是如何快速找到 $m$。考虑单调栈维护的是从根节点开始不断往右儿子走形成的链。由于 $r$ 一定在这条链上，且 $r$ 在 $m$ 的右子树中，所以 $m$ 也在这条链上。由于 $m$ 的深度是 $[l,r]$ 中最小的，所以我们在单调栈上二分，第一个满足编号 $\ge l$ 的节点就是 $m$。

时间复杂度 $\mathcal{O}((n+q)\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m,a[1000005],stk[1000005],top; //连左右儿子都不用记录
ll sum[1000005],sum2[1000005],ans[1000005];
struct qry{
	int l,r,id;
}q[1000005];
inline bool cmp(qry x,qry y){
	return x.r<y.r;
}
inline void modify(ll *a,int x,ll y){
	for(;x<=n;x+=x&-x)a[x]+=y;
}
inline ll query(ll *a,int x){
	ll res=0;
	for(;x;x&=x-1)res+=a[x];
	return res;
}
inline void Modify(int l,int r,ll x){
	modify(sum,l,x);
	modify(sum2,l,x*l);
	modify(sum,r+1,-x);
	modify(sum2,r+1,-x*(r+1));
}
inline ll Query(int l,int r){
	return (r+1)*query(sum,r)-query(sum2,r)-l*query(sum,l-1)+query(sum2,l-1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=m;++i)
		scanf("%d",&q[i].l);
	for(int i=1;i<=m;++i){
		scanf("%d",&q[i].r);
		q[i].id=i;
		ans[i]=q[i].r-q[i].l+1;
	}
	sort(q+1,q+1+m,cmp);
	for(int i=1,j=1,pre,x;i<=n;++i){
		pre=top;
		while(top && a[i]>a[stk[top]])--top;
		if(top)Modify(i,i,Query(stk[top],stk[top])+1);
		else Modify(i,i,1);
		if(top!=pre)Modify(stk[top]+1,i-1,1);
		stk[++top]=i;
		while(j<=m && q[j].r==i){
			x=*lower_bound(stk+1,stk+1+top,q[j].l);
			ans[q[j].id]+=Query(x+1,i)-(i-x)*Query(x,x);
			++j;
		}
	}
	reverse(a+1,a+1+n);
	for(int i=1;i<=m;++i){
		swap(q[i].l,q[i].r);
		q[i].l=n-q[i].l+1;
		q[i].r=n-q[i].r+1;
	}
	sort(q+1,q+1+m,cmp);
	memset(sum,0,sizeof(sum));
	memset(sum2,0,sizeof(sum2));
	top=0;
	for(int i=1,j=1,pre,x;i<=n;++i){
		pre=top;
		while(top && a[i]>a[stk[top]])--top;
		if(top)Modify(i,i,Query(stk[top],stk[top])+1);
		else Modify(i,i,1);
		if(top!=pre)Modify(stk[top]+1,i-1,1);
		stk[++top]=i;
		while(j<=m && q[j].r==i){
			x=*lower_bound(stk+1,stk+1+top,q[j].l);
			ans[q[j].id]+=Query(x+1,i)-(i-x)*Query(x,x);
			++j;
		}
	}
	for(int i=1;i<=m;++i)
		printf("%lld%c",ans[i]," \n"[i==m]);
	return 0;
}
```


---

## 作者：RenaMoe (赞：12)



> 给出一个长为 n 的排列，每次给出询问 $[l_i,r_i]$（可以离线），求 $f(l_i,r_i)$：
> $$
> f(l,r)=\begin{cases}
> (r-l+1)+f(l,m_{l,r}-1)+f(m_{l,r}+1,r)\quad &(l\le r)\\
> 0\quad &(l > r)
> \end{cases}
> $$
>
> $m_{l,r}$ 为 $[l,r]$ 的最大值的位置。

## 思路

### 转化题意

给出的式子应该很好理解吧，就是区间最大值将区间分开，递归下去。

那么一个区间的最大值也就代表这个区间，其贡献为区间长度。

最后该区间的答案就是每个点的贡献之和。

设 i 左边第一个大于 $a_i$ 的位置为 $lb(i)$，右边第一个大于 $a_i$ 的位置为 $rb(i)$，（若无该位置，$lb(i)=0,rb(i)=n+1$）。

其实就是要统计：

$$
\sum_{i=l}^r\min(rb(i)-1,r)-\max(lb(i)+1,l)+1
$$

### 预处理 $lb(i),rb(i)$

利用**单调栈** $O(n)$ 处理即可。

```cpp
int top = 0;
for (int i = 1; i <= n; ++i) {
    while (top && a[stk[top]] < a[i])
        rb[stk[top--]] = i;
    lb[i] = stk[top];
    stk[++top] = i;
}
while (top) rb[stk[top--]] = n + 1;
```

### 离线统计

现将每个点的贡献**拆开**，分别统计 $lb(i),rb(i)$，需要区间求和。

以统计 $lb(i)$ 为例：

注意到如果 $i\in [l,r],lb(i)+1<l$，该点贡献为 $l$。

我们将所有询问离线下来，固定 l，对每个 r 区间求和。

每次向右移动 l，所有 $lb(i)=l$ 的位置的贡献都应该改为 l。

那么就把这些位置去掉贡献，打上 tag，每次统计答案时，统计区间有 tag 的个数另外计算。

单点修改，区间查询，开两棵**树状数组**分别维护 $lb(i)$ 的贡献和 tag 个数。

统计 $rb(i)$ 的贡献同理，**倒着**做就行。

## 代码

```cpp
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

namespace RenaMoe {
template <typename TT> inline void read(TT &x) {}

typedef long long LL;
const int N = 1e6 + 9;

struct Ask {
	int l, r;
};

int n, m;
int a[N], lb[N], rb[N], stk[N];
LL ans[N];
Ask q[N];
vector<int> qry[N], del[N]; // qry[i]：左端点为i的询问，del[i]：lb为i的位置

struct Bit {
	LL tr[N];
	inline void clear() {
		memset(tr, 0, sizeof tr);
	}
	inline void update(int x, LL k) {
		for (int i = x; i <= n; i += i & -i)
			tr[i] += k;
	}
	inline LL query(int x) {
		LL re = 0;
		for (int i = x; i; i -= i & -i)
			re += tr[i];
		return re;
	}
} tr1, tr2;

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) read(a[i]);
	for (int i = 1; i <= m; ++i) read(q[i].l);
	for (int i = 1; i <= m; ++i) read(q[i].r);
	
    // 单调栈求lb[i],rb[i]
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top && a[stk[top]] < a[i])
			rb[stk[top--]] = i;
		if (top) lb[i] = stk[top];
		stk[++top] = i;
	}
	while (top) rb[stk[top--]] = n + 1;

	for (int i = 1; i <= n; ++i)
		del[lb[i]].push_back(i);
	for (int i = 1; i <= m; ++i)
		qry[q[i].l].push_back(i);
	for (int i = 1; i <= n; ++i)
		tr1.update(i, lb[i]); // 注意+1-1的细节
	for (int i = 1; i <= n; ++i) {
        // 清除贡献，打tag
		for (int j = 0; j < del[i-1].size(); ++j) {
			tr1.update(del[i-1][j], -lb[del[i-1][j]]);
			tr2.update(del[i-1][j], 1);
		}
		for (int j = 0; j < qry[i].size(); ++j) {
			int id = qry[i][j];
			ans[id] -= tr1.query(q[id].r) - tr1.query(q[id].l-1);
			ans[id] -= (LL)(i - 1) * (tr2.query(q[id].r) - tr2.query(q[id].l-1));
		}
	}
    
	for (int i = 0; i <= n; ++i)
		del[i].clear(), qry[i].clear();
	for (int i = 1; i <= n; ++i)
		del[rb[i]].push_back(i);
	for (int i = 1; i <= m; ++i)
		qry[q[i].r].push_back(i);
	tr1.clear(), tr2.clear();
	for (int i = 1; i <= n; ++i)
		tr1.update(i, rb[i]-1);
	for (int i = n; i; --i) {
		for (int j = 0; j < del[i+1].size(); ++j) {
			tr1.update(del[i+1][j], -rb[del[i+1][j]]+1);
			tr2.update(del[i+1][j], 1);
		}
		for (int j = 0; j < qry[i].size(); ++j) {
			int id = qry[i][j];
			ans[id] += tr1.query(q[id].r) - tr1.query(q[id].l-1);
			ans[id] += (LL)i * (tr2.query(q[id].r) - tr2.query(q[id].l-1));
		}
	}

	for (int i = 1; i <= m; ++i)
		printf("%lld ", ans[i]);
	puts("");
    return 0;
}
```



---

## 作者：jucason_xu (赞：4)

题解区里好多树状数组啊。

但是想提供一种 ST 表 + 笛卡尔树上树形 dp $O(n\log n)$ 预处理，然后在线 $O(1)$ 查询的做法。（瓶颈在于 ST 表预处理）

首先 $O(n)$ 建笛卡尔树，不清楚的右转 [P5854 【模板】笛卡尔树](https://www.luogu.com.cn/problem/P5854)。

然后考虑每一次的贡献。假设当前的询问区间是 $[l,r]$，那么先把这个区间的最大值 $m$ 找出来，笛卡尔树的性质告诉我们，$m$ 同时也是 $l,r$ 两点在笛卡尔树上的最近公共祖先。

首先让我们思考如果暴力做应该怎么做。先只考虑左半边。那么就是从 $l$ 开始暴力跳，如果 $l$ 在 $f$ 当前的左子树上，设右子树的最大值是 $rm_f$，这一层对答案的贡献就是

$$(rm_f-l+1)+f(m+1,r)$$

我们发现 $f(m+1,r)$ 是一个完整的子树，那么就可以第一次就预处理出来。

而如果 $l$ 在 $f$ 的右子树上，则这一层已经超出了 $[l,r]$ 的区间，不会对答案有任何贡献。这样跳链直到 $f=m$，退出。

所以我们得到一种 $O(nq)$ 的做法。

我们发现其实在从下往上推答案的时候，除了减了几个 $l$ 以外，没有别的和 $l$ 有关的项。那么，我们重新改写一下这个式子。假设从 $l$ 跳到 $m$ 一共有 $k$ 次是走的左儿子（包括自己），分别是在节点 $v_1,v_2,\cdots,v_k$，那么

$$f(l,m-1)=\sum_{i=1}^{k}{rm_{v_i}}-k(l-1)+\sum_{i=1}^{k}{f(rightson_{v_i})}$$

所以，我们可以维护这三个东西：

路径上所有走了它的左儿子的点的右子树的最大值之和 $sum_i$。（还有 $i$ 的右子树）

上述情况出现的次数 $k_i$。

路径上所有走了它的左儿子的点的右子树的区间贡献之和 $ans_i$。

转移的时候，先把当前节点的值赋给右子树，然后加入它的右子树对答案的贡献，再把当前节点的值赋给左子树。

注意到这三个量都是相当于前缀和的形式（从根到 $i$ 的累计总和）。那么用 $l$ 的值减去 $m$ 的值就能得到正确的三个量，然后根据公式 $O(1)$ 计算答案。

对于 $f(m+1,r)$，如法炮制即可。但是注意答案应当是


$$f(m+1,r)=k(r-1)-\sum_{i=1}^{k}{lm_i}+\sum_{i=1}^{k}{f(leftson_i)}$$

也就是，计算答案的时候要记得用 $r$ 的和去减左端点值和。

左右的数据要分开存储。



小 Trick：在计算过程中 $ans$ 和 $sum$ 的传递过程是完全一样的，可以直接存储它们两个的和。

```cpp
/*

一些声明：
1.本代码使用了FastIO，因为这一部分过于冗长，所以去掉了。
2.使用0代表左，1代表右
3.为了抢最优解（虽然没抢到），有一定卡常，但是应该不影响可读性
4.现在是cf最优解 rk2，576ms

*/
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long ll;
int n,a[1000005],s[1000005],top,q,rt,L[1000005],R[1000005];
int m[2][1000005];
int sn[2][1000005],sr[1000005][21];
ll ans[2][1000005],f[1000005];
int cnt[2][1000005];
using namespace FastIO;
inline int cmp(int &x,int &y){
	if(a[x]>a[y])return x;
	return y;
}
inline void init(){
	rep(i,1,n)sr[i][0]=i;
	rp(j,19)rep(i,1,n)if(i+(1<<j)-1<=n)sr[i][j]=cmp(sr[i][j-1],sr[i+(1<<(j-1))][j-1]);
}
inline int rmq(int l,int r){
	int x=__lg(r-l+1);
	return cmp(sr[l][x],sr[r-(1<<x)+1][x]);
}
inline void build(){// 笛卡尔树的建树 
	rt=1,s[top=1]=1;
	rep(i,2,n){
		int lst=0;
		while(top&&a[s[top]]<a[i])lst=s[top--];
		sn[0][i]=lst;
		if(lst==rt)rt=i;
		if(top)sn[1][s[top]]=i;
		s[++top]=i;
	}
}
inline void calc(int x){// 第一次dp，处理出 f 和左右最小值
	m[0][x]=m[1][x]=x;
	if(sn[0][x])calc(sn[0][x]),m[0][x]=min(m[0][x],m[0][sn[0][x]]),f[x]+=f[sn[0][x]];
	if(sn[1][x])calc(sn[1][x]),m[1][x]=max(m[1][x],m[1][sn[1][x]]),f[x]+=f[sn[1][x]];
	f[x]+=m[1][x]-m[0][x]+1;
}
inline void psh(int p,int x,int f){
	ans[p][x]=ans[p][f];
	cnt[p][x]=cnt[p][f];
}
inline void c(int x){// 第二次dp，处理出计算答案需要的值
	if(sn[0][x])psh(1,sn[0][x],x);
	if(sn[1][x])psh(0,sn[1][x],x);
	ans[0][x]+=f[sn[1][x]]+m[1][x],cnt[0][x]++;
	ans[1][x]+=f[sn[0][x]]-m[0][x],cnt[1][x]++;
	if(sn[0][x])psh(0,sn[0][x],x);
	if(sn[1][x])psh(1,sn[1][x],x);
	if(sn[0][x])c(sn[0][x]);
	if(sn[1][x])c(sn[1][x]);
}
signed main(){
	n=in(),q=in();
	rp(i,n)a[i]=in();
	build();
	init();
	calc(rt);c(rt);
	rp(i,q)L[i]=in();
	rp(i,q)R[i]=in();
	rp(i,q){
		int p=rmq(L[i],R[i]);
		out(R[i]-L[i]+1+
			ans[0][L[i]]-ans[0][p]+ans[1][R[i]]-ans[1][p]-
		    1ll*(cnt[0][L[i]]-cnt[0][p])*(L[i]-1)+
		    1ll*(cnt[1][R[i]]-cnt[1][p])*(R[i]+1))(' ');
	}
	out('\n');
	return 0;
}
```




---

## 作者：tzc_wk (赞：4)

> CF1117G

> 题意：给出长度为 $n$ 的排列，假设 $m_{l,r}$ 为区间 $[l,r]$ 中最大值对应的**下标**，定义函数 $f(l,r)=$

> $$\begin{cases}(r-l+1)+f(l,m_{l,r}-1)+f(m_{l,r}+1,r)&\text{$l \leq r$}\\0&\text{l > r}\end{cases}$$

> 有 $q$ 次询问，每一次让你求出 $f(l_i,r_i)$ 的值。

> $1 \leq n,q \leq 10^6$

又是树状数组的神仙操作。

我们记 $L_i$ 为满足 $j<i,a_j>a_i$ 的最大的 $j$，如果不存在这样的 $j$，$L_i=0$。

同理，记 $R_i$ 为满足 $j>i,a_j>a_i$ 的最小的 $j$，如果不存在这样的 $j$，$R_i=n+1$。

那么经过我们这么一转换，可以得到 

$$f(l,r)=\sum\limits_{i=l}^r\min(R_i-1,r)-\max(L_i+1,l)+1$$

进一步转化可以得到

$$f(l,r)=\sum\limits_{i=l}^r(\min(i-L_i-1,i-l)+\min(R_i-i-1,r-i))+r-l+1$$

我们只需各求出 sigma 里面的两个东西就可以了。

以 $\min(i-L_i-1,i-l)$ 为例，$\min(R_i-i-1,r-i)$ 也同理。我们枚举右端点。开两个树状数组 $sum,cnt$，位置 $i$ 上的数表示当 $l=i$ 时候的情况，由于上面的式子里既包含 $i$ 也包含 $l$ 所以 $sum$ 表示对应的 $\min(i-L_i-1,i-l)$ 与 $i$ 有关的部分的和，$cnt$ 表示有多少个 $i$ 满足 $i-l<i-L_i+1$，那么最终对答案的贡献一定是 $sum_i-l \times cnt_i$。

那么怎么加呢？我们考虑右端点从 $r-1$ 变为 $r$ 会带来什么影响，由于我们是在对应的 $l$ 的位置上添加，那么可以根据 $l$ 的大小分出两大类：

1. 如果 $r-l \leq r-L_r-1$，即 $l \geq L_r+1$，那么与 $r$ 有关的部分就只有一个 $r$，此时我们对 $sum$ 中 $[L_r+1,r]$ 的部分执行区间加 $r$，$cnt$ 中对应部分区间加 $1$。

2. 如果 $r-l > r-L_r-1$，即 $l \leq L_i$，那么与 $r$ 有关的部分就是 $r-L_r-1$，我们对 $sum$ 中 $[1,L_r]$ 的部分执行区间加 $r$ 就好了。

我们开一个桶记录右端点为 $r$ 的时候的询问编号，那么对于询问 $i$ 第一部分对答案的贡献就是 $sum_l-l \times cnt_l$。

另外一个部分同理。最后两部分答案加起来，再加上区间长度就是答案。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read();
int a[1000005],l[1000005],r[1000005];
vector<int> ql[1000005],qr[1000005];
struct Fenwick_Tree{
	int bit[1500005];
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,int val){
		for(int i=x;i<=1500005;i+=lowbit(i))	bit[i]+=val;
	}
	inline int query(int x){
		int ans=0;
		for(int i=x;i;i-=lowbit(i))	ans+=bit[i];
		return ans;
	}
	inline void add_range(int l,int r,int val){
		add(l,val);add(r+1,-val);
	}
	inline void clear(){
		fill0(bit);
	}
} cnt,sum;
int L[1000005],R[1000005],ans[1000005];
signed main(){
	fz(i,1,n)	a[i]=read();
	fz(i,1,m)	l[i]=read(),qr[l[i]].push_back(i);
	fz(i,1,m)	r[i]=read(),ql[r[i]].push_back(i);
	fz(i,1,m)	ans[i]=r[i]-l[i]+1;
	stack<pii> stk;
	fz(i,1,n){
		while(!stk.empty()&&stk.top().fi<a[i]){
			R[stk.top().se]=i;
			stk.pop();
		}
		if(!stk.empty()){
			L[i]=stk.top().se;
		}
		stk.push({a[i],i});
	}
	fz(i,1,n){
		if(!R[i])	R[i]=n+1;
	}
//	fz(i,1,n)	cout<<L[i]<<" "<<R[i]<<endl;
	fz(i,1,n){
		cnt.add_range(L[i]+1,i,1);
		sum.add_range(L[i]+1,i,i);
		sum.add_range(1,L[i],i-L[i]-1);
		foreach(it,ql[i]){
			int ind=*it;
			int j=l[ind];
			ans[ind]+=sum.query(j)-cnt.query(j)*j;
		}
	}
	cnt.clear();sum.clear();
	fd(i,n,1){
		sum.add_range(i,R[i]-1,-i);
		cnt.add_range(i,R[i]-1,1);
		sum.add_range(R[i],n,R[i]-i-1);
		foreach(it,qr[i]){
			int ind=*it;
			int j=r[ind];
			ans[ind]+=sum.query(j)+cnt.query(j)*j;
		}
	}
	fz(i,1,m)	cout<<ans[i]<<" ";
	return 0;
}
/*
r-1 -> r
min(r-L[r]-1,r-l)

r-l<r-L[r]-1  ->  L[r]+1<l

1. l>=L[r]+1   r-l        sum.add(L[r]+1,r,r),cnt.add(L[r]+1,r,1)
2. l<=L[r]     r-L[r]-1   sum.add(1,L[r],r-L[r]-1)
*/
/*
l+1 -> l
min(R[l]-l-1,r-l)

r-l<R[l]-l-1 -> R[l]-1>r

1. r<=R[l]-1   r-l        sum.add(l,R[l]-1,l),cnt.add(l,R[l]-1,1)
2. l>=R[l]     R[l]-l-1   sum.add(R[l],n,R[l]-l-1)
*/
```

---

## 作者：1saunoya (赞：4)

简单数据结构？

令 $R_i$ 是第一个大于 $i$ 的数。

$L_i$ 同理，那么贡献其实就是。

$\sum \min(R_i - 1, qr) - \max(L_i + 1, ql)$。

显然可以用两次单调栈+树状数组做完。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,I=y+1;i<I;++i)
#define per(i,x,y) for(int i=x,I=y-1;i>I;--i)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
template<class T>istream&operator>>(istream&in,vector<T>&V){for(auto&x:V)in>>x;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&V){for(auto x:V)out<<x<<' ';return out;}
template<class T>void sort(vector<T>&V){sort(V.begin(),V.end());}
template<class T>void reverse(vector<T>&V){reverse(V.begin(),V.end());}
template<class T>int SZ(const vector<T>&V){return (int)V.size();}
void debug(){cerr<<"whxorz"<<'\n';}

int n, q;

const int N = 1e6 + 5;
int a[N];

int st[N], top;
int L[N], R[N];
int QL[N], QR[N];

struct Binary_Indexed_Tree {
	ll c[N];
	
	int lowbit(int x) {
		return x & -x;
	}
	
	void update(int x, int y) {
		++x;
		for (; x < N; x += lowbit(x))
			c[x] += y;
	}
	
	ll query(int x) {
		ll ans = 0;
		++x;
		for (; x; x ^= lowbit(x))
			ans += c[x];
		return ans;
	}
	
	ll query(int l, int r) { return query(r) - query(l - 1); }
	
	void clear() {
		for (int i = 0; i < N; i++)
			c[i] = 0;
	}
} t, t2;

vector <int> v[N];
void modify(int i) { int lb = L[i]; t.update(lb, lb); t2.update(lb, 1); }
void modify2(int i) { int rb = R[i]; t.update(rb, rb); t2.update(rb, 1); }

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	for (int i = 1; i <= n; i++) { cin >> a[i]; }
	
	for (int i = 1; i <= n; i++) {
		while (top && a[st[top]] < a[i]) { R[st[top--]] = i; }
		L[i] = st[top]; st[++top] = i;
	}
	while (top) { R[st[top--]] = n + 1; }
	for (int i = 1; i <= n; i++) { L[i]++; R[i]--; }
	for (int i = 1; i <= q; i++) { cin >> QL[i]; }
	for (int i = 1; i <= q; i++) { cin >> QR[i]; }
	vector <ll> ans(q + 1, 0);
	vector <ll> sum(n + 1, 0);
	
	for (int i = 1; i <= n; i++) { sum[i] = sum[i - 1] + (R[i] - L[i] + 1); }
	for (int i = 1; i <= q; i++) {
		int l = QL[i], r = QR[i]; ans[i] = sum[r] - sum[l - 1];
		v[l - 1].push_back(-i); v[r].push_back(i);
	}
	
//	for (int i = 1; i <= q; i++) {
//		cout << ans[i] << ' ';
//	}
//	cout << '\n';
//	
//	for (int i = 1; i <= n; i++) {
//		cout << L[i] << ' ' << R[i] << '\n';
//	}
//	cout << '\n';
//	
//	for (int i = 1; i <= q; i++) {
//		cout << QL[i] << ' ' << QR[i] << '\n';
//	}
//	cout << '\n';
	
	t.clear();
	t2.clear();
	for (int i = 1; i <= n; i++) {
		modify(i);
		for (auto x : v[i]) {
			int f = (x > 0) ? 1 : -1; x *= f;
			ans[x] -= 1ll * f * (1ll * QL[x] * t2.query(QL[x]) - t.query(QL[x]));
		}
	}
	
	t.clear();
	t2.clear();
	for (int i = 1; i <= n; i++) {
		modify2(i);
		for (auto x : v[i]) {
			int f = (x > 0) ? 1 : -1; x *= f;
			ans[x] -= 1ll * f * (t.query(QR[x], n) - 1ll * QR[x] * t2.query(QR[x], n));
		}
	}
	
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}
```

---

## 作者：Prean (赞：3)

题意：区间建笛卡尔树，求每个节点的siz之和。

首先看到笛卡尔树，就应该想到，因为这是一个排列，可以找到通过左边和右边第一个比自己大的元素来“建立”笛卡尔树。

设 $ l(u) $ 为下标是 $ u $ 的元素左边第一个比自身大的元素，$ r(u) $ 同理。

答案就是
$$ \sum_{i=L}^R \min(r(i)-1,R)-\max(l(i)+1,L)+1 $$
将两部分拆开计算，本质是一样的。下面以右端为例

对于一个 $ \sum $，答案由两部分组成：

1. $ r(i) $
2. $ R $

我们只需要对其分别求和就好了

我们从 $ n $ 扫到 $ 1 $，对于一个 $ r(i) $ 会在扫到 $ r(i) $ 时变成 $ R $，且只会变一次。

用两颗树状数组和即可。复杂度 $ O(n\log n) $

code:
```cpp
#include<cstdio>
#include<vector>
const int M=1e6+6;
int n,m,a[M],l[M],r[M],L[M],R[M],num[M];long long BIT[M],ans[M];
std::vector<int>qL[M],qR[M],idL[M],idR[M];
int top,stk[M];
inline void Add1(int x,int val){
	for(;x<=n;x+=1<<__builtin_ctz(x))BIT[x]+=val;
}
inline void Add2(int x,int val){
	for(;x<=n;x+=1<<__builtin_ctz(x))num[x]+=val;
}
inline long long Query1(int x){
	long long ans=0;
	for(;x>=1;x-=1<<__builtin_ctz(x))ans+=BIT[x];
	return ans;
}
inline int Query2(int x){
	int ans=0;
	for(;x>=1;x-=1<<__builtin_ctz(x))ans+=num[x];
	return ans;
}
signed main(){
	register int i,x;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	for(i=1;i<=n;++i){
		while(top&&a[i]>=a[stk[top]])--top;
		idL[(L[i]=top?stk[top]:0)+1].push_back(i);stk[++top]=i;
	}
	top=0;
	for(i=n;i>=1;--i){
		while(top&&a[i]>=a[stk[top]])--top;
		idR[(R[i]=top?stk[top]:n+1)-1].push_back(i);stk[++top]=i;
	}
	for(i=1;i<=m;++i)scanf("%d",l+i),qL[l[i]].push_back(i);
	for(i=1;i<=m;++i)scanf("%d",r+i),qR[r[i]].push_back(i);
	for(i=1;i<=n;++i)Add1(i,R[i]-1);
	for(i=n;i>=1;--i){
		for(int&id:idR[i])Add1(id,-R[id]+1),Add2(id,1);
		for(int&id:qR[i]){
			ans[id]+=(Query1(r[id])-Query1(l[id]-1))+1ll*i*(Query2(r[id])-Query2(l[id]-1));
		}
	}
	for(i=1;i<=n;++i)BIT[i]=num[i]=0;
	for(i=1;i<=n;++i)Add1(i,L[i]+1);
	for(i=1;i<=n;++i){
		for(int&id:idL[i])Add1(id,-L[id]-1),Add2(id,1);
		for(int&id:qL[i]){
			ans[id]-=(Query1(r[id])-Query1(l[id]-1))+1ll*i*(Query2(r[id])-Query2(l[id]-1));
		}
	}
	for(i=1;i<=m;++i)printf("%lld ",ans[i]+r[i]-l[i]+1);
}
```

---

## 作者：Felix72 (赞：1)

这是无修区查，考虑是否能够差分。

发现不能直接对区间差分，因为前后两个区间可能有相互贡献。但是换个角度想，如果贡献有顺序，我们就可以对时间差分了。于是先用单调栈统计每个数为极大值的极大区间，这一部分就是有贡献的。再对询问差分成两个从一开始的区间。统计答案时，按照从左到右的顺序一边加贡献一边统计答案。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 1000010;
int n, m, a[N], l[N], r[N], sta[N], top;
int head[N], tail[N], sign, tot;
struct query {int pos, id, opt;} q[N * 2];
struct node {int head, tail, pos;} s[N * 2];
long long ans[N];
struct BIT
{
	long long c[2][N];
	inline void add(int id, int pos, long long num) {for(int i = pos; i <= n; i += lowbit(i)) c[id][i] += num;}
	inline long long ask(int id, int pos)
	{
		long long ans = 0;
		for(int i = pos; i; i -= lowbit(i)) ans += c[id][i];
		return ans;
	}
	inline void insert(int l, int r, long long num)
	{
		if(l > r) return ;
		add(0, l, num), add(0, r + 1, -num);
		add(1, l, num * l), add(1, r + 1, -num * (r + 1));
	}
	inline int sum(int l, int r)
	{return ((r + 1) * ask(0, r) - ask(1, r)) - (l * ask(0, l - 1) - ask(1, l - 1));}
};
BIT T;
inline bool cmp(query u, query v) {return u.pos < v.pos;}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) l[i] = 0, r[i] = n + 1;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i)
	{
		while(top && a[sta[top]] < a[i]) r[sta[top]] = i, --top;
		sta[++top] = i;
	}
	top = 0;
	for(int i = n; i >= 1; --i)
	{
		while(top && a[sta[top]] < a[i]) l[sta[top]] = i, --top;
		sta[++top] = i;
	}
	for(int i = 1; i <= m; ++i) cin >> head[i];
	for(int i = 1; i <= m; ++i) cin >> tail[i];
	for(int i = 1; i <= m; ++i)
	{
		if(head[i] != 1)
		{
			q[++sign].pos = head[i] - 1;
			q[sign].opt = -1, q[sign].id = i;
		}
		q[++sign].pos = tail[i];
		q[sign].opt = 1, q[sign].id = i;
	}
	sort(q + 1, q + sign + 1, cmp);
	for(int i = 1; i <= n; ++i)
	{
		s[++tot].pos = i, s[tot].head = l[i] + 1, s[tot].tail = i - 1;
		s[++tot].pos = i, s[tot].head = i + 1, s[tot].tail = r[i] - 1;
	}
	int p1, p2; p1 = p2 = 1;
	for(int i = 1; i <= n; ++i)
	{
		T.insert(i, i, 1);
		while(p1 <= tot && s[p1].pos == i)
		{
			T.insert(s[p1].head, s[p1].tail, 1);
			++p1;
		}
		while(p2 <= sign && q[p2].pos == i)
		{
			ans[q[p2].id] += q[p2].opt * T.sum(head[q[p2].id], tail[q[p2].id]);
			++p2;
		}
	}
	for(int i = 1; i <= m; ++i) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑一下式子的意义。

你发现就是区间建出笛卡尔树后所有点的子树大小之和。

不妨令 $L_i,R_i$ 分别表示 $p_i$ 左边第一个大于其的数的编号加 $1$ 与右边第一个大于其的数编号减 $1$。

那么一个数 $i$ 在区间 $[l,r]$ 中的子树大小就是 $\min(r,R_i) - \max(l,L_i) + 1$。

也就是我们要计算 $\sum_{i=l}^r \min(r,R_i) - \max(l,L_i) + 1$。

考虑拆开维护，这里以计算 $\sum_{i=l}^r \min(r,R_i)$ 为例。

考虑把询问挂在 $r$ 上，再从大到小枚举 $r$，倒着扫描线，好处是一个点的贡献一定是先为 $R_i$ 然后当扫描线 $r = R_i$ 后永久地变成 $r$，我们可以在每个分界点 $R_i$ 处挂上修改贡献形式的操作，用两个树状数组维护两种贡献即可做到 $O((n+q) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e6+114;
int tr[maxn][2];
int p[maxn],n,q;
int answer[maxn];
int l[maxn],r[maxn];
vector<int> askR[maxn],askL[maxn];
int R[maxn],L[maxn];
vector<int> indR[maxn],indL[maxn]; 
void add(int u,int c,int ty){
	while(u<maxn) tr[u][ty]+=c,u+=(u&(-u));	
}
int pre(int u,int ty){
	int res=0;
	while(u>0) res+=tr[u][ty],u-=(u&(-u));
	return res;
}
int stk[maxn],tp;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=q;i++) cin>>l[i],askL[l[i]].push_back(i);
	for(int i=1;i<=q;i++) cin>>r[i],askR[r[i]].push_back(i),answer[i]=r[i]-l[i]+1;
	for(int i=1;i<=n;i++){
		while(tp>0&&p[stk[tp]]<p[i]) tp--;		
		if(tp==0) L[i]=1;
		else L[i]=stk[tp]+1;
		indL[L[i]].push_back(i);
		stk[++tp]=i;
	}
	tp=0;
	for(int i=n;i>=1;i--){
		while(tp>0&&p[stk[tp]]<p[i]) tp--;		
		if(tp==0) R[i]=n;
		else R[i]=stk[tp]-1;
		indR[R[i]].push_back(i);
		stk[++tp]=i;
	}
	for(int i=1;i<=n;i++) add(i,R[i],0);
	for(int i=n;i>=1;i--){
		for(int id:indR[i]) add(id,-R[id],0),add(id,1,1);
		for(int id:askR[i]) answer[id]+=((pre(r[id],0)-pre(l[id]-1,0))+(pre(r[id],1)-pre(l[id]-1,1))*i);
	}
	memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++) add(i,L[i],0);
	for(int i=1;i<=n;i++){
		for(int id:indL[i]) add(id,-L[id],0),add(id,1,1);
		for(int id:askL[i]) answer[id]-=((pre(r[id],0)-pre(l[id]-1,0))+(pre(r[id],1)-pre(l[id]-1,1))*i);
	}
	for(int i=1;i<=q;i++) cout<<answer[i]<<' ';
	return 0;
}

```

---

## 作者：BreakPlus (赞：0)

给一个全题解区最菜的做法。

---

+ 我们考虑预处理出每个数左边第一个比它大的数的位置 $L_i$，右边同理有 $R_i$，同时求出 $(L_i, i-1)$ 和 $(R_i, i+1)$ 的 $f$ 值，令为 $F_i$ 和 $G_i$。

+ 这么做是因为**一个数前/后第一个比它大的数**可以作为划分的断点，来帮助我们求解问题。

+ 至于怎么预处理，可以模拟单调栈的过程：每次弹出一个之前比它小的数，累加弹出的数的 $F_i$，以及弹出这个数后，栈顶数的位置到当前位置之间的元素个数也要累加。通过模拟 $f$ 函数的求值过程即可。

+ 此时一个直观的思路是，对于询问 $(l,r)$，从 $l$ 开始顺着 $R_i$ 倍增跳。但是问题也是显然的：这么跳不一定刚好跳到 $r$。

+ 这就是前面我们还要处理 $L_i$ 和 $F_i$ 的原因：假设这段区间最大值位于 $m$，则我们可以从 $l$ 跳到 $m$，再从 $r$ 跳到 $m$，答案再加上 $r-l+1$ 就可以了。

+ 关于倍增求和的细节可以参考前面预处理的方式，通过模拟不难发现很好维护。

+ 值得一提的是这个做法很菜，空间是 $\mathcal{O}(n \log n)$。其实只要离线下来，向左跳和向右跳依次预处理并计算，二者共用两个倍增数组（一个指针，一个求和）。跳指针的倍增数组开 $\texttt{int}$，就能卡过了。

![](https://cdn.luogu.com.cn/upload/image_hosting/13b6q3ke.png)

这波压空间有点难评。

```cpp
int n,q,a[1000002]; ll g[20][1000002];
int wg[20][1000002]; 
int stk[1000002], tp;
int lll[1000002], rrr[1000002]; ll ans[1000002];
void solve(){
	n=read(), q=read();
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=1;i<=q;i++) lll[i]=read();
	for(ll i=1;i<=q;i++) rrr[i]=read();
	a[0] = a[n+1] = n+1; stk[tp=1] = 0;
	for(ll i=1;i<=n;i++){
		while(tp && a[stk[tp]] < a[i]){
			g[0][i] += g[0][stk[tp]];
			--tp; g[0][i] += i - stk[tp] - 1;
		}
		wg[0][i] = stk[tp];
		stk[++tp] = i;
	}
	for(ll i=1;i<=n;i++) g[0][i] -= wg[0][i];
	for(ll i=1;i<=19;i++)
		for(ll j=0;j<=n;j++) wg[i][j] = wg[i-1][wg[i-1][j]];	
	for(ll i=1;i<=19;i++)
		for(ll j=0;j<=n;j++) g[i][j] = g[i-1][j] + g[i-1][wg[i-1][j]];
	for(ll i=1;i<=q;i++){
		ll l=lll[i], r=rrr[i];
		ll R=r;
		for(ll j=19;j>=0;j--){
			if(wg[j][R]>=l){
				ans[i] += (1ll<<j) * r + g[j][R];
				R = wg[j][R];
			}
		}
	}
	
	
	// --------------------
		
	memset(g, 0, sizeof(g)); memset(wg, 0, sizeof(wg));
	wg[0][n+1] = n+1;
	stk[tp=1] = n+1;
	for(ll i=n;i>=1;i--){
		while(tp && a[stk[tp]] < a[i]){
			g[0][i] += g[0][stk[tp]];
			--tp; g[0][i] += stk[tp] - i - 1;
		}
		wg[0][i] = stk[tp];
		stk[++tp] = i;
	}
	for(ll i=1;i<=n;i++) g[0][i] += wg[0][i];
	for(ll i=1;i<=19;i++)
		for(ll j=1;j<=n+1;j++) wg[i][j] = wg[i-1][wg[i-1][j]];
	for(ll i=1;i<=19;i++)
		for(ll j=0;j<=n+1;j++) g[i][j] = g[i-1][j] + g[i-1][wg[i-1][j]];
	for(ll i=1;i<=q;i++){
		ll l=lll[i], r=rrr[i];
		ll L=l;
		for(ll j=19;j>=0;j--){
			if(wg[j][L]<=r){
				ans[i] += ( - (1ll<<j) * l + g[j][L] ) ;
				L = wg[j][L];
			}
		}
	}
	for(ll i=1;i<=q;i++) printf("%lld ", ans[i] + (rrr[i] - lll[i] + 1));
}
```

---

## 作者：happybob (赞：0)

题意相当于，对 $[l,r]$ 建出大根笛卡尔树后，求每个点的子树大小的和。

考虑点 $i$ 的子树大小的意义是什么？笛卡尔树上每个点的子树的编号连续。

设 $L_i$ 表示 $i$ 左边第一个大于 $a_i$ 的位置，$R_i$ 表示右边第一个大于 $a_i$ 的位置。同时，设 $a_0 = a_{n+1} = +\infty$。

点 $i$ 的子树大小为 $\min\{r,R_i-1\}-\max\{l,L_i+1\}+1$。即，点 $i$ 的子树包括这一段连续的，容易发现点权是满足堆的性质的。

故答案为 $\sum \limits_{i=l}^r \min\{r,R_i-1\}-\max\{l,L_i+1\}+1$。

$+1$ 可以直接拆出来，$\min$ 和 $\max$ 分别计算，方法相同。

考虑离线，逆序枚举 $r$，随着 $r$ 递减，$r$ 和 $R_i-1$ 的最小值发生改变只会进行至多 $1$ 次，使用树状数组维护即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int N = 1e6 + 5;

int n, m, a[N];
int l[N], r[N];
int L[N], R[N];

long long res1[N], res2[N];
vector<int> v[N], v2[N];

class SegmentTree
{
public:
	long long tr[N];
	int lowbit(int x)
	{
		return x & -x;
	}
	void CLEAR()
	{
		for (int i = 0; i < N; i++) tr[i] = 0;
	}
	void update(int u, long long x)
	{
		while (u < N)
		{
			tr[u] += x;
			u += lowbit(u);
		}
	}
	long long query(int u)
	{
		long long res = 0LL;
		while (u)
		{
			res += tr[u];
			u -= lowbit(u);
		}
		return res;
	}
}s1, s2;

vector<int> qr[N], qr2[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], L[i] = 0, R[i] = n + 1;
	for (int i = 1; i <= m; i++) cin >> l[i], qr2[l[i]].emplace_back(i);
	for (int i = 1; i <= m; i++) cin >> r[i], qr[r[i]].emplace_back(i);
	stack<int> st;
	for (int i = 1; i <= n; i++)
	{
		while (st.size() && a[st.top()] < a[i])
		{
			R[st.top()] = i;
			st.pop();
		}
		if (st.size()) L[i] = st.top();
		st.push(i);
	}
	for (int i = 1; i <= n; i++)
	{
		L[i]++, R[i]--;
		v[R[i]].emplace_back(i);
		v2[L[i]].emplace_back(i);
		s1.update(i, R[i]);
	}
	// min(r, R[i])
	for (int i = n; i >= 1; i--) // 枚举 r
	{
		for (auto& j : v[i])
		{
			s1.update(j, -R[j]);
			s2.update(j, 1);
		}
		for (auto& j : qr[i])
		{
			res1[j] = s1.query(r[j]) - s1.query(l[j] - 1) + 1LL * r[j] * (s2.query(r[j]) - s2.query(l[j] - 1));
		}
	}
	s1.CLEAR();
	s2.CLEAR();
	for (int i = 1; i <= n; i++) s1.update(i, L[i]);
	for (int i = 1; i <= n; i++)
	{
		for (auto& j : v2[i])
		{
			s1.update(j, -L[j]);
			s2.update(j, 1);
		}
		for (auto& j : qr2[i])
		{
			res2[j] = s1.query(r[j]) - s1.query(l[j] - 1) + 1LL * l[j] * (s2.query(r[j]) - s2.query(l[j] - 1));
		}
	}
	for (int i = 1; i <= m; i++)
	{
		cout << res1[i] - res2[i] + (r[i] - l[i] + 1) << " ";
	}
	cout << "\n";
	return 0;
}
```


---

## 作者：wcyQwQ (赞：0)

不难发现答案就是把 $[l, r]$ 拉出来建笛卡尔树后每个点的子树大小之和。

考虑建立笛卡尔树的过程，不难发现对于 $p_i$ 来说 $[\max(l, L_i + 1), \min(r, R_i - 1)]$ 这一段区间都是它的子树，其中 $L_i, R_i$ 分别表示 $i$ 左右第一个大于它的下标，于是我们要求的就是
$$
\sum_{i = l}^r [\min(r, R_i - 1) - \max(l, L_i + 1) + 1]
$$
将 $\max$ 和 $\min$ 拆开来变成二维偏序形式，即可 $O(n\log n)$ 解决。

[Code](https://codeforces.com/contest/1117/submission/220340792)



---

## 作者：cbyybccbyybc (赞：0)

```cpp
刚开始想复杂了, 还以为是个笛卡尔树....

实际上我们发现, 对于询问(l,r)每个点的贡献是min(r,R[i])−max(l,L[i])+1

数据范围比较大在线树套树的话明显过不了, 还是想离线的算法好了, 只考虑求∑min(r,R[i]), 对于∑max(l,L[i])同理

将询问按l从大到小排, 将点x的贡献转化为[x,R[x]−1]区间加等差, [R[x],n]区间加R[x], 这样∑min(r,R[i])就变成对位置r单点求和了

离线的代码如下 
```
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <math.h>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <string.h>
#define REP(i,a,n) for(int i=a;i<=n;++i)
#define PER(i,a,n) for(int i=n;i>=a;--i)
#define hr putchar(10)
#define pb push_back
#define lc (o<<1)
#define rc (lc|1)
#define mid ((l+r)>>1)
#define ls lc,l,mid
#define rs rc,mid+1,r
#define x first
#define y second
#define io std::ios::sync_with_stdio(false)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int P = 1e9+7, INF = 0x3f3f3f3f;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
ll qpow(ll a,ll n) {ll r=1%P;for (a%=P;n;a=a*a%P,n>>=1)if(n&1)r=r*a%P;return r;}
ll inv(ll x){return x<=1?1:inv(P%x)*(P-P/x)%P;}
//head
 
const int N = 1e6+10;
int n, q;
int a[N], L[N], R[N];
struct _ {int l,r,id;} e[N];
int v1[N<<2], t1[N<<2];
ll v2[N<<2], t2[N<<2], ans[N];
 
void pd1(int o) {
    if (t1[o]) {
        v1[lc]+=t1[o];
        v1[rc]+=t1[o];
        t1[lc]+=t1[o];
        t1[rc]+=t1[o];
        t1[o]=0;
    }
}
void pd2(int o) {
    if (t2[o]) {
        v2[lc]+=t2[o];
        v2[rc]+=t2[o];
        t2[lc]+=t2[o];
        t2[rc]+=t2[o];
        t2[o]=0;
    }
}
void upd1(int o, int l, int r, int ql, int qr, int v) {
    if (ql<=l&&r<=qr) return v1[o]+=v,t1[o]+=v,void();
    pd1(o);
    if (mid>=ql) upd1(ls,ql,qr,v);
    if (mid<qr) upd1(rs,ql,qr,v);
}
void upd2(int o, int l, int r, int ql, int qr, int v) {
    if (ql<=l&&r<=qr) return v2[o]+=v,t2[o]+=v,void();
    pd2(o);
    if (mid>=ql) upd2(ls,ql,qr,v);
    if (mid<qr) upd2(rs,ql,qr,v);
}
ll qry1(int o, int l, int r, int x) {
    if (l==r) return (ll)l*v1[o];
    pd1(o);
    if (mid>=x) return qry1(ls,x);
    return qry1(rs,x);
}
ll qry2(int o, int l, int r, int x) {
    if (l==r) return (ll)v2[o];
    pd2(o);
    if (mid>=x) return qry2(ls,x);
    return qry2(rs,x);
}
 
int main() {
    scanf("%d%d", &n, &q);
    REP(i,1,n) scanf("%d", a+i);
    REP(i,1,n) {
        L[i] = i-1;
        while (L[i]&&a[i]>a[L[i]]) L[i]=L[L[i]];
    }
    PER(i,1,n) {
        R[i] = i+1;
        while (R[i]<=n&&a[i]>a[R[i]]) R[i]=R[R[i]];
    }
    REP(i,1,n) ++L[i],--R[i];
    REP(i,1,q) scanf("%d", &e[i].l);
    REP(i,1,q) scanf("%d", &e[i].r),e[i].id=i;
    sort(e+1,e+1+q,[](_ a,_ b){return a.l>b.l;});
    int now = n;
    REP(i,1,q) {
        while (now>=e[i].l) {
            if (now<=R[now]-1) upd1(1,1,n,now,R[now]-1,1);
            upd2(1,1,n,R[now],n,R[now]);
            --now;
        }
        ans[e[i].id] += qry1(1,1,n,e[i].r)+qry2(1,1,n,e[i].r)+e[i].r-e[i].l+1;
    }
    memset(v1,0,sizeof v1);
    memset(v2,0,sizeof v2);
    memset(t1,0,sizeof t1);
    memset(t2,0,sizeof t2);
    sort(e+1,e+1+q,[](_ a,_ b){return a.r<b.r;});
    now = 1;
    REP(i,1,q) {
        while (now<=e[i].r) {
            if (L[now]+1<=now) upd1(1,1,n,L[now]+1,now,1);
            upd2(1,1,n,1,L[now],L[now]);
            ++now;
        }
        ans[e[i].id] -= qry1(1,1,n,e[i].l)+qry2(1,1,n,e[i].l);
    }
    REP(i,1,q) printf("%lld ", ans[i]);hr;
}
在线的代码如下, RE on test 8.

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <math.h>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <string.h>
#define REP(i,a,n) for(int i=a;i<=n;++i)
#define PER(i,a,n) for(int i=n;i>=a;--i)
#define hr putchar(10)
#define pb push_back
#define lc TL[o]
#define rc TR[o]
#define mid ((l+r)>>1)
#define ls lc,l,mid
#define rs rc,mid+1,r
#define x first
#define y second
#define io std::ios::sync_with_stdio(false)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int P = 1e9+7, INF = 0x3f3f3f3f;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
ll qpow(ll a,ll n) {ll r=1%P;for (a%=P;n;a=a*a%P,n>>=1)if(n&1)r=r*a%P;return r;}
ll inv(ll x){return x<=1?1:inv(P%x)*(P-P/x)%P;}
//head
 
const int N = 1e6+10, M = 1e7+10;
int n, q, tot;
int a[N], L[N], R[N], ql[N], qr[N];
int cntL[N], cntR[N], sumL[N], sumR[N];
int TL[M], TR[M];
ll val[M];
 
void add(int &o, int l, int r, int x, int v) {
    if (!o) o=++tot;
    val[o] += v;
    if (l==r) return;
    if (mid>=x) add(ls,x,v);
    else add(rs,x,v);
}
ll query(int o, int l, int r, int ql, int qr) {
    if (!o) return 0;
    if (ql<=l&&r<=qr) return val[o];
    ll ans = 0;
    if (mid>=ql) ans += query(ls,ql,qr);
    if (mid<qr) ans += query(rs,ql,qr);
    return ans;
}
 
int main() {
    scanf("%d%d", &n, &q);
    REP(i,1,n) scanf("%d", a+i);
    REP(i,1,n) {
        L[i] = i-1;
        while (L[i]&&a[i]>a[L[i]]) L[i]=L[L[i]];
    }
    PER(i,1,n) {
        R[i] = i+1;
        while (R[i]<=n&&a[i]>a[R[i]]) R[i]=R[R[i]];
    }
    REP(i,1,n) ++L[i],--R[i];
    REP(i,1,n) {
        for (int j=R[i]; j<=n; j+=j&-j) {
            add(cntR[j],1,n,i,1);
            add(sumR[j],1,n,i,R[i]);
        }
        for (int j=L[i]; j; j^=j&-j) {
            add(cntL[j],1,n,i,1);
            add(sumL[j],1,n,i,L[i]);
        }
    }
    REP(i,1,q) scanf("%d", ql+i);
    REP(i,1,q) scanf("%d", qr+i);
    REP(i,1,q) {
        ll sumr=0,suml=0,cntr=0,cntl=0;
        int l=ql[i], r=qr[i];
        for (int j=r; j; j^=j&-j) {
            sumr += query(sumR[j],1,n,l,r);
            cntr += query(cntR[j],1,n,l,r);
        }
        for (int j=l; j<=n; j+=j&-j) {
            suml += query(sumL[j],1,n,l,r);
            cntl += query(cntL[j],1,n,l,r);
        }
        ll ans = (ll)(r-l+1-cntr)*r+sumr;
        ans -= (ll)(r-l+1-cntl)*l+suml;
        ans += r-l+1;
        printf("%lld ", ans);
    } hr;
}
```
# https://www.cnblogs.com/uid001/p/10519900.html

---

## 作者：cccgift (赞：0)

## 这里给出一种更加方便、更快的做法

如另一篇题解所说，对于每一个$[l,r]$，每个点$i$的贡献是$min(R[i],r)-max(L[i],l)+1$，其中$L[i],R[i]$表示每个点向左右延伸遇到的第一个最小值的位置$+1$。这个可以用单调栈来维护。

我们把$max(L[i],l)$提出来，$min(R[i],r)$同理。

然后我们考虑枚举$l$，对于每一个点，它对答案的贡献只有两种：$l$和$L[i]$，那么从$l$到$l+1$，贡献有改变的只可能是$L[i]=l$的$i$，那么我们直接对这些点进行修改就好了。

我们考虑如下算法：

开两棵树状数组，一棵维护表示这个点对于答案的贡献是属于$L[i]$的，设为$tr1$，另一棵维护这个点对答案的贡献是属于$l$的，设为$tr2$，刚开始$tr2$清空，$tr1$把所有$L[i]$加入。每次从$l$到$l+1$的时候，把$tr1$中的所有$L[i]=l$的点设为$0$，而往$tr2$中加入这些点就好了，最后询问时直接区间询问就好了。

Q：每次询问$l$都不同，怎么办？

A：$tr2$维护每个点是否有$l$的贡献，询问时直接区间询问$*l$就好了。

至于怎么找到所有$L[i]=l$的点，发现$l$是递增的，直接把$L[i]$排序后指针扫描即可。

时间复杂度$O(nlogn)$，~~但是我们要坚信树状数组常数小于1……~~

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
#define res register int
#define ll long long
#define lowbit(x) ((x)&-(x))
//#define cccgift
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    void print(T x)
    {
        if (x<0) putchar('-'),x=-x;
        if (x>=10) print(x/10);
        putchar(x%10+'0');
    }
    template<typename T>
    inline void print(T x,char ap) {print(x);if (ap) putchar(ap);}
    template<typename T>
    inline T max(const T &x,const T &y) {return x<y?y:x;}
    template<typename T>
    inline T min(const T &x,const T &y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,const T &y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,const T &y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;using wode::print;
struct node{
	int x,id;
	bool operator <(const node &b)const {return x<b.x;}
} L[1000010],R[1000010];
int n;
struct tree{
	ll c[1000001];
	void clear() {memset(c,0,sizeof(c));}
	void modify(int b,int d) {for(;b<=n;c[b]+=d,b+=lowbit(b));}
	ll query(int b) {ll tot=0;for(;b;tot+=c[b],b^=lowbit(b));return tot;}
} tr1,tr2;
int m,a[1000001],a1[1000001],a2[1000001],ver[1000010],edge[1000010],nxt[1000010],head[1000010],ans,ver1[1000010],edge1[1000010],nxt1[1000010],head1[1000010],ans1,stack[1000010],top;
ll tot[1000010];
inline void add(int x,int y,int z) {ver[++ans]=y,edge[ans]=z,nxt[ans]=head[x],head[x]=ans;}
inline void add1(int x,int y,int z) {ver1[++ans1]=y,edge1[ans1]=z,nxt1[ans1]=head1[x],head1[x]=ans1;}
int main()
{
	read(n),read(m);
	for(res i=1;i<=n;++i) read(a[i]);
	for(res i=1;i<=m;++i) read(a1[i]);
	for(res i=1;i<=m;++i) read(a2[i]),add(a2[i],a1[i],i),add1(a1[i],a2[i],i),tot[i]=a2[i]-a1[i]+1; //注意答案初始化！
	for(res i=1;i<=n;++i) {
		L[i].id=R[i].id=i;
		for(;top&&a[i]>a[stack[top]];R[stack[top--]].x=i);
		stack[++top]=i;
	}
	top=0;
	for(res i=n;i;--i) {
		for(;top&&a[i]>a[stack[top]];L[stack[top--]].x=i);
		stack[++top]=i;
	}
	for(res i=1;i<=n;++i) if(!R[i].x) R[i].x=n+1;
	for(res i=1;i<=n;++i) ++L[i].x,--R[i].x;
//	for(res i=1;i<=n;++i) printf("%d %d\n",L[i].x,R[i].x);
	sort(L+1,L+1+n);
	for(res i=1;i<=n;++i) tr1.modify(L[i].id,L[i].x); //注意！要记录原来的编号，否则答案错误。
	int p=1;
	for(res i=1;i<=n;++i) {
		for(;p<=n&&L[p].x<=i;++p) tr1.modify(L[p].id,-L[p].x),tr2.modify(L[p].id,1); //指针扫描
		for(res j=head1[i];j;j=nxt1[j]) tot[edge1[j]]-=tr1.query(ver1[j])-tr1.query(i-1)+(tr2.query(ver1[j])-tr2.query(i-1))*i;
	}
	tr1.clear(),tr2.clear(),sort(R+1,R+1+n),p=n;
	for(res i=1;i<=n;++i) tr1.modify(R[i].id,R[i].x);
	for(res i=n;i;--i) {
		for(;p&&R[p].x>=i;--p) tr1.modify(R[p].id,-R[p].x),tr2.modify(R[p].id,1);
		for(res j=head[i];j;j=nxt[j]) tot[edge[j]]+=tr1.query(i)-tr1.query(ver[j]-1)+(tr2.query(i)-tr2.query(ver[j]-1))*i;
	}
	for(res i=1;i<=m;++i) print(tot[i],' ');puts("");
	return 0;
}
```

---

