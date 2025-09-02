# The Wall

## 题目描述

Iahub and his friend Floyd have started painting a wall. Iahub is painting the wall red and Floyd is painting it pink. You can consider the wall being made of a very large number of bricks, numbered $ 1 $ , $ 2 $ , $ 3 $ and so on.

Iahub has the following scheme of painting: he skips $ x-1 $ consecutive bricks, then he paints the $ x $ -th one. That is, he'll paint bricks $ x $ , $ 2·x $ , $ 3·x $ and so on red. Similarly, Floyd skips $ y-1 $ consecutive bricks, then he paints the $ y $ -th one. Hence he'll paint bricks $ y $ , $ 2·y $ , $ 3·y $ and so on pink.

After painting the wall all day, the boys observed that some bricks are painted both red and pink. Iahub has a lucky number $ a $ and Floyd has a lucky number $ b $ . Boys wonder how many bricks numbered no less than $ a $ and no greater than $ b $ are painted both red and pink. This is exactly your task: compute and print the answer to the question.

## 说明/提示

Let's look at the bricks from $ a $ to $ b $ $ (a=6,b=18) $ . The bricks colored in red are numbered 6, 8, 10, 12, 14, 16, 18. The bricks colored in pink are numbered 6, 9, 12, 15, 18. The bricks colored in both red and pink are numbered with 6, 12 and 18.

## 样例 #1

### 输入

```
2 3 6 18
```

### 输出

```
3```

# 题解

## 作者：Quit (赞：4)

### 朋友们好啊，这是本蒟蒻的第二篇题解。

------------

**我们来看题目：**

题目很好理解，先求$x$,$y$的最小公倍数，记为$lcm$，然后再在$[a,b]$的范围内看有多少个$lcm$的倍数。

### 那么问题来了：怎么求解$lcm$的值呢？

**（敲黑板）** 这里有个公式：

## $lcm(x,y)=x*y/gcd(x,y)$

$gcd(x,y)$表示$x$,$y$的最大公因数。

 _那么最大公因数怎么求呢？_ 

### 辗转相除法！

辗转相除法可以用递归来实现！


```cpp
int gcd(int x,int y){  
	if(x%y==0) return y;
	return gcd(y,x%y);
}
//gcd函数是求解x,y最大公因数的函数
```

那么后面就很容易了：

### 方法1：暴力枚举（$TLE$ 会超时）

因为  $a$ , $b$ $∈$ [$1$ , $2*10^{9}$]

于是我注意到了什么...

#### 顺手开了一个$long$ $long$ ！

为了方便，我们可以这么做：
```cpp
typedef long long ll;
```

### 方法2：数学分析（可以$AC$哦~）
大致思路是$a$ , $b$ 分别除以$lcm$的商,分别记为$l$ , $r$，最后输出$r-l+1$。其中要注意一些细节即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll x,ll y){ 
	if(x%y==0) return y;
	return gcd(y,x%y);
}
int main(){
	ll x,y,a,b,l,r;
	cin>>x>>y>>a>>b;
	ll lcm=x*y/gcd(x,y);//表示最小公倍数
	if(a%lcm==0) l=a/lcm;
	else l=a/lcm+1;
	r=b/lcm;	
	cout<<r-l+1<<endl;
	return 0;
}
```


------------
## 谢谢朋友们！

---

## 作者：BetaCutS (赞：3)

下面的都是小学知识！！！

引理 $1$：$[x,y]=xy\div(x,y)$。

引理 $2$：$x,y$ 的公倍数是 $[x,y]$ 的倍数。

我们就可以先把 $(x,y)$ 求出来，再用引理 $1$ 把 $[x,y]$ 求出来。

设 $z=[x,y]$。

不大于 $b$ 的能被 $z$ 整除的数有 $\left\lfloor\dfrac{b}{z}\right\rfloor$ 个；小于 $a$，也就是不大于 $a-1$ 能被 $z$ 整除的数有 $\left\lfloor\dfrac{a-1}{z}\right\rfloor$ 个。

$\left\lfloor\dfrac{b}{z}\right\rfloor$ 个数中包含 $\left\lfloor\dfrac{a-1}{z}\right\rfloor$ 个数，所以根据容斥原理，从 $\left\lfloor\dfrac{b}{z}\right\rfloor$ 中把 $\left\lfloor\dfrac{a-1}{z}\right\rfloor$ 个数去掉就是答案。

## 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
signed main()
{
	int x=read(),y=read(),a=read(),b=read(),z=x*y/__gcd(x,y);
	printf("%d",b/z-(a-1)/z);
	return 0;
}

```


---

## 作者：Colead (赞：1)

# CF340A

一道很有意思的题目。

就是求两数之间有几个另外两数的最小公倍数的倍数。

首先介绍一个STL：

## __gcd

这个玩意儿可以免去我们写递归的繁杂，直接求出两数的最大公因数。是个非常方便的东西。

但是这个东西有一个很大的缺点：

## CSP/NOIP当中不能用！

当然我们在普通情况下还是可以用的（嘻嘻）,毕竟最大公因数的模板大家应该都有。

但这题求的不是gcd，是lcm！

于是又用到了另外一个性质：

## a*b=lcm(a,b)*gcd(a,b)

于是就有了：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long x,y,a,b;
	cin>>x>>y>>a>>b;
	long long gg=__gcd(x,y);
	gg=x*y/gg;
	int st=a;
	for(long long i=a;i%gg!=0;i++)
	{
	   st=i;
	}
	if(b==st)cout<<"1"<<endl;
	else if(b>st)
	{
		cout<<(b-st)/gg+1<<endl;
	}
	else
	{
		cout<<"0"<<endl;
	}
	return 0;
}
```

注意不能一个个枚举，不然会TLE！

好啦，讲完啦，我们下次再见！！！

---

## 作者：Arvin2018 (赞：1)

题目大意：

给定x, y, a, b, 求在a到b之间（包含a和b）有多少个x和y的最小公倍数

思路：先用辗转相除法求出最小公倍数，在求其在a和b之间的个数

~~盗来一张辗转相除法的图~~![辗转相除法](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1561375712&di=398ef097cc94d7584217cc17afd178a9&imgtype=jpg&er=1&src=http%3A%2F%2Fs7.sinaimg.cn%2Fmw690%2F002lCBr9zy6SbimFYtUc6%26amp%3B690)
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int __lcm(long long x, long long y){//最小公倍数
	int ret = 1, gcd = __gcd(x, y);//用万能头里的函数求出最大公约数
	if(gcd == 1){//如果x，y互质，它们的最小公倍数 = xy
		return x * y;
	}
	if(x == y){//如果x = y，返回x（或y）
		return x;
	}
	if(x % y == 0 || y % x == 0){//如果x是y的倍数或y是x的倍数，返回大的值
		return (x > y ? x : y);
	}
	//辗转相除法
	ret *= gcd;
	x /= gcd;
	y /= gcd;
	ret *= x;
	ret *= y;
	return ret;
}

int main(){
	long long x, y, a, b;
	cin >> x >> y >> a >> b;
	long long lcm = __lcm(x, y);
//	cerr << lcm;
	if(lcm > b){//如果最小公倍数大于b，则a~b间不含lcm
		cout << 0;
		return 0;
	}
	int c = a;
	for(;; c++){//寻找lcm第一次在a~b中出现的位置
		if(c % lcm == 0){
			break;
		}
	}
	if(c <= b){
		cout << (b - c)/lcm + 1;//+1是因为此处没有算上c
	}
	else{
		//如果c > b，输出0
		cout << 0;
	}
	return 0;
}

```

---

## 作者：Qerucy (赞：0)

一道小学数学题。

类似于前缀和的思想，用 $a$ 与 $b$ 分别除以 $\operatorname {lcm} (x,y)$ ，再拿它们算出的结果分别相减，得到的差再加一便是答案。

公式：

$$ \operatorname {lcm} (x,y) = \frac { x \times y } { \gcd (x,y) } $$

代码：

```
#include<cstdio>
#include<algorithm>

#define int long long//保险起见，开long long

using namespace std;

int gcd(int x,int y){return !(x%y)?y:gcd(y,x%y);}

int lcm(int x,int y){return x*y/gcd(x,y);}

int x,y,a,b;

signed main(){
	scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
	printf("%lld",b/lcm(x,y)-a/lcm(x,y)+1);
	return 0;
}
```


---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF340A)

# 题意简述

给定 $x,y,a,b$，求在 $a$ 到 $b$ 之间（包含 $a$ 和 $b$）有多少个 $x$ 和 $y$ 的公倍数。

# Solution

一道简单练手题。

小学学过，两个数的公倍数都是它们的最小公倍数的倍数。

所以，我们首先要求出 $x$ 和 $y$ 的最小公倍数，即 $\operatorname{lcm} (x,y)$。

它的求法很简单，$\operatorname{lcm} (x,y)=\dfrac{xy}{\gcd(x,y)}$。

而 $\gcd(x,y)$ 可以用辗转相除法实现。

```cpp
int gcd(int x, int y) {//辗转相除
	if(x%y == 0) return y;
	return gcd(y, x%y);
}
```

最后，用 $a$，$b$ 分别除以 $\operatorname{lcm}(x,y)$，两个商的差加一就是最终结果。

但是，$1 \leq a,b \leq 2 \times 10^9$，**为了保险**，还是开一下 `long long`。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long gcd(long long x, long long y) {
	if(x%y == 0) return y;
	return gcd(y, x%y);
}
long long lcm(long long x, long long y) {
	return x*y/gcd(x,y);
}
int main() {
	long long x, y, a, b;
	scanf("%lld%lld%lld%lld", &x, &y, &a, &b);
	long long sum, cnt;
	sum = a/lcm(x,y);
	cnt = b/lcm(x,y);
	printf("%lld", cnt-sum+1);
	return 0;
}
```

By 2022.6.28 蒟蒻的第十六篇题解

---

## 作者：力巴尔 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF340A)

要求在 $a$ 到 $b$ 之间有多少个 $x$，$y$ 的公倍数，首先要求出 $\operatorname{lcm}(x, y)$，而 $\operatorname{lcm}(x, y) = \dfrac{x*y}{\gcd(x, y)}$，但这道题的数据范围很大，所以求最大公因数要用辗转相除法。知道了 $\operatorname{lcm}(x, y)$，答案即为 $\dfrac{b}{\operatorname{lcm}(x, y)} - \dfrac{a - 1}{\operatorname{lcm}(x, y)}$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b)
{
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}
int main()
{
    long long x, y, a, b;
    cin>>x>>y>>a>>b;
    cout<<b * gcd(x, y) / x / y - (a - 1) * gcd(x, y) / x / y;
}
```


---

## 作者：Firstly (赞：0)

这是一道数学问题。

## **题目思路：**
------------
我们先求出 $x$ 和 $y$ 的最小公倍数。然后将 $a$ 和 $b$ 变为离它们最近的在它们范围之内的是 $x$ 和 $y$ 的公倍数的数，随后求出这两个数分别除以 $\operatorname{lcm}(x,y)$，得到它们在 $x$ 和 $y$ 的公倍数中的序号（从小到大编号），然后直接输出 $b-a+1$ 即可。

求最大公因数和最小公倍数的方法：

$\operatorname{gcd}(a,b)$ 可以用算法库里的一个函数，然而在竞赛中不能使用。所以我们还是用传统的辗转相除法。


求最小公倍数，我们需要运用的是：$x\times y=\operatorname{gcd}(x,y)\times \operatorname{lcm}(x,y)$。

即，$\operatorname{lcm}(x,y)=x\times y\div \operatorname{gcd}(x,y)$。

那么，将知识讲解完之后，上代码。

## **Code：**
------------
```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗
using namespace std;
int x,y,a,b;
inline int gcd(int a,int b){//辗转相除法
	if(b==0)return a;
	return gcd(b,a%b);
}
signed main(){
	scanf("%d%d%d%d",&x,&y,&a,&b);
	if(y>x)swap(x,y);//在我们设定的辗转相除法求最大公因数的函数中，x 必须大于 y，所以如果 y 大于 x，则交换两数。
	int lcm=x*y/gcd(x,y);//求最小公倍数
	for(int i=a;;i++)
		if(i%lcm==0){a=i;break;}
	for(int i=b;;i--)
		if(i%lcm==0){b=i;break;}
	a/=lcm;b/=lcm;
	printf("%lld",b-a+1);
	return 0;
}
```


---

## 作者：Misaka_Mik0t0 (赞：0)

如果一个数同时是 $x$ 与 $y$ 的倍数，那么它就是 $\operatorname{lcm}(x,y)$ 的倍数。我们需要先求出 $\operatorname{lcm}(x,y)$。

首先我们先来了解一下 $\operatorname{lcm}$（最小公倍数）与 $\gcd$（最大公因数）。

对于 $x$ 与 $y$，$\operatorname{lcm}(x,y)=\dfrac{x\times y}{\gcd(x,y)}$。

证明：

将 $x$ 与 $y$ 质因数分解。

$x=p1_1^{q1_1}\times p1_2^{q1_2} \times \dots \times p1_n^{q1_n}$

$y=p2_1^{q2_1}\times p2_2^{q2_2} \times \dots \times p2_m^{q2_m}$

对于每个 $p1$、$p2$ 中的质数 $s$ ，设 $x$ 中的指数为 $g1$，$y$ 中的指数为 $g2$，则 $\operatorname{lcm}(x,y)$ 中 $s$ 的指数为 $\max(g1,g2)$，$\gcd(x,y)$ 中 $s$ 的指数为 $\min(g1,g2)$，乘积的指数为 $\min(g1,g2)+\max(g1,g2)=g1+g2$。

所以乘积为 $x\times y$。

证毕。

所以为了求出 $\operatorname{lcm}(x,y)$，只需求出 $\gcd(x,y)$。

求出 $\gcd(x,y)$ 的方法：

不妨设 $x\ge y$，根据 $\gcd(x,y)=\gcd(y,x\bmod y)$ 递归。

出口为 $y=0$，此时 $\gcd(x,y)=x$。

最后，问题简化成了求出 $[a,b]$ 内 $c$ 的倍数（$c=\operatorname{lcm}(x,y)$）。即 $[1,b]$ 中 $c$ 的倍数 $-$ $[1,a-1]$ 中 $c$ 的倍数。即 $\left\lfloor(a-1)/c\right\rfloor-\left\lfloor b/c\right\rfloor$。

主体代码：
```cpp
int gcd(int i,int j){//i>=j
	if(j==0)return i;
	return gcd(j,i%j);
} 
```
```cpp
int main(){
	if(x>y)lcm=gcd(x,y);
	else lcm=gcd(y,x);
	lcm=x*y/lcm;
	a=(a-1)/lcm;b=b/lcm;
	printf("%d",b-a);
	return 0;
}
```

---

## 作者：zzr1 (赞：0)



------------
#### 题目简述
求 $a$ , $b$ 间，有几个 $x$ , $y$ 的公倍数。



------------
#### 题目做法
这是一道不能暴力的题，需要找技巧。  



暴力必定 TLE  ,因为数据已经达到了 $10^9$ 。  

所以我们需要用到辗转相除法：

```cpp
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;//提高效率
}
```



但这样的时间复杂度最少也要 $O(n^2)$ 。



所以我们就需要找规律了。

我们需要先求出 $lcm(a,b)$ 来研究这道题的 $O(n)$ 解法。


通过数学的研究可以发现，公式为 $b/k-(a-1)÷lcm(x,y)$ 。

$lcm(x,y)=x*y÷gcd(x,y)$ 。


###### 注意细节。
------------

在这里提供一个函数	：  __gcd(a,b) 

这个函数是用来求两个数的最大公约数的。

这个函数目前是只有 c++11 以上的版本才能使用的。

并且大赛中不可使用。







------------

AC 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long m,n,p,ans;
long long gcd(long long a,long long b){//gcd最大公因数
    if(a%b==0)return b;
    return gcd(b,a%b);
}
int main(){
	long long a,b,x,y;
    cin>>x>>y>>a>>b;
    long long sum=gcd(x,y);
    long long k=x*y/gcd(x,y);//最大公倍数
    cout<<b/k-(a-1)/k;//公式
    return 0;
}
```


------------

~~谢谢观看。~~

---

