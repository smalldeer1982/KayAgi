# [ARC169C] Not So Consecutive

## 题目描述

给定一个整数 $N$。当且仅当长度为 $N$ 的整数序列 $x=(x_1,x_2,\cdots,x_N)$ 满足以下条件时，称其为**好**数列。

- $x$ 的每个元素都是 $1$ 到 $N$ 之间的整数。
- 对于每个整数 $i$（$1\leq i\leq N$），在 $x$ 中不存在 $i$ 连续出现 $i+1$ 次或更多次的位置。

给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\cdots,A_N)$。$A$ 的每个元素要么是 $-1$，要么是 $1$ 到 $N$ 之间的整数。请计算将每个 $-1$ 替换为 $1$ 到 $N$ 之间的整数后，可以得到多少个好数列，并对 $998244353$ 取模。

## 说明/提示

### 限制条件

- $1\leq N\leq 5000$
- $A_i=-1$ 或 $1\leq A_i\leq N$
- 输入的所有值均为整数。

### 样例解释 1

将每个 $-1$ 替换为 $1$ 或 $2$ 后，共有 $4$ 种数列。对于 $A=(1,1)$，$1$ 连续出现了 $2$ 次，因此不是好数列。对于 $A=(1,2),(2,1),(2,2)$，它们都是好数列。因此答案是 $3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
-1 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
2 -1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
4
-1 1 1 -1```

### 输出

```
0```

## 样例 #4

### 输入

```
20
9 -1 -1 -1 -1 -1 -1 -1 -1 -1 7 -1 -1 -1 19 4 -1 -1 -1 -1```

### 输出

```
128282166```

# 题解

## 作者：Redshift_Shine (赞：7)

# [Not So Consecutive](https://www.luogu.com.cn/problem/AT_arc169_c)

**毫不夸张地说**，这道题是本场 ARC 中最简单的一道题，没有之一。

## 题解

定义 $d_{i,j,k}$ 为到第 $i$ 个位置为止， $A$ 的结尾为连续 $k$ 个 $j$ 的方案数。

随后可以得出以下转移式。

$$
d_{i,j,k}=\begin{cases}
0\qquad\qquad\qquad\qquad\qquad\qquad A_i\neq -1 \space\land\space A_i\neq j\\
\begin{cases}
\sum_{l=1}^{n}\sum_{r=1}^ld_{i-1,l,r}[l\neq j]\qquad k=1\\
d_{i,j,k-1}\qquad\qquad\qquad\qquad\quad\space\space k\neq 1
\end{cases}
\end{cases}
$$

于是我们发现一个奇妙的性质： $k\neq 1$ 时的转移实际上就是把整个数组后移一位。

所以可以想到使用队列优化转移。

但是怎么求和呢？实际上，在 $k=1$ 的情况下，我们似乎只关注整个子数组的和。

所以就可以在每次进行转移时动态维护整个处在可转移范围之内的数值和以及所有数值和，来进行快速转移。

时间复杂度 $O(n^2)$ 。

## 代码

```c++
#include<iostream>
#include<queue>
using namespace std;
const int N=5e3+10,mod=998244353;
int n,a[N],sm[N],alsm,tmp[N];
queue<int> dp[N];
inline void fa(int& x,int v){
    x=(x+v>=mod?x+v-mod:x+v);
}
inline void fm(int& x,int v){
    x=(x-v<0?x-v+mod:x-v);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            for(int j=1;j<=n;j++){
                tmp[j]=max((alsm-sm[j]+mod)%mod,(int)(i==1));
            }
            for(int j=1;j<=n;j++){
                fa(alsm,tmp[j]);
                fa(sm[j],tmp[j]);
                dp[j].push(tmp[j]);
                if(dp[j].size()>j){
                    fm(sm[j],dp[j].front());
                    fm(alsm,dp[j].front());
                    dp[j].pop();
                }
            }
        }else{
            tmp[a[i]]=max((alsm-sm[a[i]]+mod)%mod,(int)(i==1));
            fa(sm[a[i]],tmp[a[i]]);
            fa(alsm,tmp[a[i]]);
            dp[a[i]].push(tmp[a[i]]);
            if(dp[a[i]].size()>a[i]){
                fm(sm[a[i]],dp[a[i]].front());
                fm(alsm,dp[a[i]].front());
                dp[a[i]].pop();
            }
            for(int j=1;j<=n;j++){
                if(a[i]==j)continue;
                while(dp[j].size())dp[j].pop();
                fm(alsm,sm[j]);
                sm[j]=0;
            }
        }
    }
    printf("%d\n",alsm);
}
```

---

## 作者：Aigony (赞：4)

读错题了，写了一车组合数还在想为什么过不去最后一个样例。

[更好的阅读体验 qwq](https://www.cnblogs.com/ying-xue/p/arc169.html)

## Description

给一个长度为 $n$ 的序列 $A$，其中一些位置为 $-1$，其余位置的值域均在 $[1,n]$ 之间。

你要给所有 $-1$ 的位置填一个 $[1,n]$ 之间的整数，要求满足：

- 对于任意 $[1,n]$ 之间的整数 $i$，不能在 $A$ 中**连续**出现超过 $i$ 次。

求方案数，答案对 $998\, 244\, 353$ 取模。$n\le 5000$。

## Solution

设 $f_{i,j}$ 表示填了前 $i$ 个位置，第 $i$ 个位置填的是 $j$ 的方案数。那么枚举这个连续段的起点，朴素转移有 

$$
f_{i,j}=\sum_{k=\max(0,i-j)}^{i-1} [\forall l\in [k+1,i],A_l=-1 \text{ or } A_l=j]\sum_{col\neq j} f_{k,col}
$$

这样直接做是 $\mathcal{O}(n^4)$ 的，考虑优化。

首先方括号里那一串式子本质上是找 $i$ 前面最后一个填了不为 $j$ 的数的位置，设这个位置为 $lst$。

对每个数维护 $pos_j$ 表示数 $j$ 当前最后一次出现的位置。那么对于每个新的 $i$，我们记录 $pos$ 的最大值和次大值即可。

这个过程对每个 $i$ 可以 $\mathcal{O}(n)$ 完成。式子变成了

$$
f_{i,j}=\sum_{k=lst}^{i-1} \sum_{col\neq j} f_{k,col}
$$

再把 $col\neq j$ 这个条件容斥掉，有
$$
f_{i,j}=\sum_{k=lst}^{i-1} \sum_{col=1}^n f_{k,col}-\sum_{k=lst}^{i-1}f_{k,j}
$$

设 $S_i=\sum\limits_{j=1}^i \sum\limits_{col=1}^n f_{i,col}$，$s_{i,j}=\sum\limits_{k=1}^i f_{k,j}$，前缀和优化即可。时间复杂度 $\mathcal{O}(n^2)$。

```cpp
#define int long long
const int N=5005,mod=998244353;
int pos[N],f[N][N],s[N][N],sum[N],n,a[N];
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    f[0][0]=1,sum[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=-1) pos[a[i]]=i;
        int mx1=0,mx2=0;
        for(int j=1;j<=n;j++) 
        {
            if(pos[j]>mx1) mx2=mx1,mx1=pos[j];
            else if(pos[j]>mx2) mx2=pos[j];
        }
        for(int j=1;j<=n;j++)
        {
            int lst=max(i-j,(a[mx1]==j)?mx2:mx1);
            f[i][j]=sum[i-1]-(lst?sum[lst-1]:0)-(s[i-1][j]-(lst?s[lst-1][j]:0));
            f[i][j]=(f[i][j]%mod+mod)%mod;
            s[i][j]=(s[i-1][j]+f[i][j])%mod;
            (sum[i]+=f[i][j])%=mod;
        }
        (sum[i]+=sum[i-1])%=mod;
    }
    cout<<(sum[n]-sum[n-1]+mod)%mod<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## Solution

首先有一个朴素的 dp，设 $f_{i,j,k}$ 为前 $i$ 个数，第 $i$ 个填 $j$，且 $j$ 连续出现了 $k$ 次的方案数，有转移：

$$
f_{i,j,k} =
\begin{cases}
0 & a_i \ne -1 \land a_i \ne j \\
f_{i-1,j,k-1} & k > 1 \\
\displaystyle \sum \limits _{1 \le j' \le n \land j' \ne j} \sum \limits _{1 \le k' \le j} f_{i-1,j',k'} & k = 1
\end{cases}
$$

于是可以发现在 $k > 1$ 的时候，相当于整个数组往后移一位，想到用队列维护；在 $k = 1$ 的时候相当于 $\sum f_i - \sum f_{i,j}$，可以考虑维护每个队列的和与所有队列的总和，不难发现这些都是可以 $O(1)$ 做的；然后特判一下 $a_i \ne -1 \land a_i \ne j$ 直接清空队列（`std::swap` 是 $O(1)$ 的）。于是就做完了。

复杂度 $O(n^2)$。

## Code

```cpp
int n,a[N],s[2][N];
queue <int> q[N];

signed main()
{
	read(n),_::r(a,n);
	
	rep(j,1,n) 
	{
		if(a[1]==-1 || j==a[1]) q[j].emplace(1),s[0][j]=1;
		else q[j].emplace(0);
		s[0][0]+=s[0][j];
	}
	
	bool fl=0;
	rep(i,2,n) 
	{
		fl=!fl;
		rep(j,1,n) s[fl][j]=s[!fl][j];
		s[fl][0]=0;
		
		rep(j,1,n)
		{
			q[j].size()>=j && (add(s[fl][j],-q[j].front()),q[j].pop(),1);
			
			if(a[i]==-1 || a[i]==j) q[j].emplace(s[!fl][0]-s[!fl][j]),add(s[fl][j],s[!fl][0]-s[!fl][j]);
			else clr(q[j]),q[j].emplace(0),s[fl][j]=0;
			add(s[fl][0],s[fl][j]);
		}
	}
	
	write(s[fl][0]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Erine (赞：2)

很一眼的 dp。一个朴素的状态是 $f_{i,j,k}$ 表示前 $i$ 个数的最后一个是 $j$，$j$ 所在的结尾连续段长度为 $k$ 的方案数。这是一个简单的 3D1D dp，当然随便优化到 3D0D。但是我们还是过不去，因为状态太多了。

这时候我们将 dp 的状态变为转移：$f_{i,j}$ 表示前 $i$ 个数的最后一个是 $j$ 的方案数，转移时枚举 $k$，此时我们优化成了一个 2D1D dp。然后 $k$ 是连续的，意味着可以进行一个前缀和，于是 2D0D 就解决了。

注意需要处理出 $pre_{i,j}$ 表示 $i$ 往前最多能放多少个 $j$ 限制 $k$ 的转移范围。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r

using namespace std;
using pii = pair<int, int>;

const int maxn = 5e2 + 10;
const int mod = 998244353;
const bool multidata = 0;

int n;
int a[maxn];
int pre[maxn][maxn];
int f[maxn][maxn];
int g[maxn][maxn];
int h[maxn];

int query(int l, int r, int j) {
	if (!l) return g[r][j];
	return (g[r][j] - g[l - 1][j] + mod) % mod;
}

void fake_main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j == a[i] || a[i] == -1) pre[i][j] = pre[i - 1][j] + 1;
		}
	}
	f[0][0] = h[0] = 1;
	for (int j = 1; j <= n; j++) g[0][j] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j == a[i] || a[i] == -1) {
				f[i][j] = query(i - min(pre[i][j], j), i - 1, j);
				(h[i] += f[i][j]) %= mod;
			}
		}
		for (int j = 1; j <= n; j++) g[i][j] = (g[i - 1][j] + (h[i] - f[i][j] + mod) % mod) % mod;
	}
	cout << h[n] << endl;
}

signed main() {
	int T;
	if (multidata) cin >> T; 
	else T = 1;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：jnzg (赞：2)

## 题意

给定长度为 $n$，值域为 $[1,n]$ 的整数数组 $a$，用 $1$ 到 $n$ 的整数替换 $a$ 中的 $-1$，并对其计数，要求所有整数 $i$ 的联通块长度不超过 $i$。

## 思路

设 $f_{i,j}$ 表示以 $i$ 结尾，在结尾处连续出现 $j$ 次的方案数，考虑如何维护 $f$ 数组。

当 $a_i \neq -1$ 时，$f_{a_i}$ 整体右移，将 $f_{a_i,1}$ 赋值为 $1$，而所有以其他数字结尾的方案都转移到 $f_{a_i,1}$，并且清空。

当 $a_i=-1$ 时，所有 $f_i$ 整体右移，所有 $f_{i,1}$ 赋值为 $1$。

直接转移当然是 $O(n^3)$ 的，注意到对于每个 $i$，可以维护一个右移标记和一个清空标记，以及一个 $f_{i,j}$ 的全局和数组，时间复杂度优化为 $O(n^2)$。

Code：

```cpp
/*
    Program: ARC169C.cpp
    Author: 1l6suj7
    DateTime: 2023-12-09 21:31:36
    Description:
*/

#include <bits/stdc++.h>
#define ll long long
#define lp(i, j, n) for(int i = j; i <= n; ++i)
#define dlp(i, n, j) for(int i = n; i >= j; --i)
#define mst(n, v) memset(n, v, sizeof(n))
#define mcy(n, v) memcpy(n, v, sizeof(v))
#define INF 1e18
#define MAX4 0x3f3f3f3f
#define MAX8 0x3f3f3f3f3f3f3f3f
#define mkp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define co(x) cerr << (x) << ' '
#define cod(x) cerr << (x) << endl
#define fi first
#define se second
#define eps 1e-8

using namespace std;

const int N = 5010;
const ll MOD = 998244353;

int n, a[N];
ll f[N][N * 3], tg[N], sum[N], cl[N];

void add(ll & t1, ll t2) { t1 = (t1 + t2) % MOD; }

ll & F(int i, int j) { return j - tg[i] >= cl[i] ? (f[i][n + j - tg[i]] = 0) : f[i][n + j - tg[i]]; }

signed main() {
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#ifndef READ
    ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cin >> n;
    lp(i, 1, n) cin >> a[i], cl[i] = n + 1;
    if(a[1] == -1) lp(i, 1, n) F(i, 1) = 1, sum[i] = 1;
    else F(a[1], 1) = 1, sum[a[1]] = 1;
    lp(i, 2, n) {
        ll t = 0;
        lp(k, 1, n) add(t, sum[k]);
        if(a[i] == -1) {
            lp(j, 1, n) {
                ++tg[j], F(j, 1) = t - sum[j];
                add(sum[j], t - sum[j] - F(j, j + 1));
            }
        }
        else {
            ++tg[a[i]], F(a[i], 1) = t - sum[a[i]];
            add(sum[a[i]], t - sum[a[i]] - F(a[i], a[i] + 1));
            lp(j, 1, n) if(j != a[i]) sum[j] = 0, cl[j] = 1 - tg[j];
        }
    }
    ll ans = 0;
    lp(i, 1, n) add(ans, sum[i]);
    cout << (ans % MOD + MOD) % MOD << endl;
    return 0;
}
```


---

## 作者：Union_Find (赞：1)

看完题，注意到 $n \leq 5000$。加上求方案数，大概率就是 dp 了。

一开始想的是 $f_{i,j,k}$ 表示前 $i$ 个数，第 $i$ 个数是 $j$，且已经连续了 $k$ 个数的方案数。但是这样就是 $O(n^3)$ 的状态了，会炸掉。

于是我们考虑保留其中最重要的两维，即 $i$ 和 $j$，并且考虑枚举 $k$，因为正常情况下，时间复杂度会比较好优化。

设 $f_{i,j}$ 表示前 $i$ 个数，第 $i$ 个数是 $j$ 的方案数。转移如下。

$$f_{i,j} = \sum_{k=i-j \wedge [\forall p \in [k,i),p = j \vee p = -1]}^{i-1}\sum_{col \not = j} f_{k,col}$$

这样子我们就可以考虑前缀和优化了。首先预处理 $k$ 的可行范围，这个可以 $O(n^2)$ 预处理。

考虑记 $s_{i,j}$ 表示 $\sum_{k=1}^i \sum_{col \not = j} f_{i,j}$。这样子就可以 $O(n^2)$ 的转移了。

初始化因为没有数字，为了防止影响后面转移，我们设 $0$ 号位置数字是 $0$。这样子 $f_{0,0} = 1,s_{0,col} = 1(col \in [1,n])$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define N 5005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const int P = 998244353;
int n, a[N], pre[N][N], f[N][N], sum[N], s[N][N];
int main(){
	n = rd();
	for (int i = 1; i <= n; i++){
		a[i] = rd();
		for (int j = 1; j <= n; j++) if (a[i] == j || a[i] == -1) pre[i][j] = pre[i - 1][j] + 1;
	}f[0][0] = sum[0] = 1;
	for (int j = 1; j <= n; j++) s[0][j] = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++) if (a[i] == j || a[i] == -1){
			int lst = i - min(pre[i][j], j);
			f[i][j] = (s[i - 1][j] - (lst ? s[lst - 1][j] : 0) + P) % P, sum[i] = (sum[i] + f[i][j]) % P;
		}for (int j = 1; j <= n; j++) s[i][j] = (s[i - 1][j] + (sum[i] - f[i][j] + P) % P) % P;
	}printf ("%lld\n", sum[n]);
	return 0;
}

```

---

## 作者：JWRuixi (赞：1)

### 题意

定义一个序列 $\{a_n\}$ 是好的当且仅当：

- $\forall 1 \le i < n$，$i$ 在 $a$ 中出现的次数小于 $i + 1$ 次。

给定一个序列 $\{a_n\}$，满足 $\forall i, a_i = \{-1, 1, 2, \dots, n\}$，求有多少种将 $-1$ 替换为 $1 \sim n$ 的方法使得所得序列 $a^\prime$ 是好的。

$n \le 5 \times 10^3$，答案对 $998244353$ 取模。

### 分析

由于数据范围小的惊人，考虑暴力一点的 dp：设 $f_{i, j, k}$ 表示考虑 $1 \sim i$，$a_i = j$，已经连续了 $k$ 个，转移是不言自明的。

但这玩意状态数太多了，没啥前途，不过状态数压缩是 trivial 的：设 $f_{i, j}$ 表示考虑 $1 \sim i$，$a_i = j$。转移考虑枚举最后一段连续了多少个，让后钦定前一位选的数不是 $j$ 即可，列出来就是：
$$
f_{i, j} = \sum_{i - x \le j}\sum_{y \not = j} f_{x, y}
$$
第一个求和明显是一段后缀，那么直接用前缀和优化转移就可以了。

但是推到这里出现了一点小问题，我们会发现如果 $\exist x < p \le i,a_p \not = j$ 那么这个转移就不能进行了，不过没关系，发现还是一个后缀，只需要维护每个值的界点就行了！

### 代码

提交记录：<https://atcoder.jp/contests/arc169/submissions/49036764>。



---

## 作者：Xy_top (赞：1)

数据范围 $n\leq 5000$，一眼 DP 了。

分析一下，对每个数字出现次数的要求都是不一样的，所以如果要 DP，填的数字这一维是一定要有的，然后还要有当前是第几个，状态是开的下的。

所以设 $f_{i,j}$ 为前 $i$ 个数字，且最后一个填 $j$ 的方案数，发现转移的时候要用到后面数组的信息于是考虑从后往前转移。

设 $f_{i,j}$ 为后 $i$ 个数字，且第一个填 $j$ 的方案数，转移方程如下。

$f_{i,j} = \sum f_{k,l}$，其中 $l\neq j$ 且 $i$ 到 $k$ 这一段可以填的下这么多连续的数，是否填的下可以在倒着扫的时候对每个数字维护一个最远可以填到的位置。

这样直接暴力枚举还是会超时，于是再维护两个前缀和，一个记录 $l=j$ 时的数组和，另一个记录所有的，两个相减就能得到 $l\neq j$ 时的了。

代码（有注释）：

```cpp
#include <iostream>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int a[5005], pre[5005], f[5005][5005], s[5005][5005], s_[5005];
const int mod = 998244353;
signed main () {
	cin >> n;
	For (i, 1, n) cin >> a[i];
	For (i, 1, n) pre[i] = n + 1;
	foR (i, n, 1) {
		if (a[i] != -1) For (j, 1, n) if (j != a[i]) pre[j] = i;
		For (j, 1, n) {
			int x = pre[j];
			if (x <= i) continue;
			x = min (x, i + j);
			if (i == n) {
				f[i][j] = 1;
				continue;
			}
			x = min (x, n + 1);
			f[i][j] = ( (s_[i + 1] - s_[x + 1] - s[i + 1][j] + s[x + 1][j]) % mod + mod) % mod;
			if (x == n + 1) f[i][j] = (f[i][j] + 1) % mod;
		}
		s_[i] = s_[i + 1];
		For (j, 1, n) {
			s[i][j] = (s[i + 1][j] + f[i][j]) % mod;
			s_[i] = (s_[i] + f[i][j]) % mod;
		}
	}
	int ans = 0;
	if (a[1] == -1) {
		For (i, 1, n) ans = (ans + f[1][i]) % mod;
		cout << ans;
	} else cout << f[1][a[1] ];
	return 0;
}
/*
从后向前进行 DP
设 f[i][j] 为 i ~ n 且第一个为 j 的方案数

那么 f[i][j] = \sigma f[k][l]

其中 l ≠j 并且 i ~ k - 1 可以全部填数字 j

并定义 s[i][j] = f[i][j] + f[i + 1][j] + f[i + 1][j] + .....

同时定义 s_[i] = \sigma f[i] + \sigma f[i + 1] + \sigma f[i + 2] + ...
*/
```


---

## 作者：0x3F (赞：0)

dp 题。

考虑 $dp_{i,j}$ 表示从 $1$ 到 $i$，$A_{i}=j$，且 $A_{i+1}\ne j$ 的方案数。

那么我们考虑可以使得 $A_{k+1}$ 到 $A_{i}$ 全部为 $j$ 的最小的 $k$。

有转移：$dp_{i,j}=\sum_{s=k}^{i-1}\sum_{t\ne j}dp_{s,t}$。特别地，如果 $k=0$，那么答案再加 $1$。

前缀和优化即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
int n, a[5010], dp[5010][5010], ans;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		int posa = 0, posb = 0;
		for (int j = i; j >= 1; j--) {
			if (a[j] != -1) {
				if (posa) {
					if (a[j] != a[posa]) {
						posb = j;
						break;
					}
				} else {
					posa = j;
				}
			}
		}
		for (int j = 1; j <= n; j++) {
			int k = ((posa && a[posa] == j) ? (posb) : (posa));
			k = max(k, i-j);
			if (!k) dp[i][j] = k = 1;
			dp[i][j] = (((long long)dp[i][j] + dp[i-1][n] - dp[k-1][n] - dp[i-1][j] + dp[k-1][j] + dp[i-1][j-1] - dp[k-1][j-1]) % p + p) % p;
		}
		for (int j = 1; j <= n; j++) {
			dp[i][j] = (((long long)dp[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1]) % p + p) % p;
		}
	}
	cout << ((dp[n][n] - dp[n-1][n]) % p + p) % p << endl;
	return 0;
}
```


---

