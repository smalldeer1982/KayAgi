# 题目信息

# Rooter's Song

## 题目描述

Wherever the destination is, whoever we meet, let's render this song together.

On a Cartesian coordinate plane lies a rectangular stage of size $ w×h $ , represented by a rectangle with corners $ (0,0) $ , $ (w,0) $ , $ (w,h) $ and $ (0,h) $ . It can be seen that no collisions will happen before one enters the stage.

On the sides of the stage stand $ n $ dancers. The $ i $ -th of them falls into one of the following groups:

- Vertical: stands at $ (x_{i},0) $ , moves in positive $ y $ direction (upwards);
- Horizontal: stands at $ (0,y_{i}) $ , moves in positive $ x $ direction (rightwards).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/78a4617a270ecba0555a87f4deb825cf1f501330.png)According to choreography, the $ i $ -th dancer should stand still for the first $ t_{i} $ milliseconds, and then start moving in the specified direction at $ 1 $ unit per millisecond, until another border is reached. It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

When two dancers collide (i.e. are on the same point at some time when both of them are moving), they immediately exchange their moving directions and go on.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/14a342567b0e0e96e2854bafb4e39a8b293ebae4.png)Dancers stop when a border of the stage is reached. Find out every dancer's stopping position.

## 说明/提示

The first example corresponds to the initial setup in the legend, and the tracks of dancers are marked with different colours in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/d441e2a826ff927d107333215574de12d2f00a07.png)In the second example, no dancers collide.

## 样例 #1

### 输入

```
8 10 8
1 1 10
1 4 13
1 7 1
1 8 2
2 2 0
2 5 14
2 6 0
2 6 1
```

### 输出

```
4 8
10 5
8 8
10 6
10 2
1 8
7 8
10 6
```

## 样例 #2

### 输入

```
3 2 3
1 1 2
2 1 1
1 1 5
```

### 输出

```
1 3
2 1
1 3
```

# AI分析结果



# Rooter's Song（舞者之歌）

## 题目描述  
在笛卡尔坐标系上有一个 $w×h$ 的矩形舞台，四个顶点为 $(0,0)$、$(w,0)$、$(w,h)$、$(0,h)$。舞台四周站着 $n$ 个舞者：  

- 垂直组：位于 $(x_i,0)$，向上移动（+y 方向）  
- 水平组：位于 $(0,y_i)$，向右移动（+x 方向）  

每个舞者先静止 $t_i$ 毫秒，然后以 1 单位/毫秒的速度移动。当两个移动中的舞者相撞时，会交换方向。求所有舞者的最终停止坐标。

---

## 题解分析与结论  

### 核心思路总结  
**关键观察**：两个舞者相撞的必要条件是 $p_i - t_i = p_j - t_j$（$p$ 为初始坐标值）。将所有舞者按 $p-t$ 分组后：  
1. 不同组的舞者永远不会碰撞  
2. 同组舞者的路径形成不交叉的"平行线"，碰撞后等价于交换终点  
3. 将同组舞者的起点和终点按特定规则排序后一一对应即可  

---

## 精选题解  

### 题解1：zyctc（⭐⭐⭐⭐）  
**亮点**：  
- 通过将起点和终点分别排序实现映射  
- 利用坐标转换将碰撞问题转化为排序问题  
- 代码结构清晰，使用统一数据结构处理两类舞者  

**核心代码思想**：  
```cpp
struct node{int x,y,id;};
vector<node> d[maxn], p; // d存储起点，p存储理论终点

// 对每个分组处理
for(auto k:dif) {
    sort(d[k].begin(),d[k].end());  // 按y从大到小，x从小到大排序
    sort(p.begin(),p.end());        // 终点按相同规则排序
    for(int i=0;i<d[k].size();i++) 
        ans[d[k][i].id] = p[i];     // 起点终点一一对应
}
```

### 题解2：moye到碗里来（⭐⭐⭐）  
**亮点**：  
- 分别处理垂直/水平舞者  
- 通过数量关系判断终点来源  
- 使用 pair 简化数据结构  

**核心实现逻辑**：  
```cpp
// 对于每个分组：
sort(vec[0][i].begin(), vec[0][i].end()); // 垂直组按坐标排序
sort(vec[1][i].begin(), vec[1][i].end()); // 水平组按坐标排序

// 判断垂直舞者终点来源
if(剩余垂直舞者数 >= 水平舞者总数) 
    终点来自同组后续舞者坐标
else 
    终点来自水平组对应位置
```

---

## 关键技巧与拓展  

### 核心技巧  
1. **碰撞等效转换**：将动态碰撞转化为静态终点映射  
2. **分组策略**：利用 $p-t$ 作为分组依据，避免处理无关碰撞  
3. **排序映射法**：通过保持起点终点排序一致性确定最终位置  

### 类似题目推荐  
1. [P1971 碰撞的小球](https://www.luogu.com.cn/problem/P1971)  
2. [CF1085G Beautiful Matrix](https://codeforces.com/problemset/problem/1085/G)（分组排序思想）  
3. [P1365 矩阵取数游戏](https://www.luogu.com.cn/problem/P1365)（坐标映射技巧）  

### 个人心得摘录  
> "画图后发现碰撞等价于交换终点，同一组的路径不会交叉。这个几何直观帮助理解了排序映射的正确性。" —— moye到碗里来  
> "将碰撞前后的运动轨迹等效为直接走到对方终点，是避免模拟的关键顿悟。" —— zyctc

---
处理用时：57.65秒