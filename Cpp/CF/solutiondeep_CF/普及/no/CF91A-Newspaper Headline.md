# 题目信息

# Newspaper Headline

## 题目描述

A newspaper is published in Walrusland. Its heading is $ s_{1} $ , it consists of lowercase Latin letters. Fangy the little walrus wants to buy several such newspapers, cut out their headings, glue them one to another in order to get one big string. After that walrus erase several letters from this string in order to get a new word $ s_{2} $ . It is considered that when Fangy erases some letter, there's no whitespace formed instead of the letter. That is, the string remains unbroken and it still only consists of lowercase Latin letters.

For example, the heading is "abc". If we take two such headings and glue them one to the other one, we get "abcabc". If we erase the letters on positions $ 1 $ and $ 5 $ , we get a word "bcac".

Which least number of newspaper headings $ s_{1} $ will Fangy need to glue them, erase several letters and get word $ s_{2} $ ?

## 样例 #1

### 输入

```
abc
xyz
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
abcd
dabc
```

### 输出

```
2
```

# AI分析结果



### 题目重述
# 报纸标题

## 题目描述

报纸《Walrusland》的标题是字符串 $s_1$，由小写拉丁字母组成。小海象Fangy想购买多份报纸，将标题剪下拼接成一个大字符串后，通过删除部分字符得到目标字符串 $s_2$。求最少需要多少个 $s_1$ 拼接才能完成此操作。

例如：当 $s_1$= "abc" 时，拼接两次得到 "abcabc"。删除位置1和5的字符得到 "bcac"。

## 输入输出样例

### 样例 #1
输入：
```
abc
xyz
```
输出：
```
-1
```

### 样例 #2
输入：
```
abcd
dabc
```
输出：
```
2
```

### 算法分类
**贪心**、**字符串处理**、**二分查找**

---

### 题解综合分析

#### 核心思路
所有题解均采用预处理字符位置的策略，主要分为两类：
1. **二分查找法**：为每个字符预存出现位置，遍历 $s_2$ 时通过二分查找确定下一个字符位置。
2. **动态规划预处理**：构建每个位置后各字符首次出现的位置表，直接查表递推。

#### 解决难点
1. **跨字符串拼接处理**：当当前 $s_1$ 片段无法找到后续字符时，需切换到新拼接的 $s_1$。
2. **快速定位字符**：通过预处理避免每次线性扫描，将时间复杂度优化至 $O(|s_2|\log|s_1|)$。

---

### 精选题解

#### 题解1：b6e0_（⭐⭐⭐⭐⭐）
**关键亮点**：
- 使用 `vector` 预存字符位置，配合 `upper_bound` 二分查找。
- 代码简洁高效，处理跨字符串逻辑清晰。
```cpp
vector<int> pos[300]; // 预处理字符位置
for (int i = 0; i < s1.size(); i++)
    pos[s1[i]].push_back(i);

int ans = 0, current_pos = -1;
for (char c : s2) {
    auto& vec = pos[c];
    auto it = upper_bound(vec.begin(), vec.end(), current_pos);
    if (it == vec.end()) { // 需要新拼接
        ans++;
        current_pos = vec[0];
    } else {
        current_pos = *it;
    }
}
```

#### 题解2：HEzzz（⭐⭐⭐⭐）
**关键亮点**：
- 使用 `set` 存储字符位置，利用其自动排序特性。
- 通过迭代器操作简化越界判断。
```cpp
set<int> pos[26];
for (int i = 0; s1[i]; i++)
    pos[s1[i]-'a'].insert(i);

int ans = 1, last = -1;
for (int i = 0; s2[i]; i++) {
    auto& s = pos[s2[i]-'a'];
    auto it = s.upper_bound(last);
    if (it == s.end()) { // 切换新字符串
        ans++;
        last = *s.begin();
    } else {
        last = *it;
    }
}
```

#### 题解3：TsH_GD（⭐⭐⭐）
**动态规划预处理**：
- 构建 `f[i][c]` 表示位置i后字符c首次出现的位置。
- 直接查表递推，无需二分。
```cpp
int f[10005][30]; 
for (int i = 0; i < len1; i++)
    for (int j = i+1; j < len1; j++)
        if (f[i][s1[j]-'a'] == -1)
            f[i][s1[j]-'a'] = j;

int now = vis[s2[0]-'a'];
for (int i = 1; i < len2; i++) {
    int next = f[now][s2[i]-'a'];
    if (next == -1) { // 切换新字符串
        ans++;
        now = vis[s2[i]-'a'];
    } else {
        now = next;
    }
}
```

---

### 最优策略总结
**关键技巧**：
1. **字符位置预处理**：将 $s_1$ 中各字符的出现位置预存，便于快速访问。
2. **二分查找优化**：在遍历 $s_2$ 时，通过二分确定下一个字符的位置，时间复杂度最优。
3. **贪心拼接计数**：当无法在当前 $s_1$ 中找到后续字符时，立即切换到新字符串。

**同类拓展**：
- 类似题目可考虑字符串匹配中的最短覆盖问题（如 LC 76）、循环字符串处理（如 CF 52C）。

---

### 推荐练习
1. [CF 52C - Circular RMQ](https://codeforces.com/problemset/problem/52/C)（循环数组处理）
2. [洛谷 P2925 - 干草出售](https://www.luogu.com.cn/problem/P2925)（贪心策略）
3. [LC 76 - 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/)（滑动窗口与字符位置处理）

---
处理用时：62.04秒