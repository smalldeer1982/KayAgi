# [ABC402G] Sum of Prod of Mod of Linear

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc402/tasks/abc402_g

给定整数 $N,M,A,B_1,B_2$。

请计算以下表达式的值：
$$ \sum_{k=0}^{N-1} \left\lbrace (Ak+B_1) \bmod M \right\rbrace \left\lbrace (Ak+B_2) \bmod M \right\rbrace $$

共有 $T$ 个测试用例，请对每个测试用例分别给出答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 10^5$
- $1 \leq N \leq 10^6$
- $1 \leq M \leq 10^6$
- $0 \leq A,B_1,B_2 < M$
- 输入中的所有数值均为整数

### 样例解释 1

对于第一个测试用例：
- 当 $k=0$ 时：$(2 \times 0 + 1) \bmod 7 = 1$，$(2 \times 0 + 4) \bmod 7 = 4$
- 当 $k=1$ 时：$(2 \times 1 + 1) \bmod 7 = 3$，$(2 \times 1 + 4) \bmod 7 = 6$
- 当 $k=2$ 时：$(2 \times 2 + 1) \bmod 7 = 5$，$(2 \times 2 + 4) \bmod 7 = 1$
- 当 $k=3$ 时：$(2 \times 3 + 1) \bmod 7 = 0$，$(2 \times 3 + 4) \bmod 7 = 3$

因此，所求值为 $1 \times 4 + 3 \times 6 + 5 \times 1 + 0 \times 3 = 27$。所以第一行输出 27。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4 7 2 1 4
12 15 2 8 7
777 1 0 0 0
100 101 0 100 100
402 402 4 19 256```

### 输出

```
27
866
0
1000000
13728568```

# 题解

## 作者：违规用户名1425622 (赞：6)

省流：一坨式子，可以直接看最后的总结。

#### 简要题意

多次询问，每次给定 $N,M,A,B_1,B_2$，求

$$
\sum_{k=0}^{N-1} \left\lbrace (Ak+B_1)\ \text{mod}\ M \right\rbrace\left\lbrace (Ak+B_2)\ \text{mod}\ M \right\rbrace
$$

#### 解法

首先你先把难看的取模变成好看一点的除法，那么式子就是

$$
\sum_{k=0}^{N-1} (Ak+B_1-M\big\lfloor \frac{Ak+B_1}{M} \big\rfloor)  (Ak+B_2-M\big\lfloor \frac{Ak+B_2}{M} \big\rfloor)
$$

你发现这个式子长得很吓人，但其实还好，只有 $\sum\limits_{k=0}^{N-1} \lfloor \frac{Ak+B_1}{M} \rfloor\lfloor \frac{Ak+B_2}{M} \rfloor$ 是难做的。

不妨设 $B_1<B_2$，那么我们有 $0 \le \lfloor \frac{Ak+B_2}{M} \rfloor-\lfloor \frac{Ak+B_1}{M} \rfloor \le 1$。

于是现在式子就是 $\sum\limits_{k=0}^{N-1} \lfloor \frac{Ak+B_1}{M} \rfloor(\lfloor \frac{Ak+B_2}{M} \rfloor-\lfloor \frac{Ak+B_1}{M} \rfloor)$。

其实到这一步多卡卡常就可以过了，但我们多推几步就可以有更优的做法。

考虑什么时候 $\lfloor \frac{Ak+B_2}{M} \rfloor-\lfloor \frac{Ak+B_1}{M} \rfloor=1$，我们设 $i=\lfloor \frac{Ak+B_1}{M} \rfloor$，考虑有多少 $k$ 满足条件，经过简单的推导容易得到

$$
\bigg\lfloor \frac{Mi+M-B_2-1}{A} \bigg\rfloor<k \le \bigg\lfloor \frac{Mi+M-B_1-1}{A} \bigg\rfloor
$$

设 $X=\lfloor \frac{A(N-1)+B_1}{M} \rfloor$，那么只在 $i=X$ 时 $k$ 有可能超过 $N-1$ 范围，特判即可。

#### 总结
一 目 了 然
$$
A^2 \sum_{k=0}^{N-1} k^2+A(B_1+B_2) \sum_{k=0}^{N-1} k+B_1B_2N-AM\sum_{k=0}^{N-1}\lfloor \frac{Ak+B_1}{M} \rfloor-AM\sum_{k=0}^{N-1}\lfloor \frac{Ak+B_2}{M} \rfloor-MB_2\sum_{k=0}^{N-1}k\lfloor \frac{Ak+B_1}{M} \rfloor-MB_1\sum_{k=0}^{N-1}k\lfloor \frac{Ak+B_2}{M} \rfloor+M^2\sum_{k=0}^{N-1}\lfloor \frac{Ak+B_1}{M} \rfloor^2+M^2\sum_{k=0}^{X-1}k(\bigg\lfloor \frac{Mk+M-B_1-1}{A} \bigg\rfloor-\bigg\lfloor \frac{Mk+M-B_2-1}{A} \bigg\rfloor)+M^2X(\min(N,\bigg\lfloor \frac{Mk+M-B_1-1}{A} \bigg\rfloor)-\min(N,\bigg\lfloor \frac{Mk+M-B_2-1}{A} \bigg\rfloor))
$$

---

## 作者：Purslane (赞：6)

# Solution

类欧。做法来自日文题解，非常简洁而优美。

题目让我们求

$$
\sum_{k=0}^{n} (ak+b_1 - m \lfloor \frac{ak+b_1}{m} \rfloor)(ak+b_2 - m \lfloor \frac{ak+b_2}{m} \rfloor)
$$

这个东西展开，发现我们要会求：

1. $\sum_{k=0}^{n} \lfloor \frac{ak+b}{c} \rfloor$，这是经典的类欧。
2. $\sum_{k=0}^{n} k \lfloor \frac{ak+b}{c} \rfloor$。这也是经典的类欧，参照 [OI-wiki](https://oi-wiki.org/math/number-theory/euclidean/#%E6%89%A9%E5%B1%95)。
3. $\sum_{k=0}^{n} \lfloor \frac{ak+b_1}{c} \rfloor \lfloor \frac{ak+b_2}{c} \rfloor$。

感觉需要一些小巧思。注意到当 $0 \le b_2 \le b_1 < c$ 时，有 $0 \le \lfloor \frac{ak+b_1}{c} \rfloor - \lfloor \frac{ak+b_2}{c} \rfloor \le 1$。

所以！有 $\sum_{k=0}^{n} (\lfloor \frac{ak+b_1}{c} \rfloor - \lfloor \frac{ak+b_2}{c} \rfloor)(\lfloor \frac{ak+b_1}{c} \rfloor - \lfloor \frac{ak+b_2}{c} \rfloor-1) =0$。

将其展开，得到

$$
\sum_{k=0}^{n} (\lfloor \frac{ak+b_1}{c} \rfloor)^2 + (\lfloor \frac{ak+b_2}{c} \rfloor)^2 - 2 \lfloor \frac{ak+b_1}{c} \rfloor \lfloor \frac{ak+b_2}{c} \rfloor + \lfloor \frac{ak+b_2}{c} \rfloor - \lfloor \frac{ak+b_1}{c} \rfloor = 0
$$

因此我们求的其实就是

$$
\frac{1}{2}(h(a,b_1,c,n) +h(a,b_2,c,n) + f(a,b_2,c,n) - f(a,b_1,c,n))
$$

（函数的具体含义参考 OI-Wiki）。

使用类欧同时求解 $f$、$g$、$h$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
struct Node {int f,g,h;};
int sq_sum(int n) {return n*(n+1)/2;}
int cb_sum(int n) {return n*(n+1)*(n+n+1)/6;}
Node solve(int a,int b,int c,int n) {
	if(n<0) return {0,0,0};
	if(a==0) {
		int x=b/c;
		return {x*(n+1),x*sq_sum(n),x*x*(n+1)};
	}
	if(a>=c||b>=c) {
		auto qr=solve(a%c,b%c,c,n);
		int A=a/c,B=b/c,sq=sq_sum(n),cb=cb_sum(n);
		return {qr.f+B*(n+1)+A*sq,qr.g+A*cb+B*sq,A*A*cb+(n+1)*B*B+A*B*sq*2+qr.h+2*B*qr.f+2*A*qr.g};
	}
	int A=a/c,B=b/c,sq=sq_sum(n),cb=cb_sum(n);
	int m=(a*n+b)/c;
	auto qr=solve(c,c-b-1,a,m-1);
	return {n*m-qr.f,(sq*m*2-qr.h-qr.f)/2,m*m*n-2*qr.g-qr.f};
}
int T,n,a,b1,b2,m;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m>>a>>b1>>b2,n--;
		if(b1<b2) swap(b1,b2);
		auto nd1=solve(a,b1,m,n),nd2=solve(a,b2,m,n);
		int ans=a*a*cb_sum(n)+b1*b2*(n+1)+a*(b1+b2)*sq_sum(n);
		ans=ans-b1*m*nd2.f-a*m*nd2.g-b2*m*nd1.f-a*m*nd1.g;
		int tmp=(nd1.h+nd2.h+nd2.f-nd1.f)/2;
		ans=ans+m*m*tmp;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：STARSczy (赞：2)

求：
$$\sum_{i=0}^n[(ai+b_1)\mod c][(ai+b_2)\mod c]$$

可化成：

$$\begin{aligned} 
&=\sum_{i=0}^n[(ai+b_1)-c\lfloor\frac{ai+b_1}{c}\rfloor][(ai+b_2)-c\lfloor\frac{ai+b_2}{c}\rfloor]\\
&=\sum_{i=0}^n(ai+b_1)(ai+b_2)-\sum_{i=0}^n c\lfloor\frac{ai+b_1}{c}\rfloor(ai+b_2)-\sum_{i=0}^n c\lfloor\frac{ai+b_2}{c}\rfloor(ai+b_1)+c^2\sum_{i=0}^n\lfloor\frac{ai+b_1}{c}\rfloor\lfloor\frac{ai+b_2}{c}\rfloor
\end{aligned} $$

前面三个求和都可以直接或使用类欧万欧解决。看看最后一个求和怎么做。

不妨令 $b_1\leq b_2$。

$$
\begin{aligned} 
\sum_{i=0}^n\lfloor\frac{ai+b_1}{c}\rfloor\lfloor\frac{ai+b_2}{c}\rfloor
&=\sum_{i=0}^n \lfloor\frac{ai+b_2}{c}\rfloor^2-\lfloor\frac{ai+b_2}{c}\rfloor(\lfloor\frac{ai+b_2}{c}\rfloor-\lfloor\frac{ai+b_1}{c}\rfloor)\\
&=\sum_{i=0}^n \lfloor\frac{ai+b_2}{c}\rfloor^2-\sum_{i=0}^n\lfloor\frac{ai+b_2}{c}\rfloor(\lfloor\frac{ai+b_2}{c}\rfloor-\lfloor\frac{ai+b_1}{c}\rfloor)
\end{aligned}$$

第一部分可以直接使用类欧或万欧算。

由于 $0\leq b_1 \leq b_2< c$，故 $0\leq\lfloor\frac{ai+b_2}{c}\rfloor-\lfloor\frac{ai+b_1}{c}\rfloor\leq 1$，我们只需要计算它等于 $1$ 的时候。

如图，由于这一坨有周期性，周期为 $c$，每一段连续的 $1$ 长度相同，所以我们可以理解为求的是红色部分。将每个红色分为上下两部分，下面是红色部分所包含的最大长方形，绿色部分为剩余部分。下面的部分是好求的；而由于周期性，每个绿色部分是一样的，我们只需求出一个绿色部分即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/t7cnjv38.png)

最后再把边界情况处理一下。

---

## 作者：wwt100127 (赞：1)

~~第一篇黑体题解，好兴奋~~
## 题意
$T$ 组数据，给定 $N,M,A,B_1,B_2$，求
$$
\sum_{i=0}^{N-1} \left[(Ai+B_1) \bmod M \right] \left[ (Ai+B_2) \bmod M \right]
$$
其中 $0 \le A,B_1,B_2 < M$。

## 前置知识
[类欧几里得算法](https://www.luogu.com.cn/problem/P5170)

## 思路
显然 $B_1,B_2$ 等价，不妨设 $B_1 \ge B_2$（否则将两数交换）。

取模比较烦人，所以将原式化成：
$$
\sum_{i=0}^{N-1}
\left[(Ai+B_1) -  M \left \lfloor \frac{Ai+B_2}{M}  \right \rfloor \right]
\left[(Ai+B_2) -  M \left \lfloor \frac{Ai+B_2}{M}  \right \rfloor \right]
$$

记
$$
a_i = \left \lfloor \frac{Ai+B_1}{M}  \right \rfloor ,b_i=\left \lfloor \frac{Ai+B_2}{M}  \right \rfloor
$$

展开后就是：
$$
\sum_{i=0}^{N-1}(Ai+B_1)(Ai+B_2) -
M \sum_{i=0}^{N-1}(Ai+B_1)b_i -
M \sum_{i=0}^{N-1}(Ai+B_2)a_i +
M^2 \sum_{i=0}^{N-1} a_ib_i
$$
第一个可以 $O(1)$ 求出，中间两个算是类欧几里得的板子，我们只需要处理第四个式子就行了。

考虑如何用已知“凑”出 $\sum_{i=0}^{N-1} a_ib_i$。

~~于是你的眼睛无意间扫到了 $0 \le B_1,B_2 < M$ 这个条件~~

也就是说，$(a_i-b_i)$ 的值只能为 $0$ 或 $1$。

那么 $\sum_{i=0}^{N-1} (a_i-b_i)(a_i-b_i-1)= 0$。

展开得：
$$
\sum_{i=0}^{N-1} a_ib_i = \frac{1}{2} \sum_{i=0}^{N-1} (a_i^2+b_i^2-a_i+b_i)
$$
同样可以用类欧几里得解决。

所以最终的答案：
$$
Answer(N-1,M,A,B_1,B_2)= \frac{A^2N(N+1)(2N+1)}{6} + \frac{A(B_1+B_2)N(N+1)}{2} + B_1B_2(N+1)
- M \left [ A \times (h(A,B_1,M,N) + h(A,B_2,M,N)) - B_1 \times f(A,B2,M,N) - B_2 \times f(A,B_1,M,N) \right]
+ \frac{M^2}{2} \left [g(A,B_1,M,N) + g(A,B_2,M,N) - f(A,B_1,M,N) + f(A,B_2,M,N) \right ]
$$

其中：
$$
f(A,B,M,N) = \sum_{i=0}^{N} \left \lfloor \frac{Ai+B}{M} \right \rfloor \\

g(A,B,M,N) = \sum_{i=0}^{N} \left \lfloor \frac{Ai+B}{M} \right \rfloor^2  \\

h(A,B,M,N) = \sum_{i=0}^{N} i \left \lfloor \frac{Ai+B}{M} \right \rfloor
$$

## 代码
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
bool Beginning;

#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define se second
#define fi first
using PII=pair<int,int>;
using PIB=pair<int,bool>;
using PBI=pair<bool,int>;
using PBB=pair<bool,bool>;
using PDI=pair<double,int>;
using PID=pair<int,double>;

namespace Memory_Love{
	int read(){ int x=0; bool flag=1; char ch=getchar();
		while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
		while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();} return flag? x:-x;}
	template<typename T> void read(T &x){ bool flag=1; x=0; char ch=getchar();
		while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
		while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();} x=(flag? x:-x);}
	template<typename T,typename ...Args> void read(T &Re,Args &...Res){read(Re),read(Res...);}
	template<typename T> void write(T x,char ch=0){if(x<0) x=-x,putchar('-');
		static short s[35],top=-1; do{s[++top]=x%10;x/=10;}while(x);
		while(~top) putchar(s[top--]+48); if(ch) putchar(ch);}
	int gcd(int a,int b){return b==0? a:gcd(b,a%b);}
	int lcm(int a,int b){return a/gcd(a,b)*b;}
} using namespace Memory_Love;
int n,m,a,b1,b2;

struct Node
{
	int f,g,h;
	Node(int F=0,int G=0,int H=0){f=F,g=G,h=H;}
};
namespace Euclid
{
	int Pow2(int x){return x*x;}
	Node solve(int a,int b,int c,int n)
	{
		int f,g,h;
		if(a==0)
		{
			f=b/c*(n+1);
			g=Pow2(b/c)*(n+1);
			h=b/c*n*(n+1)/2;
		}
		else
		if(a>=c || b>=c)
		{
			Node last=solve(a%c,b%c,c,n);
			f=(a/c*n*(n+1)/2+b/c*(n+1)+last.f);
			g=(n*(n+1)*(2*n+1)/6*Pow2(a/c)+(n+1)*Pow2(b/c)+(a/c)*(b/c)*n*(n+1)+2*(b/c)*last.f+2*(a/c)*last.h+last.g);
			h=((a/c)*n*(n+1)*(2*n+1)/6+(b/c)*n*(n+1)/2+last.h);
		}
		else
		{
			int m=(a*n+b)/c;
			Node last=solve(c,c-b-1,a,m-1);
			f=(n*m-last.f);
			g=(n*m*(m+1)-f-2*(last.h+last.f));
			h=(n*m*(n+1)-last.g-last.f)/2;
		}
		return (Node){f,g,h};
	}
}

int solve()
{
	read(n,m,a,b1,b2);
	n--; if(b1<b2) swap(b1,b2);
	Node P1=Euclid::solve(a,b1,m,n);
	Node P2=Euclid::solve(a,b2,m,n);
	int ans1=a*a*n*(n+1)*(2*n+1)/6;
	int ans2=a*(b1+b2)*n*(n+1)/2;
	int ans3=(n+1)*b1*b2;
	int ans4=m*(a*(P1.h+P2.h)+b1*P2.f+b2*P1.f);
	int ans5=m*m*(P1.g+P2.g-P1.f+P2.f)/2;
	return ans1+ans2+ans3-ans4+ans5;
}

bool Ending;
signed main()
{
	int T=read(); while(T--) write(solve(),'\n');
	cerr<<"\nused:"<<(abs(&Ending-&Beginning)/1048576)<<"MB\n";
	return 0;
}
```

---

## 作者：SukiYuri (赞：1)

前置知识：[类欧几里德算法](https://oi-wiki.org/math/number-theory/euclidean/)

推一下我~抄袭 oi-wiki~介绍类欧的的博客：[戳这](https://www.luogu.com.cn/article/02ucewbw)

---

原题链接：[[ABC402G] Sum of Prod of Mod of Linear](https://atcoder.jp/contests/abc402/tasks/abc402_g)

## 题意

求：
$$\sum\limits_{i=0}^{n} \left[(ai+b_1)\bmod c \right]\left[(ai+b_2)\bmod c \right]\tag{1}$$

其中，$a,b_1,b_2<c$，这里我们不妨假设 $b_2\le b_1$。

## 分析

看到这种线性取模、线性向下取整的基本上就是类欧了。

$$\begin{aligned}
(1)&= \sum\limits_{i=0}^{n} \left[(ai+b_1)-c\left\lfloor \frac{ai+b_1}{c} \right\rfloor \right]\left[(ai+b_2)-c\left\lfloor \frac{ai+b_2}{c} \right\rfloor \right]\\
&=\sum\limits_{i=0}^{n} (ai+b_1)(ai+b_2) + c^2\sum\limits_{i=0}^{n} \left\lfloor \frac{ai+b_1}{c}\right\rfloor \left\lfloor\frac{ai+b_2}{c}\right\rfloor\\
&\quad-\sum\limits_{i=0}^{n} c\cdot(ai+b_1)\left\lfloor\frac{ai+b_2}{c}\right\rfloor-\sum\limits_{i=0}^{n} c\cdot(ai+b_2)\left\lfloor\frac{ai+b_1}{c}\right\rfloor
\end{aligned}$$

显然上述式子难做的只有 $\sum\limits_{i=0}^{n} \left\lfloor \frac{ai+b_1}{c}\right\rfloor\left\lfloor\frac{ai+b_2}{c}\right\rfloor$ 一个和式。


根据题设，$b_2\le b_1<c$，所以 $\left(\left\lfloor \frac{ai+b_1}{c}\right\rfloor-\left\lfloor\frac{ai+b_2}{c}\right\rfloor\right)$ 取值仅为 $0$ 或 $1$ 

因此，

$$\sum\limits_{i=0}^{n} \left(\left\lfloor \frac{ai+b_1}{c}\right\rfloor-\left\lfloor\frac{ai+b_2}{c}\right\rfloor\right)\left(\left\lfloor \frac{ai+b_1}{c}\right\rfloor-\left\lfloor\frac{ai+b_2}{c}\right\rfloor-1\right)=0$$

$$\begin{aligned}
\sum\limits_{i=0}^{n} \left\lfloor \frac{ai+b_1}{c}\right\rfloor\left\lfloor\frac{ai+b_2}{c}\right\rfloor=\frac{1}{2}\cdot\left(\left\lfloor\frac{ai+b_1}{c}\right\rfloor^2+\left\lfloor\frac{ai+b_2}{c}\right\rfloor^2-\left\lfloor\frac{ai+b_1}{c}\right\rfloor+\left\lfloor\frac{ai+b_2}{c}\right\rfloor\right)
\end{aligned}$$

整理一下，我们得到： 

$$\begin{aligned}
Ans &= \frac{a^2\cdot n\cdot(n+1)\cdot (2n+1)}{6}+\frac{a\cdot(b_1+b_2)\cdot n \cdot (n+1)}{2}+(n+1)\cdot b_1\cdot b_2\\
&\quad +\frac{c^2}{2}\cdot (h(n,a,b_1,c)+h(n,a,b_2,c)-f(n,a,b_1,c)+f(n,a,b_2,c))\\
&\quad-c\cdot[a\cdot(g(n,a,b_1,c)+g(n,a,b_2,c))+b_1\cdot f(n,a,b_2,c)+b_2\cdot f(n,a,b_1,c)]
\end{aligned}$$

其中：
$$\begin{aligned}
f(n,a,b,c)&=\sum \limits_{i=0}^{n} \left\lfloor \dfrac{ai+b}{c}\right\rfloor\\
g(n,a,b,c)&=\sum \limits_{i=0}^{n} i\left\lfloor \dfrac{ai+b}{c}\right\rfloor\\
h(n,a,b,c)&=\sum \limits_{i=0}^{n} \left\lfloor \dfrac{ai+b}{c}\right\rfloor^2
\end{aligned}$$

于是这道题就结束了。

## 代码

```cpp
#include "iostream"
#include "cmath"
#include "cstdio"
using namespace std;
#define ll __int128
void calc(ll n,ll a,ll b,ll c,ll &f,ll &g,ll &h) {
    f=g=h=0; 
    ll ac=a/c,bc=b/c;
    if(!a) {
        f=bc*(n+1);
        g=bc*n*(n+1)/2;
        h=bc*bc*(n+1);
        return;
    } 
    ll _f,_g,_h;
    if(a>=c||b>=c) {
        f=(n+1)*bc+ac*n*(n+1)/2;
        g=(bc*n*(n+1)+ac*n*(n+1)*(n*2+1)/3)/2;
        h=ac*ac*n*(n+1)*(n*2+1)/6+(n+1)*bc*bc+ac*bc*n*(n+1);
        calc(n,a%c,b%c,c,_f,_g,_h);
        g+=_g; f+=_f;
        h+=ac*_g*2+_f*bc*2+_h;
        return;
    }
    ll m=(a*n+b)/c; calc(m-1,c,c-b-1,a,_f,_g,_h);
    f=n*m-_f;
    g=(n*(n+1)*m-_f-_h)/2;
    h=n*m*(m+1)-f-2*_f-2*_g;
}
int main() {
    ios::sync_with_stdio(0);
    int T; cin>>T;
    while(T--) {
        ll n,a,b1,b2,c,f1,g1,h1,f2,g2,h2;
        int _n,_c,_a,_b1,_b2;
        cin>>_n>>_c>>_a>>_b1>>_b2; --_n;
        n=_n,c=_c,a=_a,b1=_b1,b2=_b2;
        if(b1<b2) swap(b1,b2);
        calc(n,a,b1,c,f1,g1,h1);
        // cout<<f1<<" "<<g1<<" "<<h1<<'\n';
        calc(n,a,b2,c,f2,g2,h2);
        // cout<<f2<<" "<<g2<<" "<<h2<<'\n';
        long long ans=a*a*(n*(n+1)*(2*n+1)/6)+a*(b1+b2)*n*(n+1)/2+(n+1)*b1*b2
               -c*(a*(g1+g2)+b1*f2+b2*f1)+c*c*(h1+h2-f1+f2)/2;
        cout<<ans<<'\n';
    }
}
```
虽然说这道题的答案 $<9\times10^{18}$，但运算过程中稍有不慎就会爆 `long long`，对 C++ 极度不友好。

---

参考：[oi-wiki](https://oi-wiki.org/math/number-theory/euclidean/)，[atcoder](https://atcoder.jp/contests/abc402/editorial/12796)。

---

## 作者：Galois_Field_1048576 (赞：0)

考虑记 $F_i(x) = Ax + B_i$，$R_i(x) = F_i(x) \bmod M$，$Q_i(x) = \left\lfloor\dfrac {F_i(x)}{M}\right\rfloor$。那么
$$
\sum_x R_1(x) R_2(x) = \sum_x (F_1(x) - M Q_1(x)) (F_2(x) - M Q_2(x)).
$$
不难注意到除了
$$
\sum_x Q_1(x) Q_2(x)
$$
一项以外都是
$$
\sum_x Q_1(x), \sum_x x Q_2(x)
$$
的线性组合；所以我们只需要考虑计算
$$
\sum_x Q_1(x) Q_2(x).
$$
而我们考虑使用经典的公式
$$
xy = \dfrac{x^2 + y^2 - (x-y)^2}{2}.
$$
则只需要计算
$$
\sum_x Q_1(x)^2; \sum_x Q_2(x)^2; \sum_x (Q_1(x) - Q_2(x))^2.
$$
前两项是经典的扩展 Euclid 算法，而最后一项不难注意到如下事实：

**命题.** $Q_1(x) - Q_2(x)$ 的值域只可能是如下之一：

* $\{-1, 0\}$；
* $\{0\}$；
* $\{0, +1\}$。

证明是直观且显然的。

因此计算最后一项等价于计算
$$
\left\lvert \sum_x (Q_1(x) - Q_2(x)) \right\rvert,
$$
这又是扩展 Euclid 算法的线性组合。

当时只差 10 min 写完这个做法，流泪啊。

---

## 作者：linjunye (赞：0)

一道很好的数学题。

首先我们发现求余不好做，考虑有如下转化：$a\bmod b=a-b\lfloor\frac{a}{b}\rfloor$，那么开始转化式子：

$$
\sum_{k=0}^{n-1}\{(Ak+B_1)\bmod M\}\{(Ak+B_2)\bmod M\}=\sum_{k=0}^{n-1}\{(Ak+B_1)-M\lfloor\frac{Ak+B_1}{M}\rfloor\}\{(Ak+B_2)-M\lfloor\frac{Ak+B_2}{M}\rfloor\}
$$

然后可以展开，展开后为：

$$
\sum_{k=0}^{n-1}(Ak+B_1)(Ak+B_2)-\sum_{k=0}^{n-1}(Ak+B_2)M\lfloor\frac{Ak+B_1}{M}\rfloor-\sum_{k=0}^{n-1}(Ak+B_1)M\lfloor\frac{Ak+B_2}{M}\rfloor+\sum_{k=0}^{n-1}M^2\lfloor\frac{Ak+B_1}{M}\rfloor\lfloor\frac{Ak+B_2}{M}\rfloor
$$

不要慌！我们一点点计算。

发现现在分成了四个部分，先计算第一部分：$\sum_{k=0}^{n-1}(Ak+B_1)(Ak+B_2)=\sum_{k=0}^{n-1}A^2k^2+Ak(B_1+B_2)+B_1B_2=\sum_{k=0}^{n-1}A^2k^2+\sum_{k=0}^{n-1}Ak(B_1+B_2)+\sum_{k=0}^{n-1}B_1B_2=A^2\sum_{k=0}^{n-1}k^2+A(B_1+B_2)\sum_{k=0}^{n-1}k+nB_1B_2$。这里的计算比较容易，代码也比较好写。

然后就开始难了。

考虑计算第二、三部分（这里省去前面的负号）：$\sum_{k=0}^{n-1}(Ak+B_2)M\lfloor\frac{Ak+B_1}{M}\rfloor+\sum_{k=0}^{n-1}(Ak+B_1)M\lfloor\frac{Ak+B_2}{M}\rfloor=\sum_{k=0}^{n-1}AkM\lfloor\frac{Ak+B_1}{M}\rfloor+\sum_{k=0}^{n-1}B_2M\lfloor\frac{Ak+B_1}{M}\rfloor+\sum_{k=0}^{n-1}AkM\lfloor\frac{Ak+B_2}{M}\rfloor+\sum_{k=0}^{n-1}B_1M\lfloor\frac{Ak+B_2}{M}\rfloor=AM\sum_{k=0}^{n-1}k\lfloor\frac{Ak+B_1}{M}\rfloor+MB_2\sum_{k=0}^{n-1}\lfloor\frac{Ak+B_1}{M}\rfloor+AM\sum_{k=0}^{n-1}k\lfloor\frac{Ak+B_2}{M}\rfloor+MB_1\sum_{k=0}^{n-1}\lfloor\frac{Ak+B_2}{M}\rfloor$。

这里放一个链接：[P5170](https://www.luogu.com.cn/problem/P5170)。这是类欧的模板题，请先完成这道题，不然后面的内容可能会理解起来有些困难。

我们设 $f(n,a,b,c)=\sum_{i=0}^{n}\lfloor\frac{ai+b}{c}\rfloor$，$g(n,a,b,c)=\sum_{i=0}^{n}i\lfloor\frac{ai+b}{c}\rfloor$，$h(n,a,b,c)=\sum_{i=0}^{n}\lfloor\frac{ai+b}{c}\rfloor^2$。

那么原式这一个求和式变为：$AM\times g(n-1,A,B_1,M)+MB_2\times f(n-1,A,B_1,M)+AM\times g(n-1,A,B_2,M)+MB_1\times f(n-1,A,B_2,M)$，因为三个函数都能在 $O(\log n)$ 的时间求出，所以推到这里就可以了。三个函数的推导和求值这里不阐述了。

考虑最后一个部分的求和。这里是最妙的地方，日文题解的思考真的很棒。

首先不妨 $B_1\le B_2$，然后我们设 $\lfloor\frac{Ak+B_1}{M}\rfloor=x$，$\lfloor\frac{Ak+B_2}{M}\rfloor=y$，则有式子 $0\le y-x\le 1$。

这里有证明：

因为分子中相差 $B_2-B_1$，且我们假设了 $B_1\le B_2$，那么 $0\le B_2-B_1\le M$，则 $y$ 比 $x$ 多的贡献不会多余 $1$，所以 $0\le y-x\le 1$，证毕。其实还是有点跳跃，可以自行慢慢思考。

则 $(y-x)(y-x-1)=0$，因为 $y-x$ 是整数，所以这一点好证明。这是我觉得此题最妙的地方。

然后做一些简单的展开，这里就不操作了，最终能得到 $(y-x)^2=y-x$。

然后发现第四部分其实大部分就是在求 $xy$，考虑如何计算：$xy=-\frac{(y-x)^2-x^2-y^2}{2}=-\frac{y-x-x^2-y^2}{2}=\frac{x^2+y^2+x-y}{2}$。

这时候带回去，第四部分为：$\frac{M^2\sum_{i=0}^{n-1}\lfloor\frac{Ak+B_1}{M}\rfloor^2+\lfloor\frac{Ak+B_2}{M}\rfloor^2+\lfloor\frac{Ak+B_1}{M}\rfloor-\lfloor\frac{Ak+B_2}{M}\rfloor}{2}=\frac{M^2\sum_{i=0}^{n-1}\lfloor\frac{Ak+B_1}{M}\rfloor^2+\sum_{i=0}^{n-1}\lfloor\frac{Ak+B_2}{M}\rfloor^2+\sum_{i=0}^{n-1}\lfloor\frac{Ak+B_1}{M}\rfloor-\sum_{i=0}^{n-1}\lfloor\frac{Ak+B_2}{M}\rfloor}{2}=M^2\times\frac{h(n-1,A,B_1,M)+h(n-1,A,B_2,M)+f(n-1,A,B_1,M)-f(n-1,A,B_2,M)}{2}$。

最后拼接到一起，原式就是：

$$
A^2\sum_{k=0}^{n-1}k^2+A(B_1+B_2)\sum_{k=0}^{n-1}k+nB_1B_2-AM\times g(n-1,A,B_1,M)-MB_2\times f(n-1,A,B_1,M)-AM\times g(n-1,A,B_2,M)-MB_1\times f(n-1,A,B_2,M)+\frac{1}{2}M^2\times h(n-1,A,B_1,M)+\frac{1}{2}M^2\times h(n-1,A,B_2,M)+\frac{1}{2}M^2\times+f(n-1,A,B_1,M)-\frac{1}{2}M^2\times f(n-1,A,B_2,M)
$$

然后，我们只需要处理类欧的三个函数（其实就是把模板稍作一改），然后按此计算（还要处理一些求和公式），就做好了！

总算，我们做完了这道黑题。

代码：

```cpp
//https://oi-wiki.org/math/number-theory/euclidean/
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#define int __int128 //不开__int128容易出现爆long long
using namespace std;
using namespace std;
struct EL{
	int f,g,h;
	EL(){f=g=h=0;}
};
EL cal(int a,int b,int c,int n){//这里是类欧模板，具体实现不再阐述
	EL d;
	int m=(a*n+b)/c;
	if(a==0){
		d.f=(n+1)*(b/c);
		d.g=(n+1)*n/2*(b/c); 
		d.h=(n+1)*(b/c)*(b/c);
		return d;
	}
	if(a>=c||b>=c){
		d.f=(n*(n+1)/2*(a/c)+(n+1)*(b/c));
		d.g=(n*(n+1)*(2*n+1)/6*(a/c)+n*(n+1)/2*(b/c));
		d.h=(n*(n+1)*(2*n+1)/6*(a/c)*(a/c)+(n+1)*(b/c)*(b/c)+n*(n+1)*(a/c)*(b/c));
		EL e=cal(a%c,b%c,c,n);
		d.f=(d.f+e.f);
		d.g=(d.g+e.g);
		d.h=(d.h+(e.h+2*(b/c)*e.f+2*(a/c)*e.g));
		return d;
	}
	EL e=cal(c,c-b-1,a,m-1);
	d.f=n*m-e.f;
	d.g=(n*m*(n+1)-e.h-e.f)/2;
	d.h=n*m*(m+1)-2*e.g-2*e.f-d.f;
	return d;
}
int T;
int n,m,A,B1,B2;
int read(){//因为输入都是long long，但我们要转成__int128（计算方便&偷懒），故有此函数
	long long _;
	cin>>_;
	return (int)_;
}
int sum_pf(int n){//0^2+1^2+...+n^2
	return n*(n+1)*(2*n+1)/6;
}
int sum(int n){//0+1+2+...+n
	return n*(n+1)/2;
}
signed mian(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	T=read();
	while(T--){
		n=read();
		m=read();
		A=read();
		B1=read();B2=read();
		if(B1>B2)swap(B1,B2);//这里的不妨B1<=B2
		//这里我将三个函数打包在一起，a.f,a.g,a.h就是f,g,h函数
		EL res1=cal(A,B1,m,n-1);
		EL res2=cal(A,B2,m,n-1);
		int ans1=A*A*sum_pf(n-1)+A*(B1+B2)*sum(n-1)+n*B1*B2;//第一部分和
		int ans2=m*A*res1.g+m*B2*res1.f+m*A*res2.g+m*B1*res2.f;//第二、三部分和
		int ans3=(res1.h+res2.h+res1.f-res2.f)*m*m/2;//第四部分和
		int ans=ans1-ans2+ans3;//计算最终答案
		cout<<(long long)ans<<"\n";//答案不会超过 long long（感兴趣可以自行观察）所以强转 long long 便于输出
	}
	return 0;
}
/*
代码可能有点丑qwq，请谨慎观看
*/
```

---

