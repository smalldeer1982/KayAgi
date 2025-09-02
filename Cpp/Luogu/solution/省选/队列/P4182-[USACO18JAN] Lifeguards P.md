# [USACO18JAN] Lifeguards P

## 题目描述

Farmer John 为他的奶牛们开设了一个游泳池，认为这将帮助它们放松并产更多的奶。

为了确保安全，他雇佣了 $N$ 头奶牛作为救生员，每头奶牛的班次覆盖一天中的某个连续时间段。为简单起见，游泳池每天从时间 $0$ 开放到时间 $10^9$，因此每个班次可以用两个整数描述，分别表示奶牛开始和结束其班次的时间。例如，一头救生员从时间 $t = 4$ 开始到时间 $t = 7$ 结束，覆盖了 $3$ 个单位的时间（注意端点表示时间点）。

不幸的是，Farmer John 多雇佣了 $K$ 名救生员，超出了他的资金支持范围。鉴于他必须解雇恰好 $K$ 名救生员，剩下的救生员的班次能够覆盖的最长时间是多少？如果至少有一名救生员在场，则某个时间段被视为被覆盖。

## 说明/提示

在这个例子中，Farmer John 应该解雇覆盖 $1 \ldots 8$ 和 $7 \ldots 15$ 的救生员。

## 样例 #1

### 输入

```
3 2
1 8
7 15
2 14```

### 输出

```
12
```

# 题解

## 作者：Unordered_OIer (赞：35)

# P4182 题解
## 题意
提供 $n$ 个区间，要求删去 $k$ 个区间后剩下的区间覆盖长度最大。

（吐槽本题翻译，看英文才看懂的）

## 建模
我们先从一些特殊情况考虑。如果区间 $A$ 完全覆盖区间 $B$ ，那么删去这样的 $B$ 区间完全没有用，因此我们先删除这种情况。

接下来，不难看出我们可以先对所有的区间进行一次排序，并且可以证明**按照左端点排序或者右端点排序后，左端点和右端点都保持升序**。

证明如下：  
如果存在左端点 $l_i \leq l_{i+1}$ 且 $r_i \geq r_{i+1}$ ，那么区间 $i$ **完全覆盖**区间 $i+1$ ，这种情况在一开始的**特殊情况考虑**中就已经被删除。  
$∴$ 不存在 $l_i \leq l_{i+1}$ 且 $r_i \geq r_i+1$ ，因此一定左右端点都保持升序，证毕。

然后我们就可以进行**区间** $dp$ 了。

根据题目，我们设 $f[i][j]$ 表示**前 $i$ 个区间，删除 $j$ 个的最大覆盖长度**。但是转移的时候，存在的问题是**并不确定覆盖的状态**，不方便转移。

具体化 $f[i][j][S]$ 表示**前 $i$ 个区间，删除 $j$ 个，状态为 $S$ 的最大覆盖长度**？爆空间。

因此我们最好把状态控制在 $2$ 维，且要具体化，因此我们可以这样定义： $f[i][j]$ 表示**前 $i$ 个区间，删除 $j$ 个的最大覆盖长度，**$\color{red}{\normalsize{\mathbf{并且限制选第}}}$ $\color{red}{i}$ $\color{red}{\normalsize{\mathbf{个}}}$。

转移方程：
$$f[i][j]=\max\{f[k][j-\text{len}(k,i)],R[i]-\max(L[i],R[k])\}\ |\ k<i$$

其中 $\text{len}(l,r)=r-l-1$

复杂度 $\Theta(n \times k^2)$ ，明显 $\colorbox{#052242}{\text{\color{white}TLE}}$ 。

## 优化
我们继续把转移方程贴一遍：
$$f[i][j]=\max\{f[k][j-\text{len}(k,i)],R[i]-\max(L[i],R[k])\}\ |\ k<i$$
把它转化一下：
$$f[i][j]=\max\{f[k][k-\text{len}(k,i)],R[i]-L[i]\}\ |\ \text{\footnotesize{对于比较小的}}\ k$$

如果我们能够用**预计算**把 $\Theta(k)$ 的转移变为 $\Theta(1)$ 的，那么总复杂度即为 $\Theta(nk)$ ，对于这种情况就 $\colorbox{#52C41A}{\text{\color{white}{AC}}}$ 了。

这是对于较小的 $k$ 的情况。

那么对于较大的 $k$ 的情况？  
这时的转移方程是：
$$f[i][j]=\max\{f[k][k-\text{len}(k,i)],R[i]-R[k]\}$$  
记 $que\_t$ 表示所有 $f[k][k+t]-R[k]$ 的最大值，单调队列即可。

那如果 $k$ 有限制，不能太小？还是**单调队列**。

当 $k$ 有限制，第二种情况在哪里求最大值？  
$f[i][j]=que\_t[j-i+1]$ 队列里的首位 $+R[i]$ （不满足 $L[i]<R[k]$ 就离队，顺便更新 $que\_t[j-i+1]$ ）。  
并且，我们同时将 $f[i][j]$ 用 $que\_t[j-i+1]$ 来更新一下。

算完之后，更新单调队列，把 $f[i][j]-R[i]$ 插入到 $que\_t[j-i]$ 的单调队列里，即可。

那么我们理一下思路：
1. 计算 $f[i][j]$ 时，把 $que\_t[i-j-1]$ 中队首表示的区间不与 $i$ 相交的踢出去。
2. 当前队首是最大值。
3. 计算 $f[i][j]$ 并更新 $que\_t[i-j]$ 。

复杂度 $\Theta(nk)$ ，可以 $\colorbox{#52C41A}{\text{\color{white}{AC}}}$ 。

代码还是放一下吧，细节比较多，注意不要复制。

```cpp
//lifeguards P 防Copy版
for(ll i=1;i<=n*k;i++){
	ll u=min(k+1,i);
	for(ll j=0;j<n;j++){
		ll now_pos=i-j-1;
		while(!increasing_queue[now_pos].empty()&&sequence[increasing_queue[now_pos].front().node].r<sequence[i].l){
			Node tt_next=increasing_queue[now_pos].front();
			rr[now_pos]=max(rr[now_pos],tt_next.val+sequence[tt_next.node].r);
			increasing_queue[now_pos].pop_front();
		}
		f[i][j]=max(f[i][j],rr[now_pos]+sequence[i].r-sequence[i].l);
		if(!increasing_queue[now_pos].empty())f[i][j]=max(f[i][j],increasing_queue[now_pos].front().val+sequence[i].r);
		ll now_val=f[i][j]-sequence[i].r;
		now_pos=i-j;
		while((!increasing_queue[now_pos].empty())&&(increasing_queue[now_pos].back().val<now_val))increasing_queue[now_pos].pop_back();
		increasing_queue[now_pos].push_back((Node){i,now_val});
	}
}//在一定程度上参考了其他人的代码（我不会告诉你是因为我写的太丑了）
for(int i=1;i<=n;i++)ans=max(ans,f[i][k]);
```

完结撒花~

看在我码了这么多字，给个赞吧![](https://cdn.jsdelivr.net/gh/xaoxuu/volantis@1.0/img/qq/%E5%8F%AF%E6%80%9C.gif)。

---

## 作者：nihanchu (赞：19)

  好吧，自己考虑的时候没想过要开多个单调队列来优化dp。。。

  首先，如果一个区间被其他区间包含的话，很明显，它被删除也没影响。所以我们先按左节点排序，去除那些包含的区间，然后对接下来有序的区间进行dp。

dp[i][j]表示前i个区间删掉j个且第i个必取能覆盖的最大面积。

dp[i][j]=max(dp[i][j],dp[p][j-(i-p-1)]+calc(p,i))//calc(p,i)表示将第i个区间加到第p个区间后时新增的覆盖面积,因为i-p-1显然需要小于等于k，所以时间复杂度是O(n*k*k)，需优化。

  之前的区间分为是否与当前区间有重叠部分这样两种。可以发现如果之前的一个dp[x][y]可以更新dp[i][j]，那么x-y=i-j-1;

所以我们可以开k个单调队列，如果队头的元素已经和当前第i个区间不重叠，就更新不重叠的答案，并弹出队头。

操作完成后，用队头及有重叠部分的区间来更新答案。

   将dp[i][j]-a[i].r（为什么是这个值）放入第i-j个单调队列，进行更新。

   具体的程序中写。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
#define maxn 100009
using namespace std;
int n,k,p[maxn],dp[maxn][109];
struct ding{
  int l,r;
}a[maxn],b[maxn];
struct ding2{
  int node,val;
};
deque<ding2>q[maxn];
bool cmp(ding t1,ding t2)
{return t1.l==t2.l?t1.r>t2.r:t1.l<t2.l;}
int main()
{
  freopen("std.in","r",stdin);
  freopen("std.out","w",stdout);
  scanf("%d%d",&n,&k);
  b[0]=(ding){0,0};
  for (int i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r);
  if (k>=n) 
  {
      printf("0\n");
      return 0;
  }
  sort(a+1,a+1+n,cmp);
  int maxx=-1,cnt=0;
  for (int i=1;i<=n;i++)
  {
      if (a[i].r>maxx) b[++cnt]=a[i];
//去掉被包含区间
      else k--;
      maxx=max(maxx,a[i].r);
  }
  if (k<0) k=0; n=cnt;
  for (int i=1;i<=n;i++)
  {
    for (int j=0;j<min(k+1,i);j++)
    {
      int now=i-j-1;
      while ((!q[now].empty())&&(b[q[now].front().node].r<b[i].l))
//如果当前队头的区间和第i个区间不重叠那就弹出
      {
          ding2 to=q[now].front();
          p[now]=max(p[now],to.val+b[to.node].r);
//因为如果有重叠，那么dp[i][j]=dp[x][y]+a[i].r-a[x].r，所以放入队列的元素为dp[x][y]-a[x].r,我们用它来更新不重叠的答案
          q[now].pop_front();
      }
      dp[i][j]=max(dp[i][j],p[now]+b[i].r-b[i].l);
//不重叠区间更新
      if (!q[now].empty())
      dp[i][j]=max(dp[i][j],q[now].front().val+b[i].r);
//重叠的区间更新
      int nowv=dp[i][j]-b[i].r;
      now=i-j;
      while ((!q[now].empty())&&(q[now].back().val<nowv))
      q[now].pop_back();
      q[now].push_back((ding2){i,nowv});
//放入队列
    }
  }
  int ans=0;
  for (int i=1;i<=n;i++)
  for (int j=0;j<min(i,k+1);j++)
  if (j+n-i==k) ans=max(ans,dp[i][j]);
//枚举哪个区间是最后一个被取的
  printf("%d\n",ans);
  return 0;
}
```

---

## 作者：Stinger (赞：8)

# UPD:

修复了代码中一个数组越界的问题，并进行卡常，使得不开O2也能轻松过题

这题在学校听了老板讲，然而并没有听懂个啥（

然后自己重新定状态，推式子，优化（

~~IEE~~

吐槽翻译。[题面](https://www.luogu.com.cn/paste/opegmwc5)

# Solution

首先将每个救生牛的工作时段抽象为线段。则题意变为，给你 $N$ 条线段，要你删除 $K$ 条，使得剩下的线段覆盖最多的点。为了方便描述，令 $l_i=s_i$，$r_i=t_i$

很多题解一上来先去掉了什么“不需要保留的线段”。其实我认为正常做题应该是想好了如何动规再根据动规需求删除这些没有保留价值的线段。

## 朴素做法的状态与方程
根据数据范围，设 $f[i][j]$ 表示前 $i$ 条线段，删除了 $j$ 条，剩下的线段最多可以覆盖多少个点。

方程为：$f[i][j]=max\{f[k][j-i+k+1]+r_i-max(l_i,r_k)\}(i-j-1\le k\le i-1,i\le N,j\le K)$

然而时间复杂度 $O(NK^2)$，~~如果对自己的常数与厌氧程度不够自信~~建议放弃

## 优化DP

上述内容自己稍加思考便能想到。难的是优化。

状态数肯定逃不了，想办法在 $O(K)$ 的转移上做手脚。

根据动规优化的套路，将式子中与 $k$ 无关的项硬提出来。令 $x=j-i+1$。

则原式变为：$f[i][j]=max\{f[k][x+k]+r_i-max(l_i,r_k)\}$

现在很讨厌的是里面的那个 $max$。我们尝试用干掉绝对值的方法干掉这个 $max$——**分类讨论**。

如果 $r_k\le l_i$，相当于要 $f[k][x+k]$ 最大。

如果 $r_k>l_i$，相当于要 $f[k][x+k]-r_k$ 最大。

为了方便维护，我们考虑将每条线段按左端点排序。这样方便确定计算顺序。

现在，如果按传统的`for(i 1......n),for(j 1......k)`计算很不方便。

考虑按照 $x=j-i+1$ 划分阶段。$1$ 是常数，相当于按照 $j-i$ 划分阶段。

我们发现，所有能转移到状态 $f[i][j]$ 的状态 $f[x][y]$ **必定满足** $y-x=j-i+1$。所以，状态 $f[i][j]$ 能转移到的状态 $f[x_1][y_1]$ 满足 $y_1-x_1=j-i-1$。

因此按照 $j-i$ **倒序**计算每个状态。将所有 $j-i=0$ 的状态设为 $0$（相当于所有线段全部删除）。

这样，就相当于在所有范围内的 $k$ 中，对于 $r_k\le l_i$ 的情况（情况1）取一个最大值，对于 $r_k>l_i$ （情况2）取一个最大值。

考虑使用前缀和sum维护情况1，单调队列维护情况2。因为所有线段按照左端点排好了序，所以在 $x=j-i-1$ 确定的情况下，从小到大枚举 $j$（个人认为枚举 $j$ 方便，枚举 $i$ 当然也没有任何问题），$i$ 也是从小到大的，$r_{i-1}$ 也是从小到大的。（为什么是 $i-1$，因为 $i-j-1\le k\le i-1$），$l_{i-1}$ 也是从小到大的。

等等！线段只按照左端点进行了排序，为什么 $r_{i-1}$ 也“天然有序”？仔细想想，如果有两条线段 $i$，$j$，$l_i\le l_j$ 且 $r_i\ge r_j$，线段 $j$ 无论保留还是删除都不会影响结果。换句话说，$j$ 被 $i$ **完全覆盖**了，我们应该在预处理时删掉这种线段。如果预处理完已经删除了超过 $K$ 条线段直接将所有线段覆盖的点数输出即可。

扯了半天，回到式子。单调队列装下每个方案对应的 $k$，每次检查单调队列首部的元素 $k$ 是否 $r_k\le l_i$，如果是，将这个方案的 $f[k][x+k]$ 计算出来，与 $sum$ 比较取大值。单调队列`pop_front()`。然后根据各个线段的情况决定 $k=i-1$ 放到单调队列里还是直接更新前缀和。

时间复杂度：$O(NK)$。因为单调队列每个元素最多只会有一次进队和出队的机会。

细节见代码。

# $Code:$

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>

inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x > y ? x : y;}
const int MaxN = 100001, INF = 0x3fffffff;
struct Line {
    int l, r;
    inline bool operator < (const Line x) const {return l < x.l;}
} a[MaxN];

template<int MAXSIZE> struct deque {
	int head, tail, a[MAXSIZE];
	deque() {head = 0, tail = -1;}
	inline void clear() {head = 0, tail = -1;}
	inline void push_back(int x) {a[++ tail] = x;}
	inline void pop_back() {-- tail;}
	inline void pop_front() {++ head;}
	inline int size() {return tail - head + 1;}
	inline int front() {return a[head];}
	inline int back() {return a[tail];}
};

deque<1005> q;
int f[MaxN][101], L[MaxN], R[MaxN], n;

int main() {
    int N, K, ans(-INF), MaxR(-INF);
    scanf("%d%d", &N, &K);
    memset(f, ~0x3f, sizeof f);
    for (int i(1); i <= N; ++ i) scanf("%d%d", &a[i].l, &a[i].r);
    std::sort(a + 1, a + N + 1);
    for (int i(1); i <= N; ++ i) if (a[i].r > MaxR)
    L[++ n] = a[i].l, R[n] = a[i].r, MaxR = a[i].r;
    K -= N - n;
    if (K <= 0) {
        int ans(0), MaxR(L[1]);
        for (int i(1); i <= n; ++ i) ans += R[i] - max(MaxR, L[i]), MaxR = R[i];
        printf("%d", ans);
        return 0;
    }
    for (int i(0); i <= K; ++ i) f[i][i] = 0;
    for (int k(-1); k >= -n; -- k) {
        int x(k + 1), sum(-INF);
        q.clear();
        for (int j(0); j <= min(K, n + k); ++ j) {
            int i(j - k);
            while (q.size() && R[q.front()] <= L[i])
                sum = max(sum, f[q.front()][x + q.front()]), q.pop_front();
            if (R[i - 1] <= L[i]) sum = max(sum, f[i - 1][x + i - 1]);
            else {
                while (q.size() && f[q.back()][x + q.back()] - R[q.back()] <=
                f[i - 1][x + i - 1] - R[i - 1]) q.pop_back();
                q.push_back(i - 1);
            }
            f[i][j] = sum - L[i] + R[i];
            if (q.size()) f[i][j] = max(f[i][j], f[q.front()][x + q.front()] - R[q.front()] + R[i]);
        }
    }
    for (int i(n - K); i <= n; ++ i) ans = max(ans, f[i][K - n + i]);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：babingbaboom (赞：7)

来自http://blog.csdn.net/iceprincess_1968/article/details/79146028

将所有的区间按左端点从小到大排序

我们处理那些被完全包含的区间，这些区间即使删除也不会使答案变坏

这样先删一波，如果发现这种小区间的个数多于k，就可以直接算答案了

否则我们要dp

设dp[i][j]为考虑到第i个区间，已经删除了j个区间，且第i个区间没有被删除的情况下最大的覆盖长度

显然有状态转移方程dp[i][j]=max(dp[k][j-i-k-1]+第i个区间贡献的覆盖)

这个方程相当于枚举上一个没有被删除的区间k,然后将k+1~i-1全部删除

但我们看到这个转移是O(n)的，所以总复杂度为O(n*n*k)，不能接受

考虑优化dp转移

对于第i个区间，设其左端点为l

我们先看一看方程，会发现对dp[i][j]产生贡献的i'-j'=i-1-j

1. 对于i之前的那些右端点<=l的区间，它们与i没有重叠部分，所以只要在它们当中取max，再加上第i个区间的长度即可

2. 对于那些与i有重叠部分的区间，在当前区间右移的时候，这些dp的贡献会变，但相对大小不会变，所以可以维护一个单调队列，dp[i][j]对应的单调队列的编号为i-1-j，每次先把队头的那些已经跑到左边的区间弹出去（算成1的贡献），然后取队头就是当前的有重叠的状态中的最大答案

然后当前dp值算出来以后要插进对应的单调队列中（编号为i-j的单调队列），如果队尾状态加上与当前状态的右端点差还没有当前状态的dp值大的话，就把它从队尾弹出

这样总复杂度O(n*k)

---

## 作者：木xx木大 (赞：6)

[P4182 [USACO18JAN]Lifeguards P](https://www.luogu.com.cn/problem/P4182) 

转化题意为：给你 $n$ 条线段，从其中去掉 $K$ 条，使剩下的线段覆盖的并集最大。

首先把所有线段按左端点升序，左端点相同按右端点升序排序。发现如果一个线段完全被另一个线段包含，那把它去掉也没有影响。于是我们先去掉这种线段，然后进行 dp 。设 $dp_{i,j}$ 表示前 $i$ 个区间删去 $j$ 个，且钦定第 $i$ 个取的最大覆盖。那么 $dp_{i,j}=\max\limits_{k<i}(dp_{k,j-(i-k-1)}+r_i-\max(l_i,r_k))$ 。简单解释一下，就是钦定上一个选的是 $k$ ，$(k,i)$ 间的全都不选。因为 $i-k-1\le K$ ，所以复杂度为 $O(nK^2)$。

对于 $k$ 比较小，即 $r_k<l_i$ 时的情况，$dp_{i,j}=\max(dp_{k,j-(i-k-1)}+r_i-l_i)$。如果我们能对于每一个 $i-j- 1$ 预处理出 $dp_{k,k-(i-j-1)}$ 的最大值 $p$ ，就可以 $O(1)$ 转移了。

对于 $k$ 比较大，即 $r_k>l_i$ 时的情况，$dp_{i,j}=\max(dp_{k,j-(i-k-1)}+r_i-r_k)$。我们用单调队列维护 $dp_{k,j-(i-k-1)}-r_k$的最大值。当单调队列中的元素不满足 $r_k>l_i$ 时就弹出，弹出的时候顺便处理出 $p$。

总结一下，我们需要处理出 $r_k<l_i$ 时 $dp_{k,k-(i-j-1)}$ 的最大值，再开 $n$ 个单调队列，第 $i-j$ 个单调队列维护 $dp_{i,j}-r_i$ 的最大值。这样复杂度就降为了 $O(nK)$。


------------

最后说一句，deque 真是代码丑常数大啊（但功能确实强大）！导致我的代码必须要吸氧才能过。

本来还想试着改手写队列减小常数，结果菜鸡如我改着改着就改挂了。。。所以代码就凑合看看吧。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FGF
{
	int n,m;
	const int N=1e5+5;
	struct Node{
		int l,r;
	}a[N],b[N];
	int dp[N][110],p[N];
	deque<int> q[N];
	bool cmp(Node x,Node y)
	{
		return x.l^y.l? x.l<y.l:x.r<y.r;
	}
	void work()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		 	scanf("%d%d",&a[i].l,&a[i].r);
		if(m>=n)
		{
			puts("0");
			return;
		}
		sort(a+1,a+n+1,cmp);
		int mx=-1,cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].r>mx)b[++cnt]=a[i];
				else m--;
			mx=max(mx,a[i].r);
		}
		m=max(m,0);
		b[++cnt].l=1e9,b[cnt].r=1e9;
		n=cnt;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=min(i-1,m);j++)
			{
				int now=i-j-1;
				while(q[now].size()&&b[q[now].front()].r<b[i].l)
				{
					p[now]=max(p[now],dp[q[now].front()][q[now].front()-now]);
					q[now].pop_front();
				}
				dp[i][j]=max(dp[i][j],p[now]+b[i].r-b[i].l);
				if(q[now].size())dp[i][j]=max(dp[i][j],dp[q[now].front()][q[now].front()-now]-b[q[now].front()].r+b[i].r);
				now=i-j;
				while(q[now].size()&&dp[q[now].back()][q[now].back()-now]-b[q[now].back()].r<=dp[i][j]-b[i].r)
					q[now].pop_back();
				q[now].push_back(i);
			}
		}
		printf("%d",dp[n][m]);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：4)

[P4182 [USACO18JAN] Lifeguards P](https://www.luogu.com.cn/problem/P4182)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17789660.html)

提供一个~~比较优秀~~大常数的时间 $\mathcal O(nm)$，空间线性的做法。由于变量名冲突，本文中 $m$ 均指题目中的 $k$。

推推性质，发现若区间包含了另一个区间，则一定删掉被包含的区间，正确性显然。这样我们得到了一些左右端点都递增的线段。

将端点从小到大排序，很自然的设 $f_{i,j}$ 表示前 $i$ 个线段**扔了** $j$ 个，并且强制选择 $i$ 保留，容易列出转移方程：

$$
f_{i,j}=\max_{k=0}^{i-1}(f_{k,max(0,j-(i-k-1))}+r_i-\max(l_i,r_k))
$$

可以 $\mathcal O(n)$ 枚举 $k$，复杂度 $\mathcal O(n^2m)$。

观察上式，发现可以分成两个部分。

$$
f_{i,j}=

\begin{cases}

f_{k,0}+r_i-\max(l_i,r_k)\quad \quad \quad \;\;k\leq i-j-1\\

f_{k,j-i+k-1}+r_i-\max(l_i,r_k)\quad k>i-j-1

\end{cases}
$$

把 $f$ 抽象成一个二维的表，发现 $f_{i,j}$ 的决策集合是第零行的一段前缀与一条在它左边一个单位的斜线。

![image.png](https://s2.loli.net/2023/10/26/mfKraRguAiHUCB9.png)

上图中打红叉的格子是当前的 $f_{i,j}$，黄色的格子是决策集合。

所以我们可以枚举橙色格子的位置，每次处理一条向右下的斜线的所有格子 DP 值这样决策集合是单增不减的，对于第零行首先预处理出 DP 值（第一行表示一个都不删，随便 DP），然后额外维护。

但是现在的问题是如何处理式子右边的两个 $\max$，记 $pre_i$ 表示编号最小的和 $i$ 有重叠部分的线段，这样我们可以把 $\max$ 再拆开。


$$
f_{i,j}=

\begin{cases}

f_{k,0}+r_i-l_i\quad \quad \quad \;\;\;k< \min(pre_i,i-j-1)\\

f_{k,0}-r_k+r_i\quad \quad \quad \;\;pre_i\leq k\leq i-j-1\\

f_{k,j-i+k-1}+r_i-l_i\quad\; i-j-1<k< pre_i\\

f_{k,j-i+k-1}-r_k+r_i\;\;\; \max(pre_i,i-j-1)\leq k<i\\

\end{cases}
$$

注意边界特判。继续观察式子，发现我们需要维护：

1. 第 $0$ 行的前缀的 $f_{0,i}$ 的最大值。

2. 斜线上的前缀 $f_{i,j}$ 的最大值。

3. 第 $0$ 行的区间 $f_i-r_i$ 的最大值。

4. 斜线上区间 $f_{i,j}-r_i$ 的最大值。

前两个是好维护的，第四个由于 $pre_i$ 单增，决策集合右端点和左端点都只增不减，所以可以单调队列，但是第三个我们似乎没有好的处理方式，好像只能 ST 表或者线段树之类的，但是这样除非用一些科技，时间或空间会多一只 $\log$，我们想要更优秀和更简单的解决方式。

继续观察第三个式子。一条斜线上只有 $m$ 个点需要 DP，但是注意查询区间的长度是没有限制的，可能许多点的 $pre$ 都远远小于它本身，只简单的在第 $0$ 行维护一个单调队列复杂度是假的，最差仍然是 $\mathcal O(n^2m)$。

但是发现所以**左端点最多只有 $m$ 个**，所以我们可以记录哪些点是其他点的 $pre$，然后把打了标记的点之间的 $f_{0,i}-r_i$ 的权值都归到左边的标记点上。这样一条斜线的左端点数就是 $\mathcal O(m)$ 的级别了。我们只需要在第 $0$ 行维护另外一个单调队列，每次对于一条斜线预处理出它要查询的位置到当前橙色格子的 $\max f_{0,i}-r_i$（点数也是 $\mathcal O(m)$ 级别的），这样复杂度就是对的。

代码细节很多，很不好写。

```cpp
	int n,m,len,ans,cnt,now,from,real[100001],pre[100001],t[101],pos[100001],Val[100001],V[100001],vis[100001],h[100001],f[2][101];
	pii a[100001],b[100001];
	bool cmp(pii x,pii y){return x.se<y.se;}
	deque<int> Q,q;
	inline void mian()
	{
		read(n,m),from=1;
		for(int i=1;i<=n;++i)read(a[i]),--a[i].se;
		sort(a+1,a+1+n,cmp),b[0]=mp(-inf,-inf);
		for(int i=1;i<=n;++i)
		{
			while(b[len].fi>=a[i].fi)--len;
			b[++len]=a[i];
		}
		m=max(0,m-(n-len)),n=len,memset(Val,128,sizeof(Val)),memset(f,128,sizeof(f)),h[0]=len=0;
		for(int i=1,j=0;i<=n;vis[pre[i++]=j+1]=1)while(b[j+1].se<b[i].fi)++j;
		for(int i=1;i<=n;++i)h[i]=h[i-1]+b[i].se-max(b[i-1].se,b[i].fi-1);
		for(int i=n,maxn=h[n]-b[n].se;i>=1;--i,maxn=max(maxn,h[i]-b[i].se))if(vis[i])V[pos[i]=++len]=maxn,real[len]=i,maxn=-inf;
		for(int i=1;i<=n;++i)if(pos[i])pos[i]=len-pos[i]+1;
		reverse(V+1,V+1+len),reverse(real+1,real+1+len);
		if(n>=m)ans=h[n-m];
		for(int st=1,last=0;st<=n;++st)
		{
			while(!q.empty())q.pop_back();
			now^=1,from^=1;int r=min(last,pos[pre[st+m]]);
			while(!Q.empty()&&Q.front()<real[r])Q.pop_front();
			if(Q.size())
			Val[r]=h[Q.front()]-b[Q.front()].se;
			else
			Val[r]=-inf;
			for(int i=r-1;i>=pos[pre[st]];--i)
			Val[i]=max(Val[i+1],V[i]);
			for(int i=st+1,j=1,maxn=0,i1=i-2,j1=0;i<=n&&j<=m;++i,++j)
			{
				f[now][j]=h[min(st-1,max(0,pre[i]-1))]+b[i].se-b[i].fi+1;
				f[now][j]=max(f[now][j],b[i].se+Val[pos[pre[i]]]);
				while(i1+1<pre[i]&&i1+1<i&&j1+1<=j)maxn=max(maxn,f[from][++j1]),++i1;
				f[now][j]=max(f[now][j],maxn+b[i].se-b[i].fi+1);
				while(!q.empty()&&f[from][q.back()]-b[q.back()+st-1].se<=f[from][j]-b[i-1].se)q.pop_back();
				q.eb(j);
				while(!q.empty()&&q.front()+st-1<pre[i])q.pop_front();
				if(!q.empty())f[now][j]=max(f[now][j],f[from][q.front()]+b[i].se-b[q.front()+st-1].se);
				if(j+n-i>=m)ans=max(ans,f[now][j]);
			}
			if(vis[st])last=pos[st];
			for(int i=r;i>=pos[pre[st]];--i)Val[i]=-inf;
			while(!Q.empty()&&h[Q.back()]-b[Q.back()].se<=h[st]-b[st].se)Q.pop_back();
			Q.eb(st);
		}
		write(ans,'\n');
	}
```

---

## 作者：Tsawke (赞：2)

# [LG-P4182 [USACO18JAN]Lifeguards P](https://www.luogu.com.cn/problem/P4182) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P4182-Solution)

解法本身题解区已经写的较为清楚了，这里主要对大多数题解都涉及到但均未证明的一个贪心策略进行感性证明，故前面的推导过程写的较为简略。

### 题面

给定 $ n $ 个左闭右开的区间，在范围 $ [0, 10^{9}] $ 内，最大化删去其中 $ k $ 个区间后剩下区间并起来的长度，求最大值。

$ 1 \le n \le 10^5, 1 \le k \le \min(100, n) $。

### Solution

首先不难想到对于区间 $ [l_1, r_1), [l_2, r_2) $ 且 $ l_1 \le l_2 \land r_2 \le r_1 $ 那么删去 $ [l_2, r_2] $ 答案一定不变，于是可以直接全部删去，并将 $ k \leftarrow k - 1 $。

然后 DP 显然，也很好想到一个状态 $ dp(i, k) $ 表示考虑前 $ i $ 个区间，删去其中的 $ k $ 个的最优值，然后发现这玩意没有固定具体怎么删没法转移，然后就想到在原来的状态基础上钦定必须选择第 $ i $ 个区间，然后需要把区间优先按左端点，再按右端点排序，这样我们就会发现最开始去掉那些区间的作用了，去掉之后现在我们剩下的区间排序后一定满足对于 $ l $ 的升序一定也满足 $ r $ 升序，不满足的已经被我们删掉了。于是此时转移比较显然：$ dp(i, k) = \max\{ dp(j, k - (i - j - 1)) + r_i - \max(l_i, r_j) \}, j \in [i - k - 1, i - 1] $。这玩意复杂度显然是 $ O(nk^2) $ 的，显然不正确。

考虑优化，状态没什么可优化的，于是考虑优化转移，我们尝试提出来与转移时的 $ j $ 无关的项，令 $ \xi = i - k - 1 $，于是有 $ dp(i, k) = \max\{ dp(j, j - \xi) + r_i - \max(l_i, r_j) \}, j \in [i - k - 1, i - 1] $。也就是说我们要在 $ \xi = i - k - 1 $ 的前提下，换句话说就是以前的 $ dp $ 中前后索引的差为 $ \xi $ 的值中找到后面式子的最大值进行转移，这个东西简单分类讨论一下就是如果 $ l_i \ge r_j $（或者理解为区间无交）那么就是要最大化 $ dp(j, j - \xi) $。反之需要最大化 $ dp(j, j - \xi) - r_j $。

所以我们直接对前者维护一个最大值（因为我们的区间之间使有序的，所以如果对于之前的区间已经无交了，对于现在的一定也无交），后者则维护一个~~单调队列~~~~单调栈~~单调双端队列，每次处理时先把对应单调双端队列队头中所有不合法的，也就是不交的弹出然后更新不交区间里面的最大值。然后用交的和不交的里的最大值更新当前 $ dp $，每次处理完当前的 $ dp $ 就把当前的丢到对应的单调双端队列里，这时我们会按照双端队列直接把队尾不优于当前的直接丢掉而不是保留下来等待不交时更新不交的最大值，这个的原因我想了很久，感性地证明了一下，如下：

如果你仔细想一下就会发现这个算法有一点问题，首先我们在最初的找单调双端队列里面的队头不合法的值的时候，我们时按照 $ val $ 的大小，也就是 $ dp(j, j - \xi) - r_j $ 的大小维护的单调双端队列，但是我们更新不交最大值的时候需要的是与其不交区间里的最大值（废话），难道就不会存在一种情况，即队头的区间 $ val $ 更大，但是区间靠右，然而队头之后某个区间 $ val $ 较小却区间靠左，也就是存在一种情况单调优先队列的后面已经存在了不交的区间但是却被队头的相交区间阻挡了，这样的话我们难道不会少更新一些值吗？还有就是在把当前的 $ dp $ 压入单调双端队列的时候，我们会把队尾不优于当前值的直接踢掉，这个时候却没有考虑到在后面更新时这些区间可能会从相交变成不交，从而可能性地去更新不交的最大值，但是现在这被我们丢掉了，难道不会使答案更劣吗？

这几个问题困扰了我很久，完全没有头绪，直到发现了一个性质我才大概能感性理解这个贪心的正确性。

显然当我们转移的时候，如果转移的这个 $ j $ 是与 $ i $ 交的，那么最优的 $ j $ 一定是 $ l_j $ 最小的 $ j $，当然经过我们的处理之后同时也是 $ r_j $ 最小的。这个不难理解，因为我们处理过包含的区间，所以 $ i, j $ 相交那么最终这两段组成的区间一定是 $ [l_j, r_i) $，那么 $ l_j $ 尽量小一定更优，所以 $ j + 1, j + 2, \cdots, i - 1 $ 的区间都是没必要选的，选了也不会有任何贡献。

此时我们再回到刚才的考虑，我们的单调优先队列维护的是最大值，而最大值一定是 $ l $ 和 $ r $ 最小的，那么我们实际上也可以感性地认为更左的区间在单调双端队列里也更靠前，如果这个成立那么我们刚才的所有问题也就很显然是不需要考虑得了，这样的话我们弹出的队头一定是最先变得不交的，被丢掉的区间也一定是更劣的。

于是这个贪心（~~应该~~）是正确的。

当然上面这一大段证明都完全是我口糊的，不保证正确性，也不够理性和严谨，期待一个更严谨的证明。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template< typename T = int >
inline T read(void);

struct Line{
    int l, r;
    friend const bool operator < (const Line &a, const Line &b){if(a.l == b.l)return a.r < b.r; return a.l < b.l;}
}line[110000];
list < Line > _line;
int N, K;
int cnt(0);
struct Status{int idx; int val;};
deque < Status > bst[110000];
int mx[110000];
int dp[110000][110];

int main(){
    N = read(), K = read();
    for(int i = 1; i <= N; ++i){
        int l = read(), r = read();
        _line.emplace_back(Line{l, r});
    }_line.sort();
    for(auto it = next(_line.begin()); it != _line.end();)
        if(it->r <= prev(it)->r)it = _line.erase(it), --K; else ++it;
    for(auto ln : _line)line[++cnt] = ln;
    N = cnt; K = max(0, K);
    for(int i = 1; i <= N; ++i){
        for(int k = 0; k <= min(i - 1, K); ++k){
            int xi = i - k - 1;
            while(!bst[xi].empty() && line[bst[xi].front().idx].r < line[i].l){
                auto tp = bst[xi].front(); bst[xi].pop_front();
                mx[xi] = max(mx[xi], tp.val + line[tp.idx].r);
            }
            dp[i][k] = max({
                dp[i][k],
                mx[xi] + line[i].r - line[i].l,
                bst[xi].empty() ? -1 : bst[xi].front().val + line[i].r
            });
            int val = dp[i][k] - line[i].r;
            int pos = i - k;
            while(!bst[pos].empty() && bst[pos].back().val < val)bst[pos].pop_back();
            bst[pos].push_back(Status{i, val});
        }
    }int ans(-1);
    for(int i = N - K; i <= N; ++i)ans = max(ans, dp[i][K - (N - i)]);
    printf("%d\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_03 初稿

---

## 作者：大菜鸡fks (赞：2)

单调队列优化dp

dp[i][j]=max(dp[x][y]+w(x,i))

w(x,i)表示i接在x后的贡献

能转移的条件是x-y=i-j-1

考虑w(x,i) 

若相交则，w(i,x)=len(i),维护所有不相交的就可以.

若不相交,w(i,x)=b[i].r-b[x].r。 因为i递增，所以满足单调队列维护的条件，每次判断队尾是否与当前线段相交，不相交就弹出

注意要去重

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#define pa pair<int,int>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5,KK=105;
struct line{
	int l,r;
}b[N],a[N];
deque<pa> q[N];
int mxr,ans,mx[N],n,K,tot,dp[N][KK];
inline bool cmp(line A,line B){
	return A.l==B.l?A.r>B.r:A.l<B.l;
}
inline void init(){
	n=read(); K=read();
	for (int i=1;i<=n;i++) b[i]=(line){read(),read()};
	sort(b+1,b+1+n,cmp); a[++tot]=b[1];
	for (int i=2;i<=n;i++) 
		if (b[i].r>mxr) a[++tot]=b[i],mxr=a[i].r;
			else K--;
}
inline void solve(){
	K=max(K,0); n=tot;
	for (int i=1;i<=n;i++){
		for (int j=0;j<=K;j++){
			if (j>=i) break; 
			int delta=i-j-1;
			while (!q[delta].empty()&&a[q[delta].front().second].r<=a[i].l){
				int x=q[delta].front().second; q[delta].pop_front();
				mx[delta]=max(mx[delta],dp[x][x-delta]);
			}
			dp[i][j]=mx[delta]+a[i].r-a[i].l;
			if (!q[delta].empty()) dp[i][j]=max(dp[i][j],q[delta].front().first+a[i].r);
			int w=dp[i][j]-a[i].r; delta++;
			while (!q[delta].empty()&&q[delta].front().first<=w) q[delta].pop_back();
			q[delta].push_back(make_pair(w,i));
		}
	}
	ans=0;
	for (int i=1;i<=n;i++) if (K-(n-i)>=0) ans=max(ans,dp[i][K-(n-i)]);
	writeln(ans);
}
int main(){
	init(); solve();
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

比较典的一个题。

# Part 2：正文

观察数据范围大概能猜测到这个题的复杂度大概是 $O(nk)$，因此考虑一些 dp，设 $f(i,j)$ 表示考虑到前 $i$ 个区间，删除了 $j$ 个区间且强制钦定第 $i$ 个区间不被删的答案。现在的问题主要在于如何转移。

观察题目的性质，不难发现若存在区间 $A:[l_A,r_A],B[l_B,r_B]$ 满足 $l_A\leq l_B\leq r_B\leq r_A$，删去 $B$ 区间不会使答案变劣。因此我们不妨首先删去所有的满足 $B$ 的性质的区间。注意到做完这一过程以后，若我们把所有区间按照左端点升序排序，则右端点不降。按顺序考虑每一个区间，那么此时对于一个区间，若其被选，根据上述的性质，其贡献一定只和上一个被选择的区间相关。因此我们有了一个 $O(nk^2)$ 的做法。即枚举 $p\in [i-k-1,i)$，转移为，$f(i,j)\leftarrow f(p,j-(i-p-1))+r_i-\max(l_i,r_p)$。

然后考虑优化。把最值拆掉，分情况讨论。若区间不交，那么相当于对满足条件的 $p$ 的 $f(p,j-(i-p-1))$ 取最值，若相交，则是一个单调队列的形式，将 $f(p,j+p+1-i)-r_p$ 用单调队列维护即可。一种写法是直接开 $n$ 条，另一种写法是将转移分层，外层枚举 $j-i$ 的值即可用一条单调队列维护。


# Part 3：代码

```cpp
const int N=1e5+7,K=1e2+7;
int n,k;
int f[N][K];
pair<int,int>seg[N];

void solve(){
	read(n,k);
	for(int i=1;i<=n;i++)read(seg[i].first,seg[i].second);
	sort(seg+1,seg+n+1);
	int R=0,pos=0;
	for(int i=1;i<=n;i++)
		if(seg[i].second>R)
			seg[++pos]=seg[i],R=seg[i].second;
	k-=n-pos;
	n=pos;
	// for(int i=1;i<=n;i++)
	// 	printf("%d %d\n",seg[i].first,seg[i].second);
	if(k<=0){
		R=seg[1].first;int ans=0;
		for(int i=1;i<=n;i++)
			ans+=seg[i].second-max(seg[i].first,R),R=seg[i].second;
		printf("%d\n",ans);
	}
	memset(f,0xcf,sizeof(f));
	for(int i=0;i<=k;i++)f[i][i]=0;
	for(int j=1;j<=n;j++){
		deque<int>q;
		int mxv=0xcfcfcfcf;
		for(int cur=0,i=j;cur<=min(k,n-j);cur++,i++){
			while(!q.empty()&&seg[q.front()].second<=seg[i].first)
				mxv=max(mxv,f[q.front()][q.front()-j+1]),q.pop_front();
			if(seg[i-1].second<=seg[i].first)
				mxv=max(mxv,f[i-1][i-j]);
			else{
				while(!q.empty()&&f[q.back()][q.back()-j+1]-seg[q.back()].second<=f[i-1][i-j]-seg[i-1].second)
					q.pop_back();
				q.push_back(i-1);
			}
			f[i][cur]=mxv-seg[i].first+seg[i].second;
			if(!q.empty())
				f[i][cur]=max(f[i][cur],f[q.front()][q.front()-j+1]-seg[q.front()].second+seg[i].second);
		}
	}
	int ans=0;
	for(int i=n-k;i<=n;i++)
		ans=max(ans,f[i][k-n+i]);
	printf("%d\n",ans);
	return;
}
```



---

## 作者：RainFestival (赞：1)

**警告：** 这个方法不一定可以通过此题，可能会**超过时空限制**。笔者为了能卡进时空限制，用了一些手段，可能会导致**答案错误**。如果您想要对拍的话，请**不要**使用这份代码。

题意：有 $n$ 个线段，你需要删掉 $k$ 个线段，使得剩下的线段的并集最大，问这个最大值是多少。

首先我们先把删掉 $k$ 个转化成保留 $n-k$ 个。

我们发现，设 $f(s)$ 为保留 $s$ 条线段的并集最大值，那么 $f(s)$ 是凸的。

然后我们需要求 $f(n-k)$，所以我们可以考虑 wqs 二分。

每次二分惩罚 $p$，问题转化为选择一条线段需要 $p$ 的代价的最大方案。

我们考虑使用动态规划来解决这个问题，记 $dp_i$ 为考虑了前 $i$ 条线段，一定要选择第 $i$ 条线段的答案。

我们先把所有线段按照左端点排序。

对于一条线段 $i$ 的左右端点是 $l,r$，考虑上一条线段 $j$ 的右端点 $r'$。

+ 如果 $r'<l$，那么这一条线段的对答案的贡献就是 $r-l+1$，即 $dp_i\gets \max(dp_i,dp_j+(r-l+1)-p)$。

+ 如果 $l\le r'\le r$，那么这一条线段的贡献为 $r-r'$，即 $dp_i\gets \max(dp_i,dp_j+(r-r')-p)$。

+ 如果 $r'>r$，那么上一条线段一定包含了这一条，这一条线段一定没有用。

对于第一种情况，因为左端点依次递增，所以，我们把处理过的线段右端点处的答案存进数组里面就可以查询啦。

具体地，我们记 $val_i$ 为右端点 $\le i$ 的答案。每次加入线段的时候，用这一条线段更新 $val_r$。这个时候，$val_i$ 指右端点 $=i$ 的答案。当左端点更新到 $l$ 时，$i\le l-1$ 的 $val_i$ 的答案已经更新完毕，于是把 $i\le l-1$ 的 $val_i$ 更新一下，变成成右端点 $\le i$ 的答案就可以啦，也就是 $val_i\gets \max(val_{i-1},val_i)$。

从而第一种情况的答案 $s_1$ 是 $val_{l-1}-p$。

对于第二种情况，我们需要利用线段树就可以解决啦。

具体地，我们记 $a_k$ 为上一条线段的右端点为 $k$ 的最大答案。

考虑一条线段 $i$，记它的左右端点为 $l,r$，$dp_i=\max\limits_{k=l}^{r} a_k-k+r$。

我们发现 $+r$ 这一项对于每个 $i$ 是固定的，非常容易处理。

我们发现 $-k$ 这一项和 $k$ 有关，不好处理。于是我们记 $b_k=a_k-k$，于是 $\max\limits_{k=l}^{r} a_k-k+r=\max\limits_{k=l}^{r} b_k+r$，然后把 $b_k$ 存进线段树中查询就可以啦。

从而第二种情况的答案 $s_2$ 是 $(\max\limits_{k=l}^{r} b_k)+r-p$。

所以 $dp_i=\max(s_1,s_2)$。

在记录每一个 $dp$ 值的时候，我们顺便记录达到这个 $dp$ 值的方案需要选择 $c_i$ 条线段，这个很容易在取 $\max$ 的时候记录下来。

如果达到最大的 $dp$ 值需要的线段个数 $<k$，我们就加大惩罚 $p$，否则减小。

由于惩罚是个实数，我们需要一个合适的 $eps$，如果太大，就会得到错误的答案，因为我们做了错误的决策，如果太小，二分次数太多，就会超过时间限制。

所以我们手动调整 $eps$，多交几次就过啦。

卡常小技巧：先对所有的区间端点进行离散化，然后就不用动态开点线段树啦。

时间复杂度 $\mathcal{O(n\log n\log V)}$，其中 $\mathcal{V}$ 是值域；空间复杂度 $\mathcal{O(n)}$。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
#include<unordered_map>
#define maxn 205000
#define eps 0.01
struct sgt
{
	struct node
	{
		std::pair<double,int> s;
	};
	node a[530005];
	void pushup(int k)
	{
		a[k].s=std::max(a[k*2].s,a[k*2+1].s);
	}
	void update(int k,int x,std::pair<double,int> w,int l,int r)
	{
		if (l==r) return a[k].s=std::max(a[k].s,w),void();
		int mid=(l+r)/2;
		if (x<=mid) update(k*2,x,w,l,mid);
		if (mid<x) update(k*2+1,x,w,mid+1,r);
		pushup(k); 
	}
	std::pair<double,int> ask(int k,int x,int y,int l,int r)
	{
		if (a[k].s.second==-1000000000) return std::make_pair(-100000000000000.0,-100000000);
		if (x<=l&&r<=y) return a[k].s;
		int mid=(l+r)/2;
		std::pair<double,int> s=std::make_pair(-100000000000000.0,-100000000);
		if (x<=mid) s=std::max(s,ask(k*2,x,y,l,mid));
		if (mid<y) s=std::max(s,ask(k*2+1,x,y,mid+1,r));
		return s;
	}
	void pre()
	{
		clear();
	}
	void clear()
	{
		for (int i=1;i<=530000;i++) a[i].s=std::make_pair(-1000000000000000.0,-1000000000);
	}
};
struct node
{
	int l,r;
};
sgt t;
int n,k,maxl=0,g[200005],cnt,ncnt=0;
node f[100005];
std::pair<double,int> val[205005],dp[100005];
std::unordered_map<int,int> mp;
std::pair<double,int> calc(double k)
{
	t.clear();
	int now=0;
	for (int i=0;i<=205000;i++) val[i]=std::make_pair(-1000000000000000.0,-1000000000);
	val[0]=std::make_pair(0.0,0);
	t.update(1,0,std::make_pair(0.0,0),0,maxn);
	for (int i=1;i<=n;i++)
	{
		while (now<f[i].l-1) ++now,val[now]=std::max(val[now-1],val[now]);
		std::pair<double,int> s1=val[f[i].l-1];
		std::pair<double,int> s2=t.ask(1,f[i].l,f[i].r,0,maxn);
		s1.first=s1.first+(g[f[i].r]-g[f[i].l]+1)-k,s2.first=s2.first+g[f[i].r]-k;
		++s1.second,++s2.second;
		dp[i]=std::max(s1,s2);
		val[f[i].r]=std::max(val[f[i].r],dp[i]);
		t.update(1,f[i].r,std::make_pair(dp[i].first-g[f[i].r],dp[i].second),0,maxn);
	}
	std::pair<double,int> ans=std::make_pair(-1000000000000000.0,-1000000000);
	for (int i=1;i<=n;i++) if (dp[i]>ans) ans=dp[i];
	return ans;
}
double bs(double l,double r)
{
	if (r-l<eps) return l;
	double mid=l+(r-l)/2.0;
	int s=calc(mid).second;
	if (s==k) return mid;
	if (k<s) return bs(mid,r);
	return bs(l,mid);
}
int cmp(node x,node y){return x.l<y.l;}
int main()
{
	t.pre();
	scanf("%d%d",&n,&k);
	k=n-k;
	int ss[200005];
	for (int i=1;i<=n;i++) scanf("%d%d",&f[i].l,&f[i].r),--f[i].r,ss[++ncnt]=f[i].l,ss[++ncnt]=f[i].r;
	for (int i=1;i<=n;i++) maxl=std::max(maxl,f[i].r-f[i].l+1);
	std::sort(ss+1,ss+ncnt+1);
	for (int i=1;i<=ncnt;i++)
	{
		if (ss[i]==ss[i-1]&&i!=1) continue;
		mp[ss[i]]=++cnt;
		g[cnt]=ss[i];
	}
	for (int i=1;i<=n;i++) f[i].l=mp[f[i].l],f[i].r=mp[f[i].r];
	std::sort(f+1,f+n+1,cmp);
	double s=bs(0,maxl);
	std::pair<double,int> sta=calc(s);
	printf("%lld\n",(long long)(sta.first+s*k+0.5));
	return 0;
}
```
[这里](https://www.luogu.com.cn/record/70463958) 是评测记录。

感谢您的阅读。


---

## 作者：一只绝帆 (赞：0)

> 给定若干区间，你可以删除 $k$ 个区间，使得剩下的区间覆盖总长尽量大。
> 
> $n\le 10^5,k\le \min(n,100)$。

纪念一下闷头做了一下午 + 一晚上的题。

首先发现一件事情，被其他区间包含的区间一定不优，可以提前删掉，这样我们的区间就变成了端点单调区间。

于是我们可以把区间排序。

考虑 $dp$，设 $f_{k,j,i}$ 为考虑了前 $k$ 个区间，删掉了 $j$ 个，最后一个选的是 $i$。

方程是朴素的：

$$f_{k,j+1,i}\gets f_{k-1,j,i}\\f_{k,j,k}\gets f_{k-1,j,i}+r_k-\max(l_k,r_i)$$

复杂度 $O(n^2k)$，非常的菜。

接下来你发现第一个转移实际上就是把 $f_{k-1,j}$ 复制到 $f_{k,j+1}$，那我们不妨规定每次 $k-1\to k$，我们都 $j\to j+1$。

也就是每次 $k$ 跑一步的时候，我们就掩耳盗铃，把 $f_j$ 当作本来的 $f_{j+1}$。

也就相当于原来的转移终点的 $j$ 都变成了 $j-1$。

把转移柿子重新写一下：

$$f_{j-1,k}\gets f_{j,i}+r_k-\max(l_k,r_i)$$

（由于你掩耳盗铃，就直接在原来的数组上 $dp$，不需要第一维了。）

不难发现原来的 $j$ 最多到 $100$，所以一个 $j$ 连续加 $100$ 轮 $1$ 就没有意义了，在我们的新意义下就是停在原地 $100$ 轮就没有意义了，**所以我们在** $\bmod \ 100$ **意义下处理** $j$ **这一维**。

而原来没有意义的部分要不要清空呢？

不需要，本题取的是 $\max$，之前的部分选的区间很少，一定不优。

然后我们就把空间复杂度压缩到了 $O(nk)$，复杂动态规划优化的第一步往往是先把空间压到合适的地方再时间优化。

接下来我们观察这个柿子（写成填表的形式）：

$$f_{j,k}\gets \max(f_{j+1,i}+r_k-\max(l_k,r_i))$$

不难发现可以分类讨论内层的 $\max$：

$$f_{j,k}\gets \max\left(\max_{i}^{r_i\le l_i}\{f_{j+1,i}+r_k-l_k\},\max_{i}^{r_i>l_k}\{f_{j+1,i}+r_k-r_i\}\right)$$

那就可以把无关项提出来了：

$$f_{j,k}\gets \max\left(\max_{i}^{r_i\le l_i}\{f_{j+1,i}\}+r_k-l_k,\max_{i}^{r_i>l_k}\{f_{j+1,i}-r_i\}+r_k\right)$$

于是我们要做的相当于两个区间 $\max$，可以用主流数据结构做到 $O(\log n)$ 插入和查询，但这不够。

我们进一步观察，发现第一个是前缀 $\max$，可以自然维护。

第二个是区间 $\max$，但我们插入的顺序和询问的顺序具有单调性，可以开 $100$ 个单调队列自然维护。

还有这种写法比较卡空间，记得开 `int`，并且不要开多余数组，可以以 $\text{121.4MB}$ 的擦边空间通过。

```cpp
#include<bits/stdc++.h>
#define fd(x) (lower_bound(V+1,V+vnt+1,x)-V)
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
using namespace std;typedef int ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=1e5+2,K=102;const ll inf=1e9+5;
int V[N<<1],vnt,n,m,k,ls[N];
ll f[K][N],pmax[K][N],tmp[K];
struct S {
	int l,r;
	bool operator<(S b) {
		return l==b.l?r>b.r:l<b.l;
	}
} s[N],a[N];
struct DL {
	ll q[N];int hd,tl;
	DL() {hd=1;tl=0;}
	void del(int x) {
		while(hd<=tl&&q[hd]<x) hd++;
	}
	void push(ll f[],int x) {
		while(hd<=tl&&f[q[tl]]-V[a[q[tl]].r]<f[x]-V[a[x].r]) tl--;
		q[++tl]=x;
	}
	ll mx(ll f[]) {return hd<=tl?f[q[hd]]-V[a[q[hd]].r]:-inf;}
} q[K];
int main() {
	n=read();m=read();
	F(i,1,n) s[i]={V[++vnt]=read(),V[++vnt]=read()};
	sort(V+1,V+vnt+1);vnt=unique(V+1,V+vnt+1)-V-1;
	F(i,1,n) s[i].l=fd(s[i].l),s[i].r=fd(s[i].r);
	sort(s+1,s+n+1);
	int mxr=0;F(i,1,n) if(mxr<s[i].r) mxr=s[i].r,a[++k]=s[i];
	if(n-k>=m) {
		ll ans=0;F(i,1,k) ans+=V[a[i].r]-V[max(a[i].l,a[i-1].r)];
		cout<<ans<<endl;return 0;
	} 
	F(i,1,k) {
		int L=0,R=i,mid;
		while(L<=R) (a[mid=L+R>>1].r<=a[i].l)?L=mid+1,ls[i]=mid:(R=mid-1);
	}
	memset(f,-0x3f,sizeof f);
	memset(pmax,-0x3f,sizeof pmax);
	f[0][0]=0;pmax[0][0]=0;
	F(i,1,k) {
		F(j,0,99) {int pj=(j+99)%100;
			q[j].del(ls[i]+1);
			tmp[pj]=max(pmax[j][ls[i]]+V[a[i].r]-V[a[i].l],
						q[j].mx(f[j])+V[a[i].r]);
		}
		F(j,0,99) {
			tmp[j]<0&&(tmp[j]=-inf);
			f[j][i]=tmp[j];
			pmax[j][i]=max(pmax[j][i-1],f[j][i]);
			q[j].push(f[j],i);
		}
	} int zm=((-n+m)%100+100)%100;
	cout<<*max_element(f[zm],f[zm]+n+1)<<endl;
	return 0;
}
```

---

