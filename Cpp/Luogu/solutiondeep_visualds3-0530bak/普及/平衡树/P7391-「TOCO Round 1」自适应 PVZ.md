# 题目信息

# 「TOCO Round 1」自适应 PVZ

## 题目背景

爆切今天的毒瘤三维计算几何后，$\color{black}\texttt{Q}\color{red}\texttt{wQcOrZ}$ 打开了某个有趣的 exe 文件。

## 题目描述

可怜的 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 在草坪上遇到了 $n$ 只僵尸，第 $i$ 只僵尸在 $l_i$ 时刻出现，会在 $r_i$ 时刻走进房子。

$\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 手头有 $m$ 个豌豆射手。若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外两只僵尸且攻击的僵尸不能更换。

现在 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 想知道在合理的安排下，最少有几只僵尸会进入他的房子。

## 说明/提示

对于 $30\%$ 的数据，$n,m\leq 6$。  
对于 $60\%$ 的数据，$n,m\leq 10^3$。  
对于另外 $20\%$ 的数据，$m\geq n$。  
对于 $100\%$ 的数据，$1\leq n,m\leq 2\times 10^5$，$1\leq l_i<r_i\leq 10^9$。

## 样例 #1

### 输入

```
2 1
1 2
3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2
1 3
1 3
2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2 1
1 3
3 5```

### 输出

```
0```

# AI分析结果



**唯一算法分类**：贪心算法（区间调度） + 数据结构优化

---

### **综合分析与结论**
**核心思路**：  
题目转化为经典区间调度问题——在 `m` 条时间轴上无重叠地安排尽可能多的区间。最优策略为按右端点升序排列僵尸，每次选择能覆盖当前僵尸且结束时间最晚的豌豆射手进行替换，最大化后续安排的灵活性。

**解决难点**：  
- **贪心证明**：需证明右端点排序后，替换结束时间最大的豌豆射手是局部最优且不影响全局最优。  
- **高效查找**：快速找到满足 `last_end ≤ l_i` 的最大 `last_end`，需借助有序数据结构（如 `multiset`）的 `upper_bound` 操作。  

**可视化设计**：  
- **动画演示**：Canvas 绘制时间轴，僵尸区间以不同颜色块表示，豌豆射手当前结束时间用竖线标记。  
- **关键操作高亮**：新僵尸区间闪烁，匹配的豌豆射手结束时间变红后更新为当前僵尸的右端点。  
- **步进控制**：允许单步执行，展示排序后的僵尸依次尝试匹配的过程。  
- **复古风格**：8-bit 像素风，音效提示匹配成功/失败，背景音乐循环播放。  

---

### **题解清单 (≥4星)**  
1. **吴思诚（5星）**  
   - **亮点**：代码简洁，利用 `multiset` 的 `upper_bound` 高效查找前驱，时间复杂度 `O(n log m)`。  
   - **核心代码**：  
     ```cpp
     sort(z+1,z+1+n,cmp);  // 按右端点排序
     for(i=1;i<=n;i++){
         it=s.upper_bound(z[i].l);  // 找第一个大于 l_i 的位置
         if(it!=s.begin()){         // 存在可用的豌豆射手
             s.erase(--it);         // 删除旧结束时间
             s.insert(z[i].r);      // 插入新结束时间
         } else if(s.size()<m) s.insert(z[i].r);
         else ans++;  // 无法安排
     }
     ```

2. **liaoxingrui（4星）**  
   - **亮点**：代码与吴思诚类似，但补充了清晰的注释和边界处理。  
   - **个人心得**：强调区间端点开闭对查找条件的影响（`upper_bound` 查 `l_i` 而非 `l_i+1`）。

3. **sunrise1024（4星）**  
   - **亮点**：按左端点排序，平衡树维护结束时间，处理三种情况（空闲、替换最早、替换最晚）。  
   - **关键代码**：  
     ```cpp
     if (当前有空闲) 插入新结束时间;
     else if (最早结束 ≤ l_i) 替换最早;
     else 比较最晚结束是否更大，决定是否替换;
     ```

---

### **最优思路提炼**  
**核心技巧**：  
1. **排序策略**：按右端点升序排列，保证每次选择局部最优。  
2. **数据结构选择**：`multiset` 维护豌豆射手的结束时间，`upper_bound` 查找前驱实现 `O(log m)` 操作。  
3. **替换逻辑**：优先使用结束时间最晚的可用射手，减少后续冲突。  

**同类型题套路**：  
- **区间分组**：如 [P4059 [Code+#1] 找爸爸](https://www.luogu.com.cn/problem/P4059)。  
- **最大不相交区间**：如 [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)。  

---

### **推荐相似题目**  
1. **P1803 凌乱的yyy / 线段覆盖**（基础贪心）  
2. **P4059 [Code+#1] 找爸爸**（动态规划+贪心优化）  
3. **P2949 [USACO09OPEN] Work Scheduling G**（带权区间调度）  

---

### **复古游戏化动画示例（伪代码）**  
```javascript
// Canvas 初始化
const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");
let zombies = [...]; // 已排序的僵尸数组
let peas = new SortedSet(); // 当前豌豆射手结束时间

function drawFrame() {
    // 绘制时间轴和僵尸区间
    zombies.forEach(z => drawRect(z.l, z.r, "blue"));
    peas.forEach(p => drawLine(p, "red"));

    // 高亮当前操作
    let currentZombie = zombies.shift();
    highlightRect(currentZombie.l, currentZombie.r);
    let it = peas.upperBound(currentZombie.l);
    if (it != peas.begin()) {
        playSound("select.wav");
        peas.erase(--it);
        peas.insert(currentZombie.r);
    } else if (peas.size < m) {
        peas.insert(currentZombie.r);
    } else {
        playSound("fail.wav");
        ans++;
    }
}
// 自动播放循环
setInterval(drawFrame, 1000);
```

**音效设计**：  
- **匹配成功**：8-bit 上升音阶  
- **替换操作**：短促“咔嚓”声  
- **匹配失败**：低沉嗡鸣声  

---

**总结**：本题通过贪心策略与高效数据结构的结合，展示了区间调度问题的经典解法。可视化设计可通过复古像素风格和交互式步进控制，直观呈现算法动态匹配过程。

---
处理用时：71.14秒