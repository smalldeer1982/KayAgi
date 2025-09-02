# 「RdOI R1」一次函数(function)

## 题目背景

**请使用较快的读入方式。**

众所周知，一次函数的解析式如下：

$$y=kx+b$$

或者，我们可以表示为：

$$f(x)=kx+b$$

这个就是一次函数的解析式，下文中用到的解析式均用 $y=kx+b$ 表示。

- 如果不知道什么是一次函数的[戳我](https://baike.baidu.com/item/%E4%B8%80%E6%AC%A1%E5%87%BD%E6%95%B0)。
- 如果不知道什么是函数图像的[戳我](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E5%9B%BE%E5%83%8F/514135)。

## 题目描述

设 $S_k$ 表示直线 $l_{k1}:y=kx+k-1$，$l_{k2}:y=(k+1)x+k$ 与 $x$ 轴围成的三角形的面积，求：

$$\sum_{i=1}^nS_i$$

本题中，共有 $t$ 次询问，每次询问给出 $n_i$，求上式在 $n=n_i$ 时的取值。

若 $n<1$，该和式的值视作 $0$。

## 说明/提示

【样例解释】

当 $n=0$ 时，根据题意，输出 $0$。

当 $n=1$ 时，$S_1$ 就是 $y=x$、$y=2x+1$ 与 $x$ 轴所夹面积，为 $\dfrac{1}{4}$。

---

【数据范围】

- 对于 $5\%$ 的数据，$t \le 100,n=0$。
- 对于另外 $20\%$ 的数据，$t \le 100,n \le 2020$。
- 对于另外 $20\%$ 的数据，$t \le 5 \times 10^4,n \le 5 \times 10^3$。
- 对于 $100\%$ 的数据，$1 \le t \le 2 \times 10^6,0 \le n \le 2 \times 10^6$。

---

【说明/提示】

- 建议画图思考。
- **请注意输出答案的时候约分**。
- **请使用较快的读入方式**。

---

【文件读入读出】**（模拟，提交代码时不需使用）**

- 文件名：`function.cpp`
- 读入文件名：`function.in`
- 读出文件名：`function.out`

## 样例 #1

### 输入

```
2
0
1```

### 输出

```
0
1/4```

# 题解

## 作者：Thomas_Cat (赞：15)

$$\texttt{「RdOI R1」一次函数(function) 官方题解}$$

这里为了方便，拟了一个 $l_1,l_2$，仅为参考，阴影部分表示的就是要求的三角形的面积。

[![DEdMJe.png](https://s3.ax1x.com/2020/11/16/DEdMJe.png)](https://imgchr.com/i/DEdMJe)

对于直线 $l_1,l_2$，我们可以令 $y = 0$，则：

对于 $l_1$：

$$kx+k-1=0$$

$$kx=1-k$$

$$x=\dfrac{1-k}{k}$$

---

对于 $l_2$：

$$(k+1)x+k=0$$

$$(k+1)x=-k$$

$$x=-\dfrac{k}{k+1}$$

则，图像中三角形的底为

$\because \dfrac{1-k}{k}>-\dfrac{k}{k+1}$

$\therefore \dfrac{1-k}{k}-(-\dfrac{k}{k+1})=\dfrac{1}{k(k+1)}$

---

因此我们现在得到一个方程组：

$$\begin{cases}y=kx+k-1\\y=(k+1)x+k\end{cases}$$

则，

$$kx+k-1=(k+1)x+k$$

$$kx+k-1=kx+x+k$$

$$x=-1$$

当 $x=-1$ 时，$y=-1$。

则：$| -1 | = 1$。

则：图像中三角形的高为 $1$。

---

因此我们列出一个方程：

$S_1+S_2+S_3+\cdots+S_n$

$=\dfrac{1}{2} \times 1 \times(\dfrac{1}{1 \times (1+1)}+\dfrac{1}{2 \times (2+1)}+ \cdots +\dfrac{1}{n\times(n+1)})$

裂项后，得：

$=\dfrac{1}{2} \times 1 \times(1-\dfrac{1}{n+1})$

$=\dfrac{1}{2} \times \dfrac{n}{n+1}$

$=\dfrac{n}{2(n+1)}$

---

官方std：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n;
		scanf("%d", &n);
		if(n==0) puts("0");
		else{
		    int a=n;
		    int b=(n+1)*2;
		    int tmp=__gcd(a,b);
            printf("%d/%d\n", a/tmp, b/tmp);
		}
	}
	return 0;
}
```

---

## 作者：cwfxlh (赞：5)

本题是一道纯代数题 [P7127](https://www.luogu.com.cn/problem/P7127) ，解法如下。  
先求出 $ l_{k1} $ 与 $ l_{k2} $ 的交点:  
$ \quad kx+k-1=(k+1)x+k $  
$ \quad x=-1 $  
$ \quad y=-1 $  
再求出 $ l_{k1} $ 与 $ x $ 轴的交点:  
$ \quad kx+k-1=0 $  
$ \quad x=\frac{1-k}{k} $  
$ \quad y=0 $  
再求出 $ l_{k2} $ 与 $ x $ 轴的交点:  
$ \quad (k+1)x+k=0 $  
$ \quad x=\frac{-k}{k+1} $  
$ \quad y=0 $  
那么：  
$ S_k=\dfrac{1*\vert{\frac{1-k}{k}-\frac{-k}{k+1}}\vert}{2} $  
$ \quad =\dfrac{1}{2k(k+1)} $ 

$ \sum_{i=1}^{n}S_k=\frac{1}{2}(\frac{1}{1\cdot2}+\frac{1}{2\cdot3}+\frac{1}{3\cdot4}+...+\frac{1}{k\cdot(k+1)}) $  
$ \quad =\dfrac{k}{2(k+1)} $  

所以只需要输出 $ \dfrac{k}{2(k+1)} $ 就可以了。注意化简。  
贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&n);
		if(n<1)printf("%d\n",0);
		else printf("%d/%d\n",(n/__gcd(n,2)),(2*(n+1)/__gcd(n,2)));
	}
	return 0;
}
```


---

## 作者：Eason_AC (赞：5)

## Content
设 $S_k$ 为直线 $f(x)=kx+k-1$，直线 $f(x)=(k+1)x+k$ 与 $x$ 轴围成的三角形的面积。现在给出 $t$ 组询问，每组询问给定一个整数 $n$，求 $\sum\limits_{i=1}^n S_i$。结果用分数表示。

**数据范围：$1\leqslant t\leqslant 2\times 10^6.0\leqslant n\leqslant 2\times 10^6$。**
## Solution
很简单的一道找规律题目。

我们发现，形如 $f(x)=kx+k-1$ 的直线都会经过 $(-1,-1)$ 这个点。我们再稍微画几个图就能够发现，题目所要求的东西，无非就是以 $(0,0),(-1,-1)$ 以及最后一个 $S_i$，也就是 $S_n$，被约束的后一条直线 $f(x)=(n+1)x+n$ 与 $x$ 轴的点为三个顶点的三角形的面积罢了。而且很容易发现，我们的三角形如果以在 $x$ 轴上的边为底边的话，它的高自然就是 $1$。再说，这条 $x$ 轴上的边也很容易求出来：只需要求 $f(x)=(n+1)x+n$ 这条直线与 $x$ 轴的交点，再取个绝对值就好了。我们很容易求出上面所说的那条直线与 $x$ 的交点为 $(-\dfrac{n}{n+1},0)$。所以那条底边的长度就是 $\dfrac{n}{n+1}$。

因此，这道题目的答案，也就是 $\sum\limits_{i=1}^nS_i=\begin{cases}0&n=0\\\dfrac{n}{2(n+1)}&n>0\end{cases}$。注意：

- $n=0$ 的时候，显然无法构成一个三角形，因此面积为 $0$。
- 注意约分，直接将分子和分母同时除以它们的最大公约数（也就是 $\gcd\{n,2(n+1)\}$）就好。

只是一时兴起想做道题目，不意味着正式回归。

但是，请等着我。

## Code
请注意 $\textsf{NOI}$ 系列赛事不支持 algorithm 库的 `__gcd` 函数。建议自己写个 gcd 函数，反正又不难，对吧？

什么，要 gcd 函数？下面：

```cpp
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);} //数据类型根据实际情况适当调整
```

下面的是正式的代码，注意直接拿这个代码编译是不会通过的。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        if(!n) puts("0");
        else printf("%d/%d\n", n / gcd(n, 2 * (n + 1)), 2 * (n + 1) / gcd(n, 2 * (n + 1)));
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：4)

这是企鹅的第一篇题解，由于这道题是我在洛谷第一次参加的[比赛](https://www.luogu.com.cn/contest/38025)的题A，当时成功AC，可谓开门红，而碰巧此时此题题解区开放，所以企鹅写下了这篇题解。  

题目传送>>[P7127](https://www.luogu.com.cn/problem/P7127)。  
### 题意简述  
- $S_k$为直线$l_{k1}:y=kx+k-1$，$l_{k2}:y=(k+1)x+k$与$x$轴围成的三角形的面积；  
- 给定$t$组$n$,求$\sum_{i=1}^{n}{S_i}$；  
- 若$n<1$，则和式值为0。  
- 结果可能是分数，需约分至最简分数，使用$x/x$表示。
### 题目分析  
#### 思路：  
利用一次函数图象上的点的坐标特征可求出直线$l_1$、$l_2$与$x$轴的交点坐标，联立两函数解析式成方程组，通过解方程组可求出两直线的交点坐标，利用三角形面积公式可得$S_k$，将其代入$S_1+S_2+S_3+...+S_n$。  
#### 解析：  
![JieXi](https://cdn.luogu.com.cn/upload/image_hosting/s5slqse6.png)  
令$y=0$：  
$l_1:$  
$$kx+k-1=0$$
$$kx=1-k$$
$$x=\frac{1-k}{k}$$  
$l_2:$
$$(k+1)x+k=0$$
$$(k+1)x=-k$$
$$x=-\frac{k}{k+1}$$
所以直线$l_1$与$x$轴的交点坐标为$(\frac{1-k}{k},0)$，直线$l_2$与$x$轴的交点坐标为$(-\frac{k}{k+1},0)$。  
联立两直线解析式成方程组，  
$$\begin{cases}y=kx+k-1\\y=(k+1)x+k\end{cases}$$  
解得  
$$\begin{cases}x=-1\\y=-1\end{cases}$$  
$∴$两直线的交点为$(-1,-1)$。   

$∴$ 
$S_k$  
$=\frac{1}{2}×|-\frac{k}{k+1}-\frac{1-k}{k}|×|-1|$  
$=\frac{1}{2k(k+1)}$  
$=\frac{1}{2}(\frac{1}{k}-\frac{1}{k+1})$     

$∴\sum_{i=1}^{n}{S_i}$  
$=\frac{1}{2}×(1-\frac{1}{2})+\frac{1}{2}×(\frac{1}{2}-\frac{1}{3})+\frac{1}{2}×(\frac{1}{3}-\frac{1}{4})+...\frac{1}{2}×(\frac{1}{n}-\frac{1}{n+1})$  
$=\frac{1}{2}×(1-\frac{1}{2}+\frac{1}{2}-\frac{1}{3}+\frac{1}{3}-\frac{1}{4}+...+\frac{1}{n}-\frac{1}{n+1})$  
$=\frac{1}{2}×(1-\frac{1}{n+1})$  
$=\frac{1}{2}×\frac{n}{n+1}$  
$=\frac{n}{2n+2}$  
  
  $Code：$  
```cpp
#include<iostream>
using namespace std;
#define endl '\n'//利用宏定义加速 endl换行 
int n[2000001];//开数组存每次输入的n。当然也可以不开，一边输入一边输出 ......
int gcd(int m,int n)//定义一个函数，采用递归实现辗转相除法求最大公约数 
{
	return n==0? m:gcd(n,m%n);
}
int main()
{
	ios::sync_with_stdio(0); //关闭同步流，加速cin输入和cout输出 
	int t;//定义组数
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>n[i];
    }
    for(int i=1;i<=t;i++)
    {
        if(n[i]==0)//特判n为0 
        {
            cout<<"0"<<endl;//注意换行 
        }
        else
        {
        	int a,b;//定义分子，分母 
        	a=n[i];
        	b=2*n[i]+2;
            cout<<a/gcd(a,b)<<"/"<<b/gcd(a,b)<<endl; //分子和分母分别除以它们的最大公约数即达到化简分数的目的 
        }
    }
    return 0;//结束整个程序 
}
```  

### 结果(未吸氧)：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ujnv08zs.png)  
至此，企鹅的第一篇题解已认认真真地完成了，希望各位OIers进步~

---

## 作者：Remake_ (赞：2)

sb题，感觉可以评红（

题目要求$l_{k1},l_{k2}$与$x$轴所围成的三角形的面积。

要求三角形的面积首先我们需要知道他的三点所在。

先把三线的所有交点求出来吧：

$l_{k1}$与$l_{k2}$的交点：

$$kx+k-1=(k+1)x+k$$

$$kx+k-1=kx+x+k$$

$$x=-1$$

将$y=kx+k-1$代入$x=-1$得到$y=-k+k-1=-1$。

所以其中一个点是$(-1,-1)$。

$l_{k1}$与$x$轴的交点：

点在$x$轴上说明纵坐标为$0$。

$$kx+k-1=0$$

$$kx=1-k$$

$$x=\frac{1-k}{k}$$

所以其中一个点是$(\frac{1-k}{k},0)$。



$l_{k2}$与$x$轴的交点：

点在$x$轴上说明纵坐标为$0$。

$$kx+x+k=0$$

$$(k+1)x=-k$$

$$x=-\frac{k+1}{k}$$

所以其中一个点是$(0,-\frac{k+1}{k})$。

套用~~海伦公式~~三角形基本面积公式得到：

$$S_i=\frac{\frac{1}{k(k+1)}}{2}$$

$$\sum_{i=1}^n S_i=\frac{\sum\limits_{i=1}^n\frac{1}{i(i+1)}}{2}$$

上面的这个东西裂项化简得：

$$\sum_{i=1}^n S_i=\frac{\frac{k}{k+1}}{2}$$

所以最终答案就是：

$$\frac{k}{2k+2}$$

使用$\gcd$约分即可QwQ

代码：
```cpp
int main(){
    T=rd();
    while(T--){
        k=rd();
        if(k==0) printf("0\n");
        else printf("%d/%d\n",k/__gcd(k,2*k+2),(2*k+2)/__gcd(k,2*k+2));
    }
    return 0;
}
```


---

## 作者：一只书虫仔 (赞：2)

#### Description

> 定义 $S_k$ 为如下两个函数与 $x$ 轴相交的三角形面积：
> $$f_1(x)=kx+k-1,f_2(x)=(k+1)x+k$$
> 给定 $t$ 组 $n$，求：
> $$\sum\limits_{i=1}^n S_i$$

#### Solution

这个部分分不是很懂怎么做，所以来搞一个最终解（

既然题目说要求用两个一次函数，那么就用上我们万能的 [desmos](https://www.desmos.com/calculator?lang=zh-CN)。

首先我们画出 $n=1$ 的图形：

![](https://cdn.luogu.com.cn/upload/image_hosting/qdh0xh50.png)

围成的三角形面积为 $\dfrac{1}{2} \times 1 \times \dfrac{1}{2}$。

然后 $n=2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/os9vzxmx.png)

我已经把关键点 $(-0.667,0)$，他其实就是 $\left(-\dfrac{2}{3},0\right)$，那么围成的三角形面积就是 $\left(\dfrac{2}{3}-\dfrac{1}{2}\right) \times 1 \times \dfrac{1}{2}$。

然后 $n=3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/422vp29d.png)

两个关键点是 $\left(-\dfrac{3}{4},0\right)$ 和 $\left(-\dfrac{2}{3},0\right)$，三角形面积就是 $\left(\dfrac{3}{4}-\dfrac{2}{3}\right)\times 1 \times \dfrac{1}{2}$。

（你可以尝试让 $n$ 趋近于 $\infty$，在 $n=10$ 的时候就已经很明显了：

![](https://cdn.luogu.com.cn/upload/image_hosting/ktb2eqcu.png)

当 $n$ 趋近于 $\infty$ 时，三角形面积趋近于 $0$，~~然而跟这题没啥关系只是偶然发现的~~）

不难发现，当 $n=p$ 的时候，三角形面积为 $\left(\dfrac{p}{p+1}-\dfrac{p-1}{p}\right)\times \dfrac{1}{2}$，简单化简一波：

$$\begin{aligned}\left(\dfrac{p}{p+1}-\dfrac{p-1}{p}\right)\times \dfrac{1}{2}&=\dfrac{p^2-1}{p \times (p+1)}\times\dfrac{1}{2}\\&=\dfrac{1}{p \times (p+1)} \times \dfrac{1}{2}\end{aligned}$$

然后把这个代入到题目里，把 $\dfrac{1}{2}$ 提出来：

$$\begin{aligned}\dfrac{1}{2}\sum\limits_{i=1}^n\dfrac{1}{i \times (i+1)}&=\dfrac{1}{2}\sum\limits_{i=1}^n\left(\dfrac{1}{i}-\dfrac{1}{i+1} \right)\\&=\dfrac{1}{2}\left(1-\dfrac{1}{n+1}\right)\\&=\dfrac{n}{2n+2}\end{aligned}$$

只有当 $n \bmod 2=0$ 时才会约分为 $\dfrac{\frac{n}{2}}{n+1}$，其他情况都不会约分。

因此简单的代码也就有了。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		if (n == 0) puts("0");
		else if (n % 2 == 0) printf("%d/%d\n", n / 2, n + 1);
		else printf("%d/%d\n", n, 2 * n + 2);
	}
	return 0;
}
```

---

## 作者：漠寒 (赞：1)

## 分析

很简单的一道找规律的题目，经过列出前几个数的两条函数可以发现，$i$ 的$l_2$ 就是 $i+1$ 的$l_1$，并且对于每一个 $i$，它的两条直线的交点的横坐标与纵坐标都为-1，而 $i$ 为1时的 $l_1$ 已经与坐标原点有交点，之后每一条直线与 $x$ 轴的交点都在一个个向左移，因此我们只需要知道最左边的那一条与 $x$ 轴的交点，再将它除以2（~~三角形面积公式~~），再进行一次取最大公因数化简即可

### 代码（主要是分析，代码无看点）

```
#include<bits/stdc++.h>
using namespace std;
int t,n,fz,fm,gys;
inline int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}

inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+c-48;c=getchar();}
	res*=f;
}
int main()
{
	cin>>t;
	while(t--){
		read(n);
		if(n<1){//特判 
			puts("0");continue;
		}
		fz=n;//分子 
		fm=(n+1)*2;//分母 
		gys=gcd(fz,fm);//最简分数 
		printf("%d/%d\n",fz/gys,fm/gys);
	}
	return 0;
}
```


---

## 作者：juun07 (赞：1)

蒟蒻的第一篇题解来了！


------------

# 一次函数

一次函数！y=kx+b！

~~（初二学生噩梦）~~

这道题看似复杂，实际上只需要很短的代码就能实现，所以重在理解题意

### 如图，蓝色的面积即为所求

![](https://cdn.luogu.com.cn/upload/image_hosting/afusq9yq.png)

### ~~是不是很简单易懂(~~

可以很容易的看出

答案就是
```
n/[(n+1)*2]
```


因此循环，输入，判断，输出即可

然后我们又看到了：
```
请注意输出答案的时候约分。
```

？？？

转头一想，约分其实就是求两个数的最大公因数啊！

g c d

完美解决！

# 代码（拒绝代码抄袭，共创美好洛谷）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int a,int b)//辗转相除 不多解释 
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
int main()
{
	int c,n,a,b,tmp;
	scanf("%d",&c);
	while(c--)
	{
		scanf("%d",&n);//一定要用scanf，不然TLE（血的教训） 
		if(n==0)//特判，具体见题目 
		{
			puts("0");
		}
		else
		{
		    a=n;
		    b=(n+1)*2;
		    tmp=gcd(a,b);//求最大公约数 ，化简分数 
            cout<<a/tmp<<"/"<<b/tmp<<"\n";
		}
	}
	return 0;//好习惯( 
}
```

## 完结撒花！！


------------
第一篇题解求过！！

（点个赞吧！）

---

## 作者：lskksl (赞：0)

这道题有两个思路：

#### approach1：
带数进去，从 k=0 一直试下去，你会找到规律的。

当然，上面的不是正解。

#### approach2：
你可以脑补一下，既然三角形的三边有一条在 x 轴上，另外两条不确定，当然选择 x 轴的边作为底了。而另外两条直线均交于 x 轴，则它们交于 x 轴的坐标之间的距离，即这个三角形的底。

$l_{k1}$ 与 x 的交点坐标：即当 y=0 时，可求得：
   $$kx+k-1=0$$
   $$kx=1-k$$
   $$x=\dfrac{1-k}{k}$$
$l_{k2}$ 与 x 的交点坐标：即当 y=0 时，可求得：
   $$(k+1)x+k=0$$  
   $$(k+1)x=-k$$ 
   $$x=-\dfrac{k}{k+1}$$
然后你想啊，正数>负数，则:
$$∴\dfrac{1-k}{k}>-\dfrac{k}{k+1}$$
∴两点间的距离(三角形的底)：
$$\dfrac{1-k}{k}-(-\dfrac{k}{k+1})=\dfrac{1}{k(k+1)}$$
而三角形的高，则是 $l_{k1}$ 与 $l_{k2}$ 的交点的 |y|，并且，他们的 y 相同。
$$kx+x-1=kx+x+k$$
$$x=-1$$
$$∴y=|-1|=1$$
∴三角形的高为1。

因此：
$$S_{k}=\dfrac{1}{2}×1×\dfrac{1}{k(k+1)}=\dfrac{1}{2k(k+1)}$$
然后你再把原题要求的在纸上一算，会发现答案为：
$$\dfrac{n}{2(n+1)}$$

至于约分，将答案除以一个他的分子和分母的最大公因数即可。

---

## 作者：Cocoly1990 (赞：0)

介绍一个数学方法 

假设 $l_{k1}$ 交 $x$ 轴与 $\texttt{A}$, $l_{k2}$ 交 $x$ 轴与 $\texttt{B}$，$l_{k1}$ 交 $l_{k2}$ 轴与 $\texttt{C}$

![image.png](https://i.loli.net/2021/07/09/ni675J4HIEwQk8a.png)

如图红色的直线是 $l_{k1}$， 蓝色 $l_{k2}$.很显然，目标三角形的面积是
$$S_{\triangle ABC}=\frac{1}{2}\times \texttt{AB} \times |y_c|$$
我们以依次处理上面的未知部分。首先先算出 $\texttt{A},\texttt{B},\texttt{C}$ 的坐标，特别的是，我们并不需要全求，对于 $\texttt{A},\texttt{B}$ 仅需得出横坐标

则 $x_A$ 是 $y = 0$ 时 $l_{k1}$ 的函数值，即 $x_A$ 是如下方程的根
$$kx+x-1=0$$
解得
$$x=\frac{1-k}{k}$$
即
$$x_A=\frac{1-k}{k}$$
同理有
$$x_B=-\frac{k}{k+1}$$
同理
$x_C=-1$ 此时 $y_C=-1$ 

有因为$k>0$ 则 $\dfrac{1-k}{k}>-\dfrac{k}{k+1}$.
即$\texttt{AB}=\dfrac{1-k}{k}-(-\dfrac{k}{k+1})=\dfrac{1}{k(k+1)}$

那么
$$S_{k}=\frac{1}{2}\times \dfrac{1}{k(k+1)}$$
则
$$\sum\limits_{k=1}^n{S_k}=\frac{1}{2}\times(\dfrac{1}{1(1+1)}\times \dfrac{1}{2(2+1)}\times...\times\dfrac{1}{n(n+1)})$$
小学裂项有
$$\sum\limits_{k=1}^n{S_k}=\frac{n}{2(n+1)}$$
$O(1)$处理上式即可。




---

## 作者：luosw (赞：0)

### 前置知识

- ~~解析几何~~；
- 三角形面积公式 $S=\dfrac{1}{2}ah$；
- 平面直角坐标系中点 $A$ 的横坐标为 $x_A$，纵坐标为 $y_A$。

### 题目

首先，一次函数的图像不可能与 $x$ 轴平行。利用解析几何相关知识，我们可以判定：两平行直线的斜率相等，而 $k$ 和 $k+1$ 显然不等，因此构成的三角形退化的情况不存在。

我们以直线 $\ell_1,\ell_2$ 和 $x$ 轴组成的三角形的底为在 $x$ 轴上的边，则其高为 $|y_{\ell_1\cap \ell_2}|$，底为 $|x_{x\cap\ell_1}-x_{x\cap\ell_2}|$。

因此，要求出 $S_i$ 的底 $a$，高 $h$，我们需要求出下面三个点的坐标：$\ell_1\cap \ell_2,x\cap\ell_1,x\cap\ell_2$，即三角形三个顶点的坐标。

容易得到 $\ell_1\cap \ell_2=(-1,-1),x\cap\ell_1=(\dfrac{1-k}{k},0),x\cap\ell_2=(-\dfrac{k}{k+1},0)$。

因此 

$$
S_k=\dfrac{1}{2k(k+1)}.
$$

于是

$$
\sum\limits^n_{k=1}S_k=\dfrac{n}{2n+2}.
$$

单独处理分子和分母，同时去除 $\gcd(n,2n+2)$ 即可。

---

## 作者：Lacrymabre (赞：0)

题意简述：

给定一个$n$，求对于函数 $l_1:y=kx+k-1$ 和 $l_2:y=(k+1)x+k$ 对于他们从 $1$ 到 $n$ 与 $x$ 轴的交点和他们两个函数的交点的面积之和。

记 $x$ 取 $i$ 时的值为 $s_i$，答案就是$\sum_{i=1}^n s_i$.

拿到这个题目，我们想到画图探究。

* 先来进行代数推导。联立 $l_1,l_2$我们可以得到：$kx+k-1=kx+x+k$

化简得 $x+1=0$ ，即 $x=-1$，代入任何一个函数得 $y=-1$，也就是说，这两个函数总是交于 $(-1,-1)$ 这个点。

**结论一：三角形的高恒为1**

* 画图

分别画出 $x=1$ 和 $x=2$ 的情况：

![x=1](https://cdn.luogu.com.cn/upload/image_hosting/4oh1rexx.png)
----------
![x=2](https://cdn.luogu.com.cn/upload/image_hosting/7jcep51p.png)
------------

容易发现，当 $x=1$ 时 $l_1$和$x$交于$0$，$l_2$与$x$交于$-\frac12$，所以$d_{i=1}=0-\frac12=\frac12$

当 $x=2$ 时 $l_1$和$x$交于$-\frac12$，$l_2$与$x$交于$-\frac23$. 所以$d_{i=2}=-\frac23-(-\frac12)=\frac16$

此时面积总和即为 $s=\frac{(d_1+d_2)*1}{2}$

还原$d$代入得$s=(\frac{1-\frac12+\frac23-\frac12}2)= \frac{\frac23}{2}=\frac13$

容易发现，只有$\frac{n}{n+1}$对最终的答案造成影响，我们便可以得到 $O(1)$ 的最终柿子: $s=\frac{n}{2n+2}$

最后简单的判断和约分即可，连分数类都不用封装。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline long long read()
{
    ll f=1,s=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*f;
}

ll t,n;

ll gcd(ll x,ll y){
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
	t=read();
	while(t-->0){// will be fast
		n=read();
		ll x=n,y=2*n+2;
		if(!x||!y) {cout<<0<<endl;continue;}
		ll Q=gcd(x,y);
		x/=Q,y/=Q;
		printf("%lld/%lld\n",x,y);
	}
}
```



---

