---
title: "FINGP - Fingerprints"
layout: "post"
diff: 难度0
pid: SP23861
tag: []
---

# FINGP - Fingerprints

## 题目描述

教授 Emad Eldin 是模式识别领域的一位专家，他要求学生编写一个程序，检查某个特定模式是否出现在某个人的指纹中。

## 输入格式

第一行输入一个特殊模式字符串 $S$，长度为 $1$ 到 $100$。紧接着的第二行是一个整数 $N$，表示有多少个指纹（1 到 100 个）。接下来的 $N$ 行，每行是一个指纹字符串 $F_i$，其长度同样为 $1$ 到 $100$。

## 输出格式

输出一个整数 $K$，表示有多少个指纹包含该特殊模式字符串。随后输出这 $K$ 行，每行列出一个包含该模式的指纹，并按照字典序排列。如果没有指纹包含该模式，则输出 `Wrong fingerprints!`。

### 示例

```
输入：
On
5
Pattern recognatiOn
CommOn patterN
game
organizatiOn
lion
输出：
2
Pattern recognatiOn
organizatiOn
```

```
输入：
Ze
2
Fingerprint
pattern design
输出：
Wrong fingerprints!
```

### 说明

- 字符串 $S$ 仅由大小写英文字母组成。
- 其他输入字符串包含大小写英文字母以及空格。
- 比较均区分大小写（例如，'A' 与 'a' 不同）。
- 字典序比较：如果在某个位置 $s_i \neq t_i$，就比较那个位置上的字符；若没有这样的差异（即一个是另一个的前缀），则较短者更小。

 **本翻译由 AI 自动生成**

