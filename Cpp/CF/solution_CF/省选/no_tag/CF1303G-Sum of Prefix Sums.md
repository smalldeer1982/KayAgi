# Sum of Prefix Sums

## 题目描述

We define the sum of prefix sums of an array $ [s_1, s_2, \dots, s_k] $ as $ s_1 + (s_1 + s_2) + (s_1 + s_2 + s_3) + \dots + (s_1 + s_2 + \dots + s_k) $ .

You are given a tree consisting of $ n $ vertices. Each vertex $ i $ has an integer $ a_i $ written on it. We define the value of the simple path from vertex $ u $ to vertex $ v $ as follows: consider all vertices appearing on the path from $ u $ to $ v $ , write down all the numbers written on these vertices in the order they appear on the path, and compute the sum of prefix sums of the resulting sequence.

Your task is to calculate the maximum value over all paths in the tree.

## 说明/提示

The best path in the first example is from vertex $ 3 $ to vertex $ 1 $ . It gives the sequence $ [3, 3, 7, 1] $ , and the sum of prefix sums is $ 36 $ .

## 样例 #1

### 输入

```
4
4 2
3 2
4 1
1 3 3 7```

### 输出

```
36```

# 题解

## 作者：wucstdio (赞：24)

先扯一点点别的……

这场 CF 我是 F 题全场首杀，过掉 F 之后一看榜，F 题 1AC，G 题 2AC，我是 rank3。(后来发现 jiangly 是 F 题 rank2，lyh 是 F 题 rank3）当时我真的以为 G 会比 F 简单。

后来证明 G 题和 F 题相比就是一个大毒瘤，之所以 G 过的人多可能是因为 G 是原题。

最后 10 分钟写完了 G 交上去 WA，弃疗后看了一眼榜发现首页只有一个人 AK，其他人不是 F 题狂 WA 就是 G 题狂 WA，都自闭了……

废话不多说，下面开始本题题解。

---

### 题目大意

给你一棵 $n$ 个点的带点权的树，你需要求出树上的一个路径 $x_1,x_2,\ldots,x_k$，最大化 $\sum_{i=1}^kia_{x_i}$，求最大权值。

### 数据范围

$2\le n\le 150000$

### 解题过程

#### Part 1

对于路径相关，首先我们考虑如何合并两条路径。

对于一条路径 $x_1\to x_k$，我们选择一个中间点 $x_m$，把它拆成两个子路径：

- 第一部分是 $x_1\to x_m$，我们设 $l_1=m,v_1=\sum_{i=1}^mia_{x_i}$。
- 第二部分是 $x_{m+1}\to x_k$，我们设 $s_2=\sum_{i=m+1}^ka_i,v_2=\sum_{i=m+1}^{k}(i-m)a_{x_i}$。

那么我们会发现，整条路径的权值就是 $v_1+l_1s_2+v_2$。

如果我们把 $(s_2,v_2)$ 看成插入，$(v_1,l_1)$ 看成是查询，我们会发现相当于求一条直线扫到的第一个点，肯定和凸包之类的东西脱不了干系。

#### Part 2

考虑点分治。

由于树分治保证了深度是 $O(\log n)$，所以我们可以把所有的 $(v_1,l_1)$ 和所有的 $(s_2,v_2)$ 拿出来，复杂度是正确的。

找到所有的路径可以直接进行一遍 dfs，时间复杂度 $O(n)$。

假设对于每一棵子树，我们已经求出来了所有的子路径，那么接下来的问题就是选择两条不在一棵子树内的点，求 $v_1+l_1s_2+v_2$ 的最大值。

我们把 $(s_2,v_2)$ 看成插入，$(v_1,l_1)$ 看成查询，那么求的值长成了一个一次函数的形式，其中 $s_2$ 是斜率，$v_2$ 是纵截距，自变量是 $x$，因此可以用李超树维护。

所谓李超树就是一个标记永久化线段树，每一个节点维护一个一次函数，支持插入一个一次函数和求单点最大值，在 `pushdown` 的时候如果能覆盖就直接覆盖，否则单边往下递归，一次 `pushdown` 复杂度是 $O(\log n)$，更详细的描述请点击[这里](https://www.baidu.com/s?wd=%E6%9D%8E%E8%B6%85%E6%A0%91&rsv_spt=1&rsv_iqid=0xc0ee8512000202f4&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_dl=tb&rsv_enter=1&rsv_sug3=10&rsv_sug1=5&rsv_sug7=100&rsv_sug2=0&inputT=1670&rsv_sug4=1670)。

把所有路径按照所在子树进行排序，进行到每一个子树的时候先查询所有路径再插入所有路径，最后反着再做一遍（因为路径有正反），我们就可以解决这一部分。

### 复杂度分析

李超树如果支持区间插入一次函数，那么时间复杂度是 $O(n\log^2n)$ 的，但是因为我们的插入都是全局插入，因此时间复杂度是 $O(n\log n)$。

由于每一层的复杂度是 $O(n\log n)$ 的，因此总时间复杂度是 $O(n\log^2n)$，可以通过本题。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
struct Tree//李超树
{
	#define lc x<<1
	#define rc x<<1|1
	#define mid ((l+r)>>1)
	struct Node
	{
		ll a,b;
	}tree[600005];
	void ins(int x,int l,int r,ll a,ll b)//插入一个一次函数
	{
		if(tree[x].a*l+tree[x].b<=a*l+b&&tree[x].a*r+tree[x].b<=a*r+b)
		{
			tree[x].a=a,tree[x].b=b;
			return;
		}
		if(tree[x].a*l+tree[x].b>=a*l+b&&tree[x].a*r+tree[x].b>=a*r+b)return;
		if(tree[x].a*mid+tree[x].b<a*mid+b)swap(tree[x].a,a),swap(tree[x].b,b);
		if(a<tree[x].a)ins(lc,l,mid,a,b);
		else ins(rc,mid+1,r,a,b);//比较中间值，然后单边递归
	}
	void build(int x,int l,int r)
	{
		tree[x].a=tree[x].b=0;
		if(l==r)return;
		build(lc,l,mid);
		build(rc,mid+1,r);
	}
	ll query(int x,int l,int r,int p)//查询单点最大值，因为标记永久化所以需要一路取max
	{
		ll ans=tree[x].a*p+tree[x].b;
		if(l==r)return ans;
		if(p<=mid)ans=max(ans,query(lc,l,mid,p));
		else ans=max(ans,query(rc,mid+1,r,p));
		return ans;
	}
	#undef lc
	#undef rc
	#undef mid
}T;
struct Edge
{
	int to;
	int nxt;
}e[300005];
int n,m,edgenum,head[150005],dep[150005],maxd;
int pa[150005],size[150005],root,maxs[150005];
int st[150005],top;
ll a[150005],v1[150005],v2[150005],l[150005],s[150005],x[150005],maxv[150005],ans;
bool flag[150005];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void getroot(int node,int tot)//求重心，tot指的是总大小
{
	size[node]=1;
	maxs[node]=0;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node]||flag[to])continue;
		pa[to]=node;
		getroot(to,tot);
		size[node]+=size[to];
		maxs[node]=max(maxs[node],size[to]);
	}
	maxs[node]=max(maxs[node],tot-size[node]);
	if(maxs[root]>maxs[node])root=node;
	pa[node]=0;
}
void dfs(int node,ll val1,ll val2,ll sum,int from)//val1,val2,sum,from 分别表示 v1,v2,s 和当前所在子树
{
	if(node!=root&&!from)from=node;
	dep[node]=dep[pa[node]]+1;
	maxd=max(maxd,dep[node]);
	bool f=0;
	size[node]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node]||flag[to])continue;
		pa[to]=node;
		f=1;
		dfs(to,val1+sum+a[to],val2+a[to]*dep[node],sum+a[to],from);
		size[node]+=size[to];
	}
	if(!f)//容易发现，路径端点一定是叶节点，因此只考虑端点是叶节点的子路径
	{
		st[++top]=node;
		v1[top]=val1,v2[top]=val2,s[top]=sum-a[root],l[top]=dep[node],x[top]=from;
	}
}
void solve()//点分治
{
	flag[root]=1;
	maxd=0;
	top=0;
	pa[root]=0;
	dfs(root,a[root],0,a[root],0);
	st[++top]=root;
	v1[top]=a[root],l[top]=1,v2[top]=s[top]=x[top]=0;
	T.build(1,1,maxd);//预处理
	x[top+1]=x[0]=-1;
	for(int i=1;i<=top;)//正着做一遍，每次考虑一棵子树内的路径
	{
		int j=i;
		while(x[j]==x[i])ans=max(ans,T.query(1,1,maxd,(int)l[j])+v1[j]),j++;
		j=i;
		while(x[j]==x[i])T.ins(1,1,maxd,s[j],v2[j]),j++;
		i=j;
	}
	T.build(1,1,maxd);
	for(int i=top;i>=1;)//反着再做一遍
	{
		int j=i;
		while(x[j]==x[i])ans=max(ans,T.query(1,1,maxd,(int)l[j])+v1[j]),j--;
		j=i;
		while(x[j]==x[i])T.ins(1,1,maxd,s[j],v2[j]),j--;
		i=j;
	}
	int x=root;
	for(int hd=head[x];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(flag[to]||size[to]==1)continue;
		int t=size[to];
		root=0;
		getroot(to,t);
		solve();
	}
}
int main()
{
	maxs[0]=2147483647;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	getroot(1,n);
	solve();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：4)

$$\texttt{Description}$$

[Sum of Prefix Sums](https://www.luogu.com.cn/problem/CF1303G)

$$\texttt{Solution}$$

首先看到树上路径类问题，可以考虑**点分治**。

在点分治之前，我们先来研究一下这个式子：

$$s_1 + (s_1 + s_2) + (s_1 + s_2 + s_3) + \cdots + (s_1 + \cdots + s_n)$$

明显可以化简成：

$$\sum_{i = 1}^n s_i \cdot (n - i + 1) = (n + 1) \times \sum_{i = 1}^n s_i - \sum_{i = 1}^n s_i \cdot i$$

然后就考虑在点分治时如何合并两条路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/g0rzit1f.png)

我们把一条路径分成**蓝色部分**和**红色部分**。

设蓝色部分的**长度**为 $pre\_len$，红色部分的**长度**为 $suc\_len$。

设：

$$pre\_sum = \sum_{i = 1} ^ {pre\_len} pre_i$$

$$suc\_sum = \sum_{i = 1} ^ {suc\_len} suc_i$$

$$pre\_rk\_sum = \sum_{i = 1} ^ {pre\_len} i \cdot pre_i$$

$$suc\_rk\_sum = \sum_{i = 1} ^ {suc\_len} i \cdot suc_i$$

所以整条路径的权值就可以表示出来了：

$$(pre\_sum + {\color{red}suc\_sum}) \times ({\color{red}pre\_len} + suc\_len + 1) - (pre\_rk\_sum + suc\_rk\_sum + {\color{red}suc\_sum \cdot pre\_len})$$

发现**红色部分**之间可以消掉：

$$pre\_sum\cdot suc\_len+pre\_sum\cdot(pre\_sum+1)-pre\_rk\_sum+suc\_sum\cdot(suc\_len+1)-suc\_rk\_sum)$$

我们点分治的时候会去遍历到每一个 $suc$，所以式子后面**只跟 $suc$ 有关**的部分可以暂时忽略，考虑如何计算**前半部分**的最大值。

$$\begin{matrix}\underbrace{pre\_sum}\\k\end{matrix}\times\begin{matrix}\underbrace{suc\_len}\\x\end{matrix}+\begin{matrix}\underbrace{pre\_sum\cdot(pre\_sum+1)-pre\_rk\_sum}\\b\end{matrix}$$

明显是一个**一次函数**的形式，所以我们可以用**李超线段树**来维护最大值。

时间复杂度 $\Theta(n \log ^ 2 n)$。

$$\texttt{Notice}$$

+ 在统计路径时由于路径 $x \to y$ 和路径 $y \to x$ 的权值可能是不同的，所以应该**正着反着都统计一遍**。

+ 李超线段树每次统计答案之前都要**清空**，但是**直接重建时间复杂度过高**，可以考虑在线段树上从上往下扫，如果遇到最优势线段不为初始值则清空，继续扫；否则直接退出。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

using poly = vector <int>;

int n, a[150005];
poly g[150005];

bool vis[150005];
int f[150005], siz[150005], sum, rt = 0;

long long ans = 0;

void findrt(int u, int fa) {
    f[u] = 0, siz[u] = 1;

    for (auto v : g[u]) {
        if (v != fa && !vis[v]) {
            findrt(v, u);

            f[u] = max(f[u], siz[v]);
            siz[u] += siz[v];
        }
    }

    f[u] = max(f[u], sum - siz[u]);

    if (!rt or f[u] < f[rt]) {
        rt = u;
    }
}

struct LiChaoTree {
    struct node {
        int l, r;
        long long k, b;
    } t[600005];

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        t[p].k = 0, t[p].b = -4e18;

        if (l == r) {
            return ;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void clear(int p) {
        if (t[p].k == 0 && t[p].b == -4e18) {
            return ;
        }
        else {
            t[p].k = 0, t[p].b = -4e18;
        }

        if (t[p].l == t[p].r) {
            return ;
        }

        int mid = (t[p].l + t[p].r) >> 1;

        clear(p << 1), clear(p << 1 | 1);
    }

    void update(int p, long long k, long long b) {
        if (t[p].l == t[p].r) {
            if (t[p].k * t[p].l + t[p].b < k * t[p].l + b) {
                t[p].k = k, t[p].b = b;
            }

            return ;
        }

        int mid = (t[p].l + t[p].r) >> 1;

        if (k * t[p].l + b > t[p].k * t[p].l + t[p].b) {
            if (k * mid + b > t[p].k * mid + b) {
                update(p << 1 | 1, t[p].k, t[p].b);
                t[p].k = k, t[p].b = b;
            }
            else update(p << 1, k, b);
        }
        else if (k * t[p].r + b > t[p].k * t[p].r + t[p].b) {
            if (k * mid + b > t[p].k * mid + t[p].b) {
                update(p << 1, t[p].k, t[p].b);
                t[p].k = k, t[p].b = b;
            }
            else update(p << 1 | 1, k, b);
        }
    }

    long long qry(int p, int x) {
        if (t[p].l == t[p].r) {
            return t[p].k * x + t[p].b;
        }

        int mid = (t[p].l + t[p].r) >> 1;
        long long ans = t[p].k * x + t[p].b;

        if (x <= mid) ans = max(ans, qry(p << 1, x));
        else ans = max(ans, qry(p << 1 | 1, x));

        return ans;
    }
}tree;

long long pre_sum[150005], suc_sum[150005];
long long pre_rk_sum[150005], suc_rk_sum[150005];

void dfs(int u, int fa, int len) {
    siz[u] = 1;

    for (auto v : g[u]) {
        if (v != fa && !vis[v]) {
            pre_sum[v] = pre_sum[u] + a[v];
            pre_rk_sum[v] = pre_rk_sum[u] + pre_sum[v];

            suc_sum[v] = suc_sum[u] + a[v];
            suc_rk_sum[v] = suc_rk_sum[u] + 1ll * len * a[v];

            dfs(v, u, len + 1);

            siz[u] += siz[v];
        }
    }
}


void calc_dfs(int u, int fa, int len) {
    ans = max(ans, pre_rk_sum[u]);
    ans = max(ans, suc_rk_sum[u] + suc_sum[u] + 1ll * a[rt]);

    ans = max(ans, tree.qry(1, len) + suc_sum[u] * (len + 1) - suc_rk_sum[u]);

    for (auto v : g[u]) {
        if (v != fa && !vis[v]) {
            calc_dfs(v, u, len + 1);
        }
    }
}

void add_dfs(int u, int fa, int len) {
    tree.update(1, pre_sum[u], pre_sum[u] * (len + 1) - pre_rk_sum[u]);

    for (auto v : g[u]) {
        if (v != fa && !vis[v]) {
            add_dfs(v, u, len + 1);
        }
    }
}

void solve(int u) {
    vis[u] = true, rt = u;
    pre_sum[u] = pre_rk_sum[u] = a[u];
    suc_sum[u] = suc_rk_sum[u] = 0;

    ans = max(ans, 1ll * a[u]), dfs(u, 0, 1);

    tree.clear(1);

    for (auto v : g[u]) {
        if (!vis[v]) {
            calc_dfs(v, u, 1);
            add_dfs(v, u, 2);
        }
    }

    reverse(g[u].begin(), g[u].end());
    tree.clear(1);

    for (auto v : g[u]) {
        if (!vis[v]) {
            calc_dfs(v, u, 1);
            add_dfs(v, u, 2);
        }
    }

    for (auto v : g[u]) {
        if (!vis[v]) {
            rt = 0, sum = siz[v];
            findrt(v, u), solve(rt);
        }
    }
}

int main() {
    ios :: sync_with_stdio(0), cin.tie(0);

    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    sum = n, findrt(1, 0), tree.build(1, 1, n);

    solve(rt);

    cout << ans << '\n';

    return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：Lynkcat (赞：3)

因为题解没人写静态链分治，本菜鸡在写错了 $n$ 次柿子后终于过了本题，所以在这里写题解来造福写 dsu on tree 的后人/ll。

我们先声明这些东西：

$F_i$： $i$ 节点的父亲。

$dep_i$： 节点深度。

$dis_i$：$\sum_{u\in G_i}a_u\times dep_u $，$G_i$ 表示 $i$ 到根的点集，下面含义相同。

$dis1_i:\sum_{u\in G_i}a_u\times (dep_i-dep_u+1)$

$s_i:\sum_{u\in G_i}a_u$

上面的东西都能 $O(n)$ 预处理出来。

你可以理解成 $dis_i$ 是形如这样的：![图2](https://cdn.luogu.com.cn/upload/image_hosting/0lp1n5s1.png)

你可以理解成 $dis1_i$ 是形如这样的：![图1](https://cdn.luogu.com.cn/upload/image_hosting/is6dta6y.png)

你可以理解成 $s_i$ 是形如这样的：![图3](https://cdn.luogu.com.cn/upload/image_hosting/u0lulgei.png)

我们考虑 dsu on tree 和李超线段树维护这个东西。

先考虑比较容易计算的一种形式：![图4](https://cdn.luogu.com.cn/upload/image_hosting/dzg0ol2y.png)

上面 $u$ 是已经统计过的点，$v$ 是计算贡献处，设 $fa$ 为 $u$ 与 $v$ 的 LCA，下文含义相同。

不难~~很难~~得出此时答案是：
$dis_u-dis_{F_{fa}}-(s_u-s_{F_{fa}})\times(dep_{fa}-1+dep_v-dep_{fa})+dis1_v-dis1_{fa}-s_{fa}\times(dep_v-dep_{fa})$。

整理柿子，将与 $u$ 相关的提出：

$X=dis_u-s_u\times(dep_{fa}-1+dep_v+dep_{fa})$。

其他部分：

$Y=-dis_{F_{fa}}+s_{F_{fa}}\times(dep_{fa}-1+dep_v+dep_{fa})+dis1_v-dis1_{fa}-s_{fa}\times(dep_v-dep_{fa})$。

$Y$ 可以直接算出，$X$ 相当于一条 $kx+b$ 的直线，做到 $u$ 的时候在李超线段树中插入一条斜率为 $s_u$，截距为 $dis_u$ 的直线，$v$ 处查询横坐标在 $dep_{fa}-1+dep_v+dep_{fa}$ 处的最大值即可。

考虑插入的先后顺序不一定，所以还要考虑反过来的情况：![图5](https://cdn.luogu.com.cn/upload/image_hosting/d7g3kdt7.png)

不难~~更加难~~得出此时答案是：
$dis1_u-dis1_{fa}-s_{F_{fa}}\times (dep_u-dep_{fa}+1)+(s_v-s_{fa})\times (dep_u-dep_{fa}+1-dep_{fa})+dis_v-dis_{fa}$。

同样将与 $u$ 相关的提出。

$X=dis1_u+dep_u\times (-s_{F_{fa}}+s_v-s_{fa})$。

$Y=-dis1_{fa}-S_{F_{fa}}\times (1-dep_{fa})+(s_v-s_{fa})\times (1-2\times dep_{fa})+dis_v-dis_{fa}$。

$Y$ 同样也可以直接算出，$X$ 相当于一条 $kx+b$ 的直线，做到 $u$ 的时候在李超线段树中插入一条斜率为 $dep_u$，截距为 $dis1_u$ 的直线，$v$ 处查询横坐标在 $-s_{F_{fa}}+s_v-s_{fa}$ 处的最大值即可。

总时间复杂度 $O(n \log n \log v)$。

ps:如果不理解上述柿子的实际含义可以私信我，限于篇幅这里不细讲，不过同类的柿子都写在一起了（如果柿子错了请速戳我）。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 150005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
//#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int cnt,rt;
struct node
{
	ll k,b;
}tr[15000005];
int lson[15000005],rson[15000005];
int a[N];
ll F[N],dis[N],s[N],dis1[N];
int dep[N],siz[N],son[N];
vector<int>G[N];
ll B=300000000000ll;
ll ans;
int n;
inline void ad(int x,int y)
{
	G[x].push_back(y);
}
inline ll calc(node p,ll x)
{
	return p.b+p.k*x;
}
void update(int &k,ll l,ll r,node now)
{
	if (!k)
	{
		k=++cnt;
		tr[k]=now;lson[k]=0,rson[k]=0;
		return;
	}
	ll mid=l+(r-l)/2;
	if (calc(tr[k],mid)<calc(now,mid))
	{
		swap(now,tr[k]);
	}
	if (l==r) return;
	if (tr[k].k<now.k)
	{
		update(rson[k],mid+1,r,now);
	} else
	{
		update(lson[k],l,mid,now);
	}
}
ll query(int &k,ll l,ll r,ll i)
{
	if (!k) return -inf;
	ll res=calc(tr[k],i),mid=l+(r-l)/2;
	if (i<=mid)
	{
		res=max(res,query(lson[k],l,mid,i));
	} else res=max(res,query(rson[k],mid+1,r,i));
	return res;
}
void dfs(int k,int fa)
{
	F[k]=fa;
	dep[k]=dep[fa]+1;
	dis[k]=dis[fa]+dep[k]*a[k];
	s[k]=s[fa]+a[k];
	dis1[k]=dis1[fa]+s[fa]+a[k];
	siz[k]=1;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		dfs(u,k);
		siz[k]+=siz[u];
		if (siz[u]>siz[son[k]]) son[k]=u;
	}
}
inline void work(int k,int rot)
{
	ll now=query(rt,-B,B,dep[k]-dep[rot]-(dep[rot]-1));
	now-=1ll*dis[F[rot]];
	now-=1ll*(s[F[rot]])*(dep[k]-dep[rot]);
	now+=1ll*(s[F[rot]])*(dep[rot]-1);
	now+=1ll*dis1[k];
	now-=1ll*dis1[rot];
	now-=1ll*(dep[k]-dep[rot])*s[rot];
	ans=max(ans,now);
}
inline void work1(int k,int rot)
{
	ll now=query(rt,-B,B,-s[rot]+s[k]-s[F[rot]]);
	now+=1ll*(dep[rot]-1)*(s[F[rot]]);
	now-=1ll*dis1[F[rot]];
	now-=1ll*(dep[rot]-1)*(s[k]-s[rot]);
	now+=1ll*dis[k]-dis[rot];
	now-=1ll*(s[k]-s[rot])*dep[rot];
	ans=max(ans,now);
}
void que(int k,int fa,int rot)
{
	work(k,rot);
	for (auto u:G[k])
	{
		if (u==fa) continue;
		que(u,k,rot);
	}
}
void que1(int k,int fa,int rot)
{
	work1(k,rot);
	for (auto u:G[k])
	{
		if (u==fa) continue;
		que1(u,k,rot);
	}
}
void ins(int k,int fa)
{
	node now;
	now.k=s[k],now.b=dis[k];
	update(rt,-B,B,now);
	for (auto u:G[k])
	{
		if (u==fa) continue;
		ins(u,k);
	}
}
void ins1(int k,int fa)
{
	node now;
	now.k=dep[k],now.b=dis1[k];
	update(rt,-B,B,now);
	for (auto u:G[k])
	{
		if (u==fa) continue;
		ins1(u,k);
	}
}
void dfs1(int k,int fa)
{
	for (auto u:G[k])
	{
		if(u==fa||u==son[k]) continue;
		dfs1(u,k);
		cnt=0;rt=0;
	}
	if (son[k]) dfs1(son[k],k);
	node now;
	now.k=s[k],now.b=dis[k];
	update(rt,-B,B,now);
	work(k,k);
	for (auto u:G[k])
	{
		if (u==fa||u==son[k]) continue;
		que(u,k,k);
		ins(u,k);
	}
}
void dfs2(int k,int fa)
{
	for (auto u:G[k])
	{
		if(u==fa||u==son[k]) continue;
		dfs2(u,k);
		cnt=0;rt=0;
	}
	if (son[k]) dfs2(son[k],k);
	node now;
	now.k=dep[k],now.b=dis1[k];
	update(rt,-B,B,now);
	work1(k,k);
	for (auto u:G[k])
	{
		if (u==fa||u==son[k]) continue;
		que1(u,k,k);
		ins1(u,k);
	}
}
signed main()
{
	n=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read();
		ad(u,v);
		ad(v,u);
	}
	for (int i=1;i<=n;i++) a[i]=read();
	dfs(1,0);
	dfs1(1,0);
	cnt=0,rt=0;
	dfs2(1,0);
	writeln(ans);
}
/*
*/

---

## 作者：EternalAlexander (赞：3)

**这篇题解不能够 AC，大家可以当个段子看**

首先正经做法是，如果你链分治的话，在 LCA 处合并两段路径，拆掉贡献发现是一个直线形式， $\max ans_i-ans_l+(d_i-d_l)\times (s_j-s_l)+ans_j-ans_l$ 然后轻链在重链的李超树上查询就行了。点分/边分也是差不多地。

考虑一个乱搞做法，找一个点，然后类似算直径地 dfs 一遍，找到答案最大的点，然后从那个点再做一次。这个显然是不对的。

但我们考虑做 $200$ 次，正确的概率会非常大。同时考虑到，这种路径是有方向的，且不同的方向答案不同，我们考虑随机计算正向/反向的路径，可以通过绝大部分的 hack 数据。

这个程序 pp 了，并且在 open hacking phase 没有被人叉掉。然而，乱搞依然挡不住真正的神仙

![](https://cdn.luogu.com.cn/upload/image_hosting/e9izpqxj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/srrm62so.png)

hack 的方法是，先造一棵树，满足从根节点往下跑的答案是错误的，然后往这棵树的根节点连一个菊花。然后你随的点在菊花里面的话，一定得不到正确答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/48ypv6wc.png)

> 大概长这样

然后这个乱搞就被叉了233

![](https://cdn.luogu.com.cn/upload/image_hosting/p3ksza04.png)

参考代码 https://codeforces.ml/contest/1303/submission/70891428



---

## 作者：苏联小渣 (赞：2)

考虑和树上两点路径有关的方法，不难想到点分治。

考虑当前重心为 $rt$，显然：

- 如果 $rt$ 有 $\ge 2$ 个子树，那么 $x,y$ 是不同子树内的叶子结点；

- 如果 $rt$ 只有一个子树，那么 $x,y$ 一个是 $rt$，一个是叶子结点。

第二种情况比较简单，我们考虑第一种情况。

我们假定当前子树内的叶子结点为 $x$，我们需要找到一个之前子树的或者之后子树的叶子结点 $y$，使得 $f(y,x)$ 最大，其中 $f(y,x)$ 表示从 $y$ 到 $x$ 的二阶前缀和。这个式子可以拆成两部分，分别是 $y$ 到 $rt$ 的部分和 $rt$ 的某一个儿子（设作 $u$）到 $x$ 的那一部分。我们现在考虑两部分怎么合并。

我们考虑把 $y \to x$ 这条链抽出来成一个序列 $a_1,a_2,...,a_k$，其中钦定 $rt$ 为 $a_t$，定义一个位置的前缀和为 $s_i$，二阶前缀和为 $s'_i$。我们发现，假设当前位置为 $i$，那么拓展到 $i+1$，其二阶前缀和加上 $s_i+a_{i+1}$。以此类推，我们可以得出：$s'_k=s'_t+(k-t) \cdot s_t+f(u,x)$，其中 $f$ 的定义同前。而对于一个 $x$，其 $k-t,f(u,x)$ 都是已知的，不妨分别记作 $P(x),Q(x)$；$s'_t,s_t$ 都和 $y$ 有关， 不妨分别记作 $F(y),G(y)$，那么有：

$$ans(x)=\max(F(y)+P(x) \cdot G(y))+Q(x)$$

将含 $x$ 的视为参数，我们发现，$\max$ 里面的形成了一个一次函数的形式，我们需要找到一个一次函数，使得在 $P(x)$ 点处，这个一次函数比其它的都大，这个就是一个标准的李超线段树形式。对于一个 $y$，我们将 $G(y)$ 视作斜率、将 $F(y)$ 视作截距，放到李超线段树里面，然后对于另一个子树内的 $x$，查询在 $P(x)$ 点处的最值即可。注意由于 $f(x,y)$ 和 $f(y,x)$ 是不同的，所以正着反着都要跑一遍，这样用 vector 存边会更方便一些。

时间复杂度 $O(n \log^2 n)$。

### Code:

```c++
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 150000
#define lc(x) x<<1
#define rc(x) x<<1|1
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n, p, x, y, rt, mn, tsiz, num, mxdep, a[150010], h[150010], siz[150010], vis[150010];
ll ans, s[150010], ss[150010], S[150010], SS[150010], b[600010], k[600010], d[600010];
vector <int> g[150010];
struct leaf{
	ll s1, s2;
};
vector <leaf> cun[150010];
vector <leaf> ask[150010];
ll f(ll X, int Y){
	return b[X] + 1LL * k[X] * Y;
}
void modify(int cnt, int l, int r, ll x){
	if (f(x, l) > f(d[cnt], l) && f(x, r) > f(d[cnt], r)){
		d[cnt] = x;
		return ;
	}
	if (f(x, l) <= f(d[cnt], l) && f(x, r) <= f(d[cnt], r)){
		return ;
	}
	int mid = l + r >> 1;
	if (k[x] > k[d[cnt]]){
		if (f(x, mid) > f(d[cnt], mid)){
			modify(lc(cnt), l, mid, d[cnt]);
			d[cnt] = x;
		}
		else{
			modify(rc(cnt), mid+1, r, x);
		}
	}
	else{
		if (f(x, mid) < f(d[cnt], mid)){
			modify(lc(cnt), l, mid, x);
		}
		else{
			modify(rc(cnt), mid+1, r, d[cnt]);
			d[cnt] = x;
		}
	}
}
ll query(int cnt, int l, int r, int x){
	if (l == r){
		return f(d[cnt], l);
	}
	int mid = l + r >> 1;
	if (x <= mid) return max(f(d[cnt], x), query(lc(cnt), l, mid, x));
	else return max(f(d[cnt], x), query(rc(cnt), mid+1, r, x));
}
void dfs1(int x, int fa){
    siz[x] = 1;
    int mx = 0;
    for (int i=0; i<g[x].size(); i++){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        dfs1(y, x);
        siz[x] += siz[y];
        mx = max(mx, siz[y]);
    }
    mx = max(mx, tsiz - siz[x]);
    if (mx < mn) mn = mx, rt = x;
}
void dfs3(int fir, int x, int fa, int dep){
    s[x] = s[fa] + a[x];
    ss[x] = ss[fa] + s[x];
    S[x] = S[fa] + a[x];
    SS[x] = SS[fa] + 1LL * a[x] * (dep + 1);
    int son = 0;
    for (int i=0; i<g[x].size(); i++){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        dfs3(fir, y, x, dep+1);
        son ++;
    }
    if (!son){
        ans = max(ans, query(1, 0, mxdep, dep) + ss[x]);
        cun[fir].push_back((leaf){S[x], SS[x]});
        ask[fir].push_back((leaf){dep, ss[x]});
    }
}
void calc(int x, int fa, int dep){
    mxdep = max(mxdep, dep);
    for (int i=0; i<g[x].size(); i++){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        calc(y, x, dep+1);
    }
}
void solve(int x, int fa){
    mxdep = num = 0;
    vis[x] = 1;
    calc(x, 0, 0);
    num ++;
    b[num] = a[x], k[num] = a[x];
    modify(1, 0, mxdep, num);
    for (int i=0; i<g[x].size(); i++){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        cun[y].clear();
        ask[y].clear();
        s[x] = ss[x] = 0;
        SS[x] = S[x] = a[x];
        dfs3(y, y, x, 1);
        for (int j=0; j<cun[y].size(); j++){
        	num ++;
        	k[num] = cun[y][j].s1, b[num] = cun[y][j].s2;
        	modify(1, 0, mxdep, num);
		}
    }
    ans = max(ans, query(1, 0, mxdep, 0));
    for (int i=0; i<=mxdep*4; i++) d[i] = 0;
    for (int i=0; i<=num; i++) k[i] = b[i] = 0;
    num = 0;
    num ++;
    b[num] = a[x], k[num] = a[x];
    modify(1, 0, mxdep, num);
    for (int i=g[x].size()-1; i>=0; i--){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        for (int j=0; j<ask[y].size(); j++){
        	ans = max(ans, query(1, 0, mxdep, ask[y][j].s1) + ask[y][j].s2);
		}
		for (int j=0; j<cun[y].size(); j++){
			num ++;
			k[num] = cun[y][j].s1, b[num] = cun[y][j].s2;
			modify(1, 0, mxdep, num);
		}
    }
    for (int i=0; i<=mxdep*4; i++) d[i] = 0;
    for (int i=0; i<=num; i++) k[i] = b[i] = 0;
    for (int i=0; i<g[x].size(); i++){
        int y = g[x][i];
        if (y == fa || vis[y]) continue;
        rt = 0, mn = 1e9, tsiz = siz[y];
        dfs1(y, 0);
        dfs1(rt, 0);
        solve(rt, 0);
    }
}
int main(){
    n = read();
    for (int i=1; i<n; i++){
        x = read(), y = read();
        g[x].push_back(y); g[y].push_back(x);
    }
    for (int i=1; i<=n; i++){
        a[i] = read();
    }
    mn = 1e9, tsiz = n;
    dfs1(1, 0);
    dfs1(rt, 0);
    solve(rt, 0);
    printf ("%lld\n", ans);
    return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：1)

# CF1303G Sum of Prefix Sums 题解

## Description

给定一棵树和点权值 $a_i$，求树上的一个路径 $(u,v)$ 使最大化

$$\sum\limits_{i=u}^v\sum_{j=u}^i a_i$$

注意这里 $(u,v)$ 编号不一定连续，只需是树上路径即可。

## Solution

首先是树上的路径问题，容易想到使用点分治来解决问题。我们分治路径经过的点 $root$，然后找它里面所有的路径进行匹配。

如果进行这个思路，我们就需要首先了解将一条路径分成两个要如何计算。

对于一条路径 $(u,v)$，设共经过了点 $p_1,p_2,\dots,p_n$，显然，根据题目中给出的式子，有：

$$val=\sum\limits_{i=1}^n i\times a_i$$

假设它经过了中间点 $p_m$，即路径分为了 $p_1,p_2,\dots,p_m$ 和 $p_{m+1},p_{m+2},\dots,p_n$，那么计 $val1=\sum\limits_{i=1}^m i\times a_i,val2=\sum\limits_{i=m+1}^n (i-m)\times a_i,s=\sum\limits_{i=m+1}^n a_i$，那么显然有整个式子的值为：

$$val=val1+val2+s\times m$$

也就是说，我们要拿这个式子对所有经过 $root$ 的路径来进行匹配。注意到式子中有 $s\times m$ 这一项，这里 $s$ 与后一段路径相关，$m$ 和前一段路径相关，因此很容易想到一次函数的形式，考虑使用李超线段树维护。

推理到这里，我们就不难写出算法流程：

1. 找到一个子树的重心进行点分治。
2. 找到以它为根节点的子树中所有一个端点是它的路径。
3. 将这些路径进行匹配，这期间使用李超线段树。
4. 继续遍历它的儿子找到重心，继续步骤1。

因为这个题也不是板子，我也不讲点分治和李超树的详细过程了。复杂度点分治有一个 $\log$，李超线段树维护直线也有一个 $n\log n$，因此总复杂度在 $n\log^2n$。

此外，本题有一些值得注意的点：

- 在寻找路径的时候，注意到点权不为负，因此显然最优解在叶子结点上，因此只需要记录叶子结点到根节点的路径即可。
- 在计算子树大小和各个节点的父亲的时候，注意一定不要胡来给 $root$ 一个父亲，或者将它的父亲设成当前的根节点，因为在求 $dep$ 的时候会爆掉 (Wa on test 32)。
- 在匹配的时候，需要正着反着都来一遍，因为显然 $(u,v)$ 和 $(v,u)$ 这两条路径的权值是不一样的。

~~其它的就问题不大了。~~

## Main Code

```cpp
#define int long long
const int INF = 0x3f3f3f3f;
const int N = 1.5e5 + 10;
const int M = 1e6 + 10;

int n, a[N], ans;
int root, sum, maxx[N], siz[N];
int fa[N], v1[N], v2[N], l1[N], s2[N], cnt, top[N], p[N], dep[N], maxdep;
vector<int> g[N];
bool vis[N];

struct line{
	int k,b,id;
	line(){}
	line(int _k,int _b,int _id){ id=_id, k=_k, b=_b;}
	int val(int x){ return x*k+b;}
}t[N<<2];
void build(int p,int l,int r){
	t[p].id=t[p].b=t[p].k=0;
	if(l==r)	return ;
	int mid=l+r>>1;
	build(p<<1,l,mid), build(p<<1|1,mid+1,r);
}
void update(int p,int l,int r,line f){
	if(!t[p].id){ t[p]=f; return ;}
	int mid=l+r>>1;
	if(t[p].val(mid)<f.val(mid))	swap(t[p],f);
	if(t[p].val(l)<f.val(l))	update(p<<1,l,mid,f);
	if(t[p].val(r)<f.val(r))	update(p<<1|1,mid+1,r,f);
}
int query(int p,int l,int r,int x){
	if(l==r)	return t[p].val(x);
	int mid=l+r>>1;
	if(x<=mid)	return max(t[p].val(x),query(p<<1,l,mid,x));
	else	return max(t[p].val(x),query(p<<1|1,mid+1,r,x));
}

void calsiz(int x,int fat){
	siz[x]=1; maxx[x]=0, fa[x]=fat;
	for(int y:g[x]){
		if(vis[y]||y==fat)	continue;
		calsiz(y,x);
		siz[x]+=siz[y]; maxx[x]=max(maxx[x],siz[y]);
	}
	maxx[x]=max(maxx[x],sum-siz[x]);
	if(maxx[x]<maxx[root])	root=x;
}
void caldis(int x,int val1,int val2,int sum2,int tp){
	if(x!=root&&!tp)	tp=x;
	dep[x]=dep[fa[x]]+1;
	maxdep=max(maxdep, dep[x]);
	bool f=false;
	for(int y:g[x]){
		if(!vis[y]&&y!=fa[x]){
			f=true;
			caldis(y,val1+sum2+a[y],val2+dep[x]*a[y],sum2+a[y],tp);
		}
	}
	if(!f){ p[++cnt]=x; v1[cnt]=val1, v2[cnt]=val2, s2[cnt]=sum2-a[root], l1[cnt]=dep[x], top[cnt]=tp;}
}
void dfz(int x,int fat){
	vis[root]=true;
	cnt=0; maxdep=0;
	caldis(root,a[root],0,a[root],0);
	p[++cnt]=root, v1[cnt]=a[root], v2[cnt]=s2[cnt]=top[cnt]=0, l1[cnt]=1;
	top[0]=top[cnt+1]=-1;
	build(1,1,maxdep);
	for(int i=1;i<=cnt;){
		int j=i;
		while(top[j]==top[i])	ans=max(ans,query(1,1,maxdep,l1[j])+v1[j]), ++j; j=i;
		while(top[j]==top[i])	update(1,1,maxdep,line(s2[j],v2[j],j)), ++j; i=j;
	}
	build(1,1,maxdep);
	for(int i=cnt;i>=1;){
		int j=i;
		while(top[j]==top[i])	ans=max(ans,query(1,1,maxdep,l1[j])+v1[j]), --j; j=i;
		while(top[j]==top[i])	update(1,1,maxdep,line(s2[j],v2[j],j)), --j; i=j;
	}
	for(int y:g[x]){
		if(vis[y])	continue;
		sum=siz[y]; maxx[root=0]=INF;
		calsiz(y,x), calsiz(root,-1);
		dfz(root,x);
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<n;++i)	cin>>x>>y, g[x].pb(y), g[y].pb(x);
	for(int i=1;i<=n;++i)	cin>>a[i];
	maxx[root=0]=INF; sum=n;
	calsiz(1,-1); calsiz(root,-1);
	dfz(root,-1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ycx_girlfriend (赞：1)

### [原题链接](https://codeforces.com/contest/1303/problem/G)

这题好毒瘤啊!

首先看到是树上查询全局某式子的最大值，珂以想到这题无外乎是链分治($\text{dsu on tree}$)或点分治。~~作为一个专业的链分治选手,~~ 窝在比赛中想了$30$min也不会。比赛后想了想，好像$\text{dsu on tree}$不星(珂能还是窝太菜了)。

点分治。因为是全局最大值，所以珂以不用在分治里容斥。

假设当前的子树的根是$\text{u}$。

由于不用容斥，所以要确保在分治里面路径不能有重复边，这个珂以枚举$\text{u}$的儿子$\text{v}$，然后枚举$\text v$为根的子树中的节点$\text y$，另外开一个玩意儿维护之前的所有节点$\text x$的信息，其中$\text x$不在子树$\text v$里面。这样就珂以避免路径重复了。

因为询问是有方向的，为了方便，每一次枚举$\{\text x,\text y\}$时，默认方向为$\text x\rightarrow\text u\rightarrow \text y$。这样在枚举完$\text u$的儿子$\text v$之后，还要在反过来枚举一遍，即枚举另一个方向。

窝们考虑维护$\text x$的什么信息。设$\text x\rightarrow \text y$的答案为$\operatorname{ans}(\text x,\text y)$，$\text x\rightarrow\text y$路径的长度为$\operatorname{len}(\text x,\text y)$

$\operatorname{ans}(\text x,\text y)=\operatorname{ans}(\text v,\text y)+\operatorname{ans}(\text x,\text u)+\operatorname{len}(\text v,\text y)\sum\limits_{w\in \text x\rightarrow\text u}a_w$

这里，$\operatorname{ans}(\text v,\text y),\operatorname{len}(\text v,\text y)$是定值。

所以这个式子就是一个$a+x+by$的结构，其中$a,b$是珂能会变的定值。

也就是说，窝们要搞一个数据结构，支持：

1. 插入二元组$(x,y)$
2. 给定$c$，查询$\max\{x+cy\}$

到这儿，想必神仙们都会用李超线段树来切掉这题了吧

然后由于窝这个菜鸡不会李超线段树，只能用其他方法。

和李超线段树做法一样，窝们把$(y,x)$转化为平面上一条直线的$(k,b)$，然后查询就是询问$\max\{f(c)\}$。

窝采用动态凸包，用平衡树维护哪些直线珂能成为最大值，按照$k$排序。

插入直线时，用叉积判断一条直线是否珂能成为最大值。

查询时，就直接平衡树上二分每一条直线$l$是否满足最大值的要求，即$c$是否在$l\cap \operatorname{nxt}(l)$左边。

放一下代码：
```cpp
// Code by H~$~C
#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL_JUDGE
static char _in_buf[100000], *_in_p1 = _in_buf, *_in_p2 = _in_buf;
#define gc (__builtin_expect(_in_p1 == _in_p2, 0) && (_in_p2 = (_in_p1 = _in_buf) + \
        fread(_in_buf, 1, 100000, stdin), _in_p1 == _in_p2) ? -1 : *_in_p1++)
#else
#define gc getchar()
#endif
inline int read() {
  register char ch = gc;
  register int x = 0;
  while (ch < 48 || ch > 57) ch = gc;
  while (ch > 47 && ch < 58) x = (x << 3) + (x << 1) + (ch ^ 48), ch = gc;
  return x;
}

static const int Maxn = 150005;

int n;
long long a[Maxn];
long long ans;
vector<int> g[Maxn];

// use to solve something that Li-Chao-Tree do
// add a line f(x), query max{f(a)}
namespace HULL {
  bool flag;
  struct line {
    long long k, b;
    mutable function<const line* ()> nxt;
    friend bool operator < (const line &a, const line &b) {
      if (!flag) return a.k < b.k;
      const line *s = a.nxt();
      if (!s) return false;
      return a.b - s->b < b.b * (s->k - a.k);
    }
  };
  struct dynamic_hull
  : public multiset<line> {
    // check if the line is maximum somewhere
    inline bool bad(iterator it) {
      if (it == this->end()) return false;
      auto nxt = next(it);
      if (it == this->begin()) {
        if (nxt == this->end()) return false;
        return it->k == nxt->k && it->b <= nxt->b;
      }
      auto prv = prev(it);
      if (nxt == this->end()) {
        return it->k == prv->k && it->b <= prv->b;
      }
      return (prv->b - it->b) * (nxt->k - it->k) >= (it->b - nxt->b) * (it->k - prv->k);
    }
    // add a new line to the current hull
    inline void add(long long k, long long b) {
      auto it = this->insert((line){k, b});
      it->nxt = [=]() { return next(it) == this->end() ? nullptr : &*next(it); };
      if (bad(it)) return void(this->erase(it));
      while (next(it) != this->end() && bad(next(it))) this->erase(next(it));
      while (it != this->begin() && bad(prev(it))) this->erase(prev(it));
    }
    // query the maximum value where <x> = x
    long long query(long long x) {
      if (this->empty()) return -1LL << 60;
      flag = true;
      line l = *lower_bound((line){0, x});
      flag = false;
      return l.k * x + l.b;
    }
  };
}
using HULL::dynamic_hull;

bool vis[Maxn];
int sz[Maxn], mxson[Maxn];
int root, total, mnson;

void get_root(int u, int fa) {
  sz[u] = 1, mxson[u] = 0;
  for (int v: g[u]) {
    if (v == fa || vis[v]) continue;
    get_root(v, u), sz[u] += sz[v];
    mxson[u] = max(mxson[u], sz[v]);
  }
  mxson[u] = max(mxson[u], total - sz[u]);
  if (mnson > mxson[u]) {
    root = u;
    mnson = mxson[u];
  }
}

int dep[Maxn];
long long dis[Maxn], d[Maxn];
dynamic_hull h;

void dfs_query(int u, int fa, int dep, long long dis, long long sum) {
  dis += a[u];
  sum += dis;
  ans = max(ans, h.query(dep) + sum);
  for (int &v: g[u]) {
    if (v == fa || vis[v]) continue;
    dfs_query(v, u, dep + 1, dis, sum);
  }
}
void dfs_modify(int u, int fa, int dep, long long dis, long long sum) {
  dis += a[u];
  sum += a[u] * dep;
  h.add(dis, sum);
  for (int &v: g[u]) {
    if (v == fa || vis[v]) continue;
    dfs_modify(v, u, dep + 1, dis, sum);
  }
}

void solve(int u) {
  ans = max(ans, a[u]);
  
  h.clear();
  for (int v: g[u]) {
    if (vis[v]) continue;
    dfs_query(v, 0, 1, 0LL, 0LL);
    dfs_modify(v, 0, 2, a[u], a[u]);
  }
}

void divide_root(int u) {
  vis[u] = true;
  
  solve(u);
  reverse(g[u].begin(), g[u].end());
  solve(u);
  
  for (int v: g[u]) {
    if (vis[v]) continue;
    
    total = sz[v], root = 0;
    mnson = 0x3f3f3f3f;
    get_root(v, 0);
    
    divide_root(root);
  }
}

int main() {
  n = read();
  for (int i = 1; i < n; ++i) {
    int u = read(), v = read();
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  
  total = n, root = 0;
  mnson = 0x3f3f3f3f;
  get_root(1, 0);
  
  divide_root(root);
  
  printf("%lld\n", ans);
  return 0;
}

```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[CF1303G Sum of Prefix Sums](https://www.luogu.com.cn/problem/CF1303G)

## Solution

点分治，考虑将所求路径拆成两条，长度分别为 $len,len'$，点权分别为 $a,b$ 序列。

题目中要求前缀和的和，记 $s_i$ 为前缀和：

$$
\begin{aligned}
S &= s_1 + （s_1 + s_2） + \dots + s_n
\\
&= \sum\limits_{i=1}^{n}{(n - i + 1) \times s_i}
\\
&= (n + 1) \sum\limits_{i=1}^{n}{s_i} - \sum\limits_{i=1}^{n}{s_i \times i}
\end{aligned}
$$

记 $sum_A = \sum\limits_{i=1}^{len}{a_i},sum_B = \sum\limits_{i=1}^{len}{a_i \times i},sum_A' = \sum\limits_{i=1}^{len'}{b_i},sum_B'= \sum\limits_{i=1}^{len'}{b_i \times i}$，则所求路径权值根据上文所推式子：

$$
(len + len' + 1) \times (sum_A + sum_A') - (sum_B + sum_B') - sum_A' \times len
\\ \Downarrow \\
len' \times sum_A + (len + 1) \times sum_A - sumB
$$

你会发现我在这里把只跟 $len',sum_A',sum_B'$ 有关的踢掉了，因为点分治之后肯定是会遍历到的所以不用管。

然后你就能轻松看出这是一个一次函数，看来我们只需要在把式子放到李超树上维护即可，但是你要注意，$u \to v$ 的路径权值可能和 $v \to u$ 的路径权值不同，所以正反都跑一遍。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace FASTIO {
	inline int read() {
		int res = 0, f = 1;
		char ch = getchar();
		while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
		while (isdigit(ch)) res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
		return res * f;
	}
	inline void write (int x) {
		int st[33], top = 0;
		if (x < 0) x = -x, putchar ('-');
		do { st[top ++] = x % 10, x /= 10; } while(x);
		while(top) putchar (st[-- top] + '0');
		putchar ('\n');
	}
} using namespace FASTIO;
constexpr int MAXN = 1.5e5 + 10;
int n = 0, Val[MAXN], Ans = 0;
vector <int> edge[MAXN];
inline void Addedge (int u, int v) {
	edge[u].push_back (v);
	edge[v].push_back (u);
}

namespace LiChaoTree {
	struct Line {
		int k, b;
		Line (int k = 0, int b = -1e18):k(k), b(b){};
		int getL (int x) { return k * x + b; }
	};
	struct SMT {
		int l, r;
		Line ln;
		bool isCover;
		SMT (int l, int r, Line ln, bool isCover):l(l), r(r), ln(ln), isCover(isCover){};
		SMT (){};
	} Seg[MAXN << 2];
	#define lson (rt << 1)
	#define rson (rt << 1 | 1)
	void Build (int l, int r, int rt) {
		Seg[rt] = SMT (l, r, Line(), false);
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		Build (l, mid, lson);
		Build (mid + 1, r, rson);
	}
	void Update (int rt, Line lnx) {
		int l = Seg[rt].l, r = Seg[rt].r;
		if (l == r) {
			if (Seg[rt].ln.getL(l) < lnx.getL(l))
				Seg[rt].ln = lnx;
			return;
		}
		int lpos = Seg[rt].ln.getL(l), rpos = Seg[rt].ln.getL(r),
		tmplpos = lnx.getL(l), tmprpos = lnx.getL(r);
		if (!Seg[rt].isCover)
			Seg[rt].ln = lnx, Seg[rt].isCover = true;
		if (tmplpos >= lpos && tmprpos >= rpos) {
			Seg[rt].ln = lnx;
		} else if (tmplpos >= lpos || tmprpos >= rpos) {
			int mid = (l + r) >> 1;
			if (Seg[rt].ln.getL(mid) < lnx.getL(mid)) swap (Seg[rt].ln, lnx);
			if (Seg[rt].ln.getL(l) < lnx.getL(l)) {
				Update (lson, lnx);
			} else {
				Update (rson, lnx);
			}
		}
	}
	void ClearTree (int rt) {
		int l = Seg[rt].l, r = Seg[rt].r;
		if (!Seg[rt].ln.k && Seg[rt].ln.b == -1e18) {
			return;
		} else {
			Seg[rt].ln = Line();
		}
		if (l == r)
			return;
		ClearTree (lson), ClearTree (rson);
	}
	int Query (int pos, int rt) {
		int l = Seg[rt].l, r = Seg[rt].r;
		if (l == r)
			return Seg[rt].ln.getL(pos);
		int mid = (l + r) >> 1, tmpVal = Seg[rt].ln.getL(pos);
		if (pos <= mid) {
			tmpVal = max (tmpVal, Query (pos, lson));
		} else {
			tmpVal = max (tmpVal, Query (pos, rson));
		}
		return tmpVal;
	}
	#undef lson
	#undef rson
} using namespace LiChaoTree;

namespace DivTree {
	int Siz[MAXN], F[MAXN], rt = 0, SumA[MAXN], _SumA[MAXN], SumB[MAXN], _SumB[MAXN], totSiz = 0;
	bool tag[MAXN];
	void findrt (int u, int fa) {
		Siz[u] = 1, F[u] = 0;
		for (int v : edge[u]) {
			if (v == fa || tag[v])
				continue;
			findrt (v, u);
			Siz[u] += Siz[v];
			F[u] = max (F[u], Siz[v]);
		}
		F[u] = max (F[u], totSiz - Siz[u]);
		if (!rt || F[u] < F[rt]) rt = u;
	}
	void getSum (int u, int fa, int _len) {
		for (int v : edge[u]) {
			if (v == fa || tag[v])
				continue;
			SumA[v] = SumA[u] + Val[v];
			SumB[v] = SumB[u] + SumA[v];
			_SumA[v] = _SumA[u] + Val[v];
			_SumB[v] = _SumB[u] + _len * Val[v];
			getSum (v, u, _len + 1);
		}
	}
	void dfsQuery (int u, int fa, int _len) {
		Ans = max (Ans, SumB[u]);
		Ans = max (Ans, _SumB[u] + _SumA[u] + Val[rt]);
		Ans = max (Ans, Query (_len, 1) + _SumA[u] * (_len + 1) - _SumB[u]);
		for (int v : edge[u]) {
			if (v == fa || tag[v])
				continue;
			dfsQuery (v, u, _len + 1);
		}
	}
	void dfsUpdate (int u, int fa, int len) {
		Update (1, Line (SumA[u], SumA[u] * (len + 1) - SumB[u]));
		for (int v : edge[u]) {
			if (v == fa || tag[v])
				continue;
			dfsUpdate (v, u, len + 1);
		}
	}
	void Solve (int u) {
		rt = u, tag[u] = true;
		SumA[u] = SumB[u] = Val[u], _SumA[u] = _SumB[u] = 0;
		Ans = max (Ans, Val[u]), getSum (u, 0, 1), ClearTree(1);
		for (int v : edge[u]) {
			if (tag[v])
				continue;
			dfsQuery (v, u, 1), dfsUpdate (v, u, 2);
		}
		reverse (edge[u].begin(), edge[u].end()), ClearTree(1);
		for (int v : edge[u]) {
			if (tag[v])
				continue;
			dfsQuery (v, u, 1), dfsUpdate (v, u, 2);
		}
		for (int v : edge[u]) {
			if (tag[v])
				continue;
			rt = 0, totSiz = Siz[v];
			findrt (v, u), Solve(rt);
		}
	}
} using namespace DivTree;

signed main() {
	n = read();
	for (int i = 1, u, v; i < n; i ++) {
		u = read(), v = read();
		Addedge (u, v);
	}
	for (int i = 1; i <= n; i ++) 
		Val[i] = read();
	rt = 0, totSiz = n, findrt (1, 0);
	Build (1, n, 1), Solve(rt);
	write (Ans);
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

很复杂的综合题。看到路径，考虑点分治。然后看如何处理这个式子。

记 $u$ 的点权为 $val(u)$。点分治到每一层，进行一次 DFS，每个结点预处理出 $6$ 个值：
- $presum(u)$，从当前根到点 $u$ 作为路径的前半段，不包含当前根的 $\sum val(u)$；
- $pred(u)$，从当前根到点 $u$ 作为路径的前半段，不包含当前根，要经过多少个点；
- $predsum(u)$，从当前根到点 $u$ 作为路径的前半段，不包含当前根的 $\sum val(u)\cdot pred(u)$；
- $sufsum(u)$，从当前根到点 $u$ 作为路径的后半段，包含当前根的 $\sum val(u)$；
- $sufd(u)$，从当前根到点 $u$ 作为路径的后半段，包含当前根，要经过多少个点；
- $sufdsum(u)$，从当前根到点 $u$ 作为路径的后半段，包含当前根的 $\sum val(u)\cdot sufd(u)$。

那么，一条路径 $u\rightarrow rt\rightarrow v$ 的权值可以表示为：
$$
presum(u)\cdot sufd(v)+predsum(u)+sufsum(v)\cdot (sufd(v)+1)-sufdsum(v)
$$
前面的 $presum(u)\cdot sufd(v)+predsum(u)$ 可以看成一次函数，$sufd(v)$ 是自变量，放到李超树上维护。查询就是当 $x=sufd(v)$ 时的最大函数值。

由于始末点的顺序对路径权值很有影响，需要把邻接表反转后再做一次。有一个小特判需要注意，我在代码中标了注释，不然会被最后一个点 Hack 掉。

```cpp
// Title:  Sum of Prefix Sums
// Source: CF1303G
// Author: Jerrywang
#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=150010;
using namespace std;

struct line
{
    ll k, b;
    line(){}
    line(ll _k, ll _b){k=_k, b=_b;}
} a[N]; int n, t[N<<2], cnt;
ll f(int i, ll x) {return a[i].k*x+a[i].b;}
#define lc p<<1
#define rc p<<1|1
void modify(int p, int L, int R, int i, int l=1, int r=n)
{
    if(l==r)
    {
        if(f(i, l)>f(t[p], l)) t[p]=i;
        return;
    }
    int mid=l+r>>1;
    if(L<=l && r<=R)
    {
        if(f(i, l)>f(t[p], l) && f(i, r)>f(t[p], r))
        {
            t[p]=i; return;
        }
        if(f(i, l)<=f(t[p], l) && f(i, r)<=f(t[p], r))
            return;
        if(a[i].k>a[t[p]].k)
        {
            if(f(i, mid)>f(t[p], mid))
                modify(lc, L, R, t[p], l, mid), t[p]=i;
            else modify(rc, L, R, i, mid+1, r);
        }
        else
        {
            if(f(i, mid)>f(t[p], mid))
                modify(rc, L, R, t[p], mid+1, r), t[p]=i;
            else modify(lc, L, R, i, l, mid);
        }
        return;
    }
    if(L<=mid) modify(lc, L, R, i, l, mid);
    if(R>mid)  modify(rc, L, R, i, mid+1, r);
}
ll query(int p, int x, int l=1, int r=n)
{
    if(l==r) return f(t[p], x);
    int mid=l+r>>1;
    if(x<=mid) return max(f(t[p], x), query(lc, x, l, mid));
    return max(f(t[p], x), query(rc, x, mid+1, r));
}

int sz[N], mn, all, rt; bool vis[N]; vector<int> g[N];
ll val[N], presum[N], predsum[N], pred[N], sufsum[N], sufdsum[N], sufd[N], ans;
void core(int u, int fa)
{
    sz[u]=1; int mx=0;
    for(int v:g[u]) if(!vis[v] && v!=fa)
        core(v, u), mx=max(mx, sz[v]), sz[u]+=sz[v];
    mx=max(mx, all-sz[u]);
    if(mx<mn) mn=mx, rt=u;
}
int getcore(int u)
{
    mn=1e9, all=sz[u]; core(u, 0); return rt;
}

void calcdis(int u, int fa)
{
    for(int v:g[u]) if(!vis[v] && v!=fa)
    {
        pred[v]=pred[u]+1;
        sufd[v]=sufd[u]+1;
        presum[v]=presum[u]+val[v];
        sufsum[v]=sufsum[u]+val[v];
        predsum[v]=predsum[u]+val[v]*pred[v];
        sufdsum[v]=sufdsum[u]+val[v]*sufd[v];
        calcdis(v, u);
    }
}

void updans(int u, int fa)
{
    ans=max(ans, sufdsum[u]); // 特判直接从根出发！
    ans=max(ans, query(1, sufd[u])+sufsum[u]*(sufd[u]+1)-sufdsum[u]);
    for(int v:g[u]) if(!vis[v] && v!=fa)
        updans(v, u);
}

void adddis(int u, int fa)
{
    a[++cnt]=line(presum[u], predsum[u]);
    modify(1, 1, n, cnt);
    for(int v:g[u]) if(!vis[v] && v!=fa)
        adddis(v, u);
}
void Clear()
{
    rep(i, 1, cnt) a[i].k=0, a[i].b=-1e9;
    cnt=0;
}
void dfs(int u)
{
    vis[u]=1;
    presum[u]=predsum[u]=pred[u]=0;
    sufsum[u]=sufdsum[u]=val[u]; sufd[u]=1;
    calcdis(u, 0);
    Clear();
    for(int v:g[u]) if(!vis[v])
    {
        updans(v, u);
        adddis(v, u);
    }
    reverse(g[u].begin(), g[u].end());
    Clear();
    for(int v:g[u]) if(!vis[v])
    {
        updans(v, u);
        adddis(v, u);
    }
    for(int v:g[u]) if(!vis[v])
        dfs(getcore(v));
}

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    rep(i, 2, n)
    {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v), g[v].push_back(u);
    }
    rep(i, 1, n) scanf("%lld", val+i);
    sz[1]=n; dfs(getcore(1));
    printf("%lld", ans);
    
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

树上大规模路径统计问题，使用点分治。

我们想要把两条路径拼起来。

记录一下：

- `pre[u]` 表示 $u$ 到分治中心的点权前缀和；
- `prew1[u]` 表示 $dep_ua_u+dep_{fa_u}a_{fa_u} + \dots+dep_{rt}a_{rt}$，其中 $dep_{rt}=0$；
- `prew2[u]` 表示 $pre_u + pre_{fa_u} + \dots + pre_{rt}$。

那么路径 $v \to rt \to u$ 的答案就是：

$$
prew2_v+(dep_v+1) \times (pre_u - a_{rt})+prew1_u
$$

发现，设 $f_u(x) = (pre_u-a_{rt})x+prew1_u$，那么答案是 $f_u(dep_v+1) + prew2_v$。

使用李超树维护即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid (l+r>>1)
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=150000+10;
namespace DS {
	int tot,rt;
	struct Segment {ll k,b;ll f(ll x) {return k*x+b;}};
	struct Node {int lson,rson;Segment s;}t[MAXN<<2];
	void init(void) {
		ffor(i,1,tot) t[i]={0,0,{0,0}};
		return rt=tot=0,void();
	}
	void insert(int& u,int l,int r,Segment x) {
		if(!u) return u=++tot,t[u]={0,0,x},void();
		if(t[u].s.f(mid)<x.f(mid)) swap(t[u].s,x);
		if(l!=r) {
			if(t[u].s.k<=x.k) insert(t[u].rson,mid+1,r,x);
			else insert(t[u].lson,l,mid,x);
		}
		return ;
	}
	ll query(int u,int l,int r,int p) {
		if(!u) return -0x3f3f3f3f3f3f3f3f;
		if(l!=r) {
			if(p<=mid) return max(query(t[u].lson,l,mid,p),t[u].s.f(p));
			else return max(query(t[u].rson,mid+1,r,p),t[u].s.f(p));
		}
		return t[u].s.f(p);
	}
};
int n,flg[MAXN],a[MAXN],dep[MAXN];
ll ans,pre[MAXN],wpre1[MAXN],wpre2[MAXN];
vector<int> G[MAXN];
int sze[MAXN],mx[MAXN];
void dfs(int u,int f) {
	sze[u]=1,mx[u]=0;
	for(auto v:G[u]) if(v!=f&&!flg[v]) dfs(v,u),mx[u]=max(mx[u],sze[v]),sze[u]+=sze[v];
	return ;
}
int find_core(int u,int f,int al) {
	if(max(al-sze[u],mx[u])<=al/2) return u;
	for(auto v:G[u]) if(v!=f&&!flg[v]) {
		int tans=find_core(v,u,al);
		if(tans!=-1) return tans;
	}
	return -1;
}
void prep(int u,int f) {
	pre[u]=a[u]+pre[f];
	if(f) dep[u]=dep[f]+1,wpre1[u]=wpre1[f]+1ll*a[u]*dep[u],wpre2[u]=wpre2[f]+pre[u];
	else dep[u]=0,wpre1[u]=0,wpre2[u]=a[u];
	for(auto v:G[u]) if(v!=f&&!flg[v]) prep(v,u);	
	return ;
}
void add_upd(int u,int f,int anc) {
	DS::insert(DS::rt,0,n,{pre[u]-a[anc],wpre1[u]});
	for(auto v:G[u]) if(v!=f&&!flg[v]) add_upd(v,u,anc);
	return ;
}
void add_inf(int u,int f) {
	ans=max(ans,wpre2[u]),ans=max(ans,wpre1[u]+pre[u]),ans=max(ans,DS::query(DS::rt,0,n,dep[u]+1)+wpre2[u]);
	for(auto v:G[u]) if(v!=f&&!flg[v]) add_inf(v,u);
	return ;
}
int cnt;
void solve(int u) {
	dfs(u,0),u=find_core(u,0,sze[u]);
	prep(u,0),DS::init(); dfs(u,0);
	for(auto v:G[u]) if(!flg[v]) add_inf(v,u),add_upd(v,u,u);
	DS::init(),reverse(G[u].begin(),G[u].end());
	for(auto v:G[u]) if(!flg[v]) add_inf(v,u),add_upd(v,u,u);
	flg[u]=1;
	for(auto v:G[u]) if(!flg[v]) solve(v);
	return ; 
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; 
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	ffor(i,1,n) cin>>a[i];
	ans=*max_element(a+1,a+n+1);
	solve(1);
	cout<<ans;
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1303/problem/G) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1303G)

个人感觉这题称不上毒瘤。

首先看到选一条路径之类的字眼可以轻松想到点分治，也就是我们每次取原树的重心 $r$ 并将路径分为经过重心和不经过重心两类路径。对于第二类路径我们肯定可以在对 $r$ 所有子树进一步分治的过程中将其变成第一类路径，因此我们只用考虑怎样计算第一类路径的贡献即可。

显然对于一条第一类路径 $x\to y$，我们要将其拆成 $x\to r$ 和 $r\to y$ 两部分分别处理，考虑怎样合并这两部分的贡献，我们记 $dep_x$ 为 $x\to r$ 路径上点的个数，$sum_x$ 表示 $x\to r$ 上所有点的权值之和，那么对于 $x\to r$ 上某个点 $z$ 而言，它对和的贡献即为 $(dep_x-dep_z+1)\times a_z$，同理对于 $r\to y$ 上某个点 $z$，它对和的贡献即为 $(dep_x-1+dep_z)\times a_z$，那么我们考虑再设一个 $sum1_x$ 表示 $x\to r$ 路径上所有点的 $(dep_x-dep_z+1)\times a_z$，$sum2_x$ 表示 $x\to r$ 路径上所有点的 $dep_z\times a_z$ 之和。对于 $x$ 的某个儿子 $y$，显然有 $sum1_y=sum1_x+sum_y,sum2_y=sum2_x+dep_ya_y$。

因此上面 $x\to y$ 路径的权值就可以写作 $sum1_x+(dep_x-1)sum_y+sum2_y$，但注意到 $r$ 既在 $x\to r$ 的路径上也在 $r\to y$ 的路径上，它的贡献被计算了两次，因此需减去 $dep_xa_r$，得到 $sum1_x+(dep_x-1)sum_y+sum2_y-dep_xa_r$，考虑怎样快速维护这个东西，我们显然要枚举 $x,y$ 中的一个并快速维护另一个变量的决策，那么我们枚举什么好呢？注意到如果我们枚举 $y$，那么我们相当于求若干条形如 $f_x(t)=(dep_x-1)t+sum1_x-dep_xa_r$ 的直线在 $t=sum_y$ 处的最大值，而 $sum_y$ 的值域过大不好直接李超线段树，要写个动态凸壳，过于毒瘤，因此考虑枚举 $x$，这样相当于我们要求若干条形如 $f_y(t)=sum_y·t+sum2_y$ 的直线在 $t=dep_x-1$ 处的最大值，这个值域是在 $[0,n-1]$ 范围内的，就可以李超线段树维护了。

算下复杂度，点分 1log，李超线段树全局插入是 1log 的，因此总复杂度 2log，可以通过此题。

最后说几个注意点：

1. 在点分治过程中注意要正反各跑一遍，因为假设按顺序枚举的子树依次是 $t_1,t_2,\cdots,t_m$，那么对于某个 $i<j$，有可能是 $x\in t_i,y\in t_j$，也有可能 $x\in t_j,y\in t_i$。
2. 每次点分完一个点后要清空李超树，但重新建树复杂度过高，因此可以考虑将修改的点记录在一个 `std::vector` 中每次将 `vector` 中的点的最大优势线段赋为空即可。

```cpp
const int MAXN=1.5e5;
const ll INF=0x3f3f3f3f3f3f3f3fll;
int n,a[MAXN+5],hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
struct line{
	ll k,b;
	line(ll _k=0,ll _b=-INF):k(_k),b(_b){}
	ll get(int x){return 1ll*k*x+b;}
};
struct node{int l,r;line v;} s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r) return;
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
vector<int> opts;
void modify(int k,line v){
	int mid=s[k].l+s[k].r>>1;
	ll l1=s[k].v.get(s[k].l),r1=s[k].v.get(s[k].r),m1=s[k].v.get(mid);
	ll l2=v.get(s[k].l),r2=v.get(s[k].r),m2=v.get(mid);
	if(l1>=l2&&r1>=r2) return;
	if(l2>=l1&&r2>=r1) return s[k].v=v,opts.pb(k),void();
	if(m2>=m1){
		if(l2<l1) return modify(k<<1,s[k].v),s[k].v=v,void();
		else return modify(k<<1|1,s[k].v),s[k].v=v,void();
	} else {
		if(l2<l1) return modify(k<<1|1,v),void();
		else return modify(k<<1,v),void();
	}
}
ll query(int k,int x){
	if(s[k].l==s[k].r) return s[k].v.get(x);int mid=s[k].l+s[k].r>>1;
	return max(s[k].v.get(x),(x<=mid)?query(k<<1,x):query(k<<1|1,x));
}
bool vis[MAXN+5];int siz[MAXN+5],mx[MAXN+5],cent=0,subsiz[MAXN+5];
ll ans=0,sum[MAXN+5],_sum[MAXN+5],__sum[MAXN+5];int dep[MAXN+5];
void findcent(int x,int f,int tot){
	siz[x]=1;mx[x]=0;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||vis[y]) continue;
		findcent(y,x,tot);siz[x]+=siz[y];
		chkmax(mx[x],siz[y]);
	} chkmax(mx[x],tot-siz[x]);
	if(mx[x]<mx[cent]) cent=x;
}
vector<int> pts;
void getdis(int x,int f){
	pts.pb(x);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||vis[y]) continue;
		dep[y]=dep[x]+1;sum[y]=sum[x]+a[y];
		_sum[y]=_sum[x]+sum[y];
		__sum[y]=__sum[x]+1ll*a[y]*dep[y];
		getdis(y,x);
	}
}
void divcent(int x){
	vis[x]=1;chkmax(ans,a[x]);dep[x]=1;
	sum[x]=_sum[x]=__sum[x]=a[x];
	modify(1,line(sum[x],__sum[x]));
	stack<int> stk;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(vis[y]) continue;
		sum[y]=sum[x]+a[y];dep[y]=2;
		_sum[y]=sum[x]+a[x]+a[y];
		__sum[y]=sum[x]+(a[y]<<1);
		pts.clear();getdis(y,x);subsiz[y]=pts.size();
		for(int i=0;i<pts.size();i++){
			int z=pts[i];
			chkmax(ans,_sum[z]+query(1,dep[z]-1)-1ll*a[x]*dep[z]);
		}
		for(int i=0;i<pts.size();i++){
			int z=pts[i];
			modify(1,line(sum[z],__sum[z]));
		} stk.push(y);
	}
	for(int i=0;i<opts.size();i++) s[opts[i]].v=line();
	opts.clear();
	while(!stk.empty()){
		int y=stk.top();stk.pop();
		pts.clear();getdis(y,x);
		for(int i=0;i<pts.size();i++){
			int z=pts[i];
			chkmax(ans,_sum[z]+query(1,dep[z]-1)-1ll*a[x]*dep[z]);
		}
		for(int i=0;i<pts.size();i++){
			int z=pts[i];
			modify(1,line(sum[z],__sum[z]));
		}
	} chkmax(ans,_sum[x]+query(1,0)-a[x]);
	for(int i=0;i<opts.size();i++) s[opts[i]].v=line();
	opts.clear();
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(vis[y]) continue;
		cent=0;findcent(y,x,subsiz[y]);
		divcent(cent);
	} 
}
int main(){
	scanf("%d",&n);mx[0]=1e9;build(1,0,n);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	findcent(1,0,n);divcent(cent);printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：cirnovsky (赞：0)

可以发现那个式子等价于 $\sum_{i=1}^{l}ia_{i}$。

考虑点分，设当前根为 $x$。选出来的 $u,v$ 一定是叶子（点权为正），因为没有什么本质差别，所以可以一起算。我们把 $x$ 在 $(u,v)$ 中的位置记作 $o$，$(u,v)$ 的权值就为 $\sum_{i=1}^{l}ia_{i}=\sum_{i=1}^{o}ia_{i}+l\sum_{i=o+1}^{l}a_{i}+\sum_{i=o+1}^{l}(i-l)a_{i}$，这是个一次函数，令 $b_{1}=\sum_{i=1}^{l}ia_{i}=\sum_{i=1}^{o}ia_{i},b_{2}=\sum_{i=o+1}^{l}(i-l)a_{i},k=l$，得 $\sum_{i=1}^{l}ia_{i}=k\times\sum_{i=o+1}^{l}a_{i}+b_{1}+b_{2}$。

[Code](https://paste.ubuntu.com/p/sfYznyMmVQ/)

---

## 作者：1saunoya (赞：0)

## 题意:

选出一条链 $[u \to v]$，每个点有个权值，然后求  $\max{\sum s_i}$，$s_i$ 为路径前缀和。

首先路径问题先想到点分治，然后考虑如何链上计算这个贡献，如果当前重心为 $x$，我们选出了两个点 $u,v$ ，非常显然 $u,v$ 都是叶子结点。
~~（证明略）~~

然后一部分的贡献是 $[u \to x]$，另一部分怎么算呢？（指 $[x \to v]$），我们先忽略左边的长度给他带来的贡献，把本身贡献计算一下，然后很显然，这个可以把 $\sum a_i [i \in [x \to v]]$ 记下来，然后就变成了一个 $kx+b$ 的形式，就可以李超树/动态凸包了。

也就是 $k \times \sum a_i [x \to v] + \sum s_i [x \to v] + \sum s_i[u \to x]$

然后枚举即可。

由于我菜的可怜不会动态凸包，所以写了个李超树。

```cpp
#include <bits/stdc++.h> 
using namespace std;
#define int long long
int read() {
	int x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + (c - 48), c = getchar();
	return x;
}
int n;
const int maxn = 2e5 + 52;
int a[maxn], deg[maxn];
vector <int> g[maxn];
struct Line {
	int k, b; Line(int K = 0, int B = -1e18) : k(K), b(B) {}
	inline int val(int x) { return k * x + b; }
} t[maxn << 2];
void build(int l, int r, int p) {
	t[p] = Line(); if(l == r) return;
	int mid = l + r >> 1; build(l, mid, p << 1); build(mid + 1, r, p << 1 | 1);
}
void mdf(int l, int r, int p, Line x) {
	int lx = x.val(l), ly = t[p].val(l), rx = x.val(r), ry = t[p].val(r);
	if(lx <= ly && rx <= ry) return;
	if(lx >= ly && rx >= ry) { t[p] = x; return; }
	int mid = l + r >> 1, midx = x.val(mid), midy = t[p].val(mid);
	if(midx > midy) swap(t[p], x); x.k < t[p].k ? mdf(l, mid, p << 1, x) : mdf(mid + 1, r, p << 1 | 1, x); 
}
int qry(int l, int r, int p, int x) {
	int ans = t[p].val(x), mid = l + r >> 1;
	if(l == r) return ans;
	return max(ans, x <= mid ? qry(l, mid, p << 1, x) : qry(mid + 1, r, p << 1 | 1, x));
}
int fr[maxn], pos[maxn], tp = 0, upk[maxn], upb[maxn], dwn[maxn];
void add(int f, int sum ,int up, int dw, int d) { fr[++ tp] = f; upk[tp] = sum;  upb[tp] = up; dwn[tp] = dw; pos[tp] = d; }
int rt, tot, mxrt, vis[maxn], sz[maxn], dep[maxn];
void frt(int u, int p) {
	int mxs = 0; sz[u] = 1;
	for(int v: g[u]) if(!vis[v] && v ^ p) { frt(v, u); sz[u] += sz[v]; mxs = max(mxs, sz[v]); }
	mxs = max(mxs, tot - sz[u]); if(mxs < mxrt) { rt = u; mxrt = mxs; }
}
int leaf[maxn];
void DFS(int u, int p, int f, int sum, int up, int dw) {
	dep[u] = dep[p] + 1; if(u != rt && !f) { f = u; } if(deg[u] == 1) add(f, sum - a[rt], up, dw, dep[u]), leaf[u] = 1;
	for(int v: g[u]) if(!vis[v] && v ^ p) DFS(v, u, f, sum + a[v], up + dep[u] * a[v], dw + sum + a[v]), leaf[u] += leaf[v];
}
int ans = 0;
void solve(int u) {
	tp = 0; DFS(u, 0, 0, a[u], 0, a[u]); int mxd = *max_element(pos + 1, pos + tp + 1);
	build(1, mxd, 1);
	for(int i = 1, j; i <= tp; i = j) {
		for(j = i; j <= tp && fr[j] == fr[i]; ++ j) ans = max(ans, qry(1, mxd, 1, pos[j]) + dwn[j]);
		for(j = i; j <= tp && fr[j] == fr[i]; ++ j) mdf(1, mxd, 1, Line(upk[j], upb[j]));
	}
	build(1, mxd, 1);
	for(int i = tp, j; i >= 1; i = j) {
		for(j = i; j >= 1 && fr[j] == fr[i]; -- j) ans = max(ans, qry(1, mxd, 1, pos[j]) + dwn[j]);
		for(j = i; j >= 1 && fr[j] == fr[i]; -- j) mdf(1, mxd, 1, Line(upk[j], upb[j]));
	}
	vis[u] = 1; int osz = tot;
	for(int v: g[u]) if(!vis[v] && leaf[v] >= 2) { mxrt = tot = sz[v] < sz[u] ? sz[v] : osz - sz[u]; frt(v, u), solve(rt); }
}
#define pb push_back
signed main() {
	n = read();
	for(int i = 1 ; i < n ; i ++) { int u = read(), v = read(); g[u].pb(v), g[v].pb(u), deg[u]++, deg[v]++; }
	for(int i = 1 ; i <= n ; i ++) a[i] = read(); tot = mxrt = n; frt(1, 0), solve(rt);
	cout << ans << '\n';
	return 0;
}
```

---

