# [AGC020D] Min Max Repetition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc020/tasks/agc020_d

$ A $ と $ B $ を正の整数として、$ f(A,\ B) $ を以下の条件を満たす文字列と定めます。

- $ f(A,\ B) $ の長さは $ A\ +\ B $ である。
- $ f(A,\ B) $ はちょうど $ A $ 個の `A` とちょうど $ B $ 個の `B` を含む。
- $ f(A,\ B) $ の部分文字列であって同じ文字からなるもの（例: `AAAAA`、`BBBB`）のうち最長のものの長さは、上記の二つの条件が満たされるという前提のもとで最小である。
- $ f(A,\ B) $ は、上記の三つの条件が満たされるという前提のもとで辞書順最小の文字列である。

例えば、$ f(2,\ 3) $ = `BABAB`、$ f(6,\ 4) $ = `AABAABAABB` となります。

次の $ Q $ 個のクエリに答えてください。「$ f(A_i,\ B_i) $ の $ C_i $ 文字目から $ D_i $ 文字目までの部分文字列（最初の文字を $ 1 $ 文字目とする）を求めよ。」

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 10^3 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 5\ \times\ 10^8 $
- $ 1\ \leq\ C_i\ \leq\ D_i\ \leq\ A_i\ +\ B_i $
- $ D_i\ -\ C_i\ +\ 1\ \leq\ 100 $
- 入力値はすべて整数である。

### 部分点

- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^3 $ を満たすデータセットに正答すると、$ 500 $ 点が与えられる。

## 样例 #1

### 输入

```
5
2 3 1 5
6 4 1 10
2 3 4 4
6 4 3 7
8 10 5 8```

### 输出

```
BABAB
AABAABAABB
A
BAABA
ABAB```

# 题解

## 作者：GreenDay (赞：24)

`WA`了1个晚上 最终还是看了`editorial`,我果然还是太菜了qwq

---

## 题意
[链接](https://www.luogu.com.cn/problem/AT3858)

## 做法

直观上看这道题需要大量分类讨论，似乎根本不可做。

事实上，这道题非常巧妙，**几乎没有分类讨论**，直接使用**二分**进行构造。

首先，我们有最小连续长度 $k=\max  \{ \left\lceil\dfrac{a}{b+1}\right\rceil , \left\lceil\dfrac{b}{a+1}\right\rceil \}$ ,我们可以贪心的去证明。

然后，我们非常大胆的猜测了这个串串的形式是：
$|A \cdots ABA \cdots AB \cdots  \cdots |B  \cdots  BAB  \cdots BA  \cdots  \cdots |$

是分成两部分的。

- 前一部分贪心的填`A`，但是不能打破`k`的限制

- 后一部分不得已就填`B`

我们二分这个边界`p`，使得`p`的右半部分满足：$b > ak$.**这样可以使得两边都满足条件，而且可以保证分界线的左边是`A`,右边是`B`.**

输出时候分两半判断。可以看代码。

```cpp
#include <iostream>
using namespace std;

int main() {
    int T , A , B , C , D , k;
    for(cin >> T ; T ; T--) {
        cin >> A >> B >> C >> D;
        k = (A + B) / (min(A , B) + 1);
        int a , b;
        auto getAB = [&] (int p) {
            a = A - p / (k + 1) * k - p % (k + 1) , 
            b = B - p / (k + 1);
        };
        int l = 0 , r = A + B , mid;
        while(l < r) {
            mid = (l + r) >> 1;
            getAB(mid);
            if(b <= (long long)a * k) l = mid + 1;
            else r = mid;
        }
        getAB(l);
        r = l + 1 + b - a * k;
        for(int i = C ; i <= D ; ++i) {
            if(i <= l) {
                if(i % (k + 1) != 0) cout << 'A';
                else cout << 'B';
            } else {
                if((i - r) % (k + 1) != 0) cout << 'B';
                else cout << 'A';
            }
        }
        cout << endl;
    }
}
```

---

## 作者：chen_zhe (赞：11)

# [AGC020D] Min Max Repetition

集训队作业题单里难得的一个水题。

我们三个要求一个一个看。

-   要求字典序最小，那么很显然就无脑拿 `A` 开头，而且越多越好。因为你如果是 `B` 开头，后面构造再优秀，字典序也比不过以 `A` 开头的字符串。

-   要求连续的相同字符个数最大值最小。我们可以先算出这个最大值 $k$

    则有：$k=\max\{\lceil \dfrac{A}{B+1}\rceil,\lceil \dfrac{B}{A+1}\rceil \}$。

    证明其实很简单。例如 $A>B$ 的情况，那么我们会发现，均匀填充 `B` 把原来的字符串分成了 $B+1$ 段，那么在每段就能填充不超过 $\lceil \dfrac{A}{B+1} \rceil$ 个 `A`。当 $A<B$ 的时候同理。

然后还有一条是长度的限制。这个问题不大。

那么其实也就提示了我们，我们如果要一开始填充一堆 `A` 的话，填充的 `A` 的数量不能超过上面提到的 $k$，然后接下来就拿 `B` 阻断，然后再填充 `A`。但是这是理想情况。因为 `A` 不一定够那么多地让你能够这样构造下去。

我们考虑，到达一个位置时，从填充 $k$ 个 `A`，用 `B` 阻断，变成填充 $k$ 个 `B`，用 `A` 阻断。很明显的一点就是，这个位置是可以二分出来的。二分的条件就是后半部分的位置 $pos>A \times k$，就能保证构造出的序列的合法性了。既然知道如何构造了，那么输出也就不难了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int A,B,C,D,k;

inline bool check(int mid)
{
	int a=A-mid/(k+1)*k-mid%(k+1);
	int b=B-mid/(k+1);
	return b<=1LL*a*k;
}

int main()
{
	int T=read();
	while (T--)
	{
		A=read(),B=read(),C=read(),D=read();
		k=max(ceil(1.0*A/(B+1)),ceil(1.0*B/(A+1)));
		int left=0,right=A+B+1;
		while (left<right)
		{
			int mid=(left+right)>>1;
			if (check(mid))
				left=mid+1;
			else
				right=mid;
		}
		int a=A-left/(k+1)*k-left%(k+1);
		int b=B-left/(k+1);
		right=left+b-a*k+1;
		for (int i=C;i<=min(D,left);i++)
		{
			if (i%(k+1))
				cout << 'A';
			else
				cout << 'B';
		}
		for (int i=max(C,left+1);i<=D;i++)
		{
			if ((i-right)%(k+1))
				cout << 'B';
			else
				cout << 'A';
		}
		puts("");
	}
	return 0;
}

```



---

## 作者：zhylj (赞：9)

记最小的最长连续段的长度为 $l$，再记 $m = \max\{A,B\}$，$n = \min\{A,B\}$。

先考虑求 $l$：

- 若 $m = n$，则必然有 $l_{\min} = 1$.
- 否则，考虑用出现次数较小的字符去隔断出现次数较大的字符（显然出现次数较大的字符去隔断出现次数较小的字符一定是够的），至多能分成 $n + 1$ 段，故必须有 $l\cdot (n+1)\ge m$，即 $l_{\min}= \left\lceil\dfrac{m}{n+1}\right\rceil$。

接下来，我们发现，字典序最小等价于所有的 ``B`` 尽量靠后，故可以想到最优的方案大概形如：

$$
\underbrace{{\tt AA\cdots A}}_{{\tt A}\times l}{\tt B}\underbrace{{\tt AA\cdots A}}_{{\tt A}\times l}{\tt B}\cdots{\tt AABB}\cdots \underbrace{{\tt BB\cdots B}}_{{\tt B}\times l}{\tt A}\underbrace{{\tt BB\cdots B}}_{{\tt B}\times l}{\tt A}
$$

前半段位置在 $i \bmod (l + 1) = 0$ 的下标 $i$ 为 ${\tt B}$，后半部分在 $(A + B - i + 1) \bmod (l + 1) = 0$ 的下标 $i$ 为 ${\tt A}$.

现在唯一的问题就变成了找前后两部分的分界点。

我们考虑先求一个 $x$ 表示 ``A`` 在左半部分被分成的段数。

- 若 $l = 1$，则 $x$ 要么为 $A$ 要么为 $0$，取决于 $A,B$ 的大小关系。
- 否则，考虑分成 $x$ 段后，需要用 $x - 1$ 个 ``B`` 来隔断，于是在右半部分还剩下 ${\rm res_{\tt B}} = B - x + 1$ 个 ``B``。
  
  左半部分至少需要 $l\cdot (x - 1) + 1$ 个 ``A``（前 $x - 1$ 段必须满，最后一段至少要有一个），所以右半部分至多能剩下 ${\rm res_{\tt A}} = A - l\cdot (x - 1) - 1$ 个 ``A`` 用于隔断 ``B``.

  剩下的 ``A`` 必须要在右半部分能把 ``B`` 隔断成若干个不超过 $l$ 的部分，所以 ``B`` 至多能有 $({\rm res_{\tt A}} + 1)\cdot l$ 个。

  于是，我们得到不等式：

  $$
  {\rm res_{\tt B}}\le ({\rm res_{\tt A}} + 1)\cdot l
  $$

  带入上面的式子，可以解得：

  $$
  x\le \dfrac{l\cdot (A + l) - B - 1}{l^2 - 1}
  $$

  由于字典序最小，所以我们需要 $x$ 最大，即：

  $$
  x_{\max} = \left\lfloor \dfrac{l\cdot (A + l) - B - 1}{l^2 - 1}\right\rfloor
  $$

接下来，我们考虑计算右半部分的大小：``B`` 共 ${\rm res}_{\tt B}$ 个，``A`` 共 $\left\lfloor \dfrac{{\rm res}_{\tt B}}{l+1}\right\rfloor$ 个，故我们很容易求得右半部分大小，分界点的位置也就很简单地求出来了。

更具体地，有分界点的位置为：

$$
A + B - (B - x + 1) - \left\lfloor \dfrac{B - x + 1}{l+1}\right\rfloor
$$

然后这题就被我们以 $\mathcal O(Q(D - C))$ 的时间做完了。

```cpp
void Solve(int A, int B, int C, int D) {
	ll l = std::max((std::max(A, B) - 1) / (std::min(A, B) + 1) + 1, 1), x;
	if(l != 1) x = std::max((l * (A + l) - B - 1) / (l * l - 1), 1LL);
	else x = (A >= B ? A : 0);
	for(int i = C; i <= D; ++i) {
		if(i <= A + B - (B - x + 1) - (B - x + 1) / l) putchar(i % (l + 1) ? 'A' : 'B');
		else putchar((A + B - i + 1) % (l + 1) ? 'B' : 'A');
	}
	putchar('\n');
}
```

---

## 作者：myee (赞：4)

### 前言

呜呜，分类讨论题。

不过分类并不复杂，只用特判两类边界情况。

### 思路

设 $k=\max\{\lceil\frac b{a+1}\rceil,\lceil\frac a{b+1}\rceil\}=\lfloor\frac{a+b}{\min\{a,b\}+1}\rfloor$，这样就立刻得到了合法的**连续的相同字符个数的最大值的最小值**。证明显然。

考虑一个分类讨论做法。

判掉两个边界情况：
* 若 $ak\le b$，则答案形如 $b-ak$ 个 $\tt b$ 之后加 $\tt abbb\dots b$ 结构。
* 若 $bk\le a$，则答案形如 $a-bk$ 个 $\tt a$ 之前加 $\tt aaa\dots ab$ 结构。

否则，容易发现，最优解必然形如：**前面若干个 $\tt aaa\dots ab$ 结构，中间一个 $\tt aaa\dots abbb\dots b$ 结构，最后若干 $\tt abbb\dots b$ 结构。**

证明可以考虑调整法，大致就是把 $\tt b$ 尽可能后置，$\tt a$ 尽可能前置，此处略去。

假设 $x$ 个 $\tt aaa\dots ab$ 结构，$y$ 个 $\tt abbb\dots b$ 结构，中间的结构 $\tt a$ $\tt b$ 两部分分别有 $u,v$ 个，我们令 $1\le u,v\le k$。

我们希望尽可能增大 $x$，然后在此基础上尽可能增大 $u$。

容易发现 $xk+y+u=a$，$yk+x+v=b$，于是

$$(x+y)(k+1)+(u+v)=a+b$$

则

$$a+b-2k\le(x+y)(k+1)\le a+b-2$$

从而

$$\lceil\frac{a+b-2k}{k+1}\rceil\le x+y\le\lfloor\frac{a+b-2}{k+1}\rfloor$$

容易发现这样的 $x+y$ 只有 $O(1)$ 个，我们暴力枚举之，设为 $w$。

进一步，由 $xk+y+u=a$，我们得到

$$x(k-1)=a-u-w$$

从而

$$u\equiv a-w\pmod{k-1}$$

由于 $u\in[1,k]$，于是合法的 $u$ 也只有 $O(1)$ 个，暴力枚举即可。

我们发现我们只用枚举 $O(1)$ 种情况，把其中的合法方案取最优解，直接把询问区间进行模拟输出即可。

然后就完了，总复杂度 $O(\sum m)$，其中 $m$ 表示输出长度。

### Code

核心代码很短。

注意判边界要开 `long long`。

```cpp
voi solve(){
    uint a,b,l,r;scanf("%u%u%u%u",&a,&b,&l,&r),l--;
    uint k=(a+b)/(1+std::min(a,b));
    if((ullt)a*k<=b){
        while(l<r)
            putchar("BA"[l++%(k+1)==(a+b)%(k+1)]);
        putchar('\n');
        return;
    }
    if((ullt)b*k<=a){
        while(l<r)
            putchar("AB"[l++%(k+1)==k]);
        putchar('\n');
        return;
    }
    std::pair<uint,uint>ans(0,0);
    for(uint w=(a+b-k)/(k+1);w<=(a+b-2)/(k+1)&&w<=a;w++)
        for(uint u=(a-w)%(k-1);u<=k&&u+w<=a&&u+w*(k+1)<a+b;u+=k-1)if(u)
        {
            uint x=(a-u-w)/(k-1);
            if(a+b-w*(k+1)-u<=k&&x<=w){
                _max(ans,std::pair<uint,uint>(x,u));
            }
        }
    uint x=ans.first,u=ans.second;
    uint y=a-x*k-u;
    uint v=b-y*k-x;
    // printf("%u %u %u %u\n",x,u,v,y);
    while(l<r){
        if(l<x*(k+1))
            putchar("AB"[l%(k+1)==k]);
        else if(l<x*(k+1)+u)
            putchar('A');
        else if(l<x*(k+1)+u+v)
            putchar('B');
        else
            putchar("BA"[l%(k+1)==(a+b)%(k+1)]);
        l++;
    }
    putchar('\n');
}
```



---

## 作者：vеctorwyx (赞：3)

看到第一眼：~~大分讨~~。

 其实正解是二分，挺妙的。。。

----------------

首先连续相同字符串长度最小长度 $len = \large\lceil \frac{\max(A,B)}{\min(A,B)+1}\rceil$, 这个比较显然，就是插空放。

然后就是让字典序最小了，我想了很多种构造方法，最后发现最优情况是 $\text{AAABAAABABABBBABBB}$ 一类的。

这是 $A = B$ 的情况，~~然后我就去考虑怎么把多的部分去掉了~~。

但是实际上所以情况都可以归纳为以上一种情况，只不过是分界线不同而已。

上面的情况实际上是 $\text{(3A)B(3A)BA | BA(3B)A(3B)}$ ，归纳一下就是 $\text{(lenA)B(lenA)B...AAA | BBB...A(lenB)A(lenB)}$。

这时候就可以二分一个中间的分界线，把分界线左边按上面的要求放，同时求出右边剩余的 $\text{A,B}$ 的个数（分别设为 $num_a, num_b$)，发现只有在 $num_a \times len < num_b$ 的时候右边才合法。

但是这时候我们不知道左边是否合法（可能出现 $\text{(lenA)B(lenA)B | ......}$ 的情况，当然这时候 $\text{len}$ 应该是 1 ），这时候就应该往左检查，所以二分做法是正确的。

code:

```
#include<bits/stdc++.h>
#define int long long
int read()
{
    int x=0,y=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*y;
}
void write(int x){
    if(x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}
using namespace std;
int n, m, a, b, t;
signed main(){
	t = read();
	while(t--){
//		ans = 0;
		n = read(), m = read(), a = read(), b = read();
		int k = max(ceil(n * 1.0 / (m + 1)), ceil(m * 1.0 / (n + 1)));
		int l = 0, r = n + m;
		int ans = r;
		while(l <= r){
			int mid = l + r >> 1;
			int ca1 = mid / (k + 1) * k + mid % (k + 1);
			int cb1 = mid / (k + 1);
			int cb2 = m - cb1;
			int ca2 = n - ca1;
			if(cb2 > ca2 * k)
				r = mid - 1, ans = mid;
			else
				l = mid + 1;
		}
		int flag = 0;
		if(ans < a)
			flag = 1;
		for(int i = a; i <= b; i++){
			if(!flag)
				putchar(i % (k + 1) == 0 ? 'B' : 'A');
			else
				putchar((n + m - i + 1) % (k + 1) == 0 ? 'A' : 'B');
			if(i == ans)
				flag = 1;
		}
		puts("");
	}
}

```

---

## 作者：关怀他人 (赞：2)

#### Solution
首先最小连续长度$k=\left\lceil\dfrac{max(a,b)}{min(a,b)+1}\right\rceil$，证明的话考虑将出现次数小的字符塞到出现次数大的字符中间。

如果$k=1$，那么直接$ABAB\cdots$排列即可，下面考虑$k>1$的情况。

为了使字典序最小，考虑按位添加字符，这一位能填$A$当且仅当
1. 连续的$A$长度不能超过$k$
2. 后面能继续填下去，即后面不能出现连续$k+1$个相同字符。

那么不难发现前缀一定是$AA\cdots ABAA\cdots AB\cdots$，即$A$重复$k$遍后面接一个$B$。而后缀一定是$\cdots ABB\cdots BABB\cdots B$，即$B$重复$k$遍后面接一个$A$。

接下来考虑如何找到前缀和后缀的分界点，然后就可以$\mathcal O(1)$计算每个位置的值了。不难发现最优情况下分界点处必定是一个$A$，且这个$A$是前后缀共用的，假设分界点及其之前有$N_B$个$B$和$N_A$个$A$，那么要满足$N_B\leq max(0,\lfloor\frac{N_A-1}{k}\rfloor$)，同时也有$N_A=A-\lceil\frac{B-N_B}{k}\rceil+1$，带入可得$N_B\leq \left\lfloor\dfrac{A-\left\lceil\frac{B-N_B}{k}\right\rceil}{k}\right\rfloor$，由于要字典序最大，所以分界点要尽可能靠后，即$N_B$尽量大。发现$N_B$增大时，左边递增，右边递减，满足单调性，所以二分找到最大的$N_B$即可。

时间复杂度$\mathcal O(Q\log n)$
#### Code
```cpp
const char s[2] = {'A','B'};

int A,B,C,D,Q,k;

int main(){
    scanf("%d",&Q);
    while(Q--){
        scanf("%d%d%d%d",&A,&B,&C,&D);
        k = ceil(1.0 * max(A,B) / (min(A,B) + 1));
        if(k == 1){
            for(int i = C - 1;i < D;i++)
                putchar(s[(i + (B > A)) & 1]);
            putchar('\n');
            continue;
        }
        int l = 0,r = B,NB = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if((A - (B - mid + k - 1) / k) / k >= mid){
                NB = mid;
                l = mid + 1;
            }else
                r = mid - 1;
        }
        int pos = NB + A - (B - NB + k - 1) / k + 1;
        for(int i = C - 1;i < D;i++)
            putchar(i < pos ? s[i % (k + 1) == k] : s[(A + B - i) % (k + 1) != 0]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：无名之雾 (赞：1)

想到了一半，初看感觉是大分讨，但实际上是很有趣的二分。

## solution

首先有一个简单的结论是最小连续长度位 $k=\lceil\dfrac{\max(a,b)}{\min(a,b)+1}\rceil$，证明的话显然，插中间放即可。

因为题目要求字典序尽量小所以不难猜测到最后的答案形式一定形如：

$$\text{A}\cdots\text{ABA}\cdots\text{A}\text{B}\text{A}\cdots\text{A}\text{B}\cdots\text{B}\text{AB}\cdots\text{B}\text{AB}\cdots\text{B}$$


答案串的构造分为两部分，前面应为 $\text{A}\cdots\text{ABA}\cdots\text{A}$，直到某个位置 $p$ 不满足 $b\le a\times k$为止。

此时位置 $p$ 一定是 $\text{A}$，且 $b-a\times k \le k$，后面就不得不排列成 $\text{B}\cdots\text{B}\text{AB}\cdots\text{B}\text{AB}\cdots\text{B}$。


显然这个位置 $p$ 具有单调性所以我们就可以运用二分来算出边界点。

---

## 作者：樱雪喵 (赞：1)

要令连续的相同字符个数的最大值最小，可以直接贪心将 `A` 和 `B` 尽可能分开，得出答案 $k=\lfloor\frac{A+B}{\min(A,B)+1}\rfloor$。

接下来要在这个基础上构造字典序最小的答案。

我们显然希望 `A` 尽量靠前，直到超出限制时再用 `B` 分开，即靠前部分的答案形如 `AAABAAABAAAB...`。但是后面大量的 `B` 还需要用 `A` 分开，我们希望尽量少的 `A` 被放在后面，则后面部分的答案形如 `BBBABBBABBB...`。

也就是说，完整的答案字符串由前后两部分拼成，前半部分每放 $k$ 个 `A` 放 $1$ 个 `B`；后半部分每放 $k$ 个 `B` 放 $1$ 个 `A`。

那么我们可以二分这个位置 $p$，$\text{check}$ 时分别求出前后所需的两种字符个数即可。

注意 $\text{check}$ 的时候别爆 int。

```cpp
#define int long long 
int T,A,B,C,D,k;
il bool check(int x)
{
    int cntb=x/(k+1),cnta=cntb*k+x%(k+1);
    return (B-cntb)<k*(A-cnta+1);
}
signed main()
{
    T=read();
    while(T--)
    {
        A=read(),B=read(),C=read(),D=read();
        k=max((A+B)/(B+1),(A+B)/(A+1));
        int l=0,r=A+B;
        while(l<r)
        {
            int mid=(l+r+1)>>1;
            if(check(mid)) l=mid;
            else r=mid-1;
        }
        for(int i=C;i<=D;i++)
        {
            if(i<=l) printf(i%(k+1)==0?"B":"A");
            else printf((A+B-i+1)%(k+1)==0?"A":"B");
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：xht (赞：1)

## [Min Max Repetition](https://atcoder.jp/contests/agc020/tasks/agc020_d)

### 题意

- 设 $a,b$ 为正整数，定义 $f(a,b)$ 表示满足下列条件的字符串：
  - $f(a,b)$ 由恰好 $a$ 个 `A` 和恰好 $b$ 个 `B` 构成。
  - $f(a,b)$ 最长的字符全相同的子串是满足上述条件的所有字符串中最短的。
  - $f(a,b)$ 是满足上述条件的所有字符串中字典序最小的。
- 给定 $c,d$，求 $f(a,b)[c:d]$。
- $a,b \le 5 \times 10^8$，$d-c+1 \le 100$，多组数据组数 $T\le 10^3$。

### 题解

最长的字符全相同的子串的长度为 $k = \max(\lceil\frac{a}{b+1}\rceil,\lceil\frac{b}{a+1}\rceil)$。

贪心的构造串可以发现答案为 $(\texttt{A}^k\texttt{B})^{\infty}$ 的某个前缀加上 $(\texttt{A}\texttt{B}^k)^{\infty}$ 的某个后缀，二分出分界点即可，时间复杂度 $\mathcal O(T(\log(a+b) + (d-c)))$。

### 代码

```cpp
int a, b, c, d, k;

inline bool pd(int o) {
	if (!o) return 1;
	if (!(o % (k + 1))) return pd(o - 1);
	int x = a - (o - o / (k + 1)), y = b - o / (k + 1);
	return y <= 1ll * (x + 1) * k;
}

inline void solve() {
	rd(a, b), rd(c, d);
	k = (max(a, b) - 1) / (min(a, b) + 1) + 1;
	int l = 0, r = a + b;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (pd(mid)) l = mid;
		else r = mid - 1;
	}
	for (int i = c; i <= min(l, d); i++)
		printc(i % (k + 1) ? 'A' : 'B');
	for (int i = max(c, l + 1); i <= d; i++)
		printc((a + b - i + 1) % (k + 1) ? 'B' : 'A');
	prints("");
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

非常无脑的做法，有 $3$ 个二分/xk

- 求出最短的连续个数。

二分答案。如何判断一个长度是合法的：也就是所有 `a` 能被 `b` 隔开，所有 `b` 能被 `a` 隔开。

就是 $a+1\ge \lceil b/ln\rceil$ 并且 $b+1\ge \lceil a/ln\rceil$。设判断这个的函数是 $chk(a,b,ln)$。

- 设上一个答案是 $ln$，求出 `a[*ln]b` 最多多少个。

二分答案。其实就是判断 $chk(a-mid\times ln,b-mid+1,ln)$。为啥要加一？因为我们是 `a...ab`，后面有一个 `b`，我们算入要检查的地方即可。

设这个得出的答案是 $ps$。

- 在所有 `a[*ln]b` 之后最多有多少 `a`。

二分答案。其实就是判断 $chk(a-ps\times ln-mid,b-ps+1,ln)$。

- 前面所有之后怎么构造。

发现后面一定是 `...ABBBABBBABBB` 这种，那么可以通过 $(a+b-i+1)\bmod (ln+1)$ 得出。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool chk(ll x,ll y,ll mid){
	return x>=0 && y>=0 && x+1>=(y+mid-1)/mid && y+1>=(x+mid-1)/mid;
}

void solve(){
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	ll l=0,r=a+b+1;
	while (l+1<r){
		ll mid=l+r>>1;
		if (chk(a,b,mid)){
			r=mid;
		}
		else{
			l=mid;
		}
	}
	ll ln=r;
	l=0,r=a+b+1;
	while (l+1<r){
		ll mid=l+r>>1;
		if (chk(a-mid*ln,b-mid+1,ln)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	ll ps=l;
	l=0,r=ln+1;
	while (l+1<r){
		ll mid=l+r>>1;
		if (chk(a-ps*ln-mid,b-ps+1,ln)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	ll pos=ps*(ln+1)+l; 
	for (int i=c; i<=d; i++){
		if (i<=pos){
			if (i%(ln+1)==0) cout<<"B";
			else cout<<"A";
		}
		else{
			if ((a+b-i+1)%(ln+1)==0) cout<<"A";
			else cout<<"B";
		}
	}
	cout<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：zrl123456 (赞：0)

[[AGC020D] Min Max Repetition](https://www.luogu.com.cn/problem/AT_agc020_d)  

题目考察：贪心，数学，二分。  
题目简述：  
$q$ 次询问，给你 $a,b,c,d$，有一字符串 $s$：  
- $\displaystyle|s|=a+b$，$s$ 由 $a$ 个 `A` 和 $b$ 个 `B` 组成。  
- 同时，最大连续相同字符数最小。  
- 同时，字典序最小。  

求该字符串的第 $c$ 位到第 $d$ 位。  
数据范围：  
- $1\le q\le 10^3$
- $1\le a,b\le 5\times 10^8$
- $1\le c\le d\le a+b$
- $1\le d-c+1\le 100$
------------
首先我们肯定可以得出最小的最大连续相同字符数是 $\displaystyle k=\max(\lceil\frac{a}{b+1}\rceil,\lceil\frac{b}{a+1}\rceil)$。  
我们让 `B` 尽可能靠后，那么这个字符串长成这样：
$$\text{AAA\dots ABAAA\dots ABAAA\dots ABAAA\dots ABB\dots BABB\dots BABB\dots BB}$$
那么我们可以二分找出其分界点，那么我们还需要一个判断条件。  
设分界点为 $x$，则 `A` 在前面使用了 $\displaystyle\lfloor\frac{x}{k+1}\rfloor\times k+x\bmod (k+1)$ 个，那么 `A` 在后面就要使用 $\displaystyle a-\lfloor\frac{x}{k+1}\rfloor\times k-x\bmod (k+1)$ 个；`B` 在前面使用了 $\displaystyle\lfloor\frac{x}{k+1}\rfloor$ 个，那么 `B` 在后面使用了 $\displaystyle b-\lfloor\frac{x}{k+1}\rfloor$ 个。  
则我们得到判断条件：
$$(a-\lfloor\frac{x}{k+1}\rfloor\times k-x\bmod (k+1))\times k<b-\lfloor\frac{x}{k+1}\rfloor$$
然后我们发现在前半部分当 $i\bmod (k+1)=0$ 时 $s_i$ 是 `B`，`A` 反之；在后半部分当 $(a+b-k+1)\bmod (k+1)=0$ 时是 `B`，`A` 反之。  

单次询问时间复杂度为 $\Theta(\log_2(a+b)+(d-c))$。  
代码：  
```cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define int long long
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(reg int i=x;i<=(y);++i) 
#define per(i,x,y) for(reg int i=x;i>=(y);--i)
#define rpr(i,x,y,z) for(reg int i=x;i<=(y);i+=z)
#define epe(i,x,y,z) for(reg int i=x;i>=(y);i-=z)
#define endl '\n'
#define INF (int)1e16
#define pb push_back
#define fi first
#define se second
#define lcm(x,y) x/__gcd(x,y)*y
#define ull unsigned long long
#define prr make_pair
#define pii pair<int,int> 
#define gt(s) getline(cin,s)
#define at(x,y) for(reg auto x:y)
#define ff fflush(stdout)
#define mt(x,y) memset(x,y,sizeof(x))
#define idg isdigit
#define fp(s) string ssss=s;freopen((ssss+".in").c_str(),"r",stdin);freopen((ssss+".out").c_str(),"w",stdout);
#define sstr stringstream 
using namespace std;
inl bool check(int x,int k,int a,int b){
//	cout<<(a-x/(k+1)*k-x%(k+1))<<' '<<b-x/(k+1)<<endl;
	return (a-x/(k+1)*k-x%(k+1))*k<b-x/(k+1);
}
inl int lower(int l,int r,int k,int a,int b){
	reg int mid=0,ans=-1,fl=l,fr=r;
	while(l<=r){
		mid=l+r>>1;
//		cout<<mid<<endl;
		if(check(mid,k,a,b)){
			r=mid-1;
			ans=mid;
		}else l=mid+1;
	}
	if(ans!=-1) return ans;
	else if(fl==l) return -1;
	else return r+1;
}
inl void solve(){
	reg int a,b,c,d,k,x;
	cin>>a>>b>>c>>d;
	k=max(max((int)ceil(a/(b+1.0)),(int)ceil(b/(a+1.0))),1ll);
	x=lower(0,a+b,k,a,b);
//	cout<<k<<' '<<x<<endl;
	rep(i,c,d)
		if(i<=x)
			if(i%(k+1)) cout<<'A';
			else cout<<'B';
		else if((a+b-i+1)%(k+1)) cout<<'B';
		else cout<<'A';
	cout<<endl;
}
signed main(){
	fst;
	reg int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [[AGC020D] Min Max Repetition](https://www.luogu.com.cn/problem/AT_agc020_d)

根据贪心，连续的相同字符个数的最大值最小是 $\max(\frac {A} {B+1},\frac {B} {A+1})$。因为要字典序最小，所以最后的字符串一定是 $A \dots ABA \dots ABAAA|B \dots BAB \dots B$。具体说就是一开始先尽量放 $A$，然后放到一定数量发现再放下去后面的连续的 $B$ 的数量就太大了，于是开始尽量放 $B$。这个位置，即上面那根竖线的位置，是可以二分出来的。因为我们要字典序最小，所以 $A$ 肯定尽量往前放，所以后面一部分在保证最长的连续的 $B$ 不超过限制的情况下只能是两段顶到长度上线的 $B$ 的连续段中间放一个 $A$，即满足 $a \times len < b$，其中 $a,b$ 分别表示字符 $A,B$ 在摆放完前一部分后剩余的数量，$len$ 表示最小的最长连续字符的个数。

那么求出分界线以后构造就很简单了。令 $l$ 表示分界线的位置，$r=l+1+b-a \times len$，即后一部分中的第一个 $A$ 的位置。这里是先把那些多余的，即凑不满长度限制的 $B$ 放在第二部分的最前面，这样后面就不用考虑它们了。然后对于小于等于 $l$ 的位置 $i$，如果 $i \bmod (len+1) \neq 0$，那么就是 $A$，否则是 $B$。对于大于 $l$ 的位置 $j$，如果 $(j-r) \bmod (len+1) \neq 0$，那么就是 $B$，否则是 $A$。虽然 $j$ 可能会小于 $r$，但是无所谓，反正取模后不为 $0$，所以它们也还是 $B$。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int T,A,B,C,D,len;
inline bool check(int mid)
{
	int a=A-mid/(len+1)*len-mid%(len+1);
	int b=B-mid/(len+1);
	return b<=a*len;
}
signed main()
{
	scanf("%lld",&T);
	while (T--)
	{
		scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
		len=max(ceil(1.0*A/(B+1)),ceil(1.0*B/(A+1)));
		int l=0,r=A+B+1;
		while (l<r)
		{
			int mid=l+r>>1;
			if (check(mid)) l=mid+1;
			else r=mid;
		}
		int a=A-l/(len+1)*len-l%(len+1);
		int b=B-l/(len+1);
		r=l+1+b-a*len;
		for (int i=C;i<=D;++i)
		{
			if (i<=l)
			{
				if (i%(len+1)) printf("A");
				else printf("B");
			}
			else 
			{
				if ((i-r)%(len+1)) printf("B");
				else printf("A");
			}
		}
		puts("");
	}
	return 0;
}
```


---

