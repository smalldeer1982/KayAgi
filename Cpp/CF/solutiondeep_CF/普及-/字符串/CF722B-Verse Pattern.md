# 题目信息

# Verse Pattern

## 题目描述

You are given a text consisting of $ n $ lines. Each line contains some space-separated words, consisting of lowercase English letters.

We define a syllable as a string that contains exactly one vowel and any arbitrary number (possibly none) of consonants. In English alphabet following letters are considered to be vowels: 'a', 'e', 'i', 'o', 'u' and 'y'.

Each word of the text that contains at least one vowel can be divided into syllables. Each character should be a part of exactly one syllable. For example, the word "mamma" can be divided into syllables as "ma" and "mma", "mam" and "ma", and "mamm" and "a". Words that consist of only consonants should be ignored.

The verse patterns for the given text is a sequence of $ n $ integers $ p_{1},p_{2},...,p_{n} $ . Text matches the given verse pattern if for each $ i $ from $ 1 $ to $ n $ one can divide words of the $ i $ -th line in syllables in such a way that the total number of syllables is equal to $ p_{i} $ .

You are given the text and the verse pattern. Check, if the given text matches the given verse pattern.

## 说明/提示

In the first sample, one can split words into syllables in the following way:

`in-tel<br></br>co-de<br></br>ch al-len-ge<br></br>`Since the word "ch" in the third line doesn't contain vowels, we can ignore it. As the result we get $ 2 $ syllabels in first two lines and $ 3 $ syllables in the third one.

## 样例 #1

### 输入

```
3
2 2 3
intel
code
ch allenge
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1 2 3 1
a
bcdefghi
jklmnopqrstu
vwxyz
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
13 11 15 15
to be or not to be that is the question
whether tis nobler in the mind to suffer
the slings and arrows of outrageous fortune
or to take arms against a sea of troubles
```

### 输出

```
YES
```

# AI分析结果

### 题目重写

#### 题目描述

给定一个由 $n$ 行组成的文本。每行包含一些由空格分隔的单词，单词由小写英文字母组成。

我们定义一个音节为一个包含恰好一个元音字母和任意数量（可能为零）的辅音字母的字符串。在英文字母表中，以下字母被视为元音字母：'a', 'e', 'i', 'o', 'u' 和 'y'。

文本中每个包含至少一个元音字母的单词可以被划分为音节。每个字符应恰好属于一个音节。例如，单词 "mamma" 可以被划分为 "ma" 和 "mma"，"mam" 和 "ma"，以及 "mamm" 和 "a"。仅由辅音字母组成的单词应被忽略。

给定文本的韵律模式是一个由 $n$ 个整数组成的序列 $p_{1},p_{2},...,p_{n}$。如果对于每个 $i$ 从 $1$ 到 $n$，可以将第 $i$ 行的单词划分为音节，使得音节的总数等于 $p_{i}$，则文本匹配给定的韵律模式。

给定文本和韵律模式，检查给定的文本是否匹配给定的韵律模式。

#### 说明/提示

在第一个样例中，可以将单词划分为音节的方式如下：

`in-tel<br></br>co-de<br></br>ch al-len-ge<br></br>`由于第三行中的单词 "ch" 不包含元音字母，我们可以忽略它。结果我们得到前两行各有 $2$ 个音节，第三行有 $3$ 个音节。

#### 样例 #1

##### 输入

```
3
2 2 3
intel
code
ch allenge
```

##### 输出

```
YES
```

#### 样例 #2

##### 输入

```
4
1 2 3 1
a
bcdefghi
jklmnopqrstu
vwxyz
```

##### 输出

```
NO
```

#### 样例 #3

##### 输入

```
4
13 11 15 15
to be or not to be that is the question
whether tis nobler in the mind to suffer
the slings and arrows of outrageous fortune
or to take arms against a sea of troubles
```

##### 输出

```
YES
```

### 题解分析与结论

#### 综合分析

本题的核心问题在于如何正确统计每行文本中的元音字母数量，并与给定的韵律模式进行比较。难点在于处理包含空格的字符串输入，以及如何高效地统计元音字母的数量。

#### 关键思路与技巧

1. **字符串输入处理**：由于每行文本可能包含空格，使用 `getline` 来读取整行文本是必要的。需要注意的是，`cin` 不会读取换行符，因此在连续使用 `cin` 和 `getline` 时，需要使用 `getchar()` 或额外的 `getline` 来吸收换行符。

2. **元音字母统计**：通过遍历字符串中的每个字符，判断是否为元音字母，并进行计数。可以使用简单的条件判断或定义一个辅助函数来提高代码的可读性。

3. **提前终止**：如果在某一行中发现元音字母数量与给定模式不匹配，可以立即输出 "NO" 并终止程序，避免不必要的计算。

#### 评分较高的题解

1. **作者：zhang_kevin (赞：8)**  
   - **星级：4.5**  
   - **关键亮点**：代码简洁明了，使用 `getline` 处理带空格的输入，并通过简单的条件判断统计元音字母数量。  
   - **代码片段**：
     ```cpp
     getline(cin, s);
     ans = 0;
     int len = s.length();
     for(int j = 0; j <= len - 1; j++){
         if(s[j]=='a'||s[j]=='e'||s[j]=='i'||s[j]=='o'||s[j]=='u'||s[j]=='y'){
             ans++;
         }
     }
     ```

2. **作者：liangbowen (赞：4)**  
   - **星级：4**  
   - **关键亮点**：详细解释了 `getline` 的使用方法，并提供了清晰的代码结构。  
   - **代码片段**：
     ```cpp
     getline(cin, s); //把换行符吃掉先。
     for(int i = 1; i <= n; i++){
         getline(cin, s);
         int len = s.length(), cnt = 0;
         for(int j = 0; j < len; j++) cnt += (s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' || s[j] == 'u' || s[j] == 'y');
         if(cnt != num[i]) {
             cout << "NO";
             return 0;
         }
     }
     ```

3. **作者：BlanketRice (赞：1)**  
   - **星级：4**  
   - **关键亮点**：代码简洁，使用 `getline` 处理输入，并通过辅助函数 `check` 提高代码可读性。  
   - **代码片段**：
     ```cpp
     inline bool check (char c) {
         return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
     }
     ```

#### 推荐题目

1. **P1308 统计单词数**：考察字符串处理和单词统计。
2. **P1553 数字反转（升级版）**：涉及字符串处理和字符判断。
3. **P1598 垂直柱状图**：需要统计字符出现次数并输出柱状图。

#### 个人心得

- **调试经历**：多位作者提到在处理输入时遇到的换行符问题，强调了 `getchar()` 或额外 `getline` 的必要性。
- **踩坑教训**：部分作者最初忽略了 `y` 作为元音字母的情况，导致错误，提醒我们在做题时要仔细阅读题目描述。

---
处理用时：39.04秒