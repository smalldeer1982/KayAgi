# Digital Counter

## 题目描述

Malek lives in an apartment block with $ 100 $ floors numbered from $ 0 $ to $ 99 $ . The apartment has an elevator with a digital counter showing the floor that the elevator is currently on. The elevator shows each digit of a number with $ 7 $ light sticks by turning them on or off. The picture below shows how the elevator shows each digit.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495A/82c4b2ab842edc90f41be56a97fcef1aaf93be0a.png)One day when Malek wanted to go from floor $ 88 $ to floor $ 0 $ using the elevator he noticed that the counter shows number $ 89 $ instead of $ 88 $ . Then when the elevator started moving the number on the counter changed to $ 87 $ . After a little thinking Malek came to the conclusion that there is only one explanation for this: One of the sticks of the counter was broken. Later that day Malek was thinking about the broken stick and suddenly he came up with the following problem.

Suppose the digital counter is showing number $ n $ . Malek calls an integer $ x $ ( $ 0<=x<=99 $ ) good if it's possible that the digital counter was supposed to show $ x $ but because of some(possibly none) broken sticks it's showing $ n $ instead. Malek wants to know number of good integers for a specific $ n $ . So you must write a program that calculates this number. Please note that the counter always shows two digits.

## 说明/提示

In the first sample the counter may be supposed to show $ 88 $ or $ 89 $ .

In the second sample the good integers are $ 00 $ , $ 08 $ , $ 80 $ and $ 88 $ .

In the third sample the good integers are $ 03,08,09,33,38,39,73,78,79,83,88,89,93,98,99 $ .

## 样例 #1

### 输入

```
89
```

### 输出

```
2
```

## 样例 #2

### 输入

```
00
```

### 输出

```
4
```

## 样例 #3

### 输入

```
73
```

### 输出

```
15
```

# 题解

## 作者：L_zaa_L (赞：6)

# 题意
电梯坏掉了，几个地方可能没发光，请你算出楼层一共有多少种可能。
# 分析
由枚举可以得出：

$0$ 可能是 $0$，$8$。

$1$ 可能是 $1$，$3$，$4$，$7$，$8$，$9$，$0$。

$2$ 可能是 $2$，$8$。

$3$ 可能是 $3$，$8$，$9$。

$4$ 可能是 $4$，$8$，$9$。

$5$ 可能是 $5$，$6$，$8$，$9$。

$6$ 可能是 $6$，$8$。

$7$ 可能是 $0$，$3$，$7$，$8$，$9$。

$8$ 可能是 $8$。

$9$ 可能是 $8$，$9$。

于是只用将十位和个位两个数字能够变成其他数字的可能数相乘即可得出答案。

# Code
```
#include<bits/stdc++.h>
using namespace std;
int n,a[11]={2,7,2,3,3,4,2,5,1,2};
int main(){
	cin>>n;
	cout<<a[n%10]*a[n/10];
	return 0;
}
```

---

## 作者：Bpds1110 (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/CF495A)
# 题面：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495A/82c4b2ab842edc90f41be56a97fcef1aaf93be0a.png)

给出一个两位数，求出组成这个两位数共有多少种方法。
# Solution:
根据题意，我们发现**组成两位数的方案数就是这个两位数十位的方案数乘个位的方案数**。结合所给出的图片，我们可以发现各个数位上的数字分别有以下可能性。
```
0有0，8共2种可能；
1有0，1，3，4，7，8，9共7种可能；
2有2，8共2种可能；
3有3，8，9共3种可能；
4有4，8，9共3种可能；
5有5，6，8，9共4种可能；
6有6，8共2种可能；
7有0，3，7，8，9共5种可能；
8有8共1种可能；
9有8，9共2种可能。
```
由此，我们便可以得出一个数组，来存放每个数字所能有的可能性总数。只要把十位和个位的方案数相乘便能得到结果。
# Code:
```
#include<bits/stdc++.h>
using namespace std;
int n,s1,s2;
const int ans[10]={2,7,2,3,3,4,2,5,1,2};//数组存放每一位的方案数 
int main()
{
	cin>>n;
	s1=ans[n/10];//取出十位的方案数 
	s2=ans[n%10];//取出个位的方案数 
	cout<<s1*s2;//十位的方案数与个位的方案数相乘 
	return 0;
}

```


---

## 作者：sanjingshou14 (赞：2)

# 前言
这题不难，只需要手动枚举一下就可以了。

个人认为本题应评红。

# 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF495A)

借用一下他人的翻译：

给你一个电梯上显示的两位数，有一些发光条坏掉了，求原来数字有多少种可能。

# 思路
从图中可以看出，这部电梯显示数字的方式是用八个发光条拼成数字 $8$ 的样子，改变发光的条的数量和位置，从而形成其他九个数字的形状。

所以，我们可以知道，当它变成某个数字时，它原来可能的数字的个数是一定的。也就是说，我们可以把每个数字原来可能的个数算出来，再存进数组里。

接着，因为输入的是一个两位数，经过简单的排列组合，我们可以知道，只要把两种数字可能的个数相乘就好了。

# 代码
经过手动的枚举，我们可以得到 $0 - 9$ 的数字的可能个数分别是 $2$，$7$，$2$，$3$，$3$，$4$，$2$，$5$，$1$，$2$。然后，写入代码就很容易了。

注意这个数字本身也要算进去。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[11]={2,7,2,3,3,4,2,5,1,2};
int main(){
	char a,b;
	cin>>a>>b;
	cout<<x[a-'0']*x[b-'0'];//这几步不一定要用字符型来运算，也可以用整型来进行。
	return 0;
}
```

请勿抄袭，否则棕名！

---

## 作者：Zq_water (赞：0)

**一道水题**

根据乘法原理，总情况数就等于十位情况数乘各位情况数。

我们还要枚举下每种数字的所有情况

$0$ 有 $0$，$8$。

$1$ 有 $1$，$3$，$4$，$7$，$8$，$9$，$0$。

$2$ 有 $2$，$8$。

$3$ 有 $3$，$8$，$9$。

$4$ 有 $4$，$8$，$9$。

$5$ 有 $5$，$6$，$8$，$9$。

$6$ 有 $6$，$8$。

$7$ 有 $0$，$3$，$7$，$8$，$9$。

$8$ 有 $8$。

$9$ 有 $8$，$9$。

## 代码

```cpp
#include <cstdio>
using namespace std;
int n,a[10]={2,7,2,3,3,4,2,5,1,2};
int main(){
	scanf("%d",&n);
	printf("%d",a[n%10]*a[n/10]);
	return 0;
}
```


---

## 作者：__LiChangChao__ (赞：0)

## 题意/翻译
有一台电梯的楼层显示屏坏了，它只能显示一部分，现在给你当前显示的数字 $n$（输入保证有两位，但不一定是两位数），计算现在所在的楼层有几种可能？
## 思路
显然，对于每一个 $n$，设 $n=10\times a+b(0\le a,b \le 9)$，且 $a,b$ 均为整数。假设 $a$ 能被 $x$ 个数包含，$b$ 能被 $y$ 个数包含（此处的包含是指：对于一个整数 $c$，若在显示屏组成整数 $d$ 的线段包含所有组成 $c$ 的线段，则称 $d$ 能包含 $c$），则一共可以组成 $x\times y$ 个数。

由于 $0\le a,b \le 9$，可以手工计算每个 $a$ 对应的 $x$。

当 $a=0$ 时，$x=2(0,8)$。

当 $a=1$ 时，$x=7(1,3,4,7,8,9,0)$。

当 $a=2$ 时，$x=2(2,8)$。

当 $a=3$ 时，$x=3(3,8,9)$。

当 $a=4$ 时，$x=3(4,8,9)$。

当 $a=5$ 时，$x=4(5,6,8,9)$。

当 $a=6$ 时，$x=2(6,8)$。

当 $a=7$ 时，$x=5(0,3,7,8,9)$。

当 $a=8$ 时，$x=1(8)$。

当 $a=9$ 时，$x=2(8,9)$。

$a$ 的 $x$ 值同时也适用于 $b$ 的 $y$ 值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[15]={2,7,2,3,3,4,2,5,1,2};//计算方式上已给出
int n;
int main(){
	scanf("%d",&n);	//输入
			//显然，n%10=a，n/10=b
	printf("%d",a[n%10]*a[n/10]);//计算总数
}


```

---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
输入一个两位数 $n$ 。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495A/82c4b2ab842edc90f41be56a97fcef1aaf93be0a.png)

如果 $n$ 的某一位在上图中占用的线段和其他的数字占用的线段重复了，即别的数字包含 $n$ 所有的线段，就把答案加一，最后输出答案。

### 题目分析：
首先我们需要先把一个两位数 $n$ 分解成两个一位数 $a$ 和 $b$ ，满足 $a×10+b=n$ 。

```cpp
#include <iostream>
using namespace std;
int n, a, b;
int main(){
	cin>>n;
	a=n%100;
    //获取十位
	b=n%10;
    //获取百位
	return 0;
}
```
上面这就是把一个两位数分解成两个一位数的程序。

我们解决了这个问题以后，这道题就变得简单多了，我们只需要将包含分解之后的 $a$ 和分解之后的 $b$ 的线段的数字相乘就行。

~~代码差 $3$ 行破百行。。。~~

### 具体代码：
```cpp
#include <iostream>
using namespace std;
int n, a, b, ansa, ansb;
int main(){
	cin>>n;
//	while(n!=0){
//		b=n%10;
//		n/=10;
//		a=n%10;
//		n/=10;
//		cout<<a<<" "<<b;
//	}
	a=n%100;
	b=n%10;
	if(a==0){
		//0、8都包含0 
		ansa+=2;
	}
	if(a==1){
		//1、3、4、7、8、9都包含1 
		ansa+=7;
	}
	if(a==2){
		//2、8都包含2
		ansa+=2;
	}
	if(a==3){
		//3、8、9都包含3
		ansa+=3;
	}
	if(a==4){
		//4、8、9都包含4
		ansa+=3;
	}
	if(a==5){
		//5、6、8、9都包含5
		ansa+=4;
	}
	if(a==6){
		//6、8都包含6
		ansa+=2;
	}
	if(a==7){
		//0、3、7、8、9都包含7
		ansa+=5;
	}
	if(a==8){
		//8包含8
		ansa+=1;
	}
	if(a==9){
		//8、9都包含9
		ansa+=2;
	}
	if(b==0){
		//0、8都包含0 
		ansb+=2;
	}
	if(b==1){
		//1、3、4、7、8、9都包含1 
		ansb+=7;
	}
	if(b==2){
		//2、8都包含2
		ansb+=2;
	}
	if(b==3){
		//3、8、9都包含3
		ansb+=3;
	}
	if(b==4){
		//4、8、9都包含4
		ansb+=3;
	}
	if(b==5){
		//5、6、8、9都包含5
		ansb+=4;
	}
	if(b==6){
		//6、8都包含6
		ansb+=2;
	}
	if(b==7){
		//0、3、7、8、9都包含7
		ansb+=5;
	}
	if(b==8){
		//8包含8
		ansb+=1;
	}
	if(b==9){
		//8、9都包含9
		ansb+=2;
	}
	cout<<ansa*ansb; 
	return 0;
}
```

---

## 作者：i_dont_know_who_am_i (赞：0)

**题目大意：**

给你一个电梯上显示的两位数，有一些发光条坏掉了，求原来数字有多少种可能。

**分析：**

这道题比较简单，不难发现：

$0$ 只能变成 $0$ 或 $8$，共 $2$ 种；

$1$ 可以变成 $0$ 或 $1$ 或 $3$ 或 $4$ 或 $7$ 或 $8$ 或 $9$，共 $7$ 种；

以此类推，$\cdots \cdots$

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[10]={2,7,2,3,3,4,2,5,1,2};//打表得到每一个数字可变成的数字个数
int main(){
	cin >>n;
	cout<<f[n%10]*f[n/10];
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：0)

## 题意
给你一个数字，问你这个数字可能被几种数字包含？  
包含的定义：  
如题中图，若这个数字的每一个格子都能被另一个数字包括（这个数字黑色的地方另一个数字也是黑色的），那么就是算一个包含。
## 思路
应为只有两位数，我们可以手动求出每一个数字都可以被几个数字包含。最终计算出来的结果是：
- $0$ 被 $0,8$ 包含，一共有 $2$ 个。
- $1$ 被 $0,1,3,4,7,8,9$ 包含，一共有 $7$ 个。
- $2$ 被 $2,8$ 包含，一共有 $2$ 个。
- $3$ 被 $3,8,9$ 包含，一共有 $3$ 个。
- $4$ 被 $4,8,9$ 包含，一共有 $3$ 个。
- $5$ 被 $5,6,8,9$ 包含，一共有 $4$ 个。
- $6$ 被 $6,8$ 包含，一共有 $2$ 个。
- $7$ 被 $0,3,7,8,9$ 包含，一共有 $5$ 个。
- $8$ 被 $8$ 包含，一共有 $1$ 个。
- $9$ 被 $8,9$ 包含，一共有 $2$ 个。

最后把个位数能被包含的数量乘上十位数能被包含的数量即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[10]={2,7,2,3,3,4,2,5,1,2};//打表
int main(){
	scanf("%d",&n);//输入
	printf("%d\n",f[n%10]*f[n/10]);//把个位数的数量乘上十位数的数量
	return 0;
}

```


---

