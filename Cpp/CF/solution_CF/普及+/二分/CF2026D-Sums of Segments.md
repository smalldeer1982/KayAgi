# Sums of Segments

## 题目描述

You are given a sequence of integers $ [a_1, a_2, \dots, a_n] $ . Let $ s(l,r) $ be the sum of elements from $ a_l $ to $ a_r $ (i. e. $ s(l,r) = \sum\limits_{i=l}^{r} a_i $ ).

Let's construct another sequence $ b $ of size $ \frac{n(n+1)}{2} $ as follows: $ b = [s(1,1), s(1,2), \dots, s(1,n), s(2,2), s(2,3), \dots, s(2,n), s(3,3), \dots, s(n,n)] $ .

For example, if $ a = [1, 2, 5, 10] $ , then $ b = [1, 3, 8, 18, 2, 7, 17, 5, 15, 10] $ .

You are given $ q $ queries. During the $ i $ -th query, you are given two integers $ l_i $ and $ r_i $ , and you have to calculate $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 样例 #1

### 输入

```
4
1 2 5 10
15
1 1
1 2
1 3
1 4
1 5
1 10
5 10
6 10
2 8
3 4
3 10
3 8
5 6
5 5
1 8```

### 输出

```
1
4
12
30
32
86
56
54
60
26
82
57
9
2
61```

# 题解

## 作者：lijunxi20231818 (赞：8)

一道前缀和好题。

## 思路

很显然我们要按照 $b$ 序列中 $s(l,r)$ 的 $l$ 来分成 $n$ 块，因为这样可以用前缀和。

然后要查询的区间就可以拆成很多个完整的块和两端多出来的东西。

都需要一个重要的式子：

$\text{query}(l,r)=\sum \limits _{i=l}^{r}s(l,i)$

$=\sum\limits _{i=l}^r(s(1,i)-s(1,l-1))$

$=\sum \limits _{i=l}^{r}s(1,i)-s(1,l-1)\times(r-l+1) $

$=\sum \limits _{i=1}^{r}s(1,i)-\sum\limits _{i=1}^{l-1}s(1,i)-s(1,l-1)\times(r-l+1)$

很容易看出来需要维护 $a$ 的前缀和 $\text{pre}$（处理 $s(1,l-1)$ 项） 以及 $\text{pre}$ 的前缀和 $\text{pre2}$（处理 $\sum s(1,i)$ 项）。

于是上式转换为：

$\text{query}(l,r)=\sum \limits _{i=l}^{r}s(l,i)=\text{pre2}_r - \text{pre2}_{l-1}-\text{pre}_{l-1}\times(r-l+1)$

### 整块的处理

记 $bs_i$ 为第 $i$ 块的整块答案。

易得 $bs_i=\sum\limits _{j=i}^n s(i,j)=\text{pre2}_n-\text{pre2}_{i-1}-\text{pre}_{i-1}\times(n-i+1)$。

由于需要求连续很多块的答案和，我们可以对 $bs$ 做前缀和。

```cpp
//bspre为bs的前缀和
for(int i = 1; i <= n; i++){
	bs[i] = pre2[n] - pre2[i - 1] - pre[i - 1] * (n - i + 1);
	bspre[i] = bspre[i - 1] + bs[i];
}
```

### 两端多余部分的处理

首先我们需要求出询问的 $l,r$ 都在哪个块。

这里可以用数学推式子的方法做，也可以用二分做，~~由于作者数学不好~~，这里用二分做。

我们考虑预处理出每个块的结尾位置 $id$，显然第 $i$ 个块有 $n-i+1$ 个元素，那么有 $id_i=id_{i-1}+n-i+1$。

然后使用二分就可以得到询问左右端点的块，记 $l$ 在第 $\text{lid}$ 块，$r$ 在第 $\text{rid}$ 块。

具体地:
```cpp
int lid = lower_bound(id + 1, id + n + 1, l) - id;
int rid = lower_bound(id + 1, id + n + 1, r) - id;
```

---

![](https://cdn.luogu.com.cn/upload/image_hosting/je9602n3.png)

如上图，我们可以发现，$l$ 位置对应 $s(\text{lid},n-(id[\text{lid}]-l))$，$r$ 位置对应 $s(\text{rid},n-(id[\text{rid}]-r))$。

然后我们就知道：

- 左侧多余部分答案为：

  $\sum\limits _{i=n-(id[\text{lid}]-l)}^{n}s(\text{lid},i)$



  $=\sum\limits _{i=\text{lid}}^{n}s(\text{lid},i)-\sum\limits _{i=\text{lid}}^{n-(id[\text{lid}]-l)-1}s(\text{lid},i)$



  $=bs_{\text{lid}}-\sum\limits _{i=\text{lid}}^{n-(id[\text{lid}]-l)-1}s(\text{lid},i)$。


  $=bs_{\text{lid}}-\text{query(lid,}n-(id[\text{lid}]-l)-1)$

- 右侧多余部分答案为：

  $\sum\limits _{i=\text{rid}}^{n-(id[\text{rid}]-r)}s(\text{rid},i)=\text{query(rid,}n-(id[\text{rid}]-r))$

```cpp
int ans = 0;
ans += bs[lid] - query(lid, n - (id[lid] - l) - 1);
ans += query(rid, n - (id[rid] - r));
ans += bspre[rid - 1] - bspre[lid];
cout << ans << '\n';
```

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {int x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const int maxn = 3e5 + 5;
int n, q;
int a[maxn];
int bs[maxn], pre[maxn], pre2[maxn], bspre[maxn];
int id[maxn];
int query(int l, int r){
	if(r < l) return 0;
	return pre2[r] - pre2[l - 1] - pre[l - 1] * (r - l + 1);
}
signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		id[i] = (2 * n - i + 1) * i / 2;
	}
	for(int i = 1; i <= n; i++){
		a[i] = read();
		pre[i] = pre[i - 1] + a[i];
		pre2[i] = pre2[i - 1] + pre[i];
	}
	for(int i = 1; i <= n; i++){
		bs[i] = pre2[n] - pre2[i - 1] - pre[i - 1] * (n - i + 1);
		bspre[i] = bspre[i - 1] + bs[i];
	}
	q = read();
	while(q--){
		int l = read(), r = read();
		int lid = lower_bound(id + 1, id + n + 1, l) - id;
		int rid = lower_bound(id + 1, id + n + 1, r) - id;
		int ans = 0;
		ans += bs[lid] - query(lid, n - (id[lid] - l) - 1);
		ans += query(rid, n - (id[rid] - r));
		ans += bspre[rid - 1] - bspre[lid];
		cout << ans << '\n';
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/2026/submission/300532339)

![](https://cdn.luogu.com.cn/upload/image_hosting/3t61cqw5.png)

---

## 作者：BYR_KKK (赞：4)

小清新题。

令 $ans_{l,r}$ 代表 $\sum\limits_{i=l}^r b_i$，则 $ans_{l,r}=ans_{1,r}-ans_{1,l-1}$。

考虑求 $ans_{1,i}$，令 $f_i=\sum\limits_{j=i}^n s(i,j)$。则 $ans_{1,i}$ 是由 $f$ 的一段前缀和加上形如 $\sum\limits_{j=k}^{lim}s(k,j)$ 得到的。$k$ 可以二分出来，只需要考虑如何求 $\sum\limits_{j=k}^{lim} s(k,j)$ 即可。

借用刚才的做法，这个东西等价于 $f_k-\sum\limits_{j=lim+1}^ns(k,j)$，拆一下贡献，令 $g_i$ 表示 $a_i$ 的前缀和，则有 $\sum\limits_{j=lim+1}^ns(k,j)=f_{lim+1}+(g_{lim}-g_{k-1})\times (n-lim)$，直接做即可。

时间复杂度 $O(q\log n)$。

---

## 作者：postpone (赞：3)

把 $b$ 数组分成一块一块的，每一块是开头相同的 $s$ 组成的段。

设 $f_i$ 表示第 $i$ 块的答案，即 $\sum_{j=i}^{n} s(i, j)$，我们将询问的区间答案化为前缀和相减的形式，只要算 $\text{ans}_{1\rightarrow x}$ 即可，这个可以拆成整的块和最后散的几个。

先看整的块的答案怎么求，作出 $a$ 的前缀和，以及前缀和的前缀和，记为 $\rm pre$ 和 $\rm ppre$，有：

$$
f_i=\text{ppre}_n - \text{ppre}_{i - 1} - \text{pre}_{i - 1} \times (n - i + 1)
$$

怎么去理解它呢？假如 $n=4$，要求 $f_2$，即要求这么一块（数字表示下标）：

$$
2\rightarrow2,2\rightarrow3,2\rightarrow4
$$

$\text {ppre}_n$ 表示的是：

$$
\begin{align*}
&1\rightarrow1,1\rightarrow2,1\rightarrow3,1\rightarrow4 \\
\end{align*}
$$

$\text {ppre}_n - \text{ppre}_1$ 表示的是

$$
\begin{align*}
1\rightarrow2,1\rightarrow3,1\rightarrow4 \\
\end{align*}
$$

再减去块的大小与前面的数的和的乘积，对于这个示例，就是减去 $3$ 个 $1$ 的贡献，最后就变成了：

$$
2\rightarrow2,2\rightarrow3,2\rightarrow4
$$

也就是要求的东西了。

我们现在知道怎么求一整块了，那散的该怎么办呢？接着上面的例子，比如要求：

$$
2\rightarrow2,2\rightarrow3
$$

那其实就是把 $\text {ppre}_4$ 替换成 $\text{ppre}_3$，其他的与求 $f_i$ 的过程一样。

备注：散的肯定也是从形似 $s(i, i)$ 开始的。

回到题目，对于 $\text{ans}_x$，先二分找到 $x$ 所在的块，然后如上所述拆成整块和散块即可，复杂度 $O(q\log n)$，代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }

    vector<ll> ppre(n + 1);
    for (int i = 1; i <= n; i++) {
        ppre[i] = ppre[i - 1] + pre[i];
    }

    // 这里的 f 已经进行了前缀和处理
    vector<ll> f(n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] + ppre[n] - ppre[i - 1] - pre[i - 1] * (n - i + 1);
    }

    vector<ll> siz(n + 1);
    for (int i = 1; i <= n; i++) {
        siz[i] = siz[i - 1] + n - i + 1;
    }

    auto sum = [&](ll x) -> ll {
        int u = lower_bound(siz.begin() + 1, siz.end(), x) - siz.begin();
        u--;

        ll y = u + x - siz[u];

        ll res = f[u];
        res += ppre[y] - ppre[u] - pre[u] * (y - u);

        return res;
    };

    int q;
    cin >> q;

    while (q--) {
        ll l, r;
        cin >> l >> r;

        cout << sum(r) - sum(l - 1) << "\n";
    }

    return 0;
}
```

---

