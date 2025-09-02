# 题目信息

# Hard problem

## 题目描述

Vasiliy is fond of solving different tasks. Today he found one he wasn't able to solve himself, so he asks you to help.

Vasiliy is given $ n $ strings consisting of lowercase English letters. He wants them to be sorted in lexicographical order (as in the dictionary), but he is not allowed to swap any of them. The only operation he is allowed to do is to reverse any of them (first character becomes last, second becomes one before last and so on).

To reverse the $ i $ -th string Vasiliy has to spent $ c_{i} $ units of energy. He is interested in the minimum amount of energy he has to spent in order to have strings sorted in lexicographical order.

String $ A $ is lexicographically smaller than string $ B $ if it is shorter than $ B $ ( $ |A|<|B| $ ) and is its prefix, or if none of them is a prefix of the other and at the first position where they differ character in $ A $ is smaller than the character in $ B $ .

For the purpose of this problem, two equal strings nearby do not break the condition of sequence being sorted lexicographically.

## 说明/提示

In the second sample one has to reverse string $ 2 $ or string $ 3 $ . To amount of energy required to reverse the string $ 3 $ is smaller.

In the third sample, both strings do not change after reverse and they go in the wrong order, so the answer is $ -1 $ .

In the fourth sample, both strings consists of characters 'a' only, but in the sorted order string "aa" should go before string "aaa", thus the answer is $ -1 $ .

## 样例 #1

### 输入

```
2
1 2
ba
ac
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 3 1
aa
ba
ac
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
5 5
bbb
aaa
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
3 3
aaa
aa
```

### 输出

```
-1
```

# AI分析结果



# Hard problem

## 题目描述

Vasiliy 得到 $n$ 个由小写字母组成的字符串。他需要通过反转某些字符串（每次反转消耗 $c_i$ 能量），使得所有字符串按字典序排列。求最小能量消耗，若无法完成则输出 -1。

字典序规则：
1. 若字符串 A 是 B 的前缀且更短，则 A < B
2. 在首个不同字符处，字符较小的字符串较小

## 标签
动态规划

---

### 题解分析与结论

**核心思路**：使用动态规划维护每个字符串正/反两种状态的最小消耗。设：
- `dp[i][0]` 表示第 i 个字符串保持原状时的最小消耗
- `dp[i][1]` 表示第 i 个字符串反转后的最小消耗

**转移方程**：
- 比较前序字符串的正/反状态与当前字符串的正/反状态的字典序关系
- 取满足字典序条件的最小消耗路径

---

### 高分题解推荐

#### 题解1：CDFLS_mao_zx（⭐⭐⭐⭐⭐）
**亮点**：  
- 状态转移直观清晰，处理四种可能转移路径  
- 使用预处理的反转字符串数组优化比较  
- 初始化和边界处理规范  

**核心代码**：
```cpp
for(int i=2;i<=n;i++) {
    if(a[i+n] >= a[i-1])  // 前序正，当前反
        dp[i][1] = min(dp[i][1], dp[i-1][0] + v[i]);
    if(a[i] >= a[i-1])    // 前序正，当前正
        dp[i][0] = min(dp[i][0], dp[i-1][0]);
    if(a[i+n] >= a[i+n-1])// 前序反，当前反
        dp[i][1] = min(dp[i][1], dp[i-1][1] + v[i]);
    if(a[i] >= a[i+n-1])  // 前序反，当前正
        dp[i][0] = min(dp[i][0], dp[i-1][1]);
}
```

---

#### 题解2：Yukinoshita_Yukino（⭐⭐⭐⭐⭐）
**亮点**：  
- 代码简洁规范，变量命名清晰  
- 使用独立反转字符串数组提升可读性  
- 完全覆盖四种比较情况  

**核心实现**：
```cpp
for(int i=2;i<=n;i++) {
    if(str[i] >= str[i-1]) 
        dp[i][0] = min(dp[i][0], dp[i-1][0]);
    if(str[i] >= res[i-1]) 
        dp[i][0] = min(dp[i][0], dp[i-1][1]);
    if(res[i] >= res[i-1]) 
        dp[i][1] = min(dp[i][1], dp[i-1][1] + c[i]);
    if(res[i] >= str[i-1]) 
        dp[i][1] = min(dp[i][1], dp[i-1][0] + c[i]);
}
```

---

### 关键技巧总结
1. **状态设计**：用二维状态表示字符串的正/反状态  
2. **预处理优化**：预先反转所有字符串减少重复计算  
3. **字典序处理**：直接使用字符串比较运算符简化判断逻辑  
4. **空间优化**：滚动数组可将空间复杂度优化至 O(1)  

---

### 拓展练习
1. [CF910C] Minimum Sum（字符串操作+贪心）  
2. [P1279 字串距离](https://www.luogu.com.cn/problem/P1279)（字符串编辑距离DP）  
3. [P1140 相似基因](https://www.luogu.com.cn/problem/P1140)（双状态转移DP）

---
处理用时：60.26秒