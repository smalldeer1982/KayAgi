# Alice, Bob, Oranges and Apples

## 题目描述

Alice and Bob decided to eat some fruit. In the kitchen they found a large bag of oranges and apples. Alice immediately took an orange for herself, Bob took an apple. To make the process of sharing the remaining fruit more fun, the friends decided to play a game. They put multiple cards and on each one they wrote a letter, either 'A', or the letter 'B'. Then they began to remove the cards one by one from left to right, every time they removed a card with the letter 'A', Alice gave Bob all the fruits she had at that moment and took out of the bag as many apples and as many oranges as she had before. Thus the number of oranges and apples Alice had, did not change. If the card had written letter 'B', then Bob did the same, that is, he gave Alice all the fruit that he had, and took from the bag the same set of fruit. After the last card way removed, all the fruit in the bag were over.

You know how many oranges and apples was in the bag at first. Your task is to find any sequence of cards that Alice and Bob could have played with.

## 说明/提示

In the first sample, if the row contained three cards with letter 'B', then Bob should give one apple to Alice three times. So, in the end of the game Alice has one orange and three apples, and Bob has one apple, in total it is one orange and four apples.

In second sample, there is no answer since one card is not enough for game to finish, and two cards will produce at least three apples or three oranges.

In the third sample, cards contain letters 'AB', so after removing the first card Bob has one orange and one apple, and after removal of second card Alice has two oranges and one apple. So, in total it is three oranges and two apples.

## 样例 #1

### 输入

```
1 4
```

### 输出

```
3B
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
1A1B
```

# 题解

## 作者：樱雪喵 (赞：5)

## Description

一开始果篮里有 $x$ 个橘子，$y$ 个苹果。游戏开始前，Alice 从果篮中拿 $1$ 个橘子，Bob 则拿 $1$ 个苹果。  
对于一个由字符 `A` 和 `B` 组成的序列，每个字符代表一次操作。`A` 操作表示 Alice 从果篮里拿与自己手里等量的水果送给 Bob（两种分别相等），`B` 操作则相反。  
请构造一个字符串序列表示操作，使果篮在从左到右依次执行完所有操作后恰好被拿空。

$x,y\le 10^{18}$。

## Solution

发现这个操作长得像辗转相除反过来？写了一发过了。  
~~完结撒花~~

但是仔细想想发现你修改和求和的根本不是一个维度的东西，完全不能说明这样做为什么是对的，我们要证明这个做法的正确性。

设 $a_0,a_1$ 分别为 Alice 的橙子、苹果数，Bob 同理。考虑构造状态矩阵 $\begin{bmatrix}a_0 & b_0\\a_1 & b_1 \end{bmatrix}$，发现初始状态恰好为单位矩阵，即 $I=\begin{bmatrix}1 & 0\\0 & 1 \end{bmatrix}$。  
接下来用矩乘来刻画操作：`A` 操作为矩阵 $A=\begin{bmatrix}1 & 1\\0 & 1 \end{bmatrix}$，`B` 操作为矩阵 $B=\begin{bmatrix}1 & 0\\1 & 1 \end{bmatrix}$。  
最后刻画答案，设 $P$ 为当前矩阵，定义函数 $f(P)=\dfrac{a_0+b_0}{a_1+b_1}$，则答案矩阵满足 $f(ans)=\dfrac{x}{y}$。

那么我们要构造一个矩乘序列，令 $I$ 依次右乘若干个 $A,B$，最后满足上述条件。当然因为 $I$ 是单位矩阵，可以忽略不计。  
考虑矩乘操作对原数组的影响，看起来不好求，但我们可以把操作序列倒过来：  
设若干 $A,B$ 的乘积为矩阵 $P$，第一次操作是 $A$。那么我们把 $P$ 拆成 $AP'$，设 $P'=\begin{bmatrix}a & b\\c& d \end{bmatrix}$。

大力推式子：

$$P=AP'=\begin{bmatrix}1 & 1\\0 & 1 \end{bmatrix}\begin{bmatrix}a & b\\c& d \end{bmatrix}=\begin{bmatrix}a+c & b+d\\c & d \end{bmatrix}$$

$$f(P)=f(AP')=\frac{a+b+c+d}{c+d}$$

$$ f(P')=\frac{a+b}{c+d}$$

令 $a+b=n,c+d=m$。那么有：

$$f(P)=\frac{n}{m}$$

$$

f(P')=\begin{cases}\frac{n-m}{m} & n>m,\text{first opt}=A\\\frac{n}{m-n}&n<m,\text{first opt}=B\end{cases}
$$

这次是真的更相减损了。

```cpp
#define int long long
int a,b;
void solve(int a,int b,int op)
{
    if(!a||!b) return;
    if(a<b) printf("%lld%c",a==1?b/a-1:b/a,op?'A':'B'),solve(a,b%a,op^1);
    else printf("%lld%c",b==1?a/b-1:a/b,op?'A':'B'),solve(a%b,b,op^1);
}
signed main()
{
    a=read(),b=read();
    if(__gcd(a,b)>1) printf("Impossible\n");
    else if(a<b) solve(b,a,0),printf("\n");
    else solve(a,b,1),printf("\n");
    return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：5)


### 题意
- 对于一个既约分数 $\dfrac{p}q$，求该分数在 Stern-Brocot Tree 上的位置。（用 $\texttt{A,B}$ 表示从根节点往右子树/左子树走一步）

### 做法


特别推荐这个 [B 站的视频](https://www.bilibili.com/video/BV1PE411W7Ze)。

这里用 $R,L$ 代替题目中的 $A,B$。

最暴力的做法是记录一下代表当前子树范围的区间端点 $\dfrac{L_m}{L_n},\dfrac{R_m}{R_n}$。

然后找到中点 $\dfrac{L_m+R_m}{L_n+R_n}$，判断其与 $\dfrac{p}q$ 的大小关系，再决定去左边/右边。

更优做法：我们考虑去 **寻找拐点**。

[![TAWuwt.png](https://s4.ax1x.com/2021/12/18/TAWuwt.png)](https://imgtu.com/i/TAWuwt)

上图 $\dfrac{1}{2}$ 就是拐点。

如果往左走 $k$ 步，则 $\dfrac{L_m}{L_n}<\dfrac{p}q\le\dfrac{kL_m+R_m}{kL_n+R_n}$。

由左边得：$pL_n-qL_m>0$。

由右边得：$pkL_n+pR_n\le{}qkL_m+qR_m$，即 $k(pL_n-qL_m)\le{}qR_m-pR_n$。

所以 $k\le\left\lfloor\dfrac{qR_m-pR_n}{pL_n-qL_m}\right\rfloor$。

所以就搞定了！

接下来要证明这样找拐点的复杂度为什么是 $O(\log{n})$ 的？

观察这个区间 $\left({\dfrac{L_m}{L_n},\dfrac{R_m}{R_n}}\right)$。尝试用一个 $2\times2$ 的矩阵 $\begin{bmatrix}L_m&R_m\\L_n&R_n\end{bmatrix}$ 去表示。

此时 $\dfrac11$ 就是 $\begin{bmatrix}0&1\\1&0\end{bmatrix}$，而单位矩阵是 $\begin{bmatrix}1&0\\0&1\end{bmatrix}$。所以很简单，我们把矩阵变一变，变成$\begin{bmatrix}L_n&R_n\\L_m&R_m\end{bmatrix}$。

把第二层的矩阵也写出来，分别是：$\begin{bmatrix}1&1\\0&1\end{bmatrix}$ 和 $\begin{bmatrix}1&0\\1&1\end{bmatrix}$。

这个时候，你会发现很神奇的一件事情发生了：

$\begin{bmatrix}L_n&L_n+R_n\\L_m&L_m+R_m\end{bmatrix}=\begin{bmatrix}L_n&R_n\\L_m&R_m\end{bmatrix}\begin{bmatrix}1&1\\0&1\end{bmatrix}$

$\begin{bmatrix}L_n+R_n&R_n\\L_m+R_m&R_m\end{bmatrix}=\begin{bmatrix}L_n&R_n\\L_m&R_n\end{bmatrix}\begin{bmatrix}1&0\\1&1\end{bmatrix}$

令 $f(S)$ 表示矩阵 $S$ 对应的分数，$L$ 表示矩阵 $\begin{bmatrix}1&1\\0&1\end{bmatrix}$，$R$ 表示矩阵 $\begin{bmatrix}1&0\\1&1\end{bmatrix}$。

那么

 $\begin{aligned}f\left(LRR\right)&=f\left(\begin{bmatrix}1&1\\0&1\end{bmatrix}\begin{bmatrix}1&0\\1&1\end{bmatrix}\begin{bmatrix}1&0\\1&1\end{bmatrix}\right)\\&=f\left(\begin{bmatrix}3&1\\2&1\end{bmatrix}\right)=\dfrac34 \end{aligned}$

向右走相等于乘上一个 $R$，向左走相等于乘上一个 $L$。

现在要一步步回到那个 $\begin{bmatrix}1&0\\0&1\end{bmatrix}$。

对于矩阵 $S=\begin{bmatrix}L_n&R_n\\L_m&R_m\end{bmatrix}$，$LS=\begin{bmatrix}L_n+L_m&R_n+R_m\\L_m&R_m\end{bmatrix}$。

$f(S)=\dfrac{L_m+R_m}{L_n+R_n},f(LS)=\dfrac{L_m+R_m}{L_n+R_n+L_m+R_m}$。

设 $n=L_n+R_n,m=L_m+R_m$，则 $f(S)=\dfrac{m}n,f(LS)=\dfrac{m}{m+n}$。

考虑分数 $\dfrac{m'}{n'}(m'<n')$，这一步是 $L$ 的话，相等于这一步前是 $\dfrac{m'}{n'-m'}$。

对于 $\dfrac{m'}{n'}(m'>n')$ 这一步是 $R$，则这一步前是 $\dfrac{m'-n'}{n'}$。

而 $\dfrac{m'}{n'}\ge0$，所以有：

$$\begin{cases}\dfrac{m}n=f(LS)\Longleftrightarrow\dfrac{m}{n-m}=f(S)&m<n\\\dfrac{m}n=f(RS)\Longleftrightarrow\dfrac{m-n}{n}=f(S)&m>n \end{cases}$$

这是什么？这不就是更相损减吗？辗转相除一下，可以得知一共有 $O(\log n)$ 个拐点。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
inline long long read()
{
	long long x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
long long gcd(long long x,long long y)
{
	return !y?x:gcd(y,x%y);
}
void work(long long x,long long y,bool k)
{
	if(!y)	return ;
	printf("%lld",(y!=1)?x/y:x-1);putchar(k?'A':'B');
	work(y,x%y,!k);
}
int main()
{
	n=read(),m=read();
	if(gcd(n,m)!=1)	return puts("Impossible"),0;
	else	work(max(n,m),min(n,m),(n>m?1:0));
	return 0;
}

```


---

## 作者：MyukiyoMekya (赞：2)

一开始完全不能理解网上题解和题解区的辗转相除法为啥是对的。

看完混凝土里 SBT 相关内容（4.5）才大概会了这题。。。建议没看过的去看一下。

设 $n$ 为 Bob 的苹果数，$m$ 为 Bob 的橙子数，$n'$ 为 Alice 的苹果数，$m'$ 为 Alice 的橙子数。

我们设当前状态 $S$ 的矩阵为 $M(S)=\begin{bmatrix} n&n' \\ m&m'\end{bmatrix}$ ，初始状态矩阵为$I=\begin{bmatrix} 1&0 \\ 0&1 \end{bmatrix}$。

设 $f(S)=\dfrac {m+m'}{n+n'}$，

操作 $A$ 可以表示为矩阵 $A=\begin{bmatrix} 1&0 \\ 1&1\end{bmatrix}$，操作 $B$ 可以表示为矩阵 $B=\begin{bmatrix} 1&1 \\ 0&1\end{bmatrix}$。

有 $SA=\begin{bmatrix} n+n'&n' \\ m+m'&m'\end{bmatrix}$ ，有 $SB=\begin{bmatrix} n&n'+n \\ m&m'+m\end{bmatrix}$ ，

我们的目标是让 $I$ 右乘上一堆操作序列矩阵（ $A,B$ ）使得最终结果为 $U$ ，$f(U)=\dfrac xy$。

由 SBT 相关知识可得，（这里不证了）

只有 $(x,y)=1$ 时有唯一的操作序列与其对应，$(x,y)\ne 1$ 时不存在操作序列能使得 $I$ 变为 $U$。

以样例 3 为例 $IAB=\begin{bmatrix} 1&1 \\ 1&2\end{bmatrix}$，$f(SAB)=\dfrac 32$。

归纳可得 $M(S)=S$。显然任意一个 $S$  都有 $\dfrac mn<\dfrac {m+m'}{n+n'}<\dfrac {m'}{n'}$。（书上都有证明）

所以我们可以写出一份伪代码：
$$
S\leftarrow I \\
\textbf{while} \ x/y \ne f(S) \textbf{do} \\
\textbf{if} \ x/y < f(S) \ \textbf{then} \ (\texttt{output}(B),S\leftarrow SB) \\ 
\textbf{else} \ (\texttt{output}(A),S\leftarrow SA)
$$
但这个复杂度不对。

考虑倒推，我们设 $E$ 为由一堆 $A,B$ 组成的操作序列，有 $IE=U$，也就是 $E=U$。

考虑把 $E$ 一个一个拆开：

假设 $E=AE'$ ，那么我们考虑 $f(E)=\dfrac xy$ 所代表的 $x,y$ 到 $f(E')=\dfrac {x'}{y'}$ 会变成啥：

$E'=\begin{bmatrix} n&n' \\ m&m'\end{bmatrix},AE'=\begin{bmatrix} n&n' \\ m+n&m'+m'\end{bmatrix}$，

也就是说把 $E$ 前面的一个 $A$ 去掉， $\dfrac xy$ 变成了 $\dfrac {x-y}{y}$。

同理，设 $E$ 最前面是 $B$ ，我们可以得到 $BE'=\begin{bmatrix} n+m&n'+m' \\ m&m'\end{bmatrix}$，$\dfrac xy$ 变成了 $\dfrac {x}{y-x}$。

由 SBT 相关可得，这个 $\dfrac xy$ 一定是非负的，所以我们可以推出一个东西：

$\left\{
\begin{aligned}
\dfrac xy = f(AE) &  &\leftrightarrow & & \dfrac {x-y}y = f(E) &  & x>y; \\
\dfrac xy = f(BE) &  &\leftrightarrow & & \dfrac x{x-y} = f(E) &  & x<y.
\end{aligned}
\right.$

仔细一看，这就是更相减损术。改一改就成辗转相除了。代码就不给了。

---

## 作者：wenge (赞：2)

$A$操作和$B$操作本质上就是进行了辗转相除法的逆操作。

操作的次数就是$x/y$或者$y/x$。

可以使用辗转相除法倒推回去。

注意最后除1要特判。

```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <iomanip>
using namespace std;
typedef long long ll;
ll n,m;
ll gcd(ll x,ll y){
	if(y==0)return x;
	return gcd(y,x%y);
}
void solve(ll x,ll y,bool z){
	if(y==0)return;
	cout<<((y!=1)?x/y:x/y-1)<<(z?"A":"B");
	solve(y,x%y,!z);
}
int main(){
	cin>>n>>m;
	if(gcd(n,m)!=1){
		cout<<"Impossible";
		return 0;
	}
	else solve(max(n,m),min(n,m),(n>m?1:0));
    return 0;
}
```


---

