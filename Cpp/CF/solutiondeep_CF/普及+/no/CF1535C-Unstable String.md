# 题目信息

# Unstable String

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1, and ?.

Let's call a string unstable if it consists of the characters 0 and 1 and any two adjacent characters are different (i. e. it has the form 010101... or 101010...).

Let's call a string beautiful if it consists of the characters 0, 1, and ?, and you can replace the characters ? to 0 or 1 (for each character, the choice is independent), so that the string becomes unstable.

For example, the strings 0??10, 0, and ??? are beautiful, and the strings 00 and ?1??1 are not.

Calculate the number of beautiful contiguous substrings of the string $ s $ .

## 样例 #1

### 输入

```
3
0?10
???
?10??1100```

### 输出

```
8
6
25```

# AI分析结果

### 题目翻译
## 不稳定字符串

### 题目描述
给定一个由字符 `0`、`1` 和 `?` 组成的字符串 $s$。

如果一个字符串仅由字符 `0` 和 `1` 组成，且任意两个相邻字符都不同（即它的形式为 `010101...` 或 `101010...`），则称该字符串是不稳定的。

如果一个字符串由字符 `0`、`1` 和 `?` 组成，并且你可以将字符 `?` 替换为 `0` 或 `1`（对于每个字符，选择是独立的），使得该字符串变为不稳定的，则称该字符串是美丽的。

例如，字符串 `0??10`、`0` 和 `???` 是美丽的，而字符串 `00` 和 `?1??1` 不是。

计算字符串 $s$ 中美丽的连续子串的数量。

### 样例 #1
#### 输入
```
3
0?10
???
?10??1100
```
#### 输出
```
8
6
25
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕计算给定字符串中美丽子串的数量展开。不同题解采用了不同的思路和算法：
- **动态规划类**：LinkZelda、StayAlone 两位作者的题解通过定义动态规划数组，根据当前字符的不同情况（`0`、`1`、`?`）更新状态，最后累加结果得到答案。
- **暴力枚举优化类**：HoshizoraZ 作者的题解通过改变枚举方式，确定左端点后找最大延伸长度来计算合法子串个数。
- **其他思路类**：Lynkcat 作者的题解通过维护特定位置信息来确定左端点范围；奥特战士作者的题解通过遍历字符串，处理相邻字符和问号的情况来统计子串个数；Create_Random 作者的题解采用正难则反的思路，统计非法情况来间接得到答案。

### 所选题解
- **LinkZelda（5星）**：
  - **关键亮点**：思路清晰，动态规划状态定义明确，代码复杂度低，时间复杂度为 $O(\vert s\vert)$。
  - **个人心得**：无
- **StayAlone（4星）**：
  - **关键亮点**：动态规划思路简单易懂，对边界情况和状态转移的解释详细，代码实现简洁。
  - **个人心得**：比赛时第一次交没把 `dp` 数组和 `ans` 开 `long long`，导致错误。

### 重点代码
#### LinkZelda 题解核心代码
```cpp
// 定义 dp 数组，dp[i][1/0] 表示第 i 位为 1/0 ，以 i 为结尾的极长不稳定子段长
int dp[maxn][2]; 
// 状态转移
if (s[i] == '1') dp[i][1] = dp[i - 1][0] + 1;
if (s[i] == '0') dp[i][0] = dp[i - 1][1] + 1;
if (s[i] == '?') {
    dp[i][1] = dp[i - 1][0] + 1;
    dp[i][0] = dp[i - 1][1] + 1;
}
// 计算答案
for (int i = 0; i < n; i++) ans += max(dp[i][0], dp[i][1]);
```
**核心实现思想**：根据当前字符的不同情况更新 `dp` 数组，最后累加每个位置的最大极长不稳定子段长得到答案。

#### StayAlone 题解核心代码
```cpp
ll dp[200010][2]; 
// 边界处理
if (s[0] != '?') dp[0][s[0] - '0'] = 1;
else dp[0][0] = dp[0][1] = 1;
// 状态转移
for (int i = 1; i < len; ++i) {
    if (s[i] != '?') dp[i][s[i] - '0'] = dp[i - 1][!(s[i] - '0')] + 1;
    else {
        dp[i][0] = dp[i - 1][1] + 1;
        dp[i][1] = dp[i - 1][0] + 1;
    }
}
// 计算答案
for (int i = 0; i < len; ++i) ans += max(dp[i][0], dp[i][1]);
```
**核心实现思想**：先处理边界情况，然后根据当前字符的不同情况更新 `dp` 数组，最后累加每个位置的最大合法子串数量得到答案。

### 最优关键思路或技巧
动态规划是解决本题的有效方法，通过定义合适的状态数组（如 `dp[i][0/1]` 表示以第 `i` 个位置为结尾，该位置为 `0` 或 `1` 的相关状态），根据当前字符的不同情况进行状态转移，能高效地计算出结果。

### 拓展思路
同类型题可能会对不稳定字符串的定义进行修改，或者增加更多的字符类型和规则。类似算法套路可以应用于其他字符串相关的动态规划问题，如计算满足特定条件的子序列数量等。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：39.58秒