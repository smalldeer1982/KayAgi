# 题目信息

# Longest Palindrome

## 题目描述

Returning back to problem solving, Gildong is now studying about palindromes. He learned that a palindrome is a string that is the same as its reverse. For example, strings "pop", "noon", "x", and "kkkkkk" are palindromes, while strings "moon", "tv", and "abab" are not. An empty string is also a palindrome.

Gildong loves this concept so much, so he wants to play with it. He has $ n $ distinct strings of equal length $ m $ . He wants to discard some of the strings (possibly none or all) and reorder the remaining strings so that the concatenation becomes a palindrome. He also wants the palindrome to be as long as possible. Please help him find one.

## 说明/提示

In the first example, "battab" is also a valid answer.

In the second example, there can be 4 different valid answers including the sample output. We are not going to provide any hints for what the others are.

In the third example, the empty string is the only valid palindrome string.

## 样例 #1

### 输入

```
3 3
tab
one
bat```

### 输出

```
6
tabbat```

## 样例 #2

### 输入

```
4 2
oo
ox
xo
xx```

### 输出

```
6
oxxxxo```

## 样例 #3

### 输入

```
3 5
hello
codef
orces```

### 输出

```
0```

## 样例 #4

### 输入

```
9 4
abab
baba
abcd
bcde
cdef
defg
wxyz
zyxw
ijji```

### 输出

```
20
ababwxyzijjizyxwbaba```

# AI分析结果

### 题目内容重写
# 最长回文串

## 题目描述

Gildong 正在学习回文串。他了解到，回文串是指正读和反读都相同的字符串。例如，"pop"、"noon"、"x" 和 "kkkkkk" 都是回文串，而 "moon"、"tv" 和 "abab" 则不是。空字符串也是回文串。

Gildong 非常喜欢这个概念，因此他想玩一玩。他有 $n$ 个长度均为 $m$ 的 **互不相同的** 字符串。他想要删除其中的一些字符串（可能不删除或全部删除），并将剩下的字符串重新排列，使得它们的连接成为一个回文串。他还希望这个回文串尽可能长。请帮助他找到一个满足条件的回文串。

## 说明/提示

在第一个样例中，"battab" 也是一个有效的答案。

在第二个样例中，有 4 个不同的有效答案，包括样例输出。我们不会提供其他答案的提示。

在第三个样例中，空字符串是唯一有效的回文串。

## 样例 #1

### 输入

```
3 3
tab
one
bat```

### 输出

```
6
tabbat```

## 样例 #2

### 输入

```
4 2
oo
ox
xo
xx```

### 输出

```
6
oxxxxo```

## 样例 #3

### 输入

```
3 5
hello
codef
orces```

### 输出

```
0```

## 样例 #4

### 输入

```
9 4
abab
baba
abcd
bcde
cdef
defg
wxyz
zyxw
ijji```

### 输出

```
20
ababwxyzijjizyxwbaba```

### 算法分类
字符串、构造

### 题解分析与结论
该题的核心思路是通过构造回文串，使得选出的字符串能够首尾相接形成一个回文串。具体来说，每个字符串的翻转必须存在于给定的字符串集合中，或者字符串本身是回文串（可以放在中间）。所有题解都围绕这一核心思路展开，但实现方式和优化程度有所不同。

### 精选题解
1. **作者：_ztyqwq (赞：5)**  
   **星级：5**  
   **关键亮点**：  
   - 使用 `map` 来快速查找字符串的翻转是否存在，避免了暴力匹配。
   - 通过 `ans` 数组记录每对字符串的匹配情况，`ind` 数组记录输出顺序，逻辑清晰。
   - 时间复杂度为 $O(n\log n + nm)$，较为高效。
   **核心代码**：
   ```cpp
   for(int i = 1; i <= n; i++) {
       string ss = rev(s[i]);
       if(s[i] == ss) {
           if(!md) {
               md = 1;
               ans[i] = -1;
               ind[0] = i;
           }
       }
       else if(mp[ss] && !ans[mp[ss]]) {
           ans[i] = ++tot;
           ind[tot] = i;
           ps++;
       }
   }
   ```

2. **作者：123456zmy (赞：3)**  
   **星级：4**  
   **关键亮点**：  
   - 使用二维数组 `a` 记录每个字符串的匹配情况，逻辑简单直接。
   - 通过 `bitset` 记录已使用的字符串，避免了重复匹配。
   - 代码简洁，易于理解。
   **核心代码**：
   ```cpp
   for(int i = 1; i <= n; i++) for(int j = 1; j <= an[i]; j++) if(a[i][j] != i && used[i] == 0 && used[a[i][j]] == 0) {
       used[i] = used[a[i][j]] = 1;
       ans += 2;
       ansnl[ans >> 1] = i;
       ansnr[ans >> 1] = a[i][j];
   }
   ```

3. **作者：coconutt_ (赞：1)**  
   **星级：4**  
   **关键亮点**：  
   - 使用 `QAQ` 数组记录已使用的字符串，逻辑清晰。
   - 通过 `qwq` 函数判断两个字符串是否互为翻转，代码简洁。
   - 处理了回文串放在中间的情况，逻辑完整。
   **核心代码**：
   ```cpp
   for(int i = 0; i < n - 1; i++) {
       for(int j = i + 1; j < n; j++) {
           if(!QAQ[i] && !QAQ[j] && qwq(s[i], s[j])) {
               ans += 2 * b;
               QAQ[i] = 1;
               QAQ[j] = 1;
               pop++;
               sd[pop] = s[i];
               sx[pop] = s[j];
           }
       }
   }
   ```

### 最优关键思路
- **使用哈希表（如 `map`）快速查找字符串的翻转是否存在**，避免暴力匹配，提升效率。
- **记录每对字符串的匹配情况**，确保每对字符串只被使用一次。
- **处理回文串放在中间的情况**，确保回文串的长度最大化。

### 可拓展之处
- 类似的问题可以扩展到处理不同长度的字符串，或者允许字符串重复使用的情况。
- 可以进一步优化时间复杂度，例如通过更高效的数据结构来存储和查找字符串。

### 推荐题目
1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1435 [IOI2000]回文字串](https://www.luogu.com.cn/problem/P1435)
3. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：38.40秒