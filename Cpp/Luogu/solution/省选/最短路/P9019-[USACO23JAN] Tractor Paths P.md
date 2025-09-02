# [USACO23JAN] Tractor Paths P

## 题目描述

**注意：这个问题的时间限制是4秒，内存限制是512MB，是默认值的两倍。**

农民约翰有 $N
(2 \le N \le 2 \cdot 10^5)$ 台拖拉机, 其中第 $i$ 台拖拉机只能在序列 $[l_i,r_i]$ 内使用。拖拉机有左端点 $l_1<l_2<\cdots <l_N$ 和右端点 $r_1<r_2< \cdots <r_N$. 有一些拖拉机是特别的。

如果 $[l_i,r_i]$ 和 $[l_j,r_j]$ 相交，则两台拖拉机 $i$ 和 $j$ 是相邻的。 约翰可以从一辆拖拉机转移到任何相邻的拖拉机上。两台拖拉机 $a$ 和 $b$ 之间的路径由一个传输序列组成，这样序列中的第一个拖拉机是 $a$，序列中的最后一个拖拉机是 $b$，并且序列中的每两个连续的拖拉机相邻。 保证拖拉机 $1$ 和 拖拉机 $N$ 之间有一条路径。路径的长度是转移的数量 (或等价地，其中拖拉机的数量减去 $1$)。

给定 $Q (1 \le Q \le 2 \cdot 10^5)$ 组询问，每次给定 $a$ 和 $b (1 \le a<b \le N)$。 对于每组询问，你需要回答两个问题：

 - $a$ 到 $b$ 的最短路径。
 - 在保证传送次数的最少的情况下，有多少个特殊拖拉机的区间可能被某条最短路经过。

## 说明/提示

### 样例 $1$ 解释

$8$ 个拖拉机的时间间隔，按顺序，是 $[1,5],[2,10],[3,11],[4,12],[6,13],[7,14],[8,15],[9,16]$。

对于第四个查询, 第 $1$ 台和第 $5$ 台拖拉机之间有三条最短路径: $1 \rightarrow 2 \rightarrow 5$, $1 \rightarrow 3 \rightarrow 5$, 和 $1 \rightarrow 4 \rightarrow 5$。这些最短路径的长度都为 $2$。

另外, 拖拉机 $1,2,3,4,5$
都是前面提到的三条最短路径之一的一部分, 由于 $1,2,4,5$ 是特殊的，因此有 $4$ 台特殊拖拉机，这样存在至少一条包含拖拉机 $1$ 到 $5$ 的最短路径。


 - 数据点 $2-3$： $N,Q \le 5000$
 - 数据点 $4-7$： 最多 $10$ 台特别的拖拉机。
 - 数据点 $8-16$： 没有额外的约束。
 
 翻译提供者：[shuqiang](https://www.luogu.com.cn/user/685964)

## 样例 #1

### 输入

```
8 10
LLLLRLLLLRRRRRRR
11011010
1 2
1 3
1 4
1 5
1 6
1 7
1 8
2 3
2 4
2 5```

### 输出

```
1 2
1 1
1 2
2 4
2 3
2 4
2 3
1 1
1 2
1 2```

# 题解

## 作者：PersistentLife (赞：19)

### [【USACO23JAN_Pt T1】Tractor Paths](http://usaco.org/index.php?page=viewproblem2&cpid=1284)

[cnblogs](https://www.cnblogs.com/znstz2018/p/17087422.html)

容易发现，对于每个区间 $i$，存在一个数 $R_i$ 满足 $i$ 能往右跳到 $[i+1,R_i]$ 中的所有区间，且 $R_i$ 递增；类似的存在一个数 $L_i$ 满足 $i$ 往左能跳到 $[i-1,L_i]$ 中的所有区间，且 $L_i$ 递增。

第一问是简单的，倍增求解即可。

第二问考虑枚举在跳第几步的时候离开最优路径去走到一个关键点。令 $f(k,i)$ 表示从 $i$ 往右跳 $k$ 步最大跳到的编号是什么， $g(k,i)$ 表示 $i$ 往左跳 $k$ 步最小跳到的编号是多少，$cnt(l,r)$ 表示编号在 $[l,r]$ 之间有多少个关键点，第一问的答案是 $dis$。则第二问的答案是 $cnt(a,a)+cnt(b,b)+\sum_{i=1}^{ans-1} cnt(g(b,ans-i),f(a,i))$。这些区间是不交的（如果两个区间有交，则 $dis$ 并不是最短路径），拆成前缀和用倍增维护即可，复杂度 $O(n \log n)$。

```
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,Q;
char S[400005],W[400005];
int L[200005],R[200005];
int bl[200005],sum[200005];
int f[18][200005],g[18][200005];
int dist(int u,int v)
{
	if(u==v) return 0;
	int ans=0;
	for(int k=17;k>=0;k--) if(f[k][u]!=-1&&f[k][u]<v) ans+=(1<<k),u=f[k][u];
	return ans+1; 
}
int sr[18][200005],sl[18][200005];
void solve()
{
	scanf("%d%d",&n,&Q);
	scanf("%s",S+1);
	int cntL=0,nowL=1;
	for(int i=1;i<=2*n;i++)
	{
		if(S[i]=='L') cntL++;
		else R[nowL]=cntL,nowL++;
	}
	int cntR=n+1,nowR=n;
	for(int i=2*n;i>=1;i--)
	{
		if(S[i]=='R') cntR--;
		else L[nowR]=cntR,nowR--;
	}
	scanf("%s",W+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+W[i]-'0';
	memset(f,-1,sizeof(f)),memset(g,-1,sizeof(g));
	for(int i=1;i<n;i++) f[0][i]=R[i],sr[0][i]=sum[R[i]];
	for(int i=n;i>=2;i--) g[0][i]=L[i],sl[0][i]=sum[L[i]-1];
	for(int k=1;k<18;k++) for(int i=1;i<n;i++) if(f[k-1][i]!=-1) 
	{
		f[k][i]=f[k-1][f[k-1][i]];
		if(f[k][i]!=-1) sr[k][i]=sr[k-1][i]+sr[k-1][f[k-1][i]];
	}
	for(int k=1;k<18;k++) for(int i=n;i>=2;i--) if(g[k-1][i]!=-1)
	{
		g[k][i]=g[k-1][g[k-1][i]];
		if(g[k][i]!=-1) sl[k][i]=sl[k-1][i]+sl[k-1][g[k-1][i]];
	}
	while(Q--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		int ans1=dist(u,v),ans2=0;
		ans2+=W[u]-'0'+W[v]-'0';
		for(int k=17;k>=0;k--) if((ans1-1)&(1<<k)) ans2+=sr[k][u],u=f[k][u];
		for(int k=17;k>=0;k--) if((ans1-1)&(1<<k)) ans2-=sl[k][v],v=g[k][v];
		printf("%d %d\n",ans1,ans2);
	}
}
signed main()
{
	int _=1;
//	cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Ecrade_ (赞：13)

题意：

- 有 $n$ 个区间 $[l_i,r_i]$，满足 $l_1<l_2<\dots<l_n$，$r_1<r_2<\dots<r_n$，且 $\forall\ 2\le i\le n$ 都有 $l_i<r_{i-1}$。其中，一部分区间是关键区间。
- 一个区间可以传送到另一个区间，当且仅当两区间相交。
- $q$ 次询问，每次给定两个区间 $a$ 和 $b$，求：
    1. 从 $a$ 到 $b$ 至少需要传送几次。
    2. 在保证传送次数最少的前提下，有多少个关键区间可以在此过程中被传送到。
- $2\le n\le 2\cdot 10^5$，$1\le q\le 2\cdot 10^5$，$1\le a<b\le n$。

---

先将所有区间按左端点（或右端点）从小到大排序。

对于第一问，一个显然的贪心是每次选取与当前区间相交的最靠右的区间，这启发我们建出一棵树：树上的 $i$ 号结点表示第 $i$ 个区间，$i$ 号结点的父亲是与第 $i$ 个区间相交的最靠右的区间所对应的结点，记之为 $p_i$。

我们的贪心对应的树上操作就是从 $a$ 号结点开始，每次跳向父亲结点，直到当前结点编号不比 $b$ 小为止。记最终所在的结点编号为 $t$，则第一问的答案即为 $a$ 到 $t$ 的距离，利用倍增即可快速求出 $t$。**注意：实际上最后一步需要恰好跳到 $b$ 号结点，但是为了叙述方便，我们这里记录的 $t$ 是 $a$ 的一个祖先结点。**

对于第二问，我们首先需要明确每次从某个结点能跳到哪些结点。不难发现，对于一个结点 $i$，其能跳到的结点编号构成的集合为 $(i,p_i]$，那么它们具体在树的哪些位置呢？

考虑建树的过程，我们每次按编号从小到大加入结点，可以发现当加入一个结点时，其所有儿子的结点编号必然是当前所有暂无父亲的结点编号中最小的若干个（可以为零个）。由此我们可以证明，对于所有深度相同的结点编号，以及一个结点所有儿子的结点编号，它们都必然构成一段连续的区间，而这也使这棵树拥有了极好的性质。

接下来我们以下图这棵树为例（当然实际情况中树的形态可以千奇百怪，这里为了美观画了一棵对称的树）：

![](https://cdn.luogu.com.cn/upload/image_hosting/pm5r8bff.png)

形象化地，若 $i$ 号结点与 $j$ 号结点同深度且 $i<j$，则我们称 $i$ 号结点在 $j$ 号结点左边，$j$ 号结点在 $i$ 号结点右边。可以发现，$(i,p_i]$ 这段区间对应了 $i$ 右边的所有结点以及 $p_i$ 及其左边的所有结点。依旧形象化地，我们将跳到 $i$ 右边的某结点的一次操作称为 “ 向右跳 ”，将跳到 $p_i$ 及其左边的某结点的一次操作称为 “ 向左上跳 ”。

回到原问题，我们分两种情况讨论。

**1. $b=t$ 或 $b$ 在 $t$ 左边。**

由于每次操作只能使当前结点的深度减少 $0$（向右跳）或 $1$（向左上跳），而 $b$ 又与 $t$ 同深度，故我们每次只能向左上跳以保证操作次数最少。

以 $a=10,b=30,t=32$ 为例，则下图中的绿色结点即为可经过的所有结点：

![](https://cdn.luogu.com.cn/upload/image_hosting/6jsymf81.png)

不难发现，绿色结点的编号在 $[i,p_i]$ 内且 DFS 序也在一段区间内，这是经典的二维数点问题，离线下来用树状数组维护即可。

**2. $b$ 在 $t$ 的某个子结点右边。**

同样地，通过分析深度变化可知，我们需恰好进行一次向右跳的操作，其余操作均为向左上跳。

以 $a=3,b=32,t=34$ 为例，则下图中的蓝色结点即为可经过的所有结点：

![](https://cdn.luogu.com.cn/upload/image_hosting/f8d2bnrj.png)

不难发现，蓝色结点的编号在 $[i,p_i]$ 内且 DFS 序在两段区间内，也是个二维数点问题。

至此，我们便用 $O(n\log n+q\log n)$ 的时间复杂度解决了本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,q,x,y,L,tmp,timer,l[200009],r[200009],dfn[200009],dis[200009],ans[200009],bit[200009],anc[200009][20];
char d[400009],s[200009];
struct st{ll x,w,id;};
vector <ll> to[200009];
vector <st> qr[200009];
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
void upd(ll x,ll y){for (;x <= n;x += x & (-x)) bit[x] += y;}
ll query(ll x){ll res = 0; for (;x;x -= x & (-x)) res += bit[x]; return res;}
void build(){
	ll cl = 0,cr = 0,pos = 1;
	for (ll i = 1;i <= 2 * n;i += 1){
		if (d[i] == 'L') l[++ cl] = i;
		else r[++ cr] = i;
	}
	for (ll i = 2;i <= n;i += 1){
		while (pos < i && (i == n || l[i + 1] > r[pos])){
			anc[pos][0] = i;
			to[i].emplace_back(pos ++);
		}
	}
}
void dfs(ll u){
	dfn[u] = ++ timer;
	for (ll i = 1;i <= L;i += 1) anc[u][i] = anc[anc[u][i - 1]][i - 1];
	for (ll i = 0;i < to[u].size();i += 1) dfs(to[u][i]);
}
void add(ll l,ll r,ll L,ll R,ll id){
	qr[r].emplace_back((st){R,1,id});
	qr[r].emplace_back((st){L - 1,-1,id});
	qr[l - 1].emplace_back((st){R,-1,id});
	qr[l - 1].emplace_back((st){L - 1,1,id});
}
void work(){
	for (ll i = 1;i <= n;i += 1){
		if (s[i] == '1') upd(dfn[i],1);
		for (ll j = 0;j < qr[i].size();j += 1){
			ans[qr[i][j].id] += query(qr[i][j].x) * qr[i][j].w;
		}
	}
}
int main(){
	n = read(),q = read(),L = log2(n),scanf("%s",d + 1),scanf("%s",s + 1);
	build(),dfs(n);
	for (ll i = 1;i <= q;i += 1){
		x = read(),y = read(),dis[i] = 1;
		ll tmp = x;
		for (ll j = L;j >= 0;j -= 1){
			if (!anc[x][j] || anc[x][j] >= y) continue;
			dis[i] += 1 << j,x = anc[x][j];
		}
		if (dfn[tmp] < dfn[y]) add(tmp,y,1,dfn[tmp],i),add(tmp,y,dfn[y],n,i);
		else add(tmp,y,dfn[y],dfn[tmp],i);
	}
	work();
	for (ll i = 1;i <= q;i += 1) printf("%lld %lld\n",dis[i],ans[i]);
	return 0;
}
```

---

## 作者：K0stlin (赞：8)

一种不太一样的思路。

第一问可以倍增轻松解决，我们着重考虑第二问。

首先不在询问区间内的关键区间肯定不计入答案，对于在询问区间内的我们考虑以下性质：

> 计从 $ql$ 到 $qr$ 的距离是 $L$，$[ql,qr]$ 任何节点到 $ql,qr$ 的距离和 $\le L+1$，且如果 $=L$ 则可以出现在 $ql$ 到 $qr$ 的某一最短路上。

证明：首先随意拉出一条 $ql$ 到 $qr$ 的最短路 $a_1,a_2,\dots , a_L$，路上肯定满足性质，对于路径上相邻两个元素 $a_k,a_{k+1}$ 之间任意节点 $x$，必然有 $x$ 可一步到 $a_k,a_{k+1}$。因为如果不然，根据 $a_k,a_{k+1}$ 可一步互达，必包含 $x$ 元素，与区间不互相包含矛盾。

我们可以这样维护所有关键点到 $ql,qr$ 的距离和：分别从 $n\sim 1$ 和 $1\sim n$ 扫一遍，每次尽可能向左/右走一步，记录下当前节点传递着几个关键点及距离和，同时另设一变量表示当前节点的答案。

那么我们处理的唯一难点在于消除区间外的关键点贡献。对于那些不能一步从 $ql$ 到 $qr$ 的询问，设 $ql$ 向右一步最远到 $ml$，$qr$ 向左一步最远到 $mr$，那么位于 $[ql,qr]$ 外部的关键点必然会被传递至 $[ql,ml]$ 或 $[mr,qr]$ 中。考虑倍增求第一问时多求两个值 $mdl,mdr$ 分别表示 $ql,qr$ 分别向右，左走 $L-1$ 步最远到哪个节点，那么传递到 $[ql,ml]$ 中需要消除的节点贡献为其中传递的距离和以及 $[ql,mdr-1]$ 中传递的个数和乘上 $L$ 加 $[mdr,ml]$ 中传递的个数和乘上 $L-1$。$[mr,qr]$ 同理。注意我们是从 $n\sim 1$ 扫到 $qr$ 时处理 $[mr,qr]$，从 $1\sim n$ 扫到 $ql$ 时处理 $[ql,ml]$。

消除贡献部分可以通过特殊处理 $ml,mr$ 位置上由 $ql,qr$ 传过来的贡献，用在线维护前后缀和做到线性。不过为了好写，我们使用树状数组直接处理。

复杂度 $O((n+q)\log n)$，代码：
```cpp
char s[N<<1];
int n,q,L[N],R[N],ok[N],ql[N],qr[N];
int tr[25][N],tr_[25][N],len[N],md[N],md_[N];
int mL[N],mR[N],d[N],f[N];
ll S[N],Ans[N];
vector<int> T[N];
inline void init() {
    n=read();q=read();
    scanf("%s",s+1);
    for(int i=1;i<=2*n;++i)
        if(s[i]=='L') L[++L[0]]=i;
        else R[++R[0]]=i;
    scanf("%s",s+1);
    for(int i=1;i<=n;++i)
        ok[i]=s[i]-'0';
}
inline void prep() {
    int pos=1;
    for(int i=1;i<=n;++i) {
        while(pos<n&&L[pos+1]<=R[i]) ++pos;
        mR[i]=pos;
    }
    pos=n;
    for(int i=n;i>=1;--i) {
        while(pos>1&&L[i]<=R[pos-1]) --pos;
        mL[i]=pos;
    }
    for(int i=1;i<=n;++i) d[i]=d[i-1]+ok[i];
    for(int i=1;i<=n;++i) tr[0][i]=mR[i],tr_[0][i]=mL[i];
    for(int j=1;j<=19;++j)
        for(int i=1;i<=n;++i)
            tr[j][i]=tr[j-1][tr[j-1][i]],
            tr_[j][i]=tr_[j-1][tr_[j-1][i]];
    for(int i=1;i<=q;++i) {
        ql[i]=read();qr[i]=read();
        if(mR[ql[i]]<qr[i]) {
            T[ql[i]].push_back(i);T[qr[i]].push_back(-i);
            int now=ql[i];
            for(int j=19;j>=0;--j)
                if(tr[j][now]<qr[i])
                    now=tr[j][now],len[i]|=(1<<j);
            md[i]=now;++len[i];
            now=qr[i];
            for(int j=19;j>=0;--j)
                if(tr_[j][now]>ql[i])
                    now=tr_[j][now];
            md_[i]=now;
        }
        else len[i]=1,Ans[i]=(d[qr[i]]-d[ql[i]-1])-(ok[ql[i]]+ok[qr[i]])+1ll*(d[qr[i]]-d[ql[i]-1])*len[i];
    }
}
struct Bit {
    ll w[N];
    inline void Add(int x,ll val) {
        while(x<=n) {
            w[x]+=val;
            x+=x&-x;
        }
    }
    inline ll Query(int x) {
        ll sum=0;
        while(x) {
            sum+=w[x];
            x-=x&-x;
        }
        return sum;
    }
    inline void clear() {memset(w,0,sizeof w);}
}tr1,tr2;
inline void solve1() {
    int rg1,rg2;ll F=0,qwq;
    for(int i=n,p;i>=1;--i) {
        for(int&V:T[i]) {
            if(V<0) {
                p=-V;
                rg2=qr[p];rg1=mL[rg2];
                qwq=tr2.Query(rg2)-tr2.Query(rg1-1);
                qwq+=(tr1.Query(md[p])-tr1.Query(rg1-1))*(len[p]-1);
                qwq+=(tr1.Query(rg2)-tr1.Query(md[p]))*len[p];
                Ans[p]-=qwq;
            } else {
                p=V;
                Ans[p]+=F;
            }
        }
        f[mL[i]]+=f[i]+ok[i]; S[mL[i]]+=S[i]+f[i]+ok[i];
        tr1.Add(mL[i],f[i]+ok[i]); tr2.Add(mL[i],S[i]+f[i]+ok[i]);
        F+=f[i]+ok[i];
    }
    memset(f,0,sizeof f);memset(S,0,sizeof S);
    tr1.clear(); tr2.clear();
}
inline void solve2() {
    int rg1,rg2;ll F=0,qwq;
    for(int i=1,p;i<=n;++i) {
        for(int&V:T[i]) {
            if(V>0) {
                p=V;
                rg1=ql[p];rg2=mR[rg1];
                qwq=tr2.Query(rg2)-tr2.Query(rg1-1);
                qwq+=(tr1.Query(rg2)-tr1.Query(md_[p]-1))*(len[p]-1);
                qwq+=(tr1.Query(md_[p]-1)-tr1.Query(rg1-1))*len[p];
                Ans[p]-=qwq;
            } else {
                p=-V;
                Ans[p]+=F;
            }
        }
        f[mR[i]]+=f[i]+ok[i]; S[mR[i]]+=S[i]+f[i]+ok[i];
        tr1.Add(mR[i],f[i]+ok[i]); tr2.Add(mR[i],S[i]+f[i]+ok[i]);
        F+=f[i]+ok[i];
    }
    memset(f,0,sizeof f);memset(S,0,sizeof S);
    tr1.clear(); tr2.clear();
}
inline void print() {
    for(int i=1;i<=q;++i) printf("%d %lld\n",len[i],d[qr[i]]-d[ql[i]-1]-(Ans[i]-1ll*(d[qr[i]]-d[ql[i]-1])*len[i]));
}

```


---

## 作者：dead_X (赞：6)

## 前言

赢麻了。

介绍一种非常好做的方法。

## 题解

考虑第一问，直接倍增就行，时间复杂度 $O((n+q)\log n)$。

考虑第二问，我们发现了一个经典结论：设 $d(l,r)$ 为 $l$ 到 $r$ 的距离，$x$ 为 $[l,r]$ 中的任意一点，则有 $d(l,r)\leq d(l,x)+d(x,r)\leq d(l,r)+1$。

第一个不等号很好证明，第二个不等号也很好证明。

那么如果我们要计数有多少个点满足 $d(l,x)+d(x,r)=d(l,r)$，只需要求出 $\sum d(l,x)+\sum d(x,r)-\sum d(l,r)$ 即可。

这个计数挺简单的，直接按照 dfs 序离线，用每个点能到的最远的点建树，通过线段树维护每个点的权值最后计算，这部分其实我也忘记我赛时到底怎么写的了，所以我把代码给出来大家自己看一眼吧。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
struct seg
{
#define int long long
	int tag[800003],ans[800003];
	void push_down(int x,int l1,int l2)
	{
		tag[x<<1]+=tag[x],tag[(x<<1)+1]+=tag[x];
		ans[x<<1]+=tag[x]*l1,ans[(x<<1)+1]+=tag[x]*l2;
		tag[x]=0;
		return ;
	}
	void update(int l,int r,int L,int R,int id,int val)
	{
		if(L<=l&&r<=R) 
		{
			tag[id]+=val;
			ans[id]+=(r-l+1)*val;
			return ;
		}
		int mid=(l+r)>>1;
		push_down(id,mid-l+1,r-mid);
		if(L<=mid) update(l,mid,L,R,id<<1,val);
		if(R>=mid+1) update(mid+1,r,L,R,(id<<1)+1,val);
		ans[id]=ans[(id<<1)]+ans[(id<<1)+1];
		return ;
	}
	int query(int l,int r,int L,int R,int id)
	{
		if(L<=l&&r<=R) return ans[id];
		int mid=(l+r)>>1;
		push_down(id,mid-l+1,r-mid);
		int res=0;
		if(L<=mid) res+=query(l,mid,L,R,id<<1);
		if(R>=mid+1) res+=query(mid+1,r,L,R,(id<<1)+1);
		return res;
	}
#undef int
}T;
int al[200003],ar[200003];
int b[200003];
int f[200003][18];
char s[400003];
int dis(int l,int r)
{
	if(l==r) return 0;
	int ans=0;
	for(int i=17; i>=0; --i)
		if(f[l][i]<r) l=f[l][i],ans+=1<<i;
	return ans+1;
}
int F[200003];
ll G[200003];
vector<int> e[200003];
struct node{int l,r,id;};
vector<node> vl[200003],vr[200003];
int n=read(),m=read(),L=0;
void dfsl(int x)
{
	for(auto [l,r,id]:vl[x])
		G[id]-=T.query(1,L,l,r,1)-(b[l]==x);
	int pos=upper_bound(b+1,b+L+1,x)-b;
	if(pos<=L) T.update(1,L,pos,L,1,1);
	for(int y:e[x]) dfsl(y);
	if(pos<=L) T.update(1,L,pos,L,1,-1);
	return ;
}
void dfsr(int x)
{
	for(auto [l,r,id]:vr[x])
		G[id]-=T.query(1,L,l,r,1)-(b[r]==x);
	int pos=lower_bound(b+1,b+L+1,x)-b;
	if(pos>1) T.update(1,L,1,pos-1,1,1);
	for(int y:e[x]) dfsr(y);
	if(pos>1) T.update(1,L,1,pos-1,1,-1);
	return ;
}
signed main()
{
	scanf("%s",s+1);
	for(int i=1,x=0,y=0; i<=n*2; ++i)
		if(s[i]=='L') ++x; else al[++y]=x;
	for(int i=n*2,x=n+1,y=n+1; i>=1; --i)
		if(s[i]=='R') --x; else ar[--y]=x;
	scanf("%s",s+1);
	for(int i=1; i<=n; ++i)
		if(s[i]=='1') b[++L]=i;
	for(int i=n; i>=1; --i)
	{
		f[i][0]=al[i];
		for(int j=1; j<18; ++j)
			f[i][j]=f[f[i][j-1]][j-1];
	}
	for(int i=1,l,r,l1,r1; i<=m; ++i)
	{
		l=read(),r=read(),F[i]=dis(l,r),
		l1=lower_bound(b+1,b+L+1,l)-b,
		r1=upper_bound(b+1,b+L+1,r)-b-1;
		if(l1<=r1)
		{
			G[i]=1ll*(F[i]+1)*(r1-l1+1),
			vl[l].push_back((node){l1,r1,i}),
			vr[r].push_back((node){l1,r1,i});
		}
	}
	T.update(1,L,1,L,1,1);
	for(int i=1; i<n; ++i)
		e[al[i]].push_back(i);
	dfsl(n);
	for(int i=1; i<=n; ++i) e[i].clear();
	for(int i=2; i<=n; ++i)
		e[ar[i]].push_back(i);
	dfsr(1);
	for(int i=1; i<=m; ++i)
		printf("%d %lld\n",F[i],G[i]);
	return 0;
}
```

---

## 作者：analysis (赞：4)

模拟赛题目，奇奇怪怪的大无语题目又增加了。

我们分点实现。

## Inputs $2-3$

（吐槽一下教练的神奇绑点，把 $2$、$3$、$16$ 绑在一起了）

发现 $O(NQ)$ 可以过。

容易想到一个贪心策略：每步尽可能走更多的拖拉机得到的一定为最短路（仔细看看题就知道了）。

所以处理出每步能到的编号最大的拖拉机。

暴力处理即可。

（我直接想到下个做法了，所以这里没有代码）

## Inputs $4-7$

（考场出现了脑残情况，导致这点也挂了）

一个个跳过于缓慢了，考虑倍增优化。

处理出从 $i$ 点出发走 $2^j$ 步能到的编号最大的拖拉机。

然后就可以很快处理出第一问了。

第二问暴力。

对于特殊拖拉机 $k$，若

$$
dis(i,k) + dis(k,j) = dis(i,j)
$$

则 $k$ 在 $(i,j)$ 最短路上。

## 42pts in Lougu

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q;
struct qj {
    int l, r, zy;
    qj(int l = 0, int r = 0, int zy = 0) : l(l), r(r), zy(zy) {}
} a[200005];
int ts[200005], cnt, f[200005][20];
int dis(int a, int b) {
    if (a > b)
        return -0x3f3f3f3f;
    if (a == b)
        return 0;
    int k = 0, pos = a;
    for (int i = 18; i >= 0; i--) {
        if (f[pos][i] < b) {
            pos = f[pos][i];
            k += (1 << i);
        }
    }
    return k + 1;
}
int getfr(int a) {
    int l = 1, r = cnt;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (ts[mid] < a)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
signed main() {
    cin >> n >> q;
    int lpos, rpos;
    lpos = rpos = 0;
    for (int i = 1; i <= 2 * n; i++) {
        char x;
        cin >> x;
        if (x == 'L') {
            a[++lpos].l = i;
        } else {
            a[++rpos].r = i;
            a[rpos].zy = lpos;
        }
    }
    for (int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        if (x == '1')
            ts[++cnt] = i;
    }
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i].zy;
    }
    for (int j = 1; j <= 18; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int _1, _2;
        cin >> _1 >> _2;
        int aa = dis(_1, _2);
        cout << aa << " ";
        int fr = getfr(_1), tp = 0;
        for (fr; ts[fr] <= _2 && fr <= cnt; fr++) {
            if (dis(_1, ts[fr]) + dis(ts[fr], _2) == aa)
                tp++;
        }
        cout << tp << "\n";
    }
    return 0;
}
```

## All Inputs

接下来要考虑的就是优化第二问的处理。

显然（但其实我没想到），原来慢是在于大量特殊拖拉机都被遍历了，所以我们要分区块完成。

假设从起点 $i$ 出发，可以通过 $L$ 步到达一些特殊拖拉机。

那显然，在这些特殊拖拉机 $k$ 中所有满足

$$
L + dis(k,j) = dis(i,j)
$$

即从 $k$ 出发，走 $dis(i,j) - L$ 步可以到达大于等于 $j$ 的拖拉机。

我们可以维护 $fs_{i,j}$ 表示区间

$$
[1,i],[1,i+1],···,[1,i+2^j]
$$

的特殊拖拉机个数和。

$gs_{i,j}$ 表示区间

$$
[1,j],[1,i-1],···,[1,i-2^j]
$$

的特殊拖拉机个数和。

此外多处理一个 $g$，定义与 $f$ 类似，只是反过来了。

则 $ans = \sum_{j=1}^{18}fs_{x,j}-gs_{x,j}$

然后就没了。

时间复杂度：预处理 $O(N\log N)$，查询 $O(Q\log N)$

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q;
struct qj
{
    int l, r, zy;

    int fzy;

    qj(int l = 0, int r = 0, int zy = 0,int fzy=0) : l(l), r(r), zy(zy),fzy(fzy) {}
} a[200005];
int ts[200005],fts[200005], cnt,f[200005][20];

int g[200005][20],fs[200005][20],gs[200005][20],sum[200005];

int dis(int a,int b)
{
    if(a > b)return -0x3f3f3f3f;
    if(a==b)return 0;
    int k = 0,pos = a;
    for(int i=18;i>=0;i--)
    {
        if(f[pos][i] < b)
        {
            pos = f[pos][i];
            k += (1<<i);
        }
    }
    return k+1;
}
int getfr(int a)
{
    int l = 1,r=cnt;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if(ts[mid] < a)l = mid+1;
        else r = mid;
    }
    return l;
}
signed main()
{
    cin >> n >> q;
    int lpos, rpos;
    lpos = rpos = 0;
    for (int i = 1; i <= 2 * n; i++)
    {
        char x;
        cin >> x;
        if (x == 'L')
        {
            a[++lpos].l = i;
        }
        else
        {
            a[++rpos].r = i;
            a[rpos].zy = lpos;
            if(a[lpos].fzy == 0)a[lpos].fzy = rpos;
        }
    }
    a[1].fzy = 1;sum[0] = 0;
    for(int i=n;i>1;i--)if(a[i-1].fzy == 0)a[i-1].fzy = a[i].fzy;
    
    for (int i = 1; i <= n; i++)
    {
        char x;
        cin >> x;
        if (x == '1')
            ts[++cnt] = i,fts[i]=1;
        sum[i] = sum[i-1] + fts[i];
    }
    for(int i=1;i<=n;i++)
    {
        f[i][0] = a[i].zy;
        
        g[i][0] = a[i].fzy;
        fs[i][0] = sum[a[i].zy];
        gs[i][0] = sum[a[i].fzy-1];
    }
    for(int j=1;j<=18;j++)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][j] = f[f[i][j-1]][j-1];

            fs[i][j] = fs[i][j-1] + fs[f[i][j-1]][j-1];
        }
    }
    for(int j=1;j<=18;j++)
    {
        for(int i=n;i>=1;i--)
        {
            g[i][j] = g[g[i][j-1]][j-1];
            gs[i][j] = gs[i][j-1] + gs[g[i][j-1]][j-1];
        }
    }

    while(q--)
    {
        int _1,_2;
        cin>>_1>>_2;
        int aa = dis(_1,_2),tp=fts[_1] + fts[_2];
        cout<<aa<<" ";
        // int fr = getfr(_1),tp=0;
        // for(fr;ts[fr]<=_2 && fr <= cnt;fr++)
        // {
        //     if(dis(_1,ts[fr]) + dis(ts[fr],_2) == aa)tp++;
        // }
        for (int i=18;i>=0;--i)
            if ((aa-1)&(1<<i)) tp+=fs[_1][i],_1=f[_1][i];
        for (int i=18;i>=0;--i)
            if ((aa-1)&(1<<i)) tp-=gs[_2][i],_2=g[_2][i];
        cout<<tp<<"\n";
    }
    return 0;
}
```

---

## 作者：luoguhandongheng (赞：3)

(2024NOV12th,Beg myself to think)

做不出来啊......

接下来的分析中，请你注意左端点 $l_1<l_2<\dots<l_N$ 和右端点 $r_1<r_2<\dots<r_N$。

### 第一问

首先可以发现，为使路径最短，一次跳跃中，我们一定能跳多远就跳多远。形式化地说，对于每个拖拉机 $i$，在与它相邻的拖拉机中一定有一个编号最大的 $f_i$，加入目的地为 $j$，在 $f_i < j$ 时我们一定选择从 $i$ 跳到 $f_i$。

考虑倍增地跳，记 $r_{i,j}$ 表示从 $i$ 向右跳 $2^j$ 步最远能跳到编号为 $r_{i,j}$ 的拖拉机上。有 $r_{i,0} \gets f_i$，$r_{i,j} \gets r_{r_{i,j-1},j-1}$。

这样我们就用 $O((N+Q)\log N)$ 的复杂度解决了第一问。

贴个代码好理解一点：

```cpp
void init(){//预处理
    for(int i=n;i>=1;--i){
        for(int j=1;(r[i][j]=r[r[i][j-1]][j-1]);++j);
    }
}
void query(int a,int b){
    int step=0;
    for(int j=D;j>=0;--j){
        if(r[a][j] && r[a][j]<b){//这里注意是小于
            step+=(1<<j);
            a=r[a][j];
        }   
    }
    step++;//这里要加一
    qw(step);putchar(' ');
	//第二问......
}
int main(){
    read(n,q);
    queue <pii> st;
    int cnt=0;
    for(int i=1;i<=2*n;++i){//处理输入，求每个拖拉机的左右端点
        char x;
        while((x=getchar())!='L' && x!='R');
        if(x=='R'){
            rge[st.front()[0]]={st.front()[1],i};
            st.pop();
        }
        else{
            st.push({++cnt,i});
        }
    }
    memset(minx,0x3f,sizeof(minx));
    for(int i=1;i<=n;++i){
        chmax(maxx[rge[i][0]],i);
        chmin(minx[rge[i][1]],i);
    }
    for(int i=1;i<=2*n;++i){
        chmax(maxx[i],maxx[i-1]);
        chmin(minx[2*n-i+1],minx[2*n-i+2]);
    }
    for(int i=1;i<=n;++i){
        char x;
        while((x=getchar())!='0' && x!='1');
        r[i][0]=(maxx[rge[i][1]] > i ? maxx[rge[i][1]] : 0); //求f_i
    }
    init();
    D=ceil(log2(n));
    while (q--){
        int u,v;
        read(u,v);
        query(u,v);
    }
    return 0;
}
```

### 第二问

什么样的拖拉机会在 $a\to b$ 的最短路径上呢？记 $dis(x,y)$ 表示 $x$ 到 $y$ 的最短跳跃次数。如果 $dis(a,x) + dis(x,b) =dis(a,b)$，那么 $x$ 就在 $a\to b$ 的最短路径上。

由于我们已经求出 $L=dis(a,b)$，如果令 $dis(a,x)=i$，那么 $dis(x,b)=L-i$。这实际上要求让 $a$ 向右跳 $i$ 步能到 $x$，让 $b$ 向左跳 $L-i$ 步也能到 $x$。记 $r'_{i,j}$ 表示 $i$ 向右跳 $j$ 步最远跳到哪里，$l'_{i,j}$ 表示 $i$ 向左跳 $j$ 步最远跳到哪里。下图中左端点为 $a$，右端点为 $b$，红点为 $r'_{a,i}$，蓝点为 $l'_{b,L-i}$。由于向右跳最远的点实际上就是编号最大的点，向左跳最远的点实际上就是编号最小的点。可以发现编号区间 $[l'_{b,L-i},r'_{a,i}]$ 内的点都一定可以 $i$ 步之内跳到 $a$，$L-i$ 步之内跳到 $b$。且这一区间不为空，因为 $r'_{a,i}$ 再跳 $L-i$ 步一定可以到 $b$。所以这一区间的点都在 $a\to b$ 的最短路径上。对关键点个数前缀和，那么这一区间内关键点的个数就是 $sum_{r'_{a,i}}-sum_{l'_{b,L-i}-1}$。

​![](https://cdn.luogu.com.cn/upload/image_hosting/6o019gfj.png)​

同时可以发现 $[l'_{b,L-i},r'_{a,i}]$ 与 $[l'_{b,L-i\pm 1},r'_{a,i \mp 1}]$ 之间没有交集。那么第二问的答案 $F(a,b)$ 就可以大胆求和一下。

$$
F(a,b)=\sum_{i=1}^{L-1} sum_{r'_{a,i}}-sum_{l'_{b,L-i}-1}
=\sum_{i=1}^{L-1} sum_{r'_{a,i}} - \sum_{i=1}^{L-1}sum_{l'_{b,L-i}-1} = \sum_{i=1}^{L-1} sum_{r'_{a,i}} - \sum_{i=1}^{L-1}sum_{l'_{b,i}-1}
$$

我们上面的分析都是一步一步跳的，实际上也可以像第一问一样倍增地跳。

首先像上面一样维护一下 $l_{i,j}$ 表示 $i$ 向左跳 $2^j$ 步最远跳到哪里。同时发现还要维护 $\sum\limits_{i=1}^{L-1}sum_{l'_{b,i}-1}$ 和 $\sum\limits_{i=1}^{L-1} sum_{r'_{a,i}}$。记 $cntl_{i,j}= \sum\limits_{x\in S_{i,j}}sum_{x-1}$ , $cntr_{i,j}= \sum\limits_{x\in T_{i,j}}sum_{x}$。其中 $S_{i,j} = \{l_{i,0},l_{l_{i,0},0} , \dots \}$ 共有 $2^j$ 个（实际上就是跳 $2^j$ 步的所有途径点），$T_{i,j}$ 同理。预处理的时候也维护这个即可。有：

 $cntl_{i,0} \gets sum_{l_{i,0}-1}$，$cntr_{i,0} \gets sum_{r_{i,0}}$，

$cntl_{i,j} \gets cntl_{i,j-1}+cntl_{l_{i,j-1},j-1}$，$cntr_{i,j} \gets cntr_{i,j-1}+cntr_{r_{i,j-1},j-1}$。

这样倍增跳的的时候顺便求出 $\sum\limits_{i=1}^{L-1}sum_{l'_{b,i}-1}$ 和 $\sum\limits_{i=1}^{L-1} sum_{r'_{a,i}}$ 就可以求出第二问了。

注意以上的分析没有考虑 $a$ 和 $b$ 本身是否为特殊点，这个要特判一下。

预处理复杂度 $O(N \log N)$，每次询问复杂度 $O(\log N)$，总时间复杂度 $O((N+Q) \log N)$，可以通过本题。

贴个代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;!isdigit(c);c=getchar())if(c=='-')f=1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts void read(T& x,_T&... y){read(x),read(y...);}
Tp void qw(T x){
	if(x<0)x=-x,putchar('-');
	if(x/10)qw(x/10);
	putchar(x%10+48); 
}
typedef long long ll;
typedef array<int,2> pii;
const int N=2e5+5;
int l[N][20],r[N][20],n,q,maxx[N*2],minx[N*2],sum[N],cntl[N][20],cntr[N][20];
pii rge[N];
void chmax(int &a,int b){
    a=max(a,b);
}
void chmin(int &a,int b){
    a=min(a,b);
}
void init(){//预处理
    for(int i=1;i<=n;++i){
        for(int j=1;(l[i][j]=l[l[i][j-1]][j-1]);++j){
            cntl[i][j]=cntl[i][j-1]+cntl[l[i][j-1]][j-1];
        }
    }
    for(int i=n;i>=1;--i){
        for(int j=1;(r[i][j]=r[r[i][j-1]][j-1]);++j){
            cntr[i][j]=cntr[i][j-1]+cntr[r[i][j-1]][j-1];
        }
    }
}
int D;
void query(int a,int b){
    int step=0,ans=sum[a]-sum[a-1]+sum[b]-sum[b-1]/*加上a b*/,oria=a,orib=b;
    for(int j=D;j>=0;--j){
        if(r[a][j] && r[a][j]<b){
            step+=(1<<j);
            a=r[a][j];
        }   
    }
    step++;
    qw(step);putchar(' ');
    a=oria,b=orib;
    int d=ceil(log2(step));
    for(int j=d;j>=0;--j){
        if((1<<j)<=step-1){//注意求的是 \sum(1~L-1)，因此到 step-1 即可。
            step-=(1<<j);
            ans+=cntr[a][j]-cntl[b][j];
            a=r[a][j],b=l[b][j];//这里也得跟着跳
        }
    }
    qw(ans);putchar('\n');
}
int main(){
    read(n,q);
    queue <pii> st;
    int cnt=0;
    for(int i=1;i<=2*n;++i){
        char x;
        while((x=getchar())!='L' && x!='R');
        if(x=='R'){
            rge[st.front()[0]]={st.front()[1],i};
            st.pop();
        }
        else{
            st.push({++cnt,i});
        }
    }
    memset(minx,0x3f,sizeof(minx));
    for(int i=1;i<=n;++i){
        chmax(maxx[rge[i][0]],i);
        chmin(minx[rge[i][1]],i);
    }
    for(int i=1;i<=2*n;++i){
        chmax(maxx[i],maxx[i-1]);
        chmin(minx[2*n-i+1],minx[2*n-i+2]);
    }
    for(int i=1;i<=n;++i){
        char x;
        while((x=getchar())!='0' && x!='1');
        sum[i]=sum[i-1]+x-'0';
        r[i][0]=(maxx[rge[i][1]] > i ? maxx[rge[i][1]] : 0);
        l[i][0]=((minx[rge[i][0]]==minx[0] || minx[rge[i][0]]>=i) ? 0 : minx[rge[i][0]]);
        cntl[i][0]=sum[l[i][0]-1];
    }
    for(int i=1;i<=n;++i){
        cntr[i][0]=sum[r[i][0]];
    }
    init();
    D=ceil(log2(n));
    while (q--){
        int u,v;
        read(u,v);
        query(u,v);
    }
    return 0;
}

```

---

## 作者：Purslane (赞：2)

# Solution

显然可以建图，跑全源最短路。但是这么做显然十分搞笑，因为你没有用到“连续线段”的性质。

首先考虑一个最基本的贪心：不妨设 $a \le b$，那么 $a \to b$ 的最短路上不会有编号小于 $a$ 的节点，即经过的点的编号是单调递增的。

同时，如果 $a$ 能用 $k$ 步走到 $b$，则 $\forall a \le i \le b$，都可以从 $a$ 用不超过 $k$ 步走到 $i$。

所以你可以直接倍增求出最短路的长度。

第二问即统计有多少个特殊点满足 $a \le u \le b$，且 $\text{dis}(a,u) + \text{dis}(u,b) = \text{dis}(a,b)$。

接下来需要一点观察。

固定 $(\text{dis}(a,u),\text{dis}(u,b))$ 的 $u$ 是一段区间。显然这样的区间互不重叠。

设 $\text{dis}(a,b) = k$，则 $(\text{dis}(a,u),\text{dis}(u,b))=(x,k-x)$ 的点**一定存在**。

因此我们只需要在倍增的过程中记录使得 $\text{dis}(a,u) \le 2^k$ 的 $u$ 的右端点前缀和值之和，以及 $\text{dis}(u+1,b) \le 2^k$ 的 $u$ 的左端点之和。

时空复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,q,pre[MAXN],nxt[MAXN][21],lst[MAXN][21],suml[MAXN][21],sumr[MAXN][21];
int l[MAXN],r[MAXN],t1,t2;
string S;
pair<int,int> query(int l,int r) {
	if(l==r) return {0,pre[l]-pre[l-1]};
	int ans1=1,ans2=0;
	int u=l,oll=l,orr=r;
	roff(i,19,0) if(nxt[u][i]<r) ans1+=(1<<i),ans2+=suml[u][i],u=nxt[u][i];
	roff(i,19,0) if(lst[r][i]>l) ans2-=sumr[r][i],r=lst[r][i];
	return {ans1,ans2+pre[oll]-pre[oll-1]+pre[orr]-pre[orr-1]};
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q>>S,S="&"+S;
	ffor(i,1,n+n) {
		if(S[i]=='L') l[++t1]=i;
		else r[++t2]=i;	
	}	
	cin>>S,S="&"+S;
	ffor(i,1,n) pre[i]=pre[i-1]+S[i]-'0';
	ffor(i,0,19) nxt[n][i]=n,lst[1][i]=1;
	roff(i,n-1,1) {
		nxt[i][0]=nxt[i+1][0];
		while(r[i]<l[nxt[i][0]]) nxt[i][0]--;
		suml[i][0]=pre[nxt[i][0]];
		ffor(j,1,19) nxt[i][j]=nxt[nxt[i][j-1]][j-1],suml[i][j]=suml[i][j-1]+suml[nxt[i][j-1]][j-1];
	}
	ffor(i,1,n) {
		lst[i][0]=lst[i-1][0];
		while(l[i]>r[lst[i][0]]) lst[i][0]++;
		sumr[i][0]=pre[lst[i][0]-1];
		ffor(j,1,19) lst[i][j]=lst[lst[i][j-1]][j-1],sumr[i][j]=sumr[i][j-1]+sumr[lst[i][j-1]][j-1];
	}
	ffor(i,1,q) {
		int u,d;
		cin>>u>>d;
		if(u>d) swap(u,d);
		auto pr=query(u,d);
		cout<<pr.first<<' '<<pr.second<<'\n';	
	}
	return 0;
}
```

---

## 作者：Thunder_S (赞：2)

## Solution

首先有一个显然的结论，区间 $i$ 向右能到的区间是 $[i+1,RT_i]$，向左能到的区间是 $[LT_i,i-1]$。



根据这个考虑倍增。定义跳一步表示从当前区间去到最远能去的区间。设 $f_{i,j}$ 表示区间 $i$ 向右跳 $j$ 步，最远到哪个区间，$g_{i,j}$ 表示向左跳。

那么现在只需求出 $f_{i,0}$ 和 $g_{i,0}$ 就可以进行倍增。

设 $l_i$ 表示第 $i$ 个 `L` 向左最远到哪个区间，$r_i$ 表示第 $i$ 个 `R` 向右最远到哪个区间。对于 $l_i$ 来说，只需要求出往右数，最靠近 $i$ 的 `R` 是第几个 `R`，因为 `R` 越早出现表示对应的 `L` 也越早出现。这个值就是 $l_i$，$r_i$ 就反过来计算，原理是一样的。

那么 $f_{i,0}=r_i,g_{i,0}=l_i$。

然后第一问就很好做了，就倍增往后跳就行了。

第二问设 $cnt(l,r)$ 表示从 $l$ 区间到 $r$ 区间有多少特殊区间。不妨设第一问答案是 $dis$。

那么第二问答案 $ans=cnt(x,x)+cnt(y,y)+\sum\limits_{i=1}^{dis-1} cnt(g_{y,dis-i},f_{x,i})$。后面那一部分可以合并成几个倍增。所以在倍增中统计前缀和的和？

## Code
```cpp
#include<cstdio>
#include<cstring>
#define N 200005
using namespace std;
int n,q,now,cnt,ans1,ans2,l[N],r[N],sum[N],f[N<<1][18],g[N<<1][18],fs[N<<1][18],gs[N<<1][18];
char s[N<<1],vs[N];
int dis(int x,int y)
{
    if (x==y) return 0;
    int res=0;
    for (int i=17;i>=0;--i)
        if (f[x][i]!=-1&&f[x][i]<y) res+=(1<<i),x=f[x][i];
    return res+1;
}
int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    cnt=0;now=1;
    for (int i=1;i<=2*n;++i)
    {
        if (s[i]=='L') cnt++;
        else r[now]=cnt,now++;
    }
    cnt=n+1;now=n;
    for (int i=2*n;i;--i)
    {
        if (s[i]=='R') cnt--;
        else l[now]=cnt,now--;
    }
    scanf("%s",vs+1);
    for (int i=1;i<=n;++i)
        sum[i]=sum[i-1]+vs[i]-'0';
    memset(f,-1,sizeof(f));
    memset(g,-1,sizeof(g));
    for (int i=1;i<n;++i)
        f[i][0]=r[i],fs[i][0]=sum[r[i]];
    for (int i=n;i>1;--i)
        g[i][0]=l[i],gs[i][0]=sum[l[i]-1];
    for (int j=1;j<=17;++j)
        for (int i=1;i<n;++i)
        {
            if (f[i][j-1]==-1) continue;
            f[i][j]=f[f[i][j-1]][j-1];
            if (f[i][j]!=-1) fs[i][j]=fs[i][j-1]+fs[f[i][j-1]][j-1];
        }
    for (int j=1;j<=17;++j)
        for (int i=n;i>1;--i)
        {
            if (g[i][j-1]==-1) continue;
            g[i][j]=g[g[i][j-1]][j-1];
            if (g[i][j]!=-1) gs[i][j]=gs[i][j-1]+gs[g[i][j-1]][j-1];
        }
    while (q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ans1=dis(x,y);ans2=vs[x]-'0'+vs[y]-'0';
        for (int i=17;i>=0;--i)
            if ((ans1-1)&(1<<i)) ans2+=fs[x][i],x=f[x][i];
        for (int i=17;i>=0;--i)
            if ((ans1-1)&(1<<i)) ans2-=gs[y][i],y=g[y][i];
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
```

---

## 作者：小木虫 (赞：1)

### Preface
比较好的倍增练习题吧。  
### Problem  
农民约翰有 $N
(2 \le N \le 2 \cdot 10^5)$ 台拖拉机，其中第 $i$ 台拖拉机只能在序列 $[l_i,r_i]$ 内使用。拖拉机有左端点 $l_1<l_2<\cdots <l_N$ 和右端点 $r_1<r_2< \cdots <r_N$. 有一些拖拉机是特别的。

如果 $[l_i,r_i]$ 和 $[l_j,r_j]$ 相交，则两台拖拉机 $i$ 和 $j$ 是相邻的。 约翰可以从一辆拖拉机转移到任何相邻的拖拉机上。两台拖拉机 $a$ 和 $b$ 之间的路径由一个传输序列组成，这样序列中的第一个拖拉机是 $a$，序列中的最后一个拖拉机是 $b$，并且序列中的每两个连续的拖拉机相邻。 保证拖拉机 $1$ 和 拖拉机 $N$ 之间有一条路径。路径的长度是转移的数量（或等价地，其中拖拉机的数量减去 $1$）。

给定 $Q (1 \le Q \le 2 \cdot 10^5)$ 组询问，每次给定 $a$ 和 $b (1 \le a<b \le N)$。 对于每组询问，你需要回答两个问题：

 - $a$ 到 $b$ 的最短路径。
 - 在保证传送次数的最少的情况下，有多少个特殊拖拉机的区间可能被某条最短路经过。
### Solution  
我们先考虑第一问怎么做，题目给了区间的一个严格递增的限制（即右端点更大的区间左端点同样更大），所以我们可以从给定的左端点尽可能往右跳，越远越好直到抵达终点，这部分暴力做的话是 $O(nq)$ 的，可以使用稀疏表做到 $O(q\log n)$。  

然后让我们考虑第二问怎么做，朴素地，一个特殊点 $x$ 能被包含在一个询问 $(a,b)$ 里当且仅当：  
$$dis(a,b)=dis(a,x)+dis(x,b)$$  
$dis(x,y)$ 为从区间 $x$ 到 $y$ 的最低步数。  
那么如果我们的特殊点个数为 $k$，我们这样暴力检查的复杂度为 $O(qk\log n)$，可以通过前七个测试点。  

你重新观察这个求最短路的方式，你发现对于第 $i$ 步，满足条件（即第 $i$ 步踩在这个点上且依然在最短路上的点）的点都在一个区间 $[l,r]$ 内，这点由于单调性是显然的，接下来的问题是如何去求解这个区间。  
根据上面那个定义，我们实际上是可以直接通过倍增求出一个步的左右区间的，区间内的统计可以直接开前缀和，但由于步数是 $O(n)$ 的，我们现在也只能做到 $O(nq)$。  

所以我们把区间的贡献的前缀和拆开分别计算，即将 $sum_r-sum_{l-1}$ 的前后项分别计算，绑在各自方向的倍增上，随着倍增增加贡献，那么我们就做完了，复杂度 $O(q\log n)$。  


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,q,a,b,l[N],r[N],sum[N];
string s,t; 
int nxt[N][21],nval[N][21],pre[N][21],pval[N][21];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>q>>s>>t;s=" "+s;t=" "+t;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+(t[i]-'0');
	queue <int> Q;int cnt=0;
	for(int i=1;i<=2*n;i++){
		if(s[i]=='L'){
			Q.push(++cnt);
			l[cnt]=i;
		}else{
			r[Q.front()]=i;
			Q.pop();
		}
	}
	for(int i=n;i>=1;i--){
		if(i==n){
			for(int j=0;j<=20;j++)
				nxt[i][j]=nxt[i+1][j]=n+1;
		}
		else nxt[i][0]=upper_bound(l+1,l+1+n,r[i])-l-1;
		nval[i][0]=sum[i];
		for(int j=1;j<=20;j++){
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			nval[i][j]=nval[i][j-1]+nval[nxt[i][j-1]][j-1];
		} 
	}
	for(int i=1;i<=n;i++){
		if(i==1)pre[i][0]=0;
		else pre[i][0]=lower_bound(r+1,r+1+n,l[i])-r;
		pval[i][0]=sum[i-1];
		for(int j=1;j<=20;j++){
			pre[i][j]=pre[pre[i][j-1]][j-1];
			pval[i][j]=pval[i][j-1]+pval[pre[i][j-1]][j-1];
		} 
	}
	//for(int i=1;i<=n;i++)
	//	cout<<l[i]<<" "<<r[i]<<" "<<sum[i]-sum[i-1]<<"\n";
	while(q--){
		cin>>a>>b;
		int cnt=t[a]-'0'+t[b]-'0';
		int now=nxt[a][0];
		int len=2;
		if(now<b){
			for(int i=20;i>=0;i--){
				if(nxt[now][i]<b){
					len+=(1<<i);
					cnt+=nval[now][i];
					now=nxt[now][i];
				}
			}
			len++;cnt+=nval[now][0];
		}
		now=pre[b][0];
		if(now>a){
			for(int i=20;i>=0;i--){
				if(pre[now][i]>a){
					cnt-=pval[now][i];
					now=pre[now][i];
				}
			}
			cnt-=pval[now][0];
		}
		cout<<len-1<<" "<<cnt<<"\n";
	}
	return 0;
}

```

---

## 作者：yllcm (赞：1)

介绍一种无语做法。

首先可以观察到，对于节点 $x$，$x$ 能通过 $k$ 步向右到达的所有区间构成一个区间，假设为 $[l_{0,x,k},r_{0,x,k}]$，同理，$x$ 向左走 $k$ 步到达的所有区间也是区间，设为 $[l_{1,x,k},r_{1,x,k}]$。

所以一组询问 $x,y$ 实际上让我们求 $\sum|[l_{0,x,k},r_{0,x,k}]\cap[l_{1,y,d-k},r_{1,y,d-k}]|$。其中 $d$ 为 $x,y$ 间最短路。

假设你并不知道上面的区间交实际上就是 $\sum (r_{0,x,k}-l_{1,y,d-k})$ 从而可以把两个式子拆开直接算，而是直接硬着头皮算区间贡献，应该怎么做？

此时注意到如果我们将 $i$ 向右走一步能到达的最右侧的节点与 $i$ 连边，那么得到的图形如一棵树 $T_0$，并且可以发现，$i$ 在树上的 $k$ 级祖先恰好是 $r_{0,x,k}$ 的值。同理，将 $i$ 向左走一步能到达的最左侧的节点与 $i$ 连边得到树 $T_1$，$i$ 在树 $T_1$ 上的 $k$ 即祖先恰好是 $l_{1,x,k}$ 的值。

但是要求区间交仍然困难重重，使用 polylog 做法很难得到优秀的结果。转而考虑莫队维护树上祖先链信息，莫队的方法是：将所有点按照欧拉序排成一个序列，每次移动结点时，找到当前节点在欧拉序上的后继，如果是它的父亲则删掉它，否则加入一个新的节点。莫队的同时维护贡献并同时维护 $x$ 在 $T_0$ 上的编号在 $[x,y]$ 之间的一条祖先链，$y$ 在 $T_1$ 上的编号在 $[x,y]$ 之间的一条祖先链，以及上面描述的区间交的和。加入一个新节点对集合 $\{[l_{0,x,k},r_{0,x,k}]\cap[l_{1,y,d-k},r_{1,y,d-k}]\}$ 带来的影响是 $\mathcal{O}(1)$ 的，所以可以做到 $\mathcal{O}(1)$ 维护出集合信息，从而维护出和。

实现细节可以看代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 4e5 + 10;
int n, Q, B;
int id[N], sum[N];
char str[N];
struct Tree {
    vector<int> G[N];
    void add(int u, int v) {G[u].pb(v);}
    int cnt, dt, rt;
    int F[N], dep[N], pre[N], dfn[N];
    void dfs(int u) {
        dfn[u] = ++cnt; pre[cnt] = ++dt;
        for(int v : G[u]) {
            dep[v] = dep[u] + 1; F[v] = u;
            dfs(v); dt++;
        }
        return ;
    }
    int getbl(int u) {return pre[dfn[u]] / B;}
}T[2];
struct Qry {
    int id, l, r;
    Qry() {}
    Qry(int id, int l, int r):id(id), l(l), r(r) {}
    bool operator < (const Qry &tmp) const {
        if(T[0].getbl(l) != T[0].getbl(tmp.l))
            return T[0].getbl(l) < T[0].getbl(tmp.l);
        else return T[1].dfn[r] < T[1].dfn[tmp.r];
    }
}q[N];
int ans1[N], ans2[N];
int main() { 
    n = read(); Q = read(); B = sqrt(n);
    scanf("%s", str + 1);
    for(int i = 1, j = 0, k = 0; i <= (n << 1); i++)
        id[i] = (str[i] == 'L' ? ++j : ++k);
    for(int i = 1, j = 0; i < (n << 1); i++)
        (str[i] == 'L' ? j = max(j, id[i]) : (T[0].add(j, id[i]), 0));
    for(int i = (n << 1), j = (n << 1); i > 1; i--)
        (str[i] == 'R' ? j = min(j, id[i]) : (T[1].add(j, id[i]), 0));
    T[0].dfs(n); T[1].dfs(1);
    scanf("%s", str + 1);
    for(int i = 1; i <= n; i++)sum[i] = (str[i] - '0');
    for(int i = 1; i <= n; i++)sum[i] += sum[i - 1];
    for(int i = 1; i <= Q; i++) {
        int l = read(), r = read();
        q[i] = Qry(i, l, r);
    }
    sort(q + 1, q + 1 + Q);
    int x = n, y = 1, val = 0;
    deque<int> p[2]; p[0].push_back(x); p[1].push_back(y);
    auto add = [&](int z, int o) {
        if((o == 0 && z >= y) || (o == 1 && z <= x))
            p[o].pop_back(), p[o].push_back(z);
        else {
            if((o == 0 && p[!o].front() == y) || (o == 1 && p[!o].front() == x));
            else {
                int l = p[!o].front(), r = p[o].back();
                if(l > r)swap(l, r); val += sum[r] - sum[l - 1];
            }
            p[o].push_back(z); p[!o].push_front(T[!o].F[p[!o].front()]);
        }
        return ;
    };
    auto del = [&](int o) {
        if((o == 0 && p[o].back() >= y) || (o == 1 && p[o].back() <= x))
            p[o].push_front(T[o].F[p[o].back()]), p[o].pop_back();
        else {
            p[o].pop_back(); p[!o].pop_front();
            if((o == 0 && p[!o].front() == y) || (o == 1 && p[!o].front() == x));
            else {
                int l = p[!o].front(), r = p[o].back();
                if(l > r)swap(l, r); val -= sum[r] - sum[l - 1];
            }
        }
        return ;
    };
    auto move = [&](int &x, int y, int o) {
        vector<int> st; int z = y;
        while(x != y) {
            if(T[o].dep[x] > T[o].dep[y])
                del(o), x = T[o].F[x];
            else st.pb(y), y = T[o].F[y];
        }
        reverse(st.begin(), st.end());
        for(int t : st)add(t, o);
        x = z;
        return ;
    };
    for(int i = 1; i <= Q; i++) {
        move(x, q[i].l, 0); move(y, q[i].r, 1);
        ans1[q[i].id] = (int)p[0].size() - 1; 
        ans2[q[i].id] = val + (str[x] - '0') + (str[y] - '0');
    }
    for(int i = 1; i <= Q; i++)printf("%d %d\n", ans1[i], ans2[i]);
    return 0;
}
```

~~是不是可以出个新题~~

---

## 作者：NaN_HQJ2007_NaN (赞：0)

显然，对于给定的 $l,r$，最短路可以贪心求出，即每次走与当前区间相交且左端点最大的区间，这个可以用倍增加速。

定义 $f_{i,j}$ 表示从区间 $i$ 往右走 $j$ 步后到达的区间，$g_{i,j}$ 表示往左走的情况。

正反遍历一下即可求出 $f_{i,1}$ 和 $g_{i,1}$。

对于第二问，第 $i$ 步所能走到的区间会有一个范围，且对于每个 $i$ 其范围不相交。

定义 $s(i,j)$ 表示编号在 $[i,j]$ 范围内的特殊区间个数。

那么最终答案为 $s(x,x)+s(y,y)+\sum\limits_{i=1}^{dis-1}s(g_{y,dis-i},f_{x,i})$。

求倍增和的前缀和即可。复杂度 $O(n\log n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,f[N][21],g[N][21],fs[N][21],gs[N][21],id[N*2],sum[N];
char c[N*2];
string s;
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>q;
  int t=0,t2=0;
  for(int i=1;i<=2*n;++i){
    cin>>c[i];
    if(c[i]=='L')id[i]=++t;
    else id[i]=++t2;
  }
  cin>>s;s="."+s;
  for(int i=1;i<=n;++i)sum[i]=sum[i-1]+s[i]-'0';
  for(int i=2*n;i>=1;--i){
    if(c[i]=='L'){
      g[id[i]][0]=id[t];
      gs[id[i]][0]=sum[id[t]-1];
    }else t=i;
  }
  for(int i=1;i<=2*n;++i){
    if(c[i]=='R'){
      f[id[i]][0]=id[t];
      fs[id[i]][0]=sum[id[t]];
    }else t=i;
  }
  for(int j=1;j<=20;++j)for(int i=1;i<=n;++i){
    f[i][j]=f[f[i][j-1]][j-1];fs[i][j]=fs[i][j-1]+fs[f[i][j-1]][j-1];
    g[i][j]=g[g[i][j-1]][j-1];gs[i][j]=gs[i][j-1]+gs[g[i][j-1]][j-1];
  }
  while(q--){
    int x,y,d1=0,d2;cin>>x>>y;
    d2=s[x]-'0'+s[y]-'0';
    int u=x,v;
    for(int i=20;i>=0;--i){
      if(f[u][i]<y){
        d1+=(1<<i);
        u=f[u][i];
      }
    }
    ++d1;
    cout<<d1<<" ";
    u=x;v=y;
    for(int i=0;i<=20;++i){
      if((d1-1)&(1<<i)){
        d2+=fs[u][i]-gs[v][i];
        u=f[u][i];v=g[v][i];
      }
    }
    cout<<d2<<endl;
  }
  return 0;
}

```


---

