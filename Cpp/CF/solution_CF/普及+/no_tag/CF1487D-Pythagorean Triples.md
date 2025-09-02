# Pythagorean Triples

## 题目描述

A Pythagorean triple is a triple of integer numbers $ (a, b, c) $ such that it is possible to form a right triangle with the lengths of the first cathetus, the second cathetus and the hypotenuse equal to $ a $ , $ b $ and $ c $ , respectively. An example of the Pythagorean triple is $ (3, 4, 5) $ .

Vasya studies the properties of right triangles, and he uses a formula that determines if some triple of integers is Pythagorean. Unfortunately, he has forgotten the exact formula; he remembers only that the formula was some equation with squares. So, he came up with the following formula: $ c = a^2 - b $ .

Obviously, this is not the right formula to check if a triple of numbers is Pythagorean. But, to Vasya's surprise, it actually worked on the triple $ (3, 4, 5) $ : $ 5 = 3^2 - 4 $ , so, according to Vasya's formula, it is a Pythagorean triple.

When Vasya found the right formula (and understood that his formula is wrong), he wondered: how many are there triples of integers $ (a, b, c) $ with $ 1 \le a \le b \le c \le n $ such that they are Pythagorean both according to his formula and the real definition? He asked you to count these triples.

## 说明/提示

The only Pythagorean triple satisfying $ c = a^2 - b $ with $ 1 \le a \le b \le c \le 9 $ is $ (3, 4, 5) $ ; that's why the answer for $ n = 3 $ is $ 0 $ , and the answer for $ n = 6 $ (and for $ n = 9 $ ) is $ 1 $ .

## 样例 #1

### 输入

```
3
3
6
9```

### 输出

```
0
1
1```

# 题解

## 作者：Kobe303 (赞：4)

# 明显数学题

## 思路分析：

由题意得 $\begin{cases}a ^ {2} + b ^ {2} = c ^ {2}\\a ^ {2} -   b = c\end{cases}$

将上面式子移项得 $a ^ {2} = c ^ {2} - b ^ {2}$

将下面式子移项得 $a ^ {2} = c + b$

故 $c ^ {2} - b ^ {2} = c + b$

用我们初一学过的平方差公式可得（没学过的[百度搜索](https://baike.so.com/doc/5386421-5622881.html)）

$(c + b) * (c - b) = c + b$

因为$a, b, c$均为正整数， 所以$c + b \neq 0$

所以两边可以同除以$c + b$

得到$c - b = 1$

故$c = b + 1$

所以$a ^ {2} = (b + 1) ^ {2} - b ^ {2} = 2b + 1$

因为$b$为正整数, 所以$2b+ 1$为奇数

所以$a$也为奇数（$偶数 * 偶数 = 偶数， 奇数 * 奇数 = 奇数$）

易得$a \neq 1$(若$a = 1$, 则$b = 0$, 不符题意)

因为$c \leq n$， 即$b + 1 \leq n$

所以$ b \leq n - 1$

所以$a ^ {2} = 2b + 1 \leq 2n-1$

因为两边都为正整数

所以同时开平方得$a \leq \sqrt {2n-1}$

所以最终答案为$\frac {\sqrt {2n-1} - 1}{2}$(向下取整)

$\sqrt {2n-1}$要减1的理由（$a \neq 1 $）

除以2的理由($a$为奇数)


# 最终代码(时间复杂度为O(T)):

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define reg register 
#define il inline
int T, n;
il int qrint()
{
	int s = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		s = (s << 1) + (s << 3) + (ch ^ 48);
		ch = getchar();
	}
	return s * f;
}
//快读不解释
int main()
{
	
	T = qrint();
	while(T--)
	{
		n = qrint();
		int ans = (sqrt(2 * n - 1) - 1) / 2;
		printf("%d\n", ans);
	}
	return 0;
}

```


---

## 作者：Parat_rooper (赞：3)

本题就是个纯推式子加数学题

题目给了两个方程，虽然是三元二次方程但还比较好解

$c = a ^ 2 - b$

$a ^ 2 + b ^ 2 = c ^ 2$

变形一下一式得：

$c + b  = a ^ 2$

再带入二式：

$c + b + b ^ 2 = c ^ 2$

再变下形：

$c + b = c ^ 2 - b ^ 2$

$c + b = (c + b)(c - b)$

得 $c = b + 1$

带回发现：

$a ^ 2 + 1 = 2b$

再用不等式解：

$1 \leq a \leq n$ 

$1 \leq b \leq n$
所以：

$1 \leq a \leq \frac{\sqrt{2n} - 1 }{2}$

而且$a$是整数
所以$a$的个数就是$\frac{\sqrt{2n} - 1 }{2}$取整

但发现$1$不行，所以减$1$

代码很简单：
```cpp
#include <iostream>
#include <cmath>

using namespace std;

const int kMaxN = 102;

int t, n;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    cout << int((sqrt(2 * n) - 1) / 2) << endl;
  }
  return 0;
}
```
~~一下子打这么多字，好累~~

感谢同机房大佬教本蒟蒻markdown语法


---

## 作者：John_Smith (赞：2)

[获得更差的观看体验](https://www.cnblogs.com/megatrio/p/14431170.html)

一看就是推式子。

由题得

$$\begin{cases}c^2=a^2+b^2\\c=a^2-b\end{cases}$$

将下面的式子代入上式得

$$(a^2-b)^2=a^2+b^2$$

拆开，抵消，移项

$$a^4-2a^2b-a^2=0$$

两边约去 $a^2$

$$a^2-1=2b$$

$$a^2=2b+1$$

因为 $b \in N$，所以 $a$ 是奇数。

再次代入得

$$c=a^2-b=2b+1-b=b+1$$

所以对于每一个奇数 $a$，都有且仅有一对 $(b,c)$ 满足条件。于是问题转化为 $a$ 的数量。（当然，容易发现 $a=1$ 时除外。）

由于 $1 \le a \le b \le c = b+1 \le n$，所以 $b\le n-1$。

然后又因为 $a^2=2b+1 \le 2n-1$，所以 $a\le \sqrt{2n-1}$.。

又因为 $a$ 是奇数且不为 $1$，所以 $a$ 的数量为 $\dfrac{\sqrt{2n-1} -1}2$。

个人觉得这题比 C 水。

关键代码：

```cpp
long long n;cin>>n;
cout<<((int)sqrt(2*n-1)-1)/2<<endl;
```

---

## 作者：houpingze (赞：1)

直接把两个式子结合起来

$$a^2+b^2=(a^2-b)^2$$

解一下

$$a^2+b^2=a^4+b^2-2a^2b$$



$$a^2=a^4-2a^2b$$


$$2a^2b=a^4-a^2$$

$$a^2b=(a^4-a^2)/2$$

$$b=(a^4-a^2)/2/a^2$$


我们只需要枚举$a$，求出$b$，再求出$c=a^2-b$判断一下条件是否满足即可

注意，当$a$或$b$或$c$大于$n$时，直接跳出

时间复杂度约为$O(t\sqrt{n})$

---

## 作者：唐一文 (赞：0)

## Description

给定一个数 $n$，求满足
 $\begin{cases}c=a^2-b\\a^2+b^2=c^2\end{cases}$ 的三元组 $(a,b,c)\ (1\leq a\leq b\leq c\leq n)$ 的个数。

## Solution

$$c=a^2-b$$
$$a^2=b+c$$
带入 $a^2+b^2=c^2$ 得到：
$$b+c+b^2=c^2$$
$$c^2-b^2=b+c$$
$$(b+c)(c-b)=b+c$$
$$c-b=1$$
$$c=b+1$$
那么 $a^2=2c-1$，即 $c=\dfrac{a^2+1}{2}$，$a$ 为奇数。

因为 $1\leq b$，所以 $a\not=1$。

因为 $c\leq n$，所以 $\dfrac{a^2+1}{2}\leq n$。

得到 $1\leq a\leq\sqrt{2n-1}$。

因为 $a$ 为奇数且 $a\not=1$，所以满足的 $a$ （即满足的三元组）有 $\dfrac{\left\lfloor\sqrt{2n-1}\right\rfloor-1}{2}$ 个。

马蜂太丑就不放代码了。

---

## 作者：David_H_ (赞：0)

## 题意

求满足 $\max\{a,b,c\}\le n$ 且满足 $a^2+b^2=c^2$ 与 $a^2-b=c$ 的无序数对 $(a,b,c)$ 的个数。

## 解法

第一眼看这道题我蒙了，然后我打了个表。然后观察发现形如 $(2n+1,((2n+1)^2-1)/2,((2n+1)^2+1)/2)$ 都可以，就打了个 $O(T)$。具体的解法可以看别的题解（

$O(T)$ 算法简述：
 - 首先发现 $(2n+1)^2\le((2n+1)^2+1)\le(2n+2)^2$
 - 那么我们可以先把输入的数乘以二，设输入的数为 $p$，则 $\dfrac{\lfloor \sqrt{2p}\rfloor-1}2$ 即为所求。

正确性比较显然，就不证明了（

所以不用二分也可以解决了！！111

## 代码

核心代码：
```cpp
while (t--) {
    n      = read();
    ll ans = floor(sqrt(2 * n));
    ans -= 1, ans /= 2;
    cout << ans << endl;
}
```

---

## 作者：绝顶我为峰 (赞：0)

来一发纯数学做法。

$c=a^2-b$

$a^2+b^2=(a^2-b)^2=a^4-2a^2b+b^2$

$a^4-(2b+1)a^2=0$

$a^2-2b-1=0$

$b=\frac{a^2-1}{2}$

$c=a^2-\frac{a^2-1}{2}=\frac{a^2+1}{2}\leq n$

$\left\{
\begin{aligned}
1\leq \frac{a^2+1}{2}\leq n \\
1\leq \frac{a^2-1}{2}\leq n \\
1\leq a\leq n \\
\end{aligned}
\right.
$

解得 $\sqrt{3}\leq a\leq\sqrt{2n-1}$。

注意到 $a,b,c$ 均为正整数，因此 $2|a^2-1$ 推出 $2\nmid a$。

因此答案为 $\sqrt{3}\leq a\leq\sqrt{2n-1}$ 范围内的所有奇数，即 $1\leq a\leq\sqrt{2n-1}$ 奇数数量 $-1$。

因此直接统计就好了，$O(1)$ 得出答案。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long t,n;
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        printf("%lld\n",((long long)(sqrt((n<<1)-1))-1)>>1);
    }
    return 0;
}
```


---

## 作者：meyi (赞：0)

本题需要找符合条件的三元组数量，不难发现，对于一个固定的 $a$，$b$ 和 $c$ 也是固定的，因此只需求出符合条件的 $a$ 的数量，证明如下：

根据题意，有

$\left\{
    \begin{array}{l}
            a^2+b^2=c^2 \\  a^2-b=c
        \end{array}
\right.$

$\leftrightarrow b+c+b^2=c^2$

$\leftrightarrow b+c+b^2-c^2=0$

$\leftrightarrow(b+c)(b-c+1)=0$

$\because b+c \ne 0$

$\therefore b+1=c$，$a=\sqrt{b+c}=\sqrt{2b+1}=\sqrt{2c-1}$

又 $\because 1 \le a \le b \le c \le n$

$\therefore a \in [3,\lfloor\sqrt{2n-1}\rfloor]$ 且 $a$ 为奇数

证毕。

则可 $O(1)$ 求出每组数据的答案，总时间复杂度：$O(t)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
int n,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		ri r=sqrt((n<<1)-1);
		printf("%d\n",((r+1)>>1)-1);
	}
	return 0;
}
```


---

