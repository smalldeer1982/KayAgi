# 题目信息

# Crossword

## 题目描述

Vasya trains to compose crossword puzzles. He can only compose crosswords of a very simplе type so far. All of them consist of exactly six words; the words can be read only from top to bottom vertically and from the left to the right horizontally. The words are arranged in the form of a rectangular "eight" or infinity sign, not necessarily symmetrical.

The top-left corner of the crossword coincides with the top-left corner of the rectangle. The same thing is correct for the right-bottom corners. The crossword can't degrade, i.e. it always has exactly four blank areas, two of which are surrounded by letters. Look into the output for the samples for clarification.

Help Vasya — compose a crossword of the described type using the given six words. It is allowed to use the words in any order.

## 样例 #1

### 输入

```
NOD
BAA
YARD
AIRWAY
NEWTON
BURN
```

### 输出

```
BAA...
U.I...
R.R...
NEWTON
..A..O
..YARD
```

## 样例 #2

### 输入

```
AAA
AAA
AAAAA
AAA
AAA
AAAAA
```

### 输出

```
AAA..
A.A..
AAAAA
..A.A
..AAA
```

## 样例 #3

### 输入

```
PTC
JYNYFDSGI
ZGPPC
IXEJNDOP
JJFS
SSXXQOFGJUZ
```

### 输出

```
JJFS....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
IXEJNDOP
...U...T
...ZGPPC
```

# AI分析结果



### 题目内容整理

#### 题目描述
Vasya 正在练习编写简单的填字游戏。所有填字游戏由六个单词组成，以矩形 "8" 字形（或无限符号形状）排列。单词只能垂直从上到下或水平从左到右阅读。交叉点字符必须相同，且需输出字典序最小的解。

#### 样例
见原题样例（已翻译为中文）。

---

### 题解综合分析

#### 核心思路
1. **全排列枚举**：利用 `next_permutation` 生成所有可能的单词排列组合。
2. **条件验证**：对每个排列检查长度约束（如横向和纵向单词长度需满足特定关系）及交叉点字符一致性。
3. **字典序维护**：生成合法解后，按行按列比较字典序，保留最小的解。
4. **网格构造**：根据排列后的单词顺序，填充二维网格结构。

#### 解决难点
- **交叉点验证**：需检查 7 个关键交叉点的字符是否一致。
- **网格坐标映射**：将单词按规则填充到网格的对应行或列，需精确处理偏移量。
- **字典序优化**：需逐行逐字符比较所有可能解，确保最终输出最小字典序。

---

### 精选题解

#### 题解 1：作者 _lxy_（★★★★☆）
**关键亮点**：
- 使用 `next_permutation` 直接生成全排列，简化代码。
- 通过 `check` 函数集中验证所有交叉点条件，逻辑清晰。
- 利用 `vector<string>` 动态生成网格，便于字典序比较。

**核心代码片段**：
```cpp
do {
    int l1 = s[1].size(), l2 = s[2].size(), l3 = s[3].size();
    if (check(l1, l2, l3, ...)) {
        // 动态生成网格
        tmp = vector<string>(l5, string(l2, '.'));
        // 填充各单词到对应位置
        ...
        if (!flag || ans > tmp) ans = tmp;
    }
} while (next_permutation(s.begin()+1, s.begin()+7));
```

#### 题解 2：作者 CGDGAD（★★★★☆）
**关键亮点**：
- 明确划分横向和纵向单词的排列规则，长度条件验证简明。
- 使用 `vector<string>` 初始化网格，逐字符填充各单词。
- 利用 STL 的字典序比较特性直接优化解的选择。

**核心代码片段**：
```cpp
do {
    if (a[1].length() + a[3].length() - 1 == a[2].length() && ...) {
        // 检查交叉点字符
        if (a[1][0] == a[4][0] && ...) {
            // 绘制各单词到网格
            draw(res, 0, 0, 1, 0, a[1]); // 横向填充
            draw(res, 0, 0, 0, 1, a[4]); // 纵向填充
            ...
            if (best.empty() || res < best) best = res;
        }
    }
} while (next_permutation(a+1, a+7));
```

#### 题解 3：作者 封禁用户（★★★★☆）
**关键亮点**：
- 高度简化的代码结构，直接调用 `next_permutation` 并内联条件检查。
- 使用 `draw` 函数统一处理单词填充，减少冗余代码。
- 通过 `vector<string>` 直接比较字典序，逻辑紧凑。

**核心代码片段**：
```cpp
do {
    if (s[0].size() + s[2].size() == s[1].size() + 1 && ...) {
        // 内联条件检查与网格绘制
        vector<string> w(n, string(m, '.'));
        draw(w, 0, 0, 1, 0, s[0]);
        ...
        if (res.empty() || res > w) res = w;
    }
} while (next_permutation(s, s+6));
```

---

### 关键技巧总结
1. **全排列剪枝**：利用 `next_permutation` 按字典序生成排列，可提前剪枝部分无效解。
2. **条件集中验证**：将长度和交叉点检查封装为独立函数，提升可读性。
3. **网格动态构造**：使用嵌套循环或辅助函数（如 `draw`）填充网格，避免坐标计算错误。
4. **字典序优化**：直接比较 `vector<string>` 的字典序，无需手动逐字符比较。

---

### 拓展与练习
**相似题目推荐**：
1. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)  
   **标签**：全排列生成、基础枚举。
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)  
   **标签**：组合枚举、条件验证。
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)  
   **标签**：字符串拼接、交叉点处理。

**调试心得摘录**：
> "第 5 次提交因仅保证第一行字典序最小导致错误，需全网格逐行比较。"  
> —— 题解作者 Confringo 的踩坑经验，强调全局字典序比较的重要性。

---
处理用时：65.70秒