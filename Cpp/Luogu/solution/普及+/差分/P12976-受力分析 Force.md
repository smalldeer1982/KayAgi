# 受力分析 Force

## 题目背景

还在写题的 Comentropy 突然收到了挑战，竟然是一道力学题！他感到震惊，一看到数据范围就知道该怎么写了，但是过程冗长，于是找到你帮他精简一下。

注：本题没有严格的物理理论基础，且本题并不要求物理基础。

**建议阅读形式化题意。**

## 题目描述

现在有 $n\times n$ 个正方体物块摆成一个方阵，物块有自己的重量，你现在需要控制它们平衡不动。这就要求对于第 $i$ 行第 $j$ 列的物块，它底面受到的支持力在区间 $[l_{i,j},r_{i,j}]$ 中。

出题人们给出横纵方向各 $n$ 根钢丝用以给底面支持力，并把物块放置在钢丝交点处。现在你可以给这 $2n$ 根钢丝分别施加力。（注意同一根钢丝处处的力是相同的）

规定：在数值上，物块受到的支持力就是你施加给其下的两根钢丝的力的和。

![](https://cdn.luogu.com.cn/upload/image_hosting/shg5p17w.png)

如图，有两组钢丝一组横着放，施加给它们的力分别是：$[x_1,x_2,\dots,x_n]$；一组竖着放，施加给它们的力分别是：$[y_1,y_2,\dots,y_n]$，交点 $(i,j)$ 处的合力即为：$x_i+y_j$。

请你求出每根钢丝的使用力的情况。出题人们为了难倒 Comentropy，还要求序列 $[x_1,x_2,\dots,x_n,y_1,y_2\dots,y_n]$ 的字典序最小。你能帮他处理这个问题吗？

**每个力都应当是非负整数，方向向上。**

**形式化地**：
给出两个 $n\times n$ 的矩阵 $l,r$，要求 $l_{i,j}\leq x_i+y_j \leq r_{i,j}$，求一个字典序最小的非负整数解的序列 $\{x\}$, $\{y\}$（把 $x$ 和 $y$ 的序列并起来 $[x_1,x_2,\dots,x_n,y_1,y_2,\dots,y_n]$ 的字典序最小）。

## 说明/提示

**样例 1 解释：** 可能有另一组解 $x_1=2,x_2=2,y_1=0,y_2=3$，但是 $\{0,0\},\{2,5\}$ 是一组字典序更小的解，且能证明字典序最小。

对于 $10\%$ 的数据，保证 $1\leq n\leq 7,0 \leq r_{i,j}\leq 7$。

对于 $20\%$ 的数据，保证 $1\leq n\leq 50$，$1 \leq l_{i,j}\leq r_{i,j} \leq 200$。

对于 $40\%$ 的数据，保证 $1\leq n\leq 200$。

对于另外 $20\%$ 的数据，保证 $l_{i,j}=r_{i,j}$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 500$，$0 \leq l_{i,j} \leq r_{i,j} \leq 10^9$。

**请注意常数给程序带来的运行效率影响。**

## 样例 #1

### 输入

```
2
2 4
1 5
3 5
2 7```

### 输出

```
0 0 
2 5```

# 题解

## 作者：Comentropy (赞：7)

如果我们把 $x$ 取反，会得到一个经典的差分约束形式：

$$
\begin{aligned}
&l_{i,j}\leq -(-x_i)+y_j\leq r_{i,j}\\
&\begin{cases}
&(-x_i)\leq y_j-l_{i,j}\\
&y_{j}-r_{i,j}\leq (-x_i)
\end{cases}
\end{aligned}
$$

我们要最小化 $x$ 的字典序，相当于最大化 $(-x_i)\leq 0$ 的字典序。（当然这一步也可以取反 $y$。）

讲讲经典的差分约束做字典序问题的方法（会了可以跳过）。

我们这个问题有一个限制是：$-x_i\leq 0\leq y_j$。所以是存在一个上界的，可以求解最大字典序。

问题可以先简化为对 $a_i\leq 0+0$ 的约束，我们对每个约束建边跑最短路。每个约束形如 $a_i+w(i,j)\geq a_j$，我们利用松弛不等式对 $i$ 到 $j$ 建边，边权为 $w(i,j)$。

跑出来的最短路，从 $0$ 到 $i$ 的最短路满足 $a_u+w(u,v)=a_v$。也就是，这条路上的每个约束都取到了上界上，导致了 $a_i$ 的值也在上界，这条路径上任何一个值 $+1$ 都会出问题。

但是我们这个问题里面有个 $y\geq 0$ 啊，和 $x\leq 0$ 的限制又不一样了！这个怎么处理？

我们知道的是 $-x$ 已然取到上界，然而最短路却有可能不经过某些 $y$，这些 $y$ 是有可能被调整的，而我们已经知道 $x$，直接把它们代进不等式，把 $y$ 调整成可取的最小值就行了。

直接写差分约束就做完了。

---

## 作者：y_kx_b (赞：2)

赛时被硬控 2h 然后有一个处理（新建 `dis` 为 $0$ 的辅助点）没想到，喜提 30 pts。

做法好像和官解不太一样……？

我们直入主题吧。

$l_{i,j}\leqslant x_i+y_j\leqslant r_{i,j}$，考虑先固定 $x$，那么 $y_j$ 的取值范围就是一系列平移之后的线段的交。

字典序要求**先**让 $x_i$ 尽可能小，所以考虑什么时候有解。考虑怎么处理 $n$ 个线段有交，猜当且仅当两两线段有交。（~~oi 为什么需要证明？猜就完事了！~~ 证明见文末。）

那么考虑两条线段有交的问题。对于同一个 $j$ 有 $\begin{cases}(l_{i,j}-x_i)\leqslant y_j\leqslant (r_{i,j}-x_i)\\(l_{{i^\prime},j}-x_{i^\prime})\leqslant y_j\leqslant (r_{{i^\prime},j}-x_{i^\prime})\end{cases}$，两条线段有交那么 $l_{\max}\leqslant r_{\min}$ 即 $\begin{cases}(l_{i,j}-x_i)\leqslant (r_{{i^\prime},j}-x_{i^\prime})\\(l_{{i^\prime},j}-x_{i^\prime})\leqslant(r_{i,j}-x_i) \end{cases}$，整理就是 $x_i-x_{i^\prime}\geqslant (l_{i,j}-r_{{i^\prime},j})$ 的形式。这是什么？差分约束！贺个板子先。$\mathcal O(n^2)$ 建图，spfa 最坏复杂度 $\mathcal O(nm)=\mathcal O(n^3)$，基本没问题。

仔细一想，差分约束求出的就是天然最大解（不等式 $dis_v\leqslant dis_u+w$ 很多都取等了），但我们需要最小解，好办！$x_i-x_{i^\prime}\geqslant w\Leftrightarrow (-x_{i^\prime}) - (-x_i) \geqslant w$，$-x$ 最大解就是 $x$ 最小解了。然后把 $x_i$ 带回原式可以得到 $y_j$ 的取值范围，最小值就出来了。

你说的对，但是需要 $x_i\geqslant 0$ 怎么办？一开始容易想到平移（所有 $x_i$ 加一个数，所有 $y_j$ 减这个数，解仍然合法），然后一交只有 30pts。事实上考虑比如最小解 $(0,-1)$ 不合法，如果 $(0,0)$ 合法，你对最小解直接平移变成 $(1,0)$ 就不是最优解了。怎么办呢？注（看）意（题）到（解）！$(-x_i) \leqslant 0 + 0$，那么新建一个点令其 `dis` 为 $0$ 然后建边权为 $0$ 的边就好了。

你说的对，但是需要 $y_j\geqslant 0$ 怎么办？我还是采用平移的方法，但事后发现根本不会出现 $y_j<0$ 的情况。事实上（感谢出题人 @[Comentropy](https://www.luogu.com.cn/user/264360)），如果存在 $y_j<0$ 那么 $\forall i\ x_i \geqslant l_{i,j}-y_j\geqslant1$（因为 $-y_j>0,l_{i,j}\geqslant0$），也就是说 $x$ 内没有 $0$，那么可以进行如下的调整：将所有 $x_i$ 减小 $1$ 同时将所有 $y_j$ 增大 $1$，调整后的解一定合法，与调整前解字典序最小矛盾。所以直接求出的 $y_j$ 一定非负。

下面是我的实现：（完整代码见 [R221749640](https://www.luogu.com.cn/record/221749640)）
```cpp
// 注意 dis 要开 long long 不然负环走几圈早爆 int 了
#define rep(i, x, y) for(auto i = (x); i <= (y); i++)
int l[N][N], r[N][N];
int ans1[N], ans2[N];//即题目中的 x, y
int main() {
    scanf("%d", &n);
    rep(i, 1, n) rep(j, 1, n) scanf("%d", l[i] + j);
    rep(i, 1, n) rep(j, 1, n) scanf("%d", r[i] + j);
    rep(i, 1, n) rep(j, 1, n) if(i != j) {//此处 j 即为题解中 i', k 为题解中 j
        // xi - xj >= l(i,k) - r(j,k), (-xj) - (-xi) >= ~
        int p = -(1 << 30);
        rep(k, 1, n) p = max(p, l[i][k] - r[j][k]);
        //b - a >= x, a <= b - x, dis(i) <= dis(j) + (-x)
        add(j, i, -p);
    }
    rep(i, 1, n) add(n + 1, i, 0); //dis(u) <= dis(n + 1) ( = 0) + w (= 0)
    SPFA(n + 1);//dis(n+1) 天然为 0
    if(negative_loop) return puts("-1"), 0;//不要忘了main返回值是0！
    rep(i, 1, n) ans1[i] = -dis[i];
    int mn = *std::min_element(ans1 + 1, ans1 + n + 1);//注意不要写成 min(int*, int*)，后者在对指针取min（
    rep(i, 1, n) ans1[i] -= mn;//平移，使最小值为 0，防止求出 (1,1) 这种解
    rep(j, 1, n) {
        ans2[j] = -(1 << 30);
        rep(i, 1, n) ans2[j] = max(ans2[j], l[i][j] - ans1[i]);
    }
    assert(*std::min_element(ans2 + 1, ans2 + n + 1) >= 0);//proved.
    rangewriteln(ans1 + 1, ans1 + n + 1);
    rangewriteln(ans2 + 1, ans2 + n + 1);
    return 0;
}
```
撒花！

---
另外提供一个自造样例：
```
2
2 4
1 5
3 6
2 7
```
题面样例改了一个数，输出和题面样例一致。应该能很搞出一些错吧。

---

对于“$n$ 个线段有交当且仅当两两线段有交”的证明：充分性显，考虑必要性（如果 $n$ 个线段两两有交，那么这些线段就有交吗？）。注意到 $n$ 条线段的交就是 $[l_{\max}, r_{\min}]$，如果 $n$ 条线段没有交那么一定存在一个 $l$ 比另一个 $r$ 大，那么这两条线段就没有交，必要性得证。事实上推广到集合就不成立了（比如 $\big\{\{1,2\},\{2,3\},\{1,3\}\big\}$）。

---

## 作者：chenbs (赞：1)

数学题。

考虑 $x_a$ 和 $x_b$ 需要满足的条件：

$$\forall i, l_{a,i} \le x_a + y_i \le r_{a,i}, l_{b,i} \le x_b + y_i \le r_{b,i}$$

移项得，

$$\forall i, l_{a,i} - x_a \le y_i \le r_{a,i} - x_a, l_{b,i} - x_b \le y_i \le r_{b,i} - x_b$$

所以，

$$\forall i, l_{b,i} - x_b \le r_{a,i} - x_a, l_{a,i} - x_a \le r_{b,i} - x_b$$

再移项，

$$\forall i, l_{b,i} - r_{a,i} + x_a \le x_b, l_{a,i} - r_{b,i} + x_b \le x_a$$

由数学知识，前面的 $\forall i$ 可以进一步转换为 $x_a +\max\{l_{b,i} - r_{a,i}\} \le x_b$，符合差分约束的形式。

另外，题目中还有一个条件 $x_a \ge 0$。这个也很好处理，一种实现方法是：建立一个节点 $0$，从节点 $0$ 向所有的点连权值为 $0$ 的边即可。（相当于 $x_a \ge x_0 + 0$）

差分约束得到了最小的 $x$ 之后，容易证明一定存在 $y$ 符合条件，贪心取最小即可。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, l[505][505], r[505][505], mp[505][505], vis[505], cnt[505];
queue<int> q;
long long x[505]; // 这里用 long long 防止加的时候爆炸
void spfa() {
	memset(x, -1, sizeof x);
	q.push(0), vis[0]=1, x[0]=0;
	while(!q.empty()) {
		int cur=q.front();
		q.pop();
		vis[cur]=0;
		for(int i=1; i<=n; i++) {
			if(i!=cur && x[cur]+mp[cur][i] > x[i]) {
				x[i] = x[cur]+mp[cur][i];
				if(++cnt[i] > n) cout<<-1, exit(0); // 判无解
				if(!vis[i]) vis[i]=1, q.push(i);
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%d", &l[i][j]);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%d", &r[i][j]);
	for(int a=1; a<=n; a++)
		for(int b=1; b<=n; b++) {
			int t=-1e9;
			for(int i=1; i<=n; i++) t=max(t, l[b][i]-r[a][i]);
			mp[a][b]=t;
		}
	spfa();
	for(int i=1; i<=n; i++) cout<<x[i]<<" ";
	cout<<'\n';
	for(int i=1; i<=n; i++) {
		long long t=0;
		for(int j=1; j<=n; j++) t=max(t, l[j][i]-x[j]);
		cout<<t<<" ";
	}
	return 0;
}
```

---

