# 题目信息

# [COCI 2015] Divljak

## 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。
2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。


## 样例 #1

### 输入

```
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3
```

### 输出

```
1
2
1
```

# AI分析结果



# 算法分类
AC自动机、树上差分、树状数组

## 题解核心思路与难点对比
各题解均采用以下核心逻辑：
1. **构建AC自动机**：将Alice的n个模式串构建AC自动机，建立fail树（fail指针构成的有向树）
2. **fail树预处理**：通过树链剖分/dfs序预处理各节点的子树范围
3. **链并集处理**：对每个插入的P串，在AC自动机上匹配得到所有经过节点，按dfs序排序后：
   - 每个节点到根的链+1
   - 相邻节点的LCA到根的链-1（消除重复贡献）
4. **高效维护**：使用树状数组维护子树和查询

**关键难点**：
1. 如何高效处理多个链的并集
2. 避免重复统计同一节点的贡献
3. 将路径操作转化为子树操作（通过dfs序）

## 题解评分（≥4星）
1. Calculatelove（5星）：思路清晰，代码简洁，树状数组维护dfs序的差分思想突出
2. 皎月半洒花（4星）：详细解释虚树思想，代码实现完整但略冗长
3. tzc_wk（4星）：完整实现树链剖分，代码结构清晰

## 最优思路提炼
1. **Fail树性质**：匹配路径的fail链覆盖所有子串出现位置
2. **链并集优化**：排序后相邻节点LCA差分去重
3. **树状数组妙用**：将链操作转化为单点加，子树和查询转化为区间查询

## 同类题目推荐
1. P3796 【模板】AC自动机（加强版）
2. P5357 【模板】AC自动机（二次加强版）
3. P2414 [NOI2011] 阿狸的打字机

## 可视化算法演示
**核心动画步骤**：
1. **AC自动机结构**：展示Trie树及fail指针（红色箭头）
2. **P串匹配路径**：高亮匹配过程中经过的节点（蓝色闪烁）
3. **排序节点**：按dfs序排列节点，显示排序过程（绿色连线）
4. **差分操作**：
   - 每个节点+1（绿色光效）
   - 相邻LCA-1（红色光效）
5. **树状数组更新**：展示dfs序区间的加减操作（柱状图波动）

**复古像素化实现**：
```javascript
// 示例：Canvas绘制AC自动机节点
const ctx = canvas.getContext('2d');
const NODE_SIZE = 32; // 8位风格32x32像素节点

function drawNode(x, y, color) {
  ctx.fillStyle = color; 
  ctx.fillRect(x, y, NODE_SIZE, NODE_SIZE);
  ctx.strokeStyle = '#000';
  ctx.strokeRect(x, y, NODE_SIZE, NODE_SIZE);
}

// 播放音效
function playBeep(freq) {
  const oscillator = audioCtx.createOscillator();
  oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

## 关键代码片段
```cpp
// Calculatelove题解核心代码
void solve1() {
    int u=0,tp=0;
    for(int i=1;i<=len;i++){ // 匹配P串
        u = trie[u][P[i]-'a'];
        seq[++tp] = u; 
    }
    sort(seq+1, seq+tp+1, cmp); // 按dfs序排序
    
    for(int i=1;i<=tp;i++) 
        bit.add(dfn[seq[i]], 1); // 当前节点+1
    for(int i=1;i<tp;i++) 
        bit.add(dfn[lca(seq[i],seq[i+1])], -1); // LCA处-1
}

int query(int x) {
    int p = end_pos[x]; // S_x的终止节点
    return bit.query(ed[p]) - bit.query(dfn[p]-1); // 子树和查询
}
```

## 个人心得摘录
"调试时发现_end是C++关键字，一上午都在找这个错误... 按dfs序排序后，公共祖先的差分消除是核心技巧" —— 皎月半洒花

## 算法比较
所有AC自动机解法均优于SA/SAM方案，时间复杂度从O(L log²L)优化到O(L log L)。树状数组方案比线段树合并节省近50%空间。

---
处理用时：55.36秒