# [ABC286F] Guess The Number 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc286/tasks/abc286_f

この問題は **インタラクティブな問題**（あなたが作成したプログラムとジャッジプログラムが標準入出力を介して対話を行う形式の問題）です。

あなたとジャッジは下記の手順を行います。 手順はフェイズ $ 1 $ とフェイズ $ 2 $ からなり、まずフェイズ $ 1 $ を行った直後、続けてフェイズ $ 2 $ を行います。

（フェイズ $ 1 $ ）

- ジャッジが $ 1 $ 以上 $ 10^9 $ 以下の整数 $ N $ を決める。この整数は隠されている。
- あなたは $ 1 $ 以上 $ 110 $ 以下の整数 $ M $ を出力する。
- さらにあなたは、すべての $ i\ =\ 1,\ 2,\ \ldots,\ M $ について $ 1\ \leq\ A_i\ \leq\ M $ を満たす、長さ $ M $ の整数列 $ A=(A_1,A_2,\ldots,A_M) $ を出力する。
 
（フェイズ $ 2 $ ）

- ジャッジから、長さ $ M $ の整数列 $ B=(B_1,B_2,\ldots,B_M) $ が与えられる。ここで、 $ B_i\ =\ f^N(i) $ である。 $ f(i) $ は $ 1 $ 以上 $ M $ 以下の整数 $ i $ に対し $ f(i)=A_i $ で定められ、 $ f^N(i) $ は $ i $ を $ f(i) $ で置き換える操作を $ N $ 回行った際に得られる整数である。
- あなたは、$ B $ の情報から、ジャッジが決めた整数 $ N $ を特定し、$ N $ を出力する。
 
上記の手順を行った後、直ちにプログラムを終了することで正解となります。

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたが作成したプログラムとジャッジプログラムが標準入出力を介して対話を行う形式の問題）です。

（フェイズ $ 1 $ ）

- まず、$ 1 $ 以上 $ 110 $ 以下の整数 $ M $ を出力してください。出力後、必ず改行してください。
 
> $ M $

- その後、空白区切りで $ 1 $ 以上 $ M $ 以下の整数からなる長さ $ M $ の整数列 $ A=(A_1,A_2,\ldots,A_M) $ を出力してください。出力後、必ず改行してください。
 
> $ A_1 $ $ A_2 $ $ \ldots $ $ A_M $

（フェイズ $ 2 $ ）

- まず、長さ $ M $ の整数列 $ B=(B_1,B_2,\ldots,B_M) $ が入力から与えられます。
 
> $ B_1 $ $ B_2 $ $ \ldots $ $ B_M $

- 整数 $ N $ を求め、出力してください。出力後、必ず改行してください。
 
> $ N $

不正な出力がなされた場合、ジャッジは `-1` を出力します。この時、提出はすでに不正解と判定されています。ジャッジプログラムはこの時点で終了するため、あなたのプログラムも終了するのが望ましいです。

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 10^9 $ 以下の整数
 
### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で不正な出力を行った、あるいはプログラムが途中で終了した場合のジャッジ結果は不定です。**
- 答えを出力したら(または `-1` を受け取ったら)直ちにプログラムを正常終了してください。そうしなかった場合、ジャッジ結果は不定です。
- 特に、余計な改行も不正なフォーマットの出力とみなされるので注意してください。
 
### 入出力例

以下は、$ N\ =\ 2 $ の場合の入出力例です。

    入力 出力 説明        ジャッジは $ N=2 $ と決めました。$ N $ は入力としては与えられず、隠されています。    `4` $ M $ を出力します。    `2 3 4 4` $ A=(2,3,4,4) $ を出力します。    `3 4 4 4`   $ f^2(1)=3,f^2(2)=4,f^2(3)=4,f^2(4)=4 $ なので、ジャッジは $ B=(3,4,4,4) $ をあなたのプログラムに与えます。    `2` $ B $ から $ N=2 $ であると特定しました。 $ N $ を出力し、プログラムを正常終了させてください。

# 题解

## 作者：_Ad_Astra_ (赞：4)

一道很好的数论+构造题。

容易得到，将每个位置连向它下一步的位置，那么最后得到的图的每个子图最后必定连入一个环。进一步考虑不难发现，其实在环前面的部分是没有必要的，因为它们只会被经过一次，会造成点的浪费。因此我们的目标就变成了构造一张由若干个环组成的图。

而这时我们考虑每一个环。不妨设有一个长度为 $n$ 的环，上面的节点按边的顺序编号为 $0,1,2,\cdots,n-1$，那么不难得到每进行一步操作后，原来的 $i$ 将会变成 $i+1 \bmod n$。那么在总共进行 $k$ 次操作以后，$0$ 位置将会变成 $k \bmod n$。由此对于每一个环，设第 $i$ 个环的大小为 $s_i$，最后到达了 $p_i$，进行了 $n$ 次操作，那么可以得到下面的同余方程：

$$p_i \equiv n \pmod {s_i}$$

那么我们就可以得到下面的方程组（设总共有 $m$ 个环）：

$\begin{cases}p_1 \equiv n \pmod {s_1}\\p_2 \equiv n \pmod {s_2}\\\cdots\\p_m \equiv n \pmod {s_m}\end{cases}$

这就可以采用 CRT 解决。（不会的可以戳[这里](https://www.luogu.com.cn/problem/P1495)）

而现在我们就要构造 $s$ 序列。因为节点最多有 $110$ 个，所以有 $\sum\limits_{i=1}^{m}s_i \le 110$。而由于题目中的 $n \le 10^9$，为了确保不会有重复，需要 $\prod\limits_{i=1}^{m}s_i \ge 10^9$。由此我们只需要构造一个数列，满足两两互质以及上述的条件即可。

先考虑朴素的想法：列出前 $9$ 个质数 $2,3,5,7,11,13,17,19,23$，它们的和为 $100$。但是它们的乘积约为 $2.2 \times 10^8$（$223,092,870$），远小于 $10^9$。这时我们考虑修改若干个数使得满足条件。不难想到，修改大数肯定没有修改小数划算，因为同样的花费在小数上对乘积的贡献更大。试几次不难发现，当数列为 $4(2^2),9(3^2),5,7,11,13,17,19,23$（和为 $108$）时，积为 $1,338,557,220$，显然满足条件。

code：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n=108,m=9,a[10]={0,4,5,7,9,11,13,17,19,23},b[110],c[110],mul=1;
int exgcd(int a,int b,int& x,int& y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	int ans=exgcd(b,a%b,y,x);
	y-=x*(a/b);
	return ans;
}
int CRT()
{
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int mm=mul/a[i],x,y;
		exgcd(mm,a[i],x,y);
		ans=(ans+(x>=0?x:x+a[i])*mm%mul*c[i]%mul)%mul;
	}
	return ans;
}
signed main()
{
	cout<<n<<endl;
	int sum=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=a[i];j++)cout<<sum+(j%a[i])<<" ";
		sum+=a[i];
		mul*=a[i];
	}
	cout<<endl;
	for(int i=1;i<=n;i++)cin>>b[i];
	sum=1;
	for(int i=1;i<=m;i++)
	{
		c[i]=((b[sum]-sum)%a[i]+a[i])%a[i];
		sum+=a[i];
	}
	cout<<CRT();
	return 0;	
} 
```

---

## 作者：CarroT1212 (赞：2)

### 题目大意

这是一道交互题。

首先系统会随机选定一个整数 $N\,(1 \le N \le 10^9)$ 但不公布。

你需要输出一个整数 $M\,(1 \le M \le 110)$ 和一个长度为 $M$ 的整数序列 $A\,(1 \le A_i \le M)$。

接着系统会生成一个长度为 $M$ 的序列 $B$，其中 $B_i=i$。对于每个整数 $i\,(1 \le i \le M)$，系统会反复执行“将 $B_i$ 替换为 $A_{B_i}$”的操作 $N$ 次。操作全部完成后，给定 $B$，请你根据 $B$ 求出 $N$。

--------

### 解法分析

首先可以发现，若 $A$ 为一段 $1\sim M$ 的升序排列，将其循环移位一位得到 $A=\{2,3,\cdots,M,1\}$ 后，$N\bmod M=B_1-1$。

同理，若 $A$ 由 $K$ 个这样的循环移位后的升序排列组成，设 $C_1,C_2,\cdots,C_K$ 分别为这些排列的长度（此时 $A=\{2,3\cdots,C_1,1,C_1+2,C_1+3,\cdots,C_1+C_2,C_1+1,\cdots,C_1+C_2+\cdots+C_{K-1}+2,\cdots,C_1+C_2+\cdots+C_K,C_1+C_2+\cdots+C_{K-1}+1\}$），则有 $N \bmod C_1=B_1-1,\ N \bmod C_2=B_{C_1+1}-(C_1+1),\ \cdots,\ N \bmod C_K=B_{C_1+C_2+\cdots+C_{K-1}+1}-(C_1+C_2+\cdots+C_{K-1}+1)$。也就是说，我们可以知道 $N$ 对若干个整数取模的值。

那根据这些，能否通过构造合适的 $C$ 来求出 $N$ 呢？

中国剩余定理点了个赞。（[不会的快去学！](https://www.luogu.com.cn/problem/solution/P1495))

可以使用中国剩余定理求解的问题需要满足所有除数两两互质，于是考虑令 $C=\{2,3,5,7,\cdots\}$，只要 $C$ 内所有元素之积不小于 $10^9$ 就可以保证 $N$ 有唯一解。不过有一个问题，题目要求 $M\le 110$，但是 $2+3+5+7+11+13+17+19+23+29=129>110$，已经不满足条件了，而 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 \times 19 \times 23=223092870<10^9$，不够，没法确定 $N$。那为了让这个乘积尽量大，我们可以给前面两位 $2,3$ 平个方得到 $4,9$，这时总和为 $108$，而且 $4 \times 9 \times 5 \times 7 \times 11 \times 13 \times 17 \times 19 \times 23=1338557220>10^9$。于是最终 $C=\{4,9,5,7,11,13,17,19,23\}$。根据这个 $C$ 造出 $A$ 再求解即可。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define flsh fflush(stdout)
using namespace std;
const int N=117;
ll a[11]={0,1,5,14,19,26,37,50,67,86,109},b[11],c[N],mul=1,sum;
void exgcd(ll p,ll q,ll &x,ll &y) {
	if (!q) { x=1,y=0; return; }
	exgcd(q,p%q,x,y);
	swap(x,y),y-=x*(p/q);
}
ll crt() {
	for (ll i=1;i<=9;i++) mul*=a[i];
	for (ll i=1,d,x,y;i<=9;i++)
		d=mul/a[i],exgcd(d,a[i],x,y),sum=(sum+b[i]*d*(x+(x<0)*a[i]))%mul;
	return sum;
}
int main() {
	printf("108\n"),flsh;
	for (ll i=1;i<=9;i++) {
		for (ll j=a[i]+1;j<a[i+1];j++) printf("%lld ",j);
		printf("%lld ",a[i]);
	}
	printf("\n"),flsh;
	for (ll i=1;i<=108;i++) scanf("%lld",&c[i]);
	for (ll i=1;i<=9;i++) b[i]=c[a[i]]-a[i],a[i]=a[i+1]-a[i]; // 得到余数
	printf("%lld",crt()),flsh;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# ABC286F 题解 



## 思路分析

考虑把 $\{a_i\}$ 写成若干个置换环的形式，对于一个大小为 $k$ 的置换环，根据 $\{b_i\}$ 中的置换环的形态，我们能够得到 $n\bmod k$ 的余数的值。

构造一组互质的模数  $\{p_i\}$，使 $\prod p_i\ge 10^9,\sum p_i\le 110$，用 CRT 求解即可。

给一组合法的构造：$\{p_i\}=\{4,9,5,7,11,13,17,19,23\},\sum p_i=108,\prod p_i\approx 1.3\times 10^9$。

时间复杂度 $\Theta(m)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int B=1338557220;
const int p[9]={4,9,5,7,11,13,17,19,23};
const int MAXN=111;
vector <int> id[9];
int a[MAXN],b[MAXN],x[9];
signed main() {
	for(int i=0;i<9;++i) {
		int d=B/p[i];
		for(int j=1;j<p[i];++j) {
			if((d*j)%p[i]==1) {
				x[i]=d*j;
				break;
			}
		}
	}
	int m=0;
	for(int i=0;i<9;++i) {
		for(int j=0;j<p[i];++j) {
			id[i].push_back(++m);
		}
		for(int j=0;j<p[i];++j) {
			a[id[i][j]]=id[i][(j+1)%p[i]];
		}
	}
	cout<<m<<endl;
	for(int i=1;i<=m;++i) cout<<a[i]<<" ";
	cout<<endl;
	for(int i=1;i<=m;++i) cin>>b[i];
	int ans=0; 
	for(int i=0;i<9;++i) {
		for(int r=0;r<p[i];++r) {
			if(b[id[i][0]]==id[i][r]) {
				ans=(ans+x[i]*r%B)%B;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

> 构造一个排列 $\phi$（$|\phi| \le 110$）满足 $|\{\phi^x \mid x \in [0,10^9]\}| = 10^9+1$。
>
> 另外地，你需要构造映射 $f : \{\phi^x \mid x \in [0,10^9]\} \to [0,10^9]$，满足 $f(\phi^x) = x$。

题解：

不妨建有向图：$g : i \to \phi_i$。发现 $g$ 构成基环森林。显然对于每一个点都会有循环。对于基环树 $S \subseteq g$，对于每一个 $x \in S$，经过足够多（不超过 $110$）次 $\phi$，会陷入循环节为 $S$ 上环的大小的循环。而整个基环树的循环显然为这些循环节的 $\operatorname {lcm}$。于是，最优结构显然是基环森林 $g$ 全部由环组成。设所有环的大小组成的集合为 $A$，则 $A$ 需要满足如下条件：

* $\operatorname{lcm} A \geq 10^9$
* $\sum A \le 110$

，爆搜可得 $A = \{4, 5, 7, 9, 11, 13, 17, 19, 23\}$。于是得到了 $a_i$。

于是考虑 $f$ 的构造：发现 $\forall a \in A$，都可以简单地找到 $n \bmod a$，CRT 即可。

---

## 作者：yemuzhe (赞：0)

### 简化题意

- 本题是一道交互题。
- 首先你输出一个数 $M$，并满足 $1 \le M \le 110$。
- 然后你输出 $M$ 个数 $A _ i$，满足 $1 \le A _ i \le M$。
- 这时交互库会给出 $M$ 个数 $B _ i$，满足 $B _ i = f ^ N (i)$（$N$ 是交互库已经准备好的一个数，你不知道 $N$ 是多少）。
- 其中 $f (i) = A _ i$，$f ^ N (i) = f(f(f(\cdots f(f(i)))))$，其中有 $N$ 个 $f$。换句话说，$f ^ N (i) = A _ {A _ {A _ {A _ {\cdots _ {A _ i}}}}}$其中有 $N$ 个 $A$。
- 最后你要根据 $B _ i$ 猜出 $N$ 的值并输出。
- 在每一次输出完后，要另起一行并用 `std::cout << flush` 或 `fflush (stdout)`，否则可能会 `TLE`。
- $1 \le N \le 10 ^ 9$。

### 解题思路

#### Part 1：余数与环

首先，我们可以构造出由很多个「环」组成的 $A$ 数组。具体地，如 $M = 3$ 时，$A = [2, 3, 1]$，则称 $A$ 数组是「环状」的。

「环状」数组的作用是能知道 $(N - 1) \bmod M$ 的值。比如刚才举的例子，如果 $B = [3, 1, 2]$，则 $(N - 1) \bmod M = 1$。

因为我们发现，$N = 1$ 时 $B _ i = A _ i$。

当 $N = 2$ 时，$B _ 1 = f ^ 2 (1) = A _ {A _ 1} = A _ 2 = 3, B _ 2 = f ^ 2 (2) = A _ {A _ 2} = A _ 3 = 1, B _ 3 = f ^ 2 (3) = A _ {A _ 3} = A _ 1 = 2$。

$N$ 每增加 $1$，位置处于 $[2, M]$ 的数字全都往前移了一位，位置处于 $1$ 的数字则移到了 $M$ 的位置上，就像一个环。$N = k$ 和 $N = k + M$ 时的 $B$ 数组总是一样的。

于是，用刚才举的例子，当 $N = 3k + 2$ 时，$B = [3, 1, 2]$。

如何确定 $(N - 1) \bmod M$ 的值？可按规律发现，$(N - 1) \bmod M = B _ M - 1$。

#### Part 2：多环问题

虽然我们可以确定 $(N - 1) \bmod M$ 的值，但是还是不知道 $N$ 的值是多少。这可通过构造多个长度不等且互质的环来解决。

注意到 $1 \le N \le 10 ^ 9$。根据中国剩余定理，我们可知当这些不等且互质的环长的乘积 $\ge 10 ^ 9$ 时，就可求出 $N$ 的值。

具体来说，设有 $k$ 个环，第 $i$ 个环的长度为 $M _ i$，那么满足 $M = M _ 1 + M _ 2 + \cdots + M _ k \le 110$ 且 $M _ 1 M _ 2 \cdots M _ k \ge 10 ^ 9$。

又由于 $M _ i$ 之间两两互质，最终确定下来 $k = 9, M _ 1 = 4, M _ 2 = 9, M _ 3 = 5, M _ 4 = 7, M _ 5 = 11, M _ 6 = 13, M _ 7 = 17, M _ 8 = 19, M _ 9 = 23$。

这样，$\sum M _ i = 108, \prod M _ i = 1338557220$，符合要求。

**环的具体构成：**

```
2 3 4 1 6 7 8 9 10 11 12 13 5 15 16 17 18 14 20 21 22 23 24 25 19 27 28 29 30 31 32 33 34 35 36 26 38 39 40 41 42 43 44 45 46 47 48 49 37 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 50 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 67 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 86
```

这样，设 $s _ i$ 为 $\sum \limits _ {j = 1} ^ i M _ j$，$r _ i$ 为 $(N - 1) \bmod M _ i$ 的值，则类似一个环的情况，$r _ i = B _ {S _ i} - S _ {i - 1} - 1$。

#### Part 3：中国剩余定理

不会中国剩余定理可以先去做一下中国剩余定理的[模板题](/problem/P1495)。

根据 Part 2，我们得到了一下同余方程组：
$$
\begin {cases}
N - 1 \equiv r _ 1 \pmod {M _ 1} \\
N - 1 \equiv r _ 2 \pmod {M _ 2} \\
\kern {3.141592653589793238462643383em} \vdots \\
N - 1 \equiv r _ k \pmod {M _ k}
\end {cases}
$$
其中 $r _ i$ 之间两两互质。于是我们可通过中国剩余定理求出 $N - 1$，最后输出答案 $N$。

具体地，设 $P$ 为 $\prod M _ i$，由于 $M _ i$ 不大，我们可暴力求出 ${P \over M _ i}$ 的乘法逆元 $\big ({P \over M _ i} \big) ^ {-1}$，$N - 1 = \bigg (\sum \limits _ {i = 1} ^ k {P \over M _ i} \big({P \over M _ i}\big) ^ {-1} r _ i \bigg ) \bmod P$。

### AC Code

```cpp
#include <cstdio>
#define n 9
#define N (int)11.4514
using namespace std;

const int p[N] = {0, 4, 9, 5, 7, 11, 13, 17, 19, 23}; // 选出的几个质数

int tot, a[N], s[N];
long long prod = 1, now, ans;

int main ()
{
    puts ("108"), fflush (stdout);
    for (int i = 1; i <= n; i ++)
    {
        s[i] = s[i - 1] + p[i], prod *= p[i]; // 处理前缀和与乘积
    }
    for (int i = 1; i <= n; i ++)
    {
        while (++ tot < s[i])
        {
            printf ("%d ", tot + 1);
        }
        printf ("%d ", s[i - 1] + 1);
    }
    puts (""), fflush (stdout), tot = 0;
    for (int i = 1; i <= n; i ++)
    {
        while (++ tot < s[i])
        {
            scanf ("%d", &a[i]);
        }
        scanf ("%d", &a[i]), a[i] -= s[i - 1] + 1;
    }
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j < p[i]; j ++)
        {
            if (prod / p[i] * j % p[i] == 1) // 中国剩余定理：j 是模 p[i] 意义下 prod / p[i] 的乘法逆元
            {
                now = prod / p[i] * j;
                break;
            }
        }
        ans = (ans + now * a[i]) % prod; // 中国剩余定理
    }
    printf ("%lld", ans + 1);
    return 0;
}
```

---

## 作者：Galex (赞：0)

如果将 $i\to a_i$ 连边，就会形成 $k$ 个长度为 $c_1,c_2,\cdots,c_k$ 的环。所以交互库相当于告诉我们了 $n \bmod c_1,n\bmod c_2,\cdots,n\bmod c_k$ 的值。这引导我们构造合适的 $k$ 和两两互质的 $c_1,c_2,\cdots,c_k$，然后使用中国剩余定理求解。

先看看题目中的限制条件：

- $1\le N \le 10^9$

意味着 $\prod c_i$ 需要 $> 10^9$，否则就不能确定唯一解（因为若存在一个 $x$ 满足条件，则 $x+\prod c_i$ 也必定满足条件）。

- $1 \le M \le 110$

意味着 $\sum c_i \le 110$。

然后就可以根据这两个条件去构造 $c_1,c_2,c_3,\cdots,c_k$ 了。不是很难，我最后得到的结果是 $\{4, 9, 5, 7, 11, 13, 17, 19, 23\}$。

最后根据 $c_1,c_2,\cdots,c_k$ 构造 $a_1,a_2,\cdots,a_M$，其中 $M=\sum c_i$，在我的构造中为 $108$。

若只有一个长为 $x$ 的环，则可以构造 $a_1=2,a_2=3,\cdots,a_{x-1}=x,a_x=1$，可得 $n\equiv b_x(\bmod x)$。那么，对于 $k$ 个环，我们一个一个构造即可。对于第 $i$ 个环，构造 $a_{1+v}=2+v,a_{2+v}=3+v,\cdots,a_{c_i-1+v}=c_i+v,a_{c_i+v}=1+v$，可得 $n\equiv b_{v+c_i}-v(\bmod c_i)$，其中 $v=\sum_{j=1}^{i-1} c_j$。

最后跑一遍中国剩余定理即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int M = 108, a[115], b[115];
int cnt = 9, p[10] = {0, 4, 9, 5, 7, 11, 13, 17, 19, 23}, r[10];
int m[10], t[10];

int phi(int x) {
	int cnt = 0;
	for (int i = 1; i <= x; i++)
		cnt += (__gcd(i, x) == 1);
	return cnt;
}

int fpow(int a, int b, int p) {
	int ans = 1;
	while (b) {
		if (b & 1)
			ans = (ans * a) % p;
		a = (a * a) % p, b >>= 1;
	}
	return ans;
}

int CRT() {
	int M = 1;
	for (int i = 1; i <= cnt; i++)
		M *= p[i];
	for (int i = 1; i <= cnt; i++)
		m[i] = M / p[i], t[i] = fpow(m[i] % p[i], phi(p[i]) - 1, p[i]);
	int ans = 0;
	for (int i = 1; i <= cnt; i++)
		ans += m[i] * t[i] * r[i];
	return ans % M;
}

signed main() {
	cout << M << endl;
	for (int i = 1, cur = 0; i <= cnt; cur += p[i++]) {
		for (int j = 1; j < p[i]; j++)
			cout << (a[cur + j] = cur + j + 1) << ' ';
		cout << (a[cur + p[i]] = cur + 1) << ' ';
	}
	cout << endl;
	for (int i = 1; i <= M; i++)
		b[i] = read();
	for (int i = 1, cur = 0; i <= cnt; cur += p[i++])
		r[i] = b[cur + p[i]] - cur;
	cout << CRT() << endl;
	return 0;
}
```

---

