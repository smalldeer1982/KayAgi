# 题目信息

# Vanya and Cards

## 题目描述

Vanya loves playing. He even has a special set of cards to play with. Each card has a single integer. The number on the card can be positive, negative and can even be equal to zero. The only limit is, the number on each card doesn't exceed $ x $ in the absolute value.

Natasha doesn't like when Vanya spends a long time playing, so she hid all of his cards. Vanya became sad and started looking for the cards but he only found $ n $ of them. Vanya loves the balance, so he wants the sum of all numbers on found cards equal to zero. On the other hand, he got very tired of looking for cards. Help the boy and say what is the minimum number of cards does he need to find to make the sum equal to zero?

You can assume that initially Vanya had infinitely many cards with each integer number from $ -x $ to $ x $ .

## 说明/提示

In the first sample, Vanya needs to find a single card with number -2.

In the second sample, Vanya needs to find two cards with number 2. He can't find a single card with the required number as the numbers on the lost cards do not exceed 3 in their absolute value.

## 样例 #1

### 输入

```
3 2
-1 1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
-2 -2
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# 万尼亚和卡片

## 题目描述
万尼亚喜欢玩。他甚至有一套专门用来玩的卡片。每张卡片上都有一个整数。卡片上的数字可以是正数、负数，甚至可以等于零。唯一的限制是，每张卡片上的数字的绝对值不超过 $x$。

娜塔莎不喜欢万尼亚花很长时间玩，所以她把他所有的卡片都藏了起来。万尼亚很伤心，开始寻找卡片，但他只找到了 $n$ 张。万尼亚喜欢平衡，所以他希望找到的所有卡片上的数字之和等于零。另一方面，他找卡片找得很累了。帮助这个男孩，告诉他他至少还需要找到多少张卡片才能使数字之和等于零？

你可以假设最初万尼亚有无数张数字从 $-x$ 到 $x$ 的卡片。

## 说明/提示
在第一个样例中，万尼亚需要找到一张数字为 -2 的卡片。

在第二个样例中，万尼亚需要找到两张数字为 2 的卡片。他不能只找一张满足要求的卡片，因为丢失卡片上的数字的绝对值不超过 3。

## 样例 #1
### 输入
```
3 2
-1 1 2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2 3
-2 -2
```
### 输出
```
2
```

### 算法分类
数学

### 综合分析与结论
这三道题解的核心思路都是先求出已找到卡片数字的总和 `sum`，然后计算需要补充多少张绝对值不超过 `x` 的卡片使总和为 0。不同题解的主要区别在于对结果的计算方式，有的直接使用 `ceil` 函数，有的通过判断余数来计算。

### 题解评分与亮点
- **Ninelife_Cat**：4星。思路简洁明了，直接给出结论，代码实现简单，使用 `ceil` 函数计算结果。
- **Z_M__**：3星。思路清晰，对不同情况进行了分类讨论，但最终也得出了统一的结论，代码实现与 Ninelife_Cat 类似。
- **开始新的记忆**：3星。思路基本正确，但对题目的理解有偏差，代码通过判断余数来计算结果，逻辑稍复杂。

### 重点代码
```cpp
// Ninelife_Cat 的代码
#include<bits/stdc++.h>
#define int long long//个人习惯
using namespace std;
int n,x,a[1001],sum;
signed main()
{
    cin>>n>>x;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    sum=abs(sum);
    cout<<ceil(sum*1.0/x);
    return 0;
}
```
**核心实现思想**：先读取输入的卡片数量 `n` 和数字上限 `x`，然后累加已找到卡片的数字得到 `sum`，取 `sum` 的绝对值，最后使用 `ceil` 函数计算需要补充的卡片数量。

### 关键思路或技巧
- 先计算已找到卡片数字的总和，再根据总和与数字上限的关系计算需要补充的卡片数量。
- 使用 `ceil` 函数可以方便地计算向上取整的结果。

### 拓展思路
同类型题目可能会改变卡片数字的限制条件或增加其他要求，但核心思路仍然是根据已有数字的总和来计算需要补充的数字。类似的算法套路在数学问题中经常用到，例如计算需要多少个相同的数来凑成某个目标值。

### 推荐洛谷题目
- P1001 A+B Problem
- P1002 过河卒
- P1003 铺地毯

---
处理用时：22.02秒