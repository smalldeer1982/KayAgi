# Save the problem!

## 题目描述

Attention: we lost all the test cases for this problem, so instead of solving the problem, we need you to generate test cases. We're going to give you the answer, and you need to print a test case that produces the given answer. The original problem is in the following paragraph.

People don't use cash as often as they used to. Having a credit card solves some of the hassles of cash, such as having to receive change when you can't form the exact amount of money needed to purchase an item. Typically cashiers will give you as few coins as possible in change, but they don't have to. For example, if your change is 30 cents, a cashier could give you a 5 cent piece and a 25 cent piece, or they could give you three 10 cent pieces, or ten 1 cent pieces, two 5 cent pieces, and one 10 cent piece. Altogether there are 18 different ways to make 30 cents using only 1 cent pieces, 5 cent pieces, 10 cent pieces, and 25 cent pieces. Two ways are considered different if they contain a different number of at least one type of coin. Given the denominations of the coins and an amount of change to be made, how many different ways are there to make change?

As we mentioned before, we lost all the test cases for this problem, so we're actually going to give you the number of ways, and want you to produce a test case for which the number of ways is the given number. There could be many ways to achieve this (we guarantee there's always at least one), so you can print any, as long as it meets the constraints described below.

## 样例 #1

### 输入

```
18
```

### 输出

```
30 4
1 5 10 25
```

## 样例 #2

### 输入

```
3
```

### 输出

```
20 2
5 2
```

## 样例 #3

### 输入

```
314
```

### 输出

```
183 4
6 5 2 139
```

# 题解

## 作者：Refined_heart (赞：2)

题目大意：给一个构造出某个数的方案数，根据方案数构造出这个数和凑成这个数的几个数。（有点拗口）

就是说，有几种面值不同的硬币凑出一个钱数，根据方案把钱数和面值构造出来。

$\text{Solution:}$

我们可以想一下用最简单的两个数来凑：$1,2$.

因为要凑的数没啥限制，那就大力构造一个。

考虑一个数$n$可以分成$n$个$1$，每次替换$2$个$1$换成一个$2$……如果有$A$种方案，$2A$的方案数就是$A+1$,因为除了替换的方案数还有全$1$的方案数。那我们把全$2$的方案数消去，也就是$2A-1$，就可以了。

也就是说，最后的答案就是$2A-1.$

几行就写完了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int A;
	cin>>A;
	cout<<A+A-1<<" "<<2<<endl;
	cout<<1<<" "<<2<<endl;
	return 0;
}
```


---

## 作者：Tomato_Ya (赞：1)

## 思路
由于题目中说如果有多种答案只用输出其中一种，并且所有的钱数都可以分成 $1$ 块钱和 $2$ 块钱，所以我们把输入的 $A$ 分成最简单的 $1$ 和 $2$，那么总钱数可以用 $2\times A-1$ 来表示。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

long long a;

int main(){
	
	cin>>a;

	cout<<2*a-1<<" 2\n1 2\n";
	
	return 0; 
} 
```


---

## 作者：Epi4any (赞：1)

题意：给你一个数 $A$ 能被其他几个数凑出来的总可能性，让你求这个 $A$。

第一眼看完感觉是深搜，苦苦想了半天，突然看到这一行字：
 >If there are multiple tests, print any of them

所以就是说要可以**找特殊解**喽，不难发现，当凑 $A$ 的数为 $1$ 和 $2$ 时，总数目可以直接用 $A$ 求出，即 $A\cdot2-1$。

代码：
```cpp
#include <iostream>
using namespace std;
int A;
int main() {
	cin>>A;
	cout<<(A<<1)-1<<" "<<2<<endl;
	cout<<1<<" "<<2<<endl;
	return 0;
}
```


---

## 作者：S__X (赞：0)

### 题意：
给你一个数 $A$ 表示能被其他几个数凑出来的方案，让你输出其中一个方案。
**注意**：是其中一个方案，如果有多个测试，请打印其中任何一个就可以了。

### 思路：
我们可以用最简单的两个数 $1$ 和 $2$，这两个数可以构成任意一个数。

例如：
- $n$ 为奇数，$n$ 等于 $\frac{n-1}{2}$ 个 $2$ 和一个 $1$ 构成。
- $n$ 为偶数，$n$ 等于 $\frac{n}{2}$ 个 $2$ 构成。

接下来考虑 $n$ 拆分成 $1$ 和 $2$ 有多少种方法。

因为 $n$ 等于 $\left\lfloor\frac{n}{2}\right\rfloor$ 个 $2$，所以 $2$ 的个数可以是 $0$ 到 $\left\lfloor\frac{n}{2}\right\rfloor$，就有 $\left\lfloor\frac{n}{2}\right\rfloor+1$ 种方案。要使 $A$ 等于方案数，那么 $A=\left\lfloor\frac{n}{2}\right\rfloor+1$。

反之，知道 $A$，$n=2A-1$。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int A;
int main(){
	cin>>A;
	cout<<A*2-1<<" "<<2<<endl;
	cout<<1<<" "<<2<<endl;
	return 0;
}


```

---

## 作者：封禁用户 (赞：0)

思路&&题意
--
题意类似倒推，但是其实给出任意一组合理的解就可以了,其中最简单的就是 $1$ 和 $2$ 。

数总和为 $n$ ，设有 $a$ 个 $2$ ,则共有 $(n-2a)$  个 $1$ ,那么 $a$ 可以从 $1$ 取到 $n/2$ ,共有 $2a-1$ 种方法。

代码
--
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	
	cin>>n;
	cout<<n*2-1<<" "<<2<<endl;
	cout<<1<<" "<<2<<endl;
	return 0;
}

```


---

## 作者：oddy (赞：0)

## Description

给出找零方案数，求任意一组合法的找零总数和零钱面值。

## Solution

考虑只用面值为 $1$ 和 $2$ 的两种零钱。

设 $a$ 为找零方案数，则可将找零总数设为 $2a - 1$，因为顾客可以选择要 $0 \sim a - 1$ 枚“2”，剩下的全要“1”。

## Code

```cpp
#include <cstdio>

int main() {
    int a;
    scanf("%d", &a);
    printf("%d 2\n1 2", (a << 1) - 1); // a << 1 在 C 语言里相当于 2 × a
    return 0;
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 第一眼以为是个 dp，实际上这很很简单。

- 这题只要求求出一种答案，无特殊限制，所以**别相信样例！**。

- 想一想可以知道，任何数都可以用 $1$ 和 $2$ 这两个数凑出：对于奇数 $n$，用 $(n-1)\div 2$ 个 $2$ 和一个 $1$ 即可凑出出；对于偶数 $n$，用 $n\div 2$ 个 $2$ 即可凑出（也有其他方法可以凑得）。

- 剩下一个 $n$，就考虑如何将分成多个 $1$ 和 $2$ 的和的方案数，即为：$2A-1$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int A;

int main()
{
	cin >> A;
	cout << A + A - 1 << " " << 2 << endl;
	cout << 1 << " " << 2 << endl;
	return 0;
}
```


---

