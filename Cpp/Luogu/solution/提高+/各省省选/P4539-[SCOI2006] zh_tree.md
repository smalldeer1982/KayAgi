# [SCOI2006] zh_tree

## 题目描述

张老师根据自己工作的需要，设计了一种特殊的二叉搜索树。

他把这种二叉树起名为 zh_tree，对于具有 $n$ 个结点的 zh_tree，其中序遍历恰好为 $(1,2,3,\cdots,n)$，其中数字 $1,2,3,\cdots,n$ 是每个结点的编号。$n$ 个结点恰好对应于一组学术论文中出现的n个不同的单词。

第j个单词在该组论文中出现的次数记为 $d_j$，例如，$d_2=10$表示第 $2$ 个结点所对应的单词在该组论文中出现了10次。设该组论文中出现的单词总数为 S，显然，$S=d_1+d_2+…+d_n$。记 $f_j=\frac{d_j}{S}$ 为第 j 个单词在该组论文中出现的概率（频率）。 

张老师把根结点深度规定为0，如果第 $j$ 个结点的深度为 $r$，则访问该结点的代价 $h_j$ 为 $h_j=k(r+1)+c$，其中 $k$，$c$ 为已知的不超过 $100$ 的正常数。

则zh_tree是满足以下条件的一棵二叉树：它使 $h_1f_1+h_2f_2+…+h_nf_n$ 达到最小。

我们称上式为访问 zh_tree 的平均代价。 请你根据已知数据为张老师设计一棵 zh_tree。

## 样例 #1

### 输入

```
4 2 3.5
20 30 50 20```

### 输出

```
7.000```

# 题解

## 作者：mqxmm (赞：11)

## $\texttt{Solution}$

对于每个节点的深度 $r_i$，由于 $h_i = k(r_i + 1) + c$，不妨可以把根节点的深度改为 $1$，这样就可以直接用 **现在的 $r_i$** 表示 **原来的 $r_i + 1$** 了。  

先把 $\sum\limits_{i = 1}^n h_i f_i$ 化简：  
$$
\begin{aligned}
\sum\limits_{i = 1}^n (h_i \times f_i) & =
\sum\limits_{i = 1}^n (k \times r_i + c) \times \dfrac {d_i} S \\
& = \dfrac 1 S \times \sum\limits_{i = 1} ^{n} (k \times r_i + c) \times d_i \\
& = \dfrac 1 S \times \sum\limits_{i = 1}^n (k \times r_i \times d_i + c \times d_i) \\
& = \dfrac 1 S \times (\sum\limits_{i = 1}^n k \times r_i \times d_i + \sum\limits_{i = 1}^n c \times d_i) \\
& = (\dfrac 1 S \times \sum\limits_{i = 1}^n k \times r_i \times d_i) + (\dfrac 1 S \times c \times \sum\limits_{i = 1} ^{n} d_i) \\
& = (\dfrac k S \times \sum\limits_{i = 1}^n r_i \times d_i) + (\dfrac 1 S \times c \times S) \\
& = \dfrac {k \times \sum\limits_{i = 1}^n r_i \times d_i}{S} + c \\
\end{aligned}
$$

题目要我们求 $\sum\limits_{i = 1}^n h_i f_i$ 的最小值，就可以转化成求 $\sum\limits_{i = 1}^n r_i \times d_i$ 的最小值。  

- 状态定义：设 $f_{L, R}$ 表示：一棵二叉树的 **中序遍历(左子树，根节点，右子树)** 为 $L \sim R(L, L + 1, L + 2, \cdots, R)$ 时 $\sum\limits_{i = L}^R r_i \times d_i$ 的最小值，最终的答案就是 $\dfrac{k \times f_{1, n}}{S} + c$。  
- 初始化：$\forall L = R = i, f_{L, R} = d_i$；$\forall L < R, f_{L, R} = + \infty$。  
- 状态转移：对于中序遍历为 $L \sim R$ 的二叉树，枚举其根节点 $tr(L \leq tr \leq R)$，$f_{L, R} = \min\limits_{tr = L}^R \{ f_{L, tr - 1} + f_{tr + 1, R} + \sum\limits_{i = L}^{R} d_i \} = \min\limits_{tr = L}^R \{ f_{L, tr - 1} + f_{tr + 1, R} \} + \sum\limits_{i = L}^{R} d_i$。  

如果需要输出方案，可以在转移过程中记录下 $f_{L, R}$ 取最小值时的根节点，最后递归即可。  

转移时 $\sum\limits_{i = L}^{R} d_i$ 可以用前缀和作差，这样时间复杂度 $O(n ^ 4) \to O(n ^ 3)$，不过都可以 $\texttt{AC}$。

## $\texttt{code}$

```cpp
#include <cstdio>
#include <cstring>

#define Min(u, v) (((u) < (v)) ? (u) : (v))

const int MAX_n = 30;

int n, S;
int d[MAX_n + 5];
int zh[MAX_n + 5];

double k, c;
double dp[MAX_n + 5][MAX_n + 5];

int main()
{
	scanf("%d %lf %lf", &n, &k, &c);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
		zh[i] = (S += d[i]);
		dp[i][i] = 1.0 * d[i];
	}
	for (int L = 1; L + 1 <= n; L++)
		for (int R = L + 1; R <= n; R++)
			dp[L][R] = 1000000000.0;
	for (int Len = 2; Len <= n; Len++)
	{
		for (int L = 1, R = Len; R <= n; L++, R++)
		{
			for (int tr = L; tr <= R; tr++)
				dp[L][R] = Min(dp[L][R], dp[L][tr - 1] + dp[tr + 1][R]);
			dp[L][R] += 1.0 * (zh[R] - zh[L - 1]);
		}
	}
	printf("%.3lf\n", 1.0 * k * dp[1][n] / S + c);
	return 0;
}

```


---

## 作者：糪眾脦颰罷 (赞：3)

## 记搜
发现 $n\le 30$，小得一匹，**直接大力记搜就好了**。

对于一个区间$[L,R]$，我们枚举一个断电$i,i\in [L,R]$，分成$[L,i-1]$和$[i+1,R]$两部分，在分别记搜。

复杂度：$O(n^4)$（~~管它呢，只要简单粗暴能过就行了~~）

代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int n,d[10010],S;
double k,c,f[10010],dp[101][101][101],tot[10001];
double DFS(int L,int R,int h){
	if(dp[L][R][h]!=2e9+7)return dp[L][R][h];
	for(int i=L;i<=R;i++){
		double res=f[i]*(k*1.0*h+c);
		if(L<=i-1)res+=DFS(L,i-1,h+1);
		if(i+1<=R)res+=DFS(i+1,R,h+1);
		dp[L][R][h]=min(dp[L][R][h],res);
	}
	return dp[L][R][h];
}
int main(){
	for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)for(int k=0;k<=100;k++)dp[i][j][k]=2e9+7;
	scanf("%d %lf %lf",&n,&k,&c);
	for(int i=1;i<=n;i++)scanf("%d",&d[i]),S+=d[i];
	for(int i=1;i<=n;i++)f[i]=d[i]*1.0/S;
	printf("%.3lf",DFS(1,n,1));
	return 0;
}
```

---

## 作者：一扶苏一 (赞：3)


## Solution

其实就是推式子啦……

$$\begin{aligned}ans~& =~\min~\{~\sum_{i = 1}^{n} h_i~\times~f_i\}\\& =~\min~\{\sum_{i = 1}^n~h_i~\times~\frac{d_i}{S}\}\\& =~\min~\{\frac{1}{S}~\times~sum_{i = 1}^n~h_i~\times~d_i\}\\& =~\min~\{\frac{1}{S}~\times~\sum_{i = 1}^n~[k~(r_i~+~1)~c]~\times~d_i\\& =~\min~\{\frac{1}{S}~\times~\sum_{i = 1}^n~[k~(r_i~+~1)~d_i]~+~\sum_{i = 1}^n d_i~\times~c\}\\& =~\min~\{\frac{1}{S}~\times~k~\sum_{i = 1}^n~[(r_i~+~1)~d_i]~+~S~\times~c\}\\\end{aligned}$$

然后我们发现 $S~=~\sum_{i = 1}^n d_i$ 是个常数，$c$ 也是一个常数，我们将只与这两个值有关的项从 $\min$ 中提出来

$$\begin{aligned}ans~& =~\frac{1}{S}~+~S~\times~c~+~\min\{k~\sum_{i = 1}^n~(r_i~+~1)~d_i\}\\& =~\frac{1}{S}~+~S~\times~c~+~k~\times~\min\{\sum_{i = 1}^n~(r_i~+~1)~d_i\}\end{aligned}$$

于是我们发现我们事实上要最小化 $\sum_{i = 1}^n~(r_i~+~1)~d_i$，同时满足在这棵树上的中序遍历是 $1~\sim~n$

由于中序遍历的顺序是“左中右”，所以我们可以直接设 $f_{l,r}$ 为区间 $[l,r]$ 的中序遍历为 $l~\sim~r$ 时上式的最小值，转移时可以枚举一个点 $i$ 作为根，则左右子树显然要从上式最小的树形转移过来。转移时等价于左右子树每个点的树高都增加 $1$，即对答案的贡献增加 $\sum_{j = l}^{i - 1} d_j~+~\sum_{j = i + 1}^{r} d_j$。然后加上根的贡献 $d_i$，所以增加的贡献即为 $\sum_{j = l}^r d_j$。直接使用前缀和优化该式子即可。

最后计算答案时记得将常数项乘上。复杂度 $O(n^3)$。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 35;

int n;
double c, k;
double MU[maxn], frog[maxn][maxn], sum[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n); ReadDb(k); ReadDb(c);
	memset(frog, 127, sizeof frog);
	for (rg int i = 1; i <= n; ++i) {
		ReadDb(sum[i]);
		frog[i][i] = sum[i]; frog[i + 1][i] = 0;
		sum[i] += sum[i - 1];
	}
	frog[1][0] = 0;
	for (rg int len = 1; len < n; ++len) {
		for (rg int l = 1; l < n; ++l) {
			int r = l + len;
			if (r > n) break;
			for (rg int i = l; i <= r; ++i) frog[l][r] = std::min(frog[l][r], frog[l][i - 1] + frog[i + 1][r]);
			frog[l][r] += sum[r] - sum[l - 1];
		}
	}
	printf("%.3lf\n", (k * frog[1][n] + sum[n] * c) / sum[n]);
}
```

## Summary

二叉树的中序遍历是 **左中右** 不是 **中左右**！

---

## 作者：Cyhlnj (赞：1)

区间 $DP$ 入门题。。。

~~非常的傻啊~~

首先并不要输出方案。。。

设 $f[l][r]$ 表示将 $l,r$ 之间的建成一棵子树的最小代价

每次枚举一个根转移，子树的 $deep$ 全部加 $1$，算上贡献就好了

~~想怎么写怎么写~~

最后除个 $s$ 就好了

复杂度 $\Theta(n^3)$

$n< 30$ 是什么鬼。。。

```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
double k, c, d[35], s, f[35][35], sum[35][35];

int main() {
	freopen("a.in", "r", stdin);
	ios :: sync_with_stdio(false);
	cin >> n >> k >> c;
	for (int i = 1; i <= n; ++i) cin >> d[i], s += d[i];
	memset(f, 127, sizeof(f));
	for (int i = 1; i <= n; ++i) f[i][i] = (k + c) * d[i];
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j) sum[i][j] = sum[i][j - 1] + k * d[j];
	for (int len = 2; len <= n; ++len)
		for (int l = 1; l + len - 1 <= n; ++l) {
			int r = l + len - 1;
			f[l][r] = min(f[l][r - 1] + c * d[r], f[l + 1][r] + c * d[l]);
			for (int m = l + 1; m < r; ++m)
				f[l][r] = min(f[l][r], f[l][m - 1] + f[m + 1][r] + c * d[m]);
			f[l][r] += sum[l][r];
		}
	printf("%.3lf\n", f[1][n] / s);
    return 0;
}


```

---

## 作者：mydcwfy (赞：0)

一个区间 DP 的较为简单的题目。

## 1. 题意

- 要求构造一个大小为 $n$ 的二叉树，按照中序遍历标号为 $1\sim n$，然后给定每个编号的频率 $f_i$，并且给定常数 $k,c$ 为实数，请最小化（设根节点深度为 1）：

$$
\sum_{i=1}^nf_i\times(k\times dep_i+c)
$$

- $n\leq30,\sum f_i=1,0<k,c\leq100$

## 2. 思路

其实可能很多同学~~（其实就是我）~~都会想到 `Huffman Tree`，它是基于一个贪心的想法，但是我们可以比较一下两个的式子。
$$
\sum_{i=1}^nf_i\times dep_i
$$

$$
\sum_{i=1}f_i\times(k\times dep_i+c)
$$

这两个其实是有一定区别的。

本题中，不同节点是一定会出现祖先关系，并且只有 $n$ 个节点。但是 `Huffman Tree` 却要求给定的 $n$ 个节点不能出现祖先关系，构造出来后，也会超过 $n$ 个节点。

那本题怎么做呢？

首先，我们可以发现一个性质：假设当前子树覆盖的区间为 $[l,r]$，根节点为 $t$，那么左边的子树覆盖的区间为 $[l,t-1]$，右边的子树为 $[t+1,r]$。

这就是一个典型的区间 DP 了。

当我们要计算 $dp(l,r)$ 的时候，我们直接枚举根节点 $t$，然后递归计算 $dp(l,t-1)$ 和 $dp(t+1,r)$，然后我们将左右子树直接接在 $t$ 这个节点上。

怎么计算贡献呢？其实很简单，我们左右的子树的深度都要加一，对于整个的贡献就是 $k\times (s(r)-s(l-1)-f(t))$，其中 $s(i)=\sum_{j=1}^if(j)$。

再加上 $t$ 的贡献，那么，我们就可以得到式子：
$$
dp(l,r)=\min_{t\in[l,r]}\{dp(l,t-1)+dp(t+1,r)+k\times(s(r)-s(l-1))+c\times f(t) \}
$$

时间复杂度为 $O(n^3)$，轻松通过。

## 3. 代码

采用的递归式写法。

```cpp
double solve(int l, int r)
{
	if (l > r) return 0;
	if (l == r) return (k + c) * fru[l];
	double &v = f[l][r];
	if (v >= 0) return v;
	v = INF;
	for (int mid = l; mid <= r; ++ mid)
		v = min(v, solve(l, mid - 1) + k * (s[r] - s[l - 1]) + c * fru[mid] + solve(mid + 1, r));
	return v;
}
```

---

