# [AGC036A] Triangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_a

整数 $ S $ が与えられます。 以下の条件をすべて満たす $ 6 $ つの整数 $ X_1,Y_1,X_2,Y_2,X_3,Y_3 $ を $ 1 $ 組求めてください。

- $ 0\ \leq\ X_1,Y_1,X_2,Y_2,X_3,Y_3\ \leq\ 10^9 $
- 二次元平面上の $ 3 $ つの点 $ (X_1,Y_1),(X_2,Y_2),(X_3,Y_3) $ を頂点とする三角形の面積が $ S/2 $ である。

なお、この問題の制約の範囲で、条件を満たすような $ 6 $ つの整数が必ず存在することが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ S\ \leq\ 10^{18} $
- 入力される値はすべて整数である。

### Sample Explanation 1

二次元平面上の $ 3 $ つの点 $ (1,0),(2,2),(0,1) $ を頂点とする三角形の面積は $ 3/2 $ です。 なお、`3 0 3 1 0 1` や、`1 0 0 1 2 2` という出力をしても正解と判定されます。

## 样例 #1

### 输入

```
3```

### 输出

```
1 0 2 2 0 1```

## 样例 #2

### 输入

```
100```

### 输出

```
0 0 10 0 0 10```

## 样例 #3

### 输入

```
311114770564041497```

### 输出

```
314159265 358979323 846264338 327950288 419716939 937510582```

# 题解

## 作者：Little_x_starTYJ (赞：5)

### 解题思路

这就是一道数学题好吧，本蒟蒻刚好学到。

一个顶点在 $(0,0)$ 的三角形,它的面积就是 $\frac12(x1 \times y2-x1 \times x2)$。

我们的坐标要尽可能小，所以我们可以把 $x1$ 与 $y2$ 取值为 $\sqrt s$。

CODE：

```cpp
#include <stdio.h>
#include <math.h>
typedef long long ll;
int main() {
	ll s;
	scanf("%lld", &s);
	ll x1, y2;
	x1 = y2 = ceil(sqrt(s));
	ll x2 = x1 * y2 - s;
	printf("0 0 %lld %lld 1 %lld", x1, x2, y2);
	return 0;
}
```

---

## 作者：Limit (赞：5)

# 题目大意

在一个 $10^9\times10^9$ 的平面上,需要找到三个**整点**,使得三点构成的三角形的面积 $=\frac{S}{2}$.

# 分析

对于 $S\leq 10^9$ 显然可以直接放在 $\{(0,0),(s,0),(s,1)\}$,不多展开.

如果构造出来的三角形有一条边是与坐标平行的话显然 $S$ 就必须要是这条边长度的位置,且这条边的长度必定是在 $1$ 到 $10^9$ 范围内的整数,显然是不能满足于所以的 $S$ 的.所以需要换一种想法去构造.

使用与所有平面上的三角形的面积公式除了海伦公式,还会想到一个 $\texttt{面积}=\frac{\texttt{水平宽}\times\texttt{铅垂高}}{2}$,在这里也就是 $S=$ 水平宽$\times$ 铅垂高,因为水平宽必定是整数,所以可以很自然地得出铅垂高 $=\frac{S}{\texttt{水平宽}}$,将铅垂高的整数部分和小数部分分别表示为 $a,b$,也就是说 $a=\lfloor\frac{S}{\texttt{水平宽}}\rfloor$,因为 $a$ 要在 $1$ 到 $10^9$ 的范围内,所以可以将水平宽取到 $10^9$,那么 $b=\frac{S\bmod 10^9}{10^9}$,也就是需要构造出 $1\times 10^{-9},2\times 10^{-9},3\times 10^{-9},\dots,(10^9-1)\times 10^{-9}$,那么也可以想到连接 $(0,0)$ 与 $(10^9,1)$ 的线段,在这条线段上恰好包含了上面所以的小数,而高度可以直接整除得到,于是可以构造出 $\{(0,0),(10^9,1),(10^9-S\bmod 10^9,\lfloor\frac{S}{10^9}\rfloor+1)\}$.(不理解可以画图理解).

以上做法在 $S=10^{18}$ 的时候计算出来的高度大于了 $10^9$,所以需要特判这种情况.

# 代码

核心代码就三行,没啥必要了吧.

---

## 作者：cff_0102 (赞：3)

首先假设 $x_1,y_1,x_2,y_2,x_3,y_3$ 可以小于 $0$，它们的绝对值小于等于 $10^9$。

众所周知，三个顶点分别在 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$ 的三角形面积可以用 $\frac{1}{2} \begin{vmatrix} x_1 & y_1 & 1 \\ x_2 & y_2 & 1 \\ x_3 & y_3 & 1 \end{vmatrix}=\frac{1}{2}|(x_1y_2+x_2y_3+x_3y_1)-(x_1y_3+x_2y_1+x_3y_2)|$ 来表示。

所以，只需要找到符合题意的 $x_1,y_1,x_2,y_2,x_3,y_3$，使得 $\frac{1}{2}|(x_1y_2+x_2y_3+x_3y_1)-(x_1y_3+x_2y_1+x_3y_2)|=\frac12S$，即 $|(x_1y_2+x_2y_3+x_3y_1)-(x_1y_3+x_2y_1+x_3y_2)|=S$ 就可以了。

要是其中一个点在原点呢？那么原式就可以变成 $|x_1y_2-x_2y_1|=S$。

接下来，再设 $x_2=10^9,y_2=1$，且 $x_1y_2-x_2y_1\ge0$，则原式变为 $x_1-10^9y_1=S$。

很明显，对于一个范围为 $[1,10^8]$ 的 $S$，它必然可以表示为 $10^9a+b$，其中 $a,b$ 都小于等于 $10^9$。所以，此时 $x_1$ 取 $b$，$y_1$ 取 $-a$ 是一定可以的。

那么，若 $x_1,y_1,x_2,y_2,x_3,y_3$ 可以小于 $0$，最后的答案就是 $A(b,-a),B(10^9,1),C(0,0)$，其中 $a=\lfloor\frac{S}{10^9}\rfloor,b=S\bmod10^9$。

但是现在 $x_1,y_1,x_2,y_2,x_3,y_3$ 不能小于 $0$，应该怎么办呢？也很简单，只需要把整个三角形平移一下，变成 $A(b,0),B(10^9,a+1),C(0,a)$ 即可。当 $S=10^{18}$，$a+1$ 会超出范围，但是也没关系，特判一下在此时输出 $A(0,0),B(0,10^9),C(10^9,0)$ 即可。

```python
a=int(input())
if(a==1000000000000000000):
    print("0 0 0 1000000000 1000000000 0")
else:
    print(a%1000000000,0,1000000000,1+a//1000000000,0,a//1000000000)
```

---

## 作者：_xiaxii (赞：2)

# [题意传送门](https://www.luogu.com.cn/problem/AT_agc036_a)

## 题意理解

输入一个整数 $S$，找出一个以面积为 $\dfrac{1}{2} S$ 的三角形的顶点坐标。

## 思路一
题目说明了 $1 \le S \le 10^{18} $，并且限制了 $0\le X_1,X_2,X_3,Y_1,Y_2,Y_3 \le 10^9$ 且均为整数，我们自然会想到以  $\left({0,0}\right),\left(\lfloor{\sqrt{S}\rfloor-k,0}\right),\left({0,\frac{S}{\lfloor{\sqrt{S}}\rfloor-k}}\right)$ 且 $S \bmod \lfloor{\sqrt{S}}\rfloor-k =0$ 为顶点的三角形。

将 `i` 从 $ \sqrt{S}$ 向前遍历，如果 $S\bmod i=0$ 则为找到的坐标。

时间复杂度是 $\mathcal O(\sqrt{S})$，会超时。
```cpp
#include <bits/stdc++.h>
using namespace std;

long long s,a,b;

void f(long long s)
{
    for(int i=sqrt(s);i>=1;i--)
    {
        if(s%i==0)
        {
            a=i;
            b=s/i;
            break;
        }
    }
}

int main()
{
    cin>>s;
    if(s<=1000000000)//若S小于10^9，则(0,0),(s,0),(0,1)也符合要求
		printf("0 0 1 0 0 %d\n",s);
	else
	{
    	f(s);
    	printf("0 0 %lld 0 0 %lld\n",a,b);
    }
}
```
实测[TLE](https://www.luogu.com.cn/record/91699094)。

## 思路二
这很显然是一道数学题。~~初中的时候~~我们学过，**有一个顶点在原点**的三角形的面积为 $\frac{1}{2}\times \lvert {X_1Y_2-X_2Y_1}\rvert$。

为了使坐标最小，我们可以将 $X_1$ 与 $Y_2$ 取 $\sqrt{S}$，由于题目限制了坐标为整数，所以还要加一个向上取整。

于是 $X_2Y_1$ 便可以由 $X_1Y_2-S$ 计算出来。剩下的数已经很小了，所以可以将 $X_2$ 直接赋值为 $X_1Y_2-S$，且 $Y_1=1$。

因此时间复杂度降到了 $\mathcal O(1)$。
```cpp
#include <bits/stdc++.h>
using namespace std;

long long s;

int main()
{
    cin>>s;
    long long x1,x2,y2;
    x1=ceil(sqrt(s));
    y2=x1;
    x2=x1*y2-s;//由于x1与y2是向上取整，所以x1*y2就会大于S
    printf("0 0 %d %d 1 %d",x1,x2,y2);
}
```
实测[满分](https://www.luogu.com.cn/record/91701002)。

本[蒟蒻](https://www.luogu.com.cn/user/728002)的第五篇题解。

---

## 作者：离散小波变换° (赞：2)

## 题解

注意到对于平面上任意一个三角形，对它进行平移和翻转不会改变其面积。于是总是可以将其中一个点移动到原点 $(0, 0)$ 处而不会使其变得不合法。所以先确定 $(x_1,y_1)=(0,0)$。

当一个点为原点时，就很容易算出三角形面积了。可以将其补成矩形再减去多余的部分，也可以直接使用叉积，得出三角形面积的两倍为：

$$|(x_2-x_1,y_2-y_1)\times (x_3-x_1,y_3-y_1)|=|x_2y_3-y_2x_3|$$

那么我们要构造 $(x_2,y_2)$ 和 $(x_3,y_3)$ 使得 $x_2y_3-x_3y_2=S$。

注意到 $S\le 10^{18}$ 很大，而我们可以使用的坐标的范围为 $[0,10^9]$。考虑将 $S$ 看作一个 $10^9$ 进制的数，分解成 $S=a\times 10^9+b$，进而凑成 $S=(a+1)\times 10^9 -(10^9-b)$。当 $S<10^{18}$ 时，$0\le a,b<10^9$ 拆出来的四个数 $(x_2,y_2)=(10^9,1)$，$(x_3,y_3)=(10^9-b,a+1)$ 都在 $[0,10^9]$ 内；当 $S=10^{18}$ 时直接取 $x_2=y_3=10^9$，$x_3=y_2=0$ 即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int E09 = 1000000000;
const i64 E18 = 1000000000000000000ll;
int main(){
    i64 S; cin >> S;
    if(S == E18)
        printf("0 0 %d 0 0 %d\n", E09, E09);
    else {
        int a = S / E09;
        int b = S % E09;
        printf("0 0 %d %d %d %d\n", E09, 1, E09 - b, a + 1);
    }
    return 0;
}
```

---

## 作者：___cjy__ (赞：0)

# [AGC036A] Triangle 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_agc036_a)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-at-agc036-a)

### 题目大意：

求三个在 $10^9$ 以内的点坐标使得它们围成的三角形面积为 $\dfrac{S}{2}$。

### 正文：

一道不难想的数学题。

简单地，令三角形的一个顶点在 $(0,0)$，则三角形的面积就为 $\dfrac{1}{2}|x_1y_2-x_1x_2|$，$S=|x_1y_2-x_1x_2|$。

显然，最简单的方法就是直接构造一组符合条件的三角形。可以考虑令
$$x_1=y_2=\lceil\sqrt S\rceil$$
则
$$x_2=x_1y_2-S$$
$$y_1=1$$
为合适的一组解。

最后直接输出即可。

### AC Code：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int s, t;

signed main(){
	cin >> s;
	t = ceil(sqrt(s));
	//x1 = y2 = t, x2 = t * t - s, y1 = 0
	cout << "0 0 " << t << " 1 " << t * t - s << " " << t << endl;
	
	return 0;
}
```

---

## 作者：_zhx (赞：0)

# AT_agc036_a [AGC036A] Triangle 题解

##  题目大意

给定 $S$，求面积为 $\frac{S}{2}$ 的三角形三点坐标。

### 题目思路

一个顶点在 $(0,0)$ 的三角形,它的面积是 $(x1\times y2-x1\times x2)\div2$。

所以我们只用求出 $x1$、$x2$、$y2$。

（我喜欢用 $a$、$b$、$c$）

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,a,b,c;//十年OI一场空，不开 long long 见祖宗
    cin>>n;
    c=a=ceil(sqrt(n));
    b=a*c-n;
    printf("0 0 %lld %lld 1 %lld",a,b,c);
    return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/AT_agc036_a)

## 思路

一道数学题。

有一个顶点在 $(0,0)$ 的三角形,它的面积是$(x1\times y2-x1\times x2)\div2$。

我们的坐标要尽量的小，这一步可以把 $x1$ 和 $y2$ 取 $\sqrt{S}$。

但是，因为题目的限制，还要加个 ``ceil()`` 函数。

## 代码

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll S;
    cin>>S;
    ll X1,X2,Y2;
    X1=ceil(sqrt(S));
    Y2=X1;
    X2=X1*Y2-S;
    printf("0 0 %d %d 1 %d",X1,X2,Y2);
    return 0;
}
```


---

