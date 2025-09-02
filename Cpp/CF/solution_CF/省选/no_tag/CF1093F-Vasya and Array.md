# Vasya and Array

## 题目描述

Vasya 有一个由 $n$ 个整数构成的数组，以及两个整数 $k$ 和 $len$。数组中的所有数字要么在 $1$ 到 $k$（包含 $k$）之间，要么等于 $-1$。如果数组中不存在长度为 $len$ 的连续相同数字的区间，则称该数组是好的。

Vasya 将把每个 $-1$ 替换为 $1$ 到 $k$（包含 $k$）之间的某个数字，使得最终得到的数组是好的。请你告诉他有多少种替换方式。由于答案可能很大，请输出对 $998244353$ 取模后的结果。

## 说明/提示

第一个测试点的可能答案：

1. $[1, 2, 1, 1, 2]$；
2. $[1, 2, 1, 2, 2]$。

第二个测试点没有合法方案，因为前两个元素相同。

第三个测试点的答案太多，这里不再一一列举。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2 3
1 -1 1 -1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 3 2
1 1 -1 -1 -1 -1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 42 7
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1
```

### 输出

```
645711643
```

# 题解

## 作者：duyi (赞：14)

洛谷上的 latex 版本较低。更好的阅读体验请前往[我的博客](https://www.cnblogs.com/dysyn1314/p/14022343.html)

更好的做法，值得[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/14022343.html)！！！！！！！

# CF1093F Vasya and Array 更优秀的做法

## 摘要

> 本题有一个经典的 DP + 容斥做法，时间复杂度是 $O(nk)$。
>
> 本文作者在此基础上，创新性地发掘题目性质，简化 DP 状态，利用数据结构优化 DP，提出了一个时间复杂度 $O(n)$ 的做法。显然相比经典做法，是更加优秀的。
>
> 本文将分别介绍这两种做法。

## 题目大意

[题目链接](https://codeforces.com/contest/1093/problem/F)

给出一段长度为 $n$ 的整数序列，一个正整数 $k$ ，一个正整数 $\text{len}$。序列中的所有数要么在 $[1,k]$ 之间，要么等于 $-1$。

我们称一个序列是好的，当且仅当不存在 $\text{len}$ 个连续的相同的数字。

你可以将每个 $-1$，替换成任意一个 $[1,k]$ 之间的整数。求有多少种方案，使得最终序列是好的。答案对 $998244353$ 取模。

数据范围：$1\leq n\leq 10^5$，$1\leq k\leq 100$，$1\leq \text{len}\leq n$。

## 经典做法

设 $\text{dp}_0(i,j)$ 表示考虑了前 $i$ 个位置，最后一个位置上填的数是 $j$，前 $i$ 个位置组成的序列合法的方案数。设 $\text{sdp}(i)=\sum_{j=1}^{k}\text{dp}_0(i,j)$。

首先，当 $a_i\neq -1$ 且 $a_i\neq j$ 时，$\text{dp}_0(i,j)=0$。

否则，我们暂时令 $\text{dp}_0(i,j)=\text{sdp}(i - 1)$。但是这会把一些不合法的方案算进去。具体来说，这样有可能出现 $[a_{i-\text{len}+1}\dots a_i]$ 全部相同的情况。这种情况会出现当且仅当如下两个条件都满足：

- $i\geq \text{len}$。
- $[a_{i-\text{len}+1}\dots a_i]$ 中每个数都等于 $-1$ 或 $j$。

所以，我们还要减去这种情况的数量：$\text{sdp}(i-\text{len})-\text{dp}_0(i-\text{len},j)$。其中 $\text{sdp}(i - \text{len})$ 表示 $[a_{i-\text{len}+1}\dots a_i]$ 全部等于 $j$ 时，前 $i - \text{len}$ 位的填写方案。不过这些方案中，有一些方案可能在前 $i-1$ 位就已经导致不合法了。这些提前不合法的方案本来就没有被算在 $\text{sdp}(i-1)$ 中，所以不需要被减去，它们的数量是 $\text{dp}_0(i - \text{len},j)$。

综上所述，可以得到转移式：
$$
\text{dp}_0(i,j)=\begin{cases}
0&& a_i\neq0\text{ 且 }a_i\neq j\\
\text{sdp}(i-1)-(\text{sdp}(i-\text{len})-\text{dp}_0(i-\text{len},j))\cdot [\text{上文中两个条件}]&&\text{otherwise}
\end{cases}
$$
时间复杂度$O(nk)$。

## 更优秀的做法

首先，当 $\text{len} = 1$ 时，答案一定是 $0$。以下只讨论 $\text{len} > 1$ 的情况。

先考虑一种朴素的 DP。设 $\text{dp}_1(i,j,l)$ 表示考虑了前 $i$ 个位置，第 $i$ 位上填的数是 $j$，最后一个 $\neq j$ 的位置是 $l$，此时使得前 $i$ 位组成的序列合法的方案数。

转移时，考虑当前位填了什么：
$$
\begin{cases}
\text{dp}_1(i-1,j,l)\to \text{dp}_1(i,j, l) && \text{if }l\geq i - \text{len}+1\\
\text{dp}_1(i-1,j,l)\to \text{dp}_1(i,x, i) && \text{if }x\neq j
\end{cases}
$$

初始状态为 $\text{dp}_1(0,0,0) = 1$。答案是 $\sum_{j = 1}^{k}\sum_{l = n - \text{len}+1}^{n - 1}\text{dp}_1(n,j,l)$。

这个朴素 DP 的时间复杂度是 $O(n^2k)$。

---

优化它！设上一位填的数为 $j$，当前位填的数为 $x$。我们发现，当 $x$ 和 $j$ 不同时，$x$ 的值具体是什么其实不重要：对所有 $x\neq j$，它们的转移是一模一样的。这就给了我们简化的空间。

定义 $a_{n+1} = k+1$。定义 $\text{nxt}_i$ 表示位置 $i$ 后面第一个 $a_{i'}\neq -1 $ 的位置 $i'$。设 $\text{dp}_2(i,j\in\{0,1\},l)$ 表示考虑了前 $i$ 个位置，第 $i$ 位上填的数是 / 否等于 $a_{\text{nxt}_i}$，前 $i$ 位里最后一个填的数与第 $i$ 位上不同的位置是 $l$，此时使得前 $i$ 位组成的序列合法的方案数。

转移分 $a_i$ 是否为 $-1$ 两种情况。

当 $a_i\neq -1$ 时，枚举 $l$。则有如下转移：
$$
\begin{cases}
\text{dp}_2(i-1,0,l)\to \text{dp}_2(i,[a_i=a_{\text{nxt}_i}],i - 1)\\
\text{dp}_2(i-1,1,l)\to \text{dp}_2(i,[a_i=a_{\text{nxt}_i}],l) && \text{if }l\geq i - \text{len} + 1
\end{cases}
$$
当 $a_i = -1$ 时，显然 $\text{nxt}_{i} =\text{nxt}_{i-1}$。枚举 $l$。我们分别考虑如下情况：

- 第 $i-1$ 位填的数与 $a_{\text{nxt}_{i}}$ 不同：
  - 第 $i$ 位上填的数与第 $i-1$ 位上填的数相同。
  - 第 $i$ 位上填的数与第 $a_{\text{nxt}_i}$ 相同。
  - 第 $i$ 位上填的数，既不等于第 $i-1$ 位上填的数，也不等于 $a_{\text{nxt}_{i}}$。
- 第 $i-1$ 位填的数与 $a_{\text{nxt}_{i}}$ 相同：
  - 第 $i$ 位填的数与 $a_{\text{nxt}_{i}}$ 不同。
  - 第 $i$ 位填的数与 $a_{\text{nxt}_{i}}$ 相同。

这五种情况分别对应如下转移：
$$
\begin{cases}
\text{dp}_2(i - 1, 0, l)&\to \text{dp}_2(i, 0, l)&&\text{if }l\geq i - \text{len} + 1\\
\text{dp}_2(i - 1, 0, l)&\to\text{dp}_2(i, 1, i - 1)\\
\text{dp}_2(i - 1, 0, l)\times(k - 2) & \to\text{dp}_2(i,0,i-1)\\
\text{dp}_2(i - 1, 1, l)\times(k - 1) &\to \text{dp}_2(i, 0, i - 1)\\
\text{dp}_2(i - 1, 1, l)&\to\text{dp}_2(i,1,l) && \text{if }l\geq i - \text{len} + 1
\end{cases}
$$
上述式子里默认 $1 < i < \text{nxt}_i \leq n$。当 $i = 1$ 或 $\text{nxt}_i = n+1$ 时，有一些特殊情况要考虑。为了表述简洁，这里就不细写了。

现在，这个 DP 的时间复杂度是 $O(n^2)$。虽然无法 AC，但这是迈向 $O(n)$ 做法的关键一步。我将这一 DP 的代码附在了本文末尾：<a href="#bruteforcedp">点击跳转</a>。

---

在这个 DP 里，第 $1$ 维的枚举不可避免，第 $2$ 维的状态数已经被我们优化到 $O(1)$。考虑优化第 $3$ 维。

观察转移式，发现从 $i-1$ 变成 $i$ 时，第 $3$ 维的转移，相当于做如下操作：

1. 区间求和。对所有 $l\in[i - \text{len},i - 2]$ 求和。
2. 单点加。
3. 把一段区间的值覆盖为 $0$。
4. 在 $a_i\neq -1$ 且 $a_i\neq a_{\text{nxt}_i}$ 时，需要把 $\text{dp}_2(i,1)$ 中的一段 $l$，复制到 $\text{dp}_2(i,0)$ 对应的位置上。

按第二维的 $0,1$，维护两棵线段树，通过打懒标记即可实现这四种操作。

时间复杂度 $O(n\log n)$。

---

继续优化，发现区间操作都是假的。

- 操作 $3$ 要么是单点清空，要么是全局清空。
- 操作 $1$ 和操作 $4$，因为其他位置都清空了，所以区间求和、区间复制，其实就是全局求和、全局交换。

所以我们只需要用两个数组来维护。

时间复杂度 $O(n)$。

## 参考代码

前往[我的博客](https://www.cnblogs.com/dysyn1314/p/14022343.html)查看效果更佳。

### 最终代码

友情提醒：使用读入、输出优化可以使代码更快，详见本博客公告。

```cpp
// problem: CF1093F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;
const int MOD = 998244353;
inline int mod1(int x) { return x < MOD ? x : x - MOD; }
inline int mod2(int x) { return x < 0 ? x + MOD : x; }
inline void add(int &x, int y) { x = mod1(x + y); }
inline void sub(int &x, int y) { x = mod2(x - y); }


int n, K, len, a[MAXN + 5];

struct FantasticDataStructure {
	int sum;
	int arr[MAXN + 5];
	int TIM;
	int tim[MAXN + 5];
	void upd(int p) {
		if (tim[p] < TIM) {
			tim[p] = TIM;
			arr[p] = 0;
		}
	}
	void point_add(int p, int v) {
		upd(p);
		add(arr[p], v);
		add(sum, v);
	}
	void point_set0(int p) {
		upd(p);
		sub(sum, arr[p]);
		arr[p] = 0;
	}
	void global_set0() {
		TIM++;
		sum = 0;
	}
	int query() {
		return sum;
	}
	FantasticDataStructure() {}
};
FantasticDataStructure S[2];
int id[2];

// DP 转移: a[i] != -1 / a[i] == -1
void trans1(int p, int nxtval) {
	int v = S[id[0]].query();
	if (a[p] == nxtval) {
		S[id[0]].global_set0();
		if (p - len >= 0) {
			S[id[1]].point_set0(p - len);
		}
		S[id[1]].point_add(p - 1, v);
	} else {
		swap(id[0], id[1]);
		S[id[1]].global_set0();
		if (p - len >= 0) {
			S[id[0]].point_set0(p - len);
		}
		S[id[0]].point_add(p - 1, v);
	}
}
void trans2(int p, int flag) {
	int v0 = S[id[0]].query();
	int v1 = S[id[1]].query();
	
	if (p == 1) {
		S[id[0]].global_set0();
	} else {
		if (p - len >= 0) {
			S[id[0]].point_set0(p - len);
		}
	}
	
	int toadd = 0;
	if (flag + (p != 1) + 1 <= K) {
		toadd = (ll)v0 * (K - flag - (p != 1)) % MOD;
	}
	add(toadd, (ll)v1 * (K - 1) % MOD);
	S[id[0]].point_add(p - 1, toadd);
	
	if (p - len >= 0) {
		S[id[1]].point_set0(p - len);
	}
	if (flag) {
		S[id[1]].point_add(p - 1, v0);
	}
}
int main() {
	cin >> n >> K >> len;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	if (len == 1) {
		cout << 0 << endl;
		return 0;
	}
	
	id[0] = 0;
	id[1] = 1;
	S[id[1]].point_add(0, 1);
	
	a[0] = K + 1;
	a[n + 1] = K + 2;
	for (int i = 1, j = 2; i <= n; ++i) {
		ckmax(j, i + 1);
		while (a[j] == -1)
			++j;
		if (a[i] != -1) {
			trans1(i, a[j]);
		} else {
			trans2(i, j != n + 1);
		}
	}
	cout << S[id[0]].query() << endl;
	return 0;
}
```

### n^2 DP<a name="bruteforcedp"></a>

为了帮助读者更好地理解题解，这里附上 $O(n^2)$ 朴素 DP 的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1000;
const int MOD = 998244353;
inline int mod1(int x) { return x < MOD ? x : x - MOD; }
inline int mod2(int x) { return x < 0 ? x + MOD : x; }
inline void add(int &x, int y) { x = mod1(x + y); }
inline void sub(int &x, int y) { x = mod2(x - y); }


int n, K, len, a[MAXN + 5];
int dp[MAXN + 5][2][MAXN + 5];

void trans1(int p, int nxtval) {
	for (int i = max(0, p - len); i <= max(0, p - 2); ++i) {
		add(dp[p][a[p] == nxtval][p - 1], dp[p - 1][0][i]);
		if (i >= p - len + 1)
			add(dp[p][a[p] == nxtval][i], dp[p - 1][1][i]);
	}
}
void trans2(int p, int flag) {
	for (int i = max(0, p - len); i <= max(0, p - 2); ++i) {
		// a[p - 1] 和 nxtval 不同
		if (p != 1 && i >= p - len + 1) {
			add(dp[p][0][i], dp[p - 1][0][i]); // a[p] 和 a[p - 1] 相同
		}
		if (flag) {
			add(dp[p][1][p - 1], dp[p - 1][0][i]); // a[p] 和 nxtval 相同
		}
		if (flag + (p != 1) + 1 <= K) {
			// a[p] 和 nxtval, a[p - 1] 都不同
			add(dp[p][0][p - 1], (ll)dp[p - 1][0][i] * (K - flag - (p != 1)) % MOD);
		}
		
		// a[p - 1] 和 nxtval 相同
		add(dp[p][0][p - 1], (ll)dp[p - 1][1][i] * (K - 1) % MOD);
		if (i >= p - len + 1) {
			add(dp[p][1][i], dp[p - 1][1][i]); // a[p] 和 a[p - 1], nxtval 都相同
		}
	}
}
int main() {
	cin >> n >> K >> len;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	dp[0][0][0] = 1;
	a[0] = K + 1;
	a[n + 1] = K + 2;
	
	for (int i = 1, j = 2; i <= n; ++i) {
		ckmax(j, i + 1);
		while (a[j] == -1)
			++j;
		if (a[i] != -1) {
			trans1(i, a[j]);
		} else {
			trans2(i, j != n + 1);
		}
	}
	int ans = 0;
	for (int i = max(0, n - len + 1); i <= n - 1; ++i) {
		add(ans, dp[n][0][i]);
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：lhm_ (赞：7)

考虑通过 $DP$ 来解决本题。设 $f_{i,j}$ 为考虑了前 $i$ 个位置且第 $i$ 个位置为数字 $j$ 的方案数，$s_i$ 为 $\sum\limits_{j=1}^k f_{i,j}$，$l_{i,j}$ 为位置 $i$ 往前都是数字 $j$ 的最长长度，得：
$$
\large f_{i,j}=
\begin{cases}
	s_{i-1} &l_{i,j} < len\\
	\\
	s_{i-1}-s_{i-len}+f_{i-len,j} &l_{i,j} \geqslant len\\
\end{cases}
$$
$l_{i,j} < len$ 时不可能出现不合法的情况，所以直接从 $s_{i-1}$ 转移过来。

$l_{i,j} \geqslant len$ 时转移过来的状态就会出现不合法的情况。考虑对于区间 $[i-len+1,i]$，若该区间都为 $j$，就会出现不合法的情况，因为区间都为 $j$ 只有一种情况，所以其方案数即为 $s_{i-len}$。但是这里是想把长度恰好为 $len$ 且在 $i$ 结尾的不合法情况减去，直接减去 $s_{i-len}$ 会多减长度大于 $len$ 的情况，所以还要加上 $f_{i-len,j}$。

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxk 110
#define p 998244353
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,k,len;
ll a[maxn],f[maxn][maxk],s[maxn],l[maxn][maxk];
int main()
{
    read(n),read(k),read(len);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=k;++j)
            if(a[i]==j||a[i]==-1)
                l[i][j]=l[i-1][j]+1;
    s[0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=k;++j)
        {
            if(a[i]!=j&&a[i]!=-1) continue;
            f[i][j]=s[i-1];
            if(l[i][j]>=len) f[i][j]=((f[i][j]-s[i-len]+p)%p+f[i-len][j])%p;
            s[i]=(s[i]+f[i][j])%p;
        }
    }
    printf("%lld",s[n]);
    return 0;
}
```

---

## 作者：dengyaotriangle (赞：2)

题目：一个长度 $n$ 的序列，每个元素有 $1\sim m$ 的颜色，有些位置的颜色给定，其它的在 $1\sim m$ 中任取，求将其染色的方案数，使得相邻 $l$ 个元素颜色不全相同。

首先有一个 dp 方程， $f_{i,x}$ 代表前 $i$ 个染成最后一个是 $x$ 的方案数，$s_i=\sum_x f_{i,x}$

当 $[i-l+1,i]$ 可以被同时染成 $x$ 时（也就是这个区间里面没有除了 $x$ 之外的给定的颜色），

$$f_{i,x}=s_{i-1}-s_{i-l}+f_{i-l,x}$$

这个意义是，之前的随便选的方案数 $s_i$，减去这个位置恰好出现了 $l$ 个连续的方案数 $s_{i-l}-f_{i-l,x}$，由于新加一个数只可能出现恰好 $l$ 个的非法情况，所以这么减刚好就是真实的答案

否则，

$$f_{i,x}=s_{i-1}$$ 

因为随便选就一定合法。



直接维护上述式子是 $\mathcal{O}(nm)$ 的

考虑复杂度瓶颈在于维护 $f$，但是其实并不需要这样，只需要维护 $s$ 就好了。

考虑  $f_{i,x}$

我们发现，它有可能等于 

$f_{i,x}=s_{i-1}-s_{i-l}+f_{i-l,x}$

但继续还可以拆

$f_{i,x}=s_{i-1}-s_{i-l}+s_{i-l-1}-s_{i-2l}+f_{i-2l,x}$

容易发现这就是一个这样的链条，直到某个位置停止，也就是说

$f_{i,x}=s_{i-1}-s_{i-l}+s_{i-l-1}-s_{i-2l}+\cdots +s_{i-(k-1)l-1}-s_{i-kl}+s_{i-kl-1}$

这个转移方程中没有 $f$。

首先，如果我们令 $S_i=s_i+s_{i-l}+s_{i-2l}+\cdots$，显然 $S$ 可以直接维护，那么上面的转移方程显然可以变成

$$f_{i,x}=S_{i-1}-S_{i-(k+1)l-1}-(S_{i-l}-S_{i-(k+1)l})$$


那么现在问题在于如何求 $k$。

注意到对于一个 $i$ 的不同 $x$，$k$ 的取值最多只有2个不同的。

首先，每个 $x$ 对应的 $k$ 显然是每次向左走 $l$，第一次碰到不是 $x$ 的颜色的位置的 $k$（根据之前转移方程的意义）

那么令每次走 $l$，第一次碰到的颜色是 $c$，位置是 $k_1$，第一次碰到不是 $c$ 的位置是 $k_2$，注意这个 $k_1,k_2$，可以简单地扫一遍 $\mathcal{O}(n)$ 求出来。

那么显然对于所有 $x\neq c$，对应的 $k=k_1$，否则若 $x=c$ ，$k=k_2$

所以说，对于一个 $i$，有多少个 $f_{i,x}=S_{i-1}-S_{i-(k_1+1)l-1}-(S_{i-l}-S_{i-(k_1+1)l})$，多少个 $f_{i,x}=S_{i-1}-S_{i-(k_2+1)l-1}-(S_{i-l}-S_{i-(k_2+1)l})$ 都可以求出来，那么就可以 $\mathcal{O}(1)$ 求出 $s_i$

所以说就可以 $\mathcal{O}(n)$ 解决此题了！!1

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("-Ofast")
using namespace std;
//dengyaotriangle!

const int maxn=100005*2;
constexpr int mdn=998244353;

struct mint{
    int v;
    inline operator int()const{return v;}
    inline mint(int v=0):v(v){}
    inline bool operator==(const mint&a)const{return v==a.v;}
    inline bool operator!=(const mint&a)const{return v!=a.v;}
    inline mint operator~ ()const{int r=1,b=v;for(int i=1;i<=(mdn-2);i<<=1){if((mdn-2)&i)r=r*(long long)b%mdn;b=b*(long long)b%mdn;}return mint(r);}
    inline mint operator- ()const{return mint(v?mdn-v:0);}
    inline mint operator+ (const mint&a)const{mint c(v+a.v);if(c.v>=mdn)c.v-=mdn;return c;}
    inline mint operator- (const mint&a)const{mint c(v-a.v);if(c.v<0)c.v+=mdn;return c;}
    inline mint operator* (const mint&a)const{return mint(v*(long long)a.v%mdn);}
    inline mint operator/ (const mint&a)const{return (*this)*~a;}
    inline mint&operator++(){v++;if(v==mdn)v=0;return*this;}
    inline mint&operator--(){v--;if(v==-1)v=mdn-1;return*this;}
    inline mint operator++(int){mint ret=*this;++*this;return ret;}
    inline mint operator--(int){mint ret=*this;--*this;return ret;}
    inline mint&operator+=(const mint&a){v+=a.v;if(v>=mdn)v-=mdn;return*this;}
    inline mint&operator-=(const mint&a){v-=a.v;if(v<0)v+=mdn;return*this;}
    inline mint&operator*=(const mint&a){v=v*(long long)a.v%mdn;return*this;}
    inline mint&operator/=(const mint&a){v=v*(long long)(~a).v%mdn;return*this;}
    friend istream&operator>>(istream&s,mint&a){s>>a.v;return s;}
    friend ostream&operator<<(ostream&s,const mint&a){s<<a.v;return s;}
};
int n,m,l;
int a[maxn];
mint dp[maxn];
int rep[maxn];
int cnt[maxn];
int l1[maxn],l2[maxn],cl[maxn];
mint sfx[maxn];

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

int main(){
    qio>>n>>m>>l;
    for(int i=1;i<=n;i++)qio>>a[i],a[i]+=a[i]==-1;
    int div=0,lst;
    for(int i=n;i>=1;i--){
        if(a[i])div+=1==++cnt[a[i]],lst=a[i];
        if(a[i+l]&&i+l<=n)div-=0==--cnt[a[i+l]];
        if(div==0)rep[i]=0;
        else if(div==1)rep[i]=lst;
        else rep[i]=-1;
    }
    for(int i=1;i<=l;i++){
        int cc=0;int lp1=i,lp2=i,fp=i;
        l1[i]=l2[i]=i;
        for(int j=i;j<=n;j+=l){
            if(rep[j]==-1){
                lp1=lp2=j+l;cc=0;
            }else if(rep[j]!=0){
                if(cc==0){cc=rep[j];lp2=j+l;}
                else{
                    if(cc!=rep[j]){
                        lp1=fp;lp2=j+l;cc=rep[j];
                    }else lp2=j+l;
                }
                fp=j+l;
            }
            l1[j+l]=lp1;l2[j+l]=lp2;cl[j+l]=cc;
        }
    }
    //for(int i=1;i<=n;i++)cerr<<l1[i]<<' '<<l2[i]<<' '<<cl[i]<<endl;
    dp[n+1]=1;
    for(int i=n;i>=1;i--){
        if(a[i]){
            mint w=dp[i+1];
            if(rep[i]!=-1)w-=dp[i+l];
            if(cl[i]==a[i]){
                sfx[i+l]+=w;
                sfx[l1[i]]-=w;
            }else{
                sfx[i+l]+=w;
                sfx[l2[i]]-=w;
            }
        }else{
            if(rep[i]==0){
                mint w=dp[i+1]-dp[i+l];
                sfx[i+l]+=w*mint(m);
                sfx[l2[i]]-=w*mint(m-1);
                sfx[l1[i]]-=w;
            }else if(rep[i]!=-1){
                mint w1=dp[i+1],w2=dp[i+1]-dp[i+l];
                if(cl[i]==rep[i]){
                    sfx[i+l]+=w1*mint(m-1)+w2;
                    sfx[l2[i]]-=w1*mint(m-1);
                    sfx[l1[i]]-=w2;
                }else{
                    sfx[i+l]+=w1*mint(m-1)+w2;
                    sfx[l2[i]]-=w1*mint(m-2)+w2;
                    sfx[l1[i]]-=w1;
                }
            }else{
                mint w=dp[i+1];
                sfx[i+l]+=w*mint(m);
                sfx[l2[i]]-=w*mint(m-1);
                sfx[l1[i]]-=w;
            }
        }
        dp[i]=sfx[i+l];
        sfx[i]+=sfx[i+l];
        //cerr<<dp[i]<<endl;
        //cerr<<i<<' '<<cl[i]<<' '<<l1[i]<<' '<<l2[i]<<endl;
    }
    qio<<int(dp[1]);
    return 0;
}
```

---

## 作者：XG_Zepto (赞：2)

首发于 [个人博客](https://zepto.page/post/codeforces-1093f)。

### 思路

我们可以使用 $DP$ 解决这个问题。令 $f_{i,j}$ 为考虑前 $i$ 个数，第 $i$ 个数为 $j$ 的合法方案数，$s_i$ 等于 $\sum f_{i,j}$。

那么，$f_{i,j}$ 一定从 $s_{i-1}$ 转移而来，如果 $a_j$ 恰好等于 $j$ 或者 $-1$ 的话。但是，直接转移会包含不合法的情况。我们考虑，一些状态不合法，当且仅当：

1. $i≥len$;
2. 子区间 $\{a_1,\cdots,a_i\}$ 中所有的元素都等于 $−1$ 或者 $j$。

发现，满足以上两个条件的状态数实际上就是 $s_{i-len}-f_{i-len,j}$。转移的时候删去即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define md 998244353
#define maxn 100001
#define max(a,b) (a>b?a:b)
#define maxk 101
int n,k,len,a[maxn];
int f[maxn][maxk],s[maxn],cnt[maxn][maxk];
void inc(int &a,int b){a=((a+b>=md)?a+b-md:a+b);}
int main(){
	scanf("%d%d%d",&n,&k,&len);
	for (register int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=k;++j)
			inc(cnt[i][j],cnt[i-1][j]+(a[i]==j||a[i]==-1));
	for (register int i=1;i<=n;++i){
		for (register int j=1;j<=k;++j){
			if (!(a[i]==j||a[i]==-1)) continue;
			int add=1;
			if (i>1) add=s[i-1];
			inc(f[i][j],add);
			bool ok=i>=len;
			int l=max(1,i-len+1);
			ok&=(cnt[i][j]-cnt[l-1][j]==len);
			if (!ok) continue;
			if (i==len) {inc(f[i][j],md-1);continue;}
			int sum=f[i-len][j];
			inc(sum,md-s[i-len]);
			inc(f[i][j],sum);
		}
		for (register int j=1;j<=k;++j)
			inc(s[i],f[i][j]);
	}
	printf("%d\n",s[n]);
}
```

---

## 作者：daifucong (赞：2)

一道有趣的计数dp题

看完题面第一反应$O(n*k*len)$DP，好像除了能过样例并没有什么用处。

~~去看题解啊~~

我们通过数据范围发现正解应该是$O(n*k)$的。

令$f[i][j]$表示前$i$个数，最后一个数是$j$的方案数。

转移时如果$j$可以放在第$i$个位置上那么$f[i][j]=\sum^{k}_{lst=1}f[i-1][lst]$，否则$f[i][j]=0$即可。

冷静分析，我们统计的是结尾连续数字个数小于$len$的方案个数。

而总方案数可以根据上述方法非常容易地统计出来。

正难则反，我们考虑总方案数减去不合法的方案数。

我们发现如果确定了最后一个数且$[i-len+1,i]$之间只有这个数或者$-1$，那么$[i-len+1,i]$之间的方案只有一种

所以不合法的方案就是$[1,i-len]$之间的方案数，而这个方案数就是$\sum f[i-len][lst]$。

由于连续数字个数大于$len$的方案数已经被减去，所以不合法的方案数要减去$f[i-len][j]$。

接下来就是代码实现的细节问题，注意$len=1$和$i-len=0$时的特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100100,mod=998244353;
inline void Add(int &a,int b){a=a+b>=mod?a+b-mod:a+b;}
int f[maxn][110],a[maxn],n,k,len;
int nowcnt[110],allcnt;
inline void add(int p,int x)
{
	if(nowcnt[p]==0) allcnt++;
	nowcnt[p]+=x;
	if(nowcnt[p]==0) allcnt--;
}
inline bool check(int x){return (allcnt==1&&nowcnt[x]>0)||allcnt==0;}
int main()
{
	scanf("%d%d%d",&n,&k,&len);
	if(len==1) return puts("0"),0;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	if(a[1]==-1) for(int i=1;i<=k;i++) f[1][i]=1;
	else f[1][a[1]]=1;
	if(a[1]!=-1) add(a[1],1);
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=-1) add(a[i],1);
		if(i>len&&a[i-len]!=-1) add(a[i-len],-1);
		if(a[i]==-1)
		{
			int sum=0;
			for(int j=1;j<=k;j++) Add(sum,f[i-1][j]);
			for(int j=1;j<=k;j++) f[i][j]=sum;
			if(i>=len) for(int j=1;j<=k;j++) if(check(j))
			{
				int getsum=0;
				if(i-len==0) getsum=1;
				else for(int K=1;K<=k;K++) if(K!=j) Add(getsum,f[i-len][K]);
				Add(f[i][j],mod-getsum);
			}
		}
		else
		{
			for(int j=1;j<=k;j++) Add(f[i][a[i]],f[i-1][j]);
			if(i>=len&&check(a[i]))
			{
				int getsum=0;
				if(i-len==0) getsum=1;
				else for(int j=1;j<=k;j++) if(j!=a[i]) Add(getsum,f[i-len][j]);
				Add(f[i][a[i]],mod-getsum);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=k;i++) Add(ans,f[n][i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：LJC00118 (赞：2)

发现 $ len $ 的大小非常大，不能放进状态里，又发现 $ k \le 100 $，所以用 $ f[i][j] $ 表示第 $ i $ 个数是 $ j $ 且满足题目所述条件的方案数

发现不能很好的进行转移，所以再用 $ s[i] $ 表示 $ \sum_{j = 1}^{k} f[i][j] $，然后就是容斥转移一下

注意一下需要容斥的条件

可以根据代码理解一下

```cpp
#include <bits/stdc++.h>
#define CIOS ios::sync_with_stdio(false);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> ";
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename T>
inline void read(T &f) {
	f = 0; T fu = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') fu = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
	f *= fu;
}

template <typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + 48);
	else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
	print(x); putchar(t);
}

const int N = 1e5 + 5, md = 998244353;

inline int add(int x, int y) {
	x += y;
	if(x >= md) x -= md;
	return x;
}

inline int sub(int x, int y) {
	x -= y;
	if(x < 0) x += md;
	return x;
}

int f[N][105], cnt[N][105], s[N], a[N];
int n, k, len;

int main() {
	read(n); read(k); read(len); if(len == 1) { cout << 0 << endl; return 0; }
	for(register int i = 1; i <= n; i++) read(a[i]);
	for(register int i = 1; i <= n; i++) {
		for(register int j = 1; j <= k; j++) cnt[i][j] = cnt[i - 1][j] + (a[i] == -1 || a[i] == j);
	}
	s[0] = 1; if(a[1] == -1) { for(register int i = 1; i <= k; i++) f[1][i] = 1; s[1] = k; } else f[1][a[1]] = 1, s[1] = 1;
	for(register int i = 2; i <= n; i++) {
		for(register int j = 1; j <= k; j++) {
			if(~a[i] && a[i] != j) continue;
			f[i][j] = s[i - 1];
			if(i >= len) {
				int l = i - len;
				if(cnt[i][j] - cnt[l][j] == len) {
					f[i][j] = sub(f[i][j], sub(s[l], f[l][j]));
				}
			}
			s[i] = add(s[i], f[i][j]);
		}
	}
	cout << s[n] << endl;
	return 0;
}
```


---

## 作者：chenxia25 (赞：1)

我们考虑 $dp_{i,j}$ 表示考虑到第 $i$ 个，最后一个为 $j$ 的方案数。转移就枚举最近一个连续段的左端点。显然要满足两个条件，其一是长度 $<len$，其二要都是 $j$ 或 $-1$。这个左端点显然对于每个 $j$ 都是可以一路实时更新的。

然后不就是个前缀和优化的事了吗？复杂度 $\mathrm O(nk)$。

---

## 作者：TLE_Automat (赞：0)

## 题意：

给出一个长度为 $n$ ，值域为 $[1,k] \cup \{-1\}$ 的整数序列，你需要将所有等于 $-1$ 的位置赋值成一个值域为 $[1,k]$ 的整数，使得序列不存在一个长度为 $len$ 的子串满足这个子串的所有元素相等，求方案数对 $998244353$ 取模。

## 数据范围：

$1\le len\le n\le 10^{5} , 1\le k\le 100$ 。

## 做法：

考虑暴力 $\text{dp}$ ，设 $\text{dp}_{i,j,k}$ 代表当前已经处理完前 $i$ 个位置，最后一个位置填了 $j$ 这个数字，并且长度为 $k$ 的后缀都等于 $j$ 的方案数。

这样 $\text{dp}$ 的空间复杂度是 $O(n^2 k)$ 的，如果不加优化，暴力枚举下一个位置选哪个数字，那么转移的时间复杂度为 $O(k)$ ，所以总的时间复杂度为 $O(n^2k^2)$ 的。

看起来这个 $\text{dp}$ 从状态上就输了（我一开始也是这么认为的），因为这么大的状态数，根本开不下，就算开的下也跑不了，但是我们不妨来优化一下这个 $\text{dp}$ ，看一下能把复杂度优化到什么程度。

首先我们写一下这个 $\text{dp}$ 的转移，假设我们下一个位置枚举的是 $x$ ：

1. $x = j$ ：$\text{dp}_{i,j,k} \to dp_{i+1,j,k+1}$

2. $x\neq j$ ：$\text{dp}_{i,j,k} \to dp_{i+1,x,1}$

容易发现这个 $\text{dp}$ 第一维从 $i$ 转移到了 $i+1$ ，是一层一层转移的，那么我们考虑这个层与层之间的转移是否可以优化，仔细观察后可以发现以下两点性质：

- 对于第 $1$ 种转移，我们把 $i$ 去掉后实际可以看做一个 $j \times k$ 的矩形，如果把 $j$ 看做行 $k$ 看做列，实际就是行坐标不动，列坐标加 $1$ ，换句话说，就是把 $j \times k$ 的矩形整体向右平移一格。
- 对于第 $2$ 种转移，同理把 $i$ 去掉，发现就是每一行的第 $1$ 个元素的值就是，不包含该元素所在行的其他行的所有元素和。

所以我们现在要维护的是一个矩阵，支持：

- 把矩阵整体右移一格，并且在最左边空的位置填充 $0$ 。
- 把每一行的第一个 $0$ 赋值为其他行的所有元素和。

因为 $k$ 只有 $100$ ，所以我们对维护一个 $sum_i$ 代表第 $i$ 行的和，然后用 ```std :: deque  ``` 对矩阵每一行的值动态维护即可。

$\text{Source : }$

```cpp
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)((x).size()))
#define lb(x) ((x)&(-(x)))
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e5+10;
const int MAXK=1e2+10;
const int Mod=998244353;

inline void add_mod(int &x,int y){ x+=y; if(x>=Mod) x-=Mod; }

int n,kkk,len;
int a[MAXN];

int main()
{
	scanf("%d%d%d",&n,&kkk,&len);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	if(len==1)
	{
		puts("0");
		return 0;
	}

	static deque<int> dp[MAXK];
	static int sum[MAXK];

	if(a[1]==-1)
	{
		for(int i=1;i<=kkk;i++)
			dp[i].push_front(1),
			sum[i]=1;
	}
	else
	{
		dp[a[1]].push_front(1);
		sum[a[1]]=1;
	}

	for(int i=2;i<=n;i++)
	{
		if(a[i]==-1)
		{
			int val=0;
			for(int j=1;j<=kkk;j++)
				add_mod(val,sum[j]);

			for(int j=1;j<=kkk;j++)
			{
				int cur=(val-sum[j] +Mod) %Mod;
				dp[j].push_front(cur);
				add_mod(sum[j],cur);
			}
		}
		else
		{
			int x=a[i];

			int val=0;
			for(int j=1;j<=kkk;j++)
				if(j!=x) add_mod(val,sum[j]);
			dp[x].push_front(val);
			add_mod(sum[x],val);

			for(int j=1;j<=kkk;j++)
				if(j!=x)
				{
					dp[j].clear();
					sum[j]=0;
				}
		}

		for(int j=1;j<=kkk;j++)
			if(SZ(dp[j])>=len)
				add_mod(sum[j],Mod-dp[j].back()),
				dp[j].pop_back();
	}

	int ans=0;
	for(int i=1;i<=kkk;i++)
		add_mod(ans,sum[i]);
	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：dsidsi (赞：0)

设$len_{i,j}$表示在$i$位置填$j$且不考虑长度限制的最长合法后缀。$f_{i,j}$表示$i$位置填$j$的方案数。$s_i=\sum_{j=1}^kf_{i,j}$

转移比较简单

$$f_{i,j}=0 \ \ a_i \neq -1,a_i \neq j$$

$$f_{i,j}=s_{i-1} \ \ len_{i,j}\le l$$

$$f_{i,j}=s_{i-1}-s{i-l}+f_{i-l,j} \ \ len_{i,j} \ne l$$

最后的式子加上$f_{i-l,j}$的原因是补上长度$>l$的方案，因为对于一种不合法的方案，我们是在第一不合法的位置将它减掉。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 100005, maxk = 105;

int n, k, l;
int a[maxn], f[maxn][maxk], s[maxn], len[maxk];

inline int gi()
{
    char c = getchar(); bool f = 1;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') f = 0, c = getchar();
    int sum = 0;
    while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
    return f ? sum : -sum;
}

inline int inc(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int dec(int a, int b) {return a - b < 0 ? a - b + mod : a - b;}
    
int main()
{
    n = gi(); k = gi(); l = gi();
    for (int i = 1; i <= n; ++i) a[i] = gi();

    s[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) for (int j = 1; j <= k; ++j) ++len[j];
        else for (int j = 1; j <= k; ++j) if (a[i] == j) ++len[j]; else len[j] = 0;
        if (~a[i]) {
            int j = a[i];
            if (len[j] < l) f[i][j] = s[i - 1];
            else f[i][j] = inc(dec(s[i - 1], s[i - l]), f[i - l][j]);
            s[i] = f[i][j];
        } else {
            for (int j = 1; j <= k; ++j) {
                if (len[j] < l) f[i][j] = s[i - 1];
                else f[i][j] = inc(dec(s[i - 1], s[i - l]), f[i - l][j]);
                s[i] = inc(s[i], f[i][j]);
            }
        }
    }

    printf("%d\n", s[n]);
    
    return 0;
}
```

---

## 作者：_sry (赞：0)

给你一个长度为$n$的数字串，其中$-1$的表示可以填$1$~$k$中任意一个数，其余数的范围也是从$1$~$k$。而对于连续$len$个数都不是相等的。问有多少种方案。


容易发现此题是一个计数类$dp$。我们定义$f(i,j)$表示第$i$位选$j$的方案数,$ans[i]=\sum_{j=1}^k f(i,j)$。这时要有一个问题需要考虑，就是连续$len$个数不能重复，此时就要多定一个数组$del[u]$表示从当前位置之前数$len-1$个选$u$的方案数。就是为后面的$dp$做准备。所以若现在位置为$i$,则$del[u]=ans[i-len+1]-dp[i-len+1][u]$。然后$dp(i,j)$就为$dp(i,j)=ans[i-1]-del[j]$。
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
#define mod 998244353
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=100001;
const int K=101;
int dp[N][K],n,ans[N],cnt[K],del[K],a[N],k,len;
signed main(){
    n=read(),k=read(),len=read();
    if(len==1){cout<<0;return 0;}
    for(int i=1;i<=n;i++) a[i]=read();
    ans[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(a[i]==j||a[i]==-1){
                dp[i][j]=(ans[i-1]-del[j]+2*mod)%mod;
                cnt[j]++;
                if(cnt[j]>=len-1) del[j]=ans[i-len+1]-dp[i-len+1][j],del[j]=(del[j]+2*mod)%mod;
                ans[i]+=dp[i][j];
                ans[i]%=mod;
            }else{
                cnt[j]=0;
                del[j]=0;
            }
        }
    }
    printf("%I64d\n",ans[n]);
}
```

---

## 作者：1saunoya (赞：0)

$f_{i,j}$ 表示 $i$ 结尾，当前为 $j$ 的方案数。

令 $ans_i = \sum f_{i,j}$

如果连续的是 $cnt_{j} \geq len - 1$，那么 $del_j = ans_{i-len+1} - f_{i-len+1,j}$。

那么 $f_{i,j} = ans_{ i - 1} - del_j $。

目标是 $ans_{n} = \sum f_{n,j}$。


然后做完了。

---

