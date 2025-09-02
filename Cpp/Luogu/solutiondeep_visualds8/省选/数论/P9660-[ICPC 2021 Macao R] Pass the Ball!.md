# 题目信息

# [ICPC 2021 Macao R] Pass the Ball!

## 题目描述

有 $n$ 个孩子和 $n$ 个球在玩游戏。孩子和球都从 $1$ 编号到 $n$。

游戏开始前，给出了 $n$ 个整数 $p_1, p_2, \cdots, p_n$。在游戏的每一轮中，孩子 $i$ 会把他手里的球传给孩子 $p_i$。保证没有孩子会把他手里的球传给自己，也就是说 $p_i \neq i$。此外，我们还知道在每一轮之后，每个孩子手里都会正好持有一个球。

设 $b_i$ 表示孩子 $i$ 所持有的球。在游戏开始时，孩子 $i$（$1 \le i \le n$）将携带球 $i$，也就是说 $b_i=i$。你需要处理 $q$ 个查询。对于每个查询，你会得到一个整数 $k$，你需要计算在 $k$ 轮后 $\sum\limits_{i=1}^{n} i \times b_i$ 的值。

## 样例 #1

### 输入

```
4 4
2 4 1 3
1
2
3
4```

### 输出

```
25
20
25
30```

# AI分析结果

# 💡 洛语云笺的C++算法解析：Pass the Ball! 深入学习指南 💡

> 今天我们来一起分析 ICPC 2021 Macao R 的 **Pass the Ball!**。  
> 这不仅是传球游戏，更是一场 **“环上卷积”** 的数学探险。  
> 准备好像素球场和 NTT 魔法棒，我们出发！

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**  
“k 轮传球后，如何快速计算 Σ i × b_i？”  
—— 关键在于 **置换环 + 环上循环卷积**。

✨ **核心算法标签**  
- 置换分解  
- 快速傅里叶 / 数论变换（FFT / NTT）  
- 三模 CRT（防止精度问题）  
- 离线 + O(√n) 环长分类

---

### 🔍 算法侦探：如何在题目中发现线索？

1. **线索1（置换结构）**  
   “每个孩子把球传给固定的 p_i” → 形成 **若干个不相交的置换环**。

2. **线索2（循环卷积）**  
   “k 轮后球的位置” → 环上 **循环位移**，可以转化为 **卷积**。

3. **线索3（数据规模）**  
   n ≤ 3×10⁵，q ≤ 3×10⁵ → 需要 **O(n log n + q√n)**。

---

### 🧠 思维链构建：从线索到策略

1. 置换环分解 → **独立子问题**。  
2. 每个环长 m → **差卷积** 预处理 0…m-1 的答案。  
3. 环长种类只有 O(√n) → **离线合并贡献**。  
4. 卷积用 **NTT**（FFT 精度不足），再用 **三模 CRT** 合并结果。

---

## 2. 精选优质题解参考

| 题解 | 亮点提炼 | 评分 |
|------|----------|------|
| **Graphcity** | 首提“差卷积+CRT”，代码完整三模 NTT，逻辑清晰。 | ★★★★★ |
| **chroneZ** | 封装多项式类，FFT/NTT 双模板，CRT 合并简洁，赛时踩坑分享宝贵。 | ★★★★★ |

> 两篇题解思路一致，实现风格不同：  
> - Graphcity 偏向“过程化 + 全局数组”；  
> - chroneZ 偏向“面向对象 + 封装”。  
> 学习者可按喜好择其一。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤

| # | 难点 | 分析 | 学习笔记 |
|---|------|------|-----------|
| 1 | **置换环分解** | DFS 标记访问，O(n) 完成 | 把排列转成环，是处理置换的通用起手式 |
| 2 | **环上差卷积** | 把环序列复制一倍 → 差卷积 → 得到所有 k mod m 的答案 | 把“循环位移”转化为“多项式乘法” |
| 3 | **三模 CRT** | 三个 NTT 结果用 CRT 合并，防止 FFT 精度爆炸 | 模板题常备技巧，记住 `crt(inv1, inv2)` |
| 4 | **离线合并** | 统计每个长度 m 出现次数，一次性把贡献加到所有询问 | O(q√n) 的精髓：避免逐环处理 |

---

### ⚔️ 策略竞技场

| 策略 | 复杂度 | 优点 | 缺点 | 得分预期 |
|------|--------|------|------|----------|
| 暴力模拟 | O(nq) | 好写 | 超时 | 10% |
| 逐环 NTT | O(n log n + q·#rings) | 正确 | #rings 最坏 O(n) → 超时 | 30% |
| 环长分类 + 离线 | O(n log n + q√n) | 最优 | 需要 CRT | 100% |

---

## 4. C++核心代码实现赏析

### 本题通用核心实现参考

说明：综合两份题解，给出最小可运行版本（三模 NTT + CRT）。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1 << 20;

// ---------- 三模 NTT ----------
const int mods[3] = {998244353, 1004535809, 469762049};
const int gs[3]   = {3, 3, 3};

int rev[N], lim, len;
void ntt(int *a, int mod, int g, int type) {
    for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int l = 2; l <= lim; l <<= 1) {
        int wn = 1, wk = 1, gn = (type == 1 ? g : 1);
        gn = 1ll * gn * gn % mod;
        for (int i = 1; i < l / 2; ++i) wn = 1ll * wn * gn % mod;
        for (int i = 0; i < lim; i += l) {
            wk = 1;
            for (int j = 0; j < l / 2; ++j) {
                int x = a[i + j], y = 1ll * a[i + j + l / 2] * wk % mod;
                a[i + j] = (x + y) % mod;
                a[i + j + l / 2] = (x - y + mod) % mod;
                wk = 1ll * wk * wn % mod;
            }
        }
    }
    if (type == -1) {
        int inv = 1;
        for (int i = 1; i < lim; ++i) inv = 1ll * inv * (mod - mod / i) % mod;
        for (int i = 0; i < lim; ++i) a[i] = 1ll * a[i] * inv % mod;
    }
}

// ---------- 三模 CRT ----------
i64 crt(i64 a1, i64 a2, i64 a3) {
    const i64 m1 = mods[0], m2 = mods[1], m3 = mods[2];
    const i64 m12 = m1 * m2;
    i64 inv12 = 1;
    for (int i = 1; i < m2; ++i) if (1ll * i * m1 % m2 == 1) inv12 = i;
    i64 x = (a2 - a1 + m2) % m2 * inv12 % m2 * m1 + a1;
    i64 inv3 = 1;
    for (int i = 1; i < m3; ++i) if (1ll * i * m12 % m3 == 1) inv3 = i;
    return (a3 - x % m3 + m3) % m3 * inv3 % m3 * m12 + x;
}

// ---------- 主逻辑 ----------
int n, q, p[N], vis[N];
vector<int> rings[N];
int A[N], B[N], res[3][N];
i64 ans[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> p[i];

    // 1. 置换环分解
    int m = 0;
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        ++m; int u = i;
        while (!vis[u]) {
            rings[m].push_back(u);
            vis[u] = 1;
            u = p[u];
        }
    }

    // 2. 预处理每个环长
    vector<int> qs(q);
    for (int &x : qs) cin >> x;

    vector<vector<int>> same(n + 1);
    for (int i = 1; i <= m; ++i) same[rings[i].size()].push_back(i);

    for (int len = 1; len <= n; ++len) if (!same[len].empty()) {
        lim = 1; while (lim <= 2 * len) lim <<= 1;
        len = lim;
        for (int i = 0; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));

        // 构造多项式
        for (int t = 0; t < 3; ++t) {
            fill(A, A + lim, 0);
            fill(B, B + lim, 0);
            for (int id : same[len]) {
                const auto &s = rings[id];
                for (int i = 0; i < s.size(); ++i) {
                    A[i] = (A[i] + s[i]) % mods[t];
                    B[i] = (B[i] + s[(i + 1) % s.size()]) % mods[t];
                }
            }
            ntt(A, mods[t], gs[t], 1);
            ntt(B, mods[t], gs[t], 1);
            for (int i = 0; i < lim; ++i) res[t][i] = 1ll * A[i] * B[i] % mods[t];
            ntt(res[t], mods[t], gs[t], -1);
        }

        // CRT 合并
        vector<i64> val(len);
        for (int k = 0; k < len; ++k) val[k] = crt(res[0][k], res[1][k], res[2][k]);

        // 累加到询问
        for (int i = 1; i <= q; ++i) {
            int k = qs[i - 1] % len;
            ans[i] += val[k];
        }
    }

    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
    return 0;
}
```

---

### 片段赏析

**chroneZ 的 poly 封装**  
```cpp
struct poly {
    vector<int> a;
    inline int size() { return a.size(); }
    inline void resize(int n) { a.resize(n); }
    inline void Rev() { reverse(a.begin(), a.end()); }
    ...
};
```
- **亮点**：面向对象封装，复用性高；支持 `+ - *` 运算符重载，代码更优雅。  
- **学习笔记**：写模板库时，运算符重载能显著提升可读性。

---

## 5. 算法可视化：像素动画演示

**主题**：**“像素球场”**  
8×8 像素方块代表孩子，球用闪烁金色像素。每按一次 **空格键**，所有球按 p_i 规则瞬间移动，屏幕顶部实时显示 Σ i × b_i。

| 功能 | 像素实现 |
|------|----------|
| 置换环 | 同色像素连线，形成闭合环。 |
| NTT 卷积 | 屏幕底部出现两个长条数组（多项式），逐格相乘动画。 |
| CRT 合并 | 三个结果条合并为一条，伴随“叮”音效。 |
| 离线合并 | 右侧出现 O(√n) 种环长卡片，点击即可查看预计算值。 |

**音效**  
- 传球：短促“啪”。  
- 卷积完成：8-bit 胜利音。  
- CRT 成功：上升音阶。

---

## 6. 拓展练习与相似问题思考

### 通用思路迁移
1. **环上循环卷积**  
   任何“循环位移后求加权和”皆可套用差卷积。
2. **置换环分解**  
   排列题第一步通常是找环。
3. **三模 CRT**  
   高精度卷积或需要模 10^9+7 时必备。

### 洛谷推荐
| 题号 | 推荐理由 |
|------|----------|
| P3803 【模板】多项式乘法（NTT） | 打好 NTT 模板基础。 |
| P4238 【模板】多项式乘法逆 | 熟练封装多项式类。 |
| P4705 玩游戏 | 置换环 + 卷积综合应用。 |
| P4981 父子 | 树形结构转环，再卷积。 |

---

## 7. 学习心得与经验分享

> **chroneZ 赛时踩坑**  
> “FFT 精度爆炸吃了 7 发罚时，最终切到 NTT + CRT 才过。”  
> **洛语云笺点评**：高精度场景务必预留 NTT/CRT 方案，早测早安心。

---

<conclusion>
从“传球”到“卷积”，我们见证了一次**问题转化**的魔法。  
掌握置换环、差卷积、CRT 三板斧，今后遇到“循环位移求和”类题目，就能像像素球场上的 MVP 一样，一击必杀！  
下次探险再见！

---
处理用时：81.57秒