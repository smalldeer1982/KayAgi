# Endless Matrix

## 题目描述

A Russian space traveller Alisa Selezneva, like any other schoolgirl of the late 21 century, is interested in science. She has recently visited the MIT (Moscow Institute of Time), where its chairman and the co-inventor of the time machine academician Petrov told her about the construction of a time machine.

During the demonstration of the time machine performance Alisa noticed that the machine does not have high speed and the girl got interested in the reason for such disadvantage. As it turns out on closer examination, one of the problems that should be solved for the time machine isn't solved by an optimal algorithm. If you find a way to solve this problem optimally, the time machine will run faster and use less energy.

A task that none of the staff can solve optimally is as follows. There exists a matrix $ a $ , which is filled by the following rule:

The cells are consecutive positive integers, starting with one. Besides, $ a_{i,j}&lt;a_{t,k} $ ( $ i,j,t,k>=1 $ ), if:

1. $ max(i,j)&lt;max(t,k) $ ;
2. $ max(i,j)=max(t,k) $ and $ j&lt;k $ ;
3. $ max(i,j)=max(t,k) $ , $ j=k $ and $ i&gt;t $ .

So, after the first $ 36 $ numbers are inserted, matrix $ a $ will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249E/db70d71da432099ee5c0691f8311f2105a4c00eb.png)To solve the problem, you should learn to find rather quickly for the given values of $ x_{1},y_{1},x_{2} $ and $ y_{2} $ ( $ x_{1}<=x_{2},y_{1}<=y_{2} $ ) the meaning of expression:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249E/dedf88341ac4206f3e0349d9d8443767ae3040af.png)As the meaning of this expression can be large enough, it is sufficient to know only the last $ 10 $ digits of the sought value.

So, no one in MTI can solve the given task. Alice was brave enough to use the time machine and travel the past to help you.

Your task is to write a program that uses the given values $ x_{1},y_{1},x_{2} $ and $ y_{2} $ finds the last $ 10 $ digits of the given expression.

## 样例 #1

### 输入

```
5
1 1 1 1
2 2 3 3
2 3 5 6
100 87 288 2002
4 2 5 4
```

### 输出

```
1
24
300
...5679392764
111
```

# 题解

## 作者：Eltaos_xingyu (赞：4)

## 题目描述

请在形如下图的矩阵中求解：

![](https://cdn.luogu.org/upload/vjudge_pic/CF249E/db70d71da432099ee5c0691f8311f2105a4c00eb.png)

多组询问，每次询问 $x_1$，$y_1$，$x_2$，$y_2$，求 $\sum_{
x_1\leq i\leq x_2,y_1\leq j\leq y_2}T[i][j]$。

## 分析

某场考试时做的，一看就是规律题。

有人的式子看起来长，但是代码很短；我恰好相反......

可以注意到，这道题要求的矩形中，有几类可以直接求出的矩形：

- 矩形的四个顶点都在左上右下对角线的左侧

![](https://cdn.luogu.com.cn/upload/image_hosting/tfjl033x.png)

如图，可以发现红圈中的矩形从左至右都是单调递减的，那么可以利用平方和公式和等差数列求和来推这种情况的式子：
$$
\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}T[i][j]\\
=\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}(i^2-j+1)\\
=\sum_{i=x_1}^{x_2}(i^2\times(y_2-y_1+1)-\sum_{j=y_1}^{y_2}(j-1))\\
=(y_2-y_1+1)\sum_{i=x_1}^{x_2}i^2-(x_2-x_1+1)\sum_{i=y_1}^{y_2}(i-1)
$$

- 矩形的四个顶点都在左上右下对角线的右侧

和左侧一样，推推式子就行了，就不放图了。
$$
\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}T[i][j]\\
=\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}((j-1)^2+i)\\
=\sum_{i=y_1}^{y_2}((i-1)^2\times (x_2-x_1+1)+\sum_{j=x_1}^{x_2}j)\\
=(x_2-x_1+1)\sum_{i=y_1}^{y_2}(i-1)^2+(y_2-y_1+1)\sum_{i=x_1}^{x_2}i
$$
这部分的代码实现：

```cpp
#define int __int128
const int mod=1e10;

int mul_sum(int x,int y){
	if(x>y)return 0;
	x--;
	int sum1=(x*(x+1)*(2*x+1)/6);
	int sum2=(y*(y+1)*(2*y+1)/6);
	return (sum2-sum1);
}

int _sum(int x,int y){
	if(x>y)return 0;
	return (x+y)*(y-x+1)/2;
}

int matrix_sumL(int i1,int i2,int j1,int j2){
	if(i1>i2||j1>j2)return 0;
	int temp=mul_sum(i1,i2)*(j2-j1+1);
	temp=(temp-_sum(j1-1,j2-1)*(i2-i1+1));
	return temp;
}

int matrix_sumR(int i1,int i2,int j1,int j2){
	if(i1>i2||j1>j2)return 0;
	int temp=mul_sum(j1-1,j2-1)*(i2-i1+1);
	temp=(temp+_sum(i1,i2)*(j2-j1+1));
	return temp;
}
```

这部分搞懂了，那么求下面这种可以直接求出的矩形就简单了。

- 左上顶点与右下顶点都在左上右下对角线上

![](https://cdn.luogu.com.cn/upload/image_hosting/j7328u20.png)

假设我们要求红色的矩形，可以考虑先算蓝色的大矩形然后减去绿色的矩形和蓝色的小矩形。

而蓝色的矩形是可以等差数列求和的：$\sum \text{蓝} =\sum_{i=1}^{y_2^2}i$；绿色的矩形是之前我们求过的类型。

所以红色的矩形就可以求啦！

```cpp
int matrix_sumMID(int i1,int i2){
	if(i1>i2)return 0;
	int temp1=_sum(1,i2*i2),temp2=_sum(1,(i1-1)*(i1-1));
	temp1=(temp1-temp2);
	temp1=(temp1-matrix_sumR(1,i1-1,i1,i2));
	temp1=(temp1-matrix_sumL(i1,i2,1,i1-1));
	return temp1;
}
```



## 最后的实现

可以发现求完上面类型的矩形之后，剩下的图形都可以通过上面的基本图形拼在一起。

比如这个矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/b0x40df2.png)

红色的矩形可以分为这 $3$ 个基础矩形来求解。

其他矩形的分类可以看代码，还要注意输出三个点之后要输出前导 $0$，希望这篇题解对你有帮助！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
const int mod=1e10;

int mul_sum(int x,int y){
	if(x>y)return 0;
	x--;
	int sum1=(x*(x+1)*(2*x+1)/6);
	int sum2=(y*(y+1)*(2*y+1)/6);
	return (sum2-sum1);
}

int _sum(int x,int y){
	if(x>y)return 0;
	return (x+y)*(y-x+1)/2;
}

int matrix_sumL(int i1,int i2,int j1,int j2){
	if(i1>i2||j1>j2)return 0;
	int temp=mul_sum(i1,i2)*(j2-j1+1);
	temp=(temp-_sum(j1-1,j2-1)*(i2-i1+1));
	return temp;
}

int matrix_sumR(int i1,int i2,int j1,int j2){
	if(i1>i2||j1>j2)return 0;
	int temp=mul_sum(j1-1,j2-1)*(i2-i1+1);
	temp=(temp+_sum(i1,i2)*(j2-j1+1));
	return temp;
}

int matrix_sumMID(int i1,int i2){
	if(i1>i2)return 0;
	int temp1=_sum(1,i2*i2),temp2=_sum(1,(i1-1)*(i1-1));
	temp1=(temp1-temp2);
	temp1=(temp1-matrix_sumR(1,i1-1,i1,i2));
	temp1=(temp1-matrix_sumL(i1,i2,1,i1-1));
	return temp1;
}


signed main()
{
	ios::sync_with_stdio(false);
	long long T,x_1,y_1,x_2,y_2;
	int ans;
	cin>>T;
	while(T--){
		cin>>x_1>>y_1>>x_2>>y_2;
		if(x_1<=y_1&&y_2<=x_2){
			ans=(matrix_sumR(x_1,y_1-1,y_1,y_2)+matrix_sumMID(y_1,y_2)+matrix_sumL(y_2+1,x_2,y_1,y_2));
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
		if(y_1<=x_1&&x_2<=y_2){
			ans=(matrix_sumR(x_1,x_2,x_2+1,y_2)+matrix_sumMID(x_1,x_2)+matrix_sumL(x_1,x_2,y_1,x_1-1));
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
		if(y_2<=x_1){
			ans=matrix_sumL(x_1,x_2,y_1,y_2);
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
		if(y_1>=x_2){
			ans=matrix_sumR(x_1,x_2,y_1,y_2);
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
		if(y_1<=x_1&&x_1<=y_2&&y_2<=x_2){
			ans=(matrix_sumMID(x_1,y_2)+matrix_sumL(x_1,x_2,y_1,x_1-1)+matrix_sumL(y_2+1,x_2,x_1,y_2));
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
		if(x_1<=y_1&&y_1<=x_2&&x_2<=y_2){
			ans=(matrix_sumMID(y_1,x_2)+matrix_sumR(x_1,y_1-1,y_1,y_2)+matrix_sumR(y_1,x_2,x_2+1,y_2));
			if(ans>=mod){
				ans%=mod,cout<<"...";
				int yyy=1e9;
				while((ans%yyy)==ans)cout<<0,yyy/=10;
			}
			cout<<(long long)ans<<endl;
			continue;
		}
	}
	return 0;
}
```



---

## 作者：BqtMtsZDnlpsT (赞：4)

史上最水 2600，不信自己写一下。

截止 2022/2/14 18:17 我是全 CF 最优解，最慢点领先 rk2 126ms，（~~我相信我撑不过一天~~）。 

$\large\text{Solution}$

下文中，定义 $[(x_1,y_1),(x_2,y_2)]=\sum\limits_{i=x_1}^{x_2}\sum\limits_{j=y_1}^{y_2}A_{i,j}$。

首先，一个传统的差分+容斥，把问题转化为求： 

$[(1,1),(x_2,y_2)]-[(1,1),(x_1-1,y_2)]-[(1,1),(x_2,y_1-1)]+[(1,1),(x_1-1,y_1-1)]$

[如果您不理解](https://www.luogu.com.cn/paste/6jweyrzq)

于是问题转化为求 $[(1,1),(x,y)]$。

根据题意，我们可以把表格分为这样：

[![H6TrKs.md.png](https://s4.ax1x.com/2022/02/14/H6TrKs.md.png)](https://imgtu.com/i/H6TrKs)

其中从左上到右下第 $x$ 个 “L”型块按箭头方向依次为 $(x-1)^2+1,(x-1)^2+2,\dots,x^2$，而 $1\dots x$ 构成的正方形大小为 $x^2$，里面正好 包含了 $1\dots x^2$ 的所有数。

（~~讲了那么多废话~~）

这题直接做哪里麻烦？转角。考虑任意一个以 $(1,1)$ 为左上角的矩形一定包含一个以 $(1,1)$ 为左上角，$(\min(x,y),\min(x,y))$ 的正方形，减去这个正方形之后，就没有转角了。

结合图理解一下

[![H6bWPf.md.png](https://s4.ax1x.com/2022/02/14/H6bWPf.md.png)](https://imgtu.com/i/H6bWPf)

接下来对于求 $[(1,1),(x,y)]$ 根据不同情况分类讨论：

- $x=y$

可以发现是求一个以 $(1,1)$ 为左上角的正方形，就是算 $1+2+\dots+n^2=\frac{(n^2+1)*n^2}{2}$

- $x>y$

先算左上角的正方形：$1+2+\dots+\min(x,y)^2=\frac{(\min(x,y)^2+1)*\min(x,y)^2}{2}$

其实这里 $\min(x,y)$ 就是 $y$。

再算下面部分。

式子 （从第 $y+1$ 行第 $1$ 列开始，从上到下，从左到右）：

$(y+1)^2$（箭头尾端）+$(y+2)^2+\dots+x^2$

$+(y+1)^2-1+(y+1)^2-1+\dots+x^2-1$

$+\dots+$

$+(y+1)^2-y+1+(y+1)^2-y+1+\dots+x^2-y+1$

形式化的：$\sum\limits_{i=0}^{y-1}\sum\limits_{j=y+1}^x j^2-i=\sum\limits_{i=0}^{y-1}\sum\limits_{j=y+1}^x j^2-\sum\limits_{i=0}^{y-1}\sum\limits_{j=y+1}^xi=y\sum\limits_{j=y+1}^x j^2-(x-y)\sum\limits_{i=0}^{y-1}i$

注意到第一部分可以通过平方和公式 $\sum\limits_{i=1}^{n}i^2=\frac{n(n+1)(2n+1)}{6}$ 进行差分求和，第二部分是个等差数列，可以直接算。

综上所述：$[(1,1),(x,y)]=\frac{(\min(x,y)^2+1)*\min(x,y)^2}{2}+y(\frac{x(x+1)(2x+1)}{6}-\frac{y(y+1)(2y+1)}{6})-(x-y)\frac{(y-1)y}{2}$

- $x<y$ 

其实差不多，第一部分不讲了。


式子 （从第 $y+1$ 列开始，**从左到右，从上到下**）：

$x^2+1+(x+1)^2+1+\dots+(y-1)^2+1$

$+x^2+2+(x+1)^2+2+\dots+(y-1)^2+2$

$+\dots+$

$+x^2+x+(x+1)^2+x+\dots+(y-1)^2+x$

形式化的：$\sum\limits_{i=x}^{y-1}\sum\limits_{j=1}^x i^2-j=\sum\limits_{i=x}^{y-1}\sum\limits_{j=1}^x i^2-\sum\limits_{i=x}^{y-1}\sum\limits_{j=1}^xj=x\sum\limits_{i=x}^{y-1} i^2-(y-x)\sum\limits_{j=1}^xj$

同样方法得到 $[(1,1),(x,y)]=\frac{(\min(x,y)^2+1)*\min(x,y)^2}{2}+x(\frac{(y-1)(y-1+1)(2(y-1)+1)}{6}-\frac{(x-1)(x-1+1)(2(x-1)+1)}{6})-(y-x)\frac{(x+1)x}{2}$


------------

然后就好了，答案最大是 $x^4$ 级别的，中途要开 `int128`。

代码：

```cpp
#define i128 __int128
inline i128 work(i128 x,i128 y){
	i128 k=min(x,y),ans=(k*k*(k*k+1))>>1;//左上角正方形
    //以下就是根据刚才的模拟。
	if(x==y)return ans;
	if(x>y)return ans+(x*(x+1)*(x<<1|1)-y*(y+1)*(y<<1|1))/6*y-(x-y)*(y*(y-1)>>1);
	return ans+((y-1)*y*((y-1)<<1|1)-(x-1)*x*((x-1)<<1|1))/6*x+(y-x)*(x*(x+1)>>1);
}
signed main(){
	for(int T=read();T;T--){
		int x=read(),y=read(),u=read(),v=read();
		i128 ans=work(u,v)-work(x-1,v)-work(u,y-1)+work(x-1,y-1);
		if(ans>10000000000)printf("...%010lld\n",(ll)ans%10000000000);//注意一下输出格式
		else printf("%lld\n",(ll)ans);
	}
}
```

---

## 作者：zhicheng (赞：3)

### 题意简述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249E/db70d71da432099ee5c0691f8311f2105a4c00eb.png)

在上图所示的矩阵中求一个子矩形的元素和。

### 思路

先可以考虑差分。然后问题转化为求以 $(x,y)$ 为右下角的矩形的元素和。先考虑 $x\leq y$ 的情况。$x>y$ 的情况同理可推。先可以算出以 $(x,x)$ 为右下角的，答案为 $\sum\limits_{i=1}^{x^2}i$。

然后考虑剩下的部分。每一列最上方是 $x^2+1,(x+1)^2+1,\cdots,(y-1)^2+1$，每一列有 $x$ 个递增的数。所以总的就是 $x[x^2+(x+1)^2+\cdots+(y-1)^2]+[(y-1)-x+1]\times\dfrac{x(x+1)}{2}$，可以通过平方和公式 $\left(\sum \limits_{i=1}^{n}i^2=\dfrac{n(n+1)(2n+1)}{6}\right)$ 计算。若 $x>y$ 则同理。这里不给出式子。可以看看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mo4otyvv.png)

一些细节：输出的时候如果后十位有前导 $0$ 也要输出。要求判断位数是否大于十位，简单计算可得最大的答案不超过 `__int128` 的储存范围，所以计算完后判断再输出即可。

### Code

代码很短，加上 Fast IO 目前是你谷最优解。当然 CF 太强了卡不到第一。/kk

```cpp
#define ll __int128
ll sum(ll x){
	return x*(x+1)*(2*x+1)/6;
}
ll calc(ll x,ll y){
	if(x<=y){
		return x*(x+1)/2*(y-x)+(sum(y-1)-sum(x-1))*x+x*x*(x*x+1)/2;
	}
	return (sum(x)-sum(y))*y-y*(y-1)/2*(x-y)+y*y*(y*y+1)/2;
}
int main(){
	int t=gi();
	ll x,y,a,b,ans;
	while(t--){
		x=gl();
		y=gl();
		a=gl();
		b=gl();
		ans=calc(a,b)-calc(x-1,b)-calc(a,y-1)+calc(x-1,y-1);
		print(ans);
	}
}

---

## 作者：Minuswy (赞：3)

题外话，作为紫题相对简单了，模拟赛场上有一车人过。

---

### 前置证明

$\sum_{i=1}^n i^2 =n\times (n+1) \times (2 n+1)\div 6$。

想必各位学小学奥数的时候都学过吧，会的可以直接跳过。

把 $\sum_{i=1}^n$ 展开，可以写成 $1+2+2+3+3+3+4+4+4+4+ \cdots +n+n+\cdots +n $（写成 $i$ 个 $i$ 相加），在写成三角矩阵的形式。如左侧矩阵 $d1$。

则待求值即为 $sum_{d1}$。同时可以发现矩阵中有 $n \times (n+1)\div 2$ 个数。

将该矩阵顺时针旋转，得到中间矩阵 $d2$。

再旋转，得到右侧矩阵 $d3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cjgr5xz1.png)

然后我们再建一个三角矩阵 $f$，使 $f_{i,j}=d1_{i,j}+d2_{i,j}+d3_{i,j}$，那么 $sum_f=sum_{d1}+sum_{d2}+sum_{d3}$，因为 $d2,d3$ 都是由 $d1$ 旋转得到的，所以 $sum_{d1}=sum_{f}\div 3$。

简单观察一下就可以发现， $f$ 中的每个数都是 $2n+1$，$\displaystyle sum_f=n \times (n+1) \times (2n+1)\div 2$。

所以 $\displaystyle sum_{d1} =n\times (n+1) \times (2 n+1)\div 6$。得证。

## 题解部分

首先要求的是子矩阵的和，容易想到二维前缀和。设 $s_{n,m} = \sum_{i=1}^n \sum_{j=1}^m a_{i,j}$。我们的任务就转换为了 $O(1)$ 求 $s_{n,m}$。

对于 $s_{n,m}$，稍微观察一下就可以发现有两种情况，$n<m$ 和 $n\ge m$，分类讨论。

- ### $n<m$ 的情况

观察原矩阵，以框起来的数为例子。

```
 -----------------
| 1  2  5 | 10 17 |
| 4  3  6 | 11 18 |
| 9  8  7 | 12 19 |
 -----------------
 16 15 14 13 20
 25 24 23 22 21

```

我们可以将它切成两部分，左侧的 $3\times3$（就是 $n \times n$） 的矩阵一部分，剩下的数一部分。

$n \times n$ 的部分就是个 $1 \sim n \times n$ 的等差数列。和为 $n \times (1+n^2)\div 2$。

再看右侧的部分，将其左右组合，$(10+17),(11+18),(12+19)$。可以发现这也是一个等差数列。

首项为……欸，首项就是一个问题。可以对第一行做一个前缀和，$b_{m}=\sum_{i=1}^m a_{1,i}$。那么首项就可以表示出来了。

- 首项：$b_m - b_n$。
- 公差：$m-n$。可以发现从第 $n+1$ 列开始，每往右延伸一列，公差就增加 $1$。
- 项数：$n$。一共有 $n$ 行。
- 末项：$(b_m-b_n)+(n-1)(m-n)$。简单等差数列计算。
- 和：$[(b_m - b_n)+(b_m-b_n)+(n-1)(m-n)] \times n\div 2$。

**中途总结一下，$n<m$ 时，答案为 $n \times (1+n^2) \div 2+ [(b_m - b_n)+(b_m-b_n)+(n-1)(m-n)] \times n \div 2$**。

这样就结束了？等一下，$b$ 数组我们还没有 $O(1)$ 算出。~~此时可以 oeis 一下。~~

根据 $a$ 矩阵的性质，$a_{1,i}=(i-1)^2+1$。那么 $b_n=\sum_{i=1}^n (i-1)^2+1=n+\sum_{i=1}^{n-1} i^2$。

后面这个式子熟悉吗，根据前置证明，$\sum_{i=1}^{n-1} i^2=(n-1)\times n \times (2n-1)\div 6$。

**所以 $b_n=(n-1)\times n \times (2n-1)\div 6+n$。**

~~我代码里因为用了 oeis，写的形式和这个不太一样，但转化一下是一样的式子。~~

```cpp

int b(int p){
	return (2*p*p-(3*p)+7)*p/6;
}
int s(int i,int j){
	if(i<j) return (i*i+1)*(i*i)/2+(2*(b(j)-b(i))+(i-1)*(j-i))*i/2;
}

```

---

- ### $n \ge m$ 的情况

观察原矩阵，以框起来的数为例子。

```
 ----------
| 1  2  5  | 10 17
| 4  3  6  | 11 18
| 9  8  7  | 12 19
------------
| 16 15 14 | 13 20
| 25 24 23 | 22 21
 ----------

```

我们可以将它切成两部分，上侧的 $3\times3$（就是 $m \times m$） 的矩阵一部分，剩下的数一部分。

$m \times m$ 的部分就是个 $1 \sim m \times m$ 的等差数列。和为 $m \times (1+m^2)\div 2$。

再看下侧的部分，将其上下组合，$(16+25),(15+24),(14+23)$。可以发现这也是一个等差数列。

处理首项。可以对第一列做一个前缀和，$c_{n}=\sum_{i=1}^n a_{i,1}$。

- 首项：$c_n - c_m$。
- 公差：$-(n-m)$。可以发现从第 $n+1$ 行开始，每往下延伸一列，公差就增加 $-1$。
- 项数：$m$。一共有 $m$ 列。
- 末项：$(c_n-c_m)-(m-1)(n-m)$。
- 和：$[(c_n - c_m)+(c_n-c_m)-(m-1)(n-m)] \times m\div 2$。

**所以，$n\ge m$ 时，答案为 $n \times (1+n^2)\div 2+ [(c_n - c_m)+(c_n-c_m)-(m-1)(n-m)] \times m\div 2$**。

再求 $c$ 数组，~~此时可以 oeis 一下。~~

根据 $a$ 矩阵的性质，$a_{i,1}=i^2$。那么 $c_n=\sum_{i=1}^n i^2=n\times (n+1)\times (2n+1)\div 6$。

```cpp

int c(int p){
	return p*(p+1)*(2*p+1)/6;
}
int s(int i,int j){
	if(i>=j) return (j*j+1)*(j*j)/2+(2*(c(i)-c(j))-(j-1)*(i-j))*j/2;
}

```

## 代码部分

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define endl "\n"
#define int __int128
using namespace std;
const int P=1e10;
int n,m;
int c(int p){
	return p*(p+1)*(2*p+1)/6;
}
int b(int p){
	return (2*p*p-(3*p)+7)*p/6;
}
int s(int i,int j){
	if(i<j) 
	return (i*i+1)*(i*i)/2+(2*(b(j)-b(i))+(i-1)*(j-i))*i/2;
	return (j*j+1)*(j*j)/2+(2*(c(i)-c(j))-(j-1)*(i-j))*j/2;
}
inline void print(__int128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9 print(x/10);
    putchar(x%10+'0');
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	long long T;
	cin>>T;
	while(T--){
		long long x,y,xx,yy;
		cin>>xx>>yy>>x>>y;
		int awa=(s(x,y)-s(xx-1,y)-s(x,yy-1)+s(xx-1,yy-1));
		int qwq=awa%P;
		if(awa>P) printf("...%010lld\n",(long long)qwq);
		else printf("%lld\n",(long long)qwq);
	}
	return (0-0);
}


```

---

## 作者：Larryyu (赞：2)

## _Description_
构造一类矩形：

先构造矩形 $M_1=\begin{bmatrix}1\end{bmatrix}$。

对于 $i\geq1$，$T_{i+1}$ 从 $T_i$ 构造而来，方法为在最右侧和最下侧插入新的一行一列，自右上到左下 $2i+1$ 个数分别填入 $i^2+1,i^2+2\dots(i+1)^2$。

比如：

- $M_2=\begin{bmatrix}1&2\\4&3\end{bmatrix}$
- $M_3=\begin{bmatrix}1&2&5\\4&3&6\\9&8&7\end{bmatrix}$
- $M_4=\begin{bmatrix}1&2&5&10\\4&3&6&11\\9&8&7&12\\16&15&14&13\end{bmatrix}$

令左上角坐标为 $(1,1)$，从上至下第 $i$ 行，从左至右第 $j$ 个数的坐标为 $i,j$。

共 $T$ 组询问，每次询问 $x_1,y_1,x_2,y_2$，求 $\sum_{x_1\le i\le x_2,y_1\le j\le y_2}M_\infty [i][j]$。

如果答案在十位数以上，只输出答案的最后十位，前面的数位用 ```...```代替。

否则输出完整的答案。

## _前置芝士_
两个公式，可以了解一下相关证明：

$1^2+2^2+\dots+n^2=\dfrac{n\times(n+1)\times(2\times n+1)}{6}$

$1+2+\dots+n=\dfrac{(n+1)\times n}{2}$
## _Solution_
对于求一个矩形内所有数值的和，通常运用容斥来转换。

在此题上，设 $S_{x,y}$ 为 $\sum_{1\le i\le x,1\le j\le y}M_\infty [i][j]$。

利用容斥：$ans=S_{x_2,y_2}-S_{x_1-1,y_2}-S_{x_2,y_1-1}+S_{x_1-1,y_1-1}$。

所以只要会求 $S_{x,y}$ 就好了。

钦定 $y\le x$。

对于一个左上角的矩形，其一定包含一个边长为 $y$ 的正方形。

而正方形的和就是 $1+2+\dots+y^2$，利用等差数列求和公式得出。

剩下的一部分分类讨论。

![](https://cdn.luogu.com.cn/upload/image_hosting/nv2m4o92.png)

第一种情况，红色部分为 $((y+1)^2+(y+2)^2+\dots+x^2)\times y-(1+2+\dots+y-1)$。

第二种情况，红色部分为 $((y^2+(y+1)^2+\dots+(x-1)^2)+(x-y))\times y+(1+2+\dots+y-1)$。

很明显，对于 $S_{a,b}$，当 $a>b$ 时为第一种情况，当 $a\le b$ 时为第二种情况。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
#define _int __int128  //不能取模，所以开__int128
_int read(){
	_int x=0,f=1;
	char ch=getchar();
	while(ch<'0'&&ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
_int calc(_int x){
	if(x==0) return 0;
	return x*(x+1)*(2*x+1)/6;  //平方和公式 
}
_int get(_int x,_int y){
	_int ans=0;
	if(x>y){
		ans+=(y*y+1)*y*y/2;  //正方形 
		_int cnt=calc(x)-calc(y);                
		ans+=cnt*y;
		ans=ans-(x-y)*y*(y-1)/2;
	}else{
		ans+=(x*x+1)*x*x/2;  //正方形 
		_int cnt=calc(y-1)-calc(x-1)+y-x;
		ans+=cnt*x;
		ans=ans+(y-x)*x*(x-1)/2;
	}
	return ans;
}
void print(_int x,int cnt){
	if(cnt==11) return;
	print(x/10,++cnt);
	putchar(x%10+'0');
	
}
void print2(_int x,bool f){
	if(x){
		print2(x/10,0);
		putchar(x%10+'0');
	}else if(f){
		putchar('0');
	}
}
void solve(){
	_int a=read(),b=read(),c=read(),d=read();
	_int ans=((get(c,d)-get(a-1,d))-get(c,b-1))+get(a-1,b-1); //容斥 
	if(ans>=10000000000){
		printf("...");
		print(ans,1);
	}else print2(ans,1);
	printf("\n");
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：hfjh (赞：1)

# CF249E Endless Matrix 题解
看题解区好像没有我这个暴力推导式子的做法，考试时候比较蠢只想出这个方法，就分享一下。
### 题意

一个长这样的矩阵：

$$
\begin{bmatrix}
1 & 2 & 5 & 10 & 17 & \cdots \\
4 & 3 & 6 & 11 & 18 & \cdots \\
9 & 8 & 7 & 12 & 19 & \cdots \\
16 & 15 & 14 & 12 & 20 & \cdots \\
\vdots\\
\end{bmatrix}
$$

求矩阵区间和。

### 题解

考虑矩阵每个数用式子表示出来：

$$
a_{i,j} = \begin{cases}
    x^2 - 2x + y + 1 ~~~~~~~~~x\ge y\\
    y^2 - x + 1~~~~~~~~~~~~~~~~~~x<y
\end{cases}
$$

然后就求

$$
\sum_{x_1\le x\le x_2}\sum_{y_1\le y \le y_2} a_{x,y}
$$

分成 $x\ge y$ 和 $x < y$ 就可以推式子。

> 情况有点多，式子有点复杂。

大概这样：

- 当 $x\ge y$ 时：
  
  - 当 $x_2 \le y_2$：
  
  - $$
        \begin{aligned}
    &\sum_{\max(x_1, y_1)\le x \le x_2} \sum_{y_1\le y\le x} x^2-2x+y+1\\
    &=\sum_{\max(x_1, y_1)\le x \le x_2}[(x-1)^2+(\frac {x+y_1}2)](x-y_1)\\
    &=\sum_{\max(x_1, y_1)\le x \le x_2} x^3 + (-\frac 1 2-y_1)x^2 +(2y_1 - \frac 12)x + (\frac 12y_1+1)(1-y_1)
    \end{aligned}
    $$
  
  - 当 $x_2>y_2$，也就是 $x_2 \ge y_2 + 1$
  
  - $$
                \begin{aligned}
        &\sum_{\max(x_1, y_1)\le x \le y_2} \sum_{y_1\le y\le x} x^2-2x+y+  
        \sum_{\max(x_1, y_2+1)\le x \le x_2} \sum_{y_1\le y\le y_2} x^2-2x+y+1\\

    &=\sum_{\max(x_1, y_1)\le x \le x_2} x^3 + (-\frac 1 2-y_1)x^2 +(2y_1 - \frac 12)x + (\frac 12y_1+1)(1-y_1)
    +\sum_{\max(x_1, y_2+1)\le x \le x_2} (y_2 - y_1+1)x^2 + 2(y_1 - y_2 - 1)x + (1 + \frac {y_1 + y_2} 2)(y_2 - y_1 + 1)
    \end{aligned}
    $$

- 当 $x < y$，也就是 $x \le y-1$ 时：
  
  - 当 $y_2 - 1 \le x_2$
  
  - $$
    \begin{aligned}
    &\sum_{\max(x_1+  1,y_1) \le y \le y_2} \sum_{x_1 \le x \le y-1} y^2 - x+1\\
    &=\sum_{\max(x_1+  1,y_1) \le y \le y_2} y^3 + (-x_1 - \frac12)y^2 + (\frac 32)y + (\frac {x_1^2} 2 - \frac 3 2x_1)
    \end{aligned}
    $$
  
  - 当 $y_2 - 1 > x_2$，也就是 $y_2 - 2 \ge x_2$：
  
  - $$
    \begin{aligned}
    &\sum_{\max(x_1+  1,y_1) \le y \le x_2 + 1} \sum_{x_1 \le x \le y-1} y^2 - x+1
    +\sum_{\max(x_2 + 2,y_1) \le y \le y_2} \sum_{x_1 \le x \le x_2} y^2 - x+1\\
    &=\sum_{\max(x_1+  1,y_1) \le y \le x_2 + 1} y^3 + (-x_1 - \frac12)y^2 + (\frac 32)y + (\frac {x_1^2} 2 - \frac 3 2x_1)
    +\sum_{\max(x_2 + 2,y_1) \le y \le y_2} (x_2 - x_1 + 1)y^2 + (1 - \frac {x_1 + x_2} 2)(x_2 - x_1 + 1)
    \end{aligned}
    $$

求和部分运用 $k$ 次幂前缀和公式即可：

$$
\begin{aligned}
&\sum_{i=1}^n i = \frac {n(n+1)} 2\\
&\sum_{i=1}^n i^2 = \frac {n(n+1)(2n+1)} 6\\
&\sum_{i=1}^n i^3 = \frac {n^2(n+1)^2} 4\\
&\sum_{i=1}^n i^4 = \frac {n(n+1)(2n+1)(3n^2 + 3n -1)} {30}
\end{aligned}
$$
### 温馨提示：
因为又要 $\div 6$ 又要 $\div 4$ 把模数设成 $1.2 \times 10^{10}$,然后直接除就可以了。

对于常数是 $\frac 1 2$ 的放在一起算后再 $\div 2$，不然会出现小数情况。

也可以直接 int128。

```cpp
#include<bits/stdc++.h>
#define ll __int128
using namespace std;
int T;
ll x_1, y_1, x_2, y_2;
ll ans = 0;
ll read(){
	ll ans = 0;
	char c;
	while(c < '0' || c > '9'){
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		ans = ans * 10 + c - '0';
		c = getchar();
	}
	return ans;
}
void write(ll x){
	if(x <= 9){
		putchar('0' + x);
		return ;
	}
	else write(x / 10); 
	putchar('0' + x % 10);
}
void write1(ll x, int dep){
	if(dep >= 10) return ;
	if(x <= 9){
		putchar('0' + x);
		return ;
	}
	else write1(x / 10, dep + 1); 
	putchar('0' + x % 10);
}
ll js2(ll x){
	return x * (x + 1) * ((ll)2 * x + 1) / (ll)6 ;
}
ll js3(ll x){
	return x * x * (x + (ll)1) * (x + 1) / (ll)4 ;
}
ll x3(ll x, ll y){
	if(x > y) return 0;
	return (js3(y) - js3(x - 1) ) ;
}
ll x2(ll x, ll y){
	if(x > y) return 0;
	return (js2(y) - js2(x - 1) ) ;
}
ll x1(ll x, ll y){
	if(x > y) return 0;
	return (y - x + 1) * (x + y) / (ll)2 ;
}
ll x0(ll x, ll y){
	if(x > y) return 0;
	return (y - x + 1);
}
ll op(){
	ans = 0;
	ll nx1 = max(x_1, y_1), nx2 = max(x_1 + 1, y_1);
	ll ny1 = min(x_2, y_2), ny2 = min(x_2 + 1, y_2);
	ans = (ans + x3(nx1, ny1)) ;
	ans = (ans + x2(nx1, ny1) * (- y_1) ) ;
	ans = (ans + x1(nx1, ny1) * ((ll)2 * y_1) ) ;
	ans = (ans + x0(nx1, ny1) * ((ll)1 - y_1) ) ;
	ans = (ans + (-x2(nx1, ny1) - x1(nx1, ny1) + x0(nx1, ny1) * (y_1 - y_1 * y_1)) / (ll)2); 
	if(x_2 > y_2){
		nx1 = max(y_2 + 1, x_1);
		ans = (ans + x2(nx1, x_2) * (y_2 - y_1 + (ll)1 ) ) ;
		ans = (ans + x1(nx1, x_2) * (ll)2  * (y_1 - y_2 - (ll)1 )  ) ;
		ans = (ans + x0(nx1, x_2) * (y_2 - y_1  + 1)  ) ;
		ans = (ans + x0(nx1, x_2) * (y_1 + y_2) * (y_2 - y_1  + (ll)1) / (ll)2 );
	}
	//x <= y
	
	ans = (ans + x3(nx2, ny2)) ;
	ans = (ans + x2(nx2, ny2) * (- x_1 ) ) ;
	ans = (ans + (-x2(nx2, ny2) + 3 * x1(nx2, ny2) + x0(nx2, ny2) * (x_1 * x_1 - 3 * x_1)) / 2);
	if(y_2 > x_2 + 1){
		nx2 = max(x_2 + 2, y_1);
		ans = (ans + x2(nx2, y_2) * (x_2 - x_1 + 1 ) ) ;
		ans = (ans + x0(nx2, y_2) * (x_2 - x_1 + 1 ) ) ;
		ans = (ans + x0(nx2, y_2) * (-(x_1 + x_2) * (x_2 - x_1 + 1 )) / 2);
	}
	//x > y
	return ans;
}
int main(){
	T = read();
	while(T--){
		x_1 = read();
		y_1 = read();
		x_2 = read();
		y_2 = read();
		swap(x_1, y_1);
		swap(x_2, y_2);
		ans = op();
		if(ans >= 1e10){
			printf("...");
			write1(ans, 0);
		}else{
			write(ans);
		}
		putchar('\n');
	}	
}
```

---

## 作者：int08 (赞：1)

## 前言
众所周知，一篇题解需要一张头图：
![](https://cdn.luogu.com.cn/upload/image_hosting/x5crmvxj.png)

你告诉我这玩意 $2.6\times10^3$？！

# Solution
首先这道题是让我们求矩阵某个部分的总和，或者叫它**二维区间和**，容易想到以二位前缀和再相减来简化。具体来说：设 $f_{x,y}$ 表示前 $x$ 行 $y$ 列的前缀和，易知有 $ans=f_{x_2,y_2}-f_{x_2,y_1-1}-f_{x_1-1,y_2}+f_{x_1-1,y_1-1}$。

现在只需要研究矩阵的前缀和即可。

前缀和由一个长方形组成，由于这个矩阵是一层一层的，位于左上角的正方形显然就比较整齐，也就比较好算

于是，对于一个 $x\times y$ 的美丽前缀和矩形，我们先取左上角的最大正方形，和剩下部分分开算。

例如 $x=3,y=4$ 时以加粗部分和未加粗部分分别计算：

|  |  |  |  |
| :----------: | :----------: | :----------: | :----------: |
| **1** | **2** | **5** | 10 |
| **4** | **3** | **6** | 11 |
| **9** | **8** | **7** | 12 |

### 1.左上角正方形总和是多少？
发现对于 $n\times n$ 的矩阵，$1$ 到 $n^2$ 正好各一次，直接加起来，也就是 $\frac {n^2\times (n^2+1)}{2}$。

### 2.剩下的长方形部分怎么办？

先以行少列多为例：此时剩下部分整体上处于列表中靠右部分，导致每一项都为上面加一，每列最上面的为列数减一的平方加一，具体一点：

| 行\列 | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $3^2+1$ | $4^2+1$ | $5^2+1$ |
| 2 | $3^2+2$ | $4^2+2$ | $5^2+2$ |
| 3 | $3^2+3$ | $4^2+3$ | $5^2+3$ |

横着看每一个格子第一个加数，它是许多个（具体来说为行数）连续数平方的和；竖着看第二个加数，它是许多个（具体来说为列数减行数）等差数列。

而又有平方和公式：$1^2+2^2+3^2+4^2+……+n^2=\frac{n(n+1)(2n+1)}{6}$

等差数列求和公式：$1+2+3+……+n=\frac{n(n+1)}{2}$

所以以上需要求的所有东西都可以 $O(1)$ 求出，太好了。

行多列少的自己仿照上面考虑一下先。

好吧同样列表：

| 行\列 | 1 | 2 | 3 |
| :----------: | :----------: | :----------: | :----------: |
| 4 | $4^2$ | $4^2-1$ | $4^2-2$ |
| 5 | $5^2$ | $5^2-1$ | $5^2-2$ |
| 6 | $6^2$ | $6^2-2$ | $6^2-2$ |

类似地可以求出，只不过加号变为了减号。

做完了……了？

还有三个重要问题亟待解决。

### 3.如何输出后十位？

运算时对 $10^{10}$ 取模，然而，上面有乘法运算，两个 $10^{10}$ 相乘会爆 long long，只好请出 __int128 同学了。

注意输入输出时可以仍用 long long 省去快读快写。

### 4.棘手的三个点

所以说我们得判断答案是否在 $10^{10}$ 以内，怎么做？

我采取的方法是：用同样的方法再算出一遍答案，但是全程不取模，自然溢出，因为 long long 几乎 $10^{19}$，自然溢出后几乎不可能仍在 $10^{10}$ 之内。

关于前导 $0$ 应该都会写吧。

### 5.不用写逆元
发现计算过程中有除法运算出现，怎么办，是不是必须写逆元呢？不是的，因为除数只有 $2$ 和 $6$，可以取余时对 $6\times10^{10}$ 取，这样就可以放心除。

## AC 代码
写得比较冗杂，但是我认为不必优化了，就是因为我觉得这道题代码难度并不高，也希望大家自己推推式子，而不是对着代码抄或者打。

奉劝一句：记得用 C++20。
```cpp
#include<bits/stdc++.h>
#define mod __int128(10000000000)
#define mo (long long)(10000000000)
using namespace std;
long long s(__int128 x,__int128 y)
{
	if(x==0||y==0) return 0;
	__int128 ans=0,n=min(x,y);
	if(n%2) ans=((((((n*n+1)/2)%mod)*n)%mod)*n)%mod;
	else ans=(((n*n/2)%mod)*((n*n+1)%mod))%mod;
	if(x>y)
	{
		__int128 b=(((((y-1)*(2*y-1))%(6*mod))*y)/6)%mod,c=(((((x-1)*(2*x-1))%(6*mod))*x)/6)%mod;
		c=(c-b+mod)%mod;
		ans=(ans+(c*y)%mod+((((y+1)*y/2)%mod)*(x-y))%mod)%mod;
	}
	if(y>x)
	{
		__int128 c=(((((y+1)*(2*y+1))%(6*mod))*y)/6)%mod,b=(((((x+1)*(2*x+1))%(6*mod))*x)/6)%mod;
		c=(c-b+mod)%mod;
		ans=(ans+(c*x)%mod+mod-((((x-1)*x/2)%mod)*(y-x))%mod)%mod;
	}
	return (ans%mod+mod)%mod;
}
long long sc(__int128 x,__int128 y)  //上下一样的
{
	if(x==0||y==0) return 0;
	__int128 ans=0,n=min(x,y);
	if(n%2) ans=((((((n*n+1)/2))*n))*n);
	else ans=(((n*n/2))*(n*n+1));
	if(x>y)
	{
		__int128 b=((((y-1)*(2*y-1))*y)/6),c=((((x-1)*(2*x-1))*x)/6);
		c=c-b;
		ans=ans+(c*y)+((((y+1)*y/2))*(x-y));
	}
	if(y>x)
	{
		__int128 c=(((((y+1)*(2*y+1)))*y)/6),b=((((x+1)*(2*x+1))*x)/6);
		c=c-b;
		ans=(ans+(c*x)-((((x-1)*x/2))*(y-x)));
	}
	return ans;
}
long long t,xa,ya,xb,yb;
int main()
{
	cin>>t;
	for(int ac=1;ac<=t;ac++)
	{
		cin>>ya>>xa>>yb>>xb;
		if(0>=sc(xb,yb)-sc(xb,ya-1)-sc(xa-1,yb)+sc(xa-1,ya-1)||10000000000<=sc(xb,yb)-sc(xb,ya-1)-sc(xa-1,yb)+sc(xa-1,ya-1))
		{
			cout<<"...";
			long long qq=10,bb=1;
			for(long long aa=(s(xb,yb)-s(xb,ya-1)-s(xa-1,yb)+s(xa-1,ya-1)+3*mo)%mo;aa>=1;aa/=10) qq--,bb=0;
			for(int aaa=1;aaa<=(bb?9:qq);aaa++) cout<<0;
		}
		cout<<(s(xb,yb)-s(xb,ya-1)-s(xa-1,yb)+s(xa-1,ya-1)+3*mo)%mo<<endl;
	}
	return 0;
}
```
# The End.


---

## 作者：syzf2222 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/syzf2222/p/14332342.html)

这题根本配不上紫题难度，除了细节巨难调以外，思维难度几乎为零。

考虑计算$calc(x,y)=(1,1)\rightarrow(x,y)$的值，答案即为$calc(x1-1,y1-1)+calc(x2,y2)-calc(x1-1,y2)-calc(x2,y1-1)$

1. $x=y\quad calc(x,y)=\frac12(1+x^2)x^2$

2. $x>y\quad calc(x,y)=\frac12(1+y^2)y^2+\sum\limits_{i=y+1}^x \sum\limits_{j=i^2-y+1}^{i^2}j=\frac12(1+y^2)y^2+\frac12y\sum\limits_{i=y+1}^x(2i^2-y+1)$

3. $x<y\quad calc(x,y)=\frac12(1+x^2)x^2+\sum\limits_{i=x+1}^y \sum\limits_{j=(i-1)^2+1}^{(i-1)^2+x}j=\frac12(1+x^2)x^2+\frac12x\sum\limits_{i=x+1}^y(2i^2-4i+3+x)$

如果这题是模$998244353$，$1e9+7$之类的数，那么恭喜做完了。

但这题的模数是$1e10$，不但是合数，乘起来还会爆$long long$，这使我们不得不考虑一些细节。

1. 判断是否结果小于$1e10$：再模一个$1e10+9$，比对结果。

2. 防止乘法爆$long long$：使用类似快速幂的快速乘法。

3. 计算过程中有出现取过模的数除以$2$，导致答案有$5e9$的误差：把模数改为$2e10$

这时发现因为过多的取模，我们完美地$TLE$了，下面有一些卡常$tricks$。

1. 因为$1e10$对于$long long$来说很小，所以最后取一次模就好了。

2. 快速乘法中建议取一个值，大于这个值再取模。

这样就可以愉快地$AC$本题了，时间复杂度$\Theta(n\log n)$

代码如下，以供参考：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod1=2e10;
const int mod2=1e10+9;
const int mod3=1e10;
const int val=1e16;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int mod,T;
inline int mul(int x,int y){
	int res=0;
	while(y){
		if(y&1)res+=x;
		x<<=1;
		if(x>=val)x%=mod;
		y>>=1;
	}
	return res%mod;
}
inline int calc(int x,int y){
	if(!x||!y)return 0;
	int res=0;
	if(x==y){
		int t=mul(x,x);
		if(t&1)res=mul(t,(t+1)>>1);
		else res=mul(t>>1,t+1);
		return res;
	}else if(x<y){
		int t=mul(x,x);
		if(t&1)res=mul(t,(t+1)>>1);
		else res=mul(t>>1,t+1);
		t=mul(x+3,y-x);
		t-=mul(x+y+1,(y-x)<<1);
		if(y%3==0)t+=mul(y/3,mul(y+1,y<<1|1));
		else if(y%3==1)t+=mul(y,mul(y+1,(y<<1|1)/3));
		else t+=mul(y,mul((y+1)/3,y<<1|1));
		if(x%3==0)t-=mul(x/3,mul(x+1,x<<1|1));
		else if(x%3==1)t-=mul(x,mul(x+1,(x<<1|1)/3));
		else t-=mul(x,mul((x+1)/3,x<<1|1));
		t=t%mod+mod;
		if(!(t&1))res=(res+mul(x,t>>1))%mod;
		else if(mod&1)res=(res+mul(x,(t+mod)>>1))%mod;
		else res=(res+mul(x>>1,t))%mod;
		return res;
	}else{
		swap(x,y);
		int t=mul(x,x);
		if(t&1)res=mul(t,(t+1)>>1);
		else res=mul(t>>1,t+1);
		t=mod-mul(y-x,x-1);
		if(y%3==0)t+=mul(y/3,mul(y+1,y<<1|1));
		else if(y%3==1)t+=mul(y,mul(y+1,(y<<1|1)/3));
		else t+=mul(y,mul((y+1)/3,y<<1|1));
		if(x%3==0)t-=mul(x/3,mul(x+1,x<<1|1));
		else if(x%3==1)t-=mul(x,mul(x+1,(x<<1|1)/3));
		else t-=mul(x,mul((x+1)/3,x<<1|1));
		t=t%mod+mod;
		if(!(t&1))res=(res+mul(x,t>>1))%mod;
		else if(mod&1)res=(res+mul(x,(t+mod)>>1))%mod;
		else res=(res+mul(x>>1,t))%mod;
		return res;
	}
}
inline int solve(int x1,int y1,int x2,int y2){
	return ((calc(x1-1,y1-1)+calc(x2,y2)-calc(x1-1,y2)-calc(x2,y1-1))%mod+mod)%mod;
}
signed main(){
	T=read();
	int x1,x2,y1,y2;
	while(T--){
		x1=read(),y1=read();
		x2=read(),y2=read();
		mod=mod1;int res1=solve(x1,y1,x2,y2)%mod3;
		mod=mod2;int res2=solve(x1,y1,x2,y2);
		if(res1^res2)printf("...%.10lld\n",res1);
		else printf("%lld\n",res1);
	}
	return 0;
}
```
然而为什么人家都是$8$秒$9$秒，我一个人$48$秒（大雾

---

