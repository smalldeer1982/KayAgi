# 「TFOI R1」Average Number

## 题目背景

**题目背景与题意无关，可直接阅读题目描述。**

有一种人叫做「别人家的妹妹」，小 A 对此感触颇深。

小 A 的妹妹——小 L——经常把小 A 的藏书偷走看，小 A 对此很是头疼。

这一次，强迫症小 A 正在收拾他的藏书，小 L 趁小 A 不注意偷走了一本。

「还给我。」

『不给。不过。。。如果你能猜出我手上的书的编号，我就还给你。』

小 A 为了方便拿取和整理他的藏书，特意给每本书从一开始编了号。

「开玩笑，我的书这么多，我怎么猜？」

『嗯。这样吧，我告诉你剩下的那堆书的编号平均值。怎么样，这个提示够了吧。』

「。。。」

小 A 的藏书多到他都不知道有多少本，但是作为一个合格的 OIer，小 A 借助计算机成功算出了答案。只不过，他想要以这个问题来考验你一下。

## 题目描述

你知道 $\dfrac{\left(\sum\limits^{n}_ {i = 1}i \right) - m}{n - 1}$ 的值，其中 $m \in [1, n]$，$n$ 和 $m$ 均为正整数，你要求出 $n$ 和 $m$ 的值，保证有解。

如果有多种可行解，那么请输出 $n$ 较小的那一组解。

多组测试数据。

## 说明/提示

**本题采用捆绑测试**。

- Subtask 1（5 points）：$T \leqslant 10$，$n \leqslant 10^3$。
- Subtask 2（5 points）：$T \leqslant 10^3$，$n \leqslant 10^3$。
- Subtask 3（5 points）：$T \leqslant 10$，$n \leqslant 5\times 10^5$。
- Subtask 4（40 points）：$T \leqslant 10^3$，$n \leqslant 10^{18}$。
- Subtask 5（45 points）：无特殊限制。

对于所有数据，$1 \leqslant m \leqslant n \leqslant 10 ^ {18}$，$n \not = 1$，$1 \leqslant T \leqslant 2 \times 10 ^{5}$，$1 \leqslant a \leqslant 10 ^{18}$，$0 \leqslant b < c \leqslant 10 ^ {18}$ 。

**保证 $\dfrac{b}{c}$ 是最简真分数。特别的，当 $b=0$ 时，$c=1$。**

---

**题目背景（续）**

『你。。你是怎么猜出来？』

小 L 说话之际，看着小 A 的眼神中的惊讶又多了一份崇拜。

「呵，这种难度的问题怎么可能难得到我？」

『啊。既然是这样子的话，那就再来玩一次吧！』

「。。。」

## 样例 #1

### 输入

```
3
2 1 3
3 1 4
5 1 3```

### 输出

```
4 3
5 2
10 7```

# 题解

## 作者：Super_Cube (赞：7)

# Solution
这里是验题人题解。

因为平均值为 $\dfrac{\left(\displaystyle\sum_{i=1}^{n}i \right)-m}{n-1}=a+\dfrac{b}{c}$，所以 $c \mid n-1$，设 $n=c\cdot i+1$。

注意到出题人给的样例中算出的 $i$ 很小，~~我们可以大胆猜测出题人的数据中算出的 $i$ 也会很小~~，考虑暴力枚举 $i$。

以下是这项思路的具体代码实现。
```cpp
for(long long i=1,n,m;;++i){
	n=c*i+1;
	m=(__int128)n*(n+1)/2-(__int128)a*(n-1)-b*i;
	if(m>=1&&m<=n){
		printf("%lld %lld\n",n,m);
		break;
	}
}
```

但是，这样的复杂度肯定是错的，期望得分为 15 pts。

~~其实在我重造数据之前，对于随机数据这种做法跑得飞快，因为 $i$ 此时多数情况下等于 $1$。~~

时间浪费在了枚举了很多无用的值，导致算出的 $m$ 不在正确的范围 $1 \sim n$ 之间。

所以考虑求解不等式来缩小 $i$ 的范围。

下面来推一波式子。
$$
\begin{aligned}
&\because 0<\dfrac{(c\cdot i+1)(c\cdot i+2)}{2}-a\cdot c\cdot i-b\cdot i \le c\cdot i+1
\\\\
&\therefore 0<(c\cdot i+1)(c\cdot i+2)-(2\cdot a\cdot c+2\cdot b)\cdot i \le 2\cdot c\cdot i+2
\\\\
&\therefore 0<c^2\cdot i^2+(3\cdot c-2\cdot a\cdot c-2\cdot b)\cdot i + 2 \le 2\cdot c\cdot i+2
\\\\
&\therefore
\begin{cases}
c^2\cdot i^2+(3\cdot c-2\cdot a\cdot c-2\cdot b)\cdot i + 2 > 0
\\\\
c^2\cdot i^2+(c-2\cdot a\cdot c-2\cdot b)\cdot i \le 0
\end{cases}
\\\\
&\because i>0
\\\\
&\therefore
\begin{cases}
i > \dfrac{-(3\cdot c-2\cdot a\cdot c-2\cdot b)+\sqrt{(3\cdot c-2\cdot a\cdot c-2\cdot b)^2-8\cdot c^2}}{2\cdot c^2}
\\\\
i \le -\dfrac{c-2\cdot a\cdot c-2\cdot b}{c^2}
\end{cases}
\end{aligned}
$$

当然第一个不等式可能无解，此时不用管它。

这样，$i$ 的枚举时间复杂度为 $O(1)$。

上述做法可以通过本题，不过如此冗长的式子令人望而生畏。

下面提供我~~冥思苦想后~~得到的第二种做法，十分简易。

$$
\begin{aligned}
&a+\dfrac{b}{c}=\dfrac{n(n+1)-2m}{2(n-1)}=\dfrac{n}{2}+\dfrac{n-m}{n-1}
\\
&\therefore \begin{cases}
a\le \dfrac{n}{2}+\dfrac{n-m}{n-1}\Longrightarrow a-1\le \dfrac{n}{2}
\\\\
a+\dfrac{b}{c}\ge\dfrac{n}{2}\Longrightarrow a+1\ge \dfrac{n}{2}
\end{cases}
\\
&\therefore2a-2\le n \le 2a+2
\end{aligned}
$$

于是可以直接 $O(1)$ 求出合法的 $n,m$。

至此，本题得到了合理的解决。

---

## 作者：CaoXian (赞：4)

出题人题解。

原本预估的难度是黄，但是从反馈来看的话难度是绿（

---

题意应该很清楚，我的解法是推式子+缩放，一些奇怪的方法可以看 [Super_Cube 的题解](https://www.luogu.com.cn/blog/Legendary-Cube/TFOI-Average-Number)。

$$
\begin{aligned}
&\dfrac{\dfrac{n \times (n + 1)}{2} - m}{n - 1}\\
=&\dfrac{n \times (n + 1) - 2 \times m}{2 \times (n - 1)}\\
=&\dfrac{n \times (n - 1) + 2 \times n - 2 \times m}{2 \times (n - 1)}\\
=&\dfrac{n}{2} + \dfrac{n - m}{n - 1}\\
=&a + \dfrac{b}{c}\\
\end{aligned}
$$

接下来是缩放，也是我认为的这一道题最精彩的部分。

注意到 $1 \leqslant m \leqslant n$，所以 $0 \leqslant n - m \leqslant n - 1$。

所以 $0 \leqslant \dfrac{n - m}{n - 1} \leqslant 1$。

带入到上面的式子后就是：

$$
\dfrac{n}{2} \leqslant \dfrac{n}{2} + \dfrac{n - m}{n - 1} = a + \dfrac{b}{c} \leqslant \dfrac{n}{2} + 1
$$

因为 $\dfrac{b}{c}$ 是最简真分数（也就是小于 $1$），所以又有：

$$
\dfrac{n}{2} - 1 < a \leqslant \dfrac{n}{2} + 1
$$

把它拆成两个不等式并化简：

$$
\begin{cases}
n < 2\times a + 2\\
2 \times a - 2 \leqslant n
\end{cases}
$$

（因为 $n$ 是正整数，所以 $n < 2\times a + 2$ 等价于 $n \leqslant 2\times a + 1$）

最后就得到了：$2 \times a - 2 \leqslant n \leqslant 2 \times a + 1$。

于是可以在这个范围枚举 $n$，也就带一个四倍的常数。

$n$ 得到了之后带回最初的式子就可以得到 $m$ 的值，也就是：

$$
\begin{aligned}
\dfrac{\dfrac{n \times (n + 1)}{2} - m}{n - 1}&= \dfrac{a \times c + b}{c}\\
\dfrac{n \times (n + 1)}{2} - m&= \dfrac{(n - 1) \times (a \times c + b)}{c}\\
m&= \dfrac{n \times (n + 1)}{2} - \dfrac{(n - 1) \times (a \times c + b)}{c}\\
\end{aligned}
$$

因为 $m$ 也是正整数，所以要检查一下 $c$ 能不能整除 $n - 1$。

要注意上面的式子算出来的 $m$ 仍然可能不合法（比如出现负数），以及 $a = 1$ 时 $2 \times a - 2 = 0$ 但是 $n \geqslant 2$ 要判断一下。

运算过程中变量可能超 `long long`，记得开 `__int128` 还有优化运算顺序。

最后给出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar gc
typedef __int128 ll;
#define fu(i, l, r) for(ll i = l; i <= r; ++i)
char gc() {static char ibuf[1 << 20], *p1 = ibuf, *p2 = ibuf; return p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1000010, stdin), p1 == p2) ? -1 : *p1++;}
void read(ll& x) {x = 0; int f = 1; char ch = getchar(); while(ch < '0' || ch > '9') f *= ((ch == '-') ? -1 : 1), ch = getchar(); while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); x *= f;}
ll t, m, a, b, c;
int main() {
	read(t);
	while(t--) {
		read(a), read(b), read(c);
		fu(i, max(2 * a - 2, (ll)2), 2 * a + 1) {
			if((i - 1) % c) continue;
			m = i * (i + 1) / 2 - (i - 1) / c * (a * c + b);
			if(m < 1 || m > i) continue;
			printf("%lld %lld\n", (long long)i, (long long)m);
			break;
		}
	}
	return 0;
}
```

---

## 作者：回声之歌 (赞：3)

### 题意

对于正整数 $a,b,c,n,m$，满足：
- $b$ 与 $c$ 互质。
- $m \in [1,n]$。
- $\dfrac{\left(\sum\limits^{n}_ {i = 1}i \right) - m}{n - 1}=a+\dfrac{b}{c}$（$n \ne 1,c \ne 0$）。

给定 $a,b,c$，求出 $n,m$，并回答 $n$ 较小的一组解，保证有解。

### 分析

显然，需要根据题意对式子进行转化。

- 拆去求和符号，$\sum\limits^{n}_ {i = 1}i = \dfrac{n^2 + n}{2}$ 。

- 变形为两分式相等。

原式化为 $\dfrac{\dfrac{n^2 + n}{2} - m}{n - 1}= \dfrac{ac+b}{c}$。

常规地，令 $\begin{cases} n - 1 = ck, \\ \dfrac{n^2 + n}{2} - m = \left(ac + b \right) k. \end{cases}$（$k$ 为常数）。

得 $\begin{cases} n = ck + 1, \\ m = \dfrac{c^2k^2 + (3c - 2ac - 2b)k + 2}{2}. \end{cases}$。

下面求出 $k$ 的解集。

- 由 $a,b,c,n,m \in \mathbb{N+}$，得 $k \in \mathbb{Z}$。

- 由 $n \in \mathbb{N+}$ 且 $n \ne 1$，得 $n > 1$。

- 由 $m \in [1,n]$，得 $1\le m\le n$。

有 $\begin{cases} ck + 1 > 1, \\ 1\le \dfrac{c^2k^2 + (3c - 2ac - 2b)k + 2}{2}\le ck + 1. \end{cases}$。

得 $k$ 为 $\mathop{\operatorname{max}}\left(1,\dfrac{2ac + 2b - 3c}{c^2}\right)\le k\le \dfrac{2ac + 2b - c} {c^2}$ 的整数。

由题意，可知保证有解，即 $k$ 的解集中必有一个整数解。

又 $n = ck + 1$ 中，$n$ 随 $k$ 的增大而增大，当 $k_{min}$ 时有 $n_{min}$。

则 $k = \mathop{\operatorname{max}}\left(1,\lceil \dfrac{2ac + 2b - 3c}{c^2}\rceil \right)$，无需考虑 $\lceil \dfrac{2ac + 2b - 3c}{c^2}\rceil > \dfrac{2ac + 2b - c} {c^2}$。

$n,m$ 代入求值，解毕。

### 代码

注意到 $1\le a\le 10^{18},\ 0\le b < c\le 10^{18}$，请开 `__int128`。

```cpp
#include <bits/stdc++.h>
using namespace std;
__int128 read() {
	__int128 x = 0, f = 1;
	char c;
	while ((c = getchar()) < 48 || c > 57);
	do x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	return x * f;
}
void write(__int128 x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
__int128 f(__int128 x, __int128 y) {
	if (x % y) return x / y + 1;
	return x / y;
}
int t;
__int128 a, b, c, k, n, m;
int main() {
	for (cin >> t; t; t--) {
		a = read(), b = read(), c = read();
		k = f(2 * a * c + 2 * b - 3 * c, c * c);
		if (k < 1) k = 1;
		n = c * k + 1;
		m = (n * n + n) / 2 - k * (a * c + b);
		write(n), putchar(' ');
		write(m), putchar('\n');
	}
	return 0;
}
```

---

## 作者：UncleSam_Died (赞：1)

### 题目大意
已知 $\frac{(\sum^{n}_ {i}i)-m}{n-1}=a+\frac{b}{c}$ 和 $a$、$b$、$c$，求出 $n$、$m$ 且 $n$ 最小的解。

### 解题思路
其实这道题并不难，主要是分类讨论比较麻烦，大体思路如下：

$\because \frac{(\sum^{n}_ {i}i)-m}{n-1}=\frac{n}{2}+\frac{n-m}{n-1}=a+\frac{b}{c}$

$\therefore$ 即为求 $\frac{n}{2}+\frac{n-m}{n-1}=a+\frac{b}{c}$ 的 $n$ 最小的解。

$\therefore$ 易想到，分类讨论，首先分为两大点讨论：$b$ 为 $0$ 和 $b$ 为 $1$。 

#### 一：当 $b$ 为 $0$ 的时候，$\frac{n}{2}+\frac{n-m}{n-1}$ 为整数。
1. 当 $n$ 能够整除 $2$ 时，有 $n-m$ 整除 $n-1$。此时，当 $n-m$ 等于 $0$ 时，$n=2a$，当 $n-m=n-1$ 时，$n=2a-2$，显然，$n=2a-2$ 比 $n=2a$ 更优，所以，我们优先考虑取 $n=2a-2$。解出后带入原式，判断 $m$ 是否小于等于 $n$ 且大于等于 $1$，如果不满足条件，那么就取 $n=2a$ 并求解。
2. 当 $n$ 不能够整除 $2$ 时，那么 $n=2k+1$，此时 $\frac{n-m}{n-1}=\frac{1}{2}$，$n=2a-1$，没有 $2=2a-2$ 优，舍去。

#### 二：当 $b$ 不为 $0$。
1. 当 $n=2k-1$，$m=\frac{((c-2b)n+2b+c)}{2c}$，同样，算完后带入检验，如果不满足条件，直接舍去。
2. 当 $n=2k$，$m=\frac{n-b(n-1)}{c}$，算完后检验。
3. 当 $n=2k+1$，$m=\frac{((3c-2b)n+2b-c)}{2c}$，计算后带入检验

综上所述，总共分为两大类五小类讨论，按照 $n$ 从小到大的顺序讨论即可，因为保证有解，所以不需要考虑无解的情况。
### AC代码
```cpp
#include<bits/stdc++.h>
#define ull usigned long long
using namespace std;
const string TypideName="c";
inline void readc(char &c){
	c=getchar();
	while(c==' '||c=='\n')
		c=getchar();
}inline void writec(char c){putchar(c);}
template<typename T>inline void read(T& x) {
	if(typeid(x).name()==TypideName){char ch;readc(ch);x=ch;return;}
	x = 0; bool f = false; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = !f; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x = (f ? -x : x); return;
}template<typename T>inline void put(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) put(x / 10);
	putchar(x % 10 + '0'); return;
}template<typename T>inline void write(T x) {
	if(typeid(x).name()==TypideName){writec(x);return;}
	put(x);
}
template<typename T,typename... Args>
inline void read(T& x,Args&...x_) {read(x),read(x_...);}
template<typename T,typename... Args>
inline void write(T x,Args...x_){write(x),write(x_...);}
inline void read(__int128 &x){
	x = 0; bool f = false; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = !f; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x = (f ? -x : x); return;	
}inline void put(__int128 x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) put(x / 10);
	putchar(x % 10 + '0'); return;	
}inline void write(__int128 x){put(x),putchar(' ');return;}
#define ll __int128
inline ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}
ll a,b,c,n,m;
inline void work(){
	read(a),read(b),read(c);
	if(b==0){ 
		n=(a<<1)-2,m=1;
		if(m<1||m>n){
			n=(a<<1),m=n;
		}
		write(n);
		write(m);putchar('\n');
		return;
	}
	bool is=true;
	n=(a<<1)-1;
	if(((c-(b<<1))*n+(b<<1)+c)%(c<<1)!=0) is=false;
	if(is){
		m=((c-(b<<1))*n+(b<<1)+c)/(c<<1);
		if(2*(n-m)<=(n-1)||m<1||m>n) is=false;
		if(is){
			write(n),write(m);
			putchar('\n');return;
		}
	}is=true;
	n=a<<1;
	if((b*(n-1))%c!=0) is=false;
	if(is){
		m=n-b*(n-1)/c;
		if(m<1||m>n) is=false;
		if(is){
			write(n),write(m);
			putchar('\n');return;
		}
	}is=true;
	n=(a<<1)+1;
	if(((3*c-2*b)*n+2*b-c)%(c<<1)!=0) is=false;
	if(is){
		m=((3*c-2*b)*n+2*b-c)/(c<<1);
		if(2*(n-m)>=(n-1)||m<1||m>n) is=false;
		if(is){
			write(n);write(m);
			putchar('\n');return;
		}
	}
}
signed main(){
	int T;read(T);
	while(T--) work();
	return 0;
}



```


---

## 作者：Genius_Star (赞：0)

### 思路：

首先不删掉一个数的平均数是 $\frac{\sum\limits_{i = 1}^n i}{n} = \frac{n + 1}{2}$。

删掉最大的数 $n$ 后的平均数是 $\frac{\sum\limits_{i =1}^{n - 1} i}{n - 1} = \frac{n}{2}$

删掉最小的数 $1$ 后的平均数是 $\frac{\sum\limits_{i = 2}^n i}{n} = \frac{n + 1}{2} - \frac{1}{n}$。

故可以得到：

$$\frac{n}{2} \le a + \frac{b}{c} < \frac{n + 1}{2}$$

注意到 $\frac{b}{c} < 1$，故可以得到 $a$ 的范围应该在 $\frac{n}{2}$ 上下浮动，以此解出 $n$ 的范围，不超过 $10$，直接暴力枚举 $n$。

然后解一下方程推得 $m = \frac{n(n+1)}{2} - \frac{(n - 1)(ac + b)}{c}$，需要判断 $(n - 1)$ 是否是 $c$ 的倍数（因为 $m$ 要是整数）。

时间复杂度为 $O(T)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
typedef __int128 __; 
bool Begin;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
__ T, a, b, c;
inline void solve(){
	a = read(), b = read(), c = read();
	for(__ n = max(a * 2 - 10, (__)2); n <= a * 2 + 10; ++n){
		if((n - 1) % c == 0){
			__ sum = n * (n + 1) / 2 - (n - 1) / c * (a * c + b);
			if(sum < 1 || sum > n)
			  continue;
			write(n);
			putchar(' ');
			write(sum);
			putchar('\n');
			return ;
		}
	}
}
bool End;
int main(){
	T = read();
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：fqEason (赞：0)

## 思路
赛时没想出 $O(1)$ 的解法，这里说一个带一只 $\log$ 的做法

首先我们注意到，输入数据给出的分母 $c$ 一定是原分数分母 $n-1$ 经约分后得到的，不妨设 $n-1 = xc(x \in Z^+)$ 则有：

$n=cx+1,m=\frac{(n+1)\times n}{2}-\frac{(n-1)\times(a\times c+b)}{c}$

可见，对于每一个 $x$，都可以求出一组对应的 $n$ 和 $m$，但是，有些时候   $m$ 是不在题目规定的范围 $[1,n]$ 的，又由上述 $m$ 的公式可以得知，$\frac{(a\times c+b)}{c}$ 是一个定值，那么若求得的 $m<1$，则一定是 $n$ 的值过小，即 $x$ 的值过小，否则，若 $m>n$，则一定是 $x$ 的值过大。

根据这个思路对 $x$ 进行二分即可。令 $N$ 为 $10^{18}$，时间复杂度即为 $O(T\log\frac{N}{c})$，可以通过本题。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
__int128 n,m,a,b,c;//值太大，记得开__int128
inline __int128 read(){
    __int128 x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void print(__int128 n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}//__int128的输入输出需要手写
int check(__int128 x) {
    n=x*c+1;
    m=(n+1)*n/2-(n-1)/c*(a*c+b);
    if (m>=1&&m<=n) return 0;
    else if (m<=0) return 1;
    else return 2;
}//二分的判断函数，如果刚好在1~n的范围内，则返回0，太大返回2，太小返回1
int main() {
    cin >> T;
    while(T--) {
        a=read(),b=read(),c=read();
        __int128 l=1,r=1e18/c,ans=0;//n-1最多是c的1e18倍
        while(l<=r) {
            __int128 mid=(l+r)/2;
            int now=check(mid);
            if (now==0) {
                ans=mid;
                r=mid-1;
            }
            else if (now==1) {
                l=mid+1;
            }
            else {
                r=mid-1;
            }
        }//对x进行二分，求得的ans即可推出n,m
        n=ans*c+1;
        m=(n+1)*n/2-(n-1)/c*(a*c+b);
        print(n);
        cout << ' ';
        print(m);
        cout << endl;
    }
    return 0;   
}
```
## Tips
第 28 行与第 53 行的
```cpp
m=(n+1)*n/2-(n-1)/c*(a*c+b);
```
不能写成
```cpp
m=(n+1)*n/2-(n-1)*(a*c+b)/c;
```
否则会炸  __int128  TAT

---

## 作者：Super_Cube (赞：0)

# Solution

赛场上看到有人用二分过了，补一个二分做法。

跟之前写的题解一样，设 $n=c\cdot i+1$，其中 $i \in \mathbf{N^*}$。

由题意可以推出 $m=\dfrac{n(n+1)}{2}-\left(a+\dfrac{b}{c}\right)(n-1)$。

然后把上面式子带进去，得到 $m=\dfrac{(c\cdot i+1)(c\cdot i+2)}{2}-a\cdot c\cdot i-b\cdot i$。

如果不考虑 $i$ 本身的定义域，你会发现这是一个 $m$ 关于 $i$ 的二次函数，开口向上，对称轴为 $\dfrac{\left(a-\dfrac{3}{2}\right)\cdot c+b}{c^2}$。

所以对称轴往右的函数值一定是单调递增的。

于是我们可以 以对称轴为左边界 开始二分 $i$ 的取值，如果算出的函数值小于 $1$，将左边界右调，否则将右边界左调。

这样做的单次查询时间复杂度为 $O(\log V)$，其中 $V$ 为值域大小，比 std 要劣，但是能够通过此题。

赛场上很多写二分的人左边界取的是 $1$，并非对称轴，这是错误的，能够通过本题的原因是只要右边界足够大，第一次二分得到的 $mid$ 极大概率在对称轴右侧，而又有极大概率算出的函数值小于 $1$，进而导致左边界会右调到对称轴右侧，所以能够算出正确的答案。

有人愿意帮我卡掉这种错误的做法吗？

---

## 作者：Miyamizu_Mitsuha (赞：0)

用的 `__int128`。

先推式子，原式：

$
a+\frac{b}{c}= \frac{\frac{n\times (n+1)}{2}-m}{n-1}$

$= \frac{n\times (n+1)-2\times m}{2\times (n-1)} $

$= \frac{n\times (n-1)+2\times  n-2\times m}{2\times (n-1)} $

$= \frac{n\times (n-1)+2\times(n-m)}{2\times (n-1)} $

$= \frac{n}{2}+\frac{n-m}{n-1}$

然后可以推导出不等式：

$
\begin{aligned}
\begin{cases}
a\le \dfrac{n}{2}+\dfrac{n-m}{n-1}
\\\\
a+\dfrac{b}{c}\ge\dfrac{n}{2}
\end{cases}
\\
\end{aligned}
$

由于正负性和分数的限制，就可以推出 $n$ 的值域:

$
\begin{aligned}
 \begin{cases}
a-1\le \dfrac{n}{2}
\\\\
a+1\ge \dfrac{n}{2}
\end{cases}
\\
\end{aligned}
$

最后就是 $2\times a-2\le n \le 2\times a+2$

由于原式中 $n-1$ 和 $c$ 都是作为分母，所以一定有倍数关系，所以可以枚举这个值域（非常之小）中第一个 $n-1$ 使得 $(n-1)\bmod c=0$。然后直接带回去解 $m$：

假设 $n-1$ 是 $c$ 的 $k$ 倍，即 $k=\frac{n-1}{c}$。

于是原式可以化为：

$\frac{(a\times c+b)\times k}{c\times k}=\frac{\frac{n\times (n+1)}{2}-m}{n-1}$

由于 $c\times k=n-1$，

所以有 $(a\times c+b)\times k=\frac{n\times (n+1)}{2}-m$，

于是 $m=\frac{n\times (n+1)}{2}-(a\times c+b)\times k$。

由于一乘就炸，所以可以用 `__int128`。


```
#include <bits/stdc++.h>
using namespace std;
template <typename _Tp> inline void read(_Tp&x) {
    char ch;bool flag=0;x=0;
    while(ch=getchar(),!isdigit(ch)) if(ch=='-')flag=1;
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    if(flag) x=-x;
}
inline void print(__int128 x) {
    if(x<0) {x=-x;putchar('-');}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
signed main(){
  int t;
  cin>>t;
  while(t--){
    __int128 a,b,c;
    read(a),read(b),read(c);
    for(__int128 i=2*a-2;i<=2*a+2;i++)
    {
      if(i<=1)continue;
      if((i-1)%c==0)
      {
        if(i>=1&&i*(i+1)/2-(a*c+b)*((i-1)/c)>=1){
          print(i);
          cout<<" ";
          print(i*(i+1)/2-(a*c+b)*((i-1)/c));
          cout<<endl;
          break;
        }
      }
    }

  }
return 0;
}

```


---

## 作者：Noby_Glds (赞：0)

# 题目大意
原有 $n$ 个数 $1$ 到 $n$，从中抽掉一个数 $m$，给你剩下这些数的平均值，问最小的 $n$ 及其对应的 $m$。
# 解题思路
## 寻找 $n$ 的可能最小值
我们令剩下数的平均值为 $x$，那么原有 $n$ 个数时，我们可以求出 $x$ 的大致范围，也就是 $x$ 的最大值和最小值。

抽走 $1$ 时，$x_{max}=\dfrac{(n+2)(n-1)}{2(n-1)}=\dfrac{n}{2}+1$。

抽走 $n$ 时，$x_{min}=\dfrac{n(n-1)}{2(n-1)}=\dfrac{n}{2}$。

所以，原有 $n$ 个数时，$\dfrac{n}{2}\le x\le\dfrac{n}{2}+1$。

由此，在已知 $x$ 时，我们可以知道 $n$ 的范围：$2x-1\le n\le2x$，$n$ 的**可能的**最小值便可以求出来。

为什么说是可能，因为我们知道 $\dfrac{n}{2}\le x\le\dfrac{n}{2}+1$，但不是这个范围内的所有值都可以被取到，这只是一个大致的范围。

同理可知，$2x-1\le n\le2x$ 内不是每一个整数都是可行的，那如何判断我们手上的 $n$ 是否可行？

很明显，只要我们能找出一个合法的 $m$，这个 $n$ 便是可行的，所以我们先来找出求 $m$ 的方法。
## 寻找 $m$ 的值
一种很简单的方法是，我们知道 $n$ 和 $x$，可以直接代入把 $m$ 解出来，得到 $m=\dfrac{n(n+1)}{2}-x(n-1)$。

**但是**，这个式子会爆 long long（我知道很多人都用了 __int128，现在假设我们不知道这东西）。

不妨换一种思路，我们找到 $n$ 对应的 $x_{max}=\dfrac{n+1}{2}$，将它与 $x$ 相比较。

$$x_{max}-x=\dfrac{(n+2)(n-1)}{2(n-1)}-\dfrac{n(n+1)-2m}{2(n-1)}=\dfrac{m-1}{n-1}$$

由此可得，$m=(x_{max}-x)(n-1)+1$。

为什么这个式子不会爆 long long？

因为 $m$ 是整数，所以 $x_{max}-x$ 这个分数必定是可以被 $(n-1)$ 约分成整数的，所以不用担心分子爆 long long 的问题。

另外我们还由此获得了检验 $n$ 是否可行的方法：若 $x$ 无法被 $(n-1)$ 约分成整数，那么 $n$ 不可行（$x_{max}$ 必定是可以被约成整数的，所以不用考虑）。

如果 $n$ 不可行，就加 $1$ 继续检验就可以了。

细节较多，要注意一下。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,c;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		long long pos=(a-1)*2;
		if(2*b>c) pos+=2;
		else if(b) pos++;
		pos=max(pos,2ll);
		while((pos-1)%c) pos++;
		long long x=pos/2+1,y=0;
		if(pos%2) y=(pos-1)/2;
		b*=(pos-1)/c;
		cout<<pos<<" "<<(x-a)*(pos-1)+(y-b)+1<<endl; 
	}
	return 0;
}
```


---

## 作者：sbno333 (赞：0)

这可以是一道二分查找的题，我觉得应当评黄。

众所周知，$\dfrac{ac+b}{c}=\dfrac{\left(\sum\limits^{n}_ {i = 1}i \right) - m}{n - 1}$。

由于 $\left(\sum\limits^{n}_ {i = 1}i \right) - m$ 是整数，因此 $n-1=s\times c,\left(\sum\limits^{n}_ {i = 1}i \right) - m=s\times(ac+b)$。

其中 $s$ 是我们需要找的一个整数值，不难推出，当 $m \in [1, n]$ 时，我们就找到了一个答案。

因此我们只需二分查找 $s$ 的值即可。

不难发现，随着 $s$ 的增加，$\sum\limits^{n}_ {i = 1}i$ 比 $s\times(ac+b)$ 增长的快，$m$ 逐渐变大，因此，二分查找时算出的 $m$ 如果大于 $n$ 时，$s$ 过于大，进行缩小，如果小于 $1$，则扩大。

对于 $m\in[1,n]$ 的情况，应当缩小或不变。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		__int128 a,b,c;
		long long a1,a2,a3;
		cin>>a1>>a2>>a3;
		a=a1;
		b=a2;
		c=a3;
		b+=a*c;
		__int128 l,r;
		l=1;
		r=1e18;
		r/=c;
		while(l<r){
			__int128 mi;
			mi=(l+r)/2;
			__int128 x,y;
			x=mi*c;
			y=mi*b;
			__int128 vv;
			x++;
			vv=x;
			x=x*x+x;
			x/=2;
			x-=y;
			if(x<1){
				l=mi+1;
			}else{
				r=mi;
			}
		}
		__int128 x,y,z;
		x=r*c;
		y=r*b;
		x++;
		z=x;
		x=x+x*x;
		x/=2;
		x-=y;
		a1=z;
		a2=x;
		cout<<a1<<" "<<a2<<endl;
	}
	return 0;
}
```

码风丑陋，见谅，此处使用`__int128`存储，否则可能会爆掉。

---

