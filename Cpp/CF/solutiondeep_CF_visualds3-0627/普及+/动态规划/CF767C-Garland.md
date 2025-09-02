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



0. **题目翻译**  
# Garland

## 题目描述

某年新年，迪马梦见一个魔法花环。花环由若干灯泡组成，部分灯泡间用导线连接。迪马记得任意两个灯泡都直接或间接相连，且导线数量恰好比灯泡数量少一根（即构成树形结构）。

每个灯泡有独特的亮度，取决于其温度（可为正、负或零）。迪马想将花环分给两个朋友，需要剪断两根不同的导线，使花环分成三个部分，每个部分的温度总和相等。每个部分必须包含至少一个灯泡，且不能包含迪马手持的根节点。

输出应给出被剪断导线所悬挂的两个灯泡编号（非根节点）。若无法分割，输出-1。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)

## 输入样例
```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

## 输出样例
```
1 4
```

---

1. **唯一算法分类**  
无算法分类

---

2. **综合分析与结论**  
**核心思路**：  
- **条件检查**：总温度必须能被3整除，否则直接无解。  
- **子树和统计**：DFS遍历树，计算各子树的和。当某子树和为总和的1/3时，记录该子树根节点，并将该子树和置零（避免父节点重复计算）。  
- **结果判定**：若找到至少两个有效子树，则输出对应节点，否则无解。

**关键难点**：  
- 确保分割后的三个部分各自独立且不重叠。  
- 避免根节点被选为切割点。

**动态规划与可视化设计**：  
- **状态转移**：每个节点的子树和通过累加所有子节点和得到，公式为：  
  `sum[u] = val[u] + Σsum[v] (v为子节点)`  
- **置零操作**：当子树和达到目标值时，立即将其置零，防止父节点重复计数。  
- **可视化设计**：  
  - **动画效果**：树形结构逐层展开，满足条件的子树高亮显示并弹出"Cut"提示。  
  - **像素风格**：使用8位色块表示节点，绿色表示正常节点，红色表示已切割节点。  
  - **音效交互**：切割时播放"哔"声，成功找到解时播放胜利音效。  

---

3. **题解清单 (≥4星)**  
- **maniac！ (4.5星)**  
  思路清晰，代码简洁。关键点：及时置零子树和，避免重复计数。代码注释少但逻辑自洽。  
- **无咕_ (4星)**  
  使用`treesum`数组明确记录子树和，代码结构规范，适合教学。  
- **试试事实上吗 (4星)**  
  详细分析分割条件，附带示意图解释特殊案例，增强理解深度。  

---

4. **最优思路提炼**  
```cpp
void dfs(int u, int fa) {
    sum[u] = val[u];
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sum[u] += sum[v]; // 累加子树和
    }
    if (sum[u] == target) { // 达到目标值
        ans.push_back(u);
        sum[u] = 0; // 关键：置零避免重复
    }
}
```

---

5. **同类型题推荐**  
- **LeetCode 663** 均匀树划分  
- **洛谷 P2014** 选课（树形DP）  
- **洛谷 P3384** 轻重链剖分  

---

6. **个人心得摘录**  
> "在实现时，若不将满足条件的子树和置零，父节点会重复计算导致错误。调试时曾因此WA多次，后通过打印中间变量发现逻辑漏洞。" —— 作者：maniac！

---

7. **可视化与算法演示**  
**动画方案**：  
- **初始化**：根节点位于画布顶端，子节点按层级展开。  
- **遍历过程**：DFS路径以黄色光晕动态显示，当前处理节点高亮。  
- **切割判定**：满足条件的子树边框闪烁三次，并标记为红色。  
- **音效触发**：  
  - 每次节点处理完成：短促"滴"声。  
  - 切割成功：8-bit风格胜利旋律。  

**Canvas 实现片段**：  
```javascript
function drawNode(node, color) {
    ctx.fillStyle = color;
    ctx.fillRect(node.x, node.y, 30, 30); // 像素方块
    if (node.cut) {
        ctx.strokeStyle = '#FF0000';
        ctx.strokeRect(node.x-2, node.y-2, 34, 34); // 红色边框
    }
}
```

---

8. **复古游戏化设计**  
- **关卡设计**：  
  - 第1关：单层树，手动切割验证基础逻辑。  
  - 第2关：多层树，引入自动DFS演示。  
  - 第3关：复杂树形，限时寻找最优解。  
- **积分系统**：  
  - 正确切割：+100分。  
  - 错误尝试：-50分。  
  - 连击奖励：连续正确触发2倍积分。  

**音效文件**：  
```html
<audio id="cut-sound" src="8bit-cut.wav"></audio>
<audio id="win-sound" src="8bit-win.wav"></audio>
```

---
处理用时：96.68秒