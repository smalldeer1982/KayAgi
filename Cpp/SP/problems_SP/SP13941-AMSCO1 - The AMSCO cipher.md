---
title: "AMSCO1 - The AMSCO cipher"
layout: "post"
diff: 难度0
pid: SP13941
tag: []
---

# AMSCO1 - The AMSCO cipher

## 题目描述

这是由 19 世纪的 A.M.SCOtt 提出的一种不完整的列换位密码。该密码通过单字母和双字母交替出现进行加密，且必须以双字母开头。不论是奇数周期还是偶数周期，首列和首行的排列总是交替的。

**4** **1** **3** **2** **5** **IN** **C** **OM** **P** **LE** **T** **EC** **O** **LU** **M** **NA** **R** **WI** **T** **HA** **L** **TE** **R** **NA** **T** **IN** **G** **SI** **N** **GL** **E** **LE** **T** **TE** **R** **SA** **N** **DD** **I** **GR** **A** **PH** **S**

### 输入格式

输入包括 $N$ 行（$N < 1000$）。每行中包含一个数字密钥（用于指定列的排列顺序）和一段明文。明文中只包含大写字母（\[A-Z\]），且不包含标点符号。密钥长度最多为 9，明文长度上限为 250。输入的最后一行以 EOF 结束。

### 输出格式

输出需包括恰好 $N$ 行密文，其中每个密文行只包含大写字母 \[A-Z\]，不含空格。

### 示例

```
输入：

41325 INCOMPLETECOLUMNARWITHALTERNATINGSINGLELETTERSANDDIGRAPHS

输出：

CECRTEGLENPHPLUTNANTEIOMOWIRSITDDSINTNALINESAALEMHATGLRGR
```

 **本翻译由 AI 自动生成**

