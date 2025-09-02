# 题目信息

# Tavas and Pashmaks

## 题目描述

现在有两个比赛项目:跑步和游泳.每一个人在这两个项目都有一个正整数的值,第i个人分别为$a_i,b_i$,表示他在这个项目上的速度.
我们假定游泳的距离为$S_1$,跑步的距离为$S_2$(都是**正实数**),知道每一个人的值,如果对于第i个人,存在这样子的$S_1$和$S_2$使得$S_1/a_i+S_2/b_i<=S_1/a_j+S_2/b_j(1<=j<=n)$,那么就称这个人可以夺冠.
求出有多少个人可以夺冠.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
3
1 2
1 1
2 1
```

### 输出

```
1 3 
```

# AI分析结果



## 算法分类
凸包/计算几何

---

## 综合分析与结论

### 核心思路
将每个选手的 (1/a_i, 1/b_i) 视为二维平面上的点，寻找其左下凸包。只有位于左下凸包上的点才可能成为最优解，因为对于任意正实数 S1/S2 的比例，总能找到一条斜率为负的直线，使得该点对应的总时间最小。

### 解决难点
1. **几何转换**：将时间比较问题转化为凸包问题需要深入理解线性组合的几何意义。
2. **凸包构建**：需处理斜率为负的下凸壳，维护单调递减的斜率序列。
3. **去重优化**：相同 x 坐标的点需保留 y 最大的点，极大减少无效计算。

### 可视化设计
1. **Canvas 绘制**：以坐标系展示所有点，动态绘制凸包构建过程
2. **颜色标记**：
   - 红色：当前处理点
   - 绿色：已加入凸包的点
   - 灰色：被弹出的点
3. **步进控制**：可单步执行栈操作，观察斜率比较过程
4. **音效提示**：
   - 加入凸包时播放高音"哔"
   - 弹出栈顶时播放低音"咚"

---

## 题解清单（≥4星）

### 1. mrsrz 题解（★★★★★）
**亮点**：
- 严格的数学推导，清晰的凸包证明
- 代码中处理重复点的 id 数组设计巧妙
- 使用浮点数精确处理避免精度丢失

### 2. 宇智波—鼬 题解（★★★★）
**亮点**：
- 预处理阶段快速排除无效点
- 使用长整型避免浮点运算误差
- 代码注释详细，适合初学者理解

### 3. _Felix 题解（★★★★）
**亮点**：
- 坐标转换的直观解释
- 对前两者的关键补充说明
- 重点标注易错点的警示

---

## 最优思路提炼

### 关键步骤
1. **坐标转换**：将速度转换为 (1/a_i, 1/b_i)
2. **预处理排序**：
   ```python
   sorted_points = sorted(points, key=lambda x: (x.x, -x.y))
   ```
3. **单调栈构建凸包**：
   ```python
   for p in points:
       while len(stack)>=2 and slope(stack[-2],p) <= slope(stack[-1],p):
           stack.pop()
       stack.append(p)
   ```
4. **筛选有效斜率**：只保留斜率 < 0 的凸包部分

### 核心技巧
- **反比例处理**：用倒数转换将速度问题转化为几何问题
- **双精度优化**：比较斜率时使用交叉相乘避免除零错误
- **等效点合并**：相同坐标的点直接加入结果集

---

## 相似题目推荐
1. P2742 [USACO5.1] 圈奶牛 (二维凸包模板)
2. P3517 [POI2011]WYK-Plot (凸包+二分答案)
3. CF605E Intergalaxy Trips (概率与几何结合)

---

## 代码核心片段

### 凸包构建（mrsrz 解法）
```cpp
// 排序去重
std::sort(q+1,q+n+1);
p[1]=q[1];m=1;
for(int i=2;i<=n;++i)
    if(fabs(q[i].x-q[i-1].x)>1e-9)p[++m]=q[i];

// 单调栈维护凸包
sta[1]=1,sta[2]=2;
for(int i=3;i<=m;++i){
    while(top>1&&slope(sta[top-1],sta[top])>slope(sta[top-1],i))--top;
    sta[++top]=i;
}

// 筛选负斜率部分
for(int i=2;i<=top;++i)
    if(slope(sta[i-1],sta[i])<0){
        // 加入结果集
    }else break;
```

---

## 可视化伪代码

```javascript
class ConvexHullAnimation {
    constructor(canvas) {
        this.points = []; // 所有点坐标
        this.stack = [];  // 当前凸包栈
        this.step = 0;    // 当前执行步骤
    }

    nextStep() {
        const p = this.points[this.step];
        // 绘制当前点（红色）
        drawPoint(p, 'red');
        
        while(this.stack.length >= 2) {
            const slope1 = calculateSlope(this.stack[this.stack.length-2], this.stack[this.stack.length-1]);
            const slope2 = calculateSlope(this.stack[this.stack.length-2], p);
            if(slope1 > slope2) {
                // 弹出栈顶，播放音效
                this.stack.pop();
                playSound('pop');
            } else break;
        }
        
        this.stack.push(p);
        // 绘制凸包连线（绿色）
        drawLine(this.stack[this.stack.length-2], p, 'green');
        this.step++;
    }
}
```

---

## 个人心得
- **精度陷阱**：浮点比较需用 epsilon（如 1e-9），直接等号比较会 WA
- **思维转换**：将速度的倒数视为坐标是解题关键突破点
- **调试技巧**：手动画二维坐标系验证凸包结果，比直接看数据更直观

---
处理用时：79.78秒