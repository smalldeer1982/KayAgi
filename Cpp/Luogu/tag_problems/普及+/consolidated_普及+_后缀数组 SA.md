---
title: "[USACO06DEC] Milk Patterns G"
layout: "post"
diff: 普及+/提高
pid: P2852
tag: ['2006', '二分', 'USACO', '哈希 hashing', '后缀数组 SA']
---
# [USACO06DEC] Milk Patterns G
## 题目描述

Farmer John has noticed that the quality of milk given by his cows varies from day to day. On further investigation, he discovered that although he can't predict the quality of milk from one day to the next, there are some regular patterns in the daily milk quality.

To perform a rigorous study, he has invented a complex classification scheme by which each milk sample is recorded as an integer between 0 and 1,000,000 inclusive, and has recorded data from a single cow over N (1 ≤ N ≤ 20,000) days. He wishes to find the longest pattern of samples which repeats identically at least K (2 ≤ K ≤ N) times. This may include overlapping patterns -- 1 2 3 2 3 2 3 1 repeats 2 3 2 3 twice, for example.

Help Farmer John by finding the longest repeating subsequence in the sequence of samples. It is guaranteed that at least one subsequence is repeated at least K times.

## 输入格式

Line 1: Two space-separated integers: N and K


Lines 2..N+1: N integers, one per line, the quality of the milk on day i appears on the ith line.

## 输出格式

Line 1: One integer, the length of the longest pattern which occurs at least K times

## 样例

### 样例输入 #1
```
8 2
1
2
3
2
3
2
3
1
```
### 样例输出 #1
```
4
```
## 题目翻译

农夫 John 发现他的奶牛产奶的质量一直在变动。经过细致的调查，他发现：虽然他不能预见明天产奶的质量，但连续的若干天的质量有很多重叠。我们称之为一个“模式”。 John 的牛奶按质量可以被赋予一个 $0$ 到 $1000000$ 之间的数。并且 John 记录了 $N$（$1 \le N \le 2 \times 10 ^ 4$）天的牛奶质量值。他想知道最长的出现了至少 $K$（$2 \le K \le N$）次的模式的长度。比如 `1 2 3 2 3 2 3 1` 中 `2 3 2 3` 出现了两次。当 $K = 2$ 时，这个长度为 $4$。


---

---
title: "[BJWC2010] 外星联络"
layout: "post"
diff: 普及+/提高
pid: P4341
tag: ['2010', '北京', '枚举', '后缀数组 SA']
---
# [BJWC2010] 外星联络
## 题目描述

小 P 在看过电影《超时空接触》(Contact)之后被深深的打动，决心致力于寻找外星人的事业。于是，他每天晚上都爬在屋顶上试图用自己的收音机收听外星人发来的信息。

虽然他收听到的仅仅是一些噪声，但是他还是按照这些噪声的高低电平将接收到的信号改写为由 `0` 和 `1` 构成的串， 并坚信外星人的信息就隐藏在其中。他认为，外星人发来的信息一定会在他接受到的 01 串中重复出现，所以他希望找到他接受到的 01 串中所有重复出现次数大于 $1$ 的子串。

但是他收到的信号串实在是太长了，于是，他希望你能编一个程序来帮助他。
## 输入格式

输入文件的第一行是一个整数$N$ ，代表小 P 接收到的信号串的长度。  
输入文件第二行包含一个长度为$N$ 的 01 串，代表小 P 接收到的信号串。
## 输出格式

输出文件的每一行包含一个出现次数大于$1$ 的子串所出现的次数。输出的顺序按对应的子串的字典序排列。
## 样例

### 样例输入 #1
```
7
1010101
```
### 样例输出 #1
```
3
3
2
2
4
3
3
2
2
```
## 提示

对于 100%的数据，满足 $0 \le N \le 3000$


---

---
title: "[POI 2000] 公共串"
layout: "post"
diff: 普及+/提高
pid: P5546
tag: ['2000', 'POI（波兰）', '字典树 Trie', '后缀数组 SA']
---
# [POI 2000] 公共串
## 题目描述

给出几个由小写字母构成的单词，求它们最长的公共子串的长度。

## 输入格式

文件的第一行是整数 $n$，$1\le n \le 5$，表示单词的数量。接下来$n$行每行一个单词，只由小写字母组成，单词的长度至少为$1$，最大为$2000$。
## 输出格式

仅一行，一个整数，最长公共子串的长度。
## 样例

### 样例输入 #1
```
3
abcb
bca
acbc
```
### 样例输出 #1
```
2
```


---

