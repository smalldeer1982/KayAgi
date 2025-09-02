# 题目信息

# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec
```

### 输出

```
4
3 5 4 5 
```

## 样例 #2

### 输入

```
4
abcd
accd
```

### 输出

```
-1
```

# AI分析结果



### 题解分析与结论

#### **核心思路与算法要点**
- **无解判定**：所有题解均通过统计字符频率确保两字符串字母构成相同，否则直接输出-1。
- **贪心策略**：采用“逐位修正”策略。从前往后处理每个字符，当 `s[i] != t[i]` 时，在 `s` 后面的位置找到第一个与 `t[i]` 相同的字符，通过相邻交换将其移动到 `i` 的位置。
- **实现方式**：大多数题解使用双重循环，外层遍历 `t` 的每个字符，内层在 `s` 中查找并交换。

#### **解决难点**
- **交换顺序的选择**：必须保证后续字符调整不会破坏已对齐的前缀。如选择从后往前交换（类似插入排序）可避免破坏已处理部分。
- **时间复杂度控制**：虽然 `n ≤ 50`，但需确保步骤不超过 1e4。直接模拟交换的贪心法交换次数为 `O(n²)`，满足要求。

---

### 题解评分（≥4星）

1. **作者：SUNCHAOYI（4.5星）**
   - **亮点**：通过构造映射数组将问题转化为冒泡排序，思路清晰，代码结构完整。
   - **不足**：冒泡排序步骤较多，实际交换次数可能高于直接贪心法。

2. **作者：Hutao__（4.2星）**
   - **亮点**：直接模拟交换过程，代码简洁，步骤直观，交换次数较少。
   - **不足**：变量命名与注释可优化，如 `f` 改为 `found`。

3. **作者：chatoudp（4.0星）**
   - **亮点**：代码简洁高效，注释清晰，逻辑直接。
   - **不足**：缺少部分边界情况说明。

---

### 最优思路提炼
**贪心策略**：
1. **逐位修正**：从左到右处理每个位置 `i`，若 `s[i] != t[i]`，在 `s` 中 `i` 之后找到第一个等于 `t[i]` 的字符 `s[j]`。
2. **相邻交换**：将 `s[j]` 通过 `j-i` 次相邻交换移动到位置 `i`，记录每次交换的位置。

**正确性保证**：每次处理仅影响未处理的后缀，保证已处理前缀与 `t` 一致。

---

### 类似题目推荐
1. **P1106 删数问题**（贪心选择最小序列）
2. **P1230 智力大冲浪**（贪心+区间排序）
3. **P1090 合并果子**（贪心+优先队列）

---

### 可视化算法演示
**贪心过程动画设计**：
- **8位像素风格**：字符显示为彩色方块，交换时方块滑动，伴随“哔”音效。
- **高亮当前操作**：目标位置 `i` 高亮红色，移动的字符高亮绿色。
- **步进控制**：允许单步执行，显示当前交换步骤和总步数。
- **自动模式**：AI自动执行交换，背景音乐为复古芯片音乐。

**关键代码（JS伪代码）**：
```javascript
function animateSwap(s, t) {
  let steps = [];
  for (let i = 0; i < s.length; i++) {
    if (s[i] === t[i]) continue;
    let j = i + 1;
    while (j < s.length && s[j] !== t[i]) j++;
    for (let k = j; k > i; k--) {
      steps.push(k);
      swap(s, k, k-1); // 触发动画效果
    }
  }
  return steps;
}
```

---

### 题解代码示例（Hutao__ 改进版）
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    string s, t;
    cin >> n >> s >> t;
    vector<int> ans;
    
    // 检查字符频率
    int cnt[26] = {0};
    for (char c : s) cnt[c-'a']++;
    for (char c : t) if (--cnt[c-'a'] < 0) { cout << -1; return 0; }
    
    // 贪心交换
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        int pos = i + 1;
        while (pos < n && s[pos] != t[i]) pos++;
        for (int j = pos; j > i; j--) {
            ans.push_back(j);
            swap(s[j-1], s[j]);
        }
    }
    
    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
    return 0;
}
```

**核心逻辑**：逐位修正，确保每次交换不影响已处理的前缀部分，时间复杂度 O(n²)。

---
处理用时：64.08秒