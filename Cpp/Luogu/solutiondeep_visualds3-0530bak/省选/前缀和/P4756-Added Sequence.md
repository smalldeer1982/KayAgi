# 题目信息

# Added Sequence

## 题目描述

小$L$发明了一种新的数据结构，并将其命名为$L$数组。$L$数组的作用是可以在$O(1)$时间内将整个数组加上或减去一个数。现在给你一个长度为$N$的数组$a$，他想用$L$数组来挑战你的计算能力。

定义$f(i,j)=|\sum_{p=i}^{j} a_p|$其中$|x|$表示$x$的绝对值。

定义一个数组的美丽度为$\max_{1 \le i \le j \le N} f(i,j)$，每当他将整个数组加上$x$ ，请你回答此时的美丽度。

注意，你的算法必须为在线的。

## 说明/提示

四次加上的数字分别为-7，-4，-2，1。

$1 \le N,M \le 200000$

$|a_i| \le 200000$

$0 \le x_i \le 800000$

## 样例 #1

### 输入

```
4 4
4 5 6 7
1
15
0
12```

### 输出

```
6
6
14
26
```

# AI分析结果



# 算法分类：凸包/平面几何

## 综合分析与结论
**核心思路**：将前缀和视为一次函数pre_i(x) = pre_i + i*x，维护上凸包（最大值）和下凸包（最小值）。查询时二分找到x对应的极值点，计算极差。

**解决难点**：
1. 将动态全局加减转化为前缀和的一次函数形式
2. 利用凸包性质快速找到极值点
3. 处理强制在线查询的高效性要求

**可视化设计**：
1. **动画方案**：
   - 用两条不同颜色的折线分别绘制上下凸包
   - 动态显示x轴垂直线扫过凸包，高亮当前查询的x值
   - 在凸包交点处显示极值点坐标和差值计算过程
2. **复古风格**：
   - 使用16色像素调色板（红色上凸包、蓝色下凸包）
   - 用8-bit音效在二分查找时播放不同音调
   - Canvas绘制网格坐标系，关键点用闪烁方块表示
3. **交互功能**：
   - 滑动条控制x值变化，实时更新极差计算结果
   - 单步模式展示二分查找过程，显示当前mid值

## 题解清单（评分≥4星）
1. **FlierKing（5星）**
   - 亮点：利用凸包交点的数学推导，时间复杂度O(n log n)
   - 关键代码：预处理凸包后二分查询极值点
   ```cpp
   while(mxn&&cal(i,mx[mxn])<=cal(i,mx[mxn-1]))--mxn; // 维护上凸包
   while(mnn&&cal(i,mn[mnn])>=cal(i,mn[mnn-1]))--mnn; // 维护下凸包
   ```
   
2. **Trinity（4星）**
   - 亮点：详细推导交点计算公式x=-a_{i+1}，降低计算量
   - 调试心得："完全搞懂这个毒瘤题的凸包花了一个星期"

3. **asd_a（4星）**
   - 亮点：创新使用李超线段树维护极值函数
   - 关键优化：将问题转化为线段树维护最大/最小线性函数

## 最优思路提炼
**关键技巧**：
1. **凸包预处理**：将前缀和视为直线，利用单调栈维护凸包
2. **二分定位**：根据x值在凸包线段上的位置快速计算极值
3. **坐标变换**：通过(x + pre_ans) mod处理强制在线查询

**同类型题套路**：
- 带权区间最值问题（如最大子矩阵和）
- 动态直线集极值查询（李超树应用）
- 分治合并凸包求闵可夫斯基和

## 推荐题目
1. P5495【模板】二维凸包
2. P5785 [SDOI2012]任务安排（凸包优化DP）
3. P4655 [CEOI2017]Building Bridges（李超线段树）

## 核心代码实现
**凸包预处理与查询**（FlierKing解法核心）：
```cpp
// 预处理凸包
for(int i=1;i<=n;i++){
    while(mxn && cal(i,mx[mxn])<=cal(i,mx[mxn-1])) mxn--;
    mx[++mxn]=i; // 上凸包
    while(mnn && cal(i,mn[mnn])>=cal(i,mn[mnn-1])) mnn--;
    mn[++mnn]=i; // 下凸包
}

// 查询处理
ll query(int x){
    int l=1, r=mxn, a=0;
    while(l<=r){ // 二分上凸包
        int mid=(l+r)/2;
        if(x >= mxp[mid]) a=mx[mid], l=mid+1;
        else r=mid-1;
    }
    // 同理处理下凸包...
    return (a-b)*x + s[a]-s[b];
}
```

## 可视化代码片段（JS Canvas）
```javascript
function drawConvexHull(ctx, points, color) {
    ctx.strokeStyle = color;
    ctx.beginPath();
    points.forEach((p,i) => {
        const x = p.x * scale + offsetX, y = height - (p.y * scale + offsetY);
        if(i === 0) ctx.moveTo(x, y);
        else ctx.lineTo(x, y);
    });
    ctx.stroke();
}

// 动画更新查询线
function animateQueryLine(x) {
    const lineX = x * scale + offsetX;
    ctx_demo.clearRect(0, 0, width, height);
    drawConvexHull(ctx_demo, upperHull, '#ff0000');
    drawConvexHull(ctx_demo, lowerHull, '#0000ff');
    ctx_demo.strokeStyle = '#00ff00';
    ctx_demo.beginPath();
    ctx_demo.moveTo(lineX, 0);
    ctx_demo.lineTo(lineX, height);
    ctx_demo.stroke();
}
```

## 个人心得摘录
- "调试时发现凸包交点计算必须用交叉积判断，浮点精度容易出错"（Trinity）
- "强制在线实际上是纸老虎，关键在数学模型的转换"（mrsrz）
- 李超树解法中："将每个前缀和视为y=kx+b的直线，极大简化了问题"（asd_a）

## 游戏化设计
1. **音效设计**：
   - 二分查找时播放"哔-哔"音效（Web Audio合成方波）
   - 正确查询时播放8-bit胜利音效
2. **积分系统**：
   - 每次正确查询+10分，连续正确获得×2连击
   - 超过阈值解锁"凸包大师"成就
3. **自动演示模式**：
   - 模拟AI逐步构建凸包，用不同颜色高亮被弹出的栈顶元素
   - 查询时显示二分查找的光标移动轨迹

---
处理用时：66.64秒