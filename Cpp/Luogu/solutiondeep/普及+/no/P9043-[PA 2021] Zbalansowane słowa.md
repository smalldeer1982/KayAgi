# 题目信息

# [PA 2021] Zbalansowane słowa

## 题目描述

定义一个字符串 $s$ 是好的，当且仅当它包含的所有字符出现次数相同。

好的字符串例如：`mama`、`aabbcbcccbaa`。

不好的字符串例如：`ovo`。

给定一个字符串 $s$，求出 $s$ 好的**子串**数量。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq |s| \leq 3 \times 10^5$，$s$ 中只含 `a`、`b`、`c` 三个小写字母。

## 样例 #1

### 输入

```
aabbabcccba```

### 输出

```
28```

# AI分析结果

### 算法分类
前缀和

### 综合分析与结论
题目要求统计字符串中所有字符出现次数相同的子串数量。核心思路是利用前缀和来记录字符出现次数的差异，并通过哈希表或映射来快速统计符合条件的子串。难点在于如何处理多种字符的出现次数差异，并高效地枚举所有可能的子串。

### 所选题解
1. **作者：喵仔牛奶 (5星)**
   - **关键亮点**：通过维护前缀和和哈希表，实现了O(n·|Σ|)的时间复杂度，适用于字符集较大的情况。代码清晰，注释详细，优化程度高。
   - **核心代码**：
     ```cpp
     REP(i, 0, n) {
         if (i > 0) {
             ULL v = 0, w = 0, s = 0, c = 1e9;
             DEP(j, m - 1, 0) v = v * B + ct[i][j];
             for (int x : L[i]) {
                 if (x < c) v += s * (c < m ? ct[i][c] - ct[i][x] : 0), c = x;
                 v -= ct[i][c] * pw[x], s += pw[x], w |= 1 << x;
                 rs += S[v + w * pw[m]];
             }
         }
         ULL v = 0, w = 0, s = 0, c = 1e9;
         DEP(j, m - 1, 0) v = v * B + ct[i][j];
         for (int x : R[i + 1]) {
             if (x < c) v += s * (c < m ? ct[i][c] - ct[i][x] : 0), c = x;
             v -= ct[i][c] * pw[x], s += pw[x], w |= 1 << x;
             S[v + w * pw[m]] ++;
         }
     }
     ```
   - **个人心得**：通过固定最小字符来简化条件，避免了复杂的枚举过程。

2. **作者：modfisher (4星)**
   - **关键亮点**：分类讨论不同字符组合的情况，利用前缀和和映射来统计符合条件的子串。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for(ll i = 1; i <= n; i ++){
         if(i > 1 && s[i] != s[i - 1]){
             ans += (i - pre + 1) * (i - pre) / 2;
             pre = i;
         }
         if(s[i] == 'a') sa ++;
         else if(s[i] == 'b') sb ++;
         else sc ++;
         ans += mp[make_pair(sa - sb, sa - sc)] + mpa[make_pair(sb - sc, sa)] + mpb[make_pair(sa - sc, sb)] + mpc[make_pair(sa - sb, sc)];
         mp[make_pair(sa - sb, sa - sc)] ++, mpa[make_pair(sb - sc, sa)] ++, mpb[make_pair(sa - sc, sb)] ++, mpc[make_pair(sa - sb, sc)] ++;
     }
     ```
   - **个人心得**：通过分类处理不同字符组合，简化了问题复杂度。

### 最优关键思路
利用前缀和记录字符出现次数的差异，并通过哈希表或映射来快速统计符合条件的子串。固定最小字符来简化条件，避免复杂的枚举过程。

### 可拓展之处
类似的问题可以扩展到更大字符集或更复杂的条件，如字符出现次数的比例关系等。可以结合其他数据结构如树状数组或线段树来进一步优化。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】线段树 1](https://www.luogu.com.cn/problem/P3384)

---
处理用时：24.09秒