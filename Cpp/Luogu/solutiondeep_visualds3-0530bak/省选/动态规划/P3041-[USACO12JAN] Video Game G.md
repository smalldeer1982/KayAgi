# 题目信息

# [USACO12JAN] Video Game G

## 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可用形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？

## 说明/提示

#### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。
- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s$ 中只含大写字母 `A`，`B`，`C`。

## 样例 #1

### 输入

```
3 7 
ABA 
CB 
ABACB 
```

### 输出

```
4 
```

# AI分析结果



# 题目翻译

## [USACO12JAN] Video Game G

### 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可以形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？

### 说明/提示

#### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。
- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s$ 中只含大写字母 `A`，`B`，`C`。

---

# 算法分类

**线性DP**

---

# 综合分析与结论

## 核心思路
1. **AC自动机预处理**：将所有组合技构建为 Trie 树，建立失败指针形成 AC 自动机。每个节点维护 `val` 值，表示从根到该节点的路径及其所有失败路径上的组合技总数。
2. **动态规划设计**：定义 `dp[i][j]` 表示输入前 `i` 个字符后处于自动机节点 `j` 时的最大得分。转移方程为：
   ```cpp
   dp[i+1][son] = max(dp[i+1][son], dp[i][j] + trie[son].val)
   ```
   其中 `son` 是节点 `j` 通过输入字符 `A/B/C` 转移后的子节点。

## 解决难点
- **多模式串匹配**：通过 AC 自动机的高效结构，将组合技匹配问题转化为状态转移。
- **贡献值预处理**：在建立失败指针时，通过 `val += trie[fail].val` 的预处理操作，避免了每次跳转失败指针的重复计算。
- **状态转移优化**：通过将 AC 自动机节点作为状态维度，将时间复杂度优化为 $O(k \cdot M)$（$M$ 为自动机节点数）。

## 可视化设计
1. **DP矩阵动画**：  
   - 使用网格展示 `dp[i][j]` 的值，当前操作单元格用黄色高亮  
   - 转移时用箭头连接 `dp[i][j]` 到 `dp[i+1][son]`，显示 `+val` 的数值变化  
   - 底部状态栏显示当前输入的字符序列和累计得分  

2. **复古像素风格**：  
   - 使用 8-bit 风格字体和 16 色调色板（深蓝背景、亮绿文字）  
   - 音效设计：  
     - 状态转移时播放短促的 "beep" 音  
     - 更新最大值时播放上扬的 "ping" 音  
   - Canvas 绘制自动机结构，节点用闪烁方块表示  

3. **AI演示模式**：  
   - 自动选择当前最优路径，用红色光晕标记  
   - 按空格键切换手动/自动模式  

---

# 题解清单（≥4星）

## 1. yybyyb（★★★★☆）
**亮点**：  
- 使用清晰的 Trie 结构定义  
- 在建立失败指针时直接处理贡献值  
- 代码中标注关键步骤的注释  

**核心代码片段**：
```cpp
void Build() {
    queue<int> Q;
    for(int i=0;i<3;++i)
        if(t[0].vis[i])Q.push(t[0].vis[i]);
    while(!Q.empty()) {
        int u=Q.front();Q.pop();
        for(int i=0;i<3;++i) {
            if(t[u].vis[i]) {
                t[t[u].vis[i]].fail = t[t[u].fail].vis[i];
                Q.push(t[u].vis[i]);
            }
            else t[u].vis[i] = t[t[u].fail].vis[i];
        }
        t[u].p += t[t[u].fail].p; // 贡献值预处理
    }
}
```

## 2. lgswdn_SA（★★★★☆）
**亮点**：  
- 独立定义 `val` 字段明确存储贡献值  
- 使用更简洁的状态转移循环  
- 注释详细解释自动机建立过程  

**关键思路**：
```cpp
struct node { int ch[3], fail, val; };
void ac() {
    // 建立失败指针后处理val
    tr[u].val = tr[u].fin + tr[tr[u].nxt].val;
}
```

## 3. BillYang（★★★★☆）
**亮点**：  
- 使用分离的 Trie 结构定义  
- 显式处理空指针优化代码可读性  
- 完整的 DP 初始化过程  

**核心实现**：
```cpp
memset(f,0xaf,sizeof(f));
f[0][1] = 0; // 根节点初始化
for(int i=1; i<=m; ++i)
    for(int j=1; j<=cnt; ++j)
        for(int k=0; k<3; ++k)
            f[i][trie[j].ch[k]] = max(f[i][trie[j].ch[k]], 
                                     f[i-1][j] + trie[trie[j].ch[k]].val);
```

---

# 核心代码实现

## 关键DP转移逻辑
```cpp
const int MAXN = 1005, MAXM = 3005;
int dp[MAXN][MAXM]; // dp[长度][节点]

void solve() {
    // 初始化
    memset(dp, 0x80, sizeof(dp)); // -INF
    dp[0][0] = 0;
    
    for(int i=0; i<k; ++i)
        for(int j=0; j<=tot; ++j)
            for(int c=0; c<3; ++c) {
                int next = trie[j].ch[c];
                dp[i+1][next] = max(dp[i+1][next], 
                                   dp[i][j] + trie[next].val);
            }
    
    int ans = *max_element(dp[k], dp[k]+tot+1);
}
```

---

# 相似题目推荐

1. **P2292 [HNOI2004] L语言**  
   （AC自动机+DP判断可达到长度）

2. **P4052 [JSOI2007] 文本生成器**  
   （AC自动机+DP求不可读方案数）

3. **P3311 [SDOI2014] 数数**  
   （数位DP结合AC自动机）

---

# 可视化设计要点

## Canvas 动画实现
1. **自动机绘制**：
```javascript
function drawTrie() {
    ctx.fillStyle = "#2C3E50";
    ctx.fillRect(0,0,canvas.width,canvas.height);
    
    nodes.forEach(node => {
        const x = node.x, y = node.y;
        // 绘制发光节点
        if(node == currentNode) {
            ctx.shadowColor = "#F1C40F";
            ctx.shadowBlur = 15;
        }
        ctx.fillStyle = node.val > 0 ? "#E74C3C" : "#3498DB";
        ctx.fillRect(x-15, y-15, 30, 30);
        ctx.shadowBlur = 0;
    });
}
```

2. **音效触发逻辑**：
```javascript
function playSound(type) {
    const freqMap = {
        'move': 440, 
        'score': 880,
        'best': 1760
    };
    const osc = audioCtx.createOscillator();
    osc.frequency.value = freqMap[type];
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(0.1);
}
```

---

通过结合AC自动机的高效匹配与动态规划的状态转移，本问题实现了在多项式时间内的最优解计算。预处理贡献值的设计大幅提升了算法效率，是该类多模式串计数问题的典型解法。

---
处理用时：97.76秒