# 题目信息

# Array Game

## 题目描述

You are given an array $ a $ of $ n $ positive integers. In one operation, you must pick some $ (i, j) $ such that $ 1\leq i < j\leq |a| $ and append $ |a_i - a_j| $ to the end of the $ a $ (i.e. increase $ n $ by $ 1 $ and set $ a_n $ to $ |a_i - a_j| $ ). Your task is to minimize and print the minimum value of $ a $ after performing $ k $ operations.

## 说明/提示

In the first test case, after any $ k=2 $ operations, the minimum value of $ a $ will be $ 1 $ .

In the second test case, an optimal strategy is to first pick $ i=1, j=2 $ and append $ |a_1 - a_2| = 3 $ to the end of $ a $ , creating $ a=[7, 4, 15, 12, 3] $ . Then, pick $ i=3, j=4 $ and append $ |a_3 - a_4| = 3 $ to the end of $ a $ , creating $ a=[7, 4, 15, 12, 3, 3] $ . In the final operation, pick $ i=5, j=6 $ and append $ |a_5 - a_6| = 0 $ to the end of $ a $ . Then the minimum value of $ a $ will be $ 0 $ .

In the third test case, an optimal strategy is to first pick $ i=2, j=3 $ to append $ |a_2 - a_3| = 3 $ to the end of $ a $ . Any second operation will still not make the minimum value of $ a $ be less than $ 3 $ .

## 样例 #1

### 输入

```
4
5 2
3 9 7 15 1
4 3
7 4 15 12
6 2
42 47 50 54 62 79
2 1
500000000000000000 1000000000000000000```

### 输出

```
1
0
3
500000000000000000```

# AI分析结果



### 题目翻译

# 数组游戏

## 题目描述

给定一个包含 $n$ 个正整数的数组 $a$。每次操作中，选择两个不同的元素 $(i, j)$ 并将它们的绝对差值 $|a_i - a_j|$ 添加到数组末尾。要求进行 $k$ 次操作后，使数组中的最小值尽可能小，并输出该最小值。

## 输入样例与输出样例

输入：  
```
4
5 2
3 9 7 15 1
4 3
7 4 15 12
6 2
42 47 50 54 62 79
2 1
500000000000000000 1000000000000000000
```

输出：  
```
1
0
3
500000000000000000
```

---

### 算法分类
**构造、数学、二分**

---

### 题解综合分析

所有题解均采用分类讨论策略：
1. **当 $k \ge 3$ 时**，通过两次生成相同差值后第三次操作必得 0。
2. **当 $k=1$ 时**，暴力枚举所有元素对的差值。
3. **当 $k=2$ 时**，枚举第一次操作生成的差值，并在排序后的原数组中二分查找最接近该差值的元素。

**核心难点**在于处理 $k=2$ 时如何高效找到第二次操作的最优解，需结合排序后的数组性质与二分查找。

---

### 高星题解推荐

#### 1. MicroSun（4.5星）
**亮点**：
- 双指针优化二分过程，避免重复查找。
- 代码结构清晰，包含原数组最小值与相邻差值的最小值处理。
```cpp
// 关键代码：双指针查找最小差值
for(int i=1;i<n;i++){
    ll m=0;  // 双指针起始位置
    for(int j=i+1;j<=n;j++){
        ll p=ve[j]-ve[i];
        while(m<n && ve[m]<p) m++;
        m--;
        // 处理边界情况
        if(!m) minn=min(minn,abs(p-ve[1]));
        else minn=min(minn, min(abs(p-ve[m]), abs(p-ve[m+1])));
    }
}
```

#### 2. Zinc_acetate（4星）
**亮点**：
- 预处理所有可能差值并存储，简化后续操作。
- 明确分离不同情况的处理逻辑。
```cpp
vector<int> b;  // 存储所有可能的第一次操作差值
for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) 
    b.push_back(abs(a[i]-a[j]));
// 二分查找最近元素
for(auto i : b){
    int pos = lower_bound(a.begin(), a.end(), i) - a.begin();
    minn = min({minn, abs(a[pos]-i), abs(i-a[pos-1])});
}
```

#### 3. TLEWA（4星）
**亮点**：
- 简洁的二分实现，直接处理边界条件。
- 代码高度优化，无冗余步骤。
```cpp
for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
    num = arr[j] - arr[i];
    p = lower_bound(arr+1, arr+n+1, num) - arr;
    if(p<=n) minn = min(minn, arr[p] - num);
    if(p>1)  minn = min(minn, num - arr[p-1]);
}
```

---

### 关键思路总结
1. **数学构造**：当 $k \ge 3$ 时，通过两次相同差值生成 0。
2. **排序优化**：对原数组排序以快速计算相邻差值和进行二分。
3. **二分查找**：在 $k=2$ 时，将第一次操作生成的差值与原数组元素进行匹配。

---

### 拓展与心得
- **同类问题**：涉及差值构造的最优化问题（如 CF 1321C）。
- **调试心得**：需注意原数组最小值可能比所有生成的差值更小（如初始数组含 1）。

---

### 推荐练习题
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（差值统计）
2. [P1314 聪明的质监员](https://www.luogu.com.cn/problem/P1314)（二分答案）
3. [CF1321C Remove Adjacent](https://codeforces.com/problemset/problem/1321/C)（构造与贪心）

---
处理用时：57.37秒