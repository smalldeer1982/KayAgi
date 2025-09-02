# 题目信息

# Mike and Children

## 题目描述

Mike decided to teach programming to children in an elementary school. He knows that it is not an easy task to interest children in that age to code. That is why he decided to give each child two sweets.

Mike has $ n $ sweets with sizes $ a_1, a_2, \ldots, a_n $ . All his sweets have different sizes. That is, there is no such pair $ (i, j) $ ( $ 1 \leq i, j \leq n $ ) such that $ i \ne j $ and $ a_i = a_j $ .

Since Mike has taught for many years, he knows that if he gives two sweets with sizes $ a_i $ and $ a_j $ to one child and $ a_k $ and $ a_p $ to another, where $ (a_i + a_j) \neq (a_k + a_p) $ , then a child who has a smaller sum of sizes will be upset. That is, if there are two children who have different sums of sweets, then one of them will be upset. Apparently, Mike does not want somebody to be upset.

Mike wants to invite children giving each of them two sweets. Obviously, he can't give one sweet to two or more children. His goal is to invite as many children as he can.

Since Mike is busy preparing to his first lecture in the elementary school, he is asking you to find the maximum number of children he can invite giving each of them two sweets in such way that nobody will be upset.

## 说明/提示

In the first example, Mike can give $ 9+2=11 $ to one child, $ 8+3=11 $ to another one, and $ 7+4=11 $ to the third child. Therefore, Mike can invite three children. Note that it is not the only solution.

In the second example, Mike can give $ 3+9=12 $ to one child and $ 1+11 $ to another one. Therefore, Mike can invite two children. Note that it is not the only solution.

## 样例 #1

### 输入

```
8
1 8 3 11 4 9 2 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
3 1 7 11 9 2 12
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写

#### 题目描述

Mike决定在一所小学教孩子们编程。他知道要让那个年龄的孩子对代码感兴趣不是件容易的事。所以他决定给每个孩子两个糖果。

Mike有$n$个糖果，大小分别为$a_1, a_2, \ldots, a_n$。所有糖果的大小都不同，即不存在$i \ne j$且$a_i = a_j$的情况。

Mike教了很多年，他知道如果他给一个孩子两个大小为$a_i$和$a_j$的糖果，给另一个孩子两个大小为$a_k$和$a_p$的糖果，且$(a_i + a_j) \neq (a_k + a_p)$，那么得到较小糖果和的孩子会感到沮丧。显然，Mike不希望有孩子感到沮丧。

Mike想邀请尽可能多的孩子，每个孩子分到两个糖果。显然，他不能把同一个糖果分给多个孩子。他的目标是邀请尽可能多的孩子，且不让孩子感到沮丧。

由于Mike忙于准备小学的第一堂课，他请你帮忙找出他最多能邀请多少个孩子，且每个孩子分到的两个糖果的和都相等。

#### 说明/提示

在第一个样例中，Mike可以给一个孩子$9+2=11$，给另一个孩子$8+3=11$，给第三个孩子$7+4=11$。因此，Mike可以邀请三个孩子。注意这不是唯一的解。

在第二个样例中，Mike可以给一个孩子$3+9=12$，给另一个孩子$1+11=12$。因此，Mike可以邀请两个孩子。注意这不是唯一的解。

#### 样例 #1

##### 输入

```
8
1 8 3 11 4 9 2 7
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
7
3 1 7 11 9 2 12
```

##### 输出

```
2
```

### 算法分类

枚举

### 题解分析与结论

所有题解的核心思路都是通过枚举所有可能的糖果对的和，并使用桶（数组）来统计每个和出现的次数，最后取最大值作为答案。这种方法的时间复杂度为$O(n^2)$，由于$n \leq 1000$，完全可以在时间限制内完成。

### 精选题解

#### 题解1：Z_M__ (5星)

**关键亮点**：
- 使用桶统计每个和出现的次数，思路清晰。
- 代码简洁，变量命名合理，易于理解。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
        b[a[i] + a[j]]++;
for (int i = 2; i <= maxn * 2; i++)
    res = max(res, b[i]);
```

#### 题解2：WsW_ (4星)

**关键亮点**：
- 在统计和的同时更新最大值，减少了后续遍历的时间。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<i;j++){
        cnt[a[i]+a[j]]++;
        if(cnt[a[i]+a[j]]>ans){
            ans=cnt[a[i]+a[j]];
        }
    }
}
```

#### 题解3：Rbu_nas (4星)

**关键亮点**：
- 使用桶统计和的次数，代码简洁。
- 变量命名合理，易于理解。

**核心代码**：
```cpp
for(int i=1; i<=n; ++i)
    for(int j=i+1; j<=n; ++j)
        ++flag[a[i]+a[j]];
for(int i=1; i<=M; ++i)
    res=max(res, flag[i]);
```

### 最优关键思路

使用桶（数组）统计所有可能的糖果对的和出现的次数，最后取最大值作为答案。这种方法的时间复杂度为$O(n^2)$，由于$n \leq 1000$，完全可以在时间限制内完成。

### 拓展思路

类似的问题可以通过枚举所有可能的组合，并使用桶或其他数据结构来统计符合条件的组合数。例如，在统计数组中满足某些条件的数对时，可以使用类似的方法。

### 推荐题目

1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)

---
处理用时：30.65秒