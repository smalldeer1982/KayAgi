# 题目信息

# Palindromes Coloring

## 题目描述

You have a string $ s $ consisting of lowercase Latin alphabet letters.

You can color some letters in colors from $ 1 $ to $ k $ . It is not necessary to paint all the letters. But for each color, there must be a letter painted in that color.

Then you can swap any two symbols painted in the same color as many times as you want.

After that, $ k $ strings will be created, $ i $ -th of them will contain all the characters colored in the color $ i $ , written in the order of their sequence in the string $ s $ .

Your task is to color the characters of the string so that all the resulting $ k $ strings are palindromes, and the length of the shortest of these $ k $ strings is as large as possible.

Read the note for the first test case of the example if you need a clarification.

Recall that a string is a palindrome if it reads the same way both from left to right and from right to left. For example, the strings abacaba, cccc, z and dxd are palindromes, but the strings abab and aaabaa — are not.

## 说明/提示

- In the first test case, $ s $ ="bxyaxzay", $ k=2 $ . We use indices in the string from $ 1 $ to $ 8 $ . The following coloring will work: $ \mathtt{\mathbf{\color{red}{b}\color{blue}{xy}\color{red}{a}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ (the letter z remained uncolored). After painting:
  - swap two red characters (with the indices $ 1 $ and $ 4 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ ;
  - swap two blue characters (with the indices $ 5 $ and $ 8 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{y}z\color{red}{a}\color{blue}{x}}} $ .
  
  Now, for each of the two colors we write out the corresponding characters from left to right, we get two strings $ \mathtt{\mathbf{\color{red}{aba}}} $ and $ \mathtt{\mathbf{\color{blue}{xyyx}}} $ . Both of them are palindromes, the length of the shortest is $ 3 $ . It can be shown that the greatest length of the shortest palindrome cannot be achieved.
- In the second set of input data, the following coloring is suitable: $ [1, 1, 2, 2, 3, 3] $ . There is no need to swap characters. Both received strings are equal to aa, they are palindromes and their length is $ 2 $ .
- In the third set of input data, you can color any character and take it into a string.
- In the fourth set of input data, you can color the $ i $ th character in the color $ i $ .
- In the fifth set of input data can be colored in each of the colors of one character.
- In the sixth set of input data, the following coloring is suitable: $ [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0] $ . Rearrange the characters so as to get the palindromes abcba and acbca.

## 样例 #1

### 输入

```
10
8 2
bxyaxzay
6 3
aaaaaa
6 1
abcdef
6 6
abcdef
3 2
dxd
11 2
abcabcabcac
6 6
sipkic
7 2
eatoohd
3 1
llw
6 2
bfvfbv```

### 输出

```
3
2
1
1
1
5
1
1
3
3```

# AI分析结果

### 题目内容翻译
# 回文串染色

## 题目描述

你有一个由小写拉丁字母组成的字符串 $s$。

你可以将字符串中的一些字母染成 $1$ 到 $k$ 的颜色。不需要将所有字母都染色，但每种颜色必须至少有一个字母被染色。

然后，你可以任意交换两个染有相同颜色的字母，交换次数不限。

之后，将生成 $k$ 个字符串，第 $i$ 个字符串包含所有染成颜色 $i$ 的字符，按照它们在字符串 $s$ 中的顺序排列。

你的任务是给字符串中的字符染色，使得所有生成的 $k$ 个字符串都是回文串，并且这些字符串中最短的那个字符串的长度尽可能大。

### 算法分类
贪心

### 题解分析与结论
本题的核心在于如何将字符串中的字符合理分配到 $k$ 个回文串中，并且使得最短的回文串长度最大化。各题解的思路主要集中在统计字符的出现次数，尤其是成对字符的数量，然后通过贪心策略将这些字符平均分配到 $k$ 个回文串中。

### 高星题解推荐
#### 题解1：AFewSuns (4星)
**关键亮点**：
- 使用二分法来寻找最短回文串的最大长度，思路清晰。
- 通过统计字符出现次数，判断是否能够形成 $k$ 个回文串。

**核心代码**：
```cpp
bool ck(ll x){
    ll cnt[27];
    for(ll i=1;i<=26;i++) cnt[i]=0;
    for(ll i=1;i<=n;i++) cnt[c[i]-'a'+1]++;
    ll tmp=x/2,tot=0;
    for(ll i=1;i<=26;i++) tot+=cnt[i]/2;
    if(tot<tmp*k) return 0;
    if(x%2==0) return 1;
    tot=0; 
    for(ll i=1;i<=26;i++) tot+=cnt[i];
    return tot>=x*k;
}
```
**实现思想**：通过二分法确定最短回文串的最大长度，并统计字符出现次数来判断是否满足条件。

#### 题解2：lalaji2010 (4星)
**关键亮点**：
- 详细分析了回文串的构成条件，并提出了如何统计成对字符和单个字符的方法。
- 通过贪心策略将字符平均分配到 $k$ 个回文串中。

**核心代码**：
```cpp
long long answer=(ans/k)*2;
cnt+=(ans%k)*2;
if(cnt>=k){
    answer++;
}
```
**实现思想**：统计成对字符和单个字符的数量，通过贪心策略计算最短回文串的最大长度。

### 最优关键思路
1. **统计字符出现次数**：通过统计每个字符的出现次数，尤其是成对字符的数量，来判断是否能够形成 $k$ 个回文串。
2. **贪心策略**：将成对字符平均分配到 $k$ 个回文串中，剩余的单个字符可以用于增加回文串的长度。
3. **二分法**：通过二分法确定最短回文串的最大长度，提高查找效率。

### 可拓展之处
本题的贪心策略和二分法可以应用于其他需要将资源平均分配并最大化最小值的问题，例如任务调度、资源分配等。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：25.16秒