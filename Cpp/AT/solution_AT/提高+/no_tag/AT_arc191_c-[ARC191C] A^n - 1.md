# [ARC191C] A^n - 1

## 题目描述

给定范围在 $1$ 至 $10^9$ 之间的正整数 $N$。

请找出一个满足以下两个条件的正整数对 $(A, M)$。可以证明在约束条件下这样的正整数对必然存在：

- $A$ 和 $M$ 均为 $1$ 至 $10^{18}$ 之间的正整数。
- 存在某个正整数 $n$ 使得 $A^n - 1$ 是 $M$ 的倍数，且满足此条件的最小 $n$ 恰好为 $N$。

给定 $T$ 个测试用例，请分别计算每个用例的答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 10^4$
- $1 \leq N \leq 10^9$
- 输入均为整数

### 样例解释 1

以第一个测试用例 $\text{case}_1$ 为例：
若选择 $(A, M) = (2, 7)$，则：
- 当 $n = 1$ 时：$2^1 - 1 = 1$，不是 $7$ 的倍数。
- 当 $n = 2$ 时：$2^2 - 1 = 3$，不是 $7$ 的倍数。
- 当 $n = 3$ 时：$2^3 - 1 = 7$，是 $7$ 的倍数。

此时满足条件的最小 $n$ 为 $3$，因此输出 $(2, 7)$ 是正确的。其他符合条件的解例如 $(100, 777)$ 也可接受。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
16
1
55```

### 输出

```
2 7
11 68
20250126 1
33 662```

# 题解

## 作者：luanyanjia (赞：8)

也很幽默的题。

**注意到**，$A = n+1,M = n^2$ 即为所求。

证明：

$$A^x = \sum\limits_{i = 0}^{x}{\binom{x}{i}n^i} = nx+1 \pmod {n^2}$$

当 $x < n$ 时上式显然不为 $1$，$x = n$ 时就是 $1$。

不要认为某道题是完全不可做的。有时候打表也是不错的选择。

---

## 作者：Hell0_W0rld (赞：3)

## ARC191C
题意：求两个数 $A,M\leq 10^{18}$，满足对于给定的 $N$ 有 $\delta_M(A)=N$。

### Solution 1
考虑[原根](https://www.luogu.com.cn/problem/P6091)的性质：对于模 $M$ 的原根 $g$ 有 $\delta_M(g)=\phi(M)$。

即 $g^{\phi(M)}\equiv 1\pmod M$。找出一个 $\phi(M)$ 是 $N$ 的倍数的数且 $M$ 可以表示为 $p^k$ 或 $2p^k$ 的形式，其中 $p$ 为奇素数，$k\in\mathbb{Z}^+$。

不妨设 $M$ 为奇素数，那么 $\phi(M)=M-1$，即求出一个素数使得 $M=kN+1$，其中 $k\in \mathbb{N}$。可以证明 $k$ 不大。

那直接暴力枚举这个 $k$ 即可。检验要用 [Millar-Rabin](https://www.luogu.com.cn/problem/SP288)。

求出来对应的 $M$ 之后，我们用类似判原根的方法，把 $N$ 分解，检查是否对于所有的 $t\mid N$，有 $M\nmid x^{\frac{N}{t}}-1$。具体可以前往[这里](https://www.luogu.com.cn/problem/solution/P6091) 学习。

直接随机化一个 $x$，并检验它是否符合要求即可。根据原根的个数（$\phi(M-1)$），这个数值大约在上面找到的 $k$ 次左右。

时间复杂度 $O(\text{能过})$。[code](https://atcoder.jp/contests/arc191/submissions/62145800)。
### Solution 2
构造 $A=N+1,M=N^2$。

鬼知道 atc official 怎么想出来这种构造的。验题都没想到。

验证：$\displaystyle (N+1)^n-1\equiv \sum_{k=1}^n \binom nkN^k\equiv nN\equiv 0 \pmod {N^2}\iff n\equiv 0\pmod N$。（照抄官解）

时间复杂度 $O(T)$。

---

## 作者：linjunye (赞：2)

### 思路

一道很好的猜结论题。

经过不断的猜结论，我们发现在小范围内，总有一个数对满足条件，那就是 $(N+1,N^2)$。下面我们来证明，这一对数，不仅能让 $N$ 满足条件，还能使 $N$ 本身为最小解。

我们设能满足条件的这个数为 $x$，则可以列方程：$A^x-1\equiv 0\pmod M$。

带入刚才猜测的数对得：$(N+1)^x-1\equiv 0\pmod{N^2}$。

根据二项式定理，得 $(N+1)^x-1\equiv \sum_{i=0}^{x}C_x^iN^i-1\equiv\sum_{i=1}^{x}C_x^iN^i+C_x^0N^0-1\equiv\sum_{i=1}^{x}C_x^iN^i+1-1\equiv\sum_{i=1}^{x}C_x^iN^i\pmod{N^2}$。

然后发现当 $i\ge 2$ 时，$N^i\bmod N^2=0$，所以只有 $i=1$ 的结果才有效。

则：$\sum_{i=1}^{x}C_x^iN^i\pmod{N^2}\equiv C_x^1N^1\equiv xN\equiv0\pmod{N^2}$。

所以 $N^2|xN$，因为 $N>0$，所以 $N|x$（左右同时除以 $N$）。

那么可以推出 $x=kN$，其中 $k\ge 1$。此时当 $k=1$ 时为最小解，也就是说当 $x=N$ 时为最小解。所以，不仅 $N$ 满足条件，且 $N$ 本身还是最小解，证毕。

那么，代码是非常好写的。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		cout<<n+1<<" "<<n*n<<"\n";
	}
	return 0;
}
```

---

## 作者：Inv_day_in_R (赞：1)

对于这种一眼没思路的数论题，可以试试猜结论和小范围暴力找规律。

首先用数据范围猜结论，发现 $a$ 和 $m$ 的最大值 $10^{18}$ 居然刚好是 $n$ 最大值 $10^9$ 的平方啊！那么 $a$ 和 $m$ 的构造大概率在 $n^2$ 内有解，那么只枚举这些打个表康康：[戳我获得生成器](https://www.luogu.com.cn/paste/7uwzf34a)（话说你们洛谷真是的，连一到十五的数据放上去都会卡死，只好放生成器了）

当你们打开 `tmp.out` 的时候，注意力惊人的你突然发现好像每个 $m=n^2$ 都是有解的，于是你只枚举所有的 $m=n^2$ 于是得到了：[戳这里](https://www.luogu.com.cn/paste/rkuxgm9v)，你又猛地发现似乎 $a=n+1$ 都是成立的，那么就证明一下吧。

$$
a^n=(n+1)^n=\sum_{i=0}^nC_n^in^i\equiv C_n^1n+C_n^0=n^2+1\equiv1\pmod {n^2}
$$

那么如何证明是最小的呢？假设存在 $1\leq k<n$，使得 $a^k\equiv1\pmod {n^2}$，那么有：
$$
0\equiv a^k-1\equiv C_k^1n+C_k^0-1=kn\pmod{n^2}
$$
但是 $n\leq kn<n^2$，不可能为 $n^2$ 的倍数，矛盾。

综上所述，$a=n+1$ 且 $m=n^2$ 即可。

不会这都要代码吧，那我建议阁下去做[这道题](https://www.luogu.com.cn/problem/P1001)。

---

## 作者：无名之雾 (赞：1)

很好的题目。成功的浪费了我人生中宝贵的 $20$ 分钟。

## solution

对于这种看完一点思路都没有的题目，考虑先写一个暴力。

对于一个任意的 $n$，构造一个 $m$ 使得 $n \mid \varphi(m)$。

然后考虑原根的性质。

显然一个在模 $m$ 意义下的原根 $a$，有 $a^{\varphi(m)} \equiv 1 \pmod m$


所以我们直接从小到大枚举 $a$ 即可。

作完这一切你会发现你的代码连样例都不能全部跑过去。但是如果你的注意力惊人你就会发现。

$$ 3^2 \equiv 1 \pmod 4 \\ 4^3 \equiv 1 \pmod 9 \\ \ \ 5^4  \equiv 1 \pmod {16} \\ \ \ 6^5  \equiv 1 \pmod {25}$$


于是你大胆的令 $a=n+1,m=n^2$。 

通过。

### 证明

有结论后可以二项式定理显然证明。

$$(n+1)^n=\sum_{k=0}^n\binom{n}{k}n^k=1+\binom{n}{1}n+n^2\sum_{k=2}^n\binom{n}{k}n^{k-2}\equiv 1\pmod{n^2}$$

---

## 作者：Partial (赞：1)

介绍一个相对好想的方法，个人认为比较本质。  
我们需要一个知识点：[升幂引理](https://oi-wiki.org/math/number-theory/lift-the-exponent/)。  
有了升幂引理，我们自然会想到让 $N$ 和 $n$ 的质因数发生关系，也会想到 $n \mid a - 1$ ，于是根据升幂引理，我们考虑 $n$ 的所有质因数，奇偶分开讨论。  
奇质数时有 $V_{p}(a^n - 1) = V_p(a - 1) + V_p(n)$ 此时取 $a = n + 1$ 时，我们发现指数为 $ n$ 正好第一次取到 $V_{p}(a^n - 1) = 2V_p(n)$。  
  如果有偶质数时，如果 $V_2(n) \geq 2$ 则与奇质数的情况相同。如果 $V_2(n) = 1$ 时任何的奇指数都是小于 $2V_2(n)$ 的。  
综上所述，可以发现取 $a = n + 1, N = n ^ 2$ 是满足条件的。  
代码如下：  

```cpp
#include <bits/stdc++.h>
#define db long double
#define int long long
#define pb push_back
#define pii pair<int, int>
#define X first
#define Y second
#define pcc pair<char, char>
#define vi vector<int>
#define vii vector<vector<int>> 
#define Rep(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define Drp(i, a, b) for (int i = (int)(a); i >= (int)(b); --i)
#define sz(x) (x).size()
#define All(x) (x).begin(), (x).end()
using namespace std;
void solve()
{
    int n;
    cin >> n;
    int a = n + 1, b = n + 2;
    cout << a << " " << n * n << endl;
}
signed main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--) solve();    
}
```

---

## 作者：SDSXC (赞：1)

介绍一种思路。

首先一个简单的观察，因为 $A^N=1(mod M)$，所以$(A,M)=1$。

所以由欧拉定理 $A^{\varphi(M)}=1(mod M)$ 。

又 $N$ 是 $A$ 模 $M$ 的阶，所以有 $N|\varphi(M)$。

接下来考虑如何构造一个这样的 $M$。

对 $N,M$ 分解质因数 $N=\prod p_i^{\alpha _i}$，$M=\prod p_i^{\beta _i}$

带入欧拉函数的公式得到 $\varphi(M)=\prod (p_i-1)p_i^{\beta _i-1}$

所以只要让 $\alpha_i+1\leq\beta_i$，就能满足 $N|\varphi(M)$。

由此不难想到 $\alpha_i+1\leq2\alpha_i\leq\beta_i$，取 $M=N^2$

最后考虑如何构造 $A$

因为 $(A,M)=1$，即 $(A,N^2)=1$，想到尝试形如 $p^c,kN+1,kN+p^c\dots$ 的数，发现取$A=N+1$时成功

---

## 作者：Coffins (赞：1)

说一个没那么脑电波的做法（？

这个题实际上就是让你构造一对 $(a,m)$ 使得 $a$ 在模 $m$ 意义下阶恰为 $n$。

对于一般的 $m$ 考虑其阶貌似有些困难，但是如果 $m$ 是素数的话看起来会简单一些。

我们不妨考虑 $m$ 是素数，并且其原根为 $g$，于是能找到 $a$ 当且仅当 $n|m-1$，这时取 $a=g^{\frac{m-1}{n}} \bmod m$ 就好了。

那么问题就转化成找到一个 $t$ 使得 $nt+1$ 是素数

对 $n\le 10^4$ 打个表发现对于每个 $n$ 最小合法的 $t$ 最大是 84，$10^5$ 是 114，$10^6$ 是 182。于是猜测最小合法 $t$ 是 $O(\log n)$ 的量级。

于是直接从小到大枚举 $t$，拿 Miller-Rabin 判素数，知道找到一个 $t$ 之后再找到 $nt+1$ 的原根 $g$，最后输出 $(g^t\bmod (nt+1),nt+1)$ 就可以了。

然后赛时就稀里糊涂的过了（虽然调了 30 min 差点爆了）。

大常数选手要注意一下常数，然后就没啥了。

https://atcoder.jp/contests/arc191/submissions/62136501

看官解发现一直随 $t$ 直到合法也是可行的。

一个感性一点的证明就是可以认为 $nt+1$ 是一系列比较均匀随机的数，于是其中素数的密度也应该大致在 $O(\frac{1}{\log n})$ 的级别，于是期望随机 $O(\log n)$ 次就能随到，最小合法解也差不多是 $O(\log n)$ 级别的。

注：最小合法解以及期望次数有可能不是 $O(\log n)$ 的，而是一些其他复杂度，笔者只是做一步猜测，不过肯定是 $O(能过)$。

---

## 作者：Milky_Cat (赞：0)

这是题？

vp 的时候最后 1min 大致想到思路，但是我输出了 $N+1$ 和 $N$，遗憾离场。

这题一个常见的错误思路是，考虑令 $M$ 为质数，这样 $A^N \equiv 1 \pmod M$，看起来好像很可做，但是接下去会发现，$A^{N-1}$ 是 $A$ 在模 $M$ 意义下的乘法逆元，就意味着 $A^{N-1}\equiv A^{M-2} \pmod M$，这就意味着 $M$ 一定是 $N+1$ 的约数，显然不能使满足条件的最小 $n$ 为 $N$。

再经过一些小尝试可以确定这题与数论无关了。那就尝试找性质。

一个性质是，$(x+1)^x \equiv 1 \pmod x$，显然可以用二项式定理，但是这样不能保证最小。

观察发现 $x=N$ 时有一项是 $\binom{N}{1}N^{1}1^{N-1}=N^2$，而前面的每一项都是 $N^2$ 的倍数。由于这一项的存在，任何一个小于 $N$ 的数都不能满足这一项被 $N^2$ 整除。所以输出 $N+1$ 和 $N^2$ 就好了。

### 代码

这还要代码？

---

