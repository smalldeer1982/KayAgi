# [AGC038F] Two Permutations

## 题目描述

**【题意简述】**

给定两个 $0 \sim (N - 1)$ 的排列 $\{P_0, P_1, \ldots , P_{N - 1}\}$ 和 $\{Q_0, Q_1, \ldots , Q_{N - 1}\}$。

要求构造两个 $0 \sim (N - 1)$ 的排列 $\{A_0, A_1, \ldots , A_{N - 1}\}$ 和 $\{B_0, B_1, \ldots , B_{N - 1}\}$。

且必须满足条件：

- $A_i$ 要么等于 $i$，要么等于 $P_i$。
- $B_i$ 要么等于 $i$，要么等于 $Q_i$。

你需要最大化 $A_i \ne B_i$ 的下标 $i$ 的数量，输出这个最大值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le {10}^5$。

## 样例 #1

### 输入

```
4
2 1 3 0
0 2 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
10
0 4 5 3 7 8 2 1 9 6
3 8 5 6 4 0 2 1 7 9```

### 输出

```
8```

## 样例 #3

### 输入

```
32
22 31 30 29 7 17 16 3 14 9 19 11 2 5 10 1 25 18 15 24 20 0 12 21 27 4 26 28 8 6 23 13
22 3 2 7 17 9 16 4 14 8 19 26 28 5 10 1 25 18 15 13 11 0 12 23 21 20 29 24 27 6 30 31```

### 输出

```
28```

# 题解

## 作者：小粉兔 (赞：19)

把 $P$ 分解成不相交循环的乘积后，考虑其中一个循环 $(a_1, a_2, \ldots , a_k)$。

不失一般性，可以把这个循环看作 $(1, 2, \ldots , k)$。

那么对于 $A_1$，有两种情况：$A_1 = 1$ 或 $A_1 = P_1 = 2$。

如果 $A_1 = 1$，则考虑 $A_k$ 有两种情况：$A_k = k$ 或 $A_k = P_k = 1$，但是因为 $A_1 = 1$，所以只能有 $A_k = k$。  
以此类推，可以得到：对于这个循环中的所有元素 $i$，均有 $A_i = i$。

如果 $A_1 = 2$，则考虑 $A_2$ 有两种情况：$A_2 = 2$ 或 $A_2 = P_2 = 3$，但是因为 $A_1 = 2$，所以只能有 $A_2 = 3$。  
以此类推，可以得到：对于这个循环中的所有元素 $i$，均有 $A_i = P_i$。

换句话说，对于每个循环，要么这个循环被完全保留，要么这个循环被完全拆解成一个个自环。

上述结论对 $Q$ 和 $B$ 当然也适用。

我们称**选择**一个循环，指这个循环被完全保留，称**不选**一个循环，指这个循环被拆解成了一个个自环。

接着，考虑一个 $P$ 中的循环 $a$ 和一个 $Q$ 中的循环 $b$，假设它们共有一个元素 $i$。分若干类讨论：

1. $P_i = Q_i = i$：无论如何，这个位置上均有 $A_i = B_i$。
2. $P_i = i, Q_i \ne i$：如果**选择**了 $b$，则这个位置上有 $A_i \ne B_i$，否则**不选** $b$，则这个位置上有 $A_i = B_i$。
3. $P_i \ne i, Q_i = i$：如果**选择**了 $a$，则这个位置上有 $A_i \ne B_i$，否则**不选** $a$，则这个位置上有 $A_i = B_i$。
4. $P_i \ne i, Q_i \ne i, P_i \ne Q_i$：如果**不选** $a$ 且**不选** $b$，则这个位置上有 $A_i = B_i$，否则这个位置上有 $A_i \ne B_i$。
5. $P_i \ne i, Q_i \ne i, P_i = Q_i$：如果 $a, b$ 同时**选择**或同时**不选**，则这个位置上有 $A_i = B_i$，否则这个位置上有 $A_i \ne B_i$。

最终需要最大化 $A_i \ne B_i$ 的下标 $i$ 的数量，也就是最小化 $A_i = B_i$ 的下标 $i$ 的数量。

如果在上述 $5$ 种情况中，一旦发生了 $A_i = B_i$，就赋有 $1$ 的**代价**，那么就是要最小化总代价。

可以发现类似于一个**文理分科模型**，可以建立一个网络流模型，求最小割得到答案。

但是因为有些条件不符合，没法直接套用。

不过，如果把 $Q$ 中的循环割掉与源点和汇点之间的边的意义交换，就可以套用了。

而且可以发现，这样建出来的图是一个二分图，因为 $P$ 中的循环只和源点连边，$Q$ 中的循环只和汇点连边，$P, Q$ 之间也只会互相连边。（如果 $P$ 中的循环对应的节点，割掉与源点相连的边的意义是**不选**它，而 $Q$ 中的循环对应的节点的意义恰好相反的话）

所以最终是在单位容量的二分图上求最小割，使用 Dinic 算法可以做到 $\mathcal O (|E| \sqrt{|V|})$ 的复杂度。

时间复杂度为 $\mathcal O (N \sqrt{N})$，[评测链接](https://atcoder.jp/contests/agc038/submissions/10342736)。

---

## 作者：gxy001 (赞：17)

众所周知，一个排列可以拆成很多个环，我们设 $P_i$ 属于的环为 $p_i$，$Q_i$ 属于的环为 $q_i$。

对于一个环，只有两种选择，拆成若干自环或保留原状。

我们发现情况分为 $5$ 种：

- $P_i=Q_i=i$，此时必然 $A_i=B_i$。
- $P_i=i,Q_i\ne i$，当且仅当 $q_i$ 被拆分时 $A_i=B_i$。
- $P_i\ne i,Q_i=i$，当且仅当 $p_i$ 被拆分时 $A_i=B_i$。
- $P_i\ne Q_i,P_i\ne i,Q_i\ne i$，当且仅当 $p_i$ 和 $q_i$ 都被拆分时 $A_i=B_i$。
- $P_i=Q_i\ne i$，当且仅当 $p_i$ 和 $q_i$ 都被拆分或都不被拆分时 $A_i=B_i$。

我们设 $p_i$ 被拆分时在 $S$ 集合中，$q_i$ 被拆分时在 $T$ 集合中，建出最小割模型。

- $P_i=Q_i=i$，必定耗费 $1$ 代价。
- $P_i=i,Q_i\ne i$，$q_i$ 在 $T$ 集合中耗费 $1$ 代价，$S$ 向 $q_i$ 连边权为 $1$ 的边。
- $P_i\ne i,Q_i=i$，$p_i$ 在 $S$ 集合中耗费 $1$ 代价，$p_i$ 向 $T$ 连边权为 $1$ 的边。
- $P_i\ne Q_i,P_i\ne i,Q_i\ne i$，$p_i$ 在 $S$ 且 $q_i$ 在 $T$ 耗费 $1$ 代价，$p_i$ 向 $q_i$ 连边权为 $1$ 的边。
- $P_i=Q_i\ne i$，$p_i$ 和 $q_i$ 在不同集合耗费 $1$ 代价，$p_i$ 和 $q_i$ 互连边权为 $1$ 的边。

然后跑最小割即可。

这里简单描述一下最后两种边为什么要这么连，以第四种情况为例，若 $S$ 能到 $p_i$，$q_i$ 能到 $T$，为了割开集合，就必须断这条边，也就是说只有断掉这条边才有可能 $p_i$ 在 $S$ 集合中，$q_i$ 在 $T$ 集合中。

因为是最小割，所以第五种情况的边在任何情况下最多只会割掉一个方向，所以代价是 $1$，没有问题。

然后是复杂度，由于是二分图单位边权，时间复杂度 $\mathrm O(n\sqrt n)$。

```cpp
#include<cstdio>
#include<algorithm>
int ans,n,a[100010],b[100010],q[100010],p[100010],tp[100010],tq[100010],cnt,S,T;
int head[100010],to[200010],nxt[200010],w[200010]; 
void add(int const &x,int const &y,int const &wy,int const &wx){
	static int cnt=1;
	to[++cnt]=y,w[cnt]=wy,nxt[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,w[cnt]=wx,nxt[cnt]=head[y],head[y]=cnt;
}
int d[100010],que[100010],*hd,*tl,cur[100010];
bool bfs(){
	for(int i=1;i<=cnt;i++)d[i]=cnt;
	d[S]=0;
	hd=tl=que;
	*tl++=S;
	while(tl!=hd){
		int x=*hd++;
		for(int i=head[x];i;i=nxt[i])
			if(w[i]&&d[to[i]]==cnt) d[*tl++=to[i]]=d[x]+1;
	}
	return d[T]!=cnt;
}
int dfs(int const &x,int const &low){
	if(x==T) return low;
	int used=0;
	for(int &i=cur[x];i;i=nxt[i])
		if(w[i]&&d[to[i]]-1==d[x]){
			int res=dfs(to[i],std::min(w[i],low-used));
			if(res) w[i]-=res,w[i^1]+=res,used+=res;
			if(used==low) return used;
		}
	return used;
}
int dinic(){
	int ans=0;
	while(bfs()){
		for(int i=1;i<=cnt;i++)cur[i]=head[i];
		ans+=dfs(S,0x3f3f3f3f);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	ans=n;
	for(int i=1;i<=n;i++)scanf("%d",a+i),++a[i];
	for(int i=1;i<=n;i++)scanf("%d",b+i),++b[i];
	for(int i=1;i<=n;i++){
		if(!p[i]){
			p[i]=i;
			for(int x=a[i];x!=i;x=a[x])p[x]=i;
			if(a[i]!=i) tp[i]=++cnt;
		}
		if(!q[i]){
			q[i]=i;
			for(int x=b[i];x!=i;x=b[x])q[x]=i;
			if(b[i]!=i) tq[i]=++cnt;
		}
	}
	S=++cnt,T=++cnt;
	for(int i=1;i<=n;i++){
		if(a[i]==i&&b[i]==i)--ans;
		else if(a[i]!=i&&b[i]!=i){
			if(a[i]==b[i]) add(tp[p[i]],tq[q[i]],1,1);
			else add(tp[p[i]],tq[q[i]],1,0);
		}else{
			if(a[i]==i) add(S,tq[q[i]],1,0);
			else add(tp[p[i]],T,1,0);
		}
	}
	printf("%d\n",ans-dinic());
	return 0;
}
```



---

## 作者：abcdeffa (赞：10)

### 为什么写这篇题解

由于我并不理解网上大多数题解采用的建模方式中，对于 $p_i, q_i$ 都变和都不变的建边方式。而网上的题解中都几乎没有对于这个过程的解释分析，有的题解甚至直接用「根据二元关系建边」等一笔带过。

因此，本文将阐述一种有别于其他题解，且正确性更加显然的建模方式。

### 定义

在下文中，为了使叙述更清晰，我们对本文中的一些特殊用语做如下定义。

「环」：对于 $p$ 序列，我们称「环」为连完所有形如 $i \rightarrow p_i$ 这样的边后，产生的大小大于 1 的环，即本文中提到的「环」均只不包括自环的环。对于 $q$ 序列，我们也有类似的定义，相信各位都能理解，因此不在此赘述。

「散点」：对于形如 $i = p_i$ 这样的点。对于 $q$ 序列，我们也有类似的定义。

「群岛」：注意到对于环上的每个点，我们要么同时都让它等于 $p_i$，要么同时都让它等于 $i$，于是如果让它等于 $p_i$，这种变化是环状的。如果让它等于 $i$ 每个点，则没有轮换，即没有边。这使这个环看起来像一堆点，于是我们形象地称它为「群岛」。需要特别注意的是，我们不将「群岛」上的单个点称为「散点」。

### 建模方式

我们思考一下什么情况下会产生相等的位。

1. 把一个序列中的环拆成群岛后，和另一个序列的散点之间产生贡献。

2. 两个环。

3. 两个群岛。

我们考虑将原问题转化为网络流中的最小割问题，如果我们割掉一条边，则会产生代价大小个位置相等，而我们希望这个代价和最小。

于是我们有如下建图。

![](https://cdn.luogu.com.cn/upload/image_hosting/efl27t8l.png)

其中 **对于 $S \rightarrow P, Q$ 和 $P, Q \rightarrow T$ 这些边**（不包括 $P \rightarrow Q$ 和 $Q \rightarrow P$ 这些边），我们发现只可能有四种割边方式：

1. 割 $S \rightarrow P$ 和 $Q \rightarrow T$。

2. 割 $S \rightarrow Q$ 和 $P \rightarrow T$。

3. 割 $P \rightarrow T$ 和 $Q \rightarrow T$。

4. 割 $S \rightarrow P$ 和 $S \rightarrow Q$。

为什么不是其他的边？由于这些边的边权很大，于是我们不能多割这些边中的哪怕一条边，而只割一条边和割其他的两条边都断不了，于是对于 $S \rightarrow P, Q$ 和 $P, Q \rightarrow T$ 这些边，我们只有这四种断边方式。

其中第一种情况是同时成岛，断掉这两条边后还存在着一条 $S \rightarrow Q \rightarrow P \rightarrow T$ 的通路，于是我们将这种情况的贡献放在 $Q \rightarrow P$ 的这条边上。

第二种情况是同时成环，断掉这两条边后还存在着一条 $S \rightarrow P \rightarrow Q \rightarrow T$ 的通路，于是我们将这种情况的贡献放在 $P \rightarrow Q$ 的这条边上。

第三、四种情况分别表示 $P$ 成环，$Q$ 成岛和 $P$ 成岛，$Q$ 成环。对于这两种情况，断掉后图中不再存在通路，不用再付出额外的代价。这是因为基于我们对 5 种序列相等情况的分析，我们得出只有当 $p_i$ 所在的置换环和 $q_i$ 所在的置换环的成岛或成环情况相同时，我们才有可能产生额外的贡献。

对于同时成岛和同时成环的代价，这是很容易计算的，不再在此赘述。

值得一提的是，在实现时，我们将用枚举点的方式来确定 $P$ 和 $Q$ 之间的边权。而这些边权为 $c$ 的边，你可以选择直接将其建成 $c$ 条边权为 1 的边。

这样，我们在发现一个排列中的一个点可以给其所在的环，及其另一个排列中对应的环之间有贡献时，我们可以直接在它们之间建一条边权为 1 的边。由于每个点最多产生一条边，因此边数是 $O(n)$ 级别的。

需要注意的是，上图中的点 $P$ 和点 $Q$ 只有一个，是为了方便表示，在实际情况中，$P$ 点和 $Q$ 点不一定只有一个，且它们之间并不是两两都有边，我们只在有贡献的 $(P, Q)$ 或 $(Q, P)$ 点对之间连边，相信大家应该都注意到了。

如果你想了解更多的细节，可以参考下方的代码实现。注意在 Dinic 中，你需要使用当前弧优化，否则会超出题目所规定的时间限制。

### 代码实现

跑了 7.5s，略慢。

```cpp
#include <set>
#include <cstdio>
#include <cstring>
#define inf 9999999999999999LL
#define maxN 600010
struct edge{ long long x, y, c, g; } b[maxN << 1];
long long len = 1, S = 0, T = 600005;
long long dep[maxN], f[maxN];
long long Fa[maxN], cnt[maxN];
long long PtoId[maxN], QtoId[maxN];
long long cur[maxN], P[maxN], Q[maxN], h[maxN];
long long read ()
{
	long long x = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
	{
		x = x * 10 + (c - '0');
		c = getchar();
	}
	return x;
}
long long min (long long x, long long y) { return x < y ? x : y; }
void ins (long long x, long long y, long long c)
{
	len++; b[len].x = x; b[len].y = y; b[len].c = c;
	b[len].g = h[x]; h[x] = len;
	len++; b[len].x = y; b[len].y = x; b[len].c = 0;
	b[len].g = h[y]; h[y] = len;
}
bool bfs ()
{
	long long head = 1, tail = 2;
	f[1] = S; dep[S] = 1;
	while(head != tail)
	{
		long long x = f[head];
		for(register long long i = h[x];i;i = b[i].g)
		{
			long long y = b[i].y;
			if(b[i].c && !dep[y])
			{
				dep[y] = dep[x] + 1; f[tail] = y;
				if((++tail) >= maxN) tail = 1;
				if(y == T) return true;
			}
		}
		if((++head) >= maxN) head = 1;
	}
	return false;
}
long long dfs (long long x, long long flow)
{
	if(x == T) return flow;
	long long now = flow;
	for(register long long i = cur[x];i;i = b[i].g)
	{
		cur[x] = i; long long y = b[i].y;
		if(b[i].c && dep[y] == dep[x] + 1)
		{
			long long Ma = min(now, b[i].c);
			now -= Ma;
			b[i].c -= Ma, b[i ^ 1].c += Ma;
			long long rest = Ma - dfs(y, Ma);
			now += rest;
			b[i].c += rest, b[i ^ 1].c -= rest;
		}
	}
	return flow - now;
}
long long find (long long x)
{
	if(x == Fa[x]) return x;
	else return Fa[x] = find(Fa[x]);
}
int main ()
{
	freopen("per.in", "r", stdin);
	freopen("per.out", "w", stdout);
	long long n = read();
	for(long long i = 1;i <= (n << 1); i++) Fa[i] = i;
	for(long long i = 1;i <= n; i++)
	{
		P[i] = read() + 1;
		if(i != P[i])
		{
			PtoId[P[i]] = i;
			long long tx = find(i), ty = find(P[i]);
			if(tx != ty) Fa[tx] = ty;
		}
	}
	for(long long i = 1;i <= n; i++)
	{
		Q[i] = read() + 1;
		if(i != Q[i])
		{
			QtoId[Q[i]] = i;
			long long tx = find(n + i), ty = find(n + Q[i]);
			if(tx != ty) Fa[tx] = ty;
		}
	}
	long long Ans = 0;
	for(long long i = 1;i <= n; i++)
	{
		if(P[i] == i && Q[i] == i) Ans++;
		else if(Q[i] == i) cnt[find(i)]++; // cheng dao de gong xian
		else if(P[i] == i) cnt[find(n + i)]++; // tong shang
	}
	long long NodeCnt = 0;
	for(long long i = 1;i <= n; i++)
	{
		if(find(i) == i && P[i] != i) NodeCnt++, ins(S, i, 200000 + cnt[i]), ins(i, T, 200000 + 0);
	}
	for(long long i = n + 1;i <= (n << 1); i++)
	{
		if(find(i) == i && Q[i - n] != i - n) NodeCnt++, ins(i, T, 200000 + cnt[i]), ins(S, i, 200000 + 0);
	}
	for(long long i = 1;i <= n; i++)
	{
		if(P[i] == Q[i] && P[i] != i) ins(find(i), find(n + QtoId[P[i]]), 1);
		// P -> Q : tong shi cheng huan de gong xian
	}
	for(long long i = 1;i <= n; i++)
	{
		if(P[i] != i && Q[i - n] != i - n) ins(find(n + i), find(i), 1);
		// Q -> P : tong shi cheng dao de gong xian
	}
	while(bfs())
	{
		cur[S] = h[S], cur[T] = h[T]; for(long long i = 1;i <= (n << 1); i++) cur[i] = h[i];
		Ans += dfs(S, inf);
		dep[S] = 0, dep[T] = 0; for(long long i = 1;i <= (n << 1); i++) dep[i] = 0;
	}
	printf("%lld", n - (Ans % 200000));
	return 0;
}
```

### 感谢

感谢神仙 lty，教会了我此题的这种建模方法。为此题提供了一种类似但不完全一致的新的思路。

---

## 作者：Kinandra (赞：9)

标签: 网络流.

#### Part 1

显然排列可以拆成若干个环, 每个环可以选择旋转或不旋转. 设 $p_i$ 表示 $i$ 在排列 $P$ 中的环的编号, 类似定义 $q_i$.

考虑分类讨论 $A_i=B_i$ 的条件:

- $P_i=Q_i=i$ , 无论如何 $A_i=B_i$.
- $P_i=i,Q_i\neq i$, $A_i=B_i$ 当且仅当 $q_i$ 不旋转.
- $P_i\neq i,Q_i=i$, $A_i=B_i$ 当且仅当 $p_i$ 不旋转.
- $P_i\neq i, Q_i\neq i$, $A_i=B_i$ 当且仅当 $p_i,q_i$ 都不旋转.
- $P_i=Q_i\neq i$,  $A_i=B_i$ 当且仅当 $p_i,q_i$ 都不旋转或者都旋转.

#### Part 2

观察发现上述同时关联 $p,q$ 的旋转约束要么是都旋转, 要么是都不旋转, 也就是说只有旋转方式相同才会是答案减少.

所以我们用最小割解决问题时要将 $p,q$ 的不用旋转方式看成同一集合.

具体的, $p$ 分入 $S$ 集合表示旋转, $q$ 分入 $T$ 集合表示旋转.

上述 $5$ 中情况分别对应下述 $5$ 中连边:

- 不连.
- $q_i\to T$ , 割去这条边表示 $q_i$ 不旋转, 答案 $-1$.
- $S\to p_i$ , 割去这条边表示 $p_i$ 不旋转, 答案 $-1$.
- $q_i\to p_i$ , 割去这条边表示 $p_i,q_i$ 都不旋转, 答案 $-1$.
- $q_i\to p_i,p_i\to q_i$ , 割去这两条边分别表示 $p_i,q_i$ 都不旋转和 $p_i,q_i$ 都旋转, 答案 $-1$.

求个最小割即可.

时间复杂度 $\mathcal O(n\sqrt n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();

int n, s, t;
int p[200005], q[200005];
int id[2][200005], idcnt;

void work(int u, int* nx, int* id) {
    if (id[u]) return;
    id[u] = idcnt, work(nx[u], nx, id);
}

int hd[200005], nx[1000006], to[1000006], c[1000006], cnt;
void add(int f, int t, int cap) {
    nx[++cnt] = hd[f], hd[f] = cnt, to[cnt] = t, c[cnt] = cap;
}
void fadd(int f, int t, int c) { add(f, t, c), add(t, f, 0); }
struct Flow {
    int dep[200005];
    queue<int> q;
    bool bfs() {
        for (int i = 1; i <= t; ++i) dep[i] = 0;
        dep[s] = 1, q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = hd[u], v; i; i = nx[i]) {
                if (!c[i] || dep[v = to[i]]) continue;
                dep[v] = dep[u] + 1, q.push(v);
            }
        }
        return dep[t];
    }

    int iter[200005];
    int dfs(int u, int dist) {
        if (u == t) return dist;
        for (int &i = iter[u], v, d; i; i = nx[i]) {
            if (!c[i] || dep[v = to[i]] != dep[u] + 1) continue;
            if (d = dfs(v, min(dist, c[i]))) return c[i] -= d, c[i ^ 1] += d, d;
        }
        return 0;
    }
    int Dinic() {
        int rt = 0, d;
        while (bfs()) {
            for (int i = 1; i <= t; ++i) iter[i] = hd[i];
            while (d = dfs(s, 10000000)) rt += d;
        }
        return rt;
    }
} flow;

int main() {
    n = read(), cnt = 1;
    for (int i = 1; i <= n; ++i) p[i] = read() + 1;
    for (int i = 1; i <= n; ++i) q[i] = read() + 1;
    int res = n;
    for (int i = 1; i <= n; ++i)
        if (!id[0][i]) ++idcnt, work(i, p, id[0]);
    for (int i = 1; i <= n; ++i)
        if (!id[1][i]) ++idcnt, work(i, q, id[1]);

    s = ++idcnt, t = ++idcnt;
    for (int i = 1; i <= n; ++i)
        if (p[i] == i && q[i] == i)
            --res;
        else if (p[i] == i)
            fadd(id[1][i], t, 1);
        else if (q[i] == i)
            fadd(s, id[0][i], 1);
        else if (p[i] != q[i])
            fadd(id[1][i], id[0][i], 1);
        else
            fadd(id[1][i], id[0][i], 1), fadd(id[0][i], id[1][i], 1);
    printf("%d\n", res - flow.Dinic());
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：Lyrella (赞：8)

# 题目描述

给定两个 $0 \sim (N - 1)$ 的排列 $\{P_0, P_1, \ldots , P_{N - 1}\}$ 和 $\{Q_0, Q_1, \ldots , Q_{N - 1}\}$。

要求构造两个 $0 \sim (N - 1)$ 的排列 $\{A_0, A_1, \ldots , A_{N - 1}\}$ 和 $\{B_0, B_1, \ldots , B_{N - 1}\}$。

且必须满足条件：

- $A_i$ 要么等于 $i$，要么等于 $P_i$。
- $B_i$ 要么等于 $i$，要么等于 $Q_i$。

你需要最大化 $A_i \ne B_i$ 的下标 $i$ 的数量，输出这个最大值。

# 题解

对于每个排列，我们可以把它分解成若干个置换环。对于每个置换环 $A$，我们只有两种选择：$A_i$ 变或不变。如果一个置换环上其中一点确定，那么整个环也就确定了，因为要确保数字唯一性。所以我们可以先把置换环处理出来，再把每个环当做一个点做。

对于给定的两个排列，一共有五种不同情况。

1. $i=P_i=Q_i$，直接答案减一；
2. $i=P_i\ne Q_i$，只有 $Q_i$ 才会对答案产生影响，如果选 $i$，整个答案就会减一，否则不变；
3. $i=Q_i\ne P_i$，与上一种类似，不再赘述；
4. $i\ne P_i=Q_i$，如果两个同选 $i$ 或自己则答案减一；
5. $i\ne P_i\ne Q_i$，如果两个同选下标 $i$ 则答案减一。

对于这五种情况，每个置换环有两种选择：选择自己的下标或者自己的值，可以想到**最小割**。

然后我们将上面五种情况的结果改一下：

1. $i=P_i=Q_i$，直接答案减一；
2. $i=P_i\ne Q_i$，如果 $Q_i$ 选 $i$，$Q_i$ 所在环向汇点连容量为一的边；
3. $i=Q_i\ne P_i$，与上一种类似，不再赘述；
4. $i\ne P_i=Q_i$，$P_i$ 与 $Q_i$ 所在环互相连容量为一的边；
5. $i\ne P_i\ne Q_i$，$Q_i$ 所在环向 $P_i$ 所在环连容量为一的单向边。

最后直接跑最大流，然后再用总的个数减去跑出来的结果即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
ll rd(){
	ll x = 0, f = 1; char c = getchar();
	while(! isdigit(c)){if(c == '-')f = - f; c = getchar();}
	while(isdigit(c)){x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}

const int N = 2e5 + 5;
int n, s, t, hd[N], cnt = 1, cur[N], ans;
int a[N], b[N], ra[N], rb[N], d[N], top;
struct edge{
	int nxt, to, w;
}e[N << 1];
void add(int u, int v, int w){
	e[++cnt] = (edge){hd[u], v, w}; hd[u] = cnt;
}
int bfs(){
	memset(d, 0, sizeof d);
	queue < int > q;
	q.push(s); d[s] = 1; cur[s] = hd[s];
	while(! q.empty()){
		int u = q.front(); q.pop();
		for(int i = hd[u]; i; i = e[i].nxt){
			int v = e[i].to, w = e[i].w;
			if( ! d[v] and w){
				d[v] = d[u] + 1;
				cur[v] =  hd[v];
				q.push(v);
			}
		}
	}
	return d[t];
}
int dfs(int u, int lim){
	if(u == t or ! lim)return lim;
	int k, flow = 0;
	for(int &i = cur[u]; i and lim; i = e[i].nxt){
		int v = e[i].to, f = e[i].w;
		if(d[v] == d[u] + 1 and (k = dfs(v, min(lim, f)))){
			e[i].w -= k; e[i ^ 1].w += k;flow += k; lim -= k;
		}
	}
	if(! flow)d[u] = t + 1;
	return flow;
}
int dinic(){
	int res = 0, k;
	while(bfs()){
		while(k = dfs(s, INF))res += k;
	}
	return res;
}

signed main(){
	n = rd();
	for(int i = 1; i <= n; ++i)a[i] = rd() + 1;
	for(int i = 1; i <= n; ++i)b[i] = rd() + 1;
	for(int i = 1; i <= n; ++i)if(! ra[i]){
		ra[i] = a[i] != i ? ++top : top;
		int x = a[i];
		while(x != i)ra[x] = top, x = a[x];
	}
	for(int i = 1; i <= n; ++i)if(! rb[i]){
		rb[i] = b[i] != i ? ++top : top;
		int x = b[i];
		while(x != i)rb[x] = top, x = b[x];
	}
	s = top + 1, t = s + 1;
	for(int i = 1; i <= n; ++i)
		if(a[i] == i and b[i] == i)++ans;
		else if(a[i] != i and b[i] != i){
			if(a[i] == b[i]){
				add(ra[i], rb[i], 1); add(rb[i], ra[i], 1);
				add(ra[i], rb[i], 0); add(rb[i], ra[i], 0);
			}
			else{
				add(rb[i], ra[i], 1); add(ra[i], rb[i], 0);
			}
		}
		else{
			if(a[i] == i)add(rb[i], t, 1), add(t, rb[i], 0);
			else add(ra[i], s, 0), add(s, ra[i], 1);
		}
	printf("%d", n - ans - dinic());
	return 0;
}
```

---

## 作者：Graphcity (赞：3)

先考虑第一个排列。对排列进行图论建模，建一张二分图，连 $(i,i')$ 和 $(i,p_i')$ 的无向边表示 $a_i$ 的选法，由于每个点的度数都是二，能够形成若干个偶环。

对于每一个偶环，显然只能交替选边，也就只有两种选法。而且，这两种选法中，第一种对应 $a_i=i$，第二种对应 $a_i=p_i$。

对于每一个偶环，我们设 $a_i=i$ 的选法为红色，$a_i=p_i$ 的选法为蓝色。第二个排列同理。

最大化 $a_i\not=b_i$ 的位置数量就相当于最小化 $a_i=b_i$ 的位置数量。对于每个 $i$，列一张表格来进行梳理：

| $a_i$ \ $b_i$ | **红色** | **蓝色** |
| :----------: | :----------: | :----------: |
| **红色** | $i,i$ | $i,q_i$ |
| **蓝色** | $p_i,i$ | $p_i,q_i$ |

分类讨论：

1. $i\not=p_i,i\not=q_i,p_i\not=q_i$：仅有红红产生贡献。

2. $i\not=p_i,i\not=q_i,p_i=q_i$：红红和蓝蓝产生贡献。

3. $i=p_i,i\not=q_i$：任意颜色和红产生贡献。

4. $i=q_i,i\not=p_i$：红和任意颜色产生贡献。

5. $i=p_i,i=q_i$：不管怎样都会产生贡献。

考虑网络流中的最小割：设 $x$ 为 $a_i$ 所在的偶环，$y$ 为 $b_i$ 所在的偶环。$x$ 在源点集合中表示红色，否则表示蓝色；$y$ 在源点集合表示蓝色，否则表示红色。对于每种情况：

| 情况 | 连边方式 |
| :----------: | :----------: |
| 1 | $x\stackrel{1}\rightarrow y$ |
| 2 | $x\stackrel{1}\rightarrow y$，$y\stackrel{1}\rightarrow x$ |
| 3 | $s\stackrel{1}\rightarrow y$ |
| 4 | $x\stackrel{1}\rightarrow t$ |
| 5 | $ans\gets ans+1$ |

然后跑最大流。时间复杂度 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6,Maxm=2e6,inf=1e9;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,s,t,ans,maxf,dis[Maxn+5],vis[Maxn+5];
int fa[Maxn+5],p[Maxn+5],q[Maxn+5],id[Maxn+5];
vector<int> v[Maxn+5];
struct Node{int frm,to,nxt,w;} Edge[Maxm*2+5];
int tot=1,Head[Maxn+5],cur[Maxn+5];
inline void Addedge(int x,int y,int z)
{
    Edge[++tot]=(Node){x,y,Head[x],z},Head[x]=tot;
    Edge[++tot]=(Node){y,x,Head[y],0},Head[y]=tot;
}
inline int Find(int x) {return fa[x]==x?x:fa[x]=Find(fa[x]);}

inline int bfs()
{
    queue<int> q;
    For(i,1,t) dis[i]=vis[i]=0,cur[i]=Head[i];
    q.push(s),vis[s]=1;
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        for(int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to;
            if(Edge[i].w && !vis[y]) vis[y]=1,dis[y]=dis[x]+1,q.push(y);
        }
    }
    return vis[t];
}
inline int dfs(int x,int flow)
{
    if(x==t || !flow) {maxf+=flow; return flow;}
    int used=0,res=0;
    for(int i=cur[x];i && used<flow;i=Edge[i].nxt)
    {
        int y=Edge[i].to; cur[x]=i;
        if(Edge[i].w && dis[y]==dis[x]+1)
            if(res=dfs(y,min(flow-used,Edge[i].w)))
                used+=res,Edge[i].w-=res,Edge[i^1].w+=res;
    }
    return used;
}

int main()
{
    n=read();
    For(i,1,n) p[i]=read()+1;
    For(i,1,n) q[i]=read()+1;
    For(i,1,n*2) fa[i]=i;
    For(i,1,n) {int x=Find(i),y=Find(p[i]); if(x!=y) fa[x]=y;}
    For(i,1,n) {int x=Find(n+i),y=Find(n+q[i]); if(x!=y) fa[x]=y;}
    For(i,1,n*2) v[Find(i)].push_back(i);
    For(i,1,n*2) if(Find(i)==i) id[i]=++s;
    m=s,s=m*2+1,t=s+1;
    For(i,1,n)
    {
        int x=id[Find(i)],y=id[Find(i+n)];
        if(i!=p[i] && i!=q[i] && p[i]!=q[i]) Addedge(x,y,1);
        if(i!=p[i] && i!=q[i] && p[i]==q[i]) Addedge(x,y,1),Addedge(y,x,1);
        if(i==p[i] && i!=q[i]) Addedge(s,y,1);
        if(i==q[i] && i!=p[i]) Addedge(x,t,1);
        if(i==p[i] && i==q[i]) ans++;
    }
    while(bfs()) dfs(s,inf);
    cout<<n-(ans+maxf)<<endl;
    return 0;
}
```

---

## 作者：tzc_wk (赞：3)

[洛谷题面传送门](https://www.luogu.com.cn/problem/AT5203) & [Atcoder 题面传送门](https://atcoder.jp/contests/arc038/tasks/agc038_f)

~~好久前做的题了……今天偶然想起来要补个题解~~

首先考虑排列 $A_i$ 要么等于 $i$，要么等于 $P_i$ 这个条件有什么用。我们考虑将排列 $P_i$ 拆成一个个置换环，那么对于每一个 $i$，根据其置换环的情况可以分出以下几类：

- 如果 $i$ 所在置换环大小为 $1$，即 $P_i=i$，那么 $A_i$ 别无选择，只能等于 $i$
- 如果 $i$ 所在置换环大小不为 $1$，那么 $A_i$ 有两种选择，$A_i=i$ 或者 $A_i=P_i$
  - 如果 $A_i=i$，那么假设 $j$ 为满足 $P_j=i$ 的位置，那么由于排列中元素不能重复，因此 $A_j\ne P_j=i$，即 $A_j=j$，我们再找出 $P_k=j$ 的 $k$，也应有 $A_k=k$，这样即可确定整个置换环上元素的情况。
  - 如果 $A_i=P_i$，类似地，设 $j=P_i$，那么 $A_j\ne j$，因为排列中元素不能重复，故 $A_j=P_j$，我们再找出 $k=P_j$ 的位置 $k$，也应有 $A_k=P_k$，这样也能够确定整个置换环的 $A$。

也就是说，对于一个置换环而言，我们可以将其视作一个整体看待——这个置换环中要么所有元素的 $A_i$ 都等于其本身，要么所有元素的 $A_i$ 都等于 $P_i$，为了使表述更加具体形象，我们把前一种情况称作“转”~~（orz wlzhouzhuan）~~，后一种情况称作“不转”。那么对于每一个下标 $i$，它是否产生的 $A_i=B_i$ 的情况如下：

- 如果 $i=P_i=Q_i$，那么不管怎样都有 $A_i=B_i$，我们完全可以直接令答案加一，并忽略这种情况。
- 如果 $i=P_i\ne Q_i$，那么若 $Q_i$ 所在置换环不转就会有 $A_i=B_i=i$，对答案产生 $1$ 的贡献，若 $Q_i$ 所在置换环转则不会产生这样的情况。
- 如果 $i=Q_i\ne P_i$，同理，若 $P_i$ 所在置换环不转则重复元素个数 $+1$，否则重复元素个数不变。
- 如果 $i\ne P_i=Q_i$，那么如果 $P_i$ 所在置换环与 $Q_i$ 所在置换环同时转/同时不转那么重复元素个数 $+1$，否则重复元素个数不变。
- 如果 $i\ne P_i\ne Q_i$，那么如果 $P_i$ 所在置换环与 $Q_i$ 所在置换环同时不转那么重复元素个数 $+1$，否则重复元素个数不变。

如果我们将每个置换环“转”看作被划分入 A 集合，“不转”看作被划分入 B 集合，那么上述条件可以转化为：

- $i=P_i\ne Q_i$：如果 $Q_i$ 所在置换环属于 B 那么答案加 $1$
- $i=Q_i\ne P_i$：如果 $P_i$ 所在置换环属于 B 那么答案加 $1$
- $i\ne P_i=Q_i$：如果 $P_i,Q_i$ 所在置换环属于相同集合那么答案加 $1$
- $i\ne P_i\ne Q_i$：如果 $P_i,Q_i$ 都属于 B 集合那么答案加 $1$

看到“划分为两个集合”，“如果两点属于相同/不同集合则代价加 $1$，求最小/最大代价”之类的字眼，我们能够想到……**最小割**！具体来说，我们将每个置换环看作一个点，并新建源汇，我们定义 $P$ 中的置换环转当且仅当其与 $S$ 相连，不转当且仅当其与 $T$ 相连；$Q$ 中的置换环转当且仅当其与 $T$ 相连，不转当且仅当其与 $S$ 相连，这样所有代价都可以用一/两条网络流上的 $1$ 权边的形式表述，再根据最大流 $=$ 最小割求出最小代价即可。

时间复杂度同 dinic 求二分图匹配，$\mathcal O(n\sqrt{n})$。

```cpp
const int MAXN=1e5;
const int MAXV=1e5+2;
const int MAXE=2e5*2;
const int INF=0x3f3f3f3f;
int n,a[MAXN+5],b[MAXN+5],S=1e5+1,T=1e5+2,ncnt=0;
int bel_a[MAXN+5],bel_b[MAXN+5];
int hd[MAXV+5],to[MAXE+5],cap[MAXE+5],nxt[MAXE+5],ec=1;
void adde(int u,int v,int f){
	to[++ec]=v;cap[ec]=f;nxt[ec]=hd[u];hd[u]=ec;
	to[++ec]=u;cap[ec]=0;nxt[ec]=hd[v];hd[v]=ec;
} int dep[MAXV+5],now[MAXV+5];
bool getdep(){
	memset(dep,-1,sizeof(dep));dep[S]=0;
	queue<int> q;q.push(S);now[S]=hd[S];
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e],z=cap[e];
			if(z&&!~dep[y]){
				dep[y]=dep[x]+1;
				now[y]=hd[y];q.push(y);
			}
		}
	} return ~dep[T];
}
int getflow(int x,int f){
	if(x==T) return f;int ret=0;
	for(int &e=now[x];e;e=nxt[e]){
		int y=to[e],z=cap[e];
		if(z&&dep[y]==dep[x]+1){
			int w=getflow(y,min(f-ret,z));
			ret+=w;cap[e]-=w;cap[e^1]+=w;
			if(f==ret) return ret;
		}
	} return ret;
}
int dinic(){
	int ret=0;
	while(getdep()) ret+=getflow(S,INF);
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),++a[i];
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),++b[i];
	for(int i=1;i<=n;i++) if(!bel_a[i]){
		bel_a[i]=(i^a[i])?(++ncnt):ncnt;int cur=a[i];
		while(cur^i) bel_a[cur]=ncnt,cur=a[cur];
	}
	for(int i=1;i<=n;i++) if(!bel_b[i]){
		bel_b[i]=(i^b[i])?(++ncnt):ncnt;int cur=b[i];
		while(cur^i) bel_b[cur]=ncnt,cur=b[cur];
	} int res=n;
	for(int i=1;i<=n;i++){
		if(a[i]==i&&b[i]==i) res--;
		else if(a[i]!=i&&b[i]!=i){
			if(a[i]==b[i]) adde(bel_a[i],bel_b[i],1),adde(bel_b[i],bel_a[i],1);
			else adde(bel_b[i],bel_a[i],1);
		} else {
			if(a[i]==i) adde(bel_b[i],T,1);
			else adde(S,bel_a[i],1);
		}
	} printf("%d\n",res-dinic());
	return 0;
}
```



---

## 作者：WrongAnswer_90 (赞：2)

[AT_agc038_f [AGC038F] Two Permutations](https://www.luogu.com.cn/problem/AT_agc038_f)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/18083524)

下面默认 $P,Q$ 均整体加了 $1$，下标从 $1$ 开始。

首先考虑如果 $a_i=i$，则 $p_j=i$ 的 $a_j=j$。然后多迭代几次，一定会回到 $i$。这提示我们把排列拆成若干个环，每个环 $R$ 满足 $p_{r_{len}}=r_1\wedge\forall i<len,p_{r_i}=r_{i+1}$。这样每个环要么满足全部 $a_i=i$（方案 $1$），要么满足全部 $a_i=p_i$（方案 $2$）。

这样对于每个 $i$ 可以求出 $ca_i$ 和 $cb_i$ 表示在 $a$ 和 $b$ 的那个环里。接下来是分讨：

1. $a_i=b_i=i$。此时该位置的贡献一定为 $0$。

2. $a_i=i\wedge b_i\ne i$。此时若 $cb_i$ 选择方案 $1$ 则收益为 $0$，否则收益为 $1$。

3. $a_i\ne i\wedge b_i=i$。此时若 $ca_i$ 选择方案 $1$ 则收益为 $0$，否则收益为 $1$。

4. $a_i\ne i\wedge b_i\ne i$。此时若 $ca_i$ 和 $cb_i$ 均选择方案 $1$ 则收益为 $0$，若 $ca_i,cb_i$ 均选择方案 $2$ 且 $a_i=b_i$ 则收益为 $0$，否则收益为 $1$。

$1,2,3$ 都是平凡的，$4$ 是一个反着的文理分科模型，无法用流图建模。

传统的文理分科是归到 $S$ 集合是割掉和 $T$ 的边，归到 $T$ 集合是割掉 $S$ 的边。这里归到 $S$ 是选择方案 $1$，归到 $T$ 是选择方案 $2$。因为只有 $ca,cb$ 之间的关系，$ca,cb$ 内部的情况是不会造成贡献的。考虑经典套路，对于 $b$ 的意义进行翻转。此时变成了：

4. 若 $ca_i$ 归到 $S$，$cb_i$ 归到 $T$，则代价为 $1$，若 $ca_i$ 归到 $T$，$cb_i$ 归到 $S$ 且 $a_i=b_i$，则代价为 $1$。

这样就是[这道题](https://www.luogu.com.cn/problem/P2057)了，两点间连容量为 $1$ 的边即可。因为建出来的图是二分图，暴力跑 dinic 就是对的。总复杂度 $\mathcal O(n\sqrt n)$。思路还是很清晰的，第一步需要一点观察。

```cpp
	int n,num,ans,s[200010],t[200010],ca[100010],cb[100010],a[100010],b[100010];
	bool vis[100010];
	int S,T,cnt=1,head[200050],to[1000010],nex[1000010],v[1000010],d[200050],now[200050];
	inline void Add(int x,int y,int z){to[++cnt]=y,v[cnt]=z,nex[cnt]=head[x],head[x]=cnt;}
	inline void add(int x,int y,int z){Add(x,y,z),Add(y,x,0);}
	inline void clr(){memset(head,0,sizeof(head)),cnt=1;}
	inline bool bfs()
	{
		queue<int> q;memset(d,0,sizeof(d)),d[S]=1,now[S]=head[S],q.e(S);
		while(!q.empty())
		{
			int nw=q.front();q.pop();
			for(int i=head[nw];i;i=nex[i])if(v[i]&&!d[to[i]])
			{
				d[to[i]]=d[nw]+1,q.e(to[i]),now[to[i]]=head[to[i]];
				if(to[i]==T)return 1;
			}
		}
		return 0;
	}
	int dinic(int x,int flow)
	{
		if(x==T)return flow;
		int rest=flow,t;
		for(int i=now[x];i&&rest;i=nex[i])
		{
			now[x]=i;
			if(d[to[i]]!=d[x]+1||!v[i])continue;
			t=dinic(to[i],min(rest,v[i])),rest-=t;
			if(!t)d[to[i]]=0;
			v[i]-=t,v[i^1]+=t;
		}
		return flow-rest;
	}
	inline void mian()
	{
		read(n),ans=n;int x;
		for(int i=1;i<=n;++i)read(a[i]),++a[i];
		for(int i=1;i<=n;++i)read(b[i]),++b[i];
		for(int i=1;i<=n;++i)if(!ca[i]){++num,x=a[i];do ca[x]=num,x=a[x];while(!ca[x]);}
		int la=num;
		for(int i=1;i<=n;++i)if(!cb[i]){++num,x=b[i];do cb[x]=num,x=b[x];while(!cb[x]);}
		S=num+1,T=S+1;
		for(int i=1;i<=n;++i)
		{
			if(a[i]==i)
			{
				if(b[i]==i)--ans;
				else ++t[cb[i]];
			}
			else
			{
				if(b[i]==i)++s[ca[i]];
				else
				{
					add(cb[i],ca[i],1);
					if(a[i]==b[i])add(ca[i],cb[i],1);
				}
			}
		}
		for(int i=1;i<=la;++i)add(S,i,s[i]);
		for(int i=la+1;i<=num;++i)add(i,T,t[i]);
		while(bfs())while((x=dinic(S,inf)))ans-=x;
		write(ans);
	}
```

---

## 作者：Acoipp (赞：2)

## 题意

给定两个 $0 \sim (N - 1)$ 的排列 $P$ 和 $Q$。

要求构造两个 $0 \sim (N - 1)$ 的排列 $A$ 和 $B$。

必须满足以下条件：

- $A_i$ 要么等于 $i$，要么等于 $P_i$。
- $B_i$ 要么等于 $i$，要么等于 $Q_i$。

最大化 $A_i \ne B_i$ 的下标 $i$ 的数量，输出这个最大值。

## 分析

方便起见，以下环节的下标都是 $1 \sim n$，并且 $A$ 和 $B$ 排列的每个元素数值都加上了 $1$。

首先每个值是二选一让我们想到了最小割，对于每个 $A_i$ 和 $B_i$ 都要建立一个点，然后源点往这个点连边，边权为 $0$；这个点往汇点连边，边权为 $0$，这是初始状态，答案初始化为 $n$，减去最小割就是最大的值。

考虑这样一种理解方式：

- 最左边有一个源点 $S$，最右边有一个汇点 $T$。
- 中间有两个竖排的点，分别表示 $A_i$ 的虚点集合和 $B_i$ 的虚点集合。
- 中间的点都有一条源点到它的边和它到汇点的边，边权都是 $0$。
- 如果最小割的方案中割掉了源点到左边竖排的点的边，代表 $A_i$ 选的是 $i$；否则选的是 $P_i$。
- 如果最小割的方案中割掉了源点到右边竖排的点的边，代表 $B_i$ 选的是 $Q_i$；否则选的是 $i$。

图大概是下面这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/kn9g7iad.png)

图中边的走向都是单向从左往右，边流量都是 $0$。

我们分情况讨论一下：

- $P_i=Q_i$ 且 $P_i=Q_i=i$
	- 那这个点没有用了，不论怎么样都相等，而且不影响其它点的选择，答案减一即可。
    
- $P_i=Q_i$ 且 $P_i=Q_i\ne i$
	- 相当于上面的图中我们如果割了 $s \to 1$ 和 $1' \to t$ 的边，依然要保证连通，并且增广路大小是 $1$（答案要减一才能“生效”），那么连接 $1' \to 1$，流量为 $1$ 即可；如果割了 $s \to 1'$ 和 $1 \to t$ 的边，依然要保证连通，并且增广路大小是 $1$（答案要减一才能“生效”），那么连接 $1 \to 1'$，流量为 $1$ 即可；
    
- $P_i \ne Q_i$ 且 $P_i=i$

	- 相当于 $A_i$ 恒等于 $i$，如果 $B_i$ 选择 $i$，答案减一；否则不变。则把 $B_i \to t$ 的边流量改为 $1$ 即可。
    
- $P_i \ne Q_i$ 且 $Q_i=i$

	- 相当于 $B_i$ 恒等于 $i$，如果 $A_i$ 选择 $i$，答案减一；否则不变。则把 $s \to A_i$ 的边流量改为 $1$ 即可。
    
- $P_i \ne Q_i$ 且 $P_i \ne i,Q_i\ne i$

	- 相当于如果 $A_i$ 和 $B_i$ 同时选 $i$ 答案加 $1$，那么图上就是割掉了 $s \to A_i$ 和 $B_i \to t$ 的边之后，图上存在一条增广路为 $1$，那么连接 $B_i \to A_i$ 就能满足条件，边流量为 $1$。
    
然后存在某些点对，满足 $i=P_j$ 的情况，这时若 $A_i=i$ 则 $A_j \ne P_j$，转化到图上就是若割掉了 $s \to A_i$ 的边和 $A_j \to t$ 的边，图中存在增广路长度为 $\text{inf}$，连接 $A_j \to A_i$，边流量为 $\text{inf}$ 即可满足要求。

或者是 $i=Q_j$ 若 $B_i=i$ 则 $B_j \ne Q_j$，转化到图上就是若割掉了 $B_i \to t$ 的边和 $s \to B_j$ 的边，图中存在增广路长度为 $\text{inf}$，连接 $B_i \to B_j$，边流量为 $\text{inf}$ 即可满足要求。 
   
你就得到了下面的代码（建图）（下面把边权为 $0$ 的边省略了）：

```cpp
for(i=1;i<=n;i++) if(o1[i]!=i) merge(in[o1[i]],in[i],n);
for(i=1;i<=n;i++) if(o2[i]!=i) merge(out[i],out[o2[i]],n);
for(i=1;i<=n;i++){
	if(a[i]==b[i]){
		if(a[i]==i) ans--;
		else merge(in[i],out[i],1),merge(out[i],in[i],1);
	}
	else{
		if(a[i]==i) merge(out[i],t,1);
		else if(b[i]==i) merge(s,in[i],1);
		else merge(out[i],in[i],1);
	}
}
```

很显然这是错的，因为这样的话图上的边权不全部为 $1$，网络流的根号级别时间复杂度无法保证。

考虑优化建图，这里从理论的根源开始优化（以 $A$ 数组的选择开始考虑）：

- 如果 $A_i$ 选择了 $i$，那么如果存在 $P_j=i(j \ne i)$，那么 $A_j$ 只能选择 $j$；如果 $A_i$ 选择了 $P_i(P_i \ne i)$，那么如果存在 $P_j=i(j \ne i)$，那么 $A_j$ 只能选择 $P_j$；这样的话就构成了一个环，环上的一个点确定之后其它点就都确定了，于是我们可以“缩点”，把有这种关系的 $A_i$ 缩成一个点，就少了边权为 $n$ 的边。

缩点之后可以继续跑网络流，并且答案是对的，因为网络流的流量可以累加，对于 $B$ 数组的处理同理。

那么我们就只剩边权为 $1$ 的边，并且把边权为 $0$ 的边省略后就是一个二分图，用 Dinic 跑的话时间复杂度是根号级别的。（点数和边数同阶）
## 代码

代码使用 Dinic 实现，ISAP 如果实现不太好的话会被卡爆，特别是这种二分图上的网络流。

缩点下面使用并查集实现。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,inf,s,t,i,j,k,l,ans,a[N],b[N],in[N],out[N],o1[N],o2[N],q[N],he,ta;
int la[N],ne[N],to[N],val[N],dis[N],cur[N],tot=1,fath1[N],fath2[N];
int gf1(int x){return x==fath1[x]?x:fath1[x]=gf1(fath1[x]);}
int gf2(int x){return x==fath2[x]?x:fath2[x]=gf2(fath2[x]);}
inline void merge(int x,int y,int z,int zz){
	tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z;
	tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = zz;
}
bool bfs(){
	for(int i=0;i<inf;i++) dis[i]=-1;
	dis[s]=0;
	q[he=ta=1]=s;
	while(he<=ta){
		int tmp = q[he++];
		for(int i=la[tmp];i;i=ne[i]){
			if(val[i]>0&&dis[to[i]]==-1){
				dis[to[i]] = dis[tmp]+1;
				q[++ta] = to[i];
			}
		}
	}
	return dis[t]!=-1; 
}
int dfs(int x,int step){
	if(x==t) return step;
	int used = 0;
	for(int i=cur[x];i;i=ne[i]){
		cur[x] = i;
		if(dis[to[i]]==dis[x]+1&&val[i]>0){
			int temp = dfs(to[i],min(val[i],step-used));
			val[i] -= temp,val[i^1] += temp,used += temp;
			if(used==step||dis[s]>=inf) return used;
		}
	}
	return used;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	ans=n;
	s=0,t=1,inf=2;
	for(i=1;i<=n;i++) fath1[i]=i,fath2[i]=i;
	for(i=1;i<=n;i++) cin>>a[i],a[i]++,o1[a[i]]=i;
	for(i=1;i<=n;i++) cin>>b[i],b[i]++,o2[b[i]]=i;
	for(i=1;i<=n;i++) fath1[gf1(i)]=gf1(o1[i]);
	for(i=1;i<=n;i++) fath2[gf2(i)]=gf2(o2[i]);
	for(i=1;i<=n;i++){
		if(!in[gf1(i)]) in[gf1(i)]=inf++;
		if(!out[gf2(i)]) out[gf2(i)]=inf++;
	}
	for(i=1;i<=n;i++){
		if(a[i]==b[i]){
			if(a[i]==i) ans--;
			else merge(in[gf1(i)],out[gf2(i)],1,1);
		}
		else{
			if(a[i]==i) merge(out[gf2(i)],t,1,0);
			else if(b[i]==i) merge(s,in[gf1(i)],1,0);
			else merge(out[gf2(i)],in[gf1(i)],1,0);
		}
	}
	while(bfs()){
		for(i=0;i<inf;i++) cur[i]=la[i];
		ans-=dfs(s,n);
	}
	cout<<ans<<endl;
	return 0;
} 
/*
Input:
4
2 1 3 0
0 2 3 1

Output:
3
*/
```

---

## 作者：Crescent_Rose_ (赞：1)

每个置换环，有“转“与”不转“两种状态，且由于要形成排列，每个位置不独立（即一个置换环要么都是 $i$，要么都是 $P_i$ 或 $Q_i$）。

对于一组 $i,P_i,Q_i$，讨论 $i,P_i,Q_i$ 的相等关系，即是否有 $P_i=i,Q_i=i,P_i=Q_i$，共八种情况，下面用 $0/1$ 顺次表示三个条件是否满足，考虑每种情况下位置 $i$ 有 $1$ 的贡献的要求，用 $p_x,q_y\in\{0,1\}$ 分别表示 $i$ 在 $P,Q$ 上的置换环 $x,y$ 是否旋转。

- $000$：$p_x\vee q_y=1$。
- $001$：$p_x\oplus q_y=1$。
- $010$：$p_x=1$。
- $011$：不成立。
- $100$：$q_y=1$。
- $101$：不成立。
- $110$：不成立。
- $111$：一定没有贡献。

给 $p,q$ 分配 $0/1$ 在将它们划分入两个集合，要使贡献最大，不妨考虑最小割（补集转化）。

一个套路是对于 $\oplus,\vee,\wedge$ 的贡献（相同或同为某值则减去贡献），将 $p,q$ 划分进两个集合的意义反过来：割掉 $S\to p_i$（保留 $p_i\to T$）表示 $p_i=0$，割掉 $p_i\to T$（保留 $S\to p_i$）表示 $p_i=1$；割掉 $S\to q_j$ 表示 $q_j=1$，割掉 $q_j\to T$ 表示 $q_j=0$。

一个重要的点：要让 $S\to u,u\to T$ 都有 $>0$ 的边权，这样就能保证这两条边恰被割掉一条，也就是 $u$ 恰被划分进一个集合。边权 $=0$：贪心地直接割掉。于是对每个点 $u$ 先连 $(S\to u,1),(u\to T,1)$，贡献和 $+1$，这些贡献会被减掉。

- $p_x=1$：连 $(S\to p_x,1)$，贡献和 $+1$。
- $q_y=1$：连 $(q_y\to T,1)$，贡献和 $+1$。
- $p_x\oplus q_y=1$：要让 $S\to q_y\to p_x\to T,S\to p_x\to q_y\to T$ 的贡献 $-1$，于是连边 $(q_y\to p_x,1),(p_x\to q_y,1)$，贡献和 $+1$。
- $p_x\vee q_y=1$：要让 $S \to q_y \to p_x \to T$ 的贡献 $-1$，于是连边 $(q_y\to p_x,1)$，贡献和 $+1$。

可以叠合重边，容量相加。

点数最多为 $2N+2$，边数（建反边之前）最多为 $6N$。

是单位边权二分图（存疑）。

```cpp
#include <bits/stdc++.h>
#define gc getchar
#define ll long long
using namespace std;
int rd() {
	int x = 0, f = 1; char c = gc();
	while(c < '0' || c > '9') { if(c == '-') f = - 1; c = gc(); }
	while(c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
	return (x * f);
}

namespace Flows {
	const int ND = 200002, ED = 600000;
	const ll inf = ((ll)1000000000) * ((ll)1000000000);
	int nd, s, t, dis[ND + 1]; queue < int > que;
	struct E { int nxt, v; ll fl; }; E e[2 * ED + 2]; int ecnt = 1, hd[ND + 1], cur[ND + 1];
	void AddE(int u, int v, ll fl) { e[++ ecnt] = {hd[u], v, fl}; hd[u] = ecnt; }
	void A(int u, int v, ll fl) { AddE(u, v, fl); AddE(v, u, 0); }
	int Bfs() {
		for(int i = 1; i <= nd; ++ i) dis[i] = nd + 1, cur[i] = hd[i];
		dis[s] = 0; que.push(s);
		while(! que.empty()) {
			int u = que.front(); que.pop();
			for(int i = hd[u]; i; i = e[i].nxt) {
				int v = e[i].v; ll fl = e[i].fl;
				if(fl > 0 && dis[v] == nd + 1) {
					dis[v] = dis[u] + 1;
					que.push(v);
				}
			}
		}
		return dis[t] != nd + 1;
	}
	ll Dfs(int u, ll rfl) {
		if(u == t) return rfl;
		ll res = 0;
		for(int & i = cur[u]; i; i = e[i].nxt) {
			int v = e[i].v; ll fl = e[i].fl;
			if(fl > 0 && dis[v] == dis[u] + 1) {
				ll k = Dfs(v, min(rfl, fl));
				if(k > 0) {
					res += k; rfl -= k; e[i].fl -= k; e[i ^ 1].fl += k;
					if(! rfl) return res;
				}
			}
		}
		if(! res) dis[u] = nd + 1;
		return res;
	}
	ll Dinic() {
		ll res = 0;
		while(Bfs()) {
			while(true) {
				ll k = Dfs(s, inf);
				if(! k) break;
				res += k;
			}
		}
		return res;
	}
	void Init() {
		ecnt = 1;
		for(int i = 1; i <= nd; ++ i) hd[i] = 0;
		nd = 0; s = 0; t = 0;
	}
}
using namespace Flows;

const int N = 100000;
int n, p[N + 1], q[N + 1], colp[N + 1], colq[N + 1], cntp, cntq;
bool vis[N + 1];
int main() {
	n = rd();
	Init();
	for(int i = 1; i <= n; ++ i) p[i] = rd() + 1;
	for(int i = 1; i <= n; ++ i) q[i] = rd() + 1;
	for(int i = 1; i <= n; ++ i) {
		if(vis[i]) continue;
		++ cntp;
		for(int j = i; ! vis[j]; j = p[j]) {
			vis[j] = 1;
			colp[j] = cntp;
		}
	}
	for(int i = 1; i <= n; ++ i) vis[i] = 0;
	for(int i = 1; i <= n; ++ i) {
		if(vis[i]) continue;
		++ cntq;
		for(int j = i; ! vis[j]; j = q[j]) {
			vis[j] = 1;
			colq[j] = cntp + cntq; // cntp +
		}
	}
	nd = cntp + cntq + 2; s = nd - 1; t = nd;
	ll ans = 0;
	for(int i = 1; i <= cntp; ++ i) A(s, i, 1), A(i, t, 1), ++ ans;
	for(int i = 1; i <= cntq; ++ i) A(s, cntp + i, 1), A(cntp + i, t, 1), ++ ans;
	for(int i = 1; i <= n; ++ i) {
		if(p[i] != i && q[i] != i && p[i] != q[i]) A(colq[i], colp[i], 1), ++ ans;
		else if(p[i] != i && q[i] != i && p[i] == q[i]) A(colq[i], colp[i], 1), A(colp[i], colq[i], 1), ++ ans;
		else if(p[i] != i && q[i] == i && p[i] != q[i]) A(s, colp[i], 1), ++ ans;
		else if(p[i] == i && q[i] != i && p[i] != q[i]) A(colq[i], t, 1), ++ ans;
	}
	ans -= Dinic();
	printf("%lld\n", ans);
	return 0;
}
// 参考了题解。
```

---

## 作者：xht (赞：1)

## Two Permutations

### 题意

- 给定两个 $0 \sim n - 1$ 的排列 $p_{0\dots n-1},q_{0\dots n-1}$。
- 构造两个 $0 \sim n - 1$ 的排列 $a_{0\dots n-1}, b_{0\dots n-1}$，使得：
  - $a_i = i$ 或 $a_i = p_i$。
  - $b_i = i$ 或 $b_i = q_i$。
- 要求最大化 $\sum_{i=0}^{n-1} [a_i \ne b_i]$。
- $n \le 10^5$。

### 题解

考虑最小化 $\sum_{i=0}^{n-1}[a_i=b_i]$。

显然每个循环之间相互独立，环内要么不变，要么转一格。

记 $x_i$ 表示 $i$ 在 $p$ 中的环，$v(x_i)$ 表示这个环是否转。

记 $y_i$ 表示 $i$ 在 $q$ 中的环，$v(y_i)$ 表示这个环是否转。

考虑一个 $i$：

1. 若 $p_i = i$，$q_i = i$，则任何情况下都有贡献。
2. 若 $p_i = i$，$q_i \ne i$，则当 $v(y_i) = 0$ 时有贡献。
3. 若 $p_i \ne i$，$q_i = i$，则当 $v(x_i) = 0$ 时有贡献。
4. 若 $p_i \ne i$，$q_i \ne i$，$p_i = q_i$，则当 $v(x_i) = v(y_i)$ 时有贡献。
5. 若 $p_i \ne i$，$q_i \ne i$，$p_i \ne q_i$，则当 $v(x_i) = v(y_i) = 0$ 时有贡献。

发现这是一个[集合划分模型](https://www.xht37.com/二分图与网络流-学习笔记/#lwptoc45)：两个集合 $S,T$，对于一个环 $i$，如果 $v(i) = 0$，则 $i \in S$，否则 $i \in T$。

然而这样并没有办法做，集合划分模型中的约束应为**两个物品不在同一个集合**。

于是考虑修改一下定义：记 $y_i$ 表示 $i$ 在 $q$ 中的环，$v(y_i)$ 表示这个环是否转。

于是重新考虑一个 $i$：

1. 若 $p_i = i$，$q_i = i$，则任何情况下都有贡献，我们直接扔掉这种情况。
2. 若 $p_i = i$，$q_i \ne i$，则当 $v(y_i) = 1$ 时有贡献，连边 $(S, y_i, 1)$。
3. 若 $p_i \ne i$，$q_i = i$，则当 $v(x_i) = 0$ 时有贡献，连边 $(x_i, T, 1)$。
4. 若 $p_i \ne i$，$q_i \ne i$，$p_i = q_i$，则当 $v(x_i) \ne v(y_i)$ 时有贡献，连边 $(x_i, y_i, 1)$，$(y_i, x_i, 1)$。
5. 若 $p_i \ne i$，$q_i \ne i$，$p_i \ne q_i$，则当 $v(x_i) = 0$，$v(y_i) = 1$ 时有贡献，连边 $(x_i,y_i,1)$。

跑最小割即可。

据说时间复杂度是 $\mathcal O(n \sqrt n)$，理由是连出来的图实际上是一张二分图，且容量均为 $1$。

### 代码

```cpp
namespace Dinic {
	const int N = 2e5 + 7, M = 1e6 + 7;
	const ll inf = 1e18;
	int n, S, T, h[N], hi[N], e[M], t[M], tot, d[N];
	ll mxf, f[M];
	inline void add(int x, int y, ll z, int o = 1) {
		e[++tot] = y, f[tot] = z, t[tot] = h[x], h[x] = tot;
		if (o) add(y, x, 0, 0);
	}
	inline bool bfs() {
		for (int i = 1; i <= n; i++) d[i] = 0;
		queue<int> q;
		q.push(S), d[S] = 1;
		while (q.size()) {
			int x = q.front();
			q.pop();
			for (int i = h[x]; i; i = t[i]) {
				int y = e[i];
				ll z = f[i];
				if (d[y] || !z) continue;
				q.push(y), d[y] = d[x] + 1;
				if (y == T) return 1;
			}
		}
		return 0;
	}
	ll dinic(int x, ll nwf) {
		if (x == T) return nwf;
		ll rst = nwf;
		for (int &i = hi[x]; i; i = t[i]) {
			int y = e[i];
			ll z = f[i];
			if (d[y] != d[x] + 1 || !z) continue;
			ll k = dinic(y, min(z, rst));
			if (!k) d[y] = 0;
			else f[i] -= k, f[i^1] += k, rst -= k;
			if (!rst) break;
		}
		return nwf - rst;
	}
	inline void main() {
		while (bfs()) {
			for (int i = 1; i <= n; i++) hi[i] = h[i];
			ll now;
			while ((now = dinic(S, inf))) mxf += now; 
		}
	}
	inline void init(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T, tot = 1, mxf = 0;
		for (int i = 1; i <= n; i++) h[i] = 0;
	}
}

const int N = 1e5 + 7;
int n, p[N], q[N];
int t = 2, S = 1, T = 2, ans;
int x[N], y[N];
bool u[N], v[N];

int main() {
	rd(n), rda(p, n), rda(q, n);
	for (int i = 1; i <= n; i++) ++p[i], ++q[i];
	for (int i = 1; i <= n; i++)
		if (!u[i]) {
			++t;
			int o = i;
			while (!u[o]) u[o] = 1, x[o] = t, o = p[o];
		}
	for (int i = 1; i <= n; i++)
		if (!v[i]) {
			++t;
			int o = i;
			while (!v[o]) v[o] = 1, y[o] = t, o = q[o];
		}
	Dinic::init(t, S, T);
	ans = n;
	for (int i = 1; i <= n; i++) {
		if (p[i] == i && q[i] == i) --ans;
		if (p[i] == i && q[i] != i) Dinic::add(S, y[i], 1);
		if (p[i] != i && q[i] == i) Dinic::add(x[i], T, 1);
		if (p[i] != i && q[i] != i && p[i] == q[i])
			Dinic::add(x[i], y[i], 1), Dinic::add(y[i], x[i], 1);
		if (p[i] != i && q[i] != i && p[i] != q[i])
			Dinic::add(x[i], y[i], 1);
	}
	Dinic::main();
	print(ans - Dinic::mxf);
	return 0;
}
```

---

## 作者：Thunder_S (赞：1)

## Solution

声明：拆环指的是当前位置选择 $i$ 而不是 $P_i$ 或者 $Q_i$。

考虑将 $P$ 中的循环看做一个整体，因为发现，如果对于环上任意一个位置，将其拆掉，可以推导得出整个环都会被拆。$Q$ 同理。

同时根据正难则反的思想，将题目转换成出至少有多少个位置 $A_i=B_i$。

分情况讨论一下什么情况下会产生贡献：

1. 当 $P_i=Q_i=i$ 时，这种情况下无论什么情况 $A_i=B_i$，答案 -1 即可。
2. 当 $P_i=i,Q_i\not=i$ 时，将 $Q_i$ 对应的环拆掉会产生贡献，否则不会。
3. 当 $P_i\not=i,Q_i=i$ 时，同上，将 $P_i$ 对应的环拆掉才会产生贡献，否则不会。
4. 当 $P_i\not=i,Q_i\not=i,P_i\not=Q_i$ 时，同时拆掉两个环才会产生贡献，否则不会。
5. 当 $P_i\not=i,Q_i\not=i,P_i=Q_i$ 时，同时拆或者同时不拆都会产生贡献。

想到这里，网络流就呼之欲出（或许吧）。

将 $P_i$ 对应的环放在左边， $Q_i$ 对应的环放在右边，设源点 $S$ 和汇点 $T$。

根据上述情况连边，连边如下（一一对应）：

1. 不用连边，答案直接减。
2. $Q_i$ 对应的环向 $T$ 连一条流量为 1 的边。
3. $S$ 向 $P_i$ 对应的环连一条流量为 1 的边。
4. $Q_i$ 对应的环向 $P_i$ 对应的环连流量为 1 的边。（避免出现产生一些不合法的答案）
5. $P_i$ 对应的环向 $Q_i$ 对应的环连流量为 1 的边，$Q_i$ 对应的环也向 $P_i$ 对应的环连流量为 1 的边。（两条）

然后愉快的套上 $\mathcal{Dinic}$ 就好了。

## Code

```cpp
#include<queue>
#include<cstdio>
#define N 100005
#define inf 2147483647
using namespace std;
struct node
{
	int to,head,next,flow;
}a[N<<2];
int n,S,T,tot=1,cnt,ans,p[N],q[N],r1[N],r2[N],cur[N],deep[N];
bool bj1[N],bj2[N];
void getring1(int x)
{
	++cnt;
	while (!bj1[x]) r1[x]=cnt,bj1[x]=true,x=p[x];
}
void getring2(int x)
{
	++cnt;
	while (!bj2[x]) r2[x]=cnt,bj2[x]=true,x=q[x];
}
void add(int x,int y,int z)
{
	a[++tot].to=y;a[tot].flow=z;a[tot].next=a[x].head;a[x].head=tot;
	a[++tot].to=x;a[tot].flow=0;a[tot].next=a[y].head;a[y].head=tot;
}
bool bfs()
{
	queue<int> q;
	for (int i=1;i<=cnt;++i)
		deep[i]=0;
	q.push(S);deep[S]=1;
	while (!q.empty())
	{
		int x=q.front();q.pop();
		for (int i=a[x].head;i;i=a[i].next)
		{
			int v=a[i].to;
			if (!deep[v]&&a[i].flow) deep[v]=deep[x]+1,q.push(v);
		}
	}
	return deep[T]!=0;
}
int dfs(int x,int fl)
{
	if (x==T) return fl;
	int res=fl;
	for (int i=cur[x];i;i=a[i].next)
	{
		int v=a[i].to;
		cur[x]=i;
		if (deep[v]==deep[x]+1&&a[i].flow)
		{
			int f=dfs(v,min(res,a[i].flow));
			a[i].flow-=f;a[i^1].flow+=f;res-=f;
			if (!res) break;
		}
	} 
	return fl-res;
} 
int dinic()
{
	int res=0;
	while (bfs())
	{
		for (int i=1;i<=cnt;++i)
			cur[i]=a[i].head;
		res+=dfs(S,inf);
	}
	return res;
}
int main()
{
	freopen("per.in","r",stdin);
	freopen("per.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&p[i]),++p[i];
	for (int i=1;i<=n;++i)
		scanf("%d",&q[i]),++q[i];
	for (int i=1;i<=n;++i)
		if (!bj1[i])
			getring1(i);
	for (int i=1;i<=n;++i)
		if (!bj2[i])
			getring2(i);
	S=++cnt;T=++cnt;
	ans=n;
	for (int i=1;i<=n;++i)
	{
		if (p[i]==q[i]&&p[i]==i) ans--;
		else if (q[i]==i) add(S,r1[i],1);
		else if (p[i]==i) add(r2[i],T,1);
		else if (p[i]==q[i]) add(r2[i],r1[i],1),add(r1[i],r2[i],1);
		else add(r2[i],r1[i],1);
	}
	printf("%d\n",ans-dinic());
	return 0;	
} 
```



---

## 作者：YangJZHello (赞：0)

# 题意
给定两个 $1\cdots N$ 排列 $P,Q$。要求构造两个 $1\cdots N$ 排列 $A,B$，满足
* $A_i=P_i$ 或 $A_i=i$；
* $B_i=Q_i$ 或 $B_i=i$。

最大化并输出 $\sum_{i=1}^N[A_i\neq B_i]$。

# 数据范围
$1\leq N\leq10^5$。

# 思路
首先将排列 $P,Q$ 分解为循环。考虑 $A$ 的构造。由于 $A_i$ 只有 $P_i$ 或 $i$ 两种取值，分类讨论：
* 当 $A_i=i$ 时，设与 $P_i$ 同处一个循环且在 $P_i$ 前一个位置的元素为 $P_j$。由于 $A_j$ 的取值只能是 $P_j$ 或 $j$，而 $P_j=i$，为了维持循环中元素不重复， $A_j$ 只能取 $j$。以此类推，可以得到：任意与 $P_i$ 同处一个循环中的元素 $P_x$，其下标对应的元素 $A_x=x$。
* 当 $A_i=P_i$ 时，设与 $P_i$ 同处一个循环且在 $P_i$ 后一个位置的元素为 $P_j$。由于 $A_j$ 的取值只能是 $P_j$ 或 $j$，而 $P_i=j$，为了维持循环中的元素不重复，$A_j$ 只能取 $P_j$。以此类推，可以得到：任意与 $P_i$ 同处一个循环中的元素 $P_x$，其下标对应的元素 $A_x=P_x$。

即对于排列 $P$ 中的一个循环，要么不改变这个循环，要么将这个循环分裂成若干个自环，即能构成满足条件的 $A$。

由 $Q$ 构造 $B$ 同理。

在排列 $P,Q$ 中各选取有一个共同元素 $i$ 的循环 $p,q$，继续分讨：
* $P_i=Q_i=i$ 时，不管循环 $p,q$ 是否分裂，都会对答案产生 $-1$ 的贡献；
* $P_i=i,Q_i\neq i$ 时，若循环 $q$ 分裂，会对答案产生 $-1$ 的贡献，否则不产生贡献；
* $P_i\neq i,Q_i=i$ 时，若循环 $p$ 分裂，会对答案产生 $-1$ 的贡献，否则不产生贡献；
* $P_i\neq i,Q_i\neq i$ 且 $P_i\neq Q_i$ 时，若循环 $p,q$ 同时分裂，会对答案产生 $-1$ 的贡献，否则不产生贡献；
* $P_i\neq i,Q_i\neq i$ 且 $P_i=Q_i$ 时，若循环 $p,q$ 同时分裂或同时不分裂，会对答案产生 $-1$ 的贡献，否则不产生贡献。

自然想到将贡献的绝对值转化为网络的割，然后求最小割即可。由于产生贡献的情况有以下几种：
* 循环 $p$ 分裂；
* 循环 $q$ 分裂；
* 循环 $p,q$ 同时分裂；
* 循环 $p,q$ 同时不分裂。

思考 $s,t$ 的连通点具有什么性质可以使边的断裂对应以上的情况。循环 $p,q$ 的单独分裂是一个一元事件，考虑将 $p,q$ 与 $s$ 或 $t$ 连边；循环 $p,q$ 的同时分裂/不分裂是一个二元事件，考虑将 $p$ 与 $q$ 连边，断边代表了同时分裂/不分裂的情况，那么对于 $p,q$，其与 $s$ 还是 $t$ 连接所对应的情况应该是相反的。

所以可以构造源点 $s$ 可到达的所有点为 $P$ 中分裂的循环和 $Q$ 中不分裂的循环，可到达汇点 $t$ 的所有点为 $P$ 中不分裂的循环和 $Q$ 中分裂的循环。对于元素 $i$：
* $P_i=Q_i=i$ 时，不做处理；
* $P_i=i,Q_i\neq i$ 时，连接 $s$ 到 $q$ 的单位容量边；
* $P_i\neq i,Q_i=i$ 时，连接 $i$ 到 $p$ 的单位容量边；
* $P_i\neq i,Q_i\neq i$ 且 $P_i\neq Q_i$ 时，连接 $p$ 到 $q$ 的单位容量边；
* $P_i\neq i,Q_i\neq i$ 且 $P_i=Q_i$ 时，连接 $q$ 到 $p$ 和 $p$ 到 $q$ 的单位容量边。

那么最终答案为 $N-\sum_{i=1}^N[P_i=Q_i=i]-网络的最小割$。

由于不会出现 $p\to p,q\to q$ 式的连边，所以构建的网络除去 $s,t$ 外就是一个二分图，用 Dinic 算法求最小割的时间复杂度为 $\mathcal O(N\sqrt N)$。

# 参考代码
[评测记录](https://atcoder.jp/contests/agc038/submissions/54884288)。

---

## 作者：Corzica (赞：0)

非常好集合划分模型，让我交了好多次。

显然，这种排列问题可以建虚拟图然后连边，我们先找到虚拟图上每一个点所在的环。

对于这些环而言，决策只有两种。要么每个点选自身的数，要么每一个点选下一个数。

最大化 $A_i \neq B_i$ 的数量相当于最小化 $A_i = B_i$ 的数量。

显然，问题变成了一个网络流中的集合划分模型，要求代价最小。我们让在 $A$ 中的环向 $S$ 连边代表选自身，向 $T$ 连边代表选下一个数。在 $B$ 中的环则相反。

枚举每一个位置，记 $A_i$ 所在环为 $a_i$，$B_i$ 所在环为 $b_i$，分类讨论：

- $P_i=Q_i=i$，答案必定增大 $1$。

- $P_i=i,Q_i \neq i$，当 $b_i$ 自连，即 $b_i$ 不连下一个数的时候，答案加 $1$。让 $S$ 向 $b_i$ 连权值为 $1$ 的边。

- $Q_i=i,P_i \neq i$，当 $a_i$ 自连，即 $a_i$ 不连下一个数的时候，答案加 $1$。让 $a_i$ 向 $T$ 连权值为 $1$ 的边。

- $Q_i,P_i \neq i$ 且 $Q_i=P_i$，当 $a_i,b_i$ 集合不同时，答案加 $1$，让 $a_i$ 和 $b_i$ 互相连一条权值为 $1$ 的边。

- $Q_i,P_i \neq i$ 且 $Q_i \neq P_i$，当 $a_i$ 与 $S$ 相连， $b_i$ 与 $T$ 相连时答案加 $1$，让 $a_i$ 向$b_i$ 连一条权值为 $1$ 的边。

直接跑最小割即可，发现是二分图，复杂度为 $n^{1.5}$。

代码：

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n, a[100005], b[100005], head[401005], nxt[2100005], cnt, s, t,  to[2100005], w[2100005], cur[401005], d[401005], ccnt, maxl, name[100005], nname[100005];
inline void add(int p, int q, int ww) {
	nxt[++ccnt] = head[p];
	to[ccnt] = q;
	w[ccnt] = ww;
	head[p] = ccnt;
}
inline bool bfs() {
	static queue<int> que;
	while (que.size()) que.pop();
	for (int i = 1; i <= cnt; i++) {
		d[i] = 0x3f3f3f3f;
		cur[i] = head[i];
	}
	d[s] = 0;
	que.push(s);
	static int u;
	while (que.size()) {
		u = que.front();
		que.pop();
		for (int i = head[u]; i; i = nxt[i]) {
			if (d[to[i]] == 0x3f3f3f3f && w[i]) {
				que.push(to[i]);
				d[to[i]] = d[u] + 1;
			}
		}
	}
	return (d[t] != 0x3f3f3f3f);
}
inline int dfs(int p, int q) {
	if (p == t) {
		maxl += q;
		return q;
	}
	int op = 0, r;
	for (int &i = cur[p]; i; i = nxt[i]) {
		if (w[i] && d[to[i]] == d[p] + 1) {
			r = dfs(to[i], min(w[i], q));
			op += r;
			q -= r;
			w[i] -= r;
			w[i ^ 1] += r;
			if (q == 0) break;
		}
	}
	return op;
}
int ans = 0;
inline int Dinic() {
	maxl = 0;
	while (bfs()) dfs(s, 0x3f3f3f3f);
	return maxl;
}
inline void paint(int p, int q) {
	name[p] = q;
	if (!name[a[p]]) paint(a[p], q);
}
inline void ppaint(int p, int q) {
	nname[p] = q;
	if (!nname[b[p]]) ppaint(b[p], q);
}
signed main() {
	ccnt = 1;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i]++;
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		b[i]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!name[i]) paint(i, ++cnt);
	}
	for (int i = 1; i <= n; i++) {
		if (!nname[i]) ppaint(i, ++cnt);
	}
	s = ++cnt, t = ++cnt;
	bool flg, fflg;
	for (int i = 1; i <= n; i++) {
		flg = (a[i] == i), fflg = (b[i] == i);
		if (flg && fflg) {
			ans++;
		} else if (flg) {
			add( s, nname[i], 1);
			add(nname[i], s,  0);
		} else if (fflg) {
			add(t, name[i], 0);
			add(name[i], t,  1);
		} else {
			if (a[i] == b[i]) {
				add(name[i], nname[i], 1);
				add(nname[i], name[i], 1);
			} else {
				add(nname[i], name[i], 0);
				add(name[i], nname[i], 1);
			}
		}
	}
	ans += Dinic();
	cout << n - ans;
}
```

---

