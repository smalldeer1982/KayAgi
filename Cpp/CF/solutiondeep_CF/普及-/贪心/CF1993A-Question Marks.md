# 题目信息

# Question Marks

## 题目描述

Tim 正在做一个包含 $4n$ 道题目的测试，每道题目的答案仅为 `A`、`B`、`C`、`D` 四个选项中的一个，且每道题目的正确答案是均匀分配的——也就是说，`A`、`B`、`C`、`D` 四个选项分别为其中 $n$ 道题目的正确答案。

现在，对于每道题目，Tim 已经将自己的答案填到了答题卡上。我们将其视作一个长度为 $4n$ 的字符串 $s$，字符串里面的每个字符仅有可能是 `A`、`B`、`C`、`D`、`?` 五个字符当中的一个，其中第 $i$ 个字符 $s_i$ 如果是 `?`，则表示 Tim 并不确定第 $i$ 个问题的答案，否则即表示 Tim 给出的第 $i$ 个问题的答案。

现在给出 Tim 的答案，求 Tim 最多能够答对多少道题目。

## 说明/提示

对于所有数据：

- $1\leqslant T\leqslant 1000$。
- $1\leqslant n\leqslant 100$。
- $s_i\in\{\texttt{A,B,C,D,?}\}$。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
6
1
ABCD
2
AAAAAAAA
2
AAAABBBB
2
????????
3
ABCABCABCABC
5
ACADC??ACAC?DCAABC?C```

### 输出

```
4
2
4
0
9
13```

# AI分析结果



# Question Marks

## 题目描述

Tim 正在参加一个包含 $4n$ 道题目的测试，每道题目的正确答案均匀分布在 `A`、`B`、`C`、`D` 四个选项中（每个选项恰好出现 $n$ 次）。Tim 的答题卡由字符串 $s$ 表示，其中 `?` 表示未确定的答案。求 Tim 最多能答对多少题。

## 样例输入输出

### 输入样例
```
6
1
ABCD
2
AAAAAAAA
2
AAAABBBB
2
????????
3
ABCABCABCABC
5
ACADC??ACAC?DCAABC?C
```

### 输出样例
```
4
2
4
0
9
13
```

---

### 核心思路与算法分析

#### 关键模型
题目核心在于将得分拆分为两部分：
1. **确定字符的匹配数**：统计每个字母已确定的答案中最多能正确匹配的数量之和。
2. **问号的最大贡献**：问号替换后能匹配的数量受限于剩余可分配的正确答案位置。

#### 数学公式
总得分 = Σ min(已确定字母数, n) + min(问号数, 剩余正确位置数)  
其中，剩余正确位置数 = 4n - Σ min(已确定字母数, n)

#### 解决难点
- 正确理解题目中正确答案的均匀分布特性
- 将问题拆解为确定部分和问号部分的贡献
- 发现问号的贡献受剩余正确位置数限制

#### 算法实现
1. 统计各字母出现次数和问号数
2. 计算确定部分的匹配数之和
3. 计算剩余可分配的正确位置数
4. 问号贡献取两者的较小值

---

### 题解代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        
        int cnt[4] = {0}, q = 0;
        for (char c : s) {
            if (c == 'A') cnt[0]++;
            else if (c == 'B') cnt[1]++;
            else if (c == 'C') cnt[2]++;
            else if (c == 'D') cnt[3]++;
            else q++;
        }
        
        int correct = 0;
        for (int i = 0; i < 4; i++)
            correct += min(cnt[i], n);
        
        int remaining = 4 * n - correct;
        correct += min(q, remaining);
        cout << correct << endl;
    }
    return 0;
}
```

---

### 举一反三

1. **P1603**（字符串处理与计数）
2. **P1179**（统计与优化分配）
3. **P2550**（概率与期望中的资源分配）

---
处理用时：356.29秒