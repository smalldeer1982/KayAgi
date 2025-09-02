# 题目信息

# [ABC276C] Previous Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_c

$ (1,\ \dots,\ N) $ の順列 $ P\ =\ (P_1,\ \dots,\ P_N) $ が与えられます。ただし、$ (P_1,\ \dots,\ P_N)\ \neq\ (1,\ \dots,\ N) $ です。

$ (1\ \dots,\ N) $ の順列を全て辞書順で小さい順に並べたとき、$ P $ が $ K $ 番目であるとします。辞書順で小さい方から $ K-1 $ 番目の順列を求めてください。

 順列とは？ $ (1,\ \dots,\ N) $ の**順列**とは、$ (1,\ \dots,\ N) $ を並べ替えて得られる数列のことをいいます。

 辞書順とは？ 長さ $ N $ の数列 $ A\ =\ (A_1,\ \dots,\ A_N),\ B\ =\ (B_1,\ \dots,\ B_N) $ に対し、$ A $ が $ B $ より**辞書順で真に小さい**とは、ある整数 $ 1\ \leq\ i\ \leq\ N $ が存在して、下記の $ 2 $ つがともに成り立つことをいいます。

- $ (A_{1},\ldots,A_{i-1})\ =\ (B_1,\ldots,B_{i-1}) $
- $ A_i $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ P_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ P_i\ \neq\ P_j\ \,\ (i\ \neq\ j) $
- $ (P_1,\ \dots,\ P_N)\ \neq\ (1,\ \dots,\ N) $
- 入力される値は全て整数

### Sample Explanation 1

$ (1,\ 2,\ 3) $ の順列を辞書順で小さい順に並べると次のようになります。 - $ (1,\ 2,\ 3) $ - $ (1,\ 3,\ 2) $ - $ (2,\ 1,\ 3) $ - $ (2,\ 3,\ 1) $ - $ (3,\ 1,\ 2) $ - $ (3,\ 2,\ 1) $ よって $ P\ =\ (3,\ 1,\ 2) $ は小さい方から $ 5 $ 番目であり、求める順列、すなわち小さい方から $ 5\ -\ 1\ =\ 4 $ 番目の順列は $ (2,\ 3,\ 1) $ です。

## 样例 #1

### 输入

```
3

3 1 2```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
10

9 8 6 5 10 3 1 2 4 7```

### 输出

```
9 8 6 5 10 2 7 4 3 1```

# AI分析结果

### 题目内容重写
【题目描述】
给定一个长度为 $N$ 的排列 $P = (P_1, \dots, P_N)$，其中 $P$ 不是 $(1, \dots, N)$。求该排列在字典序中的前一个排列。

【说明/提示】
- 排列是指将 $(1, \dots, N)$ 进行重新排列得到的数列。
- 字典序的定义：对于两个数列 $A$ 和 $B$，若存在某个位置 $i$，使得 $A_{1..i-1} = B_{1..i-1}$ 且 $A_i < B_i$，则称 $A$ 在字典序上小于 $B$。

【样例输入】
```
3
3 1 2
```

【样例输出】
```
2 3 1
```

### 算法分类
排序

### 题解分析与结论
本题的核心是求给定排列的字典序前一个排列。大多数题解都使用了C++ STL中的 `prev_permutation` 函数，该函数可以直接求出当前排列的前一个排列，代码简洁且高效。部分题解还提供了手动实现 `prev_permutation` 的算法，通过从右向左找到第一个不满足递减的位置，然后交换并反转后续元素，从而得到前一个排列。

### 高星题解推荐

#### 题解1：作者：_H17_ (赞：6)
**星级：5星**
**关键亮点：**
- 使用 `prev_permutation` 函数，代码简洁高效。
- 详细解释了 `prev_permutation` 的用法和返回值。

**代码核心思想：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[101];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",p+i);
    prev_permutation(p+1,p+n+1);
    for(int i=1;i<=n;i++)
        printf("%d ",p[i]);
    putchar('\n');
    return 0;
}
```

#### 题解2：作者：liangbob (赞：1)
**星级：4星**
**关键亮点：**
- 手动实现 `prev_permutation` 的算法，深入理解其原理。
- 分步骤详细解释了算法的实现过程。

**代码核心思想：**
```cpp
void change()
{
    int cur = n;
    int pre = n - 1;
    while(cur > 1 && a[pre] <= a[cur])
    {
        cur--;
        pre--;
    }
    cur = n;
    while(a[cur] >= a[pre])
    {
        cur--;
    }
    swap(a[pre], a[cur]);
    reverse(a + pre + 1, a + n + 1);
}
```

#### 题解3：作者：cjh20090318 (赞：3)
**星级：4星**
**关键亮点：**
- 使用 `prev_permutation` 函数，代码简洁。
- 提供了 `next_permutation` 的拓展知识。

**代码核心思想：**
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[101];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    prev_permutation(a+1,a+n+1);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return 0;
}
```

### 最优关键思路
使用 `prev_permutation` 函数是最简洁高效的解决方案。如果需要手动实现，可以通过从右向左找到第一个不满足递减的位置，交换并反转后续元素来得到前一个排列。

### 拓展思路
- 类似题目：求下一个排列（`next_permutation`）。
- 可以进一步学习排列生成算法，如递归生成所有排列。

### 推荐题目
1. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
3. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)

---
处理用时：26.72秒