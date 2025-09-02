# 题目信息

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# AI分析结果



**唯一算法分类**  
树的后序遍历与子树和处理

---

### **综合分析与结论**  
**题目核心**：将树分割为三个温度总和相等的部分，需剪断两条边。  
**关键思路**：  
1. **总和检查**：总温度必须是3的倍数，否则无解。  
2. **DFS遍历**：后序遍历计算每个子树的温度总和，当发现子树和等于总和的1/3时，记录该节点并重置其子树和为0，避免重复统计。  
3. **结果判定**：若找到至少两个符合条件的子树，则输出对应节点；否则输出-1。  

**难点与解决**：  
- **避免重复统计**：通过将符合条件的子树和置零，确保父节点计算时不再包含已分割的部分。  
- **正确性保证**：两个子树必须位于不同的分支或层次，确保分割后的三部分独立存在。  

**可视化设计**：  
1. **动画方案**：  
   - **树结构展示**：节点显示温度值，边动态高亮。  
   - **DFS过程**：以颜色标记当前遍历节点（如绿色），回溯时更新子树和。  
   - **剪断判定**：当子树和等于目标值时，节点变为红色并播放音效，对应边闪烁。  
2. **复古像素风格**：  
   - **8位色调色板**：根节点用黄色，普通节点蓝色，符合条件节点红色。  
   - **音效触发**：遍历时播放“滴”声，找到解时播放“成功”音效，无解时播放“失败”音效。  
3. **AI自动演示**：模拟DFS遍历顺序，自动暂停在关键步骤（如子树和计算完成时）。  

---

### **题解清单 (≥4星)**  
1. **maniac！的题解（5星）**  
   - **亮点**：代码简洁，逻辑清晰，通过置零子树和避免重复统计，注释幽默。  
   - **代码片段**：  
     ```cpp
     void dfs(int x, int y) {
         tem[x] = t[x];
         for (int i = head[x]; i; i = next[i]) {
             int v = ver[i];
             if (v != y) {
                 dfs(v, x);
                 tem[x] += tem[v];
             }
         }
         if (tem[x] == sum) ans[++cnt] = x, tem[x] = 0; // 关键：置零子树和
     }
     ```
   - **个人心得**：“写完后发现其实是树的遍历，而非严格DP。”  

2. **chihik的题解（4星）**  
   - **亮点**：明确使用树形DP术语，强调分割后的子树必须是原树的子树。  
   - **代码片段**：  
     ```cpp
     if (dp[v] == sum / 3) {
         if (!v1) v1 = v;
         else if (!v2) v2 = v;
         dp[u] -= dp[v]; // 动态调整父节点和
     }
     ```
   - **优化点**：动态更新父节点和，减少重复计算。  

3. **试试事实上吗的题解（4星）**  
   - **亮点**：详细讨论分割策略，通过图示解释极端情况。  
   - **代码片段**：  
     ```cpp
     if (sz[x] == sum) ans[++cnt] = x, sz[x] = 0; // 重置子树和
     ```

---

### **最优思路提炼**  
1. **总和分块**：总和必须为3的倍数，否则直接返回-1。  
2. **后序遍历统计**：自底向上计算子树和，确保每个节点仅处理一次。  
3. **即时剪枝**：当子树和满足条件时，立即记录并置零，避免父节点重复统计。  
4. **结果验证**：至少需要两个独立子树，确保分割后剩余部分也能满足条件。  

---

### **同类型题与算法套路**  
- **通用解法**：树的遍历 + 子树和统计，适用于分割、平衡等问题。  
- **类似题目**：  
  1. **LeetCode 663. Equal Tree Partition**（判断能否分割为两个和相等的部分）。  
  2. **洛谷 P2014 [CTSC1997]选课**（树形DP计算依赖关系）。  

---

### **推荐题目**  
1. **洛谷 P1364**（树的重心，统计子树节点数）。  
2. **洛谷 P3177**（树上分组背包，动态规划）。  
3. **洛谷 P1352**（树形DP，最大权独立集）。  

---

### **个人心得摘录**  
- **maniac！**：“子树和问题常被误认为DP，实则是遍历技巧。”  
- **Kevin_F**：“注意根节点不能作为答案节点，需在遍历时排除。”  
- **试试事实上吗**：“重置子树和为0是避免重复统计的关键，否则链状结构会出错。”  

---

### **可视化代码片段（JavaScript）**  
```javascript
// 绘制树结构（Canvas实现）
function drawTree(ctx, nodes, edges) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    nodes.forEach(node => {
        ctx.fillStyle = node.highlight ? "#FF0000" : "#00FF00";
        ctx.fillRect(node.x, node.y, 20, 20); // 像素风格节点
    });
    edges.forEach(edge => {
        ctx.strokeStyle = edge.cut ? "#FF0000" : "#FFFFFF";
        ctx.beginPath();
        ctx.moveTo(edge.from.x + 10, edge.from.y + 10);
        ctx.lineTo(edge.to.x + 10, edge.to.y + 10);
        ctx.stroke();
    });
}

// 播放音效（Web Audio API）
function playSound(effect) {
    const oscillator = audioCtx.createOscillator();
    oscillator.type = "square"; // 8位风格音效
    oscillator.frequency.setValueAtTime(effect === "success" ? 880 : 440, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + 0.1);
}
``` 

---

### **算法演示交互设计**  
- **步进控制**：点击“Next”按钮单步执行DFS，显示当前节点和子树和。  
- **自动模式**：点击“Auto”后，算法以500ms/步自动运行，找到解时暂停。  
- **音效反馈**：遍历时播放低频音，找到解时高频音，无解时连续短音。  
- **积分系统**：正确分割后获得10分，失败扣5分，鼓励快速找到最优解。

---
处理用时：83.59秒