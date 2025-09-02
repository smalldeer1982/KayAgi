# Pythagorean Triples

## 题目描述

Katya studies in a fifth grade. Recently her class studied right triangles and the Pythagorean theorem. It appeared, that there are triples of positive integers such that you can construct a right triangle with segments of lengths corresponding to triple. Such triples are called Pythagorean triples.

For example, triples $ (3,4,5) $ , $ (5,12,13) $ and $ (6,8,10) $ are Pythagorean triples.

Here Katya wondered if she can specify the length of some side of right triangle and find any Pythagorean triple corresponding to such length? Note that the side which length is specified can be a cathetus as well as hypotenuse.

Katya had no problems with completing this task. Will you do the same?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707C/80a087cda42609e729836c8476c6d8655d41a6b9.png)Illustration for the first sample.

## 样例 #1

### 输入

```
3
```

### 输出

```
4 5```

## 样例 #2

### 输入

```
6
```

### 输出

```
8 10```

## 样例 #3

### 输入

```
1
```

### 输出

```
-1```

## 样例 #4

### 输入

```
17
```

### 输出

```
144 145```

## 样例 #5

### 输入

```
67
```

### 输出

```
2244 2245```

# 题解

## 作者：NFGase (赞：12)

这道题是一道数论题，不可用暴力通过，因为输入范围极大，基本上循环是不能在这道题上使用的了。

前面大佬们讲的我听不懂，于是在教练的帮助下，我利用题面给出的多组样例找到了规律。

在此之前，我们先设输入的数为 $n$ 。

 $n$ 分三种情况。

-  $n$ 是奇数；
-  $n$ 是偶数；
-  $n$ **小于等于** $2$；

首先咱们必须把 $n$ 小于等于 $2$ 的这种情况清除掉，众所周知，这种数是不可能存在解的，于是直接输出 `-1` 并结束程序即可。

之后咱们再看 $n$ 是奇数这种情况，不难发现，输出的第一个数等于 $n ^ {2} \div 2$，而第二个数则是 $(n ^ {2} \div 2) + 1$ 。

 $n$ 若是偶数则将其除以 $2$ 转化为奇数，之后输出时乘以 $2$ 即可。
 
代码如下
 
 ```cpp
 #include <iostream>
using namespace std;
long long n;
int main(){
    cin >> n;
    if(n <= 2){
        cout << -1;
        return 0;
    }
    if(n % 2 != 0) cout << ((n * n) / 2) << " " << ((n * n) / 2) + 1;
    else{
        n /= 2;
        cout << (n * n) - 1 << " " << (n * n) + 1;
    }
    return 0;
}
 ```
 
 [评测结果](https://www.luogu.com.cn/record/116940120)

---

## 作者：ryl_ahu (赞：6)

首先我们要知道勾股定理：$a ^ 2 + b ^ 2 = c ^ 2$。

然后我们设一个数 $n = a ^ 2$。

这样 $n = c ^ 2 - b ^ 2$。

根据平方差公式，所以 $n = (c + b) \times (c - b)$。

因为 $n = 1 \times n$，所以可以列出以下式子：
$$
	\begin{cases}
	n = c + b \\
	1 = c - b \\
 	\end{cases}
$$


随后我们又根据和差公式便可得知：

$$
	\begin{cases}
	c = (n + 1) \div 2 \\
	b = (n - 1) \div 2 \\
 	\end{cases}
$$

所以，如果 $n$ 是奇数，那么 $c$ 和 $b$ 就出来了：

```
if (a % 2 == 1) {
	a *= a;
	cout << (a - 1) / 2 << " ";
	cout << (a + 1) / 2 << endl;
}
```
---

接下来，我们再来判断 $n$ 是偶数的情况：如果 $n$ 是偶数，我们就将 $n$ 一直除以 $2$，直到 $n$ 除以 $2$ 余 $1$。用奇数的算法算出 $b$ 和 $c$，再乘以刚才除的那些 $2$ 就可以啦：

```
if (a % 2 == 0) {
	int ans = 1;
	while (a % 2 == 0) {
		a /= 2;
		ans *= 2;
	}
}
```
---
还有，如果 $n$ 一直除以 $2$ 除的最后正剩下 $1$，那就得特殊判断：用 $3$、$4$、$5$ 这一组勾股数带进去就可以了：
```
if (a == 1)
{
	cout << 3 * ans / 4 << " ";
	cout << 5 * ans / 4 << endl;
}
```
---

对了！我们还要判断一下 $a$ 是否小于 $3$，因为没有小于 $3$ 的勾股数，特判即可。

---
#### 结尾附上总代码：
```
#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a;
	cin >> a;
	if (a <= 2) {  // 特判
		cout << -1 << endl;
		return 0;
	}
	if (a % 2 == 1) { // 判断奇数
		a *= a;
		cout << (a - 1) / 2 << " ";
		cout << (a + 1) / 2 << endl;
	}
	if (a % 2 == 0) { // 判断偶数
		int ans = 1;
		while (a % 2 == 0) {
			a /= 2;
			ans *= 2;
		}
		if (a == 1) // 判断二次幂
		{
			cout << 3 * ans / 4 << " ";
			cout << 5 * ans / 4 << endl;
			return 0;
		}
		a *= a;
		cout << (a - 1) * ans / 2 << " ";
		cout << (a + 1) * ans / 2 << endl;
	}
	return 0; // 华丽结束！
}
```


---

## 作者：zenght (赞：3)

### 题意

给定正整数 $n$，输出一组 $m, k$，使得 $n, m, k$ 可以构成三角形三边。

### 解法

~~MOer 狂欢~~

一道码量很小的数学题，涉及到数学中的勾股方程。

对于方程 $a^2+b^2=c^2, a, b, c \in N_+$，解为 $\begin{cases}a=x^2-y^2\\b=2\cdot x\cdot y\\c=x^2+y^2\end{cases}$ 或 $\begin{cases}a=2\cdot x\cdot y\\b=x^2-y^2\\c=x^2+y^2\end{cases}, x, y \in N_+, x>y$。

我们容易验证这组解是正确的，又因为这题只要输出一个解即可，没必要证明不存在更多的解。

这时候可以分类讨论。

1. 当 $n=2a, a \in N_+$ 时，令 $n=2\cdot x\cdot y, x\cdot y=a$。不妨令 $x=a, y=1$，输出 $a^2-1, a^2+1$。但是，当 $n=2$ 时，$a=1$，此时 $x=y$，故不存在，输出 $-1$。

1. 当 $n=2a-1, a \in N_+$ 时，令 $n=x^2-y^2$。不妨令 $x=a, y=a-1$，输出 $2\cdot a^2-2\cdot a, 2\cdot a^2-2\cdot a+1$。但是，当 $n=1$ 时，$a=1$，此时 $y=0$，故不存在，输出 $-1$。

容易发现，我们构造的数均 $\le 10^{18}$，满足题意。

下面是部分代码：

```cpp
// 十年 OI 一场空，不开 long long 见祖宗
long long n;
cin >> n;
if (n == 1 || n == 2) cout << -1 << '\n';
else if (n % 2 == 0) cout << n * n / 4 - 1 << " " << n * n / 4 + 1 << '\n';
else cout << n * n / 2 << " " << n * n / 2 + 1 << '\n';
```

~~点赞 + 评论 + 关注！~~

---

## 作者：囧仙 (赞：2)

## 题目大意

> 给定正整数 $n$ ，求出一组 $(m,k)$ ，使得它们可以构成直角三角形三条边。  
$1\le n\le 10^9;1\le m,k\le 10^{18}$ 。

## 题解

可以组成直角三角形三边的数对 $(a,b,c)$ （不妨设 $c>a,c>b$ ），必定满足勾股定理：

$$a^2+b^2=c^2$$

- 
考虑令 $a=n$ 。观察勾股定理，我们能够发现，由于 $a^2=c^2-b^2=(c+b)\times (c-b)$ ，因此我们只要取 $\begin{cases}b+c=a^2\cr c-b=1\end{cases}$ ，就能符合条件。此时取 $\begin{cases}b=\frac{a^2-1}{2}\cr c=\frac{a^2+1}{2}\end{cases}$ 即可。尽管看上去很简单，但这种做法有一个缺陷：当 $n$ 不为偶数时， $b,c$ 不能是整数；同时， $a$ 不能取到 $1$ 。考虑去弥补这个缺陷。

有一个比较显然的结论是，如果 $(a,b,c)$ 是勾股数对，那么 $(a\cdot 2^k,b\cdot 2^k,c\cdot 2^k)$ 也是勾股数对。所以我们可以先把 $n$ 当中所有的质因子 $2$ 取出来。即令 $n=n'\cdot 2^s$ ，其中 $n'$ 为奇数。按照上式求出答案，再乘上 $2^s$ 就行了。

但是还有一个问题，当 $n$ 恰好是 $2$ 的次幂（即 $n=2^s$ ）时， $n'=1$ ，此时 $c=0$ 不合题意。但是能够发现，比如 $4$ 就可以构造出 $(3,4,5)$ 这样一组答案。解决办法也很简单，如果 $n=2^s$ ，并且 $s\ge 2$ ，就取 $n'=4$ 即可。

下证 $n\le 2$ 时无解。对于 $c\ge 2$ ，有 $(c+1)^2-c^2=2c+1\ge 5>n^2$ 。也就是说，当 $n\le 2$ 时， $n$ 不能作为 $\{a,b\}$ 当中的一个。同时又因为此时 $n$ 不能作为 $c$ ，于是无解。

将上述所有内容综合起来，就能得到本题的所有答案了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define debug(x) (printf("The value of [%s] in fuction[%s] is %d.\n",#x,__FUNCTION__,x))
#define up(l,r,i) for(register int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(register int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long LL;
const int INF =2147483647;
int qread(){
	int w=1,c,r=0;
	while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); r=c-'0';
	while((c=getchar())>='0'&&c<='9') r=r*10+c-'0';
	return r*w;
}
int main(){
	LL n=qread(),t=1; if(n<=2) puts("-1"),exit(0);
	while(n>4&&n%2==0) t<<=1,n>>=1;
	if(n==4) printf("%lld %lld\n",3*t,5*t);
	else n*=n,printf("%lld %lld\n",1ll*(n+1)/2*t,1ll*(n-1)/2*t);
	return 0;
}
```

---

## 作者：huqingyi (赞：1)

# CF707C
[原题传送门](https://www.luogu.com.cn/problem/CF707C)

[博客](https://www.luogu.com.cn/blogAdmin/article/edit/612487)
## 简述题意
给定正整数 $a$，求与其组成勾股数的 $b$ 和 $c$。
## 分析

我们可以分两种情况讨论：
>-  $a$ 为奇数
>- $a$ 为偶数

观察样例，不难发现，当 $a$ 为奇数时，$a^2=b+c$  并且  $c-b=1$，当 $a$ 为偶数时，$\frac{a^2}{2}=b+c$ 并且 $c-b=2$。

具体证明看下面：
- $a$ 为奇数：

结论：
 $$\begin{cases}a^2=b+c\\ c-b=1\end{cases}$$
 
证明：
 $$\begin{cases}a=(2k+1)\\a^2=4k^2+4k+1 \end{cases} $$
 $$\because b=c-1$$
 
 $$\therefore\begin{cases}b=2k^2+2k\\c=2k^2+2k+1\end{cases}$$
 
$$\begin{cases}b^2=4k^4+8k^3+4k^2\\c^2=4k^4+8k^3+8k^2+4k+1\end{cases}$$

$$a^2+b^2=c^2$$

- $a$ 为偶数：

结论：
$$\begin{cases}\frac{a^2}{2}=b+c\\c-b=2\end{cases}$$

证明：
$$\begin{cases}a=2k\\\frac{a^2}{2}=2k^2\end{cases}$$

$$\because c-b=2$$

$$\therefore \begin{cases}b=k^2-1\\c=k^2+1\end{cases}$$

$$\begin{cases}b^2=k^4-2k^2+1\\c^2=k^4+2k^2+1\end{cases}$$

$$a^2+b^2=c^2$$

而众所周知，当 $a<3$ 时一定会出现无理数，所以特判，直接输出 $-1$。

然后判断 $a$ 的奇偶性即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
void ji()
{
	long long a2=a*a;
	cout<<(a2-1)/2<<' '<<(a2+1)/2;
	return;
}
void ou()
{
	long long a2=a*a/2;
	cout<<(a2-2)/2<<' '<<(a2+2)/2;
}
int main(){
	cin>>a;
	if(a<3)
	{
		cout<<-1;
		return 0;
	}
	if(a%2!=0)
		ji();
	else 
		ou();
	return 0;
}
```

---

## 作者：Dimly_dust (赞：1)

此题为数论题，可通过查看样例得知。

- 共有三种规律，分别为：1和2、偶数，奇数。

1. 1和2

已知勾股定理最小的正整数为3、4、5。

那么1和2则是没有结果的（可以看【样例3】）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{

	long long a;
	cin>>a;
	if(a==1||a==2)
	{
		puts("-1");
		return 0;
	}
	return 0;
}
```
2. 偶数

求偶数的公式为：$x_2=\frac{x_1^2-1}{2},x_3=\frac{x_1^2+1}{2}$（具体样例看【样例2】）

```
#include<bits/stdc++.h>
using namespace std;
int main()
{

	long long a;
	cin>>a;
	if(a==1||a==2)
	{
		puts("-1");
		return 0;
	}
	if(a%2==0)
	{
		a/=2;
		cout <<a*a-1<<" "<<a*a+1<< endl;
	}

	return 0;
}
```
3.  奇数

求奇数的公式为$x_2=\frac{2x_1^2+2x_1}{2},x_3=\frac{2x_1^2+2x_1+1}{2}$

所以得到了以下AC代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{

	long long a;
	cin>>a;
	if(a==1||a==2)//特判1和2
	{
		puts("-1");
		return 0;
	}
	if(a%2==0)//处理偶数的情况
	{
		a/=2;
		cout <<a*a-1<<" "<<a*a+1<< endl;
	}
	else//处理奇数的情况
	{
		a/=2;
		cout<<2*a*a+2*a<<" " <<2*a*a+2*a+1<<endl;
	}

	return 0;
}
```


---

## 作者：Lemon_zqp (赞：0)

### 思路
首先，题目输入给我们一个正整数 $n$，那么 $n$ 就会有三种情况

- $n$ 是奇数
- $n$ 是偶数
- $n$ 小于等于 $2$

首先 $n$ 是奇数，我们通过样例就可以知道，第一个数是 $n^2 \div 2$ 向下取整，第二个数就是 $(n^2 \div 2) + 1$ 向下取整，我们可以拿一个数来验证，假设 $n$ 是 $5$，那么第一个数为 $5^2 \div 2$ 向下取整，第一个数就是 $12$，第二个数为 $(5^2 \div 2) + 1$ 向下取整，第二个数就是 $13$，按照 $a^2 + b^2 = c^2$，所以 $5^2 + 12^2 = 13^2$，通过拿数举例可以验证我们的结论是正确的。

那么 $n$ 是偶数，就先把 $n \div 2$，然后第一个数就是 $n^2 - 1$，第二个数就是 $n^2 + 1$，我们依然可以拿一个数验证，假设 $n$ 是 $8$，那么第一个数就是 $4^2 - 1$，第二个数就是 $4^2 + 1$，那么第一个数就是 $15$，第二个数就是 $17$，按照 $a^2 + b^2 = c^2$，所以 $8^2 + 15^2 = 17^2$，所以这个结论也是正确的。

最后如果 $n$ 小于等于 $2$，那么就没有解，输出 ``-1`` 即可。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	long long n;
	cin >> n;
	if(n <= 2)
	{
		cout << -1;
		return 0;
	}
	if(n % 2 != 0)
	{
		cout << (n * n) / 2 << " " << ((n * n) / 2) + 1;
	}
	else if(n % 2 == 0)
	{
		n /= 2;
		cout << (n * n) - 1 << " " << (n * n) + 1;
	}
	return 0;
}
```


---

## 作者：Nwayy (赞：0)

# solution 勾股变式

- 求勾股数的分类讨论问题，以下称 $a$ 均为输入的数。

- 我们知道勾股定理的基本式子 $a^2+b^2=c^2$，同时这个式子可以化成 $(m^2-n^2)^2+ (2 \cdot m \cdot n)^2=(m^2+n^2)^2$ 的形式，正确性证明如下：

1. 将式子左边拆开得 $m^4-2m^2n^2+n^4+4m^2n^2$，进一步化简可得 $m^4+2m^2n^2+n^4$。

1. 将式子右边拆开得 $m^4+2m^2n^2+n^4$，式子左右两边相等。

- 那么我们可以进一步推导：对于此式子中 $(2 \cdot m \cdot n)^2$ 的部分，**由于有 $2$ 这个因子，所以这玩意肯定是 $2$ 的倍数，即偶数。也就是说，在一组勾股数中，至少存在一个数是偶数**：

# solution 奇数

- 当输入为奇数时，除了 $1$ 之外，此时有 $a^2=b+c$，显然 $a$ 不满足 $2mn$ 的形式，也不是最大的，因此 $a$ 只能符合 $m^2-n^2$ 的形式，我们进行进一步推导。

1. $m^2-n^2$ 利用平方差公式可变为 $(m-n) \cdot (m+n)$，而要使这个式子是一个奇数，因此 $m+n$ 与 $m-n$ 都为奇数。把一种可能的情况带入：即考虑 $m+n=a,m-n=1$ 的情况。

1. 在这种情况下，根据初中数学知识求解二元一次方程组，可得 $m= \frac {a+1}{2} $，$n= \frac {a-1}{2}$。

1. 此时我们用含 $a$ 的式子代入前面推导的式子，可以发现式子左右两边仍然相等。**总结一下：对于奇数，存在一种情况使得 $m+n=a,m-n=1$，我们可以解出 $m$ 与 $n$，然后代入计算即可得出 $b$ 和 $c$。**

# solution 偶数
- 当输入为偶数时，这个偶数肯定满足 $2mn$ 的形式，因此我们假设这个偶数就是这组勾股数中的 $2mn$，依旧进一步推导：

1. 此时我们可以得出 $m \cdot n = \frac {a}{2}$，因此我们尝试一种特殊情况，即 $m=\frac{a}{2},n=1$，此时我们代入上面的式子发现依旧能够成立。

1. **总结一下：对于偶数，存在一种情况使得 $m=\frac{a}{2},n=1$，计算得出 $m$ 和 $n$ 代入 $b$ 和 $c$ 就能求出这组勾股数**。

# solution 特判

- ~~根据常识~~我们可以知道 $1$ 和 $2$ 是没有对应勾股数的，特判即可。

- 代码不提供，关键是你要看懂为什么这样求。


---

## 作者：Mine_King (赞：0)

tile:

- 洛谷：题解 CF1385E 【Directing Edges】
- 博客园：【做题笔记】题号 题目名称

[在我的博客获得更好的阅读体验](博客文章链接)

## Problem

[CF707C Pythagorean Triples](https://www.luogu.com.cn/problem/CF707C)

**题目大意：**

给你一个正整数 $n$，求另外两个正整数使得这三个数是一组勾股数。

## Solution

## Solution

我们知道勾股数满足 $a^2+b^2=c^2$，那么我们不妨设 $a=n$。则有：
$$
a^2=c^2-b^2=(c+b)(c-b)
$$
因为 $a,b,c$ 都是正整数且 $b<c$，所以有：
$$
\left\{
\begin{array}{l}
c+b=a^2 \\
c-b=1
\end{array}
\right.
$$
解得：
$$
\left\{
\begin{array}{l}
b=\dfrac{a^2-1}{2} \\
c=\dfrac{a^2+1}{2}
\end{array}
\right.
$$
但是我们发现一个问题：当且仅当 $a$ 为奇数时，$b,c$ 为整数。那 $a$ 为偶数咋办？

我们知道一个结论：若 $a,b,c$ 是一组勾股数，$d$ 是一个正整数，则 $a \times d,b \times d,c \times d$。

那么我们可以对于原来的 $n$，把它的因数 $2$ 都提出来，也就是让 $n = m \times 2^k$ 且 $m$ 是奇数。那么我们可以构造出两个数与 $m$ 组成一组勾股数。然后再让这两个数 $\times 2^k$ 即可。

那什么时候无解呢？$n \le 2$ 时无解。

证明：当 $n=1$ 时，显然 $n$ 只能作为勾或股。那么我们按上面的方法另 $a=n=1$，则：
$$
\left\{
\begin{array}{l}
c+b=1 \\
c-b=1
\end{array}
\right.
$$
解得 $b=0$ 不符合题意。故 $n=1$ 时无解。  
因为 $2=1 \times 2$，而 $n=1$ 无解，故 $n=2$ 时也无解。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m=1;
int main()
{
	scanf("%lld",&n);
	if(n<=2){puts("-1");return 0;}
	while(n>4&&n%2==0) n/=2,m*=2;
	if(n==4) printf("%lld %lld",3*m,5*m);
	else printf("%lld %lld\n",(n*n-1)/2*m,(n*n+1)/2*m);
	return 0;
}
```

---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF707C)】

## Analysis
- 我们都知道 $(3,4,5)$ 是最小的一组勾股数，那么如果有一个数是他们中任意一个数的倍数，那我们可以求出另外的两个数使他们构成勾股数

来看几组数据
```
3 4 5
5 12 13
7 24 25
9 40 41
```

发现了什么？

- 当$(a,b,c)$是一组勾股数且$a$是奇数时，有$ b= \dfrac{a^2-1}{2} ,c=\dfrac{a^2+1}{2}$

这只是一个猜想，我们可以证明

---

$ \because a$ 是奇数

$\therefore b= \dfrac{a^2-1}{2} ,c=\dfrac{a^2+1}{2}$ 是整数

$\because a^2+(\dfrac{a^2-1}{2})^2=(\dfrac{a^2+1}{2})^2$

$\therefore a^2+b^2=c^2$

$\therefore (a,b,c)$ 是一组勾股数

---
那如果 $a$ 不是奇数怎么办呢？

我们发现 $(6,8,10)$ 这一组数是勾股数，并且每一个数都是 $(3,4,5)$ 对应数的 $2$ 倍
  
- 当 $(a,b,c)$ 是一组勾股数时，对于任意一个正整数 $n$ ,都有 $(na)^2+(nb)^2=(nc)^2$ 

这个很好证明

- 如果输入的数不是 $2$ 的整次幂，那么我们既可以把它处理成奇数，然后按照上面的方法求出勾股数，最后乘回去就好啦
- 如果输入的数是 $2$ 的整次幂，因为 $(3,4,5)$ 是最小的一组勾股数，那么它必定是 $4$ 的倍数，那么我们就能变成 $(3,4,5)$ 这一组数，然后乘回去就好了

最后注意特判一下输入的数小于 $3$ 的时候要输出$-1$

## Code
```cpp
#include<cmath>
#include<queue>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
inline int Readint(void){
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=s*10+c-48;c=getchar();}
	return s*f;	
}
int n;
signed main(void){
	n=Readint();
	if(n<=2){
		printf("-1\n");
		return 0;
	}
	if(n%2==0){
		int temp=0;
		while(n%2==0){
			n/=2;
			temp++;
		}
		temp=(1<<temp);
		if(n==1){
		    printf("%lld %lld\n",temp/4*3,temp/4*5);
		    return 0;
		}
		printf("%lld %lld\n",(n*n-1)/2*temp,(n*n+1)/2*temp);
	}
	else printf("%lld %lld\n",(n*n-1)/2,(n*n+1)/2);
	return 0;
}
```

---

