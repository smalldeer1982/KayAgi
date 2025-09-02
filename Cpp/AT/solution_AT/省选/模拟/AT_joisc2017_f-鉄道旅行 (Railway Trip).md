# 鉄道旅行 (Railway Trip)

## 题目描述

#「JOISC 2017 Day 2」火车旅行


**译者水平有限，跪求各位大佬提供更好的译文**

**题目译自 [JOISC 2017](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/index.html) Day2 T3「[鉄道旅行](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d2.pdf)（[Railway Trip](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d2-en.pdf)）」**

某条铁路线（非环线）有 $N$ 站，依次编号为 $1\ldots N$。这条线路上跑着 $K$ 类列车，编号为 $1\ldots K$。每种列车都是双向运行的。  
这条铁路线上的每个车站都有个旅客流量，旅客流量是一个 $\le K$ 的正整数。车站 $i(1\le i\le N)$ 的旅客流量为 $L_i$，$L_1=L_N=K$。  
第 $j$ 类列车 $(1\le j\le N)$ 在且只在旅客流量 $\ge j$ 的车站停车。
现有 $Q$ 名旅客，依次编号为 $1\ldots Q$，旅客 $k(1\le k\le Q)$ 的起点是车站 $A_k$，终点是 $B_k$ $(1\le A_k, B_k\le N)$。假设这些旅客只能靠这条铁路线移动。  
对于每个旅客，求这名旅客的途中至少要**停几次站**（不含该旅客的起终点站）。保证同一名旅客的起点与终点不同。允许走回头路。

## 说明/提示

对于所有数据，$2\le N\le 10^5, 1\le K\le N, 1\le Q\le 10^5, 1\le L_i\le K(1\le i\le N), 1\le A_k, B_k\le N, A_k\not=B_k(1\le k\le Q)$。


感谢 Planet6174 提供的翻译

# 题解

## 作者：StudyingFather (赞：7)

一道非常棒的题。

## Subtask 2

我们考虑建立图论模型，套最短路算法来做。

对于每个点，分别考虑这个点左边和右边的所有点，向它能到达的左边/右边的**第一个点**分别连一条边。

为啥是第一个点呢？目的是为了减少重复的边（$a \to b \to c$ 这条路径只用连 $a \to b$ 和 $b \to c$ 的边，不用连 $a \to c$ 的边了）。

这样连边后的图最多有 $O(N)$ 条边，在新图上跑最短路即可。

时间复杂度 $O(QN \log N)$，期望得分：20 pts。

## Subtask 4

我们接下来从区间的角度来考虑这道题。

我们之前已经求出，在花费为 $1$ 时，从 $i$ 号节点出发，最左可以到达 $l_i$ 号节点，最右可以到达 $r_i$ 号节点。

那么在花费为 $k$ 的时候，从 $i$ 号节点最左和最右可以到达的点怎么求呢？

容易发现这个可以倍增来算。

现在我们把这些区间展开成一棵树：如果区间 $a$ 完全包含了区间 $b$，且区间 $a$ 代表了从 $i$ 出发跳 $k$ 次覆盖的区间，区间 $b$ 代表了从 $i$ 出发跳 $k-1$ 次覆盖的区间，那么我们将 $b$ 挂在 $a$ 下面。

现在来转化问题：我们现在让 $[A,A]$ 和 $[B,B]$ 两个点向上跳，直到它们的父节点相同为止（也就是说这两个区间紧挨着，别忘了起点和终点不算入答案）。这时候我们跳的次数就是答案。

时间复杂度 $O(Q \log N)$，期望得分：100 pts。

```cpp
// Problem : F - 鉄道旅行 (Railway Trip)
// Contest : JOI春合宿2017 オンラインジャッジ
// URL : https://joisc2017.contest.atcoder.jp/tasks/joisc2017_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 512 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <stack>
using namespace std;
int l[100005],f[100005][25],g[100005][25];
stack<int> s;
int main()
{
 ios::sync_with_stdio(false);
 int n,k,q;
 cin>>n>>k>>q;
 for(int i=1;i<=n;i++)
  cin>>l[i];
 for(int i=1;i<=n;i++)
 {
  while(!s.empty()&&l[s.top()]<l[i])
   s.pop();
  if(!s.empty())f[i][0]=s.top();
  else f[i][0]=i;
  s.push(i);
 }
 while(!s.empty())
  s.pop();
 for(int i=n;i;i--)
 {
  while(!s.empty()&&l[s.top()]<l[i])
   s.pop();
  if(!s.empty())g[i][0]=s.top();
  else g[i][0]=i;
  s.push(i);
 }
 for(int k=1;k<=17;k++)
  for(int i=1;i<=n;i++)
  {
   f[i][k]=min(f[f[i][k-1]][k-1],f[g[i][k-1]][k-1]);
   g[i][k]=max(g[f[i][k-1]][k-1],g[g[i][k-1]][k-1]);
  }
 while(q--)
 {
  int a,b,l,r;
  cin>>a>>b;
  if(a>b)swap(a,b);
  int ans=0;
  l=r=a;
  for(int k=17;k>=0;k--)
  {
   int u=min(f[l][k],f[r][k]),v=max(g[l][k],g[r][k]);
   if(v<b)
   {
    l=u,r=v;
    ans+=(1<<k);
   }
  }
  a=r;
  l=r=b;
  for(int k=17;k>=0;k--)
  {
   int u=min(f[l][k],f[r][k]),v=max(g[l][k],g[r][k]);
   if(u>a)
   {
    l=u,r=v;
    ans+=(1<<k);
   }
  }
  cout<<ans<<endl;
 }
 return 0;
}
```

---

## 作者：hello_world_djh (赞：6)

UPD on 2023.10.9：讨论区有人对于倍增的部分有疑问，我同机房的大佬表示这篇文章太过简略，所以从新写一下部分正确性证明和推导过程。

我来交作业啦！

其实本蒟蒻也是刚学倍增优化dp，过来给 [do_while_true](https://www.luogu.com.cn/user/223298) 大佬交作业。

sto dwt orz

进入正题：

简要题面：每辆火车都会在客流量大于等于自己类别的车站停车，已知每个车站的客流量和每个乘客的起始点站，求最少的停车数量。

考虑对问题转化，每个站点对于所有能到达它本身的站点连边。再考虑减少边数。

考虑每条边的样子：

![边](https://cdn.luogu.com.cn/upload/image_hosting/jejv4xel.png)

这里 $k$ 表示 $i$ 站点和 $j$ 站点之间因为 $k$ 类型的列车而相连。这里 $k$ 的取值范围一定是一段连续的区间 $(\min_{i < t < j}(h_t),\min(h_i,h_j)]$（这里 $h_i$ 表示 $i$ 的客流量），因为如果 $k$ 过小就会被 $i,j$ 之间的某一个点截停，如果 $k$ 过大就会越过 $i$ 或 $j$ 到达更远的地方，所以在优化边数的情况下，对于每个 $k$ 只有取到最大值时连肯定是正确的。所以我们删去所有取不到的边，只保留取最大值的边，共有 $2n$ 条。

我们考虑使用倍增法：

设 $l(i,j)$ 表示从 $i$ 站点出发，停靠 $2^j$ 次能够到达最靠左的站点的编号。

设 $r(i,j)$ 表示从 $i$ 站点出发，停靠 $2^j$ 次能够到达最靠右的站点的编号。

我们考虑如何对这两个状态更新，因为题目中说过：

> 允许走回头路。

所以 $j$ 往外扩展一个，两个状态都可以通过之前状态的两边更新过来，所以状态转移方程为：

$l(i,j) = \min {l(l(i,j - 1),j - 1), l(r(i,j - 1),j - 1)}$

$r(i,j) = \max {r(r(i,j - 1),j - 1), r(l(i,j - 1),j - 1)}$

更新时就在终点站的限制下将起点站往右跳，再以新的起点站为限制将终点站往左跳，倍增汇总答案即可。由于倍增数组更新是由两边更新而来，所以左右跳的所有情况都会不漏的被统计并去最大和最小值，所以统计答案的时候直接跳就可以。

Q：为什么从 $l(i,j-1)$ 更新 $r(i,j)$ 不会漏掉跳的步数不是整好为 $2^{j-1}$ 的情况？

A：考虑你并不是整好跳 $2^{j-1}$ 步的情况，而是先往整体上（有可能折返）往左跳 $2^x$ 步，再整体上往右跳 $2^j - 2^x$ 步的情况（假定 $j > x$），我们在你整体往右的 $2^j - 2^x$ 步中一定可以找到一个点是你整体上往左跳 $2^x$ 后的点再整体上往右跳 $2^x$ 的那个点。然后这个路程就被拆成先跳到 $r(i,x)$ 的位置，在整体上往右跳 $2^j - 2^x$ 步，这种情况会在统计答案的时候枚举到。所以这么跳的正确性是对的。

 

```cpp
//省略头文件和快读板子
const int N = 1e5 + 10;
int n, q, L[N][40], R[N][40], a[N], st[N], top;

int main() {
    n = read<int>();
    read<int>();
    q = read<int>();
    for (int i = 1; i <= n; i++)
        a[i] = read<int>();
    for (int i = 1; i <= n; i++) {
        while (top && a[st[top]] < a[i])
            top--;
        if (top)
            L[i][0] = st[top];
        else
            L[i][0] = i;
        st[++top] = i;
    }
    top = 0;
    for (int i = n; i; i--) {
        while (top && a[st[top]] < a[i])
            top--;
        if (top)
            R[i][0] = st[top];
        else
            R[i][0] = i;
        st[++top] = i;
    }
    for (int j = 1; j <= 16; j++)
        for (int i = 1; i <= n; i++) {
            L[i][j] = std::min(L[L[i][j - 1]][j - 1], L[R[i][j - 1]][j - 1]);
            R[i][j] = std::max(R[R[i][j - 1]][j - 1], R[L[i][j - 1]][j - 1]);
        }
    while (q--) {
        int x = read<int>(), y = read<int>(), ans = 0;
        if (x > y) x ^= y ^= x ^= y;
        int l = x, r = x;
        for (int i = 16; i >= 0; i--) {
            int nwl, nwr;
            nwl = std::min(L[l][i], L[r][i]);
            nwr = std::max(R[l][i], R[r][i]);
            if (nwr < y) {
                l = nwl;
                r = nwr;
                ans += 1 << i;
            }
        }
        x = r;
        l = r = y;
        for (int i = 16; i >= 0; i--) {
            int nwl, nwr;
            nwl = std::min(L[l][i], L[r][i]);
            nwr = std::max(R[l][i], R[r][i]);
            if (nwl > x) {
                l = nwl;
                r = nwr;
                ans += 1 << i;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

本蒟蒻刚学此算法，请各路大佬轻点喷，ありがとうございます。

---

## 作者：Purslane (赞：4)

# Solution

没记错的话这是 APIO 2024 的试机题？

题解区的有点一言难尽，倍增为什么是对的？为什么能直接从端点转移？为什么可以用“区间”表示？

想要把这题搞明白，还是需要一些小分析的。

PS：现在洛谷题解区有一个很明显的现象，就是 A 发了一篇不大严谨的题解，很快就会出现类似的、不加任何证明（甚至提都不提就默认正确）的题解。个人不认为这属于抄袭题解，而是看了一篇题解，没真的看明白，却以为自己懂了……这样很难提高水平。

UPD：太幽默了，变成自己骂的人了（第一遍题解真伪了）。感谢 @0x3b800001 老师的斧正！

----------

如果 $i$ 能做火车直达 $j$，那么在 $i$ 和 $j$ 之间连边，边权为 $1$。本质上就是询问 $A_i$ 到 $B_i$ 的最短路。

设 $i<j$，$i$ 能到 $j$ 的充要条件是：$\max_{i < k < j} L_k < \min\{L_i,L_j\}$。因此很容易用单调栈算出找到所有的边。

这样就有暴力分了。（但是你发现，瓶颈还是在于求最短路，所以和 $O(n^2)$ 找边没区别……）

----------

分析一下最短路的结构。

假设我们经过了相邻三个点，高度分别是 $h_1,h_2,h_3$。

如果 $h_1 > h_2$，且 $h_2 < h_3$，则一定会有 $h_1 \to h_3$ 存在边。更加一般的，如果 $h_1,h_2 \cdots,h_t$ 存在 $i<j$，满足 $h_i > h_{i+1}$ 和 $h_j < h_{j+1}$，一定可以调整的更优。

**因此，我们一定可以将结构视为：$a$ 不断往更高的地方跳，$b$ 也不断往更高的地方跳，直到最近的公共点**。

某种意义上，图的边就是有向的了。但是这并不能帮我们加速最短路。（因为最短路算法中有向图和无向图没有本质区别）

一篇题解认为，必经点为 $a$ 和 $b$ 之间的最高点，这实际上是错误的，考虑以下数据：

```
4 1 2 3 2 1 4
```

要从左边那个 $1$ 赶到右边那个 $1$，显然最优的路径为先到左边那个 $4$，再到最右边的 $4$，最后回到 $1$。

------------

给定一个点，考虑它能跳的结构。

结论：设 $l_i$ 和 $r_i$ 是 $i$ 向左右两边跳一次得到的点。则 $i$ 能跳到的点为向左不断跳 $l$ 和向右不断跳 $r$ 经过的点。

充分性是显然的。我们只需要证明：$i$ 向做跳了若干次 $l$ 后，再跳一次 $r$，得到的点可以通过原始的 $i$ 跳若干次 $r$ 得到。假设跳到的这个点为 $j$，是从 $t$ 跳过来的。如果不能通过 $i$ 跳 $r$ 得到，则必存在 $i<k<r$ 使得 $h_k > h_r$，这样 $t$ 就不能跳到 $j$ 了，矛盾！

![pAXFWi6.png (629×524) (ax1x.com)](https://s21.ax1x.com/2024/12/21/pAXFWi6.png)

不放设 $a<b$，同时画出他们能跳的点，大概长这样： 

![pAXFbdI.png (693×486) (ax1x.com)](https://s21.ax1x.com/2024/12/21/pAXFbdI.png)

定义 $c$ 为 $(a,b)$ 中的最大值（可能会有 $c=a$ 或 $c=b$ 的情况，但是这种情况应该比较平凡，先不做考虑）如果有多个，取最右边的那一个。

如果最终跳到的最高点在 $(a,b)$ 之间，显然取最高点中的任何一个都是可以的（因为从 $a$ 开始跳，必定得经过最高点中最左边那一个，$b$ 必须经过最高点中最右边那一个，所以到这些所有点的路程之和是相等的），我们不妨认为是最右边的那个。

如果最终跳到的最高点在 $[b,n]$ 之间（$[1,a]$ 是同理的），那么从 $a$ 开始跳，第一次到达一个 $\ge b$ 的位置 $e$。

## CASE I：如果想用最少的步数到达 $b$ 即右边的位置，是从 $d$，即 $a$ 左边的一个位置跳到 $e$ 的。则 $\min\{h_d,h_e\} > h_c$。

![](https://s21.ax1x.com/2024/12/21/pAXkEWT.png)

取 $d$ 为 **$a$ 经过 $x$ 步能到达的最远的点中，$h_d > h_c$ 的第一个位置**（注意此时不能有 $a$ 经过 $x$ 步能越过 $b$。否则，是从 $c$ 那边跑过去的，这会与我们下一种情况重复）。考虑这个极端值原理保证了什么东西：

1. 对于 $a$ 和 $d$ 之间可能经过的一个点 $g$，必有 $h_g \le h_c$。想一下为什么它不能成为 $d$，只有两种可能：一个是它需要的步数比 $d$ 多，一个是它跳不过 $c$。显然，当 $h_g > h_c$ 时这两件事情都不会发生。
2. 显然，我们到 $e$ 之后不会继续往右跳，这样很不划算（从 $b$ 开始跳的时候，到 $e$ 的步数肯定比到更远的地方的步数要少，这个应该不用证明！）
3. 对于 $b$ 和 $e$ 中的一个点 $t$，如果最优情况实际上最终没跳到 $e$，而是从 $b$ 跳到了其左边，设最后一次离开的位置是 $m$。
   1. $m$ 为 $h$，表现为 $h_m \le h_c$，这样从 $m$ 开始跳，一定会跳到 $c$（因为不会回来了。其实也有可能跳到 $b \to c$ 的斜坡，但是不重要了），然后到 $c'$，最后到 $d$。
   2. $m$ 为 $f$，表现为 $h_m > h_c$，这样直接会跳到 $d$。
4. 如果最优情况是在 $e$，那么 $e$ 往左可以调到 $k$ 左边的一个位置。

看见没有？这种情况下，我们表现为：

1. 尝试找到一个这样的 $x$ 和 $d$。
2. 从 $b$ 开始跳尽量少的步数，使得它能到达一个 $\le d$ 的位置（实际上，如果走 $x$ 步 $a$ 到达的向右最远位置是 $r$，满足 $\le r$ 即可。如果 $h_r=h_c$，那么相当于最终相遇在 $(a,b)$ 之间。否则，$\le r$ 必然 $\le d$ ）。

具体怎么找怎么算，这里先不管。

## CASE II：如果想用最少的步数到达 $b$ 即右边的位置，是从 $c$ 跳到 $e$ 的。

![pAXkxtx.png (983×603) (ax1x.com)](https://s21.ax1x.com/2024/12/22/pAXkxtx.png)

这种情况看起来简单一点。显然如果最优汇点在 $b$ 的右侧，$e$ 就是最优的。

因此设 $b$ 到 $e$ 要 $x$ 步，在 $x$ 步内 $b$ 到达的最远点是 $l$ 和 $r$。

如果到 $c$ 的步数 $\le x$，那么可跳到 $c$ 去，这样最优。所以 $c < l $。

然后再跳一步，一定可以到达一个甚至在 $a$ 左边的位置 $f$。（由于 $h_1 = m$，这样的 $f$ 一定存在！！）

所以这种过程我们实际上是：

1. 通过 $t$ 步，从 $a$ 跳到 $c$。
2. 在不到达 $\le c$ 的点的情况下，从 $b$ 跳尽量多的步数。如果下一步到了 $c$，就是在 $c$ 相遇；否则，就是在 $e$ 相遇。

综合两个 CASE，发现我们可以把算法归结为同一种：

1. 通过 $a$ 跳尽量多的步，使右端点还是 $< b$。最终得到了右端点 $r$。
2. 通过 $b$ 跳尽量多的步，使左端点 $> r$。
3. 假设分别跳了 $x$ 和 $y$ 步，两点间最短路为 $x+y+1$，答案就是 $x+y$。

而如何得知“跳 $x$ 步能得到的最远和最近点在哪里？”

回到刚开始的单调栈结构，我们发现，只需要**倍增维护左右两个端点**，每次通过这两个点扩展即可。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,k,q,v[MAXN],l[MAXN][20],r[MAXN][20]; 
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>q;
	ffor(i,1,n) cin>>v[i];
	stack<int> st;
	st.push(0);
	ffor(i,1,n) {
		while(st.top()&&v[i]>v[st.top()]) st.pop();
		if(st.top()==0) l[i][0]=i;
		else l[i][0]=st.top();
		st.push(i);	
	}
	while(!st.empty()) st.pop();
	st.push(n+1);
	roff(i,n,1) {
		while(st.top()!=n+1&&v[i]>v[st.top()]) st.pop();
		if(st.top()==n+1) r[i][0]=i;
		else r[i][0]=st.top();
		st.push(i);	
	}
	ffor(d,1,19) ffor(i,1,n) l[i][d]=min(l[l[i][d-1]][d-1],l[r[i][d-1]][d-1]),r[i][d]=max(r[l[i][d-1]][d-1],r[r[i][d-1]][d-1]);
	ffor(i,1,q) {
		int a,b;
		cin>>a>>b;
		if(a>b) swap(a,b);
		int ans1=0,p1=a,p2=a;
		roff(d,19,0) if(max(r[p1][d],r[p2][d])<b) {
			ans1+=(1<<d);
			int n1=min(l[p1][d],l[p2][d]),n2=max(r[p1][d],r[p2][d]);
			p1=n1,p2=n2;
		}
		a=p2,p1=p2=b;
		roff(d,19,0) if(min(l[p1][d],l[p2][d])>a) {
			ans1+=(1<<d);
			int n1=min(l[p1][d],l[p2][d]),n2=max(r[p1][d],r[p2][d]);
			p1=n1,p2=n2;
		}
		cout<<ans1<<'\n';
	}
	return 0;
}
```

---

## 作者：寻逍遥2006 (赞：3)

~~为什么没有人写三角剖分，这不显得我很蠢~~。

感觉原题很像最短路问题，我们先尝试构建出一张图。

我们想要知道，对于哪些点对 $(i,j)$，在他们之间通行是可以不停靠的。也就是对于哪些点对 $(i,j)$，满足 $\exists k,k\le \min(L_i,L_j)\land k> \max\limits_{k=i+1}^{j-1}L_k$。

假设 $L_i\le L_j$，则对于每一个 $i$ 来说，$j$ 就是左侧和右侧最靠近 $i$ 且满足 $L_j\ge L_i$ 的数。

我们尝试说明这张图的形态：我们考虑建出大根的笛卡尔树，则一个点 $i$ 连边的就是它的祖先集合 $U$ 中最小的 $\ge i$ 的点和最大的 $\le i$ 的点。

而这样的结构刚好构成的是一个以 $1\to 2\to \dots \to n\to 1$ 为哈密顿环的一组三角剖分的子图。所以我们通过补齐若干边就可以将原问题变成三角剖分最短路问题。

考虑三角剖分的经典分治做法。我们希望找到一条非环边 $(U,V)$，考虑每一组询问 $A,B$，查询 $A,B$ 在经过的点 $U$ 或点 $V$ 的路径中的最短路，其等于 $\min(dis(U,A)+dis(U,B),dis(V,A)+dis(V,B))$，而对于 $A,B$ 不经过 $U,V$ 的路径的情况，它就变成了在一个更小的三角剖分上的问题，可以分治处理。

现在我们要找到一个合适的 $(U,V)$，使得它分成的两个小三角剖分尽可能均匀，也就是较小的那一块尽可能的大。我们可以证明至少找得到一条边，使得较小的那边的大小至少为原图的 $\dfrac{1}{3}$。由于边权均为 $1$，所以可以直接用 bfs 找最短路，时间复杂度 $O(n)$。这样最坏情况下的时间复杂度也是 $O((n+Q)\log n)$。

虽然比倍增难写，但是这种做法就是不动脑子的经典模型套用。

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
int n,k,Q;
int L[100010],ans[100010];
struct Edge{int u,v;bool con;};
struct Query{int s,t,ind;};
int f[20][20];
int bel[100010];
int ind1[100010],ind2[100010];
vector<int> ed[100010];
int disu[100010],disv[100010];
queue<int> que;
void solve(int n,vector<Edge> &E,vector<Query> &Q)
{
	if(Q.empty()) return;
	if(n<=5)
	{


		memset(f,0x3f,sizeof(f));
		for(Edge &g:E) if(g.con) f[g.u][g.v]=f[g.v][g.u]=1;
		for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		for(Query &g:Q)	ans[g.ind]=min(ans[g.ind],f[g.s][g.t]);
		return;
	}

	for(int i=0;i<n;i++) vector<int>().swap(ed[i]);

	int mn=0,tm=0,rea;Edge id;
	for(Edge &g:E)
	{
		if(g.con)
		{
			ed[g.u].push_back(g.v);
			ed[g.v].push_back(g.u);
		}

		tm=abs(g.u-g.v);
		tm=min(tm,n-tm);
		if(tm>=mn) mn=tm,id=g;
	}
	if(id.u>id.v) swap(id.u,id.v);

	ind1[id.u]=0,ind1[id.v]=id.v-id.u;
	ind2[id.v]=0,ind2[id.u]=n+id.u-id.v;
	bel[id.u]=bel[id.v]=0;
	for(int i=id.u+1;i<id.v;i++) bel[i]=1,ind1[i]=i-id.u;
	for(int i=id.v+1;i<n;i++) bel[i]=2,ind2[i]=i-id.v;
	for(int i=0;i<id.u;i++) bel[i]=2,ind2[i]=i+n-id.v;

	memset(disu,0x3f,(n+1)<<2);
	que.push(id.u);disu[id.u]=0;
	while(!que.empty())
	{
		rea=que.front();que.pop();
		for(int v:ed[rea])
			if(disu[v]==0x3f3f3f3f)
				disu[v]=disu[rea]+1,que.push(v);
	}

	memset(disv,0x3f,(n+1)<<2);
	que.push(id.v);disv[id.v]=0;
	while(!que.empty())
	{
		rea=que.front();que.pop();
		for(int v:ed[rea])
			if(disv[v]==0x3f3f3f3f)
				disv[v]=disv[rea]+1,que.push(v);
	}

	vector<Query> Ql,Qr;

	for(Query &g:Q)
	{
		ans[g.ind]=min(ans[g.ind],min(disu[g.s]+disu[g.t],disv[g.s]+disv[g.t]));
		if(bel[g.s]!=bel[g.t]||bel[g.s]==0||bel[g.t]==0);
		else if(bel[g.s]==1) Ql.push_back(Query{ind1[g.s],ind1[g.t],g.ind});
		else Qr.push_back(Query{ind2[g.s],ind2[g.t],g.ind});
	}

	vector<Edge> El,Er;
	El.push_back(Edge{ind1[id.u],ind1[id.v],id.con});
	Er.push_back(Edge{ind2[id.u],ind2[id.v],id.con});
	for(Edge &g:E)
	if(bel[g.u]||bel[g.v])
	{
		if((bel[g.u]|bel[g.v])==1) El.push_back(Edge{ind1[g.u],ind1[g.v],g.con});
		else Er.push_back(Edge{ind2[g.u],ind2[g.v],g.con});
	}
	int Ln=ind1[id.v],Rn=ind2[id.u];
	solve(Ln+1,El,Ql),solve(Rn+1,Er,Qr);
}
int stk[100010],top;
vector<Edge> E;
vector<Query> P;
int main()
{
	n=Qread(),k=Qread(),Q=Qread();
	for(int i=1;i<=n;i++) L[i]=Qread();

	for(int i=1;i<=n;i++)
	{
		while(top&&L[stk[top]]<L[i]) top--;
		if(top) E.push_back(Edge{stk[top],i,true});
		else E.push_back(Edge{0,i,false});
		if(top==0||L[stk[top]]>L[i]) top++;stk[top]=i;
	}

	top=0;
	for(int i=n;i;i--)
	{
		while(top&&L[stk[top]]<L[i]) top--;
		if(top)
		{
			if(L[stk[top]]>L[i]) E.push_back(Edge{stk[top],i,true});
			else if(top>1) E.push_back(Edge{stk[top-1],i,false});
			else E.push_back(Edge{n+1,i,false});
		}
		else E.push_back(Edge{n+1,i,false});
		if(top==0||L[stk[top]]>L[i]) top++;stk[top]=i;
	}

	E.push_back(Edge{0,n+1,false});

	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=Q;i++)
		P.push_back(Query{Qread(),Qread(),i});
	solve(n+2,E,P);
	for(int i=1;i<=Q;i++)
		printf("%d\n",ans[i]-1);
	return 0;
}
```

---

## 作者：chenwenmo (赞：2)

### 题意
某条铁路线（非环线）有 $N$ 站，依次编号为 $1\ldots N$。这条线路上跑着 $K$ 类列车，编号为 $1\ldots K$。每种列车都是双向运行的。  
这条铁路线上的每个车站都有个旅客流量，旅客流量是一个 $\le K$ 的正整数。车站 $i(1\le i\le N)$ 的旅客流量为 $L_i$，$L_1=L_N=K$。  
第 $j$ 类列车 $(1\le j\le N)$ 在且只在旅客流量 $\ge j$ 的车站停车。
现有 $Q$ 名旅客，依次编号为 $1\ldots Q$，旅客 $k(1\le k\le Q)$ 的起点是车站 $A_k$，终点是 $B_k$ $(1\le A_k, B_k\le N)$。假设这些旅客只能靠这条铁路线移动。  
对于每个旅客，求这名旅客的途中至少要**停几次站**（不含该旅客的起终点站）。保证同一名旅客的起点与终点不同。允许走回头路。  
### 思路
我一开始的思路是将每个站和它左边和右边第一个 $\ge$ 它的站点连边，但是我不知道怎么快速求最短路，一看题解要用三角剖分，就放弃了（~~本蒟蒻不会~~。

对于起点 $x$ 和终点 $y$，要从起点跳到终点，经过的点（也就是要停的站），一定是一个上凸的结构，$p_1\le p_2\le ...\ p_i\ge p_{i+1}\ge p_{i+2}\ ...$，证明很容易，因为如果中间有一段是下凸，也就是往下跳，$p_1\ge p_2\le p_3$，那还不如直接从 $p_1$ 跳到 $p_3$。  
因此路径上必有一个点，是起点和终点**路径**之间最高的点。  
那么我们要做的就是求出起点到中间最高点的最短距离，以及终点到最高点的距离只有 $1$ 的最短距离，加起来就是答案了。  
考虑倍增优化，设 $l(j,i)$ 表示从 $i$ 点跳 $2^j$ 步最左跳到哪，$r(j,i)$ 表示最右跳到哪，因为要跳最远，那么每次肯定往流量大于等于它的站点跳，证明和上面类似。  

转移方程：$l(j,i)=\min(l(j-1,l(j-1,i)),l(j-1,r(j-1,i)))$，$r$ 同理。  
$l(0,i)$ 就是左边第一个大于等于它的站，可以用单调栈求出。
### 代码

```cpp
const int N = 1e5 + 10, L = 30;

int n, k, q, a[N], l[L][N], r[L][N];
stack <int> s;
ll ans;

void Solve(){
	cin >> n >> k >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		while(!s.empty() && a[s.top()] <= a[i]){
			r[0][s.top()] = i;
			if(!l[0][i] && a[s.top()] == a[i]) l[0][i] = s.top();
			s.pop();
		}
		if(!s.empty() && !l[0][i] && a[s.top()] > a[i]) l[0][i] = s.top();
		s.push(i); 
	}
	l[0][1] = 1;
	r[0][n] = n;
	for(int i = 1; i <= 20; i++){
		for(int j = 1; j <= n; j++){
			l[i][j] = min(l[i - 1][l[i - 1][j]], l[i - 1][r[i - 1][j]]);
			r[i][j] = max(r[i - 1][r[i - 1][j]], r[i - 1][l[i - 1][j]]);
		}
	}
	while(q--){
		ans = 0;
		int x, y;
		cin >> x >> y;
		if(x > y) swap(x, y);
		int L = x, R = x;
		for(int i = 20; i >= 0; i--){
			int tL = min(l[i][L], l[i][R]);
			int tR = max(r[i][L], r[i][R]);
			if(tR < y){
				ans += (1ll << i);
				L = tL;
				R = tR;
			}
		}
		x = R, L = y, R = y;
		for(int i = 20; i >= 0; i--){
			int tL = min(l[i][L], l[i][R]);
			int tR = max(r[i][L], r[i][R]);
			if(tL > x){
				ans += (1ll << i);
				L = tL;
				R = tR;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

[鉄道旅行 (Railway Trip) ](https://www.luogu.com.cn/problem/AT_joisc2017_f)

# 分析

非常神仙的倍增做法。

我们设 $l_{i,j}$ 表示从 $i$ 点出发，停靠 $2^j$ 站后能抵达的最左位置。

同理设 $r_{i,j}$ 表示从 $i$ 点出发，停靠 $2^j$ 站后能抵达的最右位置。

考虑如何更新这两个状态。

因为可以走回头路，所以简单的 $l_{i,j}=l_{l_{i, j-1}, j-1}$ 和 $r_{i,j}=r_{r_{i, j-1}, j-1}$ 这种倍增方法是不行的。

我们可以考虑从两个端点来更新。

递推式如下：

$$
\begin{aligned}

l_{i,j}&=\min(l_{l_{i, j-1}, j-1}, l_{r_{i, j-1}, j-1})\\
r_{i,j}&=\max(r_{l_{i, j-1}, j-1}, r_{r_{i, j-1}, j-1})

\end{aligned}
$$

每次查询时先从较左点向两侧扩展区间，如果该区间没有包含较右点，那么就扩展区间并统计答案。

然后再从较右点向两侧扩展区间，如果两区间没有交，那么扩展区间并统计答案。

最后得到的两区间再扩展一步就一定会有交。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005

int lis[maxn], l[maxn][18], r[maxn][18], stk[maxn], *top=stk;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, k, q;
    cin>>n>>k>>q;
    for(int i=1;i<=n;i++) cin>>lis[i];
    for(int i=1;i<=n;i++)
    {
        while(top!=stk&&lis[*top]<lis[i]) top--;
        if(top!=stk) l[i][0]=*top;
        else l[i][0]=i;
        *++top=i;
    }
    top=stk;
    for(int i=n;i;i--)
    {
        while(top!=stk&&lis[*top]<lis[i]) top--;
        if(top!=stk) r[i][0]=*top;
        else r[i][0]=i;
        *++top=i;
    }
    for(int j=1;j<18;j++)
        for(int i=1;i<=n;i++)
            l[i][j]=min(l[l[i][j-1]][j-1], l[r[i][j-1]][j-1]),
            r[i][j]=max(r[l[i][j-1]][j-1], r[r[i][j-1]][j-1]);
    int a, b, ans;
    while(q--)
    {
        cin>>a>>b;
        ans=0;
        if(a>b) swap(a, b);
        int lx=a, rx=a;
        for(int i=17, nl, nr;~i;i--)
        {
            nl=min(l[lx][i], l[rx][i]);
            nr=max(r[lx][i], r[rx][i]);
            if(nr<b) lx=nl, rx=nr, ans+=1<<i;
        }
        a=rx;
        lx=rx=b;
        for(int i=17, nl, nr;~i;i--)
        {
            nl=min(l[lx][i], l[rx][i]);
            nr=max(r[lx][i], r[rx][i]);
            if(nl>a) lx=nl, rx=nr, ans+=1<<i;
        }
        cout<<ans<<'\n';
    }
}
```

---

## 作者：5k_sync_closer (赞：0)

对每次询问，先求出最优方案下，左端点最多往右端点逼近几步，

然后同样求出最优方案下，右端点最多往逼近后的左端点逼近几步，

最后再逼近一步使左右端点重合即可。

倍增优化这个逼近的过程。

具体地，维护 $l_{i,j}/r_{i,j}$ 表示从 $i$ 走 $2^j$ 步最左 / 右能走到哪，

然后 $l_{i,j}=\min\{l_{l_{i,j-1},j-1},l_{r_{i,j-1},j-1}\},r_{i,j}=\max\{r_{r_{i,j-1},j-1},r_{l_{i,j-1},j-1}\}$。

$l_{i,0},r_{i,0}$ 容易单调栈求出。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, z, a[400050], p[400050], s[100050], l[400050][20], r[400050][20];
int main()
{
    scanf("%d%*d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
    {
        while (z && a[i] > a[s[z]])
            --z;
        l[i][0] = z ? s[z] : 1;
        s[++z] = i;
    }
    z = 0;
    for (int i = n; i >= 1; --i)
    {
        while (z && a[i] > a[s[z]])
            --z;
        r[i][0] = z ? s[z] : n;
        s[++z] = i;
    }
    for (int j = 1; 1 << j <= n; ++j)
        for (int i = 1; i <= n; ++i)
            l[i][j] = min(l[l[i][j - 1]][j - 1], l[r[i][j - 1]][j - 1]),
            r[i][j] = max(r[r[i][j - 1]][j - 1], r[l[i][j - 1]][j - 1]);
    for (int i = 0, u, v, x, y, q; i < m; ++i)
    {
        scanf("%d%d", &u, &v);
        if (u == v)
        {
            puts("0");
            continue;
        }
        if (u > v)
            swap(u, v);
        q = 0;
        x = y = u;
        for (int i = __lg(n), f, g; i >= 0; --i)
        {
            f = min(l[x][i], l[y][i]);
            g = max(r[x][i], r[y][i]);
            if (g < v)
                x = f, y = g, q |= 1 << i;
        }
        u = y;
        x = y = v;
        for (int i = __lg(n), f, g; i >= 0; --i)
        {
            f = min(l[x][i], l[y][i]);
            g = max(r[x][i], r[y][i]);
            if (f > u)
                x = f, y = g, q += 1 << i;
        }
        printf("%d\n", q);
    }
    return 0;
}
```


---

