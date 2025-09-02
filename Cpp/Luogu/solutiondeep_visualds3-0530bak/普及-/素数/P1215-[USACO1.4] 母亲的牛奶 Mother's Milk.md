# 题目信息

# [USACO1.4] 母亲的牛奶 Mother's Milk

## 题目描述

农民约翰有三个容量分别是 $a,b,c$ 升的桶。  

最初，$a,b$ 桶都是空的，而 $c$ 桶是装满牛奶的。有时，农民把牛奶从一个桶倒到另一个桶中，直到被灌桶装满或原桶空了。  

当然每一次灌注都是完全的。由于节约，牛奶不会有丢失。

写一个程序去帮助农民找出当 $a$ 桶是空的时候，$c$ 桶中牛奶所剩量的所有可能性。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a,b,c \le 20$。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
8 9 10
```

### 输出

```
1 2 8 9 10
```

## 样例 #2

### 输入

```
2 5 10```

### 输出

```
5 6 7 8 9 10```

# AI分析结果



# 母亲的牛奶 Mother's Milk 题解分析

## 唯一算法分类
**状态空间搜索（DFS/BFS）**

---

## 综合分析与结论
### 核心算法流程
1. **状态表示**：用三元组 `(a, b, c)` 表示三个桶的当前牛奶量
2. **状态转移**：枚举 6 种倒牛奶操作（A→B、A→C、B→A、B→C、C→A、C→B）
3. **剪枝优化**：使用三维数组 `vis[a][b][c]` 记录已访问状态
4. **结果收集**：当 a=0 时记录 c 的值，最后排序输出

### 核心难点与解决方案
- **状态爆炸问题**：通过容量限制（1-20）和状态判重将复杂度控制在 O(20^3)
- **倒牛奶计算**：使用 `min(可倒量, 目标桶剩余容量)` 确保转移合法
- **结果去重**：用数组直接记录所有可能的 c 值

---

## 题解清单（≥4星）

### 1. 远航之曲（★★★★☆）
- **关键亮点**：使用**递归式DFS**，通过双重循环处理6种倒法，代码简洁易理解
- **代码片段**：
```cpp
void dfs(int a[]) {
    if (vis[a[0]][a[1]][a[2]]) return;
    if (a[0] == 0) milk[a[2]] = true;
    for (int i = 0; i < 3; ++i) { // 从i倒向j
        for (int j = 0; j < 3; ++j) {
            int rec = min(bkt[j] - a[j], a[i]);
            int b[3] = {a[0], a[1], a[2]};
            b[i] -= rec, b[j] += rec;
            dfs(b);
        }
    }
}
```

### 2. Cambridge（★★★★☆）
- **关键亮点**：使用**BFS队列**实现层次遍历，结构清晰
- **个人心得**："小学时学习宽搜的实践经验让我选择了队列实现"

### 3. zhanghanbin（★★★★☆）
- **关键亮点**：详细注释六种倒法逻辑，新手友好
- **代码特色**：用独立条件分支处理每种倒法，便于调试

---

## 最优思路提炼
1. **状态压缩**：利用三维数组判重（容量≤20）
2. **转移计算**：`可倒量 = min(源桶量, 目标桶剩余空间)`
3. **结果处理**：直接标记结果数组，避免重复判断

---

## 同类题目推荐
1. P1214 [USACO1.4]等差数列（状态搜索）
2. P1379 八数码问题（状态空间BFS）
3. P1433 吃奶酪（状态压缩DP）

---

## 可视化方案设计
### 像素风格算法演示
**核心交互逻辑：**
```javascript
// Canvas初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const BUCKET_COLORS = ['#FF6B6B', '#4ECDC4', '#45B7D1']; // 红/青/蓝三色

function drawState(a, b, c) {
    ctx.clearRect(0, 0, 300, 200);
    // 绘制三个桶的像素化液面
    drawBucket(50, 20, a, BUCKET_COLORS[0]); 
    drawBucket(150, 20, b, BUCKET_COLORS[1]);
    drawBucket(250, 20, c, BUCKET_COLORS[2]);
    // 播放倒牛奶音效（8-bit风格）
    playSound('pour', 0.2);
}

function drawBucket(x, y, value, color) {
    // 绘制桶的像素化液面高度
    const height = Math.floor(value / maxCapacity * 80);
    ctx.fillStyle = color;
    ctx.fillRect(x, y + (80 - height), 40, height);
}
```

### 关键动画特性
1. **状态高亮**：当前操作的桶用闪烁边框标记
2. **操作轨迹**：倒牛奶时显示液体流动的像素箭头
3. **历史路径**：用半透明色块标记已访问状态
4. **音效系统**：
   - `search.wav`：状态访问时的电子音
   - `success.wav`：发现新解时的上升音阶
   - `error.wav`：重复访问时的警示音

---

## 经典实现代码
```cpp
// 远航之曲的核心DFS实现
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAX = 22;
bool milk[MAX] = {0}, vis[MAX][MAX][MAX] = {0};
int bkt[3];

void dfs(int a[]) {
    if (vis[a[0]][a[1]][a[2]]) return;
    vis[a[0]][a[1]][a[2]] = true;
    if (a[0] == 0) milk[a[2]] = true;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;
            int transfer = std::min(bkt[j] - a[j], a[i]);
            if (transfer > 0) {
                int next[3] = {a[0], a[1], a[2]};
                next[i] -= transfer;
                next[j] += transfer;
                dfs(next);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &bkt[0], &bkt[1], &bkt[2]);
    int init[3] = {0, 0, bkt[2]};
    dfs(init);
    for (int i = 0; i <= bkt[2]; ++i)
        if (milk[i]) printf("%d ", i);
    return 0;
}
```

---

## 学习建议
1. **调试技巧**：在DFS中添加状态打印语句，观察转移路径
2. **扩展思考**：如果将桶数量扩展到4个，算法需要如何修改？
3. **效率对比**：尝试实现BFS版本并比较两种方法的性能差异

---
处理用时：75.45秒