# Display Size

## 题目描述

A big company decided to launch a new series of rectangular displays, and decided that the display must have exactly $ n $ pixels.

Your task is to determine the size of the rectangular display — the number of lines (rows) of pixels $ a $ and the number of columns of pixels $ b $ , so that:

- there are exactly $ n $ pixels on the display;
- the number of rows does not exceed the number of columns, it means $ a<=b $ ;
- the difference $ b-a $ is as small as possible.

## 说明/提示

In the first example the minimum possible difference equals 2, so on the display should be 2 rows of 4 pixels.

In the second example the minimum possible difference equals 0, so on the display should be 8 rows of 8 pixels.

In the third example the minimum possible difference equals 4, so on the display should be 1 row of 5 pixels.

## 样例 #1

### 输入

```
8
```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
64
```

### 输出

```
8 8
```

## 样例 #3

### 输入

```
5
```

### 输出

```
1 5
```

## 样例 #4

### 输入

```
999999
```

### 输出

```
999 1001
```

# 题解

## 作者：666yuchen (赞：3)

# 一道非常水的数学题
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>//文件头
#define ii int
#define fyx(i,j,n) for(ii i=j;i>=n;i--)
using namespace std;
ii n;//定义n
int main()
{
  cin>>n;//输入n
  fyx(i,sqrt(n),1)//从sqrt(n)一直到1循环，因为要找两个数的差接近，所以倒着找。
  if(n%i==0)//如果n除的尽i，证明这个i就是每一行的像素个数a。
  {
  	cout<<i<<" "<<n/i;//输出这个i和n/i（n/i就是每一列的像素个数b）
  	return 0;//直接结束程序。
  }
  return 0;
}
```
### 为了营造美好的洛谷，请不要抄袭!!!

---

## 作者：tzl_Dedicatus545 (赞：1)

[更好的阅读体验](https://wangdemao.github.io/wangdemao/post/ti-jie-cf747a-display-size/)

这是一道数学题，因为题目里说了 $a\leq b$ ，可以推导出：$a\leq\sqrt{n}\leq b$ ，所以一个循环从 $n$ 到小枚举 $a$ ,如果  $n\%a=0$ ，即 $n$ 能被 $a$ 整除，输出 $a$ 和 $n/a$ 即可。



------------


### **话不多说，上代码**


```cpp
#include <iostream>
#include <cmath>   //数学库

using namespace std;
int main()
{
	int n;
	
	cin>>n;
	
	for(int i=sqrt(n);i>=1;i--)
	{
		if(n%i==0)
		{
			cout<<i<<" "<<n/i;
			return 0;
		}
	}



	return 0;
}

```

萌新第一次写题解，望管理员通过！

---

## 作者：Laser_Crystal (赞：1)

### 一个简单地贪心
因为题目要求：

第一，显示器上必须正好有n个像素； 

第二，每一行的像素个数a不能超过每一列的像素个数b， 即a<=b; 

第三，你必须让b-a的差尽可能小。

那么，我们可以用一个类似于判断质数的方法来进行贪心：

n个像素，要想长宽相差最小，那差就是0（这时候n为完全平方数），如果满足不了差为零，那就将n的平方根(变量k）取整后递减，直到n%k==0为止，然后输出k和n/k。

代码看这边：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n;
  cin>>n;
  int k=0;
  k=sqrt(n);
  while(n%k!=0) k--;
  cout<<k<<" "<<n/k;
  return 0;
}
```

---

## 作者：OneZzy_226 (赞：0)

### 前言  
~~没错，我又来水红题了。~~  
### 题目简述  
* 给定一个数 $n$ ,求两个数 $a$ 和 $b$,使得$a\cdot b = n$，并且让$b-a$的值最小。
* $n \leq 1000000,a \leq b$ 。  
### 思路  
~~这是一道简单的题。~~  
由题意，我们可以从$\sqrt{n}$到$1$循环,枚举 $a$ 的值，当找到第一个满足$a \mid n$(即 $a$ 整除 $n$)的值时，将 $b$ 的值赋值为$\frac{n}{a}$ ,输出答案并跳出循环。  
由于$\sqrt{1000000} = 1000$,所以最坏情况下循环次数不超过$1000$次，对于这一题可以稳过。  
### Code  
代码如下：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
	cin>> n ;
	for(a = sqrt(n);a >= 1;a--){//从根号n到1枚举a的值 
		if(n % a == 0){//如果a整除n 
			b = n / a;//将b赋值为n除以a的值 
			cout<< a << " " << b;//输出 
			break;//跳出循环 
		}
	}
	return 0;//华丽地结束 
}

```  
~~珍爱生命，远离抄袭。~~

---

## 作者：封禁用户 (赞：0)

简化版题目:输入$n$,$a*b=n$,在$a$和$b$均为整数的和 $a$ $\le$ $b$情况下使得 $a-b$ 最小

$a-b$最小,则此时 $a=b=$ $\sqrt{n}$ ,且$b=n/a$,若$a$不为整数,就把 $a$从 $\sqrt{n}$ 一直枚举到 $1$ 当 $n$ $\bmod$ $a=0$ ,则输出 $a$ 和$n/a$(也就是$b$)

上代码($c++$):

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int a=sqrt(n);a>=1;a--)//枚举
	{
		if(n%a==0)
		{
			cout<<a;
			int b=n/a;
			cout<<" "<<b;
			return 0;
		}
	}
}
```


---

## 作者：SocietyNiu (赞：0)

# 数学题
这道题~~十分水~~  
首先从输入的数的算术平方根入手，看乘积是否成立，若不成立，一个数--，一个数++，再次判断，由于数不是很大，O（N^2） 足够了  
代码如下  
```
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int x;cin>>x;
	for(int i=sqrt(x);i>=1;i--)
		for(int j=sqrt(x);j<=x;j++)
			if(i*j==x) {cout<<i<<" "<<j;return 0;}
}
```

---

