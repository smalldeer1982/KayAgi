# [ARC117D] Miracle Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc117/tasks/arc117_d

$ N $ 頂点の木があり、頂点には $ 1,\ 2,\ \dots,\ N $ と番号が振られています。$ i $ 番目 $ (1\ \leq\ i\ \leq\ N-1) $ の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

木を見つけた E869120 君は、$ N $ 個の頂点それぞれに整数を書き込み、square1001 君を驚かせようとしています。彼を驚かせるためには、頂点 $ i $ に書かれた整数を $ E_i $ とするとき、次の条件を満たす必要があります。

> **条件1** $ E_i\ \geq\ 1 $ $ (1\ \leq\ i\ \leq\ N) $ を満たす。  
> **条件2** すべての組 $ (i,\ j) $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $ について、$ |E_i\ -\ E_j|\ \geq\ dist(i,\ j) $ を満たす。  
> **条件3** 条件 1・条件 2 を満たす中で、$ \max(E_1,\ E_2,\ \dots,\ E_N) $ の値が最小になる。

ただし、$ dist(i,\ j) $ は次の値を指します。

- 頂点 $ i $ から $ j $ への単純パス（同じ頂点を $ 2 $ 度通らない経路）の長さ。
- つまり、単純パスを $ q_0\ \to\ q_1\ \to\ q_2\ \to\ \cdots\ \to\ q_L $（$ q_0\ =\ i,\ q_L\ =\ j $）とするときの $ L $ の値。

square1001 君を驚かせるような整数の書き方を $ 1 $ つ構成してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- 与えられるグラフは木である
- 入力はすべて整数

### Sample Explanation 1

頂点 $ 1 $ に整数 $ 2 $ を、頂点 $ 2 $ に整数 $ 1 $ を書き込んだ場合、$ dist(1,\ 2)\ =\ 1 $、$ |E_1\ -\ E_2|\ =\ 1 $ であるため、問題文中の条件 2 を満たします。 その他の条件もすべて満たすため、この書き込み方は square1001 君を驚かせることができます。 他にも、$ (E_1,\ E_2)\ =\ (1,\ 2) $ は正解となります。

### Sample Explanation 2

他にも、$ (E_1,\ E_2,\ E_3,\ E_4)\ =\ (2,\ 3,\ 4,\ 1) $ は正解となります。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
2 1```

## 样例 #2

### 输入

```
4
1 2
1 4
2 3```

### 输出

```
3 2 1 4```

# 题解

## 作者：EuphoricStar (赞：14)

第一步就没想到![](//图.tk/7)

可以考虑化简限制。设所有点按 $E_i$ 从小到大排序后顺序是 $p_1,p_2,...,p_n$。发现只需满足 $E_{p_{i+1}} - E_{p_i} \ge \operatorname{dis}(p_i, p_{i+1})$。证明是对于任意 $i < j < k$，若 $p_i,p_j$ 和 $p_j,p_k$ 均满足限制，那么 $E_{p_k} - E_{p_i} = E_{p_k} - E_{p_j} + E_{p_j} - E_{p_i} \ge \operatorname{dis}(p_k, p_j) + \operatorname{dis}(p_j, p_i) \ge \operatorname{dis}(p_k, p_i)$。

到这里显然每个不等式都可以取等，即 $E_{p_{i+1}} = E_{p_i} + \operatorname{dis}(p_i, p_{i+1})$，$E_{p_n} = 1 + \sum\limits_{i=1}^{n-1} \operatorname{dis}(p_i, p_{i+1})$。则我们需要找到一个排列 $p$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{dis}(p_i, p_{i+1})$ 最小。

注意到 $\sum\limits_{i=1}^{n-1} \operatorname{dis}(p_i, p_{i+1}) + \operatorname{dis}(p_n, p_1)$ 最小值为 $2(n-1)$，这是因为每条边至少经过两次。取到下界也很简单，$p$ 取 dfs 序即可。

现在就变成了要最大化 $\operatorname{dis}(p_1, p_n)$。$p_1,p_n$ 取直径端点即可。

[code](https://atcoder.jp/contests/arc117/submissions/41078733)

---

## 作者：Creator_157 (赞：5)

## 题意

给定一棵 $n$ 个节点的树，要求构造出一个点权序列 $E$，满足以下三个条件：

1.所有 $E_i\ge 1(1\le i\le n)$。

2.对于任意一组 $(i,j)(1 ≤ i < j ≤ N)$，使 $|E_i-E_j|\ge dist(i,j)$，$dist$ 即树上两点距离。

3.使 $E$ 中的最大值最小。

---

## 题解

考虑一种构造方式：从一个点开始进行 $\text{DFS}$，同时维护一个当前要填的数 $cnt$，每次经过一条边就 ++$cnt$（回溯时也一样，因为要使回溯到的点与他的儿子也满足第二条限制）。

这样保证了对于每一个点，它能到达的点至少与它满足第二条限制。

![](https://cdn.luogu.com.cn/upload/image_hosting/nl9dxy9g.png)

但是这可能导致不满足第三条限制。

发现：最终最大的标号是经过的边的次数 $+1$，并且不一定要回到根。

![](https://cdn.luogu.com.cn/upload/image_hosting/7k2xk7j6.png)

所以我们可以利用一个经典套路优化以上策略，选定直径作为只经过一次的边（不用回溯），以直径的一端为根进行编号，到另一端就结束。这样使得最大的编号（总边数 $\times 2-$ 没有回溯的边数）最小。

---

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re int
#define Bessie signed
int read()
{
    int A = 0, FL = 1;
    char CH = getchar();
    while(CH < '0' || CH > '9')
        FL = (CH == '-') ? -1 : 1, CH = getchar();
    while(CH >= '0' && CH <= '9')
        A = (A << 3) + (A << 1) + (CH ^ '0'), CH = getchar();
    return A * FL;
}
void ot(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x >= 10)
        ot(x / 10);
    putchar((x % 10) | '0');
}
#define pc_ (putchar(' '))
#define pc_n (putchar('\n'))
const int CTR = 2e5 + 7;
int n;
vector<int> G[CTR];
int p, q;
int dis[CTR];
void dfs1(int x, int f)
{
    dis[x] = dis[f] + 1;
    (dis[x] > dis[p]) && (p = x);
    for(re v : G[x]) if(v != f) dfs1(v, x);
}
bool fl[CTR];
void dfs2(int x, int f)
{
    if(x == q) fl[x] = 1;
    for(re v : G[x]) if(v != f) dfs2(v, x), fl[x] |= fl[v];
}
int tot;
int ans[CTR];
void dfs3(int x, int f)
{
    ans[x] = ++tot;
    for(re v : G[x]) if(v != f && !fl[v]) dfs3(v, x), ans[x] = ++tot;
    for(re v : G[x]) if(v != f && fl[v]) dfs3(v, x);
}
Bessie main()
{
    n = read();
    for(re i = 1, u, v; i < n; ++i)
        u = read(), v = read(), G[u].push_back(v), G[v].push_back(u);
    dfs1(1, 0);
    q = p;
    dfs1(p, 0);
    dfs2(p, 0);
    dfs3(p, 0);
    for(re i = 1; i <= n; ++i) ot(ans[i]),pc_;
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：4)

## 题意
给定一棵 $n$ 个节点的树，要求构造出一个点权序列 $E$，满足以下三个条件：

1.所有 $E_i\ge 1(1\le i\le n)$。

2.对于任意一组 $(i,j)(1 ≤ i < j ≤ N)$，使 $|E_i-E_j|\ge \operatorname{dist}(i,j)$，$\operatorname{dist}$ 即树上两点距离。

3.使 $E$ 中的最大值最小。

## 题解
首先考虑前两个条件，设存在长度为 $n$ 排列 $p$，使得 $\forall i \in \left[1, n\right) E_{p_i} < E_{p_{i + 1}} \land E_{p_{i + 1}} - E_{p_i} \ge \operatorname{dist}\left(p_i, p_{i + 1}\right)$。因为对于树上任意三点 $i, j, k$，都有 
$$\operatorname{dist}(i, j) \le \operatorname{dist}(i, k) + \operatorname{dist}(j, k)$$
所以对于任意 $1 \le i < k < j \le n$，有 
$$\operatorname{dist}(p_i, p_j) \le \operatorname{dist}(p_i, p_k) + \operatorname{dist}(p_j, p_k) \le E_{p_k} - E_{p_i} + E{p_j} - E_{p_k} = E_{p_j} - E_{p_i}$$

因此可以得到一个满足前两个要求的构造方法，对于任意 $1 \le i < n$，构造 $E_{p_i},E_{p_{i + 1}}$ 使得 $E_{p_{i + 1}} - E_{p_i} = \operatorname{dist}(p_i, p_{i + 1})$。

接下来考虑第三个要求，对于排列 $p$，序列 $E_i$ 的最大值为 
$$\sum\limits_{i = 1}^{n - 1} \left(E_{p_{i + 1}} - E_{p_i}\right) + 1= \sum\limits_{i = 1}^{n - 1} \operatorname{dist}(p_{i + 1}, p_i) + 1$$

考虑到 $\sum\limits_{i = 1}^{n - 1} \operatorname{dist}(p_{i + 1}, p_i) + \operatorname{dist}(p_1, p_n) + 1$ 的最小值为 $2\left(n - 1\right) + 1$，即欧拉回路的长度，此时每个边都被经历两次，考虑在此基础上最大化 $\operatorname{dist}(p_1, p_n)$，显然满足 $\operatorname{dist}(x, y)$ 最大的 $x, y$ 为树的直径的两个端点。

这样我们就得到了最终的构造方法：求出树的直径，然后从直径的一个端点进行欧拉环游，其中对于每个经过的节点，如果存在一条边在树的直径上，那么最后经过这条边。这样在到达直径的另一个端点时，可以保证所有节点均已访问过，故可以直接结束递归。

## Code
```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

valueType N;
ValueMatrix G;
ValueVector depth;

valueType dfs(valueType x, valueType from) {
    valueType maxDepth = x;

    depth[x] = depth[from] + 1;

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        valueType const result = dfs(iter, x);

        if (depth[result] > depth[maxDepth])
            maxDepth = result;
    }

    return maxDepth;
}

bitset tag;

bool addTag(valueType x, valueType from, const valueType &target) {
    if (x == target)
        return tag[x] = true;

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        if (addTag(iter, x, target))
            tag[x] = true;
    }

    return tag[x];
}

ValueVector ans;
valueType dfsCount = 0;

void calc(valueType x, valueType from) {
    ans[x] = ++dfsCount;

    valueType end = -1;

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        if (tag[iter]) {
            end = iter;

            continue;
        }

        calc(iter, x);

        ++dfsCount;
    }

    if (end != -1) {
        calc(end, x);

        ++dfsCount;
    }
}

int main() {
    std::cin >> N;

    G.resize(N + 1);
    depth.resize(N + 1, 0);

    for (valueType i = 1; i < N; ++i) {
        valueType a, b;

        std::cin >> a >> b;

        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    std::fill(depth.begin(), depth.end(), 0);
    valueType const A = dfs(1, 0);
    std::fill(depth.begin(), depth.end(), 0);
    valueType const B = dfs(A, 0);

    tag.resize(N + 1, false);

    addTag(A, 0, B);

    ans.resize(N + 1, 0);

    calc(A, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cout << ans[i] << " ";

    std::cout << std::endl;

    return 0;
}
```

---

## 作者：myyyIisq2R (赞：3)

构造题我们可以从样例入手。这里使用第二个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ljdl2gc.png)

我们发现填数的顺序是从一个子树的底部向根，再填向下一个子树。考虑到形式过于单一，我们将图进行扩展。

![](https://cdn.luogu.com.cn/upload/image_hosting/exuarawc.png)

如果给 $1$ 添加一个父节点，那么再向上填的时候，可以手搓出来，新点应该填上 $6$。因为要在与 $3$ 节点的限制关系中满足和它的点权差为 $2$ ，要递增还要取最小。接下来思考它究竟是怎么填上的，其实是我们从 $3$ 跳到父亲 $1$ 节点后再向上跳，这个过程不断累计计数器使得 $6$ 节点处填 $6$。这时我们发现 $1$ 节点处既可以填原有的 $3$ 也可以覆盖上新序 $5$，因为我们构造的限制条件在最大值最小，和点权差不小于两点距离。在满足最大值不变时，其他点只需要满足要求即可。 

这时我们便得到了一种构造方法，但我们的过程是从下往上，不容易实现。便可以从上往下，按照 $\text{dfs}$ 的顺序填编号（因为保证了两两差的绝对值不变，且最大最小值不变）。我们惊喜地发现，这就是欧拉序。

而我们从上往下遍历的过程中，必然会回溯。回溯的过程中是需要不断累计计数器的。那么需要让最终累计到的值最小，必然要保证回溯的过程越短越好。这时就需要保证直径不能回溯，当且仅当不回溯直径，点权最大值取到最小。那么我们就找到树的直径，从直径的一个端点开始 $\text{dfs}$，遍历子树的过程中，将在直径中的点拉出来，每次遍历的时候最后遍历就好了。

码太丑不好看。

```cpp

void add(int u,int v)
{
	e[++Ecnt].nxt = head[u];
	e[Ecnt].to = v;
	head[u] = Ecnt;
}
int side{};
int maxn{};
int d[N];
void dfs1(int u,int fa)
{
	d[u] = d[fa]+1;
	if(d[u] > maxn) maxn = d[u],side = u;
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v =e[i].to;
		if(v == fa) continue;
		dfs1(v,u);
	}
}
void dfs2(int u,int fa)
{
	d[u] = d[fa]+1;
	if(d[u] > maxn) maxn = d[u],side = u;
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v =e[i].to;
		if(v == fa) continue;
		dfs2(v,u);
	}
}
int num[N];
int cnt{};
int n;
int ed;

bool fnd = false;
bool zj[N];
void dfs4(int u,int fa)
{
	ed = u;
	int nd{};
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		if(zj[v]) {nd = v;continue;}
		dfs4(v,u);
	}
	if(nd) dfs4(nd,u);
}
bool ok = false;
void dfs3(int u,int fa)
{
	if(!ok)num[u] = ++cnt;
	if(u == ed) ok = true;
	int nd{};
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		if(zj[v]) {nd = v;continue;}
		dfs3(v,u);
		if(!ok)num[u] = ++cnt;
	}
	if(nd) 
	{
		dfs3(nd,u);
		if(!ok) num[u] = ++cnt; 
	}
}
void dfs5(int u,int fa,int nd)
{
	if(u == nd){fnd = true;zj[u] = true;return;}
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs5(v,u,nd);
		if(fnd) {zj[u] = true;return;} 
	}
}
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	#endif
	n = read();
	for(int i{1};i<n;i++)
	{
		int u = read(),v = read();
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	memset(d,0,sizeof(d));
	maxn = 0;
	int l = side;
	dfs2(side,0);
	int r = side;
	dfs5(l,0,r);
	dfs4(l,0),dfs3(l,0);
	int minn = LONG_LONG_MAX;
	for(int i{1};i<=n;i++) minn = min(minn,num[i]);
	for(int i{1};i<=n;i++) writek(num[i]-minn+1);
	
	return 0;
}

```

---

## 作者：Rosabel (赞：2)

其实一开始就想到了结论，但是由于一直不会证明不敢写。后面灵机一动想到了如何证明。

由于 $\mid E_i-E_j\mid\ge dis(i,j)$，意味着 $E_i$ 互不相同（显然不存在 $i\neq j$ 使得 $dis(i,j)\le 0$）。那么假设从 $1$ 到 $n$ 的排列 $p_i$ 满足 $\forall i\in[1,n),E_{p_i}\lt E_{p_{i+1}}$，这样的排列对于一个合法的 $E$ 构造一定存在且唯一。假设 $i\lt j\lt k$，根据最短路的三角不等式：
$$
dis(p_i,p_k)\le dis(p_i,p_j)+dis(p_j,p_k)
$$
再结合 $\mid E_i-E_j\mid\ge dis(i,j)$，若满足
$$
\mid E_{p_i}-E_{p_j}\mid=E_{p_j}-E_{p_i}\ge dis(p_i,p_j),\mid E_{p_j}-E_{p_k}\mid=E_{p_k}-E_{p_j}\ge dis(p_j,p_k)
$$
则必然有
$$
\mid E_{p_i}-E_{p_k}\mid=E_{p_k}-E_{p_i}=(E_{p_k}-E_{p_j})+(E_{p_j}-E_{p_i})\ge dis(p_j,p_k)+dis(p_i,p_j)\ge dis(p_i,p_k)
$$
归纳一下，只要满足 $\forall i\in[1,n),E_{p_{i-1}}-E_{p_i}\ge dis(p_i,p_j)$ 的构造就是合法的。为了要最小化 $\max E_i$，即最小化 $E_{p_n}$，那么当且仅当 $n-1$ 个不等式全部取等时有最小解。考虑 $dis(p_i,p_j)$ 在图上的实际含义，相当于根据 $p$ 数组遍历 $n$ 个点的距离和。显然有按照 DFS 序遍历最优。DFS 序遍历相当于除了 $p_n\to p_1$ 的路径上所有边贡献 $1$，其余边贡献 $2$。式子转换为：
$$
\min_p2n-2-dis(p_n,p_1)
$$
等价于最大化 $dis(p_n,p_1)$。即 $p_1$ 和 $p_n$ 是直径的两个端点。

[code](https://atcoder.jp/contests/arc117/submissions/57395446)

---

## 作者：Hanzelic (赞：2)

### [原题链接](https://www.luogu.com.cn/problem/AT_arc117_d) 
很有思维含量的一道题。

先说明如何验证 $E$ 是否合法：将所有点按照 $E$ 的大小进行排序，若能保证对于所有的 $1\le i\le n$，有 $E_{i+1}-E_i\ge dis(p_{i+1},p_i)$，则能说明 $E$ 全都合法。  
证明：若有 $\begin{cases}E_{i+1}-E_i\ge dis(p_{i+1},p_i)\\E_{i}-E_{i-1}\ge dis(p_i,p_{i-1})\end{cases}$，则将两式相加得到 
$$E_{i+1}-E_{i-1}\ge dis(p_{i+1},p_i)+dis(p_i,p_{i-1})\ge dis(p_{i+1},p_{i-1})$$
显然符合要求。  

这个题要求 $E_n$ 最小，那么肯定是要让 $E_i=E_{i-1}+dis(p_{i-1},p_i)$ 的，所以我们可以递推这个式子得到：$E_n=(E_1=1)+\sum\limits_{i=1}^{n-1}dis(p_i,p_{i+1})$。
  
从式子可以看出，我们需要让 $\sum\limits_{i=1}^{n-1}dis(p_i,p_{i+1})$ 尽可能的小，这就需要我们让回溯的距离尽可能的少，通过画图可以知道如果从根开始到根结束遍历一遍整个树，最少每一条边是要走两遍的，因为要算上回溯到父节点再到子节点的距离，可是我们不一定要到根结束，只需要走到最后一个点就可以停止回溯了，也就是说，我们可以找到**最长的一条边，让它只需要经过一次**，最长的边很明显就是直径。  

那么 $E_n$ 也就最终转换成了总边数乘二减去一遍直径的长度，每个点的 $E$ 找到直径的一个端点后用欧拉序表示就行了。我们选择用树链剖分，优先走轻链的部分，从而保证重链也就是直径只被经过了一次。

### 代码
```cpp
#include<bits/stdc++.h>
#define M 200005
using namespace std;
int n,m,a,b,c,cnt,tot,maxdep,now;
int head[M],son[M],in[M],out[M],dep[M];
struct edg{
	int to,next;
}edge[M<<1];
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x,int fat){
	dep[x]=dep[fat]+1;
	if(maxdep<dep[x]){
		maxdep=dep[x];
		now=x;
	}
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].to;
		if(y==fat)continue;
		dfs(y,x);
	}
}
void dfs1(int x,int fat){
	dep[x]=0;
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].to;
		if(y==fat)continue;
		dfs1(y,x);
		dep[x]=max(dep[x],dep[y]+1);
		if(dep[y]>dep[son[x]])son[x]=y;
	}
}
void dfs2(int x,int fat){
	in[x]=++tot;
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].to;
		if(y==fat||y==son[x])continue;
		dfs2(y,x);
	}
	if(son[x])dfs2(son[x],x);
	++tot;
}
int main(){
	scanf("%d",&n);
	for(int q=1;q<n;q++){
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	dfs(1,0); 
	dfs1(now,0);
	dfs2(now,0);
	for(int q=1;q<=n;q++){
		printf("%d ",in[q]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：WorldMachine (赞：1)

先满足前两个要求，将点按照 $E$ 从小到大排列为 $p$。

树是度量空间，有 $\text{dis}(x,z)+\text{dis}(z,y)\ge\text{dis}(x,y)$，故有：
$$
\text{dis}(p_x,p_y)\le\text{dis}(p_x,p_z)+\text{dis}(p_z,p_y)\le E_{p_x}-E_{p_z}+E_{p_z}-E_{p_y}=E_{p_x}-E_{p_y}
$$
故只需要令 $E_{p_{i+1}}-E_{p_i}=\text{dis}(p_i,p_{i+1})$ 即可。考虑什么样的 $p$ 是最优的。最大值为 $p_n=\sum\limits_{i=1}^{n-1}\text{dis}(p_i,p_{i+1})+1$。由于 $\sum\limits_{i=1}^{n-1}\text{dis}(p_i,p_{i+1})+\text{dis}(p_n,p_1)$ 有最小值 $2(n-1)$（取 $p$ 为一 dfs 序），要让后者尽可能大，则 $p_1,p_n$ 取直径的两个端点即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, d[N], r, s[N], t, e[N]; vector<int> G[N];
void dfs1(int u, int f) { d[u] = d[f] + 1; if (d[u] > d[r]) r = u; for (int v : G[u]) if (v != f) dfs1(v, u); }
void dfs2(int u, int f) { for (int v : G[u]) if (v != f) { dfs2(v, u), d[u] = max(d[u], d[v] + 1); if (d[v] > d[s[u]]) s[u] = v; } }
void dfs3(int u, int f) { e[u] = ++t; for (int v : G[u]) if (v != f && v != s[u]) dfs3(v, u); if (s[u]) dfs3(s[u], u); t++; }
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
	dfs1(1, 0), memset(d, 0, sizeof(d)), dfs2(r, 0), dfs3(r, 0);
	for (int i = 1; i <= n; i++) printf("%d ", e[i]);
}
```

---

## 作者：TempestMiku (赞：1)

# [AT_arc117_d [ARC117D] Miracle Tree](https://www.luogu.com.cn/problem/AT_arc117_d)

## 题意

给定一棵 $n$ 个节点的树，要求构造出一个点权序列 $E$，满足以下三个条件：

1.所有 $E_i\ge 1(1\le i\le n)$。

2.对于任意一组 $(i,j)(1 ≤ i < j ≤ N)$，使 $|E_i-E_j|\ge dist(i,j)$，$dist$ 即树上两点距离。

3.使 $E$ 中的最大值最小。

## 思路

假设 $p_1,p_2,p_3,\dots,p_n$ 为 $e_1,e_2,e_3,\dots,e_n$ 从小到大排完序的编号，要满足条件 $2$ 的话，就是 $e_{p_i}-e_{p_{i-1}} \ge dist(p_i,p_{i-1})$，设为 $1$ 式

同理，满足 $e_{p_{i-1}}-e_{p_{i-2}} \ge dist(p_{i-1},p_{i-2})$，设为 $2$ 式。

我们将 $1$ 式加上 $2$ 式，得到：
$$e_{p_i}-e_{p_{i-2}}\ge dist(p_i,p_{i-1})+dist(p_{i-1},p_{i-2})$$
又因为 $dist(p_i,p_{i-1})+dist(p_{i-1},p_{i-2})\ge dist(p_i,p_{i-2})$

所以：
$$e_{p_i}-e_{p_{i-2}}\ge dist(p_i,p_{i-2})$$
当不等式取等时答案最小。
$$e_{p_{i+1}}=e_{p_i}+dist({p_i},{p_{i+1}})$$
$$e_{p_n}=1+\sum_{i=1}^{n-1}dist({p_i},{p_{i+1}})$$

又因为：
$\sum_{i=1}^{n-1}dist({p_i},{p_{i+1}})+dist(p_{n},p_1)$的最小值是 $2(n-1)$，

![](https://cdn.luogu.com.cn/upload/image_hosting/7wesvqzb.png)

如图，我们现在 通过了 $(1,2),(2,3),(3,4),(4,5),(5,1)$，恰好每个边都经过了两遍，经过路径恰好是 $2(n-1)$。红线是向下搜索，绿线是向上回溯。如果去掉 $dist(p_{n},p_{1})$ 的贡献，相当于在 $2(n-1)$ 的基础上去掉 $dist(p_{n},p_{1})$。所以想要答案最小，去掉的 $dist(p_{n},p_{1})$ 应该是最大的。

我们大概模拟一下样例，会发现最优情况下，我们走过的节点除了树的直径外都走了两遍。

所以得到：
$$e_{p_n}=2\times (n-1)-\text{直径长度}$$
这样就能满足题目第三个条件了。

我们可以用两遍 dfs 求直径，一遍求出直径一端，另一遍直径一端的根据深度的划分的 $son[x]$，记录哪个儿子深度更深。

最后用类似 dfs 序求出答案即可，先走轻儿子因为贡献算两遍，再走重儿子，因为贡献只算一遍。

放上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,m,Tempestissimo(0);
const int N=2e5+5;
int head[N],from[N<<1],nxt[N<<1],to[N<<1],tot;
int dep[N],duan=1,son[N];
inline void add(int x,int y){
    to[++tot]=y,nxt[tot]=head[x],head[x]=tot;
    from[tot]=x;
    return ;
}
inline void dfs1(int now,int fa){
    dep[now]=dep[fa]+1;
    for(register int i=head[now];i;i=nxt[i]){
        int y=to[i];
        if(y==fa) continue;
        dfs1(y,now);
    }
}
inline void dfs2(int now,int fa){
    for(register int i=head[now];i;i=nxt[i]){
        int y=to[i];
        if(y==fa) continue;
        dfs2(y,now);
        dep[now]=max(dep[now],dep[y]+1);
        if(dep[y]>dep[son[now]]){
            son[now]=y;
        }
    }
}
int Sum=0,ans[N];
inline void dfs3(int now,int fa){
    ans[now]=++Sum;
    for(register int i=head[now];i;i=nxt[i]){
        int y=to[i];
        if(y==fa||y==son[now]) continue;
        dfs3(y,now);
    }
    if(son[now]){
        dfs3(son[now],now);
    }
    ++Sum;
}
signed main(void){
    n=read();
    for(register int i=1;i<n;i++){
        register int asd=read(),jkl=read();
        add(asd,jkl),add(jkl,asd);
    }
    dfs1(1,0);
    for(register int i=1;i<=n;i++){
        if(dep[i]>dep[duan]){
            duan=i;
        }
    }
    for(register int i=1;i<=n;i++){
        dep[i]=0;
    }
    dep[duan]=1;
    dfs2(duan,0);
    dfs3(duan,0);
    for(register int i=1;i<=n;i++){
        Write(ans[i]),putchar(' ');
    }
    return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

考虑对结点排列 $\{p_n\}$，可以标号 $E_{p_i}=E_{p_{i-1}}+d(p_i,p_{i-1})$，

两点之间显然满足要求，$E_{p_i}-E_{p_{i-2}}=E_{p_i}-E_{p_{i-1}}+E_{p_{i-1}}-E_{p_{i-2}}=d(p_i,p_{i-1})+d(p_{i-1},p_{i-2})\ge d(p_i,p_{i-2})$。

于是 $\max\limits_{i=1}^nE_i=E_{p_n}=\sum\limits_{i=2}^nd(p_i,p_{i-1})$，问题变为找到访问所有结点的最短路径。

直径走一遍，剩下走两遍即可。

```cpp
#include <cstdio>
struct E
{
    int v, t;
} e[400050];
int n, c, x, y, o = 1, a[200050], w[200050], d[200050], h[200050];
void A(int u, int v)
{
    e[++c] = {v, h[u]};
    h[u] = c;
}
void D1(int u, int k)
{
    if (d[u] > d[x])
        x = u;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            d[v] = d[u] + 1, D1(v, u);
}
void D2(int u, int k)
{
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            D2(v, u), w[u] |= w[v];
}
void D3(int u, int k)
{
    a[u] = o;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k && !w[v])
            ++o, D3(v, u), ++o;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k && w[v])
            ++o, D3(v, u);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i)
        scanf("%d%d", &u, &v), A(u, v), A(v, u);
    D1(d[1] = 1, 0);
    d[y = x] = 1;
    D1(y, x = 0);
    w[y] = 1;
    D2(x, 0);
    D3(x, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}
```


---

## 作者：白简 (赞：0)

### 题目大意

给定一棵 $n$ 个节点的树，要求构造出一个点权序列 $E$，满足以下三个条件：

1. 所有 $E_i\ge 1(1\le i\le n)$。
2. 对于任意一组 $(i,j)(1 ≤ i < j ≤ N)$，使 $|E_i-E_j|\geq \operatorname{dist}(i,j)$，$\operatorname{dist}(i,j)$ 即树上 $i$ 和 $j$ 两点距离。
3. 使 $E$ 中的最大值最小。

### 思路
首先只考虑前两个限制，设有点 $i,j,k$ 满足
$$E_i < E_j < E_k$$
因为有
$$E_k-E_i=E_k-E_j+E_j-E_i$$
由于
$$E_k-E_j\geq \operatorname{dist}(k,j),E_j-E_i\geq \operatorname{dist}(i,j)$$
所以有
$$E_k-E_i \geq \operatorname{dist}(k,j) + \operatorname{dist}(i,j)$$
又因为
$$\operatorname{dist}(k,j) + \operatorname{dist}(i,j) \geq \operatorname{dist}(i,k)$$
使得 $E_k-E_j$ 尽可能小，得到
$$E_k-E_i=\operatorname{dist}(k,i)$$
那么我们直接可以用欧拉序列进行构造，欧拉序列的长度为 $2n - 1$。

再考虑第三个限制条件，让 $E$ 中的最大值最小。

考虑我们欧拉序列有重复走的部分，我们使那个重复走的链的部分最短，那么那一段我们就可以选取树的直径。

那么我们怎么保证固定我们最后走哪个点呢？如果一条边在直径上，我们就最后经过这条边，这样在到达直径的第二个端点时，能够保证其他的点都已经遍历过。
### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200500;

vector<int> e[N];

int n;

int dis[N];

int EndPoint,End;

void dfs1(int x,int fa) {
    dis[x] = dis[fa] + 1;

    if(dis[x] > dis[EndPoint])
        EndPoint = x;
    
    for(auto const &to : e[x]) {
        if(to == fa)
            continue;
        
        dfs1(to,x);
    }
}

void GetCal() {
    dfs1(1,0);

    End = EndPoint;

    dfs1(EndPoint,0);
}

bool cal[N];

void dfs2(int x,int fa) {
    if(x == End)
        cal[x] = 1;
    for(auto const &to : e[x]) {
        if(to == fa)
            continue;
        
        dfs2(to,x);
        cal[x] |= cal[to];
    }
}

int ans[N],tot;

void dfs3(int x,int fa) {
    tot ++;
    ans[x] = tot;

    for(auto const &to : e[x]) {
        if(to == fa || cal[to])
            continue;
        
        dfs3(to,x);
        tot ++;
    }

    for(auto const &to : e[x]) {
        if(to == fa || !cal[to])
            continue;
        
        dfs3(to,x);
    }
}

int main() {
    cin >> n;

    for(int i = 1,u,v;i < n; i++) {
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    GetCal();
    
    dfs2(EndPoint,0);
    dfs3(EndPoint,0);

    for(int i = 1;i <= n; i++) 
        cout << ans[i] << " ";
    
    cout << "\n";
    return 0;
}
```

---

