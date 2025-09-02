# 题目信息

# Division + LCP (easy version)

## 题目描述

This is the easy version of the problem. In this version $ l=r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots,w_k $ . Let $ f_k $ be the maximal possible $ LCP(w_1,\dots,w_k) $ among all divisions.

 $ LCP(w_1,\dots,w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots,w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l,f_{l+1},\dots,f_r $ . In this version $ l=r $ .

## 说明/提示

In the first sample $ n=k $ , so the only division of $ aba $ is $ \color{red}a\color{blue}b\color{orange}a $ . The answer is zero, because those strings do not have a common prefix.

In the second sample, the only division is $ \color{red}a\color{blue}a\color{orange}a $ . Their longest common prefix is one.

## 样例 #1

### 输入

```
7
3 3 3
aba
3 3 3
aaa
7 2 2
abacaba
9 4 4
abababcab
10 1 1
codeforces
9 3 3
abafababa
5 3 3
zpozp```

### 输出

```
0
1
3
2
10
2
0```

# AI分析结果



# Division + LCP (easy version)

## 题目描述

这是该问题的简单版本，在此版本中 $l=r$。

给定一个字符串 $s$。对于固定的 $k$，考虑将 $s$ 划分为恰好 $k$ 个连续子串 $w_1,\dots,w_k$。令 $f_k$ 表示所有划分中可能达到的最大 $LCP(w_1,\dots,w_k)$。

$LCP(w_1,\dots,w_m)$ 是字符串 $w_1,\dots,w_m$ 的最长公共前缀的长度。

例如，若 $s=abababcab$ 且 $k=4$，一种可能的划分为 $\color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab}$。此时 $LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab})$ 为 $2$，因为 $ab$ 是这四个字符串的最长公共前缀。注意每个子串必须是连续的字符段，且每个字符属于且仅属于一个子串。

你的任务是找到 $f_l,f_{l+1},\dots,f_r$。在此版本中 $l=r$。

---

## 题解综合分析

### 关键思路总结
1. **二分答案框架**：所有题解均采用二分法确定最长公共前缀长度，利用答案的单调性（更长的前缀出现次数必然更少）。
2. **字符串匹配优化**：主要分为两类实现方式：
   - **KMP 预处理**：通过构建模式串的 next 数组快速匹配不相交子串（如 Pursuewind、junee 解法）
   - **滚动哈希技术**：利用前缀哈希快速比较子串（如 I_will_AKIOI、DrAlfred 解法）
3. **不相交条件处理**：匹配成功后跳过后续字符（`i = i + len - 1`），保证子串不重叠。

### 最优技巧提炼
- **跳跃式贪心匹配**：当检测到合法子串时，直接跳到该子串末尾后继续匹配，保证不重叠且线性时间复杂度。
- **随机哈希基**：避免哈希碰撞的关键技巧，使用随机模数或大质数组合（如 DrAlfred 使用 Mersenne prime 2^61-1）。
- **KMP 状态重置**：匹配成功后重置指针（`j = 0` 或 `j = nxt[j]`），正确处理非重叠匹配。

---

## 精选题解（评分≥4星）

### 题解1：Pursuewind（⭐⭐⭐⭐⭐）
**亮点**：完整展示 KMP 实现细节，通过 next 数组处理重叠匹配，逻辑清晰  
**核心代码**：
```cpp
bool check(int mid) {
    int j = 0, cnt = 1;
    for (int i = mid + 1; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = nxt[j];
        if (s[i] == s[j + 1]) j++;
        if (j == mid) {
            cnt++, j = 0;
            if (cnt >= k) return true;
        }
    }
    return false;
}
```
**实现思想**：将前 mid 个字符作为模式串，用 KMP 扫描整个字符串统计非重叠出现次数。

### 题解2：DrAlfred（⭐⭐⭐⭐⭐）
**亮点**：模块化哈希类设计，采用大数模避免碰撞，代码复用性强  
**核心代码**：
```cpp
class HashedString {
    // 使用 2^61-1 作为模数，13331 为随机基
    i64 getHash(int l, int r) { 
        return (h[r] - h[l-1] * pow[r-l+1] % M + M) % M;
    }
};
bool check = [&](int len) {
    int cnt = 1;
    for (int i = len; i + len - 1 < n; i += len) 
        if (H.getHash(0, len-1) == H.getHash(i, i+len-1)) cnt++;
    return cnt >= k;
};
```
**实现思想**：预处理前缀哈希值，每次检查时跳跃式比较子串哈希值。

### 题解3：Starrykiller（⭐⭐⭐⭐）
**亮点**：简洁的贪心思路，直接使用 KMP 模板快速实现  
**核心思想**：将问题转化为模板串匹配问题，直接利用 KMP 的自动机特性统计非重叠出现次数。

---

## 拓展与举一反三

### 同类问题套路
1. **二分答案 + 字符串验证**：如 CF535D（统计模式串覆盖）、POJ 1743（最长重复子串）
2. **跳跃式贪心匹配**：适用于需要非重叠子串统计的场景（如 CF432D）
3. **哈希/KMP 的互换性**：根据题目需求选择预处理方式，KMP 适合精确匹配，哈希适合多模式查询

### 推荐练习题
1. [P3375 - KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)  
   **考察点**：KMP 基础实现与 next 数组应用
2. [P2922 - Secret Message 秘密信息](https://www.luogu.com.cn/problem/P2922)  
   **考察点**：前缀匹配与二分答案结合
3. [P2852 - 牛奶模式](https://www.luogu.com.cn/problem/P2852)  
   **考察点**：后缀数组求最长重复子串

---

## 题解心得摘录

### 调试经验
- **I_will_AKIOI**：_"哈希一定要随机模数！赛时没搞随机模数 FST 掉了 25 分"_  
  → **教训**：哈希题务必使用双模或大素数组合，避免被特殊数据卡哈希碰撞

### 算法选择
- **迟暮天复明**：_"楼上的老哥用 KMP 学魔怔了，直接哈希更直观"_  
  → **启示**：根据实现复杂度选择合适算法，简单场景哈希更易编写

### 边界处理
- **junee**：在 KMP 循环中设置 `if (l == 1) cout << n` 处理特例  
  → **技巧**：注意 k=1 时整个字符串即为前缀的特殊情况，避免无效计算

---
处理用时：68.35秒