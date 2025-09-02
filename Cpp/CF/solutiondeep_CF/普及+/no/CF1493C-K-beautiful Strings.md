# 题目信息

# K-beautiful Strings

## 题目描述

You are given a string $ s $ consisting of lowercase English letters and a number $ k $ . Let's call a string consisting of lowercase English letters beautiful if the number of occurrences of each letter in that string is divisible by $ k $ . You are asked to find the lexicographically smallest beautiful string of length $ n $ , which is lexicographically greater or equal to string $ s $ . If such a string does not exist, output $ -1 $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case "acac" is greater than or equal to $ s $ , and each letter appears $ 2 $ or $ 0 $ times in it, so it is beautiful.

In the second test case each letter appears $ 0 $ or $ 1 $ times in $ s $ , so $ s $ itself is the answer.

We can show that there is no suitable string in the third test case.

In the fourth test case each letter appears $ 0 $ , $ 3 $ , or $ 6 $ times in "abaabaaab". All these integers are divisible by $ 3 $ .

## 样例 #1

### 输入

```
4
4 2
abcd
3 1
abc
4 3
aaaa
9 3
abaabaaaa```

### 输出

```
acac
abc
-1
abaabaaab```

# AI分析结果

### 题目内容（中文重写）
# K - 美丽字符串

## 题目描述
给定一个由小写英文字母组成的字符串 $s$ 和一个数字 $k$。如果一个由小写英文字母组成的字符串中每个字母的出现次数都能被 $k$ 整除，我们就称这个字符串是美丽的。要求你找出长度为 $n$ 且字典序大于或等于字符串 $s$ 的字典序最小的美丽字符串。如果这样的字符串不存在，则输出 $-1$。

如果满足以下条件之一，则称字符串 $a$ 的字典序小于字符串 $b$：
- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 不同的第一个位置上，字符串 $a$ 中的字母在字母表中出现的顺序比 $b$ 中相应位置的字母靠前。

## 说明/提示
在第一个测试用例中，“acac” 大于或等于 $s$，并且每个字母在其中出现 $2$ 次或 $0$ 次，所以它是美丽的。

在第二个测试用例中，每个字母在 $s$ 中出现 $0$ 次或 $1$ 次，所以 $s$ 本身就是答案。

我们可以证明在第三个测试用例中不存在合适的字符串。

在第四个测试用例中，每个字母在 “abaabaaab” 中出现 $0$ 次、$3$ 次或 $6$ 次。所有这些整数都能被 $3$ 整除。

## 样例 #1
### 输入
```
4
4 2
abcd
3 1
abc
4 3
aaaa
9 3
abaabaaaa
```

### 输出
```
acac
abc
-1
abaabaaab
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先特判 $n$ 不能被 $k$ 整除的情况（此时无解），然后判断原字符串 $s$ 是否本身就是美丽字符串，若是则直接输出。若不是，则从后往前枚举字符串中第一个比原字符串大的位置，尝试在该位置替换合适的字符，再检查后面的空位是否能补足所有字母的需求，以构造出满足条件的美丽字符串。

各题解的算法要点和难点对比：
- **算法要点**：都涉及到字符计数、枚举位置和字符、检查剩余空位是否足够等操作。
- **难点对比**：主要在于如何高效地计算出每个字母还需要的数量，以及如何判断剩余空位是否能满足需求。不同题解在实现细节上有所不同，如使用数组或向量来记录字符计数，以及不同的判断条件和构造方式。

### 题解评分与选择
- **little_sun（3星）**：思路清晰，代码结构完整，但部分变量命名不够直观，影响代码可读性。
- **ax_by_c（2星）**：思路有一定阐述，但缺乏代码实现，且时间复杂度分析不够准确。
- **xuezhe（3星）**：思路和代码都比较清晰，使用了向量来处理后续字符的填充，但代码中部分逻辑稍显复杂。
- **7KByte（3星）**：思路简洁明了，代码实现较为清晰，时间复杂度分析准确。
- **wmrqwq（2星）**：思路有说明，但代码中宏定义过多，影响代码可读性，且时间复杂度分析不准确。
- **DaiRuiChen007（3星）**：思路详细，代码使用了向量和函数封装，结构较为清晰，但部分函数的实现可以进一步优化。
- **snnu_lgw（3星）**：思路和代码都比较清晰，逻辑完整，但代码中部分变量命名可以更具描述性。
- **OranJun（2星）**：思路复杂，分类讨论较多，代码可读性较差，且部分逻辑存在问题。

由于所有题解均不足4星，故给出通用建议与扩展思路：
- **通用建议**：在实现过程中，注意变量命名的规范性和代码的可读性，避免使用过多复杂的宏定义和嵌套循环。同时，要准确分析时间复杂度，确保算法的效率。
- **扩展思路**：对于此类构造字符串的问题，可以进一步考虑优化枚举过程，减少不必要的计算。例如，可以使用更高效的数据结构来记录字符计数，或者提前剪枝，排除不可能的情况。

### 重点代码及核心实现思想
以下是 little_sun 的代码片段及核心实现思想：
```cpp
// 核心思想：先特判 n 不能被 k 整除的情况，然后判断原字符串是否本身就是美丽字符串。
// 若不是，则从后往前枚举第一个比原字符串大的位置，尝试在该位置替换合适的字符，
// 并计算后面的空位是否能补足所有字母的需求，最后构造出满足条件的字符串。
for (int i = n; i; i--)
{
    int num = 0;
    cnt[s[i] - 'a']--;            
    if (s[i] == 'z') continue;
    for (int l = s[i] - 'a' + 1; l < 26; l++)
    {
        cnt[l]++, num = 0;
        for (int j = 0; j < 26; j++)
           num += k * ((cnt[j] / k) + ((cnt[j] % k) != 0)) - cnt[j];
        if (num <= n - i)
        {
            ans = i, spos = l;
            break;
        }
        cnt[l]--;
    }
    if (ans == i) break;
}
memset(cnt, 0, sizeof(cnt));
for (int i = 1; i < ans; i++)
    t[i] = s[i], cnt[t[i] - 'a']++;
t[ans] = spos + 'a', cnt[t[ans] - 'a']++;
int pos = ans + 1, sum = 0;
for (int i = 0; i < 26; i++)
    cnt[i] = k * ((cnt[i] / k) + ((cnt[i] % k) != 0)) - cnt[i], sum += cnt[i];
while (sum + ans < n)
    sum += k, cnt[0] += k;
for (int i = 0; i < 26; i++)
    for (int j = 0; j < cnt[i]; j++)
        t[pos] = i + 'a', ++pos;
```

### 拓展同类型题或类似算法套路
同类型题可能会改变字符串的条件或要求，例如要求构造满足某种特定模式的字符串，或者在构造过程中加入更多的限制条件。类似的算法套路包括从后往前枚举、贪心选择、检查剩余条件是否满足等。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理和简单的构造。
2. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要构造满足回文和质数条件的数字。
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：主要考察字符串的匹配和计数。

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：53.56秒