# 题目信息

# Contrast Value

## 题目描述

For an array of integers $ [a_1, a_2, \dots, a_n] $ , let's call the value $ |a_1-a_2|+|a_2-a_3|+\cdots+|a_{n-1}-a_n| $ the contrast of the array. Note that the contrast of an array of size $ 1 $ is equal to $ 0 $ .

You are given an array of integers $ a $ . Your task is to build an array of $ b $ in such a way that all the following conditions are met:

- $ b $ is not empty, i.e there is at least one element;
- $ b $ is a subsequence of $ a $ , i.e $ b $ can be produced by deleting some elements from $ a $ (maybe zero);
- the contrast of $ b $ is equal to the contrast of $ a $ .

What is the minimum possible size of the array $ b $ ?

## 样例 #1

### 输入

```
4
5
1 3 3 3 7
2
4 2
4
1 1 1 1
7
5 4 2 1 0 0 4```

### 输出

```
2
2
1
3```

# AI分析结果

### 题目内容重写
#### 题目描述
对于一个整数数组 $[a_1, a_2, \dots, a_n]$，定义其对比值为 $|a_1-a_2|+|a_2-a_3|+\cdots+|a_{n-1}-a_n|$。注意，大小为 $1$ 的数组的对比值为 $0$。

给定一个整数数组 $a$，你的任务是构建一个数组 $b$，满足以下条件：
- $b$ 非空，即至少包含一个元素；
- $b$ 是 $a$ 的子序列，即 $b$ 可以通过删除 $a$ 中的一些元素（可能为零个）得到；
- $b$ 的对比值等于 $a$ 的对比值。

求数组 $b$ 的最小可能长度。

#### 样例输入
```
4
5
1 3 3 3 7
2
4 2
4
1 1 1 1
7
5 4 2 1 0 0 4
```

#### 样例输出
```
2
2
1
3
```

### 算法分类
贪心

### 题解分析与结论
该题的核心思路是通过贪心策略，保留数组中的关键转折点，从而在不改变对比值的情况下，最小化子序列的长度。具体来说，当数组中的元素单调递增或递减时，可以只保留首尾两个元素，中间的元素可以删除。对于相等的元素，可以直接删除，因为它们对对比值没有贡献。

### 所选高星题解
#### 1. 作者：Lovely_Chtholly (5星)
**关键亮点**：
- 清晰地将问题分为三种情况处理：相等、递增、递减。
- 代码简洁，逻辑清晰，直接遍历数组并统计保留的元素个数。

**核心代码**：
```cpp
for(int i=1;i<n;)
{
    if(a[i]==a[i+1])i++;
    else if(a[i]<a[i+1])
    {
        for(;i<n and a[i]<=a[i+1];i++);
        sum++;
    }
    else
    {
        for(;i<n and a[i]>=a[i+1];i++);
        sum++;
    }
}
```
**实现思想**：遍历数组，根据当前元素与下一个元素的关系，决定是否保留当前元素。如果元素相等，直接跳过；如果递增或递减，则跳过中间元素，只保留首尾。

#### 2. 作者：Night_sea_64 (4星)
**关键亮点**：
- 通过记录当前序列的单调性（递增或递减）来判断是否需要保留当前元素。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<n;i++)
{
    if(a[i]>a[i-1]&&!flag1)
        flag1=1,flag2=0,cnt++;
    if(a[i]<a[i-1]&&!flag2)
        flag2=1,flag1=0,cnt++;
}
```
**实现思想**：通过两个标志位记录当前序列的单调性，当单调性发生变化时，增加保留的元素个数。

#### 3. 作者：Furina_Hate_Comma (4星)
**关键亮点**：
- 通过挖掘性质，发现单调序列中的中间元素可以删除，只保留首尾。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
while(i<n){
    if(a[i]==a[i+1])i++;
    else if(a[i]<a[i+1]){
        while(a[i]<=a[i+1]&&i<n)
            i++;
        ans++;
    }
    else if(a[i]>a[i+1]){
        while(a[i]>=a[i+1]&&i<n)
            i++;
        ans++;
    }
}
```
**实现思想**：遍历数组，根据当前元素与下一个元素的关系，决定是否保留当前元素。如果元素相等，直接跳过；如果递增或递减，则跳过中间元素，只保留首尾。

### 最优关键思路
通过贪心策略，保留数组中的关键转折点（即单调序列的首尾元素），从而在不改变对比值的情况下，最小化子序列的长度。对于相等的元素，可以直接删除，因为它们对对比值没有贡献。

### 可拓展之处
该题的贪心策略可以推广到其他类似问题，如寻找最小长度的子序列，使得某些特定性质（如和、积等）与原序列相同。类似的思路也可以用于处理单调性相关的优化问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录
- **Lovely_Chtholly**：通过将问题分为三种情况处理，简化了问题的复杂度，代码实现更加清晰。
- **Night_sea_64**：通过记录单调性，避免了复杂的判断逻辑，代码更加简洁。
- **Furina_Hate_Comma**：通过挖掘性质，发现单调序列中的中间元素可以删除，从而简化了问题。

---
处理用时：34.13秒