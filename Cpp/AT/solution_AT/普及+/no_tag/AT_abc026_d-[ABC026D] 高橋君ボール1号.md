# [ABC026D] 高橋君ボール1号

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc026/tasks/abc026_d

高橋君は野球が得意です。高橋君は、高橋君ボール $ 1 $ 号という変化球を投げることが出来ます。

このボールは、投げてから $ t $ 秒後のボールの位置を $ f(t) $ とすると、 $ f(t)\ =\ A\ \times\ t\ +\ B\ \times{\rm\ sin}(C\ \times\ t\ \times\ π) $ と表すことが出来ます。

あなたは、$ t\ ≧\ 0 $ かつ $ f(t)\ =\ 100 $ となるタイミングで、ボールを打たなければいけません。この時の $ t $ を求めたいです。

## 说明/提示

### Sample Explanation 1

$ t\ =\ 100 $ のとき、 $ f(t)\ =\ 100 $ となります。

### Sample Explanation 2

解が一つではないことに注意してください。

## 样例 #1

### 输入

```
1 1 1```

### 输出

```
100```

## 样例 #2

### 输入

```
53 82 49```

### 输出

```
1.63372043395339```

# 题解

## 作者：Walter_Fang (赞：5)

非常明显的小数二分。我们只需要根据给定函数求出 $f(x)$ 的值，然后二分使得答案最接近 100 即可。

那么二分的终止条件是什么呢？其实这里并不需要给定终止条件，只要在不超时的情况下多做几次就可以了。因为题目只是让我们求出合理解，并非最小解。

另外还有一点需要注意的是， C++ 中并未给出圆周率 $\pi$ 的值，那么我们可以用 `acos` 函数求出来。

`acos` 函数其实是用于求以弧度表示的 $x$ 的反余弦，弧度区间为 $(0,\pi)$ ，然而其现在经常用于求圆周率的近似值。

最后贴上带有注释的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1.0);  //求圆周率pi 
double a,b,c,l,r,x;
int i;
double f(double x){  //题目中给出的f(x)函数 
	return a*x+b*sin(c*x*pi);
}
int main(){
    cin>>a>>b>>c;
    l=1;r=INT_MAX;  //区间限定 
    for(i=1;i<=114514;i++){  //二分多做几次 
        x=(l+r)/2;
        if(f(x)<=100)l=x;
        else r=x;
    }
    printf("%.12lf",l);  //进行输出 
}
```

---

## 作者：0x00AC3375 (赞：3)

## 大致题意
求解方程 $Ax+B\sin(C\pi x)-100=0$ 的近似解。

## 解答

本题的方程对应的函数 $f(x)=Ax+B\sin(Cπx)-100$ 并不是一个严格的单调函数，因此二分法不一定能立刻想到。除了二分法以外，本题可以使用[牛顿法](https://baike.baidu.com/item/%E7%89%9B%E9%A1%BF%E9%80%BC%E8%BF%91%E6%B3%95/1516472?fr=ge_ala)求解。

由于 $f(x)=Ax+B\sin(Cπx)-100$

则导函数 $f'(x)=A+BC\pi \cos(C\pi x)$

根据牛顿法的近似公式 $x_{n+1}=x_n-\dfrac{f(x_n)}{f'(x_{n})}$ 即可将这个问题直接转化为一个递推问题，当相邻两项的差值小于给定的精度时即可结束递推输出答案。本题由于已经规定了 $A,B,C$ 皆为 $[1,100]$ 范围内的整数，因此初始值 $x_0$ 也就是代码中的 `sln[0]`，可以选择从 $\dfrac{100}{A}$ 开始。

需要说明的是：
1. 牛顿法通常比二分法收敛更快，适用于不具有单调性的场合，但是前提是所求的表达式**必须在指定的区间上可导**。
2. 牛顿法的局限性在于只能求出方程某一个特定的近似解（如果方程有多解）。换用不同的初始值，得到的近似解也可能不同。本题要求对于可能的多解输出任意一个解即可，因此牛顿法可以通过此题。
3. 如果使用 `long double` 类型来存储答案，计算乘幂、三角函数和对数等需要使用函数 `powl`，`sinl`，`cosl`，`log10l` 等来进行计算，输入/输出需要使用格式字符串 `"%Lf"`。

## AC 代码
```
#include<cmath>
#include<iostream>
using namespace std;
long double A,B,C,pi=3.1415926535897932385L,eps=1e-10L;
long double sln[10000];
//The function.
long double F(long double x)
{
	return A*x+B*sinl(C*pi*x)-100.L;
}
//The derivate function of F.
long double derivateF(long double x)
{
	return A+B*C*pi*cosl(C*pi*x);
}
int main()
{
	cin>>A>>B>>C;
	int r=0;
	sln[0]=100.L/A;
	while(r<=9998)
	{
		sln[r+1]=sln[r]-1.0L*F(sln[r])/derivateF(sln[r]);
		if(fabs(sln[r+1]-sln[r])<=eps) break;
		r+=1;
	}
	printf("%.14Lf",sln[r]);
}
```
2023.08.21 更新：修正公式中的一处错误，增加一些补充说明。

---

## 作者：ys2012 (赞：2)

### 思路

解方程可以直接小数二分。

方程式 $a \times mid + b \times \sin(c \times mid \times \pi)$。其中 $mid$ 为未知数，也是二分中的中间值。

* 注意：小数二分用 double 不要用整形变量。

### ACcode
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
#define ll long long
#define fast ios::sync_with_stdio(0);cout.tie(0);cin.tie(0); 
double a,b,c;//参与小数运算用 double 
const double pi=3.14159265358979323846264338327;
double fac(double mid){
	return a*mid+b*sin(c*mid*pi);//求 mid 于公式内的答案 
} 
signed main()
{
	fast; 
	cin>>a>>b>>c;
	double l=0,r=3e9;//小数二分用 double 定义变量 
	for(ll laoda=1;laoda<=1000000;++laoda){//二分 
		double mid=(l+r)/2;//给定 mid 为中间值
		if(fac(mid)<=100){//判断如何改变左值和右值的条件
			l=mid;
		}else{
			r=mid;
		}
		
	}
	
	printf("%.12lf",l);//输出 
}
```

---

## 作者：AkeRi (赞：2)

这题绿？
# Description
有函数 $f(x)=ax+b\sin(cx\pi)$，给定 $a,b,c$，求 $f(x)=100$ 时的一个解。

# Solution
~~用工具画一画~~可得这个函数是一个弯曲着上升的图像。

Like this:
![](https://cdn.luogu.com.cn/upload/image_hosting/pbki5xuk.png)

我们虽然可以自然而然想到二分求函数图像指定值时的解，但是它不是一个完全单调的函数。

这是对的。为什么？

### 1.解只有一种情况时：

![](https://cdn.luogu.com.cn/upload/image_hosting/qauq1nip.png)

以样例的图像为例，如图所示，假设蓝线 $x=98$ 是二分的左边界，绿线 $x=105$ 是二分的右边界，紫线 $x=101.5$ 是中间值，黑线是直线 $y=100$。则显然对于解 $(100,100)$ 表示的点左边一定满足 $f(x)\lt 100$，右边的点满足 $f(x)\gt 100$，因此对于只有一个解的情况，二分是正确的。

### 2.解有多组情况时：

![](https://cdn.luogu.com.cn/upload/image_hosting/uecaod9p.png)

以函数 $f(x)=x+2.7\sin(2\pi x)$ 的图像为例，如图所示，仍然假设蓝线 $x=98$ 是二分的左边界，绿线 $x=105$ 是二分的右边界，紫线 $x=101.5$ 是中间值。那么，看一下二分的过程：

1. $mid=101.5,f(mid)=101.5\gt100$，则移动右边界到 $mid$。
2. $mid=99.75,f(mid)=97.05$， 则挪动左边界到 $mid$。
3. ...

我们每次舍弃了一些解，但是总是在接近某一组特定的解。题目要求找到一个可行解而非最小解，所以二分是正确的。

```cpp
/*

by L1rs1ngzN1sLyr

*/
#include<bits/stdc++.h>
const int AI=1e3+9;
const int KI=1e6+2;
const int CI=1e7+3;
const double eps=1e-7;
const double Pi=3.1415926535897932384626;
int read(){int x=0,w=1;char ch=0;while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}return x*w;}
double a,b,c;
double f(double x){return a*x+b*std::sin(c*x*1.0*Pi);}
int main()
{
    std::cin>>a>>b>>c;
    double l=1,r=1e9;
    for(int i=1;i<=500;i++)
    {
        double mid=(l+r)/2.0;
        if(f(mid)>100) r=mid;
        else l=mid;
    }
    printf("%.12lf",l);
}
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的二分问题(当然对于新手来说不友好)。

本题目要我们在有函数 $f(x)$，给定 $a, b, c$，求 $f(x)=100$ 时的解。

所以我们可以在当 $f(mid)≤100$ 时，重置左端点。

如果不行的话，直接重置右端点即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
double a,b,c,ans;
const double pi=3.14159265358979323846264338327;
double f(double x)
{
	return a*x+b*sin(c*x*pi);
}

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> a >> b >> c;
	double l=0,r=3e9;
	for(long long i=1;i<=1145141;i++)
	{
		double mid=(l+r)/2;
		if(f(mid) <= 100)
		{
			l=mid,ans=mid;
		}
		else
		{
			r=mid;
		}
	}
	printf("%.12lf",ans);
	return 0;
}
``````

---

## 作者：eric0928 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc026_d)

### 前提算法
实数二分，这道题用的是实数二分中的小数二分。

### 题面
有函数 $f(x)$，给定 $a,b,c$，求 $f(x)=100$ 时的解。

### 解题思路
二分，当 $f(mid)\le100$ 时，重置左端点，否则重置右端点。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
const db pi = acos(-1.0);
db a, b, c, l = 1, r = INT_MAX;
db f(db x) {
	return a * x + b * sin(c * x * pi);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b >> c;
	for (int i = 1; i <= 1e6; i++) {
		double mid = (l + r) / 2;
		if (f(mid) <= 100) l = mid;
		else r = mid;
	}
	printf("%.12lf", l);
	return 0;
}

```

---

## 作者：_AyachiNene (赞：0)

# 思路：
把图像画出来，发现这个函数是有单调性的，所以直接用二分就行了。这里有几个细节，就是这道题的二分边界不好确定，可能导致精度丢失，所以在时限内能分多少次就分多少次，还有这道题二分的值域很大，上界要调到 $3\times10^9$。
# Code：
```cpp
#include<bits/stdc++.h>
#define db double
using namespace std;
db a,b,c,ans;
const db pi=3.14159265358979323846264338327;
db f(db x)
{
	return a*x+b*sin(c*x*pi);
}
int main()
{
	cin>>a>>b>>c;
	db l=0,r=3e9;
	for(int i=1;i<=1145141;i++)
	{
		db mid=(l+r)/2;
		if(f(mid)<=100)
			l=mid,ans=mid;
		else
			r=mid;
	}
	printf("%.10lf",ans);
	return 0;
}

```


---

## 作者：maple_trees_112 (赞：0)

### 前提算法知识点

这道题对新手有一点不友好，我们经常把实数二分挂在嘴上，但是实数二分里也分类，这道题用的就是小数二分。

### 解题思路

这道题本质求的是 $f(x) = 100$ 时的一个解。

二分思路是就是站在 $f(mid) \le 100$ 时，将左端点重置。否则，就重置右端点。

不过呢这里需要注意， $pi$ 的取值需要用到 $acos$ 函数，想了解的点[这里](https://www.python100.com/html/71519.html)。

```cpp
#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
double a,b,c,l = 1,r = 1e9;
inline double f(double x) 
{ 
    return a * x + b * sin(c * x * pi); 
}
int main()
{
    std::cin>>a>>b>>c;
    for(int i = 1; i <= 100; i++)
    {
        double mid = (l + r) / 2;
        if(f(mid) <= 100) 
            l = mid;
        else 
            r = mid;
    }
    std::cout<<l<<endl;
    return 0;
}
```


---

## 作者：Prolystic (赞：0)

## Part I Preface

[原题目(洛谷)](https://www.luogu.com.cn/problem/AT_abc026_d)

[原题目(AtCoder)](https://atcoder.jp/contests/abc026/tasks/abc026_d)
## Part II Sketch

- 有函数 $f(x) = ax + b\sin(cx\pi)$。
- 给定 $a, b, c$，求 $f(x) = 100$ 解集中任意一个解的值。

## Part III Analysis
使用某些工具描出函数图像之后，我们不难发现可以二分求解。事实上这个函数并非绝对的单调，不过已经有高手解释过了，我就不多赘述。

可能有人会疑惑，我们到底到什么时候结束二分？事实上，题目只要求解集中的任意一个解即可，无论它在哪里。所以不妨直接按次数进行二分，通过多次计算答案值，以达到精确度更高的目的。C++ 并未给出现成的 $\pi$ 值，但是我们可知 $\cos(180\degree) = -1$，而 $180\degree = \pi\operatorname{Rad}$，那么 $\pi$ 的值就可以用反余弦函数求得，即 $\arccos(-1)$（注意，这里的 $-1$ 是弧度而非角度）。

整体思路：按照次数进行二分，每次取中点 $mid$，若 $f(mid) \leq 100$，将左端点 $l$ 移动到 $mid$；若 $f(mid) > 100$，则移动右端点至 $mid$。最后，输出 $l$ 保留 $12$ 位小数即可。

## Part IV Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
double a, b, c;
inline double f(double x) { return a * x + b * sin(c * x * pi); }
int main(){
    scanf("%lf%lf%lf", &a, &b, &c);
    double l = 1, r = 1e9;
    for(int i = 1; i <= 100; i++){
        double mid = (l + r) / 2;
        if(f(mid) <= 100) l = mid;
        else r = mid;
    }
    printf("%.12lf", l);
    return 0;
}
```

## Part V Record

![](https://cdn.luogu.com.cn/upload/image_hosting/grmxugtv.png)

[Record(AtCoder)](https://atcoder.jp/contests/abc026/submissions/44588526)

---

