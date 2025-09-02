# 题目信息

# Balance Addicts

## 题目描述

Given an integer sequence $a_1, a_2, \dots, a_n$ of length $n$, your task is to compute the number, modulo $998244353$, of ways to partition it into several **non-empty** **continuous** subsequences such that the sums of elements in the subsequences form a **balanced** sequence.

A sequence $s_1, s_2, \dots, s_k$ of length $k$ is said to be balanced, if $s_{i} = s_{k-i+1}$ for every $1 \leq i \leq k$. For example, $[1, 2, 3, 2, 1]$ and $[1,3,3,1]$ are balanced, but $[1,5,15]$ is not.

Formally, every partition can be described by a sequence of indexes $i_1, i_2, \dots, i_k$ of length $k$ with $1 = i_1 < i_2 < \dots < i_k \leq n$ such that

1.  $k$ is the number of non-empty continuous subsequences in the partition;
2.  For every $1 \leq j \leq k$, the $j$\-th continuous subsequence starts with $a_{i_j}$, and ends exactly before $a_{i_{j+1}}$, where $i_{k+1} = n + 1$. That is, the $j$\-th subsequence is $a_{i_j}, a_{i_j+1}, \dots, a_{i_{j+1}-1}$.

There are $2^{n-1}$ different partitions in total.

Let $s_1, s_2, \dots, s_k$ denote the sums of elements in the subsequences with respect to the partition $i_1, i_2, \dots, i_k$. Formally, for every $1 \leq j \leq k$,

$$
s_j = \sum_{i=i_{j}}^{i_{j+1}-1} a_i = a_{i_j} + a_{i_j+1} + \dots + a_{i_{j+1}-1}. 
$$
 For example, the partition $[1\,|\,2,3\,|\,4,5,6]$ of sequence $[1,2,3,4,5,6]$ is described by the sequence $[1,2,4]$ of indexes, and the sums of elements in the subsequences with respect to the partition is $[1,5,15]$.

Two partitions $i_1, i_2, \dots, i_k$ and $i'_1, i'_2, \dots, i'_{k'}$ (described by sequences of indexes) are considered to be different, if at least one of the following holds.

-   $k \neq k'$,
-   $i_j \neq i'_j$ for some $1 \leq j \leq \min\left\{ k, k' \right\}$.


## 说明/提示

For the first test case, there is only one way to partition a sequence of length $ 1 $ , which is itself and is, of course, balanced.

For the second test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 1] $ itself, then $ s = [2] $ is balanced;
- Partition into two subsequences $ [1\,|\,1] $ , then $ s = [1, 1] $ is balanced.

For the third test case, there are $ 3 $ ways to partition it:

- The sequence $ [0, 0, 1, 0] $ itself, then $ s = [1] $ is balanced;
- $ [0 \,|\, 0, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced;
- $ [0, 0 \,|\, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced.

For the fourth test case, there are $ 4 $ ways to partition it:

- The sequence $ [1, 2, 3, 2, 1] $ itself, then $ s = [9] $ is balanced;
- $ [1, 2 \,|\, 3 \,|\, 2, 1] $ , then $ s = [3, 3, 3] $ is balanced;
- $ [1 \,|\, 2, 3, 2 \,|\, 1] $ , then $ s = [1, 7, 1] $ is balanced;
- $ [1 \,|\, 2 \,|\, 3 \,|\, 2 \,|\, 1] $ , then $ s = [1, 2, 3, 2, 1] $ is balanced.

For the fifth test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 3, 5, 7, 9] $ itself, then $ s = [25] $ is balanced;
- $ [1, 3, 5 \,|\, 7 \,|\, 9] $ , then $ s = [9, 7, 9] $ is balanced.

For the sixth test case, every possible partition should be counted. So the answer is $ 2^{32-1} \equiv 150994942 \pmod {998244353} $ .

## 样例 #1

### 输入

```
6
1
1000000000
2
1 1
4
0 0 1 0
5
1 2 3 2 1
5
1 3 5 7 9
32
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
1
2
3
4
2
150994942```

# AI分析结果



**唯一算法分类**: 组合数学

---

### 综合分析与结论

**核心思路**  
问题转化为利用前缀和与后缀和的对称性构造回文序列，通过组合数学计算合法分割方案数。关键点如下：
1. 前缀和 $pre_i$ 和后缀和 $suf_i$ 的对称关系 $pre_i + suf_j = S_n$（总和的充要条件）。
2. 对于每对相等的前缀和 $x$ 和后缀和 $S_n - x$，统计其出现的连续区间长度 $cnt(x)$ 和 $cnt(S_n - x)$，计算组合数乘积。
3. 当 $S_n$ 为偶数时，中间段 $x = S_n/2$ 需额外乘 $2^{cnt(x)}$。

**解决难点**  
- **对称性处理**：利用双指针从两端向中间扫描，快速匹配 $pre_i$ 和 $suf_j$ 的相等值。
- **组合数优化**：通过预处理阶乘和逆元快速计算组合数，利用范德蒙德卷积简化 $\sum \binom{a}{k} \binom{b}{k} = \binom{a+b}{a}$。
- **边界处理**：当 $pre$ 和 $suf$ 的匹配区间重叠时，需特殊处理中间段的贡献。

**可视化设计**  
1. **动画流程**：
   - 用**红色方块**标记前缀和 $pre_i$，**蓝色方块**标记后缀和 $suf_j$。
   - 双指针 $i$ 和 $j$ 从两端向中间移动，当 $pre_i = suf_j$ 时高亮这两个方块并触发音效。
   - 显示当前匹配区间的长度 $[l_p, r_p]$ 和 $[l_s, r_s]$，并动态计算组合数贡献。
2. **复古像素风格**：
   - 使用 8 位像素字体显示组合数公式 $\binom{a+b}{a}$。
   - 背景音乐为循环的 8 位芯片音乐，成功匹配时播放上扬音效。
3. **自动推导模式**：
   - 展示双指针移动和区间匹配的自动过程，用户可暂停观察当前状态。
   - 在 Canvas 上用网格绘制前缀和和后缀和的分布，匹配时连接对应位置。

---

### 题解清单 (4星及以上)

1. **TKXZ133（5星）**  
   - **亮点**：公式推导严谨，利用范德蒙德卷积优化组合数求和，代码简洁高效。
   - **关键代码**：
     ```cpp
     for (int i = 1; i < n; i ++) mp[sum[i]] ++;
     while (sum[pos] * 2 < sum[n]) {
         ans = ans * C(mp[sum[pos]] + mp[sum[n] - sum[pos]], mp[sum[pos]]) % mod;
         pos ++;
     }
     if (sum[n] % 2 == 0) ans = ans * q_pow(2, mp[sum[n] / 2]) % mod;
     ```

2. **Alex_Wei（4星）**  
   - **亮点**：双指针实现清晰，独立处理每对区间，时间复杂度严格线性。
   - **关键代码**：
     ```cpp
     for (int l = 1, r = n - 1; l <= r;) {
         // 匹配 pre[l] 和 suf[r]，计算区间贡献
         ans = ans * sum_combinations % mod;
     }
     ```

3. **elbissoPtImaerD（4星）**  
   - **亮点**：极简双指针逻辑，直接枚举断点数量，适合教学演示。
   - **关键代码**：
     ```cpp
     for (re int k=0; k<=std::min(len[0], len[1]); ++k)
         s += C(len[0],k) * C(len[1],k);
     ```

---

### 最优思路与代码实现

**核心公式推导**  
对于每对 $x$ 和 $S_n - x$，贡献为 $\binom{cnt(x) + cnt(S_n - x)}{cnt(x)}$，总答案为各对贡献乘积。当 $x = S_n/2$ 时额外乘 $2^{cnt(x)}$。

**代码片段**  
预处理组合数并计算贡献：
```cpp
// 预处理阶乘和逆元
fac[0] = 1;
for (int i = 1; i <= L; i++) fac[i] = fac[i-1] * i % mod;
inv[L] = q_pow(fac[L], mod-2);
for (int i = L; i >= 1; i--) inv[i-1] = inv[i] * i % mod;

// 计算组合数 C(n, m)
int C(int n, int m) {
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}

// 主逻辑
map<int, int> mp;
for (int i = 1; i < n; i++) mp[sum[i]]++;
int ans = 1, pos = 1;
while (sum[pos] * 2 < sum[n]) {
    int x = sum[pos];
    ans = ans * C(mp[x] + mp[sum[n]-x], mp[x]) % mod;
    pos++;
}
if (sum[n] % 2 == 0) 
    ans = ans * q_pow(2, mp[sum[n]/2]) % mod;
```

---

### 相似题目推荐

1. **CF1770C** - 利用前缀和与组合数统计合法子数组。
2. **洛谷 P2679** - 子串计数，涉及对称性分割与组合数学。
3. **洛谷 P2513** - 逆序对与回文序列的组合优化。

---

### 个人心得摘录

- **TKXZ133**：在调试中发现未处理 $S_n$ 为偶数的中间段，导致 WA 后修正。
- **Alex_Wei**：通过将问题抽象为双指针匹配区间，避免了复杂的边界讨论。
- **ifffer_2137**：初始代码未处理区间重叠情况，补充后 AC。

---

### 复古游戏化动画代码片段

```javascript
// Canvas 初始化与像素绘制
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
ctx.imageSmoothingEnabled = false; // 保持像素风格

// 绘制前缀和方块
function drawPreSums() {
    for (let i = 0; i < n; i++) {
        ctx.fillStyle = preColors[i];
        ctx.fillRect(i * 10, 50, 8, 8); // 10x10 像素方块
    }
}

// 音效触发（使用 Web Audio API）
function playSound(freq) {
    const osc = audioCtx.createOscillator();
    osc.frequency.value = freq;
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(0.1);
}

// 自动推导模式
function autoSolve() {
    let l = 0, r = n - 1;
    while (l <= r) {
        if (pre[l] === suf[r]) {
            playSound(880); // 匹配成功音效
            highlightMatch(l, r);
            l++; r--;
        } else if (pre[l] < suf[r]) l++;
        else r--;
    }
}
```

---
处理用时：79.27秒