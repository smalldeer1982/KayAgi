# Water Lily

## 题目描述

While sailing on a boat, Inessa noticed a beautiful water lily flower above the lake's surface. She came closer and it turned out that the lily was exactly $ H $ centimeters above the water surface. Inessa grabbed the flower and sailed the distance of $ L $ centimeters. Exactly at this point the flower touched the water surface.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1199B/42f6cea9c2bcade7ac8750d98129857158bca8c3.png)Suppose that the lily grows at some point $ A $ on the lake bottom, and its stem is always a straight segment with one endpoint at point $ A $ . Also suppose that initially the flower was exactly above the point $ A $ , i.e. its stem was vertical. Can you determine the depth of the lake at point $ A $ ?

## 样例 #1

### 输入

```
1 2
```

### 输出

```
1.5000000000000
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
2.6666666666667
```

# 题解

## 作者：Retired_lvmao (赞：4)

根据此题的图

假设 水深= $X$ 花露出湖面的高度为 $H$ 花被拉出的距离为 $L$

根据勾股定理 可得计算式：$L*L+X*X=(H+X)*(H+X)$

逐步分解下去 

原式=$L*L+X*X=H*H+X*X+2*H*X$

$L*L+H*H=2*H*X$

$X=(L*L-H*H)/(2*H)$

最后附上代码:

    #include<iostream>
    #include<cstdio>
    using namespace std;
    int main()
    {
	  double h,l,ans;//不能用float 精度问题
	  cin>>h>>l;
	  printf("%.13lf\n",(l*l-h*h)/(2.0*h));//计算
	  return 0;
    }

---

## 作者：HoshizoraZ (赞：2)

学过勾股定理的同学应该都在课内做过这类数学题

我们可以设水深为 $X$，那么花长（斜边长）为 $X+H$

然后我们就可以列出方程：

$$X^2 + L^2 = (X + H)^2$$

展开：

$$X^2 + L^2 = X^2 + 2XH + H^2$$

合并：

$$L^2 = 2XH+H^2$$

移项：

$$L^2 - H^2 = 2XH$$

$H>0$，可以把 $2H$ 除过去：

$$X = \frac{L^2 - H^2}{2H}$$

所以答案就是 $\frac{L^2 - H^2}{2H}$

---

## 作者：Eason_AC (赞：0)

## Content
有一朵长在水中的莲花，其茎秆部分露出水面的高度为 $h$。有人将它往右边拽了 $l$ 米，使得整个茎秆部分都浸在水中。求池水的深度。

**数据范围：$1\leqslant h<l\leqslant 10^6$。**
## Solution
勾股定理好题，具体根据下面的图来讲讲（其实就是蒯的 CF 的）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1199B/42f6cea9c2bcade7ac8750d98129857158bca8c3.png)

我们设水的深度为 $x$，那么整个茎秆部分的高度为 $x+h$，又由于我们将它拽了 $l$ 米之后的茎秆部分的高度不变，所以原来浸在水中的一段，拽的一段以及最后全部浸在水中的一段就构成了一个直角三角形。因此我们可以列出下面的方程：

$$x^2+l^2=(x+h)^2$$  

下面给大家解一下吧：

$$x^2+l^2=x^2+2hx+h^2$$

$$2hx+h^2=l^2$$

$$2hx=l^2-h^2$$

$$\therefore x=\dfrac{l^2-h^2}{2h}$$

直接输出这个结果就好。注意，由于相乘的时候结果可能很大，$h,l$ 在开变量的时候建议开 $\texttt{long long}$。
## Code
```cpp
ll h, l;

int main() {
	getll(h), getll(l);
	double ans = (l * l - h * h) / (h * 2.0);
	printf("%.9lf", ans);
	return 0;
}
```

---

## 作者：Mars_ (赞：0)

[题目传送门](https://www.luogu.org/problem/CF1199B)

题意是说要解出方程$x^2 + L^2=(H+x)^2$的解，并且保留6位以上小数。

我们不妨将其化简，得到

 * **$x$=$\frac{L^2-H^2}{2H}$**

这道题只要看懂了题意就不难做出来，只需要注意scanf 与 printf 的应用。

***

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	double h,l,x;
	scanf ("%lf %lf",&h,&l);
	x=(l*l-h*h)/(2*h);
	printf ("%.9f",x);//这个数字可以随便改成大于6的数，但是最好不要太大
	return 0;
}
```

---

## 作者：AuroraIris (赞：0)

![](https://cdn.luogu.com.cn/upload/pic/68758.png)
题意为：
线段$AB$长度不变，$AB=AC$ 

给出h和l的长度

求$AB$-$h$的长度

设$AB$=$x$

则$AB$=$AC$

$x^2$-$l^2$=$(x$-$h)^2$

得$x$=$\frac{l^2-h^2}{2h}$

CODE：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int H,L;
	scanf("%d%d",&H,&L);
	double x=1.0*((1ll*L*L-1ll*H*H)/(1.0*2*H));
	printf("%.13f",x);
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

简单的推公式题  
图中显然有一个三角形，设水深度（要求的）为$D$，则直角边长度分别表示为$D$和$L$，斜边表示为$H+D$  
那么由勾股定理可以得  
$(H+D)^2=D^2+L^2$  
化简得  
$D=\frac{L^2-H^2}{2\cdot H}$  
于是直接读数据用公式算出答案输出

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 6e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}

int main() {
	rg ll h = fast_IO::read(), l = fast_IO::read();
	printf("%.13f", (double)(l * l - h * h) / (2 * h));
	return 0;
}
```


---

## 作者：Kizuna_AI (赞：0)

####  [我的个人博客](https://blog.likecoding.ooo/2019/08/03/cf1199b%20water%20lily%20%E9%A2%98%E8%A7%A3/)  
这道题其实很水，只要你的数学要达到一定的水平（数学好就是入门难度的题目，数学不好你再想也想不出来）

我们通过勾股定理$a^2+b^2=c^2$列举一个方程。  
设A到H的距离为x  
可以列得方程为$(x+h)^2=x^2+l^2$  
化简得到$x^2+2xh+h^2=x^2+l^2$  
$2xh=l^2-h^2$  
$x=(l^2-h^2)/2h$  

输出答案x即可。

代码很短：
```
#include<bits/stdc++.h>
using namespace std;
int h,l;
double ans,le=0,ri=1e6;
int main() {
	scanf("%d%d",&h,&l);
	ans=(double)(pow(l,2)-pow(h,2))/2/h;
	cout<<fixed<<setprecision(9)<<ans; 
	return 0;
}
```

---

## 作者：逃课小姐MS (赞：0)

CF出的清真数学题

图看懂 题目看懂就做出来了

勾股定理一上做完啦

代码如下，作者不多做做解释


```
#include<bits/stdc++.h>
using namespace std;
double l,h;
int main(){
	cin>>h>>l;
	printf("%.10f\n",(l*l-h*h)/h/2); 
	return 0;
}
```

---

## 作者：YLWang (赞：0)

设绳子长$R$, 看到一个直角三角形马上列式：

$(R - H) ^ 2 + L ^ 2 = R ^ 2$

整理一下：

$R ^ 2 + H ^ 2 - 2RH + L ^ 2 = R ^ 2$

$H ^ 2 + L ^ 2 = 2HR$

$R = \frac{H ^ 2 + L ^ 2}{2H}$

得以解决

---

