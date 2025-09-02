# [AGC026B] rng_10s

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc026/tasks/agc026_b

コンビニエンスストアのりんごマートでは，りんごジュースを販売しています。

りんごマートはある日の朝に開店し，その時にはジュースの在庫が $ A $ 本ありました。 すぬけ君は毎日昼にりんごマートでジュースを $ B $ 本買います。 りんごマートでは毎日夜にジュースの在庫を確認し，$ C $ 本以下だった場合，次の日の朝までに $ D $ 本在庫を追加します。

すぬけ君がジュースを永遠に買い続けられるかを判定して下さい。 つまり，ジュースを買おうとした時，必ず在庫が $ B $ 本以上あるかどうかを判定して下さい。 すぬけ君以外がジュースを買うことはありません。

また，今回の問題では入力ケースは $ T $ 個のクエリからなります。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 300 $
- $ 1\ \leq\ A,\ B,\ C,\ D\ \leq\ 10^{18} $
- 入力される値は全て整数である

### Sample Explanation 1

$ 1 $ 個目のクエリでは在庫の個数は以下のように変動します。 $ 9 $ →昼 $ 2 $ →夜 $ 11 $ →昼 $ 4 $ →夜 $ 13 $ →昼 $ 6 $ →夜 $ 6 $ →昼 x $ 2 $ 個目のクエリでは在庫の個数は以下のように変動します。 $ 9 $ →昼 $ 2 $ →夜 $ 11 $ →昼 $ 4 $ →夜 $ 13 $ →昼 $ 6 $ →夜 $ 15 $ →昼 $ 8 $ →夜 $ 8 $ →昼 $ 1 $ →夜 $ 10 $ →昼 $ 3 $ →夜 $ 12 $ →昼 $ 5 $ →夜 $ 14 $ →昼 $ 7 $ →夜 $ 7 $ →昼 $ 0 $ →夜 $ 9 $ →昼 $ 2 $ →夜 $ 11 $ →昼 … と続いていき，このまま永遠に購入し続けられます。

## 样例 #1

### 输入

```
14
9 7 5 9
9 7 6 9
14 10 7 12
14 10 8 12
14 10 9 12
14 10 7 11
14 10 8 11
14 10 9 11
9 10 5 10
10 10 5 10
11 10 5 10
16 10 5 10
1000000000000000000 17 14 999999999999999985
1000000000000000000 17 15 999999999999999985```

### 输出

```
No
Yes
No
Yes
Yes
No
No
Yes
No
Yes
Yes
No
No
Yes```

## 样例 #2

### 输入

```
24
1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1```

### 输出

```
No
No
No
No
No
No
Yes
Yes
No
No
No
No
Yes
Yes
Yes
No
No
No
Yes
Yes
Yes
No
No
No```

# 题解

## 作者：cjh20090318 (赞：6)

多校联考考这个题，然后因为大样例给的太水了很多人因此挂分。

## 题意

当 $A \ge B$ 时，$A \gets A - B$，如果此时 $A \le C$，$A \gets A + D$。

请问能否无限循环执行下去。

## 分析

首先分析几个比较容易判断的条件。

$A < B$ 时不会进入循环，所以不能。

$D < B$ 时即使进入了循环也没有用，因为即使能加也不能使 $A$ 回到原来的水平。

对于剩下的情况，此时已经保证了 $A \ge B$，$D \ge B$。

一种显然会无限循环的情况是 $C \ge B-1$，因为当 $A < B$ 时必然满足 $A \le C$ 的情况，且 $D \ge B$，所以一定又会将 $A$ 加回 $A \ge B$ 的状态。

剩下的情况是绝对无解或有解的吗？并不是。

如果我们可以找到一个非负整数 $k$ 使得 $( a + k(d-b) ) \bmod b > c$，也就是说经过一定的操作后 $C < A < B$，那么就不能继续循环了。

将上面那个式子转化为同余方程 $kd \equiv x - a \pmod{b}$，需要找到一个 $x \in (c,b)$ 使得该同余方程有解。

根据裴蜀定理，同余方程有解的条件是 $\gcd(b,d) \mid (x-a)$，于是我们直接求最大的 $x$ 即可。

单次时间复杂度 $O(\log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
LL a,b,c,d;
void solve(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	if(d<b||a<b) puts("No");
	else{
		if(c>=b-1) puts("Yes");
		else{
			LL g=__gcd(d,b);
			a%=b;
			LL x=(b-1-a)/g*g;
			puts((a+x)%b>c?"No":"Yes");
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Ezio__Auditore (赞：4)


## AT3971 [AGC026B] rng_10s
[[Statement]](https://www.luogu.com.cn/problem/AT3971)

Date: Apr. 14th

---
##### 题意：
很明确了，不多解释。

~~买果汁模范客户 Snuke 君。~~

---
##### 分析：
首先考虑几种特殊情况：

1. $A < B \to$ No： Snuke 君第一次就买不了，显然不行。
2. $D < B \to$ No： 补的还没有买的多，不能无限购买，显然不行。
3. 排除 1, 2 情况后，若 $C > B \to$ Yes：老板一定会在果汁卖完之前补上足够的货，使 Snuke 可以继续购买。

目前，我们可以得到：

$$
f(A, B, C ,D) = \begin{cases}
							No & \text{case} : A < B\\
							No & \text{case} : D < B\\
							Yes & \text{case}: C > B\\
							Maybe & \text{otherwise}
						 	\end{cases}
$$

---

对于 **Maybe** 的情况：

果汁数量不能处于 $(C, B)$ 之间，因为那样老板不会补货， Snuke 也无法购买到足够的果汁。

假设 Snuke 购买了 $x$ 次， 老板补货了 $y$ 次：
$$
	-xB + yD + A \not\in (C, B)\\
	-xB + yD \not \in (C - A, B - A)\\
$$
即 以下不等式：
$$
C - A < -xB + yD < B - A
$$
**不能有整数解**。

---

等价于：
$$
\forall k \in (C- A, B - A), -xB + yD = k \text{无整数解。}
$$
而我们知道，对于确定的 $k$， $-xB + yD=k$ 有整数解当且仅当 $k \bmod \gcd(B, D) = 0$（拓展欧几里得）。

所以问题等价于，命题 $\forall k \in (C - A, B - A),  \gcd(B, D)\not|\ k$ 是否成立。若成立则为 Yes， 否则为 No。

P.S. 上述不等式另一种理解形式：$A + k D > C \pmod B$， $k$ 是否存在整数解。

综上：
$$
f(A, B, C, D) = \begin{cases}
							No &  A < B\ \text{or}\ D < B\ \text{or} \\ 
							 & \exists k\in(C - A, B-A), \gcd(B, D)\ |\ k \\
							Yes & \text{otherwise}
							\end{cases}
$$

---

##### Code: 

> 代码很简单就不放了。

判断 $\exists k\in(C - A, B-A), \gcd(B, D)\ |\ k$ 的方法如下：

- **若闭区间 $[L, R]$ 中有 $d$ 的倍数，则满足 $\lfloor\frac Rd\rfloor > \lfloor\frac {L-1}d\rfloor$。**

注意负数除法向下取整的问题，可以使用如下代码：

```cpp
ll floor_frac(ll a, ll b) { // 获得 a / b 向下取整的结果
  if (!((a > 0) ^ (b > 0)))  // a / b > 0 直接除就可以了。
    return a / b;
  else  // a / b < 0 ，若不是整除则需要 - 1 补偿，才是向下取整的结果/
    return a / b - static_cast<bool>(a % b);
}
```

---
##### 后记：

Q. 可能你会质疑，求出 $x$, $y$ 的整数解就一定能通过题目中所给的方式达到吗？

A. 这里可以采用 “$A + k D > C \pmod B$， $k$ 是否存在整数解” 来理解这个问题。

我们需证明：“$A + k D > C \pmod B$，若 $k$ 的整数解集 $S \not = \emptyset$ ，则 $\exists k\in S$ 能通过题中合法操作方式得到。”



根据线型同余方程的结论，若方程有一整数解 $k$, 则 $k + t\times\frac{B}{\gcd(B, D)}, t\in \Z$ 都是合法解。

所以若 $S \not=\emptyset$，则 $k$ 一定存在自然数解，记 $k$ 的**最小自然数解** $k'$ ($k'$ 可以为 $0$，$k'$ 一定存在)。

接下来我们证明这个最小自然数解 $k'$一定可以通过题中合法操作得到，就足以说明原命题成立。

令开始时 $k = 0$，则有：

 1. 当 $(A + kD) \bmod B \le C$ 时，老板会补货，$k$ 可以变成 $k + 1$，而 Snuke 的购买相当于对 $A + kD$ 执行 $\bmod B$。

 2. 当 $(A + kD) \bmod B > C$ 时，我们确定了 Snuke 无法继续购买，不需要再讨论下去了，可以 "break"。

此时的 $k$ 就是满足条件的最小自然数解 $k'$。 $\square$

---

**END.**

---

## 作者：沉石鱼惊旋 (赞：3)

# 题目翻译

给定 $a,b,c,d$，重复执行 $a\gets a-b$。但是操作完后如果 $a\leq c$ 将会执行 $a\gets a+d$，问是否可以保证 $a\gt 0$ 的情况下无限次执行。

多测，$1\leq t\leq 300,1\leq a,b,c,d\leq 10^{18}$。

# 题目思路

特殊情况是 $a\lt b$ 表示第一天买完了，$d\lt b$ 表示你加的没有要的多，都是不合法的情况。

那么我们判掉之后就成了 $a\geq b\operatorname{and} d\geq b$。

设买了 $x$ 次，加了 $y$ 次，此时我们就是在找是否有解满足 $c\lt a-bx+dy\lt b$，表示我们现在可以到 $\gt c$ 但是加不到 $\geq b$。如果存在就说明可以被买完。

又因为 $bx-dy=k\times \gcd(b,d)$，所以就是在问是否存在这样的 $k$ 使得 $c\lt a-k\times \gcd(a,b)\lt b$，移项得到 $a-b\lt k\times \gcd(a,b)\lt a-c$。

这个是很好判断的，那么就做完了。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (min(a, d) < b)
        return puts("No"), void();
    ll g = __gcd(b, d);
    puts((a - c - 1) / g <= (a - b) / g ? "Yes" : "No");
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：火车司机 (赞：3)

## 简要分析

我们设买了 $x$ 次果汁，补了 $y$ 次果汁

那么当 $c < a - b \times x + d \times y < b$ 有正整数解时，不能无限购买

移个项得 $a - b < b \times x - d \times y < a - c$

由裴蜀定理可得，上述不等式有正整数解当且仅当 $\exists\ x$ 是 $gcd(b,d)$ 的倍数，并且满足 $a - b < x < a - c$

特殊的，当 $a < b$ 时，第一天就不能买。当 $d < b$ 时，补的比买的少，必然不能无限购买。这两种情况需要特判

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int T;
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
inline int gcd(int a, int b)
{
	while (b)
		a %= b, b ^= a ^= b ^= a;
	return a;
}
signed main()
{
	read(T);
	for (ri a, b, c, d, g; T--;)
	{
		read(a), read(b), read(c), read(d);
		if (a < b || d < b)
			puts("No");
		else
		{
			g = gcd(b, d);
			if ((a - c - 1) / g > (a - b) / g)
				puts("No");
			else
				puts("Yes");
		}
	}
	return 0;
}
```


---

## 作者：_hxh (赞：1)

### 题意

果汁店里一开始有 $A$ 瓶苹果汁，每一天 Snuke 都去买 $B$ 瓶苹果汁，每天晚上如果店里苹果汁的数量不超过 $C$ 瓶，店主就会增加 $D$ 瓶苹果汁，问 Snuke 是否可以无限买苹果汁。

### 分析

看起来是模拟题，但是你突然看到：$1 \le A,B,C,D \le 10^{18}$。行吧，那这题不出意外的话应该是结论题了。那就一步一步推吧！

首先可以特判一些情况：

1. $A < B$ 时 Snuke 第一次就买不了；
2. $D < B$ 说明苹果汁供不应求，显然不能无限购买；

对于剩下的情况，试想一下，如果苹果汁的数量在区间 $(C,B)$ 内，此时店主不会增加苹果汁，Snuke 也买不到足够的苹果汁，这不就不能无限买苹果汁了吗！所以我们可以尝试判断店内苹果汁的数量会不会某时刻在区间 $(C,B)$ 内。设 Snuke 买了 $x$ 次苹果汁，店主增加了 $y$ 次苹果汁，则此时我们就要计算是否存在正整数解 $(x,y)$ 满足 $c < a + dy - bx < b$，若**有解**就说明 Snuke **不能**无限买苹果汁。

将上面的不等式变形得：$a - b < bx - dy < a - c$，解这个不等式的前置知识是裴蜀定理。

***

裴蜀定理：**关于 $x,y$ 的不定方程 $ax + by = c$ 有整数解的充要条件是 $\gcd(a,b) \mid c$**。

***

显然 $\gcd(a,b) \mid (ax + by)$，那么对于本题的式子来说，$bx - dy$ 就可以表示为 $m \times \gcd(b,d)$，$m \in \mathbb N+$，这样我们只要判断是否存在这样的 $m$ 使 $a - b < m \times \gcd(b,d) < a - c$ 成立即可。怎么 $\Theta(1)$ 判断？原式转化为 $\dfrac{a - b}{\gcd(b,d)} < m < \dfrac{a - c}{\gcd(b,d)}$，如果存在正整数解 $m$ 的话 $\lfloor \dfrac{a - c}{\gcd(b,d)} \rfloor$ 和 $\lfloor \dfrac{a - b}{\gcd(b,d)} \rfloor$ 的差一定不小于 $1$。这等价于 $\lfloor \dfrac{a - c - 1}{\gcd(b,d)} \rfloor > \lfloor \dfrac{a - b}{\gcd(b,d)} \rfloor$，直接判断这个即可。为什么分子 $a - c$ 要加上 $-1$？因为当 $\dfrac{a - c}{\gcd(b,d)} = \dfrac{a - b}{\gcd(b,d)} + 1$ 且 $\dfrac{a - c}{\gcd(b,d)} \in \mathbb N+$ 时显然 $m$ 无解，即此时可以无限买苹果汁，但此时 $\lfloor \dfrac{a - c}{\gcd(b,d)} \rfloor > \lfloor \dfrac{a - b}{\gcd(b,d)} \rfloor$ 是成立的，如何解决？分子 $a - c$ 再加上 $-1$ 即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int gcd(int a,int b)
{
	return b == 0 ? a : gcd(b,a % b);
}
int t,a,b,c,d;
signed main()
{
	cin >> t;
	while (t--)
	{
		cin >> a >> b >> c >> d;
		if (a < b || d < b)
			cout << "No" << endl;
		else if ((a - c - 1) / gcd(b,d) > (a - b) / gcd(b,d))
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}
	return 0;
}
```

---

## 作者：focus_aurora (赞：1)

## 思路

数学。

裴蜀定理。

先进行特判。

如果 $A < B$ 或者 $D < B$ 时，直接输出 No 即可。

如果 $C > B$ 时，输出 Yes 即可。

设买了 $a$ 次果汁，补了 $b$ 次果汁。

如果 $c < A-B×a+D×b < B$ 有正整数解时，不可以无限购买。

否则可以。

根据裴蜀定理可知，不等式有整数解当且仅当存在 $a$ 是 $\gcd(B,D)$ 的倍数且满足 $A-B < a < A-C$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int gcd(int a,int b){//辗转相除法求最大公约数
	while(a%b!=0){
		int r=a%b;
		a=b;
		b=r;
	}
	return b;
}
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int a,b,c,d;
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		if(a<b||d<b){//特判No的情况
			cout<<"No"<<endl;
			continue;
		}
		if(c>b){//特判Yes的情况
			cout<<"Yes"<<endl;
			continue;
		}
		int ans=gcd(b,d);
		if((a-c-1)/g>(a-b)/g){//如果有正整数解
			cout<<"No"<<endl;
		}
		else{//如果没有正整数解
			cout<<"Yes"<<endl;
		}
	}
	return 0;
} 
```
完结撒花。

---

## 作者：Ascnbeta (赞：0)

## [AGC026B] rng_10s

一开始以为是个找规律，罚了 3 发才发现是个数论。

PS：别看样例很多但是水的要死。

很容易想到如下不合法的情况：

* $A<B$，显然买一次都不够。
* $B>D$，补的比买的少，自然不可能无限进行下去。

因此以下讨论基于 $A\ge B$ 和 $B\le D$。

又很容易发现一种一定可行的情况：

* $C\ge B$，因为如果拿完一次后出现了下一次可能不够拿的情况，这时 $A$ 一定 $<B$，又因为 $C\ge B,D\ge B$，肯定又会补回到 $\ge B$ 的情况。不知道为什么其他题解似乎都没有取这个等号。

那剩下的情况呢？

发现不能进行下去肯定是因为在一次补完货后 $C<A<B$，而又因为 $C<B$，所以肯定一开始是 $A\to A\bmod B$，然后才开始补货。

记 $A'=A\bmod B$，则实际上我们是要找一个自然数 $k$，满足：
$$
C<(A'+k(D-B))\bmod B<B
$$
模 $B$ 是因为可能补完之后拿一次还不能补货，所以要取模。

因为后面那个不等式恒成立，我们拆括号后一通乱搞，就会发现我们要求的是：
$$
(kD+A')\bmod B>C
$$
设 $x=kD+A'$，则转化为求线性同余方程 $kD\equiv x-A'\pmod B$ 有无 $x\in(C,B)$ 的整数解。

根据裴蜀定理，有解的条件是 $\gcd(B,D)|(x-A')$，我们据此直接求出小于 $B$ 的最大解，判断它和 $C$ 谁更大。

由于我们这个解必须小于 $B$，所以 $x-A'=\left\lfloor\dfrac{B-1-A}{\gcd(B,D)}\right\rfloor\times\gcd(B,D)$。

接下来把这个值加上 $A'$ 再模 $B$，判断其与 $C$ 的大小关系。若大于则不能无限进行。

时间复杂度 $\mathcal{O(T\log D)}$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,d;
signed main() {
#ifdef LOCAL
    freopen("E:/codes/exe/a.in","r",stdin);
    freopen("E:/codes/exe/a.out","w",stdout);
#endif
    cin >> T;
    while (T--) {
        cin >> a >> b >> c >> d;
        if (a < b || b > d) {
            puts("No");
        }else{//a>=b b<=d
            if (b-1 <= c) {
                puts("Yes");
            }else{//b > c
                a %= b;
                int gcd = __gcd(b,d);
                int x = (b-1-a)/gcd*gcd;
                if ((a+x)%b > c) puts("No");
                else puts("Yes");
            }
        }
    }
    return 0;
}
```

---

## 作者：TemplateClass (赞：0)

首先我们应该注意到当 $B > A$ 或 $B > D$ 时不可能无限，所以先特判输出 `No`。

然后假设我们已经买了 $x _ 1$ 次，店主已经加了 $x _ 2$ 次。注意到题目当中的无限购买情况实际上就是还剩的果汁数量 $\notin (C, B)$，这不难理解。

显见还剩的果汁数量就是 $A - Bx _ 1 + Dx _ 2$。根据 Bézout 定理，$Bx _ 1 - Dx _ 2 = k \times \gcd(B, D)$，其中 $k \in \Z$。代入得到 $C < A - k \times \gcd(B, D) < B$，移项得 $A - B < k \times \gcd(B, D) < A - C$。

也就是说，我们需要判断是否存在这个整数 $k$。直接先求出第一个 $> A - B$ 的 $\gcd(B, D)$ 的倍数，判断它是否 $ < A - C$ 即可。

```cpp
typedef long long ll;
typedef long double ld;

inline void solve() {
	ll a, b, c, d;
	std::cin >> a >> b >> c >> d;
	if(b > a || b > d) {
		std::cout << "No" << "\n";
		return ;
	}
	
	ll gcd = std::__gcd(b, d);
	__int128 fmul = (__int128)gcd * std::ceil((ld)(a - b) / gcd);
	if(fmul == a - b) fmul += gcd;
	
	std::cout << (fmul < a - c ? "No" : "Yes") << "\n";
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [AGC026B] rng_10s



## 思路

看到本题，我们首先想到的是继续模拟，看是否有循环节（即是否有第 $i$ 天与第 $j$ 天剩余苹果汁的数量相同。如果有，则可以无限买，否则如果中途发现某一天苹果汁不够了，那么就不可以）。但是这样显然是不可以实现的。于是我们从 $A,B,C,D$ 四个数字的关系上来看。

很显然的是，如果 $C+D<A$，那么一定不可以。如果 $A<B$，那么第一天就买不了。如果 $D<B$，那么补充比消耗少，也肯定不行。

我们假设 Snuke 买了 $x$ 次果汁，商店补充了 $y$ 次果汁，那么我们可以知道此时商店剩余的果汁数量为 $A-xB+yD$。那么什么时候 Snuke 买不到果汁呢？当然是果汁的数量 $<B$ 且 $>C$ 的情况了。那么很显然我们可以列出一个不等式。

$C<A-xB+yD<B$

如果这个不等式有整数解的话，那么就说明在 Snuke 买了 $x$ 次果汁，商店补充了 $y$ 次果汁后，就会出现 Snuke 买不到果汁的情况了。

整理一下这个不等式。

$\begin{cases}C<A-xB+yD\\B>A-xB+yD\end{cases}$

$\begin{cases}xB-yD<A-C\\xB-yD>A-B\end{cases}$

$A-B<xB-yD<A-C$

我们设一个不定方程 $xB-yD=k$，那么如果这个方程有整数解且 $A-B<k<A-C$ 的话，那么上面的不等式就有整数解。那么根据裴蜀定理（或贝祖定理）得：

> 若 $a,b$ 是整数，且 $\gcd(a,b)=d$，那么对于任意的整数 $x,y,ax+by$ 都一定是 $d$ 的倍数，特别地，一定存在整数 $x,y$，使 $ax+by=d$ 成立。

如果存在 $k$ 是 $\gcd(B,D)$，那么不定方程 $xB-yD=k$ 有整数解。由于我们完全可以把不定方程的左右两边都乘以一个整数，所以只要 $k$ 是 $\gcd(B,D)$ 的倍数，我们都可以找到正整数解 $(x,y)$。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,b,x,y,T,ans,res,idx,cnt;

signed main(){
	cin>>T;
	while(T--){
		int c,d;
		cin>>a>>b>>c>>d;
		
		if(a<b||d<b){
			cout<<"No\n";continue;
		}
		
		int g=__gcd(b,d);
		int flg=0;
		for(int i=a-b+1;i<a-c;i++){
			if(i%g==0)flg=1;
		}
		if(flg)cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}

```




---

## 作者：Krimson (赞：0)

安利个人[blog](https://www.cnblogs.com/Guts/p/14655127.html)  



------------
首先先特判一些情况。  
1.b>d  
这种情况会出现入不敷出，显然无法无限购买。  
2.a<b  
第一天就买不了
3.c>b
再去掉上面两种情况之后c>b的时候一定可以无限买，很显然，不解释了。  

先令 $a = a\mod b$ ，显然不影响答案。
去掉上面几种情况后，开始推式子。  
设已经买了 $x$ 次，进货了 $y$ 次，那么可以得到
$$
\begin{aligned}

a+xd &\in(yb+c,(k+1)b)\\
xd-yb &\in(c-a,b-a)\\
(x-y)d-y(b-d)&\in(L,R)\\

\end{aligned}
$$  
注意到式 $2$ 和式 $3$ 形式一样，最后肯定有一边变成 $0$ ，另一边变成 $\gcd(x,y)$。
因此，等价于是否存在整数 $k$ 满足 $k\times \gcd(x,y)\in(L,R)$。

时间复杂度$O(T \log V)$。   
  

_Code_
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
ll a,b,c,d;
il ll gcd(ll x,ll y){
    for(;y;x%=y,swap(x,y));
    return x;
}
int main(){
    for(ri t=read();t;--t){
        a=read(),b=read(),c=read(),d=read();
        if(a<b){
            puts("No");
            continue;
        }
        if(b>d){
            puts("No");
            continue;
        }
        if(c>b){
            puts("Yes");
            continue;
        }
        a%=b;
        if(a>c){
            puts("No");
            continue;
        }
        ll l=c-a,r=b-a;
        ll g=gcd(b,d),x=(l+g-1)/g*g;
        while(x<=l) x+=g;
        if(x<r) puts("No");
        else puts("Yes");
    }

    return 0;
}
```

---

