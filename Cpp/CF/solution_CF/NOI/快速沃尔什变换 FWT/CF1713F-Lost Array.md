# Lost Array

## 题目描述

我的 orzlers，我们可以把这个问题从 $O(S^3)$ 优化到 $O\left(T^\frac{5}{9}\right)$！

—— Orzlim 教创始人 Spyofgame

很久以前，Spyofgame 发明了著名的数组 $a$（$1$ 下标）长度为 $n$，其中包含了关于世界和生命的信息。之后，他决定将其转换为矩阵 $b$（$0$ 下标），大小为 $(n+1) \times (n+1)$，其中包含了关于世界、生命以及更深层次的信息。

Spyofgame 按照以下规则将 $a$ 转换为 $b$：

- 当 $0 \leq i \leq n$ 时，$b_{i,0} = 0$；
- 当 $1 \leq i \leq n$ 时，$b_{0,i} = a_i$；
- 当 $1 \leq i, j \leq n$ 时，$b_{i,j} = b_{i,j-1} \oplus b_{i-1,j}$。

这里 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

今天，考古学家发现了著名的矩阵 $b$。然而，矩阵中的许多元素已经遗失。他们只知道 $b_{i,n}$ 的值，其中 $1 \leq i \leq n$（注意这些是最后一列的部分元素，而不是最后一行）。

考古学家想知道，是否存在一个可能的数组 $a$。你能帮他们还原出任意一个可能的 $a$ 吗？

## 说明/提示

如果我们令 $a = [1,2,3]$，那么 $b$ 如下：

$\bf{0}$  $\bf{1}$  $\bf{2}$  $\bf{3}$  
$0$  $1$  $3$  $0$  
$\bf{0}$  $1$  $2$  $2$  
$\bf{0}$  $1$  $3$  $1$  

生成的 $b_{1,n}, b_{2,n}, \ldots, b_{n,n}$ 为 $[0,2,1]$，这与考古学家发现的结果一致。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
0 2 1```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
1
199633```

### 输出

```
199633```

## 样例 #3

### 输入

```
10
346484077 532933626 858787727 369947090 299437981 416813461 865836801 141384800 157794568 691345607```

### 输出

```
725081944 922153789 481174947 427448285 516570428 509717938 855104873 280317429 281091129 1050390365```

# 题解

## 作者：vectorwyx (赞：33)

考虑一个牛逼想法，我们先把 $a$ 贡献到对角线上，再由对角线贡献到 $b$。为了方便，把 $a$ 和对角线从右往左重编号为 $0,1,\cdots,n-1$，那么 $a$ 的第 $i$ 个位置会对对角线上的第 $j$ 个位置贡献 $\binom{i}{j}$ 次。而我们知道 $\binom{i}{j} \bmod 2=1$ 当且仅当 $i,j$ 二进制分解后 $j$ 是 $i$  的子集，所以由 $a$ 求对角线只需要对 $a$ 求超集和。同理可得由对角线推 $b$ 只需要对对角线求子集和。现在知道 $b$，那对 $b$ 做一次子集和的逆再做一次超集和的逆就得到了 $a$。由于是异或，子集和的逆即为子集和，超集和的逆即为超集和。这样我们就以 $O(n\log n)$ 的复杂度解决了本题。

非常震撼，tyy 实在是不平凡的！

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define ptc putchar
#define emp emplace
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e6+5;
int a[N],n; 

signed main(){
	cin>>n;n--;
	fo(i,0,n) a[i]=read();
	int lg=(int)log2(n);
	fo(i,0,lg)
		go(j,n,0) if(j>>i&1) a[j]^=a[j^(1<<i)];
	fo(i,0,lg)
		fo(j,0,n) if((j>>i&1)^1) a[j]^=a[j^(1<<i)];
	go(i,n,0) cout<<a[i]<<' ';
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：Little09 (赞：7)

第一步是如果给定 $a$，怎么求 $b$ 的最后一列。

考虑到 $b_{i,j}=b_{i,j-1}\ \text{xor}\ b_{i-1,j}$，那么我们考虑最终 $b_{i,n}$ 的贡献：对于每个 $b_{0,j}$，设 $b_{0,j}$ 有 $k$ 种不同走法（每一步向右或向下走，第一步必须向下）能到达 $b_{i,n}$，那么 $b_{0,j}(a_j)$ 对 $b_{i,n}$ 的贡献有 $k$ 次。由于是异或，$k$ 是奇数贡献为 $a_j$；否则为 $0$。

考虑计算 $b_{0,j}$ 到 $b_{i,n}$ 有几种走法，运用组合数容易得到走法数为 $\left(\begin{array}{c}
i-1+n-j \\
i-1
\end{array}\right)$。这个形式比较难受，我们考虑反转 $a$，并且 $a,b$ 下标都从 $0$ 开始，式子变成了 $\left(\begin{array}{c}
i+j \\
i
\end{array}\right)$。根据 Lucas 定理（即 [[CTSC2017]吉夫特](https://www.luogu.com.cn/problem/P3773) 的经典结论），这个式子有贡献当且仅当 $(i+j)\ \text{and}\ i=i$，也容易转化为 $i\ \text{and}\ j=0$。

将下标设成从 $0$ 开始并反转 $a$ 后，我们得到由 $a$ 推出 $b$ 的式子：$b_i=\oplus_{i\ \text{and}\ j=0}\ a_j$。我们可以用 FWT 或 FMT 在 $O(n\log n)$ 的时间内由 $a$ 计算出 $b$，但这不是本题要求。

本题中已知 $b$ 求 $a$，我们根据子集反演式子：

$$f(S)=\sum_{T \subseteq S} g(T) \Leftrightarrow g(S)=\sum_{T \subseteq S}(-1)^{|S|-|T|} f(T)$$

由于运算是异或，那么不用考虑 $-1$ 的系数，也就是说对于一个数组 $a$ 做一遍 FMT 得到 $b$，那么也可以从 $b$ 做一遍完全一致的 FMT 得到 $a$。

遗憾的是本题还没有做完。你发现把 $i\ \text{and}\ j=0$ 转化成子集形式后，$b$ 数组的前几项未知，那么你也不能做反着的 FMT 从 $b$ 推出 $a$。我场上也就到这里就止步了，所以没有做出此题。

不妨换一个思路。定义 $c$ 是 $a$ 做一遍后缀 FMT 的结果，即 $c_i$ 为所有 $i$ 的超集 $a$ 的异或和。考虑 $i\ \text{and}\ j=0$ 是 $i$ 的所有位 $j$ 都不能存在。我们容斥，枚举 $i$ 的子集 $k$，钦定这 $k$ 位需要选，其他位随意，那么要计算的是满足 $k$ 是 $j$ 的子集的所有 $j$（也就是 $c_k$），原本 $-1$ 的容斥系数由于是异或也不需要考虑。

所以从 $a$ 推 $b$ 得出了一个新的做法：先对 $a$ 每个位置变成其超集的异或和，记这个新数组为 $c$，再对 $c$ 每个位置变成其子集的异或和，就可以得到 $b$。

这个做法不会存在前一个做法“数组的前几项未知”的问题，因此从 $b$ 反着做两个 FMT 回去就行了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1000005];
int main()
{
	cin >> n;
	for (int i=0;i<n;i++) cin >> a[i];
	for (int i=0;i<19;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (j&(1<<i)) a[j]^=a[j^(1<<i)];
		}
	}
	for (int i=0;i<19;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (j&(1<<i)) a[j^(1<<i)]^=a[j];
		}
	}
	for (int i=n-1;i>=0;i--) cout << a[i] << " ";
	return 0;
}

```

小声：看官方题解不是很懂，特别感谢神仙 @[chenxinyang2006](https://www.luogu.com.cn/user/49776) 的指点，让我受益匪浅。

---

## 作者：kradcigam (赞：5)

先考虑第 $0$ 行到第 $n$ 列是怎么推的？

首先，为了方便将第 $0$ 行的数从右往左重标号为 $0, 1, \cdots, n - 1$。我们发现 $(0, i)$ 对于 $(j,n)$ 的贡献是 $C(i + j, i) \pmod 2$，根据 $\text{lucas}$ 定理可得有贡献当且仅当 $i\ \text{and}\ j = 0$。

考虑容斥，枚举 $k$，钦定 $i\ \text{and}\ j$ 在二进制下为 $k$ 的超集，则 $(0,i)$ 向 $(j,n)$ 被贡献次数为 $2^{\text{popcount}(t)}$。于是，直接异或即可。

所以，我们先考虑求出 $t_i$ 表示 $i$ 为超集的数的异或和（$t$ 为 $a_{0,i}$ 的高维后缀异或和）。

考虑枚举 $i\ \text{and}\ j = k$，于是，$a_{j,n}$ 的值即为 $\bigoplus\limits_{k\in j}^{n} t_k$（$a_{j,n}$ 为 $t_{i}$ 的高维前缀异或和）。

综上，我们发现，从第 $0$ 行推到第 $n$ 列是对 $a_{0,i}$ 先做一遍高维后缀异或和，再做一遍高维前缀异或和。

考虑从第 $n$ 列如何反推第 $0$ 行？

直接倒过来做，先对 $a_{n,j}$ 做一遍高维前缀差分异或和，再做一遍高维后缀差分异或和。（因为是在异或运算下，所以前缀和和前缀差分、后缀和和后缀差分都分别是一个东西）。

```cpp
const int N = 5e5 + 10;
int a[N];
signed main() {
	int n; read(n);
	for (int i = 0; i < n; ++i) read(a[i]);
	int lg = log2(n);
	F(i, 0, lg)
		for (int j = 0; j < n; ++j)
			if ((j >> i) & 1) a[j] ^= a[j - (1 << i)];
	F(i, 0, lg)
		for (int j = 0; j < n; ++j)
			if ((j >> i) & 1) a[j - (1 << i)] ^= a[j];
	for (int i = n - 1; ~i; --i) writes(a[i]);
	return 0;
}
```

---

## 作者：周子衡 (赞：4)

虽然生在套路题满天飞的数学赛区，但却意外地是个有点意思的题。

------------

首先考虑每个 $a_i=b_{0,i}$ 会对 $c_j=b_{j,n}$ 造成多少贡献。这相当于在方形棋盘上，从格子 $(1,i)$ 走到格子 $(j,n)$ 的方案数，其中每步要么让 x 坐标加 $1$，要么让 y 坐标加 $1$。显然这是组合数 $\binom{n+j-i-1}{j-1}$。对下标进行一些合适的处理，我们可以使得 $a_i(0\leq i < n)$ 向 $c_j(0\leq j < n)$ 转移的系数变为 $\binom{i+j}{i}$。（具体来说，$c$ 整体左移一位，$a$ 先翻转再左移一位。）

这里我们只关心组合数的奇偶性。根据数论中著名的 Kummer 定理 / Lucas 定理，可得：

**结论** $\binom{i+j}{i}$ 是奇数当且仅当 $i,j$ 二进制加法不发生进位。

这里可以看出本题应该和二进制有关联。注意到如果 $n=2^t$ 恰好是 $2$ 的整数次幂，那么翻转 $c$ 之后，$a$ 和 $c$ 之间的关系就是互为高维前缀和 / 高维差分后的结果，已知 $c$ 求 $a$ 可以直接 $O(t2^t)$ 求解。

对于一般的 $n$，我们试着来沿用上面的做法。考虑找到最小的整数 $t$ 使得 $2^t\geq n$。我们把 $a,c$ 都补齐到 $2^t$ 位。同样对 $c$ 翻转。问题变为：

- 有 $2$ 个长度为 $2^t$ 的整数数组 $(a_0,...,a_{2^t-1})$，$(c_0,...,c_{2^t-1})$。保证 $c_i$ 为 $a$ 中所有下标为 $i$ 的子集的元素的异或和。（这里称一个整数 $x$ 是另一个整数 $y$ 的子集，当且仅当对 $x$ 二进制下每个 $1$，$y$ 对应位上也都是 $1$。）
- 已知了 $a_n=a_{n+1}=\cdots a_{2^t-1}=0$，以及 $c_{2^t-n},c_{2^t-n+1},...,c_{2^t-1}$ 的值。
- 求剩下位置的一组可能值。

考虑递归地解决这个问题。我们对这个问题进行一些适当的泛化：

- 有两个自然数 $n,t$ 满足 $n\leq 2^t$**（不要求 $t$ 有最小性）**。有 $2$ 个长度为 $2^t$ 的整数数组 $(a_0,...,a_{2^t-1})$，$(c_0,...,c_{2^t-1})$。保证 $c_i$ 为 $a$ 中所有下标为 $i$ 的子集的元素的异或和。（这里称一个整数 $x$ 是另一个整数 $y$ 的子集，当且仅当对 $x$ 二进制下每个 $1$，$y$ 对应位上也都是 $1$。）
- 已知了 $a_n,a_{n+1},...,a_{2^t-1}$ **（不限制为 $0$ 了）** 以及 $c_{2^t-n},c_{2^t-n+1},...,c_{2^t-1}$ 的值。
- 求剩下位置的一组可能值。

称上面的问题为一组 A 问题，其规模为 $t$。我们已经会求解 $n=0$ 或 $n=2^t$ 时的 A 问题了。对一般的情形，考虑到 $a,c$ 两边分别剩下 $n,2^t-n$ 个未知值，一定有一边不超过 $2^{t-1}$ 个；我们如果能求解出少的那一边的全部值，就可以顺带把另一侧也全部求出来。而可以发现：递归下去的问题是一个规模为 $t-1$ 的 A 问题！求解整个问题的框架浮现出来。

具体来说，假设 $n \leq 2^{t-1}$。我们先对 $a$ 做一遍高维和（此时暂且认为 $a_0\sim a_{n-1}$ 都是 $0$），从 $c$ 对应位置扣掉值，然后将最高位砍掉，即可缩为规模为 $t-1$ 的问题。还原答案时 $a$ 全部确定，再做一遍高维前缀和即可。$n > 2^{t-1}$ 时大体类似。

时间复杂度分析：单次高维前缀和时间复杂度 $O(t2^t)$，总时间复杂度 $T(t)=T(t-1)+O(t2^t)$，解得 $T(t)=O(t2^t)$。也即，总时间复杂度 $O(n\log n)$。

---

## 作者：qczrz6v4nhp6u (赞：3)

\*2900 就这？？？

### Solution

本文中 $a,b$ 均从 $0$ 开始标号。

首先我们知道 $b_i$ 的表达式：

$$b_i=\bigoplus_{0\le j< n}\Big({i+n-j-1\choose i}\bmod 2\Big)\times a_j$$

即考虑每个 $(1,j)$ 走到 $(i,n)$ 的方案数（并非 $(0,j)$ 开始，因为第一步只能向下走）。

我们有经典结论：${n\choose m}\bmod 2=[m\subseteq n]$。应用模 $2$ 意义下的 Lucas 定理即证。代回原式：

$$\begin{aligned}
b_i&=\bigoplus_{0\le j< n}[i\subseteq(i+n-j-1)]\times a_j\\
&=\bigoplus_{0\le j< n}[i\subseteq(i+j)]\times a_{n-j-1}\\
&=\bigoplus_{0\le j< n}[i\cap j=\varnothing]\times a_{n-j-1}\\
&=\bigoplus_{0\le j< n}[j\subseteq\neg i]a_{n-j-1}
\end{aligned}$$

然后你发现这不就是个子集 xor 吗。但是现在我们要通过 $b$ 求 $a$。根据集合反演那套理论，我们知道

$$f(S)=\sum_{T\subseteq S}g(T)\iff g(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}f(T)$$

由于 xor 可以看作是在模 $2$ 意义下做运算，所以 $-1$ 其实没用，也就是说子集 xor 的逆就是子集 xor。同理，超集 xor 的逆就是超集 xor。

但是我们可能会有一些 $[0,n)$ 以外的位置非 $0$，使得我们无法得知原数组，自然也无法正确求逆。

这时候似乎没什么办法可以处理了。~~如果做题量过万，你就知道这种时候大概是范德蒙德卷积，所以~~考虑对组合数运用范德蒙德卷积。具体地，我们有：

$${i+n-j-1\choose i}=\sum_{k}{i\choose k}{n-j-1\choose i-k}$$

代回原式：

$$\begin{aligned}
b_i&=\bigoplus_{0\le j< n}\Big({i+n-j-1\choose i}\bmod 2\Big)\times a_j\\
&=\bigoplus_{0\le j< n}\Big((\sum_{k}{i\choose k}{n-j-1\choose i-k})\bmod 2\Big)\times a_j\\
&=\bigoplus_{0\le j< n}\Big(\bigoplus_k[k\subseteq i][(i-k)\subseteq(n-j-1)]\Big)\times a_j\\
&=\bigoplus_{k\subseteq i}\bigoplus_{i\setminus k\subseteq j}a_{n-j-1}\\
&=\bigoplus_{k\subseteq i}\bigoplus_{k\subseteq j}a_{n-j-1}
\end{aligned}$$

观察一下，后半部分是超集 xor，前半部分是子集 xor，并且这种做法完全可以规避掉上一种做法所产生的问题，所以直接将 $[0,n)$ 以外的数视为 $0$ 就是对的！

然后根据我们刚刚的结论，子集 xor 的逆是子集 xor，超集 xor 的逆是超集 xor，所以直接启动 FWT 就是 $O(n\log n)$ 了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=524290;
int n,lim,a[N];
void Sub(int *F){
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++)
				F[i|j|k]^=F[j|k];
}
void Sup(int *F){
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++)
				F[j|k]^=F[i|j|k];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	lim=1;while(lim<n)lim<<=1;
//	for(int i=0;i<n;i++)cin>>a[i];
//	reverse(a,a+n);
//	Sup(a),Sub(a);
//	for(int i=0;i<n;i++)cout<<a[i]<<" \n"[i==n-1];
	for(int i=0;i<n;i++)cin>>a[i];
	Sub(a);
	for(int i=n;i<lim;i++)a[i]=0;
	Sup(a);
	reverse(a,a+n);
	for(int i=0;i<n;i++)cout<<a[i]<<" \n"[i==n-1];
	return 0;
}
```

---

## 作者：monstersqwq (赞：3)

$O(n\log ^2 n)$ 或 $O(n\log n)$ 做法，没想明白的话写起来略恶心，但是很好想。

首先发现给定的条件一定可以抽象为每个 $b_i$ 是若干个 $a_i$ 的异或和，那么相当于解一个特殊形式的异或方程，由于有 $n$ 个方程，并且大致可以看出方程的解是固定的一堆 $b_i$ 异或，所以一定有解。

那么考虑观察一下形式，下面放一个 $n=15$ 情况下的方程形式，其中第 $i$ 行第 $j$ 行表示 $b_i$ 是否含有 $a_j$。
```latex
111111111111111
101010101010101
011001100110011
001000100010001
000111100001111
000010100000101
000001100000011
000000100000001
000000011111111
000000001010101
000000000110011
000000000010001
000000000001111
000000000000101
000000000000011

```
可以明显看出这是一个经典的 $1110$ 分形，也就是说可以分治解决，所以对于 $n=2^k$ 的情况可以观察到做一个高维后缀异或和即可还原（即逆变换）。（事实上从 $a$ 到 $b$ 最后一列的过程也是一个高维后缀异或和，这在一般的 $n$ 上有用）

一般的正变换，只需要将缺少的 $a$ 补齐即可。

接下来以上面的图为例说明如何计算一般的 $n$ 的逆变换，因为 $(15)_{10}=(1111)_2$，是较为一般的 $n$。

- 将前 $7$ 个 $b$ 对应的异或上后 $7$ 个，可以发现 $b_1$ 到 $b_7$ 成为了只与前 $7$ 个 $a$ 有关的方程，那么可以递归下去解决。

- 然后取消前 $7$ 个 $a$ 的贡献，也就是取消掉矩阵第 $7$ 行第 $7$ 列的 $1$ 的贡献，注意一般情况下的 $n$ 取消的贡献很多，这里我的做法是设 $a_1$，$a_1$ 中仅解完的 $a$ 为实际值，剩下的皆为 $0$ 来正变换一下，便可以计算出这些解完的 $a$ 的贡献，异或掉即可。

- 最后解一下右上角 $8\times 8$ 的方程，这就是上文所说的 $n=2^k$ 的情况，是好做的，注意前七行的方程需要从矩阵下面找到，上面的已经异或掉了。

复杂度瓶颈在第二步的正变换，每次需要做一次长度为 $n$ 的正变换，总复杂度为 $O(n\log^2 n)$。

观察到需要取消的贡献比较规律，或许有更精细的做法可以到 $O(n\log n)$。

总之都是跑的很快的，我下面的实现也就 $200$ 毫秒，跑的比一半提交都快。

一种 $O(n\log^2 n)$ 的实现：
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<unordered_map>
#define dec fjodifjsdidi
typedef long long ll;
typedef unsigned int ui;
typedef long double ld;
using namespace std;
const int maxn=524300;
int n,a[maxn],ans[maxn],t[maxn];
int lim=1,l=0;
void solve(int x,int sgn)
{
	for(int mid=1;mid<(1<<x);mid<<=1)
	{
		for(int j=0,r=(mid<<1);j<(1<<x);j+=r)
		{
			for(int k=0;k<mid;k++)
			{
				t[j+k]^=t[j+mid+k];
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(lim<n)
	{
		lim<<=1;l++;
	}
	int nw=n,tmp=(1<<l)-n;
	for(int i=l;i>=0;i--)
	{
		if(n&(1<<i))
		{
			for(int j=1;j<=nw-(1<<i);j++)
			{
				a[j]^=a[j+(1<<i)];
			}
			nw-=(1<<i);
		}
	}
	nw=0;
	for(int i=0;i<=l;i++)
	{
		if(!(n&(1<<i))) continue;
		for(int j=0;j<nw;j++) t[j]=a[j+1+(1<<i)];
		for(int j=nw;j<(1<<i);j++) t[j]=a[j+1];
		solve(i,-1);
		for(int j=nw+1;j<=nw+(1<<i);j++) ans[j]=t[j-nw-1];
		for(int j=0;j<(1<<l);j++) t[j]=0;
		for(int j=nw+1;j<=nw+(1<<i);j++) t[j+tmp-1]=ans[j];
		solve(l,1);
		for(int j=1;j<=n;j++) a[j]^=t[j-1];
		nw+=(1<<i);
	}
	for(int i=1;i<=n;i++) 
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
```


---

## 作者：yukimianyan (赞：2)

欣赏：[杨辉三角模 2](https://www.luogu.com.cn/paste/xke1nc6y)。

纪念独立做出的第一道 \*2900。人类智慧找规律做法。

## problem
一个 $n$ 的数列 $a$，给你这个数列做 $n$ 次前缀异或和的结果，还原 $a$。$n\leq 10^5$。

## solution
手算一下 $a$ 的各项“系数”（异或多少次），例如 $n=3$ 的“系数”为 $\{111,101,011\}$ 也就是说 $b=\{a_1\oplus a_2\oplus a_3,a_1\oplus  a_3,a_2\oplus a_3\}$。类似的我们可以得到这样的一个系数矩阵：
```cpp
1111111111111111
0101010101010101
0011001100110011
0001000100010001
0000111100001111
0000010100000101
0000001100000011
0000000100000001
0000000011111111
0000000001010101
0000000000110011
0000000000010001
0000000000001111
0000000000000101
0000000000000011
0000000000000001
```
我们知道这个是组合数对 2 取模后的表，我们不关注这个。只看这个表，它有如下性质：
- 若 $n=2^k$，将系数矩阵划分成四份，其中左下角为空，其它三份完全一致。
- 对于这其它的三份，它们也有如此的性质。
- 重标号：从右往左数 $0,1,2,3,\cdots$，从上往下数 $0,1,2,3,\cdots$。

考虑消元法求解这个问题。考虑 $n=2^k$ 时，将前 $2^{k-1}$ 行与后 $2^{k-1}$ 行异或，得到只有左上角的矩阵，可以继续递归求出 $a_{n/2},\cdots,a_{n-1}$；同理，后 $2^{k-1}$ 行可以继续递归下去，得到右下角的答案 $a_0,\cdots,a_{n/2-1}$。这样得到了一个 $H(n)=2H(n/2)+O(n)=O(n\log n)$ 的算法。

若 $n\neq 2^k$，我们找一个最大的 $k$ 使得 $n=2^k+b$。考虑将问题分成两步：

1. 用下面的 $b$ 行异或上面的 $b$ 行，因为左下角是空的，所以异或后上面 $b$ 行只剩下 $a_{2^k},\cdots,a_{n-1}$ 的数字，可以递归求解。
2. 消去左边刚刚求过的部分，对 $a_0,\cdots,a_{2^k-1}$ 这一部分用刚刚说的方法做。

考虑怎么消元：直接求是 $O(n^2)$ 的，但是我们一样可以分治，求出左上角和右下角，合并一下，复杂度 $T(n)=2T(n/2)+O(n)=O(n\log n)$ 并不爆炸。

所以总的时间复杂度是 $G(n)=G(n/2)+T(n)+H(n)=G(n/2)+O(n\log n)=O(n\log n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/zqvfzqx4.png)
## code
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long LL;
int n,ret[1<<19],lg[1<<19];
vector<int> reduce(int L,int R,int x,int y){
	if(L==R) return {x<=L&&L<=y?ret[L]:0};
	int mid=(L+R)>>1;
	vector<int> up=reduce(L,mid,x,y),down=reduce(mid+1,R,x,y),ans={};
	int len=R-L+1;
	for(int i=0;i<len/2;i++) ans.push_back(up[i]^down[i]); 
	for(int i=0;i<len/2;i++) ans.push_back(down[i]);
	return ans;
}
void calc(vector<int> val,int L,int R){
//	printf("calc(%d,%d)\n",L,R);
//	assert(val.size()==R-L+1);
//	printf("{");
//	for(int x: val) printf("%d,",x);
//	printf("}\n");
	if(L==R) return void(ret[L]=val.front());
	int mid=(L+R)>>1;//[L,mid],[mid+1,R]
	int len=R-L+1;
	vector<int> down={};
	for(int i=len/2;i<len;i++) down.push_back(val[i]);
	calc(down,mid+1,R);
	vector<int> up={};
	for(int i=0;i<len/2;i++) up.push_back(val[i]^val[i+len/2]);
	calc(up,L,mid);
}
void solve(vector<int> val,int L,int R){
//	printf("solve([%d,%d])\n",L,R);
//	assert(val.size()==R-L+1);
//	printf("{");
//	for(int x: val) printf("%d,",x);
//	printf("}\n");
	int k=1<<lg[R-L+1],len=R-L+1;
	if(R-L+1==k) return calc(val,L,R);
	vector<int> sub={};
	for(int i=k;i<len;i++) sub.push_back(val[i-k]^val[i]);
	solve(sub,L,L+len-k-1);
	vector<int> rec=reduce(L+len-k-k,L+len-k-1,L,L+len-k-1);
//	printf("rec:");
//	for(int x: rec) printf("%d,",x);puts("");
	for(int i=k;i<len;i++) val.pop_back();
	for(int i=0;i<k;i++) val[i]^=rec[i];
	calc(val,L+len-k,R);
}
int main(){
	scanf("%d",&n);
	lg[0]=-1; for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	vector<int> val={};
	for(int i=0,x;i<n;i++) scanf("%d",&x),val.push_back(x);
	solve(val,0,n-1);
	for(int i=0;i<n;i++) printf("%d%c",ret[i]," \n"[i==n-1]);
	return 0;
}

```


---

## 作者：ExplodingKonjac (赞：2)

[原题链接](https://www.luogu.com.cn/problem/CF1713F)

## 题目分析

题意：有一个长度为 $n$ 的序列 $a$，你不知道它是什么，记对 $a$ 做 $k$ 次前缀 $\operatorname{xor}$ 和得到的序列为 $b_k$，题目告诉你 $b_{1,n},b_{2,n},\dots,b_{n,n}$，你需要构造出一个 $a$。

首先考虑一个问题，怎么根据 $a$ 求出 $b_{1,n},b_{2,n},\cdots,b_{n,n}$。先把异或运算当做普通的加法运算。我们记 $\displaystyle A(x)=\sum_{i=1}^n a_ix^i,\ B_k(x)=\sum_{i=1}^nb_{k,i}x^i$。因为 $b_k$ 是 $a$ 做 $k$ 次前缀和，那么就有 $B_k(x)=A(x)\left(\dfrac{1}{1-x}\right)^k$。取 $n$ 次项系数可以得到

$$
b_{k,n}=[x^n]B_k(x)=\sum_{i=0}^na_{n-i}{k+i-1\choose k-1}
$$

然后，因为是异或运算，所以每个 $a_{n-i}$，只有贡献系数为奇数时才会真正有贡献。接下来介绍一个神奇的结论：$\displaystyle{n+m\choose n}\bmod 2=[n\operatorname{and} m=0]$。

可以使用 Lucas 定理推导这个结论。首先用 Lucas 定理得到 $\displaystyle{n+m\choose n}={n/2+m/2\choose n/2}{(n+m)\bmod 2\choose n\bmod 2}$。

对于右式的左半边继续做，直到 $n=m=0$。每次取出来的 $\displaystyle{(n+m)\bmod 2\choose n\bmod 2}$ 可以看做取出 $n,m$ 的每一位二进制位。因为 $\displaystyle{n+m\choose n}\bmod 2=1$ 当且仅当每一次取出来的组合数 $\bmod 2=1$，枚举一下，发现只有 $\displaystyle{(1+1)\bmod 2\choose1}=0$ 不符合条件。也就是说 $n,m$ 的每一位都不能同时为 $1$，即 $n\operatorname{and}m=0$。

所以这下好办多了，把原式写成这样：

$$
b_{k,n}=\sum_{i=0}^na_{n-i}[(k-1)\cap i=\varnothing]=\sum_{i=0}^na_{n-i}[i\subseteq\complement(k-1)]
$$

这是一个子集求和的形式，直接 FWT 即可。你现在做完了原问题的反演。

然后你思考：既然这是 FWT，那我直接逆变换回去，是不是就可以做出原问题了呢？

好的，然后你写了一发，发现样例都过不了。问题在哪呢？

我们记 $m=\min\{2^k|k\in\mathbb{Z},2^k\ge n\},\ a'_i=a_{n-i},\ b'_i=b_{\complement i+1,n}=b_{m-i,n}$。所以我们要求的是 $a'=\operatorname{FWT_{or}}^{-1}(b')$。

但问题的关键是，长度需要被补全成 $2$ 的幂，但是题目只告诉了你 $b_{1,n},b_{2,n},\dots,b_{n,n}$。也就是说对于 $b'$，你是不知道 $[0,m-n)$ 之间的项的。如果你直接做 FWT 就寄了，所以我们需要补全这些项。

对于一般的 FWT 来说，这是不可能的，但是这是异或运算，并且有题目的特殊限制，所以可以实现。先说结论：令 $c\gets\operatorname{FWT_{and}}(b')$，再 $\forall i\in[0,m-n),\ c_i\gets0$，然后 $b'\gets\operatorname{FWT_{and}}^{-1}(b')$。

我也不知道这种方法是怎么想到的，所以只讲证明。

首先对于 $i\ge m-n$，第一步求出来的 $c_i$ 肯定是正确的，因为其超集的位置都是已知的。而关键结论就是证明对于 $i<m-n$，都有 $c_i=0$。我们可以直接把式子写出来：

$$
\begin{aligned}
	c_i&=\sum_{j\supseteq i}b'_j\\
    &=\sum_{j\supseteq i}\sum_{k\subseteq j}a'_k\\
    &=\sum_k a'_k\sum_{j\supseteq i\ \land\ j\supseteq k}1\\
    &=\sum_k a'_k\sum_{j}[i\cup k\subseteq j]
\end{aligned}
$$

注意我们是异或运算，只有贡献系数是偶数的时候才真正有贡献。我们发现 $\sum_j [i\cup k\subseteq j]$ 只有当 $i\cup k=U$ 时才 $\bmod 2=1$，其余时候都是二的幂。所以原式可以写成：

$$
c_i=\sum_k a'_k[i\cup k=U]=\sum_{k\supseteq \complement i} a'_k
$$

这是一个关于 $a'$ 的超集和。注意 $\complement i=m-1-i$。所以当 $i\in[0,m-n)$ 时，$\complement i \in [n,m)$。而因为 $a'_i=a_{n-i}$，所以 $a'$ 只有在 $[0,n)$ 有值，对于 $i\in[n,m)$，可以看做 $a'_i=0$，其超集和自然也为 $0$。所以 $\forall i\in[0,m-n),\ c_i=0$。

## 代码实现

非常短。注意到因为异或运算的性质，FWT 的正逆变换均相同。

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int n,m,U,a[2000005];
inline void FWT_or(int *a)
{
	for(int i=1;i<m;i<<=1)
		for(int j=0;j<m;j+=(i<<1))
			for(int k=0;k<i;k++)
				a[i+j+k]^=a[j+k];
}
inline void FWT_and(int *a)
{
	for(int i=1;i<m;i<<=1)
		for(int j=0;j<m;j+=(i<<1))
			for(int k=0;k<i;k++)
				a[j+k]^=a[i+j+k];
}
int main()
{
	int x;
	qin>>n;
	for(m=1;m<n;m<<=1);
	U=m-1;
	for(int i=1;i<=n;i++) qin>>x,a[(i-1)^U]=x;
	FWT_and(a);
	for(int i=0;i<m-n;i++) a[i]=0;
	FWT_and(a),FWT_or(a);
	for(int i=1;i<=n;i++) qout.writesp(a[n-i]);
	return 0;
}
```


---

## 作者：happybob (赞：0)

操作就是做 $n$ 次前缀异或和，每次操作后会告诉你序列末尾的数，还原原序列。

不妨设序列从 $0$ 开始编号，对于 $k$ 次操作后，序列的末尾是什么。对于任意一个 $i \in [0,n)$，相当于其从 $(1,i)$ 开始，每次向右或向下，移动到 $(k,n-1)$，方案数是 $\dbinom{k-1+n-1-i}{k-1}$。根据 Lucas 定理，其模 $2$ 等于 $1$ 当且仅当 $k-1 \subseteq k-1+n-1-i$，也就是 $(k-1) \cap (n-1-i)=\varnothing$。将 $a$ 序列反转，则相当于是 $i \cap (k-1) = \varnothing$。

总而言之，对于任意 $0 \leq i < n$，我们得知了所有与 $i$ 不交的数的异或和。我们记其为 $a_i$。则 $a_i = \sum \limits_{j \cap i = \varnothing} b_j$。我们希望还原 $b$。

若 $n=2^k$，我们可以得到每个集合的子集异或，IFWT 回去就行。但是 $n \neq 2^k$ 时，不能简单地通过将 $n$ 补全至 $2^{\lceil \log_2 n\rceil}$ 以解决问题，原因是这样你只知道 $n$ 个子集异或信息，不足以求出整个 $b$。

考虑从 $b$ 到 $a$ 的过程，我们希望有一个可逆的过程。考虑对 $b$ 求超集和得到 $c_i = \bigoplus \limits_{i \subseteq j} b_j$，然后对 $c$ 求子集和 $a_i = \bigoplus \limits_{j \subseteq i} c_j$。考虑任意一个 $i$ 对 $j$ 的贡献，若存在某位同时为 $1$，则这位恰好被算两次，根据异或的性质被抵消。否则其恰好被算一次。

对于 $a$ 到 $b$，将上述过程逆向求解，把 $a$ IFWT 回去得到 $c$，并将 $c$ 的从 $n$ 开始的位设为 $0$，然后 IFWT 得到 $b$ 即可。

---

## 作者：Mashu77 (赞：0)

称矩阵第一行为 
$a$，最后一列为 
$b$，并将 
$a$
 翻转，从 
$0$
 开始标号。不难看出 
$b_i=\oplus_{i=0}^{n-1}a_i[\binom{i+j}{j}\bmod 2]$。

对后式用卢卡斯定理，得到 
$(i+j)\&j=j$。即 $i\&j=0$。若已知 
$a$，可以 FWT 求其子集和，各位翻转一下即为 
$b$；但当 
$n$ 不为 
$2$
 的整数次幂时，不能将 
$b$
 翻转由 
$b$
 求 
$a$。

翻转是由于 
$(i+j)\& j=j$，若其为 $i\&j=
j$，就是一个简单的子集和。由此考虑到用对角线作为中转。

从 
$a$
 到 
$b$，必然经过仅经过一次对角线。从 
$a_
i$
 到对角线（从右向左从 
$0$
 开始标号）$j$
 再到 
$b_
k$，方案为 
$\binom{i}{j}\binom{k}{j}$。产生贡献的充要条件即为 
$i\&j=j∧k\&j=
j$。于是对 
$a$
 求超集和再求子集和即为 
$b$。这样就规避了翻转。从 
$b$
 到 
$a$
 只需逆着做一遍即可。复杂度 
$O
(
n
\log
n
)$。

---

## 作者：PosVII (赞：0)

看每个 $a_{i}$ 对 $b_{j,n}$ 的贡献，显然，这两点间路径数量就为贡献的次数，因为是异或所以看奇偶性即可。我们发现，$a_{i}$ 对 $b_{j,n}$ 的贡献就是 $C^{j-1}_{n-i+j}$。也就是说 $a_{n-i+1}$ 对 $b_{j,n}$ 的贡献就是 $C^{j-1}_{i-1+j-1}$。

可以证明，对于组合数 $C^{i}_{j}$，其为奇数当且仅当 $i$ 是 $j$ 的子集。然后我们可以根据这些条件建立起一个异或方程组，可惜时间复杂度是 $O(n^3)$，不足以解决问题。

当然可以优化，发现这个异或方程组中最多 $n \sqrt{n}$ 个贡献，可以暴力存下来进行求解，但是会被卡。以下是一个异或方程组矩阵的示例。（我将 $a$ 数组反了过来，以便简化组合数）

```
1 1 1 1 1
1 0 1 0 1
1 1 0 0 1
1 0 0 0 1
1 1 1 1 0
```

因为这个异或方程组的矩阵建立方式很特殊，感觉有规律可循，希望能利用这个图快速求解。我们沿着朴素的异或方程组思路走，我们想将这个矩阵消出一个斜三角，于是矩阵变成了这样：

```
1 1 1 1 1
0 1 0 1 0
0 0 1 1 0
0 0 0 1 0
0 0 0 0 1
```

然后再按常规思路把除对角线外的东西消掉：

```
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1
```

然后就是答案了，我们发现，我们发现，第一步消元中，对第 $i$ 行消元刚好使用了 $i$ 的所有真子集，这个是可以递推优化的。

第二步中，第 $i$ 行消元刚好使用了所有以 $i$ 为真子集的行，这个同样是可以递推优化的。

然后最后的 $a$ 数组就是答案。

```
// LUOGU_RID: 104820427
#include<bits/stdc++.h>
template<typename G>inline void read(G&x) {G f=1;x=0;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();x*=f;}
using namespace std;
const int MAXN=1e6+5;
int n,a[MAXN];
signed main() {
	read(n);--n;
	for(int i=0;i<=n;++i) read(a[i]);
	for(int j=0;j<19;++j) {
		for(int i=n;i>=0;--i) {
			if(i>>j&1) a[i]^=a[i^(1<<j)];
		}
	}
	for(int j=0;j<19;++j) {
		for(int i=0;i<=n;++i) {
			if(!(i>>j&1)) a[i]^=a[i^(1<<j)];
		}
	}
	for(int i=n;i>=0;--i) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：Iam1789 (赞：0)

好牛逼的题呀。


**本题解中的 $a,b$ 均是从 $0$ 开始计数的.**

考虑 $a_0$ 对矩阵每个位置的贡献。我们不会数学，先打个表：
```
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0
1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0
1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0
1 0 1 0 0 0 0 0 1 0 1 0 0 0 0 0
1 1 0 0 0 0 0 0 1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0
1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0
1 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0
1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```
上面是 $n=16$ 时的表，其中 $1$ 表示 $a_0$ 对这个位置有贡献，$0$ 表示没有贡献。建议对着这张表阅读以下内容。



设第 $i$ 行第 $j$ 个数为 $c_{i,j}$，$f_{x1,y1,x2,y2}$ 为 $c_{x1,y1},\ldots,c_{x2,y2}$。通过观察，我们有以下结论：

**结论一**：若 $c_{i,j}=1$，则 $a_{n-j+1}$ 对 $b_{i,n}$ 有贡献。

证明：$a_1$ 对 $b_{i,j}$有贡献，因此 $a_{n-j+1}$ 对 $b_{i,(n-j+1)+(j-1)}$ 有贡献。

通过这个结论，可以看出来将 $c$ 左右翻转就是 $a_j$ 对 $b_{i,n}$ 的贡献情况。

**结论二**：$c_{i,i}(i>0)=0$

证明：由于贡献的最唯一根本来源 $c_{1,1}$ 在 $c$ 矩阵的对角线上，所以该矩阵是关于对角线对称的，因此 $c_{i,i-1}=c_{i-1,i},c_{i,i}=c_{i,i-1}\oplus c_{i-1,i}=0$。

**结论三**：第 $i(i>0)$ 行的周期为 $2^{\lceil \log_2 (i+1) \rceil}$，且后半周期均为 $0$。

证明：数学归纳法。$k=1$ 时，该结论显然成立。设 $x=2^{k-1},2^{k-1} \leq y < 2^k$。不妨设前 $x$ 行都已经满足此结论。行和列是等价的，因此该周期实质上是矩阵的周期，即 $f_{x,0,2x-1,x}=f_{x,0,x,x},\ldots,c_{x,x}$，这是前半周期。根据结论一，$c_{y,y}=0$，而 $f_{y+1,y-1,2y-1,y-1}$ 都可以通过平移的方式认为是上方某个周期的后半周期，即全 $0$，因此 $f_{y+1,y-1,2y-1,y-1}$ 也全为 $0$。

有以上结论后，由于二进制的优良性质，我们先考虑 $n=2^k$。令 $x=2^{k-1}$，$y,z$ 是 $<x$ 的某个自然数。通过结论三，我们发现，$b_{y+x,n}$ 为只考虑所有的 $z$ 在第 $y$ 行产生的贡献，$b_{y,n} \oplus b_{y+x,n}$ 为只考虑所有的 $z+x$ 在第 $y$ 行产生的贡献，因此我们可以将原问题转化为两个大小为 $x$ 的子问题求解，类似分治树的结构，每一层的时间复杂度为 $\Theta(n)$，因此总时间复杂度为 $\Theta(n\log n)$。

接着考虑 $n\neq2^k$。我们发现对于分治时的中心大矩阵，它通过上述做法并不能重新凑出一个足够大的新矩阵。令 $s= n-2^k,s<2^k$，我们先去计算大小为 $s$ 的边角小矩阵，算出 $a_s,\ldots,a_{n-1}$。让 $i \geq n$ 的 $a_i$ 都为 $0$，将矩阵补全后再去解决中心大矩阵就可以了。相对于 $n=2^k$，还需要枚举 $n$ 的每个二进制位，因此时间复杂度提升到 $\Theta(n \log^2n)$。

### 后记
看了其它选手的题解，发现这个表其实是一个 `FWT` 的形式，~~可惜我太菜了没有看出来，~~ 可能通过这个角度思考会更加方便。还有神仙用组合意义更简洁地做出来了，这道题的方法还是很多的。

---

## 作者：FZzzz (赞：0)

~~看错两次题，两个假做法拼起来就是正解，眼花人大胜利。~~

不需要技术和推导，但是稍微有点费观察的做法。

考虑先由 $b_{i,n}$ 求出 $b_{n,i}$，再求出 $b_{0,i}$。

对于前半部分，我们知道 $b_{i,j}=b_{i,j+1}\oplus b_{i-1,j+1}$。考虑下面这张图，第 $i$ 行 $j$ 列是 `1` 则表示 $b_{i,n}$ 对 $b_{n,j}$ 有贡献：
```plain
1000000000
1100000000
0010000000
0011000000
0010100000
0011110000
0010001000
0011001100
1010101010
1111111111
```
这是一个很漂亮的分形（看不出来的话只看右下角八行八列），可以递归求解，改成迭代的话就是类似 FWT 的形式。我特意画了一个 $n$ 不是二的次幂的情况，这也没差。

严谨证明写起来可能比较繁琐，主要需要证明 $b_{i,n}$ 对右下角的三角中同一列的每个位置的贡献都是同一形式，但是肯定是很直观的。

这部分本质就是其他题解里的子集和，代码写起来也一样。

对于后半部分，我们知道 $b_{i,j}=b_{i+1,j}\oplus b_{i+1,j-1}$。贡献的形式跟上面比较类似，我直接写了，对于下面的图，第 $i$ 行 $j$ 列是 `1` 表示 $b_{n,j}$ 对 $b_{0,i}$ 有贡献：
```plain
1000000000
0100000000
1010000000
0101000000
0010100000
0001010000
0000101000
1000010100
0100001010
1010000101
```
就是第一个图，往左再写一列，然后把那一列横过来再不断左移得到 $n$ 行。

然后考虑这样一个过程：先令 $b_{0,i}=b_{n,i}$，然后从低到高遍历 $n$ 的每一个为 $1$ 的二进制位 $j$，把每个 $b_{0,i}$ 异或上 $b_{0,i-2^j}$。

手玩一下你发现这样的过程就构成了上面的贡献形式。证明也是那种“我不知道怎么证但是它肯定能证”。不过我不是很清楚这个过程的本质。

可以看代码理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5e5+5;
int n,a[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	// 通过最后一列计算最后一行
	for(int i=n-1;i>=0;i--) a[i]=read();
	for(int i=0;i<20;i++)
		for(int j=0;j<n;j++)
			if(j>>i&1) a[j]^=a[j^(1<<i)];
	reverse(a,a+n+1);
	// 通过最后一行计算第一行
	for(int i=0;i<20;i++) if(n>>i&1)
		for(int j=n;j>(1<<i);j--) a[j]^=a[j-(1<<i)];
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```
有没有老哥教教我啊。

---

