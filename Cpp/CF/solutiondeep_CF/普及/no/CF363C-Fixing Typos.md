# 题目信息

# Fixing Typos

## 题目描述

Many modern text editors automatically check the spelling of the user's text. Some editors even suggest how to correct typos.

In this problem your task to implement a small functionality to correct two types of typos in a word. We will assume that three identical letters together is a typo (for example, word "helllo" contains a typo). Besides, a couple of identical letters immediately followed by another couple of identical letters is a typo too (for example, words "helloo" and "wwaatt" contain typos).

Write a code that deletes the minimum number of letters from a word, correcting described typos in the word. You are allowed to delete letters from both ends and from the middle of the word.

## 说明/提示

The second valid answer to the test from the statement is "heloo".

## 样例 #1

### 输入

```
helloo
```

### 输出

```
hello
```

## 样例 #2

### 输入

```
woooooow
```

### 输出

```
woow
```

# AI分析结果



# Fixing Typos

## 题目描述

现代文本编辑器通常会自动检查用户拼写错误。本题需要实现纠正单词中两种类型打字错误的功能：
1. 三个连续相同字母视为错误（如"helllo"）
2. 两对相同字母连续出现视为错误（如"helloo"或"wwaatt"）

要求删除最少的字母，输出修正后的正确单词。

## 标签
模拟

---

## 题解综合分析

### 最优题解（5星）

**作者：andyli**  
**核心思路**：  
维护结果字符串，逐个添加字符时实时检查后三位和后四位的情况：
1. 添加后若出现三个连续相同字母，弹出最后字符
2. 添加后若出现两对相同字母连续（如AABB），弹出最后字符

**实现优势**：  
- 时间复杂度O(n)，每个字符最多处理两次
- 无需回溯处理原字符串，空间效率高
- 逻辑简洁，边界条件处理完善

**关键代码**：
```cpp
std::string ans;
foreach(c, S) {
    ans += c;
    int n = ans.size();
    if (n >= 3 && ans[n-1] == ans[n-2] && ans[n-2] == ans[n-3])
        ans.pop_back();
    if (n >= 4 && ans[n-1] == ans[n-2] && ans[n-3] == ans[n-4])
        ans.pop_back();
}
```

### 通用优化技巧
1. **实时维护法**：对于需要持续满足条件的字符串处理问题，可维护结果容器并实时检查
2. **滑动窗口思想**：通过维护固定长度的字符窗口处理连续型问题
3. **逆向处理**：通过弹出操作替代删除操作，避免字符串频繁修改的开销

---

## 类似题目推荐
1. P1308 统计单词数 - 字符串模式匹配
2. P1598 垂直柱状图 - 字符频率统计
3. P1071 潜伏者 - 字符映射与替换

---
处理用时：234.35秒