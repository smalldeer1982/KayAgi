# 题目信息

# Update Queries

## 题目描述

Let's consider the following simple problem. You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters, as well as an array of indices $ ind $ of length $ m $ ( $ 1 \leq ind_i \leq n $ ) and a string $ c $ of length $ m $ , consisting of lowercase Latin letters. Then, in order, you perform the update operations, namely, during the $ i $ -th operation, you set $ s_{ind_i} = c_i $ . Note that you perform all $ m $ operations from the first to the last.

Of course, if you change the order of indices in the array $ ind $ and/or the order of letters in the string $ c $ , you can get different results. Find the lexicographically smallest string $ s $ that can be obtained after $ m $ update operations, if you can rearrange the indices in the array $ ind $ and the letters in the string $ c $ as you like.

A string $ a $ is lexicographically less than a string $ b $ if and only if one of the following conditions is met:

- $ a $ is a prefix of $ b $ , but $ a \neq b $ ;
- in the first position where $ a $ and $ b $ differ, the symbol in string $ a $ is earlier in the alphabet than the corresponding symbol in string $ b $ .

## 说明/提示

In the first set of input data, you can leave the array $ ind $ and the string $ c $ unchanged and simply perform all operations in that order.

In the second set of input data, you can set the array $ ind = [1, 1, 4, 2] $ and $ c = $ "zczw". Then the string $ s $ will change as follows: $ meow \rightarrow zeow \rightarrow ceow \rightarrow ceoz \rightarrow cwoz $ .

In the third set of input data, you can leave the array $ ind $ unchanged and set $ c =  $ "admn". Then the string $ s $ will change as follows: $ abacaba \rightarrow abacaba \rightarrow abdcaba \rightarrow abdcmba \rightarrow abdcmbn $ .

## 样例 #1

### 输入

```
4
1 2
a
1 1
cb
4 4
meow
1 2 1 4
zcwz
7 4
abacaba
1 3 5 7
damn
7 10
traktor
7 6 5 4 3 2 1 6 4 2
codeforces```

### 输出

```
b
cwoz
abdcmbn
ccdeefo```

# AI分析结果



### 题目重述
#### 题目描述
给定一个长度为 $n$ 的字符串 $s$，以及两个长度为 $m$ 的数组 $ind$ 和字符串 $c$。你可以任意调整 $ind$ 和 $c$ 的顺序，然后依次执行操作：将 $s$ 的第 $ind_i$ 个字符替换为 $c_i$。要求找到最终字典序最小的字符串 $s$。

#### 输入输出样例
样例输入：
```
4 4
meow
1 2 1 4
zcwz
```
样例输出：
```
cwoz
```

---

### 题解分析与结论

#### 核心思路
1. **贪心策略**：将 $ind$ 数组升序排列（优先处理靠前的位置），将 $c$ 字符串升序排列（优先使用更小的字符）。
2. **去重处理**：对于重复的 $ind$ 元素，只保留第一个出现的，因为后续重复的操作会被覆盖，最终只有最后一次修改有效。因此，将 $ind$ 去重后按升序排列，确保每个位置只分配一次最小的可用字符。
3. **字符分配**：将排序后的 $c$ 的前 $k$ 个字符（$k$ 为去重后的 $ind$ 元素数量）依次分配给去重后的 $ind$ 元素对应的位置。

#### 关键优化点
- **排序与去重**：通过排序确保贪心策略的正确性，去重避免无效覆盖。
- **时间复杂度**：排序复杂度为 $O(m \log m)$，遍历复杂度为 $O(m)$，整体高效。

#### 最优题解
##### 题解作者：zhouchuer（5星）
**亮点**：
- 代码简洁清晰，直接使用排序和去重处理。
- 正确处理了 0-based 和 1-based 索引转换。

**核心代码**：
```cpp
sort(ind+1, ind+m+1);
sort(c+1, c+m+1);
int cnt = 0;
for (int i=1; i<=m; i++) {
    if (ind[i] != ind[i-1]) {
        s[ind[i]-1] = c[++cnt]; // 转换为 0-based
    }
}
cout << s << endl;
```

##### 题解作者：CaiZi（5星）
**亮点**：
- 使用 `unique` 函数去重，逻辑更简洁。
- 正确处理输入输出的索引转换。

**核心代码**：
```cpp
sort(ind+1, ind+m+1);
sort(c.begin(), c.end());
int p = 0;
for (int i=1; i<=m; i++) {
    if (ind[i] != ind[i-1]) {
        s[ind[i]-1] = c[p++];
    }
}
```

#### 关键技巧总结
1. **贪心排序**：将 $ind$ 和 $c$ 分别排序，确保靠前的位置优先使用更小的字符。
2. **去重处理**：通过遍历跳过重复的 $ind$ 元素，避免无效覆盖。
3. **索引转换**：注意题目中的 1-based 索引与代码中的 0-based 字符串的转换。

---

### 拓展练习
1. **[CF455A Boredom](https://codeforces.com/problemset/problem/455/A)**：动态规划与贪心结合，处理重复元素的最优选择。
2. **[CF977D Divide by Three](https://codeforces.com/problemset/problem/977/D)**：贪心排序与数学性质结合。
3. **[P1090 合并果子](https://www.luogu.com.cn/problem/P1090)**：优先队列实现贪心策略。

---

### 个人心得摘录
- **索引转换**：多位题解作者强调注意题目中 1-based 和代码中字符串 0-based 的转换。
- **去重逻辑**：通过排序后相邻元素比较去重，而非使用集合，优化了空间复杂度。

---
处理用时：311.01秒