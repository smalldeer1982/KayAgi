# 题目信息

# Almost Equal

## 题目描述

You are given integer $ n $ . You have to arrange numbers from $ 1 $ to $ 2n $ , using each of them exactly once, on the circle, so that the following condition would be satisfied:

For every $ n $ consecutive numbers on the circle write their sum on the blackboard. Then any two of written on the blackboard $ 2n $ numbers differ not more than by $ 1 $ .

For example, choose $ n = 3 $ . On the left you can see an example of a valid arrangement: $ 1 + 4 + 5 = 10 $ , $ 4 + 5 + 2 = 11 $ , $ 5 + 2 + 3 = 10 $ , $ 2 + 3 + 6 = 11 $ , $ 3 + 6 + 1 = 10 $ , $ 6 + 1 + 4 = 11 $ , any two numbers differ by at most $ 1 $ . On the right you can see an invalid arrangement: for example, $ 5 + 1 + 6 = 12 $ , and $ 3 + 2 + 4 = 9 $ , $ 9 $ and $ 12 $ differ more than by $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1205A/9cba5ca83f08157cd471ad2c4144ebafdf1f05ac.png)

## 说明/提示

Example from the statement is shown for the first example.

It can be proved that there is no solution in the second example.

## 样例 #1

### 输入

```
3
```

### 输出

```
YES
1 4 5 2 3 6 ```

## 样例 #2

### 输入

```
4
```

### 输出

```
NO```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个整数 $n$。你需要将 $1$ 到 $2n$ 的整数排列成一个圆圈，每个数恰好使用一次，使得以下条件满足：

对于圆圈上每 $n$ 个连续的数，计算它们的和并写在黑板上。然后，黑板上任意两个数的差不超过 $1$。

例如，选择 $n = 3$。左边是一个有效的排列：$1 + 4 + 5 = 10$，$4 + 5 + 2 = 11$，$5 + 2 + 3 = 10$，$2 + 3 + 6 = 11$，$3 + 6 + 1 = 10$，$6 + 1 + 4 = 11$，任意两个数的差不超过 $1$。右边是一个无效的排列：例如，$5 + 1 + 6 = 12$，而 $3 + 2 + 4 = 9$，$9$ 和 $12$ 的差超过 $1$。

#### 说明/提示
题目中的例子已经展示了第一个样例。

可以证明第二个样例无解。

#### 样例 #1
##### 输入
```
3
```
##### 输出
```
YES
1 4 5 2 3 6
```

#### 样例 #2
##### 输入
```
4
```
##### 输出
```
NO
```

### 算法分类
构造

### 题解分析与结论
本题的核心是通过构造一个满足条件的排列，使得每 $n$ 个连续数的和相差不超过 $1$。通过观察样例和分析，可以发现当 $n$ 为奇数时，存在满足条件的排列；而当 $n$ 为偶数时，无解。大多数题解都基于这一结论，通过交替放置小数和大数来构造排列。

### 高星题解推荐
#### 题解1：引领天下 (4星)
**关键亮点**：
- 通过观察样例，提出了当 $n$ 为奇数时，交替放置小数和大数的构造方法。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for (int i=1;i<=n;i++)if(i&1)a[i]=++cnt,a[i+n]=++cnt;
else a[i+n]=++cnt,a[i]=++cnt;
```
**实现思想**：通过奇偶性判断，交替放置小数和大数，确保每 $n$ 个连续数的和相差不超过 $1$。

#### 题解2：xuezhe (4星)
**关键亮点**：
- 通过滑动窗口的思路，推导出相邻窗口和相差不超过 $1$ 的条件。
- 详细解释了为什么 $n$ 为偶数时无解。

**核心代码**：
```cpp
for(int i=1;i<=n;++i){
    if(i&1){
        a[i]=2*i-1;
        a[i+n]=2*i;
    }else{
        a[i]=2*i;
        a[i+n]=2*i-1;
    }
}
```
**实现思想**：根据奇偶性，交替放置小数和大数，确保每 $n$ 个连续数的和相差不超过 $1$。

#### 题解3：ZigZagKmp (4星)
**关键亮点**：
- 通过数学推导，证明了当 $n$ 为奇数时，存在满足条件的排列。
- 提供了两种构造方法，并详细解释了其正确性。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(i&1)A[++ta]=(i*2-1),B[++tb]=(i*2);
    else   A[++ta]=(i*2),B[++tb]=(i*2-1);
}
```
**实现思想**：将数字分成两部分，交替放置小数和大数，确保每 $n$ 个连续数的和相差不超过 $1$。

### 最优关键思路
通过交替放置小数和大数，确保每 $n$ 个连续数的和相差不超过 $1$。当 $n$ 为奇数时，这种构造方法有效；当 $n$ 为偶数时，无解。

### 拓展思路
类似的问题可以通过构造法解决，关键在于找到合适的排列规律。对于涉及滑动窗口或连续子序列的问题，可以考虑通过数学推导或观察样例来寻找规律。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：31.68秒