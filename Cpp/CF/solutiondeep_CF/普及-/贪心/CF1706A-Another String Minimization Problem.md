# 题目信息

# Another String Minimization Problem

## 题目描述

You have a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers between $ 1 $ and $ m $ . You also have a string $ s $ , consisting of $ m $ characters B.

You are going to perform the following $ n $ operations.

- At the $ i $ -th ( $ 1 \le i \le n $ ) operation, you replace either the $ a_i $ -th or the $ (m + 1 - a_i) $ -th character of $ s $ with A. You can replace the character at any position multiple times through the operations.

Find the lexicographically smallest string you can get after these operations.

A string $ x $ is lexicographically smaller than a string $ y $ of the same length if and only if in the first position where $ x $ and $ y $ differ, the string $ x $ has a letter that appears earlier in the alphabet than the corresponding letter in $ y $ .

## 说明/提示

In the first test case, the sequence $ a = [1, 1, 3, 1] $ . One of the possible solutions is the following.

- At the $ 1 $ -st operation, you can replace the $ 1 $ -st character of $ s $ with A. After it, $ s $ becomes ABBBB.
- At the $ 2 $ -nd operation, you can replace the $ 5 $ -th character of $ s $ with A (since $ m+1-a_2=5 $ ). After it, $ s $ becomes ABBBA.
- At the $ 3 $ -rd operation, you can replace the $ 3 $ -rd character of $ s $ with A. After it, $ s $ becomes ABABA.
- At the $ 4 $ -th operation, you can replace the $ 1 $ -st character of $ s $ with A. After it, $ s $ remains equal to ABABA.

 The resulting string is ABABA. It is impossible to produce a lexicographically smaller string.In the second test case, you are going to perform only one operation. You can replace either the $ 2 $ -nd character or $ 4 $ -th character of $ s $ with A. You can get strings BABBB and BBBAB after the operation. The string BABBB is the lexicographically smallest among these strings.

In the third test case, the only string you can get is A.

In the fourth test case, you can replace the $ 1 $ -st and $ 2 $ -nd characters of $ s $ with A to get AABB.

In the fifth test case, you can replace the $ 1 $ -st and $ 3 $ -rd characters of $ s $ with A to get ABABBBB.

## 样例 #1

### 输入

```
6
4 5
1 1 3 1
1 5
2
4 1
1 1 1 1
2 4
1 3
2 7
7 5
4 5
5 5 3 5```

### 输出

```
ABABA
BABBB
A
AABB
ABABBBB
ABABA```

# AI分析结果



# Another String Minimization Problem 的题目翻译

## 题目描述

给定一个长度为 $n$ 的序列 $a_1, a_2, \ldots, a_n$，其中每个元素的值在 $1$ 到 $m$ 之间。另有一个长度为 $m$ 的字符串 $s$，初始全为字符 `B`。你需要进行 $n$ 次操作：

- 在第 $i$ 次操作中（$1 \le i \le n$），选择将 $s$ 的第 $a_i$ 位或第 $(m + 1 - a_i)$ 位替换为 `A`。每个位置可以被多次替换。

目标是找到操作后字典序最小的字符串。  
**字典序更小**的定义：两个字符串第一个不同的位置中，字符较小的字符串更小（`A` 的字典序比 `B` 小）。

## 样例与说明

输入样例中的操作示例展示了如何通过贪心策略选择更靠前的位置来构造最小字典序的字符串。

---

## 题解分析与结论

### 核心思路
所有题解均采用**贪心策略**：对于每个 $a_i$，优先选择其对应两个位置（$a_i$ 和 $m+1-a_i$）中更小的那个。若该位置已被设为 `A`，则选择较大的位置。此策略确保前面的字符尽可能变为 `A`，从而最小化字典序。

### 算法要点
1. **位置选择**：对每个 $a_i$，计算 $\min(a_i, m+1-a_i)$ 作为优先修改的位置。
2. **状态检查**：若优先位置未被修改，则设置为 `A`；否则修改另一位置。
3. **贪心正确性**：字典序的特性决定了前面的字符影响更大，优先处理更小位置能保证全局最优。

### 最优代码实现
以下是评分较高的题解代码实现：

#### 题解作者：ExplodingKonjac（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：代码简洁，直接处理索引转换，逻辑清晰。
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, a[105];
string s;

int main() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        s = string(m, 'B'); // 初始化全B
        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            x--; // 转换为0-based索引
            int pos = min(x, m - 1 - x); // 计算较小位置
            if (s[pos] == 'B') s[pos] = 'A';
            else s[m - 1 - pos] = 'A'; // 修改另一位置
        }
        cout << s << endl;
    }
    return 0;
}
```

#### 题解作者：xzy090626（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：使用 `min` 和 `max` 明确位置选择，可读性强。
```cpp
#include <bits/stdc++.h>
using namespace std;
bool s[55];

void solve() {
    memset(s, 0, sizeof(s));
    int n, m; cin >> n >> m;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        int t1 = min(a, m + 1 - a), t2 = max(a, m + 1 - a);
        if (!s[t1]) s[t1] = true; // 优先选较小位置
        else s[t2] = true;       // 否则选较大位置
    }
    for (int i = 1; i <= m; i++)
        cout << (s[i] ? 'A' : 'B');
    cout << endl;
}
```

---

## 总结与拓展
### 关键技巧
- **贪心构造**：字典序问题常通过局部最优（优先处理更小位置）实现全局最优。
- **索引处理**：注意输入是1-based还是0-based，避免索引错误。

### 类似题目推荐
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：贪心删除字符使剩余数最小。
2. [P5659 字符串游戏](https://www.luogu.com.cn/problem/P5659)：通过操作构造最小字典序字符串。
3. [CF 1321C Remove Adjacent](https://codeforces.com/problemset/problem/1321/C)：贪心删除相邻字符。

### 个人心得摘录
- **索引转换**：在代码中明确处理1-based到0-based的转换，避免混淆（如ExplodingKonjac的题解）。
- **简化条件**：直接使用 `min` 和 `max` 替代复杂判断（如xzy090626的题解）。

---
处理用时：153.77秒