# 题目信息

# Insert and Equalize

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ , all its elements are distinct.

First, you are asked to insert one more integer $ a_{n+1} $ into this array. $ a_{n+1} $ should not be equal to any of $ a_1, a_2, \dots, a_n $ .

Then, you will have to make all elements of the array equal. At the start, you choose a positive integer $ x $ ( $ x > 0 $ ). In one operation, you add $ x $ to exactly one element of the array. Note that $ x $ is the same for all operations.

What's the smallest number of operations it can take you to make all elements equal, after you choose $ a_{n+1} $ and $ x $ ?

## 说明/提示

In the first testcase, you can choose $ a_{n+1} = 4 $ , the array becomes $ [1, 2, 3, 4] $ . Then choose $ x = 1 $ and apply the operation $ 3 $ times to the first element, $ 2 $ times to the second element, $ 1 $ time to the third element and $ 0 $ times to the fourth element.

In the second testcase, you can choose $ a_{n+1} = 13, x = 4 $ .

In the third testcase, you can choose $ a_{n+1} = 9, x = 1 $ . Then apply the operation once to $ a_{n+1} $ .

## 样例 #1

### 输入

```
3
3
1 2 3
5
1 -19 17 -3 -15
1
10```

### 输出

```
6
27
1```

# AI分析结果



# Insert and Equalize 中文翻译

## 题目描述

给定一个各元素互不相同的整数数组 $a_1, a_2, \dots, a_n$。

首先，需要在数组中插入一个新整数 $a_{n+1}$，且该整数不能与原数组中的任何元素相等。

然后，选择一个正整数 $x$，每次操作可以将 $x$ 加到任意一个元素上。要求所有元素最终相等，求最小的操作次数。

## 样例 #1

### 输入
```
3
3
1 2 3
5
1 -19 17 -3 -15
1
10
```

### 输出
```
6
27
1
```

---

**算法分类：数学**

---

## 题解分析与结论

**核心思路**：  
1. 最优的 $x$ 是原数组排序后相邻差值的最大公约数（GCD）。  
2. 插入元素的位置应选择在最大值基础上减去 $k \times x$ 的最近未占用位置。  
3. 总操作次数为原数组元素到最大值的差之和除以 $x$，加上插入元素到最大值的操作次数。

**关键技巧**：  
- 通过 GCD 确定 $x$ 来最大化每次操作的效益  
- 利用哈希表快速查找可插入位置  
- 所有计算基于相对差值，避免重复计算  

---

## 高星题解推荐

### 题解1：luobo215（4星）
**亮点**：  
- 通过预处理将问题转化为差值计算  
- 使用 map 快速查找可插入位置  
- 清晰处理边界情况（如 n=1）

**核心代码**：  
```cpp
sort(a + 1, a + 1 + n);
ll g = 0;
for (int i = 2; i <= n; ++i) 
    g = gcd(g, a[i] - a[i-1]);

ll k = g;
while (m.count(k)) k += g;
ans += k/g;  // 插入元素操作次数
```

### 题解2：FiraCode（4星）
**亮点**：  
- 逆向查找可插入位置  
- 数学推导严谨  
- 代码结构简洁高效

**核心代码**：  
```cpp
int k = -1;
while (ma[a[n] + k * Gcd]) --k;
ans -= k;  // 利用负索引简化计算
```

---

## 相似题目推荐
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
2. [P2441 角色属性](https://www.luogu.com.cn/problem/P2441)  
3. [P5436 星际旅行](https://www.luogu.com.cn/problem/P5436)

---
处理用时：424.60秒