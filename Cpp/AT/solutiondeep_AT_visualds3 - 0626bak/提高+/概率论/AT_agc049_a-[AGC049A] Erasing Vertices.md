# 题目信息

# [AGC049A] Erasing Vertices

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc049/tasks/agc049_a

$ 1 $ から $ N $ までの番号のついた $ N $ 頂点からなる有向グラフがあります． このグラフの辺は，$ N $ 個の長さ $ N $ の文字列 $ S_1,S_2,\ldots,S_N $ によって表されます． 具体的には，頂点 $ i $ から頂点 $ j $ に向かう辺が存在する場合は $ S_{i,j}= $`1` で， そうでない場合は $ S_{i,j}= $`0` です． このグラフに自己ループや多重辺はありません．

クマの AtCobear くんが，以下の操作をグラフが空になるまで繰り返します．

- (まだ削除されていない) グラフの頂点を一様ランダムに $ 1 $ つ選ぶ（このランダムな選択は，今までの選択とは独立である）． そして，その頂点，およびその頂点からいくつかの辺をたどることで到達可能なすべての頂点を，削除する． 削除された頂点に接続する辺も，すべて削除される．

操作回数の期待値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S_i $ は `0`,`1` からなる長さ $ N $ の文字列．
- $ S_{i,i}= $`0`

### Sample Explanation 1

以下の $ 3 $ つのシナリオが等確率で起こります． - 最初の操作で頂点 $ 1 $ を選び，頂点 $ 1,2,3 $ が削除される． グラフが空になったので操作を終了する． - 最初の操作で頂点 $ 2 $ を選び，頂点 $ 2,3 $ が削除される． 次の操作で，頂点 $ 1 $ を選び，頂点 $ 1 $ が削除される． グラフが空になったので操作を終了する． - 最初の操作で頂点 $ 3 $ を選び，頂点 $ 2,3 $ が削除される． 次の操作で，頂点 $ 1 $ を選び，頂点 $ 1 $ が削除される． グラフが空になったので操作を終了する． よって操作回数の期待値は，$ (1+2+2)/3=5/3 $ になります．

### Sample Explanation 2

必ず $ 3 $ 回の操作を行います．

### Sample Explanation 3

必ず $ 1 $ 回の操作を行います．

## 样例 #1

### 输入

```
3

010

001

010```

### 输出

```
1.66666666666666666667```

## 样例 #2

### 输入

```
3

000

000

000```

### 输出

```
3.00000000000000000000```

## 样例 #3

### 输入

```
3

011

101

110```

### 输出

```
1.00000000000000000000```

# AI分析结果



---

**唯一算法分类**:  
图论 - 传递闭包 & 期望的线性性

---

### **综合分析与结论**

**核心思路**  
将总期望分解为每个顶点被选中的概率之和。关键点在于：顶点 $i$ 被选中的概率等于其可达集合大小的倒数。使用传递闭包计算每个顶点的可达集合，统计每个顶点的可达点数量 $num_i$，总期望为 $\sum_{i=1}^n \frac{1}{num_i}$。

**难点与解决**  
- **难点1：概率的推导**  
  需理解“顶点 $i$ 被选中的概率仅取决于其可达集合中的顶点是否先被选中”，转化为组合数学中的均匀随机选择问题。
- **难点2：高效计算传递闭包**  
  使用 bitset 优化传递闭包计算，将复杂度降至 $O(n^3 / w)$，其中 $w$ 为机器字长。

**可视化设计**  
- **动画流程**  
  1. 展示初始有向图的邻接矩阵（像素化网格表示顶点和边）。  
  2. 逐步计算传递闭包：高亮当前处理的顶点 $i$，动态扩展其可达集合（用颜色填充可达顶点）。  
  3. 统计每个顶点的 $num_i$，并在右侧显示当前总期望。  
- **复古效果**  
  - 顶点用 8-bit 风格方块表示，边用像素线条连接。  
  - 计算传递闭包时播放电子音效，统计 $num_i$ 时播放短促音效。  
  - 背景音乐为循环 8-bit 风格旋律。  

---

### **题解清单 (≥4星)**

1. **童年的小翼龙 (★★★★★)**  
   - **亮点**: 使用 bitset 高效计算传递闭包，代码简洁且时间复杂度最优。  
   - **代码片段**:  
     ```cpp
     bitset<N> g[N];
     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= n; j++) {
             if (g[j][i]) g[j] |= g[i];
         }
     }
     ```

2. **WilliamFranklin (★★★★☆)**  
   - **亮点**: 将操作抽象为染色过程，清晰解释了期望拆分逻辑。  
   - **代码片段**:  
     ```cpp
     bitset<N> b[N];
     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= n; j++) {
             if (b[j][i]) b[j] |= b[i];
         }
     }
     ```

3. **RyanLi (★★★★☆)**  
   - **亮点**: 通过 DFS 计算可达集合，适合小规模图，代码可读性强。  
   - **代码片段**:  
     ```cpp
     void dfs(int u) {
         if (vis[u]) return;
         ++f[u], vis.set(u);
         for (int i = 1; i <= n; ++i) if (g[u][i]) dfs(i);
     }
     ```

---

### **核心代码实现**

**关键逻辑（传递闭包计算）**  
```cpp
// 初始化邻接矩阵（包含自环）
for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    for (int j = 1; j <= n; j++) {
        g[i][j] = (s[j-1] == '1');
    }
    g[i][i] = 1; // 包含自环
}

// 计算传递闭包
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (g[j][i]) { // 若 j 可达 i，则合并 j 和 i 的可达集合
            g[j] |= g[i];
        }
    }
}

// 统计每个顶点的 num_i 并计算答案
double ans = 0;
for (int i = 1; i <= n; i++) {
    int cnt = 0;
    for (int j = 1; j <= n; j++) {
        if (g[j][i]) cnt++;
    }
    ans += 1.0 / cnt;
}
```

---

### **相似题目推荐**

1. **CF280C**  
   - **标签**: 期望线性性、树形结构  
   - **题号**: [CF280C](https://codeforces.com/contest/280/problem/C)  

2. **洛谷 P4213**  
   - **标签**: 传递闭包、强连通分量  
   - **题号**: [P4213](https://www.luogu.com.cn/problem/P4213)  

3. **AT ABC202E**  
   - **标签**: 图的可达性、离线查询  
   - **题号**: [ABC202E](https://atcoder.jp/contests/abc202/tasks/abc202_e)  

---

### **可视化与复古动画代码片段**

```javascript
// Canvas 初始化与像素绘制
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const GRID_SIZE = 20;

function drawVertex(x, y, color = '#00FF00') {
    ctx.fillStyle = color;
    ctx.fillRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
}

// 传递闭包计算动画
function animateClosure(i) {
    for (let j = 1; j <= n; j++) {
        if (g[j][i]) {
            // 高亮当前处理的顶点 j
            drawVertex(j, i, '#FF0000');
            playSound('beep');
            mergeReachableSets(j, i);
        }
    }
}

// 8-bit 音效
function playSound(type) {
    const audioCtx = new (window.AudioContext)();
    const oscillator = audioCtx.createOscillator();
    oscillator.type = 'square';
    oscillator.frequency.setValueAtTime(type === 'beep' ? 440 : 880, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

**个人心得**  
- 必须显式包含自环（`g[i][i] = 1`），否则会漏算自身。  
- 传递闭包计算需按特定顺序合并集合，避免循环依赖。

---
处理用时：103.57秒