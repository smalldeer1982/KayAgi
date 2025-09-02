# 题目信息

# [USACO12DEC] First! G

## 题目描述

Bessie has been playing with strings again. She found that by changing the order of the alphabet she could make some strings come before all the others lexicographically (dictionary ordering).

For instance Bessie found that for the strings "omm", "moo", "mom", and "ommnom" she could make "mom" appear first using the standard alphabet and that she could make "omm" appear first using the alphabet

"abcdefghijklonmpqrstuvwxyz".  However, Bessie couldn't figure out any way to make "moo" or "ommnom" appear first.

Help Bessie by computing which strings in the input could be lexicographically first by rearranging the order of the alphabet.  To compute if string X is lexicographically before string Y find the index of the first character in which they differ, j.  If no such index exists then X is lexicographically before Y if X is shorter than Y.  Otherwise X is lexicographically before Y if X[j] occurs earlier in the alphabet than Y[j].

Bessie 一直在研究字符串。她发现，通过改变字母表的顺序，她可以按改变后的字母表来排列字符串（字典序大小排列）。

例如，Bessie 发现，对于字符串 $\texttt{omm},\texttt{moo},\texttt{mom}$ 和 $\texttt{ommnom}$，她可以使用标准字母表使 $\texttt{mom}$ 排在第一个（即字典序最小），她也可以使用字母表 $\texttt{abcdefghijklonmpqrstuvwxyz}$ 使得 $\texttt{omm}$ 排在第一个。然而，Bessie 想不出任何方法（改变字母表顺序）使得 $\texttt{moo}$ 或 $\texttt{ommnom}$ 排在第一个。

接下来让我们通过重新排列字母表的顺序来计算输入中有哪些字符串可以排在第一个（即字典序最小），从而帮助 Bessie。

要计算字符串 $X$ 和字符串 $Y$ 按照重新排列过的字母表顺序来排列的顺序，先找到它们第一个不同的字母 $X_i$ 与 $Y_i$，按重排后的字母表顺序比较，若 $X_i$ 比 $Y_i$ 先，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前；若没有不同的字母，则比较 $X$ 与 $Y$ 长度，若 $X$ 比 $Y$ 短，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前。

## 说明/提示

The example from the problem statement.

Only "omm" and "mom" can be ordered first.

样例即题目描述中给出的例子，只有 $\texttt{omm}$ 和 $\texttt{mom}$ 在各自特定的字典序下可以被排列在第一个。

## 样例 #1

### 输入

```
4
omm
moo
mom
ommnom
```

### 输出

```
2
omm
mom
```

# AI分析结果



## 唯一算法分类
字典树 + 拓扑排序

---

## 综合分析与结论

### 核心思路
所有题解均采用 **字典树判前缀 + 拓扑排序判环** 的双重验证机制：
1. **字典树判前缀**：若某字符串是其他字符串的前缀（如 "ab" 是 "abc" 的前缀），则无法通过调整字母表顺序使其成为最小
2. **拓扑排序判环**：在字典树的每一层，当前字符必须比同层其他字符字典序小，建立有向边后用拓扑排序检测是否存在矛盾环

### 可视化设计思路
1. **字典树构建动画**：以像素风格绘制字典树，新插入字符时对应路径亮起绿色光效，终点节点标记为红色（表示字符串结束）
2. **拓扑排序动态演示**：在每层处理时，用蓝色箭头表示当前字符指向同层其他字符的边，队列元素以黄色高亮，入度归零时播放 "哔" 音效
3. **冲突检测特效**：当发现环时，相关节点闪烁红光并播放低音警报声

---

## 题解清单（≥4星）

### 1. Heartlessly（⭐⭐⭐⭐⭐）
- **亮点**：封装字典树结构体，分离插入与验证逻辑；拓扑排序复用队列节省内存
- **核心代码**：
```cpp
inline bool find(string x) {
    memset(e, 0, sizeof (e)); // 清空边关系
    for (int i = 0; i < x.size(); ++i) {
        if (ed[u]) return 0; // 前缀检查
        int v = x[i] - 'a';
        for (int j = 0; j < 26; ++j) // 建立同层约束
            if (v != j && ch[u][j]) 
                e[v][j] = 1;
        u = ch[u][v];
    }
    return topoSort(); // 拓扑判环
}
```

### 2. littleming（⭐⭐⭐⭐）
- **亮点**：使用邻接表存边，内存效率更高；独立处理每个字符串的图结构
- **巧妙之处**：
```cpp
inline void solve(string x) {
    for (int j = 0; j < 26; j++)
        if (ch[u][j] && j != t) 
            addedge(t, j); // 邻接表存边
}
```

### 3. liuxu（⭐⭐⭐⭐）
- **亮点**：用 vector 动态维护边关系，代码简洁易懂；附带详细手绘图解说明
- **调试心得**："一定要动手画图理解拓扑约束关系，否则容易漏掉同层其他字符的边"

---

## 最优技巧提炼

### 关键技巧
1. **分层约束**：在字典树的每一层，当前字符必须比同层其他字符小
2. **即时建图**：对每个候选字符串单独构建约束图，避免全局状态干扰
3. **拓扑复用**：每次验证后重置图结构，通过队列实现 O(26) 复杂度的判环

### 思维模式
**约束传递思想**：将字典序比较转化为字符间的有向边约束，通过拓扑排序验证约束的可满足性

---

## 相似题目推荐
1. [P3065 USACO12DEC First! G](https://www.luogu.com.cn/problem/P3065)（本题原型）
2. [P2922 USACO08DEC Secret Message](https://www.luogu.com.cn/problem/P2922)（字典树前缀处理）
3. [LeetCode 269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)（拓扑排序应用）

---

## 可视化代码片段（伪代码）

```javascript
// 像素风格字典树绘制
function drawTrie(node, x, y) {
    drawRect(x, y, 16, 16, '#3366ff'); // 蓝色节点
    for (let c = 0; c < 26; c++) {
        if (node.children[c]) {
            let angle = (c / 26) * Math.PI * 2;
            let childX = x + Math.cos(angle) * 50;
            let childY = y + Math.sin(angle) * 50;
            drawLine(x+8, y+8, childX+8, childY+8, '#ffaa33'); // 橙色连接线
            drawTrie(node.children[c], childX, childY);
        }
    }
}

// 拓扑排序动画
function topologicalSort() {
    let q = new Queue();
    q.enqueue(startNode).highlight('#ffff00'); // 黄色高亮入队
    while (!q.empty()) {
        let u = q.dequeue().highlight('#00ff00'); // 绿色处理中
        for (let v of adj[u]) {
            inDegree[v]--;
            if (inDegree[v] === 0) {
                q.enqueue(v).playSound('beep');
            }
        }
    }
}
```

---

## 复古游戏化设计

### 实现方案
1. **8位风格调色板**：使用 NES 经典 56 色调色板，节点用宝蓝色（#0066ff），边用橘黄（#ff6600）
2. **音效系统**：
   - 节点扩展：8-bit "blip" 音效（200Hz 方波）
   - 发现环：低音爆破音（50Hz 三角波持续 0.3s）
3. **自动演示模式**：按 A 键自动运行算法，B 键单步执行，方向键控制速度

### 关卡设计
- **教学关**：仅 2 个字符的小规模测试
- **挑战关**：随机生成含环/无环的约束图
- **Boss战**：需要同时处理 26 个字符的全连接图

---

通过这种多维度解析，学习者既能掌握算法核心，又能在游戏化交互中深化理解，最终达到举一反三的效果。

---
处理用时：70.55秒