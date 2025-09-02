# 题目信息

# [ICPC 2022 Xi'an R] Perfect Word

## 题目描述

给定 $n$ 个字符串，你需要找到最长的「完美单词」。

字符串 $t$ 称为「完美单词」，当且仅当它的所有非空子串都出现在给定的字符串中。

字符串 $s$ 称为 $t$ 的子串，当且仅当 $s$ 可由 $t$ 在开头和结尾分别删去零个或若干个字符得到。

$1\leq n\leq 10 ^ 5$，字符串仅由小写字母组成，且总长不超过 $10 ^ 5$。

## 样例 #1

### 输入

```
4
a
t
b
ab
```

### 输出

```
2
```

# AI分析结果

### 算法分类
字符串

### 综合分析与结论
题目要求找到最长的「完美单词」，即所有非空子串都出现在给定字符串中的字符串。各题解主要采用了以下几种思路：
1. **字典树（Trie）**：通过字典树存储所有字符串，并利用递推思想判断字符串是否为「完美单词」。
2. **暴力枚举**：通过 `map` 或 `multiset` 存储所有字符串，暴力枚举每个字符串的所有子串，判断是否都出现过。
3. **优化暴力**：通过排序和剪枝，减少不必要的子串检查，提升效率。

### 所选高星题解
#### 1. 作者：Demeanor_Roy (5星)
**关键亮点**：
- 使用字典树存储字符串，递推判断「完美单词」。
- 代码结构清晰，逻辑严谨，时间复杂度较低。

**核心代码**：
```cpp
inline void insert(int cur) {
    int p = 0;
    for (int i = 0; i < (int)t[cur].size(); i++) {
        int to = t[cur][i] - 'a';
        if (!tr[p][to]) tr[p][to] = ++id;
        p = tr[p][to];
    }
    End[p] = cur;
}

inline bool check(int x) {
    if ((int)t[x].size() == 1) return true;
    int p = 0;
    for (int i = 0; i < (int)t[x].size() - 1; i++) p = tr[p][t[x][i] - 'a'];
    if (!ex[End[p]]) return false;
    p = 0;
    for (int i = 1; i < (int)t[x].size(); i++) p = tr[p][t[x][i] - 'a'];
    if (!ex[End[p]]) return false;
    return true;
}
```

#### 2. 作者：Jerrycyx (4星)
**关键亮点**：
- 利用字典树优化子串检查，时间复杂度为 \(O(n \sqrt{n})\)。
- 详细分析了字符串长度的限制，优化了算法。

**核心代码**：
```cpp
bool check(const string &str) {
    for (int i = 0; i < (int)str.length(); i++) {
        int p = 0;
        for (int j = i; j < (int)str.length(); j++) {
            int x = str[j] - 'a' + 1;
            p = trie[p][x];
            if (!ed[p]) return false;
        }
    }
    return true;
}
```

#### 3. 作者：dingshengyang (4星)
**关键亮点**：
- 通过递推公式判断「完美单词」，逻辑简洁。
- 使用字典树存储字符串，优化查询效率。

**核心代码**：
```cpp
int query(string s) {
    int p = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - '0';
        if (!son[p][c]) return 0;
        p = son[p][c];
    }
    return word[p];
}
```

### 最优关键思路
- **字典树**：通过字典树存储字符串，优化子串查询效率。
- **递推判断**：利用递推公式判断「完美单词」，减少不必要的子串检查。

### 可拓展之处
- 类似题目可以考察字符串的子串匹配、字典树的应用等。
- 可以结合其他数据结构如哈希表、后缀数组等进行优化。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3808 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3808)
3. [P3796 【模板】AC自动机（加强版）](https://www.luogu.com.cn/problem/P3796)

### 个人心得
- **调试经历**：在实现字典树时，注意节点的标记和查询逻辑，避免遗漏或错误。
- **顿悟感想**：通过递推公式判断「完美单词」，可以大大减少子串检查的次数，提升算法效率。

---
处理用时：26.41秒