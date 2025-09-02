# 题目信息

# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2
```

### 输出

```
12.566370614359172464
```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1
```

### 输出

```
21.991148575128551812
```

# AI分析结果



## 算法分类
**计算几何**

---

## 题解思路与核心难点
### 核心思路
所有题解均基于以下公式：  
**扫过的面积 = π × (最远距离² - 最近距离²)**  
- **最远距离**：多边形的顶点到中心点 P 的最大距离  
- **最近距离**：可能是顶点到 P 的最小距离，或某条边的垂足到 P 的距离（若垂足在线段上）

### 解决难点对比
1. **垂足计算**  
   - **直线方程法**（zztqwq, David24）：通过求两条直线交点（原线段与垂线）计算垂足，需处理斜率不存在（垂直线）和分母为零的特殊情况。  
   - **向量投影法**（zhenglier, liuyifan, henhen_）：利用向量点积判断垂足是否在线段上，避免处理斜率，代码更简洁。  

2. **距离比较**  
   - **顶点距离**：直接计算欧氏距离平方（避免开方）  
   - **边距离**：若垂足在线段上，取垂线距离；否则取两端点中更近者  

---

## 题解评分（≥4星）
1. **zhenglier（4.5星）**  
   - **亮点**：向量投影法避免复杂直线方程，代码简洁高效  
   - **代码**：`dis_ltop` 函数通过点积判断垂足位置  

2. **liuyifan（4.5星）**  
   - **亮点**：模块化计算几何模板，支持点/线运算，可读性强  
   - **代码**：`dis` 函数直接返回平方距离，避免精度损失  

3. **henhen_（4星）**  
   - **亮点**：叉乘计算面积求高，思路清晰  
   - **代码**：`distl_sqr` 函数结合点积和叉乘判断垂足  

---

## 最优思路与技巧
### 关键技巧
- **向量投影法**：用点积判断垂足是否在线段上  
  ```cpp
  double d1 = (q.x-p.x)*(a.x-p.x) + (q.y-p.y)*(a.y-p.y);
  if (d1 <= 0) return dis(a, p);  // 垂足在p侧外
  if (d1 >= dis(p, q)) return dis(a, q); // 垂足在q侧外
  ```
- **距离平方比较**：全程使用平方距离避免开方，提升效率与精度  

---

## 同类型题与算法套路
1. **最近点对问题**：分治法求平面最近点对  
2. **线段交点检测**：跨立实验 + 快速排斥  
3. **多边形包含判断**：射线法 / 回转数法  

---

## 推荐题目
1. **P1355** 神秘大三角（点与多边形位置关系）  
2. **P2774** 方格取数问题（网格几何 + 网络流）  
3. **P3829** [SHOI2012]信用卡凸包（旋转处理 + 凸包）  

---

## 个人心得摘录
- **zhenglier**：“开始以为只用顶点，结果被卡第三个点”——提醒注意几何问题中边的贡献  
- **shao0320**：“差点没算 s 我”——直线方程推导易错，推荐向量法简化  

---

## 可视化设计
### 核心算法演示
1. **多边形与中心点**：  
   - 红色点表示中心 P，蓝色点为多边形顶点  
   - 灰色线段连接多边形边  

2. **距离计算过程**：  
   - **顶点距离**：从 P 到顶点的绿色虚线，动态显示最长/最短  
   - **边垂足**：黄色点表示当前边垂足，若在线段上则变绿  

3. **旋转动画**：  
   - 半透明圆环展示当前最大/最小半径对应的圆  
   - 实时更新面积公式中的 π(R²-r²) 值  

### 复古游戏化效果
- **像素风格**：  
  - 16色调色板（红/蓝/绿/黄为主）  
  - Canvas 绘制多边形与动态轨迹  
- **音效设计**：  
  - **滴**：找到新的最远点  
  - **嘟**：垂足在线段上  
  - 8-bit BGM 循环播放  
- **自动演示模式**：  
  - 按空格暂停/继续，方向键控制速度  

---

## 核心代码（向量投影法）
```cpp
double dis_ltop(point a, point p, point q) {
    double d1 = (q.x-p.x)*(a.x-p.x) + (q.y-p.y)*(a.y-p.y); // 向量AP·向量PQ
    if(d1 <= 0) return (a.x-p.x)*(a.x-p.x) + (a.y-p.y)*(a.y-p.y); // 垂足在P外侧
    double d2 = (q.x-p.x)*(q.x-p.x) + (q.y-p.y)*(q.y-p.y); // |PQ|²
    if(d1 >= d2) return (a.x-q.x)*(a.x-q.x) + (a.y-q.y)*(a.y-q.y); // 垂足在Q外侧
    
    double r = d1/d2; // 投影比例
    point h = {p.x + (q.x-p.x)*r, p.y + (q.y-p.y)*r}; // 垂足坐标
    return (a.x-h.x)*(a.x-h.x) + (a.y-h.y)*(a.y-h.y); 
}
```

---
处理用时：79.23秒