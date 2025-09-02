# 题目信息

# Arrow

## 题目描述

Petya has recently started working as a programmer in the IT city company that develops computer games.

Besides game mechanics implementation to create a game it is necessary to create tool programs that can be used by game designers to create game levels. Petya's first assignment is to create a tool that allows to paint different arrows on the screen.

A user of this tool will choose a point on the screen, specify a vector (the arrow direction) and vary several parameters to get the required graphical effect. In the first version of the program Petya decided to limit parameters of the arrow by the following: a point with coordinates $ (px,py) $ , a nonzero vector with coordinates $ (vx,vy) $ , positive scalars $ a,b,c,d,a&gt;c $ .

The produced arrow should have the following properties. The arrow consists of a triangle and a rectangle. The triangle is isosceles with base of length $ a $ and altitude of length $ b $ perpendicular to the base. The rectangle sides lengths are $ c $ and $ d $ . Point $ (px,py) $ is situated in the middle of the triangle base and in the middle of side of rectangle that has length $ c $ . Area of intersection of the triangle and the rectangle is zero. The direction from $ (px,py) $ point to the triangle vertex opposite to base containing the point coincides with direction of $ (vx,vy) $ vector.

Enumerate the arrow points coordinates in counter-clockwise order starting from the tip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630O/b1373ea5c55d47b5adf32698b1a37967e1fa1cc0.png)

## 样例 #1

### 输入

```
8 8 0 2 8 3 4 5
```

### 输出

```
8.000000000000 11.000000000000
4.000000000000 8.000000000000
6.000000000000 8.000000000000
6.000000000000 3.000000000000
10.000000000000 3.000000000000
10.000000000000 8.000000000000
12.000000000000 8.000000000000
```

# AI分析结果

### 题目内容
# 箭头

## 题目描述
佩特亚最近开始在 IT 城市公司担任程序员，该公司开发电脑游戏。
除了实现游戏机制外，为了创建一款游戏，还需要创建工具程序，游戏设计师可以使用这些程序来创建游戏关卡。佩特亚的第一项任务是创建一个工具，该工具可以在屏幕上绘制不同的箭头。
此工具的用户将在屏幕上选择一个点，指定一个向量（箭头方向），并改变几个参数以获得所需的图形效果。在程序的第一个版本中，佩特亚决定将箭头的参数限制如下：一个坐标为$(px,py)$的点，一个非零向量，坐标为$(vx,vy)$，正标量$a,b,c,d$，且$a > c$。
生成的箭头应具有以下属性。箭头由一个三角形和一个矩形组成。该三角形是等腰三角形，底边长度为$a$，垂直于底边的高长度为$b$。矩形的边长分别为$c$和$d$。点$(px,py)$位于三角形底边的中点，且位于长度为$c$的矩形边的中点。三角形和矩形的相交面积为零。从点$(px,py)$到与包含该点的底边相对的三角形顶点的方向与向量$(vx,vy)$的方向一致。
从箭头尖端开始，按逆时针顺序枚举箭头各点的坐标。
![箭头示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630O/b1373ea5c55d47b5adf32698b1a37967e1fa1cc0.png)

## 样例 #1
### 输入
```
8 8 0 2 8 3 4 5
```
### 输出
```
8.000000000000 11.000000000000
4.000000000000 8.000000000000
6.000000000000 8.000000000000
6.000000000000 3.000000000000
10.000000000000 3.000000000000
10.000000000000 8.000000000000
12.000000000000 8.000000000000
```

### 算法分类
数学

### 题解综合分析与结论
两道题解都围绕根据给定参数绘制箭头这一任务展开，核心都是通过数学方法确定箭头各点坐标。
- **思路方面**：
    - **Rigel**：先假设箭头方向向上构造点，再通过旋转矩阵实现图形旋转以符合向量方向。
    - **€€£**：直接按题目要求模拟，利用向量旋转的简单性质$(x,y)$旋转后为$(y, -x)$来确定各点坐标。
- **算法要点**：
    - **Rigel**：借助三角函数计算旋转角度，通过平移 - 旋转 - 平移的步骤确定各点坐标。
    - **€€£**：根据向量方向和各参数直接计算各点坐标，通过交换向量坐标分量并改变符号实现旋转。
- **解决难点**：两者都需解决如何根据给定向量方向确定箭头各点位置的问题。Rigel 通过通用的旋转矩阵解决，€€£ 通过简单的向量旋转性质解决。

### 题解
- **Rigel（4星）**
    - **关键亮点**：思路清晰，采用先假设方向再旋转的通用方法，代码结构较为清晰，利用结构体和函数封装，可读性较好。
    - **核心代码**：
```cpp
node revolve(node ni){
    double new_x=ni.x*cos_t-ni.y*sin_t,new_y=ni.x*sin_t+ni.y*cos_t;
    return (node){new_x,new_y};
}
signed main(){
    px=read(),py=read(),vx=read(),vy=read(),a=read(),b=read(),c=read(),d=read();
    h=sqrt(vx*vx+vy*vy);
    sin_t=-vx/h,cos_t=vy/h;
    n[0]=(node){px,py+b};
    n[1]=(node){px-a/2,py};
    n[2]=(node){px-c/2,py};
    n[3]=(node){px-c/2,py-d};
    n[4]=(node){px+c/2,py-d};
    n[5]=(node){px+c/2,py};
    n[6]=(node){px+a/2,py};
    for(int i=0;i<=6;i++)n[i].x-=px,n[i].y-=py;
    for(int i=0;i<=6;i++)n[i]=revolve(n[i]);
    for(int i=0;i<=6;i++)n[i].x+=px,n[i].y+=py;
    for(int i=0;i<=6;i++)printf("%.12lf %.12lf\n",n[i].x,n[i].y);
    return 0;
}
```
    - **核心实现思想**：先计算旋转相关参数，初始化假设向上方向的各点坐标，通过平移将点移到原点，调用旋转函数旋转各点，再平移回原位置并输出坐标。

### 最优关键思路或技巧
通过数学方法，利用向量旋转相关知识确定图形各点坐标。无论是使用通用的旋转矩阵（Rigel）还是简单的向量旋转性质（€€£），都是解决此类图形旋转定位问题的有效方法。

### 可拓展思路
此类题目属于图形几何相关的数学问题，类似套路为根据给定的几何图形参数和变换条件（如旋转、平移等），利用相应的数学知识（如三角函数、向量运算）确定图形各点坐标。同类型题可涉及不同形状图形的组合与变换。

### 洛谷题目推荐
- [P1307 数字反转](https://www.luogu.com.cn/problem/P1307)：考察基本的数学运算和数字处理。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过简单的数学计算解决实际问题。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：利用数学知识进行方案选择和计算。 

---
处理用时：58.65秒