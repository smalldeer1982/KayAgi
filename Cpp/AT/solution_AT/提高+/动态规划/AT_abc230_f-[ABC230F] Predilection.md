# [ABC230F] Predilection

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc230/tasks/abc230_f

長さ $ N $ の数列 $ A $ が与えられます。 数列の長さが $ 2 $ 以上のとき、隣接する二つの値を選び、それらを削除し、それらが元にあった位置にそれらの和を挿入するという操作を好きなだけ行えます。 $ 0 $ 回以上の操作の後の数列として考えられるものは何通りあるか求め、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ 0 $ 回以上の操作の後の数列として考えられるのは以下の $ 4 $ 通りです。 - $ {1,-1,1} $ - $ {1,0} $ - $ {0,1} $ - $ {1} $

## 样例 #1

### 输入

```
3
1 -1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
10
377914575 -275478149 0 -444175904 719654053 -254224494 -123690081 377914575 -254224494 -21253655```

### 输出

```
321```

# 题解

## 作者：Bpds1110 (赞：6)

[**Link**](https://www.luogu.com.cn/problem/AT_abc230_f)
### Describe:
> 给定 $n$ 个整数，每次可以合并任意的相邻两个数，并用它们的和代替这两个数，让你求出合并完成后不同序列的个数。

### Solution:
考虑对这个数组进行前缀和操作，用 $num_i$ 表示第 $i$ 个数，则 $a_i = \sum_{j = 1}^{i} num_j$。我们发现合并第 $i$ 和 $i + 1$ 个数合并第 $i$ 和 $i + 1$ 个数后进行前缀操作，实际上就是删除了 $a_i$。对于合并第 $i$ 和 $i + 1$ 个数的操作，$i$ 最多取到 $n - 1$，即 $i < n$，从中得出在删除操作中，$a_n$ 必须保留。因为每个前缀和只能对应一个数，于是题意简化成：对给出的 $n$ 个数进行前缀和操作，每次可以删除任意一个 $a_i (i < n)$，求共有多少种不同的序列。可以发现，实际上就是求前缀数组 $a_1 \sim a_{n - 1}$ 的不同子序列的个数，我们考虑 DP 求解。

- **状态**：令 $dp_i$ 表示在前 $i$ 个数中，**不考虑空集**的不同子序列个数。
- **目标状态**：因为要求 $a_n$ 必须选中，所以为 $dp_{n - 1} + 1$，$+ 1$ 表示前 $i - 1$ 个数组合的子序列为空集的情况。
- **初始状态**：显然，$dp_1 \gets 1$。
- **状态转移**：分类讨论。当 $a_i$ 在 $a_1 \sim a_{i - 1}$ 未出现，则 $a_i$ 可以和以前所有的排列（共 $dp_{i - 1}$ 种）进行匹配（即把 $a_i$ 放入每个出现过的序列末尾），也可以不进行匹配（即保留原来的所有序列），还有一种 $a_i$ 单独成为一个序列的情况。当 $a_i$ 在 $a_1 \sim a_{i - 1}$ 出现过，我们设 $nxt$ 为上一次值为 $a_i$ 的数出现的位置。显然，$a_i$ 单独作为一串序列是不可能的，于是我们考虑 $a_i$ 和前面 $dp_{i - 1}$ 种情况匹配，有 $dp_{i - 1} \times 2$ 种，但是在 $dp_{nxt - 1}$ 的所有序列匹配 $a_{nxt}$ 和匹配 $a_i$ 是相同的。于是考虑减去 $dp_{nxt - 1}$ 即可。至于如何得出上一个值为 $a_i$ 的数出现位置，用桶 $mp$ 记录即可。得出转移方程。
$$
dp_i \gets \begin{cases}
 dp_{i - 1} \times 2 + 1 & \text{ if } mp_{a{i}} > 0\\
 dp_{i - 1} \times 2 - dp_{nxt - 1} & \text{ if } mp_{a{i}} = 0
\end{cases}
$$

### Code:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 1, mod = 998244353;
int n, a[N], dp[N];
map < int, int > mp;
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; ++ i)
		cin >> a[i], a[i] += a[i - 1];//进行前缀和操作
	dp[1] = 1; mp[a[1]] = 1;//初始状态
	for(int i = 2; i <= n; ++ i)
	{
		int nxt = mp[a[i]];
		if(! nxt) 
			dp[i] = dp[i - 1] * 2 % mod + 1;
		else dp[i] = (dp[i - 1] * 2 % mod - dp[nxt - 1] + mod) % mod;//转移
		mp[a[i]] = i;//记录a[i]出现过，并保存下标
	}
	cout << dp[n - 1] + 1;//目标状态
	return 0;
}

```


---

## 作者：World_Creater (赞：5)

套路题？

观察操作的本质：在前缀和数组内删除一个数（但是不能删除最后一个元素）。

因此最终序列的前缀和是**原序列的前缀和的一个子序列**。

由于确定前缀和能反推原序列，因此答案即为原序列前缀和中，**本质不同的子序列**个数，当然这里我们钦定最后一个元素必选（原因见上）。

这是个经典计数 $\rm DP$，直接做就可以了。

具体的，设 $f_i$ 表示以 $i$ 为末尾的子序列个数，$lst_i$ 为数字 $i$ 上一次出现的位置（未出现过为 $0$）。

则：
$$f_i=\begin{cases}f_{i-1}\times2+1\ (lst_i=0) \\ f_{i-1}\times2-f_{lst_i-1}\ (lst_i\not=0)\end{cases}$$

意义为若这个数之间未出现过，则它可以接在之前所有子序列的后面并产生一个新的单个数字的子序列；否则在接上去的前提上减去之前重复接上的。

注意处理最后一个元素即可。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace __gnu_pbds;
using namespace std;
gp_hash_table<int,int> mp;
const int mod=998244353;
int n,a[200005],pre[200005],f[200005];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		pre[i]=pre[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(!mp[pre[i]])
		{
			f[i]=f[i-1]*(i==n?1:2)+(i!=n);
		}
		else 
		{
			f[i]=f[i-1]*(i==n?1:2)-f[mp[pre[i]]-1]*(i!=n);
		}
		mp[pre[i]]=i;
		f[i]=(f[i]%mod+mod)%mod;
	}
	cout<<(f[n]+1)%mod;//加上空子序列
}
```

---

## 作者：piggy123 (赞：2)

刻画？刻画你妈刻画。

由于脑子不够用想不到题解里的刻画怎么办？我们考虑一个暴力 DP：$dp_i=\sum dp_j$。但显然这样会算重，我们考虑什么时候会算重：
```
3
-1 0 1
```
考虑这个例子，答案应该为 $3$。因为中间存在一个 $0$，把它归到前面或者后面一段得到的结果是一样的，所以我们不妨钦定将它归到前面一段，这样就不重不漏了。这里的 $0$ 实际上可以拓展到任意和为 $0$ 的段。

所以我们的 DP 转移范围即满足 $j+1\sim i-1$ 中前缀和没有与 $j$ 位置前缀和相同的 $dp_j$（即，转移区间不存在一个前缀和为 $0$）。注意需要特判从 $0$ 转移，因为 $0$ 前面没有一段，所以也要算进来。

然后上个树状数组就做完了。

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题一眼就是 dp 呀。那么我们就要来想一下什么时候才会重复，其实当我们有两个数前缀和相同时才会出现重复，所以我们就可以把问题装换成在一个前缀和中本质不同的子序列的数量（最后一个不能删），那么这就成一个模板题了。我们定义 $f_i$ 为从 $1\sim i$ 能凑出的不同子序列的个数，然后我们就来想转移了，这里分两种情况：

- 若此数之前出现过，$f_i=f_{i-1}-f_{last_{sum_{i}}-1}$ 这里是因为我们若接上上一个出现过的所有东西都会和上一个接上重复。
- 否则，$f_i=f_{i-1}\times 2+1$ 这里先接上前面的所有在加上自己。

最后输出 $f_{n-1}+1$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n;
const int N=2e5+10;
int sum[N],f[N];
map<int,int>last;
const int mod=998244353;
map<int,int>vis;
fire main() {
	cin>>n;
	rep(i,1,n) cin>>sum[i],sum[i]+=sum[i-1];
	rep(i,1,n-1) {
		if(!vis[sum[i]]) f[i]=(f[i-1]*2+1)%mod;
		else f[i]=((f[i-1]*2)%mod-f[last[sum[i]]-1]+mod)%mod;
		last[sum[i]]=i;
		vis[sum[i]]=1;
	}
	cout<<(f[n-1]+1)%mod<<endl;
	return false;
}
```

---

## 作者：carp_oier (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/AT_abc230_f.html)看看呢。

## prologue 

各位在比赛的时候一定要坚信自己的式子，然后去考虑自己的实现是不是挂了。本人在今天模拟赛的时候质疑自己的式子然后不看实现 100 -> 0。

## analysis

考虑对这个给定数组进行前缀和，然后就将问题转化成为了求这个前缀和数组的子序列的个数。对于求子序列，我们很轻松可以写出来这个式子。

下面 $pre$ 表示这个数字（前缀和）之前出现的位置。

$$f_i \gets \begin{cases}f_{i - 1} \times 2 + 1 & &  pre_i = 0\\ f_{i - 1} \times 2 - f_{pre_i - 1} &  & pre_i \neq 0\end{cases}$$

## code time
read， ww 和 flush 是我的快读快写带的函数，含义大家应该都能想到吧。

喜提最优解 23ms。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define fom(i, a) for(rl i=a; i; -- i)
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)

const ll N = 5e5 + 10, P = 998244353;

ll n, a[N], f[N];

unordered_map<ll, ll> pre;

int main()
{
    read(n); fos(i, 1, n) read(a[i]), a[i] += a[i - 1]; 
    foa(i, 1, n) f[i] = ((f[i - 1] << 1 | 1) - (pre.find(a[i]) == pre.end() ? 0 : f[pre[a[i]] - 1] + 1) + P) % P, pre[a[i]] = i; ww(f[n - 1] + 1);
    return flush(), 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

irris /hs /bx irris

刻画的过程就是：

$a,b,c,d\to a,(b+c),d$；

而对其做前缀和：

$a,a+b,a+b+c,a+b+c+d\to a,a+b+c,a+b+c+d$；

所以合并 $b,c$ 等价于在前缀和上删去 $b+c$。

我们考虑设 $f(i,j)$ 表示在前缀和数组上，前 $i$ 个数以 $j$ 结尾的子序列方案数。

显然的转移是 $f(i,j)=f(i-1,j)$。

特殊的 $j=s_i$ 时 $f(i,j)=1+\sum f(i-1,j^\prime)$。前一个选啥不重要了，我可以选现在这个。

如何优化呢，我们令 $g_i\gets \sum f(i,j)$。最后的答案显然是 $g_n$。

我们发现对于 $j\not = a_i$ 他的 $f$ 不会变，那么我们讨论 $g$ 的变化只需要看 $f(i,a_i)$ 的转移。$g_i=g_{i-1}-f(i-1,a_i)+f(i,a_i)$。

当 $a_i$ 先前没有出现过时，$f(i-1,a_i)=0$，$f(i,a_i)=1+g_{i-1}$，$g_i=2\times g_{i-1}+1$。

对于 $a_i$ 出现过，设最迟在 $p$，$f(i-1,a_i)=f(p,a_i)$。

$g_i=g_{i-1}-f(p,a_i)+f(i,a_i)=g_{i-1}-(g_{p-1}+1)+g_{i-1}+1=2\times g_i-1-g_{p-1}$。

然后直接模拟这个过程即可。

特殊的对于这个题，因为不能删完，所以答案是 $g_{n-1}+1$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int p=998244353;
map<long long, int> a;
const int N=2e5+5;
int n, i;
long long r[N], g[N];
int main()
{
	scanf("%d", &n);
	rep(i, 1, n) scanf("%lld", r+i);
	rep(i, 1, n) r[i]+=r[i-1];
//	rep(i, 1, n) printf("%lld ", r[i]);puts("");
	rep(i, 1, n-1)
	{
		if(!a.count(r[i])) g[i]=(g[i-1]<<1|1)%p;
		else g[i]=((g[i-1]<<1)-g[a[r[i]]-1]+p)%p;
		a[r[i]]=i;
//		printf("%lld\n", g[i]);
	}
	printf("%lld", g[n-1]+1);
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先，转化一下题面，对于每一次操作，相当于在原序列的前缀和数组 $s$ 中删除一个数。

$dp_i$ 表示操作 $1 \sim i$ 能得到的序列个数。

如果 $a_i$ 在 $1 \sim i - 1$ 中没有出现过，状态转移方程为 $dp_i = dp_{i - 1} \times 2 + 1$。即，在前一种状态所有可行序列的后面加上当前数，然后加上自己单独一个序列的情况。

否则，状态转移方程为 $dp_i = dp_{i - 1} \times 2 - dp_{l_{s_i} - 1}$。即，在前一种状态中所有可行序列的后面加上当前数，但是，这样会与前面 $dp_{l_{s_i}}$ 算重，所以减去前面的情况。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n;
int arr[N],dp[N];
unordered_map<int,int> l;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = arr[i - 1] + read();
	for (re int i = 1;i < n;i++){
		if (!l.count(arr[i])) dp[i] = (dp[i - 1] * 2 + 1) % mod;
		else dp[i] = ((dp[i - 1] * 2 - dp[l[arr[i]] - 1]) % mod + mod) % mod;
		l[arr[i]] = i;
	}
	printf("%lld",(dp[n - 1] + 1) % mod);
	return 0;
}
```

---

## 作者：irris (赞：0)

## Preface

不错的题阿。写个题解。

## Solution

关键在于 **刻画**「把 $\dots u\ a\ b\ v\dots$ 的形式合并为 $\dots u\ (a + b)\ v\dots$」这个过程。

**找不变量**。发现关键的一步在于序列的总和不变，所以我们联想到前缀和。

发现这就是在前缀和上删掉一个数，特殊地，最后一个数不能被删。

因为前缀和与原序列是一个一一对应的关系，所以对前缀和计数，就是前 $n - 1$ 个前缀和的本质不同子序列个数。

经典 dp 题，不多赘述，有需要的可以 [看这里的笔记](https://www.luogu.com.cn/problem/U205150)。

那么就做完了！时间复杂度 $\mathcal O(n\log n)$。

## Code

```cpp
#include <bits/stdc++.h>
namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
};
using namespace FastIO;

const int MOD = 998244353;
inline void add(int& x, int y) { (x += y) >= MOD && (x -= MOD); }
inline void del(int& x, int y) { (x -= y) < 0 && (x += MOD); }
inline int sum(int x, int y) { return (x += y) < MOD ? x : x - MOD; }

#define MAXN 300001
int g[MAXN];

std::map<long long, int> pre;
int main() {
    int N = read<int>();
    for (long long i = 1, a; i < N; ++i) {
    	g[i] = sum(g[i - 1], g[i - 1]);
		if (pre.count(a += read<int>())) del(g[i], g[pre[a] - 1]); else add(g[i], 1);
		pre[a] = i;
    }
    return print<int>(sum(g[N - 1], 1), '\n'), 0;
}
```

---

