# [ARC004C] 平均値太郎の憂鬱 ( The melancholy of Taro Heikinchi )

## 题目描述

太郎在计算1到n的平均数时漏加了一个m，给定算错的平均数，求正确的N和M

# 题解

## 作者：qcf2010 (赞：3)

## 题意

某人在算 $1$ 至 $n$ 的平均数时漏加了一个数 $m$，得出了一个错误答案 $x/y$（不一定为最简分数），让你求出所有可能的 $n$ 和 $m$。若无解，则输出```Impossible```。


## 思路

由题意可得：
$$\begin{aligned}
\frac{x}{y}&=\frac{\frac{n(n+1)}{2}-m}{n}\\
           &=\frac{n+1}{2}-\frac{m}{n}
\end{aligned}$$

因为 $1 \le m \le n$，所以 $0 < m/n \le 1$，带入上式，可得：
$$\frac{x}{y} < \frac{n+1}{2} \le \frac{x}{y}+1$$

我们又可以用 $n$ 来表示 $m$，具体如下：

因为
$$\frac{x}{y}=\frac{n+1}{2}-\frac{m}{n}$$

所以
$$\frac{m}{n}=\frac{n+1}{2}-\frac{x}{y}$$

所以
$$m=\frac{n(n+1)}{2}-\frac{nx}{y}$$

综上，我们可以枚举 $n$，计算 $m$ 是否合法即可。

## 代码
这里介绍我国古代一种计算最大公约数的方法：[更相减损术](https://oi-wiki.org/math/number-theory/gcd/#%E6%9B%B4%E7%9B%B8%E5%87%8F%E6%8D%9F%E6%9C%AF)，主要用于高精度运算，有兴趣的同学可以学习一下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll Gcd(ll a,ll b){
	while(a!=b){
		if(a>b) a-=b;
		else b-=a;
	}
	return a;
}

ll x,y,n,m;
bool f=1;

int main(){
	scanf("%lld/%lld",&x,&y);
	ll gcd=Gcd(x,y);
	x/=gcd,y/=gcd;
	n=2*x/y;
	while(y*(n+1)<=2*(x+y)){
		if(n%y!=0){
			n++;
			continue;
		}
		m=n*(n+1)/2-n/y*x;
		if(1<=m&&m<=n){
			printf("%lld %lld\n",n,m);
			f=0;
		}
		n++;
	}
	if(f) printf("Impossible\n");
	return 0;
}

```

## 重点来了
~~理解代码还是有点难的，我这里就解释一下吧。~~

* * *

### 为什么```n=2*x/y```？

  在上文提到过：
  $$\frac{x}{y} < \frac{n+1}{2} \le \frac{x}{y}+1$$

  看这一部分：
  $$\frac{x}{y} < \frac{n+1}{2}$$

  整理可得：
  $$n > \frac{2x}{y}-1$$
  
  又因为 $n$ 为整数，所以有代码```n=2*x/y```。

* * *
  
### 为什么```y*(n+1)<=2*(x+y)```？

  还是这条式子：
  $$\frac{x}{y} < \frac{n+1}{2} \le \frac{x}{y}+1$$
  
  看后半部分：
  $$\frac{n+1}{2} \le \frac{x}{y}+1$$

  整理可得：
  $$y(n+1) \le 2(x+y)$$

  所以有代码```y*(n+1)<=2*(x+y)```。

---

## 作者：NY_An18623091997 (赞：2)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/AT_arc004_3)  
题目翻译应该够简洁了吧。
## 思路
首先，$\displaystyle \sum_{i=1}^{n} i = \displaystyle \frac{n(1+n) }{2}$（等差数列）。  
   
由题意：  
   
$$\displaystyle \frac{x}{y} = \displaystyle \frac{\frac{n(1+n) }{2}-m}{n}$$  
   
化简得：  
   
$$\displaystyle \frac{x}{y} = \displaystyle \frac{n+1}{2} - \displaystyle \frac{m}{n}$$

所以：  
   
$$\displaystyle \frac{m}{n} = \displaystyle \frac{n+1}{2} - \displaystyle \frac{x}{y} $$  

$$\displaystyle m= \displaystyle \frac{n(n+1)}{2}-\displaystyle \frac{xn}{y}$$

再来看 $\displaystyle \frac{x}{y} = \displaystyle \frac{n+1}{2} - \displaystyle \frac{m}{n}$  
因为 $1 \le m \le n$，所以 $0 < \frac{m}{n} \le 1$。  
带入得：
$$\displaystyle \frac{x}{y} < \displaystyle \frac{n+1}{2} \le \displaystyle \frac{x}{y}+1$$  
就可以推出：  
$$n> \displaystyle \frac{2x}{y}+1$$
和
$$y \le 2x+(2-n)y $$
最后就根据前面推出的代数式直接枚举 $n$ 即可。
### 坑点
$\bullet$ 无解时，输出要记得换行，不换行的[后果](https://www.luogu.com.cn/record/196852340)。  
$\bullet \ 1\le X \le 10^{18}$，需要开 long long。  
$\bullet $ 代码中，  

    m=n*(n+1)/2-n/y*x;
切记不要是：

    m=n*(n+1)/2-n*x/y;
否则就会因为精度差等问题变成[这样](https://www.luogu.com.cn/record/196865759)。
## AC code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,y,z,n,m;
char c;
bool fl;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>x>>c>>y;
	z=__gcd(x,y);
	x/=z,y/=z;
	n=2*x/y;
	for(;y<=2*x+(2-n)*y;n++){
		m=n*(n+1)/2-n/y*x;
		if(n%y)	continue;
		if(1<=m&&m<=n){
			fl=1;
			cout<<n<<" "<<m<<"\n";
		}
	}
	if(fl)	return 0;
	cout<<"Impossible\n";//不换行会WA!!!
	return 0;
}
```
**[AC记录](https://www.luogu.com.cn/record/196858442)**

---

## 作者：leixinranYY (赞：1)

## 题目简译
 $1$ 到 $n$ 的平均数时漏加了一个 $m$ ，给定算错的平均数 $\frac{x}{y}$ ，求正确的 $n$ 和 $m$ 。

## 思路
首先，由题意得：

 $$\displaystyle \frac{x}{y}= \frac{\frac{n(n+1)}{2}-m}{n}=\frac{n+1}{2}-\frac{m}{n}$$ 

整理得：

 $$\displaystyle m=\frac{n(n+1)}{2}-\frac{xn}{y}$$ 

因为 $1 \le m \le n$ ，所以 $0 < \frac{m}{n} \le 1$ ，带入原式得：

 $$\displaystyle \frac{x}{y}<\frac{n+1}{2}\le \frac{x}{y}+1$$ 

经整理，得：

 $$\displaystyle n=\frac{2x}{y}$$ 

 $$\displaystyle y(n+1)\le2(x+y)$$ 

接着枚举 $n$ ，符合条件就输出。另外，因为**数据过大**，记得开 long long。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y,n,m,p;
int gcd(int a,int b) 
{ return b ? gcd(b,a%b) : a; }
void init()
{
	int g=gcd(x,y);
	x/=g,y/=g;
	n=2*x/y,p=1;
}
signed main()
{
	scanf("%lld/%lld",&x,&y);// 输入注意格式
	init();
	for(;y*(n+1)<=2*(x+y);n++)
	{
		m=(n*n+n)/2-n/y*x;
		if(n%y)continue;
		if(1<=m && m<=n)
		{
			p=0;
			printf("%lld %lld\n",n,m);
		}
	}
	if(p)printf("Impossible\n");// 换行！
	return 0;// 完结散花
}
```
**[AC 记录](https://www.luogu.com.cn/record/196861516)**

---

## 作者：scp020 (赞：1)

本题是一道数学（分式，多项式混合运算，整除）问题，考察大家的数学功底。

### 1. 坑点

- 不要使用系统自带的 $\gcd()$ 函数，因为系统 自带函数传参是 $int$ 型，而题里 $x$ 是长整型，会出错的。

- 如果有多组解，我们要输出多行，一行一组解（别看题里说的在第一行输出）。

- 输入格式为 $X/Y$，用 `scanf("%d/%d",&x,&y)` 输入即可。

### 2. 相关推导

由题，$\begin{aligned}\dfrac{x}{y} & =\dfrac{\dfrac{n(n+1)}{2}-m}{n}\\ &=\dfrac{n+1}{2}- \dfrac{m}{n} \end{aligned}$。

所以，我们可以推出（中间过程我就不写了，$\LaTeX$ 太难弄了）：

$m=\dfrac{ny(n+1)+2xn}{2y}$。

因为 $m$ 为整数，所以 $ny(n+1)+2xn\equiv0\pmod{2y}$。

对于 $ny(n+1)$，$n(n+1)\equiv0\pmod{2}$。

所以 $xn\equiv0\pmod{y}$。

### 3. 代码（有注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,n,m,GCD;
bool f;
long long gcd(long long a,long long b)//gcd递归模板 
{
    return b?gcd(b,a%b):a;
}
int main()
{
	scanf("%lld/%lld",&x,&y),GCD=gcd(x,y);//注意输入格式，为"x/y"形式，scanf好用捏 
	x/=GCD,y/=GCD;//不要使用系统函数gcd，因为它传参是int型 
	n=x*2/y;
	while(n*n*y-2*n*x+n*y<=2*n*y)//当m<=n，不懂私信我
	{
		if(n%y!=0)//n要不是y的倍数就白扯 
		{
			n++;
			continue;
		}
		m=n*(n+1)/2-n/y*x;
		if(m>=1 && m<=n) cout<<n<<" "<<m<<endl,f=true;//可能有多组解，前往别急着return 
		n++;
	}
	if(!f) cout<<"Impossible"<<endl; 
	return 0;
}
```


---

## 作者：LeavingAC (赞：0)

**begin**

[AT_arc004_3 平均値太郎の憂鬱](https://www.luogu.com.cn/problem/AT_arc004_3)

# 前言

数学题一道。

# 题目大意

给定错误的平均数形如 $\frac{x}{y}$。你需要找出所有满足的 $n$ 和 $m$。

# 思路

题目让我们根据 $n$ 从小到大排序。由此我们可以想到枚举 $n$ 求答案。

再结合题目中的隐藏条件：$1 \le m \le n $，即可进行解题。

# 分析

由题意可知：

$$\frac{x}{y} =\frac{\frac{n(n+1)}{2}-m}{n} $$

化简得到（这个式子之后很常用，以下简称 $A$）：

$$\frac{m}{n}=\frac{n+1}{2}-\frac{x}{y} $$

整理得到：

$$m=\frac{n(n+1)}{2}-\frac{nx}{y} $$

由 $1 \le m \le n $ 可知：

$$0<\frac{m}{n} \le 1 $$

结合 $A$ 得到：

$$0<\frac{n+1}{2}-\frac{x}{y}\le 1\\$$

$$\frac{x}{y}<\frac{n+1}{2}\le \frac{x}{y}+1$$

整理前半段得到 ① 式：

$$n>\frac{2x}{y}-1 $$

$$n \ge \frac{2x}{y} $$

整理后半段得到 ② 式：

$$y(n+1)\le2(x+y) $$

最后我们得出代码。

# Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define gc() getchar()
#define pc(a) putchar(a)
#define sqrt(a) __builtin_sqrt(a)
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a/__gcd(a,b)*b
#define y1 fuck_cmath
using namespace std;
const int M=1e5+10;
ll x,y,n,m,g;
char ch;
bool flag;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>x>>ch>>y;
    g=gcd(x,y);
    x/=g,y/=g;
    n=2*x/y;
    for (;y*(n+1)<=2*(x+y);n++)
    {
        if (n%y) continue;
        m=n*(n+1)/2-n/y*x; // 先除再乘避免溢出
        if (m>=1 && m<=n)
        {
            flag=1;
            cout<<n<<" "<<m<<"\n";
        }
    }
    if (!flag) cout<<"Impossible\n"; // 没\n会WA
    return 0;
}
```

---

## 作者：pjh0625 (赞：0)

似乎是没有python题解，作为python的~~狂热分子~~，必须凑个热闹。

[题目传送门](https://www.luogu.com.cn/problem/AT_arc004_3)


### 分析题目：

我们知道从 $1$ 到 $N$ 的正确总和是
$$
\frac{N(N+1)}{2-M}
$$

太郎在计算平均值时遗漏了一个数 $M$ ，因此错误的平均值计算公式是:
$$
N\frac{N+1}{2-\frac{M}{2}}
$$

这个平均值给定为 $\frac{X}{Y}$ ，所以我们可以得到以下方程： 
$$
N\frac{N+1}{2-M}=\frac{XN}{Y}
$$

重排可以得到：
$$
M=N\frac{N+1}{2-\frac{XN}{Y}}
$$

**推导条件:**
为了使 $M$ 是一个正整数且满足 $1<=M<=N$ ，我们需要分析得到的 $M$ ：  
$$
M=N\frac{N+1}{2-\frac{X}{Y}}
$$

从上面公式中可知我们需要:

1.满足 $(N+1)Y>2X$ 

2.要求 $N<\frac{2X}{Y}-1$ 

**算法步骤:**

遍历可能的 $N$ ：从 $1$ 开始逐渐增加，直到达到合适的上限。

对于每个 $N$ ，使用上面的公式计算 $M$ ，并检查:

 $M$ 是否为正整数及 $M$ 是否满足 $1<=M<=N$  。

输出所有有效的 $(N,M)$ 组合，或输出 "Impossible" 。


## 代码实现:

```python
import sys
def a(X, Y):
    b = []
    c = 10**9
    for N in range(1, c + 1):
        d = (N * (N + 1)) // 2
        if (d * Y - X * N) % Y != 0:
            continue
        M = (d * Y - X * N) // Y
        if 1 <= M <= N:
            b.append((N, M))
    if b:
        b.sort()
        for n, m in b:
            print(n, m)
    else:
        print("Impossible")

if __name__ == "__main__":
    input = sys.stdin.read().strip()
    X, Y = map(int, input.split('/'))
    a(X, Y)

```

---

## 作者：huangjunhan (赞：0)

# 题目大意
有个人在计算 $1$ 到 $n$ 的平均数时漏加了一个 $m$，已知算错的平均数是 $\frac{x}{y}$，求正确的 $n$ 和 $m$。
# 解题思路
本题输入一个分数，需要进行约分，就能直接枚举。自然，我们需要求 $x$ 和 $y$ 的最大公约数。

  由于本题数据较大，$x$ 的值有 $10^{18}$，用 int 存不下，而 C++ 自带的 gcd 函数的参数范围只有 int，所以要手打最大公约数函数。
# 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,n,m,sum,t,l;
bool flag;
char ch;
long long gcd(long long a,long long b){
	if(b==0)return a;
	gcd(b,a%b);
}
int main(){
	cin>>x>>ch>>y;
	sum=gcd(x,y);
	x/=sum,y/=sum;
	t=x*2/y;
	while((t+1)*y<=2*(x+y)){
		if(t%y!=0){
			t++;
			continue;
		}
		l=t*(t+1)/2-t/y*x;
		if(l>=1&&l<=t){
			cout<<t<<" "<<l<<endl;
			flag=1;
		}
		t++;
	}
	if(!flag)cout<<"Impossible\n";
}
```

---

## 作者：AFewSuns (赞：0)

### 题目大意

[$\color{black}\text{D}\color{red}\text{ementor}$](https://www.luogu.com.cn/user/228720#main) 在算 $1 \sim n$ 的平均数的时候，不小心把 $m$ 漏加上了，得到了一个结果 $\frac{x}{y}$。他当然不开心啦，于是他给你这个结果 $\frac{x}{y}$，让你求出 $n$ 和 $m$。

如果有多解，按 $n$ 从小到大输出。如果无解，输出 `Impossible`。

$1 \leq x \leq 10^{18},1 \leq y \leq 10^9$

### 题目分析

先对 $\dfrac{x}{y}$ 进行约分。假设我们已经知道了 $n$ 和 $m$，那么答案就是 $\dfrac{x}{y}=\dfrac{\frac{n(n+1)}{2}-m}{n}=\dfrac{n+1}{2}-\dfrac{m}{n}$。

因为有 $1 \leq m \leq n$，所以 $0 < \dfrac{m}{n} \leq 1$，可以得到 $\dfrac{x}{y} < \dfrac{n+1}{2} \leq \dfrac{x}{y}+1$。

那么这样 $n$ 的取值就最多只有 $2$ 个了，我们可以枚举 $n$ 来算 $m$。

具体地：
$$\frac{x}{y}=\frac{n+1}{2}-\frac{m}{n}$$
$$\frac{xn}{y}=\frac{n(n+1)}{2}-m$$
$$m=\frac{n(n+1)}{2}-\frac{xn}{y}$$

其中 $n$ 一定要是 $y$ 的倍数。判断一下解出来的 $m$ 符不符合 $1 \leq m \leq n$，如果是就输出。

**注意所有解都要输出，并且后面要有换行**。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,y,n,m,d;
bool ck=0;
ll gcd(ll a,ll b){
	if(!b) return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%lld/%lld",&x,&y);
	d=gcd(x,y);
	x/=d;
	y/=d;
	n=(2*x)/y;
	if(!n) n++;//计算 n 的最小值 
	while((n+1)*y<=2*(x+y)){//暴力枚举 
		if(n%y){//n要是y的倍数 
			n++;
			continue;
		}
		m=n*(n+1)/2-x*(n/y);
		if(m>=1&&m<=n){
			printf("%lld %lld\n",n,m);
			ck=1;
		}
		n++;
	}
	if(!ck) printf("Impossible\n");//注意判误解 
}
```

---

