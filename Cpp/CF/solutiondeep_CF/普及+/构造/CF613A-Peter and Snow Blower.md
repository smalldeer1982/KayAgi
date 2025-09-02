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

### 题目翻译
#### Peter和吹雪机

### 题目描述
Peter在新年得到了一台新的吹雪机作为礼物。当然，Peter决定立即试用它。阅读说明书后，他意识到这台吹雪机的工作方式与普通的不同。为了让它工作，你需要把它系在一个它不会覆盖的点上，然后打开开关。结果，它将绕着这个点做圆周运动，并清除其路径上的所有积雪。

形式上，我们假设Peter的机器是平面上的一个多边形。然后，当机器打开后，它将绕着Peter系它的点做圆周运动（这个点严格位于多边形外部）。也就是说，位于多边形内部或边界上的每个点都将沿着以Peter系机器的点为圆心的圆形轨迹移动。

Peter决定把他的机器系在点 $P$ 上，现在他想知道将被清除积雪的区域面积是多少。请帮助他。

### 说明/提示
在第一个样例中，积雪将从以下区域被清除：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

### 样例 #1
#### 输入
```
3 0 0
0 1
-1 2
1 2
```
#### 输出
```
12.566370614359172464
```

### 样例 #2
#### 输入
```
4 1 -1
0 0
1 2
2 0
1 1
```
#### 输出
```
21.991148575128551812
```

### 综合分析与结论
这些题解的核心思路一致，都是求多边形绕定点旋转扫过的圆环面积，即找出最外圆半径 $r_{max}$ 和最内圆半径 $r_{min}$，通过公式 $\pi(r_{max}^2 - r_{min}^2)$ 计算结果。其中 $r_{max}$ 一定是定点到多边形某顶点的距离，而 $r_{min}$ 可能是定点到顶点的距离，也可能是定点到某条边的距离。

各题解的算法要点和难点解决方法对比如下：
|作者|算法要点|难点解决|
| ---- | ---- | ---- |
|zztqwq|通过求定点到顶点和边的垂足距离确定 $r_{max}$ 和 $r_{min}$，利用一次函数交点求垂足坐标|考虑直线垂直引理求斜率，处理三种特殊情况（直线平行坐标轴、垂足不在线段上）|
|zhenglier|计算定点到顶点和线段的距离确定 $r_{max}$ 和 $r_{min}$，用数学方法判断垂足位置|避免开方运算防止精度丢失|
|liuyifan|使用点和直线类封装运算，求定点到顶点和边的距离确定 $r_{max}$ 和 $r_{min}$|重载运算符实现点和直线的运算，处理环的情况|
|David24|计算定点到顶点和边的垂足距离确定 $r_{max}$ 和 $r_{min}$，通过解方程组求垂足坐标|推导一次函数和垂直函数的解析式，处理特殊情况（直线平行坐标轴、垂足不在线段上）|
|shao0320|枚举边求定点到边的最短距离确定 $r_{min}$，通过直线垂直性质求垂足坐标|处理边平行坐标轴的情况|
|henhen_|用余弦定理判断能否做垂线，海伦公式求高确定 $r_{min}$|判断能否做垂线和处理最后一个点与第一个点连成的线段|
|Toothless03|用向量点乘判断垂足位置，叉乘求面积确定 $r_{min}$|使用向量运算避免复杂的直线方程计算|

### 所选题解
- **zztqwq（5星）**
    - **关键亮点**：思路清晰，详细推导了求垂足坐标的方法和特殊情况处理，代码注释丰富，可读性高。
    - **核心代码**：
```cpp
pair<double,double> cz(double X1,double Y1,double X2,double Y2)
{
    if(X1==X2) return make_pair(X1,Y0);
    if(Y1==Y2) return make_pair(X0,Y1);
    double k=(Y2-Y1)/(X2-X1),k0=-(1/k);
    double b=Y1-k*X1,b0=Y0-k0*X0;
    return make_pair((b0-b)/(k-k0),(b0-b)/(k-k0)*k0+b0);
}
```
    - **核心思想**：根据两点坐标求直线解析式，再利用直线垂直性质求垂线解析式，最后联立方程求垂足坐标，同时处理直线平行坐标轴的特殊情况。

- **liuyifan（4星）**
    - **关键亮点**：使用类封装点和直线的运算，代码结构清晰，方便复用，处理环的情况简洁。
    - **核心代码**：
```cpp
inline double dis(reg point a,reg point b,reg point c)
{
    point x=a-b,y=c-b,z=c-a;
    if((x*y)<0)return len(x);
    if((y*z)<0)return len(z);
    point v=c-b;
    double t=((a-b)*v)/(v*v);
    point fot=point(b.x+t*v.x,b.y+t*v.y);
    return sqrt((fot.x-a.x)*(fot.x-a.x)+(fot.y-a.y)*(fot.y-a.y));
}
```
    - **核心思想**：通过向量运算判断垂足位置，若垂足不在线段上则返回端点距离，否则求垂足坐标并计算距离。

- **Toothless03（4星）**
    - **关键亮点**：使用向量点乘和叉乘运算，避免了复杂的直线方程计算，思路简洁。
    - **核心代码**：
```cpp
inline double distl_sqr(point a, point p, point q)
{
    if (dot(a - q, p - q) < 0 || dot(a - p, q - p) < 0)
        return dist_sqr(a, p);
    return cross(p - a, q - a) * cross(p - a, q - a) / dist_sqr(p, q);
}
```
    - **核心思想**：用向量点乘判断垂足是否在线段上，若不在则返回端点距离，若在则用向量叉乘求面积，进而计算点到线段的距离。

### 最优关键思路或技巧
- 避免开方运算：在计算距离时，直接使用距离的平方，避免开方带来的精度损失。
- 向量运算：使用向量点乘和叉乘运算，简化了求点到线段距离的计算，避免了复杂的直线方程求解。
- 类封装：将点和直线的运算封装成类，提高代码的可读性和复用性。

### 拓展思路
同类型题目可能会涉及更复杂的多边形形状（如凹多边形）、更高维度的空间（三维空间中的旋转体体积）或多个多边形的组合。类似算法套路包括计算几何中的点线关系判断、面积体积计算等。

### 洛谷相似题目推荐
- [P1355 神秘大三角](https://www.luogu.com.cn/problem/P1355)：考察点与三角形的位置关系和三角形面积计算。
- [P2530 [SCOI2009] 生日礼物](https://www.luogu.com.cn/problem/P2530)：涉及线段覆盖和区间合并问题，与本题的线段处理有一定关联。
- [P3817 小A的糖果](https://www.luogu.com.cn/problem/P3817)：虽然题目表面不同，但解题时也需要考虑边界情况和最值问题。

### 个人心得摘录与总结
- **zhenglier**：开始理解错题目，以为只用算每个点到原点的距离的最大值和最小值，结果第三个点被卡。后来经大佬提醒，需要算出每条线段到原点的距离。总结是要仔细审题，考虑全面情况。
- **Toothless03**：第一眼认为只记录定点到每个点的长度最值即可，交上去错误。后来意识到还要看定点到每条边的距离。总结是做题不能想当然，要深入思考。 

---
处理用时：53.87秒