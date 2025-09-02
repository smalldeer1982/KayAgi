# 题目信息

# Spy-string

## 题目描述

You are given $ n $ strings $ a_1, a_2, \ldots, a_n $ : all of them have the same length $ m $ . The strings consist of lowercase English letters.

Find any string $ s $ of length $ m $ such that each of the given $ n $ strings differs from $ s $ in at most one position. Formally, for each given string $ a_i $ , there is no more than one position $ j $ such that $ a_i[j] \ne s[j] $ .

Note that the desired string $ s $ may be equal to one of the given strings $ a_i $ , or it may differ from all the given strings.

For example, if you have the strings abac and zbab, then the answer to the problem might be the string abab, which differs from the first only by the last character, and from the second only by the first.

## 说明/提示

The first test case was explained in the statement.

In the second test case, the answer does not exist.

## 样例 #1

### 输入

```
5
2 4
abac
zbab
2 4
aaaa
bbbb
3 3
baa
aaa
aab
2 2
ab
bb
3 1
a
b
c```

### 输出

```
abab
-1
aaa
ab
z```

# AI分析结果

### 题目翻译

#### Spy-string

**题目描述**

给定 $n$ 个长度为 $m$ 的字符串 $a_1, a_2, \ldots, a_n$，所有字符串都由小写英文字母组成。

请找到一个长度为 $m$ 的字符串 $s$，使得每个给定的字符串与 $s$ 在最多一个位置上不同。形式化地说，对于每个给定的字符串 $a_i$，最多存在一个位置 $j$ 使得 $a_i[j] \ne s[j]$。

注意，所求的字符串 $s$ 可能与给定的某个字符串 $a_i$ 相同，也可能与所有给定的字符串都不同。

例如，如果有字符串 `abac` 和 `zbab`，那么答案可能是字符串 `abab`，它与第一个字符串仅在最后一个字符不同，与第二个字符串仅在第一个字符不同。

**说明/提示**

第一个测试用例已在题目描述中解释。

在第二个测试用例中，答案不存在。

**样例 #1**

**输入**

```
5
2 4
abac
zbab
2 4
aaaa
bbbb
3 3
baa
aaa
aab
2 2
ab
bb
3 1
a
b
c
```

**输出**

```
abab
-1
aaa
ab
z
```

### 算法分类
枚举

### 题解分析与结论

本题的核心思路是通过枚举所有可能的字符串，检查其是否满足与所有给定字符串的差异不超过一个字符的条件。由于数据范围较小（$n \leq 10$, $m \leq 10$），暴力枚举是可行的。

#### 题解对比

1. **Warriors_Cat** 的题解：
   - **思路**：直接枚举第一个字符串的所有可能修改，然后检查是否满足条件。
   - **优点**：代码简洁，思路清晰，直接暴力枚举。
   - **缺点**：没有进一步优化，时间复杂度较高。
   - **评分**：4星

2. **_•́へ•́╬_** 的题解：
   - **思路**：先尝试不修改第一个字符串，再尝试修改第一个字符串的每个字符。
   - **优点**：思路清晰，代码实现简单。
   - **缺点**：同样没有进一步优化。
   - **评分**：4星

3. **sxshm** 的题解：
   - **思路**：暴力枚举第一个字符串的所有可能修改，然后检查是否满足条件。
   - **优点**：代码简洁，思路清晰。
   - **缺点**：没有进一步优化。
   - **评分**：4星

### 最优关键思路

1. **暴力枚举**：由于数据范围较小，直接枚举第一个字符串的所有可能修改，然后检查是否满足条件。
2. **优化思路**：可以考虑提前剪枝，如果在某个位置修改后已经无法满足条件，则直接跳过后续的枚举。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)

### 个人心得
- **调试经历**：在暴力枚举时，注意边界条件和字符串的索引，避免越界。
- **顿悟感想**：对于小数据范围的题目，暴力枚举往往是最直接有效的解决方案。

### 核心代码片段

```cpp
bool check(string ans){
    for(int i = 2; i <= n; ++i){
        int cnt = 0;
        for(int j = 1; j <= m; ++j){
            if(ans[j] != s[i][j]) cnt++;
        }
        if(cnt > 1) return 0;
    }
    return 1;
}
```

该函数用于检查一个字符串是否满足与所有给定字符串的差异不超过一个字符的条件。

---
处理用时：27.20秒