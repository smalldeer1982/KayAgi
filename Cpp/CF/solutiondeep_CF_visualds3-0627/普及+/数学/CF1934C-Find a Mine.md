# 题目信息

# Find a Mine

## 题目描述

This is an interactive problem.

You are given a grid with $ n $ rows and $ m $ columns. The coordinates $ (x, y) $ represent the cell on the grid, where $ x $ ( $ 1 \leq x \leq n $ ) is the row number counting from the top and $ y $ ( $ 1 \leq y \leq m $ ) is the column number counting from the left. It is guaranteed that there are exactly $ 2 $ mines in the grid at distinct cells, denoted as $ (x_1, y_1) $ and $ (x_2, y_2) $ . You are allowed to make no more than $ 4 $ queries to the interactor, and after these queries, you need to provide the location of one of the mines.

In each query, you can choose any grid cell $ (x, y) $ , and in return, you will receive the minimum Manhattan distance from both the mines to the chosen cell, i.e., you will receive the value $ \min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|) $ .

Your task is to determine the location of one of the mines after making the queries.

## 说明/提示

In the first test case, we start by querying the upper-left corner $ (1, 1) $ and get the result $ 3 $ , which means that there is a mine on the counter diagonal, and there is no mine above it.

In the image below, each cell contains a number indicating the distance to the blue cell. The green cells are candidates to contain the nearest mine.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9f8890c987cfc62ebf33297af68261e59cb82050.png)Then we ask three cells on that diagonal, and at the last query, we get the result $ 0 $ , which means that a mine is found at the position $ (2, 3) $ .

The second mine was located at the position $ (3, 2) $ .

In the second test case, we start by asking the lower-right corner $ (5, 5) $ , and get the result $ 1 $ , which means that one of the two neighbours contains a mine, let's call it mine $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/529c76a59b6e1128854ef8942281235840d099a4.png)Then we ask cell $ (2, 2) $ . We can see that these green cells don't intersect with the green cells from the first query, so they contain the other mine, let's call it mine $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/759e71e2b3a5d456c063d438414900b4ab40b3f1.png)Query $ 3 $ is cell $ (3, 3) $ . These cells contain mine $ 1 $ , but we still don't know where exactly. Nevertheless, we can determine that the only possible cell for mine $ 2 $ is $ (1, 1) $ , because all other candidates are at a distance closer than $ 3 $ for this query.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9b91f7f88f4e4ce648a34002d2c4a2f09feeedee.png)

## 样例 #1

### 输入

```
2
4 4

3

2

2

0

5 5

1

2

3```

### 输出

```
? 1 1

? 1 4

? 4 1

? 2 3

! 2 3

? 5 5

? 2 2

? 3 3

! 1 1```

# AI分析结果



## 算法分类
**几何**

---

## 综合分析与结论

### 核心逻辑
题目本质是几何问题，基于曼哈顿距离的几何特性（菱形区域）与对称性，通过构造特定询问缩小解空间。关键点如下：
1. **曼哈顿距离特性**：每次询问得到的距离对应一个菱形区域，地雷必在该区域边界上。
2. **对称性利用**：通过询问角落点（如(1,1)、(n,m)）确定地雷所在的对角线。
3. **解方程求交点**：多次询问后联立方程，解出曼哈顿距离约束下的交点。

### 解决难点
- **双地雷干扰**：需确保至少有一个解不受另一个地雷干扰。
- **整数解验证**：需判断解是否为整数且在网格范围内。
- **分类讨论优化**：通过特定询问顺序减少分支（如先查询角落点）。

### 可视化设计
1. **动态网格绘制**：在Canvas中绘制n×m网格，高亮每次查询点及其曼哈顿距离形成的菱形区域。
2. **交点标记**：联立方程时用不同颜色标记候选解，点击解可触发验证询问动画。
3. **像素风格**：
   - **颜色方案**：查询点用蓝色，菱形区域用半透明绿色，正确解用闪烁红点。
   - **音效**：查询时播放“哔”声，找到解时播放胜利音效。
4. **自动推导模式**：AI模拟最优路径，逐步显示方程联立过程，右侧面板显示当前方程。

---

## 题解评分（≥4星）

### [I_will_AKIOI] ⭐⭐⭐⭐
- **亮点**：对称性利用干净利落，代码仅需4次查询，逻辑分层清晰。
- **代码**：通过(1,1)确定对角线，两次端点查询锁定候选解，最终验证。

### [hgckythgcfhk] ⭐⭐⭐⭐
- **亮点**：系统化联立方程，通过三个角点覆盖所有可能，数学严谨性强。
- **公式推导**：联立 `(x+y=a+2)` 与 `(x-y=b-m+1)` 直接解出候选坐标。

### [StayAlone] ⭐⭐⭐⭐
- **亮点**：复用查询结果优化分支判断，代码中巧妙处理奇偶性验证。
- **代码片段**：通过位运算快速判断是否需要调整解。

---

## 最优思路与代码

### 核心公式推导
1. **第一次查询(1,1)**：得 `d1 = min(x1+y1-2, x2+y2-2)`。
2. **构造对角线方程**：若地雷在 `x+y = d1+2` 上，则后续查询端点 `(d1+1,1)` 或 `(1,d1+1)`。
3. **联立方程**：
   ```python
   # 例如查询(1,m)得d2后：
   x - y = d2 - m + 1
   x + y = d1 + 2
   # 解得：
   x = (d1 + d2 - m + 3) // 2
   y = d1 + 2 - x
   ```

### 代码实现（I_will_AKIOI方案）
```cpp
void solve() {
  int n,m,d[4];
  cin>>n>>m;
  cout<<"? 1 1"<<endl; cin>>d[0];
  int x1,y1,x2,y2;
  // 确定对角线端点
  x1 = (d[0]<n) ? d[0]+1 : n;
  y1 = (d[0]<n) ? 1 : d[0]+2-n;
  x2 = (d[0]<m) ? 1 : d[0]+2-m;
  y2 = (d[0]<m) ? d[0]+1 : m;
  // 查询端点
  cout<<"? "<<x1<<" "<<y1<<endl; cin>>d[1];
  cout<<"? "<<x2<<" "<<y2<<endl; cin>>d[2];
  // 计算候选坐标
  x1 -= d[1]/2; y1 += d[1]/2;
  x2 += d[2]/2; y2 -= d[2]/2;
  // 最终验证
  cout<<"? "<<x1<<" "<<y1<<endl; cin>>d[3];
  cout<<"! "<<(d[3]==0?x1:x2)<<" "<<(d[3]==0?y1:y2)<<endl;
}
```

---

## 同类型题与套路

### 常见套路
1. **曼哈顿镜像**：利用对称性将问题转化为单变量方程。
2. **极值点查询**：优先查询角落/中心点以最大化信息量。
3. **联立约束**：通过多次查询构建方程组，消元求解。

### 推荐题目
1. **P1433** - 吃奶酪（曼哈顿路径规划）
2. **CF1523D** - Love-Hate（位运算+几何约束）
3. **P3958** - 奶酪（三维几何+连通性）

---

## 可视化与复古演示

### 动画步骤
1. **初始化网格**：绘制n×m网格，坐标轴标签。
2. **首次查询**：点击(1,1)后，绘制蓝色菱形边界（距离d1）。
3. **对角线端点**：红色虚线连接对角线，高亮端点。
4. **二次查询**：点击端点后，绘制绿色菱形缩小范围。
5. **解算候选点**：黄色闪烁点表示两个候选解。
6. **最终验证**：点击候选点，正确解爆炸特效，错误解灰化。

### 复古特效
- **8位音效**：查询时8-bit“哔”声，正确解播放《超级马里奥》金币音效。
- **像素字体**：使用Press Start 2P字体显示坐标和结果。

---

## 个人心得摘录

### [Louis_lxy]
> “第一次做交互题，发现必须严格处理整数解验证，否则WA到怀疑人生。”

### [GameFreak]
> “边界条件处理是魔鬼，比如当d1+1超过n/m时，必须分类讨论端点。”

---

通过结合几何特性与系统性方程求解，本题展现了曼哈顿距离在交互题中的独特应用，其核心在于通过最少查询构建足够约束，快速缩小解空间。

---
处理用时：74.49秒