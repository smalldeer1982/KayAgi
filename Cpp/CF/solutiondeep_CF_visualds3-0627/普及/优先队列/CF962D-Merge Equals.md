# 题目信息

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1
```

### 输出

```
4
3 8 2 1 
```

## 样例 #2

### 输入

```
5
1 1 3 1 1
```

### 输出

```
2
3 4 
```

## 样例 #3

### 输入

```
5
10 40 20 50 30
```

### 输出

```
5
10 40 20 50 30 
```

# AI分析结果



# 【唯一算法分类】
优先队列（堆）

# 【综合分析与结论】

## 核心思路
1. **优先队列维护最小元素**：通过优先队列以数值为第一关键字、位置为第二关键字排序，确保每次取出最小的可合并元素。
2. **合并策略**：取出两个最小元素，若相同则合并为双倍值并放回队列，不同则保留第一个元素。
3. **顺序维护**：最终结果按原始位置排序输出，保证元素顺序正确。

## 解决难点
1. **动态维护最小元素**：优先队列自动维护全局最小值，避免手动遍历查找。
2. **合并后的再处理**：合并后的元素需重新入队参与后续合并，保证所有可能的合并都被处理。
3. **位置记录**：合并时保留右端位置，最终按位置排序维持原数组顺序。

## 可视化设计
- **动画流程**：以网格展示数组元素，优先队列显示为动态列表。每次合并时高亮操作的两个元素，合并后显示新值。
- **像素风格**：使用 8-bit 风格色块表示元素值，合并时触发像素音效，背景播放复古芯片音乐。
- **操作面板**：支持暂停/继续、单步执行、速度调节，可观察队列变化和合并过程。

# 【题解清单 (≥4星)】

1. **Bitter_Tea（4星）**
   - **亮点**：简洁的堆实现，结构体运算符重载清晰，处理合并逻辑直接。
   - **代码**：完整展示优先队列操作和结果排序，可读性强。

2. **chenxia25（方法1，4星）**
   - **亮点**：双优先队列分离处理过程和结果存储，逻辑分层明确。
   - **优化**：使用 `make_pair` 简化代码，分离答案队列避免频繁排序。

3. **Milmon（4星）**
   - **亮点**：代码极简，仅用单个优先队列和答案数组，合并与存储一气呵成。
   - **技巧**：负数处理避免自定义比较函数，直接利用 `greater<pair>` 实现小根堆。

# 【最优思路/技巧提炼】

1. **双关键字堆排序**  
   ```cpp
   struct Node { 
       ll val; int pos;
       bool operator<(const Node& x) const {
           return val != x.val ? val > x.val : pos > x.pos; // 小根堆
       }
   };
   ```
   通过自定义优先队列排序规则，保证每次取出最小值和最左位置。

2. **动态合并再入队**  
   ```cpp
   while (heap.size() >= 2) {
       auto a = heap.top(); heap.pop();
       auto b = heap.top(); heap.pop();
       if (a.val == b.val) {
           heap.push({a.val*2, b.pos}); // 合并后放回右端位置
       } else {
           ans.push_back(a);
           heap.push(b);
       }
   }
   ```
   持续合并直到无法操作，保留未合并元素。

3. **结果位置排序**  
   ```cpp
   sort(ans.begin(), ans.end(), [](auto& x, auto& y){ 
       return x.pos < y.pos; 
   });
   ```
   最终按原始位置排序输出，维持数组顺序。

# 【同类型题与算法套路】

1. **合并类问题**：如 Huffman 编码（合并最小两节点）、区间合并等，均适用优先队列。
2. **动态最小值维护**：滑动窗口最小值、实时数据处理等场景。

# 【相似洛谷题目】

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   **共同点**：优先队列合并最小元素。

2. [P6033 合并果子加强版](https://www.luogu.com.cn/problem/P6033)  
   **扩展**：大数据量下的桶排序优化。

3. [P2168 荷马史诗](https://www.luogu.com.cn/problem/P2168)  
   **变形**：k 叉哈夫曼树，多元素合并策略。

# 【个人心得摘录】

> **chenxia25调试经验**：  
> “初始实现未考虑位置排序，导致第二个样例错误。添加位置比较后AC，强调双关键字缺一不可。”

> **Milmon实现技巧**：  
> “利用负数简化比较函数，避免手写复杂运算符，减少代码量。”

# 【可视化算法演示】

```html
<!DOCTYPE html>
<html>
<body>
  <canvas id="canvas" width="800" height="400"></canvas>
  <div>
    <button onclick="togglePause()">暂停/继续</button>
    <input type="range" id="speed" min="1" max="10" value="5">
  </div>
  <script>
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    let arr = [3,4,1,2,2,1,1]; // 初始数组
    let heap = arr.map((v,i) => ({val:v, pos:i}))
                  .sort((a,b) => a.val - b.val || a.pos - b.pos);
    let ans = [];
    let paused = false;
    let step = 0;

    function draw() {
      ctx.fillStyle = '#2C3E50';
      ctx.fillRect(0, 0, 800, 400);
      // 绘制当前数组
      arr.forEach((v, i) => {
        ctx.fillStyle = step === i ? '#E74C3C' : '#3498DB';
        ctx.fillRect(50 + i*70, 150, 50, 50);
        ctx.fillStyle = 'white';
        ctx.fillText(v, 70 + i*70, 180);
      });
      // 绘制优先队列
      heap.forEach((node, i) => {
        ctx.fillStyle = '#27AE60';
        ctx.fillRect(600, 50 + i*40, 150, 30);
        ctx.fillText(`${node.val}@${node.pos}`, 610, 70 + i*40);
      });
    }

    function update() {
      if (heap.length < 2) return;
      let a = heap.shift();
      let b = heap.shift();
      if (a.val === b.val) {
        heap.push({val:a.val*2, pos:b.pos});
        arr[b.pos] = a.val*2;
        arr[a.pos] = null;
      } else {
        ans.push(a);
        heap.unshift(b);
      }
      heap.sort((x,y) => x.val - y.val || x.pos - y.pos);
    }

    setInterval(() => {
      if (!paused) {
        update();
        step = (step + 1) % arr.length;
        draw();
      }
    }, 1000 - document.getElementById('speed').value * 80);

    function togglePause() { paused = !paused; }
    draw();
  </script>
</body>
</html>
```

**实现要点**：
- **颜色高亮**：当前操作元素红色显示，队列绿色区分。
- **动态排序**：每次操作后重新排序堆，模拟优先队列行为。
- **速度控制**：滑动条调节动画速度，适合不同学习节奏。

---
处理用时：105.47秒