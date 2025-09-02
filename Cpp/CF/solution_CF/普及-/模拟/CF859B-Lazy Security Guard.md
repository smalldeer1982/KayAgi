# Lazy Security Guard

## 题目描述

Your security guard friend recently got a new job at a new security company. The company requires him to patrol an area of the city encompassing exactly $ N $ city blocks, but they let him choose which blocks. That is, your friend must walk the perimeter of a region whose area is exactly $ N $ blocks. Your friend is quite lazy and would like your help to find the shortest possible route that meets the requirements. The city is laid out in a square grid pattern, and is large enough that for the sake of the problem it can be considered infinite.

## 说明/提示

Here are some possible shapes for the examples:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF859B/5e7ebb69b8e66ba58196d654a3513a2ca92c6a2a.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
11
```

### 输出

```
14
```

## 样例 #3

### 输入

```
22
```

### 输出

```
20
```

# 题解

## 作者：cff_0102 (赞：1)

面积确定为 $n$，求周长最小。所以肯定长宽越接近越好，也就是越接近正方形越好。

$(\lfloor\sqrt n\rfloor)^2\le n \le (\lceil\sqrt n\rceil)^2$，所以答案一定是 $\lfloor\sqrt n\rfloor\times4$ 或 $\lfloor\sqrt n\rfloor\times2+\lceil\sqrt n\rceil\times2$ 或 $\lceil\sqrt n\rceil\times4$ 中的一个。

接下来分类讨论，这样思路更清晰。

- 当 $n$ 是完全平方数，即 $(\lfloor\sqrt n\rfloor)^2=n$ 时，答案就是 $\lfloor\sqrt n\rfloor\times4$。
- 如果 $n$ 不是完全平方数，此时 $\lceil\sqrt n\rceil=\lfloor\sqrt n\rfloor+1$，继续分类讨论：
  - 当 $(\lfloor\sqrt n\rfloor)^2<n\le\lfloor\sqrt n\rfloor\times(\lfloor\sqrt n\rfloor+1)$，则通过小学两年级半就学过的通过平移边求周长的方法，能够拼成一个 $\lfloor\sqrt n\rfloor\times\lceil\sqrt n\rceil$ 的矩形，答案是 $\lfloor\sqrt n\rfloor\times2+\lceil\sqrt n\rceil\times2$，或者也可以说是 $\lfloor\sqrt n\rfloor\times2+(\lfloor\sqrt n\rfloor+1)\times2=\lfloor\sqrt n\rfloor\times4+2$。
  - 当 $\lfloor\sqrt n\rfloor\times(\lfloor\sqrt n\rfloor+1)<n<(\lceil\sqrt n\rceil)^2$，通过小学两年级半学的平移边求周长的方法，能拼成一个 $\lceil\sqrt n\rceil\times\lceil\sqrt n\rceil$ 的正方形，答案就是 $\lceil\sqrt n\rceil\times4$，或者 $(\lfloor\sqrt n\rfloor+1)\times4=\lfloor\sqrt n\rfloor\times4+4$。
- 再把这些合并起来，答案就是 $\lfloor\sqrt n\rfloor\times4+
\left\{
\begin{aligned}
&0\ \ \ \ \ (\lfloor\sqrt n\rfloor\times\lfloor\sqrt n\rfloor=n) \\
&4\ \ \ \ \ (\lfloor\sqrt n\rfloor\times(\lfloor\sqrt n\rfloor+1)<n) \\
&2\ \ \ \ \ \text{otherwise}
\end{aligned}
\right.
$。

`C++` 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	int s=sqrt(n);//用 floor(sqrt(n)) 来判断并顺便来存储答案 
	if(s*s==n) s=s*4;//floor(sqrt(n))*4
	else if(s*(s+1)<n) s=s*4+4;//floor(sqrt(n))*4+4
	else s=s*4+2;//floor(sqrt(n))*4+2
	cout<<s;//别忘了输出 
	return 0;
}
```


---

## 作者：TLEWA (赞：1)

贪心地想，相同面积下，一个图形越接近正方形周长就越小（显而易见），所以我们就可以把问题变成凑一个最接近正方形的图形并计算出面积了。

如果要凑出一个最接近正方形的图形，短边就为 $\left\lfloor\sqrt{n}\right\rfloor$，而长边就为 $n \div \sqrt{n}$，周长即为短边乘上长边再乘以二。但是长边这里存在不能整除的情况，直接向上取整即可。如：

![](https://cdn.luogu.com.cn/upload/image_hosting/7xnrfb4k.png)

我们可以将其变为：

![](https://cdn.luogu.com.cn/upload/image_hosting/6rj9exa2.png)

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int sn=sqrt(n);
	int cn=n/sn+(bool)(n%sn); //需要向上取整 
	cout << (sn+cn)*2;
	
	return 0;
}
```


---

## 作者：翼德天尊 (赞：1)

有一个众所周知的结论：在面积一定的情况下，相比于长方形，正方形的周长最小。

所以我们要尽可能的凑正方形。

于是我们可以肯定，短边的长一定为下取整的 $\sqrt{n}$，那么长边的长就是 $n\div $短边。

……？真的是这样吗？

我们可以很清楚的发现，我们求出的短边的长不一定会被 $n$ 整除，所以说长边的长的答案也需要我们分类讨论：

1. 如果可以整除，则长边的答案即为上述式子。

2. 如果不行，那么长边的答案即为上述式子的值 $+1$。（c++自带的下取整；当然 $+1$ 也可以改为上述式子的值的上取整）

所以代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
	scanf("%d",&n);
	a=sqrt(n),b=n/a;
	if (n%a) printf("%d\n",(a+b+1)*2);
	else printf("%d\n",(a+b)*2);
	return 0;
}
```


---

## 作者：159号程序员 (赞：1)

简单数论+模拟。

首先我们知道，需要把 $n$ 个正方形平成周长最小的。

给定 $n$ 后，可以发现，$\sqrt{n}$ 就是长方形的边长（具体看图）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF859B/5e7ebb69b8e66ba58196d654a3513a2ca92c6a2a.png)

如果长是 $\sqrt{n}$，那么宽就是 $n \div \text{长}$。

如果正好能组成长方形，那么就直接公式 $(\text{长}+\text{宽}) \times 2$。

如果不能，只能再加两条外露的边， $(\text{长}+\text{宽}+1) \times 2$.

_AC Code_

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int a = sqrt(n);
	int b = n / a;
	if (!(n % a)) cout << (a + b) * 2; //可以组成长方形，直接公式
	else cout << (a + b + 1) * 2; //不可以组成，需要+1。
	return 0;
}
```

---

## 作者：mcDinic (赞：0)

[也许会更好的阅读体验](https://www.cnblogs.com/yjy-3054188405/p/16494941.html)

~~一道橙题而已，各种乱搞都能过~~

### 玄学做法登场

看到题解区的大佬千篇一律，都简单分析做了一下，核心代码仅三行，蒟蒻打算给题解增加些新鲜的血液（虽说运行效率低点，但足以通过本题）。

首先，要周长最短，肯定不能让三个正方形拼成凹进去的样子，这样会让周长更长，肯定不是最优解。所以，把每条边进行适当平移后，一定能**拼成一个矩形的轮廓**。

接下来，我们为了取到最优值，就要看 $m$ 个正方形拼成的矩形的周长最小是多少（ $n \le m$，$m\in Z$，令这个值是 $a_m$ ），答案就是 $\forall m,\min \lbrace a_m \rbrace$。

由于 $m$ 是需要能做到的，即它对应的矩形边缘处都要有正方形，就有 $m \le \lceil n \div 2 \rceil ^2$。但是这样还是不行的，$n \le 10^6$，时间爆掉，需要一些玄学优化。

如果正方形沿着边缘铺开很薄的几圈，和把它们铺成又窄又长的矩形无异，而我们可以很容易证明长宽越接近，周长越小。

于是我们可以推测，$m$ 比 $n$ 不会大多少，$n$ 最大是 $10^6$，盲猜一下最多大几千这样吧。这个我不会证，但是显然是正确的（至少在这么小范围是正确的，如果有人能证明出来符合条件的 $m$ 比 $n$ 大的值在某个多项式结果内，请联系作者，我会尽快补上过程）。

至于实现起来非常简单，即算出上文提到的 $a_m$ 就没问题了，若暴力判断时限有点紧，所以我就用了类似埃氏筛的东西算，具体见代码。

### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define linf 0x3f3f3f3f3f3f3f3f
#define inf 0x7fffffff
#define v e[i].y
using namespace std;
inline ll read(){
    char ch=getchar();ll x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();return x*w;
}
inline void write(ll x){
	if(x<0)x=-x,putchar('-');
    if(x<10){putchar(48+x);return;}
    write(x/10),putchar((x+10)%10+48);
}
int n,p[2000005],ans;
int main(){
    ans=inf;
    for(int i=1;i<=1e6+2000;i++){
        for(int j=i;j<=1e6+2000;j+=i)p[j]=max(p[j],min(j/i,i));
    }
    n=read();
    for(int i=n;i<=1e6+2000;i++)ans=min(ans,(i/p[i]+p[i])*2);
    write(ans);
    return 0;
}
```

---

## 作者：j1ANGFeng (赞：0)

### 分析
首先要知道，在同样面积下，正方形的周长比长方形小。

那么要使图形尽量为正方形，宽要为 $\sqrt{n}$ 向下取整，长为 $n$ 除以宽。

而 $n$ 不一定为完全平方数，我们分类讨论一下：

1. $n$ 为完全平方数，长为 $n$ 除以宽。

2. $n$ 不为完全平方数，长为 $n$ 除以宽 $+1$。
### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define ll long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}

signed main(){
	int n=rd(),m=sqrt(n);
	if(n%m)
	  wt((m+(n/m)+1)<<1);
	else wt((m+(n/m))<<1);
	return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

结论：面积一定时，正方形的周长小于长方形的周长。

思路：

根据结论，我们知道，要使正方形的数量多。所以短边的长为 $\sqrt{n}$ 向下取整，长边的长为 $n \div$ 短边的长。

又 $n$ 不一定是完全平方数，也就是 $\sqrt{n}$ 不一定能整除 $n$，所以要分类讨论：

1. 若 $\sqrt{n}$ 能整除 $n$，则长边为 $n \div$ 短边的长。

2. 若 $\sqrt{n}$ 不能整除 $n$，则长边的长为 $n \div$ 短边的长 $+1$（向上取整）。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

int main(){
	int n=read(),a=sqrt(n),b=n/a;
	if (n%a)write((a+b+1)*2);
	else write((a+b)*2);
	return 0;
}
```

闲话：通过快读快写跑出最优解第一。

---

## 作者：CH30S (赞：0)

~~好水的题。~~

[link](https://www.luogu.com.cn/problem/CF859B)



------------

- 思路

数学+分类讨论



------------
- 具体实现

首先，因为题目要求求出组成的长方形中最小的周长，所以我们就尽可能的贪心。又因为面积相同时，正方形周长比长方形的周长小，所以贪心策略就是尽可能组成正方形。

设长方形的长为 $a$，宽为 $b$ 。


如图，可以看出 $a$ 就是 $\sqrt{n} $ 。

可用 sqrt 函数

![](https://cdn.luogu.com.cn/upload/image_hosting/k3od9jng.png)

显然，b就是 $n  \div \sqrt{n}$

其次，开始分类讨论。

如果组成正方形时，$C=(a+b)\times 2$

否则我们就把它拼成一个最近似的正方形，在计算时把和加一或者式子的向上取整即可。$C=(a+b+1)\times 2$



------------
鸣谢@159号程序员 的画图思路

---

## 作者：xiaojuruo (赞：0)

## 分析
一共 $n$ 个正方形，让我们求最后拼出来的**最小**周长。那我们不妨看成有一个面积为 $n$ 的矩形，让我们来求他的长和宽。这是我们需要引入一个结论，矩形面积一定，正方形的周长一定比长方形小。
## 证明
我们设面积为 $S$ ,则长为 $a$ ,宽为 $S \div a$ ,周长为 $C$ ,则 $C= 2\times (a+S \div a)$ 。所以 $y$ 的一阶导数就为 $2 \times (1-s \div a^2)$ 。我们令此时 $y$ 的一阶导数为0，所以得出 $a= \sqrt{S}$ 。因为 $a$ 的值为 $\sqrt{S}$ ，所以宽的值也为 $\sqrt{S}$ 。所以正方形此时周长最小。
## AC代码
```cpp
#include <iostream>
#include <cmath>
long long x,y,n,sum;
int main(){
	std::cin>>n;
	x=sqrt(n);
	y=n/x;
	sum=x+y;
	if (n%x!=0) std::cout<<2*(sum+1);
	else std::cout<<2*(sum);
	return 0;
}
```


---

## 作者：dzy2008 (赞：0)

这道题目给出了 $n$ 个 $1 \times 1$ 的小正方形，求出组成的长方形中最小的周长。

我们的贪心策略就是把它尽量的组成一个正方形，周长最短。

因为相邻两个数一定互质并且我们 $C++$ 的取整功能与实际数的差不会大于 $1$ 。 所以 $n$ 如果对取整后的 $\sqrt n$ 取余为 $0$ 的话则组成的一定为正方形。

答案为 $($ 长 $+$ 宽 $) \times 2$；

如果 $n$ 个小正方形无法组成一个正方形的话我们就把它拼成一个最近似的正方形，我们直接算的时候把长加宽的和再加上一个 $1$ 就好了。

答案为 $($ 长 $+$ 宽 $+ 1 ) \times 2$

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int chang = sqrt(n);
	int kuan = n / chang;
	if (n % chang == 0) {
		cout << (chang + kuan) * 2;
	}
	else {
		cout << (chang + kuan + 1) * 2;
	}
	return 0;
}

```


---

