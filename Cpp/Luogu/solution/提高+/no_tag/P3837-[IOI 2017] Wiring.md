# [IOI 2017] Wiring

## 题目背景

这是一道交互题。

本题仅支持 C++ 系列语言，提交时不需要包含 `wiring.h` 头文件，但需要在程序开头包含 `vector` 头文件以及声明函数 `long long min_total_length(std::vector<int> r, std::vector<int> b)`。

**由于不可名状的 BUG，使用 C++14 (GCC9) 提交会导致 CE，请不要使用其提交。**

## 题目描述

Maryam 是一位电机工程师。她正在为一座通讯塔设计接线方案。在这个塔上有一些分布在不同高度的连接点。一条电线可以用来将任何两个连接点连接起来。每一个连接点都可以接上任意数目的电线。而连接点共有两种：分别为红色连接点及蓝色连接点。

为了表述方便起见，通讯塔会被视为一条直线，而那些红色及蓝色连接点会被视为在这条直线上的一些非负整数坐标。一条电线的长度是该电线所连接的两个连接点间的距离。

你要做的是帮 Maryam 找出一个接线的方案，使得满足以下条件：

1. 每个连接点上最少有一条电线连接到一个不同颜色的连接点上

2. 所用的电线的总长为最短。


## 实现细节

你需要实现以下的子程序：

`long long min_total_length(std::vector<int> r, std::vector<int> b)`

- $r$：一个长度为 $n$ 的数组，其内以升序排列着所有红色连接点的位置。

- $b$：一个长度为 $m$ 的数组，其内以升序排列着所有蓝色连接点的位置。

- 这个子程序需返回在所有可能的连接方案中，最短电线总长度的那个方案的电线作为其返回值。

- 请注意这个子程序的返回值的类型为 `long long` 。


## 说明/提示

样例中函数传递参数：

`min_total_length([1, 2, 3, 7], [0, 4, 5, 9, 10])`

以下的图表表述了样例中的数据。

 ![](https://cdn.luogu.com.cn/upload/pic/6724.png) 

- 图中以水平的方式表示出相关的通讯塔。

- 因题目打印是黑白色的，所以红色接点以较深色来表示，而蓝色接点则以较浅色来表示。

- 图中有 $4$ 个红色的连接点，其位置分别为 $1,2,3$ 及 $7$ 。

- 图中有 $5$ 个蓝色的连接点，其位置分别为 $0,4,5,9$ 及 $10$ 。

- 该例的最优解的电线总长度为 $1+2+2+2+3=10$ ，所以子程序的返回值为 $10$ 。

- 请注意共有两条电线连接在位置为 $7$ 的连接点上。


## 限制条件

- $1 \leqslant n,m \leqslant 100000$

- $0 \leqslant r[i] \leqslant 10^9 $（对于所有$0 \leqslant i \leqslant n-1$）

- $0 \leqslant b[i] \leqslant 10^9$（对于所有$0 \leqslant i \leqslant m-1$）

- 数组$r$及数组$b$都已经按升序排好序。

- 在数组$r$及$b$内的所有$n+m$个值均是不同的。


## 子任务

1. ($7$ 分)  $n,m\leqslant 200$。

2. ($13$ 分)  所有红色接点的位置坐标小于任何蓝色接点的坐标。

3. ($10$ 分)  在每$7$个连续的（接续）的连接点内必有最少一个红色接点及蓝色接点。

4. ($25$ 分)  所有接点在$[1,n+m]$范围内有不同的位置坐标。

5. ($45$ 分)  没有任何附加的限制。


## 样例 #1

### 输入

```
r = [1, 2, 3, 7]
b = [0, 4, 5, 9, 10]```

### 输出

```
10```

# 题解

## 作者：Illusory_dimes (赞：7)

[不知道更好还是更坏的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15510405.html)

复盘 pb 讲的题，来写篇题解~~造福社会~~。

## Description

有 $n$ 个红色的点，坐标为 $r_i$ 和 $m$ 个蓝色的点 $b_i$ ，问在所有点都至少与一个异色的点连边的情况下，最小花费，其中花费指两点坐标差。

$n,\ m \leq 10 ^ 5\ ,\ \ r_i,\ b_i \leq 10 ^ 9$

![](https://cdn.luogu.com.cn/upload/image_hosting/3eehzk10.png)

## Analysis

非常烦，因为并不知道到底怎么样才是最小花费。

这种两两配对的这种，其实应该是能想到网络流的，但是因为我水平严重不够，想不出来怎么做，就直接放弃了。。

于是来观察部分分有什么类型，注意到 13 分那个约束条件，就相当于整个数轴上只有两个颜色块。

块，那是不是对于其他情况都可以这么想，那对于任何一个例子，都可以画成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ps9x7q6i.png)

正好每个点连的边的数量没有限制，只是要有边就行，这样子看问题就感觉清晰多了。

## Solution

接着 Analysis 中的图，很快应该就能发现，一个颜色块里面的点顶多会跟旁边两个异色块里面的点连边。

因为再往外的话肯定就会先经过一些同色点，让那些点去连更外层的异色点显然会更优。

那么问题逐渐简洁了起来，好极了！！1

那么对于两个颜色块，假设我们已经确定了里面的点要相互连边：

![](https://cdn.luogu.com.cn/upload/image_hosting/d76ckifk.png)


肯定每个点都要伸出去一个边，然后一共会连 $\max(n,\ m)$ 条，点多的那边就肯定会贪心的把多出来的点连向最靠近自己的异色点，所以对于这个样子的图，花费就是：

$$
\sum_{i = 1}^{cnt1}(b_{cnt1} - b_i) + \sum_{i = 1}^{cnt2}(r_i - r_{cnt2}) + \max(n,\ m) \cdot (r_{cnt2} - b_{cnt1})
$$

这玩意能在做前缀和先算好，问题不大。

那些在就相当于我们只要知道在满足条件的情况，一个区间是把多少个点连向前面（剩下的就连向后面）花费最小。

考虑 DP ， $f_i$ 表示在前 $i$ 个点的最小花费。

转移的话，我们可以先把所有点划分成若干组前面一段红后面一段蓝的样子。

然后可以直接枚举在哪个地方断开，前半部分向前连边，后半部分向后连边。

然后把前面那一段看从哪里断出来一部分点向后连边更优，这些是可以提前预处理好的（就是套上面的公式），就要注意一下两个区间分出来的两部分的长度关系就可以了。

## Code

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const ll INF = 1e16;
ll col[N], s[N], cnt, lt[N], rt[N], tot;
ll f[N], pre[N], sum[N], mn[N];

ll min_total_length(std::vector<int> R, std::vector<int> B) {
	ll n = R.size(), r = 0, m = B.size(), b = 0;
	while (r < n && b < m) {
		if (R[r] < B[b]) {
			s[++cnt] = R[r++];
			col[cnt] = 1;
		}
		else {
			s[++cnt] = B[b++];
			col[cnt] = 2;
		}
	}
	while (r < n) s[++cnt] = R[r++], col[cnt] = 1;
	while (b < m) s[++cnt] = B[b++], col[cnt] = 2;
	for (r = 1; r <= cnt; r = b) {
		for (b = r; b <= cnt && col[r] == col[b]; ++b);
		lt[++tot] = r; rt[tot] = b - 1;
	}
	for (int i = lt[1]; i <= rt[1]; ++i) f[i] = INF;
	for (int i = 2; i <= tot; ++i) {
		ll invl = s[lt[i]] - s[rt[i - 1]], S = 0;
		ll lth = rt[i - 1] - lt[i - 1], now = 1;
		for (int j = rt[i - 1]; j >= lt[i - 1] - 1; --j) {
			sum[j] = sum[j + 1] + s[rt[i - 1]] - s[j];
			pre[j] = f[j] + sum[j + 1];
			mn[j] = pre[j] + invl * (rt[i - 1] - j);
		}
		for (int j = rt[i - 1]; j >= lt[i - 1]; --j) pre[j - 1] = min(pre[j - 1], pre[j]);
		for (int j = lt[i - 1]; j <= rt[i - 1]; ++j) mn[j] = min(mn[j], mn[j - 1]);
		for (int j = lt[i]; j <= rt[i]; ++j) {
			S += s[j] - s[lt[i]];
			if (now <= lth) {
				ll lef = rt[i - 1] - now + 1;
				f[j] = S + min(mn[lef - 1], pre[lef] + now * invl);
			}
			else f[j] = S + pre[lt[i - 1] - 1] + now * invl;
			++now;
		}
	}
	return f[cnt];
}
```

---

## 作者：wurzang (赞：5)

考虑模拟费用流，红点与蓝点之间连 $(|x_i-y_j|,1)$ 的边，源点与红点之间连两条边 $(\operatorname{-inf},1),(0,\inf)$，蓝点和汇点之间同理。

接下来的步骤同 [UOJ455 雪灾与外卖](https://uoj.ac/problem/455)，考虑怎么退流即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef long long ll;
const int N=1e5+5;
const ll inf=2e9;
ll ans;
struct node{
    ll c,flow;
    bool operator < (const node & b) const {
        return c < b.c;
    }
};
priority_queue<node> red,blue;
void add_red(int x){
    if(!blue.empty()){
        auto u=blue.top();blue.pop();
        ans+=x-u.c;red.push({x+x-u.c,1ll});
        u.flow--;if(u.flow>0) blue.push(u);
    }
    else ans+=inf,red.push({inf+x,1});
    while(!blue.empty()){
        if(x-blue.top().c>=0) break;
        auto u=blue.top();blue.pop();
        ans+=x-u.c;blue.push({x,1});
        u.flow--;if(u.flow>0) blue.push(u);
    }
    red.push({x,inf});
}
void add_blue(int x){
    swap(red,blue);
    if(!blue.empty()){
        auto u=blue.top();blue.pop();
        ans+=x-u.c;red.push({x+x-u.c,1ll});
        u.flow--;if(u.flow>0) blue.push(u);
    }
    else ans+=inf,red.push({inf+x,1});
    while(!blue.empty()){
        if(x-blue.top().c>=0) break;
        auto u=blue.top();blue.pop();
        ans+=x-u.c;blue.push({x,1});
        u.flow--;if(u.flow>0) blue.push(u);
    }
    red.push({x,inf});
    swap(red,blue);
}
ll min_total_length(vector<int> r,vector<int> b){
    ans=0;
    int n=r.size(),m=b.size();
    for(int i=0,j=0;i<n||j<m;){
        if(i<n && (j==m || r[i]<b[j])) add_red(r[i]),++i;
        else add_blue(b[j]),++j;
    }
    return ans;
}
```


---

## 作者：yzy1 (赞：3)

## 题目大意

给定一完全二分图，左部点数为 $n$，右部点数为 $m$（$1 \le n,m \le 10^5$）．点有点权左右侧分别记为 $a_i,b_i$（$0 \le a_i,b_i \le 10^9$）．左右部分每两个点之间都有连边，第 $x$ 个左部点和第 $y$ 个右部点之间的边权为 $|a_x-b_y|$．求出这个图的边权和最小的且满足图中每个点的度数至少为 $1$ 的生成子图．输出该生成子图的边权和．

## 做法简述

先考虑 $13$ 分的子任务应该怎么做，考虑贪心．把左右两部分点一起放在数轴上，从左到右给每个点编号 $1\sim n+m$．首先显然每个左部点都要向数轴的正方向连出一条边，每个右部点又要向数轴的负方向连出一条边，则最右侧的左部点和最左侧的右部点之间一定有 $\max\{n,m\}$ 条边经过．即答案为：

$$
(\max\{n,m\}) \cdot (b_1-a_n) + (\sum_{i=1}^n a_n - a_i) + (\sum_{i=1}^m b_i - b_1).
$$

继续考虑一般情况．发现我们可以将整个数轴划分为若干个同类段，每个同类段里仅包含左部点或者右部点．然后把每个同类段从中间切开，左一半和上一个的同类段的右边拼一块，就可以按照上面的方法做了．考虑 DP，设 $\operatorname{dp}(i)$ 仅考虑数轴上从左向右数前 $i$ 个点的答案．则有以下转移：

$$
\operatorname{dp}(i) \gets \min_{j \in \textsf{上一个同类段}} \{\operatorname{dp}(j-1) + \operatorname{F}(i,j)\}.
$$

其中 $\operatorname{F}(i,j)$ 表示将数轴上从左到右第 $i$ 个点到第 $j$ 个点连起来的代价．

我们得到了一个 $O((n+m)^2)$ 的做法，但还无法通过本题．考虑优化上述 DP．将 $\operatorname F$ 拆分为两部分：

$$
\def\st{\operatorname{start}}
\def\ed{\operatorname{end}}
\def\pos{\operatorname{pos}}
\def\dp{\operatorname{dp}}
\begin{aligned}
\dp(i) \gets \min_{j \in \textsf{上一个同类段}} \{
& {\color{darkred} \dp(j-1) + (\sum_{k=j}^{\ed(j)} \pos(\st(i)) - \pos(k))} \\
{} + {} & {\color{darkblue} (\sum_{k=\st(i)}^i \pos(i) - \pos(\st(i)))} \\
{} + {} & {\color{darkgreen} \max\{0, (i - \st(i)) - (\ed(j) - j)\} \cdot (\pos(\st(i)) - \pos(\ed(j))) }
\}.
\end{aligned}
$$

其中 $\operatorname{start}(x)$ 表示 $x$ 所在的同类段的开头点的编号，$\operatorname{end}(x)$ 表示 $x$ 所在的同类段的结尾点的编号，$\operatorname{pos}(x)$ 表示编号为 $x$ 的点的位置．

发现上述公式中的红色部分与 $i$ 无关，蓝色部分与 $j$ 无关，绿色部分与两者都相关．考虑使用线段树对于上一个同类段维护公式中的红色部分，枚举 $i$ 的时候在线段树上使用后缀加操作修改绿色部分．转移时只需查询线段树全局 $\min$ 即可．

注意需要对于同类段大小为 $1$ 的情况进行特殊处理．

时间复杂度 $O(n \log n)$，可以通过此题．

## 代码参考

```cpp
int len;
ll dp[N], buf[N];
pair<int, bool> c[N];

struct Seg {
  // 线段树省略
} seg;

long long min_total_length(std::vector<int> r, std::vector<int> b) {
  each (x, r) c[++len] = {x, 0};
  each (x, b) c[++len] = {x, 1};
  sort(c + 1, c + len + 1);
  vector<int> lst, now;
  ll sum = 0;
  bool col = c[1].second;
  memset(dp, 0x3f, sizeof dp);
  dp[0] = 0;
  re (i, len) {
    if (c[i].second != col) {
      lst = now, now.clear();
      ll sum2 = 0;
      per (j, lst.size() - 1, 0) {
        sum2 += c[i].first - lst[j];
        buf[j] = min(dp[i - lst.size() - 1 + j], dp[i - lst.size() + j]) + sum2;
      }
      seg.Build(1, 0, lst.size() - 1, buf);
      col = c[i].second;
      sum = 0;
    }
    now.push_back(c[i].first);
    sum += c[i].first - now[0];
    if (lst.empty()) continue;
    int l = lst.size() - now.size() + 1;
    up(l, 0);
    if (l <= (int)lst.size() - 1)
      seg.Add(l, lst.size() - 1, now[0] - lst.back(), 1, 0, lst.size() - 1);
    dp[i] = seg.d[1].mn + sum;
  }
  return dp[len];
}
```


---

## 作者：_•́へ•́╬_ (赞：1)

模拟赛搬两个 IOI 和一个爆炸。。。

## 思路

把连续的红点和蓝点缩起来，一块一块地处理。

考虑相邻两块之间的连边长啥样，大概是前块的一个后缀向右连，后块的一个前缀向左连。

如果前者的点数比后者多，那么优先两两匹配，没匹配的连给后块的第一个点。反过来，没匹配的连给前块第一个点。

考虑把贡献全拆了，贡献有：块的一个前缀连到第一个点，块的一个后缀连到最后一个点，两块之间的路被前块的一个后缀的点经过，两块之间的路被后块的一个前缀的点经过。实现上把第二个和第三个一起计算。

设 $f[i]$ 表示前一块有一个长度为 $i$ 的后缀的点向右连。

考虑前一块的最后一个点与这一块的第一个点之间的这段路，这段路被前一块的点经过的贡献已经在前一块处理的时候统计过了，考虑被这一块的点经过的贡献：

- 前块的点比后块多，没有贡献。实现上就是一个后缀取最小值。
- 后块的点比前块多，贡献就是点数差乘上这段路的长度。实现上就是个典。

现在 $f[i]$ 的含义就是这一块有一个长度为 $i$ 的前缀的点向左连。

然后要加上这个前缀的点连到这一块的第一个点的贡献。

然后把 $f$ 翻转，就变成了这一块有一个长度为 $i$ 的后缀的点向下一块连。

然后要加上这个后缀的点连到下一块的第一个点的贡献。

然后就是下一块的事情了。

复杂度是 $\mathcal O(n)$ 的。

## code

```cpp
#include<vector>
#define N 100009
#define int long long
using namespace std;
int n,m,p,f[N];vector<int>c[N];
long long min_total_length(vector<signed>a,vector<signed>b)
{
	n=a.size();m=b.size();
	for(int i=0,j=0;;++p)
	{
		if(i==n)
		{
			for(;j<m;c[p].emplace_back(b[j++]));
			break;
		}
		if(j==m)
		{
			for(;i<n;c[p].emplace_back(a[i++]));
			break;
		}
		if(a[i]<b[j])for(;i<n&&a[i]<b[j];c[p].emplace_back(a[i++]));
		else for(;j<m&&a[i]>b[j];c[p].emplace_back(b[j++]));
	}
	for(int i=0;i<c[0].size();++i)f[c[0].size()]+=c[1][0]-c[0][i];
	for(int i=0;i<c[0].size();f[i++]=1ll<<60);
	for(int i=1;i<=p;++i)
	{
		for(int j=c[i-1].size()+1;j<=c[i].size();f[j++]=1ll<<60);
		for(int j=c[i-1].size()-1;j>=0;--j)f[j]=min(f[j],f[j+1]);
		for(int j=0,minn=1ll<<60;j<=c[i].size();++j)
			minn=min(minn,f[j]-j*(c[i][0]-c[i-1].back())),
			f[j]=min(f[j],minn+j*(c[i][0]-c[i-1].back()));
		for(int j=0,s=0;j<=c[i].size();++j)
		{
			f[j]+=s;
			if(j<c[i].size())s+=c[i][j]-c[i][0];
		}
		for(int j=0;j<c[i].size()-j;++j)swap(f[j],f[c[i].size()-j]);
		if(i==p)break;
		for(int j=0,s=0;j<=c[i].size();++j)
		{
			f[j]+=s;
			if(j<c[i].size())s+=c[i+1][0]-c[i][c[i].size()-j-1];
		}
	}
	return f[0];
}
```

---

## 作者：Sampson_YW (赞：1)

反悔贪心。这题是老鼠进洞的变式。对这类问题不熟，写个题解记一下。

**（声明：对此算法不熟，还是凭感觉写的，所以说的不一定是对的）**

不妨将红点看作老鼠，蓝点看作洞。

问题可以看作：每种老鼠有无限个分身，每种洞也有无限个分身。一只位置在 $x$ 的老鼠进一个位置在 $y$ 的洞需要花费 $|x-y|$ 的代价。求每种老鼠至少进一个洞，每种洞至少进一只老鼠的最小代价。

老鼠和洞的贪心策略是本质相同的，下面考虑老鼠如何贪心。

首先要保证每种老鼠至少进一个洞，那么将每种老鼠分成两类（$\inf$ 表示一个极大值）：

1. 特殊拉出一只老鼠（本体），这只老鼠进洞会产生 $-\inf$ 的额外代价（钦定它必须进洞）。
2. 剩下 $+\inf$ 只老鼠（分身），它们进洞会产生 $0$ 的额外代价（不是必须进洞）。

我们按位置从小到大排序后来贪心。维护两个堆，分别表示可以匹配的老鼠，以及可以匹配的洞。老鼠的堆中记录若干个数对 $(w,v)$，表示有 $v$ 只老鼠，一个位置在 $x$ 的洞和这 $v$ 只老鼠的其中一只匹配的代价为 $x+w$。洞的堆同理。我们钦定老鼠的匹配只能在洞堆里找，洞也只能在老鼠堆里找。

假设当前位置为 $x$。

1. 对于第一类老鼠：它只需要考虑进洞。

- 如果洞堆是空的。

也就是说它前面没有空着的洞，那么就只能丢到老鼠堆里和后面的洞匹配。丢的数对为 $(-x-\inf,1)$，表示后面的洞 $y$ 和它匹配会产生 $y+(-x-\inf)$ 的代价，且这一类只有一只老鼠。

- 如果洞堆不是空的。

由于我们要让它必须进洞，那么我们就让它先和洞堆里的洞匹配一次。提出洞堆堆顶的数对 $(w,v)$，产生 $(x-\inf)+w$ 的代价。此时洞堆只少了一个代价为 $w$ 的洞，将 $(w,v-1)$ 重新丢回洞堆里。

并且这只老鼠还可以“反悔”，也就是断开这次匹配，和后面的洞匹配。相当于在老鼠堆中放入了一个数对，这个数对 $v=1$，$w=-((x-\inf)+w)+(-x-\inf)$，前面的 $-((x-\inf)+w)$ 就是断开这次匹配的代价，$(-x-\inf)$ 就是和后面的洞匹配时会产生的代价，化简后 $w=-(x+w)-x$，也就是向老鼠堆中丢入一个 $(-(x+w)-x,1)$ 的数对。

2. 对于第二类老鼠：它不仅可以进前面的洞，也可以进后面的洞；也可以先占了前面的洞，后面再把这个洞让出去。（为什么会让出去呢？例如：让给第一类老鼠会产生 $-\inf$ 的额外代价使得总代价变小）

（也就是说它的匹配方式在第一类老鼠的基础上还要额外讨论一些）

- 如果洞堆是空的。

同上，向老鼠堆中丢 $(-x,\inf)$，$\inf$ 表示有无数个分身可以匹配。

- 如果洞堆不是空的。

不断提出洞堆堆顶的数对 $(w,v)$。如果 $w+x<0$，那么就说明现在和这个洞匹配比不匹配更优秀（为什么会小于 $0$ 呢？例如：和第一类洞会产生 $-\inf$ 的代价使得总代价变小）。

然后向洞堆丢回一个 $(w,v-1)$ 的数对，向老鼠堆中丢一个 $(-(x+w)-x,1)$ 的数对。这两个数对的含义同上：少了一个代价为 $w$ 的洞、这只老鼠可以断开这次匹配，与后面的洞匹配。

我们现在考虑了进前面的洞的情况，进后面的洞的情况也是很容易的。还剩下一种情况：进了洞之后让出去。由于我们要让老鼠只在洞堆里查询，于是我们要在洞的角度考虑：断开和这只老鼠的匹配，和后面的老鼠匹配。断开的代价为 $-(x+w)$，新匹配的代价为 $w$。因此这种情况需要向洞堆里丢一个 $(-x,1)$ 的数对。

如果 $w+x\ge 0$ 了，就说明不匹配比匹配更优秀，贪心结束。并向老鼠堆中丢一个 $(-x,\inf)$ 的数对，表示还有无数个分身可以匹配。

洞的贪心策略只需要将上面的“老鼠”替换成“洞”，“洞”替换成“老鼠”。

Q：为啥这个复杂度有保证呢？

这就触及到我的知识盲区了（

不过感性理解一下：老鼠本体和洞本体只有 $O(n)$ 个，它们匹配只会向前匹配一次，向后匹配一次，因此它们匹配的次数是 $O(n)$ 的。因此只需要证明老鼠分身与洞分身的匹配次数能够被接受。显然它们匹配多了会不优，所以复杂度有保证（

[code](https://www.luogu.com.cn/paste/1f9rqljd)

---

## 作者：xiezheyuan (赞：0)

> 给定两个升序排列的整数数组 $r$ 和 $b$，分别代表红色点和蓝色点在数轴上的坐标。要求为每个点连接至少一条电线到异色点上，使得所有电线的总长度最短。求最短的总长度。$n=|r|,m=|b|,1\leq n,m\leq 10^5$。

这道题是不是大家都做复杂了，给一个考场上的普及组做法。

先将所有点放在一起排序，这样点 $i$ 就有了一个坐标 $a_i$ 和颜色 $c_i$。Subtask 2 的特殊性质保证了数轴上只存在两个同色块，这启示我们将数轴上按照颜色块分开考虑。

我们发现对于数轴上的每一个同色块，我们一定存在一个分界点，使得左边的点连向左边的与之不同色的块，右边的点连向右边与之不同色的块。然后这里就有一个类似左边决定右边的结构，这启示我们 dp。

设 $f(i)$ 表示前缀 $[1,i]$，且 $i$ 是一个分界点的答案。那么我们转移的话也很简单。我们设 $F(i)$ 分别表示 $i$ 所在的同色块的最左侧的点，那么我们可以得到一个非常简单的方程：

$$
f(i)=\min_{j=F(F(i)-1)}^{F(i)-1} \min(f(j-1),f(j)) C(j, i)
$$

稍微提一下为什么是 $\min(f(j-1),f(j))$ 而不是 $f(j-1)$，这是为了解决 $j$ 所在的同色块就 $j$ 一个数的 Corner Case（对于其他情况，$f(j)$ 肯定不优，所以没有实质影响）。

其中 $C(j,i)$ 表示两个相邻的块，左边的那个块 $j$ 开头的后缀，和右边的那个块的 $i$ 开头的前缀互相连边的最小代价。根据贪心，我们很容易得到：

$$
\begin{aligned}
C(i,j)=&\max(i-F(i)+1,F(i)-j)(a_{F(i)}-a_{F(i)-1})\\
&+\sum_{k=F(i)}^{i} a_k-a_{F(i)}+\sum_{k=j}^{F(i)-1} a_{F(i)-1}-a_k
\end{aligned}
$$

也就是尽量用右边块右侧的点，连接左边块最左侧的点，剩余的点用右边块最左侧的点（或左侧块最右边的点）连接。

这样时间复杂度 $O((n+m)^2)$ 无法通过。到这里其他题解就开始大力拆贡献，但是其实是没有必要的。

观察贡献的表达式，$\min(f(j),f(j-1)),\sum_{k=j}^{F(i)-1} a_{F(i)-1}-a_k,a_{F(i)}-a_{F(i)-1}$ 与 $i$ 无关（他们只与 $j$ 或者 $F(i)$ 有关，而 $F(i)$ 有关的贡献可以在块的最左侧点处处理）。$\sum_{k=F(i)}^{i} a_k-a_{F(i)}$ 则与 $j$ 无关，只有 $\max(i-F(i)+1,F(i)-j)$ 同时与 $i,j$ 相关。

先假设我们已经处理了同时与 $i,j$ 相关的那一部分，也就是已经将上一块的 $j$ 分成了两类：$i-F(i)+1\geq F(i)-j$ 和 $i-F(i)+1<F(i)-j$。那么就有一个显然的优化方法，将与 $j$ 相关的项预先丢到一个小根堆中（这一部分可以在 $F(i)$ 处理，这样时间复杂度就可以保证），然后每次查询堆顶元素就可以进行转移。

然后考虑如何处理 $\max(i-F(i)+1,F(i)-j)$，我们发现我们转移的时候，$i$ 总是在增加，也就是 $i-F(i)+1$ 不断增加而 $F(i)-j$ 不变，因此可以对着 $j$ 这一维双指针，就可以获得在 $i-1\to i$ 时，获得有多少个 $j$ 从 $i-F(i)+1<F(i)-j$ 变成了 $i-F(i)+1\geq F(i)-j$，那么这个堆就要支持删除数和加入数，查询最小值，将堆换成 `std::multiset` 即可。

时间复杂度 $O((n+m)\log (n+m))$ 可以通过。

[Submission](https://qoj.ac/submission/1215495)。

---

