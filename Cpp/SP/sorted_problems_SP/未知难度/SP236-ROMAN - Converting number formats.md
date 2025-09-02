---
title: "ROMAN - Converting number formats"
layout: "post"
diff: 难度0
pid: SP236
tag: []
---

# ROMAN - Converting number formats

## 题目描述

给定多个测试用例的数量 $n$，我们需要将这 $n$ 个小于 $2^{32}$ 的正整数（每行一个数字）从一种格式转换为另一种格式。为了简化输入，$n$ 以与其他数字相同的格式给出。

## 输入格式

输入使用大写英文单词表示数字。因此，允许的输入值范围是从 ZERO（或 OH）到 FOUR TWO NINE FOUR NINE SIX SEVEN TWO NINE FIVE。

## 输出格式

对于每个测试用例，输出两行结果。输出使用“扩展”罗马数字形式（又称“篡改”罗马数字），其中在一些数字上方会有一条横线（具体格式见样例），表示该值乘以 1000，小写字母表示乘以 1000000。因此，可能的输出值范围从空字符串到 ivccxcivCMLXVIICCXCV，其中 iv 和 CMLXVII 上会有一条横线。注意：

- 如果数字对 1000000 取模的结果小于 4000，则用 M 表示 1000；
- 如果结果大于等于 4000，则用 I 表示 1000。因此，数字 3999 被表示为 MMMCMXCIX，而 4000 则在 IV 上有一条横线。类似规则也适用于 M 和 i 分别表示 1000000，以及 m 和 i 表示 1000000000。

**特别注意：此题对代码长度有较为严格的限制。**

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
THREE
FOUR OH
ONE NINE NINE NINE NINE NINE NINE NINE NINE NINE
ONE TWO THREE ZERO FOUR FIVE
```

### 输出

```
XL
       ______      
mcmxcixCMXCIXCMXCIX
___      
CXXMMMXLV
```

