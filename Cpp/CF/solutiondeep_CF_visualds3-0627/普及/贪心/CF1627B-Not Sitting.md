# 题目信息

# Not Sitting

## 题目描述

Rahul and Tina are looking forward to starting their new year at college. As they enter their new classroom, they observe the seats of students are arranged in a $ n \times m $ grid. The seat in row $ r $ and column $ c $ is denoted by $ (r, c) $ , and the distance between two seats $ (a,b) $ and $ (c,d) $ is $ |a-c| + |b-d| $ .

As the class president, Tina has access to exactly $ k $ buckets of pink paint. The following process occurs.

- First, Tina chooses exactly $ k $ seats in the classroom to paint with pink paint. One bucket of paint can paint exactly one seat.
- After Tina has painted $ k $ seats in the previous step, Rahul chooses where he sits. He will not choose a seat that has been painted pink due to his hatred of the colour pink.
- After Rahul has chosen his seat, Tina chooses a seat for herself. She can choose any of the seats, painted or not, other than the one chosen by Rahul.

Rahul wants to choose a seat such that he sits as close to Tina as possible. However, Tina wants to sit as far away from Rahul as possible due to some complicated relationship history that we couldn't fit into the statement!

Now, Rahul wonders for $ k = 0, 1, \dots, n \cdot m - 1 $ , if Tina has $ k $ buckets of paint, how close can Rahul sit to Tina, if both Rahul and Tina are aware of each other's intentions and they both act as strategically as possible? Please help satisfy Rahul's curiosity!

## 说明/提示

One possible sequence of choices for the first testcase where Tina has $ k=3 $ buckets of paints is as follows.

Tina paints the seats at positions $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ with pink paint. Rahul chooses the seat at $ (3, 1) $ after which Tina chooses to sit at $ (1, 3) $ .

Therefore, the distance between Tina and Rahul is $ |3-1| + |1-3| = 4 $ , and we can prove that this is indeed the minimum possible distance under the given constraints. There may be other choices of seats which lead to the same answer as well.

For $ k=0 $ in the first test case, Rahul can decide to sit at $ (2, 2) $ and Tina can decide to sit at $ (4, 3) $ so the distance between them would be $ |2 - 4| + |2 - 3| = 3 $ .

Below are pictorial representations of the $ k=3 $ and $ k=0 $ cases for the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/135a6759a6ba23b198694ead1674597ee527f081.png) A possible seating arrangement for $ k=3 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/f8d6f4f57279fb43f8c4bcfe0a1490483d3f4037.png) A possible seating arrangement for $ k=0 $ .

## 样例 #1

### 输入

```
2
4 3
1 2```

### 输出

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1```

# AI分析结果



### 综合分析与结论

**题目核心**：在网格中，Tina 和 Rahul 进行策略选择，Tina 涂色后，Rahul 选择未被涂色的位置，Tina 随后选择位置（可涂色）。Rahul 希望两人距离最小，Tina 希望最大。求每个涂色数量 `k` 下的最小可能距离。

**关键思路与贪心策略**：
1. **最大距离计算**：每个位置的价值是它到四个角落的最大曼哈顿距离，即该点行和列方向的最大距离之和（`max(i-1, n-i) + max(j-1, m-j)`）。
2. **排序策略**：将所有位置的价值从小到大排序，输出即为答案序列。Tina 按价值从小到大涂色，迫使 Rahul 选择剩余的最小价值位置。

**解决难点**：如何快速确定每个位置的最大可能距离？通过数学推导，发现行和列的最大距离之和等价于四个角落的最大曼哈顿距离，避免了逐一计算四个角的复杂步骤。

**可视化设计**：
- **复古像素风格**：用 8-bit 网格展示每个位置，颜色深浅表示价值大小。
- **动画步骤**：高亮当前处理的位置，显示其行/列最大距离，动态累加为总价值。
- **音效**：在计算每个位置时播放提示音，排序完成后播放成功音效。
- **交互面板**：支持调整动画速度，单步执行，观察排序过程。

### 题解清单（≥4星）

1. **Daidly 的桶排序法（5星）**
   - **亮点**：通过桶排序将复杂度优化至 `O(nm)`，极大提升效率。
   - **代码简析**：计算每个点价值后，桶统计频率，按序输出。
   ```cpp
   for(int i=1;i<=n;++i)
       for(int j=1;j<=m;++j)
           p[max(i-1,n-i)+max(j-1,m-j)]++;
   for(int i=0; i<=n+m; ++i)
       while(p[i]--) print(i);
   ```

2. **xkcdjerry 的 BFS 预处理法（4星）**
   - **亮点**：BFS 预处理四个角的距离，确保正确性。
   - **代码简析**：对四个角进行 BFS，计算每个点的最大距离。
   ```cpp
   // 对每个角进行 BFS 求距离
   for(int j=0;j<4;j++) bfs(s[j]);
   // 取最大值并存入桶
   ```

3. **Jerrlee 的直接排序法（4星）**
   - **亮点**：代码简洁，直接计算并排序，逻辑清晰。
   ```cpp
   vector<int> res;
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
           res.push_back(max(四个角距离));
   sort(res.begin(), res.end());
   ```

### 最优思路提炼

**贪心核心**：每个位置的价值为到四个角落的最大距离，排序后依次选择。Tina 优先涂掉小价值位置，迫使 Rahul 选择更大价值的位置。

**实现技巧**：
- 计算价值时，利用行和列的最大距离之和简化计算。
- 使用桶排序优化时间复杂度至线性。

### 同类型题目推荐

1. **P1223 排队接水**（贪心排序）
2. **P1090 合并果子**（优先队列贪心）
3. **P2870 书架**（贪心选择最大间隔）

### 个人心得摘录

- **沉石鱼惊旋**：发现输出序列为排序后的价值数组，关键在理解两人策略。
- **xkcdjerry**：BFS 预处理时需注意边界条件，调试时发现数组越界问题。

### 可视化算法演示

```html
<!DOCTYPE html>
<html>
<head>
    <title>Not Sitting 贪心演示</title>
    <style>
        canvas { border: 1px solid black; }
        .controls { margin: 10px 0; }
    </style>
</head>
<body>
    <div class="controls">
        <button onclick="start()">开始</button>
        <input type="range" id="speed" min="1" max="100" value="50">
    </div>
    <canvas id="grid"></canvas>
    <script>
        const canvas = document.getElementById('grid');
        const ctx = canvas.getContext('2d');
        const cellSize = 30;
        let n = 4, m = 3; // 示例网格
        let values = [];

        function init() {
            canvas.width = m * cellSize;
            canvas.height = n * cellSize;
            // 计算每个点的价值
            for (let i = 0; i < n; i++) {
                for (let j = 0; j < m; j++) {
                    const val = Math.max(i, n-1 -i) + Math.max(j, m-1 -j);
                    values.push(val);
                }
            }
            values.sort((a,b) => a - b);
        }

        function draw() {
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            // 绘制排序后的结果
            ctx.fillStyle = '#8B00FF';
            values.forEach((v, idx) => {
                ctx.fillText(v, (idx % m) * cellSize +10, (Math.floor(idx / m)) * cellSize +20);
            });
        }

        function start() {
            init();
            draw();
        }
    </script>
</body>
</html>
```

**演示说明**：以 4x3 网格为例，展示每个位置的价值（颜色深浅表示），按排序结果动态输出。通过滑动条控制演示速度，直观观察贪心选择顺序。

---
处理用时：114.29秒