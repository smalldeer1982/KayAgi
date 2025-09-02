# 题目信息

# GCD Partition

## 题目描述

While at Kira's house, Josuke saw a piece of paper on the table with a task written on it.

The task sounded as follows. There is an array $ a $ of length $ n $ . On this array, do the following:

- select an integer $ k > 1 $ ;
- split the array into $ k $ subsegments $ ^\dagger $ ;
- calculate the sum in each of $ k $ subsegments and write these sums to another array $ b $ (where the sum of the subsegment $ (l, r) $ is $ {\sum_{j = l}^{r}a_j} $ );
- the final score of such a split will be $ \gcd(b_1, b_2, \ldots, b_k)^\ddagger $ .

The task is to find such a partition that the score is maximum possible. Josuke is interested in this task but is not strong in computer science. Help him to find the maximum possible score.

 $ ^\dagger $ A division of an array into $ k $ subsegments is $ k $ pairs of numbers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for every $ 1 \le j \le k - 1 $ $ l_{j + 1} = r_j + 1 $ , also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments.

 $ ^\ddagger $ $ \gcd(b_1, b_2, \ldots, b_k) $ stands for the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the array $ b $ .

## 说明/提示

In the first test case, you can choose $ k = 2 $ and split the array into subsegments $ (1, 2) $ and $ (3, 4) $ .

Then the score of such a partition will be equal to $ \gcd(a_1 + a_2, a_3 + a_4) = \gcd(2 + 2, 1 + 3) = \gcd(4, 4) = 4 $ .

In the fourth test case, you can choose $ k = 3 $ and split the array into subsegments $ (1, 2), (3, 5), (6, 6) $ .

The split score is $ \gcd(1 + 2, 1 + 1 + 1, 3) = 3 $ .

## 样例 #1

### 输入

```
6
4
2 2 1 3
2
1 2
3
1 4 5
6
1 2 1 1 1 3
10
12 30 37 88 12 78 89 17 2 12
6
7 7 7 7 7 7```

### 输出

```
4
1
5
3
1
21```

# AI分析结果



## 题目中文翻译

### GCD Partition

#### 题目描述

在Kira家，仗助看到桌上有一张写有任务的纸。

任务内容如下：给定一个长度为 $n$ 的数组 $a$，需进行如下操作：

1. 选择一个整数 $k > 1$；
2. 将数组分割为 $k$ 个连续子段$^\dagger$；
3. 计算每个子段的和，构成新数组 $b$；
4. 最终得分为 $b$ 数组的最大公约数（GCD）$^\ddagger$。

目标是找到使得分最大的分割方式，输出该最大值。

$^\dagger$ 分割为 $k$ 个子段的定义为：$k$ 个区间 $(l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k)$，满足 $l_1=1$, $r_k=n$，且相邻区间首尾相接。

$^\ddagger$ GCD定义：所有元素的GCD。

---

## 题解综合分析

### 关键思路总结
所有题解的核心结论：**分成两段时GCD最大**。  
**数学依据**：$\gcd(a_1,a_2,\dots,a_k) \leq \gcd(a_1+a_2,a_3,\dots,a_k)$，递推可得两段最优。  
**实现方法**：利用前缀和计算所有可能分割点的两段和，取最大GCD。

### 精选题解

#### 题解1：wzc_IOI_czl（⭐️⭐️⭐️⭐️4）
**亮点**：简明思路推导，直接代码示例。  
**结论**：通过合并子段证明两段最优，提供基础代码框架。  
```cpp
for(int i = 1; i < n; i++) {
    int l = s[i], r = s[n] - s[i];
    ans = max(ans, __gcd(l, r));
}
```

#### 题解2：RNTBW（⭐️⭐️⭐️⭐️4）
**亮点**：详细数学证明，代码处理多测试用例。  
**关键证明**：$\gcd(a,b,c)\leq \gcd(a+b,c)$，确保两段分割的有效性。  
**代码**：正确处理输入循环，变量初始化严谨。  
```cpp
for(int i=1;i<n;i++) 
    k=max(k,__gcd(s[i],s[n]-s[i]));
```

#### 题解3：zhicheng（⭐️⭐️⭐️⭐️4）
**亮点**：代码简洁高效，逻辑清晰。  
**实现**：前缀和直接计算，无冗余结构。  
```cpp
for(int i=1;i<=n-1;i++)
    ans=max(ans,__gcd(a[i],a[n]-a[i]));
```

---

### 核心代码实现
```cpp
// 前缀和初始化
vector<long long> s(n+1, 0);
for (int i=1; i<=n; i++)
    s[i] = s[i-1] + a[i-1]; // a为原始数组

// 遍历所有分割点
long long max_gcd = 0;
for (int i=1; i<n; i++) {
    long long part1 = s[i];
    long long part2 = s[n] - s[i];
    max_gcd = max(max_gcd, gcd(part1, part2));
}
```

---

### 扩展与举一反三
**同类题型**：  
1. [洛谷 P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)（因数分解与GCD）  
2. [洛谷 P2651 添加括号](https://www.luogu.com.cn/problem/P2651)（运算顺序优化）  
3. [洛谷 P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)（GCD与LCM综合应用）  

**思维技巧**：  
- **问题简化**：将复杂分割问题转化为两段最优问题。  
- **数学性质运用**：利用GCD的合并性质降低复杂度。

---
处理用时：60.89秒