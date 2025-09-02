# 题目信息

# [NWRRC 2017] Consonant Fencity

## 题目描述



There are two kinds of sounds in spoken languages: vowels and consonants. Vowel is a sound, produced with an open vocal tract; and consonant is pronounced in such a way that the breath is at least partly obstructed. For example, letters a and $o$ are used to express vowel sounds, while letters $b$ and $p$ are the consonants (e.g . bad, pot).

a vowel (e.g . silly) or as a consonant (e.g . yellow). The letter $w$ , usually used as a consonant (e.g . wet) could produce a vowel after another vowel (e.g . growth) in English, and in some languages (e.g . Welsh) it could be even the only vowel in a word.

In this task, we consider $y$ and $w$ as vowels, so there are seven vowels in English alphabet: a , $e , i , o , u , w$ and $y$ , all other letters are consonants.

Let's define the consonant fencity of a string as the number of pairs of consecutive letters in the string which both are consonants and have different cases (lowercase letter followed by uppercase or vice versa). For example, the consonant fencity of a string CoNsoNaNts is $2$ , the consonant fencity of a string dEsTrUcTiOn is $3$ and the consonant fencity of string StRenGtH is $5$ .

You will be given a string consisting of lowercase English letters. Your task is to change the case of some letters in such a way that all equal letters will be of the same case (that means, no letter can occur in resulting string as both lowercase and uppercase), and the consonant fencity of resulting string is maximal.



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
consonants
```

### 输出

```
CoNsoNaNts
```

## 样例 #2

### 输入

```
destruction
```

### 输出

```
dEsTrUcTiOn
```

## 样例 #3

### 输入

```
strength
```

### 输出

```
StRenGtH
```

# AI分析结果

### 算法分类
图论

### 综合分析与结论
题目要求通过改变字符串中辅音字母的大小写，使得相邻辅音字母大小写不同的对数最大化。题解中，多位作者将问题转化为图论问题，通过构建图并枚举所有可能的染色方案来求解最大权二分图。这种思路的核心是将辅音字母视为图中的节点，相邻辅音字母的出现次数作为边的权重，然后通过枚举所有可能的染色方案（即大小写状态）来找到最大权值的二分图。

### 所选题解

#### 题解1：作者：JoshAlMan
- **星级**：4星
- **关键亮点**：将问题转化为图论问题，提出最大权生成二分图的概念，并指出可以通过暴力枚举或递推来求解。思路清晰，逻辑严谨。
- **核心代码**：
  ```cpp
  // 伪代码：枚举所有可能的染色方案
  for (int i = 0; i < (1 << n); ++i) {
      int sum = 0;
      for (int j = 0; j < n; ++j) {
          if ((1 << j) & i) {
              for (int k = 0; k < n; ++k) {
                  if (!((1 << k) & i)) {
                      sum += w[j][k];
                  }
              }
          }
      }
      if (sum > max_sum) {
          max_sum = sum;
          best_state = i;
      }
  }
  ```
- **核心思想**：通过二进制枚举所有可能的染色方案，计算每种方案的权值，保留最大权值的方案。

#### 题解2：作者：XIxii
- **星级**：4星
- **关键亮点**：详细解释了如何预处理相邻辅音字母的出现次数，并通过二进制枚举所有可能的大小写状态来计算最大权值。代码实现较为完整，逻辑清晰。
- **核心代码**：
  ```cpp
  for (int i = 0; i < (1 << pos); ++i) {
      int sum = 0;
      memset(vis, 0, sizeof(vis));
      for (int j = 0; j < pos; ++j) {
          if ((1 << j) & i) {
              for (int k = 'a'; k <= 'z'; ++k) {
                  if (vis[k]) {
                      sum -= w[k][que[j]];
                      sum -= w[que[j]][k];
                  } else {
                      sum += w[k][que[j]];
                      sum += w[que[j]][k];
                  }
              }
              vis[que[j]] = 1;
          }
      }
      if (ans < sum) {
          ans = sum;
          flag = i;
      }
  }
  ```
- **核心思想**：通过二进制枚举所有可能的大小写状态，计算每种状态的权值，保留最大权值的状态。

#### 题解3：作者：ybc2025chenyuyang
- **星级**：4星
- **关键亮点**：将辅音字母的状态压缩，通过枚举所有可能的染色方案来计算最大权值。代码实现简洁，逻辑清晰。
- **核心代码**：
  ```cpp
  for (t = 0; t < (1 << 19); t++) {
      ll sum = 0;
      for (i = 'a'; i <= 'z'; i++) {
          if (vis_1[i]) continue;
          int x = vis_2[i];
          for (j = 'a'; j <= 'z'; j++) {
              if (vis_1[j]) continue;
              int y = vis_2[j];
              if (((t >> x) & 1) != ((t >> y) & 1)) {
                  sum += a[i][j];
              }
          }
      }
      if (sum > maxx) {
          maxx = sum;
          flag = t;
      }
  }
  ```
- **核心思想**：通过二进制枚举所有可能的染色方案，计算每种方案的权值，保留最大权值的方案。

### 最优关键思路或技巧
1. **图论转化**：将辅音字母视为图中的节点，相邻辅音字母的出现次数作为边的权重，问题转化为求最大权二分图。
2. **二进制枚举**：通过二进制枚举所有可能的染色方案（即大小写状态），计算每种方案的权值，保留最大权值的方案。
3. **状态压缩**：由于辅音字母数量较少（19个），可以使用状态压缩来高效枚举所有可能的染色方案。

### 可拓展之处
类似的问题可以通过图论和状态压缩的思路来解决，特别是在处理组合优化问题时，枚举所有可能的状态并计算每种状态的权值是一种常见的解题思路。

### 推荐题目
1. [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
2. [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)
3. [P1879 [USACO06NOV] Corn Fields G](https://www.luogu.com.cn/problem/P1879)

### 个人心得摘录
- **调试经历**：在枚举染色方案时，需要注意边界条件和状态转移的正确性，避免重复计算或遗漏某些状态。
- **踩坑教训**：在处理字符大小写转换时，要确保所有相同字母的大小写状态一致，避免出现同一个字母既有大写又有小写的情况。
- **顿悟感想**：将问题转化为图论问题后，思路更加清晰，解题效率也大大提高。

---
处理用时：29.52秒