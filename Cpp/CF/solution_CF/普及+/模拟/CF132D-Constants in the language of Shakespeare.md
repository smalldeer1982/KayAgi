# Constants in the language of Shakespeare

## 题目描述

Shakespeare is a widely known esoteric programming language in which programs look like plays by Shakespeare, and numbers are given by combinations of ornate epithets. In this problem we will have a closer look at the way the numbers are described in Shakespeare.

Each constant in Shakespeare is created from non-negative powers of 2 using arithmetic operations. For simplicity we'll allow only addition and subtraction and will look for a representation of the given number which requires a minimal number of operations.

You are given an integer $ n $ . You have to represent it as $ n=a_{1}+a_{2}+...+a_{m} $ , where each of $ a_{i} $ is a non-negative power of 2, possibly multiplied by -1. Find a representation which minimizes the value of $ m $ .

## 样例 #1

### 输入

```
1111
```

### 输出

```
2
+2^4
-2^0
```

## 样例 #2

### 输入

```
1010011
```

### 输出

```
4
+2^0
+2^1
+2^4
+2^6
```

# 题解

## 作者：Digital_Sunrise (赞：0)

[link](https://www.luogu.com.cn/problem/CF132D)

## 题意

给出一个长度为 $n(1\le n\le10^6)$ 的 $01$ 串，表示一个二进制串。

求表示此二进制串最少需要多少个**不同** $2$ 的次幂相加/相减操作。

要求输出最小操作次数以及相应的相加/相减的操作，输出顺序随意。

## 思路

对于一个连续的 $1$ 构成的子串，有两种构造方法：

1. 每一位依次加 $1$
2. 将整个子串的前一位加 $1$ ，整个子串的最后一位减 $1$

显然对于长度大于等于 $2$ 的连续 $1$ 子串，后者更优。

注意考虑 $...111011...$ 即两个连续 $1$ 子串之间夹了一个 $0$ 的情况，此时可以将两个子串当做一个考虑，然后把中间的 $0$ 减一次。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int cnt,n;
int a[1000005];
int siz[1000005];
vector <int> Ans;

int main()
{
	cin >> s;
	n = s.length();
	for(int i = 0;i < n;i++)
		a[n - 1 - i] = s[i] - '0';
	for(int i = 0;i < n;i++)
	{
		if(!a[i])
			continue;
		int j = i;
//		for(j;flag[j];j++);
        while(a[j]) j++;
        if(j - i >= 2)
        {
            a[i] = -1;
            for(int k = i + 1;k <= j;k++)
                a[k] = 0;
            a[j] = 1;
        }
        i = j - 1;
	}
    for(int i = 0;i <= n;i++)
        cnt += (a[i] == 1 or a[i] == -1);
    cout << cnt << endl;
    for(int i = 0;i <= n;i++)
    {
        if(a[i] == 1)
            printf("+2^%d\n",i);
        if(a[i] == -1)
            printf("-2^%d\n",i);
    }
	return 0;
}
```

---

