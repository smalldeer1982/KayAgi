# 题目信息

# Guess The String

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury has chosen a string $ s $ consisting of $ n $ characters; each character of $ s $ is a lowercase Latin letter. Your task is to guess this string; initially, you know only its length.

You may ask queries of two types:

- $ 1 $ $ i $ — the query of the first type, where $ i $ is an integer from $ 1 $ to $ n $ . In response to this query, the jury will tell you the character $ s_i $ ;
- $ 2 $ $ l $ $ r $ — the query of the second type, where $ l $ and $ r $ are integers such that $ 1 \le l \le r \le n $ . In response to this query, the jury will tell you the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type. Your task is to restore the string $ s $ .

For each test in this problem, the string $ s $ is fixed beforehand, and will be the same for every submission.

## 说明/提示

Let's analyze the example of interaction.

The string chosen by the jury is guess, so initially the jury sends one integer $ 5 $ .

1. the first query is ? 2 1 5, which means "count the number of different characters among $ s_1, s_2, \dots, s_5 $ ". The answer to it is $ 4 $ .
2. the second query is ? 1 2, which means "tell which character is $ s_2 $ ". The answer to it is u.
3. the third query is ? 2 1 2, which means "count the number of different characters among $ s_1 $ and $ s_2 $ ". The answer to it is $ 2 $ .
4. the fourth query is ? 1 1, which means "tell which character is $ s_1 $ ". The answer to it is g.
5. the fifth query is ? 1 3, which means "tell which character is $ s_3 $ ". The answer to it is e.
6. the sixth query is ? 1 4, which means "tell which character is $ s_4 $ ". The answer to it is s.
7. the seventh query is ? 2 4 5, which means "count the number of different characters among $ s_4 $ and $ s_5 $ ". The answer to it is $ 1 $ , so it's possible to deduce that $ s_4 $ is the same as $ s_5 $ .

In the end, the answer is submitted as ! guess, and it is deduced correctly.

## 样例 #1

### 输入

```
5
4
u
2
g
e
s
1```

### 输出

```
? 2 1 5
? 1 2
? 2 1 2
? 1 1
? 1 3
? 1 4
? 2 4 5
! guess```

# AI分析结果



# Guess The String

## 题目描述

**题目背景**  
这是一个交互题。在与测试程序通信时，请确保及时刷新输出缓冲区。你可以使用C++中的`fflush(stdout)`、Java中的`system.out.flush()`、Python中的`stdout.flush()`或Pascal中的`flush(output)`。若使用其他语言，请查阅相关文档。交互题指南可参考：<https://codeforces.com/blog/entry/45307>。

**题目要求**  
裁判选定了一个由小写拉丁字母组成的字符串$s$，长度为$n$。你的任务是通过两种类型的查询猜出该字符串：

1. **查询类型1**：`1 i`，询问第$i$个位置的字符（$1 \le i \le n$）。
2. **查询类型2**：`2 l r`，询问区间$[l, r]$内不同字符的数量（$1 \le l \le r \le n$）。

**限制条件**  
- 类型1查询最多使用26次。
- 类型2查询最多使用6000次。

---

### 题解综合分析

所有题解的核心思路均围绕以下两点展开：
1. **预处理字符集**：利用类型1查询确定字符串中所有不同的字符（最多26次）。
2. **维护最后出现位置**：通过类型2查询二分确定每个位置的字符，时间复杂度为$O(n \log 26)$。

#### 最优思路总结
- **关键数据结构**：维护每个字符的最后出现位置数组，按位置单调递增排序。
- **二分策略**：对于每个未知位置$i$，在最后出现位置数组上二分，通过比较区间$[a[mid].pos, i]$的不同字符数量，判断当前字符是否属于已有字符。
- **动态更新**：每次确定字符后更新该字符的最后出现位置，保持数组有序。

---

### 高分题解推荐

#### 题解1：TH讠NK (⭐⭐⭐⭐⭐)
**核心亮点**  
- **预处理优化**：通过类型2查询识别新字符的出现，避免浪费类型1查询。
- **二分逻辑清晰**：利用`(a[mid].pos, i)`区间查询结果与期望值的差值，精准定位字符。
- **代码实现**：通过结构体数组维护最后出现位置，每次二分后动态调整数组顺序。

**关键代码**  
```cpp
struct node { int x, pos; }; // x为字符编号，pos为最后出现位置
vector<node> a;

for (int i = 1; i <= n; i++) {
    if (!id[i]) {
        // 二分查找逻辑
        int l = 1, r = mx;
        while (l < r) {
            mid = (l + r + 1) >> 1;
            t = ask2(a[mid].pos, i);
            if (t == mx - mid + 1) l = mid;
            else r = mid - 1;
        }
        id[i] = a[l].x;
        // 更新最后出现位置数组
        for (int j = l; j < mx; j++) a[j] = a[j+1];
    }
    a[++mx] = {id[i], i}; // 插入新位置并保持有序
}
```

---

#### 题解2：Sellaris (⭐⭐⭐⭐)
**核心亮点**  
- **简洁的维护方式**：直接使用结构体数组按位置排序，避免复杂操作。
- **高效二分**：通过比较区间不同字符数与预期差值，快速定位字符。
- **代码可读性**：逻辑清晰，适合快速理解核心思路。

**关键代码**  
```cpp
struct node { int id, pos; };
vector<node> st; // 按pos递增排序的字符数组

for (int i = 1; i <= n; i++) {
    sort(st.begin(), st.end(), cmp); // 按位置排序
    int l = 1, r = top, jl = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (ask2(st[mid].pos, i) != (top - mid + 1) + 1) {
            jl = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    // 根据二分结果更新字符
}
```

---

### 关键技巧总结
1. **最后位置维护**：通过记录字符的最后出现位置，将问题转化为单调区间上的二分。
2. **交互优化**：仅在必要时使用类型1查询，优先通过类型2查询缩小范围。
3. **动态调整数组**：每次确定字符后更新位置数组，保持有序性以提高二分效率。

---

### 类似题目推荐
1. [CF727C - Guess the Array](https://codeforces.com/problemset/problem/727/C)  
   **考察点**：交互题设计，通过差值推断数组元素。
2. [CF1527D - MEX Tree](https://codeforces.com/problemset/problem/1527/D)  
   **考察点**：维护MEX值的动态计算，类似字符集的维护。
3. [CF862D - Mahmoud and Ehab and the binary string](https://codeforces.com/problemset/problem/862/D)  
   **考察点**：通过二分查询定位特定字符的位置。

---
处理用时：59.88秒