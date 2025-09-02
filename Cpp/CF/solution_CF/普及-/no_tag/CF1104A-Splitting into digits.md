# Splitting into digits

## 题目描述

Vasya has his favourite number $ n $ . He wants to split it to some non-zero digits. It means, that he wants to choose some digits $ d_1, d_2, \ldots, d_k $ , such that $ 1 \leq d_i \leq 9 $ for all $ i $ and $ d_1 + d_2 + \ldots + d_k = n $ .

Vasya likes beauty in everything, so he wants to find any solution with the minimal possible number of different digits among $ d_1, d_2, \ldots, d_k $ . Help him!

## 说明/提示

In the first test, the number $ 1 $ can be divided into $ 1 $ digit equal to $ 1 $ .

In the second test, there are $ 3 $ partitions of the number $ 4 $ into digits in which the number of different digits is $ 1 $ . This partitions are $ [1, 1, 1, 1] $ , $ [2, 2] $ and $ [4] $ . Any of these partitions can be found. And, for example, dividing the number $ 4 $ to the digits $ [1, 1, 2] $ isn't an answer, because it has $ 2 $ different digits, that isn't the minimum possible number.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
1 ```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
2 2
```

## 样例 #3

### 输入

```
27
```

### 输出

```
3
9 9 9
```

# 题解

## 作者：_Clown_ (赞：6)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF1104A}$|$\texttt{CF难度:800}$|[$\texttt{On 2020/12/26}$](https://www.luogu.com.cn/record/44280106)|
# 解析
题目大意是：

给定一个数字$N$,请将它拆分成$X+X+\cdots + X$,$X\in [1,9]$,使得$\sum_{i=1}^KX=N$,并且使$X$都相等

（已经简化题目大意）

-----

我们很容易想到：
- $X=1$

因此，输出就是：

$N$

$1,1,\cdots,1,1$
# 代码
```cpp
/*
Author:Xsmyy
Problem:CF1104A
Date:2020/12/26
*/
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
#define Fr(i,A,B,X) for(i=A;i<=B;i+=X)
#define Reg register
#define Ll long long
#define Iln inline
#define Str string
#define Chr char
#define Vod void
#define In int
using namespace std;
In main(Vod)
{
	BetterIO;
	Reg In N;
	cin>>N;
	Reg In i;
	cout<<N<<endl;
	Fr(i,1,N,1)
	{
		putchar('1'),putchar(' ');
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：Chtholly_L (赞：3)

### 题意：

给你一个数 $n$，把这个数字分解，使分解后的数字每个都相等（分解出的数必须小于等于 $9$ ）。输出分解出的数的个数和结果。如果有多组答案，输出任意一组。

---

### 分析：

假设输入的数 $n$ 的一个因子为 $a$，那么对应的另一个因子为 $b=\frac{n}{a}$，因此，我们只需要输出 $a$ 个 $b$ 或 $b$ 个 $a$。

不难发现，任意一个数字 $n$ 的因子都有 $1$ 和 $n$ 这一组，而毫无疑问 $1<9$，因此，我们只需要先输出一个 $n$，再输出 $n$ 个 $1$ 即可。

---

### 代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int main(){
    int n;
    cin>>n;
    cout<<n<<endl;
    for(int i=1;i<=n;i++){
        cout<<1<<' ';
    }
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定一个数字 $n$，试将这个数分成若干个数，使得这些数都相等，输出任意一个方案均可。

**数据范围：$1\leqslant n\leqslant 1000$。**
## Solution
题目里面讲了，能够满足“所有数都相等”的序列都可以输出，那我们直接输出 $n$，再输出 $n$ 个 $1$ 就好了。
## Code
```cpp
int n, k = 1;

int main() {
	getint(n);
	writeint(n), putchar('\n');
	_for(i, 1, n)	writeint(k), putchar(' ');
	return 0;
}
```

---

## 作者：YosemiteHe (赞：0)

自然数 $n$ 可以理解成 $n$ 个 $1$ 相加，此时 $k = n$，符合题意的 $k \leq n$。

于是第一行输出 $n$，第二行输出 $n$ 个 $1$ 就能AC了。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(void){
    cin >> n;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "1 ";
    }
    return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

题意：把n分成k个数（均为1~9的整数），使得这k个数的和为n，且这k个数尽量相同。

由于可以分成1，二1又是任何数的因子，故可以把n分成n个1，于是水过。

~~英文题面真能迷惑人啊！~~
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int i;
	cout<<n<<endl;
	for (i=1;i<=n;i++)
	{
		cout<<1<<" ";
	}
	return 0;
}
```

---

## 作者：zsc2003 (赞：0)

#### 2019.1.22 codeforces div2 

##### 题目大意:

读入一个正整数$n$,请把$n$拆成一些数相加，这些数必须相同，并且必须大于$0$，小于$9$

输出一种一种方案即可

##### 思路

由于输出任意一种方案，

所以直接让$n$由$n$个$1$相加即可

##### 下面附上本人的代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
int n;
int main()
{
	n=read();
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("1 ");
	return 0;
}
```



---

## 作者：DinnerHunt (赞：0)

因为`1`是任何数的因子,所以它可以组成任何数

```cpp
#include <cstdio>
using namespace std;
int main()
{
    // freopen("a.in","r",stdin);
    // freopen("k.out","w",stdout);
    int n;scanf("%d",&n); printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d ",1);
    return 0;
}
```

---

## 作者：Doubeecat (赞：0)

第一次打Div2碰到有这种巧妙做法的题目。。。。
（但是本人英语不好还是被卡掉了）
根据题面意思，我们只要输出一种可以平分的方案即可，而我们知道，每一个数$n$都可以分解为$n = 1 * n$的格式
所以我们只要暴力输出n个1就行了。
代码：
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << n << endl;
    for (int i = 1;i <= n;i++) {
        cout << 1 << " ";
    } 
    return 0;
} 

```

---

