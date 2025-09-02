# 题目信息

# Rectangle Puzzle

## 题目描述

You are given two rectangles on a plane. The centers of both rectangles are located in the origin of coordinates (meaning the center of the rectangle's symmetry). The first rectangle's sides are parallel to the coordinate axes: the length of the side that is parallel to the $ Ox $ axis, equals $ w $ , the length of the side that is parallel to the $ Oy $ axis, equals $ h $ . The second rectangle can be obtained by rotating the first rectangle relative to the origin of coordinates by angle $ α $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280A/052b43ecd665cd6e4ffd3e118c46f92dcd4eb612.png)Your task is to find the area of the region which belongs to both given rectangles. This region is shaded in the picture.

## 说明/提示

The second sample has been drawn on the picture above.

## 样例 #1

### 输入

```
1 1 45
```

### 输出

```
0.828427125
```

## 样例 #2

### 输入

```
6 4 30
```

### 输出

```
19.668384925
```

# AI分析结果

### 题目内容
# 矩形谜题

## 题目描述
给定平面上的两个矩形。两个矩形的中心都位于坐标原点（即矩形对称中心）。第一个矩形的边与坐标轴平行：与 $Ox$ 轴平行的边长为 $w$，与 $Oy$ 轴平行的边长为 $h$。第二个矩形可通过将第一个矩形绕坐标原点旋转角度 $\alpha$ 得到。

![矩形图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280A/052b43ecd665cd6e4ffd3e118c46f92dcd4eb612.png)
你的任务是找出同时属于这两个给定矩形的区域的面积。该区域在图中已阴影标注。

## 说明/提示
第二个样例已绘制在上面的图中。

## 样例 #1
### 输入
```
1 1 45
```
### 输出
```
0.828427125
```

## 样例 #2
### 输入
```
6 4 30
```
### 输出
```
19.668384925
```

### 算法分类
数学

### 题解综合分析与结论
这几道题解主要围绕如何计算两个矩形重叠部分面积展开，核心思路是先确定旋转后矩形顶点坐标，再通过不同方式处理交点情况以计算重叠面积。不同题解的差异在于处理交点及计算面积的方法。

### 所选的题解
- **作者：wanggk（5星）**
    - **关键亮点**：思路清晰，先对输入数据进行预处理简化问题，利用向量旋转公式确定旋转后矩形顶点坐标，根据线段相交情况分类讨论重叠区域形状（平行四边形或八边形），分别计算面积。代码实现简洁明了，对细节处理得当，如角度范围调整，使用叉积判断线段相交及求多边形面积，是较为标准的计算几何解法。
    - **个人心得**：强调了一些细节处理对结果正确性的影响，如 `if(w<h) swap(w,h);` 不加会WA on 13，`if(a>90) a=180-a;` 这句不加会WA on 6等。
    - **重点代码**：
```cpp
//向量逆时针旋转
Vector rotate(Vector A,long double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
//叉积
long double cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x; }
//判断线段相交
bool Properintersection(Point A,Point B,Point P,Point Q){
	return sgn(cross(B-A,P-A))*sgn(cross(B-A,Q-A))<0
		 &&sgn(cross(Q-P,A-P))*sgn(cross(Q-P,B-P))<0;
}
//求交点
Point intersection(Point P,Vector v,Point Q,Vector w)
{
    Vector u=P-Q;
    long double t=cross(w,u)/cross(v,w);
    return P+v*t;
}
```
核心实现思想：通过向量旋转公式得到旋转后矩形顶点坐标，利用叉积判断线段相交情况，根据不同相交情况确定重叠区域形状，再用叉积求多边形面积。
- **作者：lql1（4星）**
    - **关键亮点**：详细阐述解析几何思路，从确定旋转后顶点坐标，到用直线方程求交点、判断交点合法性、按极角排序交点，最后使用鞋带公式计算多边形面积，步骤完整，对知识点解释详细，适合初学者理解。
    - **重点代码**：
```cpp
//旋转坐标变换
void change_xy(double& x,double& y,double radian) {
    double old_x=x;
    double old_y=y;
    x=cos(radian)*old_x-sin(radian)*old_y;
    y=sin(radian)*old_x+cos(radian)*old_y;
}
//计算交点 
bool check_line(double x1,double y1,double x2,double y2,
                       double x3,double y3,double x4,double y4,
                       double& ix,double& iy) {
    double tmp=(y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
    if(fabs(tmp)<eps) return false; 
    double ua=((x4-x3)*(y1-y3)-(y4-y3)*(x1-x3))/tmp;
    double ub=((x2-x1)*(y1-y3)-(y2-y1)*(x1-x3))/tmp;
    if(ua<0||ua>1||ub<0||ub>1)return false;  // 交点不在这两条线段上
    ix=x1+ua*(x2-x1);
    iy=y1+ua*(y2-y1);
    return true;
}
//鞋带公式计算面积
double ccl_area(vector<pair<double,double>> point) {
	//鞋带公式 
    double area=0;
    int n=point.size();
    for(int i=0;i<n;i++) {
        int j=(i+1)%n;
        area+=point[i].first*point[j].second-point[j].first*point[i].second;
    }
    return fabs(area)/2.0;
}
```
核心实现思想：通过坐标变换公式得到旋转后顶点坐标，联立直线方程求交点并判断合法性，将所有交点按极角排序后用鞋带公式计算重叠区域面积。
- **作者：yanhao40340（4星）**
    - **关键亮点**：对情况分析细致，先对角度范围进行简化，指出只需要解决 $0< \alpha \le 90$ 的情况。通过判断线段是否相交确定交点个数（4个或8个），分别针对两种交点个数情况给出计算重叠面积的方法，将问题转化为求线段交点坐标，思路连贯。
    - **重点代码**：
```cpp
//向量旋转
pdd rotate(pdd a,double w){
	return {a.x*cos(w)-a.y*sin(w),a.y*cos(w)+a.x*sin(w)};
}
//判断线段相交
bool collide(pdd a,pdd b,pdd c,pdd d){
	if (signbit((b-a)*(c-a))^signbit((b-a)*(d-a)))
		if (signbit((d-c)*(c-a))^signbit((d-c)*(c-b))) return true;
	return false;
}
//求交点
pdd point(pdd a,pdd b,pdd c,pdd d){
	return a+b*((d*(a-c))/(b*d));
}
```
核心实现思想：利用向量旋转公式得到旋转后矩形顶点，用向量积判断线段相交情况确定交点个数，再通过特定公式求交点坐标进而计算重叠面积。

### 最优关键思路或技巧
- **数据预处理**：对输入的角度 $\alpha$ 和边长 $w, h$ 进行预处理，如将 $\alpha$ 限制在 $0 - 90$ 度范围内，调整 $w$ 和 $h$ 的大小关系，简化后续计算。
- **向量旋转与线段相交判断**：利用向量旋转公式确定旋转后矩形顶点坐标，通过向量叉积或其他方式判断线段相交情况，以此分类讨论重叠区域形状，是解决此类问题的关键技巧。
- **面积计算方法**：根据重叠区域形状（平行四边形或多边形），选择合适的面积计算方法，如叉积求平行四边形面积、鞋带公式求多边形面积等。

### 同类型题或类似算法套路拓展
同类型题通常围绕平面图形的旋转、平移后求重叠面积、交点等问题。类似算法套路是先确定图形变换后的顶点坐标，再通过判断线段相交等方式确定重叠区域的形状和边界，最后选择合适的方法计算面积。例如对于三角形、多边形等图形的类似变换问题，也可采用类似思路。

### 洛谷相似知识点题目推荐
- **P1082 [NOIP2012 提高组] 同余方程**：考察数论中的同余方程求解，与本题一样需要运用数学知识解决问题。
- **P2671 [NOIP2015 提高组] 求和**：涉及前缀和与数学运算，锻炼对数学概念在编程中的运用能力。
- **P1313 计算系数**：主要考察二项式定理等数学知识在编程中的应用，与本题类似，需要将数学原理转化为代码实现。 

---
处理用时：73.35秒