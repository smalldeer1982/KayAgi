# [AGC052B] Tree Edges XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc052/tasks/agc052_b

$ N $ 頂点の木が与えられます。ここで、$ N $ は **奇数** です。 木の頂点には $ 1 $ から $ N $ までの、辺には $ 1 $ から $ N-1 $ までの番号が付けられています。 辺 $ i $ は頂点 $ u_i,\ v_i $ を結び、初期状態での重みは $ w^1_i $ です。

あなたは、次の操作を何度でも行えます。

- 木から辺 $ (u,\ v) $ を選ぶ。この辺の現在の重みが $ w $ であるとする。$ u,\ v $ のいずれかちょうど一方に接続する各辺について、その重みを $ w $ との **XOR** に置き換える（操作前の辺の重みが $ w_1 $ であるとすると、操作後の重みは $ w_1\ \oplus\ w $ となる）。

あなたの目標は、各辺 $ i $ の重みを $ w^2_i $ とすることです。 上記の操作を何度でも行えるとして、目標の達成が可能か判定してください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 10^5 $
- $ N $ は奇数である。
- $ 1\le\ u_i,\ v_i\ \le\ N $
- $ u_i\ \neq\ v_i $
- $ 0\le\ w^1_i,\ w^2_i\ <\ 2^{30} $
- 入力中の値は全て整数である。
- 入力が表すグラフは木である。

### Sample Explanation 1

辺 $ 1 $ に対して操作を行うと、辺 $ 2 $ の重みが $ 8\ \oplus\ 1=9 $ となります。

## 样例 #1

### 输入

```
3
1 2 1 1
2 3 8 9```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 2 0 3
1 3 1 0
1 4 2 1
1 5 0 0```

### 输出

```
NO```

# 题解

## 作者：crimson000 (赞：7)

比较好的一道树相关的题目。

我们可以把边权转化为点权，但是这题和普通的边权转点权不太一样，本题中的点权为它到我们选定的根的距离（这里我选定 $1$ 号点为根）。由于一条边的边权可以由相邻的两个点的距离异或得到，因此距离的集合和边权的集合是一一对应的。

我们考虑我们进行一次操作会造成什么影响。

见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/srmagp07.png)

我们对这条边进行操作，操作过后我们可以发现，这个操作的边上面的点连的边的边权变为 $x \oplus w_1$（这里我用 $\oplus$ 表示异或），下面的边的边权分别为 $y\oplus w_1, z\oplus w_1$。我们会发现，除了这两个点的距离之外，别的点的距离都不会改变。因为在这个操作的边的子树外肯定不会变，在子树内因为到根的路径会多两个 $w_1$ 来异或，因此也不会变。

于是我们就考虑一下操作涉及到的这两个点的距离怎么改变。我们可以发现，上面的那个点的距离操作前为 $a$，操作后为 $a\oplus w_1$。下面这个点的距离操作前为 $a\oplus w_1$，操作后由于路径上有两个 $w_1$，则距离为 $a$。因此，一次操作只会交换相邻两个点的点权，也就是距离。

但是我们可以发现一些不对劲的地方，比如说，如果我们把一个点和根节点操作，理论上会交换它们的距离，但是根节点的距离应该始终为 $0$，这就出现了问题。我们为了修正这个问题，我们可以引入一个虚拟节点来向根节点连边。而一号点进行操作时也会改变这条边的边权。这样也就符合了我们上面的结论：**每次操作交换两个点的距离**。

现在就是如何判定的问题了。我们发现，唯一棘手的地方就是在这个虚拟节点和根节点之间的边的边权上，我们暂且把它称为虚拟边，只要把这一点解决了即可。我们可以发现，由于每次只会交换两个点的点权，**点权的集合是不改变的**，因此我们可以从第一棵树中得到第二棵树中有虚拟边的情况下所有点的距离的异或和，而我们又能得到第二棵树中没有虚拟边的情况下所有点的距离。同时，由于题目中的一个条件：$n$ 为奇数，因此我们就能得到第二棵树中虚拟边的权值，只需要异或一下即可。

这样我们就能求出第二棵树中所有点在有虚拟边的情况下所有点的距离。判断第一棵树和第二棵树中这个集合是否相等即可。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> PII;

const int N = 1e6 + 10;
// Tree 1
int h[N], e[N], ne[N], w[N], idx;
// Tree 2
vector<PII> G[N];
unordered_map<int, int> cnt;

int n;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dist1[N], dist2[N];
inline void dfs1(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dist1[v] = dist1[u] ^ w[i];
        dfs1(v, u);
    }
}

inline void dfs2(int u, int fa)
{
    for(auto t : G[u])
    {
        int v = t.first, w = t.second;
        if(v == fa) continue;
        dist2[v] = dist2[u] ^ w;
        dfs2(v, u);
    }
}

signed main()
{
    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read(), d = read();
        add(a, b, c), add(b, a, c);
        G[a].emplace_back(b, d);
        G[b].emplace_back(a, d);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    int w1 = 0, w2 = 0;
    for(int i = 1; i <= n; i ++ )
    {
        w1 ^= dist1[i];
        w2 ^= dist2[i];
        cnt[dist1[i]] ++;
    }

    for(int i = 1; i <= n; i ++ )
    {
        // w1 ^ w2 即为虚拟边的权值
        dist2[i] ^= (w1 ^ w2);
        if(!cnt[dist2[i]])
        {
            puts("NO");
            return 0;
        }
        cnt[dist2[i]] --;
    }

    puts("YES");

    return 0;
}

```

---

## 作者：do_while_true (赞：4)

考虑边权转点权，让边权满足其为相邻点权的异或和，操作变成交换两个点的点权。

随便钦定一个为根，设 $d_i$ 为初始时 $i$ 的点权，$f_i$ 是 $i$ 期望得到为多少。如果存在 $d,f$，满足它们是相同的集合，就有解。

注意到如果确定了一个点的点权，那么其他所有点权都能唯一的确定。

现在钦定 $f_i$ 为 $i$ 到根路径上的边权和（或者说钦定 $f_1=0$），注意到任何一组解都能把所有点权异或 $f_1$，得到 $f_1=0$ 的解，所以判断是否有解就判断 $f_1=0$ 的时候是否有解。

现在 $f$ 确定了，看是否存在 $d$，满足 $d$ 和 $f$ 是相同的集合。

现在继续钦定 $d_i$ 为 $i$ 到根路径上边权和，与 $f$ 相同，所有可能为答案的 $d'$ 都是 $d$ 异或上一个 $x$ 得到的。

那么有解的必要条件就是 $(d_1\oplus x)\oplus (d_2\oplus x)\oplus...\oplus (d_n\oplus x)=f_1\oplus f_2\oplus...\oplus f_n$，由于 $n$ 为奇数，所以可以解出 $x$ 是多少。

由于这仅是必要条件，那么最后还要 $\text{check}$ 一下是否合法。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;
typedef std::pair<ll, ll> pll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 100010;
int n, ent, head[N];
int d[N], f[N];
struct Edge {
	int next, to, v1, v2;
}e[N << 1];
inline void add(int x, int y, int w1, int w2) {
	e[++ent].to = y; e[ent].next = head[x]; e[ent].v1 = w1; e[ent].v2 = w2; head[x] = ent;
}
void dfs(int x, int fa, int h1, int h2) {
	d[x] = h1; f[x] = h2;
	for(int i = head[x]; i; i = e[i].next) {
		int v = e[i].to; if(v == fa) continue ;
		dfs(v, x, h1 ^ e[i].v1, h2 ^ e[i].v2);
	}
}
signed main() {
	read(n);
	for(int i = 1; i < n; ++i) {
		int u, v, w1, w2; read(u); read(v); read(w1); read(w2);
		add(u, v, w1, w2);
		add(v, u, w1, w2);
	}
	dfs(1, 0, 0, 0);
	int x = 0;
	for(int i = 1; i <= n; ++i) x ^= f[i] ^ d[i];
	for(int i = 1; i <= n; ++i) d[i] ^= x;
	std::sort(d + 1, d + n + 1);
	std::sort(f + 1, f + n + 1);
	for(int i = 1; i <= n; ++i)
		if(f[i] != d[i]) {
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
```

---

## 作者：Llx2022 (赞：4)

**这题真是出的太好了**

# **Description**


给一棵 $n$ 个点的树，保证 $n$ 是**奇数**。第 $i$ 条边的初始权值为 $w_i^1$。你可以进行任意如下操作：

- 选择一条边 $(u,v)$，设其边权为 $w$，则恰好有一个端点为 $u$ 或 $v$ 的边的权值异或 $w$。

你的目标是将第 $i$ 条边的权值变为 $w_i^2$，问是否可行。

# **Solution**

首先我们观察这个操作，操作每次都是对**树上相邻**的两条边进行操作，我们考虑将其转化为点与点之间的操作。因为边的个数只有 $n-1$ 条，因此肯定会有一个节点不存储权值，我们可以把他的权值视为 $0$，并让该点视为根节点，这并不影响异或操作，但是肯定会发现，这种转化成点的操作可能会产生**混乱**，我们考虑建一个虚拟原点，然后连接根节点，这样可以避免影响。

因此问题转化成了对相邻的两个点进行操作，每个点的权值可以异或上相邻的两个点的权值。

我们考虑让原权值存储每个节点到根节点的简单路径的权值异或和，这样对点的操作就转化为了**交换每个节点到根节点的路径异或值**，这样问题就成功转化为了交换点权（这里的点权是每个节点保存的到根节点的路径异或值）的问题。我们再看原来的问题，问能否从初始局面转化为目标局面，这个好像很难想，但我们发现题目中还有一个限制条件 $n$ 为奇数，那就说明了只有偶数个点有点权，这提示我们从异或的性质去思考，偶数个相同的数异或，值不变，**那么这就可以将建好的的两棵初始和目标局面的路径树中的所有点权异或起来，判断是否相等就行**，也就是说我们树中的根节点可以是任意常数 $c$，这是不会影响所有点异或起来的权值和的。那么我们就需要计算这个根节点的值 $c$。这个值就是初始状态到目标状态，每个点的异或和，计算出来后再带回原来的初始树中，再判断与目标状态是否相等就可以。


# **Code**
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e5+9;
const int M=N*2;
//w是初始值 w2是目标值
int h[N],e[M],ne[M],w[M],w2[M],idx;
void add(int a,int b,int c,int d){
    e[idx]=b;
    w[idx]=c;
    w2[idx]=d;
    ne[idx]=h[a];
    h[a]=idx++;
}
int n;
int u,v,ww1,ww2;
//initial是初始树每个节点到根节点的值
//goal是目标树每个节点到根节点的值
int initial[N],goal[N];
void dfs(int u,int fa,int path_initial,int path_goal){
    initial[u]=path_initial;
    goal[u]=path_goal;
    for(int i=h[u];~i;i=ne[i]){
        int v=e[i];
        int ww=w[i];
        int ww2=w2[i];
        if(v==fa) continue;
        dfs(v,u,path_initial^ww,path_goal^ww2);
    }  
}
int main(){
    memset(h,-1,sizeof h);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d%d",&u,&v,&ww1,&ww2);
        add(u,v,ww1,ww2);
        add(v,u,ww1,ww2);
    }
    dfs(1,0,0,0);
    int virtual_root_val=0;
   	//计算根节点常数c
    for(int i=1;i<=n;i++){
        virtual_root_val^=initial[i]^goal[i];
    }
    for(int i=1;i<=n;i++){
        initial[i]^=virtual_root_val;
    }
    sort(initial+1,initial+1+n);
    sort(goal+1,goal+1+n);
    for(int i=1;i<=n;i++){
        if(initial[i]!=goal[i]){
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
```






---

## 作者：__Floze3__ (赞：1)

## 思路简述

首先我们手玩一下，发现什么是不容易变的？就是一条路径的异或和，只要一个端点不是选定的那条边的一个端点，那么异或和就是不变的。那么我们用上一个经典（真的经典吗？）Trick：将边权转为点权。但这里不是简单的一一对应，而是将一个点的点权设为从根到这个点的路径和，那么一条路径的异或和就被转化为了两个端点的权值的异或。我们继续手玩，发现这样一个事实：对于一条边的操作，相当于交换两个点的点权。好，现在你兴冲冲的按照这个去写，判断两棵树的点权集合是否相等，尽管你感觉有些不对劲。一交，好，WA 了。哪里不对劲？在于根节点：它的权值应该保持为 $0$。

现在该怎么处理？我们仔细思考一下为什么根节点是特殊的。答案是显然的（真的吗）：因为它没有向上的边。这~~并不~~好办，我们在它上面接个虚拟节点不就是了？那么现在的问题是：这个点到根节点的边权应该是多少？我们考虑一下这条边对每个点的点权的影响，其实就是都异或上一个边权。因为 $N$ 是奇数，那么点权的异或和就会异或上一个边权。那么，如果这条边的边权不是以 $w_i^1$ 建树点权的异或和和以 $w_i^2$ 建树点权的异或和的异或，那么肯定是无法达成目标的。但是这只是一个必要条件，所以求出这个边权之后还要判断两棵树的点权集合是否相等，时间复杂度为 $O(n \log n)$。

## 代码

[提交记录](https://atcoder.jp/contests/agc052/submissions/56456113)

---

## 作者：Soh_paramEEMS (赞：0)

## 题意
给一棵个点的树，保证 $n$ 是奇数。第 $i$ 条边的初始权值为 $w_{i,1}$。你可以进行任意如下操作：

选择一条边 $(u,v)$，设其边权为 $w$，则恰好有一个端点为 $u$ 或 $v$ 的边的权值异或 $w$，异或次数不限。

问将第 $i$ 条边的权值变为目标边权 $w_{i,2}$​，是否可行。
## 思路
很厉害的题目。

已知边权，那么可以考虑**边权转点权**。

那么操作的本质就是点权的交换，为什么是这样呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/i1r82srp.png)

在上图中对边 $(1,2)$、边权为$w_1$ 进行一次操作，只有节点 $1$ 和 $2$ 到其它节点的距离集合 $s_1$ 与 $s_2$ 发生改变，并不影响其它节点 $u$ 的 $s_u$（比如 $5\rightarrow 3$ 就异或了两次 $w1$，没有改变）。

考虑研究这一改变。例如 $1$、$2$ 到 $5$ 的距离：
- 原来 $w(1,5)=x,\ w(2,5)=w1 \bigoplus x$。

- 现在 $w'(1,5)=w_1 \bigoplus x, \ w'(2,5)=w_1 \bigoplus (x \bigoplus w_1)=x$。

对于下面的 $3$ 和 $4$ 同样如此，对更多的点手搓一下就会发现一个结论：**操作的本质就是距离集合 $s_1$ 和 $s_2$ 的交换**。

设 $(u,v)$ 边边权为 $w$，那么用前缀和思想构造出一组点权 $a$ 使 $a_u \bigoplus a_v=w$。

钦定 $1$ 为根，记 $st_u$ 为 $1$ 到 $u$ 的路径初始边权异或和，那么对于任意初始边权：
$$w_1(u,v): st_u \bigoplus st_v=w_1$$

类似的，记 $en_u$ 为 $1$ 到 $u$ 的路径目标边权异或和，那么对于任意目标边权：
$$w_2(u,v): en_u \bigoplus en_v=w_2$$

那么**对边 $(u,v)$ 一次操作，就是点权 $st_u,st_v$ 的交换**，即上文距离集合的交换。

可以钦定空节点 $1$ 的点权为 $x$（相当于假想了一条边，总边数奇数变偶），那么只需找到一个可行的 $x$，使满足：
$$ \bigoplus_{i=1}^{n} \left ( st_i \bigoplus x \right) =\bigoplus_{i=1}^{n}en_i$$

即：
$$x\bigoplus \left( \bigoplus_{i=1}^{n}st_i \right) =\bigoplus_{i=1}^{n}en_i$$

移项得：
$$x=\bigoplus_{i=1}^{x}\left ( st_i \bigoplus en_i \right )$$

最后将 $st$ 异或了 $x$ 后的 $st'$ 数组和 $en$ 数组分别排序，比较即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e5+2;
ll n,x;
ll idx,head[N];
ll st[N],en[N];
struct edge
{
	ll to,next,w1,w2;
}e[N<<1];
void addedge(ll u,ll v,ll w1,ll w2)
{
	idx++;
	e[idx].to=v;
	e[idx].next=head[u];
	e[idx].w1=w1;
	e[idx].w2=w2;
	head[u]=idx;
}
void dfs(ll u,ll fa,ll s,ll t)
{
	st[u]=s;//边权换点权 
	en[u]=t;
	for(int i=head[u];i;i=e[i].next)
	{
		ll v=e[i].to,w1=e[i].w1,w2=e[i].w2;
		if(v==fa)continue;
		dfs(v,u,w1^s,w2^t);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		ll u,v,w1,w2;
		scanf("%lld%lld%lld%lld",&u,&v,&w1,&w2);
		addedge(u,v,w1,w2);
		addedge(v,u,w1,w2);
	}
	dfs(1,0,0,0);
	//xor:(d[i]^x)=xor:f[i]
	for(int i=1;i<=n;i++)
	x^=st[i]^en[i];
	for(int i=1;i<=n;i++)
	st[i]^=x;//转换
	sort(st+1,st+n+1);
	sort(en+1,en+n+1);//比较
	for(int i=1;i<=n;i++)
	{
		if(st[i]!=en[i])
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES"); 
	return 0;
}
```

---

## 作者：K_srh (赞：0)

给定一个 $n$ 个节点的树，每条边有权值，每次操作可将一条边的邻边权值 $\operatorname{xor}$ 上这条边的权值，问最终可不可以变成另一棵（边权值不同的）树。

**寻找变化中更可控更有规律的特征变化**

首先这个邻边 $\operatorname{xor}$，一看就有非常大的不可控性，考虑能不能从这个操作中找到一个可比较的，变化更有规律的值，考虑三条邻边权值分别为 $x,y,z$，我们尝试对中间的 $y$ 进行一次操作，则变成 $x\oplus y,y,y\oplus z$，看看什么东西的变化更小，我们发现如果如果其作一个前缀 $\operatorname{xor}$ 和的话，后面的结果正好是前面的结果前两项交换，并且放到树上也只会影响这俩个，考虑相当于一个节点到根的 $\operatorname{xor}$ 和，而有这个东西也能唯一确定每条边，看到这好像已经可做了，但是别忘了再找一些可能的漏洞，发现根自己的 $\operatorname{xor}$ 和永远都是 $0$，无法通过交换，我们给这个根外面连一个假想边，边权为 $w$,让他不再是根，这样相当于每个点的值就成为了原值再 $\operatorname{xor}$ 上一个 $w$，注意到 $n$ 为奇数，那么我们把所有点 $\operatorname{xor}$ 出来应该正好等于第二棵树所有点 $\operatorname{xor}$ 值再 $\operatorname{xor}$ 上一个 $w$，我们可以直接算出 $w$，再比较第一棵树每个点所构成的集合和第二棵树每个点 $\operatorname{xor}$ 上 $w$ 所构成的集合是否相同即可（数量我们也关注）。
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int N=1e6+5;
unordered_map<int,int> cnt;
vector<pii> v[N];
struct NODE{
	int v;
	int w;
	int next;
}node[N<<1];
int head[N];
int tot=0;
void add(int u,int v,int w)
{
	node[++tot].v=v;
	node[tot].w=w;
	node[tot].next=head[u];
	head[u]=tot;
}
int dis1[N],dis2[N];
void dfs1(int x,int fa)
{
	for(int i=head[x];i;i=node[i].next)
	{
		int y=node[i].v;
		if(y==fa)continue;
		dis1[y]=dis1[x]^node[i].w;
		dfs1(y,x);
	}
}
void dfs2(int x,int fa)
{
	for(auto i:v[x])
	{
		int y=i.first,w=i.second;
		if(y==fa)continue;
		dis2[y]=dis2[x]^w;
		dfs2(y,x);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(a,b,c);add(b,a,c);
		v[a].emplace_back(b,d);
		v[b].emplace_back(a,d);
	}
	dfs1(1,1);dfs2(1,1);
	int w1=0,w2=0;
	for(int i=1;i<=n;i++)
	{
		w1^=dis1[i];w2^=dis2[i];
		cnt[dis1[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		dis2[i]=dis2[i]^(w1^w2);
		if(!cnt[dis2[i]]){printf("NO");return 0;}
		cnt[dis2[i]]--;
	}
	printf("YES");
	return 0; 
}
```

---

## 作者：TallBanana (赞：0)

我们发现，若令边权变为点权的异或 $a_u\oplus a_v$，则操作变成交换 $a_u,a_v$。

但是发现 $a$ 全部异或上 $x$ 后所有边权还是不变，于是我们考虑找到这个 $x$。

注意力惊人，$\oplus_{i=1}^n (a_i\oplus x)=\oplus_{i=1}^n b_i$。而且 $n$ 是奇数，于是左侧是 $x \oplus(\oplus_{i=1}^n a_i)$，所以我们可以求出 $x$。判断 $a\oplus x$ 和 $b$ 是否在集合意义下相同即可。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=1e5+10;
LL n,a[N],b[N],x;
struct edge { LL v,w1,w2; };
vector<edge> e[N];
void dfs(LL u,LL fa)
{
	x^=a[u]^b[u];
	for(auto i:e[u])
	{
		LL v=i.v,w1=i.w1,w2=i.w2;
		if(v==fa) continue;
		a[v]=a[u]^w1;
		b[v]=b[u]^w2;
		dfs(v,u);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		LL u,v,w1,w2;
		scanf("%lld%lld%lld%lld",&u,&v,&w1,&w2);
		e[u].push_back({v,w1,w2});
		e[v].push_back({u,w1,w2});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) a[i]^=x;
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i]) return !printf("NO");
	printf("YES");
	return 0;
}
```

---

## 作者：Richard_Whr (赞：0)

神仙题。

先考虑链是什么情形：

三条相邻的边：$x,y,z$，对 $y$ 进行了一次操作后变为：$x\oplus y,y,z\oplus y$。这种中间对两边或两边对中间的神秘操作，考虑差分/前缀和。

注意到前缀和比较有规律：原来是：$x,x \oplus y,x \oplus y \oplus z$，现在是：$x \oplus y,x,x \oplus y \oplus z$。

相当于交换了一次前缀和。

树上有没有类似的特点呢？

验证发现是有的，我们指定根后，把前缀和下放到点上。

对一条边的操作，本质上是交换相邻节点的前缀和。

有一个问题是，根节点不符合规律，因为根节点没有父亲的边，他自己的前缀和永远是 $0$，我们只好假想一条边，初始权值是 $0$ 接在跟上。

最后为了把他还原位 $0$，我们把整棵树都和它的权值异或。

由于可以人以交换，那么能不能就转化为了集合是否相等。

注意到我们最后可以对第一棵树整体异或，由于 $n$ 是奇数，我们可以直接获得。

注意到整体异或的值并不是任意的，只能是第一棵树构成的线性基中可以表示的数。

不过第二棵树中必有一个 $0$，为了集合相同只能异或一个线性组合，不必担心。

代码很短：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef tuple<int,int,int> I3;
vector<I3> e[N];
int f[N],g[N];
int s1,s2;
int n;

void dfs(int u,int p)
{
	s1^=f[u],s2^=g[u];
	for(auto [v,a,b]:e[u])
	{
		if(v==p) continue;
		f[v]=f[u]^a,g[v]=g[u]^b;
		dfs(v,u);
	}
}

bool check()
{
	for(int i=1;i<=n;i++) if(f[i]!=g[i]) return false;
	return true;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n;
	for(int i=1,a,b,c,d;i<n;i++)
	{
		cin>>a>>b>>c>>d;
		e[a].push_back({b,c,d});
		e[b].push_back({a,c,d});
	}
	
	dfs(1,0);
	
	int k=s1^s2;
	for(int i=1;i<=n;i++) f[i]^=k;
	sort(f+1,f+1+n);
	sort(g+1,g+1+n);
	
	if(check()) cout<<"YES\n";
	else cout<<"NO\n";
	
	return 0; 
}
```

启发我们对这种临项操作考虑不变量/简化操作的思路。

---

