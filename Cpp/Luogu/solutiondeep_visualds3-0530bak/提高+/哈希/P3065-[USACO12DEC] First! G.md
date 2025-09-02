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



# 算法分类与题解分析

**唯一算法分类**：图论（拓扑排序）与字典树（Trie）

---

## **题解思路与核心难点**

### **核心思路**
1. **Trie 构建**：将所有字符串插入 Trie 树，记录每个节点是否为某个字符串的结尾。
2. **约束建模**：对于每个待检查字符串，在 Trie 中逐层遍历。若当前字符为 `c`，同一层的其他字符 `d` 需满足 `c < d`，即建立有向边 `c → d`。
3. **拓扑判环**：通过拓扑排序判断图中是否存在环。若无环，则该字符串可成为字典序最小。

### **解决难点**
- **前缀冲突**：若某字符串是其他字符串的前缀（通过 Trie 节点标记判断），直接排除。
- **动态建图**：每个字符串需独立构建约束图，避免干扰。
- **高效判环**：拓扑排序的时间复杂度为 `O(26)`，总复杂度为 `O(26m)`（`m` 为总字符数）。

---

## **题解评分（≥4星）**

### 1. Heartlessly（⭐️⭐️⭐️⭐️⭐️）
- **亮点**：代码结构清晰，Trie 与拓扑排序实现高效；通过 `ed[u]` 快速判断前缀冲突。
- **核心片段**：
  ```cpp
  bool find(string x) {
      memset(e, 0, sizeof(e));
      memset(in, 0, sizeof(in));
      // ... 建立约束边并拓扑排序 ...
  }
  ```

### 2. littleming（⭐️⭐️⭐️⭐️）
- **亮点**：使用邻接表存边，入度数组动态重置，代码简洁。
- **核心片段**：
  ```cpp
  inline void solve(string x) {
      // ... 动态建立边并统计入度 ...
  }
  ```

### 3. liuxu（⭐️⭐️⭐️⭐️）
- **亮点**：通过 `vector` 管理边，逻辑清晰，注释详细。
- **核心片段**：
  ```cpp
  if(work(s[i])) ans[++num_ans] = i;
  ```

---

## **最优思路与技巧提炼**

### **关键技巧**
1. **Trie 快速定位层级**：利用 Trie 的层级结构，在遍历字符串时直接获取同一层的所有字符。
2. **拓扑排序判环**：通过入度数组和队列动态维护节点关系，高效检测环。
3. **动态约束图**：每个字符串独立构建约束图，避免全局干扰。

### **同类型题**
- [LeetCode 269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
- [洛谷 P2414 阿狸的打字机](https://www.luogu.com.cn/problem/P2414)
- [Codeforces 510C. Fox And Names](https://codeforces.com/problemset/problem/510/C)

---

## **可视化与算法演示**

### **动画方案**
1. **Trie 构建**：以像素方块表示 Trie 节点，不同颜色表示不同字符，插入时路径高亮。
2. **约束边绘制**：遍历字符串时，用箭头连接当前字符与同层其他字符。
3. **拓扑排序过程**：
   - **队列状态**：显示当前入度为 0 的节点。
   - **边删除**：每处理一个节点，删除其出边并更新入度。
   - **环检测**：若最终存在未处理节点，显示红色警告。

### **复古游戏化设计**
- **像素风格**：字符用 8-bit 字体，Trie 节点为 16x16 像素方块。
- **音效触发**：
  - **建边**：短促“哔”声。
  - **拓扑完成**：成功音调（无环）或失败音效（有环）。
- **自动演示**：按空格键逐步执行，支持调节速度。

### **关键代码（伪代码）**
```javascript
// 绘制 Trie 节点
function drawTrieNode(node, x, y) {
  ctx.fillStyle = node.end ? "#FF0000" : "#00FF00";
  ctx.fillRect(x, y, 16, 16);
}

// 拓扑排序动画
function topologicalStep() {
  let u = queue.dequeue();
  highlightNode(u);
  playSound("pop");
  for (let v of adj[u]) {
    inDegree[v]--;
    if (inDegree[v] === 0) queue.enqueue(v);
  }
}
```

---

## **个人心得摘录**

- **Heartlessly**：强调 Trie 的 `ed` 标记是避免前缀冲突的关键。
- **Daidly**：贪心调整优先级的方法虽不稳定，但启发对约束条件的灵活处理。

---

**总结**：Trie 结合拓扑排序是本题的最优解，正确性高且效率可靠。可视化重点在于层级约束的动态展示与拓扑判环的交互式演示。

---
处理用时：87.80秒