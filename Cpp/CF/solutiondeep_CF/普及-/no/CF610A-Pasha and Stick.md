# 题目信息

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

# AI分析结果

### 题目翻译
# Pasha和木棍

## 题目描述
Pasha有一根正整数长度为 $ n $ 的木棍。他想正好切三刀，把木棍分成四部分。每部分的长度都必须是正整数，显然这四部分长度之和为 $ n $ 。

Pasha喜欢长方形但讨厌正方形，所以他想知道，有多少种方法可以把木棍分成四部分，使得这些部分能组成一个长方形，但不能组成正方形。

你的任务是帮助Pasha并计算出这样的方法的数量。如果存在某个整数 $ x $ ，使得第一种切割方法中长度为 $ x $ 的部分的数量与第二种切割方法中长度为 $ x $ 的部分的数量不同，则这两种切割木棍的方法被认为是不同的。

## 说明/提示
在第一个样例中，只有一种方法来分割木棍 {1, 1, 2, 2}。
在第二个样例中，有四种方法来分割木棍 {1, 1, 9, 9}、{2, 2, 8, 8}、{3, 3, 7, 7} 和 {4, 4, 6, 6}。注意 {5, 5, 5, 5} 不符合要求。

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

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先判断木棍长度 $ n $ 的奇偶性。若 $ n $ 为奇数，由于长方形周长为偶数，所以无法组成长方形，方案数为 0；若 $ n $ 为偶数，设长方形长和宽分别为 $ a $ 和 $ b $ ，则 $ n = 2(a + b) $ ，然后再根据 $ n/2 $ 的奇偶性进一步讨论，同时要排除能组成正方形的情况。各题解的区别主要在于推导最终公式的过程和代码实现方式。

### 所选题解
- **Isprime（5星）**：关键亮点是思路清晰，对 $ n/2 $ 为奇数和偶数的情况分别进行了详细分析，代码简洁明了。
- **Warriors_Cat（4星）**：关键亮点是先设出长方形的长和宽，通过公式推导得出结论，并且使用了位运算，代码有一定优化。
- **Skyjoy（4星）**：关键亮点是思路简洁直接，代码实现简单易懂。

### 重点代码
#### Isprime
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
核心实现思想：先判断 $ n $ 的奇偶性，若为奇数输出 0，若为偶数则直接使用公式 $ (n/2 - 1)/2 $ 计算方案数。

#### Warriors_Cat
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n;
int main(){
    scanf("%d", &n);
    if(n & 1) puts("0");
    else printf("%d\n", ((n >> 1) - 1) >> 1);
    return 0;
}
```
核心实现思想：使用位运算判断 $ n $ 的奇偶性，若为奇数输出 0，若为偶数则使用位运算实现公式 $ (n/2 - 1)/2 $ 计算方案数。

#### Skyjoy
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
核心实现思想：先判断 $ n $ 的奇偶性，若为奇数输出 0，若为偶数则使用公式 $ (n/2 - 1)/2 $ 计算方案数。

### 关键思路或技巧
- 利用长方形周长的性质，先判断木棍长度的奇偶性进行初步筛选。
- 对于偶数长度的木棍，通过数学推导得出方案数的计算公式，同时注意排除能组成正方形的情况。
- 可以使用位运算来优化判断奇偶性和除法运算。

### 拓展思路
同类型题可能会改变切割的次数、要求组成的图形（如平行四边形、梯形等），或者增加其他限制条件。解题时依然可以从图形的性质出发，通过数学推导来解决问题。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)

### 个人心得
无

---
处理用时：30.11秒