---
title: "AMSCO2 - Decipher the AMSCO cipher"
layout: "post"
diff: 难度0
pid: SP14435
tag: []
---

# AMSCO2 - Decipher the AMSCO cipher

## 题目描述

你需要解密一种叫做 AMSCO 密码的加密方法：

这种密码由 A.M.SCOtt 在 19 世纪发明，是一种不完整的列置换加密法，特点是交替使用单个字母和两个字母的组合。解密时，输入的第一个内容必须是两个字母的组合。无论是奇数周期还是偶数周期，第一列和第一行都会交替进行。

例如，下列排列为 7 4 5 6 3 2 1：

**RI** **D** **ER** **S** **ON** **T** **HE** **S** **TO** **R** **MI** **N** **TO** **T** **HI** **S** **HO** **U** **SE** **W** **EA** **R** **EB** **O** **RN** **J** **IM** **M** **OR** **R** **IS** **O** **N**

### 输入格式

输入包含最多 $N$ 行（$N < 1000$）。每行包括一个数字密钥（用于指示列的排列顺序）和一段密文。密文仅由大写字母 A-Z 组成，没有任何标点符号。密钥的最大长度为 9，密文的长度限制为 250。输入以 EOF 结束。

### 输出格式

输出应有 $N$ 行，每行是对应的明文，仅由大写字母 A-Z 组成，且没有空格。

### 示例

示例 1:

```
输入：
7456321 HETEAMTTOWIMONNSEJNDTOSEBRERRHOOISSMIURNORISHIROR
输出：
RIDERSONTHESTORMINTOTHISHOUSEWEAREBORNJIMMORRISON
```

示例 2:

```
输入：
41325 CECRTEGLENPHPLUTNANTEIOMOWIRSITDDSINTNALINESAALEMHATGLRGR
输出：
INCOMPLETECOLUMNARWITHALTERNATINGSINGLELETTERSANDDIGRAPHS
```

### 数据范围与提示

- $N < 1000$
- 密钥长度最大为 9
- 密文长度限制为 250

 **本翻译由 AI 自动生成**

