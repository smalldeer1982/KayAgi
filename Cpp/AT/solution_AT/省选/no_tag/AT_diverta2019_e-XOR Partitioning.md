# XOR Partitioning

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019/tasks/diverta2019_e

長さ $ n $ の数列 $ a $ の *美しさ* を $ a_1\ \oplus\ a_2\ \oplus\ \cdots\ \oplus\ a_{n} $ で定義します。ここで $ \oplus $ はビットごとの排他的論理和を表します。

長さ $ N $ の数列 $ A $ が与えられます。 すぬけ君は $ A $ に $ 0 $ 個以上の仕切りを入れて、いくつかの空でない連続する部分列に分割しようとしています。

仕切りを入れる方法は $ 2^{N-1} $ 通りあります。 それらのうち、分割された数列たちの美しさが全て等しくなるものの個数を $ 10^{9}+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ <\ 2^{20} $

### Sample Explanation 1

条件を満たす分割方法は以下の $ 3 $ 通りです。$ (1),(2),(3) $ と分割したときに限り、全ての美しさが等しくなりません。 - $ (1,2,3) $ - $ (1),(2,3) $ - $ (1,2),(3) $

### Sample Explanation 3

\- 条件を満たすものの個数を $ 10^{9}+7 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 2```

### 输出

```
1```

## 样例 #3

### 输入

```
32
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
147483634```

## 样例 #4

### 输入

```
24
1 2 5 3 3 6 1 1 8 8 0 3 3 4 6 6 4 0 7 2 5 4 6 2```

### 输出

```
292```

# 题解

## 作者：灵茶山艾府 (赞：11)

以下讨论，下标从 $0$ 开始。

先求前缀异或和数组 $s$。

例如 $a=[1,3,2,1,3]$ 的前缀异或和数组 $s=[0,1,2,0,1,2]$。

假设划分位置是 $i_0,i_1,i_2,\cdots,i_m$。

划分出来的每段子数组的异或和相同，等价于 

$$
s[0]\oplus s[i_0] = s[i_0] \oplus s[i_1] = s[i_1] \oplus s[i_2] = \cdots = s[i_m]\oplus s[n]
$$

这意味着

$$
\begin{aligned}
&s[0] = s[i_1] = s[i_3] = \cdots \\
&s[i_0] = s[i_2] = s[i_4] = \cdots
\end{aligned}
$$

相当于从 $s$ 中选择一个**交替子序列**（注意第一个和最后一个数必须选）。例如 $s=[0,1,2,0,1,2]$ 中可以选 $[0,2,0,2]$，对应划分 $[1,3],[2],[1,3]$。

### 第一种情况

如果 $s[n]> 0$，这意味着交替子序列只能是 $0,s[n],0,s[n],\cdots$

那么定义：

- $f[i][0]$ 为从 $s$ 的前 $i$ 个数中选出以 $0$ 结尾的交替子序列的方案数。
- $f[i][1]$ 为从 $s$ 的前 $i$ 个数中选出以 $s[n]$ 结尾的交替子序列的方案数。

如果 $s[i] = 0$，则从 $i$ 左边的值为 $s[n]$ 的位置转移过来，即

$$
f[i][0] = f[j_1][1] + f[j_2][1] + \cdots
$$

其中 $s[j_1]$ 满足 $j_1 < i$ 且 $s[j_1] = s[n]$，其余 $j_2$ 等同理。

如果 $s[i] = s[n]$，则从 $i$ 左边的值为 $0$ 的位置转移过来，即

$$
f[i][1] = f[j_1][0] + f[j_2][0] + \cdots
$$

其中 $s[j_1]$ 满足 $j_1 < i$ 且 $s[j_1] = 0$，其余 $j_2$ 等同理。

初始值 $f[0][0] = 1$。

答案为 $f[n][1]$。

这样写每次转移是 $\mathcal{O}(n)$ 的。我们可以把 $f[j_1][0] + f[j_2][0] + \cdots$ 记作 $s_0$，把 $f[j_1][1] + f[j_2][1] + \cdots$ 记作 $s_1$。通过维护这两个变量的值，就可以做到 $\mathcal{O}(1)$ 转移了。

### 第二种情况

本题难就难在 $s[n]=0$ 的情况。

首先，我们可以选全为 $0$ 的子序列，这有 $2^{\textit{cnt}-2}$ 种方案，其中 $\textit{cnt}$ 为 $s$ 中 $0$ 的出现次数，$-2$ 是因为 $s$ 的第一个和最后一个数都是 $0$ 且必须选。

然后来讨论交替子序列的个数。

例如 $s=[0,1,2,0,1,2,0]$，此时我们不但可以选 $[0,2,0,2,0]$，还可以选 $[0,1,0,1,0]$。如果像第一种情况那样 DP，对于 $1$ 我们需要算一遍 DP，对于 $2$ 也需要算一遍 DP。可以预见，在 $0$ 比较多的情况下，总共需要 $\mathcal{O}(n^2)$ 的时间。

那要怎么做？

遇到 $0$ 的时候，「延迟」计算 DP：只在遇到非 $0$ 的时候，才去计算 DP。

例如两个 $2$ 之间有三个 $0$，那么当遍历到第二个 $2$ 的时候，才去计算关于 $s[i]=0$ 的状态转移。这三个 $0$ 的转移来源是完全一样的，可以一起计算。

那么，怎么知道两个 $2$ 之间有多少个 $0$ 呢？

方法很多，比如在遍历的同时维护 $0$ 的个数 $\textit{cnt}$，在遍历到第一个 $2$ 的时候记录一下 $\textit{cnt}$，在遍历到第二个  $2$ 的时候用当前的 $\textit{cnt}$ 减去上一次记录的 $\textit{cnt}$，就可以知道两个 $2$ 之间有多少个 $0$ 了。

请看代码：

```go
package main
import("bufio";."fmt";"os")

const mod = 1_000_000_007

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v, xor int
	// f[xor] 相当于只看前缀异或和中的 0 和 xor，求 DP
	f := [1 << 20]struct{ s0, s1, pre0 int }{}
	for i := range f {
		f[i].s0 = 1
	}
	cnt0 := 1 // 前缀异或和的第一个数是 0
	for Fscan(in, &n); n > 0; n-- {
		Fscan(in, &v)
		xor ^= v
		if xor == 0 {
			cnt0++
		} else {
			t := &f[xor]
			// f[i][0] = 一堆 f[j][1] 的和 = s1，这里直接把 f[i][0] 加到 s0 中
			t.s0 = (t.s0 + t.s1*(cnt0-t.pre0)) % mod
			// f[i][1] = 一堆 f[j][0] 的和 = s0，这里直接把 f[i][1] 加到 s1 中
			t.s1 = (t.s1 + t.s0) % mod
			t.pre0 = cnt0
		}
	}
	if xor > 0 {
		// 答案 = f[n][1] = 一堆 f[j][0] 的和 = s0
		// 注意不能写 f[xor].s1，因为前缀异或和的末尾如果有多个 xor，我们只能选一个
		Print(f[xor].s0)
	} else {
		ans := pow(2, cnt0-2) // 只选 0 的方案数
		for _, t := range f {
			// 答案 = f[n][0] = 一堆 f[j][1] 的和 = s1
			// 注意不能写 t.s0，因为前缀异或和的末尾如果有多个 0，我们只能选一个
			ans += t.s1
		}
		Print(ans % mod)
	}
}

func pow(x, n int) (res int) {
	res = 1
	for ; n > 0; n /= 2 {
		if n%2 > 0 {
			res = res * x % mod
		}
		x = x * x % mod
	}
	return
}
```



---

## 作者：cosf (赞：3)

考虑使用 dp。

我们令 $dp_{i, 0, j}$ 表示每一段的异或和为 $i$，处理到前 $j$ 个数，且前面有偶数段的方案数，$dp_{i, 1, j}$ 则为奇数段的方案数。

所以，假设当前 $a_1 \oplus a_2 \oplus \dots, a_j = s \not= 0$，则有 $dp_{s, 1, j} \gets \sum_{k = 0}^{j - 1}dp_{s, 0, k}$。

否则，则有 $dp_{i, 0, j} \gets \sum_{k=0}^{j-1}dp_{i, 1, k}, \forall 0 \lt i \lt 2^{20}$。

可以发现，第三维可以被压掉，也就是说，我们只需要 $dp_{i, 0/1}$ 的前缀和。简化版的转移方程：

$$
\begin{cases}
dp_{s, 1} \overset{+}{\gets} dp_{s, 0} & s \not=0\\
dp_{i, 0} \overset{+}{\gets} dp_{i, 1}, \forall 0 \lt i \lt 2^{20} & s = 0
\end{cases}
$$

可以发现，第二个式子比较耗时，所以我们只需要统计一下进行了多少次第二个式子，然后记录一下对于每一个 $i$，$dp_{i, 1}$ 上一次更新的时候已经进行了多少次第二个式子，相减就是中间的操作次数。

具体而言，我们令 $g_j$ 表示操作到 $j$ 时进行第二个式子的次数，$h_i$ 表示上一次进行第一个式子时的 $g_j$，则我们只需要 $dp_{i, 0} \overset{+}{\gets} (g_j - h_i)dp_{i, 1}$ 就可以还原出这些操作了。

考虑答案。如果最后的 $s$ 的值不是 $0$，则每一段的异或和都要是 $s$，答案即 $dp_{s, 0}$。否则，答案即 $dp_0 + \sum_{k=1}^{2^{20} - 1}dp_{k, 1}$。这里的 $dp_0$ 是特殊处理的异或和为 $0$ 的情况。

$dp_0$ 算起来非常简单。它的值其实就是 $2^{g_n - 1}$。

时间复杂度 $O(n)$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 1049500
#define MOD 1000000007

using ll = long long;

ll dp[MAXN][3];

int gp = 0;

int n;

int v[MAXN];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }
    for (int i = 1; i < MAXN; i++)
    {
        dp[i][0] = 1;
    }
    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        s ^= v[i];
        if (s == 0)
        {
            gp++;
        }
        else
        {
            int cp = gp - dp[s][2];
            dp[s][0] = (dp[s][0] + dp[s][1] * cp % MOD) % MOD;
            dp[s][1] = (dp[s][1] + dp[s][0]) % MOD;
            dp[s][2] = gp;
        }
    }
    if (s != 0)
    {
        cout << (dp[s][0] + dp[s][1] * (gp - dp[s][2]) % MOD) % MOD << endl;
        return 0;
    }
    else
    {
        ll res = 500000004; // 懒得写快速幂了
        for (int i = 1; i <= n; i++)
        {
            s ^= v[i];
            if (s == 0)
            {
                res = res * 2 % MOD;
            }
        }
        for (int i = 1; i < MAXN; i++)
        {
            res = (res + dp[i][1]) % MOD;
        }
        cout << res << endl;
        return 0;
    }
}

```

---

## 作者：t162 (赞：3)

注意到以下几点：

1. 对于所有段，它们的异或和就是所有数的异或和。
2. 由于所有段的异或和为一个定值，设它为 $d$，并设所有数的异或和为 $s$。设分成了 $x$ 段，则有 $s=[x\bmod 2 = 1]d$。

分类讨论。设 $A_{1\dots N}$ 的前缀异或和数组为 $s_{1\dots N}$。

若 $s\neq 0$，那么就表明 $d=s$，同时 $x$ 是奇数。考虑所有 $x$ 段的最后一个数的位置为 $p_{1\dots x}$，那么必定有 $s_{p_{i}}=[i\bmod 2=1]d$。因此问题转化为在 $s_{1\dots N}$ 中选择奇数个位置，且最后一个数必须选，满足奇数位置上的数为 $d$，偶数位置上的数为 $0$，求方案数。设 $f(i,0/1)$ 表示前 $i$ 个位置，选了 偶数 / 奇数 个位置时的方案数。转移：
$$
f(i,0)=\begin{cases}f(i-1,0)&a_i\neq 0\\f(i-1,0)+f(i-1,1)&a_i=0\end{cases}
$$

$$
f(i,1)=\begin{cases}f(i-1,1)&a_i\neq d\\f(i-1,1)+f(i-1,0)&a_i=d\end{cases}
$$



否则若 $s\neq 0$，那么就表明 $d$ 的值不一定确定，同时 $x$ 的奇偶性也未知。假设 $x$ 是奇数，这表明 $d=0$，做法同上。然后考虑 $x$ 是偶数的情况。

同上，问题为在 $s_{1\dots N}$ 中选择偶数个位置，结尾必须选，满足奇数位置上的数为 $d$，偶数位置上的数为 $0$。直接枚举 $d$ 复杂度显然是爆炸的。但是注意到上面的转移方程中，真正会产生转移的位置只有 $a_i=0$ 或 $a_i=d$ 两种。

因此预处理出 $a_i=d$ 的位置，然后对 $a_i=0$ 的位置进行一次前缀和，就可以快速转移了。

时间复杂度 $\mathcal O(N)$。

---

## 作者：robinyqc (赞：1)

之前在 NOIP 赛前最后一场模拟赛做到了这个题，今天在机缘巧合下又一次遇到了这个题，太神奇了。

### 题意简述

给定一个长为 $n$ 的序列 $a$，求将 $a$ 划分成若干个子段，并且满足每个子段的异或和都相等的方案数，对 $10^9 + 7$ 取模。$n\leq 5\times 10^5$。

### 解题思路

设 $b$ 为 $a$ 的前缀异或和。又设每个子段的异或和都为 $x$。那么，对于一种合法的划分方案：

+ 第奇数个子段的右端点 $p$ 满足 $b_p = x$；
+ 第偶数个子段的右端点 $p$ 满足 $b_p = 0$；

所以，端点的前缀异或和是形如 $\langle x, 0, x, 0\dots\rangle$ 出现的。且若 $b_n\neq 0$，$x$ 必须等于 $b_n$；若 $b_n = 0$，$x$ 无特殊限制。

若 $x = 0$，要求所有端点等于 $0$。随便选若干个 $b_i = 0$ 的端点即可。那么方案数就是 $2^{c - 1}$（$b_n$ 必须选，所以要减一），其中 $c = \sum[b_i = 0]$。接下来只需求 $x\neq 0$ 的情况。

至此我们可以设计一个简单的 dp。设 $f_i$ 表示，当 $x \neq 0$ 时，以 $i$ 为某奇数段右端点的划分方案数。我们只需要枚举上一个奇数段右端点，然后选中间一个 $b_i = 0$ 的点作为偶数段分割点。因此有：

$$
f_i = 1 + \sum_{j = 1}^{i - 1} [b_j = b_i]f_j\sum_{k = j + 1}^{i - 1}[b_i = 0]
$$

直接做复杂度是 $O(n^2)$ 的，不行。改写一下式子，设 $t_i = \sum_{k = 1}^{i} [b_k = 0]$，那么：

$$
\begin{aligned}
f_i &= 1 + \sum_{j = 1}^{i - 1} [b_j = b_i]f_j(t_{i - 1} - t_j)\\
&= 1 + t_{i - 1}\left(\sum_{j = 1}^{i - 1} [b_j = b_i]f_j\right) - \sum_{j = 1}^{i - 1} [b_j = b_i]f_j t_j
\end{aligned}
$$

此时 $f_i$ 和 $f_j$ 分开了，剩下的就简单了。假设当前枚举到 $i$，只需对所有 $x$ 维护 $k_x = \sum\limits_{j = 1}^{i - 1} [b_j = x]f_j$，$g_x = \sum\limits_{j = 1}^{i - 1} [b_j = x]f_j t_j$ 即可。显然每次只有 $k_{b_i}$ 和 $g_{b_i}$ 发生了改变。所以计算 $f_i$ 的复杂度变为 $O(1)$。

最后算下答案：当 $b_n = 0$ 时，总共有偶数段，枚举最后一个奇数段，加上 $x = 0$ 的情况即可得到答案：$2^{c - 1} + \sum\limits_{i = 1}^n{[b_i \neq 0]f_i}$；否则，答案为 $f_n$。

本题的值域为 $2^{20}$ 可以开数组维护 $k, g$，所以时间复杂度 $O(n)$。若值域很大，可以离散化计算，区别不大。

### 代码实现


```rust
use ac_library::ModInt1000000007 as Mint;
use proconio::input;

fn mint_vec(len: usize) -> Vec<Mint>
{
    let mut res = Vec::new();
    res.resize(len, Mint::new(0));
    res
}

fn main()
{
    input! {
        n: usize,
        mut a: [usize; n]
    }
    for i in 1..n {
        a[i] ^= a[i - 1];
    }
    let mut f = mint_vec(n);
    let mut k = mint_vec(1 << 20);
    let mut b = mint_vec(1 << 20);
    let mut t = Mint::new(0);
    for i in 0..n {
        if a[i] == 0 {
            t += 1;
        }
        let p = a[i];
        f[i] = t * k[p] + b[p] + 1;
        b[p] -= t * f[i];
        k[p] += f[i];
    }
    if a[n - 1] == 0 {
        let mut ans = Mint::new(1);
        for _ in 1..t.val() {
            ans = ans * 2;
        }
        for i in 0..n {
            if a[i] != 0 {
                ans += f[i];
            }
        }
        println!("{}", ans.val());
    }
    else {
        println!("{}", f[n - 1]);
    }
}
```

---

## 作者：Reunite (赞：0)

简单题。

先把 $a_i$ 替换为其异或前缀和，则合法的分段形式一定为 $x,0,x,0\cdots$，其中结尾是 $0/x$ 是确定的，分两种情况：

- $a_n\ne 0$，则 $x$ 确定，设 $f_i$ 为 $a_i=x$ 且以 $i$ 结束一个 $x$ 的段的方案数，$s_i$ 为 $f_i$ 前缀和，$ss$ 为之前所有 $a_j=0$ 的 $s_j$ 的和，显然有 $f_i=ss+1$，顺着扫一遍即可。

- $a_n=0$，此时 $x$ 位置，暴力枚举之，用 vector 存一下 $x$ 的所有出现，考虑继续做上面的 dp，但是会被很多个 $0$ 的卡，你注意到两个相邻的 $x$ 之间的每个 $0$ 对 $ss$ 的改变都是一样的，直接乘一下就好了。

总复杂度 $O(n+\min(V,n\log n))$，实现时根本不需要 $f_i$，直接两个变量维护一下就好。

---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define int long long
#define mod 1000000007
using namespace std;

int n,V;
int a[500005];
int b[500005];
vector <int> g[2000005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

signed main(){
	in(n);
	for(int i=1;i<=n;i++){
		in(a[i]);
		a[i]^=a[i-1];
		b[i]=b[i-1]+(a[i]==0);
		g[a[i]].emplace_back(i);
		V=max(V,a[i]);
	}
	if(a[n]){
		int s=0,ss=0,sss=0;
		for(int i=1;i<=n;i++){
			if(a[i]==0) (ss+=s)%=mod;
			if(a[i]==a[n]) (s+=ss+1)%=mod;
			if(i==n-1) sss=s;
		}
		printf("%lld\n",(s-sss+mod)%mod);
		return 0;
	}
	int c=g[0].size()-1,x=1;
	for(int i=1;i<=c;i++) (x*=2)%=mod;
	int ans=x;
	for(int i=1;i<=V;i++){
		if(g[i].empty()) continue;
		int sz=g[i].size();
		int s=1,ss=0;
		for(int j=1;j<sz;j++){
			(ss+=s*(b[g[i][j]]-b[g[i][j-1]]))%=mod;
			(s+=ss+1)%=mod;
		}
		(ans+=s)%=mod;
	}
	printf("%lld\n",ans);

	return 0;
}

```

---

