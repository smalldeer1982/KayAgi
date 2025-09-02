# Pasha and Stick

## 题目描述

Pasha has a wooden stick of some positive integer length $ n $ . He wants to perform exactly three cuts to get four parts of the stick. Each part must have some positive integer length and the sum of these lengths will obviously be $ n $ .

Pasha likes rectangles but hates squares, so he wonders, how many ways are there to split a stick into four parts so that it's possible to form a rectangle using these parts, but is impossible to form a square.

Your task is to help Pasha and count the number of such ways. Two ways to cut the stick are considered distinct if there exists some integer $ x $ , such that the number of parts of length $ x $ in the first way differ from the number of parts of length $ x $ in the second way.

## 说明/提示

There is only one way to divide the stick in the first sample {1, 1, 2, 2}.

Four ways to divide the stick in the second sample are {1, 1, 9, 9}, {2, 2, 8, 8}, {3, 3, 7, 7} and {4, 4, 6, 6}. Note that {5, 5, 5, 5} doesn't work.

## 样例 #1

### 输入

```
6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
20
```

### 输出

```
4
```

# 题解

## 作者：Isprime (赞：5)

题解CF610A[Pasha and Stick]

配合[Blog](https://www.luogu.org/blog/149815/solution-cf610a)食用更佳

[原题传送门](https://www.luogu.org/problem/CF610A)

题目翻译楼上讲的很清楚了

这题~~CF水题~~

首先奇数不可能，输出0

偶数先除以二减一，再除以二

为什么？

首先，n除以二有两种可能：①奇数 ②偶数

先处理第①种情况：奇数。如果n/2为奇数，那么n/2/2和(n/2-1)/2是相等的，所以用(n/2-1)/2

第②种：偶数。如果n/2是偶数，说明它能被4整除，答案就会变成加上正方形，不符合题意，所以(n/2-1)/2才是正确答案

Code（本来不想放，想想又放了
```cpp
#include<cstdio>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    if(n%2) printf("0\n");
    else printf("%d\n",(n/2-1)/2);
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：1)

又是一道水蓝题emmm......

直接进入正文：

设这个矩形的长和宽分别为$a, b$

那么$n = 2(a+b)$

### 1.n为奇数

直接是$0$啦QAQ

### 2.n为偶数

设$n=2k$，那么$k=a+b$

#### i.k为奇数

那么共有$(k-1)/2$种

#### ii.k为偶数

那么共有$(k-2)/2$种

综上，根据$C++$语法可得：

$ans=\begin{cases}0&n\equiv1(mod 2)\\(n/2-1)/2&n\equiv0(mod 2)\end{cases}$

于是，上代码啦：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
string s = "986581972365891236750123598023475980he4flhwaeiufnydcewqory2318904d12834";//防伪 
string ss = "78923652398415cfyh483wd7128904736679142yren8dxwy4908q26497q2835d";//防伪+1
string sss = "49388852457342y5hcf34w089q562138974c1209r7ecfyguisdbtvr8qwer901263c";//防伪+2
int n;
int main(){
	scanf("%d", &n);
	if(n & 1) puts("0");
	else printf("%d\n", ((n >> 1) - 1) >> 1);
	return 0;
}
```

最后，祝大家$CSP.rp++$!

## End

---

## 作者：Loi_zxp (赞：0)

首先看题，嗯......一道极其水的题，他说有一根木棍，要切三刀成四份，每份都是整数，这个时候呢，我们就要想，如果是奇数，必然不能满足都是整数，比如说19，发现无论怎么分都不能满足是正整数，所以为奇数时，就可以直接输出“0”。

当n小于等于4时，也不能满足是正整数，所以也可以直接输出“0”。

接下来就是n大于4且n为偶数时了，这个时候我们就要分类讨论了，如果他能组成正方形，那么ans就n/4-1,为什么呢，因为他不喜欢正方形呀，所以要减去；如果不能就不需要减了呀。（其实这个ans/4相当于枚举，就是从1开始枚举到ans/4,可自己数一数）。
**OK!贴标程了！！！**
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n,ans=0;
int main(){
	cin>>n;
	if(n<=4){
		ans=0;
	}
	else if(n%2==0){
		if(n%4==0){
			ans=n/4-1;
		}
		else ans=n/4;
	}
	else{
		ans=0;
	}
	cout<<ans;
	
}
```


---

## 作者：Novice233 (赞：0)

这道题看起来很长 但其实有用的部分并不多

要拼成长方形 不要正方形->算出所有矩形个数再减一（n固定时 能且仅能拼出一个正方形）

1.如果n是奇数 ×

2.如果n是偶数 矩形的一组边的和为n/2 也就是有n/2-1种（记得要减一，是正方形导致的）

贴上代码

```
#include<bits/stdc++.h>
using namespace std;
int n; 
int main(){
    cin>>n;
    if(n%2==1) cout<<0<<endl;
    else cout<<(n/2-1)/2<<endl;
    return 0;
}
```


---

## 作者：Skyjoy (赞：0)

# 这是一道假蓝题

分析一下解法。若$n$是奇数，没有解法，直接输出$0$。如果$n$是偶数，那解法数就是$(n\div2-1)\div2$。所以只需判断即可，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n%2){
        cout<<0;
    }
    else{
        cout<<(n/2-1)/2;
    }
    return 0;
}
```

祝大家$SCP-CN-CSP2019rp++$！！！

---

## 作者：CZQ_King (赞：0)

思路：分类讨论


首先，矩形周长$=2(a+b)$，所以如果$a,b$是正数，那么周长一定是一个偶数。

当总长$n$是
- 奇数，这是不可能成为一个矩形的周长的，那么方案数为$0$，即输出$0$。
- 偶数，先除以二，如果这个数
   - 还是偶数，说明有一种方案是正方形，那么方案就是$\frac{n}{4}-1$。
   - 奇数，直接输出$\frac{n}{4}$即可。

由于整除会将小数部分舍去，所以$\frac{n}{4}-1$和$\frac{n}{4}$可以压缩成一个公式：$\frac{\frac{n}{2}-1}{2}$

------------
不带空格的一行代码：
```pyhton
n=int(input());print(0if(n&1)else(n//2-1)>>1)
```
``0if(n&1)else(n//2-1)>>1``是三目运算符，代表如果``n&1``返回``0``否则返回``(n//2-1)>>1``。

``n&1``等价于``n%2``，位运算。

``(n//2-1)>>1``代表``(n//2-1)//2``，也是位运算。

---

## 作者：yuangq (赞：0)

这题不是很难，就是要认真点

~~~
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;//输入 
	if(n%2==1)//如果n为奇数，则不存在 
	{
		cout<<0;
		return 0;
	}
	n=n/2;//一个长边和一个短边长度之和 
	n++;
	cout<<n/2-1;//计算其数量 
	return 0;
}

~~~

---

