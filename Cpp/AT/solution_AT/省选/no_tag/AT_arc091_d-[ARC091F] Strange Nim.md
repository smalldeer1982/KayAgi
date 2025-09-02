# [ARC091F] Strange Nim

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc091/tasks/arc091_d

高橋君と青木君は、石取りゲームをしています。最初、山が $ N $ 個あり、$ i $ 個目の山には $ A_i $ 個の石があり、整数 $ K_i $ が定まっています。

高橋君と青木君は、高橋君から始めて、交互に以下の操作を繰り返します。

- 山を $ 1 $ つ選ぶ。$ i $ 個目の山を選び、その山に $ X $ 個の石が残っている場合、$ 1 $ 個以上 $ floor(X/K_i) $ 個以下の任意の個数の石を $ i $ 個目の山から取り除く。

先に操作ができなくなったプレイヤーが負けです。両者最善を尽くしたとき、どちらのプレイヤーが勝つか判定してください。 ただし、$ floor(x) $ で $ x $ 以下の最大の整数を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200 $
- $ 1\ \leq\ A_i,K_i\ \leq\ 10^9 $
- 入力はすべて整数である

### Sample Explanation 1

最初、$ 1 $ 個目の山からは $ floor(5/2)=2 $ 個まで、$ 2 $ 個目の山からは $ floor(3/3)=1 $ 個までの石を一度に取り除くことができます。 - 高橋君が最初に $ 1 $ 個目の山から $ 2 $ 個の石を取ると、$ 1 $ 個目の山からは $ floor(3/2)=1 $ 個まで、$ 2 $ 個目の山からは $ floor(3/3)=1 $ 個までの石を一度に取り除くことができるようになります。 - 次に、青木君が $ 2 $ 個目の山から $ 1 $ 個の石を取ると、$ 1 $ 個目の山からは $ floor(3/2)=1 $ 個までの石を取り除くことができ、$ 2 $ 個目の山からは ($ floor(2/3)=0 $ より) 石を取り除くことができなくなります。 - 次に、高橋君が $ 1 $ 個目の山から $ 1 $ 個の石を取ると、$ 1 $ 個目の山からは $ floor(2/2)=1 $ 個までの石を一度に取り除くことができるようになります。$ 2 $ 個目の山からは石を取り除くことはできません。 - 次に、青木君が $ 1 $ 個目の山から $ 1 $ 個の石を取ると、$ 1 $ 個目の山からは $ floor(1/2)=0 $ 個までの石を一度に取り除くことができるようになります。$ 2 $ 個目の山からは石を取り除くことはできません。 これ以上の操作はできないため、青木君の勝ちです。高橋君がそれ以外の行動をした場合も、青木君はうまく行動を選ぶことで勝つことができます。

## 样例 #1

### 输入

```
2
5 2
3 3```

### 输出

```
Aoki```

## 样例 #2

### 输入

```
3
3 2
4 3
5 1```

### 输出

```
Takahashi```

## 样例 #3

### 输入

```
3
28 3
16 4
19 2```

### 输出

```
Aoki```

## 样例 #4

### 输入

```
4
3141 59
26535 897
93 23
8462 64```

### 输出

```
Takahashi```

# 题解

## 作者：xyf007 (赞：11)

本题两篇题解一篇没有复杂度分析，另一篇复杂度错误，这里提供正确的时间复杂度分析。

考虑一堆石子的情况，设有 $n$ 个石子，常数为 $k$。可以通过归纳证明
$$ \operatorname{SG}(n,k)\begin{cases}0&n<k\\\frac{n}{k}&k\mid n\\\operatorname{SG}(n-\left\lfloor\frac{n}{k}\right\rfloor-1,k)&k\nmid n\end{cases} $$
如果暴力计算，每次 $n\gets n-\left\lfloor\dfrac{n}{k}\right\rfloor-1$，接近于 $n\gets n\times\dfrac{k-1}{k}$。而 $\lim\limits_{n\to\infty}\left(1+\dfrac{1}{n}\right)^n=e$，也就是说 $\left(\dfrac{k-1}{k}\right)^{k-1}\approx\dfrac{1}{e}$。因此每 $(k-1)$ 次操作，$n\gets n\times\dfrac{1}{e}$，单次时间复杂度 $O(k\ln n)$。  
整个过程中有很多次减去 $\left\lfloor\dfrac{n}{k}\right\rfloor+1$ 的操作，考虑把相等的操作合并。令 $d=\left\lfloor\dfrac{n}{k}\right\rfloor$，当 $n\ge kd$ 时每次都减去 $d+1$，因此会连续进行 $\left\lceil\dfrac{n-kd}{d+1}\right\rceil$ 次。

注意到每次操作之后 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 的值都会减小，因此单次时间复杂度是 $O\left(\min\left(k\ln n,\dfrac{n}{k}\right)\right)=O(\sqrt{n\ln n})$。

根据 SG 定理，只需要把每一堆的 SG 值算出来异或即可，总时间复杂度 $O(n\sqrt{a\ln a})$。
```cpp
#include <iostream>
template <typename T1, typename T2>
void checkmax(T1 &x, T2 y) {
  if (x < y) x = y;
}
template <typename T1, typename T2>
void checkmin(T1 &x, T2 y) {
  if (x > y) x = y;
}
int n;
int Sg(int n, int k) {
  while (n > k && n % k) {
    int d = n / k, rnd = (n - d * k + d) / (d + 1);
    n -= rnd * (d + 1);
  }
  return n % k == 0 ? n / k : 0;
}
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  std::cin >> n;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int x, k;
    std::cin >> x >> k;
    ans ^= Sg(x, k);
  }
  std::cout << (ans ? "Takahashi" : "Aoki");
  return 0;
}
```

---

## 作者：qzhwlzy (赞：5)

题目大意：有 $n$ 堆石子和长为 $n$ 的数列 $k$，第 $i$ 堆有 $a_i$ 个石子，两人轮流从这些石子中取走若干，要求每次只能从一堆中拿（假设拿了第 $i$ 堆），拿的数量至少为 $1$ 颗，最多不超过 $\left\lfloor\frac{a_i}{k_i}\right\rfloor$ 颗（$a_i$ 随石子数变化而动态变化），最先没有石子可取的一方输。问先手是否存在必胜策略。（时限 $2s$）

我们发现 $n$ 堆石子间是独立的，所以我们把整个游戏分成 $n$ 个子游戏来看，原游戏的 SG 就是所有子游戏的 SG 的异或和。问题就转化成了求一个子游戏的 SG 值。

同样地，我们 ~~打表~~ 算出不同石子数的 SG 值（以 $k=8$ 为例）

![](https://cdn.luogu.com.cn/upload/image_hosting/xo2bdu5a.png)

我们发现以下规律：
$$
SG(i) = \begin{cases}\dfrac{i}{k}&i\bmod k = 0\\SG(i-\left\lfloor\frac{i}{k}\right\rfloor - 1)&i\bmod k\neq 0\end{cases}
$$

其实不难理解，$SG(i) = \operatorname{mex}\{SG(i-x)\,|\,1\le x\le \left\lfloor\frac{i}{k}\right\rfloor\}$，当 $\left\lfloor\frac{i}{k}\right\rfloor$ 不变时，SG 应该是一个循环节长度为 $\left\lfloor\frac{i}{k}\right\rfloor+1$ 的长度为 $k$ 的循环，且循环节恰好是 $0\sim \frac{i}{k}$ 的一个排列。当 $i$ 到 $k$ 的倍数时（记为 $i'$），$\left\lfloor\frac{i'}{k}\right\rfloor = \left\lfloor\frac{i}{k}\right\rfloor + 1$，取 $\operatorname{mex}$ 的范围恰好覆盖了原来的一个循环节，故 SG 值应该为 $\left\lfloor\frac{i}{k}\right\rfloor + 1 = \left\lfloor\frac{i'}{k}\right\rfloor$。

根据这个规律，对于给定的一组 $a$ 和 $k$，我们一直将 $a\leftarrow a-\left\lfloor\frac{a}{k}\right\rfloor-1$ 直到 $a$ 为 $k$ 的倍数。下面分析复杂度：$a\leftarrow a-\left\lfloor\frac{a}{k}\right\rfloor-1$ 可以约等于是 $a\leftarrow a\times\frac{k-1}{k}$，而 $(\frac{k-1}{k})^{k-1} = (\dfrac{1}{1+\frac{1}{k-1}})^{k-1} = \dfrac{1}{(1+\frac{1}{k-1})^{k-1}} \approx \frac{1}{e}$（众所周知 $\lim\limits_{x\to\infty}{(1+\frac{1}{x})^x} = e$），故每 $(k-1)$ 次操作 $a\leftarrow a\times\frac{1}{e}$。总时间复杂度约为 $\mathcal{O}(nk\ln a)$。

显然会 TLE，考虑优化。类似于数论分块，$\left\lfloor\frac{a}{k}\right\rfloor$ 在一定范围内是一个定值，所以我们把重复的 $\left\lfloor\frac{a}{k}\right\rfloor$ 合并，大约是 $\left\lceil\dfrac{a\bmod k}{\left\lfloor\frac{a}{k}\right\rfloor+1}\right\rceil$ 次。因为 $\left\lfloor\frac{a}{k}\right\rfloor$ 在减少，所以最终的时间复杂度约在 $\mathcal{O}\big(n \min(\dfrac{a}{k},k\ln a)\big) = \mathcal{O}(n\sqrt{a\ln a})$ 上下。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define maxn 100005
#define maxk 100005
using namespace std;
int n,a,k,ans=0;
int main(){
	scanf("%d",&n);
	for(int tt=1;tt<=n;tt++){
		scanf("%d%d",&a,&k);
		while(a>=k){
                        if(a%k==0){ans^=a/k;break;}
                        a-=(((a%k)/(a/k+1))+((a%k)%(a/k+1)!=0?1:0))*(a/k+1);
                }
	}
	if(ans==0) printf("Aoki"); else printf("Takahashi");
	return 0;
}
```

---

## 作者：zhimao (赞：3)

这应该是我第一道独立做出来的博弈论 ~~博弈论是真的毒瘤啊~~ ，写篇题解纪念下。

其实 @asuldb 已经讲得很详细了，但是还少个对 $sg$ 函数式子的证明，在这里补一下。
$$sg(n,k)=\begin{cases}0&n=0\\sg(n- \left \lfloor\dfrac{n} {k} \right \rfloor)-1,k)&n \bmod k\ne 0\\n \div k&n \bmod k=0 , n \ne 0\end{cases}$$
我们使用数学归纳法来证明：

记 $(x,y)$ 为石子数在 $x \times y-y+1$ 到 $x \times y$ 的石堆 ，在 $k$ 值为 $y$ 时的情况 。当 $x=1$ 式子显然成立 。 于是我们只要证 $(x,y)$ 成立时 ， $(x+1,y)$ 也成立 。$(x,y)$ 成立时 ，当石子数为 $x \times y-x$ 到 $x \times y$ 时 $sg$ 值为 0 到 $x$ 的排列 ，因此石子数为 $x \times y+1$ 时 , 集合中有 $x \times y-x+1$ 到 $x \times y$ 的 $sg$ 值 ，它离 0 到 $x$ 的排列只差石子数为 $x \times y-x$ 的 $sg$ 值 , 而这个值小于 $x$ ，所以石子数为 $x \times y+1$ 时的 $sg$ 值为 $x \times y-x$ 的 $sg$ 值 ，同理石子数为 $x \times y+z(0<z<x)$ 时的 $sg$ 值为 $x \times y-x+z-1$ 的 $sg$ 值 , 于是公式第二种情况得证 。当石子数为 $x \times y$ 时 ，一次能取的石头个数多了一 ，因此集合为 $\{0,1,2,......,x\}$ , 所以此时 $sg$ 值为 $x+1$ 。

于是公式得证。

---

## 作者：asuldb (赞：2)

[题目](https://www.luogu.com.cn/problem/AT3939)

显然对每一堆石子求一个SG之后异或起来就好了。

这个SG看起来只能$O(n^2)$的样子啊，考虑找规律;

一下是$k=3$时的一些SG函数的值

```
SG(1): 0 SG(2): 0 SG(3): 1
SG(4): 0 SG(5): 1 SG(6): 2
SG(7): 0 SG(8): 1 SG(9): 3
SG(10): 2 SG(11): 0 SG(12): 4
SG(13): 1 SG(14): 3 SG(15): 5
SG(16): 2 SG(17): 0 SG(18): 6
SG(19): 4 SG(20): 1 SG(21): 7
SG(22): 3 SG(23): 5 SG(24): 8
SG(25): 2 SG(26): 0 SG(27): 9
SG(28): 6 SG(29): 4 SG(30): 10
SG(31): 1 SG(32): 7 SG(33): 11
SG(34): 3 SG(35): 5 SG(36): 12
SG(37): 8 SG(38): 2 SG(39): 13
SG(40): 0 SG(41): 9 SG(42): 14
SG(43): 6 SG(44): 4 SG(45): 15
SG(46): 10 SG(47): 1 SG(48): 16
SG(49): 7 SG(50): 11 SG(51): 17
```

不难发现一些规律

$$
\operatorname{SG}(n) = \begin{cases} 0 &  0 \le n < k \\ \frac{n}{k} &   n \bmod k = 0 \\ \displaystyle \operatorname{SG} \!\left(n - \!\left\lfloor \frac{n}{k} \right\rfloor\! - 1 \right) &   n \bmod k !\neq 0 \end{cases}
$$

我们发现直接那这个式子来暴力算复杂度还是$O(n)$的，考虑在转移的过程中把$\left\lfloor \frac{n}{k} \right\rfloor$相等的转移一起做；

设$x=\lfloor \frac{n}{k} \rfloor$，则我们需要找到一个最大的$y$满足$n-y(x+1)\geq x\times k$，即$y=\lfloor  \frac{n-x\times k}{x+1}\rfloor $，这中间的转移$\lfloor \frac{n}{k} \rfloor$是不变的，于是我们可以直接令${\rm SG}(n)={\rm SG}(n-(x+1)y)$；

考虑复杂度，当$k\leq \sqrt{n}$时，$\left\lfloor \frac{n}{k} \right\rfloor>\sqrt{n}$，于是每次$n$都会至少减去$\sqrt{n}$，于是这边复杂度是$O(\sqrt{n})$的；当$k>\sqrt{n}$时，$\left\lfloor \frac{n}{k} \right\rfloor\leq \sqrt{n}$，按照上面的转移方式每进行一次转移$\left\lfloor \frac{n}{k} \right\rfloor$的值至少会减少$1$，于是复杂度也是$O(\sqrt{n})$的。

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
int T,n,m;
int bf(int n) {
	if(n<m) return 0;if(n%m==0) return n/m;
	return bf(n-n/m-1);
}
int sg(int n) {
	if(n<m) return 0;if(n%m==0) return n/m;
	int x=n/m;int u=x*m;
	int h=(n-u)/(x+1);
	if(n-h*(x+1)==u) return x;
	return sg(n-(h+1)*(x+1));
}
int main() {
	int ans=0;
	for(re int T=read();T;--T) {
		n=read(),m=read();
		if(m<=n/m) ans^=bf(n);
		else ans^=sg(n);
	}
	if(ans) puts("Takahashi");
	else puts("Aoki");
	return 0;
}
```

---

## 作者：xht (赞：1)

> [ARC091F Strange Nim](https://atcoder.jp/contests/arc091/tasks/arc091_d)

## 题意

- 有 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个石子和一个整数 $k_i$。
- 两个人轮流，每次选择一堆，**从中要取出至少一个石子**。
- 设选择了第 $i$ 堆，当前还剩下 $x$ 个石子，则可以从中取出 $[1,\lfloor \frac{x}{k_i} \rfloor]$ 个石子。
- 谁不能取了谁就输了，问最优策略下谁会获胜。
- $n \le 200$，$a_i,k_i \le 10^9$。

## 题解

显然考虑每一堆的 SG 函数，若所有 SG 值异或起来为 $0$ 则后手赢，否则先手赢。

考虑如何计算 SG 函数，可以发现在 $k$ 意义下的 SG 函数 $sg(n)$ 的值为：
$$
sg(n) =\begin{cases}\frac nk & k \mid n \\\\sg(n - \lfloor \frac nk \rfloor - 1) & k \nmid n\end{cases}
$$
考虑根号分治计算 $sg(n)$，设 $w = \max_{i=1}^n a_i$。

若 $\lfloor \frac nk \rfloor \ge \sqrt w$，则直接转化为求 $g(n - \lfloor \frac nk \rfloor - 1)$，每次 $n$ 至少减少 $\sqrt w$，至多执行 $\mathcal O(\sqrt w)$ 次。

否则，一次性将 $n$ 减若干个 $\lfloor \frac nk \rfloor + 1$，直到 $\lfloor \frac nk \rfloor$ 改变或者 $k \mid n$，每次 $\lfloor \frac nk \rfloor$ 减少 $1$，至多执行 $\mathcal O(\sqrt w)$ 次。

总时间复杂度 $\mathcal O(n \sqrt w)$。

实现时不用分治，直接写就可以了。

## 代码

```cpp
inline int SG(int n, int k) {
	int x = n / k, y = n % k;
	return y ? SG(n - (y + x) / (x + 1) * (x + 1), k) : x;
}

int main() {
	int n, w, k, ans = 0;
	rd(n);
	while (n--) rd(w, k), ans ^= SG(w, k);
	prints(ans ? "Takahashi" : "Aoki");
	return 0;
}
```

---

