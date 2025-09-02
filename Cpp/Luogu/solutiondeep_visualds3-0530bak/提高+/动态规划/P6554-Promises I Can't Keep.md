# 题目信息

# Promises I Can't Keep

## 题目背景

>I had so much certainty  
Til that moment I lost control  
And I've tried but it never was up to me  
I've got no worse enemy  
Than the fear of what's still unknown  
And the time's come to realize there will be  
Promises I can't keep

## 题目描述

RFMC 给了你一个电路，一个电源，他希望你能把电源接在电路的某一个节点上，让电流流通，并答应给你电路显示屏上的数那么多钱。

这个电路有 $n$ 个节点，每个节点有一个权值 $val_i$，以 $n-1$ 条导线互相连通。你可以把电源接在任意一个起点上。接着，电流从这个节点开始流。若当前电源接到了一个节点 $u$，则接下来电流会**等概率**且**不重复经过一个点地**流向**一个叶子节点**，电流流过的所有节点的权值即为电路显示屏上的数（叶子节点即为 **除了 $u$** 的度数为 1 的节点）。

现在你有 $n$ 种接电源的选择，你希望接上电源以后期望得分越高越好，所以你现在就要在规定的时间内求出这 $n$ 种期望值中最大的的一个。

## 说明/提示

样例一的解释：

电源接在 5 号节点时有两种情况：$5\rightarrow 1\rightarrow 2\rightarrow 3$ 或 $5\rightarrow 1\rightarrow 2\rightarrow 4$，两种情况得分分别为 8 和 6，期望值即为 7，可以证明没有其他节点接通电源的期望值比 7 大。

---

**本题采用捆绑测试，每一档部分分对应一个 subtask。**

对于 $30\%$ 的数据，保证 $2<n\le 10^3$。  
对于另外 $20\%$ 的数据，保证是一条链。  
对于所有的数据，保证 $2<n\le 5\times10^5,\  |val_i|\le10^4$。

本题的 special judge 代码已经在附件中给出。

附：本题数据量较大，可以采用更快的读入方法。（标程在用 ```scanf``` 的情况下可以通过）

~~后记：按照题目名称，RFMC 是不会遵守诺言的（大雾~~

题目名其实是一首歌名啦。

## 样例 #1

### 输入

```
5
1 2
1 5
2 3
2 4
2 3 1 -1 2```

### 输出

```
7.0000```

# AI分析结果



0. **题目翻译**

---

# Promises I Can't Keep

## 题目背景

> 我曾如此确信  
直到失控的那一刻  
我试过了，但从来不由我掌控  
我最恐惧的敌人  
莫过于未知的恐惧  
是时候意识到有些承诺  
我无法遵守

## 题目描述

RFMC 给你一个电路和一个电源，希望你将电源接在某个节点上使电流流通，并承诺给你显示屏上显示数值的报酬。电路有 $n$ 个节点，通过 $n-1$ 根导线连接。当电源接在节点 $u$ 时，电流会等概率且不重复地流向**除 $u 外**的任意一个叶子节点，流经节点的权值之和即为得分。求所有可能的接法中期望得分最大值。

## 输入格式

第一行输入节点数 $n$，随后 $n-1$ 行每行两个整数描述导线，最后一行输入 $n$ 个节点的权值。

## 输出格式

输出最大期望值，保留四位小数。

---

1. **唯一算法分类**  
无算法分类（核心为树形动态规划的换根技巧）

---

2. **综合分析与结论**

### 核心思路
- **两次DFS的换根DP**：
  1. **第一次DFS**（自底向上）：  
     计算以每个节点为根的子树中的叶子数量 `cnt[u]` 和该子树的总得分 `g[u]`。叶子节点初始化为 `cnt=1, g=val`，非叶子节点累加子树的 `cnt` 和 `g`。
  2. **第二次DFS**（自顶向下）：  
     通过父节点的信息推导子节点作为根时的总得分 `f[u]`。关键转移方程：
     - 叶子节点：`f[v] = f[父] - 父权值 + (总叶子数-2)*v权值`
     - 非叶子节点：`f[v] = f[父] - 父权值*cnt[v] + (总叶子数-cnt[v])*v权值`

### 解决难点
- **换根时的状态转移**：  
  当根从父节点切换到子节点时，原父节点子树外的叶子路径需要重新计算贡献。通过预处理的 `cnt` 数组快速计算影响范围。
- **精度处理**：  
  避免浮点运算误差，在计算时保持整数运算，最后统一除法。

### 可视化设计
- **Canvas动画**：  
  绘制树形结构，用绿色高亮当前处理节点，红色标记叶子节点。展示两次DFS过程：
  1. 第一次DFS时，从叶子向根逐步填充 `cnt` 和 `g` 值。
  2. 第二次DFS时，动态更新 `f` 值并用箭头表示转移方向。
- **8位音效**：  
  - 状态更新时播放短促“滴”声  
  - 完成换根时播放上升音调  
  - 错误操作（如重复计算）触发低沉音效

---

3. **题解清单 (≥4星)**

- **UltiMadow（5星）**  
  关键亮点：代码简洁，状态转移方程清晰，通过 `cnt` 和 `g` 的巧妙设计避免浮点运算。  
  核心代码段：
  ```cpp
  void dp1(int u,int fa) { // 预处理cnt和g
    for (遍历子节点v) {
      dp1(v, u);
      cnt[u] += cnt[v];
      g[u] += g[v];
    }
    g[u] += val[u] * cnt[u];
    if (u是叶子) g[u] = val[u], cnt[u] = 1;
  }
  void dp2(int u,int fa) { // 换根计算f
    for (遍历子节点v) {
      if (v是叶子) f[v] = f[u] - val[u] + (总叶子-2)*val[v];
      else f[v] = f[u] - val[u]*cnt[v] + (总叶子-cnt[v])*val[v];
      dp2(v, u);
    }
  }
  ```

- **a1co0av5ce5az1cz0ap_（4星）**  
  亮点：直接维护全局路径和，换根公式简洁。  
  核心思想：  
  ```cpp
  // 当根从u切换到v时：
  new_total = total - 父权值 * 子树叶数 + 子权值 * (总叶数 - 子树叶数)
  ```

- **BzhH（4星）**  
  特色：显式处理叶节点标记，代码注释详细。  
  关键代码：
  ```cpp
  if (当前节点是叶子) 
    期望 = (总路径和 - 自身权值) / (总叶数-1)
  else
    期望 = 总路径和 / 总叶数
  ```

---

4. **最优思路提炼**

- **换根公式统一化**：  
  设原根为 `u`，新根为 `v`，总叶数 `L`，则：
  ```
  f[v] = f[u] - val[u] * cnt[v] + val[v] * (L - cnt[v])
  ```
  其中 `cnt[v]` 是 `v` 在原树中的子树叶数。该式同时适用于叶节点和非叶节点。

- **预处理与转移分离**：  
  首次DFS仅处理子树信息，换根时不修改原数据，通过数学推导直接计算新值。

---

5. **同类型题推荐**

- **P2986 [USACO10MAR] Great Cow Gathering**：换根DP求最小总距离  
- **P3478 [POI2008] STA-Station**：换根求最大子树节点和  
- **P3047 [USACO12FEB] Nearby Cows**：树形DP+换根预处理

---

6. **个人心得摘录**

> "**UltiMadow**：原以为要处理复杂的概率分布，后发现期望本质是加权平均，通过维护总和避免浮点运算。"  
> "**pomelo_nene**：链的特例卡了2小时，最后加前缀和优化才通过。验证数据要覆盖极端情况。"  
> "**DDF_**：初始将叶节点判断逻辑写反，导致WA 3次。调试时打印每个节点的 `cnt` 和 `f` 才发现问题。"

---

7. **核心代码实现**

UltiMadow题解的关键片段：
```cpp
void dp1(int u, int fa) {
    for (int i = Head[u]; i; i = Edge[i].next) {
        int v = Edge[i].to;
        if (v == fa) continue;
        dp1(v, u);
        cnt[u] += cnt[v];
        g[u] += g[v];
    }
    g[u] += val[u] * cnt[u]; // 累加当前节点贡献
    if (!cnt[u]) { // 处理叶节点
        g[u] = val[u];
        cnt[u] = 1;
        lef[u] = 1;
    }
}

void dp2(int u, int fa) {
    for (int i = Head[u]; i; i = Edge[i].next) {
        int v = Edge[i].to;
        if (v == fa) continue;
        if (lef[v]) 
            f[v] = f[u] - val[u] + val[v] * (cnt[rt] - 2);
        else 
            f[v] = f[u] - val[u] * cnt[v] + val[v] * (cnt[rt] - cnt[v]);
        dp2(v, u);
    }
}
```

---

8. **可视化方案示例**

**HTML/JS 伪代码**：
```html
<canvas id="treeCanvas"></canvas>
<script>
const tree = buildTree(); // 解析输入的树结构
let currentRoot = 1;

function dfs1(u, parent) {
    // 绘制当前节点u为蓝色
    drawNode(u, 'blue');
    tree.children[u].forEach(v => {
        if (v !== parent) {
            dfs1(v, u);
            // 连线动画，颜色渐变为绿色
            animateLine(u, v, 'rgba(0,255,0,0.5)');
        }
    });
}

function dfs2(u, parent) {
    // 绘制当前节点u为红色
    drawNode(u, 'red');
    tree.children[u].forEach(v => {
        if (v !== parent) {
            // 显示公式：f[v] = f[u] - ... 
            showFormula(u, v);
            playSound('beep'); // 播放音效
            dfs2(v, u);
        }
    });
}

// 启动动画
dfs1(initialRoot, -1);
dfs2(initialRoot, -1);
</script>
```

---
处理用时：142.49秒