# 『STA - R4』And

## 题目描述

给定非负整数 $A, B$，定义有序非负整数对 $(x, y)$ 为好的当且仅当：

- $0 \le x \le y$；
- $x + y = A$；
- $x \operatorname{AND} y = B$。

其中 $\operatorname{AND}$ 代表按位与运算。在 C++ 语言中由 `&` 运算符表示。

你需要求出所有好的有序非负整数对 $(x, y)$ 的 $y - x$ 的和。

由于该值可能很大，你只需要输出其对 $M$ 取模后的结果。

形式化的，你需要求出

$$\left(\sum\limits_{x \ge 0}\sum\limits_{y \ge 0}\left(y - x\right)\left[\operatorname{good}(x, y)\right]\right)\bmod M$$

其中 $\operatorname{good}(x, y)$ 为真与有序非负整数对 $(x, y)$ 为好的等价。

## 说明/提示

**【样例 #1 解释】**

对于第一组询问，好的数对有 $\left(1, 7\right)$ 和 $\left(3, 5\right)$，因此答案为 $\left(7 - 1\right) + \left(5 - 3\right) = 8$。

对于第二组询问，好的数对只有 $\left(4, 6\right)$，因此答案为 $6 - 4 = 2$。

对于第三组询问，好的数对有 $\left(0, 6\right)$ 和 $\left(2, 4\right)$，因此答案为 $\left(6 - 0\right) + \left(4 - 2\right) = 8$。

**【样例 #2 解释】**

其所有询问均满足子任务 1 的限制，且后两组询问同时满足子任务 3 的限制。

特别的，在第三组询问的限制下，不存在好的有序非负整数对，因此答案为 $0$。

**【样例 #3 解释】**

其所有询问均满足子任务 2 的限制。

**【样例 #4 解释】**

其所有询问均满足子任务 4 的限制。

特别的，在第四、五组询问的限制下，不存在好的有序非负整数对，因此答案为 $0$。

**【数据范围】**

**本题采用捆绑测试。**

对于 $100\%$ 的数据：

- $1 \le T \le 3 \times 10^5$；
- $0 \le A, B < 2^{60}$；
- $5 \le M \le 1.1 \times 10^9$；
- $M$ 为质数。

具体部分分分配如下：

|Subtask 编号|数据范围|分值|
|:--------:|:--------:|:--------:|
|1|$T \le 200, 0 \le A, B \le 8 \times 10^5$|$15$|
|2|对于每组询问，好的数对个数不超过 $1000$ 个|$25$|
|3|$B = 0$|$25$|
|4|无特殊限制|$35$|

## 样例 #1

### 输入

```
3 23
8 1
10 4
6 0
```

### 输出

```
8
2
8
```

## 样例 #2

### 输入

```
6 883
196483 132
330788 4353
137168 35030
615316 264202
387442 0
407154 0
```

### 输出

```
579
432
0
27
807
845
```

## 样例 #3

### 输入

```
3 30996377
948664793464517468 401148893358688606
945266152577109588 398323527798785832
185133025738933982 77893802910442339
```

### 输出

```
29793121
28589865
30695563
```

## 样例 #4

### 输入

```
5 992362009
248232552654965455 563160474979616
553521216364206023 14357560845404368
668113789984338832 146840018434951169
620025528908068087 506797735136774536
522926854352266209 860580850297773973
```

### 输出

```
150959267
319548082
888288513
0
0
```

# 题解

## 作者：User_Unauthorized (赞：26)

可以发现，$x \operatorname{AND} y$ 对应了在二进制加法中进位的位置集合，$x \operatorname{XOR} y$ 对应了结果中为 $1$ 但是没有进位的位置集合。因此，通过用位运算模拟加法的过程，我们可以得出

$$x + y = 2 \times \left(x \operatorname{AND} y\right) + x \operatorname{XOR} y$$

因为已知 $x + y$ 和 $x \operatorname{AND} y$，因此可以得到 $x \operatorname{XOR} y$，设为 $C$。

那么所有可能的合法数对可以通过将 $C$ 二进制下的 $1$ 分配给 $x$ 或 $y$ 得到。注意到若 $C \operatorname{AND} B$ 不为 $0$ 那么不存在合法的分配方案，此时应按无解处理。

通过一些观察可以发现 $C$ 二进制下最高位的 $1$ 一定分配给 $y$，否则无法保证 $x \le y$。在这之后的所有情况均合法，所以可以发现对于一种方案，将 $C$ 二进制下除最高位的其他位分配方案取反，得到的方案也是合法的，且与原方案互补。

所以只会有 $C$ 二进制下最高位的 $1$ 产生贡献，贡献系数为剩余位数的方案数，即 $2 ^{\operatorname{popcount}\left(C\right) - 1}$。

因此我们可以在 $\mathcal{O}\left(1\right)$ 的时间内回答每组询问。

---

## 作者：___w (赞：10)

[P10118 『STA - R4』And](https://www.luogu.com.cn/problem/P10118)

[更好的阅读体验？](https://www.cnblogs.com/123wwm/articles/18002286)

### 题目分析

这道题感觉不错。

先从 $x \operatorname{AND} y = B$ 下手。

若 $B$ 中第 $x$ 位的数为 $1$，那么 $x$ 和 $y$ 对应的这一位必须为 $1$；若 $B$ 中第 $x$ 位的数为 $0$，那么 $x$ 和 $y$ 对应的这一位不能有一个为 $1$（废话）。

所以我们可以写钦定 $x=y=B$，这样才满足 $x \operatorname{AND} y = B$，所以 $A\le 2B$ 可以特判 $0$ 了。

那么这样 $A$ 仍有 $A-2B$ 要分配，分配在 $x,y$ 的某些位置上，很显然一个位置不能分配两个 $1$ 在 $x,y$ 上。令 $k=A-2B$，那么它二进制下的每个 $1$ 就意味着要分到 $x,y$ 上。当然若 $k \operatorname{AND} B \ne 0$ 的话也是无解。

$k$ 的 $1$ 要怎么分配？因为有 $x\le y$，所以最高位置上的 $1$ 应该给到 $y$，然后后面的几位就可以随意的分到 $x,y$ 了，然后答案就是这些所有情况的差值之和了，然后怎么求呢？

举个例子，对于 $k=(10110)_2$，$x=y=B=(1001)_2$，所有答案为：

$x=(1001)_2+(00\textcolor{red}{11}0)_2,y=(1001)_2+(10000)_2$

$x=(1001)_2+(00\textcolor{red}100)_2,y=(1001)_2+(100\textcolor{red}{1}0)_2$

$x=(1001)_2+(000\textcolor{red}10)_2,y=(1001)_2+(10\textcolor{red}{1}00)_2$

$x=(1001)_2+(00000)_2,y=(1001)_2+(10\textcolor{red}{11}0)_2$

记 $pos$ 为 $k$ 的最高位的下标，记 $s$ 为 $k$ 去除最高位后的数，$c$ 为 $s$ 在二进制下的 $1$ 的个数。所有红色部分构成了 $s$ 的所有子集，这些子集之和为 $2^{c-1}s$，那么答案可以理解为 $k$ 减去一个子集后再减去一个子集。答案为 $2^ck-2\times2^{c-1}s=2^ck-2^cs=2^c\times 2^{pos}$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f = c == '-' ? -1 : f, c = getchar();
	while (c >= '0' && c <= '9') x = (x<<3)+(x<<1)+(c^48), c = getchar();
	return x*f;
}

inline void write(int x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x/10);
	putchar('0'+x%10);
}

int t, m;

int solve() {
	int a = read(), b = read(), x = a-b*2;
	if (b*2 >= a || x&b) return 0;
	int pos = 63-__builtin_clzll(x), c = __builtin_popcountll(x^(1ll<<pos));
	return (1ll<<c)%m*((1ll<<pos)%m)%m;
}

signed main() {
	t = read(), m = read();
	while (t--) write(solve()), enter;
	return 0;
}
```

---

## 作者：wxzzzz (赞：9)

### 思路

题目要求的原式为:

$$\sum_{x\ge 0}\sum_{y\ge 0}\left(y-x\right)\left[ x+y=A,x\operatorname{AND}y=B\right]$$

因为 $x\operatorname{AND}y=B$，必然有 $B\le x\le y$，故原式可化为：

$$\sum_{x\ge 0}\sum_{y\ge 0}\left(y-x\right)\left[ (x-B)+(y-B)=A-2B,(x-B)\operatorname{AND}\ (y-B)=0\right]$$

考虑利用二进制规律求出上式。

当 $A-2B=7=(111)_2$ 时，所有 $x,y$ 组合为：

1. $\begin{cases}x=(010)_2\\y=(101)_2\end{cases}$

1. $\begin{cases}x=(001)_2\\y=(110)_2\end{cases}$

1. $\begin{cases}x=(011)_2\\y=(100)_2\end{cases}$

1. $\begin{cases}x=(000)_2\\y=(111)_2\end{cases}$

重组该四种组合：

1. $\begin{cases}x=(010)_2\\y=(110)_2\end{cases}$

1. $\begin{cases}x=(001)_2\\y=(101)_2\end{cases}$

1. $\begin{cases}x=(011)_2\\y=(111)_2\end{cases}$

1. $\begin{cases}x=(000)_2\\y=(100)_2\end{cases}$

每组的 $y-x$ 都是 $(100)_2$。

至此可以大胆地猜一个结论：

> 令 $A-2B$ 二进制下有 $cnt$ 位是 $1$， $A-2B$ 二进制下最高位为 $bit$，$x,y$ 的合法组数为 $2^{cnt-1}$，$\sum y-x$ 为 $2^{cnt-1}\times2^{bit}$。

（下文中，为方便表述，均用 $x,y$ 分别代指 $x-B,y-B$）

试着证明这个结论：

- 先证明 $x,y$ 的合法组数为 $2^{cnt-1}$：
	
    因为 $y\ge x$，且 $x\operatorname{AND}y=0$，所以在二进制下，$y_{bit}=1,x_{bit}=0$，余下任意的第 $i\in[0,bit-1]$ 位上，有 $x_i=1$ 或 $y_i=1$，方案数为 $2^{cnt-1}$。

- 接着证明 $\sum y-x=2^{cnt-1}\times 2^{bit}$。
	
    令 $x=\overline{u}$，故 $y=2^{bit}+\overline{v}$。
    
    此时有合法组合 $\begin{cases}x'=\overline{v}\\y'=2^{bit}+\overline{u}\end{cases}$
    
    所以 $y'-x=2^{bit},y-x'=2^{bit}$。

最后考虑判断无解。

显然，当 $A-2B\le 0$，或 $(A-2B)\operatorname{AND}B>0$，没有合法的 $x,y$ 组合。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, m, a, b, c, cnt, bit;
long long mod(long long x) {
    return x % m;
}
int main() {
    cin >> t >> m;

    while (t--) {
        cin >> a >> b;
        c = a - b * 2, cnt = bit = 0;

        for (int i = 1; i <= 60; i++)
            if (c >> i - 1 & 1)
                cnt++;

        for (int i = 60; i >= 1; i--) {
            if (c >> i - 1 & 1) {
                bit = i - 1;
                break;
            }
        }

        if (c <= 0 || c & b)
            cout << "0\n";
        else
            cout << mod(mod(1ll << cnt - 1)*mod(1ll << bit)) << '\n';
    }

    return 0;
}
```

---

## 作者：zjpwdyf (赞：7)

首先，我们要知道一个东西：$x+y=2 \times (x \operatorname{and} y) +(x\operatorname{xor} y)$。

我们采取按位考虑的方法来证明这个等式。

设 $x_i$ 表示 $x$ 的二进制形式下，第 $i$ 位表示的数 $(0/1)$，$y_i$ 同理。

则不难发现，在 $x_i,y_i$ 的所有取值下，等式都成立。

故将每一位合并之后，等式仍然成立，证毕。

所以本题中，$x\operatorname{xor} y=x+y-2 \times (x \operatorname{and} y)=A-2B$，设 $C=A-2B$。

将 $C$ 二进制分解后，进行按位处理：

$\hspace{0.5cm}$ 若 $C$ 的第 $i$ 位为 $0$，则说明 $x_i=y_i$，不会给答案带来任何贡献，不用讨论。

$\hspace{0.5cm}$ 若 $C$ 的第 $i$ 位为 $1$，则说明 $x_i \neq y_i$，此时需要分类讨论：

$\hspace{1.0cm}$ 如果当前是最高位的 $1$，那么为了保证 $x\le y$，必须将 $1$ 分配给 $y$。

$\hspace{1.0cm}$ 如果当前不是最高位的 $1$，则任意分配。

现在来考虑最终答案：

不难发现，在任意分配的二进制位下，这一位并没有给答案作出贡献，因为一正一负刚好抵消。

所以唯一给答案作出贡献的位为最高位的 $1$。

设 $C$ 的二进制形式中有 $k$ 个 $1$。

则最终答案为 合法分配方案数 $\times$ 最高位单次作出的贡献，即 $2^h\times 2^{k-1}=2^{h+k-1}$（其中 $h$ 为 $C$ 最高位 $1$ 的下标）。

所以只需要 $O(T\log A)$ 统计即可。

---

注意需要特判一些无解的情况：

1. 若 $C<0$，说明 $x\operatorname{xor} y <0$，显然无解。

2. 若 $B$ 的某一位为 $1$，说明 $x_i=y_i=1$，$x_i \operatorname{xor} y_i=0$，然而若 $C$ 的第 $i$ 位为 $1$，则与本文开头的等式不符。

3. 若 $C$ 为 $0$，则无法分配。

---

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll q, mod, a, b, c;
ll h, k;
ll qpow(ll base, ll p){ //快速幂 
	ll res = 1;
	while(p){
		if(p & 1) res = res * base % mod;
		base = base * base % mod;
		p >>= 1;
	}
	return res;
}
int main(){
	cin >> q >> mod;
	while(q--){
		h = k = 0;
		cin >> a >> b;
		c = a - 2 * b;
		if(c <= 0 || (b & c)){ //无解情况
			cout << "0\n";
			continue;
		}
		bitset <64> Bit(c);
		for(int i = 63; i >= 0; i --){
			if(!Bit[i]) continue;
			if(!h) h = i; //统计最高位 
			k ++; //统计 0 的个数 
		}
		cout << qpow(2, h + k - 1) << endl;
	}
	return 0;
}
```

---

这是本蒟蒻的第二篇题解。如果有不明白的地方，可以在评论区指出或私信本人，谢谢！

---

## 作者：EternalHeart1314 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P10118)

# 思路

第一次场切绿题，激动！！！

首先显而易见的把 $A$ 和 $B$ 都转化成二进制，例：

$A=13=(1101)_2$，$B=0=(0)_2$。

那么 $\operatorname{good}(x,y)$ 有：

$y=(1101)_2$，$x=(000)_2$；

$y=(1100)_2$，$x=(001)_2$；

$y=(1001)_2$，$x=(100)_2$；

$y=(1000)_2$，$x=(101)_2$。

答案即为：$\sum y-x=32$。

（这里把 $x$ 按位对齐了。）

你会发现，对于 $A$ 最高位的 $1$，它只会出现在 $y$ 里；其它的 $1$，要么出现在 $y$ 里，要么出现在 $x$ 里。

$2^2$，即 $(100)_2$ 在所有 $y$ 中出现了 $2$ 次，在所有 $x$ 中也出现了 $2$ 次，这样就抵消了。

$y$ 和 $x$ 中并没有 $2^1$，即 $(10)_2$。

$2^0$，即 $(1)_2$ 在所有的 $y$ 和 $x$ 中也都出现了 $2$ 次，都抵消了。

这样，就只剩下 $4$ 个 $2^3$，即 $(1000)_2$ 在所有的 $y$ 里都出现了，一共有 $4$ 个 $y$。

那么，最终的答案就是 $4\times 2^3=32$。

发现规律了！

答案即为：$2^{cnt-1}\times s$，$cnt$ 为 $A$ 在二进制中数位上 $1$ 的个数，$s$ 为 $A$ 在二进制中最高位的 $1$ 的值。

但是，我们刚才考虑的是 $B=0$ 的情况，那 $B\neq0$ 呢？例：

$A=8=(1000)_2$，$B=2=(10)_2$。

我们发现，$x\operatorname{AND}y=B$，那么 $B$ 的某位是 $1$，$x$ 和 $y$ 的那位都必须为 $1$。这样，$x$ 和 $y$ 都至少为 $B$，我们可以让 $A-B\times2$。

接下来，就是判无解情况，即没有一个 $\operatorname{good}(x,y)$。

第一种：$A-B\times2<0$，我们把 $A-B\times2=0$ 的情况也作无解，因为 $A-B\times2=0$ 的答案就是 $0$。

第二种：$(A-B\times2)\operatorname{AND}B\neq 0$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T, mod, a, b;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T >> mod;
	while(T --) {
		cin >> a >> b;
		if((a -= b << 1) <= 0 || a & b) {
			cout << 0 << '\n';	//无解情况：a <= 0 或 a & b != 0 
		} else {
			cout << (1LL << __builtin_popcountll(a) - 1) % mod * ((1LL << (int)log2(a)) % mod) % mod << '\n';
				//公式：2 ^ (cnt - 1) * s 
				//现在的 a 就是 s 
				//记得取模 
		}
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：2huk (赞：4)

首先分析这样一组数据：

$$
A = (1010)_2 = (10)_{10}\\
B = (0100)_2 = (4)_{10}
$$

我们希望最终 $x \operatorname{AND} y = B$，也就是希望 $x, y$ 的第 $2$ 位（从右往左数，首位为第 $0$ 位）都为 $1$，其余位都至少有一个 $0$。即：

$$
x = (?1??)_2\\
y = (?1??)_2
$$

同时需要保证 $x + y = A$，列竖式就是：

$$
x:(?\ 1\ ?\ ?)_2\\
y:\underline{(?\ 1\ ?\ ?)_2}\\
A:(1\ 0\ 1\ 0)_2
$$

接下来令 $x$ 的第 $i$ 位为 $x_i$，$y$ 的第 $i$ 位为 $y_i$，$A$ 的第 $i$ 位为 $z_i$。

依次分析 $i = (0, 1, 2, 3)$：

- 对于 $i = 0$，我们需要使得 $x_i + y_i = z_i = 0$，那么显然 $x_i = y_i = 0$ 或 $x_i = y_i = 1$。但如果它们是 $1$ 就不满足 $x \operatorname{AND} y = B$ 这个条件。因此 $x_0 = y_0 = 0$；
- 对于 $i = 1$，我们需要使得 $x_i + y_i = z_i = 1$，那么有两种情况：
	- $x_1 = 1, y_1 = 0$；
   - $x_1 = 0, y_1 = 1$。
- 对于 $i = 2$，此时 $x_i, y_i$ 都被确定为 $1$，且 $z_i = 0$。那么就代表此时我们并不需要考虑构造 $x_i$ 和 $y_i$。因此直接看下一位。注意此时**产生了一个进位**。
- 对于 $i = 3$，此时 $x_i + y_i + 1 = z_i = 1$。这里的 $+1$ 是因为在上一位产生了进位。此时 $x_i, y_i$ 的取值与 $i = 0$ 的情况一样，即 $x_3 = y_3 = 0$。

此时，我们构造出了两种情况，即

$$
x = (0110)_2 = (6)_{10}\\
y = (0100)_2 = (4)_{10}
$$

以及

$$
x = (0100)_2 = (4)_{10}\\
y = (0110)_2 = (6)_{10}
$$

验证可以发现确实满足要求。但是发现第二组数据并不满足 $x \le y$ 的条件，因此我们只计算第一组的答案，即 $6 - 4 = 2$。

为了方便，我们最开始先不判断 $x, y$ 的大小关系，而是将它们所有差的绝对值相加，最后除以二。即 $\dfrac 12 (|6 - 4| + |4 - 6|) = 2$。容易证明这样做是正确的。

---

在实现上，我们先将 $A$ 和 $B$ 拆分成二进制，存入数组 $a_i, b_i$。接下来考虑 dfs 模拟上述过程：

- [代码 1](https://www.luogu.com.cn/paste/n9ga7btl)。

注意由于计算过程中没取模，所以要开 `__int128`。

这样的时间复杂度最劣情况下 $2^{62}$，是无法接受的。

我们将 dfs 改写成有返回值的函数，让 `void dfs(int u, bool k, int s)` 变成 `int dfs(int u, bool k)`，让它的返回值为 `int s`。于是：

- [代码 2](https://www.luogu.com.cn/paste/sj27hwmp)。

然后就可以记忆化了：

- [代码 3](https://www.luogu.com.cn/paste/7rlsdvql)。

那么此时的复杂度就是 $2 \times 62$ 的了，因为转移是 $\mathcal O(1)$ 的。

但是是[不能过的](https://www.luogu.com.cn/record/145590050)。

---

原因是什么呢？构造这样一组数据：

$$
x:(?\ ?\ ?\ 1)_2\\
y:\underline{(?\ ?\ ?\ 1)_2}\\
A:(0\ 0\ 0\ 1)_2
$$

你会发现一组合法的解都不存在，因为首位就不可能 $1 + 1 = 1$！

这也就对应了 [dfs](https://www.luogu.com.cn/paste/7rlsdvql) 中的最后一行 `return 0`，这表示是不存在任何一种合法方案的。但是在回溯时，仍然可能被计算上。

为了解决这个问题，我们再定义数组 `can[u][k]`，表示 `dfs(u, k)` 的状态是否存在，然后将 `dfs` 的返回值改为 `pair<int, bool>`，前者表示实际的答案，后者表示是否存在答案。那么代码为：

- [代码 4](https://www.luogu.com.cn/paste/tm220i20)。

终于 AC 了。最终 [record](https://www.luogu.com.cn/record/145611045) & [code](https://www.luogu.com.cn/paste/pjt8rhnb)。

---

## 作者：BIG_CUTE_BUG (赞：4)

[题传](https://www.luogu.com.cn/problem/P10118)

最近洛谷比赛好多位运算好题啊。

官方题解写得熟能生巧（？），一目了然（？），运筹帷幄（？），信手拈来（？），和我的思路基本相同，所以就只好用冗杂的数学语言推一下了。

~~以及贡献最短解。~~

## 思路

下文所说的位均指二进制下的位。

设 $[\text{good}(x,y)]$ 为真。

$x\text{ AND } y=B$，说明对某一位，若 $B$ 在该位的值为 $1$，对应的在 $x$ 和 $y$ 中的该位值也同为 $1$。

那么令 $x'=x-B,y'=y-B$，此时 $x'$ 与 $y'$ 的任意位都不同为 $1$，即  $x'+y'$ 不进位。

同时因为 $B$ 的各位中，某一位为 $1$ 代表该位 $x$ 和 $y$ 同为 $1$，所以也有
$$x'\text{ AND } B=0,y'\text{ AND } B=0$$

又 $x'+y'$ 不进位，则
$$(x'+y')\text{ AND } B=0$$

又 $x+y=A$，即 $x'+y'=A-B\times 2$。令 $A'=A-B\times 2$，则
$$A'\text{ AND } B=0$$

同时 $0\le x\le y$，又 $x\text{ AND } y=B$ 即 $B\le x\le y$，则 $0\le x'\le y'$，则
$$A'\ge 0$$

综上，$A'\ge 0$ 且 $A'\text{ AND } B=0$ 时，$x,y$ 有解；反之无解。

接下来再计算答案。

首先无解时答案为 $0$。

再看有解怎么算答案。

记 $A'$ 二进制下 $1$ 的个数为 $\text{popcount}(A')$。

要求 $\sum y-x$，也就是求 $\sum y'-x'$。

因为 $x\le y$，所以 $A'$ 的最高有效位是一定分给 $y'$ 的。

剩下 $\text{popcount}(A')-1$ 位就随意分配。

对于第 $i$ 位且其值为 $1$，有两种情况（$i$ 从右往左数，从 $0$ 开始编号）：

1. 分给 $y'$ 对答案做出 $+2^i$ 的贡献。

2. 分给 $x'$ 对答案做出 $-2^i$ 的贡献。

而这两种情况的数量都是一样的（剩下 $\text{popcount}(A')-2$ 为 $1$ 位，每位都有两种情况，所以总共 $2^{\text{popcount}(A')-2}$），因此总可以抵消，所以最终对答案有贡献的也就是 $A'$ 的最高有效位，且每种情况都对答案有贡献。

总共 $2^{\text{popcount}(A')-1}$ 种情况，将其乘以 $2^{\text{popcount}(A')-1}$ 就是最终答案。

## Code

~~喜提最短解（也许吧）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a, b, p;
int t;
signed main()
{
	ios:: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>> t>> p;
	while(t--)
	{
		cin>> a>> b;
		cout<< ((((a= a- (b<< 1))<= 0) || (a& b)) ? 0 : (((1ll<< (__builtin_clzll(a)^ 63))% p* ((1ll<< (__builtin_popcountll(a)- 1))% p))% p))<< '\n';
	}
	return 0;
}
```

---

## 作者：dongrunxuan (赞：2)

# P10118 题解

## 前言 

比赛没来得及打，回来补篇题解。~~虽然我打了也不能拿多少分。~~

## 思路

通过审题，查阅资料，~~问教练无果~~这么几个环节，我们可以~~轻而易举地~~发现：
$$ x+y=2 \times x \operatorname{and}y+x \operatorname{xor} y  $$
证明：在 $x+y$ 中，用二进制数的角度来看，可以分为 $x$ 单独有的部分，$y$ 单独有的部分和 $x$ 与 $y$ 都有的部分，而 $x$ 单独有的部分加上$y$ 单独有的部分就是 $x\operatorname{xor} y$,$2 \times x\operatorname{and}y$ 就是 $x$ 与 $y$ 都有的部分。

#### 通过如上操作，可以算出 $xXOR y$ 的值，记作 $C$。

注意，这里有一个坑点，需要判断 $C$ 是否合法，不然就会像[这样](https://www.luogu.com.cn/record/145972283)。

下面我们发现，由于 $x \le y$，所以 $C$ 二进制最高位位上的 $val$ 一定贡献给了 $y$，剩下二进制位上 $cnt-1$ 个 $1$ 随意分配给两个数，共有 $2^{cnt-1}$ 种可能。而相反的两种分配方式加起来等于 $2\times val$，故答案为 $2\times val\times \frac{2^{cnt-1}}{2}$，即 $val\times2^{cnt-1}$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,mod,a,b,c;
signed main()
{
 	cin>>t>>mod;
 	while(t--)
 	{
 		cin>>a>>b;
		c=a-2*b;
		if(c<0||c&b)
		{
			cout<<0<<endl;
			continue;	
		}	
		int cnt=0,val=0;
		for(int i=0;i<=62;i++)
		{
			int tc=c>>i;
			if(tc&1)
			{
				cnt++;
				val=1ll<<i;
			}
		}
		val%=mod;
		int ccnt=1ll<<(cnt-1);
		ccnt%=mod;
		int ans=val*ccnt;
		cout<<ans%mod<<endl;
	}
 	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

首先大眼观察法可得：

$$x+y=(x\oplus y)+2(x\wedge y)$$

题目给了 $x+y$ 和 $(x\wedge y)$ 的值，所以可得：

$$x\oplus y=A-2\times B$$

然后考虑逐位分类讨论：

对于第 $i$ 位，$x\oplus y$ 和 $x\wedge y$ 分别有 $2$ 钟情况，一共有 $4$ 种情况。

下设 $x\oplus y$ 和 $x\wedge y$ 第 $i$ 位分别是 $a$ 和 $b$。

$x$ 和 $y$ 第 $i$ 位分别是 $c$ 和 $d$


1. $a=0,b=0$

只能 $c = 0, d = 0$

2. $a=1,b=1$

无解.

3. $a=0,b=1$

$c=1,d=1$

4. $a=1,b=0$

这时就有两种情况了：

$c=1,d=0$ 或者 $c=0,d=1$

不难发现 $1\ 3$ 两种情况对答案没有贡献，所以考虑情况 $4$。

首先题目有约束：$x>y$，所以从高往低第一次出现情况 $4$ 时只能 $c=1,d=0$，对答案有贡献 $2^i$，后面出现的两种情况均可，但是不难发现 $c=0,d=1$ 会与 $c=1,d=0$ 的差抵消，只会将情况数 $\times2$，所以答案就出来了：

$$2^{i+a-1}$$

注意判一下无解的情况。

---

## 作者：hh弟中弟 (赞：2)

[题目](https://www.luogu.com.cn/problem/P10118)

看到位运算，直接二进制拆分考虑。

首先 $x \operatorname{AND}y=B$，设 $x=B+m$，$y=B+n$，知道 $x+y=A$，所以设 $W=n+m=A-2\times B$，$y-x$ 等价于 $n-m$。

因为已知 $x\operatorname{AND}y=B$，所以 $n\operatorname{AND}m=0$，着意味着在二进制下 $n$ 和 $m$ 不存在某一位上都是 $1$，我们将 $W$ 进行二进制拆分为 $n$ 和 $m$。

设 $w=\sum\limits_{i=1}^{tot}2^{p_i}$，它在二进制下一共有 $tot$ 个 $1$，构成集合 $U$，考虑如何将这些 $1$ 分配给 $n$ 和 $m$。

首先从左往右数的第一个 $1$ 要分配给 $n$ 保证 $n>m$，然后我们设剩下的 $1$ 分配给 $n$ 的为集合 $Sn$，则分配给 $m$ 的 $1$ 构成的集合为 $\complement_{U}Sn$，那么此时也必有一种情况为分配给 $n$ 的为集合 $\complement_{U}Sn$，分配给 $m$ 的为集合 $Sn$，两种情况彼此抵消，最后会产生 $2\times2^{p_1}$ 的贡献，也就是说一种情况只会产生一次 $2^{p_1}$ 的贡献。

情况总数为 $2^{popcount(W)-1}$，答案就是
$$ans=2^{p_1}\times2^{popcount(W)-1}$$

关于不合法的情况我们在前面已经提到过了，$n$ 和 $m$ 必须要满足$n\operatorname{AND}m=0$，所以 $W\operatorname{AND}B=0$，否则为不合法。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
inline int read(){
    char ch=getchar();int x=0,f=1;
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
signed main(){
    // freopen("in.in","r",stdin),freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0),std::cout.tie(0);
    int T=read(),mod=read();
    while(T--){
        int a=read(),b=read();      
        int w=a-2*b;
        if(b&w||w<0){std::cout<<0<<'\n';continue;}
        int tot=__builtin_popcountll(w)-1;tot=(1ll<<tot)%mod;
        int zc=std::__lg(w);w=1ll<<zc;
        std::cout<<w%mod*tot%mod<<'\n';
    } 
}
```
吐槽一下出题人UU造的数据，你往每一个点里都塞特殊情况是吧，太毒瘤了。


---

## 作者：FreedomKing (赞：2)

感觉非常妙的位运算数学题，但是死于 popcount 板子只支持到 int。

### 思路

由于跟二进制有关，考虑搞出来 $x,y$ 的异或和，先设一个 $C=x\operatorname{xor}y$，虽然 $x,y$ 是未知的，但我们可以由推导加上从题目得到的信息知道 $C$ 与 $A,B$ 之间的关系如下：

$$\begin{aligned}

x+y&=2\times(x\operatorname{and}y)+(x\operatorname{xor}y)\\

(x\operatorname{xor}y)&=(x+y)-2\times(x\operatorname{and}y)\\

(x\operatorname{xor}y)&=A-2\times B\\

C&=A-2\times B\\

\end{aligned}$$

根据题意，由于 $(x\operatorname{and}y)=B$，所以 $B$ 的某二进制位上若是 $1$，$C$ 的那个二进制位也必须是 $1$，而 $x\operatorname{xor} y$ 则表示出了 $x,y$ 必须不同的那些二进制位。这是一个很有用的点。

题目又规定 $x\le y$，所以 $C$ 的二进制下的最高位，也就是权重最大的那位不同的二进制位，必须是 $y$ 的为 $1$，$x$ 的为 $0$，这是必然的；其他的二进制位便都有两种可能，而这两种可能中的二进制下的 $1$ 既有可能出现在 $x$ 中也有可能出现在 $y$ 中，由于需要求 $y-x$ 的运算和在两个数中偶数的出现次数，直接就都被抵消掉了。这是本题最微妙的点。

总而言之，只有 $C$ 的二进制下最高位 $1$ 做贡献，为 $2^{\operatorname{popcount}(C)-1}$，在每种方案中都会做贡献，一共有 $2^{\lfloor \log_2C \rfloor-1}$ 次的贡献，所以最终答案为 $2^{\operatorname{popcount}(C)-1}\times 2^{\lfloor \log_2C \rfloor-1}$，由于两个数最劣都只是 $\log_2$ 级别的，而 $C$ 最多只有 $60$ 位，$\log_2 60$ 基本就是常数级所以可以忽略不计，总时间复杂度约为 $O(T)$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=2e3+5;
//const int mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
	inline int popcount(int x) {//下面是换了支持到 long long 范围的 popcount，可以放心食用
		x=(x&0x5555555555555555)+((x>>1)&0x5555555555555555);
		x=(x&0x3333333333333333)+((x>>2)&0x3333333333333333);
		x=(x&0x0f0f0f0f0f0f0f0f)+((x>>4)&0x0f0f0f0f0f0f0f0f);
		x=(x&0x00ff00ff00ff00ff)+((x>>8)&0x00ff00ff00ff00ff);
		x=(x&0x0000ffff0000ffff)+((x>>16)&0x0000ffff0000ffff);
		x=(x&0x00000000ffffffff)+((x>>32)&0x00000000ffffffff);
		return x;
	}
}
signed main(){
	int T=qr,mod=qr;
	while(T--){
		int a=qr,b=qr,c=a-(b<<1);
		if(c<=0||c&b||a==0){
			puts("0");
			continue;
		}
		int cnt=c,ans=0;
		while(cnt){
			cnt>>=1;
			ans++;
		}
		qwe((qpow(2,popcount(c)-1,mod)*qpow(2,ans-1,mod))%mod);
	}
	return  0;
}
```

### 后记

感谢@[Froranzen](https://www.luogu.com.cn/user/361432)、@[liaiyang](https://www.luogu.com.cn/user/783170) 和@[hellolin](https://www.luogu.com.cn/user/751017) 对式子推导的帮助。

我肯定不是因为太菜才需要三个大佬讲三遍才听懂的，确信。

---

## 作者：toolazy (赞：1)

位运算，好玩！（但是太蒻了只打了 $\operatorname{rank} 222$，逃

---

为了方便，这里将题意改成等价的形式，看得更自然一点：

> 我们称一个无序数对 $[x,y]=[y,x]$ 为 $\operatorname{good}$ 的，当且仅当：

> $$x+y=A\space\land\space x\otimes b=B$$

> 其中 $\otimes$ 为二进制按位乘法（即求与）。定义一个无序数对 $[x,y]=[y,x]$ 的 **对称差** $\Delta[x,y]=|x-y|=|y-x|$。

> 先给定 $A,B$，求 **所有不重复** 的 $\operatorname{good}$ 的无序数对的对称差之和。

（觉得用集合 $\{x,y\}$ 的话没法定义重复元素，又不知道无序数对的符号，只好用方括号了，逃

我将带着大家把我的思路走一遍。

首先，二进制下的加法有一个很有趣的性质：

$$a+b=\operatorname{Lsh}(a\otimes b,1)+(a\oplus b)$$

其中 $\operatorname{Lsh}(a,b)$ 为左移操作（即 $a\times2^b$），$\oplus$ 为按位异或操作。

这个等式是怎么来的呢？实际上非常简单，它就是模拟本位和进位的加法。

观察一下二进制下的无进位的加法：

$$
\begin{matrix}
0+0=[0]0\\
0+1=[0]1\\
1+0=[0]1\\
1+1=[1]0
\end{matrix}$$

看得出来，**本位** 就是 **异或值**。

再来看一下进位：

$$
\begin{matrix}
0+0=0[0]\\
0+1=0[1]\\
1+0=0[1]\\
1+1=1[0]\\
\end{matrix}
$$

看得出来，**进位** 就是 **求与值**。当然啦，进位是进到下一位，所以要左移一位。

那么有了这个等式之后，我们就可以得到：

$$\begin{matrix}
x+y=A=\operatorname{Lsh}(B,1)+(x\oplus y)\\
\rightarrow x\oplus y=A-2B\end{matrix}$$

那么现在再来观察一下我们已有的信息：

$$\begin{cases}
x\otimes y=B\\
x\oplus y=A-2B
\end{cases}$$

接下来，从 **异或** 的角度来考虑 $x,y$ 的值。

$A-2B$ 是一个常数，没什么特殊的区别，直接记作 $C$。

接下来看 $C$ 在二进制下的每一位。

1. 如果在某一位上，$C$ 的值为 $1$，就意味着 $x,y$ 在同一位上的值一定不同，势必是一个为 $0$，一个为 $1$。换一个更加形象的解释，就是 $C$ 要选择把它每一位上的 $1$ 是分给 $x$ 还是分给 $y$。

由于是无序数对的原因，我们可以直接把最高位固定给其中某一个元，再来考虑剩下的。下面我们统一把 $C$ 最高位上的 $1$ 分配给 $x$。

2. 如果在某一位上，$C$ 的值为 $0$，那么就意味着 $x,y$ 在同一位上，要么双双为 $0$，要么双双为 $1$。但是很明显的是，无论是双双为 $0$ 还是 $1$，由于我们最后要取的答案是 **对称差之和**，这一位产生的贡献一定是 $0$。

说完了这些之后，把重点放在第一条。也就是说我们可行的 $[x,y]$ 就是在把 $C$ 除最高位以外的所有 $1$ 分配出来。

接下来就十分的有趣了：**无论是什么情况，除最高位以外的其它位都会被其它情况所抵消！**

列个表举个例子，下面是当 $C=(10110)_2$ 的情况下时我们需要考虑的所有情况（下面忽略右下角的 $_2$ 角标）：

$$\begin{matrix}
x&&y\\
(1)\color{red}0000&&\color{greenyellow}0110\\
(1)\color{orange}0010&&\color{yellow}0100\\
(1)\color{yellow}0100&&\color{orange}0010\\
(1)\color{greenyellow}0110&&\color{red}0000
\end{matrix}$$

证明非常简单所以不证了（逃

所以最后的答案就是：$C$ 的最高位权值 $\times$ $[x,y]$ 的可能性数量

那么可能性究竟有多少呢？这是我们所需要解决的 **最后的问题**，加油！撑一撑！

还是来分析 $C$ 除最高位以外的每一位。

1. 如果在同一位上，$C$ 是 $1$ 的同时 $B$ 也是 $1$，则会产生 **明显冲突**，可能性数量为 $0$。

2. 如果在同一位上，$C$ 是 $0$ 的同时 $B$ 是 $1$，那么只能有 $x,y$ 都是 $1$；反过来如果 $B$ 是 $0$，那么只能有 $x,y$ 都是 $0$。无论如何，$x,y$ 在这一位都是确定的，可能性数量为 $1$。

3. 如果在同一位上， $C$ 是 $1$ 的同时 $B$ 是 $0$，那么此时 $x,y$ 不确定，把 $1$ 分给 $x,y$ 都行，有两种可能性。

最后把每一位的答案乘起来就有了，但是实际上实现并不用这么麻烦：

1. 如果 $B\otimes C$ 不为 $0$，那么一定有某一位上对应到了 **情况1**，最终答案可能性为 $0$，最终答案也为 $0$。

2. 否则，对于答案有贡献的数量取决于 $C$ 里面有多少个 $1$，答案可能性数量是 $2^{\operatorname{popcount}(C)-1}$，其中 $\operatorname{popcount}(C)$ 表示二进制下 $C$ 中一的个数。

答案出来啦，一句话解决：

$$\operatorname{ans}=\begin{cases}
0,&B\otimes(A-2B)\ne 0\\
\operatorname{Lsh}(\operatorname{highbit}(A-2B), (\operatorname{popcount}(C)-1)),&\operatorname{otherwise}
\end{cases}$$

别忘记取模哦~

```cpp
#include <iostream>
#include <cctype>
using namespace std;

#define int __int128

int t, mod, A, B, C, highbit, cnt, movebit;

int read() {
	int res = 0;
	char c;
	while (isspace(c = getchar()));
	res = c ^ '0';
	while (isalnum(c = getchar()))
		res = (c ^ '0') + (res << 1) + (res << 3);
	return res;
}

void output(int n) {
	if (n / 10)
		output(n / 10);
	putchar(n % 10 + '0');
}

int popcount(int n) {
	int res = 0;
	for (; n; n >>= 1)
		if (n & 1)
			res ++;
	return res;
}

main() {
	t = read(); mod = read();
	while (t --) {
		A = read(); B = read();
		C = A - B - B;
		if (C <= 0 || (B & C)) {
			putchar('0');
			putchar('\n');
			continue;
		}
		cnt = 0;
		movebit = popcount(C) - 1;
		while (C != 1)
			cnt ++, C >>= 1;
		highbit = ((__int128)(1) << cnt) % mod;
		output((highbit * (((__int128)(1) << movebit)) % mod) % mod);
		putchar('\n');
	}
	return 0;
}
```

最后是血泪的提醒：内置的 `__builtin_popcount(int n)` 只能为 `unsigned` 类型计数！如果位数不是 $32$ 位的话...

`popcount` 函数给我手打！！！（破音

---

## 作者：liaiyang (赞：1)

一道很简单的小清新题。

显然我们有 $a+b=2(a\&b)+(a\oplus b)$，第一项是进位，第二项是不进位加法。

所以我们可以求出 $a\oplus b$ 的值，每次就是把这个值的每一位分配给两个数。

为了保证 $x\le y$，我们需要把最高位分给 $y$，剩下随机分配。

显然，异或中除最高位的每一位分配到 $x$ 和 $y$，在 $\sum y-x$ 中都会抵消。

所以最终的答案就是 $2^{\lfloor\log n\rfloor}2^{\operatorname{popcount}(n)}$。

cmath 库函数大体视作常数，时间复杂度 $O(T)$。

记得特判无解的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3,"Ofast")
#define int long long
#define y0 Y0
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y,mod) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y,mod) (((x+=y)>=mod)&&(x-=mod))
mt19937 rnd(time(0));
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1;
const int mod=998244353,g=3,gi=332748118;
const int N=2e5+10;
int popcount(int x){
    x=(x&0x5555555555555555)+((x>>1)&0x5555555555555555);
    x=(x&0x3333333333333333)+((x>>2)&0x3333333333333333);
    x=(x&0x0f0f0f0f0f0f0f0f)+((x>>4)&0x0f0f0f0f0f0f0f0f);
    x=(x&0x00ff00ff00ff00ff)+((x>>8)&0x00ff00ff00ff00ff);
    x=(x&0x0000ffff0000ffff)+((x>>16)&0x0000ffff0000ffff);
    x=(x&0x00000000ffffffff)+((x>>32)&0x00000000ffffffff);
    return x;
}
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=rd,m=rd;
    while(T--){
        int a=rd,b=rd;
        if((a-2*b)&b) wt(0,'\n');
        else if(a-2*b<=0) wt(0,'\n');
        else wt((1ll<<(int)log2(a-2*b))%m*((1ll<<popcount(a-2*b)-1)%m)%m,'\n');
    }
    return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：1)

由位运算定义知：$x+y=2 \times x\operatorname{AND} y + x \operatorname{XOR} y$。

所以我们可以知道 $x\operatorname{XOR}y$。

手玩一下不难发现只有 $x\operatorname{XOR}y$ 对答案有贡献，贡献系数是 $2^{\operatorname{popcount}(x\operatorname{XOR}y)-1}$。

模拟即可，复杂度 $O(T)$。

---

## 作者：buowen123 (赞：1)

很不错的思维题目。~~另一篇题解讲的太浅了还不放代码，个人认为讲的不太好~~

$x+y$ 和 $x \operatorname{AND} y$ 很难联系，考虑将前者转换为二进制运算（后者转换不成加减法的，别想了）。

记 $\operatorname{XOR}$ 为按位异或。

首先我们要知道 $\operatorname{XOR}$ 的本质是二进制下的不进位加法。其次可以注意到，$x \operatorname{AND} y$ 中为 $1$ 的二进制位**对应着 $x+y$ 中进位的那些位**，而进位会把 $1$ 加到前一位，也就是乘以 $2$。因此得到重要结论：

$$x+y=(x \operatorname{XOR} y)+2(x \operatorname{AND} y)$$

记 $C=x \operatorname{XOR} y$，如何求出 $y-x$ 的和呢？

先来看一个简单的：求出“好的”数对的数量。

**接下来的讨论都在二进制下进行。**

从高位往低位扫，记 $m$ 为 $B$ 的第 $i$ 位，$n$ 为 $C$ 的第 $i$ 位。那么：

- 若 $m=1,n=1$ 说明在这一位上，$x$ 和 $y$ 的按位与和按位异或结果都为 $1$，会发现这不可能，所以答案一定是 $0$。
- 若 $m=1,n=0$ 说明在这一位上，$x$ 和 $y$ 都是 $1$。
- 若 $m=0,n=1$ 说明在这一位上，$x$ 和 $y$ 一个是 $1$ 另一个是 $0$，把答案乘以 $2$ 即可。
- 若 $m=0,n=0$ 说明在这一位上，$x$ 和 $y$ 都是 $0$。

回到原题。由于 $x \le y$，从高位往低位扫时，如果第一次出现 $m=0,n=1$，假设这是从低到高第 $i$ 位，那么在这一位上，$x=0,y=1$，于是带来这一位的贡献 $t=2^{i-1}$。好比十进制中，相同位数的数从最高位开始比，要让 $y \ge x$ 就要让最高位更大。而当接下来再次出现 $m=0,n=1$ 时，**只需要把贡献乘以 $2$ 即可**。原因在于，我们考虑如下的 $(x,y)$（假设省略号后面有着相同的位数）：
```plain
x = (001...)2
y = (100...)2
```
我们把第 $3$ 位交换：
```plain
x = (000...)2
y = (101...)2
```
此时，后面的位满足 $y-x$ 在对应位（这里是第 $3$ 位）的贡献上互补，然而 $(x,y)$ 的数量变为两倍，实质上相当于把 $t$ 这一贡献的出现次数乘以 $2$。

具体实现上，考虑设置变量 $j=2^{i-1}$，获取 $x$ 从右往左的第 $i$ 位只需使用 $x \operatorname{AND} j$。

参考代码中，$bb$ 代表 $m$，$cc$ 代表 $n$，$m$ 代表题目中的模数 $M$。

还有一个事！请记住：十年 OI 一场空，不开 long long 见祖宗。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a,b,m;
void solve(){
	cin>>a>>b;
	int c=a-2*b,ans=0,j=1,flag=0;
	if(c<0||(b&c)){//当求出的 x xor y 小于 0 或者 b 和 c 存在某一位都为 1 时，输出 0
		cout<<0<<'\n';
		return;
	}
	j=(1<<30); j=j*j*4;//此处为了保险把 j 设为 2 的 62 次方。
	for(int i=62;i>=0;i--){//代码里采用 x xor (2^i) 获取从右往左第 i+1 位
		int bb=(b&j),cc=(c&j);
		if(bb==0&&cc){
			if(!flag) ans=j,flag=1;//如果是初次碰上 m=0,n=1，则记录贡献
			else ans=(ans*2)%m;//否则答案乘以 2
		}
		j/=2;
	}
	cout<<ans<<'\n';
}
signed main(){
	int t=1; 
	cin>>t>>m;
	while(t--) solve();
}
```

---

## 作者：02Ljh (赞：0)

~~赛时想到最后一步了然后瞎导柿子寄了~~

## solution:

很有意思的题，显然按位考虑，如果当前位 $b$ 为 $1$，那么选出来的 $x,y$ 上这一位都要为 $1$。但相加得 $a$ 这个要求就很烦，我们不妨先让 $a$ 减去 $2\times b$，设其为 $t$，先把必须选的给减掉，然后凑下面的数。

显然 $t$ 的为 $1$ 的每一位要么分给 $x$，要么分给 $y$，有限制条件 $x\leq y$，所以最大的那一位必须给 $y$，剩下的可以随便分。考虑计算所有状态的贡献，令 $c$ 表示该数二进制位为 $1$ 的个数，$k$ 表示最高位的数，对于 $y$，他除第一位外的所有位都能选到，每种位置产生贡献的当且仅当该位选的是 $1$，再加上总方案数乘上最高位的数，所以就是 $2^{c-1}+2^{c}\times k$。而 $x$ 除了第一位必不选外其他任意一位都有 $0/1$ 两种选择，于是 $\sum(y-x)=2^{c}\times k$。

细节上，当 $t$ 为负数或者 $t$ 与上 $b$ 不为 $0$ 时判掉（因为该位为了满足 $b$ 已经填了 $1$，无法在填满足 $a$ 了），注意随时取模，建议预处理 $2$ 的次幂。

## code：

```
 	while(_--)//pf为预处理2的次幂
	{
    	int a,b; cin>>a>>b;
   		int t=a-2*b;
   		if(a<2*b) { cout<<"0\n"; continue; }
   		int cnt=0;
   	   int mx=0;
   		For(i,0,60) 
   		{ 
   			int ba=pf[i];
   			if(ba&t)
   			{
   				cnt++;
   				mx=max(mx,i);
   			}
   		} 
      if(t&b) { cout<<"0\n"; }
      else { cout<<(pf[cnt-1]%MOD*(pf[mx]%MOD)%MOD+MOD)%MOD<<"\n"; }
	}
```

---

## 作者：sbno333 (赞：0)

这是这道题的思考过程，可以参考：

显然，位运算先考虑拆位。

对于每一位，如果为 $1$ 则对应的 $x$ 和 $y$ 的这一位也是 $1$ 否则均为 $0$ 或有一个 $1$。

对答案造成贡献可以发现只有其中一个是 $1$。

接下来考虑和。

显然，如果对于 $B$ 的某一位是 $1$，则 $x,y$ 的对应为就已知了，而我们可以把 $A$ 中 $x,y$ 的已知部分去掉，由于 $0$ 对已知，$B$ 的值没有贡献，因此 $x$ 和 $y$ 已知的和为 $2B$，此时去掉已知为 $A-2B$。

接下来由于 $x,y$ 某一位做多有一个是 $1$，因此不存在进位，又有 $x+y=A$ 因此可以看做 $A$ 为很多二进制位的集合，将这些分成两部分。

由于 $y\ge x$，因此集合中最高位要给 $y$，此时一定满足 $y>x$，因为 $x$ 没有最高位，无论如何也达不到 $y$ 的最高位的大小。

因此剩下的可以任意分，设剩下 $t$ 位，则有 $2^t$ 个方案，这些方案分配时显然跟 $x,y$ 的顺序无关，因此满足交换律，值的和相等，同时由于只能分配给一个量，因此没有方案是满足分配后 $x,y$ 相等，因此抵消后为 $0$，不计算，但对于每一个方案，都要贡献一个最高位，因此最后为最高位的值乘方案数，可以用快速幂解决，因为最高位和方案数都是 $2$ 的整数次幂。

然而，还有可能没有合法答案，比如 $A-2B<0$，由于 $A=2B$ 时答案为 $0$，因此可以特判 $A-2B\le0$。

我们发现，集合中的位如果与 $B$ 的某一有 $1$ 的位重了，则这一位无法分配，也不合法，代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int ksm(int a,int b){
	a%=m;
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=m;	
		}
		a*=a;
		a%=m;
		b>>=1;
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		x-=2*y;
		int s,t,b;
		s=0,t=0,b=0;
		bool fl;
		fl=0;
		if(x<=0){
			cout<<0<<endl;
			continue;
		}
		while(x){
			if(x&1){
				t++;//计算方案数，显然为1的个数减一
				b=s;//b记录最高位
				if((1ll<<s)&y){//（一定要写1ll，否则GG，别问我怎么知道的，调了10分钟以上）,如果 B 中有集合中的某一位
					cout<<0<<endl;
					fl=1;
					break;
				}
			}
			s++;//s记录当前位
			x>>=1;
		}
		if(fl){
			continue;
		}
		t--;
		t+=b;//两个相乘，2^t*2^b=2^(t+b)
		cout<<ksm(2,t)<<endl;
	} 
	return 0;
} 
```

---

## 作者：rsy_ (赞：0)

这道题其实感觉很一眼，但是不知道为什么场上过的人那么少。

有很显然先把他们必须有的部分减掉，然后按位考虑即可，每一种情况的总贡献就是每一位的权加起来就行了。

```
#include <bits/stdc++.h>
#define L(i,j,k) for(int i=(j);i<=(k);i=-~i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define lowbit(x) (x&-x)
#define sort stable_sort
#define int long long

using namespace std;

namespace rsy{
	const int maxn = 1e6 + 10;
	const int maxm = maxn * 25;
	typedef pair<int,int> pii;
	typedef long long ll;
	typedef unsigned long long ull;
	void chmin(int &x,int c){x=min(x,c);}
	void chmax(int &x,int c){x=max(x,c);}
	
	int A, B, mod, pw2[maxn];
	
	vector <int> s1, s2;
	void solve() {
		cin >> A >> B;
		if (B * 2 > A) {cout << "0\n";return;}
		int tmp = B;
		s1.clear(), s2.clear();
		while (tmp) s1.emplace_back(tmp & 1), tmp >>= 1;
		A -= B * 2, tmp = A;
		while (tmp) s2.emplace_back(tmp & 1), tmp >>= 1;
		int len = max(s1.size(), s2.size());
		L (i, s1.size(), len - 1) s1.push_back(0);
		L (i, s2.size(), len - 1) s2.push_back(0);
		reverse (s1.begin(), s1.end());
		reverse (s2.begin(), s2.end());
//		int cur = A;
//		L (i, 0, len - 1) cout << s1[i] << " \n"[i == len - 1];
//		L (i, 0, len - 1) cout << s2[i] << " \n"[i == len - 1];
		L (i, 0, len - 1) {
			if (s1[i] && s2[i]) {
				cout << "0\n";
				return ;
			}
		}
		int cnt = 0, sum = 0, sum2 = 0;
		L (i, 0, len - 1) cnt += s2[i];
		int cntt = 0;
		L (i, 0, len - 1) {
			if (s2[i]) cntt ++ ;
			if (cntt != 1 && s2[i]) {
				sum += pw2[len - i - 1];
				sum %= mod;
			}
			if (s2[i]) (sum2 += pw2[len - 1 - i]) %= mod;
		}
		int t = cnt;
		int ct = t - 1;
		tmp = sum * pw2[ct] % mod % mod;
//		cout << ct << '\n';
//		cout << sum2  << ' ' << ct << ' ' << sum << '\n';
		cout << (sum2 * pw2[ct] - tmp + mod) % mod << '\n';
	}
	
	signed main() {
		ios::sync_with_stdio(false); 
		cin.tie(nullptr);
		int T = 1;
		cin >> T >> mod;
		pw2[0] = 1;
		L (i, 1, 100010) pw2[i] = pw2[i - 1] * 2ll % mod;
		while (T -- ) solve();
		return 0;
	}
}

signed main() {return rsy::main();}	
```

---

## 作者：apiad (赞：0)

由于与运算，所以我们知道 $B \le x$ 而且 $B \le y$。这是显然的，我们不妨设 $x_0 = x-B$，$y_0 = y-B$。这样，只需要满足 $x_0 + y_0 = A-2\times B$ 即可。我们可以设 $c = A-2\times B$。

知道了和，我们想着如何去分配两个数呢？

对于 $c$ 的二进制下每一位肯定会分配一些在 $x_0$ 身上，或者一些在 $y_0$ 身上。由于 $x_0 \le y_0$，所以肯定要保证 $c$ 二进制下最大的一位在 $y_0$ 上，这样，后面的方案如何处理，都是合法的。对于每一位，加入这个位置是 $k$，肯定是要不放 $x_0$ 上，就是放 $y_0$ 上，如果放 $x_0$ 上，那么会让差的总和减少 $k$，如果放在 $y_0$ 上，那么会让差的总和增加 $k$，对于两种情况，正好互补，所以不用考虑了（~~有点炸骗~~）。于是我们就可以让系数为后面的方案数，然后乘上 $c$ 二进制上最高位的值（也就是一开始确定最高位属于 $y_0$ 时，$y_0 - x_0$ 的值）。设 $s$ 为出了最高位剩下二进制上为 $1$ 的个数，也就是剩下可以填写的数量，那么系数就是 $2^s$。如何取 $s$？可以用高科技 ```__popcount``` 函数来解决，据说还是 $O(1)$ 时间复杂度。

还剩一个判断合法情况。

显然 $c\le0$ 不合法，如果 $c$ 按位与 $B$ 不等于 $0$ 那么代表他们二进制中有一个是重复的，就不可以来放在 $x_0$ 或 $y_0$ 身上了，显然是不合法的。

对于以上两种情况需要特判。

还需要注意：勤取模。不然样例都过不去。

```cpp
int m,a,b;
void solve(){
	cin >> a>>b;
	int c=a-b*2;
	if(c<=0||((c)&b)!=0 ) {cout<<0<<endl;return ;}
	for(int i=60;i>=0;i--){
		if(c & (1ll<<i)){
			cout<<(((1ll<<i)%m)*((1ll<<((__popcount(c))-1ll))%m))%m<<endl;
			return ;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	cin >> T >> m;
	while(T--) solve();
	return 0;
}
```

怎么抽象的结论，蒟蒻没有场切，原因是我想到了几乎 $90\%$，只差最后一点，就是系数乘最高位那里，我当时想复杂了，可能和很多人一样，会想到二进制模拟等。最后发现，一个公式就搞定。

---

## 作者：Cure_Wing (赞：0)

[P10118 『STA - R4』And](https://www.luogu.com.cn/problem/P10118)

### 思路

$x \operatorname{AND} y=B$，我们从这个条件入手。显然对于 $B$ 的每一位，如果是 $1$，那么 $x,y$ 也一定都是 $1$。于是 $x,y\ge B$，得到 $x+y=A\ge2B$。所以如果 $A<2B$，那么一定无解，直接输出 $0$。

进一步分析，对于 $B$ 的每一位，如果为 $0$，那么我们是可以在 $x$ 或 $y$ 上填数的。简单思考得到 $C=A-2B$ 就是所填的 $1$ 得到的数之和。由于 $B$ 的第 $i$ 位上，如果为 $1$，那么这一位就不会产生贡献；如果为 $0$，那么也只能产生一次贡献，因为只能填一个数。所以如果 $C\operatorname{AND}B\not=0$，说明在 $B$ 为 $1$ 的那位上还要产生贡献，但实际无法满足，也可以输出 $0$。

剩下的情况，我们假设 $C$ 中 $1$ 的个数为 $p$，那我们要在 $x,y$ 中选择 $p$ 个位置放 $1$。因为题目限制了 $x\le y$，所以 $C$ 最高位的 $1$ 只能放在 $y$ 上。考虑每一位会产生对答案的贡献：对于不是最高位的第 $i$ 位，如果在 $y$ 填 $1$，那么为 $2^{p-2}\times2^{i-1}$，在 $x$ 填的话就是 $-2^{p-2}\times2^{i-1}$，两者恰好抵消。而对于最高位 $q$，由于它只能填在 $y$，所以贡献为 $2^{p-1}\times2^{q-1}$，答案也就是这个值。

时间复杂度很小，不分析了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
int t,m;
long long a,b,c;
inline long long uppbit(long long x){
    long long sum=1;
    for(;sum<=x;sum<<=1);
    return sum>>1;
}//寻找最高位
inline int popcount(long long x){
    int sum=0;
    while(x){sum+=x&1;x>>=1;}
    return sum;
}//统计1的个数（注意到__builtin_popcount写的是unsigned int，所以无法使用）
inline int qpow(int a,int b,int p,int t=1){for(;b;b>>=1,a=1ll*a*a%p)if(b&1)t=1ll*t*a%p;return t;}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    for(cin>>t>>m;t--;){
        cin>>a>>b;c=a-2*b;
        if(c<=0||(c&b)){cout<<"0\n";continue;}
        int k=popcount(c);
        long long q=uppbit(c);
        if(k==1){cout<<c<<'\n';continue;}
        cout<<1ll*qpow(2,k-1,m)*(q%m)%m<<'\n';
    }
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

# Solution

很厉害的题，想的时间比这场 B 和 C 加起来都长！

令 $B_i$ 是 $B$ 二进制下从低到高第 $i$ 位，$A_i,x_i,y_i$ 同理。

若 $B_i=1$，则 $x_i=y_i=1$，这是可以直接得出的。

但是这样会影响上一位，很不好。我们使 $A\gets A-2B$，现在对于 $B_i=1$，需要保证的就是 $x_i=y_i=0$。这样，就没有 $x_i=y_i=1$ 的位，也没有进位。

对于 $A_i,B_i$ 分类讨论：
- $B_i=0,A_i=0$：$x_i=y_i=0$。
- $B_i=1,A_i=0$：$x_i=y_i=0$。
- $B_i=1,A_i=1$：无解。
- $B_i=0,A_i=1$：因为没有进位，所以 $x_i=1$ 或 $y_i=1$。

由于只有 $B_i=0,A_i=1$ 的位可能使 $x_i$ 或 $y_i$ 为 $1$，考虑这种位的贡献：
- 若该位是最高的这种位，则因为 $x\leq y$，$y_i=1$。又因为 $y_i=1$，所以下面的位不管怎么选都有 $x\leq y$。设总共有 $cnt$ 个这种位，贡献为 $(2^i-0)\times2^{cnt-1}=2^{i+cnt-1}$。
- 若该位不是最高位，则 $x,y$ 的大小关系已确定，该位可以随便选。设选该位以上的位有 $p$ 种合法方案，贡献为 $(-2^i)\times p+2^i\times p=0$。

所以求出 $cnt$，找到最高位 $h$，答案即为 $2^{cnt+h-1}$。

注意无解的情况：$A-2B<0$、$B_i=1,A_i=1$ 与 $cnt=0$。

# Code

```cpp
// writer: Milkcat
// time: 2024.2.1 
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 1e6 + 5;
    LL t, mod, A, B;
    int main() {
    	cin >> t >> mod;
    	while (t --) {
    		cin >> A >> B, A -= B * 2;
    		
    		bool success = 1;
    		if (A < 0) success = 0;
			REP(i, 0, 60)
				if ((B >> i & 1) && (A >> i & 1)) success = 0;
			if (!success) { cout << "0\n"; continue; }
				
    		LL h = 0, cnt = 0;
			REP(i, 0, 60)
				if (A >> i & 1) h = i, cnt ++;
			if (!cnt) { cout << "0\n"; continue; }
			cout << ((1LL << h) % mod) * ((1LL << (cnt - 1)) % mod) % mod << '\n';
		}
        return 0;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}
```


---

## 作者：AlicX (赞：0)

## Solution 

因为 $x \& y=B$，所以 $B$ 二进制下为 $1$ 的位，$x,y$ 这一位上也为 $1$。

所以 $x,y$ 最小值都为 $B$，去掉这些位后让 $A \to A-2 \times B$。

当 $A \leq 0$ 时，没有一组满足条件的解，即输出 $0$。

接下来我们要保证 $x+y=A$，所以考虑将 $A$ 二进制拆位，把 $A$ 二进制下为 $1$ 的位存下来，那么就应当考虑每一位是给 $x$ 还是给 $y$。

因为 $y \geq x$，所以最高位一定是 $y$ 的，那么考虑 $y-x$ 的形式即如 $2^{Max}\pm p$，因为 $(2^{Max}+p)+(2^{Max}-p)=2\times 2^{Max}$，所以答案其实是 $2^{Max} \times Tim$，$Tim$ 为所有情况，不难想出 $Tim=2^{cnt-1}$，$cnt$ 为 $A$ 在二进制下 $1$ 的个数，也就是说固定最高位剩下的位任取即可。

```cpp
#include<bits/stdc++.h> 
#define int __int128 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=61; 
int Mod; 
bool st[N]; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
int qmi(int x,int k){ 
	int res=1; 
	while(k){ 
		if(k&1) res=res*x%Mod; 
		x=x*x%Mod; k>>=1; 
	} return res; 
} 
il void solve(){ 
	memset(st,false,sizeof st); 
	int a=read(),b=read(); 
	a-=2*b;  
	if(a<=0){
		puts("0"); 
		return ;
	}
	for(int i=0;i<N;i++){
		if(b>>i&1) st[i]=true; 
	} 
	int cnt=0,Max=0; 
	for(int i=0;i<N;i++){
		if(a>>i&1){
			cnt++; 
			if(st[i]){
				puts("0"); 
				return ; 
			} 
			Max=i; 
		}
	} long long ppp=qmi(2,Max)*qmi(2,cnt-1)%Mod; 
	printf("%lld\n",ppp); 
} 
signed main(){ 
	int T=read(); Mod=read(); 
	while(T--) solve(); return 0; 
} 
/*
1 883 
137168 35030

*/
```


---

## 作者：船酱魔王 (赞：0)

# P10118 『STA - R4』And 题解

## 题意回顾

求出 $ x+y=A $ 且 $ x \operatorname{AND} y = B $ 的所有满足要求的 $ (x,y)(x<y) $ 的 $ y-x $ 之和对 $ M $ 取模的结果。

多测，$ T $ 组数据。

$ 1 \le T \le 3 \times 10^5 $，$ 5 \le M \le 1.1 \times 10^9 $，$ 0 \le A,B < 2^{60} $，$ M $ 为质数。

## 分析

首先位运算题目我们按位考虑，对于 $ B $ 为 $ 1 $ 的位显然两个数该位均为 $ 1 $，我们可以将这些位统一都扣掉一个 $ 1 $，这样问题转化成为了 $ A'=A-2B $，$ B'=0 $，和为 $ A' $，与为 $ B' $ 的情况。

$ A' \le 0 $ 判无解即可。（两数相等对答案没贡献，和无解等效）

我们发现两个数同一位显然不能全为 $ 1 $，则一个位对于和的贡献最多为 $ 1 $，因此可以将 $ A' $ 二进制唯一拆分，$ A' $ 为 $ 1 $ 的位置较大数和较小数正好 $ 1 $ 个为 $ 1 $。如果存在一些位 $ A' $ 和 $ B $ 均为 $ 1 $，因为那些位已经被扣了 $ 1 $，因此直接判为无解即可。

此时我们发现对于最高的两个数中存在一个数为 $ 1 $ 的二进制位，较大数必须为 $ 1 $，剩下的位置让大数或小数为 $ 1 $ 没有限制，设剩余有 $ t $ 个含 $ 1 $ 位置，即有 $ 2^t $ 种数对可能，显然因为没有限制，非最高位对答案的贡献可以在存在 $ 1 $ 的非最高位数值全部取反后被抵消，因此只有最高位会对答案产生影响，设最高位的位权为 $ w $（即一个 $ 1 $ 代表的实际量），则答案为 $ w2^t $，记得及时取模。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int T, mod;
long long a, b;
int main() {
    cin >> T >> mod;
    for(int ti = 1; ti <= T; ti++) {
        scanf("%lld%lld", &a, &b);
        if(a <= 2 * b) {
            printf("0\n");
            continue;
        }
        long long c = a - 2 * b;
        long long ans = 0;
        int tc = 0;
        for(long long i = 1; i <= c; i <<= 1) {
            if((c & i) != 0) {
                if((b & i) != 0) tc -= 1000;
                ans = i;
                tc++;
            }
        }
        if(tc < 0) ans = 0;
        tc--;
        if(tc >= 0) ans = (ans % mod) * ((1ll << tc) % mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

另外一种做法。

我们使用这个式子：$a+b=a\operatorname{and}b+a\operatorname{or}b$，由于 $x\operatorname{and}y$ 已知，所以我们可以求出 $x\operatorname{or}y$。

判定无解:

- $x\operatorname{or}y\geq 0$。
- $x\operatorname{and}y\subseteq x\operatorname{or} y$

不满足这两个条件显然不行。

那么显然 $x,y$ 都要包含 $x\operatorname{and}y$ 这个部分，减去之后啥贡献没有，不要管了。

容易发现 $x,y$ 是 $x\operatorname{or}y-x\operatorname{and}y$ 的划分，因为 $x<y$（等于的减没了我们视而不见），所以最高位肯定是 $y$ 的一部分，对于剩下的部分随便划分即可。

那么我们把所有的 $y$ 的和减去所有的 $x$ 的和，我们发现最高位往下所有位的子集和在两边都恰好有，消掉了，只剩下最高位，这个值就是 $2^{hig}$。

那么我们现在就只关心方案数了，我们设 $x\operatorname{or}y-x\operatorname{and}y$ 有 $t$ 位，那么方案显然有 $2^{t-1}$ 种。

乘起来即可。

这题思维真的很不错，比第二题那个答辩好多了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL T,mod,a,b;
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
int main()
{
	scanf("%lld%lld",&T,&mod);
	while(T--)
	{
		scanf("%lld%lld",&a,&b);
		a-=b;
		if(a<0)
		{
			puts("0");
			continue;
		}
		if((a&b)!=b)
		{
			puts("0");
			continue;			
		}
		a^=b;
		LL ans=0,hig=-1,cnt=0;
		for(int i=60;i>=0;i--)
		{
			if((a>>i)&1)
			{
				if(hig==-1)hig=i;
				cnt++;
			}
		}
		if(hig==-1)
		{
			puts("0");
			continue;
		}
		ans=ksm(2,cnt+hig-1);
		printf("%lld\n",ans);
	}
}
```

---

## 作者：zxh923 (赞：0)

# P10118 『STA - R4』And 题解

[题目传送门](https://www.luogu.com.cn/problem/P10118)

### 分析

结论 $1$ 及证明：

结论：$a+b=a\operatorname{XOR}b+2\times a\operatorname{AND}b$

证明：把 $a$ 和 $b$ 列成二进制形式，例如：

$a:1000001,b:1010101$

对齐得：

| 位数 | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $a$ | $1$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ |
| $b$ | $1$ | $0$ | $1$ | $0$ | $1$ | $0$ | $1$ |

把表格中两个位置都是 $1$ 的数同时减掉 $2$ 次，剩下的部分就是异或和，因为两个 $1$ 应该变成两个 $0$，和消去 $1$ 的过程等价。

所以，原题目转化成了在得到的这个异或值 $c$ 上，选择 $a$ 或 $b$ 在 $c$ 该位为 $1$ 时**其中一个**为 $1$，且这一位不是最高位，因为要保证大小关系。

又可以发现，可以固定一些位数，使得只有一位可以选择是 $a$ 该位为 $1$ 还是 $b$ 该位为 $1$，这两种情况得到的答案对于该位可以抵消，由此可得除了最高位，其他位的贡献都会被抵消。

这里记 $c$ 二进制表示中 $1$ 的个数为 $x$。根据组合方面的知识，方案数为 $2^{x-1}$。再设每组的贡献为 $y$，而 $y$ 二进制的唯一一个 $1$ 又一定在 $c$ 的最高位上，于是相乘即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,mod,x,y,xorr,cnt,ao;
int ksm(int x,int y){
	int res=1;
	if(y<0)return 0;
	while(y>0){
		if(y&1)(res*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return res;
}
signed main(){
	cin>>t>>mod;
	while(t--){
		cin>>x>>y;
		xorr=x-y*2;
		if((y&xorr)){
			cout<<"0\n";
			continue;
		}
		ao=cnt=0;
		while(xorr>0){
			ao++;
			if(xorr&1)cnt++;
			xorr/=2;
		}
		cout<<ksm(2,ao-1)*ksm(2,cnt-1)%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：bigclever (赞：0)

本文中所有关于某个数某一位上的值的表述均建立在**二进制**的基础上。

如果对文中某些地方有疑问，可以自行手推（毕竟~~手推比讲解简单多了~~）。
## 思路：
先给出一个对于这道题来说极为重要的式子：
$$x+y=2 \times (x \operatorname{AND} y)+x \oplus y$$
简单解释一下：$x \operatorname{AND} y$ 表示二进制下加法运算时所有**进位**的位权和，既然是进位，那么实际进位的值即为它们的和**左移一位**，也就是 $\times 2$；$x \oplus y$ 表示的是二进制下**不进位**加法。所以两者之和就是真正的 $x+y$。

------------
回归正题，那么这个式子有什么用呢？

因为我们知道 $x \operatorname{AND} y$ 和 $x+y$ 的值，自然可以求出 $x \oplus y$。不妨设 $t=x \oplus y$，先考虑无解情况，无非只有 $x \lt 0$ 或 $t \operatorname{AND} (x \operatorname{AND} y)$ 不为 $0$。

那接下来就好做多了：

如果 $t$ 的这一位为 $0$，那么如果要使 $(x,y)$ 是好的，则 $x$ 的二进制表示的这一位**等于** $y$ 的二进制表示的这一位。因为我们最终要统计所有好的 $(x,y)$ 的 $y-x$ 的和，那么这一位**并不会**对答案产生贡献，所以可以不考虑。
 
接下来只要考虑 $t$ 的值为 $1$ 的位。因为 $x \le y$，所以 $t$ 最高的值为 $1$ 的那一位的 $1$ 必然属于 $y$，而 $x$ 的那一位为 $0$，剩下的 $t$ 的值为 $1$ 的位随意分配均可。

------------
最后就想想如何统计答案。因为我们最终要统计所有好的有序非负整数对 $(x,y)$ 的 $y-x$ 的和，简单列举易知除了 $y$ 最高的值为 $1$ 的那一位还存在，剩下的 $1$ 全部在相减时**抵消了**。设 $t$ 中值为 $1$ 的位数为 $cnt$，那么所有好的有序非负整数对 $(x,y)$ 的个数为 $2^{cnt-1}$，最终答案即为 $y$ 最高的值为 $1$ 的那一位的**位权**乘上 $2^{cnt-1}$。

讲的有些繁琐，可以结合代码理解。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
bool num[65];
int main(){
	int t,m;
	scanf("%d %d",&t,&m);
	while(t--){
		ll a,b,x;
		scanf("%lld %lld",&a,&b),x=a-2*b;
		if(x<=0||(x&b)){puts("0");continue;}
		int cnt=0;
		while(x)num[++cnt]=(x&1),x>>=1;
		ll ans=-1,moo=0;
		for(int i=cnt;i;i--)
			if(num[i]){
				if(ans==-1)ans=(1ll<<i-1)%m;//记录t最高的值为1的那一位的位权
				else moo++;//记录cnt
			}
		printf("%lld\n",(1ll<<moo)%m*ans%m);
	}
	return 0;
}
```

---

## 作者：Kevin911 (赞：0)

## 思路
如果要枚举 $x$ 或 $y$ 肯定不行，所以从二进制位的角度去考虑。

先 $B$ 入手，根据位与的性质可知，二进制下 $B$ 为 $1$ 的位置上必须 $x$ 和 $y$ 都是 $1$。然后要满足和为 $A$，所以还要在 $x$ 或 $y$ 上加上 $2^i$，而且不能同时加或者或者与之前的 $1$ 有重叠，否则就不满足位与的条件了。

然后考虑如何计算答案。因为 $x\leq y$，所以添置的 $2^i$ 中最大的要加在 $y$ 上，否则一定不满足条件。会发现，如果不考虑添置的最高位，剩下添置的情况是相对的，也就是说会完全抵消掉，因此答案就是添置的最高位 $2$ 次幂的计算次数。

时间复杂度 $O(t\log n)$。

~~说了这么多，我知道这才是你想看的~~
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int po[64];
signed main()
{
	int t,mod;
	cin>>t>>mod;
	po[0]=1;
	for(int i=1;i<=63;i++) po[i]=po[i-1]*2%mod;
	for(int p=1;p<=t;p++)
	{
		int n,m;
		cin>>n>>m;
		if(n<=2*m)
		{
			cout<<0<<endl;
			continue;
		}
		int r=n-2*m,c=0;
		bool flag=0;
		//与已有的1不重叠
		for(int i=63;i>=0;i--)
			if(r>>i&1)
			{
				c++;
				if(m>>i&1)
				{
					cout<<0<<endl;
					c++;
					flag=1;
					break;
				}
			}
		if(flag) continue;
		//找最高位
		for(int i=63;i>=0;i--)
			if(r>>i&1)
			{
				cout<<1ll*po[i]*po[c-1]%mod<<endl;
				break;
			}
	}
}
```


---

## 作者：Big_Dinosaur (赞：0)

把 $A$ 和 $B$ 转化成二进制，如样例一第一组：$A=100_2$，$B=001_2$。

因为 $x \operatorname{AND} y = B$，则有 $(x-B)+(y-B)=A-2B$（原因：$x\operatorname{AND} B = B$，$y\operatorname{AND} B = B$，两边同时减 $B$，再进行与运算为 $0$，方便后续运算）。当 $A=100_2$，$B=001_2$ 时，$(x-B)+(y-B)=A-2B=110_2$。因为 $y>x$，则最高位的 $1$ 在 $y-B$ 中，它在 $(x-B)+(y-B)$ 中位于第 $i$ 位（从右往左，最右边第 $0$ 位），$(x-B)+(y-B)$ 有 $j$ 位 $1$，最高位的 $1$ 贡献值为 $2^{i}$。剩下的 $1$ 可以随便分配，贡献为 $2^{j-1}$，它们在 $x-B$ 与在 $y-B$ 中概率相等。因此，最后答案为 $2^{i+j-1}$。

特殊情况：

1. $A-2B<B$。
2. $(A-2B)\operatorname{AND}B\ne 0$。

这两种情况为 $0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO {
	inline int r() {
		int z=1,y=0;
		char t=getchar();
		while(t<'0'||t>'9') {
			if(t=='-')z=-1;
			t=getchar();
		}
		while(t<='9'&&t>='0') {
			y=(y<<1)+(y<<3)+(t^48);
			t=getchar();
		}
		return z*y;
	}
	inline void w_(int x) {
		if(x<0) {
			x=-x;
			putchar('-');
		}
		if(x==0)return;
		w_(x/10);
		putchar(x%10+48);
	}
	inline void wln(int x) {
		if(x==0)putchar('0');
		else w_(x);
		putchar('\n');
	}
}
using namespace IO;
namespace D1n0{
	inline void _(){
		int t=r(),x,y,m=r(),Ans,la;
		while(t--) {
			x=r(),y=r();
			x-=y*2;
			if(x&y||x<0) {
				wln(0);
				continue;
			}
			Ans=1;
			la=0;
			while(x) {
				la=x;
				x-=(x&(-x));
				(Ans*=2)%=m;
			}
			(Ans*=(la%m))%=m;
			(Ans*=(m/2+1))%=m;
			wln(Ans);
		}
	}
}
signed main(){
	D1n0::_();
}
```

---

## 作者：ArcaStellar (赞：0)

# P10118 AND
题意要求根据给定的 $A,B$，求出所有符合条件的 $x,y$，最后计算 $\sum (y-x)$

## 分析思路

### 初步分析（试图找规律）
因为题目涉及到二进制，所以我们可以先考虑把 $x$、$y$、$A$、$B$ 表示成二进制。
例如，对于样例 $A=10,B=4$，写成 $A=1010$，$B=0100$

然后，因为 $x+y=A,x\ \text{AND}\ y=B$，我们就尝试从 $A,B$ 的第 $i$ 位二进制反推 $x,y$ 的第 $i$ 位二进制（分别记作 $x_i,y_i$）

------
 | $(x_i,y_i)$ | 无解 | 两组解：$(1,0),(0,1)$ | $(0,0)$ | $(1,1)$，但是会有进位$\dagger$ |
| :-----------: | :-----------: | :------------: | :-----------: | :-----------: |
| $A$ | $1$ | $1$ | $0$ | $0$ |
| $B$ | $1$ | $0$ | $0$ | $1$ |

$\dagger$ 解释一下 $A=0,B=1$ 的情况。比如说 $A=6=(110)_2,B=1=(001)_2$,，此时 $x=1=(001)_2,y=5=(101)_2$，虽然 $x,y$ 最后一位都是 $1$，但是倒数第二位并不满足表格，这是因为二进制里加法导致 $1+1$ 进位了，所以，在反推的时候，要把进位消掉。具体的做法就是 `A-=(1<<i)`。
PS： 其实这里 `1<<i` 和 `1<<(i+1)` 都是可以的，前者的话因为 $A_i=0$，所以会向前一位借一；后者是直接对前一位减一，两者都达到了对前一位减一这一目的。

**所有满足条件的 $x,y$ 都会满足这个表格。**

### 用二进制表示改写求和式

然后，我们再回看所求的式子。如果把 $x,y$ 写成 $\sum 2^i$ 的形式，就可以写成

$\sum (\sum y_i\times2^{i}-\sum x_i\times 2^{i}) \pmod M$，当且仅当 $x,y$ 符合条件，其中 $x_i$ 表示 $x$ 的第 $i$ 位。

所以，如果 $x_i=y_i$，那么在上面这个求和的式子里，他们的差就是 $0$，可以忽略。我们现在要做的，就是**找出 $x,y$ 二进制位不同的位置**（也就是找到 $i$，使得 $A_i=1,B_i=0$）。

### 考虑贡献

然后，因为 $x\le y$，对于**不是最高位**的 $x_k,y_k$ 而言，他们是对称的。即可以 $x_k=1,y_k=0$，也可以 $x_k=0,y_k=1$。如果固定所有其他二进制位不变，只考虑 $(x_k,y_k)$，可以知道有一半的 $\sum 2^{y_i}-\sum 2^{x_i}$ 是 $(x_k,y_k)=(0,1)$，即 $(1-0)*2^k=2^k$；另一半是 $(x_k,y_k)=(1,0)$，即 $(0-1)*2^k=-2^k$。这样就刚好抵消了。所以，**对于不是最高位的 $k$，他对答案没有影响**。

然后考虑最高位，因为要保证 $x\le y$，所以最高位只能是 $x_{k_0}=0,y_{k_0}=1$。他才是对答案有影响的。

然后考虑影响多少。最终的答案就是 $2^{k_0}\times\text{cur}\pmod M$，其中 $\text{cur}$ 是最高位的出现次数。那么出现次数如何计算呢？这其实就是排列组合问题了。假定一共有 $L$ 位 $x,y$ 二进制位不相同（包括了最高位），那么最高位的出现次数就是 $2^{L-1}$，其意义就是，对于所有非最高位的 $x_k,y_k$ 有 $2$ 种选择：$(0,1)$ 或 $(1,0)$。而一共有 $L-1$ 个非最高位。

综上所述，最终的答案就是 $2^{k_0}\times 2^{L-1}\pmod M$。

### 特殊情况（附证明）

最后的最后还有特殊情况，**如果 $A<2\times B$ 的话，也是不成立的**。

极限情况下 $x=y$，此时 $2\times B=A$。

当 $x<y$ 时，由于 $a=a\ \text{AND}\ 1, 0=a\ \text{AND}\ 0\ (a\in \{0,1\})$，

所以 $x\ \text{AND}\ y=B\le x$（因为按位与操作之后，一定不会发生 $x_k=0\rightarrow x_k=1$ 的情况，所以不可能更大），

所以 $2\times B\le 2\times x\lt x+y=A$，

所以 $2\times B<A$。

综上，一定有 $2\times B\le A$。


## 最后附完整代码

```cpp
// 调试 RE：-fsanitize=address,undefined
#include <bits/stdc++.h>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using ll = long long;
using ld = long double;
using lll = __uint128_t;
using pii = pair<ll, ll>;
#define YES cout << "YES\n"
#define NO cout << "NO\n"

ll MOD;
// 懒得搞 long long 的溢出、取模……之类的东西，直接用 __uint128_t 开 128 位整数偷懒了（
inline lll read() {
  lll x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - 48;
    ch = getchar();
  }
  return x * f;
}

inline void print(lll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    print(x / 10);
  putchar(x % 10 + '0');
}

void solve() {
  ll a, b;
  cin >> a >> b;
  // 对应特殊情况
  if (b * 2 > a) {
    print(0);
    putchar('\n');
    return;
  }
  lll ans = 1;
  vector<int> dif;
  for (int i = 0; i <= 63; i++) {
    bool oa = a & (1ll << i);
    bool ob = b & (1ll << i);
    // 对应前文提到的表格
    if (oa && ob) {
      ans = 0;
      break;
    } else if (!oa && !ob) {
      continue;
    } else if ((!oa) && ob) {
      a -= (2ll << i);
    } else {
      dif.push_back(i);
    }
  }
  // 如果是无解的情况，或者出现 x=y 的情况，答案都是 0
  if (!ans || dif.size() == 0) {
    print(0);
    putchar('\n');
    return;
  }
  // 否则输出答案
  ans = (lll(1) << (dif.size() - 1)) % MOD * (lll(1) << dif.back()) % MOD;
  print(ans % MOD);
  putchar('\n');
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  int t = 1;
  cin >> t >> MOD;
  while (t--)
    solve();
  return 0;
}
```


---

