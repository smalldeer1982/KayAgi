# 题目信息

# K-Complete Word

## 题目描述

Word $ s $ of length $ n $ is called $ k $ -complete if

- $ s $ is a palindrome, i.e. $ s_i=s_{n+1-i} $ for all $ 1 \le i \le n $ ;
- $ s $ has a period of $ k $ , i.e. $ s_i=s_{k+i} $ for all $ 1 \le i \le n-k $ .

For example, "abaaba" is a $ 3 $ -complete word, while "abccba" is not.

Bob is given a word $ s $ of length $ n $ consisting of only lowercase Latin letters and an integer $ k $ , such that $ n $ is divisible by $ k $ . He wants to convert $ s $ to any $ k $ -complete word.

To do this Bob can choose some $ i $ ( $ 1 \le i \le n $ ) and replace the letter at position $ i $ with some other lowercase Latin letter.

So now Bob wants to know the minimum number of letters he has to replace to convert $ s $ to any $ k $ -complete word.

Note that Bob can do zero changes if the word $ s $ is already $ k $ -complete.

You are required to answer $ t $ test cases independently.

## 说明/提示

In the first test case, one optimal solution is aaaaaa.

In the second test case, the given word itself is $ k $ -complete.

## 样例 #1

### 输入

```
4
6 2
abaaba
6 3
abaaba
36 9
hippopotomonstrosesquippedaliophobia
21 7
wudixiaoxingxingheclp```

### 输出

```
2
0
23
16```

# AI分析结果

### 题目内容重写

#### K-Complete Word

**题目描述**

长度为 $n$ 的字符串 $s$ 被称为 $k$ -complete 的，如果它满足以下两个条件：

1. $s$ 是一个回文串，即对于所有的 $1 \le i \le n$，$s_i = s_{n+1-i}$；
2. $s$ 的周期为 $k$，即对于所有的 $1 \le i \le n-k$，$s_i = s_{k+i}$。

例如，"abaaba" 是一个 $3$ -complete 的字符串，而 "abccba" 不是。

Bob 给定一个长度为 $n$ 的字符串 $s$，它仅由小写拉丁字母组成，并且给定一个整数 $k$，满足 $n$ 能被 $k$ 整除。他希望通过修改 $s$ 中的一些字符，将其转换为任意的 $k$ -complete 字符串。

Bob 可以选择任意位置 $i$（$1 \le i \le n$），并将该位置的字符替换为其他小写拉丁字母。

现在，Bob 想知道他最少需要修改多少个字符才能将 $s$ 转换为任意的 $k$ -complete 字符串。

注意，如果 $s$ 已经是 $k$ -complete 的，Bob 可以不进行任何修改。

你需要独立回答 $t$ 组测试用例。

**说明/提示**

在第一个测试用例中，一个最优解是 "aaaaaa"。

在第二个测试用例中，给定的字符串本身就是 $k$ -complete 的。

**样例 #1**

**输入**

```
4
6 2
abaaba
6 3
abaaba
36 9
hippopotomonstrosesquippedaliophobia
21 7
wudixiaoxingxingheclp
```

**输出**

```
2
0
23
16
```

### 算法分类

字符串、贪心

### 题解分析与结论

本题的核心在于如何通过最少的修改次数将给定的字符串转换为满足回文和周期条件的字符串。多个题解都采用了贪心策略，通过统计特定位置的字符出现频率，选择出现次数最多的字符作为目标字符，从而最小化修改次数。

### 评分较高的题解

#### 题解1：作者：一扶苏一 (赞：6)

**星级：5**

**关键亮点：**
- 通过分析回文和周期性质，将问题转化为统计特定位置的字符频率。
- 使用贪心策略，选择出现次数最多的字符作为目标字符，最小化修改次数。
- 代码简洁高效，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int d = n / k * 2, ans = 0, mv;
for (int i = 1, dk = (k >> 1) + (k & 1); i <= dk; ++i) {
    memset(a, 0, sizeof a);
    mv = 0;
    for (int j = i; j <= n; j += k) if (++a[s[j] - 'a'] > mv) {
        mv = a[s[j] - 'a'];
    }
    for (int j = k - i + 1; j <= n; j += k) if (++a[s[j] - 'a'] > mv) {
        mv = a[s[j] - 'a'];
    }
    ans += d - mv;
}
if (k & 1) ans -= (d - mv) >> 1;
```

#### 题解2：作者：iMya_nlgau (赞：4)

**星级：4**

**关键亮点：**
- 通过画图直观理解字符串的周期和回文性质。
- 使用贪心策略，统计相同位置的字符频率，选择出现次数最多的字符作为目标字符。
- 代码实现清晰，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
for (int i = 0; i <= (k - 1) >> 1; i++) {
    for (int j = i; j < n; j += k) {
        int q = j - 2 * i + k - 1;
        ch[s[j]]++;
        if (j != q) ch[s[q]]++;
    }
    int p = 0;
    for (int i = 'a'; i <= 'z'; i++) {
        if (ch[i] > p) p = ch[i];
        ch[i] = 0;
    }
    if (k & 1 && i == k / 2) ans += n / k - p;
    else ans += n / k * 2 - p;
}
```

#### 题解3：作者：George1123 (赞：1)

**星级：4**

**关键亮点：**
- 通过分析回文和周期性质，将问题转化为统计特定位置的字符频率。
- 使用贪心策略，选择出现次数最多的字符作为目标字符，最小化修改次数。
- 代码实现简洁，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
for (re int i = 1; i <= k / 2; i++) {
    memset(cnt, 0, sizeof cnt);
    re int tmp = 0;
    for (re int j = i; j <= n; j += k) cnt[s[j] - 'a']++, tmp++;
    for (re int j = k + 1 - i; j <= n; j += k) cnt[s[j] - 'a']++, tmp++;
    re int mx = 0;
    for (re int i = 1; i < 26; i++) if (cnt[i] > cnt[mx]) mx = i;
    ans += tmp - cnt[mx];
}
```

### 最优关键思路与技巧

1. **贪心策略**：通过统计特定位置的字符频率，选择出现次数最多的字符作为目标字符，从而最小化修改次数。
2. **回文与周期性质**：利用回文和周期的性质，将问题转化为统计特定位置的字符频率。
3. **时间复杂度优化**：通过合理的数据结构和算法设计，确保时间复杂度为 $O(n)$。

### 可拓展之处

类似的问题可以通过分析字符串的性质，将其转化为统计特定位置的字符频率，从而使用贪心策略进行优化。例如，处理回文串、周期串等问题时，可以采用类似的思路。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3398 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3398)

### 个人心得摘录

- **调试经历**：在处理回文和周期性质时，需要仔细分析字符串的结构，确保统计的字符位置正确。
- **踩坑教训**：在处理奇数长度的周期时，需要特别注意中间字符的处理，避免重复统计或遗漏。
- **顿悟感想**：通过将问题转化为统计字符频率，可以大大简化问题的复杂度，提高解题效率。

---
处理用时：48.08秒