# Karen and Supermarket

## 题目描述

On the way home, Karen decided to stop by the supermarket to buy some groceries.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815C/155b4f0d440b0d3ff60763603980cf23ed9ae97d.png)She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to $ b $ dollars.

The supermarket sells $ n $ goods. The $ i $ -th good can be bought for $ c_{i} $ dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given $ n $ coupons. If Karen purchases the $ i $ -th good, she can use the $ i $ -th coupon to decrease its price by $ d_{i} $ . Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all $ i>=2 $ , in order to use the $ i $ -th coupon, Karen must also use the $ x_{i} $ -th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget $ b $ ?

## 说明/提示

In the first test case, Karen can purchase the following $ 4 $ items:

- Use the first coupon to buy the first item for $ 10-9=1 $ dollar.
- Use the third coupon to buy the third item for $ 12-2=10 $ dollars.
- Use the fourth coupon to buy the fourth item for $ 20-18=2 $ dollars.
- Buy the sixth item for $ 2 $ dollars.

The total cost of these goods is $ 15 $ , which falls within her budget. Note, for example, that she cannot use the coupon on the sixth item, because then she should have also used the fifth coupon to buy the fifth item, which she did not do here.

In the second test case, Karen has enough money to use all the coupons and purchase everything.

## 样例 #1

### 输入

```
6 16
10 9
10 5 1
12 2 1
20 18 3
10 2 3
2 1 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 10
3 1
3 1 1
3 1 2
3 1 3
3 1 4
```

### 输出

```
5
```

# 题解

## 作者：feng_chengjie (赞：8)

题目
-------
题意:
有n件商品,每件有价格ci,优惠券di,对于i>=2,使用di的条件为:xi的优惠券需要被使用,问初始金钱为b时 最多能买多少件商品? n<=5000,ci,di,b<=1e9

题解
---
设$dp[u][j][0/1]$是以u为根子树中,u用或者不用优惠券时,选j件物品需要的最小代价  
易得：
$dp[u][sum][1]=min(dp[u][sum][1],dp[u][i][1]+dp[son][sum-i][1])$       
$dp[u][sum][1]=min(dp[u][sum][1],dp[u][i][1]+dp[son][sum-i][0])$
$dp[u][sum][0]=min(dp[u][sum][0],dp[u][i][0]+dp[son][sum-i][0])$
每次枚举子树进行更新，把已经考虑过的前面所有子树看做一个整体，与当前子树共同划分sum个贡献

有细节看代码

代码
---
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
const int maxn=5005;
struct point 
{
	int to;
	int nxt;
}edge[maxn];
struct nod
{
	int aa;
	int pos;
}ah[maxn];
int n,tot,idx;
int ncon;
long long mon;
long long a[maxn],b[maxn],tmp[maxn];
int is[50],c[maxn],head[maxn];
long long f[maxn][maxn][2];
int siz[maxn];
int bin[20];
bool subt_2,ch[maxn];
stack<int> st;

inline void add(int u,int v)
{
	tot++;
	edge[tot].nxt=head[u];
	edge[tot].to=v;
	head[u]=tot;
}


void DP(int x)
{
	siz[x]=1;
	f[x][0][0]=0;
	f[x][1][0]=a[x];
	f[x][1][1]=a[x]-b[x];
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		DP(v);
		for(int i=siz[x];i>=0;i--)//this represents all the sons before
			for(int j=0;j<=siz[v];j++)
			{
				f[x][i+j][0]=min(f[x][i+j][0],f[x][i][0]+f[v][j][0]);	
				f[x][i+j][1]=min(f[x][i+j][1],f[x][i][1]+f[v][j][1]);
				f[x][i+j][1]=min(f[x][i+j][1],f[x][i][1]+f[v][j][0]);
			}
		siz[x]+=siz[v];//prepare for next son_tree
	}
}

void solve()
{
	int M=0;
	memset(f,0x3f3f3f3f,sizeof(f));
	DP(1);
	for(int i=n;i>=1;i--)
		if(f[1][i][1]<=mon || f[1][i][0]<=mon)
			{M=i; break;}
	printf("%d",M);
}


int main()
{
	scanf("%d%d",&n,&mon);
	cin>>a[1]>>b[1];
	subt_2=1;
	for(int i=2;i<=n;i++)
	{
		cin>>a[i]>>b[i]>>c[i];
		if(c[i]!=i-1) subt_2=0;
		add(c[i],i);
	}
	solve();
	return 0;
}


```



---

## 作者：Euler_Pursuer (赞：7)

题目很简单，但是想优化却不容易。

我们可以很明显的列出DP方程，也就是考虑某个优惠券是否使用来转移状态。它使用了，那么依赖它的优惠券可使用可不使用；它没使用，那么依赖它的优惠券就不能使用。参考@[feng_chengjie](https://www.luogu.org/space/show?uid=36294) 的题解，设dp[u][j][0/1]是以u为根子树中,u用或者不用优惠券时,选j件物品需要的最小代价DP方程：

$$dp[u][sum][1]=\min(dp[u][sum][1],dp[u][i][1]+dp[son][sum-i][1])$$
$$dp[u][sum][1]=\min(dp[u][sum][1],dp[u][i][1]+dp[son][sum-i][0])$$
$$dp[u][sum][0]=\min(dp[u][sum][0],dp[u][i][0]+dp[son][sum-i][0])$$

通过枚举一个节点的儿子，转移方程即可。

但是我们发现它的空间复杂度为$O(n^2)$，而且在转移的过程中，某个节点转移完毕之后其DP数组是没用的，也就是这样浪费了很多空间。所以我们可以考虑对某个儿子DP完毕之后，释放掉该儿子占用的空间，我们可以用vector实现。

考虑其空间复杂度的最坏情况，注意到我们每次都是在DP完子树之后才对该节点扩充空间，也就是说每个节点至少要有两个儿子才能对空间产生一定的“浪费”，而每次扩充的空间都是该节点前面的子树的大小，对于当前儿子来说，它扩充的空间又是它的当前考虑的儿子的左兄弟，而我们上述考虑的节点均互不相同，因此累积起来空间复杂度为$O(n)$。当然，vector可能有点小常数，但是实际测试中时间会比优化前更快。

对于vector的释放空间的操作，不是什么clear就能解决的事。因为clear看上去空间清空了，实际上指针还在，你可以试试。实质上的释放空间是用【`vector<类型>().swap(要释放空间的vector变量)`】，扩充空间用【`变量.resize(扩充到多大空间,填充内容)`】。我的程序最慢点耗时187ms，最大空间消耗为1.27MB。

```cpp
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> G[5005];
struct F
{
    long long y, n;
};
vector<F> f[5005];
int c[5005],`d[5005], si[5005], n, q, tot;

inline void add(int a, int b)
{
    G[a].push_back(b);
}

void dfs(int x)
{
    int s = G[x].size(), e;
    long long rr, ss, tt;
    si[x] = 1;
    //f[x].insert(f[x].begin(), n+1, (F){998244353998244353, 998244353998244353});
    f[x].resize(2);
    f[x][0].n = 0;///什么都不用
    f[x][0].y = 998244353998244353;
    f[x][1].y = c[x] - d[x];
    f[x][1].n = c[x];
    ///没有使用优惠券
    ///使用了优惠券
    for(register int i = 0; i < s; i += 1)
    {
        e = G[x][i];
        dfs(e);
        f[x].resize(si[x]+si[e]+1, (F){998244353998244353, 998244353998244353});
        for(register int j = si[x]; j >= 0; j -= 1)
            for(register int k = 0; k <= si[e]; k += 1)
            {
                rr = f[x][j].n+f[e][k].n;
                ss = f[x][j]`y+f[e][k].n;
                tt = f[x][j].y+f[e][k].y;
                if(rr <= tot && f[x][j+k].n > rr)
                    f[x][j+k].n = rr;
                if(ss <= tot && f[x][j+k].y > ss)
                    f[x][j+k].y = ss;
                if(tt <= tot && f[x][j+k].y > tt)
                    f[x][j+k].y = tt;
            }
        vector<F>().swap(f[e]);
        si[x] += si[e];
    }
    //if(!s)
    //    f[x].resize(f[x].begin()+2, n-1, (F){998244353998244353, 998244353998244353});
}

int main()
{
    scanf("%d%d", &n, &tot);
    scanf("%d%d", &c[1], &d[1]);
    for(register int i = 2; i <= n; i += 1)
    {
        scanf("%d%d%d`", &c[i], &d[i], &q);
        add(q, i);
    }
    dfs(1);
    for(register int i = n; i; i -= 1)
    {
        printf("%lld %lld\n", f[1][i].y, f[1][i].n);
        if(f[1][i].y <= tot || f[1][i].n <= tot)
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("0`");//might wrong at here
    return 0;
}
```
-

-

-

抄题解的你绝对过不了。

---

## 作者：Walker_V (赞：6)

# CF815C Karen and Supermarket

树上DP。

首先，考虑建边。显然连一条$x[i]->i$的边。

其次，考虑DP。那么有数组$f[i][j][k]$表示**以$i$为根节点的子树中，选择$j$件物品的代价；$k$代表是否使用折扣**。

最后看输出。那就看以$1$为根节点，选择$ans$件物品，无论打不打折，如果代价小于$b$，则可行。此外，为了使$ans$尽量大，所以我们要从$n$到$1$遍历寻找答案。
```cpp
#include<bits/stdc++.h>
#define N 5010

using namespace std;

int n,b,cnt,ans;
int c[N],d[N],x[N],head[N],siz[N],f[N][N][2]; //f[i][j][k] 以i为根节点的子树中，选择j件物品的代价；k代表是否使用折扣

struct node {
	int nxt,to;
}edge[N];

void addEdge(int u,int v) {
	edge[++cnt]=(node){head[u],v};
	head[u]=cnt;
	return;
}

void Read() {
	scanf("%d%d%d%d",&n,&b,&c[1],&d[1]);
	for(int i=2;i<=n;i++) {
		scanf("%d%d%d",&c[i],&d[i],&x[i]);
		addEdge(x[i],i);
	}
	return;
}

void Init() {
	memset(f,0x3f,sizeof(f));
	return;
}

void DP(int x) {
	siz[x]=1;
	f[x][0][0]=0;
	f[x][1][0]=c[x];
	f[x][1][1]=c[x]-d[x];
	for(int i=head[x];i;i=edge[i].nxt) {
		int v=edge[i].to;
		DP(v);
		for(int i=siz[x];i>=0;i--) {
			for(int j=0;j<=siz[v];j++) {
				//状态转移方程
				f[x][i+j][0]=min(f[x][i+j][0],f[x][i][0]+f[v][j][0]);
				f[x][i+j][1]=min(f[x][i+j][1],f[x][i][1]+f[v][j][0]);
                f[x][i+j][1]=min(f[x][i+j][1],f[x][i][1]+f[v][j][1]);
			}
		}
		siz[x]+=siz[v];
	}
	return;
}

void Print() {
	for(int i=n;i>=1;i--) {
		if(f[1][i][0]<=b||f[1][i][1]<=b) {
			ans=i;
			break;
		}
	}
	printf("%d",ans);
	return;
}

int main()
{
	Read();
	Init();
	DP(1);
	Print();
	return 0;
}
```

---

## 作者：shinzanmono (赞：3)

看到这题第一眼：这不是背包吗。瞟了一眼数据范围：$B,c_i,d_i\leq10^9$……

于是老套路，互换维度。定义 $f_{u,i,0/1}$ 表示点前搜索到的结点是 $u$，在 $u$ 的结点中选择 $i$ 个点，且是否使用优惠券的最小价格。

转移：

$$
\begin{aligned}
&f_{u,i+j,0}=\min_{v\in son_u}\left\{f_{u,i,0}+f_{v,j,0}\right\}\\
&f_{u,i+j,1}=\min_{v\in son_u}\left\{f_{u,i,1}+\min(f_{v,j,0},f_{v,j,1})\right\}
\end{aligned}
$$

最后降序枚举答案即可。

时空复杂度 $O(n^2)$。


---

## 作者：Fireworks_Rise (赞：3)

# 思路

题目比较容易理解，难点在于如何优化时间复杂度，虽然给出的时间限制为 $2s$，但是一不小心还是会爆炸。

浅浅分析题目，可以发现这妥妥是一道树形背包类的题型。

如没有学过树形 DP，可参考本蒟蒻的另一篇文章[【动态规划 & 树形 dp】Tree  DP](https://www.luogu.com.cn/blog/Fireworks-Rise/post-dong-tai-gui-hua-shu-xing-dptree-dp)。

设 $f_{u,j,0/1}$ 表示以 $u$ 为根的子树中，当前商品是否使用优惠券时，选 $j$ 件物品需要的最小代价。

则可推出转移式为：

$\begin{cases}
f_{u,i,0}=\min(f_{u,i,0},f_{u,i-j,0}+f_{v,j,0}) \\
f_{u,i,1}=\min(f_{u,i,1},f_{u,i-j,1}+\min(f_{v,j,1},f_{v,j,0}))
\end{cases}$

优化部分（重点）：

如果直接暴力背包， $O(n^3)$ 肯定爆，学过树形背包 $O(n^2)$ 优化的都知道，需要用 $sz_u$ 记录以 $u$ 为根的子树中的节点个数，优化背包循环的上下界，从而省略无意义的操作，实现过程在此就不再一一赘述...

注意： $sz_u$ 应该是先用再加上 $sz_v$，不得先加再用，否则时间复杂度会增加回到 $O(n^3)$。

所以可以把转移方程式修改为：

$\begin{cases}
f_{u,i+j,0}=\min(f_{u,i+j,0},f_{u,i,0}+f_{v,j,0}) \\
f_{u,i+j,1}=\min(f_{u,i+j,1},f_{u,i,1}+\min(f_{v,j,1},f_{v,j,0}))
\end{cases}$

# Code

细节看代码...

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int n,x[N],b,c[N],d[N];
struct Node {
	int to,nxt;
	Node() {
		to=nxt=0;
	}
	Node(int a,int b) {
		to=a;
		nxt=b;
	}
}adj[N<<1];
int head[N],idx;
int sz[N],f[N][N][2];
void add(int x,int y) {
	adj[++idx]=Node(y,head[x]);
	head[x]=idx;
}
void dfs(int u) {
	sz[u]=1;
	f[u][0][0]=0;
	f[u][1][0]=c[u];
	f[u][1][1]=c[u]-d[u];
	for(int k=head[u];k;k=adj[k].nxt) {
		int v=adj[k].to;
		dfs(v);
		for(int i=sz[u];i>=0;i--) {
			for(int j=0;j<=sz[v];j++) {
				f[u][i+j][0]=min(f[u][i+j][0],f[u][i][0]+f[v][j][0]);
				f[u][i+j][1]=min(f[u][i+j][1],f[u][i][1]+min(f[v][j][1],f[v][j][0]));
			}
		}
		sz[u]+=sz[v];
	}
}
signed main() {
	scanf("%d%d",&n,&b);
	cin>>c[1]>>d[1];
	for(int i=2;i<=n;i++) {
		cin>>c[i]>>d[i]>>x[i];
		add(x[i],i);
	}
	memset(f,0x3f3f3f3f,sizeof f);
	dfs(1);
	int ans=0;
	for(int i=n;i>=1;i--) {
		if(f[1][i][1]<=b||f[1][i][0]<=b) {
			ans=i;
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：神眷之樱花 (赞：2)

# 题解
不难发现题目中的优惠构成了树形依赖关系，且数据保证了每个节点的 $fa\leq i$，所以这是一棵以 $1$ 为根节点的树。

所以我们考虑树形背包。

一般树形背包第二维的状态设成花费，但是因为 $b$ 很大，所以显然不能这样设。

但是因为每个物品只能买一次，且我们计算答案的时候，每个物品的贡献都记为 $1$， 所以当贡献一定的时候，花费越小越优。

所以我们可以把状态设为 $dp[x][j]$ 表示在以 $x$ 为根的子树中买 $j$ 个物品的最小花费，然后枚举 $dp[1][j]$ 如果它的花费小于 $b$，再用 $j$ 去更新答案即可。

但是如果当根节点优惠之后的价格很高时，可能会出现在这棵子树内即使全部不使用优惠，也比根节点使用优惠再在子树中买更优。

也就是说根节点使不使用优惠是有区别的。

所以我们把状态设计成 $dp[x][j][0/1]$ 表示根节点不使用和使用优惠券，在包括 $x$ 的子树中买 $j$ 个的最小花费。

其状态转移方程很显然，即（这里把变量名换成了我代码中的变量）：

$$dp[x][t][1] = min_{j = 0}^{t}(dp[x][t - j][1] + dp[y][j][1], dp[x][t - j][1] + dp[y][j][0])$$

$$dp[x][t][0] = min_{j = 0}^{t}(dp[x][t - j][0] +dp[y][j][0])$$

其中 $t$ 为倒序枚举，保证 $dp[x][t - j]$ 没有先被更新过。

但是如果我们的 $t$ 直接从 $n$ 倒序枚举的话，复杂度显然是 $n^3$ 的。

因为每次转移的时候，此时已经枚举，算在了 $x$ 为根的子树内的节点才有用，所以我们从还没有加上 $siz[y]$ 的 $siz[x]$ 开始枚举，使转移时间复杂度变为合法点对数 $n^2$。

注意初始化时的小细节，$dp[x][0][1]$ 是没有意义的，不应该初始化为 $0$。
# 代码
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>

using namespace std;

typedef long long LL;

const int N = 5e3 + 5;

int n, m, siz[N], head[N], nex[N], to[N], c[N], d[N], tot = 1;

inline void add(int x, int y) {
	nex[++ tot] = head[x], to[tot] = y, head[x] = tot;
}

int dp[N][N][2], ans = 0;

inline void dfs(int x) {
	dp[x][0][0] = 0, siz[x] = 1;
	dp[x][1][0] = c[x], dp[x][1][1] = d[x];
	for(int i = head[x], y; i; i = nex[i]) {
		y = to[i];
		dfs(y);
		for(int t = siz[x]; ~t; t--) {
			for(int j = 1; j <= siz[y]; j++) {
				dp[x][t + j][1] = min(dp[x][t + j][1], dp[x][t][1] + dp[y][j][1]);
				dp[x][t + j][1] = min(dp[x][t + j][1], dp[x][t][1] + dp[y][j][0]);
				dp[x][t + j][0] = min(dp[x][t + j][0], dp[x][t][0] + dp[y][j][0]);
			}
		}
		siz[x] += siz[y];
	}
}

inline void read(int &x) {
	x = 0; int c = getchar(), f = 1;
	for(; !isdigit(c); c = getchar())
		if(c == '-') f = -1;
	for(; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	x *= f;
}

int main() {
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	read(n), read(m);
	read(c[1]), read(d[1]);
	d[1] = c[1] - d[1];
	for(int i = 2, f; i <= n; i++) {
		read(c[i]), read(d[i]), read(f);
		add(f, i); d[i] = c[i] - d[i];
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			dp[i][j][0] = dp[i][j][1] = m + 1;
	dfs(1);
	for(int i = 0; i <= siz[1]; i++)
		if(dp[1][i][0] <= m || dp[1][i][1] <= m)
			ans = i;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：nomonick (赞：2)

[CF815C Karen and Supermarket](https://www.luogu.com.cn/problem/CF815C)

原题网址：[Codeforces Round #419 (Div. 1)C. Karen and Supermarket](https://codeforces.com/problemset/problem/815/C)

很明显是在零一背包加维操作， $DP$ 的思路很好想，假设一个数字，存储在选第几个物品时，已经有几个被选了，且考虑用不用优惠券，即：

$$
dp[i][sum][0/1]
$$

但是数据量略大，不可以直接操作，要对其进行优化。考虑其有 $n$ 件物品， $n-1$ 个优惠券使用条件，于是考虑树形 $DP$ 。

针对于一个新发现的子树我可以选择部分节点买入，对于原有子树也是同理，所以构建一个以 $1$ 为根节点的子树，同时也要记录子树大小。

而该点要是要使用优惠券，则字数内至少有一个子树有用优惠劵。

结合这个思路得出状态转移方程为：

$$
dp[u][i+j][0] = \min(dp[u][i+j][0],dp[u][i][0]+dp[v][j][0])
$$
$$
dp[u][i+j][1] = \min(dp[u][i+j][1],dp[u][i][1]+dp[v][j][1])
$$
$$
dp[u][i+j][1] = \min(dp[u][i+j][1],dp[u][i][1]+dp[v][j][0])
$$

# code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 5050;

inline int read()
{
	int x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

int n,money,num_edge;
int num[SIZE],low[SIZE],son[SIZE],head[SIZE],siz[SIZE];
int dp[SIZE][SIZE][2];
struct node
{
	int to,nxt;
};
node edge[SIZE];

inline void add(int u,int v)
{
	edge[++num_edge].to = v;
	edge[num_edge].nxt = head[u];
	head[u] = num_edge;
}

void dfs(int u)
{
	siz[u] = 1;
	dp[u][0][0] = 0;
	dp[u][1][0] = num[u];
	dp[u][1][1] = num[u] - low[u];
	for (int i = head[u]; i ; i = edge[i].nxt)
	{
		int v = edge[i].to;
		dfs(v);
		for (int j = siz[u]; j >= 0; --j)
		{
			for (int k = 0; k <= siz[v]; ++k)
			{
				dp[u][j+k][0] = min(dp[u][j+k][0],dp[u][j][0]+dp[v][k][0]);
				dp[u][j+k][1] = min(dp[u][j+k][1],dp[u][j][1]+dp[v][k][1]);
				dp[u][j+k][1] = min(dp[u][j+k][1],dp[u][j][1]+dp[v][k][0]);
			}
		}
		siz[u] += siz[v];
	}
}

int main()
{
	n = read();money = read();
	num[1] = read();low[1] = read();
	for (int i = 2; i <= n; ++i)
	{
		num[i] = read();low[i] = read();son[i] = read();
		add(son[i],i);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][1][1] = num[1] - low[1];
	dfs(1);
	for (int i = n; i >= 1; --i)
	{
		if (dp[1][i][1] <= money || dp[1][i][0] <= money)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
```

---

## 作者：chihik (赞：2)


因为使用优惠劵就必须买这件商品，我们可以将优惠劵的关系看成一棵树。

令 $dp[u][i][0/1]$ 表示 以 $u$ 为根的子树 ， 购买 $i$ 件商品 ， $u$ 是否使用优惠劵的最小花费。

边界条件：$dp[u][0][0]=0,dp[u][1][0]=c[u],dp[u][1][1]=c[u]-d[u]$

注意：$dp[u][0][1]$ 是不成立的，因为使用优惠券就必须购买商品，其余设为极大值。

然后有如下转移：

$$\begin{cases}
dp[ u ][ j + k ][ 0 ] = \min( dp[ u ][ j ][ 0 ] + dp[ v ][ k ][ 0 ] )\\
dp[ u ][ j + k ][ 1 ] = \min( dp[ u ][ j ][ 1 ] + \min( dp[ v ][ k ][ 0 ] , dp[ v ][ k ][ 1 ] ) )
\end{cases}$$

最后看满足 $\min(dp[1][k][0],dp[1][k][1])\le b$ 的最大的 $k$ 即可。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

template<typename _T>
void Read( _T &x ) {
	x = 0; int f = 1;
	char s = getchar( );
	for( ; s < '0' || s > '9' ; s = getchar( ) ) f = s == '-' ? -f : f;
	for( ; s >= '0' && s <= '9' ; s = getchar( ) ) x = x * 10 + s - '0';
	x *= f;
}
template<typename _T>
void Write( _T x ) {
	if( x < 0 ) putchar('-') , x = -x;
	if( x >= 10 ) Write( x / 10 );
	putchar( x % 10 + '0' );
} 

const int MAXN = 5000;
int n , m , fa , c[ MAXN + 5 ] , d[ MAXN + 5 ] , Size[ MAXN + 5 ];
int dp[ MAXN + 5 ][ MAXN + 5 ][ 2 ];
vector< int > Graph[ MAXN + 5 ];

void dfs( int u ) {
	Size[ u ] = 1;
	dp[ u ][ 0 ][ 0 ] = 0 , dp[ u ][ 1 ][ 0 ] = c[ u ];
	dp[ u ][ 1 ][ 1 ] = c[ u ] - d[ u ];
	
	for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
		int v = Graph[ u ][ i ];
		dfs( v ); 
		
		for( int j = Size[ u ] ; j >= 0 ; j -- ) //注意循环顺序，不然会超时
			for( int k = 0 ; k <= Size[ v ] ; k ++ ) {
				dp[ u ][ j + k ][ 0 ] = min( dp[ u ][ j + k ][ 0 ] , dp[ u ][ j ][ 0 ] + dp[ v ][ k ][ 0 ] );
				dp[ u ][ j + k ][ 1 ] = min( dp[ u ][ j + k ][ 1 ] , dp[ u ][ j ][ 1 ] + min( dp[ v ][ k ][ 0 ] , dp[ v ][ k ][ 1 ] ) );
			}
		Size[ u ] += Size[ v ];
	}
}

int main( ) {
	Read( n ) , Read( m );
	for( int i = 1 ; i <= n ; i ++ ) {
		Read( c[ i ] ) , Read( d[ i ] );
		if( i >= 2 ) {
			Read( fa );
			Graph[ fa ].push_back( i );
		}
	}
	
	memset( dp , 0x3f , sizeof( dp ) );
	dfs( 1 );
	
	for( int i = n ; i >= 0 ; i -- )
		if( dp[ 1 ][ i ][ 0 ] <= m || dp[ 1 ][ i ][ 1 ] <= m ) {
			Write( i ) , putchar('\n');
			return 0;
		} 
	return 0;
}
```


---

## 作者：Leeb (赞：0)

### 题意简述

[题面](https://www.luogu.com.cn/problem/CF815C)

### 解题思路

首先，题目很显然是一个树形结构，然后必须父节点被标记，子节点才能被标记，容易想到树型动规。

定义状态 $f_{i,j,k}$ 表示在 $i$ 节点所在的子树中选了 $j$ 个物品且 $i$ 节点状态为 $k(k\in 0,1)$ 的最小话费，那么转移就显而易见了：设 $w_i$ 表示 $i$ 的原价，$c_i$ 表示 $i$ 的特价，则 $f_{u,i+j,0}=\min(f_{u,i+j,0},f_{u,i,0}+f_{v,j,0}),f_{u,i+j,1}=\min(f_{u,i+j,1},f_{u,i,1}+f_{v,j,0})$。

初始化：$f_{u,0,0}=0,f_{u,1,0}=w_u,f_{u,1,1}=c_u$。

答案：$f_{1,i,0}$ 和 $f_{1,i,1}$ 中最大的使得花费 $\leq m$ 的 $i$。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 5005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define pii pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, m, w[N], c[N], siz[N], f[N][N][2];
struct Edge {
    int cnt;
    int to[N], nxt[N], head[N];
    Edge() {
        cnt = 0;
    }
    inline void add_edge(int u, int v) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }
} edge;
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void dfs(int u) {
    siz[u] = 1;
    f[u][0][0] = 0;
    f[u][1][0] = w[u], f[u][1][1] = c[u];
    for (int i = edge.head[u]; i; i = edge.nxt[i]) {
        int v = edge.to[i]; dfs(v);
        for (int j = siz[u]; j >= 0; --j)
            for (int k = siz[v]; k >= 0; --k) {
                f[u][j + k][0] = min(f[u][j + k][0], f[u][j][0] + f[v][k][0]);
                f[u][j + k][1] = min({f[u][j + k][1], f[u][j][1] + f[v][k][0], f[u][j][1] + f[v][k][1]});
            }
        siz[u] += siz[v];
    }
}
inline void init() {
    n = in(), m = in(); mem(f, 0x3f);
    w[1] = in(), c[1] = w[1] - in();
    for (int i = 2; i <= n; ++i) {
        w[i] = in(); 
        c[i] = w[i] - in();
        int u = in();
        edge.add_edge(u, i);
    }
}
inline void work() {
    dfs(1);
    for (int i = n; i >= 0; --i)
        if (f[1][i][0] <= m || f[1][i][1] <= m) {
            out(i, '\n'); break;
        }
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

## 作者：Paris_Commune (赞：0)

### 分析

如果使用第 $i$ 张优惠券就必须使用第 $j$ 张，我们就可以想到树形 DP，由 $i$ 向 $j$ 连边，构成一棵树。

状态设 $f_{i,j,0/1}$ 表示以 $i$ 为根的子树中选择 $j$ 件商品且 $i$ 是否使用优惠券，如果 $i$ 使用优惠券，则至少有一个子树有使用优惠劵。

边界为 $f_{u,0,0}=0$，$f_{u,1,0}=c_u$，$f_{u,1,1}=c_u-d_u$。

转移方程：
- $f_{u,j+k,0}=\min(f_{u,j,0}+f_{u,k,0})$。
- $f_{u,j+k,1}=\min(f_{u,j,0}+\min(f_{u,k,0},f_{u,k,1}))$。

### 部分代码

```
void dfs(int u){
	siz[u]=1;
	f[u][0][0]=0,f[u][1][0]=c[u],f[u][1][1]=c[u]-d[u];
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		dfs(v);
		for(int j=siz[u];j>=0;j--){
			for(int k=0;k<=siz[v];k++){
				f[u][j+k][0]=min(f[u][j+k][0],f[u][j][0]+f[v][k][0]);
				f[u][j+k][1]=min(f[u][j+k][1],f[u][j][1]+f[v][k][1]);
				f[u][j+k][1]=min(f[u][j+k][1],f[u][j][1]+f[v][k][0]);
			}
		}
		siz[u]+=siz[v];
	}
	return;
}
```

---

