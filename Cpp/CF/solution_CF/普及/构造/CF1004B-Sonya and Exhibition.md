# Sonya and Exhibition

## 题目描述

Sonya decided to organize an exhibition of flowers. Since the girl likes only roses and lilies, she decided that only these two kinds of flowers should be in this exhibition.

There are $ n $ flowers in a row in the exhibition. Sonya can put either a rose or a lily in the $ i $ -th position. Thus each of $ n $ positions should contain exactly one flower: a rose or a lily.

She knows that exactly $ m $ people will visit this exhibition. The $ i $ -th visitor will visit all flowers from $ l_i $ to $ r_i $ inclusive. The girl knows that each segment has its own beauty that is equal to the product of the number of roses and the number of lilies.

Sonya wants her exhibition to be liked by a lot of people. That is why she wants to put the flowers in such way that the sum of beauties of all segments would be maximum possible.

## 说明/提示

In the first example, Sonya can put roses in the first, fourth, and fifth positions, and lilies in the second and third positions;

- in the segment $ [1\ldots3] $ , there are one rose and two lilies, so the beauty is equal to $ 1\cdot 2=2 $ ;
- in the segment $ [2\ldots4] $ , there are one rose and two lilies, so the beauty is equal to $ 1\cdot 2=2 $ ;
- in the segment $ [2\ldots5] $ , there are two roses and two lilies, so the beauty is equal to $ 2\cdot 2=4 $ .

The total beauty is equal to $ 2+2+4=8 $ .

In the second example, Sonya can put roses in the third, fourth, and sixth positions, and lilies in the first, second, and fifth positions;

- in the segment $ [5\ldots6] $ , there are one rose and one lily, so the beauty is equal to $ 1\cdot 1=1 $ ;
- in the segment $ [1\ldots4] $ , there are two roses and two lilies, so the beauty is equal to $ 2\cdot 2=4 $ ;
- in the segment $ [4\ldots6] $ , there are two roses and one lily, so the beauty is equal to $ 2\cdot 1=2 $ .

The total beauty is equal to $ 1+4+2=7 $ .

## 样例 #1

### 输入

```
5 3
1 3
2 4
2 5
```

### 输出

```
01100```

## 样例 #2

### 输入

```
6 3
5 6
1 4
4 6
```

### 输出

```
110010```

# 题解

## 作者：zplqwq (赞：6)

# CF1004B

Hello! 

今天我们来看这道题。

# Section 1 题目分析

## 题意

构造一个 0−1 串，使得给定的几个区间内 1 和 0个数的乘积最大。

## 算法分析

数学题

我们不妨想一下，在确定0和1的个数的情况下怎么让1和0的个数的乘积最大？

记得小学学过一个口诀：和同近积大。

也就是说，在0和1个数确定的个数的情况下只需要让1和0的个数尽量相近就可以了。

那怎么做到呢？

交替着输出呗。

# Section 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;
//管理大大求过
//管理大大辛苦啦
int n;
int main()
{
    cin>>n;//输入
    for(int i=1;i<=n;i++) 
    {
        cout<<i%2;//因为%2的结果只能是0或者1，因此只要输出i%2就可以了。
    }
    return 0;
}
```

~~管理大大求过~~



---

## 作者：__Hacheylight__ (赞：4)

题意是告诉我们靠构成一个01序列，使某些区间0个数*1个数最大

这个题乍一看没什么思路，但想一想就有了，而且代码极短

考虑如何才能使某些区间0个数*1个数最大？

肯定是0和1的数量差最小，即0或1

怎么样能够使0,1的数量差最小化？

0,1间隔输出呗。。。

于是你发现序列与m并无关。。。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int main(){
	int n;
	scanf("%d",&n) ;
	for (int i=1;i<=n;i++) printf("%d",i&1) ;
}
```



---

## 作者：锦瑟，华年 (赞：3)

我又来水题解了。

好言归正传。本体的大致意思就是，然后构造一个01串，使此01串中给定的$m$个区间中0的个数与1的个数的积之和最大。

好，我们把题目给拆解一下，试问如何使一个区间内0的个数与1的个数的积最大呢？显然，0的个数与1的个数之差要尽可能小。为什么会有以上结论呢? ~~只要是人都能想出来~~ 让我给大家模拟一下。

| a | 1 |2  | 3 |
| :----------: | :----------: | :----------: | :----------: |
| b | 5 | 4 | 3 |
| a+b | 6 |6  | 6 |
| a*b | 5 | 8 | 9 |

好了，通过以上探究，我们已经知道了，为使积最大，0,1数量之差要最小。那么如何最小呢？其中一个方法就是，0和1接替着来，即0101010…………,我们再回到题目中，诶，我们发现，为使积之和最大，那么每个区间都是01交换着来，那么我们何妨不可以构造一个都是01交换着来的字符串，使积之和最大呢？

哦，我有感觉了。

代码：

	#include<stdio.h>
	using namespace std;
	int main(){
		int n,i;
		scanf("%d",&n);//其实这题中m只用不到的
		for(i=1;i<=n;i++){
			printf("%d",i%2);//01交换着输出
		}
		return 0;
	}
    
好了，ヾ(￣▽￣)Bye~Bye~


---

## 作者：Aw顿顿 (赞：1)

## 题意

需构造一个 $0-1$ 串，使得给定的几个区间内 $1$ 和 $0$ 个数的乘积最大。

## 方案

令区间长度为 $x$：

若 $x\bmod 2=0$ 则最大的答案为 $\left(\dfrac{x}{2}\right)^2=\dfrac{x^2}{4}$。

若 $x\bmod 2=1$ 则最大的答案为 $\left\lfloor\dfrac{x}{2}\right\rfloor\times\left\lceil\dfrac{x}{2}\right\rceil$。

怎么构造出这种情况？我们应该需要尽可能让其个数相近：那么我们只需要让 $1$ 和 $0$ 交替出现即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) {
        cout<<(i&1);
    }
}
```


---

## 作者：lichenfan (赞：0)

### 思维题
在和一定的情况下，不用管区间，只需让每一块的 $0$ 和 $1$ 的尽量接近就好了，也就是说让 $0$ 和 $1$ 交替出现，就可以了。至于 $0$ 和 $1$ 哪个在前面都没有关系，所以不用考虑 $m$，因为与它无关。交替的话可以用取模来解决。
## Code：
```cpp
#include<bits/stdc++.h>  		 //不需要读入li与ri，因为没用
using namespace std;
int main(){
	int n;
	cin>>n; 
	for(int i=1;i<=n;i++) cout<<i%2;  //交替输出
} 
```



---

## 作者：Cocoly1990 (赞：0)

## 思路

先考虑一个问题，**在和一定的情况下**，如何让两数积最大

结论很好猜，只需要让两数差最小即可

给出一个证明

设两数为$a,b$，和为$c$，差为$x$（设$a>b$）

则$a$可以表示$\frac{1}{2}c+x$

$b$可以表示$\frac{1}{2}c-x$

$a\times b$就可以表示为$\frac{1}{4}c^2-x^2$ 

又$c$一定，所以$x$越小，$a\times b$值越大

交替输出$0,1$即可

## Code

```cpp
#include<bits/stdc++.h>
using namespace std ;
int n ;
int main()
{
    cin >> n ;
    for(int i = 1 ; i <= n ; i ++)
        cout << i % 2 ;
    return 0 ;
}
```

---

## 作者：Imy_bisLy (赞：0)

## 简化题意：
构造一个长度为$n$的01串使$m$组询问$l-r$的区间内$cnt0$与$cnt1$数目乘积最大
## solution
第一眼？？啥这是？

第二眼哦哦裸的数学题，看了看其他题解都是直接给结论这里说一下为什么0和1交叉输出为正解
正难则反
考虑 高一必修1 均值不等式
根据均值不等式
$ a>0,b>0$
$\dfrac{a+b}{2}  \ge \sqrt{ab}$

反向逆推

$ab \le \dfrac{(a+b)^2}{4}$

$ a+b = n$ 为一个定值，根据不等式的性质在这时候取等号，就可得到$ab$的最大值，均值不等式一正二定三相等

当且仅当 $a=b$时等号成立

这时候大胆的得出结论 当 0 和 1 交替输出得出的串是最优的
### code
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
int read(){
	int s = 0 ,f = 1; char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-') f = -1 ; ch = getchar();}
	while(ch >= '0'&&ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * f;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n = read() ,m = read();
	for(int i = 1 ; i <= m ;i++){
		int l = read() , r =read();
	} 
	for(int i = 1 ; i<= n ;i++){
		if(i &1 ) cout<<'1';
        //i是奇数输出1 ，否则输出0 
		else cout<<'0'; 
	}
	return 0;
}

```

---

## 作者：Arghariza (赞：0)

**怎么让固定区间的数量之积最大？**

由于区间是一定的，故设玫瑰花数量为$x$，百合花数量为$s-x$，$s$为区间长度。

这个区间的美丽程度为$y=x(s-x)=x^2-sx$（也就是一个**二次函数**）

$∵x^2$的指数为正数$1$，所以二次函数的开口朝下，顶点为$p(\frac{s}{2},-\frac{s^2}{4})$，此时$y$取最大值。

故当$x=\frac{2}{s}$时，$x(s-x)$取最大值，这就是人们通常说的**和一定，差小积大**。

回到这题，我们发现让区间数量之积最大也就是让整个区间玫瑰花与百合花数量尽量相等，也就是$01$交替出现即可。

```
#include <iostream>
using namespace std;

int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        printf("%d", i % 2);
    }
    return 0;
}
```

---

