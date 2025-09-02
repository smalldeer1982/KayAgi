# Tree Elimination

## 题目描述

给定一棵$n$个点的树，点编号$1 \sim n$，第$i$条边连接$a_i$和$b_i$。

初始时你有一个空的序列，树上的$n$个点都有标记。

现在按照边的编号从小到大考虑每一条边：

- 如果这一条边连接的两个点都有标记，则选择其中的一个点，擦除它的标记并将它的编号放入序列的末端；

- 否则什么都不做。

求能够由上述操作得到的不同的序列数量$\bmod\  998244353$。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7
7 2
7 6
1 2
7 5
4 7
3 5
```

### 输出

```
10
```

# 题解

## 作者：xht (赞：26)

首先，不同的序列数量等同于**消除标记的方案数**。

考虑树形 dp。我们称一个点被一条边**覆盖**，表示这个点在考虑到这条边时选择消除了这个点上的标记。

设 $f_{x,0/1/2/3}$ 分别表示：点 $x$ 是被自己的父亲边之前的边覆盖的、点 $x$ 是被自己的父亲边覆盖的、点 $x$ 是被自己的父亲边之后的边覆盖的、点 $x$ 没有被覆盖。

那么对于点 $y \in \operatorname{son}_ x$，考虑 $f_ {x,0/2}$：

- 点 $y$ 不能被覆盖，即 $f_{y,2/3}$。
- 定义点 $z (\in \operatorname{son}_ x) < y$ 是指边 $(x,z)$ 在边 $(x,y)$ 之前，则点 $z$ 一定要被覆盖，即 $f_ {z,0/1}$。
- 定义点 $z (\in \operatorname{son}_ x) > y$ 是指边 $(x,z)$ 在边 $(x,y)$ 之后，则点 $z$ 可以被覆盖也可以不被覆盖，但不能被边 $(x,z)$ 覆盖，即 $f_ {z,0/2/3}$。

因此有转移：

$$
f_ {x, 0/2} = \sum_ {y \in \operatorname{son}_ x} \left( f_ {y, 2 / 3} * \prod_ {z<y} f_ {z, 0 / 1} * \prod_ {z>y} f_ {z, 0 / 2 / 3} \right)
$$

考虑 $f_{x,1}$，有转移：

$$
f_{x, 1} = \prod_{y < fa_x} f_{y, 0 / 1} * \prod_{y > fa_x} f_{y, 0 / 2 / 3}
$$

考虑 $f_{x,3}$，有转移：

$$
f_{x,3} = \prod_{y} f_{y,0/1}
$$

时间复杂度 $\mathcal O(n)$。

```cpp
const int N = 2e5 + 7;
int n, m, k;
vi e[N];
modint f[N][4], a[N], b[N], c[N];

void dfs(int x, int fa) {
	for (int y : e[x]) if (y != fa) dfs(y, x);
	a[m=k=0] = 1;
	for (int y : e[x])
		if (y == fa) k = m;
		else  ++m, a[m] = a[m-1] * (f[y][0] + f[y][1]), b[m] = f[y][2] + f[y][3], c[m] = f[y][0] + b[m];
	c[m+1] = 1;
	for (int i = m; i; i--) c[i] *= c[i+1];
	for (int i = 1; i <= m; i++) f[x][(i>k)<<1] += a[i-1] * b[i] * c[i+1];
	f[x][1] = a[k] * c[k+1], f[x][3] = a[m];
}

int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++) rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	dfs(1, 0), print(f[1][0] + f[1][2] + f[1][3]);
	return 0;
}
```

---

## 作者：清尘 (赞：21)

[My Blog](https://www.cnblogs.com/whx666/p/606-div1.html#d)

这里写一个比较详细(繁琐)的。简洁的可以看另外一篇)

因为删除的时候边有先后顺序，这题 $dp$ 的状态和转移基于时间

状态设置（ $x$ 是什么时候被删除的？或者没被删除？）：$f_{x,0/1/2/3}$ 分别表示：点 $x$ 被父亲边之前的边删除、点 $x$ 被父亲边删除、点 $x$ 被父亲边之后的边删除、点 $x$ 没有被删除 四种情况下 $x$ 子树内的答案。

转移：

对于 $f_{x,0/2}$，$x$ 不是被父亲边删除，那一定是被和儿子相连的边删除。枚举这个儿子 $y$。$y$ 此时还没被删，取 $f_{y,2/3}$。对于其他儿子 $z$，按照时间分类：

1、$(x,z)$ 在 $(x,y)$ 前，记为 $z<y$。如果这时候 $z$ 还在，说明 $x$ 已经没了，不符合情况。所以取 $f_{z,0/1}$

2、$(x,z)$ 在 $(x,y)$ 后，记为 $z > y$ 。后面的时间点对当前不影响，但不能被父亲边删，因为 $x$ 已经挂了，取 $f_{z,0/2/3}$

**有 $f_{x,0/2}=\sum\limits_{y\in son(x),y<fa_x(y>fa_x)}(f_{y,2/3}\times\prod\limits_{z<y}f_{z,0/1}\times \prod\limits_{z>y}f_{z,0/2/3})$**

注：上式中对于 $f_{x,0}$ 和 $f_{x,2}$ 所选的 $y$ 条件不同，即在父亲边之前和父亲边之后

对于 $f_{x,1}$：

1、所有 $y<fa_x$ 已经不在（如果在，$x$ 就挂了），并且 $(x,y)$ 这条边不可能删除 $x$，所以 $y$ 的删除不会拖到 $(x,y)$ 之后，不能取 $f_{y,2}$，只能取 $f_{y,0/1}$。

2、$y>fa_x$，还是随便 $y$ 怎么样，但因为 $(x,y)$ 这条边还没弄，所以不能取 $f_{y,1}$，剩下的 $f_{y,0/2/3}$ 均可

**得**$f_{x,1}=\prod\limits_{y<fa_x}f_{y,0/1}\times\prod\limits_{y>fa_x}f_{y,0/2/3}$

对于 $f_{x,3}$，所有儿子 $y$ 肯定都挂了，并且不会拖到 $(x,y)$ 以后。取 $f_{y,0/1}$

**即 $f_{x,3}=\prod\limits_{y\in son(x)}f_{y,0/1}$**

代码里直接把多重式拆出来算了，可能有些怪

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void read (int &x) {
    char ch = getchar(); x = 0; while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
} const int N = 2e5 + 5, mod = 998244353;
int n, f[N][4]; vector<int> g[N];
#define pb push_back
void dfs (int u, int la) {
    int sum = 0, s = 1, sa = 1, sb = 1, k = 0; f[u][3] = f[u][1] = 1;
    for (int v : g[u]) if (v != la) {
        dfs (v, u);
        (f[u][2] *= (f[v][0] + f[v][2] + f[v][3])) %= mod;
        (f[u][0] *= (f[v][0] + f[v][2] + f[v][3])) %= mod;
        if (!k) {
            (f[u][0] += s * (f[v][2] + f[v][3])) %= mod;
            (f[u][1] *= (f[v][0] + f[v][1])) %= mod;
        } else {
            (f[u][2] += s * (f[v][2] + f[v][3])) %= mod;
            (f[u][1] *= (f[v][0] + f[v][2] + f[v][3])) %= mod;
        }
        (s *= (f[v][0] + f[v][1])) %= mod;
        (f[u][3] *= (f[v][0] + f[v][1])) %= mod;
    } else k = 1;
}
signed main() {
    read (n);
    for (int i = 1, u, v; i < n; ++i)
        read (u), read (v), g[u].pb (v), g[v].pb (u);
    dfs (1, 0);
    printf ("%lld\n", (f[1][0] + f[1][3]) % mod);
}
```

---

## 作者：寻逍遥2006 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1276D)

我有一个第二维只有 3 个状态的做法……

考虑题目条件，假如给每个点的编号为擦除它标记的边，没有被擦除那么标记为 0，显然，每一个可行的标记方案和一个擦除方案一一对应——因为标记就对应了生成的序列，而且序列不可能和两个可行的标记对应。

理解一下：如果说点 $u$ 在处理边 $l$ 的时候有一种可行解，也就意味着在处理 $l$ 的时候，$l$ 两端的的点都没有被擦除。如果这是有另一个和它会生成完全相同的序列的标记方法，也就意味着在 $l$ 的时候该边没有被擦除，而是在之后被擦除了，但是为了让序列一样，$l$ 边应该不会擦除任何的点，这与 $l$ 两端的点都没有被擦除矛盾。

我们的问题就转化成为对可行方案的统计。

考虑什么样的方案是可行的：

1. 如果边 $l$ 执行了一次擦除操作，也就意味着 $l$ 两端的点有一个标记为 $l$，另一个没有标记或者标记大于 $l$。
2. 如果边 $l$ 没有执行擦除操作，也就意味着它的两端至少有一个点有标号且小于 $l$，而且两端的点标记都不能等于 $l$。

将这两条总结一些就是：**每条边的两端至少有一个点有标记且小于等于 $l$，但取等时有特殊要求**。

所以我们的转移也会自然而然地设计出三种状态（记点 $u$ 到它的父亲的边为 $l_u$）：
* $f[u][0]$：$u$ 节点的父亲可以有小于 $l_u$ 的标记时，以 $u$ 为根的子树标记的方案数。
* $f[u][1]$：$u$ 节点的父亲可以**必须**小于等于 $l_u$ 的标记时，以 $u$ 为根的子树标记的方案数。
* $f[u][2]$：$u$ 节点的父亲可以**不能**小于 $l_u$ 的标记时，以 $u$ 为根的子树标记的方案数。

现在就是考虑转移，显然是从 $u$ 的孩子转移到 $u$，记 $u$ 的孩子的集合是 $R_u$，其中 $u$ 的孩子与它相连的边中编号小于 $l_u$ 的构成的集合记为 $S_u$，编号大于 $l_u$ 的记为 $T_u$ ：
* 对于 $f[u][0]$：因为是可以有，那么也就意味着无论 $u$ 的父节点怎么标记，都是可行的。所以 $u$ 点的标记一定是小于 $l_u$ 的。假设这个标记是 $v_0\in S_u$，那么所有 $v\in R_u,l_v<l_{v_0}$ 的，它可以选择 $f[v][0]$ 和 $f[v][2]$；所有 $v\in R_u,l_v>l_{v_0}$ 的，它可以选择 $f[v][0]$ 和 $f[v][1]$，而 $v_0$ 只能选择 $f[v_0][1]$。所以 $f[u][0]=\sum\limits_{v_0\in S_u}\left(f[v_0][1]\times\prod\limits_{v\in R_u,l_v< l_{v_0}}\left(f[v][0]+f[v][2]\right)\times\prod\limits_{v\in R_u,l_v> l_{v_0}}\left(f[v][0]+f[v][1]\right)\right)$。
* 对于 $f[u][1]$：必须小于等于 $l_u$ 也就意味着 $u$ 没有标记或者标记大于 $l_u$ ，同理枚举 $v_0\in T_u$ 以及不标记的情况即可。转移方程： $f[u][1]=\sum\limits_{v_0\in T_u}\left(f[v_0][1]\times\prod\limits_{v\in R_u,l_v< l_{v_0}}\left(f[v][0]+f[v][2]\right)\times\prod\limits_{v\in R_u,l_v> l_{v_0}}\left(f[v][0]+f[v][1]\right)\right)+\prod\limits_{v\in R_u}\left(f[v][0]+f[v][2]\right)$，其实可以发现上式和 $f[u][0]$ 的转移方程是类似的，唯一的区别就是多了后面的一项。
* 对于 $f[u][2]$：这种情况只会对应 $u$ 节点标记为 $l_u$ 的情况，所以说转移也是类似的：$f[u][2]=\prod\limits_{v\in S_u}\left(f[v][0]+f[v][2]\right)\times\prod\limits_{v\in T_u}\left(f[v][0]+f[v][1]\right)$。

对于根节点可以钦定一个 $0$ 号边，它小于任何的其他边，那么最终的答案就应该是 $f[rt][1]$，其中 $rt$ 为根节点。

很显然这些转移中有很多重复的地方，基本只有一项的区别，所以整个转移的复杂度是 $O(|R_u|)$ 的，所以算法的复杂度为 $O(n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
int Qread()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x;
}
const long long Mod=998244353;
long long qpow(long long a,long long p)
{
	long long ret=1;
	while(p)
	{
		if(p&1) (ret*=a)%=Mod;
		p>>=1,(a*=a)%=Mod;
	}
	return ret;
}
struct Poi{
	int sta;
	long long f[3];
}p[200010];
struct Edge{
	int ind,nxt,poi;
}l[400010];
int cnt;
void add_edge(int u,int v,int ind)
{
	l[++cnt].nxt=p[u].sta,l[cnt].poi=v,l[cnt].ind=ind,p[u].sta=cnt;
	l[++cnt].nxt=p[v].sta,l[cnt].poi=u,l[cnt].ind=ind,p[v].sta=cnt;
	return;
}
void solve(int a,int fa)
{
	long long rem=1;
	for(int k=p[a].sta,v;k;k=l[k].nxt)
	{
		if((v=l[k].poi)==fa) continue;
		solve(v,a);
		(rem*=(p[v].f[0]+p[v].f[2])%Mod)%=Mod;
	}
	p[a].f[1]+=rem;
	bool situ=true;
	for(int k=p[a].sta,v;k;k=l[k].nxt)//由于链式前向星会将所有的边倒序，所以可以在转移时从大到小直接处理
	{
		if((v=l[k].poi)==fa)
		{
			p[a].f[2]=rem;
			situ=false;
		}
		else if(situ)
		{
			(rem=rem*qpow((p[v].f[0]+p[v].f[2])%Mod,Mod-2)%Mod)%=Mod;
			(p[a].f[1]+=rem*p[v].f[1]%Mod)%=Mod;
			(rem=rem*(p[v].f[0]+p[v].f[1])%Mod)%=Mod;
		}
		else
		{
			(rem=rem*qpow((p[v].f[0]+p[v].f[2])%Mod,Mod-2)%Mod)%=Mod;
			(p[a].f[0]+=rem*p[v].f[1]%Mod)%=Mod;
			(rem=rem*(p[v].f[0]+p[v].f[1])%Mod)%=Mod;
		}
	}
	return;
}
int n,i;
int main()
{
	n=Qread();
	for(i=1;i<n;i++)
		add_edge(Qread(),Qread(),i);
	solve(1,0);
	printf("%lld\n",p[1].f[1]);
	return 0;
}
```


---

## 作者：zzy0618 (赞：2)

题目让我们求数列的数量，实际上是求有多少操作方案。可以使用树形 dp 求解。

由于操作顺序按照边的编号决定，我们称 $u<v$ 即为边 $(fa_u,u)$ 在 $(fa_v,v)$ 之前。取消标记说得有点怪，我们直接说初始无标记，然后打标记算了。

设计状态 $f_{u,0/1/2/3}$ 分别为 $u$ 不被打标记；$u$ 在 $(fa_u,u)$ 之前打标记；$u$ 在 $(fa_u,u)$ 时打标记；$u$ 在 $(fa_u,u)$ 之后打标记。

先来考虑简单的 $f_{u,0}$，对于一个 $v\in son(x)$，如果 $v$ 没有且不能被打标记，就会使得 $u$ 被标记，所以 $f_{v,0}$ 不考虑。如果 $v$ 后来才被标记，一样 $u$ 现在也会被标记，所以 $f_{v,3}$ 不考虑。所以最终有：

$$f_{u,0}=\prod_{v\in son(u)}(f_{v,1}+f_{v,2})$$

然后是较为特殊的 $f_{u,2}$，所有 $v\in son(u),v<u$ 的都必须打上标记，不然 $u$ 就会被打上，当然可以通过 $(u,v)$ 这条边打上。而剩余 $v\in son(u),v>u$ 除了 $f_{v,2}$ 都可以。所以最终有：

$$f_{u,2}=\prod_{v\in son(u),v<u}(f_{v,1}+f_{v,2})\times \prod_{v\in son(u),v>u}(f_{v,0}+f_{v,1}+f_{v,3})$$

其实 $f_{u,1}$ 与 $f_{u,3}$ 比较相似。$u$ 不是被 $(fa_u,u)$ 打上标记，那一定是 $(u,v\in son(u))$ 打上的，最终是一种求和的形式。如果是 $(u,v)$ 打的标记，此时 $v$ 一定没打，即 $f_{v,0}+f_{v,3}$。考虑 $u$ 的其它儿子 $w\in son(u),w\not= v$，若 $w<v$，为了留住 $u$ ，只能取 $f_{w,1}+f_{w,2}$；若 $w>v$，除了 $f_{w,2}$，其它都可以。所以最终有：

$$f_{u,1}=\sum_{v\in son(u),v<u}(f_{v,0}+f_{v,3})\times\prod_{w<v}(f_{w,1}+f_{w,2})\times\prod_{w>v}(f_{w,0}+f_{w,1}+f_{w,3})$$

$$f_{u,3}=\sum_{v\in son(u),v>u}(f_{v,0}+f_{v,3})\times\prod_{w<v}(f_{w,1}+f_{w,2})\times\prod_{w>v}(f_{w,0}+f_{w,1}+f_{w,3})$$

最终答案为 $f_{rt,0}+f_{rt,1}$，因为 $rt$ 没有父亲，不存在父亲时与父亲后。

注意求 $f_{u,1},f_{u,3}$ 时要进行前缀优化。存图用 ```vector``` 保证顺序。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=2e5+5,P=998244353;
int n,f[N][4];vector<int> g[N];
void dfs(int u,int fa){
	bool h=1;int s=f[u][0]=f[u][2]=1;
	for(auto v:g[u]){
		if(v==fa)h=0;
		else{dfs(v,u);
			(f[u][1]*=f[v][0]+f[v][1]+f[v][3])%=P;
			(f[u][3]*=f[v][0]+f[v][1]+f[v][3])%=P;
			if(h)(f[u][1]+=s*(f[v][0]+f[v][3]))%=P,
				(f[u][2]*=f[v][1]+f[v][2])%=P;
			else(f[u][3]+=s*(f[v][0]+f[v][3]))%=P,
				(f[u][2]*=f[v][0]+f[v][1]+f[v][3])%=P;
			(s*=f[v][1]+f[v][2])%=P;
			(f[u][0]*=(f[v][1]+f[v][2]))%=P;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1,u,v;i<n;++i)
		cin>>u>>v,g[u].pb(v),g[v].pb(u);
	dfs(1,0);cout<<(f[1][0]+f[1][1])%P<<'\n';
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/1276/problem/D) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1276D)

繁琐的简单树形 dp（大雾），要是现场肯定弃了~~去做 F 题~~

~~做了我一中午，写篇题解纪念下。~~

提供一种不太一样的思路。

首先碰到这样的题肯定是没法用正常的组合计数方法求解，因此我们考虑树形 $dp$​。显然，如果对于每条边 $(u,v)$​ 而言，我们确定扫描到这条边时是删除 $u$​ 上的标记、还是删除 $v$​ 上的标记，还是 $u,v$​ 上已经有一个标记消失了（即啥也不删），并且**这种钦定方式合法**（即，当扫描到某条边 $e$ 时，不会出现你钦定要删除 $e$ 某个端点上的标记，却已经有某个端点上的标记消失了；或者你钦定啥也不删，却有 $e$ 的两个端点上的标记都没移走），那么我们就能唯一确定最后得到的序列。

考虑从这个性质入手解决问题，一个很自然的想法是设 $dp_x$ 表示有多少种合法的钦定 $x$ 子树中的边的方式，不过显然这东西不太好转移，因此考虑新加一维常数维记录一些信息。注意到对于一个点 $x$ 而言，$(x,fa_x)$ 的决策也会影响到 $x$ 与其儿子相连的边的决策，因此考虑将 $(x,fa_x)$ 这条边也纳入 DP 状态，即 $dp_x$ 的定义变为，有多少种合法的钦定 **$x$ 子树中的边及 $x$ 与其父亲的边**的方式。我们还能发现，当我们删除到边 $(x,fa_x)$ 时，有以下五种可能：

- $fa_x$ 上的标记还在，但 $x$​ 上的标记已经没了
- $x$​​ 上的标记还在，但 $fa_x$​​ 上的标记已经没了
- $x,fa_x$ 上的标记都没了
- $x,fa_x$ 上的标记都在，并且我们移走了 $x$​ 上的标记
- $x,fa_x$ 上的标记都在，并且我们移走了 $fa_x$ 上的标记

在下文中分别称这五种情况为 Condition $0\sim$​ Condition $4$​。考虑增加一维 **$dp_{x,j}$​ 我们在强制扫描到 $x$​ 与其父亲的边时情况为 Condition $j$​ 的情况下，有多少种合法的钦定 $x$​ 子树内边的方案数。**考虑对五种情况分别转移：

- Condition $0$：由于 $x$ 上的标记已经没了，因此我们肯定会在删除某一条**编号小于 $(x,fa_x)$** 且与 $x$ 相连的边时，删除了 $x$ 上的标记，因此我们考虑设 $f_y$ 为有多少种钦定方案，满足我们恰好在删除 $(x,y)$ 这条边时删除了 $x$ 的标记，那么有 $dp_{x,0}=\sum\limits_{\text{id}(x,fa_x)>\text{id}(x,y)}f_y$，其中 $\text{id}(x,y)$ 表示 $(x,y)$ 边的编号，$f_y$ 的求法将在下文中讲解。

- Condition $1$：首先对于与 $x$ 相连，且满足 $\text{id}(x,y)<\text{id}(x,fa_x)$ 的边，我们肯定不能删除 $x$ 上的标记，并且我们删除 $(x,y)$ 边也就是 $(y,fa_y)$ 时候，$x$ 上的标记肯定还是在的，因此只有两种可能 $dp_{y,0}$ 和 $dp_{y,3}$，乘法原理乘起来即可，$\text{id}(x,y)>\text{id}(x,fa_x)$ 的边，有两种选择，要么不存在某条 $(x,y)$ 删除了 $x$ 上的标记，方案数自然也是 $dp_{y,0}+dp_{y,3}$，要么存在，方案数就是 $\sum\limits_{\text{id}(x,fa_x)<\text{id}(x,y)}f_y$，两部分加起来可得
  $$
  dp_{y,1}=\prod\limits_{(x,y)\in E}(dp_{y,0}+dp_{y,3})+\sum\limits_{\text{id}(x,fa_x)<\text{id}(x,y)}f_y
  $$

- Condition $2$：聪明的读者应该能发现，对于 Condition $0$ 和 Condition $2$ 两种情况，它们对于 $\text{id}(x,y)<\text{id}(x,fa_x)$ 的限制相同，对于 $\text{id}(x,y)>\text{id}(x,fa_x)$ 的限制也相同，因此 $dp_{x,2}=dp_{x,0}$

- Condition $3$​：还是分为 $\text{id}(x,y)<\text{id}(x,fa_x)$​ 和 $\text{id}(x,y)>\text{id}(x,fa_x)$​ 两类边，$\text{id}(x,y)<\text{id}(x,fa_x)$​ 的边的方案数与 Condition $1$​ 那一部分相同，为 $dp_{y,0}+dp_{y,3}$​，$\text{id}(x,y)>\text{id}(x,fa_x)$​ 类比 Condition $1$​ 推理一下可知，删到 $(x,y)$​ 时只可能是 Condition $1,2$，因为不管怎样删到 $(x,y)$ 时 $x$ 上的标记已经没了，因此贡献为 $dp_{y,1}+dp_{y,2}$​，由乘法原理可知
  $$
  dp_{y,3}=\prod\limits_{\text{id}(x,fa_x)>\text{id}(x,y)}(dp_{y,0}+dp_{y,3})·\prod\limits_{\text{id}(x,fa_x)<\text{id}(x,y)}(dp_{y,1}+dp_{y,2})
  $$

- Condition $4$：同理可得 $dp_{x,4}=dp_{x,1}$，因为它们关于 $\text{id}(x,y)<\text{id}(x,fa_x)$ 与 $\text{id}(x,y)>\text{id}(x,fa_x)$ 两种情况的限制均对应相同。

接下来考虑怎么求 $f_y$​​，显然 $(x,y)$​​ 的贡献为 $dp_{y,4}$​​，对于我们也可以将所有与 $x$​​ 相连且不同于 $(x,fa_x),(x,y)$​​ 的边，我们也可以将它们分为两类：$\text{id}(x,z)<\text{id}(x,y)$​​ 和 $\text{id}(x,z)>\text{id}(x,y)$​​，仿照 Condition $3$​​ 的分析过程可知，第一部分的贡献为 $dp_{z,0}+dp_{z,3}$​，第二部分贡献为 $dp_{z,1}+dp_{z,2}$​，乘法原理乘起来可得：
$$
f_y=dp_{y,4}·\prod\limits_{\text{id}(x,z)<\text{id}(x,y)}(dp_{z,0}+dp_{z,3})·\prod\limits_{\text{id}(x,z)>\text{id}(x,y)}(dp_{z,1}+dp_{z,2})
$$
预处理前后缀积即可 $\mathcal O(1)$ 计算，总复杂度线性。

似乎我的这个 solution 把 condition $0,2$​ 和 condition $1,4$​ 合并之后就是 CF 官方题解给的写法？不过我这个 DP 状态至少能体现我自己的思考过程吧（

```cpp
const int MAXN=2e5;
const int MOD=998244353;
int n,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=1,bot[MAXN+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int dp[MAXN+5][5],mul[MAXN+5];
void dfs(int x,int f){
	dp[x][1]=dp[x][3]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;bot[y]=e>>1;dfs(y,x);
		if(bot[y]<bot[x]) dp[x][3]=1ll*dp[x][3]*(dp[y][0]+dp[y][3])%MOD;
		else dp[x][3]=1ll*dp[x][3]*(dp[y][1]+dp[y][2])%MOD;
		dp[x][1]=1ll*dp[x][1]*(dp[y][0]+dp[y][3])%MOD;
	} vector<int> vec,pre_mul,suf_mul;
	for(int e=hd[x];e;e=nxt[e]){int y=to[e];if(y==f) continue;vec.pb(y);}
	reverse(vec.begin(),vec.end());pre_mul.resize(vec.size());suf_mul.resize(vec.size());
	for(int i=0;i<vec.size();i++){
		int y=vec[i];
		pre_mul[i]=1ll*((!i)?1:pre_mul[i-1])*(dp[y][0]+dp[y][3])%MOD;
	} for(int i=(int)(vec.size())-1;~i;i--){
		int y=vec[i];
		suf_mul[i]=1ll*((i+1==vec.size())?1:suf_mul[i+1])*(dp[y][1]+dp[y][2])%MOD;
	} for(int i=0;i<vec.size();i++){
		int y=vec[i];
		int mul=dp[y][4];if(i) mul=1ll*mul*pre_mul[i-1]%MOD;
		if(i+1<vec.size()) mul=1ll*mul*suf_mul[i+1]%MOD;
		if(bot[y]<bot[x]) dp[x][0]=(dp[x][0]+mul)%MOD;
		else dp[x][1]=(dp[x][1]+mul)%MOD;
	} dp[x][4]=dp[x][1];dp[x][2]=dp[x][0];
}
int main(){
	scanf("%d",&n);bot[1]=n;
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	dfs(1,0);printf("%d\n",(dp[1][1]+dp[1][2])%MOD);
	return 0;
}
```



---

## 作者：PosVII (赞：1)

## 前言

前面的题解竟然没有人给结论写一个严谨的证明，在这还是贴一个证明好了。

## 题解

结论：不同的序列数与操作的方案数存在映射关系。

充分性：考虑一个合法的操作方案，我们可以通过模拟操作的过程来求出唯一的序列。

必要性：考虑一个序列，我们从小到大执行操作，由于已知序列，在每一次选择的时候我们只能选择序列中开头的那个点，于是操作方案也是唯一的。

知道这个结论后的 dp 有很多题解提到了，这里就不再赘述。

---

## 作者：Felix72 (赞：0)

非常好的树形 dp。

由于操作的有序性，状态定义肯定要考虑到时间问题。而共点的边才会互相影响，同理共边的点才会互相影响。时间关系只有小于、等于和大于三种。不妨定义状态如下：

$f_{pos, 0}$ 表示节点 $pos$ 在父亲边还未被执行时就已经被选的方案；

$f_{pos, 1}$ 表示节点 $pos$ 在父亲边被执行时被选的方案；

$f_{pos, 2}$ 表示节点 $pos$ 一直到父亲边被执行时都还没被选的方案（也许后面被选择，也许一直没被选）

对于一个点，我们把与其相连的边按时间排好序，分上面几种情况讨论（需要把最后一种拆成后面被选了和一只没被选两种情况）。

```cpp
/*Good Game, Well Play.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, mod = 998244353;
typedef pair < int, int > PII;
struct node
{
	int opt, pos, key;
	bool operator < (const node &w) const {return key < w.key;}
	bool operator > (const node &w) const {return key > w.key;}
};
int n; vector < PII > edge[N]; long long f[N][3];

inline void treedp(int now, int prt, int fid)
{
	vector < node > con;
	for(PII to : edge[now])
	{
		if(to.first == prt) continue;
		treedp(to.first, now, to.second);
		con.push_back({0, to.first, to.second});
	}
	if(prt) con.push_back({1, 0, fid});
	sort(con.begin(), con.end());
	long long g[2][4] = {{0, 0, 0, 1}, {0, 0, 0, 0}}; int wd = 0, flag = false;
	for(node s : con)
	{
		wd ^= 1; g[wd][0] = g[wd][1] = g[wd][2] = g[wd][3] = 0;
		if(s.opt == 1)
		{
			g[wd][0] = g[wd ^ 1][0];
			g[wd][1] = g[wd ^ 1][3];
			g[wd][2] = 0;
			g[wd][3] = g[wd ^ 1][3];
			flag = true;
		}
		else
		{
			if(!flag)
			{
				g[wd][0] = (g[wd ^ 1][0] * (f[s.pos][0] + f[s.pos][2]) + g[wd ^ 1][3] * f[s.pos][2]) % mod;
				g[wd][1] = 0;
				g[wd][2] = 0;
				g[wd][3] = g[wd ^ 1][3] * (f[s.pos][0] + f[s.pos][1]) % mod;
			}
			else
			{
				g[wd][0] = g[wd ^ 1][0] * (f[s.pos][0] + f[s.pos][2]) % mod;
				g[wd][1] = g[wd ^ 1][1] * (f[s.pos][0] + f[s.pos][2]) % mod;
				g[wd][2] = (g[wd ^ 1][2] * (f[s.pos][0] + f[s.pos][2]) + g[wd ^ 1][3] * f[s.pos][2]) % mod;
				g[wd][3] = g[wd ^ 1][3] * (f[s.pos][0] + f[s.pos][1]) % mod;
			}
		}
	}
	for(int i = 0; i <= 2; ++i) f[now][i] = g[wd][i];
	f[now][2] = (f[now][2] + g[wd][3]) % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		edge[x].push_back({y, i});
		edge[y].push_back({x, i});
	}
	treedp(1, 0, 0);
	cout << (f[1][0] + f[1][1] + f[1][2]) % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：chroneZ (赞：0)

首先操作序列可以视为边的定向方案。

我们发现这个操作过程中各子树是比较独立的，因此考虑树 DP。将树视为以 $1$ 为根的有根树，定义一个点的父边为连接其与其父亲的边。经过一些尝试后可以发现，我们需要定义以下 $4$ 个状态：

- $f_{u, 1}$ 表示 $u$ 子树的定向方案数，其中 $u$ 的父边指向 $u$。
- $f_{u, 2}$ 表示 $u$ 子树的定向方案数，其中在执行操作到父边之前 $u$ 已经被选过。
- $f_{u, 3}$ 表示 $u$ 子树的定向方案数，其中在执行操作到父边之前 $u$ 未被选过，且父边定向到 $fa_u$。
- $f_{u, 4}$ 表示 $u$ 子树的定向方案数，不考虑父边。

这样就足以实现转移了，答案为 $f_{1, 4}$。

记 $u$ 的父边的编号为 $t$（没有则为 $-1$），称 $u$ 的子结点中满足边的编号小于 $t$ 的为前缀点（$P$），否则称为后缀点（$S$）。若子结点 $u, v$ 满足 $u$ 的父边编号小于 $v$ 的，则称 $u \prec v$。则具体的转移如下：

- $f_{u, 1} = \prod \limits_{v \in P} (f_{v, 1} + f_{v, 2}) \prod \limits_{v \in S} f_{v, 4}$，前缀边要么指向 $v$ 要么 $v$ 已经被选，后缀边由于 $u$ 已经被选可以任意。
- $f_{u, 2} = \sum \limits_{v \in P} f_{v, 3} \prod \limits_{w \prec v} (f_{w, 1} + f_{w, 2}) \prod \limits_{v \prec w} f_{w, 4}$，即选择一个前缀中的子结点，让该子结点的父边定向到 $u$。
- $f_{u, 3}$ 和 $f_{u, 2}$ 相比改为选择后缀中的子结点。注意特殊处理没有子结点定向到 $u$ 的情况。
- $f_{u, 4}$ 和 $f_{u, 2/3}$ 相比改为任意子结点都可以被选。同样特殊处理没定向到 $u$ 的情况。

时间复杂度 $\Theta(n)$。（代码中 $f_{u, 3}$ 和 $f_{u, 4}$ 的定义互换了一下。）

```cpp
// Such a destiny was not desired.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 998244353, N = 2e5 + 5;
namespace basic {
  inline int add(int x, int y) {return (x + y >= mod ? x + y - mod : x + y);}
  inline int dec(int x, int y) {return (x - y < 0 ? x - y + mod : x - y);}
  inline void ad(int &x, int y) {x = add(x, y);}
  inline void de(int &x, int y) {x = dec(x, y);}

  inline int qpow(int a, int b) {
    int r = 1;
    while(b) {
      if(b & 1) r = 1ll * r * a % mod;
      a = 1ll * a * a % mod; b >>= 1;
    }
    return r;
  }
  inline int inv(int x) {return qpow(x, mod - 2);}

  int fac[N], ifac[N];
  inline void fac_init(int n = N - 1) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
      fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = inv(fac[n]);
    for(int i = n - 1; i >= 0; i--)
      ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  }
  int invx[N];
  inline void inv_init(int n = N - 1) {
    invx[1] = 1;
    for(int i = 2; i <= n; i++)
      invx[i] = 1ll * (mod - mod / i) * invx[mod % i] % mod;
  }
  inline int binom(int n, int m) {
    if(n < m || m < 0) return 0;
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
}
using namespace basic;

int n; vector<pair<int, int>> G[N];
int f[N][5];

void dfs(int u, int fa) {
  int t = -1;
  f[u][1] = 1;
  vector<pair<int, int>> sons;
  for(auto [w, v] : G[u]) {
    if(v == fa) {t = w; continue;}
    sons.emplace_back(w, v);
    dfs(v, u);
    if(t == -1) f[u][1] = 1ll * f[u][1] * add(f[v][1], f[v][2]) % mod;
    else f[u][1] = 1ll * f[u][1] * f[v][3] % mod;
  }
  vector<int> P = {1};
  vector<int> S = {1};

  for(int i = (int)sons.size() - 1; i >= 0; i--) {
    S.push_back(1ll * S.back() * f[sons[i].second][3] % mod);
  }
  reverse(S.begin(), S.end());
  for(int i = 0; i < sons.size(); i++) {
    P.push_back(1ll * P.back() * add(f[sons[i].second][1], f[sons[i].second][2]) % mod);
  }

  for(int i = 0; i < sons.size(); i++) {
    auto [w, v] = sons[i];
    ad(f[u][w < t ? 2 : 4], 1ll * P[i] * S[i + 1] % mod * f[v][4] % mod);
    ad(f[u][3], 1ll * P[i] * S[i + 1] % mod * f[v][4] % mod);
  }
  ad(f[u][4], P.back());
  ad(f[u][3], P.back());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  cin >> n;
  for(int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    G[u].emplace_back(i, v), G[v].emplace_back(i, u);
  }
  dfs(1, -1);
  cout << f[1][3] << "\n";
}
```

---

