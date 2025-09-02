# 题目信息

# [AGC034B] ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_b

`A`,`B`,`C` からなる文字列 $ s $ が与えられます。

すぬけ君は $ s $ に対して次の操作をできるだけ多く行おうとしています。

- $ s $ の連続した部分文字列であって `ABC` であるようなものをひとつ選び、 `BCA` に書き換える。

操作回数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ |s|\ ≦\ 200000 $
- $ s $ の各文字は `A`,`B`,`C` のいずれか

### Sample Explanation 1

`ABCABC` → `BCAABC` → `BCABCA` → `BCBCAA` とすることで $ 3 $ 回操作可能で、これが最大です。

## 样例 #1

### 输入

```
ABCABC```

### 输出

```
3```

## 样例 #2

### 输入

```
C```

### 输出

```
0```

## 样例 #3

### 输入

```
ABCACCBABCBCAABCB```

### 输出

```
6```

# AI分析结果



**算法分类**  
无算法分类（贪心策略与字符串处理）

---

### **题解思路、算法要点与解决难点**

**核心思路**  
题目要求最大化将 "ABC" 替换为 "BCA" 的操作次数。关键性质在于，每次替换后的字符串可能生成新的 "BC"，但无法直接通过线性扫描统计所有可能。正确的解法基于以下观察：

1. **预处理后缀 BC 对数目**  
   从右到左遍历字符串，记录每个位置 `i` 之后的所有 "BC" 对数目。用数组 `bc_suffix` 存储这一信息。

2. **统计连续 A 段**  
   遍历字符串，记录所有连续 'A' 的段及其结束位置。

3. **计算贡献**  
   对于每个连续 A 段，查询其结束位置之后的 "BC" 对数目，并将该数目乘以 A 段的长度，累加得到总操作次数。

**解决难点**  
- 正确统计替换后的潜在 "BC" 对数目，需预处理后缀信息。
- 连续 A 段与后续 "BC" 对的关联性，需通过分段和动态规划高效处理。

---

### **最优思路或技巧提炼**

1. **后缀预处理**  
   从右到左预处理每个位置 `i` 后的 "BC" 对数目，避免重复计算。

2. **分段统计 A**  
   将字符串中的连续 'A' 分段，每个段的贡献由其后缀 "BC" 对数目决定。

**代码实现**  
```cpp
#include <iostream>
#include <vector>
using namespace std;
#define int long long

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> bc_suffix(n + 2, 0);
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == 'B' && s[i + 1] == 'C') {
            bc_suffix[i] = 1 + bc_suffix[i + 2];
        } else {
            bc_suffix[i] = bc_suffix[i + 1];
        }
    }

    vector<pair<int, int>> a_segments;
    int current_length = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') {
            current_length++;
        } else {
            if (current_length > 0) {
                a_segments.push_back({i - 1, current_length});
                current_length = 0;
            }
        }
    }
    if (current_length > 0) {
        a_segments.push_back({n - 1, current_length});
    }

    int ans = 0;
    for (auto& seg : a_segments) {
        int end_pos = seg.first;
        int next_pos = end_pos + 1;
        if (next_pos < n) {
            ans += seg.second * bc_suffix[next_pos];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

### **同类型题或类似算法套路**

- **相似题目**  
  - **洛谷 P1090**（合并果子）：预处理后缀信息优化贪心策略。
  - **LeetCode 1358**（子串统计）：分段统计与后缀结合。
  - **Atcoder ABC189 D**（逻辑表达式优化）：动态预处理后缀状态。

---

### **推荐相似题目**

1. **洛谷 P1090**（合并果子，贪心与优先队列）
2. **LeetCode 76**（最小覆盖子串，滑动窗口与哈希预处理）
3. **Atcoder ABC190 E**（最短路径与状态压缩动态规划）

---

### **可视化与算法演示**

**动画方案**  
1. **颜色标记**  
   - 红色高亮当前处理的连续 A 段。
   - 绿色标记后续的 "BC" 对。
2. **步进控制**  
   - 展示预处理 `bc_suffix` 的过程，从右到左逐步填充数组。
   - 展示连续 A 段的统计与贡献计算。

**复古像素风格**  
- 使用 8 位像素风格绘制字符串字符，黄色表示 'A'，蓝色表示 'B'，绿色表示 'C'。
- 音效：每次统计 "BC" 对时播放短促音效，累计贡献时播放上扬音调。

---

**总结**  
通过预处理后缀和分段统计，高效解决动态替换次数问题，时间复杂度为 O(n)，适用于大规模数据。

---
处理用时：405.32秒