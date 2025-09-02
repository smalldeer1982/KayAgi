# 「GMOI R1-T2」Light

## 题目背景

前置芝士：平面镜成像原理。

因为百度的不太清楚，所以大家有不懂的可以自行搜索，也可以看本题的样例解释。

## 题目描述

通道可以认为是一个无限长的坐标轴，在原点 $O$ 上有一盏灯，在坐标为 $-L$ 和 $R$ 的地方分别有两面镜子，这两个镜子构成了无尽的灯廊。

为什么说无尽呢？是因为这两面镜子上理论上能呈现无穷个灯的像。现在，请你求出这盏灯左边或右边第 $x$ 个像的坐标。

## 说明/提示

[样例 $1$ 解释](https://www.luogu.com.cn/paste/4g9o1uzz)

对于 $100\%$ 的数据 $1\le T\le 5\times 10^5$，$1\le L,R \le 10^7$，$1\le x \le 10^{10}$。

| 测试点 | $T$ | $L,R$ | $x$ | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim3$ | $T=1$ | $1 \le L,R \le 10$ | $1 \le x \le 10$ | $15$ |
| $4\sim6$ | $T=1$ | $1 \le L,R \le 1000$ | $1 \le x \le 1000$ | $15$ |
| $7\sim11$ | $T \le 1000$ | $1 \le L,R \le 10^7$ | $1 \le x \le 10^4 $ | $25$ |
| $12\sim16$ | $T \le 10^5$ | $1 \le L,R \le 10^7$ | $1 \le x \le 10^9$ | $25$ |
| $17\sim20$ | $T \le 5 \times 10^5$ | $1 \le L,R \le 10^7$ | $1\le x \le 10^{10}$ | $20$ |

## 样例 #1

### 输入

```
2
3 5
L 1
R 1```

### 输出

```
-6
10```

# 题解

## 作者：Paris_Commune (赞：7)

### 分析

以样例 $1$ 为例，在题面的解释中有这么一个图

![](https://cdn.luogu.com.cn/upload/image_hosting/cskrumnj.png)

很明显 $O'(L)\sim O$ 的距离是 $L\sim O$ 距离的两倍， $O'(R)\sim O$ 的距离也是 $R\sim O$ 距离的两倍。那么设 $(O'(R))'(L)\sim O$  的距离为 $K$ ,那么 $K=(O'(R))'(L)\sim L+L\sim O=O'(R)\sim =O+O'(L)\sim O=2\times (O\sim L+ O\sim R)$ 。

同理,设$(O'(L))'(R)\sim O$  的距离为 $M$ , $M=2\times (O\sim R+ O\sim L)$ 。

这时再仔细看下图片，就可以找到其中的规律，我们设 $L\sim O$ 的距离为 $X$ , $O\sim R$ 的距离为 $Y$ , 依靠上边的结论并观察可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/f69qqd7x.png)

使用题目中的给定数据最终得到：当 $k$ 为偶数且输入字符为 $\tt L$ 时距离点 $O$ 的距离为 ， $(l+r)\times (k-1)+2\times l$ , 当 $k$ 为偶数且输入字符为 $\tt R$ 时距离点 $O$ 的距离为 ， $(l+r)\times (k-1)+2\times r$  ,当 $k$ 为奇数时距离点 $O$ 的距离为 $(l+r)\times k$ 。

### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,l,r;
signed main(){
	cin>>t>>l>>r;
	while(t--){
		int k;
		char lr;
		cin>>lr>>k;
		if(lr=='L'){
			if(k%2==1){
				cout<<0-((l+r)*(k-1)+2*l)<<'\n';
			}
			else cout<<0-(l+r)*k<<'\n';
		}
		else{
			if(k%2==1){
				cout<<(l+r)*(k-1)+2*r<<'\n';
			}
			else cout<<(l+r)*k<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：5)

## 官方题解

首先会在距左侧镜子 $L$ 和右侧镜子 $R$ 的地方成第一组像。

左侧的第一个像会在右侧再成一个像，因为左侧的像和右侧的镜子之间的距离为 $2L+R$ 所以会在右侧距镜子 $2L+R$ 的位置成第二个像；同理右侧的第一个像会在左侧距镜子 $2R+L$ 的位置成第二个像。

如此下去，左侧的第 $i$ 个像会对应成右侧的第 $i+1$ 个像，右侧的第 $j$ 个像也会对应成左侧的第 $j+1$ 个像。

综上所述，左侧的像的位置是：

$$-(2L),-(2L+2R),-(4L+2R),-(4L+4R)...$$

右侧像的位置则是：

$$2R,2R+2L,4R+2L,4R+4L...$$

通过汇总公式可得（利用取整）: 如果询问左边第 $n$ 个，那么输出：

$$-(\left[\frac{(n+1)}{2}\right] \times 2 \times L+\left[\frac{n}{2}\right]\times 2 \times R)$$

如果是右边第 $n$ 个，那么输出：

$$\left[ \frac{(n+1)}{2}\right] \times 2 \times R+\left[\frac{n}{2}\right]\times 2 \times L$$


---

## 作者：Infinite_Eternity (赞：4)

### Warning

警钟长鸣，这个蒟蒻只测试了大样例的前 $4$ 项，导致 $100 \rightarrow 0$。

# Description

[P8925 「GMOI R1-T2」Light](https://www.luogu.com.cn/problem/P8925)

在原点 $O$ 上有一盏灯，在坐标为 $-L$ 和 $R$ 的地方分别有两面镜子，求出这盏灯左边或右边第 $x$ 个像的坐标。

数据范围：$1\le T\le 5\times 10^5$，$1\le L,R \le 10^7$，$1\le x \le 10^{10}$。

# Analysis

明显地，结论题。根据数据范围即可得出。

以样例中的 $L=-3,R=5$ 为例：（手画，不喜勿喷，~~"蜡"写错了~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/udx46sdy.png)

------------

对于 $L_x$，有：
$$
\begin{aligned}
L_1=2\times(-3)-0\times5=2L-0R\\
L_2=2\times(-3)-2\times5=2L-2R\\
L_3=4\times(-3)-2\times5=4L-2R
\end{aligned}
$$
因此得出：
- 当 $x$ 为奇数时，$L_x=(x+1)L-(x-1)R$；
- 当 $x$ 为偶数时，$L_x=x(L-R)$。

------------

同样地，对于 $R_x$，有：
$$
\begin{aligned}
R_1=2\times5-0\times(-3)=2R-0L\\
R_2=2\times5-2\times(-3)=2R-2L\\
R_3=4\times5-2\times(-3)=4R-2L
\end{aligned}
$$
因此得出：
- 当 $x$ 为奇数时，$R_x=(x+1)R-(x-1)L$；
- 当 $x$ 为偶数时，$R_x=x(R-L)$。

------------

此外，$(L_x)_{min}=(-2)\times10^7\times10^{10}=-(2\times10^{17})$，$(R_x)_{max}=2\times10^7\times10^{10}=2\times10^{17}$。因此，只需要开 `long long` 即可，不必使用 `__int128`。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register char c = getchar();
    register int x = 0, f = 1;
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return x * f;
}
signed main()
{
    int T,L,R;
    T=read(),L=read(),R=read();
    L=L*(-1);
    while(T--)
    {
        char in=getchar();
        int need=read();
        if (in=='L')
        {
            if (need&1)
                cout << (need+1)*L-(need-1)*R << "\n";
            else
                cout << need*(L-R) << "\n";
        }
        else
        {
            if (need&1)
                cout << (need+1)*R-(need-1)*L << "\n";
            else
                cout << need*(R-L) << "\n";
        }
    }
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：3)

本文中的 $L$ 是题目中的 $-L$。

1. 一盏位于 $x$ 的灯会投影到 $2L-x$ 与 $2R-x$ 处。  
设 $x'(y)$ 表示 $x$ 关于镜子 $y$ 成的像，则如果 $x<y$，则 $x'(y)=y+(y-x)=2y-x$；如果 $x>y$，则 $x'(y)=y-(x-y)=2y-x$。所以 $x'(y)=2y-x$，所以 $x'(L)=2L-x$，$x'(R)=2R-x$，一盏位于 $x$ 的灯会投影到 $2L-x$ 与 $2R-x$ 处。
1. 所有像关于的镜子是 $L,R$ 交替出现。  
因为 $(x'(y))'(y)=2y-(2y-x)=x$，所以不会有形如 $(x'(y))'(y)$ 这样的位置，而只有 $L,R$ 两个镜子，所以所有像关于的镜子都是 $L,R$ 交替出现。
1. $(((x'(y_1))'(y_2))'\cdots)'(L)<0$，$(((x'(y_1))'(y_2))'\cdots)'(R)>0$。  
假设上式成立，设 $(((x'(y_1))'(y_2))'\cdots)=x$ 因为 $L,R$ 交替出现，所以如果最后是 $L$，那么 $x$ 最后是 $R$，而根据假设，$x>0$，那么 $2L<0$，$-x<0$，$2L-x<0$。最后是 $R$ 同理。

所以左边第 $x$ 个是 $(((O'\underbrace{\cdots)'(L))'(R))'(L)}_{x\text{个}}=\lceil\dfrac{x}{2}\rceil\times2L+\lfloor\dfrac{x}{2}\rfloor\times2R$，右边第 $x$ 个是 $(((O'\underbrace{\cdots)'(R))'(L))'(R)}_{x\text{个}}=\lceil\dfrac{x}{2}\rceil\times2R+\lfloor\dfrac{x}{2}\rfloor\times2L$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long T, L, R, x;
char opt;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T >> L >> R, L *= -1;
	while (T --) {
		cin >> opt >> x;
		if (opt == 'L') cout << ((x + 1) / 2 * L - x / 2 * R) * 2 << '\n';
		if (opt == 'R') cout << ((x + 1) / 2 * R - x / 2 * L) * 2 << '\n';
	}
	return 0;
}
```


---

## 作者：w9095 (赞：3)

[P8925 「GMOI R1-T2」Light](https://www.luogu.com.cn/problem/P8925)

让我们好好观察样例解释的这一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cskrumnj.png)

左边第 $1$ 个像到 $O$ 点的距离 ：$L\times2=2L$

右边第 $1$ 个像到 $O$ 点的距离 ：$R\times2=2R$

左边第 $2$ 个像到 $O$ 点的距离 ：右边第 $1$ 个像到达 $L$ 的距离是 $2R+L$ 。而这样子距离 $O$ 还差一个 $L$ ，最终结果就是 $2L+2R$

右边第 $2$ 个像到 $O$ 点的距离 ：同理可得 $2R+2L$

递推得到：

左边第 $n$ 个像到 $O$ 点的距离 ：右边第 $n-1$ 个像到 $O$ 点的距离加上 $2L$

右边第 $n$ 个像到 $O$ 点的距离 ：左边第 $n-1$ 个像到 $O$ 点的距离加上 $2R$

然后我们打出一张表：


|  | 左边第 $n$ 个像到 $O$ 点的距离 | 右边第 $n$ 个像到 $O$ 点的距离 |
| :----------: | :----------: | :----------: |
| $1$ | $2L+0R$ | $2R+0L$ |
| $2$ | $2L+2R$ | $2R+2L$ |
| $3$ | $4L+2R$ | $4R+2L$ |
| $4$ | $4L+4R$ | $4R+4L$ |

最后找一找系数的规律：

对于左边第 $n$ 个像到 $O$ 点的距离，$L$ 的系数是 $2,2,4,4...$ ，很明显两个一周期。利用向下取整的特性，得到式子：

$$\lfloor\frac{n+1}{2}\rfloor\times2$$

$R$ 的系数是 $0,2,2,4...$ ，除了第一个外，两个一周期，也可以利用向下取整的特性，得到式子：

$$\lfloor\frac{n}{2}\rfloor\times2$$

最后再乘以各项变量就行了：

$$\lfloor\frac{n+1}{2}\rfloor\times2L+\lfloor\frac{n}{2}\rfloor\times2R$$

注意，由于算的是距离，最后的答案需要取相反数输出：

$$-(\lfloor\frac{n+1}{2}\rfloor\times2L+\lfloor\frac{n}{2}\rfloor\times2R)$$

对于右边第 $n$ 个像到 $O$ 点的距离，同理得到：

$$\lfloor\frac{n+1}{2}\rfloor\times2R+\lfloor\frac{n}{2}\rfloor\times2L$$

AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,l,r;
int main()
{
	scanf("%lld",&t);
	scanf("%lld%lld",&l,&r);
	for(long long i=0;i<t;i++)
	    {
	    	char a;
	    	long long b;
	    	getchar();
	    	scanf("%c%lld",&a,&b);
	    	if(a=='L')printf("%lld\n",-(b+1)/2*2*l-b/2*2*r);
	    	else if(a=='R')printf("%lld\n",(b+1)/2*2*r+b/2*2*l);
		}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/98442785)

---

## 作者：yszkddzyh (赞：2)

补充dalao的官方题解，~~自认为~~具体、好懂一点

一拿到这道题，我非常高兴，这回比赛不至于一题不会了，结果一看数据范围：

$$ 1\le T \le 5 \times 10^5,1\le L,R\le 10^7,1\le x\le 10^{10}$$

我顿时一脸蒙，于是~~聪明的~~我就想到每次查询都必须是 $O(1)$ 的复杂度，嘿嘿。怎么做到这样呢？不要着急，我们按照题意画个图，当 $L=3,R=1$ 时，该坐标轴中的一部分应该是这样的:![](https://cdn.luogu.com.cn/upload/image_hosting/fbi60b89.png)

似乎有一定的规律，但又似乎不是很明显。没事，再画一个图，当 $L=2,R=1$ 时，该坐标轴中的一部分应该是这样的:![](https://cdn.luogu.com.cn/upload/image_hosting/ojhyadz1.png)

其中 $L_i$ 表示镜子 $L$ 中第 $i$ 个像所在的点，$R_i$ 表示镜子 $R$ 中的 $i$ 个像所在的点。不难发现，$L_i$ 与 $L_{i+1}$ 之间的距离、$R_i$ 与 $R_{i+1}$ 之间的距离似乎有规律，我们把抄下来：

在第一个图中：

$L_1L_2=2,L_2L_3=6,L_3L_4=2,L_4L_5=6,L_5L_6=2,L_6L_7=6$

$R_1R_2=6,R_2R_3=2,R_3R_4=6,R_4R_5=2,R_5R_6=6,R_6R_7=2$

在第二个图中：

$L_1L_2=2,L_2L_3=4,L_3L_4=2,L_4L_5=4,L_5L_6=2,L_6L_7=4,L_7L_8=2$

$R_1R_2=4,R_2R_3=2,R_3R_4=4,R_4R_5=2,R_5R_6=4,R_6R_7=2,R_7R_8=4$

规律已经非常明显了，但要怎样将任意的 $L_i$ 或 $R_i$ 表示的值与题目所给的 $x,L,R$ 联系起来呢？我们发现：两个图中相邻两个像的距离在两个值中间跳动，在图一的镜子中，两个值为 $2$ 和 $6$，$6=2\times 3$，$3$ 就是我们假设的 $L$ 的值，在图二中两个值为 $2$ 和 $4$，又 $L=2,4=2\times2$，也是符合这一规律的。而两个图中的另一个值 $2$ 似乎是 $2\times R$，再画几个图我们发现都符合规律。这时每个点的值的一般性规律就迎刃而解了，对于每个点，我们只需求出它代表的数的绝对值，就可以求出它的值，而绝对值的几何定义为：点 $A$ 表示的数的绝对值即为 $AO$ 的长度。这样，对于题目给出的 $x$，我们只用求 $L_xO$ 或 $R_xO$ 的长度即可，而求 $L_xO$ 或 $R_xO$ 的长度，只需看它们包含几个长度为 $2\times L$ 的线段和几个长度为 $2\times R$ 的线段，再把它们加起来即为答案。设 $L_x$ 表示的数为 $l_x$，$R_x$ 表示的数为 $r_x$，通过找规律，我们发现，$L_x$ 包含 $\lceil \dfrac{x}{2} \rceil$ 个长为 $2\times L$ 的线段（其中，根据平面镜成像原理，$L_1O=2\times L$）和 $\lfloor \dfrac{x}{2}\rfloor$ 个长为 $2\times L$ 的线段，因此 $\lvert l_x \rvert=\lceil \dfrac{x}{2} \rceil\times2\times L+\lfloor \dfrac{x}{2} \rfloor\times2\times R$。同理，我们发现 $\lvert r_x \vert=\lceil \dfrac{x}{2} \rceil\times2\times R+\lfloor \dfrac{x}{2} \rfloor\times2\times L$，又由题意: $l_x<0,r_x>0$，这时我们已经找出规律了。题目给出 
$$1\le x\le 10^{10},1\le L,R\le 10^7$$
所以 $l_x$ 最小值为:

$$\begin{aligned}&\;\;\;\;-(\lceil \dfrac{x}{2} \rceil\times2\times L+\lfloor \dfrac{x}{2} \rfloor\times2\times R)\\&=-\lceil \dfrac{x}{2} \rceil\times2\times L-\lfloor \dfrac{x}{2} \rfloor\times2\times R\\&=-\lceil \dfrac{10^{10}}{2} \rceil\times2\times 10^7-\lfloor \dfrac{10^{10}}{2} \rfloor\times2\times 10^7\\&=-2\times10^{17}\end{aligned}$$

$r_x$ 的最大值为:

$$\begin{aligned}&\;\;\;\;\lceil \dfrac{x}{2} \rceil\times2\times R+\lfloor \dfrac{x}{2} \rfloor\times2\times L\\&=\lceil\dfrac{10^{10}}{2}\rceil\times2\times10^7+\lfloor\dfrac{10^{10}}{2}\rfloor\times2\times10^7\\&=2\times10^{17}\end{aligned}$$

long long 的取值范围为$[-9223372036854775808,9223372036854775807]$，完全可以满足本题需要，因此不用使用高精度，但是使用 cout 输出时，需要把强制转换成 long long，不然当数据很大时，会以 %e 的格式输出，下面贴上代码:
```cpp
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
int main(){
    ll t,l,r,x;
    char c;
    cin>>t>>l>>r;
    while(t--){
        cin>>c>>x;
        if(c=='L')
            cout<<(ll)ceil((double)x/2)*(-2)*l-x/2*2*r<<endl;
        else
            cout<<(ll)ceil((double)x/2)*2*r+x/2*2*l<<endl;
    }
    return 0;
}
```
本蒟蒻第一次发题解，希望 $\LaTeX$ 不要爆

---

## 作者：zfx_VeXl6 (赞：2)

设左边第 $i$ 个像的坐标为 $L_i$，右边第 $i$ 个像的坐标为 $R_i$。则 $L_1=-2L,R_1=2R$。不难证明，像 $L_i$ 和 $R_{i-1}$ 必定是关于 $L$ 对称的，像 $R_i$ 和 $L_{i-1}$ 必定是关于 $R$ 对称的。因此可以归纳证明出以下结论：

$
L_x=
\begin{cases}
-x(L+R)&x=2k,k>0\\
-(x-1)(L+R)-2L&x=2k-1,k>0
\end{cases}
$

$
R_x=
\begin{cases}
x(L+R)&x=2k,k>0\\
(x-1)(L+R)+2R&x=2k-1,k>0
\end{cases}
$

代码不难。要开 `long long`。

```cpp
cin>>t;
cin>>L>>R;
while(t--)
{
    cin>>c>>x;
    ans=0;
    if(c=='R')
    {
        if(x&1)
            ans=(x-1)*(L+R)+2*R;
        else
            ans=x*(L+R);
        cout<<ans<<'\n';
    }
    else
    {
        if(x&1)
            ans=-(x-1)*(L+R)-2*L;
        else
            ans=-x*(L+R);
        cout<<ans<<'\n';
    }
}
```

---

## 作者：cosf (赞：2)

## [P8925 「GMOI R1-T2」Light](https://www.luogu.com.cn/problem/P8925)

通过样例，我们可以发现：

| 左边第 $i$ 个点 | 位置 |
| - | - |
| $1$ | $-(2L)$ |
| $2$ | $-(2L+2R)$ |
| $3$ | $-(4L+2R)$ |
| $\dots$ | $\dots$ |

我们可以通过计算，得出

| 左边第 $i$ 个点 | 位置 |
| - | - |
| $4$ | $-(4L+4R)$ |
| $5$ | $-(6L+4R)$ |
| $6$ | $-(6L+6R)$ |
| $\dots$ | $\dots$ |

可以推出，位置 $= -2(\lfloor \frac{i + 1}{2} \rfloor L + \lfloor \frac{i}{2} \rfloor R)$。同理，如果是右边的点，位置就是 $= 2(\lfloor \frac{i + 1}{2} \rfloor R + \lfloor \frac{i}{2} \rfloor L)$。

为什么呢？可以发现，前面表格中，如果 $i$ 是偶数，则 $L$ 和 $R$ 的系数是一样的，同为 $i$，即 $2\lfloor\frac{i}{2}\rfloor$，也等于 $2\lfloor\frac{i+1}{2}\rfloor$。如果 $i$ 是奇数，则 $L$ 的系数比 $-i$ 小 $1$，$R$ 的系数比 $-i$ 大 $1$。正好，$-2\lfloor \frac{i + 1}{2} \rfloor=-(i+1)$，$-2\lfloor \frac{i}{2} \rfloor=-(i-1)$。

那么就通过 $2(\lfloor \frac{i + 1}{2} \rfloor R + \lfloor \frac{i}{2} \rfloor L)$ 计算右边，$-2(\lfloor \frac{i + 1}{2} \rfloor L + \lfloor \frac{i}{2} \rfloor R)$ 计算左边就可以了。

至于精度，当时我使用了 `unsigned long long`，可以过，但是计算左边的时候要先输出 `-`，然后输出 $2(\lfloor \frac{i + 1}{2} \rfloor L + \lfloor \frac{i}{2} \rfloor R)$。

[参考代码](https://www.luogu.com.cn/record/98429911)
---

```cpp
#include <iostream>
using namespace std;

#define ull unsigned long long

int main()
{
    ull l, r;
    int n;
    cin >> n;
    cin >> l >> r;
    while (n--)
    {
        char ch;
        cin >> ch;
        if (ch == 'R')
        {
            ull x;
            cin >> x;
            cout << 2 * r * ((x + 1) / 2) + 2 * l * (x / 2) << endl; // 因为是整数类型，所以取整可以直接省略。
        }
        else
        {
            ull x;
            cin >> x;
            cout << '-' << 2 * l * ((x + 1) / 2) + 2 * r * (x / 2) << endl;
        }
    }
}
```


---

## 作者：Leaves_xw (赞：2)

### 题目大意：

有一个无限长的坐标轴，在原点 $O$ 上有一盏灯，在坐标为 $-L$ 和 $R$ 的地方分别有两面镜子，这两个镜子构成了无尽的灯廊。

求出这盏灯左边或右边第 $x$ 个像的坐标。

### 思路：

学过平面镜知识的应该会感觉很好写。

[平面镜原理](https://baike.baidu.com/item/%E5%B9%B3%E9%9D%A2%E9%95%9C%E6%88%90%E5%83%8F%E5%8E%9F%E7%90%86/6843044)。

现在，我们可以由题目得出，左侧像的位置为：$-(2\times L),-(2 \times L+2\times R)…$

右侧像的则位置为左成像的每一像的绝对值，即：$2\times L,2 \times L+2\times R…$

我们可以通向整理左成像的第 $n$ 个位置为：$-(2\times( L\times[\frac{(n+1)}{2}]+R \times [\frac{n}{2}]))$。

则右成像为：$2\times( R\times[\frac{(n+1)}{2}]+L \times [\frac{n}{2}])$。


由此，我们得出核心代码：

```
if(x=='L')
{
   cout<<-(((n+1)/2)*2*l+(n/2)*2*r)<<endl;
}
if(x=='R')
{
  cout<<((n+1)/2)*2*r+(n/2)*2*l<<endl;
}

```

剩下的这里就不出示了。


这里再补充一下：

比如说$ [\frac{3}{2}] $ 的答案为1，$[]$ 符号叫高斯记号代表分子除以分母后除去小数点的整数部分，也就是是指不小于这个数的最大整数，类似于向下取整(负数特殊考虑)。

欢迎指出问题。

---

## 作者：I_am_AKed_by_NOI (赞：2)

## 题目大意

原点 $O$ 上有一盏灯，在坐标为 $−L$ 和 $R$ 的地方分别有两面镜子，这两面镜子上呈现无穷个灯的像。请你求出这盏灯左边或右边第 $x$ 个像的坐标。

## 解题思路

[CSDN博客](https://www.luogu.com.cn/blogAdmin/article/edit/526237)

![](https://img-blog.csdnimg.cn/1b0e654ef75c400a821803d866350115.png)

我们按照题意将示意图（上图）画出。

然后可以发现，$O$ 点左侧的像按顺序排序依次是：

$-2L,-(2L+2R),-(4L+2R),-(4L+4R),-(6L+4R)......$。

$O$ 点右侧的像按顺序排序依次是：

$2R,(2L+2R),(4R+2L),(4L+4R),(6R+4L)......$。

于是总结规律（还是比较好总结的）：

左侧第 $x$ 盏灯的坐标是：

$x$ 为奇数是：坐标为 $((x+1)L+(x-1)R)$。

$x$ 为偶数是：坐标为 $(xL+xR)$。

右侧第 $x$ 盏灯的坐标是：

$x$ 为奇数是：坐标为 $((x+1)R+(x-1)L)$。

$x$ 为偶数是：坐标为 $(xL+xR)$。

于是对于每一次询问，都可以利用规律 O(1) 算出答案。 总时间复杂度 O(T)。

## 代码

为了避免同学直接复制，只显示核心代码（上面应该讲清楚了，所以没有注释）。

```
if(x%2==0 && c=='L')
		{
			ans=x*(L+R);
			write(-ans);
			putchar('\n');
		}
		else if(x%2==0 && c=='R')
		{
			ans=x*(L+R);
			write(ans);
			putchar('\n');
		}
		else if(x%2==1 && c=='L')
		{
			ans=(x+1)*L+(x-1)*R;
			write(-ans);
			putchar('\n');
		}
		else if(x%2==1 && c=='R')
		{
			ans=(x+1)*R+(x-1)*L;
			write(ans);
			putchar('\n');
		}
```


---

## 作者：Daidly (赞：2)

灯初始在原点，和左右镜子之间的距离为 $L,R$。

考虑左边第一个像，它必然是由灯关于 $-L$ 对称得到，同理右边第一个像是由灯关于 $R$ 对称得到。

继续考虑左边第二个，肯定是由 $-L$ 右侧对称过来的。而此时右侧只有原点灯和右一，那就是右一关于 $-L$ 对称得到。

以此类推，可以得到：左 $x$ 由右 $x-1$ 关于 $-L$ 对称得到。右 $x$ 由左 $x-1$ 关于 $R$ 对称得到。也就是：左 $x$ 由左 $x-2$ 关于 $-L$ 对称再关于 $R$ 对称得到。

不论是画图还是计算都可以得到：左 $x$ 和左 $x-2$ 之间的距离为 $2l+2r$。右侧同理。

所以，左 $x$ 的位置为： $-\Bigg(\lfloor\frac{x}{2}\rfloor(2l+2r)+[x \bmod 2=1]\times 2l\Bigg)$，右 $x$ 的位置为：$\lfloor\frac{x}{2}\rfloor(2l+2r)+[x \bmod 2=1]\times 2r$。

注意开 `long long`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

int t,l,r,x,ans;
char opt;

signed main(){
	t=read(),l=read(),r=read();
	l<<=1,r<<=1;
	while(t--){
		scanf("%c",&opt),x=read();
		ans=x/2*(l+r);
		if(x&1)ans+=((opt=='L')?l:r);
		print(opt=='L'?-ans:ans),putchar('\n');
	}
	return 0;
}
```

如果觉得有帮助就点个赞吧。

---

## 作者：luogu_user (赞：1)

先上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,b,d,answer,t;
char lr;
int main(){
    cin>>t>>a>>b;
    while(t--){
        answer=0;
        cin>>lr;
        if(lr=='L'){
            cin>>d;
            answer-=d/2*2*(a+b);
            if(d%2) answer-=2*a;//特判
        }
        else {
            cin>>d;
            answer+=d/2*2*(a+b);
            if(d%2) answer+=2*b;//特判
        }
        cout<<answer<<endl;
    }
}
```
解释：

$O$ 处的灯光首先会在 $-2L$ 和 $2R$ 的地方成第一组像。

左侧的第一个像会在右侧再成一个像，因为左侧的像和右侧的镜子之间的距离为 $2L+R$ ，所以会在 $R+(2L+R)=2L+2R$ 的位置成第二个像。

同理，右侧的第一个像会在 $-L-(2R+L)=-2L-2R$ 的位置成第二个像。

如此下去，左侧的第 $p$ 个像会对应成右侧的第 $p+1$ 个像，右侧的第 $q$ 个像也会对应成左侧的第 $q+1$ 个像。

那么，左侧的每一个像的位置依次是 

$-2L,-2L-2R,-4L-2R,-4L-4R,-6L-4R,-6L-6R,\cdots$

右侧每一个像的位置依次是

$2R,2L+2R,2L+4R,4L+4R,4L+6R,6L+6R,\cdots$

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/P8925)

我们看样例解释可以发现，它的几个成像的坐标从左到右分别为：$-22$，$-16$，$-6$，$0$，$10$，$16$。

如果我们把 $L$ 和 $R$ 放进来看就可以把它改成这个样子：$4\times(-L)-2\times R$，$2\times(-L)-2\times R$，$2\times(-L)$，$0$，$2\times R$，$2\times R-2\times(-L)$。

我们不难总结公式：如果问左边的第 $x$ 个成像的坐标，若 $x$ 为奇数，坐标为 $(x+1)\times(-L)-(x-1)\times R$，若为偶数 $x$ 为偶数，则坐标为 $x\times(-L)-x\times R$。若问右边的第 $x$ 个坐标，则坐标为 $(x+1)\times R-(x-1)\times(-L)$，否则为 $x\times R-x\times(-L)$。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r;
int main()
{
	scanf("%d%d%d",&t,&l,&r);
	while(t--)
	{
		char ch;
		long long x;
		cin>>ch;
		scanf("%lld",&x);
		if(ch=='L')
			if(x%2==1) printf("%lld\n",(x+1)*(-l)-(x-1)*r);
			else printf("%lld\n",x*(-l)-x*r);
		else
			if(x%2==1) printf("%lld\n",(x+1)*r-(x-1)*(-l));
			else printf("%lld\n",x*r-x*(-l));
	}
	return 0;
}
```

---

## 作者：dtw35l (赞：1)

## 前备物理
#### 平面镜成像原理：像和物到镜面的距离相等
如果在平面镜**正面**有一个蜡烛或者**蜡烛的像**，那这个蜡烛或者蜡烛的像关于平面镜对称的地方也会出现一个像

![](https://cdn.luogu.com.cn/upload/image_hosting/2rily8g6.png)

#### 根据题目画出图

![](https://cdn.luogu.com.cn/upload/image_hosting/pxcfbth5.png)

#### 同理可画出
![](https://cdn.luogu.com.cn/upload/image_hosting/xp3ljlwr.png)

观察可得左边蜡烛分别为： $-2L, -2L-2R, -4L-2R, -4L-4R......$

右边蜡烛分别为： $2R, 2L+2R, 2L+4R, 4L+4R......$

## 开始编码
可以发现当 $x$ 为双数时是 $x(L+R)$ ，当 $x$ 为单数时先计算前面的双数部分再加上最后一个若输入字符为 L 就加上 $2L$ 如输入字符为 R 就加上 $2R$ 
### 注意： x 和答案应该用 long long 
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int T, L, R;
long long x, ans;
char c;
int main() {
	cin >> T >> L >> R;
	while (T--) {
		cin >> c >> x;
		if (c == 'L') putchar('-');
                // 判断x
		if (x % 2 == 0) {
		    ans = x * (L + R);
		} else {
		    ans = (x - 1) * (L + R);
		    ans += (c == 'L' ? L : R) * 2;
		}
		cout << ans << endl;
	}
	return 0;
}
```

蒟蒻的第一篇题解，如果有帮助点个赞

---

## 作者：zenght (赞：1)

~~蒟蒻的第一篇题解，求过~~

赛时认为是个好题，涉及到物理芝士。（赛场做出来了，比较意外，蒟蒻一般做不出 $\text{CSP-J T2}$）

**55分解法（同学第一次想到的）**

大约能得到 $55$ 分，没写过。具体思路是模拟成像，记录下来。

复杂度 $O(Tx)$，显然会超时（而且好像会 $\text{MLE}$）

代码不给了，反正对不了。

**正解：直接结论**

学过物竞的人大笑，这题可以做到 $O(T)$，也就是说可以手算出来。

我们不妨设 $S$ 表示两个平面镜之间的距离，则 $S = L + R$。

如果是第一个字符是 $L$，那么

当 $x = 2 \cdot k + 1$ 时，答案为 $r - x \cdot S - L$；

当 $x = 2 \cdot k$ 时，答案为 $- x \cdot S$。

如果是第一个字符是 $R$，那么

当 $x = 2 \cdot k + 1$ 时，答案为 $r + x \cdot S - L$；

当 $x = 2 \cdot k$ 时，答案为 $x \cdot S$。

于是，这题就结束了。
 
在代码实现上，有一个在赛场上坑了我 $10$ 分钟的点，就是：

```cpp
scanf("%c", &c);
```

是不能正常实现的，所以，建议使用加速版 $\text{cin}$ 来处理。

还有，就是：不开 long long 见祖宗！！！

好了，上代码（右边就是代码了）：[$code$](https://www.luogu.com.cn/paste/ci8e5zws)

蒟蒻的第一篇题解，有错误欢迎指出。

upd: $2023.1.5$ 修 $\LaTeX$

---

## 作者：JackMerryYoung (赞：0)

# 前言

T2, 需要找规律。还以为是什么解同余方程组，吓我一大跳。

# 正文

记 $L_i$ 为左第 $i$ 个像的位置, $R_i$ 为右第 $i$ 个像的位置。

那么显然 $L_1 = -2L, R_1 = 2R$. 然后就可做了。

发现左边的像为：

$$
\begin{cases}
L_1 = -2L \\
L_2 = -(2L + 2R) \\
L_3 = -(4L + 2R) \\ 
\cdots \\
L_{x} = -(xL + xR) \\
L_{x+1} = -[(x+2)L + xR] \\
\end{cases}

\quad (2 \mid x, x \in N)
$$

右边的像为：

$$
\begin{cases}
R_1 = 2R \\
R_2 = 2R + 2L \\
R_3 = 4R + 2L \\ 
\cdots \\
R_{x} = xR + xL \\
R_{x+1} = (x+2)R + xL \\
\end{cases}

\quad (2 \mid x, x \in N)
$$

因此只需左边右边分别分两类求解即可。复杂度 $\mathcal{O}(T)$.

# 代码

也是按做法模拟即可，代码不放了。

~~才不是因为我是口胡选手呢！~~

# 后言

感觉难度不大，放 T2 是否有点过水了呢？ $\tiny\color{WHITE}\text{说好的略难于 CSP-J 的呢, 人均 200pts 然后 1=...}$

---

## 作者：I_AK_CTSC (赞：0)

这道题大家可以去推推关系，毕竟像这种 $x \le 10^{10}$ 这种题肯定不是硬算的，否则出题人……我不说了，切入正题。

# 思路分析
首先这道题的思路是找规律，那就列表。

我们就拿样例举例，假设 $L = 3, R = 5$ 。

我们分别假设成像时先向左和先向右成像：

![](https://cdn.luogu.com.cn/upload/image_hosting/ynb9rj13.png)

好了，就列举这么多。

那么，如图这些正数就是就是题目要求的 $R$ 的第 $x$ 项。

如图这些负数就是就是题目要求的 $L$ 的第 $x$ 项。

诶？原点左边的第 $x$ 项有一个规律：

$$
-2 \times (3+5+3+5+……)
$$
再普遍一点就是：
$$
-2 \times (L+R+L+R+……)
$$

诶？原点右边的第 $x$ 项也有一个规律：

$$
2 \times (5+3+5+3……)
$$
再普遍一点就是：
$$
2 \times (R+L+R+L……)
$$

很好，这道题就已经变的很简单了。

那么就上代码吧：

```cpp
#include <iostream>
#include <cstdlib>

using namespace std;
typedef __int128 ll;
ll read()
{
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void write(ll x)
{
	if(x < 0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if(x < 10)
	{
		putchar(x + '0');
		return;
	}
	write(x / 10);
	putchar(x % 10 + '0');
}
const ll M = 5e5 + 5;
int main()
{
	ll t;
	t = read();
	ll l, r;
	l = read(), r = read();
	char ch;
	ll x;
	while (t--)
	{
		cin >> ch;
		x = read();
		ll cnt = 0;
		ll zhouqi;
		if (ch == 'L')
		{
			zhouqi = -2 * (l + r);
			ll p = x;
			ll o = x >> 1;
			cnt = o * zhouqi;
			if (p & 1)//一个周期有两个数，万一第x个数不能完成整数个周期，那么就得单独加上
			{
				cnt += -2 * l;
			}
		}
		else
		{
			zhouqi = 2 * (l + r);
			ll p = x;
			ll o = x >> 1;
			cnt = o * zhouqi;
			if (p & 1)//同上
			{
				cnt += 2 * r;
			}
		}
		write(cnt);//数据吓到我了，我用__int128
		printf("\n");
	}
	return 0;
}
```

最后还是名言：

不贵于无过,而贵于能改过。——王守仁

20230103：抱歉各位，图片没传上去，现在传上去了。~~貌似我的图片总是要折腾几遍~~

---

## 作者：allenchoi (赞：0)

### 科技： 
智慧  
### 思路：  
首先假设大家物理都还行，知道平面镜成像。  
这道题的结论是：  
$O$ 左边第 $i$ 个像，坐标是 $-(\left\lceil\dfrac{i}{2}\right\rceil\times 2L+\left\lfloor\dfrac{i}{2}\right\rfloor\times 2R)$   
$O$ 右边第 $i$ 个像，坐标是 $\left\lceil\dfrac{i}{2}\right\rceil\times 2R+\left\lfloor\dfrac{i}{2}\right\rfloor\times 2L$  
证明：  
归纳法。  
首先，当 $i = 1$ 时，左右两边的像坐标分别是 $-2L$ ， $2R$ ，符合规律。  
设前 $i - 1$ 个像都满足这个规律（ $i\ge2$ ）。  
若 $i$ 为奇数：  
则左边、右边第 $i - 1$ 个像的坐标分别是 $-(i-1)\times(L+R)$ ， $(i-1)\times(L+R)$ 。 
根据平面镜成像的原理，左边第 $i$ 个像距离左边的平面镜的距离应该与右边第 $i-1$ 个像距离左边的平面镜距离相等（ $L+(i-1)\times(L+R)$ ），所以左边第 $i$ 个像的距离应为 $-L-(L+(i-1)\times(L+R))=-(\left\lceil\dfrac{i}{2}\right\rceil\times 2L+\left\lfloor\dfrac{i}{2}\right\rfloor\times 2R)$ ；    
右边第 $i$ 个像距离右边的平面镜应为 $R+(i-1)\times(L+R)$ ，所以第 $i$ 个像的坐标应为 $R+R+(i-1)\times(L+R)=\left\lceil\dfrac{i}{2}\right\rceil\times 2R+\left\lfloor\dfrac{i}{2}\right\rfloor\times 2L$ 。   
若 $i$ 为偶数：  
则左边、右边第 $i-1$ 个像的坐标分别是 $-(i-1)\times(L+R)+2R$ ， $(i-1)\times(L+R)-2L$ ，同理可知，左右两边的第 $i$ 个像坐标分别为 $-i\times(L+R)$ ， $i\times(L+R)$ ，符合规律。   
这道题就做出来力！！！1111  
[然而...](https://www.luogu.com.cn/record/98438263)  
$x$ 没开 long long ！！！！1111111111111
### 代码：  
~~~ cpp  
#include <cstdio>
using namespace std;
int T,L,R;
long long ans,p;
char ch;
int main()
{
	scanf("%d%d%d",&T,&L,&R);
	while(T--)
	{
		scanf("\n%c%lld",&ch,&p);
		ans = (p / 2) * 2 * (L + R);
		if(ch == 'L')
		{
			if(p % 2 == 1) ans += 2 * L;
			ans *= -1;
		}
		else if(p % 2 == 1) ans += 2 * R;
		printf("%lld\n",ans);
	}
	return 0;
}
~~~  
[AC ！！！](https://www.luogu.com.cn/record/98440374)

---

## 作者：Creative_sad_yosgic (赞：0)

## P8925の题解
### 前言
前置芝士：平面镜成像原理。

若不知道，请看官方样例一解释：https://www.luogu.com.cn/paste/4g9o1uzz。

### 思路
首先，我们按照平面镜原理画个图
![](https://cdn.luogu.com.cn/upload/image_hosting/9l0kb8xs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以看出，左半侧

第一个像坐标为 $-L\cdot2$ 

第二个像为 $-L\cdot2 -(2 \times R)$

第三个点为 $-L\cdot2-(2 \cdot L+2 \cdot R)$

第四个像为 $-L\cdot2-(2\cdot(2 \cdot L)+(2 \cdot R))$。

以此类推。

右半侧

第一个像坐标为 $R+R$ .

第二个像坐标为 $R+R+(2 \cdot L)$.

第三个像坐标为 $R+R+(2\cdot L+2\cdot R)$

第四个像显然为 $R+R+(2\cdot (2\cdot L)+2\cdot R)$。

以此类推。

故记 $N$ 为第 $X$ 个像中 $2\cdot L$ 循环的次数，

$V$ 为第 $X$ 个像中 $2\cdot R$ 循环的次数。

则在左半侧的像中，第 $X$ 个像的坐标为 $-L\cdot2-(V\cdot(R\cdot2)+N\cdot(L\cdot2))$，其中 $V = X/2$，$N=\begin{cases}
 X/2,&X\bmod 2=1 \\
X/2-1,& X \bmod2=0
\end{cases}$

右半侧中，第 $X$ 个像的坐标为

$R\cdot2-(N\cdot(L\cdot2)+(V\cdot(R\cdot2))$，其中$N=X/2$，$V=\begin{cases}
 X/2,&X\bmod 2=1 \\
X/2-1,& X \bmod2=0
\end{cases}$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;//开long long
long long lx(long long x){
	return -2*l-((x/2)*(r*2)+(x%2?x/2:x/2-1)*(l*2));
}
long long lr(long long x){
	return r+r+((x/2)*(l*2)+(x%2?x/2:x/2-1)*(r*2));//按公式即可
}
int main(){
	freopen("sample1.in","r",stdin);
	freopen("sample.out","w",stdout);
	ios_base::sync_with_stdio(false);
	int t;
	cin>>t;
	cin>>l>>r;
	while(t--)
	{
		char f;long long x;//注意x有可能爆int
		cin>>f>>x;
		if(f=='L') cout<<lx(x)<<'\n';
		else cout<<lr(x)<<'\n';
	}
	return 0;
}
```



---

