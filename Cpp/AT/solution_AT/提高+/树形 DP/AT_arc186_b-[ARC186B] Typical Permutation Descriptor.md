# [ARC186B] Typical Permutation Descriptor

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc186/tasks/arc186_b

長さ $ N $ の整数列 $ (A_1,\dots,A_N) $ が与えられます。この整数列は、各 $ i=1,\dots,N $ について、$ 0\le\ A_i\ <\ i $ を満たします。 次の条件を満たす $ (1,\dots,N) $ の順列 $ (P_1,\dots,P_N) $ の数を $ 998244353 $ で割ったあまりを求めてください。

- $ i=1,\dots,N $ について、
  - $ A_i\ <\ j\ <\ i $ であるすべての整数 $ j $ について、$ P_j\ >\ P_i $
  - $ A_i\ >\ 0 $ ならば $ P_{A_i}\ <\ P_i $

ただし、この問題の入力で与えられる $ (A_1,\dots,A_N) $ について、条件を満たす順列が存在することが保証されます。

## 说明/提示

### 制約

- $ 1\le\ N\le\ 3\times\ 10^5 $
- $ 0\le\ A_i\ \lt\ i $
- $ A_1,\dots,A_N $ について、問題文中の条件を満たすような順列が存在する
- 入力はすべて整数

### Sample Explanation 1

$ (2,\ 3,\ 1,\ 4),\ (2,\ 4,\ 1,\ 3),\ (3,\ 4,\ 1,\ 2) $ の $ 3 $ つです。

### Sample Explanation 2

$ 2350309500 $ を $ 998244353 $ で割ったあまりである、 $ 353820794 $ が答えです。

## 样例 #1

### 输入

```
4
0 1 0 3```

### 输出

```
3```

## 样例 #2

### 输入

```
22
0 1 2 2 2 2 2 2 1 9 9 9 9 0 14 15 15 15 14 19 19 19```

### 输出

```
353820794```

# 题解

## 作者：不知名用户 (赞：7)

### 题意

求长度为 $n$ 且对 $\forall 1\le i\le n$ 满足以下条件的排列 $P$ 个数：$P_{A_i}<P_i\And\forall A_i<j<i,P_j<P_i$。保证有解。

### 做法

观察到性质：$\forall A_i<j<i,A_i\le A_j$。反证：若存在 $(i,j)$ 不满足，则将 $i$ 代入 $\forall A_i<j<i,P_j<P_i$ 可以得出 $P_j>P_{A_i}$，将 $j$ 代入可以得到 $P_j<P_{A_i}$，矛盾。

即区间 $[A_i,i]$ 不会跨过相交。考虑类似包含关系建树，转化成拓扑序计数问题（即一棵树，父亲节点权值小于儿子节点权值）。操作为维护一个栈，从左向右枚举 $i$，弹栈直到栈顶为 $A_i$，再将 $i$ 入栈。根据上面的性质容易发现 $A_i$ 不可能被弹掉，因为 $i$ 入栈相当于清空栈内值域为 $(A_i,i)$（开区间）的所有元素，$A_i$ 被弹显然矛盾。

怎么转化成拓扑序，建立一些小于关系使得是一棵树？举个例子，用箭头 $i\rightarrow j$ 表示 $A_i=j$，弹了四个点：（感觉写的不是非常清楚，可以先去看代码理解）

![ARC186B0.png](https://cdn.acwing.com/media/article/image/2024/10/31/60248_261bfa2e97-ARC186B0.png)

显然 $x_1=i-1$（$i-1$ 刚刚入栈），$x_1$ 一路往左不会出现断的点，因为保证了 $A_i<i$，所以栈内元素形式上类似上图（箭头不会断开，$x_1$ 紧贴 $i$）。连有向边 $i\to x_4\to x_3\to x_2\to x_1$，连边 $i\to j$ 表示要求 $P_i<P_j$。最后栈内的元素要保证从左到右依次递增，即要从左向右连边，计算拓扑序数量即可。

树上拓扑序数量是 $\frac{n!}{size_1\cdot size_2\cdots size_n}$，$size$ 表示子树大小。这里不作展开。参见[此处](https://blog.csdn.net/qq_50285142/article/details/126436749)。

那棵树和题目给出的条件是等价的证明：显然那棵树给出的条件不会矛盾。归纳证明 $i$ 入栈时满足 $\forall A_i<j<i,P_j<P_i$：$P_{x_j}>P_i$ 显然（由上面连的四条有向边显然）；因为归纳的结论，$x_i,x_{i+1}$ 之间的数都会比 $P_{x_i}$ 大且 $P_{x_i}>P_i$，故这些数也 $>P_i$；$A_i,x_4$ 之间的数都 $>x_4$。$P_{A_i}<P_i$ 会在弹栈时满足。所以树和题目给出的条件是等价的。

### 代码

`p` 表示 $A$ 数组。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, mod = 998244353;
int p[N], s[N], t, sz[N], inv[N];
vector<int>g[N];

void dfs(int x)
{
	sz[x] = 1;
	for(auto j:g[x]) dfs(j), sz[x] += sz[j];
}

signed main()
{
	int n, i;
	scanf("%lld", &n);
	for(i=1;i<=n;i++) scanf("%lld", &p[i]);
	for(i=1;i<=n;i++)
	{
		int l = 0;
		while(t&&s[t]>p[i])
		{
			if(l) g[s[t]].emplace_back(l);
			l = s[t--];
		}
		if(l) g[i].emplace_back(l);
		s[++t] = i;
	}
	int l = 0;
	while(t)
	{
		if(l) g[s[t]].emplace_back(l);
		l = s[t--];
	}
	dfs(l);
	inv[1] = 1;
	for(i=2;i<=n;i++) inv[i] = (mod - mod / i) * inv[mod%i] % mod;
	int ans = 1;
	for(i=1;i<=n;i++) ans = ans * i % mod * inv[sz[i]] % mod;
	printf("%lld", ans);
	return 0;
}
```


### 后记

这场 ARC 一题都没做出来，直接掉蓝。/dk

做的时候只注意到最开始的性质，并没有注意到栈顶是 $i-1$，箭头不会断开，导致想复杂了，最后也没调出来。

---

## 作者：lfxxx (赞：4)

注意到 $A_i$ 就是 $i$ 左边第一个大于其的数。

再注意到在用单调栈构建笛卡尔树的过程中，我们其实不需要知道每个数具体的值，只需要知道每个值左边第一个大于其的数即可构建出笛卡尔树。

所以问题转变为存在多少种向笛卡尔树中填数的方案。

不妨令 $sz_u,dp_u$ 分别表示点 $u$ 在笛卡尔树上的子树大小与将 $[1,sz_u]$ 填入其子树的方案，转移显然有 $dp_{u} = dp_{ls_u} \times dp_{rs_u} \times {sz_u - 1 \choose sz_{ls_u}}$，直接做即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 3e5+114;
int fac[maxn];
int inv[maxn];
int A[maxn],n;
int stk[maxn],tp;
int ls[maxn],rs[maxn],sz[maxn]; 
int dp[maxn];
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res=res*res%mod;
	if(b%2==1) res=res*a%mod;
	return res;
}
int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
void DP(int u){
	sz[u]=1;
	if(ls[u]==0&&rs[u]==0) dp[u]=1;
	else if(ls[u]==0){
		DP(rs[u]);
		sz[u]+=sz[rs[u]];
		dp[u]=dp[rs[u]];
	}else if(rs[u]==0){
		DP(ls[u]);
		sz[u]+=sz[ls[u]];
		dp[u]=dp[ls[u]];
	}else{
		DP(ls[u]);
		DP(rs[u]);
		sz[u]+=(sz[ls[u]]+sz[rs[u]]);
		dp[u]=C(sz[u]-1,sz[ls[u]])*dp[ls[u]]%mod*dp[rs[u]]%mod;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	fac[0]=inv[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>A[i];
        int k=tp;
        while(k>0&&stk[k]!=A[i]) k--;
        if(k!=0) rs[stk[k]]=i;
        if(k<tp) ls[i]=stk[k+1];
        tp=k;
        stk[++tp]=i;
    }
	int root=stk[1];
	DP(root);
	cout<<dp[root]<<'\n';
	return 0;
}
```

---

## 作者：Coffins (赞：4)

很有意思但是又没什么意思的题目。

首先思考 dp 无果，考虑到过的人比较多，还是 ARC 的题目，所以应该是根据性质直接计数。

下面默认 存在一种合法的 $p$。

首先我们可以确定 1 的位置，应该为为 $\max_{a_i=0}i$（因为 1 前面一定都比他小，并且没有任何数字会把他覆盖其中），不妨设其位置为 $t$，那么发现对于 $i\ge t$，都有 $a_i>t$，于是我们发现一个结论：$t$ 两边对于最终 $a$ 的影响是独立的，我们只需要分配以下两边都是哪些数字，然后在用两边分别方案乘起来就好了。

写成具体的表达式，就是 $f_{l,r}=\dbinom{r-l}{r-t}\times f_{l,t-1}\times f_{t+1,r}$，这样直接递归下去就是 $O(n)$ 个状态，就随便做了。

https://atcoder.jp/contests/arc186/submissions/59209580

---

## 作者：Gordon_Song (赞：2)

~~为什么最近的 arc 都这么难……~~

首先有一个自然而然地想法是使用差分约束加线段树优化建图等一系列技巧，将其转化成一个求有向无环图上有多少个本质不同的拓扑序的问题。然而我太菜了，不太会这个问题，因此我放弃了这个思路。

考虑对于一段区间 $[l,r]$，如果区间外部的点对于区间中数没有大小关系的限制，我们发现可以递归成若干个更小的子问题。

（下面定义 $a_k(i)$，$a_0(i)=i$，$a_k(i)=a_{a_{k-1}(i)}$）

具体地，考虑一条链：$r->a_r->a_{a_r} \dots $，我们发现对于任意 $x \in (a_k(r),a_{k-1}(r))$，都有 $a_x \geq a_k(r)$，否则就说明 $p_{a_k(r)} > p_x > p_{a_{k-1}(r)} > p_{a_k(r)}$ 无解，而题目保证有解，所以这种情况不可能出现。因此，我们可以把问题划分成若干个子问题，其中第 $j$ 个区间是 $(a_j(r),a_{j-1}(r))$，根据上面的结论可知区间之间的大小关系不会互相影响。

对于这些子区间会选哪一些数可以通过组合数来算出，具体可以看代码。

就这样，我们拥有了一种 $O(n)$ 的做法。

代码只放出关键部分：


```cpp
ll solv(int l,int r){
	if(l>=r){
		return 1;
	}
	vector<int>duan;duan.clear();
	int now=r;
	while(now>=l){
		duan.push_back(now);
		now=a[now];
	}
	duan.push_back(l-1);
	reverse(duan.begin(),duan.end());//duan 记录所有形如 a_k(r) 的点
	ll ans=1;
	for(int i=1;i<duan.size();i++){
		(ans*=solv(duan[i-1]+1,duan[i]-1))%=mod;
		(ans*=c(r-(duan[i-1]+1)+1-1,duan[i]-1-(duan[i-1]+1)+1))%=mod;//在 [duan[i-1]+1,r] 个剩余的可选位置中选出 [duan[i-1]+1,duan[i]-1] 个数
	}return ans;
} 
```

[完整代码的链接，组合数部分码风比较丑](https://atcoder.jp/contests/arc186/submissions/59210378)

---

## 作者：aimat (赞：2)

这是一篇 $O(n\log n)$ 的题解。

首先不难发现 $p_{a_i}<p_i$ 和 $\forall j\in[a_i+1,i-1],p_i<p_j$ 是偏序关系，套路的，我们按照偏序关系连边，即若 $x<y$ 一定满足，连边 $x\to y$。具体到这道题就是连 $a_i\to i|a_i\not=0,\forall j\in[a_i+1,i-1],i\to j$ 然后拓扑排序，只保留使某个点入队的边，就形成了一棵外向树。

那么为什么一定会形成外向树呢？每个点父亲唯一或没有，而且严格偏序关系不会形成环，所以这至少是个外向树森林。考虑反证，假设有两个点 $i,j$ 没有父亲，那么 $a_i=a_j=0$，又发现 $i,j$ 不同时要么 $i\in[1,j-1]$，要么 $j\in[1,i-1]$，所以一定会形成外向树。

但我们又发现，直接连边复杂度是 $O(n^2)$ 的。考虑拓扑排序时我们只关注点的入度，所以可以改成区间减+区间找所有入度为 $0$ 的位置入队并改入度为 $\infin$。这个东西可以直接用势能线段树维护，初始入度数组直接差分再前缀和回来就好了。

最后外向树上的 dp 是简单的：

设 $f_u$ 为填完 $u$ 子树内的方案数，有转移为：
$$f_u=\prod_{v\in son_u}f_v\binom x{sz_v}$$
其中 $x$ 为未确定的子树大小，对于每个 $u$ 初始为 $sz_u-1$，遍历一个儿子 $v$ 后更新 $x\gets x-sz[v]$。

答案即为 $f_{rt}$，记得取模。

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
char *p1,*p2,buf[10010];
const int p=998244353;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
int read(){
	int x=0;
	char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c&15),c=gc();
	return x;
}
struct EDGE{
	int nxt,to;
}edg[600010],edge[600010];
struct node{
	int w,lz;
}t[1200010];
int nowu,tot,hed[300010],head[300010],d[300010],T,sz[300010],f[300010],jie[300010],ijie[300010],q[300010],a[300010];
void add(int u,int v){
	edge[++tot].to=v;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void addd(int u,int v){
	edg[++tot].to=v;
	edg[tot].nxt=hed[u];
	hed[u]=tot;
	++d[v];
	--d[v+1];
}
void update(int now){
	t[now].w=min(t[now<<1].w,t[now<<1|1].w);
}
void pushdown(int now){
	if(t[now].lz){
		t[now<<1].lz+=t[now].lz;
		t[now<<1].w-=t[now].lz;
		t[now<<1|1].w-=t[now].lz;
		t[now<<1|1].lz+=t[now].lz;
		t[now].lz=0;
	}
}
void build(int now,int l,int r){
	if(l==r)t[now].w=d[l];
	else{
		int mid=l+r>>1;
		build(now<<1,l,mid);
		build(now<<1|1,mid+1,r);
		update(now);
	}
}
void change1(int now,int l,int r){
	if(l==r){
		q[++T]=l;
		add(nowu,l);
		t[now].w=1000000000;
	}else{
		pushdown(now);
		int mid=l+r>>1;
		if(!t[now<<1].w)change1(now<<1,l,mid);
		if(!t[now<<1|1].w)change1(now<<1|1,mid+1,r);
		update(now);
	}
}
void change(int now,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		++t[now].lz;
		if(!--t[now].w)change1(now,l,r);
	}else{
		pushdown(now);
		int mid=l+r>>1;
		if(L<=mid)change(now<<1,l,mid,L,R);
		if(R>mid)change(now<<1|1,mid+1,r,L,R);
		update(now);
	}
}
void dfs(int now){
	sz[now]=1;
	int v;
	for(int i=head[now];i;i=edge[i].nxt){
		dfs(v=edge[i].to);
		sz[now]+=sz[v];
	}
}
void dfs1(int now){
	f[now]=1;
	int v,x=sz[now]-1;
	for(int i=head[now];i;i=edge[i].nxt){
		dfs1(v=edge[i].to);
		f[now]=(ll)f[now]*f[v]%p*ijie[sz[v]]%p*ijie[x-sz[v]]%p*jie[x]%p;
		x-=sz[v];
	}
}
int qpow(int a,int k){
	int ans=1;
	while(k){
		if(k&1)ans=(ll)ans*a%p;
		a=(ll)a*a%p;
		k>>=1;
	}
	return ans;
}
int main(){
	int n=read(),h=0;
	for(int i=ijie[0]=jie[0]=1;i<=n;++i)jie[i]=(ll)jie[i-1]*i%p;
	ijie[n]=qpow(jie[n],p-2);
	for(int i=n-1;i;--i)ijie[i]=(ll)ijie[i+1]*(i+1)%p;
	for(int i=1;i<=n;++i){
		if(a[i]=read())addd(a[i],i);
		++d[a[i]+1];
		--d[i];
	}
	for(int i=1;i<=n;++i){
		d[i]+=d[i-1];
		if(!d[i])q[0]=i;
	}
	d[q[0]]=1000000000;
	build(1,1,n);
	tot=0;
	while(h<=T){
		nowu=q[h++];
		if(a[nowu]<nowu-1)change(1,1,n,a[nowu]+1,nowu-1);
		for(int i=hed[nowu];i;i=edg[i].nxt)change(1,1,n,edg[i].to,edg[i].to);
	}
	dfs(q[0]);
	dfs1(q[0]);
	printf("%d",f[q[0]]);
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

好题，自己做的慢是因为不够努力。

不难发现所有的 $A_i$ 不会上过上一个 $A_x=0$ 的 $x$ 的位置，否则 $P_{A_i}>P_i$ 且 $P_i>P_x$ 但是 $P_x>P_{A_i}$ 就矛盾了。

所以我们想到可以按照 $0$ 划分区域，比如样例：

$$
\{0,1,0,3\}\to\{0,1\}\{0,3\}
$$

我们只需要考虑每个区域包含哪些数字，这个可以组合直接算，然后内部独立求解即可，这样每个区域就只有一个 $0$ 了。

对于一个只有一个 $A_x=0$ 的区域，这个 $A_x=0$ 显然在最前面，而且应该取为最小值，然后我们考虑其他数字，对于 $A_i=x$ 的数字相当于就没有了 $P_{A_i}<P_i$ 的限制，于是我们发现这些位置等价于 $A_i=0$，又可以划分。

于是我们发现这样一直分治下去就解决了问题。

但是每次 $\mathcal O(n)$ 划分肯定是可以卡成 $\mathcal O(n^2)$ 的，所以要考虑用 `vector` 存对于一个 $x$ 而言所有的 $A_i=x$ 的 $i$，就可以快速划分了。

备注：考虑每个区域包含哪些数字，这个问题其实就是考虑开头的 $0$ 一定要取最小值，然后其他数字可以随便取，所以设当前还能选择的数字是 $K$，这部分的长度是 $t$，那么组合数就是 $\dbinom {K-1} {t-1}$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;
const int N=3e5+5;
const LL Mod=998244353;
LL Fac[N],I[N];
inline LL Ksm(LL x,LL y)
{
	LL A=1;
	while(y)
	{
		if(y&1)A=A*x%Mod;
		x=x*x%Mod,y>>=1;
	}
	return A;
}
inline void Init(int n)
{
	Fac[0]=I[0]=1;
	for(LL i=1;i<=n;i++)Fac[i]=Fac[i-1]*i%Mod;
	I[n]=Ksm(Fac[n],Mod-2);
	for(LL i=n-1;i>=1;i--)I[i]=I[i+1]*(i+1)%Mod;
}
inline LL C(LL n,LL m)
{
	if(n<m||n<0||m<0)return 0;
	return Fac[n]*I[m]%Mod*I[n-m]%Mod;
}
vector<int>E[N];
int n,A[N];
inline LL Work(int L,int R)
{
	if(L>R)return 1;
	int m=E[L-1].size(),K=R-L+1;
	LL Ans=1;
	for(int i=m-1,Lst=R;i>=0;Lst=E[L-1][i]-1,i--)
	{
		int x=E[L-1][i];
		int Len=Lst-x+1;
		Ans=Ans*C(K-1,Len-1)%Mod*Work(x+1,Lst)%Mod;
		K-=Len;
	}
	return Ans;
}
int main()
{
	scanf("%d",&n);Init(n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),E[A[i]].pb(i);
	printf("%lld\n",Work(1,n));
}
```

---

## 作者：Iniaugoty (赞：0)

### [ARC186B Typical Permutation Descriptor](/problem/AT_arc186_b)

考虑最小值 $1$ 的位置，设它为  $t$。因为是最小值，不存在比它小的数，所以可以得到两个结论：$a _ t = 0$；$\nexists i, a _ i < t < i$。综合两个结论，可以得到 $t = \max _ {a _ i = 0} i$。

再考虑这个 $t$ 能给其他数的位置带来什么限制。注意到上面那个 $\nexists i, a _ i < t < i$，对于 $i < t$ 包是不满足的，而对于 $i > t$，这个限制即 $t \le a _ i$。这意味着，$t$ 分开的两部分，是互不影响的。

更进一步地，这个计数只需要关注相对大小，对于区间 $[l, r]$，我们找到这个区间内最小值的位置 $t = \max _ {l \le i \le r, a _ i = l - 1} i$，那么可以划分为 $[l, t - 1]$ 和 $[t + 1, r]$ 两个互不相关的部分。设其答案为 $dp _ {l, r}$，则 $dp _ {l, r} = \binom {r - l} {t - l} \times dp _ {l, t - 1} \times dp _ {t + 1, r}$，其中 $\binom {r - l} {t - l}$ 是将 $r - l$ 个数划分为大小 $t - l$ 和 $r - t$ 两部分的方案数。

这样的状态数是线性的，用记忆化搜索实现，再结合一个随便怎么求最小值的位置，时间复杂度不会超过 $O (n \log n)$。

[code](https://atcoder.jp/contests/arc186/submissions/59425845)。

---

## 作者：wangyibo201026 (赞：0)

## solution

不懂为什么很复杂。

首先最开始的想法应该是 $a_i + 1 \sim i$ 向 $i$ 连边，$i$ 向 $a_i$ 连边，然后跑一个 DAG 拓扑序计数。

但是你发现边数小炸，并且 DAG 上拓扑序计数是个不可做问题，所以我们需要换思路。

注意到 $a_i$ 就是 $i$ 左边第一个比 $a_i$ 小的树，如果熟悉笛卡尔树就知道可以根据这个信息建出笛卡尔树了。那么现在的问题就是填排列，使其满足该笛卡尔树的性质。

这是好做的，不难发现笛卡尔树上结点 $x$ 相当于是把一个值的集合划分成两个，分给左右儿子，最小值会自动适配，所以你可以 DP，在 DP 过程中只需要乘上一个将一个集合划分成两个集合的系数即可。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = ( x << 1 ) + ( x << 3 ) + ( _c ^ 48 ), _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;
const int mod = 998244353;

int n, top;
int a[N], lst[N], fac[N], inv[N], stk[N], f[N];

int fast_pow ( int a, int b ) {
  int res = 1;
  while ( b ) {
    if ( b & 1 ) {
      res = res * a;
      res %= mod;
    }
    b >>= 1;
    a = a * a;
    a %= mod;
  }
  return res;
}

int C ( int n, int m ) {
  if ( n < m ) {
    return 0;
  }
  return fac[n] * inv[n - m] % mod * inv[m] % mod;
}

struct Node {
  int ls, rs, siz;
} tree[N];

void dfs ( int x ) {
  if ( !x ) {
    return ;
  }
  dfs ( tree[x].ls ), dfs ( tree[x].rs );
  tree[x].siz = tree[tree[x].ls].siz + tree[tree[x].rs].siz + 1;
  if ( !tree[x].ls && !tree[x].rs ) {
    f[x] = 1;
  }
  else if ( !tree[x].ls ) {
    f[x] = f[tree[x].rs];
  }
  else if ( !tree[x].rs ) {
    f[x] = f[tree[x].ls];
  }
  else {
    f[x] = f[tree[x].ls] * f[tree[x].rs] % mod * C ( tree[x].siz - 1, tree[tree[x].ls].siz ) % mod;
  }
}

void Solve () {
  cin >> n;
  fac[0] = inv[0] = 1;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = fast_pow ( fac[i], mod - 2 );
    int tp = top;
    while ( tp && stk[tp] != a[i] ) {
      tp --;
    }
    if ( tp ) {
      tree[stk[tp]].rs = i;
    }
    if ( tp < top ) {
      tree[i].ls = stk[tp + 1];
    }
    top = tp;
    stk[++ top] = i;
  }
  dfs ( stk[1] );
  cout << f[stk[1]];
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

