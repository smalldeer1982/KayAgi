# Meme Problem

## 题目描述

给出一个非负整数d，请你找出两个非负实数a和b，使得a+b=d并且a*b=d

## 样例 #1

### 输入

```
7
69
0
1
4
5
999
1000
```

### 输出

```
Y 67.985071301 1.014928699
Y 0.000000000 0.000000000
N
Y 2.000000000 2.000000000
Y 3.618033989 1.381966011
Y 997.998996990 1.001003010
Y 998.998997995 1.001002005
```

# 题解

## 作者：FCB_Yiyang2006✈ (赞：7)

# 这道题...

也许不是很难...

## 1.思路
#### ab=d
#### a+b=d!
### 又有ab,又有a+b--伟大的定理！（韦达）
于是乎...
#### 构造出方程：x^2-d*x+d=0(a,b是方程的两实根)

#### 判断是否有a,b实际上就是判断方程是否有实根。
### ∆（判别式）
### 走起！！！
#### 如果∆<0 输出N，结束！
#### 如果∆>=0,求根公式保留九位小数，结束！

## 2.补充
### （1）韦达定理

![](https://cdn.luogu.com.cn/upload/pic/69687.png)
这里用的是逆定理

![](https://cdn.luogu.com.cn/upload/pic/69689.png)

### （2）不用判断a,b是否非负

1.ab=d>=0
#### a,b同正或同负
2.a+b=d>0
#### a,b只能同正

## 上代码（蒟蒻代码，仅供参考）
```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
int d,t;
double a,b,delta;
int main()//主晗二叉树
{
	cin>>t;//组数
	for(int i=1;i<=t;i++)
	{
		cin>>d;
		delta=d*d-4*d;
		if(delta<0)
		{
			cout<<'N'<<endl;
		}
		else
		{
			cout<<'Y'<<" ";
			a=(d*1.0+sqrt(delta))/2;
			b=(d*1.0-sqrt(delta))/2;//求根公式
			printf("%.9lf %.9lf\n",a,b);//保留九位小数
		}
	}
	return 0;//结束了！结束了！结束了！结束了！结束了！
} 
```

本蒟蒻一向

# 心地善良

这篇题解复制提交可以直接AC.

但是......

# 非紧急情况请勿使用此特殊功能！
（感谢翻译本题的用户，出题人，洛谷管理员，和所有点赞的用户）

---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1076C)

题目大意：请构造两个数，使它们相加与相乘都等于 $d$。

思路分析：此题较水，不用二元二次方程也能过。那么还可以怎么办呢？

这里可以发现，当和一定时，若两个数相差越小，那么两个数的积就越大。我们就可以控制它们两个的差，来实现它们的乘积约等于 $d$。因为满足单调性，可以用较小的数来进行二分。

在这里之前先排除 $3$ 个答案：$d \ge 1$ 且 $d \le 3$ 时。我们发现即使乘积最大的两个数也不能达到 $d$，舍去。

否则直接设较小的数为 $\frac{n}{2}$，然后依次进行二分：当乘积大于就往小减，过大就往大加。这里要注意范围。由于二分是非常高效的，$500$ 次左右就可查到答案。此时直接输出答案即可。

### AC Code:

```cpp
#include <iostream>
using namespace std;
int t;
double a,b,c,d,e;
int main()
{
    cin >> t;
    while(t --)
    {
        cin >> d;
        if(d >= 1 && d <= 3)//特判
        {
            cout << "N\n";
            continue ;
        }
        a = b = c = d / 2,e = 0;//c和e为二分的范围
        for(int i = 1;i <= 1000;i ++)//二分
        {
            if(a * (d - a) > d)c = a,a = (c + e) / 2;//若偏小二分
            else e = a,a = (c + e) / 2;//否则往大二分
        }
        printf("Y %.9lf %.9lf\n",d - a,a);//输出
    }
}

---

## 作者：damage (赞：1)

## 题意

给定$T$组数据，每组数据包含一个整数$d$，要求求出两个非负实数$a$和$b$（$a\geq{b}$），满足：

$$\left\{{\begin{aligned}a+b=d\text{\ \ \ \ \ }\\ab=d\text{\ \ \ \ \ \ \ \ \ }\end{aligned}}\right.$$

若无解则输出```N```，否则输出```Y```和$a$与$b$，保留$9$位小数。

---

## 题解

对于每组数据，就是解方程组：

$\left\{{\begin{aligned}a+b=d\text{\ \ \ \ \ 一式}\\ab=d\text{\ \ \ \ \ \ \ \ \ 二式}\end{aligned}}\right.$

我们利用②式将元（未知数）数降为$1$，即$b=\frac{d}{a}$，代入①式得$$a+\frac{d}{a}=d$$

再去分母$$a^{2}+d=ad$$

化为二元一次方程一般式$$a^{2}-da+d=0$$

判别式为$$\Delta=d^{2}-4d$$

求根$$x_{1,2}=\frac{d±\sqrt{d^{2}-4d}}{2}$$

则$$a=\frac{d+\sqrt{d^{2}-4d}}{2}$$

$$b=\frac{d-\sqrt{d^{2}-4d}}{2}$$

直接用```cmath```库（调用根号函数）求根即可

### 不过注意题目要求$a$和$b$非负，所以要特判$b\lt{0}$！

---

## 代码

```cpp
#include<stdio.h>
#include<cmath> //根号所在头文件
int t;
double d,delta;
int main()
{
	scanf("%d",&t);
	while(t--) //多组数据
	{
		scanf("%lf",&d);
		delta=d*d-4*d; //获取delta
		if(delta<0) printf("N\n"); //delta<0时无解
		else
		{
			delta=sqrt(delta); //简化运算
			if(d-delta<0) printf("N\n"); //特判b非负
			else printf("Y %.9lf %.9lf\n",(d+delta)/2,(d-delta)/2); //输出，注意九位小数
		}
	}
	return 0;
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1076C)

### $\texttt{Description}$ 

给定一个非负整数 $n$，要求构造出两个非负实数 $a,b$，满足 $a+b=d$ 且 $a \times b=d$ 的条件。如果是，输出 `Y` 并将 $a$ 和 $b$ 保留 $9$ 位小数输出，否则输出 `N` 即可。

### $\texttt{Solution}$

这题就是个数学题。

我们已知 $a+b=d$ 且 $a \times b=d$ 这两个条件。

那么我们可以得到 :

$$b=d-a$$

然后再把 $b$ 代入第二个式子，得到:

$$a \times (d-a)=d$$

再用分配律得到:

$$-a^2+a \times d=d$$

然后我们再把 $d$ 往左边移项，得到：

$$-a^2+ad-d=0$$

我们再根据求根公式得出：

$$a=\frac{d \ \pm \sqrt{d^2-4d}}{2}$$

由于 $a$ 和 $b$ 都是**非负实数**，所以可以得到：

$$a=\frac{d + \sqrt{d^2-4d}}{2}$$ 

$$b=\frac{d - \sqrt{d^2-4d}}{2}$$

那么，如果 $d^2-4d<0$ 的话，也就是 $1 \le d \le 3$ 时，$a,b$ 无解。

所以代码就很简单了。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t, d;
double a, b;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	
	while (t--) {
		cin >> d;
		
		if (d >= 1 && d <= 3) {
			cout << "N\n";
			continue;
		}
		
		a = (d + sqrt(d * d - 4 * d)) / 2.0;
		b = (d - sqrt(d * d - 4 * d)) / 2.0;
		
		cout << fixed << setprecision(9) << "Y ";
		cout << 1.0 * a << " " << 1.0 * b << "\n";
	}
	
	return 0;
}
```

本代码时间复杂度仅有 $O(t)$ 之短，完全能过。

完结。

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1076C)

我又来水题解了。

### 前置知识
一元二次方程的求根公式：

对于关于 $x$ 的方程 $ax^2+bx+c=0$，纪 $\Delta=b^2-4ac$。
+ 若 $\Delta \ge 0$，则原方程的解为 $x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$；
+ 若 $\Delta \lt 0$，则原方程无实根。
具体推导过程 [请看这里](https://www.luogu.com.cn/article/o7kx2j08/edit)。

韦达定理：

对于关于 $x$ 的方程 $ax^2+bx+c=0$，则方程的两个解 $x_1$ 和 $x_2$ 满足：
$$
\begin{cases}
x_1+x_2=-\frac{b}{a}\\
x_1x_2=\frac{c}{a}
\end{cases}
$$

### 题目大意
给出一个非负整数 $d$，请你找出两个非负整数使得：
$$
\begin{cases}
a+b=d\\
ab=d
\end{cases}
$$

### 解题思路
根据韦达定理我们可以列出一个关于 $x$ 的一元二次方程 $x^2-dx+d=0$，此时再计算 $\Delta=(-d)^2-4d=d(d-4)$。

也就是说，当 $0 \lt d \lt 4$ 时，原方程无解，否则原方程的两个解为：
$$
\begin{cases}
x_1=\frac{d+\sqrt{\Delta}}{2}\\
x_2=\frac{d-\sqrt{\Delta}}{2}
\end{cases}
$$

于是我们就在 $O(1)$ 的复杂度下解决了此题。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		if(n>0&&n<4) cout<<"N\n";
		else printf("Y %.9lf %.9lf\n",(n+sqrt(n*(n-4)))/2.0,(n-sqrt(n*(n-4)))/2.0);
	}
}
```

---

## 作者：Fkxxx (赞：0)

本题解将会讲本题的正解 $O(t)$ 做法，求解思路为方程。

## 题目概括

对于 $n$，求出 $a,b$ 使得 $ab=n,a+b=n$。

## 做题

我们不妨把 $a,b$ 取到各个值的情况表示一下，可以得到以下式子：

$$
\begin{cases}
    a+b=n \\
    ab=n
\end{cases}
$$

更直观一点，我们把它化成一元二次：

$$-a^2+an=n$$

~~接下来，掏出你 CSP-J 2023 T3 的代码。~~

其实不用，直接用公式求非负整数解：

$$
\begin{cases}
	a=\frac{n-\sqrt{n^2-4n}}{2}\\
    b=\frac{n+\sqrt{n^2-4n}}{2}
\end{cases}
$$

同时，易得本题在 $0<n<4$ 时无解。

## 参考代码

[Turn to Codeforces!](https://codeforces.com/contest/1076/submission/258834859)

---

## 作者：G__G (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1076C)

[更好的阅读体验](https://678115.blog.luogu.org/solution-cf1076c)

一道裸的数学题。

首先我们已知两个条件：

$$a+b=d$$

$$ab=d$$

由此得出：

$$b=d-a$$

再将第二个已知条件转化一下：

$$a(d-a)=d$$

展开后得：

$$ad-a^2=d$$

再把 $d$ 挪过去：

$$a^2-ad+d=0$$

根据[求根公式](https://baike.baidu.com/item/%E4%B8%80%E5%85%83%E4%BA%8C%E6%AC%A1%E6%96%B9%E7%A8%8B%E6%B1%82%E6%A0%B9%E5%85%AC%E5%BC%8F/56066624?fr=ge_ala)得出：

$$a=\frac{d \pm \sqrt{d^2-4d}}{2}$$

因为 $a$ ，$b$ 为非负实数，所以 $a=\frac{d + \sqrt{d^2-4d}}{2}$ $b=\frac{d - \sqrt{d^2-4d}}{2}$。

所以，当 $d^2-4d < 0$ 时不存在 $a$ 和 $b$。

参考代码

```
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int d,x;
		cin>>d;
		x=d*d-4*d;
		if(x<0){
			cout<<"N"<<endl;
		}
		else{
			double a,b;
			a=(sqrt(d*d-4*d)+d)/2.0;
			b=(d-sqrt(d*d-4*d))/2.0;
			cout<<"Y ";
			cout<<fixed<<setprecision(9)<<a<<" "<<b<<endl;//保留九位小数
		}
	}
    return 0;
}
```


---

## 作者：Siteyava_145 (赞：0)

大水题。

给定 $d$，求一组满足下面方程的 $a,b$。

$\begin{cases}{a+b=d}\\ab=d\end{cases}$

易得 $b=d-a$。

将其代入到第二个式子里，得到 $a(d-a)=d$。

展开得 $ad-a^2=d$，整理后为 $a^2-ad+d=0$。

根据幼儿园学过的求根公式，$a=\dfrac{\pm\sqrt{d^2-4d}+d}{2}$。题目要求 $a,b\ge0$，所以取 $a=\dfrac{\sqrt{d^2-4d}+d}{2}$.

所以 $b=\dfrac{d-\sqrt{d^2-4d}}{2}$，

如果 $d^2-4d<0$，则不存在 $a,b$。

----

## 大坑点

保留小数位数越多越好，$12$ 位最好。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        double d;
        cin>>d;
        if(d*d<4*d)cout<<"N"<<endl;
        else{
            cout<<"Y"<<' '<<fixed<<setprecision(12)<<(sqrt(d*d-4*d)+d)/2.0<<' '<<(d-sqrt(d*d-4*d))/2.0<<endl;
        }
    }
}
```


---

## 作者：Allanljx (赞：0)

## 思路
别的大佬都是解二元二次方程做的，我来发一发二分的题解。设 $a=n\div2+x,b=n\div2-x$，则 $a\times b=n^2\div4-x^2$，随着 $x$ 的增大 $a\times b$ 不断减小。因此 $a\times b$ 具有单调性，可以二分。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
long double n;
int t;
long double eps=1e-8;//解决精度问题 
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		long double l=0,r=n/2,ans=-1;
		while(l<=r)//二分a的取值 
		{
			long double mid=(l+r)/2;
			if(abs(n-mid*(n-mid))<=eps)
			{
				ans=mid;
				break;
			}
			if(mid*(n-mid)<n) l=mid+1e-12;
			else if(mid*(n-mid)>n) r=mid-1e-12;
		}
		if(ans==-1) puts("N");
		else printf("Y %.9LF %.9LF\n",ans,n-ans);
	}
}
```

---

