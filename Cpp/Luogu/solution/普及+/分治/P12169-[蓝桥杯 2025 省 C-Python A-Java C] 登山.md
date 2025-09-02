# [蓝桥杯 2025 省 C/Python A/Java C] 登山

## 题目描述

小蓝正在登山，山峰的高度构成 $n$ 行 $m$ 列的正整数矩阵，$a_{i,j}$ 表示第 $i$ 行第 $j$ 列格子 $(i,j)$ 上的山峰的高度。小蓝以一种特别的方式进行登山，如果他此刻在第 $p$ 行第 $q$ 列的格子 $(p,q)$ 上，那么下一步可以选择：

1. 走到格子 $(i,q)$，满足 $a_{i,q} < a_{p,q}$ 且 $i > p$；
2. 走到格子 $(i,q)$，满足 $a_{i,q} > a_{p,q}$ 且 $i < p$；
3. 走到格子 $(p,j)$，满足 $a_{p,j} < a_{p,q}$ 且 $j > q$；
4. 走到格子 $(p,j)$，满足 $a_{p,j} > a_{p,q}$ 且 $j < q$。

小蓝想知道，如果他依次从每一个格子开始出发，按照最优策略，他最高能到达的山峰的高度的平均值是多少？

## 说明/提示

### 样例说明 1

除了从格子 $(1,1)$ 出发以外，其他格子都能到达高度为 $3$ 的山峰，$(1 + 3 + 3 + 3)/4 = 2.5$。

### 样例说明 2

每个格子能到达的高度：

$$\begin{matrix} 4 & 4 & 4 \\ 4 & 4 & 5\end{matrix}$$

其中 $(1,1)$ 可以先到达格子 $(1,3)$ 再到达格子 $(1,2)$。

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$1 \leq n, m \leq 10^2$；
- 对于所有评测用例，$1 \leq n, m \leq 10^4$，$1 \leq n \times m \leq 10^6$，$1 \leq a_{ij} \leq 10^9$。

## 样例 #1

### 输入

```
2 2
1 3
3 2```

### 输出

```
2.500000```

## 样例 #2

### 输入

```
2 3
2 4 1
4 2 5```

### 输出

```
4.166667```

# 题解

## 作者：Levisuper (赞：1)

### 算法：并查集

由于行列是同一套逻辑，所以下面只说同一列内的行操作，同一行内的列操作直接照抄即可。

设现在我们在 $(x, y)$，且存在点 $(i, y)$ 满足 $i > x$ 且 $a_{i, y} < a_{x, y}$，那么我们可以从 $(x, y)$ 向 $(i, y)$ 连边表示 $(x, y)$ 可达 $(i, y)$。

那么同理，如果我们在 $(i, y)$，根据题中所说，$(x, y)$ 满足 $x < i$ 且 $a_{x, y} > a_{i, y}$，同样可以从 $(i, y)$ 向 $(x, y)$ 连边。

也就是说，只要存在一个逆序对，就有一对**双向边**！

但是直接 $O(n^2)$ 遍历 $O(m)$ 次复杂度过高，所以我们需要逆序对连边的等价命题。

**先给出命题：对于第 $j$ 列，设 $pre[i]$ 表示前 $i$ 个元素的最大值，$suf[i]$ 表示 $[i, n]$ 内元素的最小值，如果 $pre[i] > suf[i + 1]$，就连一条 $(i, j)$ 到 $(i + 1, j)$ 的边。**

为了方便，做几点说明。

- 逆序对连边生成的边集为 $E_0$，相邻连边生成的边集为 $E_1$；
- 简写 $(l, j)$ 到 $(r, j)$ 连双向边为 $l \Longleftrightarrow r$。

**下面证明二者等价。**

若有 $a_{l, j} > a_{r, j}$，那么有 $l \Longleftrightarrow r$，而对于 $i \in [l, r)$，一定有 $pre[i] > suf[i + 1]$，那也就是说，$E_1$ 会包含 $l \Longleftrightarrow l + 1, \ \ l + 1 \Longleftrightarrow l + 2, \ \ \cdots, \ \ r - 1 \Longleftrightarrow r$，这相当于包含了一条 $l \Longleftrightarrow r$ 的双向边，所以 $E_0 \subseteq E_1$。

若有 $pre[i] > suf[i + 1]$，那么有 $i \Longleftrightarrow i + 1$，同时，由前缀最大和后缀最小的性质可以得到，必然存在 $l \in [1, i]$ 和 $r \in (i, n]$，使得 $a_{l, j} > a_{r, j}$，那么首先就有 $l \Longleftrightarrow r$。如果 $l < i$，说明 $a_{l, j} > a_{i, j}$，由题目条件有 $l \Longleftrightarrow i$，同理如果 $i + 1 < r$，那么 $i + 1 \Longleftrightarrow r$，将这三条边合起来，就包含了一条 $i \Longleftrightarrow i + 1$ 的双向边，所以 $E_1 \subseteq E_0$。

综上，$E_0 = E_1$，二者等价。

设我们这样得到了 $N$ 个连通块，第 $i$ 个连通块的大小为 $siz_i$，其块内最大值为 $\max_i$，则最终答案为

$$
\sum\limits_{i = 1}^{N}siz_i \times max_i.
$$

#### 时间复杂度 $O(\rm{nm \cdot \alpha(nm)})$

- 其中 $\rm{\alpha(nm)}$ 是反阿克曼函数，一般可以看作 $3, 4$ 左右的常数。

#### C++ Code

```cpp
#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
    std::vector<int> f, sz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    int size(int x) {
        return sz[find(x)];
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        sz[x] += sz[y];
        f[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

template<class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}
constexpr int inf = std::numeric_limits<int>::max() / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(6);
    
    int n, m;
    std::cin >> n >> m;

    const int N = n * m;

    std::vector<int> a(N);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i * m + j];
        }
    }

    DSU dsu(N);
    for (int i = 0; i < n; i++) {
        std::vector pre(m + 1, 0);
        std::vector suf(m + 1, inf);
        for (int j = 0; j < m; j++) {
            pre[j + 1] = std::max(pre[j], a[i * m + j]);
        }
        for (int j = m - 1; j >= 0; j--) {
            suf[j] = std::min(suf[j + 1], a[i * m + j]);
        }
        for (int j = 1; j < m; j++) {
            if (pre[j] > suf[j]) {
                dsu.merge(i * m + (j - 1), i * m + j);
            }
        }
    }
    for (int j = 0; j < m; j++) {
        std::vector pre(n + 1, 0);
        std::vector suf(n + 1, inf);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = std::max(pre[i], a[i * m + j]);
        }
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = std::min(suf[i + 1], a[i * m + j]);
        }
        for (int i = 1; i < n; i++) {
            if (pre[i] > suf[i]) {
                dsu.merge((i - 1) * m + j, i * m + j);
            }
        }
    }

    std::vector max(N, 0);
    for (int i = 0; i < N; i++) {
        chmax(max[dsu.find(i)], a[i]);
    }
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
        if (dsu.find(i) == i) {
            ans += 1LL * dsu.size(i) * max[i];
        }
    }
    std::cout << 1.* ans / n / m << "\n";
    
    return 0;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题解

我们可以将 $n\times m$ 个元素抽象成一张图 $G$。题目给出的四种选择即构成了 $G$ 中的边。

注意到选择 1 和选择 2、选择 3 和选择 4 是对称的，即如果 $a$ 能直接走到 $b$，那么 $b$ 就能直接走到 $a$，因而这些边是双向的。只要我们使用并查集求出哪些节点是互相可达的，以及每个连通块里高度最高的节点，即可快速求解。

考虑同一列的格子之间的直接连边，同一行的格子的情况类似。假设第 $i$ 列格子自上而下的高度分别为 $h_1, h_2, \cdots, h_m$，那么 $h_x$ 和 $h_y$ 通过选择 1 和 2 互相直接连边，当且仅当 $h_x>h_y$。换言之，**我们会对每个逆序对连一条边**。

套路地，考虑使用归并排序处理逆序对问题。假设我们需要处理 $[l, r]$ 元素的归并问题，将其折半为两个子区间 $[l_1, r_1]$ 和 $[l_2, r_2]$（$l_1\le r_1<l_2\le r_2$，$r_1+1=l_2$），这两个区间已经分别从小到大排序。

设 $[l_1, r_1]$ 里高度最大的元素为 $a$，$[l_2,r_2]$ 里高度最小的元素为 $b$，若 $h_b\ge h_a$ 则不会形成任何逆序对；否则 $[l_1, r_1]$ 里所有在 $(h_b, h_a]$ 里的元素，以及 $[l_2, r_2]$ 里所有在 $[h_b, h_a)$ 里的元素都会被连接在同一个连通块里（比较显然，读者可以模拟一下）。显然只需要 $\mathcal O(r-l)$ 次合并操作。

归并排序的复杂度为 $\mathcal O(n\log n)$，尽管最多有 $nm\log(nm)$ 次合并操作，然而均摊可知合并操作的总复杂度不超过 $\mathcal O(nm\log (nm))$，因而总时间复杂度为 $\mathcal O(nm\log(nm))$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 3;
const int MAXM = 1e6 + 3;
int F[MAXM], W[MAXM], M[MAXM];
int n, m;
int get_id(int i, int j){
    return (i - 1) * m + j;
}

int get_fa(int x){
    return x == F[x] ? x : F[x] = get_fa(F[x]);
}

void merge(int a, int b){
    if(a == 0 || b == 0)
        return;
    int fa = get_fa(a);
    int fb = get_fa(b);
    if(fa != fb){
        W[fa] = max(W[fa], W[fb]);
        F[fb] = fa;
    }
}

int I[MAXN], J[MAXN];
bool cmp(int a, int b){
    return M[a] < M[b];
}
void solve(int l, int r){
    if(l == r){
        return;
    }
    int o = (l + r) >> 1;
    solve(l, o);
    solve(o + 1, r);

    int mn = 1e9, mx = -1e9;
    for(int i = l;i <= r;++ i){
        if(i <= o) mx = max(mx, M[I[i]]);
            else   mn = min(mn, M[I[i]]);
    }

    int last = 0;
    for(int i = l;i <= r;++ i){
        if(i <= o){
            if(mn < M[I[i]]) merge(last, I[i]), last = I[i];
        } else {
            if(M[I[i]] < mx) merge(last, I[i]), last = I[i];
        } 
    }
    
    int p = o + 1, t = l;
    for(int i = l;i <= o;){
        while(p <= r && cmp(I[p], I[i])){
            J[t ++] = I[p ++];
        }
        J[t ++] = I[i ++];
    }
    while(p <= r)
        J[t ++] = I[p ++];
    for(int i = l;i <= r;++ i)
        I[i] = J[i];
}

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;++ i){
        for(int j = 1;j <= m;++ j){
            int w, u = get_id(i, j);
            cin >> w;
            F[u] = u;
            M[u] = W[u] = w;
        }
    }
    for(int i = 1;i <= n;++ i){
        for(int j = 1;j <= m;++ j){
            I[j] = get_id(i, j);
        }
        solve(1, m);
    }
    for(int i = 1;i <= m;++ i){
        for(int j = 1;j <= n;++ j){
            I[j] = get_id(j, i);
        }
        solve(1, n);
    }
    int cnt = 0;
    for(int i = 1;i <= n;++ i){
        for(int j = 1;j <= m;++ j)
            cnt += get_id(i, j) ==  get_fa(get_id(i, j));
    }

    long long ans = 0;
    for(int i = 1;i <= n;++ i){
        for(int j = 1;j <= m;++ j)
            ans += W[get_fa(get_id(i, j))];
    }
    cout << fixed << setprecision(6) << 1.0L * ans / n / m << endl;
    return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 背景

看到小波发的讨论来做这题。

然后谔谔。

建议删除分治标签，改为单调栈和并查集。

## 题解

首先注意到只要有大的在前小的在后他们就是双向连通的。这点启发我们使用并查集和单调栈解决问题。

那么显而易见地，这个单调栈是递增形态的。但是你会发现一个问题。

那就是如果你在把所有大过它的都 merge 进去之后只留下这个位置就会发现后面本来能被 merge 的位置 merge 不进去了。

所以正确方法是在弹掉所有能 merge 的元素之后重新把最大的元素压进去。这样是最优的。

然后就做完了。

时间复杂度 $O(nm\alpha(nm))$。

很难想象当时蓝桥杯出题组给这题定 5s 限时时的心理状态。

## 代码

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
int n, m, f[N], a[N], stk[N], ps;
constexpr int rmp(int x, int y)
{
	return x * m + y;
}
inline int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)
		return;
	if (a[x] < a[y])
		swap(x, y);
	f[y] = x;
}
using ll = long long;
ll res;
void run()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[rmp(i, j)];
			f[rmp(i, j)] = rmp(i, j);
		}
	}
	for (int i = 0; i < n; i++)
	{
		ps = 0;
		for (int j = 0, ori = 0; j < m; j++)
		{
			ori = ps;
			stk[ps + 1] = rmp(i, j);
			while (ps and a[stk[ps]] > a[rmp(i, j)])
				merge(stk[ps], rmp(i, j)), ps--;
			if (ps != ori)
			{
				stk[++ps] = stk[ori];
				continue;
			}
			else
				ps++;
		}
	}
	for (int j = 0; j < m; j++)
	{
		ps = 0;
		for (int i = 0, ori = 0; i < n; i++)
		{
			ori = ps;
			stk[ps + 1] = rmp(i, j);
			while (ps and a[stk[ps]] > a[rmp(i, j)])
				merge(stk[ps], rmp(i, j)), ps--;
			if (ps != ori)
			{
				stk[++ps] = stk[ori];
				continue;
			}
			else
				ps++;
		}
	}
	for (int i = 0; i < n * m; i++)
	{
		res += a[find(i)];
	}
	cout << fixed << setprecision(6) << 1.0 * res / (n * m) << '\n';
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

