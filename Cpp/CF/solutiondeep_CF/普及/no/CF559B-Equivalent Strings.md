# 题目信息

# Equivalent Strings

## 题目描述

Today on a lecture about strings Gerald learned a new definition of string equivalency. Two strings $ a $ and $ b $ of equal length are called equivalent in one of the two cases:

1. They are equal.
2. If we split string $ a $ into two halves of the same size $ a_{1} $ and $ a_{2} $ , and string $ b $ into two halves of the same size $ b_{1} $ and $ b_{2} $ , then one of the following is correct: 
  1. $ a_{1} $ is equivalent to $ b_{1} $ , and $ a_{2} $ is equivalent to $ b_{2} $
  2. $ a_{1} $ is equivalent to $ b_{2} $ , and $ a_{2} $ is equivalent to $ b_{1} $

As a home task, the teacher gave two strings to his students and asked to determine if they are equivalent.

Gerald has already completed this home task. Now it's your turn!

## 说明/提示

In the first sample you should split the first string into strings "aa" and "ba", the second one — into strings "ab" and "aa". "aa" is equivalent to "aa"; "ab" is equivalent to "ba" as "ab" = "a" + "b", "ba" = "b" + "a".

In the second sample the first string can be splitted into strings "aa" and "bb", that are equivalent only to themselves. That's why string "aabb" is equivalent only to itself and to string "bbaa".

## 样例 #1

### 输入

```
aaba
abaa
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
aabb
abab
```

### 输出

```
NO
```

# AI分析结果



【题目翻译】

# 等价字符串

## 题目描述

Gerald在关于字符串的讲座中学习了一个新的等价定义。两个长度相等的字符串$a$和$b$被称为等价的情况有两种：

1. 它们完全相同。
2. 若将$a$分为等长的两半$a_1$和$a_2$，将$b$分为等长的两半$b_1$和$b_2$，则以下任一情况成立：
   - $a_1$与$b_1$等价，且$a_2$与$b_2$等价
   - $a_1$与$b_2$等价，且$a_2$与$b_1$等价

你需要判断给定的两个字符串是否等价。

---

【算法分类】  
分治

---

### 题解对比与结论

#### 关键思路对比
1. **直接递归法**（ljk8886初始方案）：  
   - 时间复杂度：O(4^log n) → 超时  
   - 递归层数多，存在重复计算  

2. **最小字典序构造法**（ljk8886优化方案/DennyQi方案）：  
   - 核心思想：将字符串递归转换为最小字典序形态  
   - 时间复杂度：O(n log n)  
   - 关键优化：每个递归层级仅处理一次合并操作  

3. **哈希剪枝法**（allenchoi方案）：  
   - 使用哈希快速比较字符串  
   - 剪枝策略：字符出现次数统计  
   - 时间复杂度：O(n log n)  

#### 最优解法结论
最小字典序构造法是最优方案，通过将字符串转换为唯一的最小形态进行比较，既保证了正确性，又具有最优时间复杂度。

---

### 精选题解

#### 1. ljk8886（5星）
**核心亮点**  
- 创新性提出最小字典序构造法  
- 代码简洁，时间复杂度最优  
- 通过分治策略实现O(n log n)复杂度  

**关键代码**  
```cpp
string minstr(string s) {
    if (s.size() & 1) return s;
    string s1 = minstr(s.substr(0, s.size()/2));
    string s2 = minstr(s.substr(s.size()/2));
    return (s1 < s2) ? (s1 + s2) : (s2 + s1);
}
// 比较minstr(a) == minstr(b)
```

#### 2. DennyQi（4星）
**核心亮点**  
- 与最小字典序法思路一致  
- 代码结构清晰，易于理解  
- 使用字符串拼接优化比较  

**个人心得**  
> "通过将等价集合映射到最小字典序形式，可以将复杂的递归判断转换为简单的字符串比较"

---

### 同类题目推荐
1. [P3805 最长回文子串](https://www.luogu.com.cn/problem/P3805)  
   - 相似点：字符串分割与递归处理  
2. [CF525D Arthur and Walls](https://codeforces.com/problemset/problem/525/D)  
   - 相似点：基于分治的构造策略  
3. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)  
   - 相似点：区间分割与动态规划结合  

---

### 调试技巧总结
1. **剪枝优化**：在递归中预判字符出现次数可减少无效递归分支（见于allenchoi方案）  
2. **字典序技巧**：通过强制排序子串来消除交换对称性（如ljk8886的minstr函数）  
3. **边界处理**：奇偶长度分界处需要特别处理，否则会导致无限递归

---
处理用时：54.23秒