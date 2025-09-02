# 题目信息

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA
```

### 输出

```
AB
```

## 样例 #2

### 输入

```
5
ZZZAA
```

### 输出

```
ZZ
```

# AI分析结果

### 题目内容重写

#### Two-gram

**题目描述**

Two-gram 是一个由两个大写拉丁字母组成的有序对（即长度为2的字符串）。例如，"AZ"、"AA"、"ZA" 是三个不同的 two-gram。

给定一个由 $n$ 个大写拉丁字母组成的字符串 $s$，你的任务是找到在该字符串中作为子串（即字符串中连续的两个字符）出现次数最多的任意一个 two-gram。例如，对于字符串 $s$ = "BBAABBBA"，答案是 two-gram "BB"，它在 $s$ 中出现了三次。换句话说，找到出现次数最多的 two-gram。

注意，two-gram 的出现可以相互重叠。

**说明/提示**

在第一个样例中，"BA" 也是一个有效的答案。

在第二个样例中，唯一可以输出的 two-gram 是 "ZZ"，因为它在字符串 "ZZZAA" 中出现了两次。

**样例 #1**

**输入**

```
7
ABACABA
```

**输出**

```
AB
```

**样例 #2**

**输入**

```
5
ZZZAA
```

**输出**

```
ZZ
```

---

### 题解分析与结论

#### 题解对比与评分

1. **WinterRain208 (4星)**
   - **关键亮点**：使用 `map<string, int>` 来统计每个 two-gram 的出现次数，代码简洁且易于理解。通过 `for(auto && p : m)` 遍历 `map`，展示了 C++11 的遍历方式。
   - **代码实现**：
     ```cpp
     map <  string , int > m; 
     for( auto && p : m )
         if(p.second>M){
             M=p.second;
             ans=p.first.c_str();
         }
     ```
   - **个人心得**：强调了 `map` 的使用方法，特别是如何遍历 `map` 并获取键值对。

2. **Cult_style (4星)**
   - **关键亮点**：使用二维数组 `k[30][30]` 来统计 two-gram 的出现次数，避免了 `map` 的开销，适合小规模数据。通过将字符转换为数字作为数组下标，实现了高效的统计。
   - **代码实现**：
     ```cpp
     int k[30][30];
     for(int i=0;i<n-1;i++){
         int x=a[i]-'A',y=a[i+1]-'A';
         k[x][y]++;
         if(k[x][y]>ma) ma=k[x][y];	
     }
     ```
   - **个人心得**：通过将字符转换为数字，简化了统计过程，适合对性能有一定要求的场景。

3. **judgejudge (4星)**
   - **关键亮点**：使用二维数组 `a[27][27]` 来统计 two-gram 的出现次数，并通过遍历数组找到最大值。代码结构清晰，易于理解。
   - **代码实现**：
     ```cpp
     int a[27][27];
     for(i=0;i<n-1;i++)
         a[st[i]-64][st[i+1]-64]++;
     for(i=1;i<=26;i++)
         for(j=1;j<=26;j++)
             if(maxl<a[i][j]){
                 maxl=a[i][j];
                 row=i;
                 col=j;
             }
     ```
   - **个人心得**：通过将字符转换为 ASCII 码，简化了统计过程，适合对性能有一定要求的场景。

#### 最优关键思路

- **数据结构选择**：对于小规模数据，使用二维数组（如 `k[30][30]` 或 `a[27][27]`）来统计 two-gram 的出现次数，性能优于 `map`。
- **字符转换**：将字符转换为数字（如 `a[i]-'A'` 或 `st[i]-64`）作为数组下标，简化了统计过程。
- **遍历方式**：使用 C++11 的 `for(auto && p : m)` 遍历 `map`，代码简洁且易于理解。

#### 拓展思路

- **同类型题**：类似的问题可以扩展到统计长度为3或更长的子串，或者统计不连续的子串。
- **算法优化**：对于大规模数据，可以考虑使用哈希表或其他更高效的数据结构来统计子串的出现次数。

### 推荐题目

1. **P3370 【模板】字符串哈希** - 考察字符串哈希的基本应用。
2. **P3375 【模板】KMP字符串匹配** - 考察字符串匹配算法。
3. **P3374 【模板】树状数组 1** - 考察树状数组的基本应用。

### 个人心得总结

- **调试经历**：在使用 `map` 时，注意遍历方式的选择，特别是 C++11 的 `for(auto && p : m)` 可以简化代码。
- **踩坑教训**：在处理字符时，注意字符与数字的转换，避免数组越界等问题。
- **顿悟感想**：对于小规模数据，使用二维数组统计子串出现次数，性能优于 `map`，且代码更简洁。

---
处理用时：29.92秒