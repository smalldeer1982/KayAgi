# [CERC2014] Outer space invaders

## 题目描述

来自外太空的外星人（最终）入侵了地球。保卫自己，或者解体，被他们同化，或者成为食物。迄今为止，我们无法确定。

外星人遵循已知的攻击模式。有 $N$ 个外星人进攻，第 $i$ 个进攻的外星人会在时间 $a_i$ 出现，距离你的距离为 $d_i$，它必须在时间 $b_i$ 前被消灭，否则被消灭的会是你。

你的武器是一个区域冲击波器，可以设置任何给定的功率。如果被设置了功率 $R$，它会瞬间摧毁与你的距离在 $R$ 以内的所有外星人（可以等于），同时它也会消耗 $R$ 单位的燃料电池。

求摧毁所有外星人的最低成本（消耗多少燃料电池），同时保证自己的生命安全。

## 样例 #1

### 输入

```
1
3
1 4 4
4 7 5
3 4 7
```

### 输出

```
7```

# 题解

## 作者：Cry_For_theMoon (赞：31)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P4766)

&emsp;&emsp;不是所有"数字大但是个数少"的都能离散化的，本题我们离散化只是因为**我们只关注每个事件（即一个外星人的进攻，死亡）的相对关系**，比如如果有一个外星人在 $4$ 死亡，下一个外星人出生发生在 $8$，且中间没有别的事件发生，那么中间那段时间是无足轻重的，因为你肯定不会在一个没有外星人存在的时间发动武器。还有一种情况就是两个外星人的出生之间没有别的事件发生，此时如果选在这段中间时间攻击，等同于放在第一个外星人出生的时候攻击，因为攻击到的对象都是一样的。只关注相对大小，这才是离散化的核心。

&emsp;&emsp;进入正题：区间DP

&emsp;&emsp;离散化后 $n = 600$，又因为本题时限 2s（然而1s就足以水过），显然复杂度吻合一般区间DP的$O(n^3)$。我们设计的状态自然而然想到了 $f(i,j)$ 表示消灭时刻 $[i,j] $ 的所有外星人的最小花费。

&emsp;&emsp;区间 DP 一定会被拆成两个子区间，不管以什么方式合并。但是如果上手就是拆成两个子区间考虑，**跨越子区间的在这种情况下会被考虑两次**，最关键的是，虽然被考虑，但是不一定被计算，因为如果子区间里有距离更远的，他就无意义了。这样的话，我们也无法很好地消去跨越两个子区间的外星人们的影响，因为你得维护诸如哪些外星人跨越了断点 $k$，哪些跨越断点的外星人影响到了解，如何去掉这些影响。反正我是不会做QwQ。

&emsp;&emsp;区间DP的另一大套路就是：当我不好"拆分-合并"的时候，先考虑**最后执行的操作**，再用这个最后执行的操作把区间分成两部分，可以视作"合并-拆分"。有时候甚至需要枚举断点-合并-拆分（顺便推荐一道用到这个思想的区间DP：[传送门](https://www.luogu.com.cn/problem/P5851)）。考虑这里能否确定最后一次操作，可以确定的是，**该区间内出现的距离最大的外星人一定直接打掉**，因为既然距离最大，不可能有打掉别人的同时打掉这个外星人的情况的出现，因此一定有一次进攻操作是针对这个距离最远的外星人的。

&emsp;&emsp;设这个距离最远的外星人编号为 $g$，那么 $[g.l,g.r]$（当然指离散化后） 的所有时间段都可以打，枚举点 $k$，然后**所有出现时间跨越了$k$，都消失了**，那么最后一个问题也解决了：状态里的 $i,j$，考不考虑某个外星人的生活事件超出了 $[i,j]$ 的情况。我们发现如果考虑，那么你计算 $f(i,k-1)$ 和 $f(k+1,j)$ 的时候，跨越子区间还有 $k$ 的外星人明明被消灭了，但是在你这里没有体现，还会被计算。

&emsp;&emsp;最后找不超过 $[i,j]$ 的外星人的最大距离时没有像别的题解每次暴力枚举，也是用了 $n^2$ 的 $DP$ 预处理了以下，这个东西相信来做这道题的都会了，就放在代码里吧。当然因为最后DP的时候还是要枚举那个最大外星人的生存时间，所以复杂度其实并没有降下来，只是会快一点点QwQ。

```cpp
//CERC,2014
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN=310,INF=1e9;
struct Node{
	int l,r,w;
	int bl,br; 
}node[MAXN];
int t,n,b[MAXN*2],tot;
int f[MAXN*2][MAXN*2],g[MAXN*2][MAXN*2];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(g,0,sizeof g);
		set<int>s;
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&node[i].l,&node[i].r,&node[i].w);
			s.insert(node[i].l);s.insert(node[i].r);
		}
		set<int>::iterator it;
		tot = 0;
		for(it = s.begin();it!=s.end();it++){
			int v = *it;
			b[++tot] = v;
		}
		sort(b+1,b+1+tot);
		for(int i=1;i<=n;i++){
			node[i].bl = lower_bound(b+1,b+1+tot,node[i].l) - b;
			node[i].br = lower_bound(b+1,b+1+tot,node[i].r) - b;
		}
		for(int i=1;i<=n;i++){
			g[node[i].bl][node[i].br] = (node[g[node[i].bl][node[i].br]].w>node[i].w)?g[node[i].bl][node[i].br]:i;
		}
		for(int len=2;len<=tot;len++){
			for(int i=1;i+len-1<=tot;i++){
				int j=i+len-1;
				int tmp = (node[g[i][j-1]].w > node[g[i+1][j]].w) ? g[i][j-1]:g[i+1][j];
				g[i][j] = (node[tmp].w > node[g[i][j]].w) ? tmp : g[i][j];
			}
		}
		for(int len=1;len<=tot;len++){
			for(int i=1;i+len-1<=tot;i++){
				int j=i+len-1;
				if(g[i][j] == 0){
					f[i][j] = 0;continue;
				}
				f[i][j] = INF;
				for(int k=node[g[i][j]].bl;k<=node[g[i][j]].br;k++){
					f[i][j] = min(f[i][j],f[i][k-1]+f[k+1][j]+node[g[i][j]].w);
				}
			}
		}
		printf("%d\n",f[1][tot]);
	}
	
	return 0;
}
```


---

## 作者：红黑树 (赞：24)

[可能更好的阅读体验](https://rbtr.ee/luogu-P4766)

## [题意](https://www.luogu.com.cn/problem/P4766)
有 $n$ 个敌人，第 $i$ 个敌人跟你的距离是 $d_i$，必须在 $\left[a_i, b_i\right]$ 时刻消灭。

你可以在某个时刻消耗 $r$ 的代价，消灭距离 $r$ 以内的所有敌人。求摧毁所有敌人的最小代价。

$1 \leq n \leq 300$

## 题解
尝试使用线性 DP 后发现不行，所以考虑区间 DP。

$f\left(l, r\right)$ 表示左右端点都在 $\left[l, r\right]$ 的敌人被消灭的最小代价。

每次转移时找到距离最远的点 id，然后枚举是在那个时间点消灭的，把这个点能消灭的都消灭掉。离散化后，时间复杂度 $\mathcal O\left(n^3\right)$。

转移方程：
$$f\left(l, r\right) = d_{id} + \min\limits_{k \in \left[l_{id}, r_{id}\right]}\{f\left(l, k - 1\right) + f\left(k + 1, r\right)\}$$

## 代码
```cpp
// Please submit with C++14!
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#define ra _Read()
#ifdef ___RB_DEBUG___
#include "rb_debug.h"
#else
#define dbg(...)
#define dputs(...)
#endif

using tp = long long;
using namespace std;
constexpr bool __MTCS__ = 1;
constexpr tp Hat_N = 303;
tp _Read();

namespace __SOL__ {
struct Alien {
  tp l, r, d;
};

signed main() {
  tp n = ra, m = 0;
  array<tp, Hat_N * 2> b;
  array<Alien, Hat_N> v;
  array<array<tp, Hat_N * 2>, Hat_N * 2> f;
  for (tp i = 1; i <= n; ++i) {
    b[++m] = v[i].l = ra;
    b[++m] = v[i].r = ra;
    v[i].d = ra;
  }
  stable_sort(b.begin() + 1, b.begin() + m + 1);
  m = unique(b.begin() + 1, b.begin() + m + 1) - b.begin() - 1;
  for (tp i = 1; i <= n; ++i) {
    v[i].l = lower_bound(b.begin() + 1, b.begin() + m + 1, v[i].l) - b.begin();
    v[i].r = lower_bound(b.begin() + 1, b.begin() + m + 1, v[i].r) - b.begin();
  }
  for (tp len = 0; len < m; ++len) {
    for (tp l = 1; l + len <= m; ++l) {
      tp r = l + len, id = -1;
      for (tp i = 1; i <= n; ++i) {
        if (l <= v[i].l && v[i].r <= r && (!~id || v[i].d > v[id].d)) {
          id = i;
        }
      }
      if (!~id) {
        f[l][r] = 0;
      } else {
        f[l][r] = -1ull >> 2;
        for (tp k = v[id].l; k <= v[id].r; ++k) {
          f[l][r] = min(f[l][r], f[l][k - 1] + f[k + 1][r]);
        }
        f[l][r] += v[id].d;
      }
    }
  }
  printf("%lld\n", f[1][m]);
  return 0;
}
}  // namespace __SOL__

signed main() {
  tp __MTCS__ = ::__MTCS__ ? ra : 1;
  while (__MTCS__--) {
    __SOL__::main();
  }
  return EXIT_SUCCESS;
}

tp _Read() {
  bool __neg(0);
  char __c(getchar());
  tp __val(0);
  for (; __c < 48 || __c > 57; __c = getchar()) {
    __neg = __c == 45;
  }
  for (; __c > 47 && __c < 58; __c = getchar()) {
    __val = __val * 10 + (__c & 15);
  }
  return __neg ? ~__val + 1 : __val;
}
```

---

## 作者：灵乌路空 (赞：14)

[TOC]

知识点：区间 DP

链接：[Luogu](https://www.luogu.com.cn/problem/P4766)。

可能更好的阅读体验：[My blog](https://www.cnblogs.com/luckyblock/p/17056671.html)。

### 简述

>有 $n$ 匹黄金船赶来侵略地球。第 $i$ 匹黄金船会在时间 $a_i$ 出现在距离你 $d_i$ 的位置，被消灭的时间不能大于 $b_i$，否则你就会被外星怪马抓回她的母星每天做十万次马儿跳。在任一时刻你可以释放一次距离为 $R$ 的忍术，花费 $R$ 的代价将距离你不大于 $R$ 的黄金船干掉。求不被抓走前提下干掉所有黄金船的最小代价。  
>$T$ 组数据，每组数据给定长度为 $n$ 的三个数列 $a,b,d$，描述了一次外星怪马的侵略，求抵挡这次侵略的最小代价。    
>$1\le n\le 300$，$1\le a_i<b_i\le 10^4$，$1\le d_i\le 10^4$。    
>题面中没有给出 $T$ 的范围，但经测试 $T$ 并不影响总复杂度。  
>2S，128MB。  

### 假算法一

我想到一个线性 DP！

显然只在恰好 $b_i$ 时刻释放忍术是最优的。考虑先将黄金船按 $b_i$ 升序排序，这样在后面的忍术对是否消灭了前面的黄金船没有影响。设 $f_i$ 表示消灭前 $i$ 匹黄金船的最小代价，转移时枚举最后一次释放忍术的时刻 $b_j$，考虑最后一次释放忍术把 $j\sim i$ 这一段黄金船全部消灭，则在满足 $\left( \max_{k=j}^{i} a_i \le b_j\right)$ 条件下，有：  

$$f_i = \min_{j= 1}^{i}\left( f_{j - 1}+ \max_{k = j}^{i} d_k\right) $$

答案即 $f_n$，总复杂度 $O(n)$ 级别。

然而假了。虽然排序后后面的忍术不会影响前面的黄金船，但前面的忍术会影响到后面的黄金船。具有后效性，无法进行线性 DP。

### 真算法一

发现 $n$ 较小，但 $a,b$ 较大，考虑先离散化，记离散化后最大的时刻为 $m$。

按时间顺序枚举具有后效性，则考虑对时间维进行区间 DP。设 $f_{i,j}$ 表示将满足 $i\le a_p < b_p\le j$ 的黄金船 $p$ 全部消灭的代价。转移时考虑最后在位置 $k(i\le k\le j)$ 进行的一次操作，在这次操作之前消灭了 $[a_p,b_p]\subseteq [i,k-1]$ 和 $[a_p, b_p]\subseteq [k+1,i]$ 中的所有黄金船 $p$，这次操作消灭了满足 $i\le a_p \le k \le b_p\le j$ 的全部黄金船，即有：

$$f_{i,j} = \min_{k=i}^{j}\left( f_{i, k - 1} + f_{k + 1, j}  + d_{i,j,k}\right)$$

上式中 $d_{i,j,k}$ 表示满足：$i\le a_p \le k \le b_p\le j$ 的黄金船 $p$ 中最远的距离，即：

$$d_{i,j,k} = \max_{i\le a_p \le k \le b_p\le j} d_p$$

最终答案即 $f_{1,m}$。

发现 DP 的过程是 $O(n^3)$ 级别的，但预处理 $d$ 是 $O(n^4)$ 级别的，不预处理则 DP 变为 $O(n^4)$ 级别，无法通过本题。

### 真算法二

发现复杂度瓶颈出在取最大值的过程中。取最大值的目的是得到 $[a_p, b_p]$ 跨越区间分界点 $k$ 的最大的 $d_p$，计算出使得 $[i,j]$ 中的黄金船全部被消灭的**最后一次**操作的代价。

发现操作的顺序并不影响正确性，我们不妨钦定满足 $[a_p,b_p]\subseteq [i,j]$ 的 $d_p$ 最大的黄金船是在最后一次操作中被消灭的。转移时先求得这匹黄金船的编号 $\operatorname{id}$，则枚举的分界点 $k$ 被限定在了 $[a_{\operatorname{id}}, b_{\operatorname{id}}]$ 中，有：  

$$f_{i,j} = \min_{k=a_{\operatorname{id}}}^{b_{\operatorname{id}}}\left( f_{i, k - 1} + f_{k + 1, j}  + d_{\operatorname{id}}\right)$$

仅需在枚举 $k$ 之前 $O(n)$ 地求得 $\operatorname{id}$ 即可。答案仍为 $f_{1,m}$。总复杂度 $O(n^3)$ 级别，可以通过本题。

### 真算法三

真算法二和其他题解中的写法已经非常类似了，但其他题解中在转移时没有分界点 $k$ 的限制，为什么仍然得到了正确的答案呢？换言之，怎么保证 $k\notin [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移一定不优于 $k\in [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移呢？

需要指出的是，真算法二实际上是对真算法一的一种减去无用转移的优化。我们考虑一次 $k\notin [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移 $f_{i,j} = \min\left( f_{i, k - 1} + f_{k + 1, j}  + d_{\operatorname{id}}\right)$。此时有 $[a_{\operatorname{id}}, b_{\operatorname{id}}] \subseteq [i,k-1]$ 或 $[a_{\operatorname{id}}, b_{\operatorname{id}}]\subseteq [k+1, j]$，若这里的 $f_{i,j}$ 定义不变，则最大的代价 $d_{\operatorname{id}}$ 已经在 $f_{i,k-1}$ 或 $f_{k+1,j}$ 中被计算了一次了。更进一步地，在真算法一中，我们在计算 $f_{i,j}$ 时选择的是 $k\in [a_p, b_p]$ 的最大的代价 $d_p$，显然有 $d_p\le d_{\operatorname{id}}$。当我们在真算法二中进行 $k\in [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移时，$d_p$ 的贡献也是已经被包含在了 $f_{i,k-1}$ 或 $f_{k+1,j}$ 中了。

总结一下，$k\notin [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移实质上都是 $k\in [a_{\operatorname{id}}, b_{\operatorname{id}}]$ 的转移的重复状态，把它们都考虑上也并不会影响正确性。

### 代码

真算法二

```cpp
//By:Luckyblock
/*
知识点：区间 DP
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
const int kN = 300 + 10;
const int kD = kN << 1;
const int Inf = 1e9;
//=============================================================
int n, l[kN], r[kN], d[kN], f[kD][kD];
int dnum, data[kD]; 
//=============================================================
inline int read() {
	int f = 1, w = 0; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = - 1;
	for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + ch - '0';
	return f * w;
}
void Init() {
	n = read();
	for (int i = 1; i <= n; ++ i) {
		l[i] = read(), r[i] = read(), d[i] = read();
		data[i] = l[i], data[i + n] = r[i];
	}
	dnum = 0;
	std::sort(data + 1, data + 2 * n + 1);
	for (int i = 1; i <= 2 * n; ++ i) {
		if (data[i] != data[i - 1]) {
			data[++ dnum] = data[i];
		}
	}
	for (int i = 1; i <= n; ++ i) {
		l[i] = std::lower_bound(data + 1, data + dnum + 1, l[i]) - data;
		r[i] = std::lower_bound(data + 1, data + dnum + 1, r[i]) - data;
	}
}
void DP() {
	for (int i = 1; i <= dnum; ++ i) {
		for (int j = 1; j <= dnum; ++ j) {
			f[i][j] = Inf;
		}
	}
	for (int lth = 1; lth <= dnum; ++ lth) {
		for (int ll = 1, rr = ll + lth - 1; rr <= dnum; ++ ll, ++ rr) {
			int maxd = 0, maxdid = 0;
			for (int k = 1; k <= n; ++ k) {
				if (ll <= l[k] && r[k] <= rr) {
					if (d[k] > maxd) maxd = d[k], maxdid = k;
				}
			}
			if (!maxd) {
				f[ll][rr] = 0;
				continue;
			}
			for (int k = l[maxdid]; k <= r[maxdid]; ++ k) {
				f[ll][rr] = std::min(f[ll][rr], 
														 f[ll][k - 1] + f[k + 1][rr] + maxd);
			}
		}
	}
}
//=============================================================
int main() {
	int T = read();
	while (T --) {
		Init();
		DP();
		printf("%d\n", f[1][dnum]);
	}
	return 0;
}
```

---

## 作者：Skyjoy (赞：10)

# 思路

这题的题意可以这样转化：给你一个平面直角坐标系，以时间轴为 $x$ 轴，以距离轴为 $y$ 轴（可能表述得不准确）。在这个坐标系上有一些平行于 $x$ 轴的线段，你要用若干条下端点在 $x$ 轴上的线段与每一条横向的线段相交，问这若干条线段的长度和的最小值是多少。

我们发现，当我们在计算 $[l,r]$ 这段时间时，我们必须用一条线段来交纵坐标最大（也就是 d 值最大）的线段，下面的一些线段也就自动被消除了。我们假设我们此时必须交的线段的时间为 $[ll,rr]$ ，则我们可以枚举 $[ll,rr]$ 上的每一个点来放线段，这样我们就可以用区间 dp 来算出答案了。

假设我们枚举区间 $[l,r]$ 时的答案为 $f(l,r)$ ，在此区间中距离最远的线段距离为 $d$ ，其区间为 $[ll,rr]$ ，则有：

$$f(l,r)=\sum_{i=ll}^{rr}(f(l,i-1)+f(i+1,r)+d)$$

然后就可以写代码啦！

值得注意的是，这道题的 $a_i$ 和 $b_i$ 都是比较大的，直接以它们的大小来开二维数组是会炸的。但是这题的线段数量比较小，我们也只需要区间的相对大小而不是真实大小，所以对 $a_i$ 和 $b_i$ 进行离散化处理就可以了！

~~然而这题有些坑，记忆化搜索被卡得好惨，作者就因此被卡了好多次，只能用标准的区间 dp 写法了。~~

# 代码

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define Elaina std
I love Elaina;
const int N=310;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int T,n,a[N],b[N],c[N<<1],d[N],m,f[N<<1][N<<1];
int main(){
	T=read();
	while(T--){
		memset(f,0,sizeof(f));
		memset(c,0,sizeof(c));
		n=read();
		for(int i=1;i<=n;i++)a[i]=c[2*i-1]=read(),b[i]=c[2*i]=read(),d[i]=read();
		sort(c+1,c+2*n+1);
		m=unique(c+1,c+2*n+1)-c-1;//去重
		for(int i=1;i<=n;i++)a[i]=lower_bound(c+1,c+m+1,a[i])-c,b[i]=lower_bound(c+1,c+m+1,b[i])-c;//离散化
		for(int len=2;len<=m;len++){//区间 dp 板子
			for(int l=1,r=l+len-1;r<=m;l++,r++){
				int maxn=0,ll=-1,rr=-1;
				for(int i=1;i<=n;i++)if(a[i]>=l&&b[i]<=r&&maxn<d[i])maxn=d[i],ll=a[i],rr=b[i];
				if(ll==-1)continue;
				f[l][r]=0x3f3f3f3f;
				for(int i=ll;i<=rr;i++)f[l][r]=min(f[l][r],f[l][i-1]+f[i+1][r]+maxn);
			}
		}
		printf("%d\n",f[1][m]);
	}
	return 0;
}
```

祝各位大神们省选顺利，取得理想的成绩！

---

## 作者：pigstd (赞：9)

首先离散化，使时间区间为 $[1,p]$，$dp_{i,j}$ 表示杀死出现时间 $[l,r] \in [i,j]$ 的所有外星人的最低成本，则答案为 $dp_{1,p}$，考虑转移。

- 如果没有外星人，那么 $dp_{i,j}=0$。
- 如果有外星人，那么设 $maxn_i=max(d_p)\ ([l_p,r_p]\in [i,j])$，不难得到 $dp_{i,j}=\min(dp_{i,k-1}+maxn_k+dp_{k+1,j})\ (k \in [i,j])$。

然后发现预处理 $maxn$ 数组是 $O(n^2)$ 的，时间复杂度是 $O(n^4)$ 貌似并不过的去，如果用线段树维护 $maxn$ 的话也要 $O(n^3 \times logn)$，因为离散化之后 $n$ 达到了 $600$ 的规模也很难过去。

接下来是一个比较重要的结论了：我们并不用处理 $maxn$ 数组，只要直接找到一个 $p$ 满足 $d_p$ 在所有满足条件的点中最大，这样子就能够做到 $O(n^3)$ 了。

为什么这样子是对的呢？~~绝大部分题解都没有解释，可能他们觉得这个太简单了~~。感性理解一下，枚举的这个 $k$ 就意味这在 $k$ 这个时间点上进行一次操作。那么对于 $p$，必然有一个操作是在 $[l_p,r_p]$ 之间的（为了消除 $p$），而且因为 $p$ 是最大的，那么 $maxn$ 就显然是 $d_p$ 不用预处理了。

[code](https://www.luogu.com.cn/paste/umr8j8ob)。

---

## 作者：Mudrobøt (赞：6)

这道题作为区间DP的补充还是非常有意思的。

一句话题意：

就是你知道每一个外星人的出生时间和消失时间和他和你的距离，为了消灭完他们！我们需要用一个很NB的武器，就是一个什么可以攻击一个圆的武器（以自己为圆心），每次消耗的能量为攻击半径，问我们消灭所有外星人消耗的最小的能量。

这道题首先我们应该想到的是首先先对所有的时间进行离散化，因为我们发现，只有最多300个外星人，但是时间的大小是10000，有一点大，但是只要我们离散化以后，开一个二维数组还是非常的合理的。

然后我们呢类似于合并石子的思路，我们定义当前二位动态规划数组的一维存的是从一个时间，二维存的是到另一个时间点，表示的是消灭此时间区间的外星人所需要的最小的能量。

然后我们就可以非常快速的推出动态转移方程式：

```
dp[s][e]=min(dp[s][e],dp[s][k-1]+a[id].v+dp[k+1][e]);
```

但是我们要明白的一点就是，我们这里肯定是要打到外星人，那么我们就必须确保这一段区间中存在外星人，并且一定是该区间距离中心最远的外星人。所以所我们每次枚举出来一个区间后一定要看该区间中有没有外星人存在并且要保证当前区间完全包含外星人，否则会出现混乱。然后我们就枚举这个k的时间点（k必须在我们枚举出的外星人存在范围内）然后进行dp取最小即可。

注意我们一定是从小区间开始然后慢慢合成到大区间！！！

所以说大家可以认真的思考一下代码中动态规划前面两个for循环为什么要这样写！

参考代码：

```
#include<bits/stdc++.h>
#define BIG 3000005
using namespace std;
struct sd{
    int l,r,v;
}a[305];
int t,n;
int que[305*5],count_que=0,dp[2*305][2*305];
void manage()
{
    count_que=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].v);
        que[++count_que]=a[i].l;
        que[++count_que]=a[i].r;
    }
    sort(que+1,que+count_que+1);
    count_que=unique(que+1,que+count_que+1)-que-1;
    for(int i=1;i<=n;++i) a[i].l=lower_bound(que+1,que+1+count_que,a[i].l)-que,a[i].r=lower_bound(que+1,que+1+count_que,a[i].r)-que;//上面都是读入和离散化
    //下面是真正的区间DP
    for(int w=0;w<count_que;++w)
    {
        for(int s=1;s+w<=count_que;++s)
        {
            int e=s+w,id=-1;
            for(int i=1;i<=n;++i)if(s<=a[i].l&&a[i].r<=e&&(id==-1||a[i].v>a[id].v))id=i;
            if(id==-1){ dp[s][e] = 0;continue;}
            dp[s][e]=BIG;
            for(int k=a[id].l;k<=a[id].r;++k) dp[s][e]=min(dp[s][e],dp[s][k-1]+a[id].v+dp[k+1][e]);
        }
    }
    printf("%d\n", dp[1][count_que]);
}
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;++i) manage();
    return 0;
}
```
By njc

---

## 作者：cjlak1o1 (赞：5)

小小讲一讲吧，写篇题解。  
[博客食用更佳哦](https://www.cnblogs.com/windseekerblog/p/16518209.html)

### 条件

- $n$ 非常小，大概 $n^3$ 能过。

- 有编号，时间，距离三个要素。

- 时间很大，不可能直接作为数组的两维。

### 思路

出于对上述条件的考虑，一位大佬思考过后决定使用区间dp，并教会了我。

- 用离散化后的时间作为数组的两维。

- 而后每次枚举时间的时候，找到这在当前时间区间中距离最大的外星人。由于这个外星人必须被杀，且杀完它之后其他外星人都被杀了，所以我们直接考虑它就可以了。

### 状态转移方程

$$dp_{i,j}=\min \limits_{k=l_{id}}^{r_{id}}(dp_{i,j},dp_{i,k-1}+dp_{k+1,j}+d_{id})$$

$id$ 为当前区间距离最大的外星人的编号。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=750,Inf=11000*300;

template<class T> T read(T &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x;
} 

int T,n;
int dp[N][N],tim[N],id[11000];//tim为离散数组,注意数组的大小 
struct node{
	int l,r,d;
}a[N];

int main(){
	read(T);
	while(T--){
		read(n);
		int cnt=0;
		memset(dp,0,sizeof(dp));//初始化重点
		for(int i=1;i<=n;i++) read(a[i].l),read(a[i].r),read(a[i].d),tim[++cnt]=a[i].l,tim[++cnt]=a[i].r;
		sort(tim+1,tim+cnt+1);
		for(int i=1;i<=cnt;i++) id[tim[i]]=i;
		for(int i=1;i<=n;i++) a[i].l=id[a[i].l],a[i].r=id[a[i].r];//离散化
		for(int len=1;len<cnt;len++){
			for(int i=1;i+len<=cnt;i++){
				int j=i+len,now=0;
				dp[i][j]=Inf;//初始化 
				for(int k=1;k<=n;k++){//寻找max
					if(a[k].l>=i&&a[k].r<=j)
					 	if(!now||a[k].d>a[now].d) now=k;
				}
				if(!now) {dp[i][j]=0;continue;}//dp[i][j]=0没有敌人 
				for(int k=a[now].l;k<=a[now].r;k++) dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]+a[now].d);
			}
		}
		printf("%d\n",dp[1][cnt]);
	}
}
/*
1
3
1 4 4
4 7 5
3 4 7
*/
/*
7
*/
```
**蒟蒻拙见，请指教。**

---

## 作者：ListenSnow (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P4766 "原题链接")

## 题意

有 $n$ 个敌人，第 $i$ 个敌人的距离为 $d_i$，必须在 $[a_i,b_i]$ 时刻内被消灭。

可以在任意时刻消耗 $r$ 的代价，消灭距离为 $r$ 以内的所有敌人，求消灭所有敌人的最小代价。

$1 \leq n \leq 300,1 \leq d_i \leq 10000,1\leq a_i \leq b_i \leq 10000$。

## 思路

注意到时刻的范围比较大，实际用到的时刻很少，可以将端点时刻**离散化**一下。

如果设 $f_i$ 为消灭了按照 $b_i$ 排序后前 $i$ 个敌人的最小代价，可以发现消灭前 $i$ 个敌人时，也可以消灭 $i+1\sim n$ 的敌人，而这部分对于后面的转移又有影响，所以无法直接线性转移。

既然用消灭的敌人来设计状态行不通，就可以尝试按照时间来设计状态。

考虑假设 $f_{l,r}$ 为消灭了所有出现时刻在 $[l,r]$ 区间内的敌人（即所有满足 $l \leq a_i \leq b_i \leq r$ 的敌人）的最小代价。这样设计状态就可以有效地避免前面提到的后效性问题。

假设在这个区间内距离最远的敌人距离为 $r$，出现时刻为 $[L,R]$。那么必然会在 $[L,R]$ 内选择某一时刻消耗 $r$ 的代价来消灭敌人，可以得到状态转移方程：

$$f_{l,r}=r+\min_{L\leq k \leq R}(f_{l,k-1}+f_{k+1,r})$$

而对于断开点 $k \notin [L,R]$，如 $f_{l,R-1}+f_{R+1,r}$ 这类的转移，实质上在 $f_{R+1,r}$ 中还是会把 $r$ 计算一遍，所以这类转移是重复的，也就没必要写进转移方程内了。

## code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=610,INF=0x3f3f3f3f;
int num[N],f[N][N],n,tot;
struct alien{int l,r,v;}a[N];
void solve()
{
	scanf("%d",&n);tot=0;for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].v),num[++tot]=a[i].l,num[++tot]=a[i].r;
	sort(num+1,num+tot+1);tot=unique(num+1,num+tot+1)-num-1;
	for(int i=1;i<=n;i++) a[i].l=lower_bound(num+1,num+tot+1,a[i].l)-num;
	for(int i=1;i<=n;i++) a[i].r=lower_bound(num+1,num+tot+1,a[i].r)-num;
	for(int len=1;len<=tot;len++)
	    for(int l=1,r=l+len-1;r<=tot;l++,r++)
	    {
	    	f[l][r]=INF;int p=0;
	    	for(int k=1;k<=n;k++) if(a[k].l>=l&&a[k].r<=r&&a[k].v>a[p].v) p=k;
	    	if(!p) {f[l][r]=0;continue;}//也就是没有敌人的出现时刻完全在这个区间内
	    	for(int k=a[p].l;k<=a[p].r;k++) f[l][r]=min(f[l][r],f[l][k-1]+f[k+1][r]+a[p].v);
		}
	printf("%d\n",f[1][tot]);
}
int main()
{
	int T;scanf("%d",&T);while(T--) solve();
	return 0;
}
```

---

## 作者：Chthologist7507 (赞：3)

区间 DP。

首先考虑离散化，因为时间跨度比较大，而且我们只考虑时间的先后顺序问题。

然后设计 DP 方案。

设 $f[i][j]$ 表示 杀死所有出现时间在区间 $[i,j]$ 内的所有外星人所需的最低代价。

如果区间 $[i,j]$ 内没有外星人，那么 $f[i][j]=0$

如果有，那么考虑将区间分割为 $[i,k-1],\{k\},[k+1,j]$

这样就有 $f[i][j]=\min\limits_{k=i}^j\{f[i][k-1]+f[k+1][j]+\max\limits_{p,[a_p,b_p]\in[i,j]}d_p\}$

然后 $\max\limits_{p,[a_p,b_p]\in[i,j]}d_p$ 需要预处理一下，没了

```cpp
#include <bits/stdc++.h>
#define ll long long
#define inl inline
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
const int N=310;
int t[N<<1],f[N<<1][N<<1],maxn[N<<1],cnt;
struct Node{
	int a,b,d;
}a[N];
map<int,int>mp;
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--){
		mp.clear();cnt=0;
		int n;cin>>n;
		rep(i,1,n)cin>>a[i].a>>a[i].b>>a[i].d,t[++cnt]=a[i].a,t[++cnt]=a[i].b;
		sort(t+1,t+cnt+1);
		int tm=0;
		rep(i,1,cnt)mp[t[i]]=++tm;
		rep(i,1,n)a[i].a=mp[a[i].a],a[i].b=mp[a[i].b];
		rep(i,1,n)rep(j,a[i].a,a[i].b)maxn[j]=max(maxn[j],a[i].d);
		rep(l,1,tm)rep(i,1,tm-l){
			int j=i+l,r=0,id=0;f[i][j]=0x3f3f3f3f;
			rep(k,1,n)if(a[k].a>=i&&a[k].b<=j&&r<a[k].d)r=a[k].d,id=k;
			if(!r){f[i][j]=0;continue;}
			rep(k,a[id].a,a[id].b)f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+a[id].d);
		}
		cout<<f[1][tm]<<'\n';
	}
}
```

---

## 作者：ShineEternal (赞：3)

[link](https://blog.csdn.net/kkkksc03/article/details/110098711)

## description：
有 $n$ 个外星人进攻，第 $i$ 个进攻的外星人会在时间 $a_i$ 出现，距离你的距离为 $d_i$ ，它必须在时间 $b_i$ 前被消灭，否则被消灭的会是你。

你的武器是一个区域冲击波器，可以设置任何给定的功率。如果被设置了功率 $R$，它会瞬间摧毁与你的距离在 $R$ 以内的所有外星人（可以等于），同时它也会消耗 $R$ 单位的燃料电池。（个人注解：这个冲击波是**瞬时**的。）

求摧毁所有外星人的最低成本（消耗多少燃料电池），同时保证自己的生命安全。

## solution：
这道题我们可以考虑区间dp。

设 $f[l][r]$ 表示在 $[l,r]$ 上最低的成本。

但是我们发现，坐标的范围达到了 $1e4$，这就意味着数组也会开得较大。我们不妨离散化一下。（因为 $n$ 较小）

然后考虑如何转移。

发现对于一段时间区间，我们可以贪心的消去最远的外星人，这样浪费就少。

于是，我们以最远的外星人为转移契机：

$f[l][r]=f[l][k-1]+f[k+1][r]+d[tag](a[tag]\leq k\leq b[tag])$，其中 $tag$ 为该段时间内最远的外星人的序号。



```cpp
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
map<int,int>mp;
int f[705][705];//f[l][r]表示[l,r]这段时间所需的花费。 
int a[1005],b[1005],d[1005]; 
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));
		for(int i=1;i<=10000;i++)mp.clear();
		int n,cnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&a[i],&b[i],&d[i]);
			mp[a[i]]=1;//离散
			mp[b[i]]=1;
		}
		for(int i=1;i<=10000;i++)
		{
			if(mp[i]==1)
			{
				mp[i]=++cnt;//重新编号
			}	
		}
		for(int i=1;i<=n;i++)
		{
			a[i]=mp[a[i]];//赋值编排
			b[i]=mp[b[i]];
		}
		for(int len=1;len<cnt;len++)//众所周知，区间dp的第一层循环要先枚举区间的长度。
		{
			//printf("test\n");
			
			for(int i=1;i+len<=cnt;i++)//接着是区间的起始点。
			{
			//	printf("Test2\n");
				int j=i+len;
				f[i][j]=1000000000;
				int tag,ans=0;
				for(int k=1;k<=n;k++)
				{
					//printf("Test3\n");
					if(a[k]>=i&&b[k]<=j&&d[k]>ans)//寻找最大的外星人。
					{
						ans=d[k];
						tag=k;
					}
				}
				if(ans==0)
				{
					f[i][j]=0;
					continue;
				}
				for(int k=a[tag];k<=b[tag];k++)//在这个最大的外星人的安全时间内的区间都可以如此合并。
				f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+ans);
			}
		} 
		printf("%d\n",f[1][cnt]);
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：2)

考虑区间 dp。

令 $f_{l,r}$ 表示将时间离散化后，消灭出现和消失都在区间 $[l,r]$ 的外星人的总代价。

转移：$f_{l,r}=\min\{f_{l,k-1}+f_{k+1,r}+\text{cost}(k)\}(l<k<r)$

考虑怎么计算 $\text{cost}(k)$。

用数据结构维护是简单的。但大多要带上 $\log$。

我们发现，一个区间内最远的外星人一定会被处理到。

所以只需要在当前区间距离最远的外星人存在的时间线上枚举 $k$。可以 $O(n)$ 和划分子问题时一起完成。

时间复杂度 $O(n^3)$。

---

## 作者：Jiang_zi_chuan (赞：2)

双倍经验吼啊！

首先发现坐标蛮大的，但是n≤300

，于是我们可以离散化一下。

区间DP：设f[i][j]
表示把起点为j，长度为i

的区间里的外星人都打死的最小花费。

每次转移时，在区间里找到最远的外星人x

。

状态转移方程：

f[i][j]=min{f[k−j+1][j]+f[j+i−k][k]+d[x]},a[x]≤k≤b[x]

答案为f[m][0]
，m

为离散化之后的最大区间坐标。

（用开区间转移的时候似乎更容易处理一点）

```cpp
// luogu-judger-enable-o2
//#define LOCAL
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

#define ull unsigned long long
#define ll long long
#define FOR(a, b, n) for(int a = b; b >= n ? a >= n : a <= n; b >= n ? a-- : a++)
#define M(a, n) memset(a, n, sizeof(a));
#define S(n) scanf("%d", &n)
#define P(n) printf("%d\n", n)
#define G(n) getline(cin, n)
#define PI acos(-1.0)
typedef long long LL;
typedef double db;

using namespace std;

const int NR = 310;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') { 
        if(ch == '-')
            f = -1; 
        ch = getchar(); 
    }
    while(ch >= '0' && ch <= '9') { 
        x = (x << 1) + (x << 3) + ch - '0'; 
        ch = getchar(); 
    }
    return x * f;
}
const LL INF = 0x3f3f3f3f;
int n, a[NR], b[NR], d[NR], f[NR * 2][NR * 2], tmp[NR * 2], cnt;
map<int, int>mp;
int main()
{
    int T = read();
    while(T--)
    {
        mp.clear();
        cnt = 0;
        n = read();
        FOR(i, 1, n) {
            a[i] = tmp[++cnt] = read();
            b[i] = tmp[++cnt] = read();
            d[i] = read();
        }
        sort(tmp + 1, tmp + 1 + cnt);
        cnt = unique(tmp + 1, tmp + 1 + cnt) - tmp - 1;
        FOR(i, 1, cnt)
            mp[tmp[i]] = i;
        FOR(i, 1, n) {
            a[i] = mp[a[i]];
            b[i] = mp[b[i]];
        }
        ++cnt;
        FOR(i, 1, cnt + 1) {
            for(int j = 0; j + i - 1 <= cnt; ++j)
            {
                f[i][j] = INF;
                int _max = 0;
                FOR(k, 1, n)
                    if(a[k] > j && b[k] < j + i - 1 && d[k] > d[_max])
                        _max = k;
                if(!_max)
                {
                    f[i][j] = 0;
                    continue;
                }
                FOR(k, a[_max], b[_max])
                    f[i][j] = min(f[i][j], f[k - j + 1][j] + f[j + i - k][k] + d[_max]);
            }
        }
        P(f[cnt + 1][0]);
    }
    return 0;
}
```

---

## 作者：比利♂海灵顿 (赞：2)

# CERC2014 Outer space invaders

这个题为什么没有写分治的呀？

## 题意

先把题意抽象一下。

$n$ 条水平线段，坐标 $\leq 10000$，要求选一些横坐标，花费 $v$ 使得所有包含这个坐标的高度 $\leq v$ 的线段被覆盖，求所有 $n$ 条线段被覆盖的最小花费。

## 解法

因为 $n$ 比较小，所以离散化横坐标。

因为对于一组数据，必须先覆盖最高的线段，而覆盖它可以选择横坐标区间内的任何一个点，假设选的是 $Mid$，那么这些线段就会分成 $3$ 类，包含 $Mid$ 的，完全在 $Mid$ 左边的，完全在 $Mid$ 右边的。

其中包含 $Mid$ 的会被直接覆盖，不需要关心。剩下的两种线段就变成了两个子问题。

接下来就可以递归求解了。

$O(n)$ 枚举 $Mid$，$O(n)$ 给线段分类，所以每一个子问题递归之前是 $O(n^2)$。可以构造数据使得每次有 $n - 1$ 个线段在其中一个子问题中，这样就把算法卡到了 $O(n^n)$。

所以我们使用记忆化搜索，对于一个子问题，它的左端点的最小值和右端点最大值组成的区间最多有 $n^2$ 种，所以我们可以使 $f_{i, j}$ 表示 $[i, j]$ 内完全包含的线段都覆盖最少需要多少花费 (和区间 DP 的状态设计相同)。然后记忆化搜索即可，复杂度 $O(n^4)$。

从官网下载数据进行分析，发现除了样例以外，剩下的两个点一个 $n \in [10, 20]$，$T = 240$，另一个 $n \in [299, 300]$，$T = 9$。$O(n^4)$ 可以搞一下。

随便写了一发可以过 $n \leq 20$。

算出来复杂度是 $7*10^{10}$，看起来相当吓人，但是因为在 $n$ 较小的子问题中，包含 $Mid$ 的线段数量相对于 $n$ 是非常可观的，所以实际复杂度和理论复杂度相差甚远，所以基本上卡卡常就能过。

算法的复杂度主要是枚举 $Mid$ 时分类线段贡献的。

发现给线段分类的时候，随着 $Mid$ 增加，$Mid$ 左边的线段集合会不断加入元素，$Mid$ 右边的线段集合会不断减少元素，这样在 $Mid$ 改变的时候，只要遍历左边的集合以外的线段，将线段加入左边，遍历右边的集合，将线段踢出右边，就将常数减少了一倍。

这时的程序总时间已经可以跑到 $1.09s$ 了，所以已经可以 AC 了。

但是发现程序仍可以优化，之前计算子问题的坐标区间的时候，是将原来的区间递归下去，这样算出的区间边界不紧，导致同一个子问题被多次求解。将递归传参改为根据每条线段取左端点最小值和右端点最大值可以避免这种情况。将总时间压到了 $874ms$。

下面给出代码，已经比部分 $O(n^3)$ 的 DP 要快了。

```cpp
unsigned b[605], m, n;
unsigned A, B, C, D, t;
unsigned Cnt(0), Ans(0);
unsigned f[605][605];
struct Alien {
  unsigned L, R, Val;
}a[305];
inline unsigned Do (const unsigned Fr, const unsigned To) {
  unsigned U(0x3f3f3f3f), D(0);
  for (unsigned i(Fr); i <= To; ++i) U = min(U, a[i].L), D = max(D, a[i].R);
  if(Fr == To) f[U][D] = a[Fr].Val;
  if(f[U][D] < 0x3f3f3f3f) return f[U][D];
  unsigned Mid(Fr), Mdl, Mdr, Mdv, Ri(To), Le(Fr);
  for (unsigned i(Fr); i <= To; ++i) if(a[Mid].Val < a[i].Val) Mid = i;
  Mdl = a[Mid].L, Mdr = a[Mid].R, Mdv = a[Mid].Val, Mid = 0x3f3f3f3f;
  for (unsigned j(To); j >= Fr; --j) if(a[j].L > Mdl) swap(a[j], a[Ri--]);
  for (unsigned i(Mdl); i <= Mdr; ++i) {
    unsigned Tmp(0);
    for (unsigned j(Le); j <= To; ++j) if(a[j].R < i) swap(a[j], a[Le++]);
    for (unsigned j(To); j > Ri; --j) if(a[j].L == i) swap(a[j++], a[++Ri]);
    if(Le > Fr) Tmp = Do(Fr, Le - 1);
    if(Ri < To) Tmp += Do(Ri + 1, To);
    Mid = min(Mid, Tmp);
  }
  f[U][D] = Mid + Mdv;
  return f[U][D];
}
signed main() {
  t = RD();
  for (unsigned T(1); T <= t; ++T){
    n = RD();
    for (unsigned i(0); i < n; ++i) {
      a[i + 1].L = b[i << 1] = RD();
      a[i + 1].R = b[(i << 1) ^ 1] = RD(); 
      a[i + 1].Val = RD();
    }
    sort(b, b + (n << 1));
    m = unique(b, b + (n << 1)) - b;
    if(m <= 40) {
      for (unsigned i(0); i < m; ++i)
        for (unsigned j(i); j < m; ++j) 
          f[i][j] = 0x3f3f3f3f;
    } else memset(f, 0x3f, sizeof(f));
    for (unsigned i(1); i <= n; ++i) {
      a[i].L = lower_bound(b, b + m, a[i].L) - b;
      a[i].R = lower_bound(b, b + m, a[i].R) - b;
    }
    printf("%u\n", Do(1, n));
  }
  return Wild_Donkey;
}
```

---

## 作者：cosf (赞：0)

## [P4766 Outer Space Invaders](https://www.luogu.com.cn/problem/P4766)

## 思路

看到这道题目，一个显而易见的做法是区间 dp。我们令 $dp_{l, r}$ 表示打掉 $a_i$ 和 $b_i$ **均** 在 $[l, r]$ 之间的所有敌人。根据定义，$dp_{\min{a_i}, \max{b_i}}$ 就是我们想要的。由于 $a_i$ 和 $b_i$ 的范围都太大了，所以我们稍微离散化一下，这样至多只有 $2n$ 个点了。

接下来考虑如何转移。我们枚举断点 $k$，表示要在 $k$ 处发射炮弹。那么我们肯定希望把能打死的敌人全部打死。因为，对于每一个敌人，我们至少要打他一下，所以枚举到 $k$ 的时候我们其实就假设了他是在这个时刻被打死的。

那么，最原始的做法就出来了：

$$
dp_{l, r} = \min_{l \le k \le r}dp_{l, k - 1} + \max_{l \le a_i \le k, k \le b_i \le r}d_i + dp_{k + 1, r}
$$

显然，这个做法是 $O(n^4)$ 的，当然超时。

我们可以发现，集合 $\{i|l \le a_i \le k, k \le b_i \le r\}$ 随着 $k$ 的增大只有两处边界值的元素发生了变化，于是我们可以用 set 来维护它，时间复杂度降到了 $O(n^3\log n)$。但是，仍然无法通过此题。

这个时候，我们考虑换个思路，不枚举 $k$，而是从按 $d$ 大到小的顺序枚举满足 $l \le a_i, b_i \le r$ 的区间 $[a_i, b_i]$，这个区间内若要发炮，必然是发一个半径为 $d_i$ 的，不过前面的区间枚举过的点就跳过。

这复杂度不又回到 $O(n^4)$ 了吗？我们回顾一下 [花神游历各国](https://www.luogu.com.cn/problem/P4145) 里面不用线段树（或树状数组）的玄学算法，那是用了路径压缩，而达到了 $O(n)$ 的复杂度。同样这个算法可以运用到本题，这样复杂度就是 $O(n^3)$ 了。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1005
#define MAXD 10005

struct Query
{
    int d, l, r;
} val[MAXN], cur[MAXN];

int dp[MAXN][MAXN];

int vis[MAXD];
int in[MAXN];

int nxt(int i) // 路径压缩
{
    return !vis[in[i]] ? in[i] : in[i] = nxt(in[i]);
}

int main()
{
    int n;
    int cc;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i <= MAXD; i++)
        {
            vis[i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> val[i].l >> val[i].r >> val[i].d;
            vis[val[i].l] = 1;
            vis[val[i].r] = 1;
        }
        sort(val + 1, val + n + 1, [](Query a, Query b)
             { return a.d > b.d; }); // 排序
        int c = 0;
        for (int i = 1; i <= MAXD; i++)
        {
            if (vis[i])
            {
                vis[i] = ++c;
            }
        }
        for (int i = 1; i <= n; i++) // 离散化
        {
            val[i].l = vis[val[i].l];
            val[i].r = vis[val[i].r];
        }
        for (int i = 1; i <= c; i++)
        {
            dp[i][i] = 0;
            for (int j = i + 1; j <= c; j++)
            {
                dp[i][j] = 0x3fffffff;
            }
        }
        for (int s = 2; s <= c; s++)
        {
            for (int l = 1; l + s - 1 <= c; l++)
            {
                cc = 0;
                int r = l + s - 1;
                for (int i = 1; i <= n; i++)
                {
                    if (l <= val[i].l && val[i].r <= r)
                    {
                        cur[++cc] = val[i];
                    }
                }
                if (!cc)
                {
                    dp[l][r] = 0;
                    continue;
                }
                for (int i = l; i <= r; i++)
                {
                    in[i] = i + 1;
                    vis[i] = 0;
                }
                vis[r + 1] = 0;
                for (int i = 1; i <= cc; i++)
                {
                    int md = cur[i].d;
                    if (!vis[cur[i].l])
                    {
                        dp[l][r] = min(dp[l][r], dp[l][cur[i].l - 1] + md + dp[cur[i].l + 1][r]);
                        vis[cur[i].l] = 1;
                    }
                    for (int k = nxt(cur[i].l); k <= cur[i].r; k = nxt(k))
                    {
                        dp[l][r] = min(dp[l][r], dp[l][k - 1] + md + dp[k + 1][r]);
                        vis[k] = 1;
                    }
                }
            }
        }
        cout << dp[1][c] << endl;
    }
    return 0;
}

```


---

## 作者：云浅知处 (赞：0)

简单题

首先把 $a_i,b_i$ 离散化，现在相当于这样的问题：

> 有一个序列和若干限制 $a_i,b_i,d_i$，表示序列的区间 $[a_i,b_i]$ 中的最大值至少为 $d_i$。
>
> 问序列中所有元素的和至少是多少。序列长度 $\le 600$。

考虑在笛卡尔树上 DP，设 $f(l,r)$ 表示只考虑区间 $[l,r]$ 以及该区间内的约束，要符合条件的最小代价。

转移时，枚举根节点的位置 $l\le x\le r$，预处理出 $\text{cost}(l,r,x)$ 表示满足 $l\le a_i\le x\le b_i\le r$ 的所有区间 $[a_i,b_i]$ 中 $d_i$ 的最大值，那么最优方案显然是在 $x$ 处填入 $\text{cost}(l,r,x)$。

接下来，跨越 $x$ 的区间的约束都已经被满足，可以转移至 $f(l,x-1)+f(x+1,r)$。

总的时间复杂度为 $O(n^3)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int N=605;
int f[N][N],n,m,st[N],ed[N],cost[N],val[N];
vector<int>lsh;
vector<pair<int,int> >vec[N];
const int INF=1e9;

#define mk make_pair
#define fi first
#define se second

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		st[i]=read(),ed[i]=read(),val[i]=read();
		lsh.emplace_back(st[i]),lsh.emplace_back(ed[i]);
	}
	sort(lsh.begin(),lsh.end());m=unique(lsh.begin(),lsh.end())-lsh.begin();lsh.resize(m);
	for(int i=1;i<=n;i++)st[i]=lower_bound(lsh.begin(),lsh.end(),st[i])-lsh.begin()+1;
	for(int i=1;i<=n;i++)ed[i]=lower_bound(lsh.begin(),lsh.end(),ed[i])-lsh.begin()+1;
	for(int i=1;i<=n;i++)vec[ed[i]].emplace_back(mk(st[i],val[i]));

	for(int i=0;i<=m;i++)for(int j=0;j<=m;j++)f[i][j]=INF;
	for(int i=1;i<=m;i++)f[i][i-1]=0;

	for(int i=m;i>=1;i--){
		memset(cost,0,sizeof(cost));
		for(int j=i;j<=m;j++){
			for(auto t:vec[j]){
				if(t.fi<i)continue;
				for(int x=t.fi;x<=j;x++)cost[x]=max(cost[x],t.se);
			}
			for(int x=i;x<=j;x++)f[i][j]=min(f[i][j],f[i][x-1]+f[x+1][j]+cost[x]);
		}
	}

	cout<<f[1][m]<<endl;

	lsh.clear();for(int i=1;i<=m;i++)vec[i].clear();
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	int tt=read();while(tt--)solve();

	return 0;
}
```

---

