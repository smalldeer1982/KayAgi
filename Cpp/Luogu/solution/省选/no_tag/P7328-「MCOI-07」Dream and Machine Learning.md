# 「MCOI-07」Dream and Machine Learning

## 题目描述

Dream 构造了一个红石计算机来验证 $b^e\equiv r\pmod m$ 形式的公式。  
Dream 固定了 $b$ 和 $m$ 并且构造了 $n$ 对满足以上条件的 $(e,r)$ 正整数对。  
可惜，Dream 忘记了 $m$ 的具体值。现在他给了你 $b$ 和这 $n$ 对数。请替代 Dream 的计算机，回答 $q$ 组 $b^{a_i}\pmod m$ 形式的询问。

## 说明/提示

#### 样例 1 解释

可以唯一确定 $m=97$。  
样例 1 仅仅说明题意，并不代表任何 subtask 的任何测试点。

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（5 pts）：$m\le10^3$
 - Subtask 2（19 pts）：$m\le10^9$
 - Subtask 3（19 pts）：$m\le10^{19}$
 - Subtask 4（19 pts）：$m\le10^{29}$
 - Subtask 5（19 pts）：$m\le10^{99}$
 - Subtask 6（19 pts）：$m\le10^{199}$

对于 $100\%$ 的数据，$b\in\{2,3\}$，$1\le q\le100$，$2\le e,a_i\le 10^9$，$n=10^5$。  
**保证** $m$ 为质数。  
**保证** 所有 $e$ 互不相同。  
**保证** 数据随机。

## 样例 #1

### 输入

```
3 8 3
108 75
616 36
220 16
37 66
114 64
514 24
1919 65
810 33
19260817
123456789
23333333
```

### 输出

```
3
79
49```

## 样例 #2

### 输入

```
请见附件 sample.in```

### 输出

```
请见附件 sample.out```

# 题解

## 作者：Alex_Wei (赞：2)

> *[P7328 「MCOI-07」Dream and Machine Learning](https://www.luogu.com.cn/problem/P7328)*

给出一个 **不依赖于 $b\in \{2, 3\}$**，且不太依赖于 $n$ 的大小的做法。

注意到 $e_i$ 随机给出，我们尽可能利用这个性质。同时，注意到若 $e_a + e_b = e_c + e_d$，则 $r_ar_b\equiv r_cr_d\pmod m$，这说明 $r_ar_b - r_cr_d$ 是 $m$ 的倍数。

我们求出若干组这样的 $a, b, c, d$，并对所有 $|r_ar_b - r_cr_d|$ 求 $\gcd$ 即可得到 $m$。剩下来是 trivial 的。

由于 $r_ar_b - r_cr_d$ 为 $\mathcal{O}(m ^ 2)$ 级别，所以期望进行很少次 $\gcd$ 即可得到正确的 $m$。实际测试中只需要 $c = 10$ 次即可。

接下来考虑如何求出 $a, b, c, d$。很经典的 meet-in-the-middle 套路。在时间限制范围内将足够多的 $(a, b)$ 塞入哈希表（设为 $B$ 个），key 值为 $e_a + e_b$。直接枚举 $c, d$ 并检查 $e_c + e_d$ 是否在哈希表中出现，若出现且对应的 value $(a, b)\neq (c, d)$，则可以进行一次 gcd。枚举四元组的时间复杂度期望为 $c\times \dfrac {\max e_i}{B}$。

笔者实现后发现时间瓶颈在于高精度快速幂，如果使用 FFT 优化和压位优化应该能跑得更快。求解 $m$ 并不是瓶颈。

接下来说说这个做法相较于 std 可以扩展的地方。

首先它不依赖于 $b$，所以这个 $b$ 可以出到 $\mathcal{O}(m)$ 级别。

其次，它不太依赖于 $n$ 的级别。当 $n$ 变小的时候，我们仍然可以将足够多的 $T$ 元组扔进哈希表，并在与 $n$ 很大时相同的复杂度得到足够多的 $2T$ 元组求解 gcd。

唯一的问题在于这会使得 $\prod_{i\in X} r_i - \prod_{i\in Y} r_i$ 变得很大，级别为 $\mathcal{O}(m ^ T)$，不过这个问题其实并不严重，因为这只给复杂度乘了常数，或者说给求解 $m$ 的复杂度乘上了 $T ^ 3\approx \log_n ^ 3 \max e_i$（求解 $\gcd$ 的次数乘上 $T$，乘法复杂度乘上 $T ^ 2$）。

综上，本题可以加强至 $b$ 为任意 $m$ 以内的数，$n = 100$，严格优于使用生日悖论的方法。而且不算难写（除了高精度板子，和 binary GCD）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int L = 600;
bool Mbe;
struct BigInt {
	int len;
	short a[L];
	BigInt() {memset(a, 0, L << 1), len = 0;} // ADD len = 0
	void print() {if(len) for(int i = len - 1; ~i; i--) putchar(a[i] + '0'); putchar('\n');}
	void read() {
		char s = getchar();
		while(!isdigit(s)) s = getchar();
		while(isdigit(s)) a[len++] = s - '0', s = getchar();
		reverse(a, a + len);
	}
	void flush() {
		len += 2;
		for(int i = 0; i < len; i++) a[i + 1] += a[i] / 10, a[i] %= 10;
		while(len && !a[len - 1]) len--;
	}
	void shrink() {
		len += 2;
		for(int i = 0; i < len; i++) if(a[i] < 0) a[i + 1]--, a[i] += 10;
		while(len && !a[len - 1]) len--;
	}
	bool operator < (BigInt rhs) {
		if(len != rhs.len) return len < rhs.len;
		for(int i = len - 1; ~i; i--) if(a[i] != rhs.a[i]) return a[i] < rhs.a[i];
		return 0;
	}
	BigInt operator + (BigInt rhs) {
		BigInt res;
		res.len = max(len, rhs.len);
		for(int i = 0; i < res.len; i++) res.a[i] = a[i] + rhs.a[i]; // len -> res.len
		res.flush();
		return res;
	}
	BigInt operator - (BigInt rhs) {
		BigInt res;
		res.len = max(len, rhs.len);
		for(int i = 0; i < res.len; i++) res.a[i] = a[i] - rhs.a[i];
		res.shrink();
		return res;
	}
	BigInt operator * (BigInt rhs) {
		BigInt res;
		res.len = len + rhs.len;
		for(int i = 0; i < len; i++)
			for(int j = 0; j < rhs.len; j++)
				res.a[i + j] += a[i] * rhs.a[j];
		res.flush();
		return res;
	}
	BigInt operator * (int v) {
		BigInt res;
		res.len = len; // ADD THIS LINE
		for(int i = 0; i < len; i++) res.a[i] = a[i] * v;
		res.flush();
		return res;
	}
	BigInt operator / (int v) {
		BigInt res;
		res.len = len;
		int rem = 0;
		for(int i = len - 1; ~i; i--) rem = rem * 10 + a[i], res.a[i] = rem / v, rem %= v;
		while(res.len && !res.a[res.len - 1]) res.len--;
		return res;
	}
	BigInt operator % (BigInt rhs) {
		BigInt rem;
		for(int i = len - 1; ~i; i--) {
			rem = rem * 10, rem.a[0] += a[i], rem.flush();
			while(!(rem < rhs)) rem = rem - rhs;
		}
		return rem;
	}
} f[N], m, pw[32];
BigInt gcd(BigInt x, BigInt y) {
	int pw = 0;
	while(x.len && x.a[0] % 2 == 0 && y.len && y.a[0] % 2 == 0) pw++, x = x / 2, y = y / 2;
	while(x.len && y.len) {
		while(x.a[0] % 2 == 0) x = x / 2;
		while(y.a[0] % 2 == 0) y = y / 2;
		if(x < y) swap(x, y);
		x = x - y;
	}
	if(x < y) swap(x, y);
	while(pw--) x = x * 2;
	return x;
}
int cnt = 20, b, n, q, e[N];
map <int, pair <int, int>> mp;
mt19937 rnd(time(0));
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}
BigInt ksm(int b) {
	BigInt s;
	s.len = s.a[0] = 1;
	int cnt = 0;
	while(b) {
		if(b & 1) s = s * pw[cnt] % m;
		b >>= 1, cnt++;
	}
	return s;
}
void solve() {
	pw[0].len = 1, pw[0].a[0] = b;
	for(int i = 1; i < 30; i++) pw[i] = pw[i - 1] * pw[i - 1] % m;
	while(q--) {
		int a;
		scanf("%d", &a);
		ksm(a).print();
	}
	exit(0);
}
bool Med;
int main() {
	fprintf(stderr, "%.4lf\n", (&Med - &Mbe) / 1048576.0);
	// freopen("sample.in", "r", stdin);
	cin >> b >> n >> q;
	for(int i = 1; i <= n; i++) scanf("%d", &e[i]), f[i].read();
	for(int i = 1; i <= 1e5; i++) {
		int a = rd(1, n), b = rd(1, n);
		mp[e[a] + e[b]] = make_pair(a, b);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			auto it = mp.find(e[i] + e[j]);
			if(it == mp.end()) continue;
			int a = it -> second.first, b = it -> second.second;
			if(a == i || b == i) continue;
			BigInt x = f[a] * f[b], y = f[i] * f[j];
			if(x < y) swap(x, y);
			m = gcd(m, x - y);
			if(!--cnt) solve();
		}
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

先恢复 $m$，再计算答案。  
首先插入一个 $e=0,r=1$ 并且将输入的 $e$ 递增排序。  
考虑两队 $(e_1,r_1,e_2,r_2)$ 意味着什么。  

$$b^{e_1}\equiv r_1\pmod m\wedge b^{e_2}\equiv r_2\pmod m\implies r_1b^{e_2-e_1}-r_2=mk$$

提取几个最小的 $e_2-e_1$，计算出来对应 $mk$，求 gcd 即可恢复 $m$。  
$r_1b^{e_2-e_1}-r_2$ 可以被抽象为随机值；两个 $O(n)$ 级别的随机数的 gcd 接近于 $O(\log n)$，于是需要做 $O(\log^*b^{\frac{\max e}{n}})$ 次 gcd；总共时间复杂度为 $O(\text{高精 gcd}\times\log^*b^{\frac{\max e}{n}})=O(\frac{\max e}{n}\log^2\frac{\max e}{n}\log\log\frac{\max e}{n}\log^*\frac{\max e}{n})$。

---

## 作者：dead_X (赞：2)

## 前言
一开场听同学说 C 比 A 和 B 都要简单，然后以为 python 的高精可以算 $2^{10^9}$ 于是以为自己 python 哪里搞错了……

果然我是傻逼……

后来赛后发现还是个水题（
## 思路
1. Naive solution

显然 $b^e=km+r$。

于是我们可以根据所有的 $e$ 得出所有的 $km$。

所有的 $km$ 直接 $\gcd$ 一下就是答案了。

2. Correct solution

我们发现 $b^e$ 太大了，但是由于有 $10^5$ 个数，$b^{e-e'}$ 可能很小。

于是我们看看怎么对于相邻两个 $e$ 求出答案。

显然 $b^{e}=km+r,b^{e+t}=k'm+r'$

我们随便推导一下。

$$b^{e+t}=b^eb^t=(km+r)b^t=k'm+r'$$
$$(km+r)b^t=k'm+r'$$
$$kmb^t+rb^t=k'm+r'$$
$$rb^t-r'=(k'-kb^t)m$$

于是我们可以根据相邻两项的差 $t$ 求出 $(k'-kb^t)m$

由于数据随机还是 $\gcd$ 一下就是答案了。

注意，为了保证随机不出问题，如果在 $t$ 很大的时候，我们可以直接选择跳过这次运算。

3. Hint

高精度可以使用 Python 编写程序。
## 代码（Python 3）
```cpp
import math
def qsort(a,b,l,r):
    mid=a[(l+r)//2]
    i,j=l,r
    while i<=j:
        while a[i]<mid:i+=1
        while a[j]>mid:j-=1
        if i<=j:
            a[i],a[j]=a[j],a[i]
            b[i],b[j]=b[j],b[i]
            i+=1
            j-=1
    if l<j:qsort(a,b,l,j)
    if i<r:qsort(a,b,i,r)
def qpow(x,y,z):
    if y==1:
        return x
    if y==0:
        return 1
    t=y//2
    g=qpow(x*x%z,t,z)
    if y%2==1:
        g=g*x%z
    return g
s=input().split()
base=int(s[0])
n=int(s[1])
q=int(s[2])
a=[]
b=[]
for i in range(0,n):
    s=input().split()
    a.append(int(s[0]))
    b.append(int(s[1]))
qsort(a,b,0,n-1)
m=0
if a[1]<=1000:
    m=(base**a[1])-b[1]
for i in range(1,n):
    if a[i]-a[i-1]<=1000:
        m=math.gcd(m,b[i-1]*(base**(a[i]-a[i-1]))-b[i])
for i in range(0,q):
    x=int(input())
    print(qpow(base,x,m))
```
## 后记
这题没有紫吧……

---

## 作者：dengyaotriangle (赞：1)

首先发现关键性质：若 $b^{e}\bmod m=x,b^{e+1}\bmod m=y$，则有 $bx-y\in\{0,m,\cdots,(b-1)m\}$

因为 $0\leq bx-y<bm$ 且 $bx\equiv y \pmod{m}$，上面的式子是显然的。

又因为数据随机，且 $10^5>\sqrt{10^9}$（生日悖论相关结论），期望其实是可以找到不少 $e_i,e_j$，满足 $e_j=e_i+1$。

而又因为数据随机且 $b\leq 3$，算出的 $bx-y$ 有至少 $1/3$ 的概率 $=m$

然后对于所有满足 $e_j=e_i+1$ 的 $i,j$，计算 $bx-y$，考虑把所有找到的**非零的** $bx-y$ 取 $\min$ 就有很大概率是 $m$ 了。

至于找到所有的 $e_j=e_i+1$，把数据按 $e_i$ sort一下然后扫过去就好了。

使用python编写可以免除高精度的实现。

正确率不会分析，反正能过（

```python3
r=input().split(' ')
b=int(r[0])
n=int(r[1])
q=int(r[2])

w = []
for i in range(0,n):
    p=input().split(' ')
    w.append((int(p[0]),int(p[1])))

def getk(x):
    return x[0]
w.sort(key=getk)

def powm(a,b,m):
    ret=1
    while b:
        if b&1:
            ret=ret*a%m
        b>>=1
        a=a*a%m
    return ret
mi=-1
for i in range(1,n):
    if w[i][0]-w[i-1][0]==1:
        dif = w[i-1][1]*b-w[i][1]
        if dif!=0:
            if mi==-1:
                mi=dif
            else:
                mi=min(mi,dif)

for i in range(0,q):
    a=int(input())
    print(powm(b,a,mi))
```

---

