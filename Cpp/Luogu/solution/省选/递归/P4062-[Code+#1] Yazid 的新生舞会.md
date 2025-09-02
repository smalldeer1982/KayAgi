# [Code+#1] Yazid 的新生舞会

## 题目背景

这道题是没有舞伴的 Yazid 用新生舞会的时间出的。


## 题目描述

Yazid 有一个长度为 $n$ 的序列 $A$，下标从 $1$ 至 $n$。显然地，这个序列共有 $\frac{n\left( n+1\right)}{2}$ 个子区间。

对于任意一个子区间 $[l,r]$，如果该子区间内的众数在该子区间的出现次数严格大于 $\frac{r-l+1}{2}$（即该子区间长度的一半），那么 Yazid 就说这个子区间是“新生舞会的”。

所谓众数，即为该子区间内出现次数最多的数。特别地，如果出现次数最多的数有多个，我们规定值最小的数为众数。

现在，Yazid 想知道，共有多少个子区间是“新生舞会的”。


## 说明/提示

**【样例解释 #1】**

“新生舞会的”子区间有 $[1,1],[1,2],[1,3],[2,2],[2,4],[3,3],[3,4],[3,5],[4,4],[5,5]$ 共 $10$ 个。

 ![](https://cdn.luogu.com.cn/upload/pic/12825.png) 

对于所有数据，保证 $0\leq A_i\leq n-1$。

对于 $type=0$ 的数据，没有任何特殊约定。

对于 $type=1$ 的数据，保证 $A_i\in \{ 0, 1 \}$。

对于 $type=2$ 的数据，保证序列 $A$ 的众数在整个序列中的出现次数不超过 $15$。

对于 $type=3$ 的数据，保证 $A_i\leq 7$。

来自 CodePlus 2017 11 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

Credit：idea/郑林楷 命题/王聿中 验题/郑林楷

Git Repo：https://git.thusaac.org/publish/CodePlus201711

感谢腾讯公司对此次比赛的支持。


## 样例 #1

### 输入

```
5 0
1 1 2 2 3```

### 输出

```
10```

# 题解

## 作者：OMG_wc (赞：74)

写一个比较自然的题解，不需要利用什么性质。分别给出了用树状数组、线段树实现的方法，时间复杂度皆为 $O(n\log n)$。

由数据范围 $0\le A_i\le n-1$，我们想到枚举每个种类的数，分别计算贡献。

对当前选中的数 $w$，设 $S_i$ 为前 $i$ 个数中 $w$ 的个数 ，那么对于一段区间 $[l+1,r]$ ，$w$ 能成为绝对众数（数量严格超过一半的众数）的条件是 $S_r-S_l>r-l-(S_r-S_l)$。

移项得到 $2S_r-r>2S_l-l$，那问题就变成了对每个 $r$ ，统计 $l\in[0,r-1]$ 的范围内有多少满足 $2S_r-r>2S_l-l$。（可以发现， $2S_i-i$ 其中就是前缀里 $w$ 的个数减去非 $w$ 的个数）如果用树状数组来维护每个 $2S_i-i$ 的个数，时间复杂度度 $O(n^2log(n))$ ，只能骗部分分。当然有些细节要注意，比如 $2S_i-i$ 的值域范围是 $[-n,n]$ ，你需要加个 $n+1$ 的偏移量才能用数据结构维护。

为了方便叙述，记 $P_i=2S_i-i$。

然后观察对某个选中的数 $w$，其 $P_i$ 的变化情况。可以发现如果有 $k$ 个 $w$，那么可以分成 $k+1$ 个区间（以 $0$ 位置及每个 $w$ 为开头到下个 $w$ 之前的数为止），每个区间内部的 $P_i$ 值都是公差为 $-1$ 的等差数列。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/da2aj13d.png)

这样如果我们能用某种方法把每段里的数**同时处理**，那么总共需要处理的段数就是 $O(n)$ 的了。

具体来说，假设当前这段的等差数列是 $y,y-1,y-2,\dots ,x$ ，用数据结构来维护权值 $c_i$，那么也就是对区间 $[x,y]$ 加 $1$。

并且可以发现同一段是不会有任何贡献的（因为是递减的），只需查询前面所有段的 $P_i$ 值带来的影响，所以在更新操作之前，我们应该先做查询，

记 $T_i$ 表示权值的前缀和，即 $T_i=\sum\limits_{j=1}^{i}c_j$。对段内每个位置的 $P_i$ ，我们得到的贡献是 $T_{P_i-1}$。也就是说，对整个段内 $[x,y]$ 这些数，总贡献是 $\sum\limits_{i=x-1}^{y-1}T_i$。记 $G_i$ 表示权值的前缀和的前缀和，即 $G_i=\sum\limits_{j=1}^{i}T_j$，那么总贡献可以表示为 $G_{y-1}-G_{x-1}$。

现在问题简化为区间加一个数和求二阶前缀和，下面分别用树状数组和线段树解决这个问题：

---

### 树状数组

想必你用树状数组做过 “区间加一个数，区间求和”的问题，本质单点更新，是求二阶前缀和。

事实上，使用 $n$ 个树状数组，可以实现单点更新，查询 $n$ 阶前缀和：

比如 $n=3$ 时，

设 $c$ 是 $b$ 的前缀和， $b$ 是 $a$ 的前缀和，$a$ 是 $d$ 的前缀和，即 $c$ 是 $d$ 的三阶前缀和，那么有


$$
\begin{aligned}
&c_x=\sum\limits_{i=1}^{x} b_i\\
&=\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{i} a_j\\
&=\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{i}\sum\limits_{k=1}^{j}d_k\\
&=\sum\limits_{k=1}^{x}\frac{(x+2-k)(x+1-k)}{2}d_k\\
&=\frac{(x+2)(x+1)}{2}\sum\limits_{k=1}^{x}d_k-\frac{2x+3}{2}\sum\limits_{k=1}^{x}d_k\cdot k+\frac{1}{2}\sum\limits_{k=1}^{x}d_k\cdot k^2
\end{aligned}
$$

对这题而言，现在区间更新可以转换为差分数组 $d$ 的两个单点更新，原数组的二阶前缀和变为差分数组 $d$ 的三阶前缀和。

那么只要用三个树状数组维护 $d_i,d_i\times i,d_i\times i^2$ 即可，完整代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 500005;
// 修改差分 来维护前缀和的前缀和
// c1 为差分d c2为d*i  c3 为d*i*i
LL c1[N * 2], c2[N * 2], c3[N * 2];
LL sum(int x) {
    LL res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        res += c1[i] * (x + 2) * (x + 1) - c2[i] * (2 * x + 3) + c3[i];
    }
    return res / 2;
}
void add(int x, LL d, int n) {
    for (int i = x; i <= n; i += i & -i) {
        c1[i] += d;
        c2[i] += d * x;
        c3[i] += d * x * x;
    }
}
int a[N];
vector<int> b[N];
int main() {
    int n;
    scanf("%d%*d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[a[i]].push_back(i);
    }
    const int wc = n + 1;  // 偏移量，把[-n,n] 平移到 [1,2n+1]
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        b[i].push_back(n + 1);
        int last = 0;
        for (int j = 0; j < b[i].size(); j++) {
            int y = 2 * j - last + wc, x = 2 * j - (b[i][j] - 1) + wc;
            // 查询 sum([1,t-1] 的权值和), 其中t在[x,y]范围内，
            ans += sum(y - 1) - (x >= 3 ? sum(x - 2) : 0);
            // [x,y] 这些数的权值+1
            add(x, 1, 2 * n + 1);
            add(y + 1, -1, 2 * n + 1);
            last = b[i][j];
        }
        last = 0;
        for (int j = 0; j < b[i].size(); j++) {
            int y = 2 * j - last + wc, x = 2 * j - (b[i][j] - 1) + wc;
            add(x, -1, 2 * n + 1);
            add(y + 1, 1, 2 * n + 1);
            last = b[i][j];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

### 线段树

其实也可以用两棵线段树来求二阶前缀和，但这就没有意思了，和树状数组维护三阶前缀和没区别。

我的方法是用线段树维护权值的前缀和 $T_i$ ，这样在 $[x,y]$ 上的区间加 $1$ 就变成了：在 $[x,y]$ 上加等差数列 $1,2,3,\ldots,y-x+1$，在 $[y+1,2n+1]$ 上加上 $y-x+1$。后者也可看成是公差为 $0$ 的等差数列。

那么线段树怎么维护等差数列呢？

我们可以发现任意个等差数列的和都是等差数列，只是公差和首项发生了变化。

那么只要把公差和首项作为延迟标记，来维护区间和就好了，具体实现见代码。

因为维护的是 $T_i$ ，查询也只是简单的区间查询了，注意一些边界问题就OK了。

完整代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 500005;

// sx,gc 表示首项和公差
LL val[N << 3], sx[N << 3], gc[N << 3];
inline void push_up(int u) {
    val[u] = val[u << 1] + val[u << 1 | 1];
}
inline void gx(int u, LL v, LL d, int len) {
    val[u] += (v + v + (len - 1) * d) * len / 2;
    sx[u] += v;
    gc[u] += d;
}
inline void push_down(int u, int len1, int len2) {
    if (sx[u] || gc[u]) {
        gx(u << 1, sx[u], gc[u], len1);
        gx(u << 1 | 1, sx[u] + gc[u] * len1, gc[u], len2);
        sx[u] = gc[u] = 0;
    }
}
void update(int u, int l, int r, int x, int y, int v, int d) {
    if (x <= l && r <= y) {
        gx(u, v + (l - x) * d, d, r - l + 1);
        return;
    }
    int mid = l + r >> 1;
    push_down(u, mid - l + 1, r - mid);
    if (x <= mid) update(u << 1, l, mid, x, y, v, d);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y, v, d);
    push_up(u);
}
LL query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return val[u];
    }
    int mid = l + r >> 1;
    push_down(u, mid - l + 1, r - mid);
    LL res = 0;
    if (x <= mid) res += query(u << 1, l, mid, x, y);
    if (y > mid) res += query(u << 1 | 1, mid + 1, r, x, y);
    return res;
}
int a[N];
vector<int> b[N];
int main() {
    int n;
    scanf("%d%*d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[a[i]].push_back(i);
    }
    const int wc = n + 1;  // 偏移量，把[-n,n] 平移到 [1,2n+1]
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        b[i].push_back(n + 1);
        int last = 0;
        for (int j = 0; j < b[i].size(); j++) {
            int y = 2 * j - last + wc, x = 2 * j - (b[i][j] - 1) + wc;
            // 查询 sum([1,t-1] 的权值和), 其中t在[x,y]范围内
            ans += query(1, 1, 2 * n + 1, max(x - 1, 1), y - 1);
            // [x,y] 这些数的权值+1，真正要维护的是它们的前缀和，
            // 在[x,y] 上是加上一段等差数列 1,2,3,...,y-x+1，[y+1,2n+1] 上每个数+y-x+1
            update(1, 1, 2 * n + 1, x, y, 1, 1);
            if (x + 1 <= 2 * n + 1) update(1, 1, 2 * n + 1, y + 1, 2 * n + 1, y - x + 1, 0);
            last = b[i][j];
        }
        last = 0;
        for (int j = 0; j < b[i].size(); j++) {
            int y = 2 * j - last + wc, x = 2 * j - (b[i][j] - 1) + wc;
            update(1, 1, 2 * n + 1, x, y, -1, -1);
            if (x + 1 <= 2 * n + 1) update(1, 1, 2 * n + 1, y + 1, 2 * n + 1, -(y - x + 1), 0);
            last = b[i][j];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

最后，同样时间复杂度是 $O(n\log n)$，但是线段树跑的时间是树状数组的三倍。

---

## 作者：Alex_Wei (赞：43)

> ### [Code+#1]Yazid 的新生舞会
>
> 经典老题，洛谷原题链接：https://www.luogu.com.cn/problem/P4062。

**线性做法！**

---

由于出现次数严格大于 $\dfrac{r-l+1}2$，所以一个区间最多被一个众数贡献。因此考虑求出每个数作为符合题意的众数出现的区间个数之和即答案。

我们设序列 $s_k$ 表示 $k$ 的出现次数前缀和，即 $s_{k,i}=\sum_{j=1}^i[a_j=k]$。根据题意，一个区间 $[l+1,r]$ 被 $k$ 贡献当且仅当 $s_{k,r}-s_{k,l}>\dfrac{r-l}2$。稍作变形得 $2s_{k,r}-r>2s_{k,l}-l$。这就很显然了，即求 $2s_{k,i}-i$ 的逆序对数。

但是我们不能对每个 $k$ 都 $n\log n$ 求一遍逆序对。注意到出现次数总数为 $n$，也就是说对于固定的 $k$ 可能有一大串 $s_k$（$s_{k,p}\sim s_{k,q}$）都相同，注意到计算贡献其实就是询问 $q-p+1$ 段前缀和，且右端点递减，即矩形 + 等腰直角三角形。这个显然可以线段树维护区间 $\sum v_i$（矩形）以及 $\sum i\times v_i$（用梯形减去矩形就得到了等腰直角三角形）。在线段树中加入这些值（$s_{k,p}-p\sim s_{k,q}-q$）就是区间加了。

此外清空不能直接 memset 否则复杂度会退化为 $n^2$，需要记录做过的操作然后撤销。时间复杂度 $\mathcal{O}(n\log n)$。

用线段树被卡常了怎么办？还有树状数组。注意到一次修改实际上是在差分数组上区间加，即对于每个 $i\in [p,q]$，都给 $s_{k,p}-i\sim \mathrm{upperbound}$ 加上 $1$，一次修改是差分数组单点加，两次就是区间加。考虑维护差分数组的差分数组，那么区间求和就是求**三次前缀和**：我们维护的东西的前缀和是差分数组，差分数组的前缀和是原数组，原数组的前缀和就是我们要单点求的东西。

对于这种**树状数组维护高阶前缀和**的问题，一般考虑在 $p$ 处加上 $1$ 对 $q$ 的贡献：$\sum_{i=p}^{q}i-p+1$：一阶差分数组在 $p$ 处 $+1$ 会在原数组前缀和的 $q$ 处贡献 $q-p+1$，而二阶差分数组在 $p$ 处 $+1$ 会在一阶差分数组的 $p\sim q$ 处都加上 $1$，故有此式。先乘以 $2$（因为有等差数列求和，计算除以 $2$ 不方便）稍作化简得到 $(p+q)(q-p+1)+2(1-p)(q-p+1)$，这里出现了 $q$ 的 $0,1,2$ 次项，分别维护其系数即 $(p^2-3p+2)q^0+(-2p+3)q+q^2$，最后答案除以 $2$ 即可。

```cpp
const int N = 5e5 + 5;

ll n, type, ans;
vint buc[N];
struct BIT {
	ll a0[N << 1], a1[N << 1], a2[N << 1];
	void add(ll x, int v) {
		ll c0 = (x * x - 3 * x + 2) * v, c1 = (3 - 2 * x) * v;
		while(x <= n * 2 + 1) a0[x] += c0, a1[x] += c1, a2[x] += v, x += x & -x;
	}
	void add(int l, int r, int v) {add(l + n + 1, v), add(r + n + 2, -v);}
	ll query(int x) {
		ll t = x, c0 = 0, c1 = 0, c2 = 0;
		while(x) c0 += a0[x], c1 += a1[x], c2 += a2[x], x -= x & -x;
		return c0 + c1 * t + c2 * t * t;
	}
	ll query(int l, int r) {return query(r + n + 1) - query(l + n);}
} tr;

vpii d;
void doit(int l, int r) {tr.add(l, r, 1), d.pb(l, r);}
void discard() {for(pii it : d) tr.add(it.fi, it.se, -1); d.clear();}
void solve(vint &cur) {
	for(int i = 1; i < cur.size(); i++) {
		int pre = cur[i - 1], now = cur[i], s = i - 1 << 1;
		if(pre + 1 < now) {
			int l = s - now + 1, r = s - pre - 1;
			if(i > 1) ans += tr.query(l - 1, r - 1);
			doit(l, r);
		}
		if(i < cur.size() - 1) {
			int p = i * 2 - now;
			ans += tr.query(p - 1, p - 1), doit(p, p);
		}
	}
	discard();
}

int main(){
	cin >> n >> type;
	for(int i = 0; i < n; i++) buc[i].pb(0);
	for(int i = 1; i <= n; i++) buc[read()].pb(i);
	tr.add(0, 0, 1);
	for(int i = 0; i < n; i++) buc[i].pb(n + 1), solve(buc[i]);
	cout << ans / 2 << endl;
    return 0;
}
```

**能不能再给力一点啊**？可以。

不妨设 $d_i$ 表示 $2s_{k,i}-i$。

**observation 1**：对于固定的众数 $k$，最多有 $2s_{k,n}$ 个位置对答案有贡献。即对于所有 $k$，使得 $d_p>\min_{i=1}^{p-1}d_i$ 的 $p$ 个数之和是 $\mathcal{O}(n)$ 的。感性理解即若出现的 $0\ (a_i\neq k)$ 足够多，无论左端点怎么往左扩展都无法使 $k$ 符合条件。

上述结论使我们不需要求原数组的区间和，只需要对于连续递减的一段 $d_i$，查询单点即求出二阶差分数组的二阶前缀和，直到当前的 $d_i$ **小于 $d_i$ 的前缀最小值**，因为再枚举下去对答案的贡献为 $0$（注意到我们是给 $[d_i+1,\infty]$ 区间加 $1$ ），直接忽略。可以显著减小常数。但问题仍不弱于求逆序对个数。

**observation 2**：$|d_i-d_{i-1}|\leq 1$。 

上述结论保证了每次查询的间隔不超过 $1$，除了对于连续递减的一段 $d_{l\sim r}$ 的最后一次查询（不妨设为位置 $p$）与 $d_{r+1}$ 之间会有一个间隔，但是忽略这个间隔这并不影响结果，因为 $d_{r+1}-1\sim d_p-1$ 这一段并没有进行任何修改：它小于 $d_l$ 的前缀最小值，自然不会产生任何贡献。那么由于指针的移动距离之和是 $\mathcal{O}(n)$ 的，因此直接维护二阶差分数组，一阶差分（基于二阶差分数组修改）和当前位置的值（基于一阶差分修改）即可做到线性。

```cpp
const int N = 5e5 + 5;

int n, type, add[N << 1], del[N << 1], s[N];
int cnt, hd[N], nxt[N << 1], val[N << 1];
void link(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, val[cnt] = v;}
void modify(int l, int r, int v) {add[l + N] += v, del[r + N + 1] += v;}
ll ans;

int main(){
	cin >> n >> type, modify(1, 1, 1);
	for(int i = 1; i <= n; i++) link(read(), i);
	for(int p = 0; p < n; p++) {
		if(!hd[p]) continue;
		int minp = 0, id = 1;
		static int tmp[N]; tmp[0] = 0, tmp[1] = n + 1;
		for(int i = hd[p]; i; i = nxt[i]) tmp[++id] = val[i];
		reverse(tmp + 1, tmp + id + 1);
		ll dc = 0, c = 0;
		for(int i = 1; i <= id; i++) {
			int pre = tmp[i - 1], cur = tmp[i];
			int r = s[i - 1] - 1, l = r - (cur - pre) + 2;
			if(l <= r && pre) {
				int lim = max(minp, l);
				for(int j = r; j >= lim; j--) {
					c -= dc, ans += c;
					dc += del[j + N + 1] - add[j + N + 1];
				}
			}
			if(i == id) break;
			modify(l + 1, r + 1, 1);
			dc += add[l + N + 1] - del[l + N + 1];
			c += dc, ans += c, s[i] = l + 1;
			modify(s[i] + 1, s[i] + 1, 1), cmin(minp, l);
		}
		for(int i = 1; i < id; i++)
			modify(s[i], s[i - 1], -1),
			modify(s[i] + 1, s[i] + 1, -1);
	}
	cout << ans << endl;
    return cerr << clock() << endl, flush(), 0;
}
```

---

## 作者：Limit (赞：25)

Update on 7.7

被两个 $\log$ 的做法吊打呢,被 [$\sf \color{black}{e}\color{red}{xz\alpha ng}$](https://www.luogu.com.cn/blog/id-exzang/solution-p4062) 的三 $\log$ 做法吊打呢,自闭了/kk.

#  题目大意

给出一个序列,询问又多少子串 $[l,r]$ 满足出现次数最多的数出现了**大于** $\lfloor\frac{r-l+1}{2}\rfloor$ 次(其实就是问又多少子串有[绝对众数]([https://www.baidu.com/s?ie=UTF-8&wd=%E7%BB%9D%E5%AF%B9%E4%BC%97%E6%95%B0](https://www.baidu.com/s?ie=UTF-8&wd=绝对众数))).

# 分析

好像有一种高大上的分治做法,但是我不会.

考虑 $a_i\in[0,1]$ 怎么做,因为对于每个子串最多只会有一个绝对众数,所以考虑计算 $0$ 和 $1$ 分别为绝对众数时的答案,相加就好了.

如果一个子串拥有绝对众数,那么必定有一个数出现的次数大于其他所有数出现的次数之和,那么将 $a_i=p$ 的位置为 $1$,$a_i\not=p$ 的位置为 $-1$($p$ 为腰计算贡献的数),就是要计算有多少子串的和大于 $0$.考虑再前缀和一下,问题就变成了找顺序对($i<j\land sum_i<sum_j$)个数,这个东西就可以用树状数组(权值线段树,平衡树等数据结构轻松解决),然后您发现 $a_i\leq 7$ 的部分也写完了.

时间复杂度 $\mathcal{O}(kn\log n)$(其中 $k$ 为序列中不同数个数).

但是对于最大的数据其中不同数的个数有 $n$ 种,显然不能这样搞了,考虑去优化这个方法.

假设序列 $a$ 为 $[1,1,2,3,2,1,3]$.

先枚举到 $1$,将等于 $1$ 的位置在序列 $b$ 中改为 $1$,其他地方改为 $-1$.

那么 $b$ 为 $[1,1,-1,-1,-1,1,-1]$.

计算一下前缀和.

$sum=[0,1,2,1,0,-1,0,-1]$(不要忘记在开头有一个 $0$).

计算顺序对个数为 $5$.

再枚举到 $2\dots$

不难发现在序列 $b$ 中会有很多连续的 $-1$,而且这些连续的 $-1$ 的段数最多为 $2n-2$(和 $n$ 同阶),并且在 $b$ 中为 $1$ 的位置的数量恰好为 $n$.

而且这些连续的 $-1$ 在前缀和中为一段公差为 $-1$ 的等差数列,既然是一段连续的数加入,那么自然可以想到在权值线段树上打标记.

那么比较麻烦的是这段数计算贡献.

假设中间这段数的前缀和为 $sum_l,sum_{l+1},\dots,sum_{r-1},sum_r$,那么对于 这段数的贡献为 $\sum\limits_{i=l}^{r}\sum\limits_{j=0}^{l-1}(sum_j<sum_i)$,其中把这段数为公差为 $-1$ 的等差数列这个结论带入就变成了 $\sum\limits_{i=0}^{r-l}\sum\limits_{j=0}^{l-1}(sum_j<sum_l-i)$,假设用一个 $s$ 数组来记录 $sum_{i\in[0,l-1]}$ 中每个数出现的次数,那么这个公式就变成了 $\sum\limits_{i=0}^{r-l}[(r-l-i)s_{sum_l-1-i}]+(r-l+1)\sum\limits_{i=-\infty}^{sum_r-1}s_i$.那么只需要在权值线段树上维护一个 $\sum\limits_{i=l}^{r}(r-i+1)s_i$,就可以很方便的计算了.

时间复杂度 $\mathcal{O}(n\log n)$.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=5e5+5;
int n,m;
inline int Read()
{
	int x(0),f(1);
	char c(getchar());
	while(c<'0'||'9'<c)
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while('0'<=c&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return f*x;
}
vector<int>place[MAXN];
struct LazyTag
{
	bool clean;//因为不可能每次都暴力清空整颗线段树,所以需要一个清空标记
	int add;
	inline void Clean()
	{
		clean=0;
		add=0;
	}
}for_make;
inline LazyTag MakeTag(int opt,int add=0)
{
	for_make.Clean();
	if(opt==0)
	{
		for_make.clean=1;
	}
	if(opt==1)
	{
		for_make.add=add;
	}
	return for_make;
}
struct SegmentTree
{
	int len;
	long long sum,sum_;//权值线段树上维护权值和以及取的数量从 len 依次减一的和
	LazyTag tag;
}sgt[MAXN*8];
#define LSON (now<<1)
#define RSON (now<<1|1)
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NOW now_left,now_right
inline void PushUp(int now)
{
	sgt[now].sum=sgt[LSON].sum+sgt[RSON].sum;
	sgt[now].sum_=sgt[LSON].sum_+sgt[LSON].sum*sgt[RSON].len+sgt[RSON].sum_;//计算 sum_ 建议自己推一下式子
}
void Build(int now=1,int left=1,int right=n*2+10)
{
	sgt[now].len=right-left+1;
	if(left==right)
	{
		return;
	}
	Build(LEFT);
	Build(RIGHT);
}
inline void Down(LazyTag tag,int now)
{
	if(tag.clean)
	{
		sgt[now].sum=sgt[now].sum_=0;
		sgt[now].tag.Clean();//需要把懒标记也清空
		sgt[now].tag.clean=1;
	}
	if(tag.add)
	{
		sgt[now].tag.add+=tag.add;
		sgt[now].sum+=1ll*sgt[now].len*tag.add;
		sgt[now].sum_+=1ll*(sgt[now].len+1)*sgt[now].len/2*tag.add;//直接用等差数列求和公式即可
	}
}
inline void PushDown(int now)
{
	Down(sgt[now].tag,LSON);
	Down(sgt[now].tag,RSON);
	sgt[now].tag.Clean();
}
inline void CleanTree()
{
	Down(MakeTag(0),1);
}
void UpdataAdd(int now_left,int now_right,int add,int now=1,int left=1,int right=n*2+10)
{
	if(now_left<=left&&right<=now_right)
	{
		Down(MakeTag(1,add),now);
		return;
	}
	PushDown(now);
	if(now_left<=MIDDLE)
	{
		UpdataAdd(NOW,add,LEFT);
	}
	if(MIDDLE+1<=now_right)
	{
		UpdataAdd(NOW,add,RIGHT);
	}
	PushUp(now);
}
long long QuerySum(int now_left,int now_right,int now=1,int left=1,int right=n*2+10)
{
	if(now_left<=left&&right<=now_right)
	{
		return sgt[now].sum;
	}
	PushDown(now);
	long long result=0;
	if(now_left<=MIDDLE)
	{
		result=QuerySum(NOW,LEFT);
	}
	if(MIDDLE+1<=now_right)
	{
		result+=QuerySum(NOW,RIGHT);
	}
	return result;
}
long long QuerySum_(int now_left,int now_right,int now=1,int left=1,int right=n*2+10)
{
	if(now_left<=left&&right<=now_right)
	{
		
		return sgt[now].sum_+sgt[now].sum*(now_right-right);//在计算 sum_ 的时候需要适当加上一些 sum,建议自己画图推式子
	}
	PushDown(now);
	long long result=0;
	if(now_left<=MIDDLE)
	{
		result=QuerySum_(NOW,LEFT);
	}
	if(MIDDLE+1<=now_right)
	{
		result+=QuerySum_(NOW,RIGHT);
	}
	return result;
}
#undef LSON
#undef RSON
#undef MIDDLE
#undef LEFT
#undef RIGHT
#undef NOW
int main()
{
	int opt;
	scanf("%d%d",&n,&opt);
	REP(i,0,n-1)
	{
		place[i].push_back(0);
	}
	REP(i,1,n)
	{
		place[Read()].push_back(i);
	}
	REP(i,0,n-1)
	{
		place[i].push_back(n+1);
	}
	Build();
	int add_num=n+3;//建议在线段树中不要使用负下标,如果要使用在计算 middle 不能直接使用 (left+right)>>1,而是应该一直向下取整,即 left=-5,right=-2 时 middle 应该为 -4,而不是 -3
	long long answer=0;
	REP(i,0,n-1)
	{
		CleanTree();//清空权值线段树
		UpdataAdd(add_num+0,add_num+0,1);//不要忘记把 0 放入权值线段树
		int now=0;
		REP(j,1,place[i].size()-1)
		{
			if(place[i][j-1]+1!=place[i][j])
			{
				answer+=QuerySum_(add_num+now-(place[i][j]-place[i][j-1]-1),add_num+now-2)+1ll*(place[i][j]-place[i][j-1]-1)*QuerySum(1,add_num+now-(place[i][j]-place[i][j-1]-1)-1);//按上面给出的计算等差数列贡献的方法计算
				UpdataAdd(add_num+now-(place[i][j]-place[i][j-1]-1),add_num+now-1,1);//将这一整段数都放入权值线段树
				now-=(place[i][j]-place[i][j-1]-1);
			}
			if(place[i][j]!=n+1)
			{
                //在等于枚举的数的位置就直接计算贡献
				now++;
				answer+=QuerySum(1,add_num+now-1);
				UpdataAdd(add_num+now,add_num+now,1);
			}
		}
	}
	printf("%lld\n",answer);
	return 0;
}
```


---

## 作者：skylee (赞：23)

**题目大意：**

给你一个长度为$n(n\leq 5\times 10^5)$的序列$A_{1\sim n}$。求满足区间众数在区间内出现次数严格大于$\lfloor\frac{r-l+1}{2}\rfloor$的区间$[l,r]$的个数。


**思路：**

分治。

对于一个区间$[l,r]$，设$mid=\lfloor\frac{l+r}{2}\rfloor$，我们可以求出所有经过$mid$的区间内能够成为众数的所有数。

不难发现所有的区间众数满足如下一个性质：如果$x$是区间$[l,r]$的众数，那么对于$l\leq k\leq r$，$x$一定是区间$[l,k]$或区间$(k,r]$的众数。

利用这一性质，我们可以令$k=mid$，这样就可以$O(n)$从$mid$出发往左右两边扫，求出能够成为众数的所有数。

接下来枚举每个众数$x$，求一下当前$[l,r]$区间中，以$x$作为众数的子区间个数。

具体我们可以先从$mid$往左扫，设往左扫到的端点为$b$，记录一下对于不同的$b$，$mid-b+1-cnt[x]$不同取值的出现次数。然后再往右扫，求出对于当前右端点$e$，求出满足$e-b+1-cnt[x]>\lfloor\frac{e-b+1}{2}\rfloor$的区间$[b,e]$的个数，这可以用前缀和快速求出。

这样我们就统计了区间$[l,r]$，经过$mid$的所有子区间。

对于不经过$mid$的子区间可以递归求解。

递归树中，每一层区间长度加起来是$n$，可能的众数个数有$\log n$个，每一层的时间复杂度是$O(n\log n)$。总共有$\log n$层，总的时间复杂度是$O(n\log^2 n)$。


**代码：**

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
typedef long long int64;
inline int getint() {
    register char ch;
    while(!isdigit(ch=getchar()));
    register int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int N=500001;
int a[N],pos[N],num[N],cnt[N*2];
int64 ans;
void solve(const int &l,const int &r) {
    if(l==r) {
        ans++;
        return;
    }
    const int mid=(l+r)/2;
    solve(l,mid);
    solve(mid+1,r);
    for(register int i=mid;i>=l;i--) {
        if(++cnt[a[i]]>(mid-i+1)/2) {
            if(!pos[a[i]]) {
                num[pos[a[i]]=++num[0]]=a[i];
            }
        }
    }
    for(register int i=mid+1;i<=r;i++) {
        if(++cnt[a[i]]>(i-mid)/2) {
            if(!pos[a[i]]) {
                num[pos[a[i]]=++num[0]]=a[i];
            }
        }
    }
    for(register int i=l;i<=r;i++) {
        pos[a[i]]=cnt[a[i]]=0;
    }
    for(register int i=1;i<=num[0];i++) {
        int sum=r-l+1,max=sum,min=sum;
        cnt[sum]=1;
        for(register int j=l;j<mid;j++) {
            if(a[j]==num[i]) {
                sum++;
            } else {
                sum--;
            }
            max=std::max(max,sum);
            min=std::min(min,sum);
            cnt[sum]++;
        }
        if(a[mid]==num[i]) {
            sum++;
        } else {
            sum--;
        }
        for(register int i=min;i<=max;i++) {
            cnt[i]+=cnt[i-1];
        }
        for(register int j=mid+1;j<=r;j++) {
            if(a[j]==num[i]) {
                sum++;
            } else {
                sum--;
            }
            ans+=cnt[std::min(max,sum-1)];
        }
        for(register int i=min;i<=max;i++) {
            cnt[i]=0;
        }
    }
    num[0]=0;
}
int main() {
    const int n=getint(); getint();
    for(register int i=1;i<=n;i++) {
        a[i]=getint();
    }
    solve(1,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：super蒟蒻 (赞：19)

蒟蒻提供一种 $n \sqrt n$ 的算法。

先考虑部分分怎么做。

对于 $type=1$ ，先计算众数为 $1$ 的有多少区间，如果做一个前缀和，就是在问有多少对 $(L,R)$ 满足： $L<=R$ 且 $sum_R-sum_{L-1}> \frac {R-L+1}{2}$。

变一下柿子为：$2*sum_R-R>2*sum_{L-1}-(L-1)$。

枚举 $R$ ，用树状数组这些数据结构维护就好，时间复杂度 $O(n \log n)$ 。

不过为了后面的根号算法能过，还得优化一下这个计算过程，想办法丢掉一个 $\log$ 。

考虑到 $R-1$ 往后移一位，$sum_R$ 要么等于 $sum_{R-1}+1$ ，要么等于$sum_{R-1}$ ，那么 $2*sum_R-R$ 的值相对于 $2*sum_{R-1}-(R-1)$ 就会 $+1$ 或者 $-1$，就可以根据**已经计算好的 $R-1$ 的贡献来修改**进而得到 $R$ 的贡献。

怎么修改？

这样一来查询的区间只会往左或往右移一位，那么就得知道多出来的一位或少了的一位贡献是多少，得到对应的变化量，开个桶记录一下所有的 $2*sum_x-x$ 的相同的有多少个（$x<R$）就能进行修改了。（看文字没明白的画个图就懂啦）

这样就能做到 $O(n)$ 求解。

对于 $type=3$ ，最多只有 $8$ 个数字，同样枚举众数，把枚举的数所在的位置改成 $1$ ，其余为 $0$ ，解法同 $type=1$ 的情况。

对于 $type=2$ ，意味着满足条件的区间长度最长不超过 $30$ ，可以暴力扫这些区间算答案，时间复杂度 $O(30n)$。

接下来就是根号算法啦！

上面的两种做法区别在于一个是针对数字种类，一个是针对数字出现次数。

不妨对每个数字出现的出现次数分个类。

对于所有 $ cnt_x \le \sqrt n $ 的数字 $x$，我们就暴力扫长度为 $2 \sqrt n $ 的区间，所有这些数字的贡献都会被算到。（注意不要算了出现次数大于 $\sqrt n$ 的数字的贡献 ），时间复杂度 $O(n \sqrt n)$ 。

对于 $ cnt_x \geq \sqrt n $ 的，用 $type=1$ 的做法做，这些不同的数字最多不会超过 $\sqrt n$ 个，时间也是 $O(n \sqrt n)$ 。

如果你不想用 $type=1$ 的优化而是直接用树状数组，似乎也能过 ... ...

$code:$

```
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
int read() {
	char ch=getchar();int x=0,pd=0;
	while(ch<'0'||ch>'9') pd|=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return pd?-x:x;
}
const int maxn=505005;
int _max(int a,int b) { return a<b?b:a; }
int _min(int a,int b) { return a<b?a:b; }
int n,type;
int a[maxn];
int cnt[maxn],vis[maxn],cnt2[maxn];
int s1[maxn];
LL ans;
int main() {
	n=read(),type=read();
	for(int i=1;i<=n;i++) ++vis[a[i]=read()];
	int size=sqrt(n),limit=size*2;
	for(int i=1;i<=n;i++) {
		int maxx=0;
		for(int j=i;j<i+limit&&j<=n;j++) {
			if(vis[a[j]]<=size) maxx=_max(maxx,++cnt[a[j]]);
			if(maxx>(j-i+1)/2) ++ans;
		}
		for(int j=i;j<i+limit&&j<=n;j++)
			if(vis[a[j]]<=size) --cnt[a[j]];
	}
	for(int num=0;num<n;num++)
		if(vis[num]>size) {
			for(int i=0;i<=n+15;i++) cnt2[i]=0;
			int minn=0x3f3f3f3f;
			for(int i=1;i<=n;i++) {
				s1[i]=s1[i-1]+(a[i]==num);
				minn=_min(minn,2*s1[i]-i);
			}
			int p=1-minn+1,sum=0;
			cnt2[p]=1; // 有负数，加个偏移量 
			for(int i=1;i<=n;i++) {
				if(s1[i]==s1[i-1]) sum-=cnt2[ 2*s1[i-1]-(i-1)-1+p ];
				else sum+=cnt2[ 2*s1[i-1]-(i-1)+p ];
				++cnt2[2*s1[i]-i+p];
				ans+=sum;
			}
		}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：vectorwyx (赞：15)

严格线性，不用并查集，不用差分。

考虑枚举绝对众数 $x$，定义新序列 $b_i=\begin{cases}1&a_i=x\\-1& a_i\not=x \end{cases}$。问题变为求 $b$ 序列中和为正的子段数。

暴力的想法是扫一遍 $b$，转成求前缀和序列的“顺序对”数，但这样会超时。根据经验，我们希望只保留有可能产生贡献的位置，对这些位置组成的若干连续段进行计算。什么样的位置可能产生贡献呢？考虑把所有 $+1$ 组成的连续段和 $-1$ 组成的连续段缩起来，dp 求出以第 $i$ 个 $+1$ 连续段为结尾的最大子段和 $f_i$ 以及以第 $i$ 个 $+1$ 连续段为开头的最大子段和 $F_i$（允许空子段，即 $f_i,F_i\ge 0$），对于一个长为 $\mathit{len}$ 的 $-1$ 连续段，如果它两边的 $+1$ 连续段 $i,i+1$ 满足 $f_i+F_{i+1}>\mathit{len}$，这个 $-1$ 连续段中的所有位置都是有意义的，直接把它和两边的 $+1$ 连续段缩在一起。否则这个连续段中一定有无意义的位置，它会隔断两个 $+1$ 连续段。记 $c_x$ 为 $x$ 的出现次数，此过程的复杂度为 $O(c_x)$。

剩下的任务就是对缩出来的连续段分别计算它们前缀和序列的“顺序对”数，由于前缀和的变化只有 $\pm 1$，所以可以利用桶由前一个位置的贡献推出下一个位置的贡献。复杂度 $O(\mathit{len})$。接下来只需证明对于每个 $x$，被额外缩进来的 $-1$ 的数量为 $O(c_x)$。

证明：记一个连续段的势能为以它为开头的最大子段和加上以它为结尾的最大子段和。那么初始时所有 $+1$ 连续段的势能均为 $2\mathit{len}$，同时，对于两个首尾相邻的连续段，它们并起来的连续段的势能是各自的势能相加。考虑合并两个 $+1$ 连续段的过程，相当于在第一个连续段的后面不断插入 $-1$，在第二个连续段的前面不断插入 $-1$，然后在中间某个位置汇合。而如果开头的最大子段和大于 $0$，在开头插入一个 $-1$ 对势能带来的影响是 $-1$，否则为 $0$。结尾插入 $-1$ 同理。由前文提到的限制，总可以找到一个汇合点使得两个连续段在插入 $-1$ 的过程中不会出现势能不变的情况。于是把两个连续段缩起来时，每有一个 $-1$ 被额外缩起来总势能就会 $-1$，而初始时所有连续段的势能为 $2c_x$，所以缩进来的 $-1$ 数量为 $O(c_x)$。

于是总复杂度为 $O(\sum c_x)=O(n)$。

代码如下（码字不易，给个赞再走好不好QAQ）：

```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

//20:40~20:57,20:57~21:00

const int N=5e5+5;
int a[N],n,f[N],F[N],cnt[N],cnt_[N];
ll ans;
vector<int> g[N];

ll calc(int l,int r,int X){
	#define cnt(x) (x<0?cnt_[-(x)]:cnt[x])
//	printf("calc(%d,%d,%d)\n",l,r,X);
	ll ret=0,S=0;
	cnt[0]=1;
	int sum=0;
	fo(i,l,r){
		if(a[i]==X) sum++,S+=cnt(sum-1);
		else sum--,S-=cnt(sum);
		cnt(sum)++;
		ret+=S;
	}
	sum=0;
	fo(i,l,r){
		if(a[i]==X) sum++;else sum--;
		cnt(sum)=0;
	}
//	printf("ret=%lld\n",ret);
	re ret;
	#undef cnt
}

signed main(){
	cin>>n;read();
	fo(i,1,n) g[i].eb(0);
	fo(i,1,n) a[i]=read()+1,g[a[i]].eb(i);
//	cout<<"a:";out(a,1,n);
	fo(i,1,n){
		int m=(int)g[i].size()-1;
		if(m==0) co;
		f[1]=1;fo(j,2,m) f[j]=max(1,f[j-1]-(g[i][j]-g[i][j-1]-1)+1);
		F[m]=1;go(j,m-1,1) F[j]=max(1,F[j+1]-(g[i][j+1]-g[i][j]-1)+1);
//		printf("%d!!!!!\n",i);cout<<"f:";out(f,1,m);cout<<"F:";out(F,1,m);
		int lst=1;
		fo(j,1,m-1) if(g[i][j+1]-g[i][j]-1>=f[j]+F[j+1]){
			ans+=calc(max(1,g[i][lst]-F[lst]),min(n,g[i][j]+f[j]),i);
			lst=j+1;
		}
		ans+=calc(max(1,g[i][lst]-F[lst]),min(n,g[i][m]+f[m]),i);
	}
	cout<<ans;
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```





---

## 作者：shadowice1984 (赞：14)

人傻常数大……

只是理论复杂度$O(nlogn)$实际上被$O(nlog^2n)$的解法爆踩

_________________

## 本题题解

题意简单明了，求区间众数出现次数过半的子区间数目

那么我们会发现这是一个非常奇怪的限制，为什么一定要过半呢?

答案是这个条件保证了“新生舞会”的区间的众数是唯一的~~(那个相同就取最小的限制是唬你的)~~

因此我们可以尝试枚举所有可能的众数值k，然后统计众数为k的新生舞会的区间有多少个，最后将这些数加起来就是我们要求的“新生舞会”的区间的总数目了

好了那么问题来了我们怎么求呢？

一个简明易懂的想法是我们将所有等于k的数设成1，所有不是k的数字设成-1，然后我们会发现这个序列变成了一个+1,-1序列，此时众数为k的一个“新生舞会”的区间，和这个转化后的序列上一个区间和大于0的区间是一一对应的，因此我们只需求出这个序列有多少子区间和为0即可了

发现还是不好做，那么让我们接着转化

我们采取求区间和的经典套路，将区间和表示成两个前缀和相减的形式

那么我们要做的是对于每个i求出有多少j满足$sum_{i}>sum_{j}$且$i>j$这样的话就可以满足$[j+1,i]$这个区间和大于0了

换句话说就是求前缀和序列的顺序对个数咯

那么此时那个$A_{i}<=7$的部分分就非常可做了

**每次暴力扫一遍整个序列，树状数组求一遍顺序对即可了**

好了但是这个东西放到$A_{i}$无限制这个东西上面就立马炸了

考虑一下为什么会炸

假设我们在做一个1很少-1很多的序列

那么你会发现前缀和数组很多地方是一个公差为-1的等差数列

因为我们求的是顺序对，所以你会发现这段区间的顺序对显然是0

这样就非常的不好了……

所以我们考虑你线段树求逆序对的过程

**foreach i**

 _1.ans+=线段树上$0,sum_{i}-1$的区间和_ 

 _2.在线段树$sum_{i}$的位置加上1_ 

然后我们现在尝试这将每一段等差数列一口气加到线段树里面

可以发现的是对应的修改应该是线段树上一段区间+1

并且发现另一个更为有趣的事实是由于每次插入的数刚好比前一个数少1，所以前面的数字有没有被插入根本不影响求区间和的过程

然后我们尝试着求出这个等差数列(从st到ed)对于答案的贡献，其中$cnt_{j}$
是线段树所维护的数组


可以发现是这个式子

$$\sum_{i=st}^{ed}\sum_{j=- \infty}^{i-1}cnt_{j}$$

简单的交换一发求和号就是

$$(ed-st+1)\sum_{i= -\infty}^{st-1}cnt_{i}+\sum_{i=st}^{ed}(ed-i)cnt_{i}$$

所以我们只需要用线段树维护$cnt_{i}$以及$i×cnt_{i}$的和就行了,线段树所资瓷的操作是区间加

当然，对于那些不属于等差数列的前缀和点，我们求线段树的区间和，然后单点加就行了

这样的话,我们会发现对于每一个众数的值复杂度为$O(mlogn)$m为这个值在序列中的出现次数

所以总复杂度是$O(nlogn)$常数奇大无比，又加上我人懒直接吧线段树的值域开成了2n常数就更大了……

上代码

```C
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;const int N=5*1e5+10;typedef long long ll;
vector <int> po[N];int n;ll ans;int t;
struct linetree//线段树
{
	ll sum[8*N];ll isum[8*N];ll add[8*N];
	inline void pd(int p,int l,int r)
	{
		if(add[p]==0)return;int mid=(l+r)/2;int l1=mid-l;int l2=r-mid;
		sum[p<<1]+=add[p]*l1;add[p<<1]+=add[p];isum[p<<1]+=(add[p]*(l+1)+add[p]*mid)*l1/2;
		sum[p<<1|1]+=add[p]*l2;add[p<<1|1]+=add[p];isum[p<<1|1]+=(add[p]*(mid+1)+add[p]*r)*l2/2;add[p]=0;
	} 
	inline void ud(int p){sum[p]=sum[p<<1]+sum[p<<1|1];isum[p]=isum[p<<1]+isum[p<<1|1];}
	inline void setadd(int p,int l,int r,int dl,int dr,ll ad)
	{
		if(dl==l&&dr==r){sum[p]+=ad*(r-l);isum[p]+=(ad*(l+1)+ad*r)*(r-l)/2;add[p]+=ad;return;}	
		pd(p,l,r);int mid=(l+r)/2;
		if(dl<mid)setadd(p<<1,l,mid,dl,min(dr,mid),ad);
		if(mid<dr)setadd(p<<1|1,mid,r,max(dl,mid),dr,ad);ud(p);
	}
	inline ll gsum(int p,int l,int r,int dl,int dr,ll* val)
	{
		if(dl==l&&dr==r)return val[p];pd(p,l,r);int mid=(l+r)/2;ll res=0;
		if(dl<mid)res+=gsum(p<<1,l,mid,dl,min(dr,mid),val);
		if(mid<dr)res+=gsum(p<<1|1,mid,r,max(dl,mid),dr,val);return res;
	}
	inline void ins(int l,int r){setadd(1,0,2*n,n+l,n+r,1);}
	inline void ins(int x){setadd(1,0,2*n,n+x-1,n+x,1);}
	inline void del(int l,int r){setadd(1,0,2*n,n+l,n+r,-1);}
	inline void del(int x){setadd(1,0,2*n,n+x-1,n+x,-1);}
	inline ll csum(int l,int r,ll* val){return gsum(1,0,2*n,n+l,n+r,val);}
}lt;
inline void calc(ll st,ll ed)
{ans+=(ed-st+1)*lt.csum(-n,st-1,lt.sum)+(ed+n)*lt.csum(st-1,ed,lt.sum)-lt.csum(st-1,ed,lt.isum);}
int main()
{
	scanf("%d%d",&n,&t);
	for(int i=1,t;i<=n;i++)scanf("%d",&t),po[t].push_back(i);lt.ins(0);
	for(int i=0;i<n;i++)//大力分情况讨论一下插入的等差序列就行了
	{	
		if(po[i].empty())continue;int up=po[i].size();
		if(po[i][0]!=1)lt.ins(-po[i][0],-1);ans++;lt.ins(-po[i][0]+2);
		for(int j=1,st,ed;j<up;j++)
		{
			st=2*j-po[i][j]+1;ed=2*j-po[i][j-1]-1;
			if(st<=ed)calc(st,ed),lt.ins(st-1,ed);ans+=lt.csum(-n,st,lt.sum);lt.ins(st+1);
		}int ed=2*up-po[i][up-1]-1;int st=2*up-n;if(st<=ed)calc(st,ed);
		if(po[i][0]!=1)lt.del(-po[i][0],-1);lt.del(-po[i][0]+2);
		for(int j=1,st,ed;j<up;j++)
		{st=2*j-po[i][j]+1;ed=2*j-po[i][j-1]-1;if(st<=ed)lt.del(st-1,ed);lt.del(st+1);}
	}printf("%lld",ans);return 0;
}
```




 
 




---

## 作者：zhongqijun (赞：8)

### P4062 [Code+#1]Yazid 的新生舞会 维护三阶前缀和


[P4062 [Code+#1]Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062)

#### 发现偏序性质

我们希望统计“新生舞会”子区间，先要发现它的性质。

从简单的情况入手，例如考虑只有 0 和 1 的序列，如果统计 1 的“新生舞会”子区间，那么条件是 $cnt(l,r)>\lfloor\dfrac{r-l+1}{2}\rfloor$ . 自然地，我们想到维护一个前缀和快速求得 $cnt(l,r)$ ，记 $S_i$ 表示 $[1,i]$ 中 1 的个数，那么上式改写为：
$$
\begin{aligned}
S_r-S_{l-1}&>\dfrac{r-l+1}{2}\\[2ex]
2S_r-r &> 2S_{l-1}-(l-1)
\end{aligned}
$$
于是我们发现，只要统计满足以上偏序关系的偏序对的个数就能得到 1 的“新生舞会”子区间个数。

#### 利用等差数列性质改进算法

但是如果对每一个数都做一遍统计，不难发现其复杂度是 $O(n^2)$ 的，我们需要改进复杂度。

继续从简单情况入手，我们观察 $2S_i-i$ 的性质：

|   $i$    |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |
| :------: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  $a_i$   |  0   |  0   |  1   |  0   |  1   |  1   |  0   |  0   |
| $2S_i-i$ |  -1  |  -2  |  -1  |  -2  |  -1  |  0   |  -1  |  -2  |

我们可以发现一个重要性质：**$2S_i-i$ 总是以 $a_i=1$ 的位置为开头或者结尾组成一段公差为 $-1$ 的等差序列。**

可以发现 $[1,2]$，$[3,4]$，$[5,5]$，$[6,8]$ 的 $2S_i-i$ 都组成了等差序列，那么如何利用这个性质？首先一个显然的结论是等差序列内部不会对答案产生贡献，因为内部总是递减，一定不满足之前推出的偏序关系，所以我们如果考虑插入等差序列（每一个数都作为一段等差序列的开头或者结尾 $O(n)$） 并查询等差序列与前面的等差序列产生的贡献（期望 $O(n\log n)$），就可能解决此题。

#### 思考插入等差序列和查询答案的实现细节

现在做一个小推广，假设统计以下序列中，5 的“新生舞会”子区间

|  $i$  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |
| :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| $a_i$ |  1   |  2   |  5   |  3   |  5   |  5   |  4   |  2   |

显然将 5 看作 1，其它数看作 0 就是上一个表格的情况。插入一段由 $a_i$ 中 $[3,4]$ 对应的 $2S_i-i$ 组成的等差序列 等价于给 $2S_i-i$ 的值域区间 $[-1,-2]$ 加上权值 1 ，也就是区间加。查询等差序列 $[3,4]$ 与前面产生的贡献就是：求等差序列中，每一个数与前面满足偏序关系的数的个数之和。例如这个例子，就是统计前面与 $-1$ 满足偏序关系的 $2S_i-i$ 的个数加上前面与 $-2$ 满足偏序关系的 $2S_i-i$ 的个数。

那么用简洁的表达式表达，就是：

记 $v(x)$ 为 $2S_i-i = x$ 的 $i$ 个数，也就是 $x$ 的权值；令 $p=2S_l-l$ 为等差序列开头的那个数 ,令 $q=2S_r-r$ 为等差序列结尾的那个数，那么由 $[l,r]$ 中的 $ 2S_i-i$ 组成的等差序列与前面的等差序列产生的贡献就是：
$$
\sum_{q\leqslant k\leqslant p}\sum_{t < k} v(t)
$$
为了提高运算速度，考虑用前缀和优化，并用树状数组维护前缀和。记 $g(x)=\sum_{k\leqslant x} v(k)$ ，是 $2S_i-i\leqslant x$ 的 $i$ 的个数，也就是 $v(x)$ 的前缀和；记 $h(x) = \sum_{k\leqslant x} g(k)$ ，表示对于所有 $2S_i-i\leqslant x$ 的 $2S_i-i$ ，满足 $2S_j-j\leqslant 2S_i-i$ 的 $j$ 的个数之和，也就是 $g(x)$ 的前缀和；用上面的例子，我们知道查询 $[3,4]$ 组成的等差序列与前面的贡献就是 $h((-1)-1)-h((-2)-2)$ 。普遍意义下，查询开头为 $p=2S_l-l$ ，结尾为 $q=2S_r-r$ 的等差序列与前面的贡献是 $h(p-1)-h(q-2)$ ，这样就能求得答案。

于是我们可以制作下表：

| $x=S_i-i$ |  -3  |  -2  |  -1  |  0   |  1   |
| :-------: | :--: | :--: | :--: | :--: | :--: |
|  $v(x)$   |  0   |  1   |  1   |  0   |  0   |
|  $g(x)$   |  0   |  1   |  2   |  2   |  2   |
|  $h(x)$   |  0   |  1   |  3   |  5   |  7   |

#### 维护三阶前缀和

然后考虑加入一段等差序列的问题：上面也已经说了，插入一段以 $[l,r]$ 中的 $ 2S_i-i$ 组成的等差序列等价于在 $2S_i-i$ 的权值域 $v$ 中对区间 $[2S_r-r,2S_l-l]$ 区间加 1.于是我们考虑对 $v$ 区间加 1 后，对 $h$ 有什么影响就好了，这里的思考思路参考《挑战程序设计竞赛》中处理树状数组区间加和区间查询的思路。

现在我们将目光转向 $v,g,h$ 三个函数，以下的 $[l,r]$ 都是指三个函数的定义域 $x = S_i-i$ 上的区间（前面的是指 $a_i$）

考虑令满足 $l\leqslant x\leqslant r$ 的 $v(x)$ 全部加 1.

记操作前的 $x$ 对应的 $g$ 函数为 $g(x)$ ，操作后为 $g'(x)$ ，$h$ 函数同理。分类讨论：

- $x<l$ ，则 $g(x)$ 和 $h(x)$ 不受影响，即 $g'(x)=g(x),h'(x)=h(x)$

- $l\leqslant x\leqslant r$ ，则
  $$
  \begin{aligned}
  g'(x) &= g(x)+x-l+1\\[2ex]
  h'(x) &= h(x)+\sum_{k = l}^{x} (k-l+1)\\[1ex]
  &=h(x)+\dfrac{(x-l+1)(x-l+2)}{2}\\[1ex]
  &= h(x) + \dfrac{1}{2}\left(x^2+(3-2l)x+l^2-3l+2\right)
  \end{aligned}
  $$
  可以借用上面给出的表格与例子推一推。

- $r<x$ ，则
  $$
  \begin{aligned}
  g'(x) &= g(x) + r-l+1\\[2ex]
  h'(x)&=h(x) + \sum_{k=l}^r(k-l+1)+(x-r)(r-l+1)\\[1ex]
  &=h(x) + \dfrac{(r-l+2)(r-l+1)}{2}+(x-r)(r-l+1)\\[1ex]
  &= h(x) + \dfrac{1}{2}\left(2(r-l+1)x+(r-l+2)(r-l+1)-2r(r-l+1)\right)
  \end{aligned}
  $$

然后我们发现，变化量与 $x^2$ ，$x$ 和常数项（$x^0$）有关，于是用三个树状数组 $\rm{bit0}$，$\rm{bit1}$，$\rm{bit2}$ 分别维护这三项，具体做法是：

对于 $[l,r]$ 区间加 1：

- 令 ${\rm{bit0}}(l)$ 加上 $l^2-3l+2$；令 ${\rm bit1}(l)$ 加上 $3-2l$ ；令 ${\rm bit2}(l)$ 加上 $1$
- 令 ${\rm bit0}(r + 1)$ 加上 $(r-l+2)(r-l+1)-2r(r-l+1)-(l^2-3l+2)$ ；令 ${\rm bit1(r + 1)}$ 加上 $2(r-l+1)-(3-2l)$ ；令 ${\rm bit2}(r + 1)$ 加上 $-1$

查询的时候，例如查 $h(x)$ 就是 
$$
h(x)=\dfrac{\operatorname{Query}({\rm bit0},x)+\operatorname{Query}({\rm bit1},x)\times x+\operatorname{Query}({\rm bit2},x)\times x^2}{2}
$$
这里乘上 $\dfrac{1}{2}$ 是因为我们刚刚修改的时候没有乘上 $\dfrac{1}{2}$ .

以上式子还要慢慢理解。这里再放出一张图，用于理解二阶前缀和的变化，也就是 $g(x)$ 的变化，至于 $h(x)$ 的变化，确实需要一定的数学功底与思维能力理解（这几条式子我也推了很久，推了 2h ，而且有几次推错了，甚至有几次多项式相乘展开都算错了，我数学太菜了...）


![](https://cdn.luogu.com.cn/upload/image_hosting/lelejeyr.png)


#### 整理思路，解决问题

综上所述，我们就可以将记录一种数出现的所有位置，然后将原序列简化为仅包含 0 和 1 的序列，维护一下 $h(x)$ 并统计答案，逐个击破即可。最后要注意的就是不要傻傻地将负数作为下标了，设置一个偏移量 $\Delta$ 就可以避免数组越界地情况。时间复杂度 $O(n\log n)$

#### 参考程序

```cpp
#include<iostream>
#include<cstdio>
#include<vector> 

using namespace std;
typedef long long ll;
const ll dlt = 500003;
ll ans,t[5][1000010];
int n,type,x;
vector<ll > a[500005];

int lowbit(int num)
{
	return num&(-num);
}

void bitadd(int ty,int i,ll val)
{
	for(;i <= n + dlt;i += lowbit(i)) t[ty][i] += val;
	return ;
}

ll bitq(int ty,int i)
{
	ll res = 0;
	for(;i;i -= lowbit(i)) res += t[ty][i];
	return res;
}

ll BIT_Query(ll num)
{
	ll res = 0;
	res = ((bitq(0,num) + bitq(1,num)*num + bitq(2,num)*num*num)/2);
	return res;
}

void BIT_Add(ll l,ll r,ll val)//维护三个树状数组
{
	ll tmp0 = l*l - (ll)3*l + (ll)2;
	ll tmp1 = (ll)3 - l - l;
	ll tmp2 = (ll)1;
	bitadd(0,l,tmp0*val);
	bitadd(1,l,tmp1*val);
	bitadd(2,l,tmp2*val);
	tmp0 = -tmp0 + (r - l + (ll)1)*(r - l + (ll)2) - (ll)2*r*(r - l + (ll)1) ;
	tmp1 = -tmp1 + (ll)2*(r - l + (ll)1);
	tmp2 = -tmp2;
	bitadd(0,r + 1,tmp0*val);
	bitadd(1,r + 1,tmp1*val);
	bitadd(2,r + 1,tmp2*val);
	return ;
}

void solve(ll num)
{
	ll cnt = 0;ll lt = 0;ll rt = 0;
	BIT_Add(dlt,dlt,1);\\dlt 是偏移量
	if(a[num][0] > 1) lt = -a[num][0] + 1 ,rt = -1,BIT_Add(lt + dlt,rt + dlt,1); 
	for(int i = 0;i < a[num].size() - 1;i ++)//插入，查询，统计答案
	{
		cnt ++;rt = cnt + cnt - a[num][i];lt = cnt + cnt - a[num][i + 1] + 1;
		ans += BIT_Query(rt - 1 + dlt) - BIT_Query(lt - 2 + dlt);
		BIT_Add(lt + dlt,rt + dlt,1);
	}
	cnt = 0;
	BIT_Add(dlt,dlt,-1);
	if(a[num][0] > 1) lt = - a[num][0] + 1,rt = -1,BIT_Add(lt + dlt,rt + dlt,-1);
	for(int i = 0;i < a[num].size() - 1;i ++)//清空树状数组
	{
		cnt ++;lt = cnt + cnt - a[num][i + 1] + 1;rt = cnt + cnt - a[num][i];
		BIT_Add(lt + dlt,rt + dlt,-1);
	}
	return ;
}

int main()
{
	scanf("%d%d",&n,&type);
	for(int i = 1;i <= n;i ++)
	{
		scanf("%d",&x);
		a[x].push_back(i);//记录位置
	}
	for(int i = 0;i <= n;i ++)//逐个击破
		if(!a[i].empty())
		{
			a[i].push_back(n + 1);
			solve(i);
		}
	printf("%lld",ans);
	return 0;
 } 
```



---

## 作者：FutaRimeWoawaSete (赞：7)

有人此题 5min 胡单 log，却调了 2h，我不说是谁。

有的人退役是顺其自然的事，因为他丧失的是代码能力，而且是写傻卵题的代码能力。

-------------------------------------------------------

考虑对于严格众数的 trick，像摩尔投票，概率选点做区间数颜色这些 trick 缺少对于具象问题的刻画，只能单纯维护区间的合法性，所以自然而然地想到枚举绝对众数，用区间和来判断区间合法性这一常见 trick。

枚举严格众数，将当前枚举的颜色设为 $+1$，其它颜色设为 $-1$，用前缀和，我们发现，若 $[l,r]$ 合法在当前的充要条件是 $sum_{r} - sum_{l - 1} > 0$。

即，问题变成了求当前序列的全局正序对。

一个自然的想法是根号分治后大于阈值的用数据结构维护全局正序对，小于阈值的暴力枚举区间，但是时间复杂度并不优秀，考虑 polylog 做法。

我们发现，事实上对于每种颜色，其将序列划分成了若干个段，每一段的前缀和形如一个等差数列。

于是就很好做了，使用线段树维护每个位置，当前加入一个数时前面有多少个数小于它，问题转化成了区间等差数列加，区间和，该半群信息可以通过线段树 lazytag 形式维护。

再稍微推一下就有 $O(n)$ 的做法了，但是个人感觉没什么必要。

时间复杂度 $O(n \log n)$。

```cpp
/*
考虑直接枚举颜色，尝试去统计一下。
那么就是求有多少个子区间和是 > 0。
如果要根号分治的话难点就是线性扫，考虑先滚个前缀和，然后就是全局的顺序对个数，那就必须带 log 了。
考虑正常一点的做法。不妨从 > B 的角度出发。
不妨重新考虑一下这个东西，对每种颜色单独考虑我们发现，间隙之间的 sum 是递减的，所以一定可以维护成一个合并信息
不妨倒置一下信息，交换维护与查询信息，写成区间加加等差数列的形式。
还要区间求和。
O(n \log n)
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
#define int ll
#define ll long long
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
int n,m,a[Len],tp;
ll sum[Len << 2],tag[Len << 2],tagd[Len << 2],gat[Len << 2];
//i < j,sum_i < sum_j
inline void push_up(int p){sum[p] = sum[ls(p)] + sum[rs(p)];}
inline void cgd(int p,int w,int d,int len){sum[p] += 1ll * (w + w + 1ll * (len - 1) * d) * len / 2;tag[p] += w , tagd[p] += d;}
inline void cg(int p,int w,int len){sum[p] += 1ll * len * w;gat[p] += w;}
inline void push_down(int p,int l,int r)
{
    if(tag[p] || tagd[p])
    {
        int mid = (l + r) >> 1;
        cgd(ls(p) , tag[p] , tagd[p] , mid - l + 1) , cgd(rs(p) , tag[p] + (mid - l + 1) * tagd[p] , tagd[p] , r - mid);
        tag[p] = 0;tagd[p] = 0;
    }
    if(gat[p])
    {
        int mid = (l + r) >> 1;
        cg(ls(p) , gat[p] , mid - l + 1) , cg(rs(p) , gat[p] , r - mid);
        gat[p] = 0;
    }
}
//3 + 3 = 6
void update_d(int p,int l,int r,int nl,int nr,int w,int d)
{
    if(nl <= l && nr >= r)
    {
        cgd(p , w + 1ll * (l - nl) * d , d , r - l + 1);
        return;
    }
    push_down(p , l , r);
    int mid = (l + r) >> 1;
    if(nl <= mid) update_d(ls(p) , l , mid , nl , nr , w , d);
    if(nr > mid) update_d(rs(p) , mid + 1 , r , nl , nr , w , d);
    push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int w)
{
    if(nl <= l && nr >= r){cg(p , w , r - l + 1);return;}
    push_down(p , l , r);
    int mid = (l + r) >> 1;
    if(nl <= mid) update(ls(p) , l , mid , nl , nr , w);
    if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , w);
    push_up(p);
}
ll query(int p,int l,int r,int nl,int nr)
{
    if(nl <= l && nr >= r) return sum[p];
    push_down(p , l , r);
    int mid = (l + r) >> 1;ll res = 0;
    if(nl <= mid) res += query(ls(p) , l , mid , nl , nr);
    if(nr > mid) res += query(rs(p) , mid + 1 , r , nl , nr);
    return res;
}
inline ll Q(int l,int r){return query(1 , 0 , (n * 2) , l , r);}
struct Node
{
    int op,l,r,w,d;
    Node(){op = l = r = w = d = 0;}
    Node(int OP,int L,int R,int W,int D){op = OP , l = L , r = R , w = W , d = D;}
};
void build(int p,int l,int r)
{
	tag[p] = sum[p] = gat[p] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
vector<int> vec[Len];
signed main()
{
    scanf("%lld %lld",&n,&tp);
    for(int i = 1 ; i <= n ; i ++) 
    {   
        scanf("%lld",&a[i]);
        vec[a[i]].push_back(i);
    }
    ll as = 0;update(1 , 0 , n * 2 , n + 1 , (n * 2) , 1);
    for(int i = 0 ; i <= n ; i ++)
    {
        vector<Node> vc;int suf = 0;
        //if(i != 2) continue;
        for(int j = 0 ; j < (int)vec[i].size() ; j ++)
        {
            int x = vec[i][j];
            if(!j && x != 1) 
            {
            	int len = x - 1;
            	//[n - len , n - 1]
            	//对于 [n , n * 2] 贡献为 len
            	//对于 [n - len + 1 , n - 1] 贡献为 1 开始的等差数列
				update(1 , 0 , n * 2 , n , n * 2 , len) , vc.push_back(Node(0 , n , n * 2 , len , 0));
				if(n - len + 1 <= n - 1) update_d(1 , 0 , n * 2 , n - len + 1 , n - 1 , 1 , 1) ,  vc.push_back(Node(1 , n - len + 1 , n - 1 , 1 , 1));
			}
            if(j == (int)vec[i].size() - 1) suf = n;
            else suf = vec[i][j + 1] - 1;
            //[sm - len + 1,sm]
            int len = suf - x + 1 , sm = n + j + 1 - (x - (j + 1));
            //printf("!!!%d %d\n",sm - len + 1,sm);
    		//对于 [sm + 1 , n * 2] 贡献为 len
			//对于 [sm - len + 2 , sm] 贡献为从 1 开始的等差数列
			as += Q(sm - len + 1 , sm);
			update(1 , 0 , n * 2 , sm + 1 , n * 2 , len) , vc.push_back(Node(0 , sm + 1 , n * 2 , len , 0));
			if(sm - len + 2 <= sm) update_d(1 , 0 , n * 2 , sm - len + 2 , sm , 1 , 1) ,  vc.push_back(Node(1 , sm - len + 2 , sm , 1 , 1));
        }
        for(int j = 0 ; j < (int)vc.size() ; j ++)
        {
            if(!vc[j].op) update(1 , 0 , n * 2 , vc[j].l , vc[j].r , -vc[j].w);
            else update_d(1 , 0 , n * 2 , vc[j].l , vc[j].r , -vc[j].w , -vc[j].d);
        }
    }
    printf("%lld\n",as);
    return 0;
}
//[3,4,5]
```

---

## 作者：WeLikeStudying (赞：6)

- 此题为开摆计划 T1。
- 某些给我点踩的~~好自为之~~。

**[题意](https://www.luogu.com.cn/problem/P4062)**
- 给出一个数列，找出所有存在布尔什维克数（大于 $n/2$）的区间。

**做法 1**
- $O(n^2)$ 做法过于逊，不讲。
- 下面的其它做法都以枚举颜色而非枚举区间，这告诉我们多角度思考的重要性。

**做法 2**
- 首先，布尔什维克数它是一个数！所以我们尝试枚举它。
- 出现次数大于 $\sqrt n$ 的我们称为布数，否则称为孟数。
- 对于布数，$O(n)$ 求前缀和，那么我们的判定就是：
$$2(S(r)-S(l))> r-l$$
$$2S(r)-r> 2S(l)-l$$
- 看似是二维偏序不可以快速计算，但是你发现，我们每次查询的位置变换幅度很小：加一或减一，我们可以在这里动态维护前缀和更新，这里的复杂度是 $O(n)$ 的。
- 接下来是对于孟数，我们可以平方枚举以任意两个点为重心向外拓展的方案数，这个时候我们需要用到一开始的式子。
$$2(S(r)-S(l))> r-l$$
- 我们可以得到区间的最大长度，然后接下来变成一个经典的问题（可以 $O(1)$ 计算）：
$$\sum_{i=1}^n\sum_{j=1}^m[i+j\le k]$$
- 综上，总的复杂度为 $O(n\sqrt n)$，[代码](https://www.luogu.com.cn/paste/inixjoyw)。
- 有更优的解法吗？显然有。

**做法 3**
- 真的就不可以有关于颜色数的更好的做法了吗？
- 让我们看看一开始那个做法，当没有颜色的时候，数列一定是一个递降序列，所以咱们相当于区间加，查询区间前缀查询的和。
- 这玩意当然可以魔改，由可差分性直接魔改成单点加，$3$ 阶前缀和查询，运用[这里](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/ci-fen-yu-qian-zhui-hu-di-jian-dan-ji-lu)的简单知识，我们可以得到 $O(n\log n)$ 的算法，[代码](https://www.luogu.com.cn/paste/sw772uwv)。

---

## 作者：wurzang (赞：6)

讲一个暴力点的做法。

首先发现如果一个数字是 $[l,r]$ 之间的众数的话，那么这个数字肯定是 $[l,mid]$ 之间的众数或者是 $[mid+1,r]$ 之间的众数。（其中 $mid=\left\lfloor\frac{l+r}{2}\right\rfloor$） 

于是就可以分治，对于每一个区间 $[l,r]$ 计算出经过 $mid$ 的满足题意的区间数。

直接对于每个数字暴力计算是 $\mathcal{O}(n^2 \operatorname{log}^2 n)$ 的，肯定过不去，考虑优化。

可以考虑直接挑出可能成为经过 $mid$ 的区间的众数的数字。发现这个数字数量是 $\log n$ 级别的，于是优化到 $\mathcal{O}(n\operatorname{log}^3n)$

你可能觉得3只log不可能过5e5，但因为实际上压根跑不满，于是它过了，而且还跑得飞快，还跑得比 $\sf\color{black}{L}\color{red}{imit}$ 的线段树做法快...

至于接下来怎么去做，相信很多题解里已经讲过了，我这里再复述一遍。

挑出这些数字以后，我们把问题转化为：给定一个数字 $x$，求区间 $[l,r]$ 中有多少子区间经过 $mid$，而且满足区间众数是 $x$ 且区间满足题意。

根据摩尔投票法，我们可以把每一个等于 $x$ 的地方转为 1，否则就是 -1，问题变成了求有多少子区间经过 $mid$，而且满足区间和大于0。

考虑把区间 $[l,r]$ 前缀和一下，设前缀和后第 $i$ 个点的结果为 $sum_i$，问题变成了求

$$
\sum_{i=mid}^r \sum_{j=l}^{mid-1} [sum_i>sum_j]
$$

其中 $[p]$ 表示布尔表达式，即 $p$ 是否为真。


这坨东西发现可以轻松用树状数组搞定。然后就没有然后了。


不过发现区间大小为 1 的时候容易重复计算，那么就直接加个区间大小大于 1 的限制即可，即求：

$$
\sum_{i=mid+1}^r \sum_{j=l}^{mid-1} [sum_i>sum_j]
$$

最后加上大小为 1 的区间数量即可。时间复杂度 $\mathcal{O}(n\operatorname{log}^3n)$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500000+5;
int n,tree[N<<2];
int limit;
void add(int x,int c){
	x+=n+1;
	while(x<=limit) tree[x]+=c,x+=(x&-x);  
}
int query(int x){
	int res=0;x+=n+1;
	while(x>0) res+=tree[x],x-=(x&-x);
	return res;
}
long long ans;
int cnt[N],a[N];
set<int>::iterator it;
void calc(int x,int l,int mid,int r){
	int sum=0;
	add(0,1);
	for(int i=l;i<=mid;++i){
		sum+=(a[i]==x?1:-1);
		if(i!=mid) add(sum,1);
		//cout<<sum<<" A"<<endl;
	}
	for(int i=mid+1;i<=r;++i)
		sum+=(a[i]==x?1:-1),
		//cout<<sum<<" B\n",
		ans+=query(sum-1);
	sum=0;
	for(int i=l;i<mid;++i){
		sum+=(a[i]==x?1:-1);
		add(sum,-1);
	}
	add(0,-1);
}
void query(int l,int r){
	if(l==r) return ++ans,void(0);
	int mid=(l+r)>>1;
	query(l,mid);query(mid+1,r);
	set<int> s;
	for(int i=mid+1,mx=0;i<=r;++i){
		++cnt[a[i]];
		if(cnt[a[i]]>cnt[mx]) mx=a[i],s.insert(mx);
	}
	for(int i=mid+1;i<=r;++i) --cnt[a[i]];
	for(int i=mid,mx=0;i>=l;--i){
		++cnt[a[i]];
		if(cnt[a[i]]>cnt[mx]) mx=a[i],s.insert(mx);
	}
	//out<<l<<" "<<r<<" seg\n";
	//for(int i=l;i<=r;++i)cout<<a[i]<<" ";cout<<endl;
	for(int i=mid;i>=l;--i) --cnt[a[i]];
	for(it=s.begin();it!=s.end();++it)
		//cout<<l<<" "<<r<<" "<<(*it)<<" "<<ans<<endl,
		calc(*it,l,mid,r);
}
int main(){
	int type;
	scanf("%d%d",&n,&type);limit=n+n+1;
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),a[i]=a[i]+1;
	query(1,n);
	cout<<ans;
	return 0;
}
```




---

## 作者：kcn999 (赞：5)

**提供一种 $O(n\sqrt{n})$ 的做法，不过蒟蒻常数貌似太大，T了一个点。因此，这里仅为提供一种思路，代码仅供参考。**

----

&emsp;

# 题目大意
有 $n$ 个非负整数 $a_1,a_2,\dots,a_n$ ，求有多少个区间 $[l,r]$ ，满足 $a_l,a_{l+1},\dots,a_r$ 中的众数数量**大于** $\dfrac{r-l+1}{2}$。    
其中， $1 \leq n \leq 5 \times 10^5$ ， $0 \leq a_i \leq n - 1$ 。
&emsp;

# 题解
观察部分分，当 $type = 2$ 时，容易发现，满足条件的子区间长度不超过 $2 \times 15$。   
于是我们可以从 $1$ 到 $n$ 枚举 $l$ ，在从 $l$ 到 $l + 30 - 1$ 枚举 $r$ ，枚举时不断更新当前子区间的众数，并判断是否满足条件。    
时间复杂度为 $O(30n)$ 。     
&emsp;     
继续观察部分分，当 $type = 3$ 时（ $type = 1$ 的情况实际上是 $type = 3$ 的情况的子集），不同 $a_i$ 的数量很少，最多只有 $8$ 种。        
思考若一个区间众数为 $m$ ，众数的数量为 $c(m)$ ，若这个区间满足要求，则必须保证 $c(m)$ **大于**区间长度的一半，即 $c(m) > (r - l + 1) - c(m)$ 。     
移项，得 $2c(m) > r - l + 1$ 。     
我们设区间 $[1,i]$ 中出现 $m$ 的数量为 $s(i)$ ，代入上式，得 $2\left(s(r) - s(l - 1)\right) > r - l + 1$ 。
移项，得 $2s(r) - r > 2s(l - 1) - (l - 1)$ 。     
显然我们可以用树状数组等数据结构维护 $2s(i) - i$ 。
所以我们可以先从 $0$ 到 $7$ 枚举，设当前枚举到的数为 $num$，再从 $1$ 到 $n$ 枚举 $a_i$ ，算出当前的 $2s(i) - i$ 并 ```insert``` ，每次贡献的答案为 $2s(j) - j$ 的数量，其中 $0 \leq j < i$ 且 $2s(j) - j < 2s(i) - i$ 。     
时间复杂度为 $O(8n\log n)$          
&emsp;     
然而上面的做法貌似不能过部分分，所以还要继续优化。     
观察得 $2s(i) - i = \begin{cases} 2s(i - 1) - (i - 1) + 1 & a_i = m \\ 2s(i - 1) - (i - 1) - 1 & a_i \not = m \end{cases}$     
所以我们可以不用树状数组来维护。     
我们设 $sum = \sum\limits_{j = 1}^{i}\left[2s(j) - j \leq 2s(i) - i\right]$ ，设 $t(2s(i) - i) = \sum\limits_{j = 1}^{i}\left[2s(j) - j = 2s(i) - i\right]$ 。
显然，每枚举一个 $a_i$ ， $t(2s(i) - i) \gets t(2s(i) - i) + 1$ 。     
当 $a_i = m$ 时， $sum \gets sum + t(2s(i) - i)$ ；
当 $a_i \not = m$ 时， $sum \gets sum - t(2s(i - 1) - (i - 1)) + 1$ 即 $sum \gets sum - t(2s(i) - i + 1) + 1$ 。     
显然时间复杂度为 $O(8n)$ 。     
&emsp;     
此时我们考虑 $type = 0$ 的情况即正解。 $type = 2$ 时满足条件的子区间长度较短， $type = 3$ 时满足条件的子区间内众数的种类较少。     
设满足条件的子区间的最大长度为 $p$ ，则按照 $type = 2$ 的做法来做时间复杂度为 $O(pn)$ 。     
设满足条件的子区间的众数最多数量为 $q$ ，其实就是不同 $a_i$ 的数量，则按照 $type = 3$ 做法来做时，时间复杂度为 $O(qn)$ 。     
**考虑正解，我们是否可以综合两种做法的优点？**     
直接说正解，我们设 $a_i$ 在序列里出现的次数为 $C(a_i)$ ，则我们可以先做一次 $type = 2$ 的做法，只计算 $m$ 满足 $C(m) \leq \sqrt{n}$ 的贡献，显然 $p \leq 2\sqrt{n}$ ，则这一次操作的复杂度为 $O(2n\sqrt{n})$ 。     
然后我们从 $0$ 到 $n - 1$ 枚举数 $num$ ，若 $C(num) > \sqrt{n}$ ，则做一次 $type = 3$ 的做法。     
因为 $\sum C(num)\left[C(num) > \sqrt{n}\right] \leq n$ 且我们只有满足 $C(num) > \sqrt{n}$ 时才进行操作，所以 $ q \leq \dfrac{n}{\sqrt{n}} = \sqrt{n}$ 。所以做 $type = 3$ 的做法的时间复杂度为 $O(n\sqrt{n})$ 。     
综合起来，总的时间复杂度为 $O(n\sqrt{n})$ 。
（不过我的常数太大了，在洛谷上会T一个点。。。）     

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>

#define MAX_N (500000 + 5)

using std::sqrt;
using std::memset;

int n;
int a[MAX_N];
int cnt[MAX_N], vis[MAX_N];
int t[MAX_N * 2];
long long ans;

int Read()
{
	int res = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9')
	{
		res = res * 10 + ch - '0';
		ch = getchar();
	}
	return res;
}

int main()
{
	n = Read();
	Read();
	for (int i = 1; i <= n; ++i)
	{
		a[i] = Read();
		++cnt[a[i]];
	}
	const int plus = n + 1;
	const int sqrtn = sqrt(n);
	int num, mode;
	for (int i = 1; i <= n; ++i)
	{
		num = 0;
		for (int j = i; j <= n && j - i + 1 <= sqrtn + sqrtn; ++j)
		{
			++vis[a[j]];
			if (vis[a[j]] > num) num = vis[a[j]], mode = a[j];
			if (num + num - (j - i + 1) > 0 && cnt[mode] <= sqrtn) ++ans;
		}
		for (int j = i; j <= n && j - i + 1 <= sqrtn + sqrtn; ++j)
		{
			--vis[a[j]];
		}
	}
	int cur, sum;
	for (int i = 0; i < n; ++i)
	{
		if (cnt[i] <= sqrtn) continue;
		memset(t, 0, sizeof t);
		cur = plus;
		sum = 1;
		t[cur] = 1;
		for (int j = 1; j <= n; ++j)
		{
			if (a[j] == i)
			{
				++cur;
				++t[cur];
				sum += t[cur];
			}
			else
			{
				--cur;
				++t[cur];
				sum = sum - t[cur + 1] + 1;
			}
			ans += sum - t[cur];
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：pyyyyyy (赞：5)


[P4062 Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062)

> 给定一长度为$n$的序列，求有多少子序列$[l,r]$的众数出现$\frac{r-l+1}{2}$次

- 算法一（针对$n\leq 300$）

考虑枚举所有区间，然后求其众数及出现次数，并判断是否超过区间总长的一半，统计答案即可。时间复杂度$O\left( n^3\right)$

- 算法二（$n\leq 2,000$）

考虑先枚举区间的左端点$l$，再从左到右枚举右端点$r$并用数组维护每个数的出现次数，同时使用变量维护当前众数、众数的出现次数。不难发现，当右端点向右移动时，这些信息都是非常方便维护的。于是我们便可以在$O\left( n^2\right)$的时间复杂度内统计所有答案。

- 算法三（$type=1$）

对于$01$序列，我们不难发现，众数出现次数严格大于子区间长度当且仅当子区间内$0,1$出现次数不同（那么那个出现次数较多的就是众数）。于是我们将原序列中的$0$视作$-1$，并对该序列求前缀和$S$，则子区间$[l,r]$为“新生舞会的”，当且仅当$S_r-S_{l-1}\not= 0$

有了这个性质我们就可以$O(1)$来求解子区间$[l,r]$是不是符合要求了，但是不幸的是这样仍需要枚举$l,r$，复杂度仍是$O(n^2)$。

我们不妨**反着来想**，子区间$[l,r]$**不是**“新生舞会的”，当且仅当$S_r-S_{l-1}=0$即$S_r=S_{l-1}$因此对$S$进行排序并从小到大统计相等的个数然后用总的子区间数量$\frac{n\cdot(n+1)}{2}$减去相等的个数即为答案

- 算法四（$type=2$）

对于所有数的出现次数都较小（不超过$15$）的情况，不难发现所有“新生舞会的区间”的长度也会较小（不超过$2\times 15-1=29$）。于是使用算法二，枚举所有长度少于$30$的区间并统计答案即可。

- 算法五（$type=3$）

对于$A_i\leq 7$的测试点，我们不妨枚举所有值作为众数的情况。考虑统计所有众数为$k$的“新生舞会的”区间，将所有等于$k$的位置取为$1$，不等于$k$的位置取为$-1$，得到新序列$B$并求前缀和得到序列$S$，则区间$[l,r]$需要被统计，当且仅当$S_r-S_{l-1}\geq 1$。从左到右枚举右端点，并用线段树维护当前右端点左边每种前缀和出现的次数即可。时间复杂度$O\left( 8nlogn\right)$

- 算法六（$100pts$）

考虑改进算法五。我们考虑取出所有$B$中的极长$-1$子区间，观察这些区间中的所有点作为右端点对答案的贡献。不难发现极长$-1$子区间$[l,r]$中的所有点作为右端点对答案的贡献为$\sum_{i=1}^{r-l+1}\sum_{j=-\infty}^{S_{l-1}-i-1}cnt[j]$，其中$cnt[j]$表示在区间$[0,l-1]$之间前缀和为$j$的端点数目；在统计这段区间的答案后，我们还需要对区间$[S_{i-1}-(r-l+1),S_{i-1}-1]$中的所有$cnt$均进行$+1$操作。显然地，我们使用一个维护$B_i$和$C_i=i\times B_i$的线段树就可以支持这些查询、修改操作。于是我们使用这棵线段树维护相关信息，并从左到右枚举右端点，统计答案即可。

不难发现，极长$-1$子区间的数目与序列中$k$的数目同阶，因此，对于统计众数为$k$的“新生舞会的”区间的时间开销，不难发现我们通过上述优化将时间开销缩短到了$O\left( number_k\log{n}\right)$

于是，总时间复杂度即为$O\left(\sum_{k} number_k\log{n}\right)$，即$O\left(n\log{n}\right)$。

---

## 作者：tzc_wk (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/P4062)

题意：

给出一个序列 $a$，求 $a$ 有多少个子区间 $[l,r]$，满足这个区间中出现次数最多的数出现次数 $>\dfrac{r-l+1}{2}$

$1 \leq n \leq 5\times 10^5$

首先肯定要枚举出现次数最多的数是什么，假设为 $x$。

记序列中为 $x$ 的数为 $+1$，数列中不为 $x$ 的数为 $-1$，那么 $x$ 出现次数 $>\dfrac{r-l+1}{2}$ 等价于该区间中对应的数的和 $>0$。

考虑对这个 $+1,-1$ 的序列做一遍前缀和得到 $s_i$，那么满足条件的区间个数即为 $s_i$ 的**顺序对个数**。

对于 $type=1,3$ 的情况，做 $8$ 次树状数组求顺序对就可以了。

然而对于原题来说这样肯定是不行的，不过发现对于 $x$ 取什么值，$1$ 的个数加起来只有 $n$ 个，这意味着大部分数都是 $-1$，那么我们思考能不能拿这个性质做文章呢？

考虑从左到右依次插入一段连续的 $-1$，显然这些位置的 $s$ 值可以形成一段连续的区间（公差为 $-1$ 的等差数列），不妨设其为 $[L,R]$。

假设 $cnt_j$ 为当前 $s_i=j$ 的 $i$ 的个数，那么这段区间的贡献就是

$$\sum\limits_{i=L}^{R}\sum\limits_{j=-\infty}^{i-1}cnt_j$$

把这个式子稍微调整一下就可以得到

$$(R-L+1)\times\sum\limits_{j=-\infty}^{L-1}cnt_j+\sum\limits_{j=L}^Rcnt_j\times(R-j)$$

是不是感觉有亿点点可维护？

线段树维护 $cnt_j$ 的值，支持区间加、求区间 $cnt_i$ 的和，以及区间 $i \times cnt_i$ 的和，就可以在 $\mathcal O(\log n)$ 的时间内求出上面那个式子的值。

由于 $s_j$ 可能 $<0$，所以下标要整体加上一个值。

虽然 $-1$ 的个数很多，但是连续的 $-1$ 段的个数是 $\mathcal O(n)$ 级别的，而我们恰好利用了这个性质将复杂度降了下来。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
const int MAXN=5e5+5;
int n,a[MAXN];
vector<int> v[MAXN];
struct node{
	int l,r;
	ll val,mul,lz,sumi;
} s[MAXN<<4];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;s[k].val=s[k].lz=s[k].mul=0;if(l==r){s[k].sumi=l-MAXN;return;}
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	s[k].sumi=s[k<<1].sumi+s[k<<1|1].sumi;
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].val+=(s[k<<1].r-s[k<<1].l+1)*s[k].lz;
		s[k<<1].mul+=s[k<<1].sumi*s[k].lz;s[k<<1].lz+=s[k].lz;
		s[k<<1|1].val+=(s[k<<1|1].r-s[k<<1|1].l+1)*s[k].lz;
		s[k<<1|1].mul+=s[k<<1|1].sumi*s[k].lz;s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].val+=(s[k].r-s[k].l+1)*x;
		s[k].mul+=s[k].sumi*x;s[k].lz+=x;
		return;
	} pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	s[k].val=s[k<<1].val+s[k<<1|1].val;
	s[k].mul=s[k<<1].mul+s[k<<1|1].mul;
}
ll query(int k,int l,int r){
//	printf("%d %d %d\n",k,l,r);
	if(l<=s[k].l&&s[k].r<=r) return s[k].val;
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
ll queryi(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].mul;
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return queryi(k<<1,l,r);
	else if(l>mid) return queryi(k<<1|1,l,r);
	else return queryi(k<<1,l,mid)+queryi(k<<1|1,mid+1,r);
}
int main(){
	int qwq;scanf("%d%d",&n,&qwq);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].pb(i);
	build(1,0,MAXN<<1);ll ret=0;
	for(int i=0;i<n;i++){
//		printf("%d\n",i);
		int pre=0,sum=0;modify(1,MAXN,MAXN,1);
		for(int j=0;j<v[i].size();j++){
			int cur=v[i][j];
			if(pre+1!=cur){
				int r=sum-1,l=sum-(cur-pre-1);
				ret+=r*query(1,l+MAXN,r+MAXN)-queryi(1,l+MAXN,r+MAXN);
				ret+=(r-l+1)*query(1,0,l-1+MAXN);modify(1,l+MAXN,r+MAXN,1);
				sum-=(cur-pre-1);
			}
			sum++;ret+=query(1,0,sum-1+MAXN);modify(1,sum+MAXN,sum+MAXN,1);
			pre=cur;
		}
		if(pre!=n){
			int r=sum-1,l=sum-(n-pre);
			ret+=r*query(1,l+MAXN,r+MAXN)-queryi(1,l+MAXN,r+MAXN);
			ret+=(r-l+1)*query(1,0,l-1+MAXN);modify(1,l+MAXN,r+MAXN,1);
			sum-=(n-pre);
		}
		pre=0,sum=0;modify(1,MAXN,MAXN,-1);
		for(int j=0;j<v[i].size();j++){
			int cur=v[i][j];
			if(pre+1!=cur){
				int r=sum-1,l=sum-(cur-pre-1);
				modify(1,l+MAXN,r+MAXN,-1);
				sum-=(cur-pre-1);
			}
			sum++;modify(1,sum+MAXN,sum+MAXN,-1);
			pre=cur;
		}
		if(pre!=n){
			int r=sum-1,l=sum-(n-pre);
			modify(1,l+MAXN,r+MAXN,-1);
			sum-=(n-pre);
		}
	}
	printf("%lld\n",ret);
	return 0;
}
```

upd on 2020.12.4：

考场上想的做法竟然过了！incredible！我还以为它过不了呢/xyx

讲一个 $n\sqrt{n\log n}$ 的做法。

考虑分块，设一个临界值 $B$。

对于每个出现次数 $\leq B$ 的数，显然它只能对长度 $<2B$ 的区间产生贡献，枚举每个长度 $<2B$ 的区间。

对于每个出现次数 $>B$ 的数，这样的数顶多 $\dfrac{n}{B}$ 个，对于每一个这样的数搞一遍树状数组求顺序对。

时间复杂度 $2nB+\dfrac{n^2\log n}{B}$。

~~woc 这玩意儿真的 nb $10^9$ 左右给我跑过去了。~~

顺便提一句：考场上我在求 $<2B$ 的区间的贡献的时候用了 memset 所以 T 掉了还以为是程序本身的锅。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
typedef long long ll;
int n,sub,a[MAXN];
const int BLK=800;
int cnt[MAXN],f[MAXN];
int sum[MAXN];
int bit[MAXN<<1];
void add(int x,int v){for(int i=x;i<MAXN+MAXN;i+=(i&(-i))) bit[i]+=v;}
int query(int x){int ret=0;for(int i=x;i;i-=(i&(-i))) ret+=bit[i];return ret;}
int solve(){
	for(int i=1;i<=n;i++) f[a[i]]++;
	ll ret=0;
	for(int i=1;i<=n;i++){
		int mx=0,pos=0;
		for(int j=i;j<=n&&j<=i+BLK*2;j++){
			cnt[a[j]]++;if(cnt[a[j]]>mx) mx=cnt[a[j]],pos=a[j];
			if(mx>(j-i+1)/2&&f[pos]<BLK) ret++;
        }
        for(int j=i;j<=n&&j<=i+BLK*2;j++){
			cnt[a[j]]--;
		}
	}
	for(int i=0;i<n;i++){
		if(f[i]<BLK) continue;
		memset(sum,0,sizeof(sum));
		for(int j=1;j<=n;j++){
			if(a[j]==i) sum[j]=sum[j-1]+1;
			else sum[j]=sum[j-1]-1;
		}
		memset(bit,0,sizeof(bit));
		add(MAXN,1);
		for(int j=1;j<=n;j++){
			ret+=query(sum[j]-1+MAXN);
			add(sum[j]+MAXN,1);
		}
	}
	printf("%lld\n",ret);
	return 0;
}
int main(){
	scanf("%d%d",&n,&sub);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	return solve();
}
```

---

## 作者：_ANIG_ (赞：3)

[[Code+#1] Yazid 的新生舞会 ](https://www.luogu.com.cn/problem/P4062)

分治。

考虑左端点在 $[l,mid]$，右端点在 $[mid+1,r]$ 中的贡献。

首先有一个性质：以 $n$ 结尾的所有区间的绝对众数构成的集合大小不超过为 $\log n$。

还有一个性质：所有区间 $[a,b](l\le a\le mid,mid<b\le r)$ 的绝对众数构成的集合大小不超过 $2\log n$。

证：

区间 $[l,r]$ 可以拆成 $[l,mid],[mid+1,r]$ 两部分，区间 $[l,r]$ 的绝对众数一定是区间 $[l,mid]$ 或区间 $[mid+1,r]$ 的绝对众数。否则设 $a$ 为实际的绝对众数在区间 $[l,mid]$ 的出现次数，$b$ 为实际绝对众数在区间 $[mid+1,r]$ 的出现次数，则若这个数不是这两个区间的绝对众数，有 $a\le\frac{mid-l+1}2,b\le\frac{r-mid}2$，得到 $a+b\le\frac{r-l+1}{2}$，与这个数是区间 $[l,r]$ 的绝对众数矛盾。

也就是区间 $[l,r]$ 的绝对众数构成的集合就是以 $mid$ 结尾和以 $mid+1$ 开头的并集，也就是 $2\log n$。

枚举区间的左端点 $a$，再枚举绝对众数的值 $k$，看有哪些右端点 $b$，满足 $k$ 在 $[a,b]$ 的出现次数大于 $\frac{b-a+1}2$。

对于每个 $k$，把值等于 $k$ 的下标存到数组 $g$，则 $k$ 在区间 $[a,b]$ 的出现次数为 $c_b-c_a+1$（$c_i$ 表示 $i$ 在 $g$ 中的位置）。

则 $c_b-c_a+1>\frac{b-a+1}2$，解得 $b-2c_b<a-2c_a+1$。

可以对每个 $k$ 分别计算，把 $b$ 按 $b-2c_b$ 排序，统计满足这个不等式的数量即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
int n,p[2*N],wz[2*N],tp;
ll res;
struct node{
    int bh,sm;
    friend bool operator<(node a,node b){
        return a.sm<b.sm;
    }
}g[N];
map<int,int>mk,hs;
void solve(int l,int r){
    if(l==r)return;
    int mid=l+r>>1;
    vector<int>cn;
    solve(l,mid);
    cn.clear();
    for(int i=mid;i>=l;i--){
        mk[p[i]]++;
        if(mk[p[i]]>(mid-i+1)/2)if(!hs[p[i]])cn.push_back(p[i]),hs[p[i]]=1;
    }
    mk.clear();
    for(int i=mid+1;i<=r;i++){
        mk[p[i]]++;
        if(mk[p[i]]>(i-mid)/2)if(!hs[p[i]])cn.push_back(p[i]),hs[p[i]]=1;
    }
    hs.clear();
    mk.clear();
    for(int i=0;i<cn.size();i++){
        int c=cn[i],nw=0,idx=0,mn=1e9,mx=0;
        for(int j=l;j<=r;j++){
            if(j<=mid)mn=min(mn,j-nw-nw+1),mx=max(mx,j-nw-nw+1);
            if(p[j]==c)nw++;
            if(j<=mid)continue;
            g[j]=(node){j,j-2*(nw-1)};
        }
        if(!nw)continue;int ng=nw;
        nw=0;
        sort(g+mid+1,g+r+1);
        g[r+1]=(node){n,1000000000};
        wz[mn-1+n]=mid+1;
        for(int j=mn;j<=mx;j++){
            wz[j+n]=wz[j+n-1];
            while(j>g[wz[j+n]].sm)wz[j+n]++;
        }
        for(int j=l;j<=mid;j++){
            int w=wz[j-nw-nw+1+n]-1;
            res+=w-mid;
            if(p[j]==c)nw++;
        }
    }
    solve(mid+1,r);
}
signed main(){
    cin>>n>>tp;
    for(int i=1;i<=n;i++)scanf("%d",&p[i]);
    solve(1,n);
    cout<<res+n;
}
```


---

## 作者：do_while_true (赞：3)

还是考虑那个众数的套路，考虑一个数 $c$ 的贡献，将 $c$ 置为 $1$，不是 $c$ 的置为 $-1$，那么一个区间和 $>0$ 的绝对众数是 $c$．

从左往右和从右往左各跑一边，每次让一个 $+1$ 匹配左边第一个没匹配的 $-1$ （没有的话就匹配到虚空），如果一个位置从前往后或者从后往前都没匹配到，意味着它不可能和其他位置组成逆序对，这个位置就会寄掉，用并查集即可完成匹配。

跑出了这些绝对众数可能为 $c$ 的连续段，这些连续段的总长度至多是 $c$ 出现次数的两倍，所以所有 $c$ 的若干连续段的总长是 $\mathcal{O}(n)$ 的。

那么作前缀和，在每个连续段内对答案的贡献就是一个二维数点的形式。

注意到相邻数只会有 $\pm 1$ 的改变，那么扫描线的时候，考虑计算这一个位置统计的答案和上一个位置的差值是多少即可，只需要开个桶记录一下每个值的出现次数。

如果使用线性序列并查集算法，复杂度是 $\mathcal{O}(n)$ 的，不过写这篇题解的时候用纯路径压缩跑到了洛谷上第一。

找出极长连续段的实现上需要精细一点，可能要双指针什么的（

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
inline void cmax(int &x, int y){x=x>y?x:y;}
inline void cmin(int &x, int y){x=x<y?x:y;}
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline void read(int &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	r=w?-r:r;
}
const int N=500100;
int n,type;
int a[N],L[N],R[N],visbuf[N<<1],*vis=visbuf+N;
vi vec[N];
ll ans;
int f[N],p[N];
int st[N],top;
int getfa1(int x){
	return f[x]==x?x:f[x]=getfa1(f[x]);
}
void merge1(int x,int y){
	int fx=getfa1(x),fy=getfa1(y);
	f[fy]=fx;
}
int getfa2(int x){
	return p[x]==x?x:p[x]=getfa2(p[x]);
}
void merge2(int x,int y){
	int fx=getfa2(x),fy=getfa2(y);
	p[fy]=fx;
}
signed main(){
	read(n);read(type);
	for(int i=1;i<=n;i++)read(a[i]),p[i]=f[i]=i,vec[a[i]].pb(i);
	p[n+1]=f[n+1]=n+1;
	for(int o=0;o<n;o++){
		int mn=n+1;top=0;
		for(auto i:vec[o]){
			int fa=getfa1(i-1);
			merge1(fa,i);
			if(fa)merge1(fa-1,fa);
			L[i]=fa;
			while(top&&st[top]>fa)--top;
			st[++top]=fa;
		}
		reverse(vec[o].begin(),vec[o].end());
		for(auto i:vec[o]){
			int fa=getfa2(i+1);
			merge2(fa,i);
			if(fa<=n)merge2(fa+1,fa);
			cmax(R[L[i]],fa);
		}
		reverse(vec[o].begin(),vec[o].end());
		for(int k=1;k<=top;k++){
			int l=st[k],r=R[l];
			while(l<=r){
				++l;cmax(r,R[l]);
			}
			l=st[k];cmin(r,n);
			int cnt=0,s=0;
			for(int i=l;i<=r;i++){
				L[i]=R[i]=0;f[i]=p[i]=i;
				if(i){
					if(a[i]==o)cnt+=vis[s++];
					if(a[i]!=o)cnt-=vis[--s];
				}
				++vis[s];
				ans+=cnt;
			}
			s=0;
			for(int i=l;i<=r;i++){
				if(i){
					if(a[i]==o)++s;
					if(a[i]!=o)--s;
				}
				vis[s]=0;
			}
			while(k<=top&&st[k]<=r)
				++k;
			--k;
		}
		#undef now
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：kradcigam (赞：3)

为什么最劣解选手还有脸来写题解啊……

这题首先考虑每个数 $x(1\leq x\leq n)$​​​​ 分开算贡献。设 $B_1,B_2,\cdots,B_{m_x}(A_{B_i}=x)$​​​​。我们发现对于每个数分开计算是，$A_1,A_2,\cdots,A_n$​​​​ 只有两种数，一种是等于 $x$​​​，另一种是不等于 $x$​​​​。考虑一个答案区间 $l' \sim r'$​​​，一定是由一个我们称为“根区间” $l\sim r(l'\leq l,r\leq r')$​ 的东西扩展出来的。所谓的“根区间”就是指 $A_l=A_r=x$​，即区间左右两个端点都是这个数，~~于是就有了一个 $O(n^2)$​ 的暴力做法。~~我们发现“根区间”能够衍生、拓展出来的区间数，与“根区间”内等于 $x$​ 的数的个数 $-$​ 不等于 $x$​ 的数的个数以及 $l$​ 左边连续不为 $x$​ 的个数和 $r$​ 右边连续不为 $r$​ 的个数有关（不然根区间就不是 $l\sim r$​​​​ 了）。

既然无法直接枚举根区间，我们就要另外想办法。其实提到计算区间贡献这个东西，显然会想到分治。于是就是愉快的讨论：对于一个区间 $l\sim r$，中点为 $mid$，“根区间” $l'\sim r'(l\leq l'\leq r'\leq r)$一共分为 $3$ 种：

1. $l'\leq r'\leq mid$
2. $l'\leq mid < r'$
3. $mid< l' \leq r'$

对于第一种和第三种分别属于 $l\sim mid$​​ 和 $mid+1\sim r$​​ 区间内的，如实我们就只要想办法计算跨越 $mid$​​ 的根区间即第二种 $l'\leq mid\leq r'\leq r$​​ 的贡献了。我们考虑用一棵权值线段树维护对于每个 $y$​​ 有多个个 $l'$​​ 满足 $l'\sim mid$​​ 中等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数 $=$​​ $y$​​。考虑 $B_{i}+1\sim B_i$​​ 这一段等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数形成了一个公差为 $1$​​ 的等差数列。我们先看一下我们会有什么形式的询问：对于 $B_{i}\sim B_{i+1}-1$​​ 这一段中等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数形成了一个公差为 $-1$​​ 的等差数列，对于等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数 $=$​​ $y$​​ 的数，对于答案的贡献为左边段中等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数可以为 $-y+1\sim n$​​，于是对答案的贡献就是左区间中等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数为 $-y+1\sim n$​​ 的方案数和。比如说 $n=6,A=\{1,0,0,0,0,1\}$​​ 对于 $x=1$​​ ,$B={1,6}$​​，$l=1,r=2,mid=1$​​，$2\sim 3$​​ 等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数形成了一个公差为 $1$​​ 的等差数列 $-2,-1$​​，当然还有 $1$​​ 等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数 $= -1$​​。右区间 $4\sim 5$​​ 中等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数形成了一个公差为 $-1$​​ 的等差数列 $-1,-2$​​，需要查询的是左边等于 $x$​​ 的个数 $-$​​ 不等于 $x$​​ 的个数为 $-(-1)+1=2 \sim n$​​ 和 $-(-2)+1=3 \sim n$​​，当然还有最后的一项 $-1$​​​​ 要查询。我们感兴趣的是 $4\sim5$​ 这一段：观察项的系数值为 $2$  的数为 $1$，值为 $3\sim n$ 的数为 $2$。发现一定是一个等差数列 $+$​​ 一个所有数相同的数列，分别维护即可，时间复杂度 $O(n\log^2 n)$​/kk。

实现：

 等于 $x$ 的个数 $-$ 不等于 $x$ 的个数的范围是 $-n \sim n$ 的，但是真正有用的区间没有那么多，所以考虑动态开点。

每一次都要注意将树清空或将清除之前的所有修改操作。

注：细节很多，比较难写难调/kk。

代码：

```cpp
#include<bits/stdc++.h>
// #define ls (num<<1)
// #define rs (num<<1|1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=5e5+10;
vector<int>v[N];
int cnt,n,ls[N<<2],rs[N<<2],rt;
bool cl[N<<2];
LL ans,tag[N<<2],sum[N<<2],sum2[N<<2],len[N<<2],len2[N<<2];
inline void down(int&num,int x,int l,int r){
	if(!num){
		num=++cnt;
		len2[num]=r-l+1;
		len[num]=len2[num]*(l+r)/2;
	}
	tag[num]+=x;
	sum[num]+=len[num]*x;
	sum2[num]+=len2[num]*x;
}
inline void down2(int&num,int l,int r){
	if(!num){
		num=++cnt;
		len2[num]=r-l+1;
		len[num]=len2[num]*(l+r)/2;
	}
	cl[num]=true;
	sum[num]=sum2[num]=tag[num]=0;
}
inline void pushdown(int num,int l,int r){
	if(cl[num]){
		int mid=(l+r)>>1;
		down2(ls[num],l,mid);
		down2(rs[num],mid+1,r);
		cl[num]=false;
	}
	if(tag[num]){
		int mid=(l+r)>>1;
		down(ls[num],tag[num],l,mid);
		down(rs[num],tag[num],mid+1,r);
		tag[num]=0;
	}
}
inline void pushup(int num){
	sum[num]=sum[ls[num]]+sum[rs[num]];
	sum2[num]=sum2[ls[num]]+sum2[rs[num]];
}
inline void change(int&num,int l,int r,int L,int R,int x){
	if(!num){
		num=++cnt;
		len2[num]=r-l+1;
		len[num]=len2[num]*(l+r)/2;
	}
	if(L<=l&&r<=R){
		down(num,x,l,r);
		return;
	}
	pushdown(num,l,r);
	int mid=(l+r)>>1;
	if(mid>=L)change(ls[num],l,mid,L,R,x);
	if(mid<R)change(rs[num],mid+1,r,L,R,x);
	pushup(num);
}
inline int query(int&num,int l,int r,int L,int R){
	if(!num){
		num=++cnt;
		len2[num]=r-l+1;
		len[num]=len2[num]*(l+r)/2;
		return 0;
	}
	if(L<=l&&r<=R)return sum[num];
	pushdown(num,l,r);
	int mid=(l+r)>>1;
	if(mid<L)return query(rs[num],mid+1,r,L,R);
	if(mid>=R)return query(ls[num],l,mid,L,R);
	return query(ls[num],l,mid,L,R)+query(rs[num],mid+1,r,L,R);
}
inline int query2(int&num,int l,int r,int L,int R){
	if(!num){
		num=++cnt;
		len2[num]=r-l+1;
		len[num]=len2[num]*(l+r)/2;
		return 0;
	}
	if(L<=l&&r<=R)return sum2[num];
	pushdown(num,l,r);
	int mid=(l+r)>>1;
	if(mid<L)return query2(rs[num],mid+1,r,L,R);
	if(mid>=R)return query2(ls[num],l,mid,L,R);
	return query2(ls[num],l,mid,L,R)+query2(rs[num],mid+1,r,L,R);
}
inline void solve(int num,int l,int r){
	if(l==r){
		ans++;
		return;
	}int mid=(l+r)>>1;
	solve(num,l,mid);solve(num,mid+1,r);
	int s=0;
	down2(rt,-n,n);
	DF(i,mid,l){
		int r=s-(i==mid?1:0);
		s-=v[num][i+1]-v[num][i]-1;
		int l=s;
		s++;
		if(l<=r)change(rt,-n,n,l,r,1);
	}
	if(!l)change(rt,-n,n,s-(v[num][l]-(l?v[num][l-1]:0)-1),s,1);
	else change(rt,-n,n,s,s,1);
	s=0;
	F(i,mid+1,r){
		s++;
		int l=s;
		s-=(i==SZ(v[num])?n+1:v[num][i+1])-v[num][i]-1;
		int r=s;
		l=(-l)+1;
		r=(-r)+1;
		ans+=query(rt,-n,n,l,r);
		if(l!=1)ans-=(l-1)*query2(rt,-n,n,l,r);
		if(r!=n)ans+=(r-l+1)*query2(rt,-n,n,r+1,n);
	}
}
signed main(){
	n=read();int type;type=read();
	F(i,1,n){
		int x=read();
		v[x].push_back(i);
	}
	F(i,0,n-1)
		if(v[i].size())solve(i,0,SZ(v[i]));
	cout<<ans;
	return 0;
}
```





---

## 作者：strcmp (赞：2)

**题目大意：** 给定长度为 $n$ 的序列 $a$，求 $a$ 中有多少个区间存在绝对众数。

------------

其实这题转个方向并不算难。

$n^2$ 随便做都行，枚举区间做个摩尔投票就行了。

但是我们发现这样完全没有优化空间。

考虑另一种做法，枚举数 $x$ 为绝对众数。那么将与 $x$ 相等的值设为 $1$，否则设成 $-1$。求出此时的前缀和 $s$，那么就是求 $i < j \wedge s_j - s_i > 0$。

枚举值然后用个树状数组维护即可，时间复杂度 $\Theta(n^2 \log n)$，鉴定为不如暴力。

但是这样我们就有优化的空间了。

因为你发现，很多数出现次数其实很少，那么这种情况下序列中为 $-1$ 的值就会很多。准确来说，枚举所有绝对众数情况下的序列，为 $1$ 的数恰好有 $n$ 个。

如果我们把连续的 $-1$ 缩到一起了，如果能快速计算它们的贡献就对了。

为什么呢？因为 $k$ 个 $1$ 最多把 $k + 1$ 段 $-1$ 隔开，那么所有 $-1$ 段的数量，加上为 $1$ 的位置的数量和是 $\Theta(n)$ 级别的。

通过求 $\text{nxt}(i)$ 为 $i$ 之后第一个和 $a_i$ 相等的位置，我们可以轻松的弄出当前序列的所有 $1$ 位置，以及 $1$ 之间的 $-1$ 段。

这样我们处理的序列就类似于这样：

$$
[1,\,(-1,\,2),\,1,\,1,\,1,\,(-1,\,6),\,1,\,(-1,\,3)]
$$

其中 $(-1,\,x)$ 代表有连续 $x$ 个 $-1$。

你会发现，对这些连续的 $-1$ 求前缀和后，连续的 $-1$ 段对应的前缀和是公差为 $-1$ 的等差数列。

显然这些 $-1$ 段内部是不会产生贡献的，因为公差是 $-1$，它们严格递减。

不妨考虑扫描线，$p_v$ 为 $s_i = v$ 的 $i$ 个数，令 $q_i \leftarrow \sum_{j=1}^{i}p_i$，则位置 $i$ 的贡献为 $q_{s_i - 1}$。令 $g_i \leftarrow \sum_{j = 1}^{i}q_j$。由于 $-1$ 段内的公差为 $1$。设整个 $-1$ 段的 $s_i$ 值在区间 $[vl,\,vr]$ 内，则贡献为 $g_{vr - 1} - g_{vl - 1}$。

也就是区间加一数，求二阶前缀和。

可以用线段树维护，但比较麻烦。

考虑树状数组差分后，变为单点加一数，求三阶前缀和。

$$g_m = \sum_{i = 1}^{m}\sum_{j=1}^{i}\sum_{k=1}^{j} a_k = \dfrac{(m+2)(m+1)}{2}\sum_{i=1}^{m}a_i - \dfrac{2m + 3}{2}\sum_{i=1}^{m}a_i \times i + \dfrac12 \sum_{i=1}^{m}a_i \times i^2$$

树状数组维护即可，时间复杂度 $\Theta(n \log n)$。

月亮好闪，拜谢月亮。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 1e6 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
ll c[3][maxn]; int n, ty, b[maxn], d[maxn], nxt[maxn];
inline ll query(int x) {
	if (x <= 0) return 0LL; ll ans = 0; ll e = x;
	while (x) ans += c[0][x] * (e + 2) * (e + 1) - c[1][x] * (2LL * e + 3) + c[2][x], x -= x & -x;
	return ans >> 1;
}
pii s[maxn]; int t = 0;
inline void add(int x, ll w) {
	ll e = x;
	while (x <= (n << 1 | 1)) c[0][x] += w, c[1][x] += w * e, c[2][x] += w * e * e, x += x & -x;
}
int main() {
	scanf("%d%d", &n, &ty); 
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if (b[x]) nxt[b[x]] = i; b[x] = i;
		if (!d[x]) d[x] = i;
	}
	for (int i = 1; i <= n; i++) if (!nxt[i]) nxt[i] = n + 1; ll ans = 0;
	for (int o = 0; o < n; o++) {
		int w = d[o];
		if (!w) continue; int p = 0, cnt = 0;
		for (int i = w; i; i = nxt[i]) {
			int vl = cnt * 2 - i + n + 2, vr = cnt * 2 - p + n + 1;
			ans += query(vr - 1) - query(vl - 2);
			add(vl, 1); add(vr + 1, -1);
			s[++t] = { vl, -1 }; s[++t] = { vr + 1, 1 }; ++cnt, p = i;
		}
		while (t) add(s[t].first, s[t].second), --t;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：MspAInt (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P4062)

每个区间至多一个绝对众数，那么反着考虑一个数是多少个区间的绝对众数。

两个特殊性质明示了根号分治。

对于数量 $\le B$ 的颜色，考虑到其最多只能是长度为 $2B-1$ 的区间的绝对众数，直接枚举区间预处理即可。

对于数量 $>B$ 的颜色，我们考虑设 $s_i$ 为此颜色的出现次数前缀和，如果此颜色是区间 $[l,r]$ 的绝对众数，则有 $s_r-s_{l-1}>\frac{r-l+1}{2}$，即 $2s_r-r>2s_{l-1}-l+1$。这是一个逆序对的形式，可用树状数组求得满足条件的数对个数即答案，但是这样有个 log 很难过。发现 $2s_i-i=2s_{i-1}-(i-1)\pm1$，开一个桶维护每个 $2s_i-i$ 的出现次数，多了或少了 $1$ 时直接 $\Theta(1)$ 维护这个点的贡献（即 $\sum_{j=0}^{i-1}[2s_i-i>2s_j-j]$），这样就是线性的。这种颜色只会出现最多 $\frac{n}{B}$ 次。

总时间复杂度 $\Theta(\frac{n^2}{B}+nB)$，$B=\sqrt{n}$ 时复杂度为 $\Theta(n\sqrt{n})$。

然而我们可以调参，$B=30$ 时这份代码对于所有测试点均能在 1s 内通过。

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10,B=30;
int n,type,a[N],b[N],t[N<<2],c[N];
ll ans,p[N];
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d",&n,&type);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),c[a[i]]++;
    for(int i=1;i<=n;i++){
        int cnt=0,val=0;
        for(int j=i;j<=min(n,i+B);j++){
            t[a[j]]++;
            if(t[a[j]]>cnt)cnt=t[a[j]],val=a[j];
            if(cnt>(j-i+1)/2)p[val]++;
        }
        for(int j=i;j<=min(n,i+B);j++)t[a[j]]=0;
    }
    for(int i=0;i<n;i++){
        if(c[i]>B/2+1){
            ll now=0;p[i]=0;
            for(int j=1;j<=n;j++)b[j]=(a[j]==i)+b[j-1];
            for(int j=1;j<=n;j++)b[j]=(b[j]<<1)-j;
            t[1000000]=1;
            for(int j=1;j<=n;j++){
                if(b[j]>b[j-1])now+=t[b[j-1]+1000000];
                else now-=t[b[j]+1000000];
                // now=max(now,0ll);
                t[b[j]+1000000]++;
                p[i]+=now;
            }
            memset(t,0,sizeof(t));
        }
        ans+=p[i];
    }
    printf("%lld\n",ans);
    // system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/137906807)

---

## 作者：_LHF_ (赞：2)

来口胡一个简单易懂的线性做法。

首先枚举绝对众数 $x$，然后把 $a_i=x$ 的看作 $+1$，其它的看成 $-1$。

然后看这个序列的前缀和 $s$，对于 $i<j$，如果有 $s_i<s_j$，那么就会对答案造成 $+1$ 的贡献。

直接做显然不行，考虑如何优化。

不难观察发现：

> 如果 $s_i$ 同时是前缀最小值和后缀最大值，那么 $s_i$ 不会对答案造成任何贡献。

证明显然。

再考虑假设 $=x$ 的数有 $k$ 个，那么序列元素和为 $2k-n$，那么本质不同的前缀最小值和后缀最大值的数量均为 $\max(n-2k,0)$。

所以有用的数量只有 $O(k)$ 个，于是总共有用的数量就只有 $O(n)$ 个。

显然对于固定的 $x$，我们可以把有用的数构成的极长连续段拉出来分别作就行了。

现在考虑对于一段 $+1,-1$ 的段计算之前的贡献。乍一看，需要单点修改，查询前缀和，好像至少要一个 $\log$。

但观察发现两次查前缀的位置分别为 $x,y$，有 $|x-y|\le 1$，于是直接开桶记录即可。

于是就 $O(n)$ 了。

---

## 作者：1234567890sjx (赞：1)

题意就是问有多少个区间 $[l,r]$ 存在绝对众数。

考场暴力做法：

枚举左端点 $l$，扫一遍 $r$ 并跑摩尔投票法，每跑完一组之后验证摩尔投票法得到的解是否合法即可。时间复杂度 $O(n^2)$。

然后考虑正解。

容易发现实际有用的 $a_i$ 最多不会超过 $n$ 个，所以对 $a_i$ 做离散化。

考虑枚举每一个 $a_i$ 的值，并计算其对答案产生的贡献。若值 $x$ 对区间 $[l,r]$ 产生 $1$ 的贡献，令 $s_{x,i}$ 表示 $1\sim i$ 中 $x$ 在 $a$ 数组中出现的次数，那么当且仅当 $2\times (s_{x,r}-s_{x,l-1}) > r-l+1$ 也就是 $2\times s_{x,r}-r>2\times s_{x,l-1}-l+1$。

然后问题转化为计数，求对于每一个右端点 $r$ 有多少个 $l\in [1,r]$ 满足上述条件。容易发现是二维偏序问题，直接按照套路搞掉一维然后另一维 `BIT` 掉，可以获得 $35$（赛时 $50$）分，甚至和暴力没有什么区别。

但是没有过这个题肯定是不行的。特殊的令 $f_i=2\times s_{x,i}-i$，容易发现，对于每一个不同的 $S_{x,i}$ 都可以从她开始划分出一个区间一直到 $S_{x,i}$ 增加 $1$ 为止，这一段是一个公差为 $-1$ 的等差数列。

发现这是一个套路。考虑开一个权值数组 $Q$，若此时等差数列的首项是 $l$，末项是 $r$，那么在权值数组中统计就是将区间 $[l,r]$ 增加 $1$。

套路的令 $Q'$ 为 $Q$ 数组的前缀和，对于上述的区间 $[l,r]$，其贡献就是 $\sum_{i=r-1}^{l-1}Q'_i$，再令 $Q''_i$ 为 $Q'_i$ 的前缀和，答案就比较好算了，根据前缀和的定义可以得到答案为 $Q''_{r-1}-Q''_{l-2}$。这个东西就可以用差分，然后用三个树状数组来维护三层前缀和的值。

时间复杂度很抽象，大概是小常数 $O(n\log n)$ 的吧。

[代码，很丑](https://www.luogu.com.cn/paste/x047w20k)

------

某位神仙同学提出了 $O(n\sqrt n\log n)$ 的神仙做法并薄纱了 `std`，但是没看懂，所以就不写了。

---

## 作者：MrcFrst (赞：1)

### 题外话

我记得第一次看见这道题是几个月前刚开始集训的时候，当时一点思路都没有，但是今天自己做出来了，很喜欢这种感觉！

------------
### $\text{Links}$

[原题传送门](https://www.luogu.com.cn/problem/P4062)

[可能更好的阅读体验](https://www.cnblogs.com/MrcFrst-LRY/p/17756806.html)


------------
### 题意

求给定序列中有多少个子区间满足众数出现次数严格大于区间长度的一半。



------------
### 题解

题目要求满足条件的子区间，一个很直接的想法是每次固定左（右）端点，求有多少个右（左）可以与其匹配对答案造成贡献。

那么考虑一个暴力做法：每次固定左端点，然后往后面一直扫，枚举每个右端点，中途记录众数出现次数，然后依次判断即可。时间复杂度为 $O(n^2)$。

这肯定是过不了的，那么我们再从条件入手，注意到：

> - 严格大于区间长度的一半

于是就说明每个区间对应的这个众数只会有一个！考虑利用一下这个性质。

那么我们可以枚举这个众数。设我们当前枚举的众数为 $x$，记录一个数组 $s$，$s_i$ 表示前 $i$ 个数中 $x$ 的出现次数。

沿用上面固定一个端点求另一个合法端点数量的思路，对于一个右端点 $r$，合法的左端点 $l$ 显然应该满足：

$$
l \le r,s_r-s_{l-1}\gt \frac{r-(l-1)}{2}
$$

$l-1$ 看着有点烦（，把 $-1$ 去掉，变成：

$$
l\lt r ,s_r-s_l\gt \frac{r-l}{2}
$$

不等式两边同时 $\times 2$：

$$
l\lt r,2s_r-2s_l\gt r-l
$$

移项得：

$$
l\lt r,2s_r-r\gt 2s_l-l
$$

记 $s'_i=2s_i-i$，则：

$$
l\lt r,s'_r\gt s'_l
$$

经典问题，树状数组维护即可。但时间复杂度为 $O(n^2\log n)$，甚至不如 $O(n^2)$ 暴力（悲。

那么我们考虑整体观察一下序列 $s'$，说不定能发现什么（。

显然地，如果满足 $a_i=x$ 的若干个 $i$ 的的位置都确定了，那么整个 $s'$ 序列就可以确定了，所以我们要想办法只用这些 $i$ 的位置来计算答案，使得每次的时间复杂度都只与 $m$ 相关，其中 $m$ 为这些 $i$ 的数量。再因为 $\sum m=n$，于是可以大幅降低总时间复杂度。

记 $d$ 为 $s'$ 的差分序列，那么如果 $a_i=x$，则有 $d_i=1$，否则 $d_i=-1$，我们把前者中的 $i$ 视为一个“**断点**”，那么整个 $s'$ 序列就是若干个公差为 $-1$ 的**等差数列**“首尾衔接”拼在一起。

因为公差为 $-1$，即单调递减，所以每一个等差数列内部是不会产生任何贡献的，那么我们考虑把每个等差数列视作整体，看它前面的等差数列可以产生多少贡献。

沿用上面树状数组的做法，开一个**桶** $t$，$t_i$ 表示 $s'$ 值为 $i$ 的位置有多少个，因为每次要查询小于某个值的数量，所以把它记成前缀和的形式，记 $v$ 为它的**前缀和序列**。那么对于每个右端点 $r$，它的答案显然是 $v_{s'_r-1}$。我们把每一段等差数列的贡献写下来就是：

$$
\sum_{i=fir}^{lst}v_{i-1}
$$

然后它又可以写成两个前缀和相减的形式，也就成了 $t$ 序列的**二阶前缀和**，那么我们就需要在这个桶上面实现：区间加（插入一个等差数列），维护二阶前缀和。

~~呵，果然又变成大力 ds 了是吧~~

线段树和树状数组都可以维护，在我看来各有优势吧，线段树写此题代码的时候比较容易理解，好写一点，但这题树状数组的常数吊打线段树。

这里给出线段树的实现方式：

哦对，因为 $s'$ 序列中可能出现负数，所以要加上一定的偏差值给它强制转成正数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
const int N=5e5+113;
int n,a[N],b[N],ans,dt,vmax;
pii lst[N];
bitset<N>solved;
vector<int>v[N];
struct SegT{
    int ans,sum,tag,l,r;
}L[N<<3];
#define ls (id<<1)
#define rs (id<<1|1)
il void Pushup(SegT &fa,SegT lson,SegT rson){
    fa.sum=lson.sum+rson.sum;
    int l=lson.l,mid=lson.r,r=rson.r;
    fa.ans=lson.ans+rson.ans+lson.sum*(r-mid);
}
il int Get(int x){
    return (x*(x+1))>>1;
}
il void Add(SegT &fa,int x){
    fa.tag+=x,fa.sum+=(fa.r-fa.l+1)*x,fa.ans+=Get(fa.r-fa.l+1)*x;
}
il void Pushdown(SegT &fa,SegT &lson,SegT &rson){
    if(!fa.tag)return;
    Add(lson,fa.tag),Add(rson,fa.tag);
    fa.tag=0;
}
il void Add(int id,int l,int r,int x,int y,int z){
    if(l>=x&&r<=y){
        Add(L[id],z);
        return;
    }
    Pushdown(L[id],L[ls],L[rs]);
    int mid=(l+r)>>1;
    if(x<=mid)Add(ls,l,mid,x,y,z);
    if(y>mid)Add(rs,mid+1,r,x,y,z);
    Pushup(L[id],L[ls],L[rs]);
}
il SegT GetAns(int id,int l,int r,int x,int y){
    if(l>=x&&r<=y)return L[id];
    Pushdown(L[id],L[ls],L[rs]);
    int mid=(l+r)>>1;
    SegT res;
    if(x<=mid&&y>mid){
        SegT Left=GetAns(ls,l,mid,x,y);
        SegT Right=GetAns(rs,mid+1,r,x,y);
        Pushup(res,Left,Right);
    }
    else if(x<=mid)res=GetAns(ls,l,mid,x,y);
    else res=GetAns(rs,mid+1,r,x,y);
    Pushup(L[id],L[ls],L[rs]);
    return res;
}
il void Build(int id,int l,int r){
    L[id]={0,0,0,l,r};
    if(l==r)return;
    int mid=(l+r)>>1;
    Build(ls,l,mid),Build(rs,mid+1,r);
}
il void solve(int x){
    solved[x]=1;
    int siz=v[x].size()-1,mx=dt,mn=dt;
    for(re int i=0;i<=siz;i++)
        b[i]=(i<<1)-v[x][i]+dt,mx=max(mx,b[i]),mn=min(mn,b[i]);
    for(re int i=0;i<=siz;i++){
        int r=b[i],l=(i==siz)?b[i]-(n-v[x][i]):b[i]-(v[x][i+1]-v[x][i]-1);
        ans+=GetAns(1,1,vmax,1,r-1).ans-GetAns(1,1,vmax,1,l-2).ans;
        Add(1,1,vmax,l,r,1);
    }
    for(re int i=0;i<=siz;i++){
        int r=b[i],l=(i==siz)?b[i]-(n-v[x][i]):b[i]-(v[x][i+1]-v[x][i]-1);
        Add(1,1,vmax,l,r,-1);
    }
}
il int read(){
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
signed main(){
    n=read(),a[0]=read();
    dt=n+10,vmax=n+dt;
    for(re int i=1;i<=n;i++){
        a[i]=read();
        if(v[a[i]].empty())v[a[i]].push_back(0);
        v[a[i]].push_back(i);
    }
    Build(1,1,vmax);
    for(re int i=1;i<=n;i++)
        if(!solved[a[i]])solve(a[i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：dcmfqw (赞：1)


每个合法区间肯定只有一个众数。

所以对每个颜色可以单独考虑，不会算重。

看到众数还是超过一半可能会想到[P3524](https://www.luogu.com.cn/problem/P3524)和[P2397](https://www.luogu.com.cn/problem/P2397)的 trick。

但是这个 trick 太抽象了要具体化一下。

在单独考虑一个颜色的时候可以把这个颜色所在位置标为 1，不是这个颜色的标为 -1。

然后会发现一个区间中的标号的和是正的那么它就是合法的。

所以做一个前缀和，问题就演化成了一个前缀和前面有多少个前缀和比它小。

维护一个下标为前缀和的权值树状数组，对于每一个颜色从前到后扫一遍，复杂度是 $O(n^2\log n)$ 的。

好像比暴力还慢啊。

慢就慢在每个颜色都要遍历一遍数组。

但是会每个颜色在每个位置只出现一次，所以每个颜色的出现次数的和就是 $n$。

所以要一次性处理一段连续的极大的标为 -1 的区间。

首先这一段区间的前缀和是连续的，做一个区间修改就完事了。

（注意这个区间修改指的是在前缀和的值域意义上的区间加 1）

但是这一段区间对答案的贡献呢？

如果记 $S_i$ 为前缀和 $i$ 在前面出现了多少次，$l$ 和 $r$ 为当前处理的这段区间内的前缀和的最小值和最大值。

那么这段区间对答案的贡献为：

$$\sum\limits_{i=l}^r\sum\limits_{j=-n}^{i-1}S_j$$

分个类：

$$=(\sum\limits_{i=l}^r(r-i)S_i)+(r-l+1)\sum\limits_{i=-n}^{l-1}S_i$$

再拆：

$$=r(\sum\limits_{i=l}^rS_i)-(\sum\limits_{i=l}^riS_i)+(r-l+1)\sum\limits_{i=-n}^{l-1}S_i$$

这就好区间询问了，分别处理 $\sum\limits_{i=l}^rS_i$ 即区间和与 $\sum\limits_{i=l}^riS_i$。

区间询问和区间查询还是用权值线段树方便一点吧。

注意一下前缀和有负数所以线段树空间记得开大一点。

具体实现的时候可以顺带和区间前面那个 1 一起计算，反正前缀和还是连续的。

~~下面是喜提最劣解的代码。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define inl inline
#define rep(i, d, u) for(reg int i = d; i <= u; ++i)
#define dep(i, u, d) for(reg int i = u; i >= d; --i)
#define cep(n) while(n--)
#define gep(i, a) for(reg int i = firs[a]; i; i = neig[i])
int ured() {
	reg int re = 0, ch;
	do {
		ch = getchar();
	} while('9' < ch || ch < '0');
	do {
		re = re * 10 + (ch ^ '0');
	}	while('0' <= (ch = getchar()) && ch <= '9');
	return re;
}
void uwit(reg long long da) {
	reg int cn = 0, ch[21];
	do {
		ch[++cn] = da - da / 10 * 10;
	} while(da /= 10);
	do {
		putchar('0' ^ ch[cn]);
	} while(--cn);
}
const int _maxn = 500011;
int n, t, a[_maxn], lazy[_maxn << 3], firs[_maxn], neig[_maxn], lasp, plef, prig;
long long data[_maxn << 3], dats[_maxn << 3], rans;
inl void push(reg int at, reg int le, reg int ri) {
	if(lazy[at]) {
		data[at] += 1ll * lazy[at] * (ri - le + 1);
		dats[at] += 1ll * lazy[at] * (le + ri) * (ri - le + 1) / 2;
		if(le != ri) {
			lazy[at << 1] += lazy[at];
			lazy[at << 1 | 1] += lazy[at];
		}
		lazy[at] = 0;
	}
}
void modi(reg int at, reg int le, reg int ri, reg int ql, reg int qr, reg int da) {
	if(ql <= le && ri <= qr) {
		lazy[at] += da;
	}	else {
		push(at, le, ri);
		if(ql <= (le + ri) >> 1) {
			modi(at << 1, le, (le + ri) >> 1, ql, qr, da);
		}
		if(qr > (le + ri) >> 1) {
			modi(at << 1 | 1, ((le + ri) >> 1) + 1, ri, ql, qr, da);
		}
		push(at << 1, le, (le + ri) >> 1);
		push(at << 1 | 1, ((le + ri) >> 1) + 1, ri);
		data[at] = data[at << 1] + data[at << 1 | 1];
		dats[at] = dats[at << 1] + dats[at << 1 | 1];
	}
}
long long quer(reg int at, reg int le, reg int ri, reg int ql, reg int qr) {
	push(at, le, ri);
	if(ql <= le && ri <= qr) {
		return data[at];
	}	else {
		reg long long re = 0;
		if(ql <= (le + ri) >> 1) {
			re += quer(at << 1, le, (le + ri) >> 1, ql, qr);
		}
		if(qr > (le + ri) >> 1) {
			re += quer(at << 1 | 1, ((le + ri) >> 1) + 1, ri, ql, qr);
		}
		return re;
	}
}
long long ques(reg int at, reg int le, reg int ri, reg int ql, reg int qr) {
	push(at, le, ri);
	if(ql <= le && ri <= qr) {
		return dats[at];
	}	else {
		reg long long re = 0;
		if(ql <= (le + ri) >> 1) {
			re += ques(at << 1, le, (le + ri) >> 1, ql, qr);
		}
		if(qr > (le + ri) >> 1) {
			re += ques(at << 1 | 1, ((le + ri) >> 1) + 1, ri, ql, qr);
		}
		return re;
	}
}
int main() {
	n = ured();
	t = ured();
	rep(i, 1, n) {
		a[i] = ured();
		firs[i - 1] = n + 1;
	}
	dep(i, n, 1) {
		neig[i] = firs[a[i]];
		firs[a[i]] = i;
	}
	rep(i, 0, n - 1) {
		lasp = 0;
		plef = -1;
		gep(j, i) {
			prig = plef + 1;
			plef = prig - (j - lasp - 1);
			rans += quer(1, -n - 1, n + 1, plef, prig) * prig - ques(1, -n - 1, n + 1, plef, prig) + quer(1, -n - 1, n + 1, -n - 1, plef - 1) * (prig - plef + 1);
			modi(1, -n - 1, n + 1, plef, prig, 1);
			lasp = j;
		}
		lasp = 0;
		plef = -1;
		gep(j, i) {
			prig = plef + 1;
			plef = prig - (j - lasp - 1);
			modi(1, -n - 1, n + 1, plef, prig, -1);
			lasp = j;
		}
	}
	uwit(rans);
	putchar('\n');
  return 0;
}
```

---

## 作者：chenxia25 (赞：1)

**[Portal]( https://www.luogu.com.cn/problem/P4062 )**

首先考虑用众数而非区间来贡献答案。我们考虑对每个数都处理出它所在的位置 list，然后对每个 list 独立搞。

一个简单粗暴的想法是，列出两个位置构成的区间满足条件的充要条件，然后发现是一个关于 $i$ 的式子和关于 $j$ 的式子的不等式，BIT 维护一下就行了，但这样每个是 $\mathrm O(n\log)$，最坏能被卡到 $\Omega\!\left(n^2\right)$。于是我们要努力让复杂度不关于 $n$，只关于当前数的个数。

于是我们一步步来把 $n$ 给去掉。首先肯定不能枚举右端点 $j$ 了。设当前数的位置 list 为 $a$。于是我们考虑枚举 $a_j\sim a_{j+1}-1$ 的这个 gap，这样至少枚举量不关于 $n$ 了。我们看对于左端点 $i$，它右边第一个为 $a_i'$，那么它与 $j$ 的共同贡献，就看一下它至少要伸多远，和  $a_{j+1}-1$ 取个 $\min$，然后算一下到 $a_j$ 的距离与 $0$ 取个 $\max$。式子列出来：
$$
\max\!\left(0,\min\!\left(a_{j+1}-1,a_i'+2(j-i+1)-1-1\right)-a_j+1\right)
$$
比较长的那串整理一下是 $a_i'+2j-2i$。然后有两个 $\min/\max$，考虑分类讨论：

1. $a_i'+2j-2i<a_{j+1}-1$ 即 $a_i'-2i+1<a_{j+1}-2j$。这样里面那个 $\min$ 的值就是 $a'_i+2j-2i$。然后还要使它 $\leq a_j-1$，不然会值为 $0$，即 $a'_i-2i+1\geq a_j-2j$，然后值是 $a'_i+2j-2i-a_j+1=\left(a'_i-2i+1\right)+(2j-a_j)$。于是这个我们每次将 $a'_i-2i+1$ 加入 BIT，然后数一下 $[a_j-2j,a_{j+1}-2j)$ 内的计数与和，就可以算了；
2. $a'_i+2j-2i\geq a_{j+1}-1$ 即 $a'_i-2i+1\geq a_{j+1}-2j$。这样值就是 $a_{j+1}-1-a_j+1=a_{j+1}-a_j$，这个只跟 $j$ 有关，于是后缀计数一下乘一下即可。

但是这样统计答案的次数是不跟 $n$ 有关了，但是加入 BIT 的次数还跟 $n$ 有关。于是我们考虑一个 gap 整体加入，那这显然计数是区间加，而和的失职，其实是区间加等差数列。我们考虑线段树维护，那么这个区间加等差数列、区间求和其实是个经典问题，只需要维护懒标记，然后下传的时候就用一下等差数列求和公式就可以了，可以 $\mathrm O(\log)$ 维护。这样总复杂度就是线对了。

然后每次不能重新建树，会 T，必须每次撤销。

**_[code]( https://www.luogu.com.cn/paste/61y8s1x7 )_**

---

