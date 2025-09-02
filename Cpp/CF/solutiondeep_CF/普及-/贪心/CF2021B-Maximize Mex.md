# 题目信息

# Maximize Mex

## 题目描述

You are given an array $ a $ of $ n $ positive integers and an integer $ x $ . You can do the following two-step operation any (possibly zero) number of times:

1. Choose an index $ i $ ( $ 1 \leq i \leq n $ ).
2. Increase $ a_i $ by $ x $ , in other words $ a_i := a_i + x $ .

Find the maximum value of the $ \operatorname{MEX} $ of $ a $ if you perform the operations optimally.

The $ \operatorname{MEX} $ (minimum excluded value) of an array is the smallest non-negative integer that is not in the array. For example:

- The $ \operatorname{MEX} $ of $ [2,2,1] $ is $ 0 $ because $ 0 $ is not in the array.
- The $ \operatorname{MEX} $ of $ [3,1,0,1] $ is $ 2 $ because $ 0 $ and $ 1 $ are in the array but $ 2 $ is not.
- The $ \operatorname{MEX} $ of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ are in the array but $ 4 $ is not.

## 说明/提示

In the first test case, the $ \operatorname{MEX} $ of $ a $ is $ 4 $ without performing any operations, which is the maximum.

In the second test case, the $ \operatorname{MEX} $ of $ a $ is $ 5 $ without performing any operations. If we perform two operations both with $ i=1 $ , we will have the array $ a=[5,3,4,1,0,2] $ . Then, the $ \operatorname{MEX} $ of $ a $ will become $ 6 $ , which is the maximum.

In the third test case, the $ \operatorname{MEX} $ of $ a $ is $ 0 $ without performing any operations, which is the maximum.

## 样例 #1

### 输入

```
3
6 3
0 3 2 1 5 2
6 2
1 3 4 1 0 2
4 5
2 5 10 3```

### 输出

```
4
6
0```

# AI分析结果



【题目中文翻译】  
# 最大化 MEX

## 题目描述  
给定一个包含 $n$ 个正整数的数组 $a$ 和一个整数 $x$。你可以执行以下两步操作任意次（包括零次）：  
1. 选择一个下标 $i$（$1 \leq i \leq n$）。  
2. 将 $a_i$ 增加 $x$，即 $a_i := a_i + x$。  

请通过最优操作，求数组 $a$ 的最大可能 $\operatorname{MEX}$ 值。  
$\operatorname{MEX}$ 定义为数组中未出现的最小非负整数。  

## 输入样例  
输入包含多组测试数据，具体格式参考原题。  

---

### 题解分析与结论  
#### 核心思路  
所有题解均围绕**贪心策略**展开：  
1. **覆盖关键区间**：$\operatorname{MEX}$ 最大时，数组应尽可能覆盖 $0,1,2,...,k-1$。  
2. **重复元素处理**：对重复的数值 $i$，将多余元素通过加 $x$ 转化为更高数值（$i+x$），以填补后续空缺。  
3. **模分组优化**：部分题解利用 $a_i \equiv j \pmod{x}$ 的性质分组处理，确保每个余数类的最小值能被覆盖。  

#### 最优解法总结  
**贪心+频率统计**：  
1. 统计每个数值的出现次数。  
2. 从 $i=0$ 开始遍历，若 $i$ 未出现则返回当前值；若出现多次则将多余次数转移到 $i+x$。  
3. 时间复杂度 $O(n)$，空间复杂度 $O(n)$。  

---

### 高星题解推荐  
#### 1. [chenxi2009] ⭐⭐⭐⭐⭐（5星）  
**亮点**：  
- 思路清晰，代码简洁高效。  
- 直接通过频率统计和转移操作实现贪心策略。  
- 明确处理重复元素的数学证明。  

**核心代码**：  
```cpp
map<int,int> m;  // 统计出现次数
for (int i = 0; i < n; i++) {
    if (!m[i]) { ans = i; break; }
    if (m[i] > 1) m[i+x] += m[i] - 1;  // 转移多余次数
}
```

#### 2. [Colinxu2020] ⭐⭐⭐⭐（4星）  
**亮点**：  
- 基于模 $x$ 分组，用优先队列维护最小值。  
- 更直观处理数值覆盖关系，适合理解模运算性质。  

**核心代码**：  
```cpp
map<int, priority_queue<int, vector<int>, greater<int>>> mp;
// 按余数分组并排序
for (int w = 0; w <= n; w++) {
    if (mp[w%x].empty() || mp[w%x].top() > w) return w;
    mp[w%x].pop();  // 消耗一个元素覆盖w
}
```

#### 3. [Butterfly_qwq] ⭐⭐⭐⭐（4星）  
**亮点**：  
- 代码极简，直接实现频率转移。  
- 正确性证明清晰，适合快速实现。  

**核心代码**：  
```cpp
map<int, int> bul;
for (int i = 0; ; i++) {
    if (bul[i] == 0) return i;
    bul[i+x] += bul[i] - 1;  // 转移多余次数
}
```

---

### 关键技巧总结  
1. **贪心覆盖**：从 $0$ 开始逐个填补空缺，确保连续区间最大化。  
2. **频率转移**：将重复元素的次数转移到更高数值，避免浪费。  
3. **模分组优化**：利用同余性质快速判断可覆盖的数值。  

---

### 同类题目推荐  
1. [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)（基础 MEX 问题）  
2. [P7667 [JOI 2018] Art Exhibition](https://www.luogu.com.cn/problem/P7667)（贪心策略应用）  
3. [CF1656D K-good](https://www.luogu.com.cn/problem/CF1656D)（模运算与数论结合）  

---

### 题解心得摘录  
- **chenxi2009**：  
  > "重复元素对增大 mex 无帮助，必须转移。单个元素无需操作，否则会破坏已有覆盖。"  
  > **启示**：贪心操作需保留基准元素以确保当前 mex 不降低。  

- **Colinxu2020**：  
  > "操作不影响模 x 结果，分组处理可快速定位可用元素。"  
  > **启示**：利用数学性质（如同余）可显著优化算法。

---
处理用时：57.07秒