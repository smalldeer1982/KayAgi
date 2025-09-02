# BOXES - Boxes

## 题目描述

### 题目大意
$n$ 个盒子围成一圈（$1\le n\le 1000$）。 第 $i$ 个盒子初始时有 $a_i$ 个小球，小球数量总和满足 $\displaystyle\sum_{i=1}^{n}{a_i \leq n}$。  
每次可以把一个小球从一个盒子移到相邻的两个盒子之一。求最少需要移动多少次，使得每个盒子中小球的个数不超过 $1$。

## 样例 #1

### 输入

```
1
12
0 0 2 4 3 1 0 0 0 0 0 1```

### 输出

```
19```

# 题解

## 作者：喵仔牛奶 (赞：3)

## $\mathcal{Solution}$

费用流。

下文 $\text{Add}(u,v,w,c)$ 表示建一条 $u\to v$，流量为 $w$，费用为 $c$ 的边，$S$ 表示源点，$T$ 表示汇点。

很容易想到把盒子看成点。第 $i$ 个点有 $a_i$ 个球可以用 $\text{Add}(S,i,a_i,0)$ 表示，直接汇过来 $a_i$ 个球。每个盒子向汇点连边 $\text{Add}(i,T,1,0)$，限制每个盒子只能交一个球。

因为可以把球移动到相邻点，这个显然不限次数，费用为 $1$，$\text{Add}(i,i-1,\inf,1)$，$\text{Add}(i,i+1,\inf,1)$。

## $\mathcal{Code}$

费用流，[1.17s](https://www.luogu.com.cn/record/98672659)。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
struct edge {
	LL to, next, w, c;
} e[N << 1];
LL T, n, m, sum, u, v, w, c, s, t, tot, cnt, a[N], pos1[N], dis[N], head[N];
bool vis[N];
void add(int u, int v, int w, int c) {
	e[++ cnt].to = v;
	e[cnt].w = w;
	e[cnt].c = c;
	e[cnt].next = head[u];
	head[u] = cnt;
}
void Add(int u, int v, int w, int c) {
//	cout << "Added " << u << ' ' << v << ' ' << w << ' ' << c << '\n';
	add(u, v, w, c), add(v, u, 0, -c);
}
bool SPFA() {
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	queue<int> q;
	q.push(s), vis[s] = 1, dis[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].next) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].c && e[i].w) {
				dis[v] = dis[u] + e[i].c;
				if (!vis[v]) vis[v] = 1, q.push(v);
			}
		}
	}
	return dis[t] < 0x3f3f3f3f;
}
LL dfs(int u, LL flow, LL& cost) {
	if (u == t) return flow;
	LL tmp = flow;
	vis[u] = 1;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (!vis[v] && dis[v] == dis[u] + e[i].c && e[i].w) {
			LL res = dfs(v, min(e[i].w, tmp), cost);
			cost += res * e[i].c, e[i].w -= res, e[i ^ 1].w += res, tmp -= res;
			if (!tmp) break;
		}
	}
	return flow - tmp;
}
pair<LL, LL> dinic() {
	LL res = 0, cost = 0;
	while (SPFA()) {
		LL tmp;
		while ((tmp = dfs(s, 1e9, cost)))
			memset(vis, 0, sizeof vis), res += tmp;
	}
	return make_pair(res, cost);
}
int main() {
	cin >> T;
	while (T --) {
		memset(head, 0, sizeof head);
		memset(pos1, 0, sizeof pos1);
		cin >> n, tot = 0, s = ++ tot, t = ++ tot, cnt = 1;
		for (int i = 1; i <= n; i ++) {
			cin >> a[i], pos1[i] = ++ tot;
			Add(s, pos1[i], a[i], 0), Add(pos1[i], t, 1, 0);
		}
		for (int i = 1; i <= n; i ++) {
			int L = (i - 2 + n) % n + 1, R = i % n + 1;
			Add(pos1[i], pos1[L], 1e9, 1), Add(pos1[i], pos1[R], 1e9, 1);
		}
		cout << dinic().second << '\n';
	}
	return 0;
}
```


---

## 作者：Transparent (赞：3)

提供一种比费用流更优秀的 dp 做法，但是不能通过 Hard Version。

这个做法可以解决：给定一个环和环上每个位置初始的元素个数 $a_i$，求最小的移动次数使得每个位置剩下的元素在 $[l_i,r_i]$ 中。显然本题中，对任意的 $i$ 都有 $l_i=0,r_i=1$

-----

考虑断开一条边成为链的情况，通过枚举断开的边的传递情况就可以解决环的问题。这时第一个位置只能向后传递。于是可以 dp，设 $dp_{i,j}$ 表示前 $i$ 个位置已经合法且第 $i$ 个位置往下一个位置传递了 $j$ 个时（$j$ 为负数表示从下一个位置拿到 $i$），传递次数的最小值。于是可以得出转移方程：
$$
dp_{i,j}=\min\limits_{k=j-a_i+l_i}^{j-a_i+r_i}\{dp_{i-1,k}\}+|j|
$$

显然可以单调队列做到 $\Theta(n\sum\limits_{i=1}^{n} a_i)$。

----

复杂度还不优秀，考虑优化转移的过程。令 $f_i(x)=dp_{i,x}$。
发现每次从 $dp_i$ 到 $dp_{i+1}$ 其实可以拆分成三个操作：

- 令 $f(x)=\min\limits_{i=x}^{x+a}f(i)$
- 令 $f(x)$ 沿 $x$ 轴方向左右平移 $a$ 个单位。
- 令 $f(x)=f(x)+|x|$

首先发现，在 $i=0$ 的时候，只有 $f_0(0)=0$，$f_0(x)$ 的其余地方均为 $+\infty$。这显然是下凸的。而 $|x|$ 同样是下凸的，并且对一个凸函数进行前两个操作后得到的显然还是凸函数，于是可以将问题转化为维护一个下凸包。

考虑用对顶堆实现，两个堆存放斜率的转折点，其中一个维护斜率大于 $0$ 的部分，另一个维护小于 $0$ 的部分。堆中的每个元素表示斜率在对应的 $x$ 处增减 $1$，而重复的元素则可以表示大于 $1$ 的斜率变化，同时维护一个最小值。
然后分别实现这三个操作：

第一个操作即为：在斜率为 $0$ 的位置分开，将上升段向右平移 $a$ 个单位，直接对上升段打 tag 即可，对最值无影响。

第二个操作直接对上升段和下降段一起打 tag 即可，对最值无影响。

第三个操作中，由于 $x=0$ 处函数增减性可能不同，需要分类讨论：

- $0$ 所在的位置斜率为 $0$，于是上升段的斜率和下降段的斜率都会在 $0$ 处变化 $1$，向两个堆中插入 $0$ 即可，对最值无影响。
- $0$ 所在的位置斜率小于 $0$，于是下降段中 $0$ 以前的斜率 $-1$，$0$ 以后的斜率 $+1$；变化量为 $2$，故需要插入两个 $0$ 而之前斜率从 $-1$ 变为 $0$ 的位置
（即下降段最后一个转折点）会在修改后不再属于下降段，因为现在在这个点，斜率是由 $0$ 变为 $1$，需要从下降段移除并加入上升段，显然，最值需要加上下降段末尾到 $0$ 的距离。
- $0$ 所在位置的斜率大于 $0$ 时，同理。

最后根据最低点的值，沿斜率转折点依次移到 $x$ 即可。

至此，一次 dp 的复杂度可以做到 $O(n\log_2n)$。

-----

现在还需要确定断开的那条边上的传递情况，如果枚举，就可以得到一个 $O(n\log_2n\sum\limits_{i=1}^{n}a_i)$ 的做法。但是还可以优化。

设 $F(x)$ 表示 $n$ 给 $1$ 拿 $x$ 个时，需要的最小操作次数。打表发现好像是凸函数，考虑证明。

首先，将每次移动次数拓展到实数，答案不变。感性理解是要取得最值时，一定有至少一个位置恰为 $l_i$ 或 $r_i$，否则不传递这些小数部分不会更劣。当然，费用流做法也可以证明这个结论，因为把费用流做法拓展到实数显然结果不变。

然后假设有两个合法方案 $(a_1,a_2,\dotsb,a_n)$ 和 $(b_1,b_2,\dotsb,b_n)$，其中第 $i$ 个数表示第 $i$ 个位置向下一个位置传递的次数。此时将两个方案的每个位置求平均值，得到新的方案 $(c_i)$ 使得 $c_i=\frac{a_i+b_i}{2}$。由于前两个方案都合法，所以它们都能使得每个位置的值在 $[l_i,r_i]$ 内，于是它们求平均值后显然也都能落在区间内。因为有 $|c_i| \le |\frac{a_i+b_i}{2}|\le |\frac{a_i}{2}|+|\frac{b_i}{2}|$，所以 $\sum\limits_{i=1}^{n}|c_i| \le \sum\limits_{i=1}^{n}|\frac{a_i}{2}|+|\frac{b_i}{2}|$，令 $F(A)=\sum\limits_{i=1}^{n}|a_i|$，$F(B),F(C)$ 同理。根据定义得到 $C=\frac{A+B}{2}$，又有 $F(C) \le \frac{F(A)+F(B)}{2}$ 即 $F(\frac{A+B}{2}) \le \frac{F(A)+F(B)}{2}$ 于是 $F(x)$ 是凸函数。

于是可以在最外层套三分，最终复杂度为 $O(n\log_2n\log_2\sum\limits_{i=1}^{n}a_i)$。

```cpp
#include <ext/pb_ds/priority_queue.hpp>
#include<bits/stdc++.h>

using namespace std;

constexpr int MAXN=2e5+10;

int n,a[MAXN];

int calc(int x) {
    int tagl=0,tagr=0,val=0;
    __gnu_pbds::priority_queue<int,less<int>,__gnu_pbds::pairing_heap_tag>ql;
    __gnu_pbds::priority_queue<int,greater<int>,__gnu_pbds::pairing_heap_tag>qr;
    for(int i=1;i<=n;++i) ql.push(x),qr.push(x);

    for(int i=1;i<=n;++i) {
        tagl+=a[i]-1;tagr+=a[i];
        int lp=ql.top()+tagl,rp=qr.top()+tagr;
        if(lp<=0&&0<=rp) {
            ql.push(-tagl);qr.push(-tagr);
        } else if(lp>0) {
            val+=lp;ql.pop();ql.push(-tagl),ql.push(-tagl);qr.push(lp-tagr);
        } else {
            val-=rp;ql.push(rp-tagl);qr.pop();qr.push(-tagr);qr.push(-tagr);
        }
    }
    
    while(!ql.empty()) {
        int lp=ql.top()+tagl;ql.pop();
        if(lp<=x) break;
        val+=lp-x;
    }
    while(!qr.empty()) {
        int rp=qr.top()+tagr;qr.pop();
        if(rp>=x) break;
        val+=x-rp;
    }
    return val;
}

void solve() {
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];

    int suma=0;
    for(int i=1;i<=n;++i) suma+=a[i];

    int L=-suma,R=suma,res=0;
    while(L<=R) {
        int mid=(L+R)>>1;
        if(calc(mid)<calc(mid+1)) {
            res=mid,R=mid-1;
        } else L=mid+1;
    }

    cout<<calc(res)<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int T=0;cin>>T;
    while(T--) solve();

    cout<<flush;
    return 0;
}
```

---

## 作者：C_liar (赞：2)

## 题意简述

$n$ 个盒子围成一圈。第 $i$ 个盒子初始时有 $a_i$ 个小球，小球数量总和满足
$$\sum_{i=1}^{n}{a_i \leq n}$$
每次可以把一个小球从一个盒子移到相邻的两个盒子之一。求最少需要移动多少次，使得每个盒子中小球的个数不超过 $1$。

数据范围：$t\leq 20,n\leq1000$。

## 前言

类似于 [P4016 负载平衡问题](https://www.luogu.com.cn/problem/P4016)，但不能数学+贪心，而且数据更强。

## 题解

说一下我的思路吧。

首先，理解题意，尝试将题意抽象出一个模型。

#### 模型转化

发现初始状态下，每个盒子里有**一定量的球**，球可以在盒子之间**相互转移**，每次转移单位数量的球**费用**为 $1$，但**盒子中球的总数不变**，而且在终止状态下，**限制**每个盒子中**球的个数**不能超过 $1$，求达到终止状态，转移球花费的**最少费用**。

那如果我们将盒子抽象为结点，将球设置为流量，那问题就转化为经典的最小费用最大流问题了，关键是如何**建立费用流模型**。

#### 建立费用流模型

由于有 $n$ 个盒子，每个盒子都可以成为源点和汇点，所以新建超级源点、超级汇点，分别设为 $s,t$。

设球的总数为 $sum=\sum_{i=1}^na_i$。

那么，容易想到，初始状态的建立只需要从 $s$ 向每个盒子建一条容量为 $a_i$，费用为 $0$ 的边，表示初始状态每个盒子有 $a_i$ 个球。

```cpp
for(int i=1;i<=n;i++) e.add(s,i,0,a[i]),e.add(i,s);
```

（其中，`e` 代表边集，使用链式前向星存图，`add` 函数如下）

```cpp
void add(int u,int v,int c=0,int w=0){
	to[++t]=v,next[t]=head[u],head[u]=t,cost[t]=c,dis[t]=w;
}
```

而终止状态的建立，只需要从每个盒子向汇点建一条容量为 $1$，费用为 $0$ 的边，表示限制最终每个盒子中小球的个数不超过 $1$。

```cpp
for(int i=1;i<=n;i++) e.add(i,t,0,1),e.add(t,i);
```

由于 $sum\leq n$，所以只要限制流网络的最小割不小于 $sum$，即可使小球总量在求解最大流过程中不变。

那我们之间将**转移过程**中所有边的容量设为 $+\infty$ 或者 $n$ 或者 $sum$ 即可，表示转移过程中每次最多可以将小球全部转移到下一个盒子。

但关键在于，怎样建立转移过程中的边。

当初做这题时，走了好多弯路，这里给出我做题时的思路。

#### 朴素方法：

这也是我最初想到的方法，由于盒子有初始状态和终止状态，所以我们很自然地想到，对每个盒子拆点，拆成一个初始的点和终止的点，编号分别为 $i$ 和 $i+n$。

```cpp
for(int i=1;i<=n;i++) e.add(s,i,0,a[i]),e.add(i,s);
for(int i=1;i<=n;i++) e.add(i+n,t,0,1),e.add(t,i+n);
```

由于要从初始状态向终止状态转移，而题意中说，每次只能向相邻的盒子转移小球。

但是我们发现，如果第 $i$ 个盒子直接花费 $2$ 的费用向第 $i+2$ 个盒子转移，和第 $i$ 个盒子先花费 $1$ 的费用向第 $i+1$ 个盒子转移，再花费 $1$ 的费用向第 $i+2$ 个盒子转移，结果是相同的。

这就启发我，对于每个 $i$ 结点，向编号为 $j+n$ 的结点建立一条容量为 $a_i$，费用为 $dis(i,j)$ 的边，其中 $dis(i,j)$ 代表 $i,j$ 两个盒子在**环上**的最短距离，表示第 $i$ 个盒子可以通过移动向第 $j$ 个盒子最多转移 $a_i$ 个球。

```cpp
for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
	e.add(i,j+n,Dis(i,j),a[i]),e.add(j+n,i,-Dis(i,j));
}
```

（一点小压行，应该问题不大）

高高兴兴地写完 `Dinic`，过了样例，交上去，发现超时了。

其实只要算一下边数，就会发现，流网络中的边数达到了 $m=2n^2+4n$ 的级别（由于有反向边），`Dinic` 的复杂度是 $O(n^2m)$ 的，再加上 $t$ 组数据，总复杂度 $O(t\times n^4)$，虽然 `Dinic` 跑不满，但也直接T飞了。

这也启发了我，要对建图上做一些优化。

#### 优化 step 1：

依然拆点，但考虑优化从初始状态向终止状态转移的方式。

由于对每个结点两两之间都建一条边太浪费了，好多边都不会用到，所以直接从初始状态向相邻的盒子转移。

转移有两种方式：

1. 从 $i$ 向相邻的初始结点转移，代表小球的移动过程，还没有确定最终的落脚点。

2. 从 $i$ 向终止结点转移，代表小球选定了最终的落脚点。

对于两种转移，第一种，直接从每个结点向相邻结点建立一条容量为 $+\infty$，费用为 $1$ 的边，第二种，直接从每个结点向自己的终止结点建立一条容量为 $+\infty$，费用为 $0$ 的边，向相邻的终止结点建立一条容量为 $+\infty$，费用为 $1$ 的边即可。

（其实第二种向相邻终止结点转移时，和第一种重复了，但这就是蒟蒻当初的想法 QwQ）

这样，边的条数变成了 $m=14n$ 的级别，可以接受。

```cpp
for(int i=1;i<=n;i++) if(a[i]) e.add(s,i,0,a[i]),e.add(i,s);
for(int i=1;i<=n;i++) e.add(i+n,t,0,1),e.add(t,i+n);
for(int i=1;i<=n;i++){
	e.add(i,Next(i),1,n),e.add(Next(i),i,-1);
	e.add(i,Pref(i),1,n),e.add(Pref(i),i,-1);
	e.add(i,Next(i)+n,1,n),e.add(Next(i)+n,i,-1);
	e.add(i,Pref(i)+n,1,n),e.add(Pref(i)+n,i,-1);
	e.add(i,i+n,0,n),e.add(i+n,i);
}
```

#### 优化 step 2：

仔细想了想，其实还能再优化一点。

其实观察建图的过程，发现完全可以不用拆成两个点，直接从源结点向每个结点建边，每个结点向汇点建边，相邻结点之间建立一条容量为 $+\infty$，费用为 $1$ 的边，表示可以相互转移就可以了。

容易发现，这样也是正确的，因为这样建边并不会比之前建边少转移几个状态或者转移到了非法的状态，而且由于不用拆点，建边更少，优化到了 $m=8n$ 的级别，这样，这道题也就做完了。

注意，由于盒子是环形，所以要特殊处理边界。

## 代码

最后放上代码，由于多组数据，注意要记得清空。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
typedef long long ll;
const int _=2e3+10;
const int __=2e5+10;
const int inf=0x3f3f3f3f;
using namespace std;

int n,s,t,a[_],sum,Result;

struct Edge{ // 边集
	int to[__],next[__],head[_],cost[__],dis[__],t;
	Edge(){t=1;}
	void add(int u,int v,int c=0,int w=0){
		to[++t]=v,next[t]=head[u],head[u]=t,cost[t]=c,dis[t]=w;
	}
	void C_liar(){ // 清空，clear 函数
		memset(head,0,sizeof head);
		for(int i=1;i<=t;i++) to[i]=next[i]=cost[i]=dis[i]=0;
		t=1;sum=Result=0;
	}
}e;

int Dis(int a,int b){ // 朴素解法中的 dis(i,j) 函数
	return min(abs(b-a),abs(min(a,b)+n-max(a,b)));
}

int d[_],New[_];bool vis[_];

bool bfs(){
	memset(d,0x3f,sizeof d);
	queue<int> q;
	q.push(s),d[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=0,New[x]=e.head[x];
		for(int i=e.head[x],y;i;i=e.next[i]){
			if(!e.dis[i]) continue;
			if(d[y=e.to[i]]>d[x]+e.cost[i]){
				d[y]=d[x]+e.cost[i];
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return d[t]!=0x3f3f3f3f;
}

int Dinic(int x,int flow){
	if(x==t) return flow;
	int res=flow;vis[x]=1;
	for(int i=New[x],y;i&&res;i=e.next[i],New[x]=i){
		if(!e.dis[i]||vis[y=e.to[i]]||d[y]!=d[x]+e.cost[i]) continue;
		int k=Dinic(y,min(res,e.dis[i]));
		if(!k) d[y]=0x3f3f3f3f;
		e.dis[i]-=k,e.dis[i^1]+=k,res-=k,Result+=k*e.cost[i];
	}
	return vis[x]=0,flow-res;
}

int Next(int x){return x==n?1:x+1;}
int Pref(int x){return x==1?n:x-1;}

void work(){
	e.C_liar();
	scanf("%d",&n);
	s=n+1,t=n+2;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    // 这里建边加了个小剪枝，如果容量为 0 可以直接不建。
	for(int i=1;i<=n;i++) if(a[i]) e.add(s,i,0,a[i]),e.add(i,s);
	for(int i=1;i<=n;i++) e.add(i,t,0,1),e.add(t,i);
	for(int i=1;i<=n;i++){
		e.add(i,Next(i),1,n),e.add(Next(i),i,-1);
		e.add(i,Pref(i),1,n),e.add(Pref(i),i,-1);
	}
	while(bfs()) while(Dinic(s,n));
	printf("%d\n",Result);
}

int main(){
	int t;scanf("%d",&t);
	while(t--) work();
	return 0;
}
```

---

## 作者：bsTiat (赞：2)

题意翻译的格式炸了，我修了一下放在下面。

### 题意简述

$ n $ 个盒子围成一圈。第 $ i $ 个盒子初始时有 $ a_i $ 个小球，小球数量总和满足 $ \sum_{i=1}^{n}{a_i \leq n} $ 。每次可以把一个小球从一个盒子移到相邻的两个盒子之一。求最少需要移动多少次，使得每个盒子中小球的个数不超过 $ 1 $ 。( $ n \leq 1000 $ )

### 题目分析

首先很容易想到一个很裸的贪心：对于每个小球数量多的盒子，把多的小球移到离它最近没小球的盒子，然后发现样例都过不了，考虑一下错哪了？

把多的小球移到离它最近的盒子并不一定是最优的，可能挤占了其他更优移法的位置，让本来可以很近的移法要移很远的位置，然后我们就有一种反悔贪心的感觉，但是很难写，而费用流的本质就是反悔贪心，所以我们很自然地想到用网络流来解题。

### 费用流建模

建立超级源点与超级汇点。

首先，考虑最终状态，每个盒子中最多有一个小球，我们可以将每个盒子向汇点连边，边的流量为一，表示最终只能有一个小球。

然后，考虑起始状态，第 $ i $ 个盒子中有 $ a_i $ 个小球，我们从源点向第 $ i $ 个盒子中连流量为 $ a_i $ 的边。

接下来，考虑盒子之间小球的转移如何用边来表示，容易想到，盒子与其左右两个盒子连一条流量为正无穷的边。

最后，我们可以发现，最大流必为  $ \sum_{i=1}^{n}{a_i} $ ，最终状态与状态之间的转移都符合题意，考虑如何求最小操作数。

按照题意，把一个小球从一个盒子移到相邻的两个盒子之一为一次操作，所以我们将盒子之间的每条边的单位费用定为 $ 1 $ ，表示进行了一次操作，与源点汇点之间的边费用为零。

然后跑费用流，结束。

注意盒子是围成一个圈的。

### code

```cpp
#include<bits/stdc++.h>
# define v to[i]
using namespace std;
const int N = 2e4;
const int inf = 2e9;
inline int rd(){
	char c=getchar();int sum=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
int n,m,s,t,mincost,tot=1,T,a[N];
int flow[N],val[N],nxt[N],pre[N],to[N],head[N],cost[N],dis[N],vis[N];
inline void add(int x,int y,int z,int w){
	to[++tot]=y;val[tot]=z;cost[tot]=w;nxt[tot]=head[x];head[x]=tot;
	to[++tot]=x;val[tot]=0;cost[tot]=-w;nxt[tot]=head[y];head[y]=tot;
} 
bool spfa(){
	queue<int>q;pre[t]=0;
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;flow[s]=inf;vis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=nxt[i])
			if(val[i]&&dis[u]+cost[i]<dis[v]){
				dis[v]=dis[u]+cost[i];
				flow[v]=min(flow[u],val[i]);
				pre[v]=i;
				if(!vis[v])q.push(v),vis[v]=1;
			}
	}
	return pre[t];
}
void mcmf(){
	while(spfa()){
		int x=t,i;
		mincost+=dis[t]*flow[t];
		while(x!=s){
			i=pre[x];
			val[i]-=flow[t];
			val[i^1]+=flow[t];
			x=to[i^1];
		}
	}
}
signed main(){
	T=rd();
	while(T--){
		tot=1;mincost=0;
		memset(head,0,sizeof(head));
		n=rd();
		s=0,t=n+5;
		for(int i=1;i<=n;++i){
			m=rd();
			add(s,i,m,0);add(i,t,1,0);
			if(i!=1&&i!=n)
				add(i,i+1,inf,1),add(i,i-1,inf,1);
		}
		add(1,2,inf,1);add(1,n,inf,1);
		add(n,n-1,inf,1);add(n,1,inf,1);
		mcmf();
		cout<<mincost<<"\n";
	}
	return 0;
}

```


---

## 作者：harmis_yz (赞：0)

## 分析

板子题，考虑费用流。

对于每个格子最多有 $1$ 个球的限制，让每个点向汇点连一条容量为 $1$ 的无代价的边即可。

移动到相邻的格子，因为没有限制移动的次数，所以连一条容量无线代价为 $1$ 的边。

很显然，满流时最小的费用即为答案。跑一个费用流就行了，注意多测。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=6e6+10,inf=1e18;
int n,s,t;
int h2[N],ne[N<<1],e[N<<1],w[N<<1],w2[N<<1],h[N],idx=1;
bool vis[N],Vis[N];
int dep[N],ans,sum;
int a[N];

il void add(int a,int b,int c,int d){
	ne[++idx]=h[a],e[idx]=b,w[idx]=c,w2[idx]=d,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,w[idx]=0,w2[idx]=-d,h[b]=idx;
}

il bool bfs(){
	for(re int i=s;i<=t;++i)
		vis[i]=0,dep[i]=1e18,h2[i]=h[i];
	queue<int> qu;
	dep[s]=0,qu.push(s),vis[s]=1;
	while(!qu.empty()){
		int now=qu.front();qu.pop();
		vis[now]=0;
		for(re int i=h[now];i;i=ne[i]){
			int j=e[i];
			if(dep[j]>dep[now]+w2[i]&&w[i]){
				dep[j]=dep[now]+w2[i];
				if(!vis[j]) vis[j]=1,qu.push(j);
			}
		}
	}
	if(dep[t]<1e18) return 1;
	return 0;
}
il int dfs(int now,int Min){
	if(now==t) return ans+=Min,Min;
	int use=0;Vis[now]=1;
	for(re int i=h2[now];i;i=ne[i]){
		int j=e[i];h2[now]=i;
		if(!Vis[j]&&dep[j]==dep[now]+w2[i]&&w[i]){
			int use_=dfs(j,min(Min-use,w[i]));
			if(use<0) continue;
			use+=use_,sum+=w2[i]*use_;
			w[i]-=use_,w[i^1]+=use_;
			if(use==Min) break;
		}
	}Vis[now]=0;
	return use;
}
il void dinic(){
	while(bfs()) dfs(s,1e18);
	return ;
}

il void solve(){
    n=rd,s=0,t=n+1,idx=1,ans=0,sum=0;
    for(re int i=s;i<=t;++i) h[i]=0;
    for(re int i=1;i<=n;++i) a[i]=rd;
    for(re int i=1;i<=n;++i) add(s,i,a[i],0);
    for(re int i=1;i<=n;++i){
        if(i-1>=1) add(i,i-1,inf,1);
        else add(i,n,inf,1);
        if(i+1<=n) add(i,i+1,inf,1);
        else add(i,1,inf,1);
    }
    for(re int i=1;i<=n;++i) add(i,t,1,0);
    dinic();
    printf("%lld\n",sum);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=rd;while(t--)
	solve();
	return 0;
}
```

---

## 作者：Wilderness_ (赞：0)

## 思路

### 分析
根据题面，我们不难想到 [P4016 负载平衡问题](https://www.luogu.com.cn/problem/P4016)。那道题目有一种贪心做法，所以先考虑贪心。

令 $a_i$ 为第 $i$ 个盒子中的小球数，那么对于每个 $a_i>1$ 的盒子，把其中 $a_i-1$ 个球移到离它最近且 $a_i=0$ 的盒子中。结果可想而知，~~程序挂了~~，因为我们是以编号大小遍历盒子的，那么就会有编号大的盒子中的球有更优解但被编号小的盒子先移动抢占的可能。

面对这种情况，我们需要反悔来寻找最优解，那么这道题就呈现出一种反悔贪心的感觉。~~由于我不会打反悔贪心~~ 由于网络流本质上是一种反悔贪心，外加 P4016 有最小费用最大流的解法，我们还是回到网络流的写法。

### 建图
首先建立一个源点 $s$ 和汇点 $t$。

先考虑开始时每个盒子中有 $a_i$ 个小球，那么我们可以将源点 $s$ 看作那个放小球的人，开始时 $s$ 向第 $i$ 个盒子中放 $a_i$ 个球，即 $s$ 向 $i$ 连一条权值为 $a_i$ 的边。

然后考虑到小球只能移到相邻两个盒子中，于是对于第 $i$ 个盒子 $i$ 分别向 $i-1$ 和 $i+1$ 连一条权值为 $inf$ 的边。

（其中 $inf$ 表示一个极大的值，还有就是注意当 $i=1$ 时，连向 $i-1$ 的边应连向 $n$；当 $i=n$ 时，连向 $i+1$ 的边应连向 $1$。）

再考虑最后每个盒子中最多只有一个小球（$a_i\le1$），所以对于第 $i$ 个盒子 $i$ 向 $t$ 连一条权值为 $1$ 的边。

经一眼丁真，我们发现这样建图时，$\sum\limits_{i=1}\limits^{n}{a_i}$ 一定是最大流，接下来就该思考移动次数最少时的操作次数怎么求。

我们惊人的发现一次转移的操作次数竟然为 $1$！（这不废话）那么我们除了连向 $s,t$ 两点或从这两点连出的边以外，每条边的费用都为 $1$。

那么至此，图就建完了。

### Last step
跑最小费用最大流即可。

### 注意事项：

注意多测！！！

## Code
```
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll int
using namespace std;
ll n,m,s,t,T,maxflow,mincost,dis[5011],tot=1,now[5011],hd[5011],pre[5011],flow[5011],num[5011],ave; 
bool vis[5011];
struct node
{
	ll to,nxt,val,cost;
}edge[114514];
void addedge(ll u,ll v,ll w,ll c)
{
	edge[++tot].to=v;
	edge[tot].val=w;
	edge[tot].cost=c;
	edge[tot].nxt=hd[u];
	hd[u]=tot;
}
inline bool SPFA()
{
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	queue<ll>q;
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	flow[s]=INF;
	while(q.size())
	{
		ll top=q.front();
		q.pop();
		vis[top]=0;
		for(ll i=hd[top];i;i=edge[i].nxt)
		{
			ll v=edge[i].to;
			if(edge[i].val&&dis[v]>dis[top]+edge[i].cost)
			{
				dis[v]=dis[top]+edge[i].cost;
				flow[v]=min(flow[top],edge[i].val);
				pre[v]=i;
				if(!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                }
			}
		}
	}
	return dis[t]!=INF;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		maxflow=mincost=0;
		memset(hd,0,sizeof hd);
		memset(pre,0,sizeof pre);
		for(ll i=0;i<=114513;++i)edge[i]={0,0,0,0};
		scanf("%d",&n);s=0,t=n+1;
		for(ll i=1;i<=n;++i)scanf("%d",&num[i]);
		for(int i=1;i<=n;++i)if(num[i])addedge(s,i,num[i],0),addedge(i,s,0,0);
		for(int i=1;i<=n;++i)addedge(i,t,1,0),addedge(t,i,0,0);
		for(int i=1;i<=n;++i)
		{
			addedge(i,(i==n?1:i+1),n,1);addedge((i==n?1:i+1),i,0,-1);
			addedge(i,(i==1?n:i-1),n,1);addedge((i==1?n:i-1),i,0,-1);
		}
		while(SPFA())
		{
			maxflow+=flow[t];
			mincost+=flow[t]*dis[t];
			for(int i=t;i!=s;i=edge[pre[i]^1].to)
			{
				edge[pre[i]].val-=flow[t];
				edge[pre[i]^1].val+=flow[t];
			}
		}
		printf("%d\n",mincost);
	} 
	return 0;
}
```

---

## 作者：hexagon (赞：0)

**前置知识**：费用流

为了方便叙述下文约定：

1. $(a,b,c,d)$ 表示从 $a$ 向 $b$ 建一条**容量**为 $c$ ,**费用**为 $d$ 的边 
2. $s$ 为原点，$t$ 为汇点。

这道题有一个显然的做法，我们对于每一个盒子建一个点 $A_i$：

+ $A_i\geq1$ 建边 $(s,i,A_i-1,0)$ ，表示这个盒子可以拿出 $A_i-1$ 个球。
+  $A_i<1(A_i=0)$ 建边 $(i,t,1,0)$ 表示这个盒子需要放入 $1$ 个球。

对于任意两个盒子 $u,v$ ,建边 $(u,v,\inf,dis(u,v))$,$(v,u,\inf,dis(u,v))$ 其中 $dis(u,v)$ 表示 $u$ 和 $v$ 在环上的距离，其表示每把一个球从 $u$ 放入 $v$ 或从 $v$ 放入 $u$ 的操作次数。

考虑这个图的意义：

1. 每一条从 $s$ 到 $t$ 的大小为一的流代表把一个球从一个盒子放入另一个盒子。
2. 最后流量的大小一定为空的盒子的个数。

所以跑费用流后的最小费用就是答案。

但是这样的边数是 $O(n^2)$ 的，并不够优秀。

其实只用对于任意两个**相邻**的盒子连边就好了，会发现这样的 $2*n$ 条边包含了上面的两两盒子间的连边。

这样边数就变成了 $O(n)$ ，可以通过。

#### code:
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;i--)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int N=1005;
int n,m,s,t,dis[N],h[N],cur[N],vis[N],num=1,ans,ret,a[N];
struct Edge{
    int x,t,w,c;
}e[2*N*N];
inline void add(int s,int t,int w,int c){
    e[++num].x=h[s],e[num].t=t,e[num].w=w,e[num].c=c,h[s]=num;
    e[++num].x=h[t],e[num].t=s,e[num].w=0,e[num].c=-c,h[t]=num;
}
inline bool spfa(){
    mem(dis,INF),memcpy(cur,h,sizeof(h));
    queue<int> q;
    dis[s]=0,vis[s]=1,q.push(s);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]=0;
        for(int i=h[now];i;i=e[i].x) if(e[i].w&&dis[e[i].t]>dis[now]+e[i].c){
            dis[e[i].t]=dis[now]+e[i].c;
            if(!vis[e[i].t]) q.push(e[i].t),vis[e[i].t]=1;
        }
    }
    return dis[t]!=INF;
}
inline int dfs(int now,int lim){
    if(now==t) return lim;
    vis[now]=1;
    int k,res=0;
    for(int&i=cur[now];i&&lim;i=e[i].x) if(e[i].w&&!vis[e[i].t]&&dis[e[i].t]==dis[now]+e[i].c){
        k=dfs(e[i].t,min(lim,e[i].w));
        res+=k,lim-=k,e[i].w-=k,e[i^1].w+=k,ret+=k*e[i].c;
        if(lim==0) break;
    }
    vis[now]=0;
    return res;
}
inline void solve(){
    mem(h,0),ans=ret=0,num=1;
    cin>>n;
    s=0,t=n+1;
    rep(i,1,n){
        cin>>a[i];
        if(a[i]>1) add(i,t,a[i]-1,0);
        if(a[i]==0) add(s,i,1,0);
    }
    rep(i,1,n){
        add((i-1==0)?n:i-1,i,INF,1);
        add(i,(i-1==0)?n:i-1,INF,1);
    }
    while(spfa()) ans+=dfs(s,INF);
    cout<<ret<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

