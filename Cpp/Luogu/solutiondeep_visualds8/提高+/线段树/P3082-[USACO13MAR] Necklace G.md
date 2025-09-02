# 题目信息

# [USACO13MAR] Necklace G

## 题目描述

Bessie the cow has arranged a string of N rocks, each containing a single letter of the alphabet, that she wants to build into a fashionable necklace.

Being protective of her belongings, Bessie does not want to share her necklace with the other cow currently living on her side of the barn.  The other cow has a name that is a string of M characters, and Bessie wants to be sure that this length-M string does not occur as a contiguous substring anywhere within the string representing her necklace (otherwise, the other cow might mistakenly think the necklace is for her).  Bessie decides to remove some of the rocks in her necklace so that the other cow's name does not appear as a substring.  Please help Bessie determine the minimum number of rocks she must remove.

贝西收集了N颗石头，每颗石头上都有一个字母，贝西想把这些石头做成项链。

贝西的身边有另一只奶牛，这只奶牛的名字是一个长度为M的字符串，贝西不希望这只牛的名字出现在她的项链上(项链的子串)，她想知道，最少删掉几颗石头就可以避免这种情况发生。


## 说明/提示

```cpp
For at least 20% of test cases, N <= 20. 
For at least 60% of test cases, N <= 1000, M <= 100. 
For all test cases, N <= 10000, M <= 1000. 
For all test cases, M <= N. 
```
The modified necklace should be "abbaa".

---

$\text{upd 2022.7.29}$：新增加一组 Hack 数据。

## 样例 #1

### 输入

```
ababaa 
aba 
```

### 输出

```
1 
```

# AI分析结果

# 💡 洛语云笺的C++算法解析：[USACO13MAR] Necklace G 深入学习指南 💡  
> 今天我们来一起分析「Necklace G」这道字符串 DP 题。它看似只是“删掉几个字母”，背后却隐藏着「KMP × 动态规划」的精妙配合。跟着洛语云笺，一起拆解吧！

---

## 1. 题目解读与策略初探

### ✨ 核心挑战
> **在一条长为 N 的项链（字符串 S）里，最少删掉几颗石头，才能让另一只奶牛的名字 T 不再作为连续子串出现？**

### ✨ 算法标签
- 字符串匹配（KMP / AC 自动机）
- 线性动态规划（Linear DP）
- 状态压缩思想（用匹配长度做第二维）

### 🗣️ 思路概览
| 方法 | 思路一句话 | 复杂度 | 预期得分 |
| --- | --- | --- | --- |
| 暴力枚举子集 | 枚举删哪些字符，再检查是否含 T | O(2^N · M) | 10-20% |
| 纯 KMP 多次匹配 | 每删一个字符就重跑一次 KMP | O(N^2) | 40-50% |
| **KMP + DP** | **把“当前匹配到 T 的第几位”塞进状态里，一次线性递推** | **O(N·M)** | **100%** |

> 为什么 DP 可行？  
> 因为「删字符」具有**无后效性**：前面删哪些不影响后面决策，只关心「目前匹配到 T 的哪个位置」即可。

---

### 🔍 算法侦探：如何在题目中发现线索？
1. **线索1（目标）**：最小化删除数量 → 经典「最长保留」DP。
2. **线索2（约束）**：不能出现子串 T → 需要实时知道「离出现 T 还有多远」。
3. **线索3（数据）**：N ≤ 1e4，M ≤ 1e3 → O(N·M) ≈ 1e7 次运算，可过。

### 🧠 思维链构建：从线索到策略
> “我先想到暴力，但指数级肯定不行；  
> 接着想用 KMP，可每删一次就重跑太浪费；  
> 于是把 KMP 的‘失配指针’嵌进 DP 状态：  
> **f[i][j] = 处理完 S 前 i 位，当前后缀与 T 最长公共前缀长度为 j 时的最长保留长度**  
> 这样就把『匹配进度』压缩成了一个维度，线性递推即可。”

---

## 2. 精选优质题解参考

| 题解 | 亮点提炼 | 推荐指数 |
| --- | --- | --- |
| **¶凉笙** | 用 **AC 自动机** 统一处理多模式串思想，把 T 建成 trie 图，再跑 DP；代码简洁。 | ⭐⭐⭐⭐ |
| **zhaoyp** | 直接 **KMP next 数组** 预处理转移表 g[i][c]，清晰展示「失配指针」如何嵌入 DP。 | ⭐⭐⭐⭐⭐ |
| **Parsley_** | 图文并茂解释 **状态设计动机**（为什么第二维是 j），对新手极友好。 | ⭐⭐⭐⭐ |
| **SolIII** | 用 **记忆化搜索** 封装转移函数，避免重复计算，展示「空间换时间」技巧。 | ⭐⭐⭐ |

> 由于篇幅，下面重点解析 zhaoyp 的 KMP-DP 方案（思路最直观，代码最短）。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（以 zhaoyp 方案为例）

#### 关键点1：把「匹配进度」变成状态
- **状态**：`f[i][j]` 表示考虑完 S 前 i 位，当前后缀与 T 前 j 位完全匹配时的 **最长保留长度**。
- **答案**：`n - max(f[n][j] | 0 ≤ j < m)`，因为 j 不能等于 m（否则出现 T）。

#### 关键点2：预处理转移表 `g[j][c]`
- 作用：已知当前匹配到 T 的 j 位，再读入字符 c，会跳到哪个新位置？
- 求法：利用 KMP 的 next 数组递归跳失配指针，复杂度 O(26·M)。
```cpp
g[i][c] = (T[i+1]==c) ? i+1 : g[next[i]][c];
```

#### 关键点3：DP 转移
- **保留**第 i+1 个字符：`f[i+1][ g[j][c] ] = max(..., f[i][j]+1)`  
- **删除**第 i+1 个字符：`f[i+1][j] = max(..., f[i][j])`  
- 注意：若 `g[j][c] == m` 说明已经完整匹配 T，不能保留，直接丢弃。

💡 **学习笔记**  
> 把「失配指针」预处理成二维表，就能把字符串匹配融合进 DP，实现线性复杂度。

---

### ⚔️ 策略竞技场

| 策略 | 核心思想 | 优点 | 缺点 | 适用场景 |
| --- | --- | --- | --- | --- |
| 暴力 | 枚举删哪些位 | 思维零门槛 | O(2^N) 爆炸 | N ≤ 20 |
| 纯 KMP | 每删一位重跑 | 代码短 | O(N^2) 超时 | N ≤ 1e3 |
| **KMP-DP** | 状态 = 匹配长度 | O(N·M) 稳过 | 需预处理转移表 | N ≤ 1e4, M ≤ 1e3 |

---

## 4. C++核心代码实现赏析

### ✅ 通用核心参考（zhaoyp 版，已精简）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5, M = 1e3 + 5;
int n, m, f[N][M], g[M][26], nxt[M];
char a[N], b[M];

void build_next() {            // KMP 预处理
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && b[i] != b[j + 1]) j = nxt[j];
        if (b[i] == b[j + 1]) ++j;
        nxt[i] = j;
    }
    for (int i = 0; i < m; ++i)
        for (int c = 0; c < 26; ++c) {
            int j = i;
            while (j && b[j + 1] != c + 'a') j = nxt[j];
            g[i][c] = (b[j + 1] == c + 'a') ? j + 1 : 0;
        }
}

int main() {
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);
    build_next();
    memset(f, 0xcf, sizeof(f));            // -inf
    f[0][0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) if (f[i][j] >= 0) {
            // 保留 a[i+1]
            int nj = g[j][a[i + 1] - 'a'];
            if (nj < m) f[i + 1][nj] = max(f[i + 1][nj], f[i][j] + 1);
            // 删除 a[i+1]
            f[i + 1][j] = max(f[i + 1][j], f[i][j]);
        }
    int ans = 0;
    for (int j = 0; j < m; ++j) ans = max(ans, f[n][j]);
    cout << n - ans << '\n';
    return 0;
}
```
**代码解读概要**  
- `build_next()`：先用 KMP 求出 next 数组，再顺便把「当前状态 + 字符」的转移表 g 算好。  
- 主循环：经典 01 背包式两层循环，外层枚举 S，内层枚举匹配长度 j。  
- 答案：最长保留长度 ans，再用 `n - ans` 即最少删除数量。

---

## 5. 算法可视化：像素动画演示

> 主题：**“像素小精灵躲避魔咒 T”**  
> 场景：8×N 的像素跑道，小精灵一路捡起字母石，头顶显示当前与 T 的匹配进度条。

| 帧 | 画面 & 音效 | 目的 |
| --- | --- | --- |
| 0 | 像素跑道初始化，小精灵在起点，进度条=0 | 建立场景 |
| 1 | 出现字母石 `a[i]`，小精灵思考：捡 or 丢？ | 引导决策 |
| 2 | 若捡起 → 进度条跳到 `g[j][c]`；若丢弃 → 进度条不变 | 展示状态转移 |
| 3 | 进度条达到 m → 小精灵被“魔咒”击中，红色闪烁，强制丢弃 | 强调非法状态 |
| 4 | 跑道尽头出现旗帜，显示 `ans` 像素数字 | 结果展示 |

交互按钮：  
- ⏯️ 自动 / 单步  
- 🔄 重置  
- 🎵 8-bit 音效开关

---

## 6. 拓展练习与相似问题思考

### 通用技巧迁移
- **状态压缩**：把“与模式串的匹配进度”作为 DP 第二维，可推广到：
  - 文本中出现多个禁用词（AC 自动机 + DP）。
  - 最长不含敏感词的子序列。
  - 带通配符的匹配问题。

### 洛谷推荐
| 题号 | 推荐理由 |
| --- | --- |
| P3193 [USACO16OPEN] Closing the Farm | 同样利用「当前连通块状态」做 DP 第二维 |
| P3435 [USACO07NOV] Cow Traffic | 把「走到哪一步」作为状态，线性 DP |
| P2414 [NOI2011] 阿狸的打字机 | AC 自动机 + DP 的经典综合题 |

---

## 7. 学习心得与经验分享

> **Parsley_ 的顿悟**：  
> “我最初卡壳在‘为什么第二维是 j’，后来把 KMP 的失配指针画成图，才明白：**DP 状态就是 KMP 自动机的节点**。”

洛语云笺点评：  
把抽象字符串匹配可视化成「进度条」或「自动机节点」，就能让状态设计不再玄学。

---

<conclusion>
今天我们用「KMP-DP」组合拳解决了 Necklace G：  
- 先用 KMP 思想把“匹配进度”压成状态；  
- 再用线性 DP 一次递推求最长保留；  
- 最后 `n - ans` 即最小删除。  
记住：看到“子串禁止出现”，先想**状态 = 匹配长度**，再用 KMP 预处理转移！  
下次探险见！💪
</conclusion>

---
处理用时：85.70秒