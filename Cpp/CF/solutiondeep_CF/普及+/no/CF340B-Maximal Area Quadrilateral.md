# 题目信息

# Maximal Area Quadrilateral

## 题目描述

Iahub has drawn a set of $ n $ points in the cartesian plane which he calls "special points". A quadrilateral is a simple polygon without self-intersections with four sides (also called edges) and four vertices (also called corners). Please note that a quadrilateral doesn't have to be convex. A special quadrilateral is one which has all four vertices in the set of special points. Given the set of special points, please calculate the maximal area of a special quadrilateral.

## 说明/提示

In the test example we can choose first $ 4 $ points to be the vertices of the quadrilateral. They form a square by side $ 4 $ , so the area is $ 4·4=16 $ .

## 样例 #1

### 输入

```
5
0 0
0 4
4 0
4 4
2 3
```

### 输出

```
16.000000```

# AI分析结果

### 题目内容
# 最大面积四边形

## 题目描述
Iahub 在笛卡尔平面上绘制了一组 $n$ 个点，他称之为“特殊点”。四边形是一种简单多边形，没有自相交，有四条边（也称为棱）和四个顶点（也称为角）。请注意，四边形不一定是凸的。特殊四边形是指四个顶点都在特殊点集合中的四边形。给定特殊点集合，请计算特殊四边形的最大面积。

## 说明/提示
在测试示例中，我们可以选择前 4 个点作为四边形的顶点。它们构成一个边长为 4 的正方形，所以面积是 $4×4 = 16$。

## 样例 #1
### 输入
```
5
0 0
0 4
4 0
4 4
2 3
```
### 输出
```
16.000000
```

### 算法分类
枚举

### 题解综合分析与结论
三道题解思路本质相同，均是通过枚举对角线来寻找最大面积四边形。具体做法为：先枚举所有可能的对角线（两个点确定一条对角线），再对每条对角线，分别找出在其两侧能与对角线端点构成三角形面积最大的点，将这两个最大三角形面积相加得到以此对角线构成的四边形的最大面积，最后取所有对角线情况下的最大值即为答案。

不同点在于判断点在直线哪一侧以及计算三角形面积的方式：
 - 流绪的题解通过向量叉乘公式计算三角形面积，可根据结果正负判断点在直线哪一侧，代码简洁明了。
 - Jerry_heng 的题解通过直线解析式判断点的位置，利用海伦公式计算三角形面积。
 - skyskyCCC 的题解同样利用直线解析式判断点的位置，用海伦公式算面积，代码逻辑稍显复杂。

### 所选的题解
 - **流绪题解**：★★★★
    - **关键亮点**：利用向量叉乘计算三角形面积，可直接根据结果正负判断点在对角线哪一侧，代码简洁高效，思路清晰。
    - **核心代码**：
```cpp
double f(node a,node b,node c)
{
    double a1=b.x-a.x;
    double a2=c.x-b.x;
    double a3=b.y-a.y;
    double a4=c.y-b.y;
    return (a1*a4-a2*a3)/2; 
}
int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> a[i].x >> a[i].y;
    double ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            double ls=0,rs=0;
            for(int k=1;k<=n;k++)
            {
                double s=f(a[i],a[j],a[k]);
                if(s>0&&s>ls)
                    ls=s;
                else if(s<0&&-s>rs)
                    rs=-s;
            }
            if(ls+rs>ans&&ls>0&&rs>0)
                ans = ls+rs;
        }
    printf("%.6lf",ans);
}
```
 - **Jerry_heng 题解**：★★★
    - **关键亮点**：通过直线解析式判断点在对角线上下方，利用海伦公式计算三角形面积，逻辑清晰。但相比流绪题解，计算三角形面积方式较复杂。
    - **核心代码**：
```cpp
bool pd(hyh x1,hyh y1,hyh x2,hyh y2,hyh x3,hyh y3){
    hyh k=(y2-y1)/(x2-x1),b=y1-k*x1;
    return x3*k+b<y3;
}
hyh s(hyh x1,hyh y1,hyh x2,hyh y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
hyh js(hyh x1,hyh y1,hyh x2,hyh y2,hyh x3,hyh y3){
    hyh a=s(x1,y1,x2,y2),b=s(x1,y1,x3,y3),c=s(x2,y2,x3,y3);
    hyh p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++){
            hyh s1=0,s2=0;
            for(int k=1;k<=n;k++){
                if(k==i||k==j)continue;
                bool pos=pd(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y);
                if(pos==0)s1=max(s1,js(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y));
                else s2=max(s2,js(a[i].x,a[i].y,a[j].x,a[j].y,a[k].x,a[k].y));
            }
            if(s1==0||s2==0)continue;
            ans=max(ans,s1+s2);
        }
    printf("%.9lf",ans);
    return 0;
}
```

### 最优关键思路或技巧
利用枚举对角线并结合向量叉乘计算三角形面积来判断点与直线位置关系的方法，相比通过直线解析式判断位置关系以及利用海伦公式计算三角形面积，代码实现更简洁，计算量更小。

### 可拓展思路
此类题目属于计算几何中的面积求解问题，常见拓展方向为增加点的数量、改变图形形状（如求最大面积多边形）。通用算法套路为通过合理的枚举方式（如本题枚举对角线），结合合适的几何公式（如向量叉乘求三角形面积、海伦公式等）来求解。

### 洛谷相似题目推荐
 - [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：与本题类似，通过枚举边长来寻找最大正方形面积，锻炼枚举思想。
 - [P2036 [COCI2008-2009#2] PERKET](https://www.luogu.com.cn/problem/P2036)：通过枚举食材组合计算美味度，同样考察枚举策略。
 - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：虽然是数组问题，但同样是通过枚举寻找最大子段和，与本题枚举找最值思路类似。 

---
处理用时：50.67秒