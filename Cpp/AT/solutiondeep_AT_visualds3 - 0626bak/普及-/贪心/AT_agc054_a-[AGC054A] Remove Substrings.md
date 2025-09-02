# 题目信息

# [AGC054A] Remove Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc054/tasks/agc054_a

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます．

あなたは，$ S $ に対して以下の操作を好きな回数行えます．

- 先頭の文字と最後の文字が異なる連続した（非空な）部分列を選び，これを削除する．

$ S $ を空文字列にすることが可能か判定し，可能な場合は必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ S $ は英小文字からなる長さ $ N $ の文字列

### Sample Explanation 1

`abba` →（`ab`を選んで削除）→ `ba` →（`ba`を選んで削除）→ 空文字列 と操作すればよいです．

## 样例 #1

### 输入

```
4

abba```

### 输出

```
2```

## 样例 #2

### 输入

```
3

aba```

### 输出

```
-1```

# AI分析结果



无算法分类

---

### **综合分析与结论**

本题要求通过删除首尾不同的子串将字符串清空，关键在于判断可行性和最小操作次数。核心思路如下：

1. **首尾不同**：直接删除整个字符串，操作次数为1。
2. **首尾相同**：
   - 若所有字符相同，无法操作，返回-1。
   - 否则，检查是否存在至少一个字符不等于首字符，且其相邻字符中至少有一个也不同于首字符。若存在，则可通过两次操作完成，否则返回-1。

**核心难点**在于如何快速判断首尾相同时是否存在可分割的子串。通过遍历字符检查相邻字符的不同性，可在O(n)时间内解决。

---

### **最优思路与技巧提炼**

1. **首尾检查优化**：利用首尾字符是否不同直接决定第一步操作。
2. **相邻字符判断**：对于首尾相同的情况，只需检查是否存在某个字符的相邻字符不同，即可确定能否两次操作完成。

---

### **同类型题与算法套路**

类似题目通常考察字符串处理与贪心策略，例如：
1. **判断字符串能否通过特定规则完全删除**。
2. **最小操作次数满足条件的子串删除**。

---

### **推荐题目**
1. [LeetCode 680. 验证回文字符串 II](https://leetcode-cn.com/problems/valid-palindrome-ii/)
2. [LeetCode 1332. 删除回文子序列](https://leetcode-cn.com/problems/remove-palindromic-subsequences/)
3. [Codeforces 1433D. Districts Connection](https://codeforces.com/problemset/problem/1433/D)

---

### **代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    char first = s[0], last = s.back();
    if (first != last) {
        cout << 1 << endl;
        return 0;
    }
    bool all_same = true;
    for (char c : s) {
        if (c != first) {
            all_same = false;
            break;
        }
    }
    if (all_same) {
        cout << -1 << endl;
        return 0;
    }
    bool possible = false;
    for (int i = 0; i < n; ++i) {
        if (s[i] != first) {
            if (i > 0 && s[i-1] != first) {
                possible = true;
                break;
            }
            if (i < n-1 && s[i+1] != first) {
                possible = true;
                break;
            }
        }
    }
    cout << (possible ? 2 : -1) << endl;
    return 0;
}
```

**核心逻辑**：
1. **首尾不同**直接返回1。
2. **首尾相同**时检查是否所有字符相同。
3. 遍历字符串，检查是否存在满足条件的字符，决定返回2或-1。

---

### **可视化设计要点**

- **动画演示**：
  - 初始高亮首尾字符，若不同则红色标记整个字符串并删除。
  - 若首尾相同，遍历字符时高亮当前字符及相邻字符，若满足条件则展示两次删除步骤。
- **像素风格**：使用8位色块表示字符，删除时添加粒子消散效果。
- **音效**：成功删除时播放清脆音效，无解时播放低沉音效。

---

### **总结**
本题通过首尾判断与相邻字符检查，快速确定最小操作次数。关键在于利用字符串的局部特征进行贪心决策。

---
处理用时：539.00秒