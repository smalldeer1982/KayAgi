# 「SWTR-4」Meeting in the Forest

## 题目背景

每当月圆时分，五个族群的族猫们都会聚集在小岛上，进行每月的森林大会。蒟星为了了解其它五族猫的特点，就扮成了一只独行猫来到小岛上……

## 题目描述

森林大会上有 $n$ 只猫，每只猫的武力值为 $a_i$，于是蒟星列出了下面这样一个方程：

$$x^n+\sum_{i=1}^{n}a_ix^{n-i}=0$$

- 通俗地讲，这个方程就是 $x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$。

蒟星根据 TA 优（cu）秀（bi）的数学知识可以知道，这个方程在复数集内有 $n$ 个根，不妨把这 $n$ 个根设为 $x_1, x_2, ..., x_n$。

接下来蒟星想要知道森林大会上的猫的实力如何，于是列出了下面一个表达式：

$$\sum_{i=1}^{n}(b_i\times \sum_{1\le j_1 < j_2 <\cdots< j_i \le n}^{n}x_{j_1}x_{j_2}\cdots x_{j_i})$$

- $\sum_{1\le j_1 < j_2 < \cdots < j_i \le n}^{n}x_{j_1}x_{j_2}\cdots x_{j_i}$ 就是从方程的 $n$ 个根中选出 $i$ 个，求所有可能方案的 $i$ 个根的乘积之和。

但蒟星只要这个表达式对 $10^9+7$ 取模后的值就好了。

- 若答案为负数 $a$，请输出 $a + (10^9+7)$。

蒟星把这个任务交给了您，不过他已经告诉你了 $n$，$a_i$ 和 $b_i$，您能帮帮 TA 吗？

## 说明/提示

【样例 $1$ 说明】

原方程为 $x^2-2x+1=0$，此时 $x_1=x_2=1$。

表达式的值为 $x_1+x_2+x_1x_2=1+1+1=3$。

【样例 $2$ 说明】

原方程为 $x^3-3x^2+4=0$，此时 $x_1=-1,x_2=x_3=2$。

表达式的值为 

$$\begin{aligned}&2\cdot (x_1+x_2+x_3)+3\cdot(x_1x_2+x_1x_3+x_2x_3)+4\cdot x_1x_2x_3\\=\ &2\times(-1+2+2)+3\times(-2+(-2)+4)+4\times (-4)\\=\ &-10\end{aligned}$$

因为 $-10$ 为负数，所以输出 $-10+(10^9+7)=999999997$。

【数据范围与约定】

对于 $10\%$ 的数据，$n=1$。

对于另外 $20\%$ 的数据，$n=2$。

对于 $40\%$ 的数据，$n\leq 10$。

对于 $60\%$ 的数据，$n\leq 10^3$。

对于 $100\%$ 的数据，$1\leq n \le 2 \times 10^5$，$-10^9 \le a_i, b_i \le 10^9$。

【Tips】

[韦达定理](https://baike.baidu.com/item/%E9%9F%A6%E8%BE%BE%E5%AE%9A%E7%90%86/105027?fr=aladdin)也许会对你有帮助。

【Source】

[Sweet Round 04](https://www.luogu.com.cn/contest/26414)$\ \ $C

idea & std：[蒟蒻的名字](https://www.luogu.com.cn/user/147999)

## 样例 #1

### 输入

```
2
-2 1
1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
-3 0 4
2 3 4```

### 输出

```
999999997```

# 题解

## 作者：Rubidium_Chloride (赞：8)

~~这题是数论题吧。~~

### 0.前言

请容许我~~无耻地~~放一下我的[博客](https://www.luogu.com.cn/blog/Rolling-blog1424/)的链接……

接下来，让我们进入正题。

## 1.分析题目

### 1.1 题目大意

[题目传送门](https://www.luogu.com.cn/problem/P6211)

即求$\sum\limits_{i=1}^{n}(b_i\times\sum\limits_{1\le j_1< j_2<...< j_i\le n}x_{j_1} x_{j_2}\dots x_{j_i})------(1)$

其中$x_1,x_2...x_n$为$n$次方程$x^n+a_1x^{n-1}+a_2x^{n-2}+...+a_n=0$的$n$个复数范围内的根。

### 1.2 分析做法

仔细想想，什么东西有和$(1)$有相同/类似的性质呢？

本蒟蒻前想后想，终于想出了一个相同的东西：**韦达定理**。

~~（话说提示里不是有吗？）~~

## 2.韦达定理

如果您还不知道~~伟大~~韦达定理，珂以看[这里](https://baike.baidu.com/item/%E9%9F%A6%E8%BE%BE%E5%AE%9A%E7%90%86/105027?fr=aladdin)。

证明如下：

由于[代数基本定理](https://www.baidu.com/link?url=6AUJ7OMyHE7lIXEKXq6qDjFedr4xbOze8pvWllWQ73zcxHdFT0KZK7EqG3IO4-8rS6aji5RXLtgH7WIvkJMgOmtZMTOCCvIfjwdS5fezNzEavLKla7Axfz6c-4dpwSbscVQuaBozi5ouldBk4vtPSa&wd=&eqid=c287f42d000068db000000055e7c1a18)，有$x_1,x_2\dots x_n$是$a_0x^n+a_1x^{n-1}+\dots+a_n=0$的$n$个复数根。

那么根据因式分解基本常识，可以得到$a_0(x-x_1)(x-x_2)\dots(x-x_n)=0------(2)$

这个方程的$n$个复数根和$(1)$的$n$个根**一模一样**。

**所以可以得到：$(2)$与$(1)$是同一个方程**！

将$(2)$展开，得：

$a_0x^n-a_0(\sum\limits_{1\le i\le n}x_i)x^{n-1}+a_0(\sum\limits_{1\le i_1< i_2\le n}x_{i_1}x_{i_2})x^{n-2}\dots+(-1)^na_0\prod\limits_{i=1}^{n}x_i$

其各项系数应该与$(1)$的各项系数相同。

于是可得以下等式：

$\begin{cases}a_0(\sum\limits_{1\le i\le n}x_i)=a_1\\a_0(\sum\limits_{1\le i_1< i_2\le n}x_{i_1}x_{i_2})=a_2\\\dots\\(-1)^na_0\prod\limits_{i=1}^{n}x_i=a_n\end{cases}$

将每行等式同时除以$a_0$即得韦达定理最终形式：

$\begin{cases}\sum\limits_{1\le i\le n}x_i=\frac{a_1}{a_0}\\\sum\limits_{1\le i_1< i_2\le n}x_{i_1}x_{i_2}=\frac{a_2}{a_0}\\\dots\\\prod\limits_{i=1}^{n}x_i=(-1)^n\frac{a_n}{a_0}\end{cases}$

这不就和题目要我们求的东西差不多嘛？

### 3.最后分析与Code

~~（没错，你们最爱的代码君将在若干行后到达题解）~~

由第$2$部分的证明，我们得到了题目让我们求的东西就是:

$\sum\limits_{i=1}^{n}(-1)^ia_ib_i$

所以我们就有了如下的代码：

```cpp
#include<bits/stdc++.h>
#define N 200009
using namespace std;
typedef long long ll;
ll n,a[N],b[N],ans,flag=1;
const ll MOD=1e9+7;
inline int read(){//写了一个快读卡常 
	int x=0;int f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		flag*=-1;//flag就是用来计算(-1)^n的 
		b[i]=read();
		ans+=(a[i]*b[i]*flag);ans%=MOD;
	}
	printf("%lld",(ans+MOD)%MOD);//别忘了最后负数取模！ 
	return 0;
//}禁止抄袭！

```
### 4.后记

看我这么努力地写了这篇通俗易懂的题解，还附上了十分具体的证明，您不给我点个赞吗？

~~最后的最后，管理大大求过。~~

---

## 作者：Scrutiny (赞：4)

# 解决这题只用四个字：韦达定理

个人感觉此题橙（毕竟韦达定理是初中内容 ）

首先，对于一元二次方程$ax^2+bx+c=0(a≠0)$,我们知道$x=\frac{-b±sqrt(b^2-4ac)}{2a}$,故$x_1+x_2=\frac{-b}{a},x_1x_2=\frac{c}{a}$

那么对于一元三次方程$ax^3+bx^2+cx+d=0(a≠0)$,我们设其根为$x_1,x_2,x_3$,则$ax^3+bx^2+cx+d=a(x-x_1)(x-x_2)(x-x_3)$

所以$x_1+x_2+x_3=\frac{-b}{a},x_1x_2+x_2x_3+x_3x_1=\frac{c}{a},x_1x_2x_3=\frac{-d}{a}$

同理，对于题中所述一元$n$次方程$x^n+a_1x^{n-1}+......+a_n=0$也有类似的式子:
$$\begin{cases}x_1+......+x_n=-a_1\\\sum\limits_{1≤i<j≤n}x_ix_j=a_2\\......\\x_1x_2......x_n=a_n\end{cases}$$

所求的式子珂以化为$\sum\limits_{i=1}^n(-1)^na_ib_i$

还有一些小细节如取模等，这里不再赘述

上代码：

```cpp
#include<bits/stdc++.h>
#define N 1000000007
using namespace std;
long long ans,a[200010],b[200010],n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	for(int i=1;i<=n;i++){
		if(i%2==0){
			ans+=a[i]*b[i];
			if(ans<0){
				ans+=N;
			}
			ans%=N;
		}
		else{
			ans-=a[i]*b[i];
			if(ans<0){
				ans+=N;
			}
			ans%=N;
		}
	}
	cout<<(ans+N)%N;
	return 0;
}
```

还是那句话，~~要抄窝的题解请理解后再抄~~

---

## 作者：Warriors_Cat (赞：2)

### $1.\;10\;pts$

送分的，答案就是 $-a_1\times b_1$。

### $2.\;30\;pts$

对于一个二次方程，用求根公式 $x_{1, 2}=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}$，存储一下 $\Delta$，然后暴算即可。

### $3.\;60\;pts$

这个其实只是用来凑数的，也不知道有什么方法。

### $4.\;100\;pts$

下面来讲正解惹QAQ。

其实这道题是韦达定理的拓展应用，在这里就手推一下韦达定理吧。

首先，根据题目我们可以得到：

$x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$ 的根为 $x_1, x_2, ... ,x_n$。

其次，有个东东叫做余式定理，它是在说这样一件事：

> 对于一个多项式 $f(x)$，它除以 $x-a$ 的余式为 $f(a)$。

> 特别的，当 $f(a)=0$ 时，$x-a$ 是 $f(x)$ 的一个因式。

于是，我们可以令 $f(x)=x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$，那么 $f(x_1)=f(x_2)=...=f(x_n)=0$。

根据余式定理，我们可以知道：

$$x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=(x-x_1)(x-x_2)...(x-x_n)$$

这个表达式是**恒成立**的！

因此，我们把右边的式子拆开，与左边的系数一一匹配，发现了这样一件事情：

$$\sum_{1\le j_1 < j_2 <\cdots< j_i \le n}^{n}x_{j_1}x_{j_2}\cdots x_{j_i}=(-1)^i\times a_i$$

到这里，这道题就基本解决了。我们只需要在输入 $a_i$ 时判断 $i$ 的奇偶性，如果奇数就变为 $-a_i$，然后与 $b_i$ 相乘，最后累加起来就可以啦。

下面放上 $100\;pts$ 代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring> 
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int n, a[200010], b[200010], c[200010], ans;
signed main(){
	//freopen("test20.in", "r", stdin);
	//freopen("test20.out", "w", stdout);
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
	for(int i = 1; i <= n; ++i){
		if(i & 1) c[i] = -a[i];//奇数变为相反数
		else c[i] = a[i];//否则还是自己
    }
    for(int i = 1; i <= n; ++i) ans = (ans + b[i] * c[i] % mod) % mod;//答案累加
	printf("%lld", (ans + mod) % mod);//注意负数的判断QAQ
	return 0;//完结撒花
}
```
## End

---

## 作者：Aw顿顿 (赞：1)

毕竟一道韦达定理的题目，难度大概是普通初中数学。

## 引入

在我们学习一元二次方程的时候，我们接触过：

$$ax^2+bx+c=0$$

$$x=\dfrac{-b±\sqrt{b^2-4ac}}{2a}$$

于是我们可以得到该方程两个复数根的关系：

$$x_1+x_2=-\dfrac{b}{a}\quad x_1x_2=\dfrac{c}{a}$$

而现在我们尝试引入高次韦达定理。

对于题目中给出的 $n$ 次的方程：

$$x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$$

我们可以断定，一定存在 $n$ 个复数根，记为 $x_1,x_2,x_3\cdots,x_{n-1},x_n$。

根据**余式定理**：

$f(x)$ 除以 $x-c$ 的余式记为 $f(c)$，当 $f(c)=0$ 时 $x-c$ 是 $f(x)$ 的因式。这是一个很直观的内容

这时候，我们可以尝试构造出一个**同样存在这些根的方程**，也就是说，构造出一个方程，使得这两个方程可以等效对应——利用小学即可以理解的因式分解，得到：

$$x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=(x-x_1)(x-x_2)(x-x_3)\cdots(x-x_n)$$

这里我们把这些复数根看作常数。

两边展开对比系数，然后你会发现有：

$$x_1+x_2+x_3+\cdots x_n=-a_1$$

$$x_1x_2+x_2x_3+x_3x_4+\cdots x_{n-1}x_n=a_2$$

$$x_1x_2x_3+x_2x_3x_4+\cdots x_{n-2}x_{n-1}x_n=a_3$$

$$\cdots$$

$$x_1x_2x_3\cdots x_n=a_n$$

结合题目所求可以发现要求的内容是：

$$\sum\limits_{i=1}^{n}(-1)^na_ib_i$$

每一项进行讨论然后与 $b_i$ 相乘即可。




---

## 作者：ny_123457 (赞：0)

## Part.1 韦达定理
设复系数一元 $n$ 次方程 $a_{n}x^n+a_{n-1}x^{n-1}+a_{n-2}x^{n-2}+\cdots+a_{1}x+a_{0}=0$ 的根为 $x_{1},x_{2},x_{3},\cdots,x_{n}$，则成立：$\sum_{i=1}^{n}=-\frac{a_{n-1}}{a_{n}}$ 且 $x_{1}x_{2} \cdots x_{n}=(-1)^n\frac{a_{0}}{a_{n}}$。
## Part.2 正文解析
不难发现题目描述中所述的方程与我们要求的可以应用上文所提到的韦达定理。    
将韦达定理代入进去可以发现文中所求的式子可以化为 $\sum_{i=1}^{n}(-1)^na_{i}b_{i}$，用代码求这串式子只需分开算 $(-1)^n$ 为整数和为负数的情况。
## Part.3 注意事项
本题涉及到对乘积的求和，所以不能用 int。  
对于每一次答案的更新都需要对 $10^9+7$ 取模。
## Part.4 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],b[200005],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++){
		if(i%2==0){
			ans+=a[i]*b[i];
			if(ans<0)ans+=1000000007;
			ans%=1000000007;
		}
		else{
			ans-=a[i]*b[i];
			if(ans<0)ans+=1000000007;
			ans%=1000000007;
		}
	}
	ans+=1000000007;
	cout<<ans%1000000007;
	return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6211)
# 思路
## 题目大意
在 $n$ 次方程 $x^{n} + a_{1}x^{n-1} + \dots + a_{n-1}x + a_{n} = 0$ 中 $x$ 的所有解为 $x_{1} , x_{2} , \dots , x_{n-1},x_{n}$，要求出 $\sum \limits_{i = 1}^{n} (b_{i} \times \sum \limits_{1 \le j_{1} < j_{2} < \dots < j_{i} \le n} x_{j_{1}} x_{j_{2}} \dots x_{j_{i-1}} x_{j_{i}})$ 的值。
## 做法
其实做出这个题目只要四个字：韦达定理。

### 证明：
对于一个一元二次方程 $ax^{2} + bx + c = 0$，它的两个解为 $x_1,x_2$ 一定满足 $x_1 + x_2 = \dfrac{-b}{a} , x_1x_2 = \dfrac{c}{a}$。

对于一元三次方程 $ax^{3} + bx^{2} + cx + d = 0$，它的三个解为 $x_1,x_2,x_3$ 一定满足 $x_1 + x_2 + x_3 = \dfrac{-b}{a} , x_1x_2 + x_1x_3 + x_2x_3 = \dfrac{c}{a} , x_1x_2x_3 = \dfrac{-d}{a}$。

相信大家已经找到规律了，所以在一元 $n$ 次方程 $x^{n} + a_{1}x^{n-1} + \dots + a_{n-1}x + a_{n} = 0$ 中可以列出 $n$ 个算式：
$$\begin{cases} x_1 + x_2 + \dots + x_n = -a_1 \\ \sum\limits_{1 \le i < j \le n} x_ix_j = a_2 \\ \dots \\ x_1x_2 \dots x_n = a_n \end{cases}$$
### 上述总结
最后，上面的 $n$ 个式子可以归并成 $\sum\limits_{i=1}^{n} (-1)^n \times a_ib_i$ 这一个式子。
# Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int P=1e9+7;
int a[N],b[N]; 
int main()
{
	int n;
	cin >>n;
	for(int i=1;i<=n;i++) cin >>a[i];
	for(int i=1;i<=n;i++) cin >>b[i];
	long long sum=0;
	for(int i=1;i<=n;i++)
	{
		if(i%2==0) sum+=1ll*a[i]*b[i];
		else sum-=1ll*a[i]*b[i];
		if(sum<0) sum+=P; //注意这里要取模
		sum%=P;
	}
	cout <<(sum+P)%P; //最后也要取模，不然会超
	return 0;
}

```

---

## 作者：tmlrock (赞：0)

## 思路
#### 韦达定理：
$$\sum_{i=1}^n x_i=-\dfrac{a_n-1}{a_n}$$
$$\sum_{1\leq i\leq n}^nx_i=\dfrac{a_1}{a_0}$$
$$\sum_{1\leq i\leq j\leq n}^nx_ix_j=\dfrac{a_2}{a_0}$$
$$\cdots$$
$$\prod_{i}^nx_i=(-1)^n\dfrac{a_n}{a_0}$$
----
so?
因为 $a_0=1$ , 所以题目中的
$$\large\begin{cases}
\sum_{1\leq i\leq n}^nx_i=-a_1\\

\sum_{1\leq i\leq j\leq n}^nx_ix_j=a_2\\
\cdots\\
\prod_{i}^nx_i=(-1)^na_n
\end{cases}$$

得出题目中的表达式是
$\sum_{i=1}^n\left(b_i\sum_{1\leq j_1\leq j_2\leq \cdots\leq j_i\leq n}^n \prod_{k=1}^i x_{j_k}\right)$

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\sum_{i=1}^nb_ia_i(-i)^i$ ,

所以，上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200010];
long long b[200010];
int main() {
	int n;
	cin>>n;
	long long ans=0;
	for(int i = 1; i<=n; ++i)cin>>a[i];
	for(int i = 1; i<=n; ++i)cin>>b[i];
	for(int i = 1; i<=n; ++i) {
		if(i&1)ans -= (a[i]*b[i])%1000000007;
		else ans+=(a[i]*b[i])%1000000007;//公式
	}
	cout<<(ans%1000000007+1000000007)%1000000007;//负数取模
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# 「SWTR-04」Meeting in the Forest

## 题目描述

给定方程 $x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$。

可以知道，这个方程在复数集内有 $n$ 个根，不妨把这 $n$ 个根设为 $x_1, x_2, ..., x_n$。

列出了下面一个表达式：

$\sum_{i=1}^{n}(b_i\times \sum_{1\le j_1 < j_2 <\cdots< j_i \le n}^{n}x_{j_1}x_{j_2}\cdots x_{j_i})$

- $\sum_{1\le j_1 < j_2 < \cdots < j_i \le n}^{n}x_{j_1}x_{j_2}\cdots x_{j_i}$ 就是从方程的 $n$ 个根中选出 $i$ 个，求所有可能方案的 $i$ 个根的乘积之和。

求表达式对 $10^9+7$ 取模后的值。

- 若答案为负数 $a$，请输出 $a + (10^9+7)$。


## 大意

初看没有头绪，那么八成是个数学题了。

举例可能会明显一点。

假设原方程为三次方程，解为 $x_1,x_2,x_3$。

那么表达式的值为：

$b_1\cdot (x_1+x_2+x_3)+b_2\cdot(x_1x_2+x_1x_3+x_2x_3)+b_3\cdot x_1x_2x_3$

## 思路

我们先从最简单的例子开始——二次方程。

我们给出一个二次方程 $ax^2+bx+c=0$，通过初中的数学知识可以知道这个方程一定有 $2$ 个解（不保证每个解都是实数，可能有复数）

这里照顾一下不知道虚数和复数的童鞋，虚数中有一个单位 $i$，满足 $i^2=-1$。

或者可以看一下以下文章。

[虚数的意义](https://zhuanlan.zhihu.com/p/43835594)

初中我们知道，只要二次方程 $ax^2+bx+c=0$ 有实数解，我们就可以把这个二次函数写成 $a(x-x_1)(x-x_2)=0$。现在我们引入了虚数和复数，那么对于每一个二次方程 $ax^2+bx+c=0$，我们都可以把它写成 $a(x-x_1)(x-x_2)=0$ 的形式。



扩展到 $x^n+a_1x^{n-1}+a_2x^{n-2}+\cdots+a_{n-1}x+a_n=0$，很显然我们也可以把它写成 $(x-x_1)(x-x_2)\dots(x-x_n)=0$ 的形式。因为 $x^n$ 的系数为 $1$，所以 $a=1$ 被省略。

任何我们再一一把 $(x-x_1)(x-x_2)\dots(x-x_n)=0$ 拆开，发现其为这种形式：

$x^n-(x_1+x_2+\dots+x_n)x^{n-1}+(x_1x_2+x_1x_3+\dots+x_{n-1}x_{n})x^{n-2}-\dots=0$

我们惊奇的发现，$a_1=-(x_1+x_2+\dots+x_n),a_2=x_1x_2+x_1x_3+\dots+x_{n-1}x_{n},a_3=-\dots$。

根据大意中的例子，我们发现这些正是我们要求的东西，只不过正负不同罢了。

还是根据大意中的例子，我们可以知道表达式的值为 $b_1\cdot (-a_1)+b_2\cdot(a_2)+b_3\cdot (-a_3)$。

这下就好求多了。

> 实际上我们应该知道 $a_i$ 的作用很大，因为当我们知道 $x^n$ 的系数为 $1$，方程的值为 $0$ 时，我们就可以通过该方程的根来计算出 $a_i$，那么反过来，题目告诉了我们 $a_i$，那么我们就可以通过 $a_i$ 来得到有关根的一些消息。

通过这个例子，我们就可以总结出答案了，即 $\sum\limits_{i=1}^n b_i\times a_i\times (-1)^i$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code by Ntsc .
       . Fancy Chargcy .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e6;
const int M=1e5;
const int MOD=1e9+7;
const int INF=1e5;

ll n,m,ans;
ll a[N],b[N];


signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		if(i%2)ans=(ans-a[i]*b[i])%MOD;
		else ans=(ans+a[i]*b[i])%MOD;
	}
	if(ans<0)ans+=MOD;
	cout<<ans;
	return 0;
}

```




---

## 作者：一只书虫仔 (赞：0)

#### Description

> 给定一个 $n$ 次方程 $x_n+a_1x_{n-1}+a_2x_{n-2}+\cdots+a_n$，设这个方程的解集为 $X_i$（$|X|=n$），求：
>
> $$\sum\limits_{i=1}^n\left(b_i\times \sum\limits_{1 \le j_1<j_2<\cdots<j_i \le n}X_{j_1}X_{j_2}\cdots X_{j_i}\right)$$

#### Solution

已知解集为 $X$，则原方程一定能化为：

$$x_n+a_1x_{n-1}+a_2x_{n-2}+\cdots+a_n=\prod\limits_{i=1}^n(x-X_i)$$

（tips：本来右边的式子要带一个系数 $a$，但因为左边方程 $n$ 次项系数就是 $1$，所以右边系数省略）

右边的拆开即得：

$$x^n+\sum\limits_{i=0}^{n-1}(-1)^{n-i}\sum\limits_{1\le j_1<j_2<\cdots<j_{n-i} \le n}\prod\limits_{k=1}^{n-i}X_{j_k}$$

系数一一对应就能发现，这东西和题目给的居然完全一样，就是：

$$\sum\limits_{1 \le j_1<j_2<\cdots<j_i \le n}X_{j_1}X_{j_2}\cdots X_{j_n}=(-1)^ia_i$$

原式即为：

$$\sum\limits_{i=1}^n\left(b_i\times \sum\limits_{1 \le j_1<j_2<\cdots<j_i \le n}X_{j_1}X_{j_2}\cdots X_{j_n}\right)=\sum\limits_{i=1}^n(-1)^ia_ib_i$$

然后这道谔谔题就做完了。

---

## 作者：JamesQin (赞：0)

此题出题人比较良心，告诉你是用韦达定理。       
因为原方程等价于$\prod\limits_{i=1}^n(x-x_i)$,所以
$$\sum\limits_{sym}^{}{\prod\limits_{i=1}^k{x_i}}=(-1)^k \times a_i$$    
其中$ 1 \leq k \leq n$。
所以说要求的式子为
$$\sum_{i=1}^n{(-1)^i \times a_i \times b_i}$$
直接计算即可，注意取模。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
int a[200010],b[200010];
signed main(){
	int n;
	cin>>n;
	
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	int ans=0,flag=1;
	for(int i=0;i<n;i++){
		if(flag) ans-=a[i]*b[i];
		else ans+=a[i]*b[i];
		flag=1-flag;
		ans%=mod;
	}
	cout<<(ans%mod+mod)%mod<<endl;
	return 0;
} 
```


---

## 作者：youngk (赞：0)

这道题我们可以通过用维达定理来轻松的解决它。(当然也可以通过这道题来学维达定理)。

相比于我们一般二元的维达定理。对于方程$ax^2+bx+c=0$
我们可以得到

$x_1+x_2=-\frac{b}{a}$

$x_1*x_2=\frac{c}{a}$

当然二元形式的结论我们直接同求根公式来实现证明。
但这里我们可以给出一个在$n$元情况下的一个维达定理。

对于方程$a_0x^n+a_1x^{n-1}+a_2x^{n-2}+...+a_{n-1}x+a_n=0$每个解为$x_1,x_2,...,x_n$有

$ \sum_{i=1}^{n}x_i=(-1)^{1}\frac{a_{1}}{a_0}$

$ \sum_{i=1}^{n}\sum_{j=i+1}^{n}x_i*x_j=(-1)^{2}\frac{a_{2}}{a_0}$

$ \sum_{i=1}^{n}\sum_{j=i+1}^{n}\sum_{k=j+1}^{n}x_i*x_j*x_k=(-1)^{3}\frac{a_{3}}{a_0}$

$.....$

$\prod_{i=1}^{n}x_i=(-1)^n\frac{a_{n}}{a_0}$

当然我们也可以把多元情况下的维达定理证明一下。

显然对于每个解，我们带入原方程会使原方程$f(n)=0$,考虑一下用高中的两点式推广到$n$点式。

$a_0x^n+a_1x^{n-1}+a_2x^{n-2}+...+a_{n-1}x+a_n=a_0*(x-x_1)*(x-x_2)*(x-x_3)*...*(x-x_n)$

显然两个式子相对的充要条件是$x^i$前的系数要相等。同时右边的式子每一项都是由$n$个数的乘积得到的，也就是说$x^i$项前的系数除于$a_0$就是$n-i$项乘积的轮换。其中要注意以下正负号，当$n-i$为奇数是为负，$n-i$为偶数是为正。

有了这个前置知识，这个题目的答案显然就是$ \sum_{i=1}^{n}(-1)^i*a[i]*b[i]$

```cpp
#include<cstdio>
#include<iostream>
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#define maxn 200100
#define endl '\n'
using namespace std;
const int mod = 1e9 + 7;
int n, a[maxn], b[maxn], ans, p = -1;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++) {
		ans = 1LL * ((ans + 1LL * p * b[i] * a[i] % mod) % mod + mod) % mod;
		p = -p;
	}
	cout << ans << endl;
	return 0;
}
```


---

