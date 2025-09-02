# 题目信息

# [USACO09MAR] Look Up S

## 题目描述

Farmer John's N (1 <= N <= 100,000) cows, conveniently numbered 1..N, are once again standing in a row. Cow i has height H\_i (1 <= H\_i <= 1,000,000).

Each cow is looking to her left toward those with higher index numbers. We say that cow i 'looks up' to cow j if i < j and H\_i < H\_j. For each cow i, FJ would like to know the index of the first cow in line looked up to by cow i.

Note: about 50% of the test data will have N <= 1,000. 

约翰的 $N(1\le N\le10^5)$ 头奶牛站成一排，奶牛 $i$ 的身高是 $H_i(1\le H_i\le10^6)$。现在，每只奶牛都在向右看齐。对于奶牛 $i$，如果奶牛 $j$ 满足 $i<j$ 且 $H_i<H_j$，我们可以说奶牛 $i$ 可以仰望奶牛 $j$。 求出每只奶牛离她最近的仰望对象。

Input

## 说明/提示

FJ has six cows of heights 3, 2, 6, 1, 1, and 2.


Cows 1 and 2 both look up to cow 3; cows 4 and 5 both look up to cow 6; and cows 3 and 6 do not look up to any cow.

【输入说明】$6$ 头奶牛的身高分别为 3,2,6,1,1,2。

【输出说明】奶牛 #1,#2 仰望奶牛 #3，奶牛 #4,#5 仰望奶牛 #6，奶牛 #3 和 #6 没有仰望对象。

【数据规模】

对于 $20\%$ 的数据：$1\le N\le10$；

对于 $50\%$ 的数据：$1\le N\le10^3$；

对于 $100\%$ 的数据：$1\le N\le10^5,1\le H_i\le10^6$。


## 样例 #1

### 输入

```
6 
3 
2 
6 
1 
1 
2 
```

### 输出

```
3 
3 
0 
6 
6 
0 
```

# AI分析结果



# 算法分类  
**单调栈**

# 题解思路与核心难点分析  
## 题解对比  
### [胡萝卜2333333333] 跳跃指针法（4星）  
**核心思路**：倒序遍历数组，每个元素通过跳跃式比较快速定位答案  
- 关键变量：`ans[i]` 存储答案，`j` 跳跃指针  
- 实现方式：  
  1. 初始比较右侧相邻元素  
  2. 若当前元素更大，则跳转到该元素答案指向的位置  
  3. 用 `while(a[i]>=a[j] && a[j]>0)` 避免死循环  

### [Seanq] 单调栈（5星）  
**核心思路**：维护递减栈，栈顶即最近的大元素  
- 关键数据结构：`stack<int>` 存储元素索引  
- 实现流程：  
  1. 倒序遍历元素  
  2. 弹出所有小于当前元素的栈顶元素  
  3. 栈顶即为当前元素答案  

### [蔡俊黠] 双端队列实现（4星）  
**创新点**：用 `deque` 替代栈，在队尾维护单调性  
- 优势：可直观处理区间相关问题  
- 核心代码：  
  ```cpp
  while(!q.empty()&&a[i].s>q.back().s) 
    ans[q.back().id]=i, q.pop_back();
  ```

# 最优思路提炼  
**关键技巧**：  
1. **逆向处理**：从右往左遍历，可复用已计算的结果  
2. **跳跃比较**：利用已有答案快速跳过无效比较（时间复杂度从O(n²)降为O(n)）  
3. **单调性维护**：通过栈/队列维护候选元素序列，保证每次操作均摊O(1)  

# 可视化算法设计  
## 动画演示方案  
**场景1：单调栈处理过程**  
![单调栈动画](https://i.imgur.com/VIPj5yG.gif)  
- **高亮元素**：当前处理的元素（红色）  
- **栈状态**：蓝色方块表示栈内元素，弹出时变为灰色  
- **步进逻辑**：  
  1. 元素6入栈（栈：[6]）  
  2. 元素1入栈（栈：[6,1]）  
  3. 处理元素2时，弹出两个1后入栈（栈：[6,2]）  

**场景2：跳跃指针法**  
- **指针轨迹**：用绿色箭头表示跳跃路径  
- **代码同步**：实时显示 `i=3` → `j=4` → `j=ans[4]=6`  

## 复古游戏化实现  
```javascript
// 伪代码：像素风格栈操作演示
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');

function drawStack() {
  ctx.fillStyle = '#3366CC'; // 栈元素颜色
  stack.forEach((val, idx) => {
    drawPixelBlock(val, 100 - idx*10); // 像素块绘制
  });
}

function playBeep() {
  const osc = audioCtx.createOscillator();
  osc.frequency.setValueAtTime(500, audioCtx.currentTime);
  osc.connect(audioCtx.destination);
  osc.start(); osc.stop(0.1);
}
```

# 同类型题目推荐  
1. [P1901 发射站](https://www.luogu.com.cn/problem/P1901)  
2. [P5788 模板-单调栈](https://www.luogu.com.cn/problem/P5788)  
3. [LeetCode 739. 每日温度](https://leetcode.cn/problems/daily-temperatures/)

# 个人调试心得摘录  
> "在跳跃指针法中，必须添加 `a[j]>0` 的判断条件，否则当j=0时会访问非法内存导致死循环" ——胡萝卜2333333333  
> "双端队列实现时，忘记判断队列空导致段错误，加!q.empty()后解决" ——蔡俊黠  

# 标准解法代码  
```cpp
#include <stack>
using namespace std;

const int MAXN = 1e5+5;
int H[MAXN], ans[MAXN];

void solve(int n) {
  stack<int> s;
  for(int i=n; i>=1; --i) {
    while(!s.empty() && H[s.top()] <= H[i]) 
      s.pop();
    ans[i] = s.empty() ? 0 : s.top();
    s.push(i);
  }
}
```

---
处理用时：61.18秒