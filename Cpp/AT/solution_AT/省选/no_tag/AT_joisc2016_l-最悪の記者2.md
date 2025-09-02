# 最悪の記者2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2016/tasks/joisc2016_l



# 题解

## 作者：Code_星云 (赞：5)

容易发现本题的条件构成了一个完美匹配。

一个很明显的思路是对于任意满足条件 $b_i < d_i$ 的对，若 $a_i=c_i$ 则将他们配对。但事实是这样贪心的选择后不一定能保证后面的对能构成完美匹配。

因此我们在每次配对的时候，要判断一下剩下的能不能构成一个完美匹配。然后就可以用霍尔定理来判断。

本题的连边比较特殊，我们发现连边都是向值更小的相连。因此我们考虑通过前缀来处理，然后把两块合并到一个序列上来处理。对于 $d_i$ 的前缀，根据霍尔定理，其相邻点集合大小要小于 $|d|$。因此我们用线段树来维护，对于 $b_i$，其值为 $1$；否则为 $-1$。然后要想判定后面是否能构成完美匹配，即对于任意前缀，其和都要非负。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> pii;
#define mid ((l(x) + r(x)) >> 1)
#define lc (x << 1)
#define rc (x << 1 | 1)
#define mp make_pair
#define px first
#define py second

const int N = 400005;
pii bar[N];
set<pii> s[N];
int n, id[N], reta[N], retb[N], vala[N], valb[N];

namespace sgtree{
	struct segtree{
		int l, r, sum, minpre;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define sum(x) tree[x].sum
		#define minpre(x) tree[x].minpre
	};
	segtree tree[N << 2];
	void pushup(int x){
		sum(x) = sum(lc) + sum(rc);
		minpre(x) = min(minpre(lc), sum(lc) + minpre(rc));
	}
	void build(int x, int l, int r){
		l(x) = l; r(x) = r;
		if(l == r){
			sum(x) = minpre(x) = (bar[l].py <= n ? 1 : -1);
			return;
		}
		build(lc, l, mid);
		build(rc, mid + 1, r);
		pushup(x);
	}
	void modify(int x, int p, int op){
		if(l(x) == r(x)){
			if(op == 1) sum(x) = minpre(x) = (bar[p].py <= n ? 1 : -1);
			else sum(x) = minpre(x) = 0;
			return;
		}
		if(p <= mid) modify(lc, p, op);
		else modify(rc, p, op);
		pushup(x);
	}
};
using namespace sgtree;

int main(){
	scanf("%d", &n); int ttmp;
	for(int i = 1; i <= n; i ++){
		scanf("%d %d", &ttmp, &vala[i]);
		s[ttmp].insert(mp(vala[i], i));
		bar[i] = mp(vala[i], i);
	}
	for(int i = 1; i <= n; i ++){
		scanf("%d %d", &id[i], &valb[i]);
		bar[i + n] = mp(valb[i], i + n);
	}
	sort(bar + 1, bar + 2 * n + 1);
	for(int i = 1; i <= 2 * n; i ++)
	  if(bar[i].py <= n) reta[bar[i].py] = i;
	  else retb[bar[i].py - n] = i;
	int ans = n;
	build(1, 1, 2 * n);
	for(int i = n; i >= 1; i --){
		set<pii>:: iterator k = s[id[i]].lower_bound(mp(valb[i], n + 1));
		if(k == s[id[i]].begin()) continue;
		k --;
		modify(1, reta[(* k).py], -1);
		modify(1, retb[i], -1);
		if(minpre(1) < 0){
			modify(1, reta[(* k).py], 1);
		    modify(1, retb[i], 1);
		    continue;
		}
		ans --; s[id[i]].erase(k);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：wcyQwQ (赞：3)

感谢 LJ07 不厌其烦地教了我三遍，终于懂了。

我们考虑对于每一个 $b_i$ 如何贪心地去匹配，首先我们肯定会贪心地选取一个 $d_j$ 最小的，满足 $a_i = c_j$，且 $j$ 还未被匹配的去和他匹配，如果不存在，我们可以随机匹配，但是随机配显然是错的，所以我们可以维护一个二分图  $G$，然后把这样的失配点丢进 $G$ 里面。所以我们每次给 $i$ 匹配的时候就相当于从 $G$ 中删去一个点 $j$。在进一步会发现，就算存在这样的 $j$，$i$ 也不一定能和他匹配，因为我们不确定删去了 $j$ 之后 $G$ 是否还存在完美匹配，根据 Hall 定理，等价于 $\min(|N(S)| - |S|) \ge 0$，更进一步，因为 $G$ 中每一个点都会向他所有前缀连边，所以我们其实不用取所有的 $S$，只需要判断前缀最小是否 $ \ge 0$ 即可，每次加入/删除一个点都会影响一个前缀的 $|N(S)| - |S|$，所以我们使用线段树区间加，区间最小值即可。时间复杂度 $O(n\log n)$。

[Code](https://loj.ac/s/1858802)

---

## 作者：fangzichang (赞：2)

想了想还是发一下，感觉总的讲还是不一样，可能不如并查集做法接近本质，但是绕过了其他做法的 Hall 定理和线段树，用一个奇思妙想反悔贪心实现了整个过程。  
膜拜 lgswdn 大神。  

---

做法应该算是相当简洁。如果你只希望快速学会做法，可以跳过引用格式标注出来的证明部分。  

将比赛过程中的人称为左部点，用 $i\in [1,n]$ 指代某个左部点，同样用 $j$ 指代右部点也即比赛结束后的人。  

> 引理 1：只需更改左部点颜色 $A_i$ 即可满足题目所给条件。  
> 证明考虑最优解中的每一对匹配都至多有一个是被改变过的；并且对于任何更改右部点使颜色匹配左部点的情况，都容易不花费额外代价调整至更改左部点的情况，这是对称的。

因而我们需要求一个二分图完美匹配，每一对匹配的 $(i,j)$ 满足 $B_i\le D_j$，在此基础上最小化 $\sum [A_i\ne C_j]$。

首先贪心，简单地把所有左部点按照 $B_i$ 降序排序，如果能不更改 $A_i$ 就找到匹配，也即存在未匹配的右部点 $j$ 满足 $A_i=C_j\land B_i\le D_j$，就把 $i$ 和 $D_j$ 最小的 $j$ 匹配起来。这样两边都可能剩下一些没配上的点。  
用 `set` 简单实现。

```cpp
for(int i=1;i<=n;i++)
  cin(a[i],b[i]),p.pb(i);
for(int i=1;i<=n;i++)
  cin(c[i],d[i]),s[c[i]].insert(d[i]);
sort(all(p),[](int i,int j){return b[i]>b[j];});
for(int i:p){
  auto it=s[a[i]].lower_bound(b[i]);
  if(it!=s[a[i]].end())
    q.pb(pii(*it,b[i])),s[a[i]].erase(it);
    //匹配上 i 和 it 对应的右部点，这对匹配放进集合里面备用
  else
    f.push(b[i]);//i 是没配上的左部点，放进大根堆里面备用
}
```

大概看个意思就行了。  

> 引理 2：没配上的点的颜色无关紧要。  
> 粗略理解的话，右部点反正等着被匹配到就好了，没配上的左部点反正是要改颜色了。  

然后继续贪心。考虑每一步都找出 $B_i$ 最大的没配上的左部点，在没配上的右部点里面找 $B_i\le D_j$ 且最小的 $D_j$，把 $i$ 和 $j$ 匹配。因为前面的贪心排序过了，所以这一步必然需要更改 $i$ 的颜色，对答案有 $1$ 的贡献。这样进行若干轮。  

```cpp
for(int i=1;i<=n;i++)
  for(int v:s[i])t0.insert(v);//t0 放了所有没配上的右部点的值
for(int w;!f.empty();res++){
  w=f.top(),f.pop();
  auto it=t0.lower_bound(w);
  if(it!=t0.end())
    t0.erase(it);
  else
    //不知道怎么办
}
```

当然问题出现了，可能找不到 $B_i\le D_j$ 的 $j$。 

所以引入一个反悔操作。拆散一对匹配上了的 $(k,j) (B_i\le D_j)$，然后把 $i$ 和 $j$ 匹配，对答案产生 $1$ 的贡献，最后将 $k$ 设为没配上，插入大根堆里面等下继续第二轮贪心。  

> 引理 2（续）：反悔没有破坏性质，这次一定会产生 $1$ 的贡献，$i$ 和 $j$ 颜色必定不同。  
> 留作课后习题。

考虑拆散哪一对。  

> 引理 3：拆散的匹配颜色一定相同，也即是第一轮贪心中给出的匹配。  
> 引理 4：拆散的匹配中 $B_k$ 一定不大于 $B_i$，而且一定能找到这样一对匹配。  
> 其实有引理 4 就有引理 2 和 3 了。使用费用流建模，结合保证有解的题目条件，可以证明这几个。

引理 2 告知我们，被拆散的匹配的颜色也将无关紧要，所以只需要在拆了有用的匹配里面找 $B_i$ 最小的就行了。  
具体地，将所有的不产生贡献的匹配 $(k,j)$ 按照 $D_j$ 从大到小排序，当前可以拆的匹配是一个前缀。因为大根堆中取出的值是降序的，所以用一个单调递增的指针维护这个前缀，每次将 $B_k$ 放入一个小根堆中表示这些是可选的被拆的左部点，需要拆匹配的时候取堆顶即可。  

（我写了好多字讲一个简单的过程！该加训语言表达了。）  

```cpp
for(int w;!f.empty();res++){
  w=f.top(),f.pop();
  for(static auto it=q.begin();
    it!=q.end()&&it->x>=w;it++)t1.push(it->y);
  auto it=t0.lower_bound(w);
  if(it!=t0.end())
    t0.erase(it);
  else
    f.push(t1.top()),t1.pop();
}
```

等有时间了补一个模拟费用流的证明。    
[full code](https://loj.ac/s/2314320)

---

## 作者：XuYueming (赞：2)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_joisc2016_l)；[AtCoder](https://atcoder.jp/contests/joisc2016/tasks/joisc2016_l)。

**强烈建议去[我的博客](https://www.cnblogs.com/XuYueming/p/18697527)阅读获得更好的阅读体验，因为那里有折叠块，更好地划分文章层级，这里我仅做简单的加粗替换。**

## 形式化题意

~~建议阅读原题面。~~

给定长度为 $n$ 的序列 $a, b, c, d$，求最少修改多少次 $a_i$，使得存在一个排列 $p$，满足 $a_i=c_{p_i} \land b_i \leq d_{p_i}$。

$n \leq 2 \times 10^5$，$b, d$ 单减，保证有解。

## 题目分析

首先你必须分析出来，这是一个最大权二分图完美匹配问题，不然连最基础的状压都不会写，然后爆零（当然说的是我自己）。

考虑把 $X_i = (a_i, b_i)$ 看做左部点，$Y_j = (c_j, d_j)$ 看做右部点，所有满足 $b_i \leq d_j$ 的 $X_i, Y_j$ 之间连边，边权是 $[a_i \neq c_j]$，我们所求的就是最小花费完美匹配。

考虑状压 DP。记 $f_{S}$ 表示右部点匹配上的点集为 $S$，和前 $|S|$ 个左部点匹配，最小的花费是多少。初始 $f_\varnothing = 0$，答案是 $f_Y$。转移的时候，每次选取一个点转移即可：$f_{S\cup\{Y_i\}} \gets \min \Big\{f_{S\cup\{Y_i\}}, f_S + [a_{|S|+1} \neq c_i]\Big\}$。时间复杂度 $\mathcal{O}(n2^n)$。

以上是~~我没写出来的~~部分分。我们考虑直接跑 KM 算法求是 $\mathcal{O}(n^3)$，不太行。那么说明这个二分图一定有特殊的性质，因为如果是一般的二分图的话，我们会的算法 KM 已经最快了。（费用流显然也不太对。）

我们猜测一下算法，肯定需要贪心。我们不妨按照某一个顺序枚举右部点，尝试把它通过一条 $0$ 边和某一左部点匹配。

**性质一**：

对于一个右部点 $Y_i$，通过一条边权为 $0$ 边，尝试和 $b_j$ 大的 $X_j$ 配对，肯定不劣。我们将这个匹配的 $X_j$ 记作 $\pi(i)$。

**证明**：

$b_j$ 大小关乎 $X_j$ 与多少右部点有边，显然 $b_j$ 小的连出的边更多。倘若我们选择了 $b_j$ 更小的 $X_j$，一定可以将其替换为满足 $b_{j'}\geq b_j$ 的 $X_{j'}$，而替换下来的 $X_j$ 留着可能和别的右部点匹配，从而不劣。

我们能匹配就让他们匹配上。这么做是对的基于所有点的贡献相同，如果我们按照一个恰当的顺序贪心，如果现在不进行匹配，之后让别的点和 $X_j$ 匹配不会让答案更优，所以这么贪心是不劣的。

接下来思考，什么时候我们发现他们不能匹配呢？倘若匹配他们后，把它们删去，剩下的图还不能形成一个完美匹配，那我们就不能让他们匹配。

是否存在完美匹配？这是一个很典的问题。

**定理一：Hall's marriage theorem（霍尔定理）**：

**引用**：[wikipedia](https://en.wikipedia.org/wiki/Hall%27s_marriage_theorem)

Hall's condition is that any subset of vertices from one group has a neighbourhood of equal or greater size.

即，一张二分图是否存在完美匹配的充要条件是，对于左部点 / 右部点的任意子集的邻居点集（有边相连的右部点 / 左部点）大小不小于该子集的大小。不妨将该条件称作 Hall 判定条件。

**Necessity Proof**：

假设二分图 $G = (X\sqcup Y, E)$ 存在完美匹配 $M\subseteq E$，那么 $\forall S \subseteq X$，记 $T = \Big\{y\in Y \mid x\in S \land(x, y)\in M \Big\}$，记 $S$ 的邻居 $N_G(S) = \Big\{y\in Y \mid x\in S \land(x, y)\in E \Big\}$，由于 $M \subseteq E$，我们有 $T \subseteq N_G(S)$，故 $|N_G(S)|\geq|T|=|S|$。对于 $Y$ 同理。必要性证毕。

**Sufficiency Proof**：

归纳证明。对于 $|X| = 1$，显然成立。假设 $|X|<n$ 命题成立，对于 $|X|=n>1$，分如下两类讨论：

1. $\forall S\subseteq X, N_G(S) \geq |S|+1$：
  将任意 $x\in X$ 与任意 $y\in N_G(\{x\})$ 匹配，剩下的子图 $G'$ 依然满足命题条件，而 $X' = X \setminus \{x\}$，根据归纳假设，成立。
1. $\exists S\subseteq X, N_G(S) = |S|$：
  将 $S$ 与 $N_G(S)$ 组成 $|S|$ 组匹配，剩下的子图 $G'$ 依然满足命题条件（倘若 $\exists S' \subseteq X', |N_{G'}(S')| < |S'|$，则 $N_G(S\cup S')=N_G(S)\cup N_{G'}(S')$，从而有 $|N_G(S\cup S')|<|S\cup S'|$，与假设矛盾），故根据归纳假设，成立。

对于任意子集的话……难道我们要枚举子集？显然不现实。这时候，似乎需要用到这个二分图的一些性质了。

**性质二**：

我们发现，对于一个左部点 $X_i$，它所连的右部点是一段前缀，不妨设为 $Y_1\sim Y_{p_i}$，这个可以用双指针处理。类似同理，右部点连到的左部点总是一段后缀。

**证明**：

证明显然，自证不难。

这个性质很自然得到，有什么用呢？

**性质三**：

我们考虑一个右部点的子集 $S$，记 $Y_{y_0} = arg \max\limits_{Y_i\in S} d_i$，$S'=\operatorname{suf}(y_0)=\{Y_i\mid d_i \leq d_{y_0}\}$。

**我怎么听不懂你在讲什么？**

如果我们把左右部点，分别按照 $b, d$ 从小到大的顺序，从上到下排列，$Y_{y_0}$ 就是 $S$ 中最靠上的点，$S'$ 就是 $Y_{y_0}$ 及以下的右部点构成的点集（不妨将 $Y_i$ 及以下的右部点构成的点集记作 $\operatorname{suf}(i)$）。

$S'$ 满足 Hall 判定条件是 $S$ 满足 Hall 判定条件的充分条件。因为 $S'$ 相比 $S$，邻居没变 $N_G(S') = N_G(S) = N_G(\{Y_{y_0}\})$，而 $|S'| \geq |S|$。

如此，我们把需要判定的子集个数由 $2^n$ 简化至 $n$ 个后缀。原问题似乎变得十分可做。慢着，我们还有一个问题一直没有解决，那就是按照什么顺序枚举右部点呢？

先说结论：按照 $d_i$ 从小到大枚举，即按照下标从后往前枚举右部点。

**证明**：

我们考虑 $c_i = c_j \land d_i \geq d_j$ 的右部点 $Y_i,Y_j$，且有 $\pi(i) = \pi(j) = \pi_0$。让 $Y_j$ 和 $\pi_0$ 匹配，而不是 $Y_i$ 和 $\pi_0$ 匹配，原因是，两者唯一的差别就是考虑 $d_k\in(d_j, d_i)$ 的 $Y_k$，$\operatorname{suf}(k)$ 在 $Y_j$ 和 $\pi_0$ 匹配后，我们会删去 $Y_j$ 这个右部点，而无论是 $Y_i / Y_j$ 和 $\pi_0$ 匹配，$N_G\Big(\operatorname{suf}(k)\Big)$ 不变。导致让 $Y_j$ 先匹配，$Y_k$ 更有可能满足 Hall 判定条件。

至于 $\pi(i)$ 的维护，对每种 $a_i/c_i$ 开一个栈，然后双指针即可。我们可以写出如下 $\mathcal{O}(n^2)$ 代码。（由于不支持折叠块，请移步[我的博客](https://www.cnblogs.com/XuYueming/p/18697527)。）

那么我们需要优化的部分就是 `check` 了。

我们考虑将判定条件 $\forall i, \Bigg|N_G\Big(\operatorname{suf}(i)\Big)\Bigg|\geq|\operatorname{suf}(i)|$ 移项变为 $\forall i, \Bigg|N_G\Big(\operatorname{suf}(i)\Big)\Bigg|-|\operatorname{suf}(i)|\geq 0$，用数据结构维护左侧式子，为了方便叙述，将式子表示为 $\forall i, u_i - v_i \geq 0$。

发现我们在匹配 $\pi(i), Y_i$ 时，将 $Y_1 \sim Y_{p_{\pi(i)}}$ 的 $u$ 减了一，将 $Y_1\sim Y_{i-1}$ 的 $v$ 减少了一。至于之后 `check` 的时候不考虑 $Y_i$，可以直接将 $u_i \gets \infty$。或者除了上述操作，将 $Y_i$ 的 $v$ 也减一，就不需要特殊处理 $Y_i$。

**证明**：

感性理解一下。由于 $Y_1 \sim Y_{p_{\pi(i)}}$ 包含了 $Y_i$，再把 $v_i$ 减一相当于它 $u_i, v_i$ 都不变。考虑 $v_i = v_{i+1} + 1$，我们又有 $u_i-v_i=u_i-1-v_{i+1}$，而 $u_i-1\geq u_{i+1}$，所以 $Y_i$ 和后缀里某个点等价，如果不合法，后缀某个点会出现问题。

于是，我们可以使用一棵线段树，方便地执行区间加减操作，查询全局的最小值，看看如果 $\geq 0$ 就合法，否则不合法。

时间复杂度：$\mathcal{O}(n \log n)$。瓶颈在于线段树维护区间加减一，全局最值查询，和 [这题](https://www.cnblogs.com/XuYueming/p/18370812) 最后瓶颈相同。

## 代码

状压、暴力 `check`、正解代码见[我的博客](https://www.cnblogs.com/XuYueming/p/18697527)。

---

## 作者：论文 (赞：2)

**结论**：苯题疑似存在 $O(n)$ 做法。

考虑 $2$ 小时的人 $X$ 匹配了哪个 $5$ 小时的人 $Y$。不妨认为 $X_i$ 的分数 **不比** $X_{i+1}$ 的分数 **低**，$Y$ 同理。

$X_i$ 能匹配的 $Y_j$ 的 $j$ 构成一个区间 $j\in \left[1,f_i\right]$。容易发现 $i\le f_i\le f_{i+1}$。

这些分界线自然地把 $Y$ 序列划分成了若干个块。

定义 $Y_i$ 属于块 $k$，当且仅当 $k$ 满足 $f_{k-1}+1\le i\le f_{k}$，并记 $B_i=k$，$siz_k=f_{k}-f_{k-1}$，初始时 $cnt_{k}=0$。

由于求的是最多的匹配数量，容易发现存在最优解，方案是：根据 $i$ 从小到大考虑，如果可以在 $[1,f_i]$ 中找到未匹配的人并且国籍相同的人，就直接匹配。

考虑当前考虑 $X_i$ 匹配的是谁。记目前划分出来的标号最大的块的标号为 $num$。为了行文方便，**暂时** 先用 `std::multiset` $S$ 来储存 $\left[1,f_i\right]$ 未匹配的人 $Y$。

现在考虑在 $S$ 中找一个人 $Y_j$ 使得国籍和 $X_i$ 相同，并且所属于的块标号最大。

- 操作 $1$：当找到这样的人 $Y_j$，在块 $B_{j}$ 上插一个匹配旗，并且执行赋值语句 $cnt_{B_j}\leftarrow cnt_{B_j}+1$，把 $B_j$ 从 $S$ 中删除。

- 操作 $2$：当找不到这样的人 $Y_j$，就在块 $num$ 上插一个占座旗，并且执行赋值语句 $cnt_{num}\leftarrow cnt_{num}+1$。它的意义是要在 $[1,f_{i}]$ 中留一个人给它匹配，因此它实际上可以放在块 $1,2,\cdots,num$ 中的任意一个可以放的块里边。

当上面的赋值语句中使得 $cnt_{x}=siz_x+1$，肯定是块 $x$ 里占座旗过多，考虑将其中一个占座旗移动到前面的块，给新加进来的这个旗子让出位置，从而使得 $cnt_x$ 依然和 $siz_x$ 相等；如果无法把占座旗放进前面的块，也就是无法把占座旗继续往前移，那么可以判定找到的这个人 $Y_j$ 必定是被前面的人给占了。因此将这个人从 `multiset` 中删除，继续在 $S$ 中找人。

这个算法已经可以找出正确答案了。最后，来优化一下上面算法里复杂度比较高的地方。

- 第一个是找块 $x$ 前边没满的块。维护一个 $pre$ 数组，用 $pre_x$ 代表 $x$ 的上一个块。如果某个块已经满了，那么后边也用不到了，因此可以 **路径压缩**。总共时间 **据有位高手说** 是 $O(n)$。

- 第二个是使用 `std::multiset` 多出来的 $\log$ 因子。由于国籍最多 $O(n)$ 个，用 $O(n)$ 个栈去记某个国籍、还没被删掉的人 $Y$，对应的块的标号。总共时间也是 $O(n)$。

输入时 $X,Y$ 已经分别有序了，因此也不必排序。总复杂度就是 $O(n)$ 了。

[在 LOJ 上的提交](https://loj.ac/s/1424399)。目前在 AT 和 LOJ 上均为最优解，但俺不太会证这个路径压缩的复杂度，以后会了再补上，或者等一个高手来指点指点俺吧。



---

## 作者：Graphcity (赞：1)

考虑贪心。首先转化一下问题，最少的修改对数变为最多的匹配对数。

从小往大枚举 $i$，利用双指针找到所有 $>B_i$ 的是总榜的前多少名，同时维护每种颜色的集合 $Q_i$。

观察一：当前能匹配则匹配。与其留给后面去匹配，现在匹配的贡献是不变的，结果必然不劣。

观察二：匹配时，应该匹配当前颜色集合中 $D_i$ 最小的数。因为我们要把较大的 $D_i$ 留出去给其他数。

这样我们就能够唯一确定每个位置的匹配情况。但是还有未被匹配成功的数，我们必须要留一些位置给它们，这些位置的排名还必须要小于某个值。

如果存在一个数 $k$，满足所有 $\ge k$ 的 $D_i$ 中要么被匹配过了，要么恰好被未匹配的数填满，那么所有 $\ge k$ 的位置都被废掉了。废掉的数要从颜色集合中删除。线段树可以方便维护这些位置。颜色集合则可以用单调队列维护。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,cnt,ans,tag[Maxn*4+5];
int A[Maxn+5],B[Maxn+5],C[Maxn+5],D[Maxn+5],sum[Maxn+5];
deque<int> q[Maxn+5];

struct Node{int k,x;} t[Maxn*4+5];
inline Node operator+(Node a,Node b) {Node c; c.k=min(a.k,b.k),c.x=(b.k==c.k?b.x:a.x); return c;}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
inline void push_up(int p) {t[p]=t[ls(p)]+t[rs(p)];}
inline void mk(int p,int k) {t[p].k+=k,tag[p]+=k;}
inline void push_down(int p) {if(tag[p]) mk(ls(p),tag[p]),mk(rs(p),tag[p]),tag[p]=0;}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=Node{l,l}; return;}
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {mk(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p);
}

int main()
{
    n=read(),Build(1,n,1);
    For(i,1,n) A[i]=read(),B[i]=read();
    For(i,1,n) C[i]=read(),D[i]=read();
    for(int i=1,it=0;i<=n;++i)
    {
        while(it<n && B[i]<=D[it+1]) it++,q[C[it]].push_back(it);
        if(!q[A[i]].empty())
        {
            int x=q[A[i]].back(); q[A[i]].pop_back();
            Modify(1,n,x,n,1,-1),ans++;
        } else Modify(1,n,it,n,1,-1);
        if(!t[1].k)
        {
            int p=t[1].x; while(m<p)
            {
                m++,cnt+=sum[m];
                if(!q[C[m]].empty() && q[C[m]].front()==m) q[C[m]].pop_front();
            }
        }
    }
    cout<<n-ans<<endl;
    return 0;
}
```



---

## 作者：Vidoliga (赞：0)

赛时乱搞做法，然后没开可重集被卡成 $90$。

当然这题并不需要开可重集。

考虑费用流建模，如果把 $(c_i,d_i)$ 二元组合当成左部点，把 $(a_i,b_i)$ 当成右部点。

然后由于要求一一对应且 $d_{p_i} \geq b_i$，所以可以将 $(o,d_i)$ 连向 $\forall p \in [0,d_i], (o,p)$，费用为 $0$，流量为 $1$。对于 所以可以把同类的 $(o,d_i)$ 连向 $\forall g \not = o,p \in [0,d_i], (g,p)$，费用为 $1$，流量为 $1$。

然后跑最小费用最大流可以做到 $O(n^3)$。

一眼这东西不好搞，直接考虑一些可行策略。

考虑贪心策略，把尽可能多的点不改变类型，也就是贪心的选比当前值大的最小数，如果没有，则必然改变类型，否则贪心选取。

然而显然要求的是对于你选择的决策 $S$，你必然需要满足决策 $S$ 满足存在完美匹配。

然而显然上述贪心不一定能满足存在完美匹配。

那每次贪心的时候判断存在完美匹配，考虑其正确性。

首先感性得理解，不难发现由于已经从大到小排序，选择比当前数大的最小决策一定不会影响后面同类的决策。

然后考虑用拟阵证明：

考虑 $M=(S,L)$ 的拟阵，考虑 $L$ 是 完美匹配的子集，$S$ 是边集。

考虑 $w(x)$ 为同类连边是 $0$，否则为 $1$。

考虑 $L$ 是否满足遗传性和交换性，不难发现子集显然满足遗传性，而交换性也不难得出。

所以按照 $w(x)$ 递减排序，显然是对的。但是照着贪心复杂度不太能接受，毕竟边集是 $O(n^2)$，考虑右部点固定时只能选一条边，固考虑用一条最优边来判断。考虑取大的最小值的左部点显然在固定右部点时，存在完美匹配的可能性更高，即如果判定出不存在完美匹配，则所有 $w(x)=0$ 且为当前右部点的边集都不能选，否则选择这条边仍然能去除当前右部点的边集。

然后还有点问题，$w(x)=1$ 的边怎么办，很简单，其实只用计数 $w(x)=0$ 的边取的最多边数，然后总数减去选择的右部点点数即可。

考虑完美匹配怎么判，不难想到hall定理，考虑连边的特殊性，连边为一段前缀，那可以判断值域的前缀大小关系。

这个可以做差，维护全局最小值，删边可以在线段树上做。

复杂度 $O(n \log n)$。

```cpp
signed main(){
    //fprintf(stderr,"%.3lfMB\n",(&test2-&test1)/1048576.0);
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),h[++tot]=b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read(),h[++tot]=d[i]=read();
    sort(h+1,h+tot+1);tot=unique(h+1,h+tot+1)-h-1;
	for(int i=1;i<=n;i++) b[i]=lower_bound(h+1,h+tot+1,b[i])-h;
	for(int i=1;i<=n;i++) d[i]=lower_bound(h+1,h+tot+1,d[i])-h;
	// for(int i=1;i<=n;i++) printf("%lld ",b[i]);puts("");
	// for(int i=1;i<=n;i++) printf("%lld ",d[i]);puts("");
    for(int i=1;i<=n;i++) st[c[i]].insert(d[i]);
    for(int i=1;i<=n;i++) t.update(1,1,tot,d[i],tot,-1),t.update(1,1,tot,b[i],tot,1);
    int res=0;
    for(int i=1;i<=n;i++){
        
        auto u=st[a[i]].lower_bound(b[i]);
        if(u==st[a[i]].end()) res++;
        else{
            int p=*u;t.update(1,1,tot,p,tot,1),t.update(1,1,tot,b[i],tot,-1);
            if(t.mn[1]>=0){st[a[i]].erase(u);}
            else{
                t.update(1,1,tot,p,tot,-1),t.update(1,1,tot,b[i],tot,1);
                res++;
            }
        }
    }
    printf("%d\n",res);
    return 0;
}
```


---

