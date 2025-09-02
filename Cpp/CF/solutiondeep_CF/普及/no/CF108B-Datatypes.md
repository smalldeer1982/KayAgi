# 题目信息

# Datatypes

## 题目描述

Tattah's youngest brother, Tuftuf, is new to programming.

Since his older brother is such a good programmer, his biggest dream is to outshine him. Tuftuf is a student at the German University in Cairo (GUC) where he learns to write programs in Gava.

Today, Tuftuf was introduced to Gava's unsigned integer datatypes. Gava has $ n $ unsigned integer datatypes of sizes (in bits) $ a_{1},a_{2},...\ a_{n} $ . The $ i $ -th datatype have size $ a_{i} $ bits, so it can represent every integer between $ 0 $ and $ 2^{a_{i}}-1 $ inclusive.

Tuftuf is thinking of learning a better programming language. If there exists an integer $ x $ , such that $ x $ fits in some type $ i $ (in $ a_{i} $ bits) and $ x·x $ does not fit in some other type $ j $ (in $ a_{j} $ bits) where $ a_{i}&lt;a_{j} $ , then Tuftuf will stop using Gava.

Your task is to determine Tuftuf's destiny.

## 说明/提示

In the second example, $ x=7 $ $ (111_{2}) $ fits in $ 3 $ bits, but $ x^{2}=49 $ $ (110001_{2}) $ does not fit in $ 4 $ bits.

## 样例 #1

### 输入

```
3
64 16 32
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
4
4 2 1 3
```

### 输出

```
YES
```

# AI分析结果



# 中文题目重写（保持原格式）

## 题目描述

Tattah 的弟弟 Tuftuf 刚接触编程。他渴望超越哥哥，目前在德国开罗大学 (GUC) 学习 Gava 语言。今天，Tuftuf 学习了 Gava 的无符号整数数据类型。

Gava 有 $n$ 种无符号整型，位数分别为 $a_1,a_2,...a_n$。第 $i$ 种类型能表示 $0$ 到 $2^{a_i}-1$ 的整数。

若存在整数 $x$，使得 $x$ 能存入某类型 $i$（位数 $a_i$），但 $x^2$ 无法存入另一个位数更大的类型 $j$（$a_j > a_i$），则 Tuftuf 会放弃 Gava。你需要判断这种情况是否存在。

## 说明/提示

样例 2 中，$x=7$（二进制 111）可用 3 位存储，但 $x^2=49$（二进制 110001）需要 6 位，超过 4 位类型的最大值 15。

## 样例 #1

### 输入
```
3
64 16 32
```

### 输出
```
NO
```

## 样例 #2

### 输入
```
4
4 2 1 3
```

### 输出
```
YES
```

---

**算法分类**：数学

---

### 题解综合分析

题目核心在于找出是否存在两个位数类型 $a_i < a_j$，使得 $x$ 在 $a_i$ 范围内，但 $x^2$ 超出 $a_j$ 范围。通过数学推导可得条件 $2a_i > a_j$，利用排序优化后只需检查相邻元素。

---

### 精选题解（评分≥4）

#### 1. Larryyu（★★★★☆）
**亮点**：清晰的数学推导与简洁实现  
**代码核心**：
```cpp
sort(a+1,a+1+n);
for(int i=1;i<n;i++)
    if(a[i]<a[i+1] && a[i]*2>a[i+1])
        cout<<"YES";
```
**思路**：排序后遍历，检查是否存在相邻元素满足 $2a_i > a_{i+1}$。

#### 2. ZM____ML（★★★★☆）  
**亮点**：详细解释为何只需比较相邻元素  
**关键分析**：  
> "排序后如果存在满足条件的 $a_i,a_j$，则相邻元素必定存在该条件，否则可以通过传递性推导矛盾。"

#### 3. CheerJustice（★★★★☆）  
**亮点**：严谨的不等式推导流程  
**数学推导**：  
$$x < 2^{a_i} \Rightarrow x^2 < 2^{2a_i}$$  
$$x^2 > 2^{a_j}-1 \Rightarrow 2^{2a_i} > 2^{a_j} \Rightarrow 2a_i > a_j$$

---

### 关键思路总结
1. **数学转换**：将问题转化为寻找满足 $a_i < a_j$ 且 $2a_i > a_j$ 的元素对。
2. **排序优化**：通过排序将双重循环简化为单次遍历，时间复杂度降至 $O(n\log n)$。
3. **相邻检查**：排序后只需比较相邻元素，若存在满足条件的元素对，必能在相邻元素中找到。

---

### 拓展与应用
- **类似题型**：寻找满足特定不等式关系的元素对（如两数之和/差/商等）。
- **优化思路**：在涉及元素间关系的题目中，排序往往是降低时间复杂度的有效手段。
- **易错点**：忽略 $a_i$ 必须严格小于 $a_j$ 的条件，或未处理重复元素。

---

### 推荐练习题
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）  
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（双指针/哈希）  
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（DP+二分优化）  

---

### 题解心得摘录
- **ZM____ML**：  
> "其他题解对为何只需比较相邻元素解释不清，其实排序后若存在满足条件的 $a_i,a_j$，则必定存在 $a_k,a_{k+1}$ 也满足条件。"  
- **Katsura_Hinagiku**：  
> "通过极值分析发现，当 $x=2^{a_i}-1$ 时 $x^2$ 的范围为 $(2^{2a_i-1}, 2^{2a_i})$，此观察简化了条件判断。"

---
处理用时：76.31秒