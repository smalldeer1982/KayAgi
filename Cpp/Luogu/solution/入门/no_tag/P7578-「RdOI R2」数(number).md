# 「RdOI R2」数(number)

## 题目描述

试求出两两不同的三个正整数 $x,y,z(x\gt y\gt z)$ 使得其中的任意两个数的和能被第三个数整除。

现在给出你下面的几种要求：

- 给出你 $x-y$ 的值，求出 $x,y,z$。
- 给出你 $x-z$ 的值，求出 $x,y,z$。
- 给出你 $y-z$ 的值，求出 $x,y,z$。

## 说明/提示

**样例解释**

由 $x-y=1$ 得 $x,y$ 差 $1$ ，经尝试，得 $x=3,y=2,z=1$。

此时显然有 $z\mid (x+y)$，$y\mid (x+z)$，$x\mid (y+z)$。

---

**数据范围**

- 对于 $1\%$ 的数据，即样例 \#1。
- 对于 $100\%$ 的数据，$1\le T\le 10^6,1\le x,y,z\le10^8$。

## 样例 #1

### 输入

```
1
x-y 1```

### 输出

```
3 2 1```

# 题解

## 作者：Thomas_Cat (赞：24)

签到题。

由题意知道题目中由三种输入方式分别为是 $x-y,x-z,y-z$ 其中  $(x>y>z)$。

因此题目可以简化为：

得出 $x-y,x-z,y-z$ 中任意一个并且按照题目中所给的比例求出 $x,y,z$ 即可，$x,y,z$ 即为 $3:2:1$ 的关系。

一些证明：（设 $a-b,b-c=1$）

任何一个比例 $a:b:c$ 都可以化成 $1:\dfrac{b}{a}:\dfrac{c}{a}$。

任何一个满足条件的比例都可以写成 $1:a:b \times a-1$，因为 $\dfrac{(b \times a-1+1)} {a} = b$。

$b$ 是一个整数，所以最后就是要 $ba-1$ “整除” $a+1$

显然 $a+1 \ge ba-1$


那么 $(b-1)a \le 2$

$b$ 是整数，而且这里 $a>1$ ，那么 $b$ 就是 $2$ 或 $1$。

因为 $1<a<b\times a-1$，所以如果 $b=1$ , 那么则有 $1<a<a-1$，矛盾。

所以 $b$ 只能是 $2$ ，于是转化为一个 $2a-1$“整除”$a+1$。

注意 $2a-1$ 除以 $a+1$ 的值不可能大于等于 $2$，所以 $2a-1=a+1$，解出 $a = 2$。

于是最后得到的比例就是：$1:2:3$。

也就是 $b \times a = 1 = 2 \times 2 - 1 = 3$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    unsigned long long t;
    cin>>t;
    while(t--){
        string s;
        unsigned long long n;
        cin>>s>>n;
        if(s=="x-y")
            cout<<3*n<<' '<<2*n<<' '<<n<<endl;
        if(s=="y-z")
            cout<<3*n<<' '<<2*n<<' '<<n<<endl;
        if(s=="x-z")
            cout<<3*n/2<<' '<<2*n/2<<' '<<n/2<<endl;
    }
    return 0;
}
```

---

## 作者：地狱石QAQ (赞：16)

## 题目

一道**签到题**。

[点击查看P7578](https://www.luogu.com.cn/problem/P7578)

## 解题思路

首先看下题目，在 $ x, y, z $ 中，**任意两个数的和能被第三个数整除**。

我们可以通过推出 $ x, y, z $ 的**比例关系**来求出这三个数。

首先，因为 $ x > y > z $ ，我们可以得出 $ y + z < 2x $ 。因为 $ y + z $ 能被 $ x $ 整除，所以只能 $ y + z = x $ 。

我们设 $ z = k $ 。那么易得 $ x = y + k $ 。所以 $ x + z = y + 2 × k $ 。由题意可得 $ x + z $ 为 $ y $ 的倍数，则 $ 2 × k $ 为 $ y $ 的倍数。

此时， $ z $ 的值为 $ k $ 。因为 $ y > z $ ，所以 $ y $ 只能为 $ 2 × k $ 。那么， $ x $ 就是 $ 3 × k $ 了。

综上所述， $ x : y : z = 3 : 2 : 1 $ 。

剩下代码自己敲。

## AC代码

```cpp
#include <iostream>
using namespace std;

long long t, x;
string s;

int main()
{
    cin >> t;
    for( long long i = 1; i <= t; i++ )
    {
        cin >> s >> x;
        if( s == "x-y" )
        {
            cout << 3 * x << " " << 2 * x << " " << x << endl;
        }
        else if( s == "x-z" )
        {
            cout << 3 * x / 2 << " " << 2 * x / 2 << " " << x / 2 << endl;
        }
        else
        {
            cout << 3 * x << " " << 2 * x << " " << x << endl;
        }
    }
    return 0;
}
```

---

## 作者：Aw顿顿 (赞：3)

## 题意

任意两数的和都能被另一个数整除，即：

- $x|(y+z)$
- $y|(x+z)$
- $z|(x+y)$

于此同时，满足 $x>y>z$。

## 解法

首先，存在 $1<y<x$ 和 $1<z<x$，简单合并可以发现显然有 $1<y+z<2x$。同时我们已知 $y+z$ 是 $x$ 的因数，不难发现 $y+z=x$ 是符合条件的。

用类似的手法对 $y$ 进行处理，最后得到 $x:y:z=3:2:1$。

然后就很容解决这道题了。

## 实现

令输入值为 $k$，对于三种情况，有：

- $k=x-y$，输出 $3k,2k,k$。
- $k=y-z$，输出 $3k,2k,k$。
- $k=x-z$，输出 $\frac{3}{2}k,k,\frac{1}{2}k$。

细节处理上，注意字符串判读与常数优化。




---

## 作者：Scrutiny (赞：3)

简单小学数论题，主要考察整除的基本性质.

根据题目描述，我们有

$$\begin{cases}x\mid (y+z)\\y\mid (x+z)\\z\mid (x+y)\end{cases}$$

，其中 $x>y>z.$

容易知道，$0<y+z<2x$，故 $y+z=x.$

将上式代入 $y\mid(x+z)$ 中，得 $y\mid (y+2z)\Rightarrow y\mid 2z.$

由于 $y>z$，因此只能 $y=2z.$

所以，一切满足条件的 $(x,y,z)$ 为 $(3k,2k,k)$，其中 $k\in\mathbb{Z^+}.$

将输入所给的条件带入即可.

Sample Code(C++11):

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io
{
	const int SIZE = 1 << 22 | 1;
	char iBuf[SIZE], *iS, *iT, c;
	char oBuf[SIZE], *oS = oBuf, *oT = oBuf + SIZE;
	#define gc() (iS == iT ? iT = iBuf + fread(iS = iBuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	template<class I> void gi(I &x)
	{
		int f = 1;
		for(c = gc(); c < '0' || c > '9'; c = gc())
			if(c == '-') f = -1;
		for(x = 0; c >= '0' && c <= '9'; c = gc())
			x = (x << 3) + (x << 1) + (c & 15);
		x *= f;
	}
	inline void flush()
	{
		fwrite(oBuf, 1, oS - oBuf, stdout);
		oS = oBuf;
	}
	inline void putc(char x)
	{
		*oS++ = x;
		if(oS == oT) flush();
	}
	template<class I> void print(I x)
	{
		if(x < 0) putc('-'), x = -x;
		static char qu[55];
		char *tmp = qu;
		do *tmp++ = (x % 10) ^ '0'; while(x /= 10);
		while(tmp-- != qu) putc(*tmp);
        putc(' ');
	}
	template<class I> void println(I x)
	{
		if(x < 0) putc('-'), x = -x;
		static char qu[55];
		char *tmp = qu;
		do *tmp++ = (x % 10) ^ '0'; while(x /= 10);
		while(tmp-- != qu) putc(*tmp);
        putc('\n');
	}
	struct flusher{ ~flusher() { flush(); } }_;
}
using io :: gi;
using io :: putc;
using io :: print;
using io :: println;
int t,a;
char c;
int main(){
    scanf("%d\n",&t);
    while(t--){
        c=getchar();
        if(c=='x'){
            c=getchar();
            c=getchar();
            scanf("%d\n",&a);
            if(c=='y'){
                print(3*a);print(2*a);println(a);
            }
            else{
                print(3*a/2);print(a);println(a/2);
            }
        }
        else{
            c=getchar();
            c=getchar();
            scanf("%d\n",&a);
            print(3*a);print(2*a);println(a);
        }
    }
    return 0;
}
```


---

## 作者：zplqwq (赞：2)

验题人来写个题解。

是个数论题没错。

结论：$x:y:z=3:2:1$。

证明：

首先根据题目可得：
 $$ \left\{
\begin{aligned}
x∣(y+z) \\
y∣(x+z) \\
z∣(x+y)
\end{aligned}
\right.
$$

我们知道 $1<y+z<2x$ 且 $z∣(x+y)$， 因此 $x=y+z$。

带入 $y∣(x+z)$ 可得 $y|2z$。

因为 $y>z$， 所以我们可以令 $y=2z$。

带入 $x=y+z$ 可得 $x=3z$。

因此 $x:y:z=3:2:1$。

综上所述，可得出以下结论：

当输入 $x-y$ 时，我们输出 $3n,2n,n$。

当输入 $y-z$ 时，我们输出 $3n,2n,n$。

当输入 $x-z$ 时，我们输出 $3\times \frac{n}{2},2\times \frac{n}{2},\frac{n}{2}$。






---

## 作者：int32 (赞：0)

### 前言

这题是一道数论签到题（？）。

### 思路

先给出结果：$x:y:z=3:2:1$.

证明如下：

由题可得: $x|(y+z),y|(x+z),z|(x+y).$

$\because 1<y+z<x+x=2x$ 且 $x|(y+z).$

$\therefore y+z=x.$

$\therefore y|[(y+z)+z]$ 即 $y|2z.$

又 $\because y>z.$

$\therefore y=2z.$

$\therefore x=3z.$

$\therefore x:y:z=3z:2z:z=3:2:1.$

证毕。

于是我们可以开始写代码了。

### 代码

1.79s (C++11 O2)

```cpp
#include<bits/stdc++.h>
using namespace std;
int cases;
int main(){
	cin>>cases;
	while(cases--){
		string how;
		int result;
		cin>>how>>result;
		int x=result*3, y=result*2, z=result;
		if(how=="x-y"||how=="y-z") printf("%d %d %d\n",x,y,z);
		else printf("%d %d %d\n",x/2,y/2,z/2);//仔细想想。
	}
	return 0;
}
```

麻烦管理员大大审核了。

---

