# Bad Ugly Numbers

## 题目描述

You are given a integer $ n $ ( $ n > 0 $ ). Find any integer $ s $ which satisfies these conditions, or report that there are no such numbers:

In the decimal representation of $ s $ :

- $ s > 0 $ ,
- $ s $ consists of $ n $ digits,
- no digit in $ s $ equals $ 0 $ ,
- $ s $ is not divisible by any of it's digits.

## 说明/提示

In the first test case, there are no possible solutions for $ s $ consisting of one digit, because any such solution is divisible by itself.

For the second test case, the possible solutions are: $ 23 $ , $ 27 $ , $ 29 $ , $ 34 $ , $ 37 $ , $ 38 $ , $ 43 $ , $ 46 $ , $ 47 $ , $ 49 $ , $ 53 $ , $ 54 $ , $ 56 $ , $ 57 $ , $ 58 $ , $ 59 $ , $ 67 $ , $ 68 $ , $ 69 $ , $ 73 $ , $ 74 $ , $ 76 $ , $ 78 $ , $ 79 $ , $ 83 $ , $ 86 $ , $ 87 $ , $ 89 $ , $ 94 $ , $ 97 $ , and $ 98 $ .

For the third test case, one possible solution is $ 239 $ because $ 239 $ is not divisible by $ 2 $ , $ 3 $ or $ 9 $ and has three digits (none of which equals zero).

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
-1
57
239
6789```

# 题解

## 作者：AutumnKite (赞：7)

为什么您们都能想到构造 $2333\cdots 333$ 啊 QAQ

显然一个能被 $p$ 整除的数，加或减一个不能被 $p$ 整除的数后，不能被 $p$ 整除。

我们考虑 $777\cdots 777$ 能被 $7$ 整除，而 $777\cdots 77x$（$x > 0$）不能被 $7$ 整除。

又~~根据小学数学知识~~，能被 $4$ 整除的数的特征是最后两位能被 $4$ 整除，由于 $74\bmod 4\ne 0$，所以我们构造 $777\cdots 774$ 即可。

注意需要特判 $n=1$。

```cpp
int n;
void solve(){
	read(n);
	if (n == 1) return print(-1), void(0);
	for (register int i = 1; i < n; ++i) putchar('7');
	putchar('4'), putchar('\n');
}
```

---

## 作者：Lylighte (赞：2)

#### 题意描述

给你一个正整数 n，找到任意一个整数 s，要求：

- $s>0$；

- $s$ 有 $n$ 位；

- $s$ 的任意一位数字不为 $0$；

- $s$ 不能被其数位上的任意一个数整除。

$t$ 组数据，对于每个 $n$，输出一个符合要求的 $s$ 即可。

#### 一种思路

直接枚举是不可能的，因为 $s$ 有 $n$ 位，并且所有 $n$ 的和最大为 $10^5$。所以需要构造。

考虑第四点要求：「 $s$ 不能被其数位上的任意一个数整除。」能填的数只有 $2$ 到 $9$，列举出这些数整除的特征：

- $2$ 可以整除末位是偶数的整数；

- $3$ 可以整除各位上的数字之和为 $3$ 的整数倍的整数；

- $4$ 可以整除末两位能被 $4$ 整除的整数；

- $5$ 可以整除末位是 $0$ 或 $5$ 的整数；

- $6$ 可以整除同时满足 $2$ 和 $3$ 的整除条件的整数；

- $7$ 可以整除末三位数字所组成的数与末三位以前的数字所组成的数的差能被 $7$ 整除的整数；

- $8$ 可以整除末三位能被 $8$ 整除的整数；

- $9$ 可以整除各位上的数字之和为 $9$ 的整数倍的整数。

找寻切入点：$3$ 的整除性质。让 $s$ 的 $n-1$ 位数字都为 $3$，剩下一位数字不为 $3$ 的整数倍即可。

让剩下一位数字为 $2$ 怎样？$s=233\cdots 3$（有 $n-1$ 个 $3$）。

很容易证明这个数满足上述要求：末位不是偶数，数位之和不为 $3$ 的倍数。

同样还有 $433\cdots 3$，$533\cdots 3$，$833\cdots 3$ 等数字也符合要求。

所以，当 $n$ 不为 $1$ 时，输出 $233\cdots 3$ （或其它符合要求的数）即可。$n$ 为 $1$ 时只能输出 $-1$。

#### 代码

[戳这里。](https://codeforces.com/contest/1326/submission/73687785)

---

## 作者：andyli (赞：1)

题意：  
找出满足每一位均不为 $0$ 且不能被其任意一位整除的一个 $n$ 位正整数， $1\leq n\leq 10^5$ ，无解输出 $-1$ 。  

分析：  
当 $n=1$ 时显然无解，当 $n>1$ 时，可构造一个第 $n$ 位为 $2$ ，其余数位为 $3$ 的正整数，易知该数不能被 $2$ 或 $3$ 整除，直接输出即可。  
时间复杂度 $\mathcal O(n)$ 。  

代码如下 ([快读模板](https://www.luogu.com.cn/blog/andyli/read-template))：  
```cpp
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        if (n == 1) {
            writeln(-1);
            continue;
        }
        io.putch('2');
        for (int i = 2; i <= n; i++)
            io.putch('3');
        writeln();
    }
    return 0;
}
```


---

## 作者：chenyilai (赞：1)

$n$的数据范围很大，所以这道题要用数学方法。

思路：先输出$n-1$个$2$，在输出$9$，不过这个数有$9$的倍数个$2$时$\bmod\,9=0$，例如$2222222229\bmod9=0$，因此要进行判断。

有了思路后，这道题就So easy了。

AC代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n;
int main()
{
	scanf("%lld",&T);
	while (T--){
		scanf("%lld",&n);
		if (n==1) {
			printf("-1\n"); continue;
		}//对1进行特判。
		for (int i=2;i<n;i++) printf("2");
		if ((n-1)%9==0) printf("99\n");
		else printf("29\n");//进行判断
	}
	return 0;
} 
```
当然，这不是唯一解法，还有很多解法，例如输出一个$2$再输出$n-1$个$9$，在这就不一一列举了。

最后还要提醒大家：莫抄袭，没了AC记录，空悲切。

---

## 作者：StudyingFather (赞：0)

$n=1$ 时显然无解。

当 $n \gt 1$ 时，我们可以这样构造：$233\ldots 3$（开头一个 $2$，后面 $n-1$ 个 $3$），容易发现这种构造方法是满足要求的。

```cpp
// Problem : A. Bad Ugly Numbers
// Contest : Codeforces Global Round 7
// URL : https://codeforces.com/contest/1326/problem/A
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
using namespace std;
int main()
{
 int t;
 cin>>t;
 while(t--)
 {
  int n;
  cin>>n;
  if(n==1)cout<<-1<<endl;
  else
  {
   cout<<2;
   for(int i=2;i<=n;i++)
    cout<<3;
   cout<<endl;
  }
 }
 return 0;
}
```

---

