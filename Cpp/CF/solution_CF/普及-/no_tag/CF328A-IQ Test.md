# IQ Test

## 题目描述

Petya is preparing for IQ test and he has noticed that there many problems like: you are given a sequence, find the next number. Now Petya can solve only problems with arithmetic or geometric progressions.

Arithmetic progression is a sequence $ a_{1} $ , $ a_{1}+d $ , $ a_{1}+2d $ , $ ... $ , $ a_{1}+(n-1)d $ , where $ a_{1} $ and $ d $ are any numbers.

Geometric progression is a sequence $ b_{1} $ , $ b_{2}=b_{1}q $ , $ ... $ , $ b_{n}=b_{n-1}q $ , where $ b_{1}≠0 $ , $ q≠0 $ , $ q≠1 $ .

Help Petya and write a program to determine if the given sequence is arithmetic or geometric. Also it should found the next number. If the sequence is neither arithmetic nor geometric, print 42 (he thinks it is impossible to find better answer). You should also print 42 if the next element of progression is not integer. So answer is always integer.

## 说明/提示

This problem contains very weak pretests!

## 样例 #1

### 输入

```
836 624 412 200
```

### 输出

```
-12
```

## 样例 #2

### 输入

```
1 334 667 1000
```

### 输出

```
1333
```

# 题解

## 作者：xujian (赞：3)

题解 CF328A 【IQ Test】

首先我们由题目翻译可得，此题是要我们求等差数列与等比数列的下一项，如果它不是其中任何一个数列则输出$42$。

由于本题只有$4$个数，本应十分方便操作，但是$CF$给的数据十分的恶心，所以需要考虑许多种情况。

做法大致是先将其读入，判断是否为等差数列或等比数列，否则就输出$42$.

有几个需要注意的，一是要注意判断全$0$的情况，这点在条件和$printf$均可以进行判断；二是要考虑等比数列的精度问题，$float$精度不够，$double$又会出现神奇的错误，所以只能通过乘法来判断；三是要注意如果一个数列既是等差数列又是等比数列（即相差等于$0$），是输出这个数而不是$42$的。

看代码吧↓（标准$C$语言）

```
#include<stdio.h>
int main(){
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(a-b==b-c&&b-c==c-d&&(a||b||c||d))printf("%d",d-(a-b));
	else if(a*c==b*b&&b*d==c*c)printf("%d",d*d%c?42:d*d/c);
	else printf("%d",42);
	return 0;
}
```


---

## 作者：Legendre_Gauss (赞：2)

CF328A   
既然编号是A，那么一定不太难写   
本题只两种情况：等差数列或者等比数列      

1.对于等差数列，判断两两之间的差是否相等，若相等就拿最后一个数减去公差  
2.等于等比数列,由a/b=b/c得a\*c=b\*b，仍然是一次判断即可

贴代码：
```
#include <cstdio>
#include <cmath>
using namespace std;
int a,b,c,d;
int main() {
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(abs(a-b)==abs(b-c) && abs(c-d)==abs(b-c))printf("%d\n",d-a+b);
	else if(a*c==b*b && b*d==c*c) {
		if(!(d*d%c))printf("%d\n",d*d/c);
		else printf("%d\n",42);
	} 
	else printf("%d\n",42);
	return 0;
}
```

---

## 作者：zmza (赞：1)

这题就是求等差数列和等比数列

等差数列：

					令i为差
$$a_1 - a_2 = i$$
$$a_2 - a_3 = i$$
$$......$$
$$a_{n-1}-a_n = i$$

等比数列：

					令i为商
$$a_1\div a_2 = i$$
$$a_2\div a_3 = i$$
$$......$$
$$a_{n-1}\div a_n = i$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(a - b == b - c && b - c == c - d)//等差数列 
	{
		printf("%d",d + b - a);
	}
	else if(a * c == b * b && b * d == c * c)//等比数列。因为这个是向下取整，所以不能a / b == b / c 
	{
		if(d * d % c == 0)//要整除才行 
		{
			printf("%d",d * d / c);
		}
		else
		{
			printf("42");
		}
	}
	else
	{
		printf("42");
	}
	return 0;
}

```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF328A)

# 前置芝士

要通过这道题，我们必须知道什么叫：

### 等差数列与等比数列

一个数列：$a_1,a_2,......,a_n$

如果它是等差数列：

那么$a_1-a_2=a_2-a_3=......=a_{n-1}-a_n$

如果它是等比数列：

那么$\frac{a_1}{a_2}=\frac{a_2}{a_3}=......=\frac{a_{n-1}}{a_n}$（其中$a_1\neq0$）


------------
# 思路

知道了前置芝士，让我们来看一下这道题的几个坑：（详见代码）

1、结果可能为负数

2、等比数列中所求的数必须是整数，不是整数得输出$42$（题目中貌似没翻译到）

3、因为$int$型的变量相除后如果不是整数会自动向下取整，

所以必须将$\frac{a_1}{a_2}=\frac{a_2}{a_3}$变形为$a_1\times a_3=a_2\times a_2$再判断其是否为等比数列

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main(){
    cin>>a>>b>>c>>d;//输入 
    if(a-b==b-c&&b-c==c-d){//等差数列性质 
        cout<<d+b-a<<endl; 
    }else if(a*c==b*b&&b*d==c*c){//等比数列变形后的性质 
        if(d*d%c==0){//判断整除 
            cout<<d*d/c<<endl;
        }else{
            cout<<42<<endl;
        }
    }else{
        cout<<42<<endl;
    }
    return 0;//好习惯 
}
```

代码看完了，你学废了吗？

---

## 作者：云浅知处 (赞：0)

这题也不算太难啦qwq。

首先，判断等差数列。

等差数列其实就是相邻两个数之间的差相等的数列。比如，如果 $a,b,c$ 满足 $a-b=b-c$，那么 $a,b,c$ 成等差数列。

直接移项，不难看出 $a+c=2b$。

所以判断等差数列就可以直接判断了。

等比数列其实差不多，还是上面的 $a,b,c$，如果 $\dfrac{a}{b}=\dfrac{b}{c}$，那么 $a,b,c$ 成等比数列。

随便变形一下就可以看出来 $ac=b^2$，也是直接判断。

那么输出下一项呢？

- 如果 $a,b,c,d$ 成等差数列，那么公差就是 $b-a$，输出 $d+b-a$ 即可。
- 如果 $a,b,c,d$ 成等比数列，那么设下一项是 $e$，则由上面的性质，我们可以知道：$ce=d^2$，所以 $e=\dfrac{d^2}{c}$。
- **注意：题目中说这个数必须是整数，所以此时必须有 $c\left|d^2\right.$，否则下一项不是整数，需要输出 `42`！**

Code：

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int a,b,c,d;

int main(void){
	
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(a+c==b*2&&b+d==c*2)printf("%d\n",d+(b-a));
	else if(a*c==b*b&&b*d==c*c)printf("%d\n",((d*d)%c)?42:(d*d/c));
	else puts("42");

	return 0;
}

```

---

## 作者：修罗海神王 (赞：0)

## 首先，题目中提到了两个数列：
[等差数列](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97/1129192?fr=aladdin)    以及
[等比数列](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97/1129457?fr=aladdin)

###### ~~大家可以先点进去看看，这两个数列到底是什么意思。~~

### 然后，我们就可以来分析一下这道题目了：

首先输入：


```cpp
cin>>a>>b>>c>>d;
```


然后满足等差数列的数列，条件可以为两两之间相差的绝对值相等，那么就可以输出这个等差数列的下一项了，为最后一项+(最后一项-最后第二项)：
```cpp
else if(a*c==b*b&&b*d==c*c) {if(d*d%c==0) cout<<d*d/c<<"\n";else cout<<"42\n";}
```



接着，是满足等比数列的数列，这个条件的由来楼下讲的都很清楚，就不多说了。当这个满足时，还需要判断，因为如果最后一项的平方不能整除最后第二项时，就会输出很奇怪的double，应该直接输出42，否则，即能够整除，就可以直接输出最后一项的平方除以了~~（不知道你们能不能懂，逃…~~：


```cpp
if(abs(a-b)==abs(b-c)&&abs(c-d)==abs(b-c)) cout<<d+(d-c)<<"\n";
```

最后，就可以直接输出42了：

```cpp
else cout<<"42\n";
```


## ~~献上完整代码~~：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main()
{
	cin>>a>>b>>c>>d;//第一条
	if(abs(a-b)==abs(b-c)&&abs(c-d)==abs(b-c)) cout<<d+(d-c)<<"\n";//第二条
	  else if(a*c==b*b&&b*d==c*c) {if(d*d%c==0) cout<<d*d/c<<"\n";else cout<<"42\n";}//第三条
	         else cout<<"42\n";//第四条
	return 0;
}
```

###### 应该够完整了吧o(*￣︶￣*)o


---

## 作者：封禁用户 (赞：0)

此题就是判断是否成等比或等差数列，一共有4个数字

等差数列真的是简单的不得了，代码如下↓↓↓
```
if(a-b==b-c && b-c==c-d)//差一样 
	{
		j=a-b;//先求出差 
		cout<<d-j;//再求出最后一个数字减去差 
	}
```
等比数列有一种比较坑人，我不知道他有没有出现，就是0,0,0,0.于是，我打了一个特判↓↓↓（可不打，看后面就知道了）
```
else if(a==0 && b==0 && c==0 && d==0)//全部都是0 
	cout<<0;
```
接下来就是等比数列。但是如果直接a/b，b/c可能会有不好的结果，举个栗子，2,2,3,3。你把他们相除商都是1，但他们是等比数列吗？？？

让我们来仔细分析一下：首先是a/b与/c，我们可以把他看成ac/bc和bb/bc，那我们可以通过比较ac与bb来比较他们是否相等。以此类推。

当判断是的又该如何判断是不是整数呢，老办法，化简!d/(c/d)=d*d/c。那么我们只要判断d*d%c==0即可。不满足输出42，否则输出d*d/c

都不满足嘛~~输出42

整体代码如下↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
long long a,b,c,d,j;
int main()
{
	cin>>a>>b>>c>>d;
	if(a-b==b-c && b-c==c-d)//差一样 
	{
		j=a-b;//先求出差 
		cout<<d-j;//再求出最后一个数字减去差 
	}
	else if(a==0 && b==0 && c==0 && d==0)//全部都是0 
	cout<<0;
	else if(a*c==b*b && b*d==c*c) //经过简化后的商比较 
	{
		if(d*d%c==0)//如果是整数 
		cout<<d*d/c;
		else
		cout<<42;//其他输出42 
	}
	else//其他的 
	cout<<42;//输出42 
	return 0;
}
```

---

## 作者：Zhou_Wingay (赞：0)

### 思路：先判断是等差数列还是等比数列或是都不是，然后再输出。

等差数列定义：每两个相邻的数的差都相等。

等比数列定义：每两个相邻的数的比值都相等。

注意：
 1. 等比数列不要用除法，移位变乘即可。
 
 2. 等比数列如果最后一位除不尽，那仍需输出42。

然后就是代码了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a-b==b-c&&b-c==c-d){
		cout<<d+b-a;
	}
	else if(a*c==b*b&&b*d==c*c){//移位变乘
		if(d*d%c==0) cout<<d*d/c;
		else cout<<42;//特判
	}
	else{cout<<42;}
	return 0;
}
```


---

