# 题目信息

# Correcting Mistakes

## 题目描述

Analyzing the mistakes people make while typing search queries is a complex and an interesting work. As there is no guaranteed way to determine what the user originally meant by typing some query, we have to use different sorts of heuristics.

Polycarp needed to write a code that could, given two words, check whether they could have been obtained from the same word as a result of typos. Polycarpus suggested that the most common typo is skipping exactly one letter as you type a word.

Implement a program that can, given two distinct words $ S $ and $ T $ of the same length $ n $ determine how many words $ W $ of length $ n+1 $ are there with such property that you can transform $ W $ into both $ S $ , and $ T $ by deleting exactly one character. Words $ S $ and $ T $ consist of lowercase English letters. Word $ W $ also should consist of lowercase English letters.

## 说明/提示

In the first sample test the two given words could be obtained only from word "treading" (the deleted letters are marked in bold).

In the second sample test the two given words couldn't be obtained from the same word by removing one letter.

In the third sample test the two given words could be obtained from either word "tory" or word "troy".

## 样例 #1

### 输入

```
7
reading
trading
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
sweet
sheep
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
toy
try
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 纠正错误

## 题目描述
分析人们在输入搜索查询时所犯的错误是一项复杂且有趣的工作。由于没有确定的方法来判定用户输入某个查询时原本的意图，我们必须使用不同类型的启发式方法。

波利卡普需要编写一段代码，该代码能够在给定两个单词的情况下，检查它们是否可能是由于输入错误而从同一个单词得到的。波利卡普认为最常见的输入错误是在输入单词时恰好跳过一个字母。

实现一个程序，该程序在给定两个长度均为 $n$ 的不同单词 $S$ 和 $T$ 时，能够确定存在多少个长度为 $n + 1$ 的单词 $W$ 具有这样的特性：通过恰好删除一个字符，你可以将 $W$ 转换为 $S$ 和 $T$。单词 $S$ 和 $T$ 由小写英文字母组成。单词 $W$ 也应由小写英文字母组成。

## 说明/提示
在第一个样例测试中，这两个给定的单词只能从单词 “treading” 得到（删除的字母用粗体标记）。

在第二个样例测试中，这两个给定的单词无法通过从同一个单词中删除一个字母得到。

在第三个样例测试中，这两个给定的单词可以从单词 “tory” 或单词 “troy” 得到。

## 样例 #1
### 输入
```
7
reading
trading
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
sweet
sheep
```
### 输出
```
0
```

## 样例 #3
### 输入
```
3
toy
try
```
### 输出
```
2
```

### 算法分类
字符串

### 综合分析与结论
这几道题解的核心思路都是通过分析两个给定字符串不同之处，来判断能构造出满足条件的原字符串的数量。关键在于找到字符串中不同字符的区间，并判断在该区间内字符的对应关系能否构造出原字符串。题解们都意识到答案最多为2种的特性，且都通过线性遍历的方式来处理字符串，时间复杂度均为O(n)。不同之处在于具体判断的细节和代码实现方式。

### 所选的题解
- **作者：CarrotMeow (5星)**
    - **关键亮点**：思路清晰，通过正难则反的思维，将问题转化为在两个字符串中添加字符使其相等，明确指出找到不同字符的最长区间后，根据区间内字符对应关系判断能否构造出原字符串，逻辑简洁明了。
    - **核心代码实现思想**：找出 `s` 和 `t` 中不同字符的最长区间 `[l, r]`，检查区间内是否存在 `s_i!= t_{i + 1}` 或 `s_{i + 1}!= t_i` 的情况，若存在则无法构造出原字符串。
```cpp
// 伪代码示意
// 找出区间 [l, r] 并判断能否构造出 w
for (int i = 0; i < n; ++i) {
    if (s[i]!= t[i]) {
        l = min(l, i);
        r = max(r, i);
    }
}
bool canConstruct1 = true, canConstruct2 = true;
for (int i = l + 1; i <= r; ++i) {
    if (s[i]!= t[i - 1]) canConstruct1 = false;
    if (s[i - 1]!= t[i]) canConstruct2 = false;
}
int result = canConstruct1 + canConstruct2;
```
- **作者：skyskyCCC (4星)**
    - **关键亮点**：先对题意进行清晰的转换，以删除两端相同子串，只保留有区别部分的方式来思考问题，通过具体例子详细阐述了添加字符匹配的两种可能情况，便于理解。
    - **核心代码实现思想**：先找到两个字符串不同字符的区间 `[l, r]`，然后检查区间内字符是否满足两种添加字符匹配的条件，统计满足条件的情况数。
```cpp
// 伪代码示意
// 找不同的区间
for (int i = 0; i < n; i++) {
    if (s1[i]!= s2[i]) {
        l = min(l, i);
        r = max(r, i);
    }
}
int ans1 = 1, ans2 = 1;
// 判断两种添加字符匹配的条件
for (int i = l + 1; i <= r; i++) {
    if (s1[i]!= s2[i - 1]) ans1 = 0;
    if (s1[i - 1]!= s2[i]) ans2 = 0;
}
int result = ans1 + ans2;
```
- **作者：Rt__ (4星)**
    - **关键亮点**：通过将原字符串及两个目标字符串进行抽象表示，清晰地展示了字符删除与原字符串构造的关系，根据不同字符区间的子串匹配情况来确定答案，代码实现简洁明了。
    - **核心代码实现思想**：找到两个字符串最左边和最右边不同字符的位置 `fr` 和 `ba`，然后检查两种子串匹配情况，统计满足条件的情况数。
```cpp
// 伪代码示意
// 找最左边和最右边不同字符的位置
for (fr = 1; fr <= n; fr++) {
    if (s1[fr]!= s2[fr]) break;
}
for (ba = n; ba >= 1; ba--) {
    if (s1[ba]!= s2[ba]) break;
}
int ans = 0;
// 检查两种子串匹配情况
if (s1.substr(fr + 1, ba - fr) == s2.substr(fr, ba - fr)) {
    ans++;
}
if (s1.substr(fr, ba - fr) == s2.substr(fr + 1, ba - fr)) {
    ans++;
}
```

### 最优关键思路或技巧
1. **转换思维**：将从原字符串删除字符得到两个字符串的问题，转换为向两个字符串添加字符使其相等的问题，简化思考过程。
2. **确定关键区间**：找到两个字符串中不同字符的区间，重点分析该区间内字符的对应关系，从而判断能否构造出原字符串。

### 拓展
同类型题目通常围绕字符串的编辑距离展开，例如给定字符串的插入、删除、替换操作，求最少操作次数使两个字符串相等。类似算法套路是关注字符串差异部分，通过分析差异的位置和特征来解决问题。

### 洛谷题目推荐
1. **P1025 数的划分**：涉及整数划分问题，可类比通过分析不同划分情况来解决，与本题分析字符串不同情况类似。
2. **P1106 删数问题**：同样是对字符串（数字串）进行删除操作，通过分析删除位置对结果的影响来求解，和本题思路有相似性。
3. **P1308 统计单词数**：处理字符串匹配相关问题，需要分析字符串中单词的特征，和本题分析字符串特征的思路类似。 

---
处理用时：60.62秒