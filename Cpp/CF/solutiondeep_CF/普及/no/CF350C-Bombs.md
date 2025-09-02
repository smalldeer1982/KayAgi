# 题目信息

# Bombs

## 题目描述

You've got a robot, its task is destroying bombs on a square plane. Specifically, the square plane contains $ n $ bombs, the $ i $ -th bomb is at point with coordinates $ (x_{i},y_{i}) $ . We know that no two bombs are at the same point and that no bomb is at point with coordinates $ (0,0) $ . Initially, the robot is at point with coordinates $ (0,0) $ . Also, let's mark the robot's current position as $ (x,y) $ . In order to destroy all the bombs, the robot can perform three types of operations:

1. Operation has format "1 k dir". To perform the operation robot have to move in direction $ dir $ $ k $ ( $ k>=1 $ ) times. There are only $ 4 $ directions the robot can move in: "R", "L", "U", "D". During one move the robot can move from the current point to one of following points: $ (x+1,y) $ , $ (x-1,y) $ , $ (x,y+1) $ , $ (x,y-1) $ (corresponding to directions). It is forbidden to move from point $ (x,y) $ , if at least one point on the path (besides the destination point) contains a bomb.
2. Operation has format "2". To perform the operation robot have to pick a bomb at point $ (x,y) $ and put it in a special container. Thus, the robot can carry the bomb from any point to any other point. The operation cannot be performed if point $ (x,y) $ has no bomb. It is forbidden to pick a bomb if the robot already has a bomb in its container.
3. Operation has format "3". To perform the operation robot have to take a bomb out of the container and destroy it. You are allowed to perform this operation only if the robot is at point $ (0,0) $ . It is forbidden to perform the operation if the container has no bomb.

Help the robot and find the shortest possible sequence of operations he can perform to destroy all bombs on the coordinate plane.

## 样例 #1

### 输入

```
2
1 1
-1 -1
```

### 输出

```
12
1 1 R
1 1 U
2
1 1 L
1 1 D
3
1 1 L
1 1 D
2
1 1 R
1 1 U
3
```

## 样例 #2

### 输入

```
3
5 0
0 5
1 0
```

### 输出

```
12
1 1 R
2
1 1 L
3
1 5 R
2
1 5 L
3
1 5 U
2
1 5 D
3
```

# AI分析结果



# Bombs

## 题目描述

你有一个机器人，其任务是摧毁放置在平面坐标系上的所有炸弹。平面坐标系中有 $n$ 个炸弹，第 $i$ 个炸弹的坐标为 $(x_i, y_i)$。已知没有两个炸弹位于同一坐标点，且所有炸弹都不在原点 $(0,0)$。机器人初始位于原点，可通过以下三种操作完成任务：

1. **移动操作** `1 k dir`：沿方向 `dir`（"R"右、"L"左、"U"上、"D"下）移动 $k$ 步。移动路径上（除终点外）不能有其他炸弹。
2. **拾取操作** `2`：拾取当前坐标的炸弹。要求当前位置有炸弹且容器为空。
3. **销毁操作** `3`：在原点销毁容器中的炸弹。要求容器非空且机器人在原点。

要求构造最短的操作序列，摧毁所有炸弹。

**样例输入 #1**
```
2
1 1
-1 -1
```

**样例输出 #1**
```
12
1 1 R
1 1 U
2
1 1 L
1 1 D
3
1 1 L
1 1 D
2
1 1 R
1 1 U
3
```

## 算法分类
模拟、构造、排序

---

## 题解综合分析

### 共同思路
1. **按曼哈顿距离排序**：将所有炸弹按 $\lvert x \rvert + \lvert y \rvert$ 升序排序，确保处理路径不会经过未处理的炸弹。
2. **操作次数计算**：每个炸弹需要：
   - $2$ 次移动（若坐标非零） + $2$ 次返回移动（方向相反）
   - 固定 $2$ 次操作（拾取和销毁）
3. **方向处理**：根据坐标正负决定移动方向，返回时反向移动。

### 最优题解

#### 题解1：ikunTLE（5星）
**关键亮点**  
- 代码简洁，直接通过结构体排序处理炸弹顺序。
- 利用布尔运算简化移动次数的计算。
- 清晰的输出逻辑，分正向移动和反向返回两阶段。

**核心代码**  
```cpp
sort(a+1,a+n+1); // 按曼哈顿距离排序
for(int i=1;i<=n;++i) {
    // 正向移动
    if(a[i].x<0) printf("1 %d L\n",-a[i].x);
    else if(a[i].x>0) printf("1 %d R\n",a[i].x);
    if(a[i].y<0) printf("1 %d D\n",-a[i].y);
    else if(a[i].y>0) printf("1 %d U\n",a[i].y);
    
    printf("2\n"); // 拾取
    
    // 反向返回
    if(a[i].x<0) printf("1 %d R\n",-a[i].x);
    else if(a[i].x>0) printf("1 %d L\n",a[i].x);
    if(a[i].y<0) printf("1 %d U\n",-a[i].y);
    else if(a[i].y>0) printf("1 %d D\n",a[i].y);
    
    printf("3\n"); // 销毁
}
```

#### 题解2：jwsdy（4星）
**关键亮点**  
- 独立处理横纵坐标，逻辑直观。
- 使用绝对值简化方向判断，增强可读性。

**代码片段**  
```cpp
if(a[i].x>0) cout<<"1 "<<a[i].x<<" R\n";
else if(a[i].x<0) cout<<"1 "<<-a[i].x<<" L\n";
if(a[i].y>0) cout<<"1 "<<a[i].y<<" U\n";
else if(a[i].y<0) cout<<"1 "<<-a[i].y<<" D\n";
```

---

## 关键思路总结
1. **排序策略**：曼哈顿距离排序保证路径安全，避免中途碰撞。
2. **移动优化**：分坐标正负处理方向，返回时反向操作。
3. **操作计数**：每个炸弹的操作数固定为 $2 \times (x_{\text{非零}} + y_{\text{非零}}) + 2$。

## 拓展与举一反三
- **类似问题**：路径规划中需按特定顺序处理对象（如优先处理近端任务）。
- **推荐题目**：
  1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（贪心排序）
  2. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（构造操作序列）
  3. [P1518 两只塔姆沃斯牛](https://www.luogu.com.cn/problem/P1518)（模拟移动与路径判断）

---
处理用时：71.04秒