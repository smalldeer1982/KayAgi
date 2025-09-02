# LEGOndary Grandmaster

## 题目描述

After getting bored by playing with crayons, you decided to switch to Legos! Today, you're working with a long strip, with height $ 1 $ and length $ n $ , some positions of which are occupied by $ 1 $ by $ 1 $ Lego pieces.

In one second, you can either remove two adjacent Lego pieces from the strip (if both are present), or add two Lego pieces to adjacent positions (if both are absent). You can only add or remove Lego's at two adjacent positions at the same time, as otherwise your chubby fingers run into precision issues.

You want to know exactly how much time you'll spend playing with Legos. You value efficiency, so given some starting state and some ending state, you'll always spend the least number of seconds to transform the starting state into the ending state. If it's impossible to transform the starting state into the ending state, you just skip it (so you spend $ 0 $ seconds).

The issue is that, for some positions, you don't remember whether there were Legos there or not (in either the starting state, the ending state, or both). Over all pairs of (starting state, ending state) that are consistent with your memory, find the total amount of time it will take to transform the starting state to the ending state. Print this value modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case, $ 00 $ is the only possible starting state, and $ 11 $ is the only possible ending state. It takes exactly one operation to change $ 00 $ to $ 11 $ .

For the second test case, some of the possible starting and ending state pairs are:

- $ (000, 011) $ — takes $ 1 $ operation.
- $ (001, 100) $ — takes $ 2 $ operations.
- $ (010, 000) $ — takes $ 0 $ operations, as it's impossible to achieve the ending state.

## 样例 #1

### 输入

```
6
2
00
11
3
???
???
3
??1
0?0
4
??0?
??11
5
?????
0??1?
10
?01??01?1?
??100?1???```

### 输出

```
1
16
1
14
101
1674```

# 题解

## 作者：伟大的王夫子 (赞：24)

这题于看似简单的思路与代码中，蕴含着好几个美妙的技巧。下面就由我来一一解说。如果理解了这些小技巧，不仅能轻松理解这题思路，还能在做到类似题目时触类旁通，举一反三。

技巧一：操作的转化

原题中的取反操作要求两个连续的数都相同，那么我们可以将奇数位上的数取反，然后转化为交换操作。交换操作有一个特点，就是可以保证交换的两个数不相等，对应原字符串中就是两个数相等，这样很巧妙的满足了这个条件。

技巧二：次数的计算

首先，很明显推到这里，少了一个限制，这种题目的计算公式已经不会很复杂了。设 $x$ 数组中存了第一个串中 1 出现的下标，$y$ 数组中存了第二个串中 1 出现的下标，那么次数就是 $\sum |x_i-y_i|$。但这样计算起来就不是很方便。接下来可以利用一个套路的结论。设 $a_i$ 表示第一个串中前 $i$ 个数 1 的个数，$b_i$ 表示第二个串中前 $i$ 个数 1 的个数，次数就是 $\sum |a_i-b_i|$。因为你每交换两个数，最多只能使一个前缀和发生变化。

技巧三：利用贡献法。

讲到这里，我想最后一步也十分简单了。对于每个 $i$，我们枚举 $j = a_i-b_i$，计算这个 $j$ 的贡献。具体的，可以令 $pre_{i, j}$ 表示前 $i$ 个数使 $a_i - b_i = j $ 的方案数， $suf_{i, j}$ 则表示相应的后缀的方案，那么 $(i,j)$ 的贡献就是 $pre_{i, j} \times suf_{i+1,-j} \times |j|$。并且经过转化之后，这个转移也变得十分简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7, N = 2005;
typedef long long LL;
int n;
LL suf[N][N << 1], pre[N][N << 1];
char a[N], b[N];
bool equal(char a, int b) {
	return a == '?' || a == b + 48;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%s%s", &n, a + 1, b + 1);
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= 2 * n; ++j)
				suf[i][j] = pre[i][j] = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] != '?' && (i & 1)) a[i] = (a[i] ^ 48 ^ 1) + 48;
		for (int i = 1; i <= n; ++i)
			if (b[i] != '?' && (i & 1)) b[i] = (b[i] ^ 48 ^ 1) + 48;
		pre[0][n] = 1;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= 2 * n; ++j)
				for (int k = 0; k <= 1; ++k)
					for (int p = 0; p <= 1; ++p) 
						if (equal(a[i + 1], k) && equal(b[i + 1], p) && j + k - p >= 0) (pre[i + 1][j + k - p] += pre[i][j]) %= P;
		suf[n + 1][n] = 1;
		for (int i = n + 1; i >= 2; --i)
			for (int j = 0; j <= 2 * n; ++j)
				for (int k = 0; k <= 1; ++k)
					for (int p = 0; p <= 1; ++p) 
						if (equal(a[i - 1], k) && equal(b[i - 1], p) && j + k - p >= 0) (suf[i - 1][j + k - p] += suf[i][j]) %= P;
		LL ans = 0;
		for (int i = 1; i < n; ++i)
			for (int j = -n; j <= n; ++j)
				(ans += pre[i][j + n] * suf[i + 1][n - j] % P * abs(j) % P) %= P;
		printf("%lld\n", ans);
	}
}
```

---

## 作者：Rainbow_qwq (赞：21)

$O(n)$ 做法，目前 CF 最优解。

首先，考虑如何计算两个串的答案。

把奇数位置的值取反，那每次操作相当于 $01\to10$ 或 $10\to 01$。于是当两个串 $1$ 的个数相等时可以达成。

可以看作若干个 $1$ 在一条链上移动到新的位置。答案为距离之和，把移动贡献均摊到每条边上，那每一条边的贡献就是  两个串$[1,i]$ 中的 $1$ 个数的差值。

枚举 $[1,i]$ 中两个串 `?` 处填写 $0$ 的差值个数，那另一边 $[i+1,n]$ 中 `?` 处填写 $0$ 的差值个数确定。

如果确定了一边的 `?` 处填写 $0$ 的差值个数，那枚举第一个串中的 $0$ 个数，一边的答案形如：

$$\sum_j\binom{A}{j}\binom{B}{j+d}$$
$$\sum_j\binom{A}{j}\binom{B}{B-j-d}$$

可以用范德蒙德卷积，化成一个组合数：

$$\binom{A+B}{B-d}$$

另一边也相同，方案数就是两边乘起来。于是可以得到 $O(n^2)$ 的做法。

```cpp
// s[i]='0/1' -> s[i]=0/1.
// s[i]='?' -> s[i]=2.
For(i,0,2) as[i]=at[i]=bs[i]=bt[i]=0;
For(i,1,n) ++bs[s[i]],++bt[t[i]];
modint res=0;
For(i,1,n-1){
	--bs[s[i]],--bt[t[i]];
	++as[s[i]],++at[t[i]];
	For(j,-n,n)
		res+=C(as[2]+at[2],at[2]-j-as[0]+at[0])
			*C(bs[2]+bt[2],bt[2]+j-bs[0]+bt[0])
			*(j>0?j:-j);
}
```

观察这个式子，发现我们每次要求的形如：

$$\binom{A}{A_2-j}\binom{B}{B_2+j}|j|$$

要求这个答案 $n$ 次，并且每次的 $A+B,A_2+B_2$ 为定值。

这个式子很像范德蒙德卷积，考虑把绝对值先拆成 $|j|=(-j)+(2j)[j\ge 0]$.

第一部分要求 $\binom{A}{A_2-j}\binom{B}{B_2+j}j$. 可以变成：

$$\binom{A}{A_2-j}\binom{B}{B_2+j}(B_2+j) - \binom{A}{A_2-j}\binom{B}{B_2+j}B_2$$

组合数收缩公式：

$$\binom{A}{A_2-j}\binom{B-1}{B_2+j-1}B - \binom{A}{A_2-j}\binom{B}{B_2+j}B_2$$

再用范德蒙德卷积：

$$\binom{A+B-1}{A_2+B_2-1}B-\binom{A+B}{A_2+B_2}B_2$$

于是可以单次 $O(1)$。

第二部分要求 $\binom{A}{A_2-j}\binom{B}{B_2+j}j[j\ge 0]$.

用相同的方法变成：

$$\binom{A}{A_2-j}\binom{B-1}{B_2+j-1}B[j\ge 0] - \binom{A}{A_2-j}\binom{B}{B_2+j}B_2[j\ge 0]$$

两部分是相同的，只考虑其中一部分，那就是要求：

$$\binom{A}{A_2-j}\binom{B}{B_2+j}[j\ge 0]$$

$$\binom{A}{j}\binom{B}{A_2+B_2-j}[j\le A_2]$$

由于 **每次的 $A+B,A_2+B_2$ 为定值**，设 $S_1 = A+B,S_2 = A_2+B_2$。

考虑其组合意义，相当于有 $S_1$ 个球，其中要放 $S_2$ 个黑球，并且要求前 $A$ 个球中只有 $\le A_2$ 个黑球的方案数。

考虑在这条链上，从 $i\to i+1$ 的时候，$A$ 和 $A_2$ 都只会有 $O(1)$ 的变化。如果能 $O(1)$ 移动 $A±1,A_2±1$ 并且实时维护答案，那就能做了。

如果 $A_2\to A_2+1$，答案只需要加上新的贡献 $\binom{A}{A_2+1}\binom{S_1-A}{S_2-(A_2+1)}$。

如果 $A\to A+1$，答案会减少。再考虑其组合意义，减少的量就是“第 $A_2+1$ 个黑球放在 $A+1$ 位置”的方案数。于是答案只需要减去 $\binom{A}{A_2}\binom{S_1-A-1}{S_2-A_2-1}$.

于是我们解决了 $O(1)$ 移动端点的问题，整个问题可以 $O(n)$ 解决。

[Submission](https://codeforces.com/contest/1615/submission/221393180)

~~顺便吐槽一句，为什么其他题解都用 dp 而不是组合数啊。~~

---

## 作者：tzc_wk (赞：7)

> 摘自我的 [杂题选做Ⅴ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp5.html) 中的第 $107$ 题。

首先碰到这样的问题，我们肯定要考虑怎样快速对于两个 01 串 $s,t$，计算从 $s$ 到 $t$ 的最少步数。我们考虑这样一个套路化的操作：对于下标为偶数的位置，我们自动将两个字符串上对应的位置都取反，即 $0$ 变 $1$，$1$ 变 $0$，我们记操作后得到的字符串为 $s’,t’$。那么不难发现，将原字符串上两个相邻且值相同的位置取反，等价于交换这两个字符，而对于相邻且值不同的位置，交换它们则等价于什么也没有干，因此我们可以将操作描述为，交换 $s’$ 中两个相邻的字符，问最少需要多少次操作才能将 $s’$ 变为 $t’$。

很显然，$s’$ 可以变成 $t’$ 的充要条件是 $s’,t’$ 中 $1$ 的个数相同。考虑怎样计算步数。对于一般序列，计算一个序列 $a$ 变为 $b$ 的最少交换次数需要计算逆序对进而求解，不过对于 01 序列而言有一个更简便的解法：我们设 $s’$ 中第 $i$ 个 $1$ 的下标为 $x_i$，$t’$ 中第 $i$ 个 $1$ 的下标为 $y_i$，那么最少交换次数即为 $\sum\limits_{i=1}^c|x_i-y_i|$，其中 $c$ 为 $s’,t’$ 中 $1$ 的个数。这个式子看起来已经很简便了，但是应用于此题而言还不足以在 $\mathcal O(n^2)$ 的时间复杂度内求解，考虑进一步化简。我们设 $a_i,b_i$ 分别表示 $s’[1…i]$ 中 $1$ 的个数以及 $t’[1…i]$ 中 $1$ 的个数。那么答案可以进一步写作 $\sum\limits_{i=1}^n|a_i-b_i|$。因为由于一次操作至多使 $|a_i-b_i|$ 减少 $1$，因此最少需要 $|a_i-b_i|$ 次操作才能使得 $a_i=b_i$，因此最少操作次数的下界就是 $\sum\limits_{i=1}^n|a_i-b_i|$，而显然我们可以通过先通过交换使 $s’_1=t’_1$，再使 $s’_2=t’_2$，依次类推……来达到这个下界。

发现这个结论之后就很好 DP 了，记 $pre_{i,j}$ 表示现在以及确定了 $s,t$ 前 $i$ 位的值，$a_i-b_i=j$ 的方案数，$suf_{i,j}$ 表示现在已经确定了 $s,t$ 后 $n-i+1$ 位的值，后 $n-i+1$ 位中，$s’$ 中 $1$ 的个数与 $t’$ 中 $1$ 的个数之差为 $j$ 的方案数，那么答案即为 $\sum\limits_{i=1}^n\sum\limits_{j=-n}^npre_{i,j}·suf_{i+1,-j}·|j|$。

时间复杂度 $n^2$。

```cpp
const int MAXN = 2000;
const int DLT = 2003;
const int MOD = 1e9 + 7;
int n; char s[MAXN + 5], t[MAXN + 5];
int pre[MAXN + 5][DLT * 2 + 5], suf[MAXN + 5][DLT * 2 + 5];
bool match(char c, int d) {return (c == '?' || c - '0' == d);}
void add(int &x, int v) {((x += v) >= MOD) && (x -= MOD);}
void solve() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for (int i = 0; i <= n + 1; i++) for (int j = 0; j < DLT * 2 + 5; j++)
		pre[i][j] = suf[i][j] = 0;
	pre[0][DLT] = suf[n + 1][DLT] = 1;
	for (int i = 0; i < n; i++) for (int j = -i; j <= i; j++) if (pre[i][j + DLT])
		for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++)
			if (match(s[i + 1], x ^ (i & 1)) && match(t[i + 1], y ^ (i & 1))) {
				add(pre[i + 1][j + x - y + DLT], pre[i][j + DLT]);
			}
	for (int i = n + 1; i > 1; i--) for (int j = i - n - 1; j <= n + 1 - i; j++) if (suf[i][j + DLT])
		for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++)
			if (match(s[i - 1], x ^ (i & 1)) && match(t[i - 1], y ^ (i & 1))) {
				add(suf[i - 1][j + x - y + DLT], suf[i][j + DLT]);
			}
	int res = 0;
	for (int i = 1; i <= n; i++) for (int j = -i; j <= i; j++)
		res = (res + 1ll * pre[i][j + DLT] * abs(j) % MOD * suf[i + 1][-j + DLT]) % MOD;
	printf("%d\n", res);
}
int main() {
	int qu; scanf("%d", &qu);
	while (qu--) solve();
	return 0;
}
```

---

## 作者：A1443356159 (赞：7)

# CF1615F 题解

题目描述：对于一个 0/1 串，你有一种操作，每次可以把相邻的两个 1 变成 0，相邻两个 0 变成 1。给定 $S,T$ 的一些位置，求 $S,T$ 的所以可能中，把 $S$ 变为 $T$ 的最小操作数之和。特别的，若不能变成，操作数为 0。

主要是要知道一个关键的转化。

若已知 $S,T$ 怎么求最小？先把 $S,T$  的偶数位置 0/1 翻转，原操作等价于交换两个相邻位置的值。

可能会疑惑操作对应到原串中不合法，但是观察发现该情况对应到构造串是交换两个相同的数，这是没有意义的。

记 $x_i$ 表示 $S$ 中第 $i$ 个 1 的位置，$y_i$ 表示 $T$ 中第 $i$ 个 1 的位置，$Ans=\sum |x_i-y_i|$，1 的个数不等答案为 0。可以根据这个 $dp$。

或者，设 $prex_i$ 表示前 $i$ 个位置的 1 的个数，$prey_i$ 同理，$Ans=\sum|prex_i-prey_i|$。设 $f_{i,j}$ 表示考虑到前 $i$ 个位置，$prex_i-prey_i=j$ 的方案，设 $g_{i,j}$ 表示答案，容易转移。

```cpp
void work() {
	scanf("%lld%s%s",&n,S+1,T+1);
	for(int i=2;i<=n;i+=2) {
		if(S[i]=='1')S[i]='0';
		else if(S[i]=='0')S[i]='1';
		if(T[i]=='1')T[i]='0';
		else if(T[i]=='0')T[i]='1';
	}
	f[0][N]=1;
	for(int i=1;i<=n;++i) {
		memset(f[i],0,sizeof(f[i]));
		memset(g[i],0,sizeof(g[i]));
		for(int j=-n;j<=n;++j)
			for(int x=0;x<2;++x)
				for(int y=0;y<2;++y) {
					if(S[i]!='?'&&S[i]!='0'+x)continue; 
					if(T[i]!='?'&&T[i]!='0'+y)continue;
					int nw=j+x-y;
					(f[i][nw+N]+=f[i-1][j+N])%=P;
					(g[i][nw+N]+=abs(j)*f[i-1][j+N]+g[i-1][j+N])%=P;
				}
	}
	printf("%lld\n",g[n][N]);
}
```



---

## 作者：7KByte (赞：6)

将两个串的奇数位取反，那么一次操作相当于邻项交换，我们记录 $a_i$ 表示 $s$ 中第 $i$ 个 $1$ 的位置，$b_i$ 表示 $t$ 中第 $i$ 个 $1$ 的位置，那么最小操作数就是 $\sum|a_i  - b_i|$。

考虑 DP，这里提供一个不同的 DP 方法。

我们定义状态 $g_{i,j}$ 表示 $s_i = t_j = 1$，且 $s_i$ 和 $t_j$ 匹配的方案数，$f_{i,j}$ 则表示所有方案的距离之和。

那么我们可以枚举 $u,v$ 转移，$g_{i,j} = \sum\limits_{u,v}g_{u,v}$，$f_{i,j} = g_{i,j} + \sum\limits_{u,v}f_{u,v}$，其中需要满足 $s$ 串的 $u,i$ 之间没有 $1$，$t$ 串的 $v,j$ 之间没有 $1$，因为我们枚举的是上一对匹配的 $1$。

不难发现每次转移是一个子矩阵和，二维前缀和优化即可，时间复杂度 $\mathcal{O}(N^2)$。

```cpp
#define N 2005
int n, f[N][N], g[N][N], s[N][N], t[N][N], p[N], q[N]; char a[N], b[N];
int w(int op,int x,int y,int X,int Y){
	if(1 == op){
		if(!x && !y)return s[X][Y];
		if(!x)return s[X][Y] - s[X][y - 1];
		if(!y)return s[X][Y] - s[x - 1][Y];
		return s[X][Y] - s[x - 1][Y] - s[X][y - 1] + s[x - 1][y - 1];
	}
	if(!x && !y)return t[X][Y];
	if(!x)return t[X][Y] - t[X][y - 1];
	if(!y)return t[X][Y] - t[x - 1][Y];
	return t[X][Y] - t[x - 1][Y] - t[X][y - 1] + t[x - 1][y - 1];
}
void solve(){
	read(n);
	scanf("%s%s", a + 1, b + 1);
	rp(i, n)if(i & 1){
		if(a[i] != '?')a[i] ^= 1;
		if(b[i] != '?')b[i] ^= 1;
	}
	++n, a[n] = b[n] = '1';
	rp(i, n){
		if(a[i - 1] == '1')p[i] = i - 1; else p[i] = p[i - 1];
		if(b[i - 1] == '1')q[i] = i - 1; else q[i] = q[i - 1];
	}
	rp(i, n)rp(j, n){
		f[i][j] = g[i][j] = 0;
		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1];
		ad(s[i][j], 0), su(s[i][j], 0), ad(t[i][j], 0), su(t[i][j], 0);
		if(a[i] != '0' && b[j] != '0'){
			ad(g[i][j], (w(0, p[i], q[j], i - 1, j - 1) % P + P) % P), ad(f[i][j], (w(1, p[i], q[j], i - 1, j - 1) % P + P) % P);
			ad(f[i][j], g[i][j] * 1LL * abs(i - j) % P);
		}
		ad(s[i][j], f[i][j]), ad(t[i][j], g[i][j]);
	}
	printf("%d\n", f[n][n]);
}
int main() {
	g[0][0] = 1; 
	rep(i, 0, N - 5)t[0][i] = t[i][0] = 1;
	int T; read(T);
	while(T--)solve();
	return 0; 
}
```

---

## 作者：Alex_Wei (赞：5)

> D. [CF1615F LEGOndary Grandmaster](https://www.luogu.com.cn/problem/CF1615F) *2800

考虑对于确定的 $s, t$ 如何求解最小移动步数。

使用经典套路，将所有偶数位或奇数位的值异或 $1$，操作转化为交换相邻的 $0$ 和 $1$（本题最核心的地方就在于对操作的转化，剩下来就不难想了）。

若转化后 $s, t$ 中 $01$ 个数不等，无解。否则最小移动步数即 $s, t$ 对应 $1$ 下标之差的和。

那么就简单了。应用在每个间隔处统计答案的技巧，设 $f_{i, j}$ 表示考虑前缀 $i$，当前 $s$ 中 $1$ 的个数比 $t$ 中 $1$ 的个数多 $j$ 的方案数，$g_{i, j}$ 表示所有这样的方案的答案之和。

$f_{i, j}$ 转移枚举 $s$ 和 $t$ 下一位为 $0$ 或 $1$ 转移到 $f_{i + 1, j - 1 / j / j + 1}$。

$g_{i, j}$ 转移同理，加上 $f_{i, j}|j|$ 作为贡献，因为我们在每个间隔（$i\to i + 1$ 的过程）处统计答案。

时间复杂度平方。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
const int mod = 1e9 + 7;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, f[N][N << 1], g[N][N << 1];
char s[N], t[N];
void solve() {
	cin >> n >> s + 1 >> t + 1, g[0][N] = 1;
	for(int i = 1; i <= n; i++) memset(f[i], 0, sizeof(f[i])), memset(g[i], 0, sizeof(g[i]));
	for(int i = 2; i <= n; i += 2) if(s[i] != '?') s[i] ^= 1;
	for(int i = 2; i <= n; i += 2) if(t[i] != '?') t[i] ^= 1;
	for(int i = 0; i < n; i++)
		for(int j = -i; j <= i; j++) {
			for(int k = 0; k < 2; k++)
				for(int l = 0; l < 2; l++) {
					if(s[i + 1] != '?' && (k ^ s[i + 1] ^ 48)) continue;
					if(t[i + 1] != '?' && (l ^ t[i + 1] ^ 48)) continue;
					int p = j + k - l;
					add(g[i + 1][p + N], g[i][j + N]);
					add(f[i + 1][p + N], (1ll * g[i][j + N] * abs(j) + f[i][j + N]) % mod);
				}
		}
	cout << f[n][N] << endl;
}
int main() {
	// freopen("1.in", "r", stdin);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：forest114514 (赞：4)

这题出现在了我们联考里面，然后出题人草八牛大佬放了一个树上版本的这题，所以就随便讲一下树上版本 $O(n\log n)$ 链上即本题 $O(n)$ 的做法。

首先第一步转化因为操作的同色块黑白染色不同，所以就反转一下就变成每次交换黑白点问两个东西同构的最小次数之和，显然只要黑点数量相同就能移动在一起，考虑每条边的贡献就是子树内黑点的差的绝对值。


然后考虑最后设黑点为 $1$，白点为 $0$，子树的贡献就是 $|z_i=s_i-t_i|$。

设 $A$ 为 $a$ 的问号数量，$B$ 为 $b$ 的问号数量，$C$ 为非问号的差值，$u$ 子树 $a$ 有 $x$ 个问号，$b$ 有 $y$ 个，非问号差值为 $z$，$u$ 答案就是：
$$
\begin{aligned}
f(u)&=\sum\limits_{i=0}^{x}\sum\limits_{j=0}^{y}\sum\limits_{k=0}^{A-x}\sum\limits_{l=0}^{B-y}[C+i-j+k-l=0]\binom{x}{i}\binom{y}{j}\binom{A-x}{k}\binom{B-y}{l}|z+i-j|\\
&=\sum\limits_{i-j=p=-y}^{x}\sum\limits_{k-l=q=y-B}^{A-x}[C+p+q=0]|z+p|\sum\limits_{i=0}^{x}\binom{x}{i}\binom{y}{i-p}\sum\limits_{k=0}^{A-x}\binom{A-x}{k}\binom{B-y}{k-q}\\
&=\sum\limits_{p=-y}^{x}\sum\limits_{q=y-B}^{A-x}[C+p+q=0]|z+p|\binom{x+y}{x-p}\binom{A+B-x-y}{A-x-q}\\
&= \sum\limits_{p=-y}^{x}\binom{x+y}{x-p}\binom{A+B-x-y}{A+C-x+p}|z+p|\\
&= \sum\limits_{p=0}^{x+y}\binom{x+y}{p}\binom{A+B-x-y}{A+C-p}|z+x-p|
\end{aligned}
$$
 设 $F(X,Y)=\sum\limits_{p=0}^{X}\binom{X}{p}\binom{A+B-X}{A+C-p}|Y-p|$

考虑 $O(1)$ 移动 $F(X,Y)\to F(X+1,Y),F(X,Y\pm 1)$，这样一条重链的答案变化是轻子树的 $siz$ 的和是 $O(n\log n)$ 级别的。

拆绝对值可以得到 $F(X,Y)=\sum\limits_{p=0}^{X}\binom{X}{p}\binom{A+B-X}{A+C-p}(p-Y)+2\sum\limits_{p=0}^{\min(X,Y)}\binom{X}{p}\binom{A+B-X}{A+C-p}(Y-p)$。

注意到 $\sum\limits_{p=0}^{X}\binom{X}{p}\binom{A+B-X}{A+C-p}(p-Y)=-Y\binom{A+B}{A+C}+X\sum\limits_{p-1=0}^{X-1}\binom{X-1}{p-1}\binom{A+B-X}{A+C-p}=-Y\binom{A+B}{A+C}+X\binom{A+B-1}{A+C-1}$ 。

只用算右边的部分 $G(X,Y)=\sum\limits_{p=0}^{\min(X,Y)}\binom{X}{p}\binom{A+B-X}{A+C-p}(Y-p)$，首先上界 $\min(X,Y)$ 写成 $Y$ 是对的因为 $p>X,\binom{X}{p}=0$，所以 $G(X,Y)=\sum\limits_{p=0}^{Y}\binom{X}{p}\binom{A+B-X}{A+C-p}(Y-p)=Y\sum\limits_{p=0}^{Y}\binom{X}{p}\binom{A+B-X}{A+C-p}-X\sum\limits_{p-1=0}^{Y-1}\binom{X-1}{p-1}\binom{A+B-1-(X-1)}{A+C-1-(p-1)}$。

$Y$ 的变化，直接加减即可，不讲。

$X\to X+1$， 设 $H(a,b,X,Y)=\sum\limits_{p=0}^{Y}\binom{X}{p}\binom{a-X}{b-p}$，有一种组合意义的理解方式但是~~版权原因不放了~~，组合意义天地灭，代数推导保平安，我们纯代数推导。


$$
\begin{aligned}
H(a,b,X+1,Y)&=\sum\limits_{p=0}^{Y}\binom{X+1}{p}\binom{a-X-1}{b-p}\\
&=\sum\limits_{p=0}^{Y}\left[\binom{X}{p}+\binom{X}{p-1}\right]\left[\binom{a-X}{b-p}-\binom{a-X-1}{b-p-1}\right]\\
&=H(a,b,X,Y)+\sum\limits_{p=0}^{Y}\binom{X}{p-1}\left[\binom{a-X}{b-p}-\binom{a-X-1}{b-p-1}\right]-\binom{X}{p}\binom{a-X-1}{b-p-1}\\
&=H(a,b,X,Y)+\sum\limits_{p=0}^{Y}\binom{X}{p-1}\binom{a-X-1}{b-p}-\binom{X}{p}\binom{a-X-1}{b-p-1}\\
&=H(a,b,X,Y)+\sum\limits_{p-1=0}^{Y-1}\binom{X}{p-1}\binom{a-X-1}{b-1-(p-1)}-\sum\limits_{p=0}^{Y}\binom{X}{p}\binom{a-X-1}{b-p-1}\\
&=H(a,b,X,Y)+\sum\limits_{p=0}^{Y-1}\binom{X}{p}\binom{a-X-1}{b-1-p}-\sum\limits_{p=0}^{Y}\binom{X}{p}\binom{a-X-1}{b-p-1}\\
&=H(a,b,X,Y)-\binom{X}{Y}\binom{a-X-1}{b-Y-1}
\end{aligned}
$$

然后 $G$ 可以写成两个 $H$ 的和，就能 $O(1)$ 递推了，但是请注意 corner cases，比如有时候上下标是负数的组合数又不是为 $0$。

> 上指标反转公式：$\binom{n}{m}=(-1)^{m}\binom{m-n-1}{m}$，显然 $m\geq 0$。

在组合数 $\binom{n}{m}$ 里面 $m<0$ 显然为 $0$，否则 $m\geq 0,n<0$ 直接套上面的式子即可。

显然序列上即链的时候链剖只有一条链变化就是 $O(n)$ 的了。

---

## 作者：Dtw_ (赞：4)

# 前言

上课终于听懂一道题，赶紧写了，嘻嘻。

老师讲的和题解里的一篇一样，所以代码实现上还看了 [7KByte](/user/119261) 大佬的，但感觉大佬有点笔误，且有些地方可能不太适合我这种蒟蒻听，故写一篇自认为比较详细易懂的题解。

# 思路
~~老师说经典套路。~~

对于奇数位或偶数位进行异或，这样就可以转换为：交换相邻的 $0$ 和 $1$，这样就好想了。

先想，如果两个序列的 $1$ 的数量不相等，那想都不用想，肯定不行。

再想一个问题，怎样答案最优呢？比如说对于这样两个序列：

$a=(0,1,0,0,1,1)$ 以及 $b = (1,0,1,1,0,0)$。

我们可以对于每个 $1$ 进行标号，那就是：

$a' =  (0,1,0,0,2,3)$。

$b' = (1,0,2,3,0,0)$。

那这样就是序号相同的相配对（$0$ 不用配对，因为把 $1$ 配好之后 $0$ 一定也配对），这样是最优的，所以说这个距离和就是在序列上的距离的和，即为 $\left | i-j \right |$。

然后就可以开始 DP 了。

设 $g_{i,j}$ 表示 $a_i = 1$ 且 $b_j = 1$ 且他们两个配对的方案数，$f_{i,j}$ 表示距离之和。那么有:

$$g_{i,j}=\sum_{k}^{i-1}\sum_{l}^{j-1} g_{k,l}$$

$$f_{i,j} = \sum_{k}^{i-1}\sum_{l}^{j-1} f_{k,l} + g_{i,j} \times \left | i-j \right | $$

主要解释一下 $g_{i,j} \times \left | i-j \right | $。首先 $g_{i,j}$ 是方案数，而 $\left | i-j \right | $ 是 $i$ 和 $j$ 配对的距离，所以乘起来，就是总距离，那现在就没问题了。

但这样转移是 $O(n^4)$ 然后就 T 飞了。但是发现后面那一坨是一个矩阵的和，所以用二维前缀和优化一下就行了。复杂度为 $O(n^2)$，就可过了。

具体细节：因为我们的状态钦定 $a_i=1$ 且 $b_j = 1$ 但这样算答案的时候没法算，还要枚举，所以直接在 $a$ 和 $b$ 后面各接一个 $1$，但算的时候不计入就行了，答案就是 $f_{n,n}$。然后取前缀和的值的时候要特判边界，因为有可能传进来的是 $0$，然后再减 $1$ 成 $-1$ 越界了。最后把前缀和在更新一下就好。

初始化：显然，$g_{0,0}=1$，啥也没有，那方案为 $1$。那和 $g$ 数组对应的前缀和数组 $t$ 也要初始化，那就是 $t_{i,0} = t_{0,i} = 1$。这是显然的，其中一个没得选，那方案数为 $1$。

~~多测要清空！~~
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define pii pair<long long, long long>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 1e9 + 7;

const int N = 2e3 + 10;

int n;

char a[N], b[N];

int p[N], q[N];

int f[N][N], g[N][N], s[N][N], t[N][N];

inline int get(int op, int x, int y, int x2, int y2)
{
	if(op == 1)
	{
		if(x == 0 && y == 0) return s[x2][y2];
		if(x == 0) return s[x2][y2] - s[x2][y - 1];
		if(y == 0) return s[x2][y2] - s[x - 1][y2];
		return s[x2][y2] - s[x - 1][y2] - s[x2][y - 1] + s[x - 1][y - 1];
	}
	if(x == 0 && y == 0) return t[x2][y2];
	if(x == 0) return t[x2][y2] - t[x2][y - 1];
	if(y == 0) return t[x2][y2] - t[x - 1][y2];
	return t[x2][y2] - t[x - 1][y2] - t[x2][y - 1] + t[x - 1][y - 1];
}

void solve()
{
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++) cin >> b[i];
	for(int i=1; i<=n; i++)
	{
		if(i % 2)
		{
			if(a[i] != '?') a[i] ^= 1;
			if(b[i] != '?') b[i] ^= 1;
		}
	}
	n++;
	a[n] = b[n] = '1';
	for(int i=1; i<=n; i++)
	{
		if(a[i - 1] == '1') p[i] = i - 1;
		else p[i] = p[i - 1];
		if(b[i - 1] == '1') q[i] = i - 1;
		else q[i] = q[i - 1];
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			f[i][j] = g[i][j] = 0;
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
			t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1];
			s[i][j] = (s[i][j] % P + P) % P;
			t[i][j] = (t[i][j] % P + P) % P;
			if(a[i] != '0' && b[j] != '0')
			{
				g[i][j] = (g[i][j] + get(0, p[i], q[j], i - 1, j - 1) % P + P) % P;
				f[i][j] = (f[i][j] + get(1, p[i], q[j], i - 1, j - 1) % P + P) % P;
				f[i][j] = (f[i][j] + g[i][j] * abs(i - j) % P) % P;
			}
			s[i][j] = (s[i][j] + f[i][j]) % P;
			t[i][j] = (t[i][j] + g[i][j]) % P;
		}
	}
	cout << f[n][n] << endl;
	return;
}

signed main()
{
	fst;
	g[0][0] = 1;
	for(int i=0; i<=2000; i++)
	{
		t[0][i] = t[i][0] = 1;
	}
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}




```

---

## 作者：NOI_Winner (赞：2)

先考虑没有问号怎么做。

按原题中的操作难以统计答案，我们考虑转化问题。将串中所有的下标为奇数的位置 $0$ 变 $1$，$1$ 变 $0$，可以发现原来的操作转化为了相邻两项交换的操作。若此时两个串中 $1$ 的数量不同则无解，否则一定有解。设 $s$ 一共有 $m$ 个 $1$，$x_i$ 表示 $s$ 中第 $i$ 个 $1$ 的位置，$y_i$ 表示 $t$ 中第 $i$ 个 $1$ 的位置，那么答案即为 $\sum_{i=1}^m|x_i-y_i|$。

再考虑有问号的情况，我们发现上面这种统计方法在此时也不太好用，因此我们进一步转化问题。设 $a_i$ 表示 $s$ 中前 $i$ 个数中 $1$ 的个数，$b_i$ 表示 $t$ 中前 $i$ 个数中 $1$ 的个数，答案即为 $\sum_{i=1}^n |a_i-b_i|$。这样为什么正确呢？我们考虑 $1 \le i \lt n$，可以发现 $i$ 和 $i+1$ 之间需要交换的次数即为 $|a_i-b_i|$。这样我们就可以方便的统计答案了。设 $c_i$ 表示 $s$ 中后 $i$ 个数中 $1$ 的个数，$d_i$ 表示 $t$ 中后 $i$ 个数中 $1$ 的个数，$pre_{i,j}$ 表示前 $i$ 个数中 $j=a_i-b_i$ 的方案数，$suf_{i,j}$ 表示后 $i$ 个数中 $j=c_i-d_i$ 的方案数，那么答案即为 $\sum_{i=1}^{n-1}\sum_{j=-i}^i pre_{i,j} \times suf_{i+1,-j} \times |j|$。

代码示例：
```cpp
#include <iostream>

using namespace std;

constexpr int maxn = 2000, delta = maxn + 5, mod = 1000000007;
char s1[maxn + 5], s2[maxn + 5];
int pre[maxn + 5][2 * maxn + 10], suf[maxn + 5][2 * maxn + 10];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n >> s1 + 1 >> s2 + 1;
        for (int i = 1; i <= n; i += 2)
            if ('0' == s1[i])
                s1[i]  = '1';
            else if ('1' == s1[i])
                s1[i] = '0';
        for (int i = 1; i <= n; i += 2)
            if ('0' == s2[i])
                s2[i] = '1';
            else if ('1' == s2[i])
                s2[i] = '0';

        for (int i = 0; i <= n + 1; i++)
            for (int j = -n; j <= n; j++)
                pre[i][j + delta] = suf[i][j + delta] = 0;

        pre[0][0 + delta] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = -i; j <= i; j++)
                if ('0' == s1[i])
                    if ('0' == s2[i])
                        pre[i][j + delta] = pre[i - 1][j + delta];
                    else if ('1' == s2[i])
                        pre[i][j + delta] = pre[i - 1][j + 1 + delta];
                    else
                        pre[i][j + delta] = (pre[i - 1][j + delta] + pre[i - 1][j + 1 + delta]) % mod;
                else if ('1' == s1[i])
                    if ('0' == s2[i])
                        pre[i][j + delta] = pre[i - 1][j - 1 + delta];
                    else if ('1' == s2[i])
                        pre[i][j + delta] = pre[i - 1][j + delta];
                    else
                        pre[i][j + delta] = (pre[i - 1][j - 1 + delta] + pre[i - 1][j + delta]) % mod;
                else
                    if ('0' == s2[i])
                        pre[i][j + delta] = (pre[i - 1][j + delta] + pre[i - 1][j - 1 + delta]) % mod;
                    else if ('1' == s2[i])
                        pre[i][j + delta] = (pre[i - 1][j + 1 + delta] + pre[i - 1][j + delta]) % mod;
                    else 
                        pre[i][j + delta] = (2ll * pre[i - 1][j + delta] + pre[i - 1][j - 1 + delta] + pre[i - 1][j + 1 + delta]) % mod;
        
        suf[n + 1][0 + delta] = 1;
        for (int i = n; i >= 1; i--)
            for (int j = -i; j <= i; j++)
                if ('0' == s1[i])
                    if ('0' == s2[i])
                        suf[i][j + delta] = suf[i + 1][j + delta];
                    else if ('1' == s2[i])
                        suf[i][j + delta] = suf[i + 1][j + 1 + delta];
                    else
                        suf[i][j + delta] = (suf[i + 1][j + delta] + suf[i + 1][j + 1 + delta]) % mod;
                else if ('1' == s1[i])
                    if ('0' == s2[i])
                        suf[i][j + delta] = suf[i + 1][j - 1 + delta];
                    else if ('1' == s2[i])
                        suf[i][j + delta] = suf[i + 1][j + delta];
                    else
                        suf[i][j + delta] = (suf[i + 1][j - 1 + delta] + suf[i + 1][j + delta]) % mod;
                else
                    if ('0' == s2[i])
                        suf[i][j + delta] = (suf[i + 1][j + delta] + suf[i + 1][j - 1 + delta]) % mod;
                    else if ('1' == s2[i])
                        suf[i][j + delta] = (suf[i + 1][j + 1 + delta] + suf[i + 1][j + delta]) % mod;
                    else 
                        suf[i][j + delta] = (2ll * suf[i + 1][j + delta] + suf[i + 1][j - 1 + delta] + suf[i + 1][j + 1 + delta]) % mod;
        
        int ans = 0;
        for (int i = 1; i < n; i++)
            for (int j = -i; j <= i; j++)
                ans = (ans + 1ll * pre[i][j + delta] * suf[i + 1][-j + delta] % mod * abs(j) % mod) % mod;
        cout << ans << endl;
    }

    return 0;
}
```

---

## 作者：SunsetSamsara (赞：2)

## 题意

对于两个长度为 $n$ 的 $01$ 串 $s,t$，你可以对 $s$ 进行两种操作：把相邻两个 $0$ 变成 $1$ 或把相邻两个 $1$ 变成 $0$ ，定义 $s$ 到 $t$ 的距离为最少操作次数使得 $s$ 变成 $t$ ，如过没法变则距离为 $0$ 。

现在你有两个不完整的字符串，可以把其中的 $?$ 变成 $0$ 或 $1$ ，求所有情况所得到的两个 $01$ 串的距离之和。

## 分析

将偶数位翻转后，每一次操作可以看作交换两个相邻的值。
这样可能会有一些操作不合法（如翻转了 $01$），但是这里的操作不合法会变成交换两个相同的数，没有意义，不予考虑。

那么就简单多了。首先，如果 $S$ 和 $T$ 的 $1$ 个数不同，就距离为 $0$。否则，答案就是 $S$ 和 $T$ 中第 $i$ 个 $1$ 的位置的差的绝对值之和，即 $\sum\limits_{1 \le i \le k\space(\text{S 和 T 中 1 的个数})} |x_i - y_i|$，其中 $x_i$, $y_i$ 为 $S$ 和 $T$ 中第 $i$ 个 $1$ 的位置。

看上去是 dp，但是这东西不容易转移。

经过计算，不难发现答案为 $\sum\limits_{1\le i \le n}|p_i - q_i|$，其中 $p_i$ 为 $S$ 中前 $i$ 个位置 $1$ 的个数，$q_i$ 为 $T$ 中前 $i$ 个位置 $1$ 的个数。

令 $f_{i, j}$ 表示 $p_i - q_i = j$ 的方案数，令 $g_{i, j}$ 表示 $p_i - q_i = j$ 的方案的答案之和。

$f_{i, j}$ 的转移就枚举 $S$ 和 $T$ 下一位转移到 $f_{i + 1, j + 1 / j / j - 1}$

$g_{i, j}$ 就按前面写的 $\sum\limits_{1\le i\le n}|p_i - q_i|$ 转移，因为有 $f_{i, j}$ 种方案，每种有 $|j|$ 的贡献，所以就是 $|j|f_{i, j}$ 之和。

## 代码

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long lld;
using namespace std;
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x < y ? y : x; }
const int mod = 1e9 + 7;
const int N = 2010;
int Cases, n;
char S[N], T[N];
int f[N][N << 1], g[N][N << 1];
int main() {
	scanf("%d", &Cases);
	for (; Cases --; ) {
		scanf("%d%s%s", &n, S + 1, T + 1);
		for (int i = 2; i <= n; i += 2) S[i] ^= (S[i] != '?'), T[i] ^= (T[i] != '?');
		for (int i = 1; i <= n; ++ i) memset(f[i], 0, sizeof(f[i])), memset(g[i], 0, sizeof(g[i]));
		f[0][N] = 1;
		for (int i = 0, j, k, l; i < n; ++ i) {
			for (j = -i; j <= i; ++ j) {
				for (k = 0; k <= 1; ++ k)
					for (l = 0; l <= 1; ++ l)
						if ((S[i + 1] == '?' || k == S[i + 1] - '0') && (T[i + 1] == '?' || l == T[i + 1] - '0')) {
							int nw = j + k - l;
							f[i + 1][nw + N] = (f[i + 1][nw + N] + f[i][j + N]) % mod;
							g[i + 1][nw + N] = (g[i + 1][nw + N] + 1ll * f[i][j + N] * abs(j) % mod + g[i][j + N]) % mod;
						}
			}
		}
		printf("%d\n", g[n][N]);
	}
}
```

---

## 作者：MatrixGroup (赞：2)

- 前言

看到题解区好像都是用动规做的。但原题的 tag 里面有 `combinatorics`，怎么能不写一篇组合计数的题解呢？

- 前置知识

$O(n+\log p)$ 预处理 $O(1)$ 求组合数（二项式系数）。

组合数的一些公式。

- 解法

首先前面处理别的题解都说的很清楚了。

把奇数位反转，操作就变成了相邻位交换。对于 $\texttt{01}$ 串 $s$ 和 $t$，记 $x$ 的第 $i$ 个 $\texttt{1}$ 是第 $f_i(x)$ 位。则：

- 若 $s$ 和 $t$ 中的 $\texttt{1}$ 数量不等则无解。

- 否则答案为 $\sum\limits_{i=1}^{cnt}|f_i(s)-f_i(t)|$。至少是显然的。构造就是一个一个移动。

考虑若确定后 $s_i=t_j=\texttt{1}$ 时它们的贡献。

不妨设 $s$ 的第 $i$ 位左边有 $x$ 个 $\texttt{1}$，$y$ 个 $\texttt{?}$，$t$ 的第 $j$ 位左边有 $x'$ 个 $\texttt{1}$，$y'$ 个 $\texttt{?}$，则枚举有多少个 $\texttt{?}$ 赋为 $\texttt{1}$，由于要保证两串 $\texttt{1}$ 的数量相等，因此情况数为：

$$
\begin{array}{ll}
& \sum\limits_{i=0}^y\binom{y}{i}\binom{y'}{i+x-x'}\\
= & \sum\limits_{i=0}^y\binom{y}{y-i}\binom{y'}{i+x-x'}
\end{array}
$$

发现组合意义就是在 $y+y'$ 个东西里里选 $y+x-x'$ 个，枚举的是左边没选多少个，因此该式 $=\binom{y+y'}{y+x-x'}$。

右边同理，根据乘法原理乘在一起，再乘上 $|i-j|$ 就是贡献。

组合数可以 $O(n+\log p)$ 预处理 $O(1)$ 求，于是枚举 $i,j$，复杂度 $O(n^2)$。

- 代码

似乎是目前次优解。（代码写的丑，轻喷）

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)
#define rep1(i,n) for(int i=1,_##i##__end=(n);i<=_##i##__end;++i)
#define per1(i,n) for(int i=(n);i>=1;--i)
typedef long long ll;
using namespace std;
const ll mod2=1000000007;
int T,n;
ll tot;
char s[2005];
char t[2005];
ll bs[2005][3],bt[2005][3],sa[2005][3],ta[2005][3];//这些是前缀/后缀和 bs:在s[i]前 bt: 在t[j]前 sa:在s[i]后 ta:在t[i]后 
ll fac[4005],ivf[4005];

ll qp(ll a,ll b)//快速幂 
{
	ll res=1;
	while(b)
	{
		if(b&1)
		res=res*a%mod2;
		a=a*a%mod2;
		b>>=1;
	}
	return res;
}
void init()//预处理阶乘逆元 
{
	fac[0]=1;
	rep1(i,4000)
	fac[i]=fac[i-1]*i%mod2;
	ivf[4000]=qp(fac[4000],mod2-2);//费马小定理求逆元 
	per(i,4000)
	ivf[i]=ivf[i+1]*(i+1)%mod2;
}

ll C(ll n,ll m)
{
	if(m<0||m>n) return 0; return fac[n]*ivf[m]%mod2*ivf[n-m]%mod2;
}
ll calc(int i,int j)
{
	return abs(i-j)*C(bs[i][2]+bt[j][2],bs[i][1]+bs[i][2]-bt[j][1])%mod2*C(sa[i][2]+ta[j][2],sa[i][1]+sa[i][2]-ta[j][1])%mod2;
}

void Q()
{
	scanf("%d%s%s",&n,s,t);
	tot=0;//多测不清空，_____ 
	for(int i=1;i<n;i+=2)
	{
		if(s[i]!='?') s[i]^=1;//奇数位反转 
		if(t[i]!='?') t[i]^=1;
	}
	
	
	bs[0][0]=bs[0][1]=bs[0][2]=bt[0][0]=bt[0][1]=bt[0][2]=0;//多测不清空，_____ 
	rep(i,n-1)
	{
		switch(s[i])//讨论 
		{
			case '0':
				bs[i+1][0]=bs[i][0]+1;
				bs[i+1][1]=bs[i][1];
				bs[i+1][2]=bs[i][2];
				break;
			case '1':
				bs[i+1][0]=bs[i][0];
				bs[i+1][1]=bs[i][1]+1;
				bs[i+1][2]=bs[i][2];
				break;
			case '?':
				bs[i+1][0]=bs[i][0];
				bs[i+1][1]=bs[i][1];
				bs[i+1][2]=bs[i][2]+1;
				break;
		}
		switch(t[i])
		{
			case '0':
				bt[i+1][0]=bt[i][0]+1;
				bt[i+1][1]=bt[i][1];
				bt[i+1][2]=bt[i][2];
				break;
			case '1':
				bt[i+1][0]=bt[i][0];
				bt[i+1][1]=bt[i][1]+1;
				bt[i+1][2]=bt[i][2];
				break;
			case '?':
				bt[i+1][0]=bt[i][0];
				bt[i+1][1]=bt[i][1];
				bt[i+1][2]=bt[i][2]+1;
				break;
		}
	}
	sa[n-1][0]=sa[n-1][1]=sa[n-1][2]=ta[n-1][0]=ta[n-1][1]=ta[n-1][2]=0;
	per(i,n-1)
	{
		switch(s[i+1])
		{
			case '0':
				sa[i][0]=sa[i+1][0]+1;
				sa[i][1]=sa[i+1][1];
				sa[i][2]=sa[i+1][2];
				break;
			case '1':
				sa[i][0]=sa[i+1][0];
				sa[i][1]=sa[i+1][1]+1;
				sa[i][2]=sa[i+1][2];
				break;
			case '?':
				sa[i][0]=sa[i+1][0];
				sa[i][1]=sa[i+1][1];
				sa[i][2]=sa[i+1][2]+1;
				break;
		}
		switch(t[i+1])
		{
			case '0':
				ta[i][0]=ta[i+1][0]+1;
				ta[i][1]=ta[i+1][1];
				ta[i][2]=ta[i+1][2];
				break;
			case '1':
				ta[i][0]=ta[i+1][0];
				ta[i][1]=ta[i+1][1]+1;
				ta[i][2]=ta[i+1][2];
				break;
			case '?':
				ta[i][0]=ta[i+1][0];
				ta[i][1]=ta[i+1][1];
				ta[i][2]=ta[i+1][2]+1;
				break;
		}
	}
	
	
	rep(i,n) rep(j,n)
	{
		if(s[i]!='0'&&t[j]!='0')//必须可以为 1 
		{
			tot=(tot+calc(i,j))%mod2;
		}
	}
	
	
	printf("%d\n",int(tot));
}

int main()
{
	scanf("%d",&T);
	init();
	while(T--)
	Q();
	return 0;
}
```

---

## 作者：qzilr (赞：2)

#### 题意简述
两个 $01$ 序列，有若干位为 $?$，$?$ 表示可以填 $1$，又也可以填 $0$，将相邻两个值相同的位置取反定义为一次操作，使 $s$ 和 $t$ 相同的最小操作次数定义为两个序列的距离，求两个序列所有可能情况的距离之和。
#### 题意分析
第一次碰到这种题目，肯定会无从下手这时我们不妨仔细分析题目给的条件，我们先考虑一次操作的影响，考虑如下序列：

- …… 正正 ……

操作后变为：

- …… 反反 ……

似乎没有什么突破口，这时我们再将偶数位取反：

- …… 正反 ……
- …… 反正 ……

我们惊奇的发现交换之后这两位是相同的，所以我们可以得出一个结论：两个序列偶数位取反后，对一序列相邻位的交换操作等价于原来对一序列的相邻相同位的取反操作。这时我们将原问题简化为先将 $s$ 和 $t$ 的偶数位取反，求交换相邻位使 $s$ 和 $t$ 相等的次数和。

有一定做题量的同学应该能意识到这是一道经典的逆序对应用，典型例题是[火柴排队](https://www.luogu.com.cn/problem/P1966)，不过题目限定了每一位的取值范围，只能取 $0$ 或 $1$，这将问题求解大大简化，我们不必再求逆序对，而是贪心的考虑，$s$ 中第 $i$ 个 $1$ 一定是跟 $t$ 中的第 $i$ 个 $1$ 匹配，若不是，要么 第 $i$ 个 $1$ 绕路，要么其它的 $1$ 绕路，若是第 $i$ 个 $1$ 绕路，路线产生了交叉，一定不优，若其它的 $1$ 绕路，那么路线产生了覆盖，一定更不优，因此我们得到了最小次数的式子 $\sum_{i=1}^n |x_i-y_i|$，但是这样考虑不方便转移，我们再考虑转换。

在上述方法中，我们以序列为对像，一次跑一遍，我们能不能做到一次跑完所有呢。（这里的思考方向有点像 Dinic，都是将一次的信息利用最大化）答案是可以的，我们将 $i$ 到 $i+1$ 的交换当作研究对像，我们考虑 $i$ 和 $i+1$ 一共要交换多少次，这比较好想，就是 $s$ 中前 $i$ 位 $1$ 的数量与 $t$ 中 前 $i$ 位 $1$ 的数量的差的绝对值。因此，答案又可以表示位 $\sum_{i=1}^n|cnts_i-cntt_i|$。

这样我们就可以比较方便的在这个式子的基础上进行转移，我们设 $pre_{i,j}$ 表示两序列前 $i$ 个，$1$ 的个数差为 $j$ （不含绝对值）时交换次数之和，$nxt_{i,j}$ 表示后 $i$ 个，$1$ 的个数差为$j$ 时的交换次数之和，由乘法原理易知答案为前后缀方案数相乘，所以式子显然：
$$ans=\sum_{i'=1}^i\sum_{j=-i}^ipre_{i,j}·nxt_{n-i+1,-j}$$
$pre$ 和 $nxt$ 可以在移位时由当前位更新。
#### 代码
```cpp
const int N=2002;
char s[N],t[N],len;
int pre[N][N<<1],nxt[N][N<<1];
inline bool chk(char a,int b){return (a=='?'||a==b+'0');}
signed main(){
	//file();
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d%s%s",&n,s+1,t+1);
		int a=0,b=0;
		pre[0][N]=nxt[n+1][N]=1;
		rep(i,0,n-1) rep(j,-i,i)
		    if(pre[i][j+N]) rep(x,0,1) rep(y,0,1)
		        if(chk(s[i+1],x^(i&1))&&chk(t[i+1],y^(i&1)))
		            pre[i+1][j+x-y+N]=add(pre[i+1][j+x-y+N],pre[i][j+N]);
		per(i,n+1,2) rep(j,i-n-1,n-i+1)
		    if(nxt[i][j+N]) rep(x,0,1) rep(y,0,1)
		        if(chk(s[i-1],x^(i&1))&&chk(t[i-1],y^(i&1)))
		            nxt[i-1][j+x-y+N]=add(nxt[i-1][j+x-y+N],nxt[i][j+N]);
		int ans=0;
		rep(i,1,n) rep(j,-i,i) ans=add(ans,1ll*pre[i][j+N]*nxt[i+1][-j+N]%mod*abs(j)%mod);
		cout<<ans<<endl;
		rep(i,0,n+1) rep(j,0,N*2-1) pre[i][j]=nxt[i][j]=0;
	}
    return 0;
}
```
#### 总结
这题有两个很经典也很套路的转换，应当反复思考，体会其中的巧妙，在这里推荐[一道题目](https://www.luogu.com.cn/problem/AT2046)，是这题的拓展，将这题的序列变为了树和基环树，可以借此加深自己对这两个技巧性转换的理解。

---

## 作者：Richard_Whr (赞：1)

怎么没人 dp 套 dp？

考虑给定两个串如何求最小步数。

设 $f_{u,0},f_{u,1}$ 表示 $u$ 结点需要作为 $0,1$ 的操作次数。

那么最终的答案就是 $\frac{1}{2}\sum f_{u,0}+f_{u,1}$。

从下往上 dp。

在叶子，显然可以通过是否需要变化一次来决定，且需要借用父亲的操作。

在非叶子，儿子借用父亲的操作在当前节点都要进行，可以黑白匹配，如果有多出来的，则又需要借用父亲的，给父亲贡献即可。

注意到转移的时候往父亲只会贡献一种颜色的操作，可以记录数值正负而非两个数组来表示。

这样我们通过记录一个值，复杂度 $O(n)$ 的树形 dp 解决了底层问题。

计数的话直接把 dp 数组压进状态里面，这样就是 $O(n^2)$ 的了。

---

## 作者：2huk (赞：1)

拜谢 @[WA_QJ](/user/938933) 大佬/bx/bx

## 题意

对于两个长度为 $n$ 的 $01$ 串 $s,t$ ，你可以对 $s$ 进行两种操作：把相邻两个 $0$ 变成 $1$ 或把相邻两个 $1$ 变成 $0$ ，定义 $s$ 到 $t$ 的距离为最少操作次数使得 $s$ 变成 $t$ ，如过没法变则距离为 $0$ 。

现在你有两个不完整的字符串，可以把其中的 $?$ 变成 $0$ 或 $1$ ，求所有情况所得到的两个 $01$ 串的距离之和。

## 做法

第一次见这个 trick。第一个想出这个 trick 的人一定不是人。

首先考虑没有问号，直接求两个字符串的距离怎么做。

我们将 $s, t$ 的所有奇数位上的数取反（$\texttt0$ 变 $\texttt1$，$\texttt1$ 变 $\texttt0$）。那么原来将 $s$ 中的两个相邻且相同的位置取反，等价于现在将 $s$ 中的两个相邻且不同的位置交换（即 $s_i = \texttt0, s_{i+1}=\texttt1$ 或 $s_{i}=\texttt1,s_{i+1}=\texttt0$ 时，交换 $s_i, s_{i+1}$）。

若新的 $s, t$ 中 $\texttt1$ 的数量不同，无解。

不难发现多次进行交换可以看作是一个 $\texttt1$ 在很多 $\texttt0$ 之间移动。例如对于 $s = \texttt{0010}$，那么先交换 $s_2,s_3$ 再交换 $s_1, s_2$ 得到的字符串 $s' = \texttt{1000}$，可以看作是 $1$ 向左移动了两位。此时 $\texttt1$ 的移动位数即操作次数。

那么我们想让 $s$ 中的每个 $\texttt1$ 都移动到某个位置，使得 $s = t$，且移动次数最小。这是简单贪心，不难得出若令 $[i_1, i_2, \dots, i_m]$ 为 $s$ 中的 $\texttt1$ 的出现位置（已排序），$[j_1, j_2, \dots, j_m]$ 为 $t$ 中的 $\texttt1$ 的出现位置（已排序），那么答案为 $\sum_{k=1}^m |i_k - j_k|$。

对于带 $\texttt ?$ 的原题，我们考虑 DP。

设 $f(i, j)$ 表示 $s[1\dots i], t[1 \dots j]$ 的答案（即每个合法的 $s, t$ 的距离和），且保证 $s_i = t_j = \texttt1$，$g(i, j)$ 表示方案数。显然只有在 $s_i \ne \texttt 0$ 且 $t_i \ne \texttt 0$ 时 $f(i, j), g(i, j)$ 才有意义。

转移枚举两个串分别的倒数第二个 $\texttt1$ 的位置。

$$
g(i, j) = \sum_{i'=p_i}^{i-1} \sum_{j'=q_j}^{j-1}g(i',j') \\
f(i, j) = g(i, j) \times |i-j|+\sum_{i'=p_i}^{i-1} \sum_{j'=q_j}^{j-1}f(i',j')
$$

其中 $p_i$ 表示 $s$ 中 $i$ 之前第一个 $\texttt1$ 的位置，$q_i$ 是 $t$ 的。因为 $i', j'$ 是倒数第二个 $\texttt1$，所以 $[i'+1, i-1], [j'+1, j-1]$ 不能跨越任何一个 $\texttt1$。

这里 $g(i, j) \times |i - j|$ 是拆贡献，表示 $|i - j|$ 在 $g(i, j)$ 个串中有用。

复杂度 $\mathcal O(n^4)$。二维前缀和优化转移即可做到 $\mathcal O(n^2)$。

代码去看[这篇题解](https://www.luogu.com.cn/article/hrtn2hio)吧。

---

## 作者：Petit_Souris (赞：1)

不难，自己做的，但是很容易想麻烦。如果熟练记忆两部分的经典结论的话 10 分钟就能做出来了。

首先考虑如何计算两个串互相转化的最少操作次数。你发现对于相邻位的操作不会改变 $0,1$ 的个数奇偶性，更进一步地，你发现对于奇数位和偶数位，他们的 $0,1$ 个数差不会改变。因此不妨把所有奇数位翻转，这样就把操作变成了交换相邻的一组 $01$ 或 $10$。

然后计算次数就是简单的了，我们一定会按照原序列的顺序将所有 $1$ 匹配，这样次数就是所有对应 $1$ 的位置差之和。但是这样的形式不便于计数，所以我们不妨在每个位置统计他被移动经过的次数，也就是两个串前缀的 $1$ 个数差。

这样就可以直接 dp 了。设 $f_{i,j}$ 为前 $i$ 个位置，两个串的 $1$ 个数差目前为 $j$ 的方案数，$g_{i,j}$ 为对应状态的操作次数总和，转移只需要枚举两个串接下来分别填什么就行了，转移复杂度是 $\mathcal O(1)$ 的。总时间复杂度 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
//首先观察这个操作的性质，每次 1 的个数奇偶性不变
//更具体地，发现奇偶位的 1 个数差不变
//那么不妨把所有偶数位 flip 一下，这样就变成选择相邻的 01 交换
//这样代价就是每个 1 排序后的按顺序匹配
//更直接地发现是 sum |pre1[i]-pre2[i]|
//那么 dp 的时候记录前缀和的差就行了
//f[i][j] 表示前 i 个差为 j 的方案数
//g[i][j] 表示前 i 个差为 j 的答案和
const ll N=2009,Mod=1e9+7;
ll T,n,f[2][N*2],g[2][N*2];
char s[N],t[N];
void Upd(ll&x,ll y){
    x+=y;
    if(x>=Mod)x-=Mod;
}
void solve(){
    n=read();
    scanf("%s%s",s+1,t+1);
    rep(i,1,n){
        if(i&1){
            if(s[i]!='?')s[i]^=1;
            if(t[i]!='?')t[i]^=1;
        }
    }
    rep(i,0,1){
        rep(j,-n,n)f[i][j+n]=g[i][j+n]=0;
    }
    ll cur=0;
    f[0][0+n]=1;
    rep(i,1,n){
        rep(j,-n,n)f[cur^1][j+n]=g[cur^1][j+n]=0;
        rep(j,-n,n){
            if(!f[cur][j+n])continue;
            rep(p,0,1){
                if(s[i]!=p+'0'&&s[i]!='?')continue;
                rep(q,0,1){
                    if(t[i]!=q+'0'&&t[i]!='?')continue;
                    ll nj=j+p-q;
                    Upd(f[cur^1][nj+n],f[cur][j+n]);
                    Upd(g[cur^1][nj+n],(g[cur][j+n]+abs(nj)*f[cur][j+n])%Mod);
                }
            }
        }
        cur^=1;
    }
    write(g[cur][0+n]),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：lzqy_ (赞：1)

哎哎哎，正解的转化太精妙了。不过没脑子也是可以摁做的！

考虑**从左往右**依次操作，并钦定影响的方向是**从右往左**的。那么如果当前位置有 $a_i=c,b_i=!c$，这意味着右侧要多“透支”一次 ` c 变成 !c`  操作。显然同时透支 $c\rightarrow !c$ 和 $!c\rightarrow c$ 是不可能的，因此容易设 $f_{i,c,j}$，表示操作完前 $i$ 个数，$i$ 需要透支 $j$ 次 ` c 变成 !c` 操作的填数方案，再设 $g_{i,c,j}$ 表示步数之和。

考虑转移。

位置 $i$ 需要透支 $j$ 步 $!c\rightarrow c$，可以推出位置 $i+1$ 需要透支 $(j\pm O(1))$ 步 $c\rightarrow !c$，具体的步数和 $a_{i+1},b_{i+1}$ 的值相关。

暴力枚举 $a_{i+1},b_{i+1}$ 的值转移即可。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=2010;
const int mod=1e9+7;
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
char a[maxn],b[maxn];
int f[maxn][2][maxn];
int g[maxn][2][maxn];
//f_{i,c1,j,c2}:第i个要变成颜色c j次
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s%s",a+1,b+1);
		if(a[1]=='?'&&b[1]=='?')
			f[1][0][0]=f[1][1][0]=f[1][0][1]=f[1][1][1]=1;
		else if(a[1]=='?')
			f[1][b[1]-'0'][0]=f[1][b[1]-'0'][1]=1;
		else if(b[1]=='?')
			f[1][a[1]-'0'][0]=f[1][!(a[1]-'0')][1]=1;
		else f[1][b[1]-'0'][a[1]!=b[1]]=1;
		for(int i=1;i<n;i++)
			for(int c=0;c<2;c++)
				for(int j=0;j<=i;j++){
					if(!f[i][c][j]) continue;
					for(int c1=0;c1<2;c1++)
						for(int c2=0;c2<2;c2++){
							if(a[i+1]!='?'&&a[i+1]-'0'!=c1) continue;
							if(b[i+1]!='?'&&b[i+1]-'0'!=c2) continue;
							if(!j){
								int jj=(c1!=c2);
								ad(f[i+1][c2][jj],f[i][c][j]);
								ad(g[i+1][c2][jj],g[i][c][j]);
								continue;
							}
							int jj=j-(c1==(!c))+(c2==(!c));
							if(jj<0) continue;
							ad(f[i+1][!c][jj],f[i][c][j]);
							ad(g[i+1][!c][jj],g[i][c][j]);
							g[i+1][!c][jj]=(g[i+1][!c][jj]+1ll*f[i][c][j]*j)%mod;
						}
				}
		printf("%d\n",(g[n][0][0]+g[n][1][0])%mod);
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=n+1;j++)
				for(int c=0;c<2;c++)
					f[i][c][j]=g[i][c][j]=0;
	}
	return 0;
} 
```

---

## 作者：LZDQ (赞：1)

碰巧上午做了 [AGC004F](https://www.luogu.com.cn/problem/AT2046)，晚上就遇到这个模型。

首先是操作的转化。如果我们对序列黑白染色，奇数染 1，偶数染 0，也就是把所有奇数位的颜色取反。那么一次操作可以看作**交换相邻两个（不同）颜色**。对于给定的两个串，显然当 1 的个数相等时可以通过交换得到，交换需要的次数就是先把所有 1 的位置排序，$s,t$ 中出现 1 的位置分别为 $a_{1\sim m},b_{1\sim m}$，那么次数就为 $\sum_{i=1}^m |a_i-b_i|$。

接下来可以 DP 了。如果我们能求出每一对 $(i,j)$ 使得 $s_i,t_j$ 均为 1 且作为一组 $|a-b|$ 出现的次数，就能累加到答案里。相当于我们要在 $s_{1\sim i},t_{1\sim j}$ 里选数量相等的 1，$s_{i\sim n},t_{j\sim n}$ 同理。

令 $f_{ij}$ 表示在 $s_{1\sim i},t_{1\sim j}$ 里选数量相等的 1 且强制 $s_i=t_j=1$ 的方案数。$f_{ij}$ 对于可以填 1 的 $f_{kl} \space (k>i,l>j)$ 的贡献，如果 $s_{(i,k)}$ 之间可以全部填 0，$t_{(j,l)}$ 也可以全部填 0，那么贡献为 1，否则为 0。不难发现这是一个二维平面上的矩形加，所以可以直接二维差分。

对于 $s_{i\sim n},t_{j\sim n}$ 只需要把整个序列反过来做一次就行了。直接 reverse 然后复制粘贴完事。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int MAXN=2005,mod=1e9+7;
int n;
char s[MAXN],t[MAXN];
int ns[MAXN],nt[MAXN];
int f1[MAXN][MAXN],g[MAXN][MAXN],f2[MAXN][MAXN],ans;
inline void Add(int x1,int y1,int x2,int y2,int v){
	g[x1][y1]=(g[x1][y1]+v)%mod;
	g[x1][y2+1]=(g[x1][y2+1]-v+mod)%mod;
	g[x2+1][y1]=(g[x2+1][y1]-v+mod)%mod;
	g[x2+1][y2+1]=(g[x2+1][y2+1]+v)%mod;
}
int main(){
	int _; scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		scanf("%s%s",s+1,t+1);
		ans=0;
		for(int i=1; i<=n; i++){
			if(s[i]=='?') s[i]=2;
			else s[i]=s[i]-'0'+i&1;
			if(t[i]=='?') t[i]=2;
			else t[i]=t[i]-'0'+i&1;
		}
		ns[n+1]=nt[n+1]=n+1;
		for(int i=n; i; i--){
			if(s[i]==1) ns[i]=i;
			else ns[i]=ns[i+1];
			if(t[i]==1) nt[i]=i;
			else nt[i]=nt[i+1];
		}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				g[i][j]=0;
		Add(1,1,ns[1],nt[1],1);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++){
				if(s[i]&&t[j]) f1[i][j]=g[i][j],Add(i+1,j+1,ns[i+1],nt[j+1],f1[i][j]);
				g[i+1][j]=(g[i+1][j]+g[i][j])%mod;
				g[i][j+1]=(g[i][j+1]+g[i][j])%mod;
				g[i+1][j+1]=(g[i+1][j+1]-g[i][j]+mod)%mod;
			}
		reverse(s+1,s+n+1);
		reverse(t+1,t+n+1);
		ns[n+1]=nt[n+1]=n+1;
		for(int i=n; i; i--){
			if(s[i]==1) ns[i]=i;
			else ns[i]=ns[i+1];
			if(t[i]==1) nt[i]=i;
			else nt[i]=nt[i+1];
		}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				g[i][j]=0;
		Add(1,1,ns[1],nt[1],1);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++){
				if(s[i]&&t[j]) f2[i][j]=g[i][j],Add(i+1,j+1,ns[i+1],nt[j+1],f2[i][j]);
				g[i+1][j]=(g[i+1][j]+g[i][j])%mod;
				g[i][j+1]=(g[i][j+1]+g[i][j])%mod;
				g[i+1][j+1]=(g[i+1][j+1]-g[i][j]+mod)%mod;
			}
		reverse(s+1,s+n+1);
		reverse(t+1,t+n+1);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(s[i]&&t[j]) ans=(ans+1ll*abs(i-j)*f1[i][j]%mod*f2[n-i+1][n-j+1])%mod;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

**题目大意**

> 给定两个长度为 $n$ 的 01 串 $s,t$，每次操作可以把 $s$ 中的 `00` 变成 `11`，或把 `11` 变成 `00`。
>
> 定义 $d(s,t)$ 表示 $s\to t$ 的最少操作次数，现已知 $s,t$ 的部分位，求所有情况中 $d(s,t)$ 的和。
>
> 数据范围：$n\le 2000$。

**思路分析**

考虑一个 trick，把 $s,t$ 的奇数位 01 翻转，那么题目中的操作等价于交换 $s$ 中相邻两位。

设 $s,t$ 的前缀和为 $S_i,T_i$，那么 $d(s,t)=\sum_{i=1}^{n-1}|S_i-T_i|$，且要求 $S_n=T_n$。

设 $f_{i,x}$ 表示填完 $1\sim i$，当前 $S-T=x$ 的方案数，$g_{i,x}$ 表示填完 $i\sim n$，当前 $S-T=x$ 的方案数。

那么答案为 $\sum_{i=1}^{n-1}\sum_x|x|\times f_{i,x}\times g_{i+1,-x}$。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005,MOD=1e9+7;
char s[MAXN],t[MAXN];
int n,f[MAXN][MAXN<<1],g[MAXN][MAXN<<1];
void add(int &x,int y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
void solve() {
	scanf("%d%s%s",&n,s+1,t+1);
	for(int i=1;i<=n;i+=2) {
		if(s[i]!='?') s[i]^=1;
		if(t[i]!='?') t[i]^=1;
	}
	f[0][n]=1;
	for(int i=1;i<=n;++i) {
		int *x=f[i],*y=f[i-1];
		memset(f[i],0,sizeof(f[i]));
		for(int j=-i+1;j<=i-1;++j) if(y[j+n]) {
			if(s[i]!='1'&&t[i]!='1') add(x[j+n],y[j+n]);
			if(s[i]!='0'&&t[i]!='1') add(x[j+n+1],y[j+n]);
			if(s[i]!='1'&&t[i]!='0') add(x[j+n-1],y[j+n]);
			if(s[i]!='0'&&t[i]!='0') add(x[j+n],y[j+n]);
		}
	}
	reverse(s+1,s+n+1),reverse(t+1,t+n+1);
	g[0][n]=1;
	for(int i=1;i<=n;++i) {
		int *x=g[i],*y=g[i-1];
		memset(g[i],0,sizeof(g[i]));
		for(int j=-i+1;j<=i-1;++j) if(y[j+n]) {
			if(s[i]!='1'&&t[i]!='1') add(x[j+n],y[j+n]);
			if(s[i]!='0'&&t[i]!='1') add(x[j+n+1],y[j+n]);
			if(s[i]!='1'&&t[i]!='0') add(x[j+n-1],y[j+n]);
			if(s[i]!='0'&&t[i]!='0') add(x[j+n],y[j+n]);
		}
	}
	int ans=0;
	for(int i=1;i<n;++i) {
		for(int j=-n;j<=n;++j) {
			ans=(ans+1ll*(j<0?-j:j)*f[i][j+n]%MOD*g[n-i][-j+n]%MOD)%MOD;
		}
	}
	printf("%d\n",(ans+MOD)%MOD);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

这题简直典完了。

大家都做过 $\rm AGC004F \ Namori$，很容易发现这种操作要将偶数位置的 $0/1$ 翻转，变为序列上移动 $1$ 的问题。

处理后，假设 $S$ 的前 $i$ 位有 $s_i$ 个 $1$，$T$ 的前 $i$ 位有 $t_i$ 个 $1$，那么答案就是 $\sum_{i=1}^{n-1} | s_i-t_i|$，当然前提是 $s_n=t_n$。

----------

咋计数呢？很容易相当，设 $pre_{i,j}$ 表示前 $i$ 个数，$S$ 比 $T$ 多 $j$ 个 $1$ 的方案数，$suf_{i,j}$ 表示后 $i$ 个数，$S$ 比 $T$ 多 $j$ 个 $1$ 的方案数。答案就是

$$
\sum_{i=1}^{n-1} \sum_{j=-i}^{i} |j|pre_{i,j}suf_{n-i,-j}
$$

复杂度 $O(n^2)$。

看见 Rainbow 有 $O(n)$ 组合计数方法，感觉很牛。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD=1e9+7;
int Tc,n,ans,pre[MAXN][MAXN<<1],suf[MAXN][MAXN<<1];
string S,T;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>Tc;
	while(Tc--) {
		cin>>n>>S>>T,S="&"+S,T="&"+T;
		ffor(i,1,n) if(i&1) {
			if(S[i]=='0') S[i]='1';
			else if(S[i]=='1') S[i]='0';
			if(T[i]=='0') T[i]='1';
			else if(T[i]=='1') T[i]='0';
		}
		ffor(i,0,n+1) ffor(j,0,n+n) pre[i][j]=suf[i][j]=0;
		pre[0][n]=suf[n+1][n]=1;
		ffor(i,1,n) {
			ffor(s,0,1) ffor(t,0,1) if(S[i]-'0'!=1-s&&T[i]-'0'!=1-t) {
				ffor(j,n-(i-1),n+i-1) pre[i][j+s-t]=(pre[i][j+s-t]+pre[i-1][j])%MOD;
			}
		}
		roff(i,n,1) {
			ffor(s,0,1) ffor(t,0,1) if(S[i]-'0'!=1-s&&T[i]-'0'!=1-t) {
				ffor(j,n-(n-i),n+n-i) suf[i][j+s-t]=(suf[i][j+s-t]+suf[i+1][j])%MOD;
			}
		}
		ans=0;
		ffor(i,1,n-1) ffor(j,0,n+n) ans=(ans+abs(n-j)*pre[i][j]%MOD*suf[i+1][n+n-j])%MOD;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

