# [ABC336D] Pyramid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_d

正の整数 $ k $ について、サイズ $ k $ の **ピラミッド数列** とは、長さ $ (2k-1) $ の数列であって各項の値が順に $ 1,2,\ldots,k-1,k,k-1,\ldots,2,1 $ であるようなものをさします。

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。  
 $ A $ に対して、次の操作のうち一方を選んで行うことを繰り返して ($ 0 $ 回でも良い) 得ることのできるピラミッド数列のサイズの最大値を求めてください。

- 数列の項を $ 1 $ つ選び、その項の値を $ 1 $ 減少させる。
- 先頭または末尾の項を削除する。
 
なお、問題の制約のもとで、操作を繰り返すことで必ず $ 1 $ 種類以上のピラミッド数列を得ることができることが証明できます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ A=(2,2,3,1,1) $ から始めて、 次のようにして数列 $ A $ からサイズ $ 2 $ のピラミッド数列を作る事ができます。 - 第 $ 3 $ 項を選び、$ 1 $ 減少させる。数列は $ A=(2,2,2,1,1) $ となる。 - 先頭を削除する。数列は $ A=(2,2,1,1) $ となる。 - 末尾を削除する。数列は $ A=(2,2,1) $ となる。 - 第 $ 1 $ 項を選び、$ 1 $ 減少させる。数列は $ A=(1,2,1) $ となる。 $ (1,2,1) $ はサイズ $ 2 $ のピラミッド数列です。 一方、どのように操作を行ってもサイズ $ 3 $ 以上のピラミッド数列を作ることはできないため $ 2 $ を出力します。

## 样例 #1

### 输入

```
5
2 2 3 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
3```

## 样例 #3

### 输入

```
1
1000000000```

### 输出

```
1```

# 题解

## 作者：__Allen_123__ (赞：15)

本题思路十分巧妙。动规的思想。

### 题目分析

在本篇题解中，定义左金字塔序列为 $1,2,\cdots,x$（其中 $x\ge 1$），右金字塔序列为 $x,x-1,\cdots,1$。容易发现两个序列拼合在一起，去掉中间的一个 $x$ 后，就可以组成一个金字塔序列。

我们设 $f_i$ 为以 $a_i$ 为末尾的，经过多次操作可以成为左金字塔序列的序列的最大长度，$g_i$ 为以 $a_i$ 为首的，经过多次操作可以成为右金字塔序列的序列的最大长度。容易发现，对于以 $a_i$ 为中间项的金字塔序列，其最大长度即为 $\min\{f_i,g_i\}$。

比较明显地，$f_1=g_n=1$（因为 $a_1$ 无法向左延伸形成更长的金字塔序列，$a_n$ 同理）。那么我们怎么进行状态转移呢？

我们发现，如果从 $a_i$ 向左延伸可以形成一个长度为 $x$ 的左金字塔序列，那么必定可以形成一个长度为 $y(1\le y\le x)$ 的左金字塔序列。并且，如果想以 $a_i$ 为末尾形成一个长度为 $z$ 的左金字塔序列，那么 $a_i\ge z$。

我们可以这样设想，如果 $a_i$ 和 $n$ 足够大（理想状态，忽略掉本题数据范围），那么 $f_i=f_{i-1}+1$，因为此时我们可以一直减下去，使 $a_i$ 为末尾可以形成一个左金字塔序列；如果 $f_{i-1}$ 和 $n$ 足够大，那么 $f_i=a_i$，因为此时最多只能向左延伸 $a_i-1$ 项。回到本题，没有了理想状态，转移方程便呼之欲出（即为最小值）：

$$f_i=\min\{f_{i-1}+1,a_i\}$$

从前往后扫一遍，就可以求出每个 $f_i$。

同理，我们也可以推得 $g_i=\min\{g_{i+1}+1,a_i\}$，从后往前扫一遍即可。最终求每个 $\min\{f_i,g_i\}$ 的最大值，即为最终答案。

[AC 记录](https://atcoder.jp/contests/abc336/submissions/49301700)

---

## 作者：BIG_CUTE_BUG (赞：6)

[题传](https://www.luogu.com.cn/problem/AT_abc336_d)

赛时还写了个二分，结果现在发现可以直接线性做。

## 思路

如题，我们令 $k$ 为金字塔序列中项的值。

考虑对每个 $i$，若 $i$ 为金字塔序列中项时，$k_i$ 的最大取值。

此时我们设 $i$ 取 $p_i$ 时，可以构造出的 $1,2,...,p_i-1, p_i$ 最长；取 $q_i$ 时，可以构造出的 $q_i,q_i-1,...,2,1$ 最长。

那么就有 $k_i=\min(p_i,q_i)$。

最后答案就是 $\max\limits_{i=1}^n k_i$。

其中 $q$ 和 $p$ 可以递推做，即

$$
\begin{aligned}
p_i&=\min(p_{i-1}+1,a_i)\\
q_i&=\min(q_{i+1}+1,a_i)
\end{aligned}
$$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N= 2e5+ 5;
int n, a[N], q[N], p[N];
signed main()
{
	scanf("%d", &n);
	for(int i= 1; i<= n; i++) scanf("%d", &a[i]);
	int ans= 0;
	for(int i= 1; i<= n; i++)
		q[i]= min(q[i- 1]+ 1, a[i]);
	for(int i= n; i>= 1; i--)
		p[i]= min(p[i+ 1]+ 1, a[i]);
	for(int i= 1; i<= n; i++)
		ans= max(min(p[i], q[i]), ans);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Saka_Noa (赞：4)

~~一个很阴间的做法。~~

首先二分答案，把最优化问题转换成可行性问题。

我们发现只要在 $a$ 中找到一段区间 $[l,r]$，满足 $a_{l+i} \ge b_i$ 其中 $b = \{1,2,3,\cdots ,k-1,k,k-1,\cdots,3,2,1 \}$，就可以变成合法序列。

这是一个字符串匹配问题，可以使用 KMP 解决。复杂度 $O(n \log_2 n)$。

```cpp

#include<bits/stdc++.h>

const int N=2e5+50;
using namespace std;

int n, m, a[N];
int A[N], p[N];

void sp(){
  int j = 0;
  for(int i=2;i<=m;++i){
    while(j&&A[j+1]>A[i]) j=p[j];
    j+=(A[j+1]<=A[i]);
    p[i]=j;
  }
}

int kp() {
  int j = 0, i = 1;
  for(;i<=n;++i){
    while(j&&A[j+1]>a[i])j=p[j];
    j+=(A[j+1]<=a[i]);
    if(j==m) return 1;
  }
  return 0;
}

bool check(int x) {
  if(x * 2 - 1 > n) return 0;
  m = x * 2 - 1;
  memset(p,0,sizeof p);
  for(int i=1;i<=x;++i){
    A[i] = i;
    A[2 * x - i] = i;
  }
  sp();
  return kp();
}

int main(){
  cin >> n;
  int l = 1, r = 0;
  for(int i=1;i<=n;++i){
    cin >> a[i];
    r = max(r, a[i]);
  }
  while(l<r){
    int mid = l + r + 1 >> 1;
    if(check(mid)) l = mid;
    else r = mid - 1;
  }
  cout << l;
  return 0;   
}

```

---

## 作者：2huk (赞：3)

### Solution1 二分 + 线段树

发现答案是有单调性的（如果 $k$ 满足，那么比 $k$ 小的数也能满足），因此二分这个 $k$。

接下来的问题就是在 $a$ 中找到一个长度为 $2k - 1$ 子区间 $[l, r]$，使得每一个 $a_i$ 都大于等于它应该变成的数。这里应该变成的数就是题目中的金字塔数。

我们令 $c_i$ 表示 $a_i$ 减去它应该变到的数。那么如果这个区间 $[l, r]$ 是满足条件的，就意味着每个 $l \le i \le r$ 都有 $c_i \ge 0$。也就是：
$$
\min_{i = l}^rc_i \ge 0
$$
所以在二分 check 的时候可以计算出这个 $c$ 数组来，然后判断上述条件是否满足。

但是对于每个区间 $[l, r]$ 都暴力计算 $c$ 时不优的，需要优化它。看这个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/l9ow08v6.png)

可以发现，在这个变化过程中。$c_1 \sim c_3$ 的值都增加了 $1$，$c_4 \sim c_6$ 的值都减少了 $1$。

具体地，当从区间 $[l, r]$ 变成区间 $[l+1, r+1]$ 时：

- 对于所有 $l \le i \le l + k - 1$，$c_i \gets c_i + 1$；
- 对于所有 $l + k \le i \le r + 1$，$c_i \gets c_i - 1$。

然后发现 $c$ 用到了区间加和求最小值。lazy_tag 的线段树即可。

时间复杂度 $\mathcal O(n \log^2n)$。

具体看[代码](https://atcoder.jp/contests/abc336/submissions/49314784)。

### Solution2 递推

令 $pre_i$ 表示如果以 $i$ 为金字塔的中点，那么从 $i$ 开始，最多能往左扩展多少。

令 $suf_i$ 表示如果以 $i$ 为金字塔的中点，那么从 $i$ 开始，最多能往右扩展多少。

有递推：

- $pre_i = \min(a_i, pre_{i - 1} + 1)$；
- $suf_i = \min(a_i, suf_{i + 1} + 1)$。

那么答案为 $\max_{i = 1}^n \min(pre_i, suf_i)$。

原因显然。时间复杂度 $\mathcal O(n)$。

[代码](https://atcoder.jp/contests/abc336/submissions/49346963)。

---

## 作者：yhx0322 (赞：2)

## Description
给你一个长度为 $N$ 的序列 $A$，问能否用若干次操作构成长度最大的「金字塔序列」。

操作有两种：
- 选一个数将它 $-1$。
- 删除第一个或最后一个数。



------------
「金字塔数列」：设长度为 $k$，则序列为 $1,2,\dots,k,k-1,\dots,1$。

## Solution
一道 DP 题，类似最长上升子序列的思想。

维护两个数组 $f_i,g_i$，分别表示以 $a_i$ 结尾左侧最长上升子序列的长度，右侧最长上升子序列的长度。

分两种情况转移状态：
- $a_i \le  f_{i-1}$：表示不能接上去，需要将高度降为 $a_i$。即：

$$f_{i} = a_i$$

- 否则 $a_i > f_{i-1}$：能接上去，长度 $+1$，即：

$$f_i = f_{i-1} + 1$$

求出 $f$ 数组，$g$ 数组也是同理，倒着求一遍即可。

最后取答案的时候便是 $\min(f_i,g_i)$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int a[N], n, f[N], g[N];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) f[i] = min(a[i], f[i - 1] + 1);
	for (int i = n; i >= 1; i--) g[i] = min(a[i], g[i + 1] + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, min(f[i], g[i]));
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：xz001 (赞：1)

设立 $f_{i,0}$ 表示从头到第 $i$ 位的最长长度，$f_{i,1}$ 表示从尾到第 $i$ 位的最长长度，因为以 $i$ 位中心，所以长度不能超过 $a_i$，在此基础上可以接在前一个的后边，所以转移为：

$$
f_{i,0}=\min(f_{i-1,0}+1,a_i)
$$

$$
f_{i,1}=\min(f_{i+1,1}+1,a_i)
$$

答案即为:

$$
\max_{1\le i\le n}\min(f_{i,0},f_{i,1})
$$

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long

// typedef
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

// const
const int N = 1e6 + 10, M = 2e6 + 10;
const int INF = 2e9, P = 998244353;
const double eps = 1e-6;

int n, a[N], f[N][2], ans; 

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
	for (int i = 1; i <= n; ++ i) f[i][0] = min(f[i - 1][0] + 1, a[i]);
	for (int i = n; i >= 1; -- i) f[i][1] = min(f[i + 1][1] + 1, a[i]);
	for (int i = 1; i <= n; ++ i) ans = max(ans, min(f[i][0], f[i][1]));
	printf("%lld\n", ans);
	return 0;
}


```

---

## 作者：Guizy (赞：1)

## 题目大意

给你一个 $n$ 和一个长度为 $n$ 的数列 $a_1,a_2,\ldots,a_{n-1},a_n$。

你可以对这个数列进行以下操作：

- 选一个数，把它减 $1$。

- 删除数列开头或者末尾的数。

要你找形如 $1,2,\ldots,k-1,k,k-1,\ldots,2,1$ 的序列中，$k$ 的最大值。

- $1\le n\le 2\times10^5$

- $1\le a_i\le 10^9$

## 思路

显然，这里要用 $O(n)$ 或 $O(n\log n)$ 的算法。

我们用一个数组 $pre$ 记录，$pre_i$ 表示以 $i$ 为中心的数列最多向左延伸多少。

因为我们可以对数列进行无限次减法，所以这些数只能大，不能小。

$pre$ 数组的递推式为：

$$pre_i=\min(pre_{i-1}+1,a_i)$$

再定义一个 $nxt$ 数组，同理，$nxt_i$ 表示以 $i$ 为中心的数列最多向右延伸多少。

$nxt$ 数组的递推式为：

$$nxt_i=\min(nxt_{i+1}+1,a_i)$$

最后答案就是 $\min(pre_i,nxt_i)$ 的最大值。

## 实现

非常简单，直接给出代码。

```cpp
#include<bits/stdc++.h>
#define Max 200001 
using namespace std;

int pre[Max],nxt[Max];
int n,a[Max],ans=-1;

int main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	pre[1]=1,nxt[n]=1;
	for(int i=2;i<=n;i++)
		pre[i]=min(pre[i-1]+1,a[i]);
	for(int i=n-1;i>=1;i--)
		nxt[i]=min(nxt[i+1]+1,a[i]);
	
	for(int i=1;i<=n;i++){
		ans=max(ans,min(pre[i],nxt[i]));
	}
	
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AtCoder_abc336

## D - Pyramid

[题目链接](https://www.luogu.com.cn/problem/AT_abc336_d)

### 思路

~~赛时看着这个像二分，没写出来寄了，赛后发现这多简单一道DP啊~~

先考虑暴力解法，我们可以枚举每个点，然后计算以这个点为最中间那一项 $K$ 最大可以为几。

时间复杂度大概 $O(N^2)$，显然超时了。

枚举每个点为中间点这一层肯定是不能少的，优化只能从判断入手。

由于”金字塔数列“是对称的，所以我们确定中点后只需要判断它的一侧最大能满足几，另一侧按同样方法跑一边即可。

如果我们知道现在有一段序列，他可以构成长度为 $K$ 的金字塔序列的左半部分，现在再加入一个数 $X$，显然可以分为两种情况：

- 若 $X>K$，那么 $X$ 就可以和前面 $K$ 个数凑在一起，组成一段长度为 $K+1$ 的金字塔序列。
- 若 $X\le K$，那么 $X$ 一定可以和前 $X-1$ 个数凑在一起，组成一段长度为 $X$ 的金字塔序列。

设 $lef_i$ 表示 $i$ 点左侧最大长度为几，$rit_i$ 表示 $i$ 点右侧最大长度为几。

那么最终的结果 $ans=\max\limits^{i\le n}_{i=1}\{min(lef_i,rit_i)\}$。

### Code

```cpp
// Problem:D - Pyramid
// Contest: AtCoder - AtCoder Beginner Contest 336
// URL: https://atcoder.jp/contests/abc336/tasks/abc336_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// AC Date:2024-01-16
// By:lmq

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ans;
int a[200005];
int lef[200005],rit[200005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		lef[i]=min(a[i],lef[i-1]+1);
	for(int i=n;i>=1;i--)
		rit[i]=min(a[i],rit[i+1]+1);
	for(int i=1;i<=n;i++)
		ans=max(ans,min(lef[i],rit[i]));
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：fydj (赞：0)

# **D - Pyramid**

### 题目大意

定义一个大小为 $k$ 个金字塔为一个长度为 $2k-1$ 的数列，前 $k$ 个数是 $1$ 到 $k$，后面的数是 $k-1$ 到 $1$。

给你一个长度为 $n$ 的数列 $a$，要找出大小最大的金字塔（设大小为 $k$）使得存在一段大小为 $2k-1$ 的连续子序列中每一个数都大于等于金字塔中对应位置的数。

### 思路

枚举金字塔的中间点 $i$，分别求出以点 $i$ 为起点可以最多向左或向右延伸多少位置。

考虑 DP。先求向左的情况，向右同理。设 $f_i$ 表示以点 $i$ 为起点最多可以向左延伸多少，可以发现 $f_i\le f_{i-1}+1$，因为点 $i$ 向左延伸一格就变成了点 $i-1$ 的情况，所以点 $i$ 最多比点 $i-1$ 多延伸一格；也可以发现 $f_i\ge a_i$，因为以点 $i$ 为中心的金字塔中间的数最大是 $a_i$，左半边长度最大为 $a_i$。所以得到 DP 式：$f_i=\min(f_{i-1}+1,a_i)$。

时间复杂度 $O(n)$。

### 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=200099;
char chart; bool fushu;
template <typename T> void read(T &a) { a=fushu=0; do chart=getchar(); while((chart<48||chart>57)&&chart!='-'); if(chart=='-') fushu=1,chart=getchar(); do a=(a<<1)+(a<<3)+(chart^48),chart=getchar(); while(chart>47&&chart<58); if(fushu) a=-a; return ; }
template <typename T,typename ...Args> void read(T &a,Args &...args) { read(a); read(args...); return ; }
int n,a[N]={},f[N]={},g[N]={},ans=0;
void get(int f[]) {
	int i;
	for(i=1;i<=n;++i)
		f[i]=min(a[i],f[i-1]+1);
	return ;
}
int main()
{
	int i;
	read(n);
	for(i=1;i<=n;++i)
		read(a[i]);
	get(f);
	for(i=1;i<n-i+1;++i)
		swap(a[i],a[n-i+1]);
	get(g); // 向左和向右的情况类似，求向右最多可以延伸多少格可以把数列反转用求向左的方式处理
	for(i=1;i<=n;++i)
		ans=max(ans,min(f[i],g[n-i+1]));
	printf("%d",ans);
}
```



---

## 作者：heyx0201 (赞：0)

# ABC336D Pyramid 题解
## Des.
> 给定一个序列，通过以下操作把它变为形如 $1, 2, 3, 4, \dots k, k - 1, k - 2, \dots, 1$ 的序列，求最大长度：
> - 选择一个数，将它 $+1$ 或者 $-1$。
> - 删除开头或者末尾。

## Sol.
考虑把整个序列分成左右两半：$L = 1, 2, 3, \dots, k$ 和 $R = k, k - 1, k - 2, \dots, 2, 1$。

设 $L_i$ 表示以 $A_i$ 结尾的最长金字塔序列长度，也就是说 $L' = A_{i - L_i + 1}, A_{i - L_i + 2}, A_{i - L_i + 3}, \dots, A_i$ 为一个金字塔序列。为了方便，此处 $L_0=0$，那么此时 $L_i = \min\{ A_i, L_{i-1} + 1 \}$。因为 $A_i$ 可以表示长度为 $A_i$ 的金字塔序列，这样有可能是更优的，而 $L_{i-1}$ 表示以 $A_{i-1}$ 结尾的最长金字塔序列长度，取 $\min$ 是因为 $A_i$ 有可能不合法，也就是大了或小了，但是 $L_{i-1}$ 是准确的，取 $\min$ 是因为小的那个才是合法的。如果 $A_i > A_{i-1}$，也就是 $A_i$ 肯定不合法，那么就直接 $L_{i-1}$，否则取 $\min$。

$R$ 同理。设 $R_i$ 表示以 $A_i$ 开头的最长金字塔序列长度，也就是说 $R' = A_{i}, A_{i + 1}, A_{i + 2}, \dots, A_{i + R_i - 1}$ 为一个金字塔序列。为了方便，此处 $R_{N+1}=0$，那么此时 $R_i = \min\{ A_i, R_{i+1} + 1 \}$。因为 $A_i$ 可以表示长度为 $A_i$ 的金字塔序列，这样有可能是更优的，而 $R_{i-1}$ 表示以 $A_{i-1}$ 开头的最长金字塔序列长度，取 $\min$ 是因为 $A_i$ 有可能不合法，也就是大了或小了，但是 $R_{i+1}$ 是准确的，取 $\min$ 是因为小的那个才是合法的。如果 $A_i > A_{i+1}$，也就是 $A_i$ 肯定不合法，那么就直接 $R_{i+1}$，否则取 $\min$。

## Cod.
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int n, a[MAXN], b[MAXN][2];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    b[i][0] = a[i] > a[i - 1] ? b[i - 1][0] + 1 : min(a[i], b[i - 1][0] + 1);
  }
  for (int i = n; i >= 1; i--) {
    b[i][1] = a[i] > a[i + 1] ? b[i + 1][1] + 1 : min(a[i], b[i + 1][1] + 1);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, min(b[i][0], b[i][1]));
  }
  cout << ans;
  return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc336_d)

[ABC336D](https://atcoder.jp/contests/abc336/tasks/abc336_d)

## 题意

定义大小为 $k$ 的金字塔序列为 $1,2,\dots,k-1,k,k-1,\dots,2,1$。给出长度为 $n$ 的序列 $a$，可以进行如下操作各若干次：

- 选择一个 $i$，$a_i \leftarrow a_i-1$。

- 丢掉当前的第一项或最后一项。

问 $a$ 操作后能变成的金字塔序列的最大大小（指上文中的 $k$）。

## 做法

二分答案 $mid$。只需判断 $a$ 中是否存在一个子段 $a[s\dots s+2\times mid-2]$，使得 $a_j$ 中每一项不小于对应的。具体地，令中间点 $h=s+mid-1$，则要求如下：

- 对于 $s \le i \le h$，$a_i \ge i-s+1$ 即 $a_i-i \ge s+1$。

- 对于 $h\le i \le s+2\times mid-2$，$a_i \ge mid-(i-h)$ 即 $a_i+i \ge mid+h$。

维护 $a_i-i$ 和 $a_i+i$ 的区间 $\min$，判断 $\min_{i=s}^{s+2mid-2} a_i+i$ 和 $\min a_i-i$ 是否分别大于 $s+1$ 和 $mid+h$，就能判断一个子段是否满足要求。

因此对于一个 $mid$，枚举子段左端点 $s$，用上述方法即可做到判断是否可行，这个 `check` 的复杂度可以是 $O(n\log n)$ 或 $O(n)$，取决于维护 $\min$ 的数据结构。

总复杂度 $O(n\log n)$ 或 $O(n\log^2n)$，都能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int n,a[N];

int s[N<<2][2];

#define ls (t<<1)
#define rs (t<<1|1)
#define md ((l+r)>>1)

void pushup(int t){
	s[t][0]=min(s[ls][0],s[rs][0]);
	s[t][1]=min(s[ls][1],s[rs][1]);
}

void build(int l,int r,int t){
	if(l==r){
		s[t][0]=a[l]+l+1;
		s[t][1]=a[l]-l-1;
		return;
	}
	build(l,md,ls),build(md+1,r,rs);
	pushup(t); 
}

int qry(int l,int r,int t,int x,int y,int o){
	if(l>y||r<x) return (int)1e9;
	if(l>=x&&r<=y) return s[t][o];
	return min(qry(l,md,ls,x,y,o),qry(md+1,r,rs,x,y,o));
}

bool check(int x){
	for(int s=1;s+2*x-2<=n;++s){
		int h=s+x-1,t=h+x-1;
		if(qry(1,n,1,s,h,1)>=-s && qry(1,n,1,h+1,t,0)>=h+x+1) return 1; 
	}
	return 0; 
}

signed main(){
	cin >> n;
	for(int i=1;i<=n;++i) cin >> a[i];
	build(1,n,1);
	int l=1,r=(n-1)/2+1,ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout << ans;
}
```

---

## 作者：Cure_Wing (赞：0)

[AT_abc336_d [ABC336D] Pyramid](https://www.luogu.com.cn/problem/AT_abc336_d)

### 思路

由金字塔的定义，我们可以把它拆分成左右两部分。对于原数组的一个位置 $i$，我们记录两个值 $l_i,r_i$，分别表示以 $i$ 为左边递增序列和右边递增序列能达到的最大值。因为根据金字塔的定义，它的两侧都是以一单调递增，所以维护这两个值。

考虑转移。因为 $A_i\ge1$，所以 $l_i,r_i$ 初始为 $1$，即自己就是塔顶。考虑金字塔的高度怎样才能增加，对于左半边，如果想要让下一个节点成为新更高的塔顶，那么必然要满足该点作为塔顶的高度 $+1$ 小于下一个点的 $A_i$，这样通过对这个 $A_i$ 不断 $-1$ 才可以达到指定高度。但是如果 $l_{i-1}+1>A_i$ 这个点就没用了吗？不是的，我们可以让前面的金字塔下降一定高度，使这一段和 $i$ 拼接起来，使得以 $i$ 作为左半边顶端时得到最大值，即把 $l_i=A_i$。对于前面的金字塔，如果下降到负数了，相当于忽略，在操作上就是删除左边或右边的数。右半边也是如此。

最后统计答案时，只要对 $l_i,r_i$ 取最小值（显然要让两边都能到达）即为该点作为塔顶时的最高高度，然后再取这些高度的最大值就是答案了。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005;
int n,a[N],l[N],r[N],ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	int cnt=1;//cnt表示当前点作为塔顶时可到达的最高高度
	for(int i=1;i<=n;++i,++cnt)//计算 li 升高金字塔高度
		if(cnt<=a[i]) l[i]=cnt;//如果可以直接记录
		else l[i]=cnt=a[i];//否则下降到可以实现的高度
	cnt=1;
	for(int i=n;i>=1;--i,++cnt)//计算 ri 同理
		if(cnt<=a[i]) r[i]=cnt;
		else r[i]=cnt=a[i];
	for(int i=1;i<=n;++i) ans=std::max(ans,std::min(l[i],r[i]));//统计答案
	cout<<ans;
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

蒟蒻赛时没有切，赛后发现一眼就是橙！

相信很多人赛时想到了二分长度，然后单调队列，ST 表，线段树等做法，蒟蒻也是那么想，但是太复杂了，所以下面讲一种简单的方法，而且时间复杂度 $O(n)$。

我们可以贪心的想到，要把三角形数列的两端控制成 $1$，然后向中间逐渐加一，是最优测率，更能使得他形成一个三角形数列，也就是最大化答案。

对于这个三角形数列，我们可以想成一个递增的和一个递减的，然后拼起来。

设 $dp_i$ 为到第 $i$ 个点最长上升的长度，如果此刻 $a_i \le dp_{i-1}$。那么代表到这个 $a_i$ 无法延续以前有的最长上升，所以长度最多为 $a_i$。否则，长度继续累加。

后面累加也是同理。

```cpp
int n,a[N],dp[N];
int ans=1;
void solve(){
	cin >>n;for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]>dp[i-1])dp[i] = dp[i-1]+1;
		else dp[i]=a[i];
	}int tmp=0;
	for(int i=n;i>=1;i--){
		if(a[i]>tmp)tmp++;
		else tmp=a[i];
		ans=max(ans,min(dp[i],tmp));
	}cout<<ans;
}
```

---

