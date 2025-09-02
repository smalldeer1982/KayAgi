# 题目信息

# Zuhair and Strings

## 题目描述

Given a string $ s $ of length $ n $ and integer $ k $ ( $ 1 \le k \le n $ ). The string $ s $ has a level $ x $ , if $ x $ is largest non-negative integer, such that it's possible to find in $ s $ :

- $ x $ non-intersecting (non-overlapping) substrings of length $ k $ ,
- all characters of these $ x $ substrings are the same (i.e. each substring contains only one distinct character and this character is the same for all the substrings).

A substring is a sequence of consecutive (adjacent) characters, it is defined by two integers $ i $ and $ j $ ( $ 1 \le i \le j \le n $ ), denoted as $ s[i \dots j] $ = " $ s_{i}s_{i+1} \dots s_{j} $ ".

For example, if $ k = 2 $ , then:

- the string "aabb" has level $ 1 $ (you can select substring "aa"),
- the strings "zzzz" and "zzbzz" has level $ 2 $ (you can select two non-intersecting substrings "zz" in each of them),
- the strings "abed" and "aca" have level $ 0 $ (you can't find at least one substring of the length $ k=2 $ containing the only distinct character).

Zuhair gave you the integer $ k $ and the string $ s $ of length $ n $ . You need to find $ x $ , the level of the string $ s $ .

## 说明/提示

In the first example, we can select $ 2 $ non-intersecting substrings consisting of letter 'a': "(aa)ac(aa)bb", so the level is $ 2 $ .

In the second example, we can select either substring "a" or "b" to get the answer $ 1 $ .

## 样例 #1

### 输入

```
8 2
aaacaabb
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1
ab
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 2
abab
```

### 输出

```
0
```

# AI分析结果

### 题目内容
#### Zuhair and Strings

**题目描述**

给定一个长度为 $n$ 的字符串 $s$ 和整数 $k$（$1 \le k \le n$）。字符串 $s$ 的等级为 $x$，如果 $x$ 是最大的非负整数，使得可以在 $s$ 中找到：

- $x$ 个不重叠的长度为 $k$ 的子串，
- 这些子串的所有字符都相同（即每个子串只包含一个不同的字符，并且这个字符对于所有子串都是相同的）。

子串是连续字符的序列，由两个整数 $i$ 和 $j$（$1 \le i \le j \le n$）定义，表示为 $s[i \dots j] = "s_{i}s_{i+1} \dots s_{j}"$。

例如，如果 $k = 2$，那么：

- 字符串 "aabb" 的等级为 $1$（可以选择子串 "aa"），
- 字符串 "zzzz" 和 "zzbzz" 的等级为 $2$（可以选择两个不重叠的子串 "zz"），
- 字符串 "abed" 和 "aca" 的等级为 $0$（无法找到至少一个长度为 $k=2$ 的子串，且子串只包含一个不同的字符）。

Zuhair 给你整数 $k$ 和长度为 $n$ 的字符串 $s$。你需要找到 $x$，即字符串 $s$ 的等级。

**说明/提示**

在第一个例子中，我们可以选择 $2$ 个不重叠的子串，由字母 'a' 组成："(aa)ac(aa)bb"，所以等级为 $2$。

在第二个例子中，我们可以选择子串 "a" 或 "b" 来得到答案 $1$。

**样例 #1**

**输入**

```
8 2
aaacaabb
```

**输出**

```
2
```

**样例 #2**

**输入**

```
2 1
ab
```

**输出**

```
1
```

**样例 #3**

**输入**

```
4 2
abab
```

**输出**

```
0
```

### 算法分类
贪心

### 题解分析与结论
题目要求找到字符串中最多可以有多少个不重叠的长度为 $k$ 的子串，且这些子串的所有字符都相同。这是一个典型的贪心问题，可以通过遍历字符串，统计每个字符的连续出现次数，然后计算每个字符可以形成多少个符合条件的子串，最后取最大值。

### 题解评分与亮点
1. **hsfzLZH1**（5星）
   - **关键亮点**：使用了一个长度为 $26$ 的计数器来统计每个字符的连续出现次数，并在遍历时直接计算可以形成多少个符合条件的子串。代码简洁且高效，时间复杂度为 $O(n)$。
   - **代码核心思想**：遍历字符串，统计每个字符的连续出现次数，并在字符变化时计算可以形成多少个符合条件的子串，最后取最大值。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
     {
         if(i!=1&&s[i]!=s[i-1])ans[s[i-1]-'a']+=nww/k,nww=0;
         nww++;
     }
     ans[s[n]-'a']+=nww/k;
     for(int i=0;i<26;i++)maxx=max(maxx,ans[i]);
     ```

2. **HEzzz**（4星）
   - **关键亮点**：通过枚举每个字符，遍历字符串，统计每个字符的连续出现次数，并计算可以形成多少个符合条件的子串。思路清晰，代码简洁。
   - **代码核心思想**：枚举每个字符，遍历字符串，统计每个字符的连续出现次数，并在字符变化时计算可以形成多少个符合条件的子串，最后取最大值。
   - **核心代码**：
     ```cpp
     for(char t='a';t<='z';++t)
     {
         int res=0,now=0;
         _rep(i,1,n+1)
         {
             if(s[i]!=t) res+=now/k,now=0; 
             else now++;
         }
         ans=max(ans,res);
     }
     ```

3. **Rachel_in**（4星）
   - **关键亮点**：使用数组 $f$ 记录每个位置的连续字符长度，然后遍历数组，统计每个字符可以形成多少个符合条件的子串。思路清晰，代码简洁。
   - **代码核心思想**：使用数组 $f$ 记录每个位置的连续字符长度，然后遍历数组，统计每个字符可以形成多少个符合条件的子串，最后取最大值。
   - **核心代码**：
     ```cpp
     for(int i=1;i<n;i++)
     {
         if(s[i]==s[i-1])
         f[i]=f[i-1]+1;
         else
         f[i]=1;
     }
     for(int i=0;i<n;i++)
     {
         if(f[i]!=0&&f[i]%m==0)
         ans[(int)s[i]-'a']++;
     }
     ```

### 最优关键思路或技巧
最优的思路是通过遍历字符串，统计每个字符的连续出现次数，并在字符变化时计算可以形成多少个符合条件的子串，最后取最大值。这种方法的时间复杂度为 $O(n)$，且代码简洁高效。

### 可拓展之处
类似的问题可以扩展到更复杂的字符串匹配问题，如寻找多个不重叠的子串，且这些子串满足特定的模式或条件。此外，还可以考虑动态规划或滑动窗口等方法来优化类似的字符串处理问题。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：36.36秒