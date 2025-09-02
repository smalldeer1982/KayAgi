# 题目信息

# Anya and the Mysterious String

## 题目描述

Anya received a string $ s $ of length $ n $ brought from Rome. The string $ s $ consists of lowercase Latin letters and at first glance does not raise any suspicions. An instruction was attached to the string.

Start of the instruction.

A palindrome is a string that reads the same from left to right and right to left. For example, the strings "anna", "aboba", "level" are palindromes, while the strings "gorilla", "banan", "off" are not.

A substring $ [l \ldots r] $ of string $ s $ is a string $ s_l s_{l+1} \ldots s_{r-1} s_r $ . For example, the substring $ [4 \ldots 6] $ of the string "generation" is the string "era".

A string is called beautiful if it does not contain a substring of length at least two that is a palindrome. For example, the strings "fox", "abcdef", and "yioy" are beautiful, while the strings "xyxx", "yikjkitrb" are not.

When an integer $ x $ is added to the character $ s_i $ , it is replaced $ x $ times with the next character in the alphabet, with "z" being replaced by "a".

When an integer $ x $ is added to the substring $ [l, r] $ of string $ s $ , it becomes the string $ s_1 s_2 \ldots s_{l-1} (s_l + x) (s_{l+1} + x) \ldots (s_{r-1} + x) (s_r + x) s_{r+1} \ldots s_n $ . For example, when the substring $ [2, 4] $ of the string "abazaba" is added with the number $ 6 $ , the resulting string is "ahgfaba".

End of the instruction.

After reading the instruction, Anya resigned herself to the fact that she has to answer $ m $ queries. The queries can be of two types:

1. Add the number $ x $ to the substring $ [l \ldots r] $ of string $ s $ .
2. Determine whether the substring $ [l \ldots r] $ of string $ s $ is beautiful.

## 说明/提示

In the first test case of the first test, the following happens:

- tedubcyyxopz: the string edub is beautiful;
- tedubcyyxopz $ \to $ tedwdeaaxopz;
- tedwdeaaxopz: the string tedwdea is not beautiful as it contains the palindrome edwde;
- tedwdeaaxopz $ \to $ terkreaaxopz;
- terkreaaxopz $ \to $ terkreaaarsz;
- terkreaaarsz $ \to $ terkreaaaasz;
- terkreaaaasz: the string kreaaaa is not beautiful as it contains the palindrome aaaa;
- terkreaaaasz: the string asz is beautiful.

## 样例 #1

### 输入

```
5
12 8
tedubcyyxopz
2 2 5
1 4 8 2
2 1 7
1 3 5 40
1 9 11 3
1 10 10 9
2 4 10
2 10 12
10 4
ubnxwwgzjt
2 4 10
2 10 10
1 6 10 8
2 7 7
11 3
hntcxfxyhtu
1 4 6 1
2 4 10
1 4 10 21
13 2
yxhlmzfhqctir
1 5 9 3
1 8 13 15
2 3
bp
1 1 2 15
1 1 2 18
1 2 2 1000000000```

### 输出

```
YES
NO
NO
YES
NO
YES
YES
YES```

# AI分析结果

### 题目内容中文重写

# Anya 和神秘的字符串

## 题目描述

Anya 收到了一个从罗马带来的长度为 $n$ 的字符串 $s$。字符串 $s$ 由小写拉丁字母组成，乍一看并没有什么可疑之处。但附带的说明却让她感到困惑。

**说明开始。**

回文串是指从左到右和从右到左读都相同的字符串。例如，字符串 "anna"、"aboba"、"level" 是回文串，而字符串 "gorilla"、"banan"、"off" 则不是。

字符串 $s$ 的子串 $[l \ldots r]$ 是指从 $s_l$ 到 $s_r$ 的连续字符组成的字符串。例如，字符串 "generation" 的子串 $[4 \ldots 6]$ 是 "era"。

一个字符串被称为“美丽的”，如果它不包含长度至少为 2 的回文子串。例如，字符串 "fox"、"abcdef" 和 "yioy" 是美丽的，而字符串 "xyxx"、"yikjkitrb" 则不是。

当字符 $s_i$ 加上整数 $x$ 时，它会被替换为字母表中接下来的 $x$ 个字符，其中 "z" 会被替换为 "a"。

当字符串 $s$ 的子串 $[l, r]$ 加上整数 $x$ 时，它会变成字符串 $s_1 s_2 \ldots s_{l-1} (s_l + x) (s_{l+1} + x) \ldots (s_{r-1} + x) (s_r + x) s_{r+1} \ldots s_n$。例如，当字符串 "abazaba" 的子串 $[2, 4]$ 加上数字 $6$ 时，结果字符串为 "ahgfaba"。

**说明结束。**

在阅读完说明后，Anya 意识到她需要回答 $m$ 个查询。查询有两种类型：

1. 将数字 $x$ 加到字符串 $s$ 的子串 $[l \ldots r]$ 上。
2. 判断字符串 $s$ 的子串 $[l \ldots r]$ 是否是美丽的。

## 说明/提示

在第一个测试用例中，发生了以下情况：

- tedubcyyxopz: 字符串 "edub" 是美丽的；
- tedubcyyxopz $ \to $ tedwdeaaxopz；
- tedwdeaaxopz: 字符串 "tedwdea" 不是美丽的，因为它包含回文子串 "edwde"；
- tedwdeaaxopz $ \to $ terkreaaxopz；
- terkreaaxopz $ \to $ terkreaaarsz；
- terkreaaaasz: 字符串 "kreaaaa" 不是美丽的，因为它包含回文子串 "aaaa"；
- terkreaaaasz: 字符串 "asz" 是美丽的。

### 算法分类
字符串、线段树、差分

### 题解分析与结论

题目要求处理两种操作：区间修改和区间查询。区间修改是将字符串的某个子串中的每个字符加上一个数，区间查询是判断某个子串是否是“美丽的”（即不包含长度至少为 2 的回文子串）。由于回文串的判断可以简化为判断是否存在长度为 2 或 3 的回文子串，因此我们可以通过维护区间的最左、次左、最右、次右字符来判断是否存在回文子串。

### 精选题解

#### 题解1：苏联小渣 (5星)
**关键亮点**：使用线段树维护区间的最左、次左、最右、次右字符，并通过合并操作判断是否存在长度为 2 或 3 的回文子串。代码清晰，思路明确。
**核心代码**：
```cpp
node operator + (node x, node y){
    node ret;
    ret.l = x.l, ret.r = y.r, ret.len = x.len + y.len;
    if (x.len == 1) ret.l2 = y.l;
    else ret.l2 = x.l2;
    if (y.len == 1) ret.r2 = x.r;
    else ret.r2 = y.r2;
    ret.sx = (x.sx | y.sx), ret.sy = (x.sy | y.sy);
    if (x.r == y.l) ret.sy = 1;
    if (x.len > 1 && x.r2 == y.l) ret.sx = 1;
    if (y.len > 1 && y.l2 == x.r) ret.sx = 1;
    return ret;
}
```
**个人心得**：通过维护区间的最左、次左、最右、次右字符，可以高效地判断是否存在回文子串。

#### 题解2：shinzanmono (4星)
**关键亮点**：采用分块的方法处理区间修改和查询，散块暴力重构，整块打标记。时间复杂度为 $O(n\sqrt{n})$，适合大数据量。
**核心代码**：
```cpp
void add(int ln,int rn,int val){
    if(belong[ln]==belong[rn]){
        remake(belong[ln]);
        for(int i=ln;i<=rn;i++)arr[i]=(arr[i]+val)%26;
        build(belong[ln]);
        return;
    }
    remake(belong[ln]);
    for(int i=ln;i<=br[belong[ln]];i++)arr[i]=(arr[i]+val)%26;
    build(belong[ln]);
    remake(belong[rn]);
    for(int i=bl[belong[rn]];i<=rn;i++)arr[i]=(arr[i]+val)%26;
    build(belong[rn]);
    for(int i=belong[ln]+1;i<belong[rn];i++)tag[i]=(tag[i]+val)%26;
}
```
**个人心得**：分块处理区间操作时，散块暴力重构，整块打标记，可以有效降低时间复杂度。

#### 题解3：WaterSun (4星)
**关键亮点**：使用线段树维护区间的最左、次左、最右、次右字符，并通过标记变量 $f_1, f_2$ 判断是否存在长度为 2 或 3 的回文子串。代码简洁，思路清晰。
**核心代码**：
```cpp
inline node merge(node a,node b){
    node res = {a.l,b.r,0,{a.lc[0],a.lc[1]},{b.rc[0],b.rc[1]},{a.f[0] | b.f[0],a.f[1] | b.f[1]}};
    if (!~res.lc[1]) res.lc[1] = b.lc[0];
    if (!~res.rc[1]) res.rc[1] = a.rc[0];
    if (~a.rc[0] && ~b.lc[0] && a.rc[0] == b.lc[0]) res.f[0] = true;
    if (~a.rc[1] && ~b.lc[0] && a.rc[1] == b.lc[0]) res.f[1] = true;
    if (~a.rc[0] && ~b.lc[1] && a.rc[0] == b.lc[1]) res.f[1] = true;
    return res;
}
```
**个人心得**：通过维护区间的最左、次左、最右、次右字符，可以高效地判断是否存在回文子串。

### 最优关键思路
1. **线段树维护区间信息**：通过维护区间的最左、次左、最右、次右字符，可以高效地判断是否存在长度为 2 或 3 的回文子串。
2. **分块处理区间操作**：对于大数据量，可以采用分块的方法，散块暴力重构，整块打标记，降低时间复杂度。

### 可拓展之处
类似的问题可以通过维护区间的边界信息来判断某些特定条件，如回文串、连续相同字符等。线段树和分块是处理区间操作的常用方法，可以根据具体问题选择合适的算法。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：68.74秒