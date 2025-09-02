# 题目信息

# Letters Rearranging

## 题目描述

You are given a string $ s $ consisting only of lowercase Latin letters.

You can rearrange all letters of this string as you wish. Your task is to obtain a good string by rearranging the letters of the given string or report that it is impossible to do it.

Let's call a string good if it is not a palindrome. Palindrome is a string which is read from left to right the same as from right to left. For example, strings "abacaba", "aa" and "z" are palindromes and strings "bba", "xd" are not.

You have to answer $ t $ independent queries.

## 说明/提示

In the first query we cannot rearrange letters to obtain a good string.

Other examples (not all) of correct answers to the second query: "ababaca", "abcabaa", "baacaba".

In the third query we can do nothing to obtain a good string.

## 样例 #1

### 输入

```
3
aa
abacaba
xdd
```

### 输出

```
-1
abaacba
xdd```

# AI分析结果



# Letters Rearranging

## 题目描述

给定一个仅由小写字母组成的字符串 $ s $。你可以重新排列该字符串的所有字符，目标是得到一个"好字符串"（即非回文串）。若无法做到则输出 -1。需要处理 $ t $ 个独立测试用例。

## 说明/提示

当字符串全为相同字符时，无法构造非回文串。其他情况下，例如输入 "abacaba" 可以有多种有效排列如 "abaacba"。

## 样例 #1

### 输入
```
3
aa
abacaba
xdd
```

### 输出
```
-1
abaacba
xdd
```

**算法分类**：构造、字符串

---

## 题解综合分析

### 核心思路对比
1. **排序法**（4题解采用）：排序后若首尾字符不同则必然非回文，否则全相同输出-1
2. **交换法**：找到第一对不同字符交换破坏回文结构
3. **全排列/随机法**：通过枚举排列或随机打乱寻找解（效率较低）

### 最优思路提炼
**排序法**是最优解：
1. 时间复杂度 O(n log n)，对本题数据完全可行
2. 只需检查首尾字符即可确定是否可构造
3. 代码简洁（约5行核心逻辑）

---

## 高星题解推荐

### 题解1（作者：Sooke） ★★★★★
**亮点**：极简实现，利用排序后首尾不同的特性  
**关键代码**：
```cpp
std::sort(s.begin(), s.end());
if(s[0] == s[s.size()-1]) std::cout << -1;
else std::cout << s;
```

### 题解2（作者：一扶苏一） ★★★★☆  
**亮点**：Python实现同样思路，强调字符分组思想  
**代码片段**：
```python
ss = sorted(s)
if ss[0] == ss[-1]: print(-1)
else: print(''.join(ss))
```

### 题解3（作者：little_sun） ★★★★  
**亮点**：C++标准实现，包含边界处理  
**关键判断**：
```cpp
if(s[0] == s[len-1]) printf("-1\n");
else std::cout << s;
```

---

## 拓展与总结

**关键技巧**：对于构造类问题，优先考虑排序后的极值位置（首尾字符）特性  
**同类题目推荐**：
1. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)（字符串排序应用）
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)（自定义排序规则）
3. [CF1294B Collecting Packages](https://codeforces.com/problemset/problem/1294/B)（路径构造）

**调试心得**（来自题解）：
> 作者Reywmp提到："比赛时没想到排序法，采用交换法后发现处理各种边界条件较复杂"，最终验证了排序法的简洁性  
> 作者happybob尝试全排列法后意识到："当n较大时next_permutation会超时"，验证了算法选择的重要性

---
处理用时：41.92秒