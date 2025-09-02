# 题目信息

# Digital Counter

## 题目描述

Malek lives in an apartment block with $ 100 $ floors numbered from $ 0 $ to $ 99 $ . The apartment has an elevator with a digital counter showing the floor that the elevator is currently on. The elevator shows each digit of a number with $ 7 $ light sticks by turning them on or off. The picture below shows how the elevator shows each digit.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495A/82c4b2ab842edc90f41be56a97fcef1aaf93be0a.png)One day when Malek wanted to go from floor $ 88 $ to floor $ 0 $ using the elevator he noticed that the counter shows number $ 89 $ instead of $ 88 $ . Then when the elevator started moving the number on the counter changed to $ 87 $ . After a little thinking Malek came to the conclusion that there is only one explanation for this: One of the sticks of the counter was broken. Later that day Malek was thinking about the broken stick and suddenly he came up with the following problem.

Suppose the digital counter is showing number $ n $ . Malek calls an integer $ x $ ( $ 0<=x<=99 $ ) good if it's possible that the digital counter was supposed to show $ x $ but because of some(possibly none) broken sticks it's showing $ n $ instead. Malek wants to know number of good integers for a specific $ n $ . So you must write a program that calculates this number. Please note that the counter always shows two digits.

## 说明/提示

In the first sample the counter may be supposed to show $ 88 $ or $ 89 $ .

In the second sample the good integers are $ 00 $ , $ 08 $ , $ 80 $ and $ 88 $ .

In the third sample the good integers are $ 03,08,09,33,38,39,73,78,79,83,88,89,93,98,99 $ .

## 样例 #1

### 输入

```
89
```

### 输出

```
2
```

## 样例 #2

### 输入

```
00
```

### 输出

```
4
```

## 样例 #3

### 输入

```
73
```

### 输出

```
15
```

# AI分析结果

### 题目翻译
# 数字计数器

## 题目描述
Malek 住在一栋有 100 层的公寓楼里，楼层编号从 0 到 99。公寓里有一部电梯，电梯上有一个数字计数器，显示电梯当前所在的楼层。电梯用 7 根发光条来显示每个数字，通过点亮或熄灭这些发光条来显示不同的数字。下图展示了电梯是如何显示每个数字的。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF495A/82c4b2ab842edc90f41be56a97fcef1aaf93be0a.png)

有一天，当 Malek 想从 88 层乘坐电梯到 0 层时，他注意到计数器显示的是 89 而不是 88。然后当电梯开始运行时，计数器上的数字变成了 87。经过一番思考，Malek 得出结论：只有一种解释：计数器的其中一根发光条坏了。那天晚些时候，Malek 还在思考那根坏掉的发光条，突然他想到了以下问题。

假设数字计数器显示的数字是 n。Malek 称一个整数 x（0 <= x <= 99）是“好的”，如果计数器原本可能要显示 x，但由于某些（可能没有）发光条损坏而显示成了 n。Malek 想知道对于一个特定的 n，有多少个“好的”整数。所以你必须编写一个程序来计算这个数字。请注意，计数器总是显示两位数字。

## 说明/提示
在第一个样例中，计数器原本可能要显示 88 或 89。

在第二个样例中，“好的”整数是 00、08、80 和 88。

在第三个样例中，“好的”整数是 03、08、09、33、38、39、73、78、79、83、88、89、93、98、99。

## 样例 #1
### 输入
```
89
```
### 输出
```
2
```

## 样例 #2
### 输入
```
00
```
### 输出
```
4
```

## 样例 #3
### 输入
```
73
```
### 输出
```
15
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是先通过枚举得出 0 - 9 每个数字可能的显示情况数量，再利用乘法原理，将输入的两位数的十位和个位各自可能的显示情况数量相乘，得到最终结果。各题解的主要区别在于代码实现的细节，如输入输出方式、变量命名等。

### 所选题解
- **作者：L_zaa_L (赞：6)，4星**
    - **关键亮点**：思路清晰，代码简洁，直接给出了每个数字对应的可能情况数量数组，通过简单的输入输出和乘法运算得到结果。
- **作者：Bpds1110 (赞：2)，4星**
    - **关键亮点**：对思路的解释详细，明确指出组成两位数的方案数是十位方案数乘个位方案数，并结合图片说明各个数位上数字的可能性。
- **作者：sanjingshou14 (赞：2)，4星**
    - **关键亮点**：对题目思路的阐述较为全面，不仅说明了如何枚举每个数字的可能情况，还提到了利用排列组合的思想计算最终结果。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[11]={2,7,2,3,3,4,2,5,1,2};
int main(){
    cin>>n;
    cout<<a[n%10]*a[n/10];
    return 0;
}
```
**核心实现思想**：首先定义一个数组 `a` 来存储 0 - 9 每个数字可能的显示情况数量。然后通过 `cin` 输入一个两位数 `n`，利用 `n % 10` 得到个位数字，`n / 10` 得到十位数字，最后将这两个数字对应的数组元素相乘并输出结果。

### 扩展思路
同类型题目通常会涉及根据某些条件枚举所有可能的情况，再进行相应的计算。例如，一些关于图形显示、密码组合等问题，可能需要根据给定的规则枚举所有可能的状态，然后利用乘法原理、加法原理等进行计算。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径枚举和动态规划思想。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：需要枚举栈的操作情况。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：涉及质数判断和回文数枚举。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：29.47秒