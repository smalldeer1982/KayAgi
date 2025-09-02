# 题目信息

# Sand Fortress

## 题目描述

You are going to the beach with the idea to build the greatest sand castle ever in your head! The beach is not as three-dimensional as you could have imagined, it can be decribed as a line of spots to pile up sand pillars. Spots are numbered $ 1 $ through infinity from left to right.

Obviously, there is not enough sand on the beach, so you brought $ n $ packs of sand with you. Let height $ h_{i} $ of the sand pillar on some spot $ i $ be the number of sand packs you spent on it. You can't split a sand pack to multiple pillars, all the sand from it should go to a single one. There is a fence of height equal to the height of pillar with $ H $ sand packs to the left of the first spot and you should prevent sand from going over it.

Finally you ended up with the following conditions to building the castle:

- $ h_{1}<=H $ : no sand from the leftmost spot should go over the fence;
- For any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/77d67b6184b30d84bfc3e3e2794dc8de9b20fcf2.png) $ |h_{i}-h_{i+1}|<=1 $ : large difference in heights of two neighboring pillars can lead sand to fall down from the higher one to the lower, you really don't want this to happen;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/7c65b11667de38fcb78de5945051b7b0879e1abf.png): you want to spend all the sand you brought with you.

As you have infinite spots to build, it is always possible to come up with some valid castle structure. Though you want the castle to be as compact as possible.

Your task is to calculate the minimum number of spots you can occupy so that all the aforementioned conditions hold.

## 说明/提示

Here are the heights of some valid castles:

- $ n=5,H=2,[2,2,1,0,...],[2,1,1,1,0,...],[1,0,1,2,1,0,...] $
- $ n=6,H=8,[3,2,1,0,...],[2,2,1,1,0,...],[0,1,0,1,2,1,1,0...] $ (this one has $ 5 $ spots occupied)

The first list for both cases is the optimal answer, $ 3 $ spots are occupied in them.

And here are some invalid ones:

- $ n=5,H=2,[3,2,0,...],[2,3,0,...],[1,0,2,2,...] $
- $ n=6,H=8,[2,2,2,0,...],[6,0,...],[1,4,1,0...],[2,2,1,0,...] $

## 样例 #1

### 输入

```
5 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 8
```

### 输出

```
3
```

# AI分析结果



## 算法分类
二分答案、数学推导

---

## 题解思路与核心难点

### 核心思路
题目要求用最少的沙堆位置满足三个条件。关键在于构造合法的沙堆序列并计算总沙袋数。所有题解均围绕如何快速判断给定位置数是否合法展开：

1. **二分答案法**：通过二分可能的位置数 k，计算该情况下最大可能的沙袋总和。需分两种情况：
   - k ≤ H：序列为递减等差数列，总和为 k*(k+1)/2
   - k > H：序列先递增到峰顶后递减，总和由两个等差数列组成（奇偶不同）

2. **数学推导法**：直接计算最小位置数：
   - 当 H 足够大时，直接解等差数列方程
   - 否则构造先增后减的峰形序列，通过平方根公式计算所需位置

### 解决难点
- **构造合法序列**：需确保相邻高度差 ≤1，且总和恰好为 n
- **避免溢出**：大数计算需用 long long 或 double
- **数学公式推导**：将问题转化为二次方程求解，快速定位最优解

---

## 题解评分 (≥4星)

1. **___new2zy___ (5星)**  
   - 思路清晰，详细分奇偶讨论峰形结构  
   - 代码结构严谨，二分条件处理到位  
   - 包含可视化公式推导图，易于理解

2. **cff_0102 (4星)**  
   - 数学推导简洁，直接分情况给出公式  
   - 代码实现简短高效  
   - 缺少详细推导过程，对数学基础要求较高

3. **Xiao_mo (4星)**  
   - 分情况讨论明确，代码逻辑清晰  
   - 处理大数时用 double 避免溢出  
   - 包含调试注释，实践性强

---

## 最优思路提炼
**数学分情况法**：  
1. **当 H 足够大**（H*(H+1)/2 ≥ n）：
   - 直接解方程 x(x+1)/2 ≥ n → x = ceil[(√(8n+1)-1)/2]
   
2. **当 H 较小**：
   - 构造峰形序列，总沙袋数为 H 的等差数列 + 峰顶扩展部分
   - 计算 x = ceil[2√(n + H(H-1)/2)] - H

---

## 同类型题推荐
1. CF679B - Bear and Tower of Cubes (构造最优堆叠)
2. LeetCode 441 - Arranging Coins (等差数列二分)
3. 洛谷 P1873 - 砍树 (二分答案经典题)

---

## 个人心得摘录
> "熬到深夜推导公式，终于搞懂奇偶分界时的不同求和方式。测试样例时要特别注意边界情况，比如 n 刚好等于某个等差数列和时是否要 +1。" —— ___new2zy___

---

## 可视化算法演示

### 动画设计
1. **像素风格沙堆**：  
   - 用不同颜色方块表示沙堆高度（红色=高，绿色=低）  
   - 峰顶用金色高亮，动态展示递增/递减过程

2. **关键步骤高亮**：  
   - 二分时用黄色标记当前检查的 k 值  
   - 计算总和时用进度条显示当前值 vs n

3. **音效提示**：  
   - 每次二分调整时播放 "beep" 音  
   - 找到解时播放 8-bit 胜利旋律

### 代码片段 (JavaScript)
```javascript
// 绘制峰形沙堆
function drawPeak(H, x) {
  let canvas = document.getElementById('sand-canvas');
  let ctx = canvas.getContext('2d');
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  // 绘制递增部分
  for (let i = 0; i < x; i++) {
    let height = H + i;
    drawBlock(i * 20, 100 - height * 10, height);
  }
  
  // 绘制递减部分
  let peak = H + x - 1;
  for (let i = x; i < totalBlocks; i++) {
    let height = peak - (i - x + 1);
    drawBlock(i * 20, 100 - height * 10, height);
  }
}
```

---

## 核心代码实现
```cpp
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    long long n, H;
    cin >> n >> H;
    
    long long x = (sqrt(8 * n + 1) - 1) / 2; // 等差数列解
    if (x <= H) {
        cout << (x*(x+1)/2 >= n ? x : x+1);
        return 0;
    }
    
    // 峰形结构解
    long long ans = ceil(2 * sqrt(n + H*(H-1)/2.0)) - H;
    cout << ans;
    return 0;
}
```

---
处理用时：97.01秒