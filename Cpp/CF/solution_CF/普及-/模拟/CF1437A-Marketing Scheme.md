# Marketing Scheme

## 题目描述

You got a job as a marketer in a pet shop, and your current task is to boost sales of cat food. One of the strategies is to sell cans of food in packs with discounts.

Suppose you decided to sell packs with $ a $ cans in a pack with a discount and some customer wants to buy $ x $ cans of cat food. Then he follows a greedy strategy:

- he buys $ \left\lfloor \frac{x}{a} \right\rfloor $ packs with a discount;
- then he wants to buy the remaining $ (x \bmod a) $ cans one by one.

 $ \left\lfloor \frac{x}{a} \right\rfloor $ is $ x $ divided by $ a $ rounded down, $ x \bmod a $ is the remainer of $ x $ divided by $ a $ .

But customers are greedy in general, so if the customer wants to buy $ (x \bmod a) $ cans one by one and it happens that $ (x \bmod a) \ge \frac{a}{2} $ he decides to buy the whole pack of $ a $ cans (instead of buying $ (x \bmod a) $ cans). It makes you, as a marketer, happy since the customer bought more than he wanted initially.

You know that each of the customers that come to your shop can buy any number of cans from $ l $ to $ r $ inclusive. Can you choose such size of pack $ a $ that each customer buys more cans than they wanted initially?

## 说明/提示

In the first test case, you can take, for example, $ a = 5 $ as the size of the pack. Then if a customer wants to buy $ 3 $ cans, he'll buy $ 5 $ instead ( $ 3 \bmod 5 = 3 $ , $ \frac{5}{2} = 2.5 $ ). The one who wants $ 4 $ cans will also buy $ 5 $ cans.

In the second test case, there is no way to choose $ a $ .

In the third test case, you can take, for example, $ a = 80 $ .

## 样例 #1

### 输入

```
3
3 4
1 2
120 150```

### 输出

```
YES
NO
YES```

# 题解

## 作者：Eason_AC (赞：3)

## Content
有 $t$ 组询问，每组询问给定两个整数 $l,r$，问是否存在一个 $a$，使得 $\forall x\in[l,r]$，都有 $x\mod a\geqslant\dfrac{a}{2}$。

**数据范围：$1\leqslant t\leqslant 1000,1\leqslant l,r\leqslant 10^9$。**
## Solution
我们可以让 $a=2x$，这样就很容易使得 $x\mod a\geqslant \dfrac{a}{2}$，因此我们只需要看是否有 $l\times 2\leqslant r$ 即可，如果这个条件成立的话，那么后面必会有一部分不能够满足 $x\mod a\geqslant \dfrac{a}{2}$，因为到某一个点肯定会有 $x\mod a=0$，然后之后就会有一部分 $x\mod a<\dfrac{a}{2}$ 了。而且，我们很容易证明，没有办法能够使得 $a>2x$，否则肯定不会满足条件。所以，这样的话就不能够满足题目所给的条件了。

如果能够想清楚的话，这道题目还是挺简单的。
## Code
```cpp
int t, l, r;
     
int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(t);
	while(t--) {
		getint(l), getint(r);
		if(l * 2 <= r) puts("NO"); else puts("YES");
	}
	return 0;
}
```

---

## 作者：帝千秋丶梦尘 (赞：2)

[童鞋们先看题目吖](https://www.luogu.com.cn/problem/CF1437A)

题意翻译已经十分清楚了，但童鞋们应该是不懂翻译中的符号

# ∃：存在

即对于条件，范围内至少有一个满足条件的数。

对于∃x（实数），使得x=x*x，这显然是一个真命题

对于∃x（实数），使得x>(x+1)，这显示是假命题

------------


# ∀：任意

即对于条件，范围内的所有数都要满足条件。

对于∀x（实数），使得x>（x-1），这显然是一个真命题。

对于∀x（实数），使得x=x*x，这显然就是个假命题。


------------


# ∈：属于

A∈B，即对于集合A中任意一个元素，都在B中找得到。

如A={1}，B={0,1,2,3} 那么A∈B


------------


所以，懂我意思哇？

翻译一下题面：对于在l~r之间的任何一个数，能否找到一个值x，

使得i%x>x/2

so,这道题是不是就简单起来了？

其实此题找规律就欧克（~~因为A不会太难的~~）：

3 4 YES

1 2 NO

120 150 YES

~~so,只要你有足够的应试技巧，就能看出，哦，好像看不出啥~~

那么，我们要高呼：暴力大法好。

#一个小技巧：

切记，只要你不能保证100%能A的，就给我打个暴力程序对拍。
							
                       —————by wtd（懂得都懂）

打个暴力找规律吧，QwQ。

最后能找的出来，其实 l*2＞r，就能使x存在，即找到符合条件的x。

so,up代码：

```
#include<bits/stdc++.h>
#define ri register
using namespace std;
int n,l,r;
int main(void)
{
	scanf("%d",&n);
	for(ri int i(1);i<=n;++i)
	{
		scanf("%d%d",&l,&r);
		if(l*2>r)
		{
			puts("YES");
		}
		else puts("NO");
	}
	return 0;
}//感jo也没什么好将的了，只要理解题意，找到规律，肯定能A。
```
# 各位看官走好，( ^_^ )/~~拜拜

---

## 作者：_ajthreac_ (赞：2)

### 0.Description
给定一个区间，求一个 $a$ 使得区间内任一数 $i$ 均满足 $i\mod a\ge\frac a2$ 。
### 1.Solution
考虑 $a$ 与区间端点 $l,r$ 的关系。     
对于 $l$ ，它一定满足 $l\ge\frac a2$ ，否则 $l$ 到 $\frac a2$ 这一段不满足题意。             
对于 $r$ ，它一定满足 $r<a$ ，否则 $a$ 到 $\min\{a+\frac a2,r\}$ 这一段不满足题意。
### 2.Code
[开头代码](https://www.cnblogs.com/juruoajh/p/12632444.html)
```cpp
int n,l,r;
int main(){
	Read(n);
	while(n--){
		Read(l),Read(r);
		if(l*2>r)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：itisover (赞：2)

题目大意：

给你一个区间 $[l,r]$，求是否有一个数 $a$，使得这个 $a$ 对于区间内任意的数 $x$，都要满足 $x \bmod a>=\frac{a}{2}$，有就输出"YES"，否则输出"NO"。

考虑怎么做：（感谢[大佬](https://www.luogu.com.cn/user/224436)的给出的证明）

分类讨论：

①当 $a>l$ 时，$l\bmod a=l$ 则如果有解 $l\bmod a=l>=\frac{a}{2}$ 即 $a<=2l$。

若$r>=2l$，则在$[l,2l]$之间，一定有 $x\bmod a=0<\frac{a}{2}$。

若 $r<2l$，则 $a$ 取 $2l$ 时一定有 $x\bmod a>=\frac{a}{2}$。

所以当 $r<2l$ 时，一定有解。

②当 $a=l$ 时，显而易见，一定有 $x\bmod a=0<\frac{a}{2}$

③当 $l<a<r$ 时，且 $r>=2l$ 时，原不等式可以表示为 $x-ka>=\frac{a}{2}\texttt{(k为x/a的商且k>=1})$

当 $x=l$ 时，$l-ka>=\frac{a}{2}$，则 $l<(k+1)a$，$2l>=2ka+a$ 即 $r>=(2k+1)a$。所以 $l<(k+1)a<r$ 即 $(k+1)a\in[l,r]$，则一定有 $(k+1)a\bmod a=0<\frac{a}{2}$。

综上，当 $r>=2l$ 时无解，当 $r<2l$ 时一定有解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int T,l,r;
int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&l,&r);
    if(r<(l<<1)) printf("%s\n","YES");
    else printf("%s\n","NO");
  }
  return 0;
}
```


---

## 作者：vеctorwyx (赞：2)

### 题目大意：

（背景略~~~）

给定$l,r$，求一个$a$使得任意$x(l\le x\le r)$满足$(x\mod a)\ge \dfrac {a}{2}$。


### 关于 $mod $:

两个数$x,y$满足$x-y=1$，则对于任意整数$z$（$z>1$），x，y总满足

$(x\mod z)-(y\mod z)=1$，

或 $(x\mod z)=0,(y\mod z)=z-1$。

那么我们可以得出结论（其实手算一下更快）：

连续$b$个数$\mod a$（$a<b$）的结果组成的序列一定包含$0$到$a-1$每个数至少一次。

所以本题中的$a$若要满足条件，必须要保证$l\ge \dfrac {a}{2} $（否则会存在$(x\mod a)<\dfrac {a}{2}$）且$a>r$（否则会存在$x=a$造成$(x\mod a)=0$）。

于是就可以根据以上结论写代码：

```
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*y;
}
int t,l,r;
int main()
{
	t=read();
	while(t--)
	{
		l=read(),r=read();
		if(l*2>r)
		cout<<"YES\n";
		else//不存在a
		cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：幼儿园第一名 (赞：2)

#### 思路：
每场CFdiv2的A基本都能根据样例找规律。

当$l=1,r=2$时，$r/2=l$，输出$NO$；

当$l=120,r=150$时，$r/2<l$，输出$YES$；

当$l=3,r=4$时，$r/2<l$，输出$YES$；

大家估计都能看出来了，当$r/2<l$时，输出$YES$，否则输出$NO$。

#### Code:
```
#include<iostream>

using namespace std;

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int l,r;
		cin>>l>>r;
		if(r/2<l)
			puts("YES");
		else	
			puts("NO");
	}
	return 0;
}
```

---

## 作者：—维尼— (赞：1)

## 题目大意

在给定的$\large l-r$区间是否有一个数$\large x$（$x$可以不在区间里）使区间内任意一个数都满足$\large i\mod a\ge\frac{a}{2}$

## 题目思路

**$l$和$r$的位置关系分这两种情况：**

![](https://pic.downk.cc/item/5f9a6ac31cd1bbb86bc72dd8.png)

下面结论推理过程需要边看边脑补 x是如何满足或不满足的

* 如图一

如果$l\times2\le r$

那么1 —— $l\times2$这个区间不符合题意,因为在这里选择的$x$有$\large i\mod a>\frac{a}{2}$的情况

$l\times2$——max更不用说了，所以整段都没有符合条件的$x$

* 如图二

如果$l\times2> r$

那么$1$——$r$这个区间（左闭右开）不符合题意，理由同上

而如果把$x$设置到$r$外边，那么就满足在范围内的所有$\large i\mod a\ge\frac{a}{2}$



总结：只要$l\times2>r$就能找出符合题意的$x$



## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int l,r;
		cin>>l>>r;
		if(l*2>r)
		cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
	return 0;
}
```





---

## 作者：Aw顿顿 (赞：0)

## 题意

判断是否存在 $x$，使得 $(i\bmod x)\ge\dfrac{x}{2}$，$i\in[l,r]$。

## 解法

首先给结论，判断是否存在 $2\cdot l\le r$。

----


$$i\bmod x\ge \dfrac{x}{2}$$

首先考虑构造一组特殊的可行解，我们容易知道，如果能够令 $x=2i$ 就一定有解。

为什么呢？我们只要熟悉模的定义与计算方法，很轻易就可以对此进行说明：

$$i\bmod 2i=i$$

$$i\ge\dfrac{2i}{i}$$

所以可以。

那么只要我们能保证存在 $r\ge 2\cdot l$ 就一定有解。

那么，我们该怎么说明剩下的内容呢？如果不满足这个条件，直观可以看出来接下来的结果是根据 $x<i$ 和 $x>i$ 分为两个分别递增的过程的，那么可以分别讨论。

一定不存在这样的一个解。

那么就可以写出代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r;
int main(){
	cin>>T;
	while(T--){
		cin>>l>>r;
		if(l*2>r)puts("YES");
		else puts("NO");
	}return 0;
}
```

**$\bold C$ 语言代码**
```c
int T, l, r;
scanf("%d", &T);
while ( T -- ) {
    scanf ("%d%d", &l, &r) ;
	if(l * 2 > r) puts( "YES" ) ;
	else puts( "NO" );
}
```

---

## 作者：yewanxingkong (赞：0)

首先需要明确一个概念， $%$ 运算是指除以这个数得到的余数。

那么想要一个数在 $%$ 另一个数后还要不比这另一个数的 $1/2$ 小，那么这个数最小也是另一个数的 $1/2$ 。

如果一个区间都要满足这个条件那么就把区间左端作为这个数的 $1/2$ ，那么就要满足右端点要小于这个数。

即 $r<l*2$ 。

下面是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
int t,l,r;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	t=read();
	while(t--){
		l=read();
		r=read();
		if(r<l*2)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

