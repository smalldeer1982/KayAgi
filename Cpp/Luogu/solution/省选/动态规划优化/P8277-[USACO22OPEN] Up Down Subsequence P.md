# [USACO22OPEN] Up Down Subsequence P

## 题目描述

Farmer John 的 $N$ 头奶牛（$2 \leq N \leq 3\cdot 10^5$），编号为 $1 \ldots N$，排列成 $1\ldots N$ 的一个排列 $p_1,p_2,\ldots,p_N$。另外给定一个长为 $N-1$ 的字符串，由字母 U 和 D 组成。请求出最大的 $K\le N-1$，使得存在 $p$ 的一个子序列 $a_0,a_1,\ldots,a_{K}$，满足对于所有 $1\le j\le K$，当字符串中第 $j$ 个字母是 U 时 $a_{j - 1} < a_j$，当字符串中的第 $j$ 个字母是 D 时 $a_{j - 1} > a_j$。


## 说明/提示

【样例解释 1】

我们可以选择 $[a_0,a_1,a_2,a_3,a_4]=[p_1,p_2,p_3,p_4,p_5]$；整个排列与给定的字符串相一致。

【样例解释 2】

我们可以选择 $[a_0,a_1,a_2,a_3]=[p_1,p_3,p_4,p_5]$。

【测试点性质】

- 测试点 3-4 满足 $N\le 500$。
- 测试点 5-8 满足 $N\le 5000$。
- 测试点 9-12 中，字符串中的 U 均在 D 之前。
- 测试点 13-22 没有额外限制。


## 样例 #1

### 输入

```
5
1 5 3 4 2
UDUD```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 5 3 4 2
UUDD```

### 输出

```
3```

# 题解

## 作者：xiaoyaowudi (赞：12)

## 题意

给定一个排列 $p$ 和一个字符串 $s$，$s$ 由大于小于号组成，求 $p$ 中最长的子序列 $t_0,t_1,t_2\cdots t_k$ 使得 $t_i,t_{i+1}$ 的大小关系和 $s_{i+1}$ 相同。

$n\le 3\times 10^5$。

## 分析

下文假设如果 $x$ 表示一个大于小于号，那么 $\hat{x}$ 表示相反的符号。

设 $f_i$ 为 $p_1,p_2,\cdots p_i$ 中以 $p_i$ 结尾的子序列在 $s_i$ 中能匹配的最长前缀长度。

下证，存在一个下标子序列 $x_0,x_1\cdots x_{f_i},x_{f_i}=i$ 使得 $\forall 0\le k\le f_i,k=f_{x_k}$，$p_{x_0},\cdots p_{x_{f_i}}$ 能够匹配 $s_1,s_2\cdots s_{f_i}$。

假设 $t_0,t_1,\cdots t_{f_i}$ 为 $x_{f_k},x_{f_k-1},\cdots x_0$ 字典序最小时对应的 $p_{x_0},p_{x_1}\cdots p_{x_{f_i}}$，因为 子序列个数有限，因此 $t$ 存在。

若存在 $0\le k \lt f_i$ 使得 $f_{x_k}\gt f_i$，

假设 $j=x_k,r=f_j,l=f_i$，$j$ 达成最大匹配时子序列为 $b_0,b_1\cdots b_r$。

那么 $b_{k}\; s_{k+1}\;b_{k+1}\;s_{k+2}\cdots b_{r-1}\;s_{r}\;b_{r}$，且 $b_r=t_k \;s_{k+1}\; t_{k+1}\;s_{k+2}\;\cdots s_{l}\;t_{l} $。

下证 $b_{k},b_{k+1},\cdots b_{r}=t_k,\cdots t_l$ 存在一个长度为 $l-k+1$ 或 $l-k$ 的子序列能够匹配 $s_{k+1},s_{k+2}\cdots s_{l+1}$ 或 $s_{k+1},s_{k+2}\cdots s_l$。

若 $\forall k\le m\lt l$，$b_{k} \;s_{k+1}\;t_{k+1}$ 不成立。

那么分两种情况，$s_{k+1}=s_{k+2}=\cdots s_{l}$。

那么 $b_{l}\; \hat{s_l}\;b_{l-1}\; \hat{s_{l}}\;t_{l}$，即 $b_{l} \;\hat{s_l}\; t_l$，于是 $s_{l+1},s_{l+2}\cdots s_{r}$ 中必存在一个前缀使得 $s_{l+1},s_{l+2},\cdots s_{d},l\lt d\le r$，且 $s_{k+1}=s_{k+2}=\cdots =s_{l}=s_{l+1}\cdots s_{d-1}=\hat{s_d}$，由传递性可知 $t_l\;s_{l}\;b_{l}\;s_{l+1}\; b_{l+1} \cdots s_{d-1}\;b_{d-1}$ 可以推出 $b_{d-1} \;\hat{s_{d-1}}\;t_{l}$ ，又 $\hat{s_{d-1}}=s_d$ 那么 $b_{d-1}\; s_d\; t_{l}$，于是存在一个以 $i$ 结尾的子序列可以匹配 $s$ 的前缀长度为 $d\gt l=f_i$ 矛盾！

否则存在相邻两项 $s_{d+1}=\hat{s_{d}},k\lt d\lt l$，那么 $b_{d-1}\;\hat{s_d}\; t_d$，$b_{d}\;\hat{s_d} \;b_{d-1}$，$t_{d+1}\;s_{d+1}\;b_{d}$，$t_{d}\;s_{d+1}\;t_{d+1}$，于是 $b_{d-1}\;\hat{s_{d}}\;t_{d}\;s_{d+1}\;t_{d+1}\;s_{d+1}\;b_{d}\;\hat{s_{d}}\;b_{d-1}$。

由 $s_{d+1}=\hat{s_d}$ 可知中间四个符号都相同，那么 $b_{d-1}\;s_{d-1}\; b_{d-1}$ 矛盾！

所以 $\exists k\le m\lt l$，使得 $b_{k}\;s_{k+1}\;t_{k+1}$。

那么此时把 $t_{m+1},t_{m+2}\cdots t_{l}$ 接到 $b_{0},b_{1}\cdots b_{m}$ 后面也是一组合法的解，此时 $x^{\prime}_{f_i},x^{\prime}_{f_i-1},\cdots x^{\prime}_0$ 的字典序更小，因为 $x_{m}$ 变小了而 $x_{m+1},\cdots x_{f_i}$ 均没变化。

与假设矛盾！

若存在 $0\le k\lt f_{i}$ 使得 $f_{x_k}\neq k$ ，那么这时令 $j=x_k,r=f_{j},l=r$，$j$ 达成最大匹配时子序列为 $b_0,b_1\cdots b_r$。

与上面同理，只有 $s_{k+1}=s_{k+2}\cdots =s_l$ 时会推出 $b_{r}=b_{l}\;\hat{s_{l}}\;t_{l}$，而 $b_r=t_k$ ，由 $s_{k+1}=s_{k+2}\cdots =s_l$ 得出 $b_r\; s_l\;t_l$，矛盾！

命题成立。

因此我们可以直接用树状数组维护 dp 值。

## Code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
constexpr int N=300010;
int b1[N],b2[N];
void upd(int *b,int x,int v){for(;x<N;x+=(x&(-x))) b[x]=max(b[x],v);}
int qry(int *b,int x){int ans=0;for(;x;x-=(x&(-x))) ans=max(ans,b[x]);return ans;}
char s[N];int n,a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);scanf("%s",s+1);int ans=0;
	for(int i=1;i<=n;++i){
		int f=max(qry(b1,a[i]-1),qry(b2,n-a[i]));ans=max(ans,f);
		if(s[f+1]=='U') upd(b1,a[i],f+1);else upd(b2,n-a[i]+1,f+1);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Elma_ (赞：9)

以下我们将 ```U``` 的极长连续段称为上升段， ```D``` 的极长连续段称为下降段。

很容易想到一个直观的贪心：即维护当前的子序列 $a$，每次找到最近的满足 $s$ 限制的位置。但很遗憾，这个做法甚至在 $s$ 全为 ```U``` 时都是错的。

但这也给了我们启示，虽然在 LIS 和 LDS 问题中我们不能使用贪心，但我们可以试着在上升段和下降段交换时使用这种贪心的方式。具体来说，假设 $s_j$ 为 ```D```，且接下来的 $x$ 个位置都是 ```U```。考虑能和 $s_1 \sim s_j$ 对应的所有 $p$ 的子序列 $a$，设其结尾位置 $a_j$ 的最小值为 $k$，我们找到在 $p_k \sim p_n$ 内长度为 $x+1$ 的，结尾位置最靠前的上升子序列 $b$，设 $b$ 的结尾位置为 $k'$。

显然，对于 $p$ 的能和 $s_1 \sim s_{j + x}$ 对应的子序列，其结尾位置一定 $\geq k'$。我们断言，根据序列 $a$ 和 $b$ 一定能够构造出一个子序列使得其和 $s_1 \sim s_{j + x}$ 对应，且结尾位置为 $k'$。

分类讨论：若 $a_j = b_0$，那就只需要把它们拼在一起就行了。否则，注意到此时一定有 $a_j > b_0$，否则我们可以把 $a_j$ 加在序列 $b$ 的开头，然后把 $b$ 的末尾元素删掉，这样能够得到一个结尾位置更靠前的长为 $x+1$ 的上升子序列。于是我们可以把 $a_j$ 删掉，然后将 $b$ 接在后面即可。

从 ```U``` 变为 ```D``` 时同理。也就是说，这种贪心在不同段落交换时都是成立的。

于是我们的算法可以按照如下流程进行：将 $s$ 划分成若干上升段和下降段，维护当前子序列的结尾位置 $t$，对于一个长为 $x$ 的段，我们试着找到在 $p_t \sim p_n$ 内长度为 $x+1$ 的，结尾位置最靠前的上升/下降子序列，若存在这样的子序列，设其结尾位置为 $t'$，我们将答案加上 $x$，然后令 $t \gets t'$，否则将答案加上后缀的 LIS 或 LDS 的长度，并结束计算。

容易通过树状数组优化 DP 来维护上述过程，时间复杂度 $\mathcal{O}(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3e5 + 5;
int n, ans, a[N], q[N], c, f[N];
struct BIT {
    int c[N];
    void clr(int x) {
        for (int i = x; i <= n; i += i & -i) c[i] = 0;
    }
    void mdf(int x, int v) {
        for (int i = x; i <= n; i += i & -i) c[i] = max(c[i], v);
    }
    int qry(int x) {
        int ret = 0;
        for (int i = x; i >= 1; i -= i & -i) ret = max(ret, c[i]);
        return ret;
    }
} t;
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    string s;
    cin >> s;
    q[++c] = 1;
    for (int i = 1; i < n - 1; i++) {
        if (s[i] == s[i - 1]) {
            q[c]++;
        } else {
            q[++c] = 1;
        }
    }
    bool _ = s[0] == 'U';
    int k = 1, j = 1;
    for (int i = 1; i <= c; i++, _ ^= 1) {
        if (j == n) 
            break;
        k = j;
        int x = q[i] + 1, val = 0;
        if (_) {
            f[j] = 1, t.mdf(a[j], 1);

            while (j < n && f[j] < x) {
                j++;
                f[j] = t.qry(a[j]) + 1, t.mdf(a[j], f[j]);
            }
            while (k <= j) {
                t.clr(a[k]), val = max(val, f[k]), k++;
            } 
        } else {
            f[j] = 1, t.mdf(n - a[j] + 1, 1);

            while (j < n && f[j] < x) {
                j++;
                f[j] = t.qry(n - a[j] + 1) + 1, t.mdf(n - a[j] + 1, f[j]);
            }
            while (k <= j) {
                t.clr(n - a[k] + 1), val = max(val, f[k]), k++;
            } 
        }
        if (j < n) {
            ans += q[i];
        } else {
            ans += val - 1;
        }
    }
    cout << ans << "\n";
    return 0;   
}

```


---

## 作者：vegetable_king (赞：3)

[可能更佳的阅读体验](https://yjh965.github.io/post/xie-dao/)

不需分析结论的麻烦做法，模拟赛时想到这个做法没写出来，跟同学说场上没写出这个题的时候同学大为震惊……

首先，可以想到设 $f'_{i, j}$ 为最后一个元素为 $i$，选了 $j + 1$ 个是否可行。转移方程即为

$$\begin{cases}
f'_{i, j} \gets f_{k, j - 1} \ (j = \texttt{"U"},a_i > a_k)\\
f'_{i, j} \gets f_{k, j - 1} \ (j = \texttt{"D"},a_i < a_k)\\
\end{cases}$$

这个转移显然可以用前缀或优化，我们设 $f_{i, j, k}$ 为 $\bigvee_{x \le i, a_x < k} f'_{x, j}$，类似的设 $g_{i, j, k}$ 为 $\bigvee_{x \le i, a_x > k} f'_{x, j}$。

首先可以滚掉第一维 $k$。即变为 $f_{j, k}, g_{j, k}$ 这样的形式；然后可以舍弃原数组。具体来说，$f'_{i, j}$ 就等于 $f_{j - 1, a_i}$ 或者 $g_{j - 1, a_i}$，所以可以对于 $k > a_i$ 的所有 $f_{j, k}$ 以及 $k < a_i$ 的所有 $g_{j, k}$ 更新过去，不需再用原数组。转移方程变为

$$\begin{cases}
f_{j, k} \gets f_{j - 1, a_i} \ (j = \texttt{"U"},k > a_i)\\
g_{j, k} \gets f_{j - 1, a_i} \ (j = \texttt{"U"},k < a_i)\\
f_{j, k} \gets g_{j - 1, a_i} \ (j = \texttt{"D"},k > a_i)\\
g_{j, k} \gets g_{j - 1, a_i} \ (j = \texttt{"D"},k < a_i)\\
\end{cases}$$

现在转移还是需要 $O(n)$，而且现在需要维护的状态是一个 $01$ 数组，这很不好。继续发现，因为 $f$ 前缀或的性质，所以对于每个 $j$，一定可以找到一个断点 $pf_j$（$1 \le pf_j \le n$） 满足对于所有 $k \le pf_j$ 的 $k$，都有 $f_{k, j} = 0$；对于所有 $k > pf_j$ 的 $k$，都有 $f_{k, j} = 1$。对于 $g$ 也可以类似的找到 $pg_j$。

我们只需要维护这些断点，就可以 $O(1)$ 找出对应的 $f$ 值和 $g$ 值。而且，我们还可以发现，对于一个有效转移（即转移过去的值为 $1$），就相当于给对应的断点取了一个 $\min / \max$。于是可以写出转移方程：

$$\begin{cases}
pf_j \overset{\min}{\gets} a_i, pg_j \overset{\max}{\gets} a_i \ (j = \texttt{"U"},pf_{j - 1} < a_i)\\
pf_j \overset{\min}{\gets} a_i, pg_j \overset{\max}{\gets} a_i \ (j = \texttt{"D"},pg_{j - 1} > a_i)\\
\end{cases}$$

现在时间复杂度被优化到了 $O(n^2)$，而需要维护的状态数已经变为了 $O(n)$ 级别，距离目标已经很近了。

我们猜测，$pf, pg$ 这两个断点序列都是单调的，但是很遗憾，这个结论是错误的。但是我们可以发现一个进阶结论：对于所有的 $b_j$ 相同的位置，$pf, pg$ 在这些位置上是单调的，也就是说，它们都是由两个单调序列拼起来的，因为在 $b$ 相同的情况下，相邻的两个位置的决策必然有一个包含另一个。

所以，能转移的 $j$ 一定是在一个前缀内且满足 $b_j$ 为某个字符的，而这个前缀也是可以快速求出的。

具体的，我们需要维护 $pf, pg$ 并支持以下操作：
- 对于一个前缀内 $b_j = ch$ 的 $j$ 令 $pf_j \overset{\min}{\gets} a_i, pg_j \overset{\max}{\gets} a_i$；
- 求出位置 $j$ 使得 $j$ 为最后一个满足 $b_{j + 1} = \texttt{"U"}$ 且 $pf_j < a_i$ 的位置；
- 求出位置 $j$ 使得 $j$ 为最后一个满足 $b_{j + 1} = \texttt{"D"}$ 且 $pg_j > a_i$ 的位置。

我们开一棵线段树，每一个节点中对于每一种二元组 $(b_j, b_{j + 1})$ 维护出区间内的 $\min pf_j, \max pg_j$ 以及标记，每次修改直接对于所有满足要求的二元组都对应的打上标记，而询问位置就在线段树上二分即可。

求答案比较简单，我们只需要倒着搜整棵线段树，找到第一个 $pf_j < n$ 或者 $pg_j > 1$ 的 $j$ 作为答案。总时间复杂度为 $O(n \log n)$，常数较大。

接下来是完整代码：

```cpp
#include <algorithm>
#include <cstring>
#include <cstdio>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 300001;
int n, a[N], ci[N];char b[N];
struct node{int pf[4], pg[4], cz[4], tg[4];}tr[N << 2];
inline void tmin(int& x, int y){if (x == -1) x = y;else x = min(x, y);}
inline void tmax(int& x, int y){x = max(x, y);}
inline void addtag(int u, int z, int x){if (x == -1) return;
	if (z == 0) tmin(tr[u].pf[0], x), tmin(tr[u].pf[2], x), tmin(tr[u].tg[0], x);
	if (z == 1) tmax(tr[u].pg[0], x), tmax(tr[u].pg[2], x), tmax(tr[u].tg[1], x);
	if (z == 2) tmin(tr[u].pf[1], x), tmin(tr[u].pf[3], x), tmin(tr[u].tg[2], x);
	if (z == 3) tmax(tr[u].pg[1], x), tmax(tr[u].pg[3], x), tmax(tr[u].tg[3], x);
}
inline void downtag(int u){for (int i = 0;i < 4;i ++)
	addtag(u << 1, i, tr[u].tg[i]), addtag(u << 1 | 1, i, tr[u].tg[i]), tr[u].tg[i] = -1;
}
inline void pushup(int u){
	for (int i = 0;i < 4;i ++){tr[u].pf[i] = n, tr[u].pg[i] = 0;
		if (tr[u << 1].cz[i]) tmin(tr[u].pf[i], tr[u << 1].pf[i]), tmax(tr[u].pg[i], tr[u << 1].pg[i]);
		if (tr[u << 1 | 1].cz[i]) tmin(tr[u].pf[i], tr[u << 1 | 1].pf[i]), tmax(tr[u].pg[i], tr[u << 1 | 1].pg[i]);
	}
}
void build(int u, int l, int r){memset(tr[u].tg, -1, 16);
	if (l == r){ci[l] = (b[l + 1] == 'D') << 1 | b[l] == 'D';
		memset(tr[u].pf, 0x3f, 16), memset(tr[u].pg, 0, 16);
		tr[u].pf[ci[l]] = n, tr[u].pg[ci[l]] = tr[u].cz[ci[l]] = 1;return;
	}int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r), pushup(u);
	for (int i = 0;i < 4;i ++) tr[u].cz[i] = tr[u << 1].cz[i] | tr[u << 1 | 1].cz[i];
}
void update(int u, int l, int r, int p, int z, int x){
	if (r <= p) return addtag(u, z << 1, x), addtag(u, z << 1 | 1, x);
	if (l > p) return;int mid = l + r >> 1;downtag(u);
	update(u << 1, l, mid, p, z, x), update(u << 1 | 1, mid + 1, r, p, z, x), pushup(u);
}
inline int gtf(int u){int res = inf;if (tr[u].cz[0]) tmin(res, tr[u].pf[0]);if (tr[u].cz[1]) tmin(res, tr[u].pf[1]);return res;}
inline int gtg(int u){int res = 0;if (tr[u].cz[2]) tmax(res, tr[u].pg[2]);if (tr[u].cz[3]) tmax(res, tr[u].pg[3]);return res;}
int fndpos(int u, int l, int r, int x){
	if (l == r) return x > gtf(u) ? l : -1;int mid = l + r >> 1;downtag(u);
	if (gtf(u << 1 | 1) < x) return fndpos(u << 1 | 1, mid + 1, r, x);
	return fndpos(u << 1, l, mid, x);
}
int gndpos(int u, int l, int r, int x){
	if (l == r) return x < gtg(u) ? l : -1;int mid = l + r >> 1;downtag(u);
	if (gtg(u << 1 | 1) > x) return gndpos(u << 1 | 1, mid + 1, r, x);
	return gndpos(u << 1, l, mid, x);
}
int solve(int u, int l, int r){
	if (l == r) return tr[u].pf[ci[l]] < n || tr[u].pg[ci[l]] > 1 ? l : 0;
	int mid = l + r >> 1;downtag(u);
	return max(solve(u << 1, l, mid), solve(u << 1 | 1, mid + 1, r));
}
int main(){scanf("%d", &n);
	for (int i = 1;i <= n;i ++) scanf("%d", &a[i]);
	scanf("%s", b + 1), build(1, 0, n - 1);
	for (int i = 1, p0, p1;i <= n;i ++){
		p0 = fndpos(1, 0, n - 1, a[i]), p1 = gndpos(1, 0, n - 1, a[i]);
		update(1, 0, n - 1, p0 + 1, 0, a[i]);
		update(1, 0, n - 1, p1 + 1, 1, a[i]);
	}printf("%d", solve(1, 0, n - 1));
}
```

---

## 作者：Leasier (赞：2)

首先有一个简单的暴力：

- 设 $dp_{i, j}$ 表示考虑到 $i$，在 $[1, i]$ 中选了 $j$ 个数放进子序列是否可行。
- 暴力转移是 $O(n^3)$ 的，BIT 优化即可做到常数极小的 $O(n^2 \log n)$。

但是这个做法看上去没啥前途 /ng

~~至少我模拟赛时想了 40min 还是不会做（~~

但是注意到把 bool 作为状态值往往是浪费的，考虑把 $j$ 扔到状态值上去。

但是直接取 $\max$ 显然是不可取的，因为下一位是 `U` 还是 `D` 的影响不容忽视。

于是我们直接设 $f_i$ 表示考虑到 $i$，在 $[1, i]$ 中选了 $j + 1$ 个数放进子序列是否可行，满足 $s_{j + 1} = $ `U` 且尽可能大；$g_i$ 类似。

转移时讨论一下 $s_{f_i + 2}, s_{g_i + 2}$，并用 BIT 优化即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int lowbit(int x){
	return x & (-x);
}

typedef struct {
	int tree[300007];
	
	inline int get_max(int x){
		int ans = 0;
		while (x > 0){
			ans = max(ans, tree[x]);
			x -= lowbit(x);
		}
		return ans;
	}
	
	inline void update(int n, int x, int k){
		while (x <= n){
			tree[x] = max(tree[x], k);
			x += lowbit(x);
		}
	}
} BIT;

BIT bit1, bit2, bit3, bit4;
int p[300007], dp1[300007], dp2[300007];
char s[300007];

int main(){
	int n, ni, ans = 0;
	scanf("%d", &n);
	ni = n - 1;
	for (register int i = 1; i <= n; i++){
		scanf("%d", &p[i]);
	}
	scanf("%s", &s[1]);
	for (register int i = 1; i <= n; i++){
		dp1[i] = max(bit1.get_max(p[i] - 1), bit2.get_max(n - p[i]));
		if (dp1[i] == 0 && s[1] == 'D'){
			dp1[i] = -1;
		} else if (dp1[i] < ni){
			if (s[dp1[i] + 2] == 'U'){
				bit1.update(n, p[i], dp1[i] + 1);
			} else {
				bit3.update(n, p[i], dp1[i] + 1);
			}
		}
		dp2[i] = max(bit3.get_max(p[i] - 1), bit4.get_max(n - p[i]));
		if (dp2[i] == 0 && s[1] == 'U'){
			dp2[i] = -1;
		} else if (dp2[i] < ni){
			if (s[dp2[i] + 2] == 'U'){
				bit2.update(n, n - p[i] + 1, dp2[i] + 1);
			} else {
				bit4.update(n, n - p[i] + 1, dp2[i] + 1);
			}
		}
		ans = max(ans, max(dp1[i], dp2[i]));
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

基础的贪心：对于每个位置，我们希望它尽量往后匹配。

显然这是错的。比如一个位置的值如果是 $n$，如果能匹配到一个比较靠后的长度，但是下一个字符是 `U` 那么肯定是不可能的。

所以又有了一个朴素的想法——对于每个位置，记录使得下一个位置是 `U` 和 `D` 的最长位置。只在这些有用的位置间转移即可做到 $O(n \log n)$。

考场就这么写吧，能过：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,p[MAXN],ans,bt[3][MAXN];
string S;
void update(int pos,int op,int v) {
	if(op==2) pos=n-pos+1;
	while(pos<=n) bt[op][pos]=max(bt[op][pos],v),pos+=pos&-pos;
	return ;
}
int query(int pos,int op) {
	int ans=0;
	if(op==2) pos=n-pos+1;
	while(pos) ans=max(ans,bt[op][pos]),pos-=pos&-pos;
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>p[i];
	cin>>S,S="&"+S;
	map<char,int> t;
	t['U']=1,t['D']=2;
	ffor(i,1,n) {
		ans=max(ans,0);
		int p1=query(p[i],1);
		int p2=query(p[i],2);
		if(p1) ans=max(ans,p1),p1++;
		if(p2) ans=max(ans,p2),p2++;
		if(p1<n) update(p[i],t[S[p1]],p1);
		if(p2<n) update(p[i],t[S[p2]],p2);	
		update(p[i],t[S[1]],1);
	}
	cout<<ans;
	return 0;
}
```

我们只需要证明：最优解都可以被这样选出来。

取最后一个数最靠前的最优解。设他的答案是 $k$。显然它有一个前驱答案是 $k-1$，且这个 $k-1$ 是满足下一个位置为 `U` 或 `D` 的最大值。

考虑这个前驱的前驱。如果这个新的前驱答案为 $\le k-2$ 即证。否则，新前驱的答案为 $k-1$。（设最后一个数是 $lst$，前驱是 $p$，前驱的前驱是 $pp$）我们担心这时 $p$ 就不能通过 $pp$ 转移而来。

这种情况只会发生在 $a_{pp} > a_{lst} > a_p$ 或者恰好相反的情况下（否则，能从 $lst$ 直接跳到 $pp$ 而且答案不变）。我们就考虑这种情况吧。

显然第 $k$ 位要求的是 `U`。我们需要从 $k-1$ 位转移到 $p$，这一位要求是 `D`。

这两位恰好不一样，所以对于 $lst$ 来说恰好会把他们当成关键点找出来。

即证。

---

