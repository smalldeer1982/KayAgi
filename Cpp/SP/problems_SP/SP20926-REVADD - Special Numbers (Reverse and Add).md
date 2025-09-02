---
title: "REVADD - Special Numbers (Reverse and Add)"
layout: "post"
diff: 难度0
pid: SP20926
tag: []
---

# REVADD - Special Numbers (Reverse and Add)

## 题目描述

一个数 $ N $ 被称为「特殊数」，如果它可以表示为 $$ N = \mathrm{reverse}(N_1) + N_1 = \mathrm{reverse}(N_2) + N_2, $$ 其中 $ N_1 $ 和 $ N_2 $ 是正整数，并且它们的位数不同。

例如，$ 121 $ 是一个特殊数，因为可以表示为：
$$ \begin{aligned}
  121 &= \mathrm{reverse}(74) + 74 = \mathrm{reverse}(110) + 110 \\
      &= 47 + 74 = 11 + 110.
\end{aligned} $$

在小于 $ 10,000 $ 的范围内，只有两个这样的特殊数。

请找出按升序排列的前 5,000 个最小的特殊数，每行输出一个。

## 输出格式

依次输出前 5,000 个特殊数，每个数占一行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
None
```

### 输出

```
121
1111
...
[4998 lines]
...
```

