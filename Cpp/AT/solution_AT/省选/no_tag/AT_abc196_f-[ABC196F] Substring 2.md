# [ABC196F] Substring 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc196/tasks/abc196_f

`0`, `1` からなる文字列 $ S,\ T $ が与えられます。  
 $ T $ が $ S $ の部分文字列となるように、$ T $ のいくつかの文字を書き換えます。  
 少なくとも何文字書き換える必要がありますか？

 部分文字列とは？ $ S $ のある連続した部分を取り出してできる文字列が $ T $ と一致するとき、$ T $ は $ S $ の部分文字列であるといいます。 例えば、`000` は `10001` の部分文字列ですが、`11` は `10001` の部分文字列ではありません。

## 说明/提示

### 制約

- $ S,\ T $ は `0`, `1` からなる
- $ 1\ <\ = |T|\ <\ =\ |S|\ <\ =\ 10^6 $

### Sample Explanation 1

$ T $ を `001` と書き換えると、$ S $ の $ 2 $ 文字目から $ 4 $ 文字目が $ T $ と一致します。

## 样例 #1

### 输入

```
0001
101```

### 输出

```
1```

## 样例 #2

### 输入

```
0101010
1010101```

### 输出

```
7```

## 样例 #3

### 输入

```
10101000010011011110
0010011111```

### 输出

```
1```

# 题解

## 作者：Purslane (赞：2)

# Solution

从近期的 ABC-EX 的题解里看到了这道题，特记录。

考虑我们把 $T$ 贴到 $S$ 的第 $x$ 位处。则答案应该为：

$$\sum_{i=1}^m S_{x+i-1} \oplus T_i$$

考虑如果 $a\le1,b\le1$，那么 $a \oplus b=a(1-b)+b(1-a)=a+b-2ab$。那么可以化为：

$$\sum_{i=1}^m (S_{x+i-1}+T_i) -2\sum_{i=1}^m S_{x+i-1}T_i$$

后者是相乘两数下标差为定值的两个数，可以令 $T'_i=T_{m-i+1}$。于是你的减数可以变为：

$$2\sum_{i=1}^m S_{x+i-1}T_{m-i+1}$$

这个就是很常见的卷积的形式。可以用 NTT 解决。

[代码](https://atcoder.jp/contests/abc196/submissions/42978959)。

---

## 作者：hzlqwq (赞：1)

暴力的做法不难想，若将 $T_1$ 和 $S_i$ 对齐，则 $\displaystyle ans_i=\sum_{j=1}^{|T|} S_{i+j-1}\oplus T_j$，逐个位置计算即可。

因为当 $a,b\in \{0,1\}$ 时，$a\oplus b=a+b-2ab$，于是原式可化为 $\displaystyle ans_i=\sum_{j=1}^{|T|} S_{i+j-1}+\sum_{j=1}^{|T|}T_j-2\sum_{j=1}^{|T|}S_{i+j-1}T_j$；

第一坨东西可以前缀和算，第二坨直接求和即可；注意到第三坨中，$i+j-1$ 与 $j$ 的差是定值，于是我们考虑把 $T$ 倒过来，令 $P_i=T_{|T|-i+1}$，则 $\displaystyle \sum_{j=1}^{|T|}S_{i+j-1}T_j=\sum_{j=1}^{|T|}S_{i+j-1}P_{|T|-j+1}$；如此一来，$i+j-1$ 与 $|T|-j+1$ 的和 $|T|+i$ 就是定值了，就可以卷积计算了。

总时间复杂度 $O\left((n+m)\log (n+m)\right)$，瓶颈在 FFT/NTT 上。

```cpp
#include <cstring>
#include <iostream>

using namespace std;

const int N = 2.1e6, g = 3, ig = 7689558, mod = 23068673;

char s[N], t[N];
int n, m, pre[N], sum, ans = N;
int lon, len = 1, ilen, rev[N], a[N], b[N];

inline int qpow(int x, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1)
            res = 1ll * res * x % mod;
        x = 1ll * x * x % mod, k >>= 1;
    }
    return res;
}

inline void init()
{
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (a[i] = s[i] ^ 48);
    for (int i = 1; i <= m; i++)
        sum += (b[m - i + 1] = t[i] ^ 48);
    while (len <= n + m)
        len <<= 1, lon++;
    ilen = qpow(len, mod - 2);
    for (int i = 0; i < len; i++)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << lon - 1;
}

inline void NTT(int *num, bool t)
{
    for (int i = 0; i < len; i++)
        if (i < rev[i])
            swap(num[i], num[rev[i]]);
    for (int i = 1; i < len; i <<= 1)
    {
        int gn = qpow(t ? g : ig, (mod - 1) / (i << 1));
        for (int j = 0; j < len; j += i << 1)
        {
            int g0 = 1;
            for (int k = 0; k < i; k++, g0 = 1ll * g0 * gn % mod)
            {
                int x = num[j + k], y = 1ll * g0 * num[i + j + k] % mod;
                num[j + k] = (x + y) % mod, num[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> s + 1 >> t + 1;
    init();
    NTT(a, 1), NTT(b, 1);
    for (int i = 0; i < len; i++)
        a[i] = 1ll * a[i] * b[i] % mod;
    NTT(a, 0);
    for (int i = 1; i <= n - m + 1; i++)
        ans = min(0ll + ans, pre[i + m - 1] - pre[i - 1] + sum - 2ll * a[i + m] * ilen % mod);
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：porse114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc196_f)

这道题第一眼就是暴力，遍历 $i$ 从 $0$ 到 $n - m$，然后暴力算 $[i,i + m - 1]$ 区间的不同个数，最后求 $\min$ 即可。

暴力代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
char a[maxn],b[maxn];
int n,m,len,minn = maxn,ans;
int main()
{
	cin >> a >> b;
	n = strlen(a);m = strlen(b);
	for(int i = 0;i <= n - m;i++)
	{
		ans = 0;
		for(int j = i;j <= i + m - 1;j++)
		{
			if(a[j] != b[j - i]) ans++;
		}
		minn = min(minn,ans);
	}
	cout << minn << '\n';
	return 0;
}
```


## 正解 FFT

**前置知识**

1. 多项式乘法中，$h_i$ 的系数等于
$$\sum^{i}_{j=1}f_j \times g_{i-j}$$
2. $x \text{ xor } y=x+y-2xy=x(1-y)+y(1-x)$

暴力的代码中，**第一层循环**是优化不了的，所以我们从**第二层循环**入手。

第二层循环其实是在求这个东西：

对于每一个 $[i,i + m - 1]$ 中的 $i$，求
$$\sum^{|T|-1}_{j=0}S_{i+j}\text{ xor }T_j$$
此时，运算是 $\text{xor}$，我们需要将他改成加减乘除，所以由前置知识2，就可以把式子化简为
$$\sum^{|T|-1}_{j=0}S_{i+j}\text{ × }(1-T_j)\text{ + }T_j\text{ × }(1-S_{i+j})$$
令 $T^{'}_i=1-T_i \,,S^{'}_i=1-S_i$，则原式可化简为
$$\sum^{|T|-1}_{j=0}S_{i+j}\text{ × }T^{'}_j\text{ + }T_j\text{ × }S^{'}_{i+j}$$
但此时下标之和不是定值，所以

令 $T^{''}_i=T^{'}_{m-i-1} \,,T^{'''}_i=T^{}_{m-i-1}$，则原式可化简为
$$\sum^{|T|}_{j=1}S_{i+j}\text{ × }T^{''}_{m-j-1}\text{ + }T^{'''}_{m-j-1}\text{ × }S^{'}_{i+j}$$
此时，两下标相加为定值 $i+m-1$，就只需要用FFT求出 $S$ 与 $T^{''}$，$T^{'''}$ 与 $S^{'}$ 的积，再求第 $i+m-1$ 位的值就行了。

再加上外面的循环，这题就结束了。

这题有 $1 \text{GB}$ 的空间，所以数组可以开的狂放一点；时限为三秒，也不需要卡常。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = (1 << 21) + 10;//len最多到这，要不然可能会RE 
const double pi = acos(-1);//反三角函数 
struct z{
	double a,b;
	z operator + (z other)
	{
		return {this -> a + other.a,this -> b + other.b};
	}
	z operator - (z other)
	{
		return {this -> a - other.a,this -> b - other.b};
	}
	z operator * (z other)
	{
		return {this -> a * other.a - this -> b * other.b,this -> a * other.b + this -> b * other.a};
	}//重载运算符 
}S[maxn],s_[maxn],T[maxn],T_[maxn],T__[maxn],T___[maxn],h[maxn],H[maxn];
char a[maxn],b[maxn];
int n,m,len;
int minn = maxn;//最多不会修改超过maxn次 
void FFT(z *f,int l,int op)
{
	if(l == 1) return ;//判边界 
	z A0[l >> 1],A1[l >> 1]; 
	for(int i = 0;i < l;i++)//奇偶分离 
	{
		if(i & 1) A1[i >> 1] = f[i];//i & 1 意为是否为奇数 
		else A0[i >> 1] = f[i];
	}
	FFT(A0,l >> 1,op);
	FFT(A1,l >> 1,op);//递归 
	z w = {1,0};//第0个单位根是1 
	z wk = {cos(2.0 * pi / l),op * sin(2.0 * pi / l)};//注意，虚部要乘op 
	for(int i = 0;i < (l >> 1);i++,w = w * wk)
	{
		f[i] = A0[i] + w * A1[i];
		f[i + (l >> 1)] = A0[i] - w * A1[i];//O1为另一半赋值 
	}
	return ;
}
int main()
{
	cin >> a >> b;
	n = strlen(a);m = strlen(b);
	for(int i = 0;i < n;i++)
	{
		S[i].a = a[i] - 48; 
		s_[i].a = 1 - S[i].a;
	}
	for(int i = 0;i < m;i++)
	{
		T[i].a = b[i] - 48;
		T___[m - i - 1].a = T_[i].a;
	}
	for(int i = 0;i < m;i++)
	{
		T_[i].a = 1 - T[i].a;
		T__[m - i - 1].a = T_[i].a;
	}
	//初始化 
	len = 1;
	while(len <= n + m + 1) len <<= 1;//寻找超过 n + m + 1 的最小的2的幂次 
	FFT(S,len,1);
	FFT(T__,len,1);
	FFT(s_,len,1);
	FFT(T___,len,1);
	for(int i = 0;i < len;i++)
	{
		h[i] = S[i] * T__[i];
		H[i] = s_[i] * T___[i];
	}//求点值 
	FFT(h,len,-1);
	FFT(H,len,-1);//逆运算 
	for(int i = 0;i < len;i++)
	{
		h[i].a = ((int)(h[i].a / len + 0.5));
		H[i].a = ((int)(H[i].a / len + 0.5));//一定要除以 len
	}
	for(int i = 0;i <= n - m;i++)
	{
		minn = min(minn,((int)(h[i + m - 1].a + H[i + m - 1].a)));//最后求min就行了 
	}
	cout << minn << '\n';
	return 0;//又切一道紫 
}
```

---

## 作者：ZnPdCo (赞：0)

题目大意：存在两个字符串 $S$，$T$，问你最少修改多少次 $T$ 才能使 $T$ 成为 $S$ 的子串？

因为是多项式题，所以以 $0$ 为起始下标。

首先我们可以枚举 $i$ 表示 $T$ 经过若干次修改后是 $S_{i,i+m-1}$，容易得到答案为：
$$
\mathop{\arg\min}_{i=0}^{n-m}(\sum_{j = 0}^{m-1}(S_{i+j}\oplus T_j))
$$
我们发现，因为值域只有 $[0,1]$，所以 $a\oplus b$ 可以被表示为 $a+b-2ab$。

所以式子就可以化简：
$$
\begin{aligned}
\sum_{j = 0}^{m-1}(S_{i+j}\oplus T_j) &= \sum_{j = 0}^{m-1} (S_{i+j}+T_j-2S_{i+j}T_j) \\
&= \sum_{j = 0}^{m-1} S_{i+j}+\sum_{j = 0}^{m-1} T_j- 2\sum_{j = 0}^{m-1}S_{i+j}T_j
\end{aligned}
$$

第一个我们可以用前缀和做，第二个直接统计，第三个发现是一个比较明显的卷积。

我们使得 $P_i=S_{n-1-i}$，然后有：
$$
\sum_{j = 0}^{m-1}S_{i+j}T_j=\sum_{j = 0}^{m-1}P_{n-1-i-j}T_j
$$
我们直接用 FFT 做即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long
#define N 8000010
struct complex {
	double x, y;
	complex(double xx = 0, double yy = 0):x(xx), y(yy){};
	friend complex operator +(const complex &a, const complex &b) {return complex(a.x + b.x, a.y + b.y);}
	friend complex operator -(const complex &a, const complex &b) {return complex(a.x - b.x, a.y - b.y);}
	friend complex operator *(const complex &a, const complex &b) {return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}
} A[N], B[N];
ll n, m;
char s[N], t[N];
ll siz = 1, l;
ll r[N], ans = 1e15;
ll ss[N], ts;
double PI = acos(-1);
void FFT(complex *a, ll type) {
	for(ll i = 0; i < siz; i ++) {
		if(i < r[i]) swap(a[i], a[r[i]]);
	}
	for(ll x = 2; x <= siz; x <<= 1) {
		complex wn(cos(2 * PI / x), type * sin(2 * PI / x));
		for(ll i = 0; i < siz; i += x) {
			complex w(1, 0);
			for(ll j = 0; j < (x >> 1); j ++, w = w * wn) {
				complex A = a[i + j], B = a[i + (x >> 1) + j];
				a[i + j] = A + B * w;
				a[i + (x >> 1) + j] = A - B * w;
			}
		}
	}
}
int main() {
	scanf("%s %s", s, t);
	n = strlen(s), m = strlen(t);
	while(siz < n + m) siz <<= 1, l ++;
	for(ll i = 0; i < siz; i ++) {
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
	for(ll i = 0; i < n; i ++) {
		A[i] = complex(s[n - 1 - i] - '0', 0);
		ss[i] = s[i] - '0';
		if(i > 0) ss[i] += ss[i - 1];
	}
	for(ll i = 0; i < m; i ++) {
		B[i] = complex(t[i] - '0', 0);
		ts += t[i] - '0';
	}
	FFT(A, 1);
	FFT(B, 1);
	for(ll i = 0; i < siz; i ++) {
		A[i] = A[i] * B[i];
	}
	FFT(A, -1);
	for(ll i = 0; i <= n - m; i ++) {
		ll num = A[n - 1 - i].x / siz + 0.5;
		ans = min(ans, ss[i + m - 1] - (i == 0 ? 0 : ss[i - 1]) + ts - 2 * num);
	}
	printf("%lld", ans);
}
```

---

## 作者：songhongyi (赞：0)

ABC Ex 你怎么拉了。但是这题确实很 edu。

字符串任意位置匹配编辑距离之类的，只能考虑卷积优化。

不妨设匹配在第 $x$ 位，那么我们有这里的答案是
$$
\sum _{i=1}^{m}\left[S_{x+i-1} \neq T_i\right]
$$
因为值域为 0/1，这个东西可以表示成
$$
\sum _{i=1}^{m}\left(S_{x+i-1}-T_i\right)^2 = \sum_{i=1}^m\left(S_{x+i-1}^2+T_i^2-2S_{x+i-1}T_i\right)
$$
把独立项取出来，则答案为
$$
\sum_{i=1}^m\left(S_{x+i-1}^2+T_i^2\right ) -2\sum_{i=1}^mS_{x+i-1}T_i
$$
后面这坨是一个减法卷积，把 $T$ 翻转后就是正常卷积，可以 FFT。

哦对了 AT 可以用 AC library 哦。



---

## 作者：loser_seele (赞：0)

参考自官方题解。

不难发现可以枚举所有的子串，然后统计修改的代价，但这样显然无法通过。

注意到答案为 $ \min\limits_{0 \leq i \leq \left| s \right|-\left| t \right|}  \sum_{j=1}^{\left| t \right|}(s_{i+j} \oplus t_j) $，类似卷积形式，于是考虑转化。

将 $ t $ 翻转，则考虑计算所有 $ \sum\limits_{j=1}^{\left| t \right|}(s_{i+j} \oplus t_{\left| t \right|-1-j})\ $，令 $ c $ 表示 $ s,t $ 的卷积 $ c_i=\underset{i=j+k} \sum s_j \oplus t_k $，则 $ c_{i+\left| t \right|-1}= \sum\limits_{j=1}^{\left| t \right|}(s_{i+j} \oplus t_{\left| t \right|-1-j}) $，和题意一致，直接取最小值即可。

于是直接在异或意义下 FFT 卷积即可。时间复杂度 $ \mathcal{O}(n\log{n}) $，代码不贴。

---

