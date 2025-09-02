# 题目信息

# Fixing a Binary String

## 题目描述

You are given a binary string $ s $ of length $ n $ , consisting of zeros and ones. You can perform the following operation exactly once:

1. Choose an integer $ p $ ( $ 1 \le p \le n $ ).
2. Reverse the substring $ s_1 s_2 \ldots s_p $ . After this step, the string $ s_1 s_2 \ldots s_n $ will become $ s_p s_{p-1} \ldots s_1 s_{p+1} s_{p+2} \ldots s_n $ .
3. Then, perform a cyclic shift of the string $ s $ to the left $ p $ times. After this step, the initial string $ s_1s_2 \ldots s_n $ will become $ s_{p+1}s_{p+2} \ldots s_n s_p s_{p-1} \ldots s_1 $ .

For example, if you apply the operation to the string 110001100110 with $ p=3 $ , after the second step, the string will become 011001100110, and after the third step, it will become 001100110011.

A string $ s $ is called  $ k $ -proper if two conditions are met:

- $ s_1=s_2=\ldots=s_k $ ;
- $ s_{i+k} \neq s_i $ for any $ i $ ( $ 1 \le i \le n - k $ ).

For example, with $ k=3 $ , the strings 000, 111000111, and 111000 are $ k $ -proper, while the strings 000000, 001100, and 1110000 are not.

You are given an integer $ k $ , which is a divisor of $ n $ . Find an integer $ p $ ( $ 1 \le p \le n $ ) such that after performing the operation, the string $ s $ becomes $ k $ -proper, or determine that it is impossible. Note that if the string is initially $ k $ -proper, you still need to apply exactly one operation to it.

## 说明/提示

In the first test case, if you apply the operation with $ p=3 $ , after the second step of the operation, the string becomes 11100001, and after the third step, it becomes 00001111. This string is $ 4 $ -proper.

In the second test case, it can be shown that there is no operation after which the string becomes $ 2 $ -proper.

In the third test case, if you apply the operation with $ p=7 $ , after the second step of the operation, the string becomes 100011100011, and after the third step, it becomes 000111000111. This string is $ 3 $ -proper.

In the fourth test case, after the operation with any $ p $ , the string becomes $ 5 $ -proper.

## 样例 #1

### 输入

```
7
8 4
11100001
4 2
1110
12 3
111000100011
5 5
00000
6 1
101001
8 4
01110001
12 2
110001100110```

### 输出

```
3
-1
7
5
4
-1
3```

# AI分析结果



# Fixing a Binary String（修复二进制字符串）

## 题目描述
给定一个长度为 $n$ 的二进制字符串 $s$，你可以执行以下操作恰好一次：
1. 选择整数 $p$（$1 \le p \le n$）
2. 反转前缀子串 $s_1s_2\ldots s_p$，此时字符串变为 $s_p s_{p-1} \ldots s_1 s_{p+1} \ldots s_n$
3. 将字符串循环左移 $p$ 次，最终字符串变为 $s_{p+1}s_{p+2}\ldots s_n s_p s_{p-1}\ldots s_1$

定义 $k$-proper 字符串需满足：
1. 前 $k$ 个字符相同
2. 对所有 $1 \le i \le n-k$，有 $s_{i+k} \neq s_i$

给定整除 $n$ 的整数 $k$，求能生成 $k$-proper 字符串的 $p$，若不存在输出 $-1$。

---

## 题解分析与结论

### 关键解题思路
所有题解核心围绕两种合法模式展开：
1. **模式构造**：合法串只能是 `k个0与k个1交替` 或 `k个1与k个0交替`
2. **哈希加速**：通过预处理前后缀哈希，快速计算操作后字符串的哈希值
3. **拼接验证**：操作后的字符串由原字符串后缀和反转前缀组成，哈希拼接公式为 $hash = hash_{suffix} \cdot B^p + hash_{reverse\_prefix}$

### 高星题解精选

#### 1. [Engulf] 哈希双模式匹配（⭐⭐⭐⭐⭐）
**核心亮点**：
- 预处理两种目标模式的完整哈希
- 利用反转后缀哈希快速计算操作后的哈希值
- 复杂度 $O(n)$，代码简洁高效
```cpp
// 预处理两种目标模式
for (int i = 1; i <= k; i++) v1[i] = '1', v2[i] = '0';
for (int i = k + 1; i <= n; i++) v1[i] = rev(v1[i - k]), v2[i] = rev(v2[i - k]);

// 计算操作后哈希
ull h = (pre[n] - pre[i] * pw[n - i]) * pw[i] + (suf[n] - suf[n - i] * pw[i]);
```

#### 2. [cjh20090318] 随机双哈希防碰撞（⭐⭐⭐⭐）
**关键技巧**：
- 使用随机选择的双底数自然溢出哈希
- 动态构造两种目标模式并哈希化
- 通过四维哈希降低碰撞概率
```cpp
// 随机选择哈希底数
p1=P[mtrd()%6]; do p2=P[mtrd()%6];while(p1==p2);

// 双模式哈希验证
if(qryl(hsl[0],pn1,p+1,n)==qryl(htl[0],pn1,1,n-p) 
 && qryr(hsr[0],pn1,1,p)==qryl(htl[0],pn1,n-p+1,n)){...}
```

#### 3. [Lu_xZ] 分段合法性检查（⭐⭐⭐⭐）
**创新点**：
- 预处理前缀合法性数组 `pre[]` 和后缀合法性数组 `suf[]`
- 仅在合法分段边界处进行验证
- 减少不必要的全串检查
```cpp
// 预处理合法性
for(int i=1;i<=n;i++) 
    pre[i] = pre[i-1] && (i<=k || s[i] != s[i-k]);

for(int i=n;i>=0;--i) 
    suf[i] = suf[i+1] && (i+k>n || s[i] != s[i+k]);
```

---

## 关键代码实现
Engulf 解法核心哈希计算：
```cpp
// 预处理幂次和哈希
for (int i = 1; i <= n; i++) {
    pre[i] = pre[i-1] * base + s[i];
    suf[i] = suf[i-1] * base + revs[i]; // revs是反转后的字符串
}

// 验证每个p的情况
for (int p = 1; p <= n; p++) {
    ull suffix_hash = pre[n] - pre[p] * pw[n-p];   // s[p+1..n]的哈希
    ull prefix_hash = suf[n] - suf[n-p] * pw[p];   // s[1..p]反转后的哈希
    ull total_hash = suffix_hash * pw[p] + prefix_hash;
    if (total_hash == target_hash) return p;
}
```

---

## 拓展与心得
**重要心得**：
- 哈希碰撞可通过随机底数+自然溢出组合规避（cjh20090318）
- 操作后的字符串结构固定，无需真正操作字符串（多篇题解）
- k-proper 的周期性特征决定只有两种可能模式

**同类题目推荐**：
1. [P3370] 字符串哈希（模板题）
2. [P1368] 最小表示法（循环移位相关）
3. [CF1200E] Compress Words（哈希拼接技巧）

**调试经验**：
- 样例4需注意原串已合法仍需操作（Engulf题解注释）
- 哈希幂次预处理要足够（ZhongYuLin线段树解法）
- 当k=n时特判全相同字符（Lu_xZ题解）

---
处理用时：61.67秒