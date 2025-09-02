# Construct Tree

## 题目描述

You are given an array of integers $ l_1, l_2, \dots, l_n $ and an integer $ d $ . Is it possible to construct a tree satisfying the following three conditions?

- The tree contains $ n + 1 $ nodes.
- The length of the $ i $ -th edge is equal to $ l_i $ .
- The (weighted) diameter of the tree is equal to $ d $ .

## 说明/提示

Below, you are given the illustrations of trees for the first and third test cases. One of the diameters is highlighted by coloring its edges in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1917F/b0da55c56a8230f64464b5410b99445c4424c394.png)

## 样例 #1

### 输入

```
3
4 10
1 2 3 4
4 7
1 4 3 4
6 18
2 4 3 7 6 7```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：honey_ (赞：15)

# 题意：   
给定 $d$ 和长为 $n$ 的数列 $l$，要求构造一个 $n + 1$ 个节点的树，第 $i$ 条边的长度为 $l_i$，满足这棵树的带权直径为 $d$。   
$2 \leq n \leq 2000,1 \leq d \leq 2000$。   

# 分析：   
首先给 $l$ 从小到大排序。   
* 性质 1：如果序列最大的两个值的和大于 $d$（即 $l_n + l_{n - 1} > d$），则一定无解。   
证明：一定存在一条跨过这两条边的路径，使得这条路径的和大于 $d$。   
* 性质 2：如果存在 $l$ 的一个子集 $S$，使得 $S$ 的和为 $d$，并且 $l$ 的最大值在 $S$ 集合内（即存在 $S \subseteq l,\sum\limits_{i \in S} l_i = d,n \in S$），则一定有解。   
证明：可以构造一条长为 $|S|$ 的链，然后把 $(1,2)$ 的边权设为 $l_n$，其他没有用到的边都一定有 $l_i \leq 1_n$，直接把这些边连在结点 $2$ 上即可，这些边无论怎么与已放的边组合都不会使得直径变得更大。   
* 性质 3：如果存在 $l$ 的两个互不相交的子集 $s1,d2$ 使得这两个子集的和都不小于 $l_n$，并且 $s1,s2$ 的和恰好为 $d$（即存在 $s1 \subseteq l,s2 \subseteq l,s1 \cap s2 = \varnothing,(\sum\limits_{i \in s1} l_i) \geq l_n,(\sum\limits_{i \in s2} l_i) \geq l_n,(\sum\limits_{i \in s1} l_i)+(\sum\limits_{i \in s2} l_i) = d$），则一定有解。   
证明：可以同上构造一条链，然后找到一个点 $u$，使得左端点到 $u$ 的边权和为 $\sum\limits_{i \in s1} l_i$，把剩下的边挂在 $u$ 上即可。   

对于性质 2，直接 $O(nd)$ 跑一个背包即可。   
对于性质 3，设 $dp(i,j)$ 表示第一个集合和为 $i$，第二个集合和为 $j$ 是否可以得到，也可以直接跑背包，这样做是 $nd ^ 2$ 的，由于状态是 $01$，可以直接用 $bitset$ 优化，这样时间复杂度是 $O(\frac{nd ^ 2}{w})$ 的，可以通过。   

[Code](https://codeforces.com/contest/1917/submission/238851170)   

---

## 作者：shinkuu (赞：5)

大常熟另类做法。不用排序。

要求直径长度，则想到把直径这一条链拎出来处理。然后考虑其他边会接在哪里，发现树最优情况下一定是一个毛毛虫的形式。更进一步，所有边都挂在接近直径中点的点上。

然后再考虑这些不在直径中的，长度为 $l$ 的边带来的限制，设直径为 $d$，从每个点将直径切成两半，记其中一段为 $c_i$，则有 $\max(\min(c_i,d-c_i))\ge l$。

于是考虑一个 dp：设 $dp_{i,j,k}$ 表示只考虑前 $i$ 条边，当前已经选进直径的边长度之和为 $j$，不在直径中的 $l$ 的最大值为 $k$，是否可行。每次新加入一条边，长度为 $l_i$，就看它是否加入直径。转移即为：

$$dp_{i,j,l_i}:=dp_{i,j,l_i}+\sum dp_{i-1,j,p\le l_i}$$

$$dp_{i,j,k>l_i}:=dp_{i,j,k}+dp_{i-1,j,k}$$

$$dp_{i,j,k}:=dp_{i,j,k}+dp_{i-1,j-l_i,k}$$

在 bool 值下运算。

如果有 $dp_{n,i,j}$ 满足 $dp_{n,i,j}=1\land j\le\min(i,d-i)$ 则可行。

发现有一点小问题：有可能一个 $i$ 是无法满足最后获得长为 $d$ 的直径的。则再设一个 dp：$f_{i,j,k}$ 表示只考虑前 $i$ 条边，直径总长为 $j$，其中一段长为 $k$ 是否可行。也是 bool 背包转移。

然后发现上面两个东西都可以用 bitset 维护，然后就可以 $O(\dfrac{nd^2}{\omega})$ 做完了。

但是常数大，如果你在代码里多用左移/右移好像会 TLE，尽量少用，卡卡就过了。cf 机子真是令人流汗。

code：

```cpp
int n,m;
bitset<N> dp[2][N],f[2][N];
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,0,m)dp[0][i].reset();
	rep(i,0,m)f[0][i].reset();
	dp[0][0].set(0),f[0][0].set(0);
	bitset<N> ALL;ALL.set();
	rep(i,1,n){
		int x,p=i&1;scanf("%d",&x);
		rep(j,0,m)dp[p][j].reset();
		rep(j,0,m)f[p][j].reset();
		bitset<N> S;
		rep(j,0,x)S.set(j);
		rep(j,0,m){
			dp[p][j][x]=(dp[p^1][j]&S).any();
			dp[p][j]|=dp[p^1][j]&(ALL^S);
		}
		rep(j,x,m)dp[p][j]|=dp[p^1][j-x];
		rep(j,x,m){
			f[p][j]|=f[p^1][j-x];
			f[p][j]|=f[p^1][j-x]<<x;
		}
		rep(j,0,m)f[p][j]|=f[p^1][j];
	}
	bool ans=0;
	rep(i,0,m)rep(j,0,m)ans|=f[n&1][m][i]&&dp[n&1][i][j]&&j<=min(i,m-i);
	puts(ans?"Yes":"No");
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：EuphoricStar (赞：4)

考虑形式化地描述这个问题。先把 $l$ 排序。然后相当于是否存在一个 $\{1, 2, \ldots, n\}$ 的子集 $S$，使得：

- $\sum\limits_{i \in S} l_i = d$。
- $\exists T \subseteq S, \max\limits_{i \notin S} l_i \le \min(\sum\limits_{i \in T} l_i, \sum\limits_{i \in S \land i \notin T} l_i)$。

注意到若 $n - 1 \in S \land n \in S$ 则第二个条件一定满足，让 $n - 1 \in T$ 且 $n \notin T$ 即可。所以如果 $l_1, l_2, \ldots, l_{n - 2}$ 能凑出来 $d - a_{n - 1} - a_n$ 就可行。

然后依次讨论 $\max\limits_{i \notin S} i = n - 1$ 或 $n$ 的情况。

- 若 $\max\limits_{i \notin S} i = n - 1$，那么 $n \in S$。若前 $n - 2$ 个元素能凑出来和为 $x$ 和 $d - x - a_n$ 的两个不相交集合，且 $a_{n - 1} \le \min(x + a_n, d - x - a_n)$ 就可行。
- 若 $\max\limits_{i \notin S} i = n$，那么若前 $n - 1$ 个元素能凑出来和为 $x$ 和 $d - x$ 的两个不相交集合，且 $a_n \le \min(x, d - x)$ 就可行。

二维可行性背包考虑 bitset 优化，复杂度 $O(\frac{nd^2}{\omega})$。

[code](https://codeforces.com/contest/1917/submission/238932670)

---

## 作者：蒟蒻君HJT (赞：3)

先将 $l_1\sim l_n$ 升序排序。

注意到一种合法的方案数一定是用若干个 $l_i$ 凑出直径 $d$ 后，将剩余的边 $l_j$ 挂在中间（一边总长 $x$，一边总长 $d-x$，两边长度尽可能平均）使得这些 $l_j\leq\min(x,d-x)$。所以其实我们只关心不在直径上的边的最大边权 $l_m$，只要它满足 $l_m\leq\min(x,d-x)$ 就好了。

考虑 $l_n$ 是否在直径上。$l_n>d$ 无解。记 $s=\displaystyle\lfloor\frac{d}{2}\rfloor$。

1. 若 $l_n>s$，则 $l_n$ 必须取，否则它挂不上去。显然取 $x=l_n$ 是最优的。只要检查 $l_1\sim l_{n-1}$ 中是否都不大于 $d-l_n$ 且能凑出 $d-l_n$ 的总和就可以了。这个可以用可行性背包以 $\Theta(nd)$ 的复杂度判断。

2. 若 $l_n\leq s$，且 $l_n$ 在直径上，那么其他边必然能挂上去，用同样的方法检查 $l_1\sim l_{n-1}$ 能凑出 $d-l_n$ 的总和就可以了。否则要让 $l_n$ 能挂上去，必须从 $l_1\sim l_{n-1}$ 中选择两个不相交的子集 $S_1,S_2$，使得 $l_n\leq \min(\displaystyle \sum_{x\in S_1}x, \displaystyle \sum_{y\in S_2}y)$。考虑二维背包分别记录 $S_1,S_2$ 当前的总和，复杂度 $\Theta(nd^2)$，不能通过。但因为我们只关注方案存在与否，转移类似于 $a=\text{b or c or d}$ 的形式，所以将某一维压成 `std::bitset` 可以让常数除以 $64$，这样就能卡过去了。

[for reference only.](https://codeforces.com/contest/1917/submission/238800184)

---

## 作者：happybob (赞：1)

注意到如果 $l$ 中最大的两个数之和 $>d$，显然无解。

比较容易想到的是，我们先构造一条边权和为 $d$ 的链，然后考虑讲其他边全都连在一个点上，这样显然是优的。

考虑这个点两边边权到链顶点距离和分别为 $x,y$，那么考虑除链上的边权最大值 $z$，必然要满足 $z \leq x$ 且 $z \leq y$。否则这条链就不是直径了。

考虑 $z$ 只有两种，第一种是 $z$ 为 $l$ 全局最大值。此时相当于判定 $l$ 中是否存在两个不相交子集，两个子集和为 $d$，且两个子集和的最小值都不小于 $l$ 中最大值。用 `bitset` 维护背包就可以做到 $O(\dfrac{nd^2}{\omega})$ 的复杂度。

第二种是 $l$ 的最大值在链上，此时只要有这样一条链满足和为 $d$ 且最大值在链上即可。不需要考虑其他权值。朴素背包处理即可。

综上，总复杂度 $O(\dfrac{nd^2}{\omega})$，可以通过。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const int N = 2005;

int t, n, d, l[N];
bitset<N> bt[N], g[N];
bool f[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> d;
		for (int i = 0; i <= d; i++) bt[i].reset(), f[i] = 0;
		bt[0][0] = 1;
		for (int i = 1; i <= n; i++) cin >> l[i];
		sort(l + 1, l + n + 1);
		if (l[n] + l[n - 1] > d)
		{
			cout << "nO\n";
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = d; j >= 0; j--)
			{
				g[j] = bt[j] << l[i];
			}
			for (int j = d; j >= l[i]; j--)
			{
				bt[j] |= (bt[j - l[i]] | g[j]);
			}
			for (int j = l[i] - 1; j >= 0; j--) bt[j] |= g[j];
		}
		int nd = d - l[n];
		for (int i = 0; i <= d; i++)
		{
			if (bt[i][d - i] && i >= l[n] && d - i >= l[n])
			{
				cout << "yEs\n";
				goto E;
			}
		}
		f[0] = 1;
		for (int i = 1; i < n; i++)
		{
			for (int j = d; j >= l[i]; j--) f[j] |= f[j - l[i]];
		}
		if (f[nd])
		{
			cout << "yEs\n";
			goto E;
		}
		cout << "nO\n";
	E:;
	}
	return 0;
}
```


---

## 作者：灵乌路空 (赞：1)

Link：[http://codeforces.com/problemset/problem/1917/F](http://codeforces.com/problemset/problem/1917/F)

知识点：背包，构造

### 简述

>$T$ 组数据，每组数据给定参数 $d$ 与一长度为 $n$ 的数列 $l$，仅需**判断**是否可以构造出一棵树，满足：
>- 树的所有边长与数列元素一一对应。  
>- 树的直径为 $d$。  
>
>$1\le T\le 250$，$2\le n\le 2000$，$1\le l_i\le d\le 2000$，$\sum n\le 2000$。  
>2S，256MB。

### 分析

先和 dztle 讨论出一堆结论：

首先若存在 $l_{i} + l_{j}>d$ 显然无解。

否则若仅存在唯一的 $l_i>\frac{d}{2}$，则这条边一定在直径上，则此时最可行的构造是用其他边构造出一条长为 $d-l_i$ 的链与 $l_i$ 相连构成直径，然后将其他边直接接到 $l_i$ 靠近直径中点的端点。直接背包判断即可。

否则考虑先构造出长为 $d$ 的直径，考虑其他边应该接到哪里：
  - 发现所有边直接连到**距离直径的中点最近的点 $m$**上是最可行的。
  - 若 $m$ 与较近的直径端点距离为 $d'$（显然有 $d'\le \frac{d}{2}$）。则若所有边的长度**不大于** $d'$ 说明构造合法。
  - 为什么合法？考虑一条边 $l_i(l_i\le d')$ 位于该构造中的什么位置：
    - 边在 $m$ 与较近的直径端点的链上，则显然有 $l_i\le d'\le \frac{d}{2}$。
    - 边在 $m$ 与较远的直径端点的链上，则有 $l_i<d'<\frac{d}{2}, d'+l_i\le d$，则直径合法。
    - 边不在直径上且与 $m$ 相连，则有 $d'+l_i\le d, d - d' + l_i\le d - d' + d' = d$，则直径合法。
  - 由上述讨论可知当 $\forall 1\le i\le n, l_i\le d'$ 时在这棵树上所有边都有自己要做的事，所以构造合法。否则必然出现与直径为 $d$ 冲突的情况。

于是同样考虑背包，首先想到设 $f_i$ 表示构造出长度为 $i$ 的链时，最靠近 $\frac{d}{2}$ 的位置与较近的端点的距离。初始化 $f_0=0, \forall 1\le i\le d, f_i = -\infin$，转移时枚举当前要加入的边 $l_i$，再枚举加入边后的链长 $j$，则有转移：

$$\begin{cases}
  f_j\leftarrow f_{j-l_i} + l_i &(f_{j - l_i} + l_i\le \frac{d}{2})\\
  f_j\leftarrow f_{j - l_i}  &\text{otherwise}
\end{cases}$$

然后发现这个状态有点问题，有可能长度为 $l-a_i$ 的链存在多种构造使得最靠近 $\frac{d}{2}$ 的位置与较近的端点的距离不同，为了考虑周全应当把这些情况都记录下来。于是考虑修改状态将 $f$ 设为 `bitset`，表示构造出长度为 $i$ 的链时，最靠近 $\frac{d}{2}$ 的位置与较近的端点的距离为某个值是否可行。初始化 $f_{0, 0} = \text{true}$ 同样修改上述两种转移的形式：
- $f_j\leftarrow f_{j-l_i} + l_i$，等价于 $f_j$ 按位或上 $f_{j-l_i}$ 左移 $l_i$ 位的前 $\frac{d}{2}$ 位。
- $f_j\leftarrow f_{j - l_i}$，等价于 $f_j$ 直接或上 $f_{j-l_i}$。

最后检查 $f_d$ 最右侧的 1 的位置是否大于最长的边即可。

总时间复杂度大概是 $O\left( \frac{n^2d}{w} \right)$，$w = 64$，反正能过吸吸

### 代码

```cpp
//知识点：背包
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 2010;
//=============================================================
int n, d, ans, a[kN];
bool g[kN];
std::bitset <kN> f[kN], h;
//=============================================================
bool DP1() {
  g[0] = 1;
  for (int i = 1; i <= d; ++ i) g[i] = 0;
  for (int i = 1; i < n; ++ i) {
    for (int j = d - a[n]; j >= a[i]; -- j) {
      g[j] |= g[j - a[i]];
    }
  }
  return g[d - a[n]];
}
bool DP2() {
  h.reset();
  for (int i = 0; i <= d / 2; ++ i) h.set(i);
  for (int i = 0; i <= d; ++ i) f[i].reset();
  f[0].set(0);
  
  for (int i = 1; i <= n; ++ i) {
    for (int j = d; j >= a[i]; -- j) {
      f[j] |= f[j - a[i]] | ((f[j - a[i]] << a[i]) & h);
    }
  }
  return f[d]._Find_next(a[n] - 1) != f[d].size();
}
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> d;
    for (int i = 1; i <= n; ++ i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    if (a[n] + a[n - 1] > d) {
      ans = 0;
    } else if (a[n] > d / 2) {
      ans = DP1();
    } else {
      ans = DP2();
    }
    std::cout << (ans ? "Yes\n" : "No\n");
  }
  return 0;
}
```

---

## 作者：翼德天尊 (赞：1)

考虑有解的充要条件：可以找到一个值 $x$，把直径分为长度为 $x$ 的一段和长度为 $d-x$ 的一段之后，此时剩下的所有边的边权 $s$ 都 $\le \min(x,d-x)$。此时我们可以将剩下的边都挂在该分界点上。

不妨设 $x\ge d-x$，则上述等价于，选择若干条边组成长度为 $x$ 的链之后，剩下所有边的边权都 $\le d-x$。

故不妨枚举“剩下所有边”组成的边集 $S$ 中边的最大值 $p$，此时所有 $>p$ 的边都会变成长为 $x$ 的链的一部分，设这些边的总长为 $z$，不难发现需满足 $z\le x$ 且 $p\le d-x$，则剩下的问题相当于，在 $S$ 中是否存在两个不相交的边集 $A,B$，使得 $A$ 中边权和为 $x-z$，$B$ 中边权和为 $d-x$。

不妨设 $f_{i,A,B}$ 表示前 $i$ 小边权的边组成的边集是否包含大小分别为 $A,B$ 的不相交子集。可以使用 bitset 优化转移，此时预处理时间复杂度为 $O(\frac{nd^2}{\omega})$。

然后从小到大枚举 $p$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
int t,n,d,a[N];
bitset<N*N> f[2];
bitset<N> g[2][N];
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 

int main(){
	// freopen("in.in","r",stdin);
	t=read();
	while (t--){
		n=read(),d=read();
		int sum=0;
		for (int i=1;i<=n;i++) a[i]=read(),sum+=a[i];
		sort(a+1,a+1+n);
		// for (int i=1;i<=n;i++) cout<<a[i]<<" ";puts("");
		f[0].reset();
		for (int j=0;j<=d;j++) g[0][j].reset(),g[1][j].reset();
		bool flag=0;
		f[0][0]=1,g[0][0][0]=1;
		for (int i=1;i<=n;i++){
			int x=i&1;
			f[x]=f[x^1]|(f[x^1]<<a[i]);
			for (int j=0;j<=d;j++){
				g[x][j]=(g[x^1][j]<<a[i])|g[x^1][j];
				if (j>=a[i]) g[x][j]|=g[x^1][j-a[i]];
			}
			ll z=0;
			for (int j=n;j>i;j--) z+=a[j];
			for (int j=sum-(d+1)/2;j>=sum-d;j--){
				int y=sum-j;
					// cout<<i<<" "<<a[i]<<" "<<j<<" "<<y<<" "<<d-y<<" : "<<g[x][y-z][d-y]<<"\n";
				if (y<z) continue;
				if (g[x][y-z][d-y]&&f[x][j]&&a[i]<=d-y){
					flag=1;
					break;
				} 
			}
			if (flag) break;
		}
		if (flag) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

# 题意：

给你数组 $l$ 和数字 $d$。问你是否能够构造一棵有 $n+1$ 个节点的树使得第 $i$ 条边为 $l_i$，且直径为 $d$。

$2\le n\le2000,1\le d\le 2000,1\le l_i\le d$。
# 做法
## 结论 1：
若 $l$ 的最大值加次大值大于 $d$。无解。

因为一定可以找到一条经过这两条边的链。
## 结论 2：
若可以有一条链经过 $l_{max}$ 且长度为 $d$，那么有解。

因为我们可以把 $l_{max}$ 放到这条链的第一个位置，再把不在链上的边全都连在链上的第二个点上，这样就能保证直径为 $d$。
## 结论 3：
若一条链长度为 $d$ 且可以被分成两半使得两边的和都大于等于 $l_{max}$，那么有解。

因为可以把剩下的边全部连在分割点上，这样就能保证直径为 $d$。

其他的情况就都无解。
对于结论 2 可以设 $f_{i,j}$ 表示前 $i$ 条边能否选出一些边使得和为 $j$ 且没选 $l_{max}$。时间复杂度 $O(nd)$。

对于结论 3 可以设 $f_{i,j,k}$ 表示前 $i$ 条边能否选出一些边使得一部分和为 $j$，一部分和为 $k$.时间复杂度 $O(nd^2)$。但这样是过不了的，由于现在 $f_{i,j,k}$ 存的是 $0/1$ 所以可以用 `bitsit` 优化时间复杂度 $O(\frac{nd^2}{w})$。（结论 2 也可以这样优化）。

两个 DP 数组的第一维都可以去掉。

代码比较短，但写的丑，不要介意。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,t,a[2001],ma,g,h,mi;
bitset<2001>f[2001],o;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%d%d",&n,&d);
		ma=mi=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),ma=max(ma,a[i]);
		for(int i=0;i<=d;i++){
			o[i]=0;
			for(int j=0;j<=d-i;j++)
				f[i][j]=0;
		}
		f[0][0]=1;
		o[0]=1;
		h=0;
		for(int i=1;i<=n;i++){
			for(int j=d;j>=0;j--){
				f[j]|=(f[j]<<a[i]);
				if(j>=a[i])
					f[j]|=f[j-a[i]];
			}
			if(h==1||a[i]!=ma)
				o|=(o<<a[i]),mi=max(mi,a[i]);
			else
				h=1;
		}
		g=o[d-ma];
		for(int i=0;i<=d;i++)
			if(i>=ma&&d-i>=ma&&f[i][d-i]==1)
				g=1;
		if(g==1&&mi+ma<=d)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

考虑找出树的重心。除了直径的一条边外将其他边全部连到重心上显然是不劣的。

考虑枚举位置 $i$ 表示最大的不在直径上的边。此时后面的边一定在直径上，做一个 dp 求出在一边直径上长度为 $j$ 是否可行。同时对前缀做 dp，求出选出 $j$ 个在一边，$k$ 个在另一边的是否可行。枚举判断是否满足要求。

可以通过前缀和等方法做到 $O(nd^2)$。在此基础上，使用 bitset 优化 dp 的转移即可做到 $O(\frac{nd^2}{\omega})$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
using namespace std;
bitset<2005> suf[2005];
bitset<2005> pre[2005];
signed main(){
	int t; cin>>t;
	while(t--){
		int n,k; cin>>n>>k; int a[n+1],sufs[n+2]; for(int i=1;i<=n;i++) cin>>a[i]; sufs[n+1]=0;
		sort(a+1,a+n+1);
		for(int i=n;i>=1;i--) sufs[i]=sufs[i+1]+a[i];
		for(int i=0;i<=n+1;i++) suf[i].reset();
		for(int i=0;i<=k;i++) pre[i].reset();
		suf[n+1].set(0);
		for(int i=n;i>=1;i--) suf[i]=suf[i+1],suf[i]|=(suf[i]<<a[i]);
		pre[0].set(0);
		bool ok=0;
		a[0]=0;
		for(int i=0;i<=n;i++){
			for(int j=k;j>=a[i];j--){
				pre[j]|=(pre[j-a[i]]<<a[i])|pre[j-a[i]];
			}
			if(a[i]>k/2) break;
			if(k<sufs[i+1]) continue;
			for(int j=0;j<=sufs[i+1];j++){
				if(suf[i+1][j]){
					bitset<2005> tmp=pre[k-sufs[i+1]];
					if(a[i]-j>0) tmp=(tmp>>(a[i]-j))<<(a[i]-j);
					tmp=(tmp<<(2004-(k/2-j)))>>(2004-(k/2-j));
					if(tmp.count()) ok=1;
				}
			}
		}
		if(ok) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：hcywoi (赞：0)

### 题解

先将 $l$ 从小到大排序，记 $S$ 为边的集合满足 $\sum\limits_{i\in S}l_i=d$。

- 性质：当 $S$ 可以作为树的直径需要存在一个集合 $T\in S$ 满足，$\min\{\sum\limits_{i\in T}l_{i}, \sum\limits_{i\notin T}l_{i}\}\ge \max\limits_{i\notin S}\{l_i\}$。

- 性质：$\{n-1\}\in S\wedge \{n\}\in S$，一定有解。

显然地，我们可以将长度为 $l_{n-1}$ 和 $l_{n}$ 的边挂在根节点上。

因此我们需要判断 $\{l_1, l_2,\cdots,l_{n-2}\}$ 中是否存在一个集合 $T$ 满足 $\sum\limits_{i\in T}l_i=d-l_{n-1}-l_{n}$。

---

对于 $\max\limits_{i\notin S}\{l_i\}=l_{n-1}$ 的情况。

那么 $\{l_n\}\in S$，我们需要从 $\{l_1, l_2,\cdots, l_{n-2}\}$ 找出两个互不相交的子集满足和分别为 $x$ 和 $d-a_n-x$，其中 $\min\{x, d-x\}\ge l_{n-1}$。

---

对于 $\max\limits_{i\notin S}\{l_i\}=l_{n}$ 的情况。

我们需要从 $\{l_1,l_2,\cdots, l_{n-1}\}$ 找出两个互不相交的子集满足和分别为 $x$ 和 $d-x$，其中 $\min\{x, d-x\}\ge l_{n}$。

二维可行性背包即可，用 `bitset` 优化，时间复杂度为 $\mathcal O(\frac{nd^2}{\omega})$。

### 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2010;

void solve() {
    int n, d;
    std::cin >> n >> d;

    std::vector<int> l(n);
    for (int i = 0; i < n; i ++ ) {
        std::cin >> l[i];
    }
    std::sort(l.begin(), l.end());

    std::vector<std::bitset<N>> f(d + 1);
    f[0].set(0);
    for (int i = 0; i < n; i ++ ) {
        if (i == n - 2) {
            if (l[i] + l[i + 1] <= d && f[0].test(d - l[i] - l[i + 1])) {
                std::cout << "Yes\n";
                return;
            }
            for (int j = l[i]; j <= d - l[i]; j ++ ) {
                if (j + l[n - 1] <= d && f[j].test(d - j - l[n - 1])) {
                    std::cout << "Yes\n";
                    return;
                }
            }
        }
        for (int j = d; j >= 0; j -- ) {
            f[j] |= f[j] << l[i];
            if (j >= l[i]) {
                f[j] |= f[j - l[i]];
            }
        }
    }

    for (int i = l[n - 1]; i <= d - l[n - 1]; i ++ ) {
        if (f[i].test(d - i)) {
            std::cout << "Yes\n";
            return;
        }
    }
    std::cout << "No\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t -- ) {
        solve();
    }

    return 0;
}
```

---

## 作者：WRuperD (赞：0)

[本文同步发表于我的博客中，欢迎来玩!](http://wruperd.github.io/post/2024-11-06-solution-cf1917e/)

巨大简单题。看完样例就会做了吧。

首先考虑如果权值最大的边和权值次大的边的和大于 $d$ 那么一定无解。（原因是树是联通的所以直径一定至少是这个值。）

不妨设最大权值为 $w$，次大的为 $w'$。

所以我们不妨直接把他们挂在一个节点上。考虑如果我们钦定这个直径包括了边权最大的那条边的话，那么就相当于我们还有在这个节点上面挂一条长度为 $d-w$ 的链。只要能凑出来就一定行。原因：我们把除了这条链上的边全部也挂在这个节点上，那么首先有 $d-w \geq w'$ 所以我们一定是会取这条链和最大权值边作为我们的直径的。接着考虑权值最大的边不作为直径上的边。那么我们就必须要挂两条权值和大于 $w$ 的链。同理在这种情况下我们也会直接选择这两条链。所以我们直接对这两部跑动态规划解决就可以了。使用 bitset 以做到 $O({d^3\over \omega})$。

```cpp
// Problem: Construct Tree
// URL: https://www.luogu.com.cn/problem/CF1917F
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 2e3 + 10;

int a[MAX];
bool f[MAX];
bitset <MAX> f2[MAX];

void solve(){
	int n = read(), d = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	sort(a + 1, a + n + 1);
	if(a[n] + a[n - 1] > d){
		puts("NO");
		return ;
	}
	d -= a[n];
	for(int i = 0; i < MAX; i++)	f[i] = 0;
	for(int i = 0; i < MAX; i++)	for(int j = 0; j < MAX; j++)	f2[i][j] = 0;
	f[0] = 1;
	for(int i = 1; i < n; i++){
		for(int j = d; j >= a[i]; j--){
			f[j] |= f[j - a[i]];
		}
	}
	f2[0][0] = 1;
	for(int i = 1; i < n; i++){
		for(int j = d + a[n]; j >= 0; j--){
			bitset <MAX> ans = f2[j];
			if(j >= a[i])	ans |= f2[j - a[i]];
			ans |= f2[j] << a[i];
			f2[j] = ans;
		}
	}
	if(f[d]){
		puts("Yes");
	}else{
		for(int i = a[n]; i <= d; i++){
			int j = d + a[n] - i;
			if(j < a[n])	continue;
			if(f2[i][j]){
				puts("Yes");
				return ;
			}
		}
		puts("No");
	}
}

signed main(){
	int t = read();
	while(t--)	solve();
	return 0;
}
```

---

