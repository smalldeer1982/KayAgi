# Floor or Ceil

## 题目描述

Ecrade 有一个整数 $x$。存在两种操作：

1. 将 $x$ 替换为 $\left\lfloor \dfrac{x}{2}\right\rfloor$，其中 $\left\lfloor \dfrac{x}{2}\right\rfloor$ 表示不大于 $\dfrac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \dfrac{x}{2}\right\rceil$，其中 $\left\lceil \dfrac{x}{2}\right\rceil$ 表示不小于 $\dfrac{x}{2}$ 的最小整数。

Ecrade 将**恰好执行** $n$ 次操作 1 和 $m$ 次操作 2，且操作顺序任意。他想知道在 $n + m$ 次操作后 $x$ 的**最小可能值**和**最大可能值**。这个问题似乎有些困难，请帮助他！

## 说明/提示

为简化描述，我们将操作 1 称为 $\text{OPER 1}$，操作 2 称为 $\text{OPER 2}$。

在第一个测试用例中：

- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，可得到最小值 $1$。
- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2$，可得到最大值 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
12 1 2
12 1 1
12 0 0
12 1000000000 1000000000
706636307 0 3```

### 输出

```
1 2
3 3
12 12
0 0
88329539 88329539```

# 题解

## 作者：Butterfly_qwq (赞：3)

我们考虑以下两个式子：

$$\lfloor\frac{\lceil\frac{n}{2}\rceil}{2}\rfloor=\lfloor\frac{n+1}{4}\rfloor$$

$$\lceil\frac{\lfloor\frac{n}{2}\rfloor}{2}\rceil=\lfloor\frac{n+2}{4}\rfloor$$

证明就是，如果它除四余零，那么显然是对的，如果它除四余一，那么显然是对的，如果它除四余二，那么显然是对的，如果它除四余三，那么显然是对的。

你注意到前者小于后者，于是先进行所有上取整操作再进行所有下取整操作一定最小，于是先进行所有下取整操作再进行所有上取整操作一定最大。

至于求值，你考虑每次除二，无论是上取整还是下取整，最多求 $O(\log x)$ 次变成 $0$（下取整）或 $1$（上取整），然后就一直不变。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,x,n,m;
int getf(int x,int y)
{
	while(y--)
	{
		if(!x)return 0;
		x>>=1;
	}
	return x;
}
int getc(int x,int y)
{
	while(y--)
	{
		if(x<2)return x;
		x=x+1>>1;
	}
	return x;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>x>>n>>m;
		cout<<getf(getc(x,m),n)<<' '<<getc(getf(x,n),m)<<'\n';
	}
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

## Statement

给定 $x,n,m$，每次可以选取进行任意一次如下操作：

1. $x \leftarrow \lfloor\frac{x}{2}\rfloor$。
2. $x \leftarrow \lceil\frac{x}{2}\rceil$。

总共进行 $n$ 次 $1$ 操作，$m$ 次 $2$ 操作，$n + m$ 次操作不限制顺序，求最终可能得到的 $x$ 的最小值和最大值。

## Solution

贪心。

如果说 $n$ 足够大，最后最大最小值都会是 $0$。

在保持 $x > 1$ 同时，求最小值我们先尽量消耗 $m$，再消耗 $n$，这样一来如果说最后 $n > 0$ 最小值一定为 $0$。

在保持 $x > 1$ 同时，求最大值我们尽量消耗 $n$，再消耗 $m$，这样尽量避免最大值取到 $0$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
int Test, x, n, m;

inline void Solve() {
	scanf ("%lld %lld %lld", &x, &n, &m);
	int mnVal = x, mxVal = x, _n = n, _m = m;
	while (mnVal > 1 && n + m > 0) {
		if (!(mnVal & 1)) {
			if (m > 0) m --;
			else n --;
			mnVal /= 2;
		} else {
			if (m > 0) {
				mnVal = (mnVal / 2) + 1, m --;
			} else {
				mnVal /= 2, n --;
			}
		}
	}
	if (n > 0) mnVal = 0;
	n = _n, m = _m;
	while (mxVal > 1 && n + m > 0) {
		if (!(mxVal & 1)) {
			if (n > 0) n --;
			else m --;
			mxVal /= 2;
		} else {
			if (n > 0) {
				mxVal /= 2, n --;
			} else {
				mxVal = (mxVal / 2) + 1, m --;
			}
		}
	}
	if (n > 0) mxVal = 0;
	printf ("%lld %lld\n", mnVal, mxVal);
}

signed main() {
	scanf ("%lld", &Test);
	while (Test --) Solve();
	return 0;
}
```

---

## 作者：Wind_love (赞：0)

### 思路
考虑贪心。  
容易想到，在原数较大的情况下，使用多次向下取整可以使得原数较向上取整时差较大，即使得原数更小。  
相同的，在原数较小时，使用向上取整可以使原数更大。   
因此，我们得到贪心思路，最小化操作时，先执行 $m$ 次操作二，再执行 $n$ 次操作一；最大化操作时，先执行 $n$ 次操作一，再执行 $m$ 次操作二。  
对于操作一，在原数为零时，无法使原数改变；对于操作二，在原数为零或一时，无法使原数改变。因此，在遇到这些情况时，直接退出即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,n,m;
signed main(){
	cin>>t;
	while(t--){
		cin>>x>>n>>m;
		int temp=x,t2=n,t3=m;
		while(m&&x!=1&&x)x=(x+1)/2,m--;
		while(n&&x)x/=2,n--;
		cout<<x<<" ";
		x=temp,n=t2,m=t3;
		while(n&&x)x/=2,n--;
		while(m&&x!=1&&x)x=(x+1)/2,m--;
		cout<<x<<"\n";
	}
	return 0;
}

---

## 作者：mc_xiexie (赞：0)

### 题意

对一个数以任意顺序进行 $n$ 次 $ \left\lfloor \dfrac{x}{2}\right\rfloor $，$m$ 次 $ \left\lceil \dfrac{x}{2}\right\rceil $。问能得到的最大值和最小值是多少。

### 证明

例如：$10=(1010)_2$。

|次数|操作二过程|操作一过程|
|:-:|:-:|:-:|
|1|$(1010+1)>>1=101$|$(1010)>>1=101$|
|2|$(101+1)>>1=11$|$(101)>>1=10$|
|3|$(11+1)>>1=10$|$(10)>>1=1$|

我们就可以发现当操作二进位后，操作二会比操作一大一，且之后不会再进位。所以最小值最多只会比最大值小一。

其实除了最后一次操作，前面的操作都没意义。如果最后一次操作没有进位，最大值和最小值一样。所以最小值的顺序就是最后进行操作一，而最大值相反。

### 结论

先进行 $m$ 次 $ \left\lceil \dfrac{x}{2}\right\rceil $ 再进行 $n$ 次 $ \left\lfloor \dfrac{x}{2}\right\rfloor $，可以得到最大值。

先进行 $n$ 次 $ \left\lfloor \dfrac{x}{2}\right\rfloor $ 再进行 $m$ 次 $ \left\lceil \dfrac{x}{2}\right\rceil $，可以得到最大值。

由于 $ \left\lceil \dfrac{x}{2}\right\rceil $ 最小只能到 $1$，当其小于 $1$ 时我们就可以结束循环。

而 $ \left\lfloor \dfrac{x}{2}\right\rfloor $ 最小只能到 $0$，当其小于 $0$ 时我们就可以结束循环。

最终复杂度为 $O(T \log x)$。

[AC记录。](https://codeforces.com/contest/2082/submission/311201346)

---

## 作者：_O_v_O_ (赞：0)

div2B 最难的一集。

我们注意到，一次操作二最多进位 $1$，那么我们就可以发现，最大与最小值最多差 $1$（取决于最后一次操作时是否可以进位）。

那么，我们就不妨在求最小值时，先用所有的二操作，再用所有的一操作。同理求最大值时，先用所有的一操作，再用所有的二操作。

为什么呢？很显然，把所有操作二后置就能在最后的操作中尽量多的进位，进而能在最后一次操作中进位。

---

## 作者：_Lazy_whr_ (赞：0)

水贪心。

先考虑一个问题，如果 $n, m$  超过了 $30$，那么超出的部分是没有意义的。因为如果我们要最优化答案，那么一定是将两种操作放在一起使用，即一下子把一种操作全用光，这样的话当 $n, m > 30$ 时，$2^n$ 与 $2^m$ 会大于 $10^9$，不符合题意，所以计算时只需按照 $\min(n, 30)$ 和 $\min(m, 30)$ 来计算即可。

接下来就是贪心，如上文所说，将两种操作一次性全用完。可以证明：先统一向下取整再统一向上取整所得的答案比先统一向上取整再统一向下取整所得的答案更大。

[AC Link](https://codeforces.com/problemset/submission/2082/311248810)

---

