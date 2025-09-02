# 题目信息

# Longest Divisors Interval

## 题目描述

Given a positive integer $ n $ , find the maximum size of an interval $ [l, r] $ of positive integers such that, for every $ i $ in the interval (i.e., $ l \leq i \leq r $ ), $ n $ is a multiple of $ i $ .

Given two integers $ l\le r $ , the size of the interval $ [l, r] $ is $ r-l+1 $ (i.e., it coincides with the number of integers belonging to the interval).

## 说明/提示

In the first test case, a valid interval with maximum size is $ [1, 1] $ (it's valid because $ n = 1 $ is a multiple of $ 1 $ ) and its size is $ 1 $ .

In the second test case, a valid interval with maximum size is $ [4, 5] $ (it's valid because $ n = 40 $ is a multiple of $ 4 $ and $ 5 $ ) and its size is $ 2 $ .

In the third test case, a valid interval with maximum size is $ [9, 11] $ .

In the fourth test case, a valid interval with maximum size is $ [8, 13] $ .

In the seventh test case, a valid interval with maximum size is $ [327869, 327871] $ .

## 样例 #1

### 输入

```
10
1
40
990990
4204474560
169958913706572972
365988220345828080
387701719537826430
620196883578129853
864802341280805662
1000000000000000000```

### 输出

```
1
2
3
6
4
22
3
1
2
2```

# AI分析结果

### 题目翻译
# 最长因数区间

## 题目描述
给定一个正整数 $n$，找出正整数区间 $[l, r]$ 的最大长度，使得对于区间内的每个 $i$（即 $l \leq i \leq r$），$n$ 都是 $i$ 的倍数。

给定两个整数 $l\leq r$，区间 $[l, r]$ 的长度为 $r - l + 1$（即该区间内整数的数量）。

## 说明/提示
在第一个测试用例中，一个最大长度的有效区间是 $[1, 1]$（它是有效的，因为 $n = 1$ 是 $1$ 的倍数），其长度为 $1$。

在第二个测试用例中，一个最大长度的有效区间是 $[4, 5]$（它是有效的，因为 $n = 40$ 是 $4$ 和 $5$ 的倍数），其长度为 $2$。

在第三个测试用例中，一个最大长度的有效区间是 $[9, 11]$。

在第四个测试用例中，一个最大长度的有效区间是 $[8, 13]$。

在第七个测试用例中，一个最大长度的有效区间是 $[327869, 327871]$。

## 样例 #1
### 输入
```
10
1
40
990990
4204474560
169958913706572972
365988220345828080
387701719537826430
620196883578129853
864802341280805662
1000000000000000000
```
### 输出
```
1
2
3
6
4
22
3
1
2
2
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路基本一致，都是从 $1$ 开始枚举正整数，找到第一个不是 $n$ 的因数的数 $x$，那么 $x - 1$ 就是满足条件的最长区间长度。部分题解还对这一结论进行了证明，利用了连续正整数的性质，即长度为 $x$ 的连续正整数区间内必定存在 $x$ 的倍数。不同题解在代码实现上略有差异，但整体逻辑相同。

### 高星题解
- **Czy_Lemon（4星）**
    - **关键亮点**：思路清晰，对结论进行了详细的证明，先分析了 $n$ 为奇数的特殊情况，然后通过反证法证明了从 $1$ 开始枚举的正确性。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
int t,n;
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
        int ans=1;
        while(n%ans==0) ans++;
        printf("%lld\n",ans-1);
    }
    return 0;
}
```
核心实现思想：从 $1$ 开始枚举，不断检查当前数是否是 $n$ 的因数，直到找到第一个不是因数的数，输出该数减 $1$ 作为结果。

- **Scene（4星）**
    - **关键亮点**：通过逆向思考，结合具体例子说明一个数不是 $n$ 的因数时，其倍数不能在区间内，从而得出结论，思路直观易懂。
    - **核心代码**：
```cpp
ll T;
int main()
{
    cin>>T;
    while(T--)
    {
        ll n; cin>>n; ll i=1;
        for(;i<=100;i++)
        {
            if(n%i!=0) break;
        }
        write(i-1),pc('\n'); 
    }
    return 0;
}
```
核心实现思想：从 $1$ 开始枚举，当遇到第一个不是 $n$ 的因数的数时停止，输出该数减 $1$。

- **panhongxuanyyds（4星）**
    - **关键亮点**：给出了两种解法，第一种解法对结论进行了证明，第二种解法通过设定阈值在一定范围内找最大合法区间，提供了不同的思考角度。
    - **核心代码（解法一）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, m, x;
int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        x = 1;
        while (n % x == 0) {
            ++x;
        }
        --x;
        printf("%lld\n", x);
    }
    return 0;
}
```
核心实现思想：从 $1$ 开始枚举，找到第一个不是 $n$ 的因数的数，输出该数减 $1$。

### 关键思路或技巧
- **数学性质的运用**：利用连续正整数的性质，即长度为 $x$ 的连续正整数区间内必定存在 $x$ 的倍数，来证明从 $1$ 开始枚举的正确性。
- **逆向思考**：通过分析不是 $n$ 的因数的数对区间的限制，得出结论。

### 可拓展之处
同类型题目可能会对区间的条件进行变化，或者结合其他数学知识，如质数、最大公约数等。类似的算法套路可以用于解决一些与因数、倍数相关的区间问题，通过分析数的性质来确定区间的范围。

### 推荐洛谷题目
- P1072 [NOIP2009 提高组] Hankson 的趣味题
- P1306 斐波那契公约数
- P2568 GCD

### 个人心得摘录与总结
- **tang_mx**：表示自己作为蒟蒻，一开始没发现解法，花了很长时间，提示我们遇到问题可以通过举例子分析因数分布情况来寻找思路。 

---
处理用时：38.48秒