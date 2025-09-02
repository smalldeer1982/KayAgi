# Perfect Number

## 题目描述

We consider a positive integer perfect, if and only if the sum of its digits is exactly $ 10 $ . Given a positive integer $ k $ , your task is to find the $ k $ -th smallest perfect positive integer.

## 说明/提示

The first perfect integer is $ 19 $ and the second one is $ 28 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
19
```

## 样例 #2

### 输入

```
2
```

### 输出

```
28
```

# 题解

## 作者：DeepSkyBlue__ (赞：3)

这道题直接暴力枚举是能过的，从 $1$ 开始一个一个枚举，每遇到一个数字和为 $10$ 的计数器就加一，一直到计数器为 $n$ 时输出当前的数，退出循环。

我们可以写一个计算各位数字和的函数方便分析。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt(int x)//计算各位数字之和的函数
{
    int s=0;
    while(x>0)
    {
        s+=x%10;
        x/=10;
    }
    return s;
}
int main()
{
    int n;
    cin>>n;
    int sum=0;//计数器
    for(int i=1;;i++)//循环找数
    {
        if(cnt(i)==10)sum++;//如果各位数字之和为10那么计数器+1
        if(sum==n)//如果是第n个数了
        {
            cout<<i<<endl;//输出这个数
            return 0;//找到了，退出循环
        }
    }
    return 0;
}
```


---

## 作者：L2_sheep (赞：2)

做了一道CF题，求第k个数字之和为10的数，k最大为10000。应该说这题不难，甚至直接枚举都不会超时，但是你事先并不知道这个数会是多少，有多大。如果这题数据范围再扩大（比如10^12）的话，应该怎么做呢？

可以先打个表，看一下是怎么回事。
设x = 10^n，1到x之间有k个数的数字之和为10。
k和n之间有函数关系，可以用组合式来推导:
k = ∑ C(9, i)× C(n, i+1)(0 < i < min(10,n)) = C(n+9, n-1) - n.

于是，可以得到一张表。	 可以算出当k等于20029990时，答案已经接近10^20，已经是个非常大的数了。
那应该怎么做才能快速地算出答案呢？其实，还是可以用组合数学来解决。
方法并不复杂：从高位开始，通过分段累计求和，一旦超过k，就忽略这一段，从下一位开始继续这个步骤。
但还是要注意细节，最高位不能为0。组合数可以用杨辉三角来生成。具体代码如下：

```cpp
#include <stdio.h>
#define N 81
#define M 11

long long c[N][M] = {1};

int main() 
{
    int i, j, l, s;
    long long k, t = 0;

    scanf("%lld", &k);

    for(i = 1; i < N; i++){
        c[i][0] = 1;
        for(j = 1; j < M; j++) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }

    for(i = 2, j = 11; j < N; i++, j++){
        if(c[j][10] - i >= k) break;
        t = c[j][10] - i;
    }
    l = i - 1, s = 10;
    for(i = 1; ; i++){
        if(t + c[s - i - 1 + l][s - i] >= k) break;
        else t += c[s - i - 1 + l][s - i];
    }
    printf("%d", i);
    l--, s -= i;
    while(l > 0){
        if(s == 0) printf("0");
        else{
            for(i = 0; ; i++){
                if(t + c[s - i - 1 + l][s - i] >= k) break;
                else t += c[s - i - 1 + l][s - i];
            }
            printf("%d", i);
            s -= i;
        }
        l--;
    }
    printf("%d", s); 
    return 0;
}
```

---

## 作者：char32_t (赞：1)

# 题解 CF919B 【Perfect Number】
------------
模拟题，暴力扫描即可。
```cpp
#include<cstdio>
int judge(int a) {//判断a是否为Perfect Number
	int i=0, count=0;
	while(a>0) {
		count+=a%10;
		a/=10;
	}
	return count==10?1:0;//珂怕的三目运算符
}
int main() {
	int count=0, n;
	scanf("%d", &n);//读入数据
	for(int i=9; i<=12000000; i++) {
		if(judge(i)) count++;//每当找到一个Perfect Number时，计数器加1
		if(count==n) {//到达范围边界时
			printf("%d", i);//输出
			break;//退出
		}
	}
	return 0;//结束程序
}
```

---

## 作者：Nemonade (赞：0)

## 数位和模板

题目很明显地要求我们求出正整数的数位和。

相当明显地，一个正整数对于 $10$ 取模，会得到这个数的个位。

以 $6$ 位数 $114514$ 举例：

$$114514\bmod10 = 4$$

而一个 `int` 类型的数经过除法产生小数时会自动舍去小数位：

$$114514\div10=11451$$

我们惊奇的发现，这时原来数字的十位到了原来的个位上，我们就可以再次对于 $10$ 取模：

$$11451\bmod10 = 1$$

以此类推，直到原数为 $0$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,cnt;
int sum(int x){
	int sum=0;
	while(x){
		//取出个位并且累加 
		sum+=x%10;
		//下一位 
		x/=10;
	}
	return sum;
}
int main(){
	cin>>k;
	for(int i=1;i;++i){
		//如果此数数位和是10，计数器加一 
		if(sum(i)==10){
			++cnt;
			//如果到了第k个就输出 
			if(k==cnt){
				cout<<i;return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个数字 $k$，求出第 $k$ 小的各数位和为 $10$ 的数。

**数据范围：$1\leqslant k\leqslant 10000$。**
## Solution
这题为什么不可以打表解决呢？我们可以直接枚举、判断，获得所有第 $1\sim10000$ 个各数位和为 $10$ 的数，然后就可以直接输出答案了。
## Code
```cpp
int k, f[10007], cur;

int main() {
	while(f[0] < 10000) {
		int sum = 0, p = cur;
		while(p) {
			sum += p % 10;
			p /= 10;
		}
		if(sum == 10)	f[++f[0]] = cur;
		cur++;
	}
	getint(k);
	writeint(f[k]);
	return 0;
}
```

---

## 作者：Level_Down (赞：0)

## 2020/10/11 修订

### 题意简述

给定 k，求第 k 小的各个数位上的数加起来为 10 的数

### 方法

为什么题解里都只有暴力啊？懒得打暴力的我给你们介绍一种新方法。（虽然本质和暴力有点像但是较正统暴力有很大改进）

首先我们要打个表找规律：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long k,a[10005],t;
int pd(long long a)//判断各个数位上的数加起来是否为10。
{
	int sum = 0;
	while(a > 0) sum += a % 10,a /= 10;
	if (sum == 10) return 1;
	else return 0;
}
int main()
{
	for (int i = 1; i <= 1000; i++)
		{
			if (pd(i) == 1) cout << i << " ";//如果是就输出。
		}
	return 0;	
 } 
```

我们可以得到这个结果：

```
19 28 37 46 55 64 73 82 91 109 118 127 136 145 154 163 172 181 190 208 
217 226 235 244 253 262 271 280 307 316 325 334 343 352 361 370 406 415 
424 433 442 451 460 505 514 523 532 541 550 604 613 622 631 640 703 712 
721 730 802 811 820 901 910
```

在表里我们可以发现，每一个符合要求的数，与相邻的数的差都是9的倍数且至少是一倍。

于是我们可以操作 k 次，每次先加一个 9 ，然后一直加 9 直到符合要求即可。

还要注意一下答案的初值是10。

然后我们就可以打出AC代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long k,a = 10;
int pd(long long a)
{
	int sum = 0;
	while(a > 0) sum += a % 10,a /= 10;
	if (sum == 10) return 1;
	else return 0;
}
int main()
{
	cin >> k;
	for (int i = 1; i <= k; i++)
		{
			a += 9;//先加一个9
			while (pd(a) == 0) a += 9;//然后一直加 9 直到符合要求
		}
	cout << a;//输出答案	
	return 0;	
 } 
```

嗯看着比普通暴力清爽多了。



------------


[附赠我打的表（逃](https://www.luogu.com.cn/paste/vmtw7vqb)

---

## 作者：LucasXu80 (赞：0)

本文给大家介绍Python的做法。

**说明**：本份PY代码你**并不能AC**，因为会TLE（PY太慢，极端数据本地跑了十秒左右）。文末附有C++AC代码。


------------

首先，本题的核心思路一定在如何计算一个数的各位数字和，我看题解区没有这方面的讲解。

首先，拿到一个数，你可以很容易地分离出它的最后一位：

```cpp

sum+=n%10;//顺便加入累加器

```

但是这个时候你去分离倒数第二位就不方便了。因此，我们需要**去掉最后一位**，使得倒数第二位变成最后一位：

```cpp

n/=10;//PY中需要使用“//”运算符来自动向下取整

```
那么这个时候就完成了“去掉最后一位”，可以继续循环下去。

那么循环到什么时候为止呢？设想一个数$8$。

第一次，你把$8$%$10=8$加入累加器，并把$8/10=0$。

这个时候，你就**不需要继续循环**，因为$n$已经为$0$，没有数，不需要再找下去了。

```cpp

while (n) {
//相当于while (n>=0) {

```
好了，这下我们把那个函数搞定了。

剩下的就没什么难的了，代码中见~

PY**非AC**代码：

```python

import sys
def divide(n): #定义函数
    sum=0 #累加器
    while n>0: #n中还有数
        sum+=n%10 #将最后一位加入累加器
        n=n//10 #注意是//不是/
    return sum #返回累加器中的数
n=int(input())
cnt=0 #记录找到了第几个完美数
for i in range(20000000): #第10000个完美数应该是10800100,2e7够了
    if divide(i)==10: cnt+=1 #找到完美数，计数器+1
    if cnt==n: #第n个完美数
        print(i) #输出并结束程序（不然每一个点都要TLE了）
        sys.exit()

```
C++**AC**代码：

```cpp

#include <iostream>
using namespace std;
int divide(int n)
{
    int sum=0;
    while (n)
    {
        sum+=n%10;
        n/=10;
    }
    return sum;
}
int main()
{
    int n;
    cin>>n;
    int i=1,cnt=0;
    while (i++)
    {
        if (divide(i)==10) cnt++;
        if (cnt==n)
        {
            cout<<i;
            return 0;
        }
    }
    return 0;
}

```
（与PY同理，这里就不加注释了~）

在这种PY明显会超时的题目（尤其是这种做法），PY并不是一个明智的选择，但是如果$k$足够小，PY就可以方便地使用了。

最后，希望大家喜欢，求过求赞~

---

## 作者：cq_loves_Capoo (赞：0)

竟然没几篇题解！    
   
好吧这题其实直接暴力枚举是可以过的，也不用啥脑子。    
   
直接判断一个数的各个数位和是否等于 $10$ ，如果等于 $10$ 则计数器 $+1$ 。 当计数器等于 $k$ 时输出 $i$ 然后退出循环就好了。   
   
代码：   
   
```
#include<bits/stdc++.h>
#define endl "\n"
#define int long long//不知道具体要不要开 long long ，但是保险
#pragma GCC optimize(3)

using namespace std;
int n, num;
inline int sum_count (int x)//算出一个数各个位数的和
{
	int sum=0;
	for(int i=x; i>=1; i/=10) sum += i%10;
	return sum;
}
inline bool choose (int x)//如果等于10则返回true，不等于则返回false
{
	return sum_count(x) == 10;
}

signed main()
{
	ios::sync_with_stdio(false);
	/**/
	cin >> n;//输入
	for(int i=1; ; i++) 
	if (choose (i))//符合要求
	{
		num++;//计数器+1
		if(num == n)//如果计数器到了要求
			return cout << i , 0;//这是一个坏习惯
	}
}


```

---

