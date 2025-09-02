# [QkOI#R1] Quark and Equations

## 题目描述

给定 $n,m$，求有几组正整数对 $(i,j)$ 满足下列方程组：

$$
\begin{cases}
   i+j=n \\
   \lfloor\frac{i}{j}\rfloor+\lceil\frac{j}{i}\rceil=m
\end{cases}
$$

上式中，$\lfloor x\rfloor$ 表示对 $x$ 向下取整，$\lceil x\rceil$ 表示对 $x$ 向上取整。

## 说明/提示

### 样例解释

当 $n=m=2$ 时，只有 $(1,1)$ 满足条件。  
当 $n=2,m=1$ 时，无解。  
当 $n=6,m=2$ 时，只有 $(2,4),(3,3)$ 满足条件。

---

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$T,n,m\le 500$。
- Subtask 2（40 pts）：$T,n,m\le 5000$。
- Subtask 3（5 pts）：$m=1$。
- Subtask 4（5 pts）：$m>n$。
- Subtask 5（5 pts）：$m\in[n-1,n]$。
- Subtask 6（35 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n,m\le 10^{7}$。

## 样例 #1

### 输入

```
2
2 2
2 1
```

### 输出

```
1
0```

## 样例 #2

### 输入

```
1
6 2
```

### 输出

```
2
```

# 题解

## 作者：vectorwyx (赞：25)

附：方程化简那块LaTeX炸了……但在[博客](https://www.luogu.com.cn/blog/yuan-xin/solution-p6511)里显示的是正常的，我也不知道为啥……还请大家多多包容/kel，您如果有需要可以移步博客，感谢谅解！


以下是原文：

------------

考场上花了2h才推出式子，我太菜了/kel

## 一.前置知识：
令$\lfloor a \rfloor$表示对$a$向下取整，$\lceil a \rceil$表示对$a$向上取整。则有：

* 对于一个小数部分不为0的浮点数$a$，若$a$的整数部分为$k$，则$\lfloor a \rfloor=k$，$\lceil a \rceil=k+1$。
* 对于一个小数部分等于0的浮点数$a$，$\lfloor a \rfloor=\lceil a \rceil=a$
* 对于一个浮点数$a$，若$\lfloor a \rfloor=k$，那么a的取值范围为$k\le a  <k+1$，若$\lceil a \rceil=k$，那么a的取值为$k-1<a\le k$

## 二.推导式子
题目的要求是求出方程$\lfloor \frac{i}{j}\rfloor+\lceil \frac{j}{i} \rceil=m$且$i+j=n$的正整数解的个数。

那好办，**把**这个**方程转化成不等式**不就行了。

第一个方程有两个变化量：$\lfloor \frac{i}{j}\rfloor$和$\lceil \frac{j}{i} \rceil$，它们之间的关系并不明朗。如果能**把两个化简成一个**那该多好啊。

如何化简呢？不难发现$i<j$时$\lfloor \frac{i}{j} \rfloor=0$，而$i\ge j$时$\lceil \frac{j}{i}\rceil=1$。也就是说**不管$i,j$谁大谁小，总是有一个变化量的值是可以确定的**。因此这个方程就愉快地化简成了：
$$
\begin{cases}
0+\lceil\frac{j}{i}\rceil=m&(i<j)\\

\lfloor\frac{i}{j}\rfloor+1=m&(i\ge j)           
\end{cases}
$$

至此，我们的任务就是求解$\lceil \frac{j}{i} \rceil=m$和$\lfloor \frac{i}{j}\rfloor=m-1$

**根据前置知识中的第3条，$\lceil \frac{j}{i} \rceil=m$可转化为不等式$m-1<\frac{j}{i}\le m$，把$i$用$n-j$代替，解出来就是$\frac{n}{m+1}\le i<\frac{n}{m}$，由于$i$是正整数，所以这个不等式等价于$\lceil\frac{n}{m+1}\rceil\le i<\lceil\frac{n}{m}\rceil$，故方程的正整数解有$\lceil\frac{n}{m}\rceil-\lceil\frac{n}{m+1}\rceil$个**

同理，另一个方程$\lfloor \frac{i}{j}\rfloor=m-1$通过上述做法可以得出正整数解有$\lfloor\frac{n}{m}\rfloor-\lfloor\frac{n}{m+1}\rfloor$个

（就只是变了一下数值和取整的方向，不再赘述qwq）

综上，对于每组$n,m$，其答案为$\lceil\frac{n}{m}\rceil-\lceil\frac{n}{m+1}\rceil+\lfloor\frac{n}{m}\rfloor-\lfloor\frac{n}{m+1}\rfloor$。

最后特判一下特殊情况，直接输出，这题就做完了。
## 三.代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)//宏定义简化for循环 
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){//快读 
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

void work(){//求解 
	int n=read(),m=read(),ans=0;
	//很好想的特判不多说 
	if(m>n||m==1){
		puts("0");
		return;
	} 
	if(m==n-1||m==n){
		puts("1");
		return;
	}
	int x,y;//取值范围 
	x=ceil(n*1.0/(m+1)),y=ceil(n*1.0/m);//化简后得到的第一个不等式 
	ans+=y-x;
	x=floor(n*1.0/(m+1)),y=floor(n*1.0/m);//化简后得到的第二个不等式 
	ans+=y-x;
	printf("%d\n",ans);
	return;
}

int main(){
	int T=read(); 
	while(T--) work();
	return 0;
}
```
码LaTeX不易，如果这篇文章给予了您帮助，您看能不能点个赞再走？谢谢！

---

## 作者：绝顶我为峰 (赞：9)

~~让我们一起赞美良心的出题人吧~~

这题作为签到题非常不错

部分分非常好想，就直接讲正解了

首先，我们注意到 $\frac{i}{j}$ 和 $\frac{j}{i}$ 中一定有一个是小于 $1$ 的

当 $i<j$ 时，$\lfloor\frac{i}{j}\rfloor=0$

否则 $\lceil\frac{j}{i}\rceil=1$

那么我们只要讨论另一部分大于 $1$ 的部分就可以了

首先当 $i<j$ 时，$\lfloor\frac{i}{j}\rfloor+\lceil\frac{j}{i}\rceil=\lceil\frac{j}{i}\rceil=m$

由 $i+j=n$ 得 $j=n-i$

代入可得 $\lceil\frac{n-i}{i}\rceil=\lceil\frac{n}{i}-1\rceil=\lceil\frac{n}{i}\rceil-1=m$

所以 $\lceil\frac{n}{i}\rceil=m+1$

将这个式子拆成不等式组，可得

$$\begin{cases}
\frac{n}{i}>m\\
\frac{n}{i}\leq m+1
\end{cases}$$

因为 $i>0$，所以

$$\begin{cases}
\frac{n}{m}>i\\
\frac{n}{m+1}\leq i
\end{cases}$$

所以满足条件的 $i$ 的范围是 $\frac{n}{m+1}\leq i<\frac{n}{m}$

同理，当$j\leq i$ 时，范围是$\frac{n}{m+1}< i\leq\frac{n}{m}$

综上进行整理，答案是

```cpp
floor(n*1.0/m)-ceil(n*1.0/(m+1))+ceil(n*1.0/m)-floor(n*1.0/(m+1))
```

然而这个代码并不能处理 $m=1$ 的情况

所以再来个特判

代码很简单啦~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int t,n,m;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        if(m==1)
        {
            puts("0");
            continue;
        }
        int ans=floor(n*1.0/m)-ceil(n*1.0/(m+1))+ceil(n*1.0/m)-floor(n*1.0/(m+1));
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：7)

### $Solution:$

考虑分类讨论。

#### $1. i < j$。

$\therefore\lfloor\dfrac{i}{j}\rfloor=0$，$\lceil\dfrac{j}{i}\rceil = m$。

$\therefore (m-1)i < j \le mi$

$mi < n \le (m+1)i$

$\dfrac{n}{m+1} \le i < \dfrac{n}{m}$

同时注意一下 $i < \dfrac{n}{2}$ 就行了。

#### $2. i = j$

那么只有 $n \equiv 0 \mod 2$ 且 $m = 2$ 时才成立。

#### $3. i > j$

$\therefore \lceil\dfrac{j}{i}\rceil = 1$，$\lfloor\dfrac{i}{j}\rfloor=m-1$

$\therefore (m-1)j \le i < mj$

$mj \le n < (m+1)j$

$\dfrac{n}{m+1} < j \le \dfrac{n}{m}$

同时注意一下 $j < \dfrac{n}{2}$ 就行了。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
int t, n, m;
int main(){
	t = read();
	while(t--){
		n = read(); m = read();
		int l, r, x, ans = 0;
		if(n & 1) x = n / 2; else x = n / 2 - 1;
		if(n % (m + 1)) l = n / (m + 1) + 1; else l = n / (m + 1);
		if(n % m) r = n / m; else r = n / m - 1;
		l = max(l, 1); r = min(r, x);
		ans += max(r - l + 1, 0);
		if(n % 2 == 0 && m == 2) ans++;
		l = n / (m + 1) + 1; r = n / m;
		l = max(l, 1); r = min(r, x);
		ans += max(r - l + 1, 0);
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：Ireliaღ (赞：5)

提供一个在考场上很好想的解法。

观察第二个方程，两个分式，并且是$i$和$j$互相除并取整，不难看出值在变化的只有“较大整数除以较小整数”，也就是说两个分式只有一个的值在变化。所以我们可以分类讨论。

* $i > j$

	- 上取整式的值为$1$，所以$\lfloor \frac{i}{j} \rfloor = m - 1$
    
    - 考虑枚举$j$，再将$n - j$代入$i$，我们就要求出$\forall j$使得$n - j \in [(m - 1)j, mj)$ ①
    
* $j > i$

	- 下取整式的值为$0$，所以$\lceil \frac{j}{i} \rceil = m$
    
    - 考虑枚举$i$，再将$n - i$代入$j$，我们就要求出$\forall i$使得$n - i \in ((m - 1)i, mi]$ ②
    
观察①式和②式，不难发现，随着被枚举值的增大，左式的值在左移，而右式的区间在右移，那么被枚举值满足条件的取值一定是一个连续区间，所以通过倍增求出区间的左右端点即可。

最后不要忘记特判$i=j$的情况。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long LL;

int main() {
	int T, n, m;
	scanf("%d", &T);
	while (T--) {
		int ans = 0;
		scanf("%d%d", &n, &m);
		int l = 0, r = 0;
		for (int i = 25; ~i; i--) {
			int w = (1 << i), tmp = l + w;
			if (tmp + tmp >= n) continue;
			if (n - tmp >= (LL)m * tmp)
				l = tmp;
		}
		l++; r = l - 1;
		for (int i = 25; ~i; i--) {
			int w = (1 << i), tmp = r + w;
			if (tmp + tmp >= n) continue;
 			if (n - tmp >= (LL)(m - 1) * tmp)
 				r = tmp;
		}
		ans += r - l + 1;
		l = 0, r = 0;
		for (int i = 25; ~i; i--) {
			int w = (1 << i), tmp = l + w;
			if (tmp + tmp >= n) continue;
			if (n - tmp > (LL)m * tmp)
				l = tmp;
		}
		l++; r = l - 1;
		for (int i = 25; ~i; i--) {
			int w = (1 << i), tmp = r + w;
			if (tmp + tmp >= n) continue;
			if (n - tmp > (LL)(m - 1) * tmp)
				r = tmp;
		}
		ans += r - l + 1;
		if (n % 2 == 0 && m == 2) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：LCuter (赞：3)

**建议在博客界面内查看**

## A - Quark and Equations

##### $\text{Description}$

给定 $n,m$，求下列方程组有几组正整数解，我们认为无解为 $0$ 组解。

$$
\begin{cases}
   i+j=n \\
   \lfloor\frac{i}{j}\rfloor+\lceil\frac{j}{i}\rceil=m
\end{cases}
$$

**本题单个数据点含多组数据。**

$1\le T\le 10^5,1\le n,m\le 10^{7}$

$\text{Solution}$

首先特判掉 $n=1$ 的情况，显然无解。

显然当 $m\in (-\infty,1]\cup[n+1,+\infty)$ 时无解，因为第二个方程的左边最大值和最小值分别为 $n,2$（实际上这是本来想出的）。

当 $i<j$ 时，第二个方程实际上是 $\lceil\frac{n}{i}\rceil=m+1$。转换成不等式组：

$$\begin{cases}\begin{aligned}& i\le\lfloor\frac{n-1}{m}\rfloor \\& i\ge \lfloor\frac{n-1}{m+1}\rfloor+1 \end{aligned}\end{cases}$$

当 $i\ge j$ 时，第二个方程实际上是 $\lfloor\frac{n}{j}\rfloor=m$。转换成不等式组：

$$\begin{cases}\begin{aligned}& j\le \lfloor\frac{n}{m}\rfloor \\& j\ge\lfloor\frac{n}{m+1}\rfloor+1 \end{aligned}\end{cases}$$

事实上已经把原先的小于/大于号通过奇怪的手段加上了等号，把没有取整符号的加上了取整符号，这样做起来会方便。

所以最后答案就是：

$$\lfloor\frac{n-1}{m}\rfloor-\lfloor\frac{n-1}{m+1}\rfloor+\lfloor\frac{n}{m}\rfloor-\lfloor\frac{n}{m+1}\rfloor$$

---

## 作者：do_while_true (赞：2)

泥萌的柿子为什么辣么长辣么麻烦。

让我来带你大力找规律。

观察一下给出的式子，我们很快能想到一个 $\mathcal{O}(N)$做法，每当一个 $i$ 出现时，保证第一个式子成立，则 $j=n-i$，关于 $n$ 的式子比关于 $m$ 的式子简单，所以我们开始打关于 $n$ 的表。也就是打出对于每一个符合 $i+j=n$ 的 $i,j$，它的第二个式子的值是多少。最后对出现的值的数量进行统计即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,vis[100010],ans,j;
int main()
{
    freopen("out.txt","w",stdout);
    scanf("%d",&n);
    puts("ans");
    for(int i=1;i<n;i++) //i=0或j=0都会使第二个式子出错
    {
        j=n-i; 
        ans=i/j+j/i+( j%i==0 ? 0 : 1);
        printf("%d=%d\n",i,ans);//算出对应的m 
        vis[ans]++;
    }
    puts("vis");
    for(int i=1;i<=n;i++)
        printf("%d: %d\n",i,vis[i]);//记录出每一个值出现的次数 
    fclose(stdout);
    return 0;
}
```
当你输入一个小 $N$ 观察无果时，你决定输入一个比较大的 $N$ ，想了想，输入了一个 $1000$。

你把 out.txt 使劲往下拉，发现在 $vis$ 后半部分全是 $0$。这是为什么呢？

你从后往前找，发现 $vis_{1000},vis_{999}$ 为 $1$ ，再往前就是 $vis_{500}=vis_{499}=1$，再往前是 $vis_{250}=vis_{249}=1$。诶等等，你心里默念着，$1000,500,250....$，这些不都是 $N=1000$ 的因子吗。如果一个数 $x$ 会被 $N$ 整除，那么 $x$ 以及 $x-1$ 都会加 $1$。

可是你刚才发现，$vis_{333}=2$，这是为什么呢。重新把刚才找到的数画在纸上，$1000/1000=1,1000/500=2.1000/250=4$，等等，中间有个 $3$ 在哪里？你回过头看 $333$，发现一个 $\lfloor\frac{1000}{3}\rfloor$ 恰好为 $333$,虽然 $333$ 不是 $1000$ 的因子，但是因为 $1000$ 整除一个数恰好为 $333$，所以 $vis_{333}=2$。

结合之前找到的，你想到了这样一个规律：对于一个 $x$，若 $N$ 能整除 $x$ ，则 $vis_{N/x}$ 和 $vis_{N/x-1}$ 都 $+1$。否则 $vis_{N/x}+2$。

向上翻你找到了 $vis_{27}=4$，你想了想发现，对于 $x=36,37$，都会使得 $vis_{27}+2$。继续向上到 $1$ ，你的规律对于 $vis$ 数组完全够用。

可是我们总不能枚举所有的 $x$ 求出全部的 $m$ 对应的答案啊。题目中已经给出了 $m$ ，我们可以反过来通过 $m$ 推出有多少个 $x$ 满足上面的规律。

显然对于 $m$ ，最小的 $x$ 为 $N/m$。我们同样知道对于 $m+1$，最小的 $x$ 为 $N/(m+1)$，则 $m+1$ 的最小的 $x$ 再往前一个就是对于 $m$ 最大的 $x$ 了。

我们可以求出推出对于 $m$ 所对应的所有符合条件的 $x$。最小的 $x1=N/m$，最大的 $x2=N/(m+1)$，$x1$ 和 $x2$ 中间的所有 $x$ 一定会给答案贡献 $2$。再特判 $N \bmod m,N \bmod (m+1)$，看最小/大的 $x$ 对答案的贡献是 $1$ 还是 $2$ 即可。

## $\mathcal{Code} :$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int T,n,m,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(m==1||m>n) puts("0");
		else {
			int x1,x2,ans=0;
			x1=n/m;
			if(n%m==0) {
				ans++;
				x1--;
			}
			x2=n/(m+1);
			if(n%(m+1)==0)
				ans++;
			ans+=(x1-x2)*2;
			printf("%d\n",ans);
		}
	}
}
```


---

## 作者：dead_X (赞：2)

## 思路简述
数 学 题

你管这叫橙???

这里给出一种 $O(Tlogn)$ 的考场保险做法。

我们考虑先指定大小关系之后分类讨论，得到 $i,j(i>j)$ 满足

$\lceil \frac{i}{j} \rceil = m (i>j)$

或者

$\lfloor \frac{i}{j} \rfloor = m-1$

的时候就是满足条件的一组解了。

显然， $\lceil \frac{i}{j} \rceil$ 和 $\lfloor \frac{i}{j} \rfloor$ 都有单调性并且大小区间是 $[0,10^7]$ 的，那么就可以直接写二分了。

代码不难给出(但是细节贼多)
## 代码(又臭又长)
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),m=read(),l=n>>1,r=n-1,x=(n-1)>>1,y=n,z=(n-1)>>1,w=n;
		if(n==1 || m==1) 
		{
			puts("0");
			continue;
		}
		if(n==2)
		{
			if(m==2) puts("1"); else puts("0");
			continue;
		}
		if(n<m)
		{
			puts("0");
			continue;
		}
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if((mid-1)/(n-mid)+1>=m) r=--mid; else x=mid,l=++mid;
		}
		l=n>>1,r=n-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if((mid-1)/(n-mid)+1>m) y=mid,r=--mid; else l=++mid;
		}
		l=n>>1,r=n-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(mid/(n-mid)>=m-1) r=--mid; else z=mid,l=++mid;
		}
		l=n>>1,r=n-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(mid/(n-mid)>m-1) w=mid,r=--mid; else l=++mid;
		}
		printf("%d\n",y+w-x-z-2);
	 } 
	return 0;
}

```

---

## 作者：SUNCHAOYI (赞：2)

这道题给定 $n,m$，要求方程组的解的数量。若无解，则输出 $0$。

----

$\texttt{Subtask 1}$

直接两层循环，从 $1$ 至 $\max(n,m)$ 枚举 $i,j$,若满足条件，则将答案 $+1$。

$\texttt{Subtask 2}$

由方程组的 $i + j = n$ 可知 $i = n - j$，也就是说对于一个 $i$ 都会有一个对应的 $j$，因此可以化简为一层循环。

$\texttt{Subtask 3-5}$

当 $m = 1$时,$\lfloor \dfrac{i}{j} \rfloor + \lceil \dfrac{j}{i} \rceil = 1$。由题知，$i > 0,j >0$,则 $\lfloor\dfrac{i}{j}\rfloor =0,\lceil\dfrac{j}{i}\rceil =1$,即 $j > i$ 且 $j \le i$,显然此时无解。

而当 $m > n$ 或 $m ∈[n - 1,n]$ 时，同理能证得无解。

$\texttt{subtask 6}$

最后来看正解，对 $i,j$进行分类讨论。

- $i < j$，$\lfloor \dfrac{i}{j} \rfloor = 0$,即 $\lceil \dfrac{j}{i} \rceil = m$
- $i \ge j$，$\lceil \dfrac{j}{i} \rceil= 1$,即 $\lfloor \dfrac{i}{j} \rfloor = m + 1$

联立两式，于是我们就能得到两个不等式，整理可得最终答案为：
$\lceil \dfrac{n - 1}{m} \rceil - \lceil \dfrac{n - 1}{m + 1} \rceil + \lceil \dfrac{n}{m} \rceil - \lceil \dfrac{n}{m + 1} \rceil$

------------

**代码：**  
注意特判哦！
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		long long ans = 0,n,m;scanf("%lld%lld",&n,&m);
		if(m == 1)
		{
			cout<<0<<endl;
			continue;
		}
		ans = floor((n - 1) / m) - floor((n - 1) / (m + 1)) + floor(n / m) - floor(n / (m + 1));
		printf("%lld\n",ans);
	} 
	return 0;
}

```


---

## 作者：就皮这一下 (赞：1)

这道题部分分给的还是很足的……良心出题人！

接下来，就让我带领大家从 10 分暴力算法，一点点走到 100 分的满分算法~

## 10 pts 

双重循环，枚举 $i,j$，符合条件就记一次数。时间复杂度 O($Tn^2$)
``` cpp
while(T--) {
    read(n, m);
    int ans = 0;
    for (int i = 1; i<n; ++i) {
        for (int j = 1; j<n; ++j)
            if (i + j == n && i/j + (j+i-1)/i == m) ans++;
    }
    printf("%d\n",ans);
}
```

## 50 pts
注意到 $j = n-i$ ，直接计算。时间复杂度 O($Tn$)
``` cpp
while(T--) {
    read(n, m);
    int ans = 0;
    for (int i = 1; i<n; ++i) {
        int j = n-i;
        if(i/j + (j+i-1)/i == m) ans++;
    }
    printf("%d\n",ans);
}
```
## 65 pts
- Subtask 3（5 pts）：$m=1$。
- Subtask 4（5 pts）：$m>n$。
- Subtask 5（5 pts）：$m \in [n-1,n]$

可以偷个懒，直接用 50 pts 代码做个试验。证明不太困难，留给读者思考。

``` cpp
while (T--)
{
    read(n, m);
    int ans = 0;
    if (n == 1 || m == 1){
        printf("0\n");
        continue;
    }
    if (m == n - 1 || m == n){
        printf("1\n");
        continue;
    }
    if (m <= n)
        for (int i = 1; i < n; ++i){
            int j = n - i;
            if (i / j + (j + i - 1) / i == m)
                ans++;
        }
    printf("%d\n", ans);
}
```
## 100 pts

**警告：前方有大量数学推导，~~请准备好速效救心丸~~**

首先我们有：

$$
\begin{cases}
i+j = n \\
\lfloor \dfrac{i}{j} \rfloor + \lceil \dfrac{j}{i} \rceil = m
\end{cases}$$

向上取整真是讨厌，看着就烦。没关系，化成向下取整。这里正确性显然，不做赘述。

$$ \lfloor \dfrac{i}{j} \rfloor + \lfloor \dfrac{j+i-1}{i} \rfloor = m $$

很好，让我们代入$j = n-i$，稍作变形。

$$ \lfloor \dfrac{i}{n-i} \rfloor + \lfloor \dfrac{n-1}{i} \rfloor = m $$

$n-1 \geq i$，除此之外右面的式子似乎没什么特点。没关系，让我们先对左面的式子下手。

$$
\begin{cases}
\lfloor \dfrac{i}{n-i} \rfloor = 0 && n-i>i \to 2i<n \\
\lfloor \dfrac{i}{n-i} \rfloor \neq 0 && 2i\geq n \to i\geq j
\end{cases}
$$
看懵了？没关系，快结束了，我发誓。

考虑第一种情况，这种情况下只需要满足$\lfloor \dfrac{n-1}{i} \rfloor = m$ 即可。进而得：
$$mi \leq n-1 < (m+1)i$$
这就很简单了，略作处理，加上开始时的条件，得：
$$\begin{cases}
i \leq \dfrac{n-1}{m} \\\\
i < \dfrac{n}{2} \\\\
i > \dfrac{n-1}{m+1}
\end{cases}
$$
求出满足条件的整数个数即可。
落实到程序上，三行搞定。
``` cpp
Llim = (m+n)/(m+1);
Rlim = std::min((n-1)/m, (n-1)/2);
ans += (Rlim - Llim + 1);
```
回过头看第二种情况。既然$i \geq j$，那么$\lceil \dfrac{j}{i} \rceil = 1$，这种情况下只要满足$\lfloor \dfrac{i}{n-i} \rfloor = m-1$即可。

同理，得到式子：

$$ (m-1)(n-i) \leq i < m(n-1) $$

接下来的化简给出一个提醒：善用倒数。

易知
$$\dfrac{(m-1)n}{m} \leq i < \dfrac{mn}{m+1}$$

加上开始时的条件，得：
$$\begin{cases}
\dfrac{(m-1)n}{m} \leq i \\\\
i < \dfrac{mn}{m+1} \\\\
i > \dfrac{n}{2}
\end{cases}
$$

落实到程序上，三行代码：
``` cpp
Llim = std::max((n+1)/2, ((long long)(m-1)*n+m-1)/m);
Rlim = (m*n-1)/(m+1);
ans += (Rlim - Llim + 1);
```
跑过样例一了，跑过样例二了，对拍没问题了，交上去——恭喜你，AC了这道题！

完整代码奉上：
``` cpp
#include <iostream>
#include <cstdio>

template<typename Tp>
int read (Tp &x) {
    int sign = 1;
    x = 0;
    int c;
    while(!isdigit(c = getchar())) {
        if (c == '-') sign = -1;
        if (c == EOF) return EOF;
    }
    x = c-'0';
    while(isdigit(c=getchar()))
        x = x*10+c-'0';
    x *= sign;
    return 1;
}
template<typename Tp,typename... type>
inline int read (Tp& a,type&...b) {
    return read(a)+read(b...);
}
int main () {
#ifdef LOCAL
   // freopen("testdata.in","r",stdin);
#endif
    long long n, m, T;
    read(T);
    while(T--) {
        read(n, m);
        // int ans = 0;
        // if (n == 1 || m == 1) {printf("0\n");continue;}
        // if (m == n-1 || m == n) {printf("1\n");continue;}
        // if (m <= n)
        //     for (int i = 1; i<n; ++i) {
        //         int j = n-i;
        //         if(i/j + (j+i-1)/i == m) ans++;
        //     }
        // printf("%d\n",ans);

        long long Llim, Rlim, ans = 0;
        Llim = (m+n)/(m+1);
        Rlim = std::min((n-1)/m, (n-1)/2);
        ans += (Rlim - Llim + 1);
        Llim = std::max((n+1)/2, ((long long)(m-1)*n+m-1)/m);
        Rlim = (m*n-1)/(m+1);
        ans += (Rlim - Llim + 1);
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：registerGen (赞：1)

~~呵呵，对 MOer 很友好啊~~

[更好的阅读体验](https://registergen.github.io/post/solution-quark-and-equations/)

# Solution

出题人 tql！我来说一个 $O(T\log n)$ 的解法。

首先特判一下：

- 若 $m\le 1$ 或 $m>n$，则答案为 $0$。
- 若 $m=n-1$ 或 $m=n$，则答案为 $1$。

突破点：

当 $i\le j$ 时，$\left\lfloor\dfrac{i}{j}\right\rfloor+\left\lceil\dfrac{j}{i}\right\rceil=\left\lceil\dfrac{j}{i}\right\rceil$；

当 $i\ge j$ 时，$\left\lfloor\dfrac{i}{j}\right\rfloor+\left\lceil\dfrac{j}{i}\right\rceil=\left\lfloor\dfrac{i}{j}\right\rfloor+1$。

所以我们就把本题转换成了这题：

> 给定 $n,m$，求有多少组 $(i,j)$ 满足
>
> $$\begin{cases}i+j=n\\\left\lceil\dfrac{j}{i}\right\rceil=m\text{ 或 }\left\lfloor\dfrac{i}{j}\right\rfloor=m-1\end{cases}$$

很明显 $\left\lceil\dfrac{j}{i}\right\rceil$ 和 $\left\lfloor\dfrac{i}{j}\right\rfloor$ 有单调性，于是二分一（四）下就好了。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

int T,n,m;

int bin1()
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(int(ceil(1.0*mid/(n-mid)))>m)r=mid-1;
		else l=mid+1;
	}
	return r;
}

int bin2()
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(int(ceil(1.0*mid/(n-mid)))>=m)r=mid-1;
		else l=mid+1;
	}
	return r;
}

int bin3()
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(int(floor(1.0*mid/(n-mid)))>=m)r=mid-1;
		else l=mid+1;
	}
	return r;
}

int bin4()
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(int(floor(1.0*mid/(n-mid)))>=m-1)r=mid-1;
		else l=mid+1;
	}
	return r;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(m<=1||m>n){puts("0");continue;}
		if(m==n-1||m==n){puts("1");continue;}
		int ans=0;
		ans+=bin1()-bin2();
		ans+=bin3()-bin4();
		printf("%d\n",ans);
	}
	return 0;
}
```

---

