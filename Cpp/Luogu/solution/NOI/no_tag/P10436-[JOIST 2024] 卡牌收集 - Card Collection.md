# [JOIST 2024] 卡牌收集 / Card Collection

## 题目描述

JOI 君对一款卡牌游戏中的卡牌收集充满热情。卡牌游戏中的每张卡牌都有两个整数，代表其强度和成本。为了获得一张新卡牌，JOI 君将 $N$ 张卡牌带到一个卡牌交换处。每张卡牌编号从 $1$ 到 $N$。第 $i$ 张卡牌（$1 \leq i \leq N$）的强度是 $S_i$，成本是 $V_i$。

卡牌交换处有两台机器可供使用。如果你将两张卡牌 $A$ 和 $B$ 插入其中一台机器，你将能够获得满足以下条件的卡牌 $C$：

- 如果你使用第一台机器，那么 $C$ 的强度等于 $A$ 和 $B$ 的强度中的最大值，并且 $C$ 的成本等于 $A$ 和 $B$ 的成本中的最大值。
- 如果你使用第二台机器，那么 $C$ 的强度等于 $A$ 和 $B$ 的强度中的最小值，并且 $C$ 的成本等于 $A$ 和 $B$ 的成本中的最小值。

JOI 君计划使用这些机器正好 $N - 1$ 次以获得一张新卡牌。为此，他将 $N$ 张卡牌按卡牌 $1$ 到卡牌 $N$ 的顺序依次排列。然后，他重复以下操作 $N - 1$ 次：

- 选择两张相邻的卡牌，使用其中一台机器来得到一张新卡牌，并将新卡牌放在操作前所选两张卡牌的位置。

在执行 $N-1$ 次操作后，JOI 君将只剩下一张卡牌。这张卡牌的强度和成本将取决于他执行的操作。

JOI 君有一个希望在执行 $N-1$ 次操作后获得的卡牌列表。第 $j$ 张卡牌（$1 \leq j \leq M$）由一对整数 $(T_j, W_j)$ 表示，其中 $T_j$ 是第 $j$ 张卡牌的强度，$W_j$ 是第 $j$ 张卡牌的成本。编写一个程序，给定有关 JOI 君卡牌的信息以及他想获得的卡牌列表，确定在执行 $N-1$ 次操作后他可以获得的列表中的哪些卡牌。


## 说明/提示

#### 样例解释 1

例如，JOI 君可以通过以下方式获得一张强度为 2，成本为 3 的卡牌：

- 交出卡牌 4 和卡牌 5，获得一张强度为 1，成本为 1 的卡牌。
- 交出卡牌 3 和第一次操作中获得的卡牌，获得一张强度为 1，成本为 1 的卡牌。
- 交出卡牌 1 和卡牌 2，获得一张强度为 2，成本为 3 的卡牌。
- 交出第二次和第三次操作中获得的卡牌，获得一张强度为 2，成本为 3 的卡牌。

请注意，即使在第三次操作中获得了一张强度为 2，成本为 3 的卡牌，JOI 君仍需要执行最后一次操作。即使在某些操作后获得了某张卡牌，也可能在执行 $N-1$ 次操作后无法获得它。

这个样例输入满足所有子任务的约束条件。

#### 样例解释 2

与此样例输出一样，如果在执行 $N-1$ 次操作后无法获得列表中的任何卡牌，则应输出一个空行。

这个样例输入满足所有子任务的约束条件。

#### 样例解释 3

这个样例输入满足所有子任务的约束条件。


### 约束条件

- $2 \leq N \leq 200,000$．
- $1 \leq M \leq 200,000$．
- $1 \leq S_i \leq 10^9$ ($1 \leq i \leq N$)．
- $1 \leq V_i \leq 10^9$ ($1 \leq i \leq N$)．
- $1 \leq T_j \leq 10^9$ ($1 \leq j \leq M$)．
- $1 \leq W_j \leq 10^9$ ($1 \leq j \leq M$)．
- 给定的值均为整数。

### 子任务

1. (11 分) $N \leq 20$，$M \leq 10$．
2. (38 分) $N \leq 2,000$，$M \leq 10$．
3. (22 分) $M \leq 10$．
4. (29 分) 无额外约束。

## 样例 #1

### 输入

```
5 3
1 3
2 2
4 4
1 3
1 1
2 3
2 1
4 4```

### 输出

```
1 3```

## 样例 #2

### 输入

```
2 2
1 1
2 2
1 2
2 1
```

### 输出

```
```

## 样例 #3

### 输入

```
8 8
5 2
4 4
1 3
7 8
3 1
8 7
6 5
2 6
1 4
7 2
8 8
3 1
5 6
2 7
6 3
2 5```

### 输出

```
3 4 5 8```

# 题解

## 作者：云浅知处 (赞：9)

首先，注意到对于一组询问，我们只需要关注每个数与 $(T_j,W_j)$ 的相对大小关系。这一共有 $9$ 种情况，于是我们直接做区间 DP，设一个形如 $f(l,r,0/1/2,0/1/2)$ 的状态，即可得到 $O(N^3M)$ 的做法；进一步使用 bitset 优化可以做到 $O(\frac{N^3M}{w})$，但是无法通过（甚至 $N=2000,M=10$ 可能都无法通过）。 

-------

我们考虑想要得到一个 $(T_j,W_j)$，不论怎样，操作总是由两部分构成：

- 用区间 $[l,r]$ 造出来一个 $(T_j,W_j)$。
- 然后无伤通关 $[1,l-1]$ 和 $[r+1,N]$，把这个 $(T_j,W_j)$ 保持到最后。

考虑能够保持到最后的条件。我们发现，如果某一侧全部都形如 $(\ge T_j,<W_j)$，或者全部都形如 $(\le T_j,>W_j)$，那么一定是不可能保持到最后的。否则，我们证明一定可以。

如果不是全部形如以上两种形态，那么相当于至少存在一个 $(\le T_j,\le W_j)$ 或 $(\ge T_j,\ge W_j)$。我们在这一侧一直取 min 或取 max 就可以保留这个  $(\le T_j,\le W_j)$ 或 $(\ge T_j,\ge W_j)$。最后，进行一次取 min 或取 max 即可。

现在我们考虑，用区间 $[l,r]$ 造出了 $(T_j,W_j)$，如果是直接得到的也就是 $l=r$，这种情况是好判断的。

如果这个过程也经历了至少一次合并，我们设最后一步合并的两个区间为 $[l,m]+[m+1,r]$，那么这两个区间的结果有四种可能：

- $(T_j,\le W_j)+(\le T_j,W_j)$
- $(T_j,\ge W_j)+(\ge T_j,W_j)$
- $(\le T_j,W_j)+(T_j,\le W_j)$
- $(\ge T_j,W_j)+(T_j,\ge W_j)$

不管哪种情况，我们发现总是可以将操作改为：先分别合并出 $[l,m]$ 和 $[m+1,r]$，然后把 $[1,l-1]$ 得到的 $(\le T_j,\le W_j)$ 或 $(\ge T_j,\ge W_j)$ 合并到 $[l,m]$ 里面，并保持形态不变；把 $[r+1,N]$ 得到的  $(\le T_j,\le W_j)$ 或 $(\ge T_j,\ge W_j)$ 合并到 $[m+1,r]$ 里面，最后再把 $[1,m],[m+1,N]$ 合并。

于是，我们只需要考虑最后一步操作形如 $[1,m]+[m+1,N]$ 的情形。

---------

现在，我们可以把原问题转化为 $O(N)$ 次判断如下的问题：

- 能否用一个序列造出一个形如 $(T_j,\le W_j)$ 的数。

由对称性，其他情况也是类似的。

我们考虑想要造出一个 $(T_j,\le W_j)$，发现如果它是由两个均不为 $(T_j,\le W_j)$ 的卡牌合并而来，那么唯一的情况就只有 $(\ge T_j,\le W_j)+(T_j,>W_j)$。

我们先来考虑，如何一个序列能否造出 $(\ge T_j,\le W_j)$。类似地，这个过程也由两部分组成：

- 用区间 $[l,r]$ 造出来一个 $(\ge T_j,\le W_j)$。
- 然后无伤通关 $[1,l-1]$ 和 $[r+1,N]$，把这个 $(\ge T_j,\le W_j)$ 保持到最后。

这时我们发现，$(\ge T_j,\le W_j)$ 不可能由两个均不为 $(\ge T_j,\le W_j)$ 的卡牌合并而来。于是，唯一的情况只有：原序列中存在至少一个能保留到最后的 $(\ge T_j,\le W_j)$。

现在考虑一个 $(\ge T_j,\le W_j)$ 能保留到最后的条件。发现如果某一侧全都是 $(<T_j,>W_j)$ 那么肯定无解；否则这一侧必须存在 $(\ge T_j,*)$ 或者 $(*,\le W_j)$（其中 $*$ 表示任取）。对于这种情况，同理我们也可以先在这一边一直取 min 或 max 保留这个卡牌，最后进行一次操作留下 $(<T_j,>W_j)$。

现在，我们可以在 $O(N)$ 时间内判断一个长为 $N$ 的序列能否造出一个形如 $(\ge T_j,\le W_j)$ 的卡牌。

回到原问题，考虑如何造出一个 $(T_j,\le W_j)$ 的卡牌。下面我们证明，这等价于： 

- 存在至少一个形如 $(T_j,*)$ 的卡牌，且这个序列能造出 $(\ge T_j,\le W_j)$ 的卡牌。

首先，必要性是显然的。对于充分性，假设我们使用了某个 $k$ 满足 $(S_k,V_k)$（这里 $S,V$ 是给定的初始序列）一开始就形如 $(\ge T_j,\le W_j)$，且两侧均存在至少一个 $(\ge T_j,*)$ 或 $(*,\le W_j)$。

设 $p$ 是序列中任意一个满足 $S_p=T_j$ 的卡牌，分以下两种情况：

- $p=k$。这种情况下，我们类似地在左右先进行操作，可以发现总是能保留这个 $(T_j,\le W_j)$。
- $p\neq k$。不妨设 $p<k$，那么我们在右侧正常操作，对于左侧，我们无脑保留 $T_j$（在不关心第二维的情况下，这当然是可以做到的），然后最后把留下来的 $(T_j,*)$ 和 $(\ge T_j,\le W_j)$ 进行一次合并即可。

综上命题得证。

于是，我们可以在 $O(N)$ 的时间内判断一个长为 $N$ 的序列能否造出一个形如 $(T_j,\le W_j)$ 的卡牌。对于每组询问我们都需要做 $N$ 遍上述过程，于是总的时间复杂度为 $O(N^2M)$。

------

下面就是我们熟悉的部分了！~~相信在得到最后的条件后，作为 CN OIer 你的内心已经蠢蠢欲动了（雾~~

还是不妨设最后一步合并形如 $(T_j,\le W_j)+(\le T_j,W_j)$。

我们找到第一个形如 $(T_j,*)$ 的卡牌 $x$，以及第一个形如 $(\ge T_j,\le W_j)$ 且左侧存在至少一个 $(\ge T_j,*)$ 或 $(*,\le W_j)$，或者左侧没有任何卡牌的卡牌 $y$。找到 $y$ 右侧第一个形如 $(\ge T_j,*)$ 或 $(*,\le W_j)$ 的卡牌 $z$，那么能合成 $(T_j,\le W_j)$ 的前缀只有 $[1,y]$（此时还需要 $x\le y$），以及所有的 $[1,p]$，其中 $p\ge \max(x,z)$。

同理我们也可以找到所有的后缀使得其能构造出 $(\le T_j,W_j)$。现在相当于给出 $p_1,q_1,p_2,q_2$，判断是否存在一个 $i$ 满足 $i\in \{p_1\}\cup[q_1,n],i+1\in \{p_2\}\cup [1,p_1]$。分四种情况讨论即可。

对于找到这个前缀，可以发现只需要每组询问只需要做一次「查询 $p$ 之后第一个 $(\ge u,\le v)$ 的卡牌的位置」这样的询问，还有两次查询 $(\ge u,*)$ 和 $(*,\le v)$ 的询问。后两个都容易通过线段树二分或 ST 表解决，对于第一个，我们把询问按 $u$ 排序后扫描线，那么只需要线段树二分同时维护单点修改即可。

最后还需要考虑直接拿着序列中一个 $(T_j,W_j)$ 走到最后的情形。考虑把询问记忆化，每次枚举序列中的所有 $(T_j,W_j)$ 并一一判断其前后是否分别都有一个 $(\ge T_j,\ge W_j)$ 或 $(\le T_j,\le W_j)$。注意这并不是三维偏序，因为我们只需要判断存在性。同理按照 $T$ 从小到大插入，每次线段树二分即可。

综上，本题在 $O((N+M)\log N)$ 时间内解决。带有 $8$ 倍常数，因为有四种情况且每次都要对前缀后缀同时算。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=4e5+5;
int n,m,a[N],b[N],val[N],qx[N],qy[N];
vector<pair<int,int> >ques[N];
bool ans[N];
int st[N],ed[N];

struct sgt{
	int mx[N<<2],mn[N<<2];
	#define ls(p) (p<<1)
	#define rs(p) (p<<1|1)
	void pushup(int p){mx[p]=max(mx[ls(p)],mx[rs(p)]),mn[p]=min(mn[ls(p)],mn[rs(p)]);}
	void build(int l,int r,int p){
		if(l==r)return mn[p]=mx[p]=val[l],void();
		int mid=(l+r)>>1;
		build(l,mid,ls(p)),build(mid+1,r,rs(p)),pushup(p);
	}
	int geq(int l,int r,int v,int ql,int qr,int p){ // min i in [l,r] s.t. val[i]>=v
		if(mx[p]<v||l>r)return n+1;
		if(ql==qr)return ql;
		int mid=(ql+qr)>>1,ret=n+1;
		if(l<=mid)ret=geq(l,r,v,ql,mid,ls(p));
		if(ret!=n+1)return ret;
		return geq(l,r,v,mid+1,qr,rs(p));
	}
	int leq(int l,int r,int v,int ql,int qr,int p){ // min i in [l,r] s.t. val[i]<=v
		if(mn[p]>v||l>r)return n+1;
		if(ql==qr)return ql;
		int mid=(ql+qr)>>1,ret=n+1;
		if(l<=mid)ret=leq(l,r,v,ql,mid,ls(p));
		if(ret!=n+1)return ret;
		return leq(l,r,v,mid+1,qr,rs(p));
	}
	void mdf(int x,int v,int ql,int qr,int p){
		if(ql==qr)return mx[p]=mn[p]=v,void();
		int mid=(ql+qr)>>1;
		if(x<=mid)mdf(x,v,ql,mid,ls(p));
		else mdf(x,v,mid+1,qr,rs(p));
		pushup(p);
	}
}T1,T2,T3;

int pos[N],V,pv[N],q1[N],q2[N],qq[N];
vector<int>vals[N];
void solve1(){
	for(int i=1;i<=n;i++)val[i]=a[i];T1.build(1,n,1);
	for(int i=1;i<=n;i++)val[i]=b[i];T2.build(1,n,1);
	for(int i=1;i<=n;i++)val[i]=V+1;T3.build(1,n,1);
	
	for(int i=1;i<=V;i++)pv[i]=n+1,vector<int>().swap(vals[i]);
	for(int i=1;i<=n;i++)cmin(pv[a[i]],i),vals[a[i]].emplace_back(i);

	for(int u=V;u>=1;u--){
		for(int j:vals[u])T3.mdf(j,b[j],1,n,1);
		for(auto [v,id]:ques[u]){
			int p=0;
			if(a[1]>=u&&b[1]<=v)p=1;
			else{
				p=min(T1.geq(1,n,u,1,n,1),T2.leq(1,n,v,1,n,1));
				if(p>n){pos[id]=n+1,qq[id]=0;continue;}
				p=T3.leq(p+1,n,v,1,n,1);
				if(p>n){pos[id]=n+1,qq[id]=0;continue;}
			}
			int q=min(T1.geq(p+1,n,u,1,n,1),T2.leq(p+1,n,v,1,n,1));
			pos[id]=max(q,pv[u]);
			if(pv[u]<=p)qq[id]=p;
			else qq[id]=0;
		}
	}
}

void solve(){
	for(int i=1;i<=V;i++)vector<pair<int,int> >().swap(ques[i]);
	for(int i=1;i<=m;i++)ques[qx[i]].emplace_back(mk(qy[i],i));
	solve1();
	for(int i=1;i<=m;i++)st[i]=pos[i],q1[i]=qq[i];

	reverse(a+1,a+n+1),reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++)swap(a[i],b[i]);for(int i=1;i<=m;i++)swap(qx[i],qy[i]);
	
	for(int i=1;i<=V;i++)vector<pair<int,int> >().swap(ques[i]);
	for(int i=1;i<=m;i++)ques[qx[i]].emplace_back(mk(qy[i],i));
	solve1();
	for(int i=1;i<=m;i++)ed[i]=n-pos[i]+1,q2[i]=n-qq[i]+1;

	for(int i=1;i<=m;i++){
		ans[i]|=(st[i]<ed[i]);
		if(q1[i]!=0)ans[i]|=(q1[i]<ed[i]);
		if(q2[i]!=n+1)ans[i]|=(st[i]<q2[i]);
		if(q1[i]!=0&&q2[i]!=n+1)ans[i]|=(q1[i]==q2[i]-1);
	}
	
	reverse(a+1,a+n+1),reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++)swap(a[i],b[i]);for(int i=1;i<=m;i++)swap(qx[i],qy[i]);
}

bool s1[N],s2[N],t1[N],t2[N],can[N];
map<int,vector<int> >Map[N];
map<int,bool>res[N];

void solve_case1(){
	vector<vector<int> >ps(V+1);
	for(int i=1;i<=n;i++)ps[a[i]].emplace_back(i);
	for(int i=1;i<=n;i++)val[i]=n+1;T1.build(1,n,1);
	for(int i=1;i<=V;i++){
		for(int j:ps[i])T1.mdf(j,b[j],1,n,1);
		for(int j:ps[i])s1[j]=(T1.leq(1,n,b[j],1,n,1)<=j-1);
	}

	for(int i=1;i<=n;i++)val[i]=-1;T1.build(1,n,1);
	for(int i=V;i>=1;i--){
		for(int j:ps[i])T1.mdf(j,b[j],1,n,1);
		for(int j:ps[i])s2[j]=(T1.geq(1,n,b[j],1,n,1)<=j-1);
	}
	for(int i=1;i<=V;i++)ps[i].clear();

	reverse(a+1,a+n+1),reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++)ps[a[i]].emplace_back(i);
	for(int i=1;i<=n;i++)val[i]=n+1;T1.build(1,n,1);
	for(int i=1;i<=V;i++){
		for(int j:ps[i])T1.mdf(j,b[j],1,n,1);
		for(int j:ps[i])t1[j]=(T1.leq(1,n,b[j],1,n,1)<=j-1);
	}

	for(int i=1;i<=n;i++)val[i]=-1;T1.build(1,n,1);
	for(int i=V;i>=1;i--){
		for(int j:ps[i])T1.mdf(j,b[j],1,n,1);
		for(int j:ps[i])t2[j]=(T1.geq(1,n,b[j],1,n,1)<=j-1);
	}
	for(int i=1;i<=V;i++)ps[i].clear();

	reverse(t1+1,t1+n+1),reverse(t2+1,t2+n+1),reverse(a+1,a+n+1),reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++)can[i]=((s1[i]|s2[i]|(i==1))&(t1[i]|t2[i]|(i==n)));
	for(int i=1;i<=V;i++)Map[a[i]][b[i]].emplace_back(i);

	for(int i=1;i<=m;i++){
		if(res[qx[i]].find(qy[i])!=res[qx[i]].end()){ans[i]|=res[qx[i]][qy[i]];continue;}
		for(int j:Map[qx[i]][qy[i]])if(can[j]){ans[i]=res[qx[i]][qy[i]]=1;break;}
	}
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("01-03.in","r",stdin);
	// freopen("in.txt","r",stdin);
#endif

	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=m;i++)qx[i]=read(),qy[i]=read();

	vector<int>lsh(n+m);
	for(int i=1;i<=n;i++)lsh[i-1]=a[i];
	for(int i=1;i<=m;i++)lsh[i+n-1]=qx[i];
	sort(lsh.begin(),lsh.end());
	int V1=unique(lsh.begin(),lsh.end())-lsh.begin();lsh.resize(V1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin()+1;
	for(int i=1;i<=m;i++)qx[i]=lower_bound(lsh.begin(),lsh.end(),qx[i])-lsh.begin()+1;

	lsh.resize(n+m);	
	for(int i=1;i<=n;i++)lsh[i-1]=b[i];
	for(int i=1;i<=m;i++)lsh[i+n-1]=qy[i];
	sort(lsh.begin(),lsh.end());
	int V2=unique(lsh.begin(),lsh.end())-lsh.begin();lsh.resize(V2);
	for(int i=1;i<=n;i++)b[i]=lower_bound(lsh.begin(),lsh.end(),b[i])-lsh.begin()+1;
	for(int i=1;i<=m;i++)qy[i]=lower_bound(lsh.begin(),lsh.end(),qy[i])-lsh.begin()+1;
	V=max(V1,V2);

	solve_case1();

	solve();

	for(int i=1;i<=n;i++)swap(a[i],b[i]);
	for(int i=1;i<=m;i++)swap(qx[i],qy[i]);
	solve();

	for(int i=1;i<=n;i++)a[i]=V-a[i]+1,b[i]=V-b[i]+1;
	for(int i=1;i<=m;i++)qx[i]=V-qx[i]+1,qy[i]=V-qy[i]+1;
	solve();

	for(int i=1;i<=n;i++)swap(a[i],b[i]);
	for(int i=1;i<=m;i++)swap(qx[i],qy[i]);
	solve();

	for(int i=1;i<=m;i++)if(ans[i])cout<<i<<" ";puts("");

	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：7)

![](https://cdn.luogu.com.cn/upload/image_hosting/492deokg.png)

一个思维量小很多的做法。

### Solution

哇又是神秘操作判定合不合法，考虑类似 P12294 搞一个 DFA 出来判定。

但是会遇到问题：字符集的大小实在太大。尝试把字符集缩小到常数级。

注意到对于一组询问 $(x,y)$，只有 $a_i$ 与 $x$ 的大小关系和 $b_i$ 与 $y$ 的大小关系有用。令 ${\rm sgn}(x)=[x>0]-[x<0]$（即 $x>0$ 时为 $1$，$x=0$ 时为 $0$，$x<0$ 时为 $-1$），则我们可以将 $a_i\gets {\rm sgn}(a_i-x),b_i\gets {\rm sgn}(b_i-y)$，最后查询能否合出 $(0,0)$ 即可。

那么现在的字符集已经小到足够搞一个 DFA 出来了。沿用 P12294 的方法：设阈值 $X,Z$，枚举长度 $\le X$ 的串 $x,y$，若对于所有长度 $\le Z$ 的串 $z$ 都有 $f(x+z)=f(y+z)$（$f(s)$ 表示串 $s$ 能否合出 $(0,0)$），则认为 $x$ 和 $y$ 等价。每个等价类中任意取出一个长度最小的字符串，按照转移关系即可建出 DFA。经过试验，本题中取 $X=4,Z=3$ 即可造出正确的 DFA，此时 DFA 的点数为 $24$。

把这个 DFA 表出来，每次询问都在自动机上走即可获得一个 $O(nq)$ 的做法，可以获得 $71$ 分。

然后考虑优化。直接套一个 D2T2 做法应该可以做到 $O((n+q)\sqrt{n|S|})$（其中 $S$ 为 DFA 的状态集合），然而太不优美了。尝试找一些 DFA 的性质。

$\bf Observation~1$：DFA 忽略自环后是 DAG。

$\bf Observation~2$：这个 DAG 的最长路包括 $8$ 个节点。

考虑每次跳出不是自环的一步，根据上面的分析这样至多会跳 $8$ 次，于是我们将问题转化为了区间查满足 $a_i<x,b_i<y$ 的最小的 $i$（两个小于号可以独立地变为大于号，不过本质相同故忽略）。直接树套树维护后缀矩形 $\min$ 即可做到 $O(n\log^2 n+q|P||\Sigma|\log^2 n)$，其中 $P$ 为最长路的状态集合，$\Sigma$ 为字符集。这个看起来能过吗。

然后考虑优化。~~经过 qbf 提醒~~考虑每次把所有点跳一步。对 $a$ 那维离线扫描线，以下标的线段树并维护 $\min b_i$，每次线段树二分即可在 $O(\log n)$ 时间内找出转化后问题的答案。

于是原问题就被我们做到了 $O((n+q)|P||\Sigma|\log n)$，若可持久化还可做到 $O(n|\Sigma|\log n+q|P||\Sigma|\log n)$，虽然需要卡常但已经足够通过了。这不神奇吗？？？

### Code

造自动机代码：

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2005,X=4,Z=3;
int mrg1[9][9],mrg2[9][9];
bool f[48427562][9];bool ck[48427562];char bel[48427562];
int del[10],pw[10],tot;pii s[N];int to[N][9];bool val[N];
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			mrg1[i][j]=max(i/3,j/3)*3+max(i%3,j%3);
			mrg2[i][j]=min(i/3,j/3)*3+min(i%3,j%3);
		}
	pw[0]=1;
	for(int i=1;i<=X+Z;i++)pw[i]=pw[i-1]*9;
	for(int i=1;i<=X+Z;i++)del[i]=del[i-1]+pw[i-1];
	for(int i=0;i<9;i++)f[del[1]+i][i]=1;
	ck[del[1]+4]=1;
	for(int i=2;i<=X+Z;i++){
		for(int r=0;r<pw[i];r++){
			auto &arr=f[del[i]+r];
			for(int j=1;j<i;j++){
				int p=r%pw[j],q=r/pw[j];
				for(int x=0;x<9;x++)if(f[del[j]+p][x])
					for(int y=0;y<9;y++)if(f[del[i-j]+q][y])
						arr[mrg1[x][y]]=arr[mrg2[x][y]]=1;
			}
			ck[del[i]+r]=arr[4];
		}
	}
	for(int i=0;i<=X;i++)
		for(int r=0;r<pw[i];r++){
			bel[del[i]+r]=-1;
			for(int o=1;o<=tot;o++){
				int j=s[o].fi,p=s[o].se;bool ok=1;
				for(int k=0;k<=Z;k++){
					for(int q=0;q<pw[k];q++)
						if(ck[del[i+k]+r+q*pw[i]]!=ck[del[j+k]+p+q*pw[j]]){
							ok=0;
							break;
						}
					if(!ok)break;
				}
				if(ok){
					bel[del[i]+r]=o;
					break;
				}
			}
			if(!~bel[del[i]+r]){
				++tot;
				bel[del[i]+r]=tot;
				s[tot]=make_pair(i,r);
			}
		}
	for(int i=1;i<=tot;i++){
		int j=s[i].fi,r=s[i].se;
		val[i]=ck[del[j]+r];
		for(int k=0;k<9;k++)
			to[i][k]=bel[del[j+1]+r+k*pw[j]];
	}
	cout<<tot<<'\n';
	cout<<"constexpr bool val[]={0,";
	for(int i=1;i<=tot;i++)cout<<val[i]<<",}"[i==tot];
	cout<<";\n";
	cout<<"constexpr int to[][9]={\n";
	cout<<"    {},\n";
	for(int i=1;i<=tot;i++){
		cout<<"    {";
		for(int j=0;j<9;j++)
			cout<<to[i][j]<<",}"[j==8];
		if(i<tot)cout<<',';
		cout<<'\n';
	}
	cout<<"};\n";
	return 0;
}
```

AC 代码（复杂度 $O((n+q)|P||\Sigma|\log n)$）：

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=5e5+5,Q=2e5+5,T=N+Q,INF=1e9;
constexpr bool val[]={0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0};
constexpr int to[][9]={
	{}, // 0
	{2,3,4,5,6,7,8,9,2}, // 1
	{2,3,10,5,6,7,12,9,2}, // 2
	{3,3,3,18,18,14,15,15,3}, // 3
	{10,3,4,7,20,7,10,3,10}, // 4
	{5,13,16,5,13,16,5,19,5}, // 5
	{11,11,17,11,11,11,22,11,11}, // 6
	{7,14,7,16,18,7,16,18,7}, // 7
	{12,9,12,5,21,5,8,9,12}, // 8
	{9,15,15,19,13,13,9,9,9}, // 9
	{10,3,10,16,6,7,23,15,10}, // 10
	{11,11,11,11,11,11,11,11,11}, // 11
	{12,15,23,5,6,16,12,9,12}, // 12
	{11,11,11,11,11,11,22,11,11}, // 13
	{14,14,14,18,18,14,18,18,14}, // 14
	{15,15,15,11,11,11,15,15,15}, // 15
	{16,11,16,16,11,16,16,11,16}, // 16
	{11,11,17,11,11,11,11,11,11}, // 17
	{11,11,17,11,11,11,11,11,11}, // 18
	{19,13,13,19,13,13,19,19,19}, // 19
	{20,14,20,18,18,14,24,18,20}, // 20
	{21,13,24,19,13,13,21,19,21}, // 21
	{11,11,11,11,11,11,22,11,11}, // 22
	{23,15,23,16,6,16,23,15,23}, // 23
	{24,11,24,11,11,11,24,11,24} // 24
};
int _id,_Test,n,q,a[N],b[N],x[Q],y[Q];
pii cur[Q],nxt[Q];
bool mark[Q];
int nx[T],lx,ny[T],ly;
vector<int> va[T],vb[T],vx[T],vy[T];
int L[N<<2],R[N<<2],M[N<<2],Min[N<<2],ver[N];
void build(int l,int r,int p=1){
	L[p]=l,R[p]=r,M[p]=(l+r)>>1,Min[p]=INF;
	if(l==r){
		ver[l]=p;
		return;
	}
	build(L[p],M[p],p<<1);
	build(M[p]+1,R[p],p<<1|1);
}
inline void ins(int x,int v){
	for(int p=ver[x];p;p>>=1)
		Min[p]=min(Min[p],v);
}
int vec[2][N],len[2];
inline void clr(){
	vec[0][len[0]=1]=1;
	for(bool op=0;len[op];op^=1){
		len[!op]=0;
		for(int i=1;i<=len[op];i++){
			int p=vec[op][i];
			if(Min[p]==INF)continue;
			Min[p]=INF;
			if(L[p]<R[p]){
				vec[!op][++len[!op]]=p<<1;
				vec[!op][++len[!op]]=p<<1|1;
			}
		}
	}
}
inline int qry(int l,int r,int v,int p=1){
	if(l>r||Min[p]>=v)return n+1;
	if(L[p]==R[p])return L[p];
	if(r<=M[p])return qry(l,r,v,p<<1);
	if(M[p]<l)return qry(l,r,v,p<<1|1);
	int res=qry(l,r,v,p<<1);
	if(res<=n)return res;
	return qry(l,r,v,p<<1|1);
}
inline bool ck(int x,int k){return to[x][k]!=x;}
inline void ckmin(pii &a,const pii &b){if(a.fi>b.fi)a=b;}
int pos[N];
void solve0(){ // 4
	for(int i=1;i<=lx;i++){
		if(!va[i].size()||!vx[i].size())continue;
		sort(vx[i].begin(),vx[i].end(),[&](int x,int y){
			return cur[x].fi<cur[y].fi;
		});
		const auto &v0=va[i],&v1=vx[i];
		int l=v0.size()-1,r=v1.size()-1;
		while(r>=0){
			while(l>=0&&v0[l]>=cur[v1[r]].fi)
				pos[b[v0[l]]]=v0[l],l--;
			int o=v1[r];
			if(!mark[o]&&ck(cur[o].se,4))
				ckmin(nxt[o],make_pair(pos[y[o]],4));
			r--;
		}
		while((++l)<(int)v0.size())
			pos[b[v0[l]]]=n+1;
	}
}
void solve1(){ // 1, 3, 5, 7
	for(int i=1;i<=lx;i++){
		if(!va[i].size()||!vx[i].size())continue;
		const auto &v0=va[i],&v1=vx[i];
		for(const auto &o:v0)
			ins(o,b[o]);
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,3))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,y[o]),3));
		clr();
		for(const auto &o:v0)
			ins(o,ly-b[o]+1);
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,5))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,ly-y[o]+1),5));
		clr();
	}
	
	for(int i=1;i<=ly;i++){
		if(!vb[i].size()||!vy[i].size())continue;
		const auto &v0=vb[i],&v1=vy[i];
		for(const auto &o:v0)
			ins(o,a[o]);
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,1))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,x[o]),1));
		clr();
		for(const auto &o:v0)
			ins(o,lx-a[o]+1);
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,7))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,lx-x[o]+1),7));
		clr();
	}
}
void solve2(){ // 0, 2, 6, 8
	for(int i=1;i<=lx;i++){
		const auto &v0=va[i],&v1=vx[i];
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,0))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,y[o]),0));
		for(const auto &o:v0)
			ins(o,b[o]);
	}
	clr();
	
	for(int i=1;i<=lx;i++){
		const auto &v0=va[i],&v1=vx[i];
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,2))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,ly-y[o]+1),2));
		for(const auto &o:v0)
			ins(o,ly-b[o]+1);
	}
	clr();
	
	for(int i=lx;i>=1;i--){
		const auto &v0=va[i],&v1=vx[i];
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,6))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,y[o]),6));
		for(const auto &o:v0)
			ins(o,b[o]);
	}
	clr();
	
	for(int i=lx;i>=1;i--){
		const auto &v0=va[i],&v1=vx[i];
		for(const auto &o:v1)
			if(!mark[o]&&ck(cur[o].se,8))
				ckmin(nxt[o],make_pair(qry(cur[o].fi,n,ly-y[o]+1),8));
		for(const auto &o:v0)
			ins(o,ly-b[o]+1);
	}
	clr();
}
void Solve(){
	cin>>n>>q;
	lx=ly=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		nx[++lx]=a[i];
		ny[++ly]=b[i];
	}
	for(int i=1;i<=q;i++){
		cin>>x[i]>>y[i];
		nx[++lx]=x[i];
		ny[++ly]=y[i];
		cur[i]=make_pair(1,1),mark[i]=0;
	}
	sort(nx+1,nx+lx+1),lx=unique(nx+1,nx+lx+1)-nx-1;
	sort(ny+1,ny+ly+1),ly=unique(ny+1,ny+ly+1)-ny-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(nx+1,nx+lx+1,a[i])-nx;
		b[i]=lower_bound(ny+1,ny+ly+1,b[i])-ny;
	}
	for(int i=1;i<=q;i++){
		x[i]=lower_bound(nx+1,nx+lx+1,x[i])-nx;
		y[i]=lower_bound(ny+1,ny+ly+1,y[i])-ny;
	}
	for(int i=1;i<=lx;i++){
		va[i].clear(),va[i].shrink_to_fit();
		vx[i].clear(),vx[i].shrink_to_fit();
	}
	for(int i=1;i<=ly;i++){
		vb[i].clear(),vb[i].shrink_to_fit();
		vy[i].clear(),vy[i].shrink_to_fit();
	}
	for(int i=1;i<=n;i++){
		va[a[i]].emplace_back(i);
		vb[b[i]].emplace_back(i);
	}
	for(int i=1;i<=q;i++){
		vx[x[i]].emplace_back(i);
		vy[y[i]].emplace_back(i);
	}
	for(int i=1;i<=ly;i++)pos[i]=n+1;
	build(1,n);
	for(int t=1;t<8;t++){
		bool flag=0;
		for(int i=1;i<=q;i++){
			nxt[i]=make_pair(n+1,9);
			flag|=!mark[i];
		}
		if(!flag)break;
		solve0(),solve1(),solve2();
		for(int i=1;i<=q;i++)if(!mark[i]){
			if(nxt[i].fi<=n)
				cur[i]=make_pair(nxt[i].fi+1,to[cur[i].se][nxt[i].se]);
			else
				mark[i]=1;
		}
	}
	for(int i=1;i<=q;i++)
		if(val[cur[i].se])
			cout<<i<<' ';
	cout<<'\n';
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	_Test=1;
	while(_Test--)Solve();
	return 0;
}
```

---

## 作者：Kalenist (赞：3)

## 前言
质量极高的题目，赛时竟无人通过。既需要缜密的思维又需要对数据结构的熟练掌握。

## 题意简述
给定长为 $n$ 的有序二元组序列 $\{(S_i,V_i)\}$，可以进行的操作是选择两个相邻二元组并将它们合并，合并结果是两维同时取 $\max$ 或 $\min$（可以选择）。再给出 $m$ 个询问二元组 $(T_i,W_i)$，询问是否可以通过恰好 $n-1$ 次操作使得最后得到的二元组是 $(T_i,W_i)$，询问相互独立。$n,m\le 2\times 10^5,S_i,V_i,T_i,W_i\in [1,10^9]$。

## Solution
第一个直接的观察是一个合并后的卡牌一定来源于一段区间，那么我们可以区间 DP。但这样光区间状态就是 $O(n^2)$ 的，没有前途。

于是直觉告诉我们**势必要找到刻画能否成功的简洁条件**。下面考虑能否凑出一个 $(A,B)$。

直接考虑合并的过程，可以发现必须要存在一个 $(A,*)$ 和 $(*,B)$，但显然不够。发现接下来的合并过程非常复杂。注意到**最终状态唯一且一步的抉择数量比较少，因此考虑倒过来观察分裂的过程**，注意到一定分裂出一个前缀和一个后缀。下面记 “$+$” 为取 $\max$ 的合并，“$-$” 为取 $\min$ 的合并。


------------

先讨论存在 $(A,B)$ 的情况。直接看合法似乎还是很复杂，不妨先考虑不合法。由于它最后一步只能分裂出 $(\le A,\le B)$ 或 $(\ge A,\ge B)$ 的卡，因此若它前后都是形如 $(<A,>B)$ 或 $(>A,<B)$ 的卡，那么显然不合法，因为不等号相反。那么若存在不等号相同的单独的 $(\le A,\le B)$ 或 $(\ge A,\ge B)$，我们发现由于不等号是同向的，因此总可以通过只 $+$ 或 $-$ 保留同向的卡，最后一步与 $(A,B)$ 合并。因此可以发现此时的充要条件就是：

- **存在一个 $(A,B)$，使得它前后都存在一个 $(\le A,\le B)$ 或 $(\ge A,\ge B)$。**



接下来考虑 $A,B$ 分居前后缀的情况。根据最后一步是 $+$ 还是 $-$，不难发现只有这几种情况：

- $(A,\ge B)-(\ge A,B)$
- $(\ge A,B)-(A,\ge B)$
- $(A,\le B)+(\le A,B)$
- $(\le A,B)+(A,\le B)$

（虽然这里的讨论可能有重复，但可以发现不影响合法性。）

注意到这些形式是很对称的，不妨考虑一个区间什么时候能够得到 $(A,\le B)$。

首先存在 $(A,*)$ 是必须的。不妨设它在前缀，仍考虑最后一步分裂的过程，只有两种情况：

- $(A,*)-(\ge A,\le B)$
- $(A,\le B)+(\le A,\le B)$

注意到第二种情况是有子问题形式的。它要么在某处递归到第一种情况，要么递归到 $(A,B)+(\le A,\le B)$。后者已经证明了合法性，同时 $(\le A,\le B)$ 的存在不影响 $(\ge A,\le B)$，因此只用考虑第一种情况。

找到第一个包含 $(A,*)$ 的前缀，由于只有第一维的限制，$(A,*)$ 一定能被合并出。于是现在只要考虑如何能凑出 $(\ge A,\le B)$。

注意到其不等号相反，它必然分裂出一个 $(\ge A,\le B)$。归纳可以知道必须存在一个单独的 $(\ge A,\le B)$。考虑这个卡前后的卡。类似对 $(A,B)$ 的讨论，前后不能都是 $(<A,>B)$。发现这个限制更松。进一步的只需要存在单独的 $(\ge A,*)$ 或 $(*,\le B)$ 的卡即可，因为我们可以用 $+/-(\ge A,\le B)$ 来免去另一维的限制。充分性的证明与“存在 $(A,B)$”部分是同理的。

注意到 $(A,*)$ 可以将 $(\ge A,\le B)$ 某一侧的卡牌全部合并完，因此它相当于提供了 $(\ge A,*)$。于是判定一个区间能否合并出 $(A,\le B)$ 的充要条件就是：

- **存在一个 $(A,*)$，同时存在一个 $(\ge A,\le B)$ 使得它前后都存在 $(\ge A,*)$ 或 $(*,\le B)$。**



至此我们已经完成了全部判定。容易在 $O(n^2)$ 的复杂度内通过枚举前后缀判定一个 $(A,B)$，总复杂度为 $O(n^2m)$，[可以拿到 $\text{49pts}$](https://loj.ac/s/2084391)。



------------


注意到上面的条件都形如“找到一个满足条件的卡，使得它前后都存在满足另一个条件的卡”。如此简洁的形式让我们不禁**考虑用贪心和数据结构优化之**。

由于“存在 $(A,B)$”和“不存在 $(A,B)$”的判定可以是“或”的关系，于是我们可以看作两个独立的问题分别判定。

对于存在 $(A,B)$ 的部分，由于限制是“前后存在 $(\le A,\le B)$ 或 $(\ge A,\ge B)$”，那么我们可以贪心找到第一个满足条件的 $l$ 和最后一个满足条件的 $r$，于是只要判断 $[l+1,r-1]$ 中是否存在 $(A,B)$（$(A,B)$ 在 $1,n$ 的情况也可以借助 $l,r$ 简单判断）。

找 $(A,B)$ 的过程可以用哈希+主席树实现，而找 $l,r$ 的过程可以对 $A$ 一维做扫描线，每次将一个位置作为关键值挂在以 $B$ 这一维为下标的线段树上，于是只用做单点修改和区间最值，可以做到 $O(n\log n)$。（如果不想写哈希和主席树也可以枚举 $(A,B)$ 的位置，这样只用找 $l,r$ 并简单判定。）

对于不存在 $(A,B)$ 的部分，四个子部分的前后缀也可以分别判定。以 $(A,\ge B)-(\ge A,B)$ 中凑出 $(A,\ge B)$ 为例，由于条件也仅仅是“存在”，因此若前缀 $[1,x]$ 能凑出 $(A,\ge B)$，$[1,x+1]$ 一定也可以。于是同样可以贪心找到第一个 $(A,*)$，设其位置为 $p$，那么它已经能提供 $(\le A,*)$ 的条件了。于是只要找到 $[1,p-1]$ 中第一个 $(\le A,*)$ 或 $(*,\ge B)$ 设为 $q$，并判定 $[q+1,p-1]$ 中是否存在 $(\le A,\ge B)$，若存在最短合法前缀即为 $[1,p]$；否则找到 $[p+1,n]$ 中第一个 $(\le A,\ge B)$ 设为 $t$，并找到 $[t+1,n]$ 中第一个 $(\le A,*)$ 或 $(*,\ge B)$ 设为 $s$，于是合最短法前缀就是 $[1,s]$。只需要判定前后缀是否相交即可。

找 $(A,*)$ 是简单的，找形如一个前缀或后缀中第一个或最后一个 $(\le A,*)$ 可以用线段树二分实现。判定 $[l,r]$ 中是否存在 $(\le A,\ge B)$ 可以对 $A$ 一维扫描线，将 $B$ 作为关键值挂在以序列位置为下标的线段树上，同样是单点修改和区间最值。找到一段后缀中第一个 $(\le A,\ge B)$ 就是在这个线段树上二分。同样可以做到 $O(n\log n)$。

那么最终复杂度就是 $O(n\log n)$。最终实现时可以对对称的问题交换 $A,B$ 两维或翻转序列再做一次。

## 代码
根据上面的分析可以知道具体实现并不高深但是十分复杂，这可能也是赛时无人通过的重要原因。[这里给出一份官方实现的代码。](https://loj.ac/s/2062849)

---

