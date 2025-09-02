# 题目信息

# Genetic Engineering

## 题目描述

You will receive 3 points for solving this problem.

Manao is designing the genetic code for a new type of algae to efficiently produce fuel. Specifically, Manao is focusing on a stretch of DNA that encodes one protein. The stretch of DNA is represented by a string containing only the characters 'A', 'T', 'G' and 'C'.

Manao has determined that if the stretch of DNA contains a maximal sequence of consecutive identical nucleotides that is of even length, then the protein will be nonfunctional. For example, consider a protein described by DNA string "GTTAAAG". It contains four maximal sequences of consecutive identical nucleotides: "G", "TT", "AAA", and "G". The protein is nonfunctional because sequence "TT" has even length.

Manao is trying to obtain a functional protein from the protein he currently has. Manao can insert additional nucleotides into the DNA stretch. Each additional nucleotide is a character from the set {'A', 'T', 'G', 'C'}. Manao wants to determine the minimum number of insertions necessary to make the DNA encode a functional protein.

## 说明/提示

In the first example, it is sufficient to insert a single nucleotide of any type between the two 'T's in the sequence to restore the functionality of the protein.

## 样例 #1

### 输入

```
GTTAAAG
```

### 输出

```
1
```

## 样例 #2

### 输入

```
AACCAACCAAAAC
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 基因工程

## 题目描述
解决本题你将获得3分。

马瑙正在为一种新型藻类设计遗传密码，以高效生产燃料。具体来说，马瑙专注于一段编码一种蛋白质的DNA。这段DNA由一个仅包含字符'A'、'T'、'G'和'C'的字符串表示。

马瑙已经确定，如果这段DNA包含一段长度为偶数的连续相同核苷酸的最大序列，那么该蛋白质将无法发挥功能。例如，考虑由DNA字符串“GTTAAAG”描述的蛋白质。它包含四个连续相同核苷酸的最大序列：“G”、“TT”、“AAA”和“G”。该蛋白质无法发挥功能，因为序列“TT”的长度为偶数。

马瑙试图从他目前拥有的蛋白质中获得一种有功能的蛋白质。马瑙可以在DNA片段中插入额外的核苷酸。每个额外的核苷酸是集合 {'A', 'T', 'G', 'C'} 中的一个字符。马瑙想确定使DNA编码出有功能蛋白质所需插入的最少核苷酸数量。

## 说明/提示
在第一个示例中，在序列中的两个'T'之间插入任意类型的单个核苷酸就足以恢复蛋白质的功能。

## 样例 #1
### 输入
```
GTTAAAG
```
### 输出
```
1
```

## 样例 #2
### 输入
```
AACCAACCAAAAC
```
### 输出
```
5
```

### 算法分类
字符串

### 题解综合分析与结论
这些题解思路基本一致，均是通过遍历字符串，统计连续相同字符的长度，若长度为偶数则增加计数器。算法要点在于利用循环遍历字符串，同时用一个变量记录连续相同字符的个数，遇到不同字符时判断该个数是否为偶数。解决难点在于正确处理连续相同字符的计数以及边界情况。整体来看，各题解质量相近，思路较为直接，代码实现也相对简单，多数题解在思路清晰度和代码可读性上表现一般，没有特别突出的优化。

### 通用建议与扩展思路
建议在代码实现时增加注释，提高代码可读性。对于类似题目，可以进一步拓展到处理更复杂的字符串模式匹配问题，或结合其他数据结构如哈希表来优化查找效率。

### 相似知识点洛谷题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1914 小书童——密码](https://www.luogu.com.cn/problem/P1914)
- [P2038 无线网络发射器选址](https://www.luogu.com.cn/problem/P2038) 

---
处理用时：21.64秒