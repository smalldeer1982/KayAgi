# 题目信息

# Equalize the Remainders

## 题目描述

You are given an array consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and a positive integer $ m $ . It is guaranteed that $ m $ is a divisor of $ n $ .

In a single move, you can choose any position $ i $ between $ 1 $ and $ n $ and increase $ a_i $ by $ 1 $ .

Let's calculate $ c_r $ ( $ 0 \le r \le m-1) $ — the number of elements having remainder $ r $ when divided by $ m $ . In other words, for each remainder, let's find the number of corresponding elements in $ a $ with that remainder.

Your task is to change the array in such a way that $ c_0 = c_1 = \dots = c_{m-1} = \frac{n}{m} $ .

Find the minimum number of moves to satisfy the above requirement.

## 样例 #1

### 输入

```
6 3
3 2 0 6 10 12
```

### 输出

```
3
3 2 0 7 10 14 
```

## 样例 #2

### 输入

```
4 2
0 1 2 3
```

### 输出

```
0
0 1 2 3 
```

# AI分析结果



## 唯一算法分类
**贪心算法**

---

## 综合分析与结论
### 核心思路与难点
题目要求通过最少的操作次数，使得每个余数出现次数相等。核心难点在于：
1. **余数环形特性**：当目标余数小于当前余数时，需绕一圈计算移动步数（如余数4转3需加 `m-1` 而非直接减1）。
2. **贪心分配策略**：将多余元素优先分配给最近的不足余数，保证操作次数最小。
3. **两次循环处理**：遍历余数两次（0~2m-1），解决第一次循环后剩余未处理的余数。

### 题解共性分析
各题解均采用以下步骤：
1. **按余数分组存储**：用 `vector<vector<int>>` 或队列保存每个余数的元素下标。
2. **多余元素队列**：将超过 `n/m` 的元素存入队列，供后续分配。
3. **环形遍历余数**：两次遍历余数（0~2m-1），确保所有余数被处理。
4. **步数计算**：根据目标余数与原余数的位置关系，计算最小移动步数。

### 可视化设计思路
1. **像素化余数网格**：将余数0~m-1排列为环形网格，每个格子显示当前余数的元素数量。
2. **高亮移动路径**：当元素从余数i转移到j时，用箭头动态展示移动路径，步数以颜色区分（绿色为短步，红色为长步）。
3. **队列动态显示**：用像素方块表示队列中的多余元素，每次分配时方块弹出并飞向目标余数格子。
4. **音效反馈**：移动时播放“滴”声，完成分配时播放上扬音效，失败时短促“嘟”声。

---

## 题解清单（评分≥4星）
1. **Tachibana27（★★★★☆）**
   - **亮点**：两次循环处理余数，特判余数绕环情况，代码逻辑清晰。
   - **关键代码**：
     ```cpp
     for(int i=0;i<2*m;i++) { // 遍历两次余数
         while(mod[i%m].size()>op) { // 多余元素入队
             lot.push({i%m, mod[i%m].back()});
             mod[i%m].pop_back();
         }
         while(mod[i%m].size()<op) { // 分配元素
             int yu = lot.front().first;
             int id = lot.front().second;
             a[id] += (i%m < a[id]%m) ? i-yu : (i%m - yu);
             ans += ...;
         }
     }
     ```

2. **wutiruo（★★★★☆）**
   - **亮点**：使用 `free` 队列动态维护多余元素，代码简洁高效。
   - **关键代码**：
     ```cpp
     for(int i=0; i<m*2; i++) { // 遍历两次
         while(v[cur].size()>k) // 入队多余元素
             free.push_back({p, i});
         while(free.size() && v[cur].size()<k) {
             int dj = i - mod; // 计算移动步数
             a[element] += dj;
             s += dj;
         }
     }
     ```

3. **jch123（★★★★☆）**
   - **亮点**：破环为链处理两次，用队列直接存储下标，实现简洁。
   - **关键代码**：
     ```cpp
     for(int i=0; i<2*m; i++) {
         while(p[i%m].size()>k) q.push(...);
         while(q.size() && p[i%m].size()<k) {
             int dis = (i%m < y) ? i%m + m - y : i%m - y;
             ans += dis;
         }
     }
     ```

---

## 最优思路与技巧提炼
### 关键技巧
1. **环形遍历余数**：遍历 `0~2m-1` 而非 `0~m-1`，确保所有余数被覆盖。
2. **队列动态分配**：用队列缓存多余元素，按需分配给后续余数。
3. **步数计算优化**：通过判断目标余数与原余数的大小，选择最短路径：
   ```cpp
   if (target < current) steps = target + m - current;
   else steps = target - current;
   ```

### 通用解法模板
```cpp
vector<vector<int>> mod(m);
queue<int> extra;
for (遍历元素) mod[a[i]%m].push_back(i);
for (i=0 到 2m-1) {
    while (mod[i%m].size() > n/m) 存到extra;
    while (mod[i%m].size() < n/m) 从extra取元素计算步数;
}
```

---

## 类似题目推荐
1. **CF1005D - Polycarp and Div 3**（余数分组与贪心）
2. **Luogu P3143 [USACO16OPEN]钻石收集者**（滑动窗口与余数平衡）
3. **LeetCode 358. Rearrange String k Distance Apart**（周期性分配元素）

---

## 可视化与复古游戏化设计
### 核心动画流程
1. **初始化界面**：屏幕顶部显示余数环形网格（8-bit像素风格），底部显示操作队列。
2. **元素移动动画**：当元素从余数i转移到j时，元素图标从i的格子飞向j的格子，路径显示为像素箭头。
3. **步数计数器**：右侧显示总操作次数，每次更新时数字滚动并伴随音效。

### 音效与交互
- **移动音效**：8-bit风格“滴”声，音调随步数长短变化。
- **完成提示**：所有余数平衡时播放胜利音乐，背景变为绿色闪烁。
- **交互控制**：支持暂停/继续，步进执行，速度调节（1x/2x/5x）。

### 复古像素实现（伪代码）
```javascript
// Canvas绘制余数网格
function drawGrid() {
    for (let i=0; i<m; i++) {
        ctx.fillStyle = (i === currentMod) ? '#FF5555' : '#5555FF';
        ctx.fillRect(x, y, 32, 32); // 32x32像素格子
        ctx.fillText(`Count: ${mod[i].length}`, x+5, y+15);
    }
}
// 元素移动动画
function animateElement(from, to) {
    const elem = document.getElementById(`elem-${id}`);
    elem.animate([
        {transform: `translate(${from.x}px, ${from.y}px)`},
        {transform: `translate(${to.x}px, ${to.y}px)`}
    ], {duration: 500});
    playSound('beep');
}
```

---

## 个人心得摘录
> **Tachibana27**：  
> “不开 long long 会见祖宗。”  
> —— 数据范围需注意，总操作次数可能超 `int`，必须用 `long long`。

> **jch123**：  
> “破环为链处理两次，避免前面的余数无法补偿。”  
> —— 两次遍历确保环形问题被线性处理。

> **Miracle_1024**：  
> “贪心不会证，但AC了！”  
> —— 贪心策略直觉正确性难以严格证明，但可通过构造测试验证。

---
处理用时：82.28秒