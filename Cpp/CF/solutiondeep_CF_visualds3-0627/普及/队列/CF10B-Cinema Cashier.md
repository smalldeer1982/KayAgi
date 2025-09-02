# 题目信息

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 样例 #1

### 输入

```
2 1
1 1
```

### 输出

```
1 1 1
-1
```

## 样例 #2

### 输入

```
4 3
1 2 3 1
```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1
```

# AI分析结果



**唯一算法分类**：暴力枚举 + 贪心优化

---

### 题解思路、算法要点与解决难点

**核心思路**：  
1. 对每波观众，枚举所有可能的行和连续座位起点  
2. 检查该座位段是否可用  
3. 计算该座位段的总曼哈顿距离  
4. 选择满足条件的最优座位段  

**关键优化点**：  
- **数学公式优化**：通过分段讨论将距离计算复杂度从 O(M) 降为 O(1)  
- **跳跃式检查**：发现不可用座位后，跳过后续无效位置（如第三题解的 `j += result.second`）  
- **贪心优先级**：按总距离→行号→左端点的优先级筛选最优解  

**解决难点**：  
1. 曼哈顿距离的快速计算  
2. 大规模座位可用性的高效检查  
3. 多条件择优的优先级处理  

---

### 题解清单（≥4星）

1. **404Not_Found（4.5星）**  
   - 使用树状数组优化区间查询  
   - 数学推导距离计算公式  
   - 时间复杂度 O(nk²logk)  

2. **一铭君一（4星）**  
   - 纯暴力但代码简洁  
   - 加入跳跃式检查优化  
   - 时间复杂度 O(nk²)  

3. **YNH_QAQ（4星）**  
   - 最直观的暴力实现  
   - 明确展示核心判断逻辑  
   - 适合快速理解题意  

---

### 最优思路提炼

**核心技巧**：  
1. **中心对称性**：利用曼哈顿距离的对称性，将距离计算分解为行差和列差  
2. **分段求和公式**：  
   ```math
   \sum_{y=start}^{end} |y - mid| = 
   \begin{cases} 
   \frac{(start + end)(end - start + 1)}{2} - m \cdot mid & \text{if } start \geq mid \\
   m \cdot mid - \frac{(start + end)(end - start + 1)}{2} & \text{if } end \leq mid \\
   \text{分段计算} & \text{otherwise}
   \end{cases}
   ```
3. **贪心优先级队列**：通过三级条件（总距离→行号→左端点）维护候选最优解  

---

### 可视化算法演示设计

**动画要素**：  
1. **电影院网格**：以棋盘格展示座位，已占座位显示为红色  
2. **扫描过程**：  
   - 当前扫描行高亮为黄色  
   - 候选座位段显示为绿色闪烁框  
   - 不可用段立即变红并跳过  
3. **距离计算**：  
   - 实时显示当前候选段的总距离值  
   - 最优解用金色边框标记  

**复古风格实现**：  
```javascript
// 伪代码示例
class CinemaAnimation {
  constructor(k) {
    this.canvas = document.createElement('canvas');
    this.ctx = this.canvas.getContext('2d');
    this.pixelSize = 16; // 8位风格像素大小
    this.colors = ['#000', '#F00', '#0F0', '#FF0', '#FFF']; // 经典FC配色
  }

  drawSeat(x, y, state) {
    this.ctx.fillStyle = this.colors[state];
    this.ctx.fillRect(x*pixelSize, y*pixelSize, pixelSize, pixelSize);
  }

  highlightScanRow(row) {
    // 行扫描动画
    for(let i=0; i<k; i++) {
      this.drawSeat(i, row, 3); // 黄色高亮
    }
  }
}
```

**音效设计**：  
- `seat_available.wav`：轻快的电子音（找到候选座位）  
- `best_solution.wav`：上升和弦（更新最优解）  
- `final_choice.wav`：胜利音效（确定最终座位）  

---

### 同类型题目推荐

1. **P1056 排座椅** - 类似的行列选择与最优安排  
2. **P1661 扩散** - 曼哈顿距离的动态传播  
3. **P2895 [USACO08FEB] Meteor Shower S** - 带时间约束的最优路径  

---

### 关键代码片段

**数学优化版距离计算**：  
```cpp
int calculate_cost(int x, int y, int m, int mid) {
    int cost = m * abs(x - mid);
    if (y >= mid) {
        cost += (y + y + m - 1) * m / 2 - mid * m;
    } else if (y + m - 1 <= mid) {
        cost += mid * m - (y + y + m - 1) * m / 2;
    } else {
        // 分段计算
        int left_len = mid - y;
        int right_len = y + m - 1 - mid;
        cost += (mid*(mid+1) - y*(y-1))/2 - (mid*(mid-1) - (y+left_len-1)*(y+left_len))/2;
    }
    return cost;
}
```

**跳跃式检查优化**：  
```cpp
for(int j=1; j<=k; j++) {
    if(!sits[i][j]) {
        auto result = check_seats(i, j, m);
        if (!result.valid) {
            j += result.checked; // 跳过已检查的无效位置
        }
    }
}
```

---

**可视化演示示例**：  
![Cinema Scanning Demo](https://via.placeholder.com/400x300/000/fff?text=Scanning+Row+3)  
*图示：正在扫描第3行，绿色框为候选座位，红色块为已占座位*

---
处理用时：79.43秒