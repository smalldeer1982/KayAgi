# Self-exploration

## 题目描述

Wall-B 厌倦了一遍又一遍地探索月球，决定去探索他自身的组成——二进制数。他取了一个二进制数，决定统计所有长度为 $2$ 的不同子串出现的次数。他将这些值分别存储在 $c_{00}$、$c_{01}$、$c_{10}$ 和 $c_{11}$ 中，分别表示子串 $00$、$01$、$10$ 和 $11$ 在该数中出现的次数。例如：

$10111100 \rightarrow c_{00} = 1,\ c_{01} = 1,\ c_{10} = 2,\ c_{11} = 3$

$10000 \rightarrow c_{00} = 3,\ c_{01} = 0,\ c_{10} = 1,\ c_{11} = 0$

$10101001 \rightarrow c_{00} = 1,\ c_{01} = 3,\ c_{10} = 3,\ c_{11} = 0$

$1 \rightarrow c_{00} = 0,\ c_{01} = 0,\ c_{10} = 0,\ c_{11} = 0$

Wall-B 发现，可能有多个二进制数满足相同的 $c_{00}$、$c_{01}$、$c_{10}$ 和 $c_{11}$ 约束。因此，他想统计在区间 $[A, B]$ 内，有多少个二进制数满足给定的 $c_{xy}$ 约束。不幸的是，他的计算能力不足以处理他感兴趣的大区间。你能帮帮他吗？由于答案可能很大，请输出对 $10^9 + 7$ 取模后的结果。

## 说明/提示

示例 1：区间 $[10,1001]$ 内的二进制数有 $10,11,100,101,110,111,1000,1001$。只有 $110$ 满足约束：$c_{00} = 0, c_{01} = 0, c_{10} = 1, c_{11} = 1$。

示例 2：区间内没有任何数满足约束。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10
1001
0
0
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
10001
1
2
3
4
```

### 输出

```
0
```

# 题解

## 作者：Lunch (赞：5)

## [题意](https://www.luogu.org/problemnew/show/CF1045H)
- 求在区间$[l,r]$中有多少个二进制数满足，子串$00$的个数为$C_{00}$，子串$01$的个数为$C_{01}$，子串$10$的个数为$C_{10}$，子串$11$的个数为$C_{11}$。

首先找一下性质，可以发现$C_{01}=C_{10}$或$C_{01}=C_{10}-1$。那么不满足这个条件的直接判掉，还有一个性质就是序列中连续$0$的段数等于$C_{10}$，序列中$1$的个数等于$C_{01}+1$，那么我们就可以确定这个序列的长度了。

我们考虑没有限制的情况，那么答案显然就是：
$$f(C_{00},C_{10})\times f(C_{11},C_{01}+1)$$
其中$f(x,y)$表示把$x$个连续的数分成$y$段的方案数，在有限制的情况下，我们把限制拆成$[0,r]$和$[0,l)$，我们先算出总共的，每次枚举一个前缀并且最后一位为$0$（最后一位为$1$肯定没有超过限制），表示从这个前缀开始超过限制，那么把总共的减去这些超过限制的就好了。
```cpp
#include <bits/stdc++.h>

#define For(i, a, b) for (int i = a; i <= b; ++ i)
#define Forr(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 1e6 + 7;
const int mod = 1e9 + 7;

string l, r; 

int fac[N], ifac[N];
int c[2][2], d[2][2], len = 1;

int qpow(int _, int __) {
	int ___ = 1; 
	for (; __; _ = 1ll * _ * _ % mod, __ >>= 1) 
		if (__ & 1) ___ = 1ll * ___ * _ % mod;
	return ___;
}

void Math_Init(int n) {
	fac[0] = ifac[0] = 1; 
	For(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	Forr(i, n, 1) ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

int C(int n, int m) { 
	if (n < m || n < 0 || m < 0) return 0;
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod; 
} 

int f(int n, int m) { return m ? C(n + m - 1, m - 1) : !n; }

int calc(string S) {
	For(i, 0, 1) For(j, 0, 1) d[i][j] = c[i][j];
	int res = 1ll * f(c[0][0], c[1][0]) * f(c[1][1], c[0][1]) % mod, sz = S.size();
	if (sz ^ len) return sz < len ? 0 : res;
	For(i, 1, sz - 1) {
		int lst = S[i - 1] ^ 48;
		if (-- d[lst][1], S[i] == '1') continue;
		(res -= 1ll * f(d[0][0], d[1][0]) * f(d[1][1], d[0][1]) % mod) %= mod;
		++ d[lst][1], -- d[lst][0];
	}
	return (res + mod) % mod;
}

int check(string S) {
	int d[2][2] = {0}, sz = S.size();
	For(i, 1, sz - 1) ++ d[S[i - 1] ^ '0'][S[i] ^ '0'];
	++ d[0][1];
	For(i, 0, 1) For(j, 0, 1) if (d[i][j] ^ c[i][j]) return 0;
	return 1;
}

int main() {

	Math_Init(N - 5);

	cin >> l >> r;
	For(i, 0, 1) For(j, 0, 1) {
		scanf("%d", &c[i][j]);
		len += c[i][j];
	}
	if (++ c[0][1] != c[1][0] && c[0][1] - c[1][0] != 1) return puts("0"), 0;
	printf("%d\n", (calc(r) - calc(l) + check(l) + mod) % mod);

	return 0;
}

```

---

## 作者：tribool4_in (赞：1)

首先合法的数字位数一定为 $1+\sum c$。考虑不带 $[A,B]$ 区间限制的情况。

“相邻两项”之间并不能随意拼接，有类似边的性质。不妨将子串 $ab\ (a,b\in \{0, 1\})$ 视作一个将 $a$ 变成 $b$ 的“转移”，且注意到此时最高位一定为 $1$，则有解的充要条件为 $c_{10}-c_{01}\in [0, 1]$，即改变数字的转移交替进行，形成 $c_{10}+c_{01}+1$ 个连续段，其中为 $0$ 的段数为 $c_{10}$，为 $1$ 的段数为 $c_{01}+1$。而其余 $c_{00},c_{11}$ 相应插入其中对应的段内。答案可用插板法得到：

$$
\binom{c_{00}+c_{10}-1}{c_{10}-1}\binom{c_{11}+(c_{01}+1)-1}{(c_{01}+1)-1}
$$

然后考虑区间的限制，进行差分，令 $f(X)$ 表示上限为 $X$ 的答案，则答案为 $f(B)-f(A-1)$。考虑求 $f(X)$，钦定一个前缀 $i$ 相等且第 $i+1$ 位未顶满上限，后半部分可以与无限制的情况同理计算。注意此时开头位为 $0$ 而非 $1$，且应特判若 $X$ 本身满足限制的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int lA, lB, c[4], L;
bool A[N], B[N];
char sA[N], sB[N];
int qpow(int a, int b = mod - 2) {
    int res = 1;
    for (; b; a = 1ll * a * a % mod, b >>= 1)
        if (b & 1) res = 1ll * res * a % mod;
    return res;
}
int fac[N], ifac[N];
void init(int n = 1e5 + 2) {
    for (int i = fac[0] = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n]);
    for (int i = n; i > 0; i--) ifac[i - 1] = 1ll * ifac[i] * i % mod;
}
int C(int n, int m) { return (n < 0 && m < 0) ? 1 : ((n < m || m < 0) ? 0 : 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod); }
int f(bool b[], int n) {
    if (n < L) return 0;
    if (n > L) {
        int c0 = c[0b10], c1 = c[0b01] + 1;
        return 1ll * C(c[0b00] + c0 - 1, c0 - 1) * C(c[0b11] + c1 - 1, c1 - 1) % mod;
    }
    static int c[4];
    memcpy(c, ::c, sizeof(c));
    int ans = 0;
    bool f = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (b[i]) {
            int o = b[i + 1] << 1 | b[i] ^ 1;
            c[o] -= 1;
            if (c[0b01] - c[0b10] <= 1 && c[0b01] >= c[0b10]) {
                int c0 = c[0b10] + 1, c1 = c[0b01];
                ans += 1ll * C(c[0b00] + c0 - 1, c0 - 1) * C(c[0b11] + c1 - 1, c1 - 1) % mod;
                ans %= mod;
            }
            c[o] += 1;
        }
        int o = b[i + 1] << 1 | b[i];
        c[o] -= 1;
        if (c[o] < 0) {
            f = 0;
            break;
        }
    }
    if (f) (ans += 1) %= mod;
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    cin >> sA >> sB >> c[0b00] >> c[0b01] >> c[0b10] >> c[0b11];
    L = c[0b00] + c[0b01] + c[0b10] + c[0b11] + 1;
    lA = strlen(sA), lB = strlen(sB);
    for (int i = 0; i < lA; i++) A[lA - i] = sA[i] - '0';
    for (int i = 0; i < lB; i++) B[lB - i] = sB[i] - '0';
    int p = 1;
    while (A[p] == 0) A[p++] = 1;
    A[p] = 0;
    while (lA && !A[lA]) --lA;

    if (c[0b10] - c[0b01] > 1 || c[0b10] < c[0b01]) {
        cout << "0\n";
        return 0;
    }
    cout << (f(B, lB) - f(A, lA) + mod) % mod << '\n';
    return 0;
}
```

---

