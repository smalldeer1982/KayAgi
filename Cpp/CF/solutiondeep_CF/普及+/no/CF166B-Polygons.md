# 题目信息

# Polygons

## 题目描述

You've got another geometrical task. You are given two non-degenerate polygons $ A $ and $ B $ as vertex coordinates. Polygon $ A $ is strictly convex. Polygon $ B $ is an arbitrary polygon without any self-intersections and self-touches. The vertices of both polygons are given in the clockwise order. For each polygon no three consecutively following vertices are located on the same straight line.

Your task is to check whether polygon $ B $ is positioned strictly inside polygon $ A $ . It means that any point of polygon $ B $ should be strictly inside polygon $ A $ . "Strictly" means that the vertex of polygon $ B $ cannot lie on the side of the polygon $ A $ .

## 样例 #1

### 输入

```
6
-2 1
0 3
3 3
4 1
3 -2
2 -2
4
0 1
2 2
3 1
1 0
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2
4 2
3 -3
-2 -2
-2 1
4
0 1
1 2
4 1
2 -1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
-1 2
2 3
4 1
3 -2
0 -3
5
1 0
1 1
3 1
5 -1
2 -1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 多边形

## 题目描述
你又遇到了一个几何问题。给定两个非退化多边形 $A$ 和 $B$ 的顶点坐标。多边形 $A$ 是严格凸多边形。多边形 $B$ 是任意不自交且不自触的多边形。两个多边形的顶点均按顺时针顺序给出。对于每个多边形，任意三个连续的顶点都不在同一条直线上。

你的任务是检查多边形 $B$ 是否严格位于多边形 $A$ 内部。这意味着多边形 $B$ 的任意一点都应严格在多边形 $A$ 内部。“严格”表示多边形 $B$ 的顶点不能位于多边形 $A$ 的边上。

## 样例 #1
### 输入
```
6
-2 1
0 3
3 3
4 1
3 -2
2 -2
4
0 1
2 2
3 1
1 0
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
5
1 2
4 2
3 -3
-2 -2
-2 1
4
0 1
1 2
4 1
2 -1
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5
-1 2
2 3
4 1
3 -2
0 -3
5
1 0
1 1
3 1
5 -1
2 -1
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
大神题解将判断多边形 $B$ 是否严格在凸多边形 $A$ 内部的问题，等价转换为判断两个凸包是否相同的问题。通过对多边形 $A$ 以及合并后的多边形 $A$ 和 $B$ 的点集分别求凸包（使用Andrew算法），然后比较凸包的点数以及对应点是否相同，来确定多边形 $B$ 是否在多边形 $A$ 内部。该思路巧妙地利用凸包性质简化了问题，但需要对凸包算法有较好的理解和实现能力。

### 所选的题解
- **星级**：4星
  - **关键亮点**：将原问题等价转化为凸包比较问题，减少了逐个点判断的复杂度，利用Andrew算法有效求出凸包并能处理边界情况。
  - **重点代码**：
```cpp
double cross(Vector a,Vector b)//求向量叉积
{
    return a.x*b.y-b.x*a.y;
}

int andrew1(Vector p[],int n)//对A求凸包
{
    sort(p+1,p+n+1);
    int m=1,i;
    for(i=1;i<=n;i++)//求下凸壳
    {
        while(m>2 && cross(res[m-1]-res[m-2],p[i]-res[m-2])<0) m--;
        res[m++]=p[i];
    }
    int k=m;
    for(i=n-1;i>=1;i--)//上凸壳
    {
        while(m>k && cross(res[m-1]-res[m-2],p[i]-res[m-2])<0) m--;
        res[m++]=p[i];
    }
    if(m>2) m--;
    return m;
}

int andrew2(Vector p[],int n)//对AB求凸包
{
    sort(p+1,p+n+1);
    int m=1,i;
    for(i=1;i<=n;i++)
    {
        while(m>2 && cross(res2[m-1]-res2[m-2],p[i]-res2[m-2])<0) m--;
        res2[m++]=p[i];
    }
    int k=m;
    for(i=n-1;i>=1;i--)
    {
        while(m>k && cross(res2[m-1]-res2[m-2],p[i]-res2[m-2])<0) m--;
        res2[m++]=p[i];
    }
    if(m>2) m--;
    return m;
}
```
核心实现思想：`cross`函数计算向量叉积，用于判断点的相对位置。`andrew1`和`andrew2`函数分别对多边形 $A$ 和合并后的点集求凸包，先排序，再分别求下凸壳和上凸壳，通过叉积判断是否需要弹出栈顶元素（即当前凸包的最后一个点），从而构建凸包。

### 最优关键思路或技巧
将复杂的多边形包含判断问题转化为凸包比较问题，利用凸包的性质简化判断过程。同时，掌握Andrew算法求凸包，能有效处理几何问题中的凸包求解与边界判断。

### 可拓展之处
同类型题常出现在计算几何领域，类似套路包括利用几何性质（如叉积判断点与线、多边形的位置关系）简化复杂的几何位置判断问题。

### 洛谷推荐题目
- [P2742 【模板】二维凸包](https://www.luogu.com.cn/problem/P2742)
- [P3829 [SHOI2012]信用卡凸包](https://www.luogu.com.cn/problem/P3829)
- [P4290 [HAOI2008] 下落的圆盘](https://www.luogu.com.cn/problem/P4290) 

---
处理用时：50.17秒