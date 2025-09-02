# Wine Factory (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

There are three arrays $ a $ , $ b $ and $ c $ . $ a $ and $ b $ have length $ n $ and $ c $ has length $ n-1 $ . Let $ W(a,b,c) $ denote the liters of wine created from the following process.

Create $ n $ water towers. The $ i $ -th water tower initially has $ a_i $ liters of water and has a wizard with power $ b_i $ in front of it. Furthermore, for each $ 1 \le i \le n - 1 $ , there is a valve connecting water tower $ i $ to $ i + 1 $ with capacity $ c_i $ .

For each $ i $ from $ 1 $ to $ n $ in this order, the following happens:

1. The wizard in front of water tower $ i $ removes at most $ b_i $ liters of water from the tower and turns the removed water into wine.
2. If $ i \neq n $ , at most $ c_i $ liters of the remaining water left in water tower $ i $ flows through the valve into water tower $ i + 1 $ .

There are $ q $ updates. In each update, you will be given integers $ p $ , $ x $ , $ y $ and $ z $ and you will update $ a_p := x $ , $ b_p := y $ and $ c_p := z $ . After each update, find the value of $ W(a,b,c) $ . Note that previous updates to arrays $ a $ , $ b $ and $ c $ persist throughout future updates.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. Even though there are $ 2 $ liters of water remaining, only $ 1 $ liter of water can flow into tower 4.
- When $ i = 4 $ , there are $ 4 $ liters of water in tower 4. All $ 4 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 4 = 11 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [5, 1, 1] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. Even though there are $ 6 $ liters of water remaining, only $ 1 $ liter of water can flow to tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. Even though there are $ 2 $ liters of water remaining, only $ 1 $ liter of water can flow into tower 4.
- When $ i = 4 $ , there are $ 4 $ liters of water in tower 4. All $ 4 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 4 = 8 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [5, 1, 0] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. Even though there are $ 6 $ liters of water remaining, only $ 1 $ liter of water can flow to tower 3.
- When $ i = 3 $ , there is $ 1 $ liter of water in tower 3 and $ 0 $ liters of water is turned into wine. Even though there is $ 1 $ liter of water remaining, no water can flow to tower 4.
- When $ i = 4 $ , there are $ 3 $ liters of water in tower 4. All $ 3 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 3 = 5 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
5 2 1
4 3 8 1000000000
2 5 1 1
3 0 0 0```

### 输出

```
11
8
5```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
6 5 9 2
5 4 9 1
1 1 1 1
2 7 4 8
4 1 1 1
1 8 3 3```

### 输出

```
31
25
29
21
23```

# 题解

## 作者：wrhaco (赞：22)

好想又好写的分块做法。

考虑对序列分块，对于每一块内，维护以下几种东西：

$w_i$ 表示不考虑前面的块流过来的水时，第 $i$ 块产生的酒量。

$f_i$ 表示不考虑前面的块流过来的水时，第 $i$ 块会向下一块流多少水。

上面两种可以根据题意直接递推求出。

```cpp
w[i]+=min(f[i]+a[j],b[j]);
f[i]=min(c[j],max(0ll,f[i]+a[j]-b[j]));
```
接下来需要考虑前面的块流过来的水产生的贡献，可以分成三类：

1.在这一块中变成酒。设 $s_i$ 表示第 $i$ 块中 $b$ 的总和，容易发现这部分的贡献的上界为 $s_i - w_i$.

2.继续流到下一块。没有在第一种贡献中变成酒，也没有超出管道流量限制的水会继续流到下一块。

3.被管道拦截住。水被管道流量 $c_i$ 限制住，不会产生任何贡献。

可以对每一块维护 $g_i$ 表示在被管道拦截之前能够造成贡献的水量上限。将前面流过来的水量总和与 $g_i$ 取 min，然后分别计算前两种贡献产生的影响即可。

$g_i$ 可以对每一根管道分别求出前面转化成酒的水量和继续流到后面的水量之和，然后对块内所有管道的限制取最小值。

```cpp
g[i]=min(g[i],(sumb[i]-w[i])+(c[j]-f[i]));
```

计算答案时可以额外记录一个变量 $S$ 统计前面所有块流到当前位置的水量总和，然后枚举所有整块，根据块内维护的三种信息更新 $S$ 并统计答案。

```cpp
for(int i=1;i<=N;i++){
	S=min(S,g[i]);
	int x=min(S,sumb[i]-w[i]);
	ans+=x,S-=x;
	ans+=w[i],S+=f[i]; 
} 
```

由于每个块的信息都是独立的，每次修改可以直接修改 $a,b,c$ 数组然后暴力重构修改位置所在的块。

复杂度 $O(n \sqrt n)$ , 几乎没什么常数，在 CF 上可以轻松通过。

完整代码：

```cpp
inline void build(int i){
	int L=(i-1)*B+1,R=min(n,i*B);
	w[i]=f[i]=sumb[i]=0,g[i]=INF;
	for(int j=L;j<=R;j++){
		sumb[i]+=b[j];
		w[i]+=min(f[i]+a[j],b[j]);
		f[i]=min(c[j],max(0ll,f[i]+a[j]-b[j]));
		g[i]=min(g[i],(sumb[i]-w[i])+(c[j]-f[i]));
	}
	return;
}
void solve(){
	init();
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	for(int i=1;i<n;i++) c[i]=read();
	int N=(n-1)/B+1;
	for(int i=1;i<=N;i++) build(i);
	while(q--){
		int pos=read();
		a[pos]=read(),b[pos]=read(),c[pos]=read();
		build((pos-1)/B+1);
		int ans=0,S=0;
		for(int i=1;i<=N;i++){
			S=min(S,g[i]);
			int x=min(S,sumb[i]-w[i]);
			ans+=x,S-=x;
			ans+=w[i],S+=f[i]; 
		} 
		printf("%lld\n",ans);
	} 
	return;
}
```

---

## 作者：henrytb (赞：13)

考虑用线段树直接维护。发现合并两个区间，相当于将左区间的冗余水经过两区间之间的水管导向右区间。

于是维护区间的以下信息即可：

- 当前答案。
- 当前冗余水量（即到达了区间右端点的没有变成酒的水量）。
- 当前剩余可变酒空间（即假如从这个区间左边流入了一些水，最多有多少可以变成酒）。
- 当前在剩余可变酒空间耗尽后，有多少水可以变成冗余水量（即假如从区间左边流入的水将变酒空间耗尽后，还有多少能流到这个区间的右端点）。

合并两个区间时，将左区间的冗余水量贡献给右区间，看能填满多少右区间的可变酒空间，以及假如填满了之后能否变为大区间的冗余水量等等细节即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 5e5 + 5;
int n, a[N], b[N], c[N], q;
struct Segment {
    int l, r, sum, rem, can, nowcan;
    // sum: now ans
    // rem: remain -> sum
    // can: > rem can deliver more?
    // nowcan: delivering
    friend Segment operator + (const Segment &lhs, const Segment &rhs) {
        Segment res; res.l = lhs.l; res.r = rhs.r;
        res.sum = lhs.sum + rhs.sum;
        int btn = c[lhs.r];
        int nowcanr = min(btn, lhs.nowcan);
        if (nowcanr > rhs.rem) {
            res.sum += rhs.rem;
            res.nowcan = min(nowcanr - rhs.rem, rhs.can);
            res.rem = lhs.rem;
            res.can = min(lhs.can, min(btn - nowcanr, rhs.can - res.nowcan));
            res.nowcan += rhs.nowcan;
        } else {
            res.sum += nowcanr;
            res.nowcan = rhs.nowcan;
            res.rem = lhs.rem + min(lhs.can, min(rhs.rem - nowcanr, btn - nowcanr));
            res.can = rhs.rem <= btn && rhs.rem - nowcanr <= lhs.can ? min(min(btn - nowcanr, lhs.can) - rhs.rem + nowcanr, rhs.can) : 0;
        }
        return res;
    }
} t[N << 2];
void pushup(int p) {
    t[p] = t[p << 1] + t[p << 1 | 1];
}
void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r;
    if (l == r) {
        if (a[l] > b[l]) {
            t[p].sum = b[l];
            t[p].can = 1e18;
            t[p].nowcan = a[l] - b[l];
        } else {
            t[p].sum = a[l];
            t[p].rem = b[l] - a[l];
            t[p].can = 1e18;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
void modify(int p, int pos) {
    if (t[p].l == t[p].r) {
        if (a[t[p].l] > b[t[p].l]) {
            t[p].sum = b[t[p].l];
            t[p].rem = 0;
            t[p].can = 1e18;
            t[p].nowcan = a[t[p].l] - b[t[p].l];
        } else {
            t[p].sum = a[t[p].l];
            t[p].rem = b[t[p].l] - a[t[p].l];
            t[p].can = 1e18;
            t[p].nowcan = 0;
        }
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if (pos <= mid) modify(p << 1, pos);
    else modify(p << 1 | 1, pos);
    pushup(p);
}
signed main() {
    scanf("%lld%lld", &n, &q);
    rep(i, 1, n) scanf("%lld", &a[i]);
    rep(i, 1, n) scanf("%lld", &b[i]);
    rep(i, 1, n - 1) scanf("%lld", &c[i]);
    build(1, 1, n);
    rep(i, 1, q) {
        int p, x, y, z;
        scanf("%lld%lld%lld%lld", &p, &x, &y, &z);
        a[p] = x; b[p] = y; c[p] = z;
        modify(1, p);
        printf("%lld\n", t[1].sum);
    }
    return 0;
}
```

---

## 作者：Lucky_Xiang (赞：5)

## 题目

[CF1919F2](https://www.luogu.com.cn/problem/CF1919F2)

## 分析

首先，题目可以转化为网络流。具体的，连三种边：

1. 连 $S\to i$ 的边，边权为 $a_i$（A 类边）。
2. 连 $i\to T$ 的边，边权为 $b_i$（B 类边）。
3. 连 $i\to i+1$ 的边，边权为 $c_i$（C 类边）。

但是，硬跑网络流肯定是不行的，考虑转化为最小割。可以分析这个图的性质。

**性质：在最小割中，对于一个点 $i$，它的 A 类边和 B 类边恰好被割掉一条**。

> 证明：
> - 如果都不割，则存在 $S\to i\to T$ 的路径，不是割。
> - 如果都割掉，分两种情况讨论：
>   1. 如果存在 $S\to i$ 的路径，则不割掉 A 类边一定不劣。
>   2. 如果不存在 $S\to i$ 的路径，则不割掉 B 类边一定不劣。

于是可以用线段树维护贡献。每个节点中记录四个值，分别记录区间**最左端**和**最右端**割掉的是哪种边时的最小割。区间合并时，如果**左区间**的**最右端**割掉的是 B 类边，且**右区间**的**最左端**割掉的是 A 类边，则需要**额外割掉**连接它们的 C 类边。

## 代码

[Code](https://codeforces.com/contest/1919/submission/240762235)

---

## 作者：qiuzx (赞：5)

upd：复杂度写错了，是 $O(n\log n)$。

官方题解和大部分做法都是最大流转最小割。这里给出一种只需要会画图和线段树就可以完成的做法。

## 题意

有 $n$ 个水桶中间连 $n-1$ 条水管，每条水管的容量为 $c_i$。现在从第 $1$ 个水桶开始，每次先往当前水桶加 $a_i$ 的水，倒掉 $b_i$ 的水，然后将 $c_i$ 的水移到下一个水桶。重复这个过程直到倒掉第 $n$ 个桶的水为止。这中间如果有任何一步不够了就全部拿走。需要支持 $q$ 次单点修改 $a_i,b_i,c_i$，每次要回答这个过程中一共倒掉的水量。$n,q\le 5\times 10^5$。

## 思路

先考虑没有 $c_i$ 怎么做。维护一个折线图状物，横坐标表示事件，纵坐标表示剩余总水量。那么一次 $(a_i,b_i)$ 的操作就相当于先向上走 $a_i$，再向下走 $b_i$，然后和 $0$ 取 $\max$，最后所有向下走的距离之和就是答案。这个和 $0$ 取 $\max$ 不方便使用数据结构维护以支持修改，所以考虑一些转化规避这个事情。如果不管这个限制则答案显然为 $\sum b_i$，那么从这里开始，计算考虑这个限制时答案会减少多少。

假设第一次到 $0$ 之下时到了 $-t$ 这个位置，那么按理说现在我们应该需要将后面的部分从 $0$ 开始，并将答案减去 $t$。但我们不这么做，而是继续从 $-t$ 开始后面的折线，这样相当于是我们把后面的折线应有的部分向下整体平移了 $t$ 个单位，于是从此刻开始，判定和 $0$ 取 $\max$ 实际上是在和 $-t$ 取 $\max$。换句话说，我们实际上将 $x$ 轴向下平移了 $t$ 个单位来继续后面的过程。于是从整体来看，会使得答案减小且 $x$ 轴平移的位置是这个折线中前缀 $\min $ 的位置。假设它们依次为 $t_1,\cdots,t_k$，那么会使得答案减小 $(t_2-t_1)+(t_3-t_2)+\cdots+(t_k-t_{k-1})=t_k-t_1=t_k$（因为初始的 $t_1=0$），而折线每个位置的值是 $a_i-b_i$ 的前缀和，所以就转化为区间加求全局 $\min$ 的问题，线段树维护即可。

下面考虑加上 $c_i$ 这个限制会对我们的折线产生什么影响。发现就是每次结束的时候不仅要对 $0$ 取 $\max$，还要对 $c_i$ 取 $\min$，但是对 $c_i$ 取 $\min$ 的操作不影响答案。那么继续考虑平移坐标轴来代替平移折线。假设在某个时刻 $x$ 轴一共被平移了 $t$ 步，且假设在原始折线上当前位置的值为 $s_i$，那么现在它实际的值是 $s_i-t$，所以如果 $s_i-t>c_i$，$t$ 需要变成 $s_i-c_i$，这个操作即为 $t=\max(t,s_i-c_i)$。而若 $s_i-t<0$，则答案会减少 $t-s_i$，且 $t$ 会变成 $s_i$。因此实际上我们现在在干的事情就是维护一个 $t$，每次先执行操作 $t=\max(t,s_i-c_i)$，再执行操作 $t=\min(t,s_i)$，所有第二种操作中 $t$ 移动的步数之和即是答案。

直接维护这么一种操作是困难的，但是考虑放缩一下这些限制。如果我们钦定一些位置执行 $t\leftarrow s_i-c_i$，一些位置执行 $t\leftarrow s_i$，那么会发生什么呢？首先这样一种钦定方式最终算出来 $t$ 的值一定不会大于答案，因为与真实的 $t$ 值相比，所有钦定第一种操作不会使得 $t$ 的值比真实的变大，钦定的第二种操作不会使得 $t$ 的值比真实的变小，那么向下移动的距离之和自然是不会更大的。另一方面，只要我们按照真实过程钦定所有的位置，就可以取到答案。所以可以将 $\min,\max$ 去掉，改为对所有钦定的可能性取 $\max$。直接做似乎和上一步 $t$ 的值有关，但我们发现两个连着的同种操作可以只保留后一个。因为对于第一种操作而言，先执行 $t\leftarrow x$，再执行 $t\leftarrow y$ 不会影响权值，而最终对 $t$ 的影响就是 $t\leftarrow y$。对于第二种操作而言，先执行 $t\leftarrow x$，再执行 $t\leftarrow y$ 会使得权值加上 $x-t+y-x=y-t$，所以也等价于直接执行 $t\leftarrow y$。

这样一来，问题就被转化为选择若干 $l_1<r_1<l_2<r_2<\cdots<l_k<r_k$，含义是在 $l_i$ 位置执行第一种操作，在 $r_i$ 位置执行第二种操作，权值为 $\sum s_{r_i}-(s_{l_i}-c_{l_i})$，使得权值最大，需要支持区间加 $s_i$ 和单点修改 $c_i$。使用线段树维护，在线段树的每个点上维护一个二维矩阵 $v[0/1][0/1]$，表示区间最左/右侧选择的是 $l/r$，合并是简单的。考虑一次修改操作会对线段树的值产生什么影响，其中单点修改是简单的，直接递归到叶子修改权值即可。考虑区间对 $s$ 的加法，如果不是对整个区间的加法就向下递归合并。对于标记的下传以及整个区间权值的加法来说，注意到给 $s$ 增加 $v$ 会使得所有选择 $l_i$ 的位置对答案的贡献减少 $v$，所有选择 $r_i$ 的位置对答案的贡献增加 $v$，所以一对 $l_i,r_i$ 的贡献抵消了。那么只有在选择的两端都是 $l$ 或都是 $r$ 才会对这种情况的权值增加或减少 $v$，所以标记是可以正常下传的。这样就做完了，复杂度 $O(n\log n)$。

[代码](https://codeforces.com/contest/1919/submission/240597842)

---

## 作者：zhuzhu2891 (赞：3)

首先定义 $f_{l,r}(x)$ 表示假设有 $x$ 升水流入 $l$ 节点，那么从 $r$ 节点流出的水量。

再定义 $g_{l,r}(x)$ 表示假设有 $x$ 升水流入 $l$ 节点，那么从 $l$ 到 $r$ 节点造的酒总数。

感性理解会发现这两个函数都长这样

![](https://cdn.luogu.com.cn/upload/image_hosting/miledl2q.png)

于是我们直接上线段树，区间 $[l,r]$ 存储 $f_{l,r}$ 与 $g_{l,r}$ 是什么。

显然每次修改只会导致 $\log$ 个节点被改变，于是直接修改就行了，答案就是 $g_{1,n}(0)$。

至于这个函数怎么复合，区间怎么合并，以及 $f_{i,i}$ 与 $g_{i,i}$ 是什么，反正都是 $O(1)$ 的，分类讨论就行了，具体方法留给读者思考。

---

## 作者：User_Unauthorized (赞：2)

考虑使用网络流刻画这个问题，将每个工厂建一个对应的节点，连出以下三种边：

- 从源点向工厂连一条容量为 $a_i$ 的边
- 从工厂向汇点连一条容量为 $b_i$ 的边
- 从工厂 $i$ 向工厂 $i + 1$ 连一条容量为 $c_i$ 的边

这样这个网络的最大流就是答案，但是直接使用最大流算法会超时，所以我们考虑观察该网络的性质以快速求出其最大流。

首先根据最大流最小割定理，我们可以知道最大流等于最小割，因此我们只需要求出最小割即可。

结论：对于每个 $i$，边 $S \rightarrow i$ 和边 $i \rightarrow T$ 一定恰好有一条在最小割中。

下面证明该结论成立。

首先我们证明不可能存在两条边都不在最小割中的情况，由于流量均为非负整数，若这两条边中存在一条流量为 $0$，那么将这条边加入最小割集对答案没有影响，因此我们只考虑两条边流量均不为 $0$ 的情况。发现在这种情况下流量可以通过 $S \rightarrow i \rightarrow T$，与割的定义矛盾，因此不存在两条边都不在最小割中的情况。

接下来考虑不存在两条边都在最小割中的情况，假设存在这样的最小割，那么我们按如下两种情况分类讨论：

- 若 $S$ 可以不通过边 $S \rightarrow$ 到达 $i$，例如 $S \rightarrow j \rightarrow j + 1 \rightarrow \cdots \rightarrow i$，那么无论边 $S \rightarrow i$ 是否被割，对答案均没有影响，因此我们可以将边 $S \rightarrow i$ 移出最小割集，得到一个不劣的方案。

- 若 $S$ 必须通过边 $S \rightarrow$ 到达 $i$，那么只要我们确保边 $S \rightarrow i$ 在最小割集中，那么就一定没有流量到达点 $i$，因此可以将边 $i \rightarrow T$ 移出最小割集，得到一个不劣的方案。

综上所述，我们可以得到结论：对于每个 $i$，边 $S \rightarrow i$ 和边 $i \rightarrow T$ 一定恰好有一条在最小割中。

现在我们考虑如何维护全局的最小割。

不妨称 $S \rightarrow i$ 的边为 $\tt{A}$ 类边，$i \rightarrow T$ 的边为 $\tt{B}$ 类边，$i \rightarrow i + 1$ 的边为 $\tt{C}$ 类边。

可以发现上文中的结论可以改写为：对于每个 $i$，$\tt{A}$ 类边和 $\tt{B}$ 类边一定恰好有一条在最小割中。

发现由于其对 $\tt{C}$ 类边没有限制，因此其实际上为满足最小割的一个必要不充分条件，我们考虑如何表达 $\tt{C}$ 类边的限制。

考虑对于一条形如 $i \rightarrow i + 1$ 的 $\tt{C}$ 类边，若 $i$ 的 $\tt{B}$ 类边在最小割中，同时 $i + 1$ 的 $\tt{A}$ 类边也在最小割中，那么这条边也一定在最小割中，因为若其不在最小割中，流量可以通过 $S \rightarrow i \rightarrow i + 1 \rightarrow T$，与割的定义矛盾。可以发现对于其他的情况均对 $\tt{C}$ 类边没有限制。

考虑使用线段树维护最小割，具体的，每个节点维护其对应区间 $\left[l, r\right]$ 满足在 $l$ 处选择 $\tt{A}$ 类边或 $\tt{B}$ 类边，在 $r$ 处选择 $\tt{A}$ 类边或 $\tt{B}$ 类边共四种情况的最小代价，合并两区间时，枚举 $l$ 和 $r$ 的选择情况，根据上文的结论，可以得到合并后的区间的最小代价。这四种情况的最小值便是这个区间的最小割。

时间复杂度 $\mathcal{O}\left(n \log n\right)$。

---

## 作者：EuphoricStar (赞：2)

题目看着感觉很像最大流，不妨建模，$S \to i$，容量为 $a_i$；$i \to T$，容量为 $b_i$；$i \to i + 1$，容量为 $c_i$。答案是这个图的最大流。

考虑最大流转最小割。观察到 $S \to i$ 和 $i \to T$ 的边**恰好**被割掉一条。因为不可能都不被割，$S, T$ 不能同时和 $i$ 连通。如果 $S, i$ 连通就割 $i \to T$，否则割 $S \to i$。

这样如果割了 $i \to T$ 和 $S \to i + 1$，也要割掉 $i \to i + 1$ 的边。所以实际上是一个动态 dp。

考虑线段树维护，$[l, r]$ 对应的结点维护 $f_{0/1, 0/1}$ 表示当 $l$ 是割到 $S$ 还是到 $T$ 的边，$r$ 是割到 $S$ 还是到 $T$ 的边的边权最小值。那么合并两儿子时如果是 $f_{\ast, 1}$ 和 $f_{0, \ast}$ 合并，那么费用再加 $c_{mid}$。

时间复杂度 $O(n + m \log n)$。

[code](https://codeforces.com/contest/1919/submission/240925457)

---

## 作者：huangrenheluogu (赞：1)

就线段树了，分块应该也可以，但是这道题难就难在 push_up 的函数上。

本篇题解就来讲一下 push_up 函数（向上更新）的推到过程，~~作为备忘录~~。

对于一棵子树 $p$，存储 $l\sim r$ 的信息，我们需要维护的变量如下：

- $l\sim r$ 中可以酿出的酒 $ans$。

- $l\sim r$ 中如果 $l$ 流入 $\inf$ 的水，可以酿酒的量 $maxin$。

- $l\sim r$ 中如果 $l$ 流入 $\inf$ 的水，可以流到 $r$ 的水的量 $maxcan$。 

- $l\sim r$ 中在 $r$ 处待流出的水量 $out$。

在 build 函数的时候，应该还是比较容易的。

```cpp
#define ls p << 1
#define rs p << 1 | 1
if(l == r){
	t[p].ans = min(a[l], b[l]);
	t[p].maxcan = inf;
	t[p].out = max(a[l] - b[l], 0ll);
	t[p].maxin = max(b[l] - a[l], 0ll);
//	debug(p, l, r);
	return ;
}
```

那么，下面开始 push_up 的部分。

下面描述中 $ls$ 是左儿子，$rs$ 是右儿子。

$p$ 从 $ls$ 和 $rs$ 转移的过程中，$p$ 先统计 $ls$ 和 $rs$ 的答案，同时，可以计算出左边到右边可能得流量 $flow$，就是左边儿子流出的量和连接左右儿子管道的量取个 $\min$。

接下来，进行分类讨论。

- 如果 $flow$ 比 $rs$ 的 $maxin$ 多。

那么 $flow$ 的一部分会酿成酒，其余的流动。

$p$ 的 $maxin$ 和 $ls$ 一致，并且 $ans$ 加上新酿的酒 $maxin_{rs}$。

$p$ 的右侧新增的酒就是可能可以流到右边的最大值（$maxcan_{rs}$）和没有被酿成酒的部分（$flow-maxin_{rs}$）取 $\min$，这一部分新增的量记为 $newwater$

$p$ 可能流到右侧的值由 $3$ 个部分取 $\min$ 构成：

> 1. 左边可以流到分界点的最大值 $maxcan_{ls}$。
> 
> 2. 分界点控制的流量 $c_{mid}-flow$，其中 $mid$ 是分界点。
> 
> 3. 右边可以流过的减去上面流过去的（$newwater$）。

```cpp
t[p].maxin = t[ls].maxin;
t[p].ans += t[rs].maxin;
t[p].out = min(t[rs].maxcan, flow - t[rs].maxin) + t[rs].out;
t[p].maxcan = min(t[ls].maxcan, min(t[rs].maxcan - min(t[rs].maxcan, flow - t[rs].maxin), c[mid] - flow));
```

- 如果 $flow$ 没有比 $rs$ 的 $maxin$ 多。

同样的，累计答案 $flow$。

$p$ 的 $maxin$ 可以分成左、右两部分。左部分就是 $maxin_{ls}$；右部分是下面 $3$ 个值取 $\min$：

> 1. 右边原来可以酿的酒减去左向右流过的水。
> 
> 2. 左边还可以允许流到分界点的水量。
> 
> 3. 连接左右通道上还可以流过的水量。

$p$ 流出的就是 $out_{rs}$。

下面就是 $p$ 还可能流到右边的水量（这一部分整理之后发现挺简单的，但是开始看题解的时候想了很久，也许是因为菜）。

首先，$maxcan_p$ 显然不能超过 $maxcan_{rs}$。

那么有一项是左边可以流到右边的水量 $\min\{maxcan_{ls},c_{mid}-flow\}$，当然，因为左边流到右边的水量可能会被右边直接利用（拿去酿酒），所以要减去右边还可以利用的的水量 $maxin_{rs}-flow$。

最后注意这里可能小于 $0$。

```cpp
t[p].ans += flow;
t[p].maxin = min(min(t[rs].maxin - flow, c[mid] - flow), t[ls].maxcan) + t[ls].maxin;
t[p].out = t[rs].out;
t[p].maxcan = min(t[rs].maxcan, min(t[ls].maxcan, c[mid] - flow) - (t[rs].maxin - flow));
if(t[p].maxcan < 0ll) t[p].maxcan = 0ll;
```

这样，push_up 就写好了。这种 push_up 复杂的题目真的不多见。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 5e5 + 5, inf = 1e18;
int n, q, a[N], b[N], c[N], p;
struct segtree{
	int ans, maxin, maxcan, out;
}t[N << 2];
inline void debug(int p, int l, int r){
	printf("debug : p = %lld, l = %lld, r = %lld, ans = %lld, maxin = %lld, maxcan = %lld, out = %lld\n", p, l, r, t[p].ans, t[p].maxin, t[p].maxcan, t[p].out);
}
inline void push_up(int p, int l, int r){
	int mid = l + r >> 1;
	t[p].ans = t[ls].ans + t[rs].ans;
	int flow = min(c[mid], t[ls].out);
	if(flow > t[rs].maxin){
		t[p].maxin = t[ls].maxin;
		t[p].ans += t[rs].maxin;
		t[p].out = min(t[rs].maxcan, flow - t[rs].maxin) + t[rs].out;
		t[p].maxcan = min(t[ls].maxcan, min(t[rs].maxcan - min(t[rs].maxcan, flow - t[rs].maxin), c[mid] - flow));
	}
	else{
		t[p].ans += flow;
		t[p].maxin = min(min(t[rs].maxin - flow, c[mid] - flow), t[ls].maxcan) + t[ls].maxin;
		t[p].out = t[rs].out;
		t[p].maxcan = min(t[rs].maxcan, min(t[ls].maxcan, c[mid] - flow) - (t[rs].maxin - flow));
		if(t[p].maxcan < 0ll) t[p].maxcan = 0ll;
	}
//	debug(p, l, r);
}
inline void build(int p, int l, int r, int x = 0){
	if(l == r){
		t[p].ans = min(a[l], b[l]);
		t[p].maxcan = inf;
		t[p].out = max(a[l] - b[l], 0ll);
		t[p].maxin = max(b[l] - a[l], 0ll);
//		debug(p, l, r);
		return ;
	}
	int mid = l + r >> 1;
	if(!x || mid >= x) build(ls, l, mid, x);
	if(!x || mid < x) build(rs, mid + 1, r, x);
	push_up(p, l, r);
}
signed main(){
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for(int i = 1; i < n; i++) scanf("%lld", &c[i]);
	build(1, 1, n);
	while(q--){
		scanf("%lld", &p);
		scanf("%lld%lld%lld", &a[p], &b[p], &c[p]);
		build(1, 1, n, p);
		printf("%lld\n", t[1].ans);
	}
	return 0;
}
```

---

## 作者：xuanxuan001 (赞：1)

重回 IGM 祭！~~rk100整祭！~~

E 的原题 ARC146E 之前做过，赛时也想起来了，但还是坚定地自己写调了整整 1h，~~当时就该不要 B 脸把之前写的代码粘过来改的~~，最后半个小时冲 F2，在最后一分钟调过了 F1 的样例，但事实证明离过掉还是很远，唉。

感觉这次给的表现分普遍比普通 div1+2 同排名时高，不知道为什么，是参赛人多吗？

正文
-

完全没想到最大流转最小割，提供一个极其难写但很套路的做法。

看到单点修改和序列操作不难想到线段树，那么难点在于如何合并两段信息。

发现经过一段塔(?)之后对答案的贡献看似会与从最左边流入的水量有关，但仔细思考发现这个影响其实可以被表示出来，具体的有一下两种情况：

1. 从没有水逐渐增加，那么这些多水最终会在这个区间内变成酒，这时会存在一个上界，设它为 $A$。
2. 继续增加水量，这时这些水无法在区间内变成酒，它们最终会从这个区间的最右边流走，这时也会有一个上界，设它为 $B$。
3. 继续增加水量，发现这时不会产生影响，因为它们会卡在中间的某个塔中，受巫师魔力的限制无法变成酒，受容量限制也无法继续传递。

除了记录 $A,B$ 以外，还需要记录从这一段塔中自己产生的水量，即如果没有从左边进入的水，那么会从右边流出的水量 $lft$。

那么记录了加上答案的这四个变量后进行亿些分讨就可以通过了。

设更新线段树的某个节点时左儿子是 $ls$，右儿子是 $rs$，中间的连接容量为 $c$。

代码中的大致思路就是先考虑更新答案，除了两个儿子内部的还会产生 $min(lft_{ls},A_{rs},c)$ 的答案，然后分讨 $lft_{ls}$ 和 $A_{rs}$ 的大小关系可以得到两种对合并后的 $A$ 和 $lft$ 的影响，同时考虑 $c$ 的限制就可以求出，然后继续推导就可以得到 $B$。

感觉还是需要自己理逻辑，看代码可能帮助不大，[所以就贴个记录得了](https://codeforces.com/contest/1919/submission/240628444)。

给两组我调的时候从 test3 偷下来的数据，希望能帮到其他人调题：

```
6 1
2 1 1 1 1 0 
0 1 1 1 0 2 
1 1 1 0 2 
1 2 0 1

output:4
```

```
6 1
2 1 1 1 1 0 
0 1 0 1 2 2 
1 1 2 2 2 
1 2 0 1

output:5
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/CF1919F2)。题目中多次出现【水流】，于是想【网络流】。直观地，如此建边：

- $S\to i$，容量 $a_i$；
- $i\to i+1$，容量 $c_i$；
- $i\to T$，容量 $b_i$。

那么答案就是最大流。感性理解是，题目的贪心策略是正确的。要证明，就是说按题目策略流完后，找不到增广路。

- 如果还有 $S\to i\to j\to T(j<i)$ 的增广路。那么 $j\to j+1$ 这条边的反向边有容量，原边就有流量。但是要求 $j\to T$，这说明 $j\to T$ 未满流。题目策略是先流完 $b_j$ 再流 $c_j$，这是矛盾的。
- 如果还有 $S\to i\to j\to T(j>i)$ 的增广路。那么 $i\to i+1$ 未满流。按照题目策略，$S\to i$ 和 $i-1\to i$ 的流量加起来都不足以达到 $b_i+c_i$，此时 $S\to i$ 必然满流。所以不存在 $S\to i$，矛盾。
- 如果还有 $S\to i\to T$ 的增广路。那么 $S\to i$ 和 $i\to T$ 均未满流。按照题目策略，显然可以让 $a_i$ 多分一点给 $b_i$，矛盾。

不需要模拟，而是【最大流 $=$ 最小割】。先证明，$S\to i$ 和 $i\to T$ 恰好被割掉一个。

- 显然不可能二者都不割。
- 二者都割的话。如果还存在 $S\to i$ 的路径，那么可以不割 $S\to i$。如果不存在 $S\to i$ 的路径，那么可以不割 $i\to T$。

然后 EZver 就做完了。割 $c_i$ 不优，因此不存在 $i<j$ 满足：割掉 $i\to T$ 和 $S\to j$。答案就是 $\large \max_i\{\sum_{j=1}^i a_j+\sum_{j=i+1}^n b_j\}$，线段树即可。

考虑 HardVer。对于每一个 $i=j-1$ 满足：割掉 $i\to T$ 和 $S\to j$，都必须割掉 $i\to j$。线段树维护四个值，左端点割 $a_l/b_l$、右端点割 $a_r/b_r$ 的最佳答案。`pushup` 不难想，每次单点修改即可。

```cpp
int a[N],b[N];ll c[N];

namespace sgt{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	struct node{
		ll aa,ab,ba,bb;
		#define aa(x) t[x].aa
		#define ab(x) t[x].ab
		#define ba(x) t[x].ba
		#define bb(x) t[x].bb
	}t[N<<2];
	void updata(int x,int r){
		#define L ls(x)
		#define R rs(x)
		aa(x)=min(min(aa(L)+aa(R),aa(L)+ba(R)),
				  min(ab(L)+aa(R)+c[r],ab(L)+ba(R)));
		ba(x)=min(min(ba(L)+aa(R),ba(L)+ba(R)),
				  min(bb(L)+aa(R)+c[r],bb(L)+ba(R)));
		ab(x)=min(min(aa(L)+ab(R),aa(L)+bb(R)),
				  min(ab(L)+ab(R)+c[r],ab(L)+bb(R)));
		bb(x)=min(min(ba(L)+ab(R),ba(L)+bb(R)),
				  min(bb(L)+ab(R)+c[r],bb(L)+bb(R)));
	}
	void sig(int x,int p){
		aa(x)=a[p];bb(x)=b[p];ab(x)=ba(x)=1e18;
	}
	void build(int now,int ln,int rn){
		if(ln==rn) return sig(now,ln);
		int mid=ln+rn>>1;
		build(ls(now),ln,mid);
		build(rs(now),mid+1,rn);
		updata(now,mid);
	}
	void upd(int now,int ln,int rn,int p){
		if(ln==rn) return sig(now,p);
		int mid=ln+rn>>1;
		if(p<=mid) upd(ls(now),ln,mid,p);
		else upd(rs(now),mid+1,rn,p);
		updata(now,mid);
	}
	ll qry(){return min(min(aa(1),ab(1)),min(ba(1),bb(1)));}
}

int main()
{
	int n,q;re(n);re(q);
	for(int i=1;i<=n;++i) re(a[i]);
	for(int i=1;i<=n;++i) re(b[i]);
	for(int i=1;i<n;++i) re(c[i]);
	sgt::build(1,1,n);while(q--){
		int p;re(p);re(a[p]);re(b[p]);re(c[p]);
		sgt::upd(1,1,n,p);wr(sgt::qry());puts("");
	}
}
```



---

