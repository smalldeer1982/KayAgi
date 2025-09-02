# 题目信息

# 「EZEC-4」paulzrm Loves Array

## 题目背景

原题面：

$\color{gray}\text{zrmpaul}$ has an array consisting of $n$ integers: $a_1,a_2,...,a_n$. The initial value of $a_i$ is $i(1\le i\le n)$. There are $m$ operations, including four types as follows.

Type $1$: `1` sort the array.   
Type $2$: `2` sort the array and reverse it.   
Type $3$: `3 x y` swap $a_x,a_y$. **It is guaranteed that $x$ is not equal to $y$, and $1\leq x ,y \leq n$**.    
Type $4$: `4` reverse the array.

You need to output the array after $m$ operations.

First line with two intergers $n,m(1\leq n,m\leq 10^6)$.

Next $m$ lines are the operations.

One line, $n$ numbers, the array.

## 题目描述

小 Z 有一个下标从 $1$ 开始并且长度为 $n$ 的序列，初始时下标为 $i$ 位置的数字为 $i$。有 $m$ 个操作，每个操作会是以下四种之一。

- `1` 对序列从小到大进行排序。
- `2` 对序列从小到大进行排序后将其翻转，(译者注：就是从大到小排序）。
- `3 x y` 将下标为 $x,y$ 的数交换位置。保证 $x\neq y$ 且 $1\le x,y\le n$。
- `4` 将序列翻转。

你要输出在 $m$ 次操作后的序列。

## 说明/提示

【数据范围】

**【本题采用捆绑测试】**

subtask 1（24pts）: $1\leq n,m\leq 2 \times 10^3$ 。

subtask 2（13pts）: 没有操作三。

subtask 3（63pts）: $1\leq n,m\leq 10^6$ 。


【样例解释】

序列经过的操作为：
> $1, 2, 3, 4, 5$     
$1, 2, 3, 4, 5$   
$5, 4, 3, 2, 1$   
$5, 2, 3, 4, 1$   
$1, 4, 3, 2, 5$   
$5, 4, 3, 2, 1$



## 样例 #1

### 输入

```
5 5
1
2
3 2 4
4
3 1 5```

### 输出

```
5 4 3 2 1```

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
题目要求对数组进行多次操作，包括排序、翻转和交换。由于操作次数和数据规模较大，直接暴力模拟会导致超时。因此，优化思路主要集中在减少不必要的操作和简化翻转操作的处理。

### 所选题解
1. **作者：RedLycoris**  
   - **星级**: 5星  
   - **关键亮点**: 通过找到最后一个排序操作，忽略之前的操作，大大减少了计算量。使用一个变量记录当前数组的翻转状态，简化了翻转操作的处理。  
   - **核心代码**:
     ```cpp
     for(int i=lst+1;i<=m;++i){
         if(ope[i]==3){
             if(not rev)swap(arr[x[i]],arr[y[i]]);
             else swap(arr[n-x[i]+1],arr[n-y[i]+1]);
         }else rev=1-rev;
     }
     ```
   - **个人心得**: 通过找到最后一个排序操作，可以忽略之前的操作，大大减少了计算量。

2. **作者：hensier**  
   - **星级**: 4星  
   - **关键亮点**: 分别处理了没有操作3和有操作3的情况，通过记录最后一个排序操作和翻转次数，简化了操作的处理。  
   - **核心代码**:
     ```cpp
     if(flag){
         if(opt[p][0]==2)rev=true;
         for(int i=p+1;i<=m;i++){
             if(opt[i][0]==3){
                 if(rev)swap(a[n-opt[i][1]+1],a[n-opt[i][2]+1]);
                 else swap(a[opt[i][1]],a[opt[i][2]]);
             }else rev^=true;
         }
     }
     ```
   - **个人心得**: 通过记录最后一个排序操作和翻转次数，简化了操作的处理。

3. **作者：Remake_**  
   - **星级**: 4星  
   - **关键亮点**: 通过优化连续的翻转操作，减少了不必要的计算。使用手写的翻转函数，进一步优化了常数。  
   - **核心代码**:
     ```cpp
     void rvs(){
         for (register int i = 1; i <= n / 2; ++i)
             swap(a[i], a[n - i + 1]);
     }
     ```
   - **个人心得**: 通过优化连续的翻转操作，减少了不必要的计算。

### 最优关键思路
1. **找到最后一个排序操作**: 忽略之前的操作，减少计算量。
2. **记录翻转状态**: 使用一个变量记录当前数组的翻转状态，简化翻转操作的处理。
3. **优化连续的翻转操作**: 将连续的翻转操作转化为奇偶次翻转，减少不必要的计算。

### 可拓展之处
类似的操作优化思路可以应用于其他需要处理大量操作的题目，如字符串处理、矩阵操作等。通过记录关键操作的状态，可以大大减少计算量。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：21.53秒