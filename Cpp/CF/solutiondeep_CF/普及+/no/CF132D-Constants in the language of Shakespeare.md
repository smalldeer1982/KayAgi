# 题目信息

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

# AI分析结果

### 题目内容
# 莎士比亚语言中的常量

## 题目描述
莎士比亚是一种广为人知的深奥编程语言，其程序看起来就像莎士比亚的戏剧，数字由华丽的修饰词组合表示。在本题中，我们将深入研究莎士比亚语言中数字的描述方式。

莎士比亚语言中的每个常量都是通过2的非负次幂，运用算术运算创建的。为简化问题，我们仅允许加法和减法，并寻找用最少运算次数表示给定数字的方法。

给定一个整数 $n$ ，你必须将其表示为 $n=a_{1}+a_{2}+...+a_{m}$ ，其中每个 $a_{i}$ 是2的非负次幂，可能乘以 -1 。找到使 $m$ 值最小的表示方法。

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

### 算法分类
贪心

### 综合分析与结论
该题解的核心思路是基于贪心策略，对于输入的二进制串中连续的1子串，通过比较两种构造方式，选择操作次数更少的方式来表示数字，从而达到最小化操作次数的目的。其难点在于如何处理连续1子串以及相邻子串间夹0的情况。题解整体思路清晰，代码实现也较为简洁明了。

### 所选的题解
 - **星级**：4星
 - **关键亮点**：通过贪心策略，对连续1子串采用更优的构造方式，减少操作次数；代码简洁，逻辑清晰。
 - **重点代码**：
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
核心实现思想：先将输入的字符串转化为二进制数组，从左到右遍历数组，若遇到1则寻找连续1子串的结束位置，对于长度大于等于2的连续1子串，采用贪心策略修改数组表示方式，最后统计操作数并输出结果。

### 最优关键思路或技巧
贪心策略的运用，针对连续1子串选择更优构造方式，减少操作次数。

### 可拓展之处
同类型题可考虑更多限制条件下的数字表示问题，类似算法套路可用于其他通过选择最优局部策略解决全局最优解的问题。

### 推荐题目
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080) 

---
处理用时：44.12秒