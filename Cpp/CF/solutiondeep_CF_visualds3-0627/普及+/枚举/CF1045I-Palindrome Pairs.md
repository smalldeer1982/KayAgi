# 题目信息

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出

```
6
```

# AI分析结果



## 唯一算法分类
哈希表 + 位运算

---

## 题解思路与难点分析

### 核心算法流程
1. **二进制掩码**：将每个字符串转化为 26 位二进制数，记录每个字符出现次数的奇偶性（奇数次为 1，偶数次为 0）。
2. **哈希表动态维护**：遍历每个字符串时，利用哈希表记录已处理字符串的掩码出现次数。
3. **条件匹配**：对于当前掩码，检查哈希表中是否存在以下两种情况的掩码：
   - **完全相同**（异或结果为 0，所有字符总出现次数为偶数）。
   - **仅某一位不同**（异或结果仅有一位为 1，允许一个字符出现奇数次）。

### 解决难点
- **高效查询**：通过哈希表（`unordered_map`）实现 O(1) 的查询复杂度，避免暴力枚举所有可能的字符串对。
- **去重处理**：动态维护哈希表（仅记录已处理的字符串），保证每对字符串只计算一次。

### 可视化设计思路
- **掩码动画**：以 8 位像素风格显示每个字符串的二进制掩码，用绿色表示 0，红色表示 1。
- **哈希表更新**：用网格展示哈希表内容，当前处理的掩码高亮显示。
- **交互反馈**：匹配成功时播放“成功音效”，并在右侧面板显示累计结果。

---

## 题解评分（≥4星）
1. **yijan（5星）**  
   - **亮点**：动态维护哈希表，时间复杂度 O(n·26)，代码简洁高效。
   - **代码片段**：
     ```cpp
     for (ll i=0; i<n; ++i) {
         res += S[num[i]]; // 完全相同的掩码
         for (ll j=0; j<26; ++j)
             if ((num[i] >> j) & 1) 
                 res += S[num[i] ^ (1 << j)]; // 某一位不同的掩码
         ++S[num[i]]; // 更新哈希表
     }
     ```

2. **mrsrz（5星）**  
   - **亮点**：代码极简，逻辑清晰，直接使用 `map` 替代排序。
   - **代码片段**：
     ```cpp
     for (int i=2; i<=n; ++i) {
         ans += b[a[i]]; // 完全相同的掩码
         for (int j=0; j<26; ++j)
             ans += b[a[i] ^ (1 << j)]; // 某一位不同的掩码
         ++b[a[i]]; // 更新哈希表
     }
     ```

3. **HomuraCat（4星）**  
   - **亮点**：排序后二分查找，避免哈希表空间问题，但时间复杂度稍高（O(n·26 log n)）。
   - **代码片段**：
     ```cpp
     std::sort(u + 1, u + n + 1);
     for (int i=1; i<=n; ++i) {
         ans += upper_bound(..) - lower_bound(..) - 1; // 完全相同
         for (int j=0; j<26; ++j)
             ans += upper_bound(..) - lower_bound(..); // 某一位不同
     }
     ans >>= 1; // 去重
     ```

---

## 最优思路提炼
- **关键技巧**：将字符串转化为二进制掩码，利用异或运算快速判断回文条件。
- **优化核心**：动态维护哈希表，确保每对字符串仅计算一次。
- **思维角度**：将字符奇偶性抽象为位运算问题，降低时间复杂度至 O(n·26)。

---

## 类似题目推荐
1. **[CF888G](https://codeforces.com/problemset/problem/888/G)**：利用二进制掩码和 Trie 树求最小异或对。
2. **[LeetCode 136. Single Number](https://leetcode.com/problems/single-number/)**：位运算判断唯一奇数次出现的元素。
3. **[洛谷 P1469](https://www.luogu.com.cn/problem/P1469)**：利用异或性质找筷子配对问题。

---

## 可视化与交互设计
### 算法动画方案
- **掩码生成**：以 8x4 像素块表示 26 位掩码，每块颜色表示 0/1。
- **哈希表交互**：点击当前掩码时，高亮其对应的哈希表条目。
- **音效反馈**：匹配成功时播放 8-bit 风格音效，背景音乐循环播放复古芯片音。

### 复古游戏化设计
- **像素风格**：掩码以 FC 红白机风格渲染，哈希表条目以网格展示。
- **自动演示模式**：模拟“贪吃蛇 AI”逐步处理字符串，按空格键暂停/继续。
- **积分系统**：每成功匹配一对得 10 分，连续匹配触发连击特效。

---

## 代码实现（核心逻辑）
```cpp
#include <unordered_map>
using namespace std;

int main() {
    int n; 
    unordered_map<int, int> mask_count;
    long long ans = 0;
    // 处理每个字符串
    for (int i = 0; i < n; ++i) {
        int mask = compute_mask(s[i]); // 生成掩码
        ans += mask_count[mask];       // 完全匹配
        for (int j = 0; j < 26; ++j)  // 枚举每一位
            ans += mask_count[mask ^ (1 << j)];
        mask_count[mask]++;            // 更新哈希表
    }
    cout << ans;
}
```

---
处理用时：352.74秒