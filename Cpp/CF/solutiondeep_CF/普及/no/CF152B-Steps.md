# 题目信息

# Steps

## 题目描述

One day Vasya went out for a walk in the yard but there weren't any of his friends outside and he had no one to play touch and run. But the boy didn't lose the high spirits and decided to play touch and run with himself. You may ask: "How did he do that?" The answer is simple.

Vasya noticed that the yard is a rectangular $ n×m $ field. The squares have coordinates $ (x,y) $ ( $ 1<=x<=n,1<=y<=m $ ), where $ x $ is the index of the row and $ y $ is the index of the column.

Initially Vasya stands in the square with coordinates ( $ x_{c},y_{c} $ ). To play, he has got a list of $ k $ vectors $ (dx_{i},dy_{i}) $ of non-zero length. The game goes like this. The boy considers all vectors in the order from $ 1 $ to $ k $ , and consecutively chooses each vector as the current one. After the boy has chosen a current vector, he makes the maximally possible number of valid steps in the vector's direction (it is possible that he makes zero steps).

A step is defined as one movement from the square where the boy is standing now, in the direction of the current vector. That is, if Vasya is positioned in square $ (x,y) $ , and the current vector is $ (dx,dy) $ , one step moves Vasya to square $ (x+dx,y+dy) $ . A step is considered valid, if the boy does not go out of the yard if he performs the step.

Vasya stepped on and on, on and on until he ran out of vectors in his list. Ha had been stepping for so long that he completely forgot how many steps he had made. Help the boy and count how many steps he had made.

## 说明/提示

In the first sample Vasya is initially positioned at square $ (1,1) $ and makes $ 3 $ steps by the first vector $ (1,1) $ . So, he consecutively visits the squares $ (2,2),(3,3),(4,4) $ . Then he makes $ 0 $ steps by the second vector $ (1,1) $ . He makes $ 1 $ more step by the third vector $ (0,-2) $ and he ends up in square $ (4,2) $ . Overall, Vasya makes $ 4 $ steps.

In the second sample Vasya is initially positioned in square $ (1,2) $ and makes $ 0 $ steps by vector $ (-1,0) $ , as the square with coordinates $ (0,2) $ is located outside the yard.

## 样例 #1

### 输入

```
4 5
1 1
3
1 1
1 1
0 -2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 10
1 2
1
-1 0
```

### 输出

```
0
```

# AI分析结果



# 题目中文翻译

## 题目描述

有一天，Vasya 来到院子散步，发现院子里没有朋友，也没有人陪他玩"触碰与奔跑"游戏。但这个男孩并没有失去兴致，决定自己和自己玩这个游戏。你可能会问："这怎么玩呢？"答案很简单。

院子是一个 $n×m$ 的矩形网格。每个方格的坐标为 $(x,y)$（$1 \leq x \leq n, 1 \leq y \leq m$），其中 $x$ 是行号，$y$ 是列号。

初始时 Vasya 站在坐标 $(x_c,y_c)$ 的方格上。他有一个包含 $k$ 个非零向量 $(dx_i,dy_i)$ 的列表。游戏规则如下：Vasya 按顺序考虑每个向量，对于当前向量，他会尽可能多地沿着该方向移动合法的步数（可能为零步）。

每一步的定义是从当前所在方格 $(x,y)$，按照当前向量 $(dx,dy)$ 移动一次到达 $(x+dx,y+dy)$。只有当移动后不超出院子边界时，该步才被视为合法。

Vasya 持续移动直到处理完所有向量。请你帮他计算总共移动了多少步。

## 说明/提示

第一个样例中，Vasya 初始位置在 $(1,1)$，第一个向量 $(1,1)$ 可以走 3 步，依次经过 $(2,2),(3,3),(4,4)$。第二个向量 $(1,1)$ 无法移动。第三个向量 $(0,-2)$ 走 1 步到达 $(4,2)$。总共 4 步。

第二个样例中，初始位置 $(1,2)$ 无法向向量 $(-1,0)$ 移动，因为会越界到 $(0,2)$。

## 样例 #1

### 输入
```
4 5
1 1
3
1 1
1 1
0 -2
```

### 输出
```
4
```

## 样例 #2

### 输入
```
10 10
1 2
1
-1 0
```

### 输出
```
0
```

**算法分类**: 模拟

---

# 题解分析与结论

### 题目核心思路
所有题解均采用模拟策略，核心在于计算每个向量方向下 x/y 轴的最大合法步数。关键公式：
- 当 dx>0 时，x轴最大步数 = (n - x) // dx
- 当 dx<0 时，x轴最大步数 = (1 - x) // dx
- y轴同理，最终取两轴最小值作为该向量方向的步数

### 最优题解亮点

#### 1. 题解作者：zlqwq（评分：★★★★★）
**关键亮点**：
- 使用 `inf` 处理无限制方向（如纯横向/纵向移动）
- 清晰的分情况判断 dx/dy 的正负
- 变量命名直观，逻辑简洁
- 提前处理边界条件，避免复杂运算

**核心代码**：
```cpp
if(dx > 0) {
    int nx = n - x;
    t = min(t,nx / dx);
} else if(dx < 0) {
    int nx = 1 - x;
    t = min(t,nx / dx);
}
// 类似处理 dy
x += t * dx; // 更新坐标
ans += t;    // 累加步数
```

#### 2. 题解作者：tzjahinie（评分：★★★★☆）
**关键亮点**：
- 紧凑的条件判断结构
- 使用 0x3f3f3f3f 表示极大值
- 代码行数最少，效率最优
- 包含重要调试提示（long long）

**核心代码**：
```cpp
t=0x3f3f3f3f;
if(dx>0) t=min(t,(n-x)/dx);
else if(dx) t=min(t,(1-x)/dx);
// 类似处理 dy
```

#### 3. 题解作者：_Maverick_（评分：★★★★☆）
**关键亮点**：
- 显式处理 dx/dy 为零的情况
- 使用 1e9 作为无限制方向的步数
- 完整展示坐标更新过程
- 包含代码框架提示（signed main）

**核心代码**：
```cpp
if (a == 0) p = 1e9; // 横向无限制
if (b == 0) q = 1e9; // 纵向无限制
long long w = min(p, q);
x += a * w; // 坐标更新
```

---

### 关键技巧总结
1. **方向分界处理**：通过正负号判断边界方向（n或1）
2. **整数除法截断**：利用整除特性自动取最大合法步数
3. **数据类型控制**：必须使用 long long 防止累加溢出
4. **极值替代法**：当某方向无限制时（如纯横向移动），用极大值确保不影响另一维度的计算

---

### 拓展应用
此类边界模拟问题常见于：
1. 棋盘类移动问题（如洛谷 P1518 牛的十字阵）
2. 粒子运动轨迹模拟（如洛谷 P1563 玩具谜题）
3. 资源分配中的最小限制问题

---

### 推荐练习题
1. P1518 [USACO2.4] 两只牛的十字阵（模拟+方向处理）
2. P1563 玩具谜题（环形移动模拟）
3. P1120 小书童的回家之路（多向量路径规划）

---

### 个人心得摘录
- "十年OI一场空，不开long long见祖宗"（jubaoyi2011）
- "注意坐标更新要同步进行，否则会影响后续计算"（OIer6666）
- "极值处理是解决多维度限制问题的关键"（_zhaosihan_qwq_）

---
处理用时：69.37秒