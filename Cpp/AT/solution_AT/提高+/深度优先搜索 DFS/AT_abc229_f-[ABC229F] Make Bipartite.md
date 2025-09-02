# [ABC229F] Make Bipartite

## 题目描述

给你一张由 $N+1$ 个点组成的无向图，分别命名为 $0,1,...,N$

这张图只有 $2N$ 条边，用 $A$ 和 $B$ 两个数组表示：
+ $A_i$ 表示连接 $0$ 和 $i$ 两点的无向边的权值
+ $B_i$ 表示连接 $i$ 和 $i+1$ 两点的无向边的权值, 这里，点 $N$ 与 点 $1$ 连接

现在要删除若干条边， 使得这个图变成一张二分图，求删除边的最小权值和

## 说明/提示

- $ 3\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- 输入的所有数据都在整型范围内
### 样例解释
![graph](https://img.atcoder.jp/ghi/ded08d4aa13d31bea28b91afe246c790.png)
删除 $(0,2),(0,4),(0,5)$ 三条边

## 样例 #1

### 输入

```
5
31 4 159 2 65
5 5 5 5 10```

### 输出

```
16```

## 样例 #2

### 输入

```
4
100 100 100 1000000000
1 2 3 4```

### 输出

```
10```

# 题解

## 作者：jiazhichen844 (赞：13)

# 题意
有一个如下图的图，请你删去一些边，使图成为二分图，且删去边权和最小。

![](https://img.atcoder.jp/ghi/ded08d4aa13d31bea28b91afe246c790.png)

# 思路
# Step 1
~~瞪眼法~~分析性质，二分图有一个性质：对顶点黑白染色，不会有相邻顶点同色，于是考虑把 $0$ 号点染成 $0$ 号颜色（白），则我们可以对于每个点的染色，都有相应代价，于是考虑 dp。

令 $dp_{i,j}$ 为染完 $1$ 至 $i$ 号点，且第 $i$ 号点颜色为 $j$ 的最小代价，考虑 $i-1$ 号点的颜色，得到：
$dp_{i,0}=min(dp_{i-1,0}+a_i,dp_{i-1,1})+b_i,dp_{i,1}=min(dp_{i-1,1}+a_i,dp_{i-1,0})$
于是就~~AC~~WA了。
# Step 2
看有什么情况没考虑到。

我们发现：原来的式子没有考虑 $1$ 至 $n$ 的连边，自动把他删除了，还没计算价值，可以发现，问题出在 $1$ 号节点，所以可以把它的颜色设进状态。

令 $dp_{i,j,k}$ 为染完 $1$ 至 $i$ 号点，且第 $i$ 号点颜色为 $j$，$1$ 号点颜色为 $k$ 的最小代价。

同样考虑 $i-1$ 号点的颜色，得到：
$dp_{i,0,k}=min(dp_{i-1,0,k}+a_i,dp_{i-1,1,k})+b_i,dp_{i,1,k}=min(dp_{i-1,1,k}+a_i,dp_{i-1,0,k})$
初值：$dp_{1,0,0}=b_1,dp{1,1,1}=0,dp_{1,1,0}=dp_{1,0,1}=inf$

只要在输出答案时按照 $1$ 号和 $n$ 号点颜色分类即可。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[200005][2][2];
int a[200005];
int b[200005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	dp[1][1][0]=dp[1][0][1]=LONG_LONG_MAX/2;
	dp[1][0][0]=a[1];
	for(int i=2;i<=n;i++)
	{
		dp[i][0][0]=min(dp[i-1][0][0]+b[i-1],dp[i-1][1][0])+a[i];
		dp[i][0][1]=min(dp[i-1][0][1]+b[i-1],dp[i-1][1][1])+a[i]; 
		dp[i][1][0]=min(dp[i-1][1][0]+b[i-1],dp[i-1][0][0]);
		dp[i][1][1]=min(dp[i-1][1][1]+b[i-1],dp[i-1][0][1]);
	}
	cout<<min(min(dp[n][0][1],dp[n][1][0]),min(dp[n][0][0],dp[n][1][1])+b[n]);
}
```

---

## 作者：weizhiyonghu (赞：6)

## F

### Des

给定一张 $n + 1$ 个点，$2n$ 条边的无向图。点编号依次为 $0,1,2,\dots,n$。

边有边权，且只有以下形态的边：

+ 形如 $(0,u)\ (1 \le u \le n)$ 的无向边，边权为 $a_u$。记为第一类边。
+ 形如 $(u,u + 1) \ (1 \le u \lt n)$ 的无向边，边权为 $b_u$。特别地，有边 $(n,1)$。记为第二类边。

现在你需要删除若干条边，令整张图变成一个二分图。问最小的删边权值之和。

### Sol

一个很显然的结论是，二分图中没有奇环。

很好证明：记这个奇环大小为 $s$，令环上每个节点依次为 $1,2,3,\dots,s$，那么根据二分图定义，对于 $1 \le i \lt s$，$i$ 与 $i + 1$ 不能在同一个集合。

那么，由于 $2 \nmid s$，$1$ 和 $s$ 最终属于同一个集合。但 $1$ 和 $s$ 之间又有连边，矛盾。故这样的图不满足二分图定义。

再来考虑证明其充分性：如果一个连通图中不存在奇环，那么考虑若有 $p(u,v)$，即 $u,v$ 两点相互可达：

+ $u,v$ 在偶环中：记偶环大小为 $s'$，那么 $1$ 和 $s'$ 不属于同一个集合。则可以满足定义。
+ $u,v $ 在一条不为环的路径中：更简单了，因为不会出现头尾相接，所以只需要将相邻的点加入不同的集合即可。

所以这是一个充要条件。

那么，我们可以用是否存在奇环来判定二分图。

也就是说，原问题等价于求将图中所有奇环删除的最小代价。

回到这个题。我们发现，图的形态是相对固定的：组成每个图的最小子结构是相同的：形如 $(0,u,u+1)$ 形成的奇环。

同时我们发现，对于一条一类边，其能影响两个最小奇环。对于一条二类边，只能影响一个奇环。

那么，我们发现可以把一条边的影响控制在相邻的两个位置上；也就是说删边其实无后效性，此时问题变成了一个 dp 问题：

规定：$i$ **表示的奇环**指 $0,i-1,i$ 形成的奇环。

$f_i$ 表示 $2,3,\dots,i$ 表示的奇环均被删除的情况下，最小边权花费。

转移：

我们发现，只有三种结构是必须分讨的：单个奇环、两个相邻的奇环、三个相邻的奇环。

两个要考虑是简单的，因为一条一类边影响到两个奇环。

三个也要考虑，因为可能出现连删两个一类边，此时要把中间那个二类边删了，不然弄出一个边数为 $5$ 的奇环。

同时，一个更大的情况，是可以被上面三种小的情况拼出来的。

那么容易得到转移方程：

$1$ 个奇环的部分：$f_{i-1} + b_{i - 1}$。

$2 $ 个奇环的部分：$f_{i-2} + a_{i-1}$。

$3$ 个奇环的部分：$f_{i-3} + a_{i-1} + a_{i-2} + b_{i-2}$

取 $\min$ 即可。$f_{i} = \min(f_{i-1} + b_{i-1},f_{i-2} + a_{i-1},f_{i-3} + a_{i-1} + a_{i-2} + b_{i-2})$。

同时，因为状态设定为以 $i $ 结尾的奇环，所以最后一个奇环可以计算+断环成链得出。

时间复杂度 $\mathcal{O}(n)$，常数非常小。这份代码 $10 \rm ms$，Atcoder 最优解。

```cpp
// LUOGU_RID: 155159928
#include <bits/stdc++.h>
#define int long long
#define L(t,l,r) for(int t = l;t <= r;t++)
#define R(t,l,r) for(int t = r;t >= l;t--)

using namespace std;
const int N = 5e5 + 10;
int n,ans = 1e18,a[N],b[N],f[N];

namespace IO
{
	char buff[30000000],*p1=buff,*p2=buff;
	inline char get_c() {if(p1 == p2) p2 = (p1=p2) + fread(buff,1,30000000,stdin);return *p1++;}
	template<typename T> inline void in(T &x)
	{
		x = 0;short sign = 1;
		char ch = IO::get_c();
		while(ch < 48 || ch > 57)
		{
			if(ch == 45) sign = -1;
			ch = get_c();
		}
		while(ch >= 48 && ch <= 57)
			x = (x<<3)+(x<<1)+ch-'0',
			ch = get_c();
		x *= sign;return ;
	}
	template<typename T> inline void out(T x)
	{
		if(x < 0) putchar(45),x=-x;
		if(x > 9) out(x / 10);
		putchar(x % 10 + '0');
	}
}using namespace IO;

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	in(n);
	L(i,1,n) in(a[i]);
	L(i,1,n) in(b[i]);
	a[n + 1] = a[1],b[n + 1] = b[1];
    a[n + 2] = a[2],b[n + 2] = b[2];
    a[n + 3] = a[3],b[n + 3] = b[3];
    
	L(x,0,2) // rorate the first odd_cycle so we can get all answer
	{
		f[1 + x] = 0,f[2 + x] = b[1 + x];
		f[3 + x] = min(f[2 + x] + b[2 + x],f[1 + x] + a[2 + x]);
		L(i,4 + x,n + x)
		{
			int ans_typ1 = f[i - 1] + b[i - 1];
			int ans_typ2 = f[i - 2] + a[i - 1];
			int del_all_cyc = f[i - 3] + a[i - 1] + a[i - 2] + b[i - 2];
			f[i] = min({ans_typ1,ans_typ2,del_all_cyc});
		}

		int edge_1 = f[n + x] + b[n + x];
		int edge_2 = f[n - 1 + x] + a[n + x];
		int edge_3 = f[n - 2 + x] + a[n + x] + a[n - 1 + x] + b[n - 1 + x];
		ans = min({ans,edge_1,edge_2,edge_3});
	}

	out(ans);
	return 0;
}
```

---

## 作者：lsz_ (赞：3)

此题的第一篇题解。。？

> 这题 DP 的思路谁想得到啊

> ——作者

[题目链接（AtCoder 版）](https://atcoder.jp/contests/abc229/tasks/abc229_f)

[题目链接（洛谷版）](https://www.luogu.com.cn/problem/AT_abc229_f)

[更好的阅读体验](https://www.luogu.com.cn/blog/lsz-qwq/solution-at-abc229-f)


### 题目大意

给定一个连通图，每条边都有一个权值，求最小化删掉的边权值之和使图成为一个二分图。

该连通图有 $N+1$ 个点，$2N$ 条边，且点 $0$ 到任何一个非零的点都有一条边。对于 $1<i\leq N$，$i$ 和 $i-1$ 也有一条边，还有一条边就是 $1$ 和 $N$。

请读者结合图（这是样例）自行理解一下：

![](https://img.atcoder.jp/ghi/ded08d4aa13d31bea28b91afe246c790.png)

### 思路

二分图最常见的判断方法就是染色法，这里不多概述，容易想到设点 $0$ 为红色。

（以下简称红色是 $0$，蓝色是 $1$）

接下来因为删边具有关联性，容易想到 DP ~~哪里好想到了~~。

设状态 $f[i][j][k]$ 表示已经处理完了前 $i-1$ 个点，正在处理第 $i$ 个点，其中第 $i$ 个点颜色是 $j$，顶点 $1$ 的颜色是 $k$ 的最小答案。

$f[i]$ 这一维可通过 $f[i-1]$ 推导而来，初始化后面再讲。

需要注意的是，点 $1$ 和 $N$ 之间也有一条边，最后选答案的时候处理一下即可。

复杂度为 $O(N)$。

### 初始化

肯定要先 `memset(f,0x3f,sizeof f)`。

因为 $f$ 的定义问题，只需初始化 `f[1][0][0]` 和 `f[1][1][1]` 即可。

`f[1][0][0]`：那点 $1$ 和点 $0$ 就是同一边，要把他们两个之间的边删掉，代价为 `a[1]`。

`f[1][1][1]`：那点 $1$ 和点 $0$ 就是不为同一边，不用进行修改，故代价为 $0$。

### 代码
```
#include<bits/stdc++.h>
#define LL long long
#define N 200010
using namespace std;
int n,i,j,k,op;
LL ans=0x3f3f3f3f3f3f3f3f;
LL a[N],b[N];
LL f[N][2][2];
int main()
{
	memset(f,0x3f,sizeof f);
	cin>>n;
	for(i=1;i<=n;i++)	cin>>a[i];
	for(i=1;i<=n;i++)	cin>>b[i];
	f[1][0][0]=a[1];
	f[1][1][1]=0;
	for(i=2;i<=n;i++)
		for(j=0;j<=1;j++)
			for(k=0;k<=1;k++)
				for(op=0;op<=1;op++)
					f[i][j][k]=min(f[i][j][k],f[i-1][op][k]+(j==0?a[i]:0)+(j==op?b[i-1]:0));
	for(j=0;j<=1;j++)
		for(k=0;k<=1;k++)
			ans=min(ans,f[n][j][k]+(j==k?b[n]:0));
	cout<<ans;
	return 0;
}
```

---

## 作者：Fislett (赞：2)

## 题意

给你一张图，其中点 $i$ 与点 $0$ 和点 $i + 1$（特别的，点 $n$ 与点 $1$ 有一条连边） 有一条连边，每条边有一个权值，求使这张图成为一张二分图最少要删除边权总值为多少的边。

## 解法

考虑对整张图进行染色，钦定点 $0$ 为白色。设 $dp[i][0/1][0/1]$ 表示染完前 $i$ 个点，第 $1$ 个点为白/黑色，第 $i$ 个点为白/黑色，所需要的边权总和最小值。

考虑从 $i - 1$ 处转移。

- $dp[i][0][0] = \min(dp[i - 1][0][0] + b[i - 1], dp[i - 1][0][1]) + a[i]$，若上一个点和当前点颜色相同，则断掉 $i - 1$ 到 $i$ 的边以及 $0$ 到 $i$ 的边，否则不断掉 $i - 1$ 到 $i$ 的边。

- $dp[i][0][1] = \min(dp[i - 1][0][0], dp[i - 1][0][1] + b[i - 1])$，若上一个点和当前点颜色相同，则断掉 $i - 1$ 到 $i$ 的边。

- $dp[i][1][0] = \min(dp[i - 1][1][0] + b[i - 1], dp[i - 1][1][1]) + a[i]$，若上一个点和当前点颜色相同，则断掉 $i - 1$ 到 $i$ 的边以及 $0$ 到 $i$ 的边，否则不断掉 $i - 1$ 到 $i$ 的边。

- $dp[i][1][1] = \min(dp[i - 1][1][0], dp[i - 1][1][1] + b[i - 1])$，若上一个点和当前点颜色相同，则断掉 $i - 1$ 到 $i$ 的边。

初始状态：```dp[1][0][1] = dp[1][1][0] = inf, dp[1][0][0] = a[1], dp[1][1][1] = 0```。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
#define rint register int 
using namespace std;
inline int read()
{
    rint x = 0, flag = 1, c = getchar();
    while ((c < '0' || c > '9') && c ^ '-') c = getchar();
    c == '-' ? flag = -1 : x = (c ^ 48), c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * flag;
}
inline void print(rint x, rint flag = 0)
{
    if (x < 0) putchar('-'), x = ~(x - 1);
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
    if (flag) flag & 1 ? putchar(' ') : putchar('\n');
}
int n, a[200005], b[200005], dp[200005][2][2];
signed main()
{
    n = read();
    for (rint i = 1; i <= n; ++ i) a[i] = read();
    for (rint i = 1; i <= n; ++ i) b[i] = read();
    dp[1][0][0] = a[1], dp[1][1][1] = 0, dp[1][0][1] = dp[1][1][0] = 8e18;
    for (rint i = 2; i <= n; ++ i)
    {
        dp[i][0][1] = min(dp[i - 1][0][0], dp[i - 1][0][1] + b[i - 1]);
        dp[i][0][0] = min(dp[i - 1][0][0] + b[i - 1], dp[i - 1][0][1]) + a[i];
        dp[i][1][0] = min(dp[i - 1][1][0] + b[i - 1], dp[i - 1][1][1]) + a[i];
        dp[i][1][1] = min(dp[i - 1][1][0], dp[i - 1][1][1] + b[i - 1]);
    }
    print(min({dp[n][1][1] + b[n], dp[n][1][0], dp[n][0][1], dp[n][0][0] + b[n]}));
    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

诈骗！！！

我们直接考虑 Dp。

由于二分图判定法有一个叫做黑白染色法。

通过染色 $0$ 和 $1$ 来判定二分图。

所以我们在转移的时候也一定要考虑到这个点。

设 $dp_{i,j,k}$ 为已经染色了前 $i$ 个点，然后此时 $i$ 的颜色为 $j$，$1$ 的颜色为 $k$。

所以我们就可以得出转移方程：

- $dp_{i,0,0} = \min(dp_{i-1,0,0}+b_{i-1},dp_{i-1,1,0}) + a_i$ 
- $dp_{i,0,1} = \min(dp_{i-1,0,1}+b_{i-1},dp_{i-1,1,1}) + a_i$
- $dp_{i,1,0} = \min(dp_{i-1,1,0}+b_{i-1},dp_{i-1,0,0})$
- $dp_{i,1,1} = \min(dp_{i-1,1,1}+b_{i-1},dp_{i-1,0,1})$

很好理解，我们要保证根中间的节点保持不一样的颜色，和上一个节点也保持这不一样的颜色。

分四种情况讨论就是这样。

[link](https://atcoder.jp/contests/abc229/submissions/52202276)。

---

