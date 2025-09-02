# Emotes

## 题目描述

xht37 正在玩一款著名的卡牌游戏。

在这个游戏中，有 $ n $ 种表情可以使用，使用第 $ i $ 种表情一次可以为对方增加 $ a_i $ 点快乐值。

你现在有 $ m $ 次使用表情的机会，每种表情可以使用零次或任意多次。但任意一款表情不能连续使用超过 $ k $ 次。

xht37 想要算出他能给对方带来的快乐值是多少。他当然知道该怎么算，但是他想考考你。

## 说明/提示

$2 \le n \le 2 \cdot 10^5,1 \le k \le m \le 2 \cdot 10^9,1 \le a_i \le 10^9$

## 样例 #1

### 输入

```
6 9 2
1 3 3 7 4 2
```

### 输出

```
54
```

## 样例 #2

### 输入

```
3 1000000000 1
1000000000 987654321 1000000000
```

### 输出

```
1000000000000000000
```

# 题解

## 作者：闫飞天jyh (赞：5)

#                			   贪心做法

### **题意**：
给出n个不同的表情及对应的开心值，求m个表情最多可以得到的开心值，  
要求同一表情不能连续出现超过k次。

## 方法：
贪心   
**sort**找出开心值第一和第二的表情   
所以最优解就是**k**个开心值最大的表情+**1**个开心值第二的表情    。  
总共循环
  $$
  \large m/(k+1) 
 $$  
 次

贴代码：
```
#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int N=20001;

int ac[N];

int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&ac[i]);
    sort(ac+1,ac+1+n);
    ll t1=ac[n],t2=ac[n-1];
    ll sum=t1*k+t2;
    ll tan=m/(k+1);//贪心
	ll xin=m%(k+1);//贪心 
    ll ans=tan*sum+xin*t1;
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：justinjia (赞：4)

这是一道比较水（你看这题难度不就是水的颜色吗）的小学奥数题（考察知识点：周期问题）。。。

[此题解在题解区域食用更佳（原因：我那个表格在博客里貌似显示不出来）](http://www.luogu.com.cn/problem/solution/CF1117B)

首先搭上框架：
```cpp
#include"stdio.h"//我习惯这么写
#include"algorithm"
using namespace std;
#define int long long//根据本题的数据范围，需要开long long
signed main(void){//signed等同于int，如果还写int main(void)的话就相当于long long main()，会CE
    int n,m,k,a[200000];
    scanf("%lld%lld%lld",&n,&m,&k);//别忘了我们这是long long，我曾经因为占位符写错而被卡了N次
    for(int i=0;i<n;i++)
        scanf("%lld",&a[i]);
    sort(a,a+n);
```
接下来，你可能会用循环来累加每次选择的表情，但是这样会$\colorbox{darkblue}{\color{white}TLE}$。

那该怎么办呢？

就像我第一句话所说的，这题就是个小学奥数题，一个简单的周期问题。最优方案如下表：

|使用的第几个表情|表情编号（从$0$开始，排序后）|
|-|-|
|$1$|$n-1$|
|$2$|$n-1$|
|$......$|$......$|
|$k$|$n-1$|
|$k+1$|$n-2$|
|周期结束分割线|$-----------$|
|$k+2$|$n-1$|
|$k+3$|$n-1$|
|$......$|$......$|
|$2k$|$n-1$|
|$2k+1$|$n-2$|
|周期结束分割线|$-----------$|
|$2k+2$|$n-1$|
|$......$|$......$|
|$m$|$n-1$（如果$m\bmod k=0$，则为$n-2$）|
所以，我们要定义一个变量，统计最后结果：
```cpp
    int ans=0;
```
后面要加上好多个数，我就分开写，这样看的更清楚：
```cpp
    ans+=m/(k+1)*(a[n-1]*k+a[n-2]);
```
其中，`m/(k+1)`为**完整**周期个数，`a[n-1]*k`为周期中第$1$~$k$个表情快乐值的总和，`a[n-2]`就是周期中第$k+1$个表情的快乐值。

然后处理不完整周期：
```cpp
    ans+=m%(k+1)*a[n-1];
```
`m%(k+1)`就是不完整周期数的个数，剩下的应该不用我解释了吧。

最后：
```cpp
    printf("%lld",ans);//再次提醒我们这是long long
    return 0;
}
```
放上完整代码：
```cpp
#include"stdio.h"
#include"algorithm"
using namespace std;
#define int long long
signed main(void){
    int n,m,k,a[200000],cnt=0;
    int ans=0;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=0;i<n;i++)
        scanf("%lld",&a[i]);
    sort(a,a+n);
    ans+=m/(k+1)*(a[n-1]*k+a[n-2])+m%(k+1)*a[n-1];
    printf("%lld",ans);
    return 0;
}
```
最后说两件事：

第一件事是给管理们说的：**这是蒟蒻的第一篇题解，求过！**

第二件事是给过路的大佬们说的：**这是蒟蒻的第一篇题解，可能会存在不少错误，欢迎大佬来喷！**

---

## 作者：SpectatorX (赞：2)

~~这题难度$\color{SkyBlue}\text{提高+/省选-}$？？？~~

言归正传，本题正解应该是**贪心**。

我们首先找到$a$中的**最大值**$maxn_1$和次大值$maxn_2$，然后每$k+1$个表情取到最大快乐值的方案即为
$$\begin{matrix}\underbrace{maxn_1+maxn_1+\cdots+maxn_1}\\k\end{matrix}+maxn_2$$

最后$m$中余下的部分全取$maxn_1$即可。

$Code$:

```cpp
#include<bits/stdc++.h>
#define int long long//long long！！
using namespace std;
int n,m,k,a,ans,maxn,mxn;//maxn 最大 mxn 次小
inline void read(int &x)
{
	x=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
inline void print(int x)
{
	if(x>9) print(x/10);
	putchar(x%10+48);
}
signed main()
{
	read(n);read(m);read(k);
	for(register int i=1;i<=n;++i)
	{
		read(a);
		if(a>=maxn) mxn=maxn,maxn=a;
		if(a>mxn&&a<maxn) mxn=a;
	}
	ans=maxn*k+mxn;
	ans=ans*(m/(k+1))+maxn*(m%(k+1));
	print(ans);
}
```
成功达到最优解~~page2~~rk1。

---

## 作者：冰糖鸽子 (赞：2)

还是没有打破写了题解的蓝题都是一次过的魔咒 /cy

----

### 思路

显然（如果这两个字冒犯您了我很抱歉），应该尽量多用快乐值最大的表情，然后再用一个快乐值次大的表情。

也就是说是有一个周期的，如下（ $k=4,m=17$ ）（最大值用 1 表示，次大值用 2 表示）：

| 第几个表情 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|  | 1 | 1 | 1 | 1 | 2 | 1 | 1 | 1 | 1 | 2 | 1 | 1 | 1 | 1 | 2 | 1 | 1 |

很明显有一个长度为 $k+1$ 的周期，有了周期剩下的就是小学数学了。

### 代码

最大值用一个排序完美解决

```cpp

// Problem: CF1117B Emotes
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1117B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,ans,a[300000];
int m_st,m_rd;
signed main()
{
	cin>>n>>m>>k;
	k++;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	m_rd=a[n-1];
	m_st=a[n];
	if(m%k==0)
	{
		ans=(m/k)*m_rd;
		ans+=(m-m/k)*m_st;	
	}
	else
	{
		int fff=m%k;
		m-=fff;
		ans=(m/k)*m_rd;
		ans+=(m-m/k)*m_st;	
		ans+=fff*m_st;
	}
	cout<<ans;
	return 0;
}
```

----

祝大家CSP2020：

```cpp
while(1)
{
	rp++;
	score++;
}
```

---

## 作者：是个妹子啦 (赞：2)

不用sort跑的飞快~~rank1~~

```cpp
#include<iostream>
using namespace std;
int n,m,k,x;
inline void read(int &e){
	e = 0;char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) e = (e<<3)+(e<<1)+(c^48),c=getchar();
}
inline void write(long long x){
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main(){
	int a = 0,b = 0;
	read(n); read(m); read(k);
	for(int i=1;i<=n;++i){
	 	read(x);
	  	if(x>=a) b=a,a=x;
	  	else if(x>=b) b=x; 
	} 
	long long sum = m / (k+1),mod = m % (k+1);
	write(sum * (1ll * a * k + b) + mod * a);
	return 0; 
}
```

---

## 作者：xyf007 (赞：1)

# 不断地取最大值，再取一次最小值
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,m,k,a[200001];
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1,cmp);
	long long sum=m/(k+1),mod=m%(k+1);//贪心
	printf("%lld",sum*(a[1]*k+a[2])+mod*a[1]);
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

蓝->黄

果然是恶评

这题应该评红

------------

看题。

```
你现在有 m 次使用表情的机会，每种表情可以使用零次或任意多次。但任意一款表情不能连续使用超过 k 次。

输出一个整数，即 xht37 能给对方带来的最大快乐值。
```

不能连续使用超过 k 次，但可以分开来使用。

那么一个表情最多使用次数就是 $m/(k+1)*k+m\%(k+1)$ 次（~~想一想，为什么）~~

如果要求快乐值最大，那么增加快乐值最大的表情就应该用最多次。

那么柿子就变成了$m/(k+1)*k*max+m\%(k+1)*max$

那么剩下的表情怎么办呢?

肯定是用增加快乐值第二大的表情。

如果用不是快乐值第二大的表情，那么用快乐值第二大的表情肯定能带来更高的快乐值。

快乐值第二大的表情能带来的快乐值为$m/(k+1)*max_2$，其中 $max_2$ 代表快乐值第二大的表情。

两个柿子一加就是最终的答案。

$m/(k+1)*k*max+m\%(k+1)*max+m/(k+1)*max_2$

稍微化简一下得

$m/(k+1)*(k*max+max_2)+m\%(k+1)*max$

------------

只是取前二大的值，没有必要排序，复杂度能降到$O(n)$

程序里使用两个变量$ max1,max2$ 存储第一、第二大的数。~~也可以维护一个只有两个节点的大根堆。~~

十年OI一场空。

```cpp
//CF1117B
#include <cstdio>
using namespace std;

int main(){
	long long n,m,k,cf1117b,max1=0,max2=0;
	scanf("%lld %lld %lld",&n,&m,&k);
	for(long long i=0; i<n; ++i){
		scanf("%lld",&cf1117b);
		if(cf1117b>max1) max2=max1,max1=cf1117b;
		else if(cf1117b>max2) max2=cf1117b;
	}
	printf("%lld",m/(k+1)*(max1*k+max2)+m%(k+1)*max1);
	return 0;
} 
```


---

## 作者：Unordered_OIer (赞：0)

# CF1117B 题解
真就水蓝？ /jk /jk

## 题意
给定 $n,m,k$ 与 $a_1 \sim a_n$，要求选择 $m$ 个 $a_i$ 出来，可以重复但不能连续超过 $k$ 次选择同一个 $a_i$，求在这种情况下这 $m$ 个 $a_i$ 的和的最大值。

## 题解
首先如果没有**不得连续超过 $k$ 次**这个条件的话，我们很容易看出来直接输出 $m \times \max\limits_{i=1}^na_i$ 即可。

再考虑**不得连续超过 $k$ 次**这个条件，我们先设 $x=\max\limits_{i=1}^na_i$，则为了使收益最大，我们要最大化 $x$ 的取值次数。也就是说，当 $x$ 取满了 $k$ 次，我们就使用次大值，设为 $y$，来进行一次替补即可。

于是原问题的答案就可以表示出来了：
$$ans=(kx+y) \times \left\lfloor \dfrac{m}{k+1} \right\rfloor+m\bmod (k+1) \times x$$

复杂度 $\mathcal O(n)$ 或 $\mathcal O(1)$，对于这道题的极水数据范围来说 $\mathcal O(n)$ 就可以了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,a[200005];
#undef int
int main(){
#define int long long
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    printf("%lld\n",(k*a[n]+a[n-1])*(m/(k+1))+m%(k+1)*a[n]);
    return 0;
}
```

---

## 作者：WanderingTrader (赞：0)

简单贪心题
### 题目分析
>每种表情可以使用零次或任意多次

因此其实我们的目标就是尽可能多的拿数列中最大的数。

>任意一款表情不能**连续**使用超过 $k$ 次。

注意到“连续”，因此我们将连续 $k$ 个最大值和 $1$ 个次大值 组成一个周期，那么本题就变成了一个周期问题。

令最大值 $A$，次大值 $B$，那么答案即为 $(Ak+B)\left\lfloor\dfrac m{k+1}\right\rfloor+A\times m\bmod (k+1)$.

由于 $n$ 不是很大，求次大值直接用`sort`即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e5+5;
LL a[maxn];
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i) scanf("%lld",a+i);
	sort(a+1,a+1+n,greater<LL>());
	printf("%lld\n",(k*a[1]+a[2])*(m/(k+1))+m%(k+1)*a[1]);
	return 0;
}
```
非常简单，注意是从大到小排序，可以用`greater<>()`。

$$\texttt{The End.}$$

---

## 作者：零殇 (赞：0)

#### 题意
你有$n$个数据，有$m$个机会，一个数据不能连续选择超过$k$次，求你能取得的和最大值。

#### 思路

显然，既然每个数据没有总量上的次数限制，也就是说，我们尽量选择最大的数据。

当我们选择了$k$次最大值的时候，就不能再选了，这个时候，为了保证和最大，我们选择次大值分隔出这一段，然后再重复同样的操作。直到$m$次机会用完。此时，一段长度即为$k+1$。

我们用$num$记录分成几段，即：

```
num=m/(k+1);
```

那么，我们选择的最大值个数即为$(num*k+$余数 $)$，次大值个数即为$num$。

我们要的和就是$(num*k+$余数$)*$ 最大值 $+$ $num$ *次大值。

至于最大值和次大值，我们当然还是用无敌的$sort$寻找啦！

上代码：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iomanip>
#include<cmath>
using namespace std;
int n,m,k;
long long a[200001],ans;
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a,a+n+1);
	int num=m/(k+1);
	m-=num*(k+1);//余数
	cout<<(m+num*k)*a[n]+num*a[n-1];
	return 0;
}
```
完结撒花~


---

