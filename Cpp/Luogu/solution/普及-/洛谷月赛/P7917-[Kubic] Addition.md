# [Kubic] Addition

## 题目背景

建议先看 B 题题目背景。

## 题目描述

有一个初始长度为 $n$ 的序列 $a$。你需要进行 $n-1$ 次操作。每一次操作先在当前序列中选出两个相邻的数 $x,y$ 并删除（原序列中 $x$ 在 $y$ 左边），再往原位置插入一个 $x+y$ 或一个 $x-y$。$n-1$ 次操作之后最终只会剩下恰好一个数，求这个剩下的数的最大值。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5,|a_i|\le 10^9$。

||分值|$n$|$\vert a_i\vert$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$10$|$\le 2$|无特殊限制|无|
|$\operatorname{Subtask}2$|$20$|$\le 100$|无特殊限制|无|
|$\operatorname{Subtask}3$|$5$|无特殊限制|无特殊限制|$a_i\ge 0$|
|$\operatorname{Subtask}4$|$30$|无特殊限制|$\le 1$|无|
|$\operatorname{Subtask}5$|$35$|无特殊限制|无特殊限制|无|

### 样例解释

一种操作过程如下：

`-1 1 1 -1 1`

`-1 1 1 -2`

`-1 1 3`

`-1 4`

`3`

可以证明没有更优的方案。

## 样例 #1

### 输入

```
5
-1 1 1 -1 1```

### 输出

```
3```

# 题解

## 作者：银杉水杉秃杉 (赞：4)

由题可得，要使得最终答案最大，就得使数列中每一个负数变成其绝对值加入答案中，也就是减去这个负数。假如 $a_1$ 是负数，但由于 $a_1$ 前面没有数可以减去它，所以 $a_1$ 保持不变；而 $a_2 \sim a_n$ 中前面均有数可以减去它使其变为绝对值。所以最终的答案为$ans=a_1+\vert a_2\vert+\vert a_3\vert+\cdots+\vert a_n\vert$。

```cpp
#include <bits/stdc++.h>
#define int long long//记得开 long long
using namespace std;
const int N = 1e5 + 10;
int n, x, ans;
signed main()
{
    scanf("%lld%lld", &n, &x);
    ans = x;
    for (int i = 2; i <= n; i++)
    {
        scanf("%lld", &x);
        ans += x < 0 ? -x : x;
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：mzyc_jx (赞：3)

[Addition](https://www.luogu.com.cn/problem/P7917)

前言：

这是本蒟蒻AC的第二道月赛题，这道题是真的简单，~~我骗分骗着骗着就AC了。~~

### 思路：

1. 当 $y\geq 0$ 时，$x+y\geq x-y$ 
2. 当 $y\leq 0$ 时，$x+y\leq x-y$

综上，可以发现 $x+|y|$ 最大。

所以贪心策略为：加每个数的绝对值（第一个数不行）。

### 注意：

1. 第一个数不能加他的绝对值！
2. sum 记得开 long long !

### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//比赛时用来加速
	int n,b,c;
	cin>>n;
	cin>>a[1];//第一个数要单独判断（可能为负）
	long long sum=a[1];
	for(int i=2;i<=n;i++)
	{
		cin>>a[i];
		sum+=abs(a[i]);//累加绝对值
	}
	cout<<sum;
	return 0;
}
```

### 十年OI一场空，不开long long见祖宗！

---

## 作者：InterN_NOT_FOUND (赞：3)

这道题还是挺简单的，月赛的时候一次就 AC 了。

来讲一下思路。

题目的样例说明 说明负数也可以出现在过程中，而且绝对值越大用另一个数减去它所得的值就越大，所以判断的时候要判断 $x+y$ 和 $x-y$ 的绝对值。

$x$ 和 $y$ 是相邻的，说明可以用一个循环跑完全程。

然而，你如果用了 `for(int i=1;i<=n;i++)` 就会 WA 。

来看会有哪些问题。

举个实例，$x=-1,y=2$ ,如果你用了刚才那个循环顺序，程序会认为 $|-1+2|<|-1-2|$ 。

所以你最后得到的值是-3。 （$x-y$ 的值）。

光是这样看不出问题，如果把它放进数列里呢？

比如这个数列:$ -1$ $2$ $3$ 。

你的程序最后得出的结果会是$-6$ 。因为$-1-2=-3,-3-3=-6$ 。程序认为这样得到的绝对值最大。

怎么解决呢？倒过来循环不就行了嘛。

$3+2=5,5-(-1)=6$

但是，有时候最后会得出一个绝对值很大的负数，所以在最后一次循环加个特判，要**数值**（**而不是绝对值**）最大的那个。

放个 AC 程序：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline bool isnum(char ch){return ch>='0'&&ch<='9';}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isnum(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isnum(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void out(int x,char ch){
    if(x<0){putchar('-');x=-x;}
    if(x>9)out(x/10,'/');
    putchar(x%10+'0');
    if(ch=='l')printf("\n");
    if(ch=='s')printf(" ");
}

inline int f(int x){return x>0?x:-x;}//手写绝对值
int n=read(),a[114514];
signed main()
{
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i>=2;i--){//i最小值取2避免下标越界
		int x=a[i-1],y=a[i];
		if(i!=2){//不是最后一次循环
			if(f(x-y)>f(x+y))a[i-1]=x-y;//因为不能把绝对值赋给a[i-1],所以用if不用max
			else a[i-1]=x+y;
		}
		else {//最后一次循环，要数值最大的
			a[i-1]=max(x-y,x+y);
		}
	}
	out(a[1],'l');//第一个数就是最终答案了
	return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
你有一个长度为 $n$ 的序列 $a$。你可以执行 $n-1$ 次操作，每次操作中你可以选择一个位置 $i$，并删除 $a_i$ 和 $a_{i+1}$，再在原位置上面插入 $a_i+a_{i+1}$ 或者 $a_i-a_{i+1}$。求出恰好剩下的一个数的最大值。

**数据范围：$1\leqslant n\leqslant 10^5$，$|a_i|\leqslant 10^9$。** 

## Solution

很标准的一道良心送分 A 题。

不难想到，由于要插入的值是左边的那个数的值加上或减去右边那个数的值，所以，我们将 $a_2,\dots,a_n$ 这些数全部往 $a_1$ 里面累积进去，具体地，如果 $a_i(i\geqslant 2)$ 是负数，就往 $a_1$  加进去其相反数，否则就直接加进 $a_1$。

上面这句话归结成一个式子就是 $a_1+\sum\limits_{i=2}^n |a_i|$。
## Code
```cpp
namespace Solution {
	int n, x;
	ll ans;
	
	iv Main() {
		read(n);
		F(int, i, 1, n) read(x), ans += (i == 1 ? x : abs(x));
		write(ans);
		return;
	}
}
``` 

---

## 作者：Ginger_he (赞：1)

# 题解
从左到右依次进行如下操作：若当前数为正数，答案加上当前数；否则减去当前数。  
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
long long f[2]; 
int main()
{
	scanf("%d%lld",&n,&f[1]);
	for(int i=2;i<=n;i++,x^=1)
	{
		scanf("%lld",&f[x]);
		f[x]=f[x]<0?f[x^1]-f[x]:f[x^1]+f[x];
	}
	printf("%lld\n",f[x^1]);
	return 0;
}
```



---

## 作者：HarunluoON (赞：1)

这道题，我的思路是贪心，从左往右进行操作，“能大则大”，最后得出答案。

对于样例，所需要进行的操作如下：

1. 对第 $1$ 个数 $-1$ 与第 $2$ 个数 $1$ 进行操作，$-1+1>-1-1$，所以序列变成：`0 1 -1 1`。
2. 对 $0$ 和 $1$ 进行操作，$0+1>0-1$，所以序列变成：`1 -1 1`。
3. 对 $1$ 和 $-1$ 进行操作，$1+(-1)<1-(-1)$，所以序列变成：`2 1`。
4. $2+1=3$，所以输出 $3$。

即答案为第一个数加上后面每个正数，减去后面每个负数。

那如何证明这个方案可以得到最优解呢？在样例解释中给了我们一个保证最优的方案：

$$3=\color{red}-1\color{black}+\{\color{orange}1\color{black}+[\color{green}1\color{black}-(\color{blue}-1\color{black}-\color{fuchsia}1\color{black})]\}$$

去括号，得：

$$3=\color{red}-1\color{black}+\color{orange}1\color{black}+\color{green}1\color{black}\color{black}-\color{blue}(-1)\color{black}+\color{fuchsia}1$$

也就是：

$$3=\{[(\color{red}-1\color{black}+\color{orange}1\color{black})+\color{green}1\color{black}]-\color{blue}(-1)\color{black}\}+\color{fuchsia}1$$

所以这道题可以通过贪心得到全局最优解，贪心的顺序与结果无关。

代码实现：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	int n,a;
	long long ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(i==1)
		ans=a;
		else
		ans+=abs(a);
	}
	printf("%ld",ans);
	return 0;
}
```

---

## 作者：Jerrlee✅ (赞：1)

## 题意
有一个初始长度为 $n$ 的序列 $a$。你需要进行 $n-1$ 次操作。每一次操作先在当前序列中选出两个相邻的数 $x,y$ 并删除，再往原位置插入一个 $x+y$ 或 $x-y$。$n-1$ 次操作之后最终只会剩下恰好一个数，求这个剩下的数的最大值。
## 思路
$\texttt{subtask}$ $1$

既然 $n \leq 2$，那么就很好分类了：

- 只有一个数，直接输出；

- 有两个数，输出 $max(a+b,a-b)$（设两个数为 $a,b$）。

### 代码
```cpp
if(n==1){cin>>a;cout<<a;}
else if(n==2){cin>>a>>b;cout<<max(a+b,a-b);}
```
[记录](https://www.luogu.com.cn/record/61300389)

$\texttt{subtask}$ $2$

留给一些较慢的暴力？

$\texttt{subtask}$ $3$

$a_i \geq 0$，读入一个数直接加即可。

### 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    long long n,a,b,sum=0;
    cin>>n;
    if(n==1){cin>>a;cout<<a;}
    else if(n==2){cin>>a>>b;cout<<max(a+b,a-b);}
    else{
        int a[n+1];
        for(int i=1;i<=n;i++){cin>>a[i];sum+=a[i];}
        cout<<sum;
    } //把 1 和 3 结合了
}
```
[记录](https://www.luogu.com.cn/record/61301021)

$\texttt{subtask}$ $4$

留给那些不开 `long long` 的，[$40$ 分](https://www.luogu.com.cn/record/61399157)。

$100$ 分：

其实就是个暴力。

如果读入的 $a_i \geq 0$ 加上去，否则减，存到 $\texttt{sum}$ 里。

切记 $\texttt{sum}$ 开始初始为 $a_1$！否则 [$45$ 分](https://www.luogu.com.cn/record/61301518)。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    long long n,a,b,sum=0;
    cin>>n;
    if(n==1){cin>>a;cout<<a;}
    else if(n==2){cin>>a>>b;cout<<max(a+b,a-b);}
    else{
        int a[n+1];
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(i==1) sum=a[i];
            else if(a[i]>0) sum+=a[i];
            else sum-=a[i];
        }
        cout<<sum;
    }
}
```
[AC记录](https://www.luogu.com.cn/record/61301987)

---

## 作者：Veranda (赞：0)

贪心签到题

---

可以对 $x$ 和 $y$ 进行分类讨论。

首先对被减数 $y$ 进行讨论，在 $x$ 一定的情况下：

- 当 $y < 0$ 时， $x - y > x + y$ ；

- 当 $y > 0$ 时， $x - y < x + y$ ；

- 当 $y = 0$ 时， $x - y = x + y$ ；

综上，当 $y ∈ R$ 时，取 $x + |y|$ 为部分最优
。

其次对 $x$ 进行讨论：

先假设数列形如： $x_1$ $,$ $x_2$ $,$ $x_3$ $,$ $...$ , $x_{n-1}$ $,$ $y$

- 当 $x_i < 0$ 时，令 $x_{i-1} - x_i = x_{i-1} + |x_i|$ 此时等效于 $x_i > 0$
；
- 当 $x_i > 0$ 时， $x+|y|$ 最大 ；

- 当 $x_i = 0$ 时， 无所谓 ；

而当 $ i = 1$ 时 $x_{i - 1}$ 不存在，故第一个数最大是其本身。

由此证明 $Max = a_1 + |a_2| + |a_3| + ... +|a_n|$

贪心成立。

由于题解区中大部分题解对贪心的证明并不严谨，只讨论了 $y$ 的情况，故发本篇题解给出严谨证明。

简简单单的代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	long long n,ans = 0; //注意要开longlong 
	cin >> n >> ans;
	for(int i = 2;i <= n;i ++){
		long long a;
		cin >> a;
		ans += abs(a);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：int08 (赞：0)

# 前言
还是讲详细点好啊……
# Solution
光看题的话，~~像我一样的蒟蒻~~看不出什么名堂来。
当然根据题目规定的操作方法，我们很容易把这道题转义。

以样例数列 $-1,1,1,-1,1$ 为例。
### 第 $1$ 次操作

将第 $4$ 项，第 $5$ 项和为 $-2$：

$-1,1,1,-2$ 也就是 $-1,1,1,(-1-1)$。

### 第 $2$ 次操作

将第 $3$ 项，第 $4$ 项和为 $3$：

$-1,1,3$ 也就是 $-1,1,(1-(-1-1))$。

~~以下省略。~~

从以上的合并我们可以得出，原问题就等价于：给定一个由 $n$ 个数组成的数列，在每个数之间加上加号，减号**以及括号**，组成一个合法的表达式，求表达式的最大值。

样例数列 $-1,1,1,-1,1$ 的最大值就是 $-1+1+1-(-1-1)=3$ 。

但是我们突然想起来有加法结合律 $a+(b+c)=a+b+c$ ，减法的性质 $a-(b+c)=a-b-c$ 。

这样可以把这个表达式的所有括号去掉，而表达式仍然由原数列，加减号组成。

原问题就又等价于：给定一个由 $n$ 个数组成的数列，在每个数之间加上加号，减号，组成一个合法的表达式，求表达式的最大值。

这个时候，因为没有括号，我们就可以按照正常的计算顺序，从左到右依次计算了。

## 于是就回到了各大题解的熟悉配方
考虑当前的数 $a$ 和数列的下一个数 $b$ ：

如果 $b>0$ ，最大值为 $a+b$ ；

如果 $b<0$ ，最大值为 $a-b$ 。

总结成一句话：**加绝对值！**

注意在数列的第 $1$ 个数前面是没有符号的，那个位置就不能加绝对值而要保持原数，后面的所有位置，都可以加其绝对值。
#  AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,i,ans;
int main()
{
	scanf("%lld",&a);
	scanf("%lld",&ans);  //此处就是对不能加绝对值的第一个数的特殊处理
	for(i=2;i<=a;i++)
	{
	scanf("%lld",&n);
	ans+=abs(n);
	}
	cout<<ans;
	return 0;
} 
```
最后奉劝一句话：**十年OI一场空……**

---

## 作者：封禁用户 (赞：0)

题目传送>>[P7917](https://www.luogu.com.cn/problem/P7917)。  
一道水到不能再水的月赛题，水完之后发现题解区居然还开着，再加上本人的写法与题解区现有题解的写法稍有区别，故又水下此篇题解。  
### 题意简述：  
- 给定一长度为 $n$ 的序列 $a$，求经 $n-1$ 次任选两相邻数 $x$、$y$ 替换为 $x+y$ 或 $x-y$ 的操作后剩下那个数的最大值。  
- $1 \leq n \leq 10^5$，$|a_i| \leq 10^9$。  

### 题目分析:  
值得注意的是，替换操作针对的是两**相邻**数中的左数加右数或左数减右数，即为 $x+y$ 或 $x-y$，而不能是 $y-x$。那么我们也就可以从左端以第一数为始向右逐渐推进操作，终得一数余。对于遇到的右数，我们进行讨论，若正（或零），无疑加它为佳；反之，若负（或零），减它为佳，因为减去一个负数等于加上它的相反数（正数）。  
### AC 代码及评测结果（均未吸氧）：  
#### 未加手写快读快写:
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll n,a,ans=0;
int main()
{
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>a;
		ans+=(i==1 or a>=0)? a:-a;
	}
	cout<<ans;
	return 0;
}
```  
![](https://cdn.luogu.com.cn/upload/image_hosting/3uhcu9si.png)  
#### 加手写快读快写:  
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll n,a,ans=0;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
}
int main()
{
	n=read();
	for(ll i=1;i<=n;i++)
	{
		a=read();
		ans+=(i==1 or a>=0)? a:-a;
	}
	write(ans);
	return 0;
}
```  
![](https://cdn.luogu.com.cn/upload/image_hosting/o36zg4y4.png)  
****  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：WsW_ (赞：0)

通过加法结合律可以发现，计算顺序与最终答案无关。  
再考虑最大。显而易见，加上一个正数比减去一个正数要大，减去一个负数比加上一个负数要大。所以，对于所有正数，都进行加法；对于所有负数，都进行减法，也就相当于加上那个数的绝对值。  
另外最终答案最大会是 $\vert a_i \vert \times n=10^{14}$，要开 ```long long```
### 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,ans;
signed main(){
	scanf("%lld",&n);
	scanf("%lld",&ans);
	for(int i=2;i<=n;i++){
		scanf("%lld",&x);
		ans+=abs(x);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

## 思路

求最大值，不是二分答案就是贪心。这里很难二分所以考虑贪心。很容易想到贪心策略，从左往右扫，右侧的数 $<0$ 就减，右侧的数 $>0$ 就加，如果右侧的数是 $0$ 无所谓。

考虑证明。对于 $2$ 个数（假设第一个是 $x$，第二个是 $y$）的情况明显有：

- 当 $y\leqslant0$，$x-y\geqslant x+y$（这里取等于的时候 $y=0$）
- 否则 $x-y<x+y$。

容易发现满足最优子结构的性质（或者说能够归纳证明），每次合并两个数都最优，最终的答案一定最优。

## 代码

掌握了思路完全不难写。

```
cin>>n;
for(int i=1;i<=n;i++){
	cin>>a[i];
}
for(int i=1;i<=n-1;i++){//依次进行合并
	if(a[i+1]<0){//贪心策略，我这里把0归类到加
		a[i+1]=a[i]-a[i+1];//是负数就减
	}
	else{
		a[i+1]+=a[i];//非负数就加
	}
}
cout<<a[n]<<endl;//输出第n个，即最终留下的数
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:P7917](https://www.luogu.com.cn/problem/P7917)

* **【解题思路】**

首先我们知道，第一个数对答案的贡献只能是它本身。

之后，我们贪心地每次都选第一个（设为 $a$）与下一个数（设为 $b$）进行操作：

如果 $b<0$，那么删除它们并插入 $a-b$。$b$ 对答案做出正贡献。

如果 $b>0$，那么删除它们并插入 $a+b$。$b$ 依然对答案做出正贡献。

如果 $b=0$，则怎么样无所谓，对答案无贡献。

可以证明这必定是一种最优方案。

实现时只要将第一个数与其他数的绝对值相加即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long inital,cnt,tmp;
	cin>>cnt>>inital;
	while(--cnt)
		 cin>>tmp,inital+=abs(tmp);
	cout<<inital;
	return 0;
}
```

---

## 作者：Viktley (赞：0)

**题目大意：**

给定一个序列 $n$ ，有 $n-1$ 次操作，每次操作规定将相邻两个数 $x,y$ 取出，放入一个新的数 $x+y$ 或 $x-y$ 问最后剩余那个数的最大值！

**思路：**

注意到题目给出了正负两种操作，考虑对于两个数操作后值最大，那么显然符号取决去右边那个数的正负性（~~对于右边数，如果是负数就用减号，反之亦然~~）。

那么给出贪心策略：对于每个数，我们只用加他的绝对值即可（第一个数~~不能~~操作~~）

**Code:**

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define ll long long

using namespace std;

const int N = 1e5 + 10;
ll n, a, ans;

int main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a);
		if(i == 1) ans = a;
		else ans += abs(a);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7917)

简单的贪心题

**贪心方法**：答案是 $a_1+abs(a_2)+...+abs(a_n)$

**证明**：先来看个例子：

一个数列 $1,-2,-3,4,-5$

错误方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/16u1t4np.png)

正确方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/vv66qgir.png)

那么这是为什么呢？

从 $a_2$ 或 $a_3$ 或 $...$ 或 $a_n$ 开始操作的话，不能保证前面的数没有负数，

有负数时，就如上文的错误方法一样，只能将这个负数加上之前的最大值。

显而易见，这会使最大值变小不可能是最优情况。

所以最优情况，就是从第一个数开始往后遍历，这样能保证最多的值是被加到最大值中的，而不是减进去的，就如上文的正确方法。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
    int n;
    long long ans=0;
    scanf("%d%d",&n,&a[1]);
    for(int i=2;i<=n;i++){
        scanf("%d",&a[i]);
        ans+=abs(a[i]);
    }
    printf("%lld",ans+a[1]);
    return 0;
}
```
注意 `ans` 要开 `long long` ！


---

## 作者：phmaprostrate (赞：0)

## 分析
题意简明，直接开始分析，仔细观察两个操作，$x + y$ 和 $x - y$ 假设 $x$ 为正数，那一定能保证加上 $y$ 的绝对值。是负的就减，是正的就加。再考虑 $x$ 为负数时，一样，加上绝对值一定是最大的。这样，只有第一个只能加上本身，其他的可以加绝对值。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int ans = 0;
signed main(){
	 cin >> n;
	 for(int i = 1 ; i <= n ; i ++){
	 	int x;
	 	cin >> x;
	 	if(i == 1) ans += x;
	 	else ans += abs(x);
	 }
	 cout << ans;
	return 0;
}
```



---

## 作者：A_Đark_Horcrux (赞：0)

考虑一个简单的贪心，记录一个 ans 作为结果，从左到右遍历，如果 $a_i < 0$ 就用 ans 减去它，否则就加上它，使得每一次的和都能往上增长。最后的答案就是求出的和

由于每次操作只能左加右或者左减右，因此不管从哪一位开始操作，只要操作方案是相同的，结果就是相同的。因此可以保证从左到右遍历是合理的qwq

再提一句，ans 的初始值要赋成 $a_1$，第一位是非加不可的。

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
int n,x; long long ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&x),ans=(x>0||i==1?ans+x:ans-x);
	printf("%lld\n",ans); return 0;
 } 

---

## 作者：Buried_Dream (赞：0)

签到题，比较水。

## 题意：
给定一个长度为 $n$ 的序列，进行 $n - 1$ 次操作，没次操作可能有两种，一种为放入 $x + y$ ,另一种是放入 $x - y$，使最后剩下的数最大。
 
## 思路：

首先我们想让最后剩下的数最大，可以将这个序列分成两部分，一部分是第一个数，另一部分是剩下的数。

那为什么这样分？

因为第一个数的正负你无法通过加减去改变，然后不考虑第一个数，剩下的数是不是都可以变成正的，如果他是负的左边的减去他可以变成正的，正的话就加。

加的顺序也不会影响最后的答案。

所以说最后的答案就是第一个数加上剩下所有数的绝对值。

## code：
```cpp
/*
Work by: 看我后面——
goal： Cheat points
algorithm：？？？
thinking support：？？？
*/
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define int short
#define il inline
#define re register
#define inf -0x3f3f3f3f
#define FJH 1314
using namespace std;

const int maxn = 1e8 - 44;
const int MAXN = 2e3 + 32;

inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-'){w = -1;}ch = getchar();}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
il void print(int x){
	if(x < 0) putchar( '-' ),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int ans_2 = 0;
signed main(){
	int n = read(); 
	for(int i = 1; i <= n; i++) {
	int x = read();
		if(i == 1) {
			ans_2 = x;
		}
		else ans_2 += abs(x);
	}
	cout << ans_2;
}

```


---

## 作者：joy2010WonderMaker (赞：0)

对于每个数，我们可以分两种情况考虑。

- $a \le 0$，我们可以加上 $|a|$。

- $a \ge 1$，我们可以加上 $a$。

可以证明，这一定是最优解。

所以除去第一个数，其他数就加上它的绝对值。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,ans;
int main(){
    scanf("%lld%lld",&n,&a);
    ans=a;
    for(int i=1;i<n;i++)
        scanf("%lld",&a),ans+=abs(a);
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Light_in_Dark (赞：0)

## P7917 [Kubic] Addition
> 众所周知，$\displaystyle \sum^{n}_{i=1}{a[i]} \le \displaystyle \sum^{n}_{i=1}{|a[i]|}$ 是永远成立的，所以我们只需要每次增加一个 $sum$ 的绝对值即可使数的值最大。

> 由于第一个数不能在前面加绝对值，所以用第一个数加上后面的数的绝对值即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a, ans;
int main() {
	cin >> n >> ans;
	for (int i = 1; i < n; ++i) {
		cin >> a;
		ans += abs(a);
	}
	cout << ans;
	return 0;
}
```

过于简短，不喜勿喷。

---

## 作者：CaoXian (赞：0)

## P7917 [Kubic] Addition 题解

很简单的贪心题。

对于每一个非负数，将答案直接加上它一定是最优的。对于除了第一个数的负数，将答案减去它也肯定是最优的（第一个数只能作为初始答案，因为题目要求操作的两数 `x` ， `y` ， `x` 一定在 `y` 的左边，所以第一个数永远不可能作为减数）。

因为每次操作的数只能是相邻的，操作后的结果又是在两数原位置，原数列所有数字的相对位置不会变。所以一个数执行的操作与它操作的顺序无关，可以放心的从左至右贪心了。

Code：
```cpp
#include <stdio.h>
long long n, a, ans;
int main() {
	scanf("%lld%lld", &n, &ans);
	while(--n) {
		scanf("%lld", &a);
		(a < 0) ? (ans -= a) : (ans += a);//按照上述的贪心策略也可以写成ans+=abs(a);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

首先，先来证明一个结论：对于数对 $(x,y)$，若 $y<0$，则最大值为 $x-y$，反之为 $x+y$，所以说 $(x,y)$ 的最大值为 $x+|y|$，但我们是用前面减后面的，所以第一个数只能加它本身，所以我们可以用贪心的思路直接求 $\sum\limits_{i=2}^na_i+a_1$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,ans;
signed main(){
    scanf("%lld%lld",&n,&ans);
    for(int i=2;i<=n;i++){
        scanf("%lld",&a);
       	ans+=abs(a);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：HappyCode (赞：0)

### 思路
这题需要将 $n$ 个整数相邻两个进行加减运算，问最大是多少。但实际上就是在 $n$ 个数字间填上加减号，求最大值。  
加一个整数原数变大，减一个负数原数变小。  
但算式开头默认有个加号，所以第一个数必须要加上，不管它是否是负数。  
我们定义一个 $s$，存储 $a$ 数组中最大的和，然后去遍历 $a$ 数组。  
如果 $a_i \ge 0$，那么就将 $s$ 增加 $a_i$。  
如果 $a_i \le 0$，那么就将 $s$ 减少 $a_i$。  
但要注意，当 $i=1$ 时，必须将 $s$ 增加 $a_i$
### 提醒
还是那句话：**十年 OI 一场空，不开 `long long` 见祖宗。**  
再提醒一句：**第一个数只能加上！我在月赛过程中就因为这个 Boom 0 了无数次！**

### 代码
```cpp
#include<iostream>
using namespace std;
long long n,a[100005],s;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        if(a[i]>=0){
            s+=a[i]; //正数就加
        }else if(i!=1){
            s-=a[i]; //负数就减
        }else{
            s+=a[i]; //第一个只能加上！
        }
    }
    cout<<s<<endl;
    return 0;
}
```

---

