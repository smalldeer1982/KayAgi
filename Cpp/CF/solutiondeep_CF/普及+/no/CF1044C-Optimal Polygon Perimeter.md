# 题目信息

# Optimal Polygon Perimeter

## 题目描述

You are given $ n $ points on the plane. The polygon formed from all the $ n $ points is strictly convex, that is, the polygon is convex, and there are no three collinear points (i.e. lying in the same straight line). The points are numbered from $ 1 $ to $ n $ , in clockwise order.

We define the distance between two points $ p_1 = (x_1, y_1) $ and $ p_2 = (x_2, y_2) $ as their Manhattan distance: $ $$$d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2|. $ $ </p><p>Furthermore, we define the perimeter of a polygon, as the sum of Manhattan distances between all adjacent pairs of points on it; if the points on the polygon are ordered as  $ p\_1, p\_2, \\ldots, p\_k $   $ (k \\geq 3) $ , then the perimeter of the polygon is  $ d(p\_1, p\_2) + d(p\_2, p\_3) + \\ldots + d(p\_k, p\_1) $ .</p><p>For some parameter  $ k $ , let's consider all the polygons that can be formed from the given set of points, having <span class="tex-font-style-bf">any</span>  $ k $  vertices, such that the polygon is <span class="tex-font-style-bf">not</span> self-intersecting. For each such polygon, let's consider its perimeter. Over all such perimeters, we define  $ f(k) $  to be the maximal perimeter.</p><p>Please note, when checking whether a polygon is self-intersecting, that the edges of a polygon are still drawn as straight lines. For instance, in the following pictures:</p><center> <img class="tex-graphics" src="/predownloaded/4e/c2/4ec25e6ecb8feac3ac0b9b7fa51a118c2b777e87.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center><p>In the middle polygon, the order of points ( $ p\_1, p\_3, p\_2, p\_4 $ ) is not valid, since it is a self-intersecting polygon. The right polygon (whose edges resemble the Manhattan distance) has the same order and is not self-intersecting, but we consider edges as straight lines. The correct way to draw this polygon is ( $ p\_1, p\_2, p\_3, p\_4 $ ), which is the left polygon.</p><p>Your task is to compute  $ f(3), f(4), \\ldots, f(n) $ . In other words, find the maximum possible perimeter for each possible number of points (i.e.  $ 3 $  to  $ n$$$).

## 说明/提示

In the first example, for $ f(3) $ , we consider four possible polygons:

- ( $ p_1, p_2, p_3 $ ), with perimeter $ 12 $ .
- ( $ p_1, p_2, p_4 $ ), with perimeter $ 8 $ .
- ( $ p_1, p_3, p_4 $ ), with perimeter $ 12 $ .
- ( $ p_2, p_3, p_4 $ ), with perimeter $ 12 $ .

For $ f(4) $ , there is only one option, taking all the given points. Its perimeter $ 14 $ .

In the second example, there is only one possible polygon. Its perimeter is $ 8 $ .

## 样例 #1

### 输入

```
4
2 4
4 3
3 0
1 3
```

### 输出

```
12 14 ```

## 样例 #2

### 输入

```
3
0 0
0 2
2 0
```

### 输出

```
8 ```

# AI分析结果

### 题目内容
# 最优多边形周长

## 题目描述
给定平面上的 \(n\) 个点。由这 \(n\) 个点构成的多边形是严格凸的，即该多边形是凸多边形，且不存在三个共线的点（即位于同一条直线上）。这些点按顺时针顺序从 \(1\) 到 \(n\) 编号。

我们定义两点 \(p_1 = (x_1, y_1)\) 和 \(p_2 = (x_2, y_2)\) 之间的距离为它们的曼哈顿距离：
\[d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2|\]

此外，我们将多边形的周长定义为其所有相邻点对之间曼哈顿距离的总和；如果多边形上的点按 \(p_1, p_2, \ldots, p_k\) （\(k \geq 3\)）的顺序排列，那么该多边形的周长为 \(d(p_1, p_2) + d(p_2, p_3) + \ldots + d(p_k, p_1)\) 。

对于某个参数 \(k\)，让我们考虑从给定的点集可以构成的所有多边形，这些多边形具有任意 \(k\) 个顶点，且多边形不自交。对于每个这样的多边形，考虑其周长。在所有这些周长中，我们定义 \(f(k)\) 为最大周长。

请注意，在检查多边形是否自交时，多边形的边仍按直线绘制。例如，在以下图片中：
<center> <img class="tex-graphics" src="/predownloaded/4e/c2/4ec25e6ecb8feac3ac0b9b7fa51a118c2b777e87.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center>
在中间的多边形中，点的顺序（\(p_1, p_3, p_2, p_4\)）是无效的，因为它是一个自交多边形。右边的多边形（其边类似于曼哈顿距离）具有相同的顺序且不自交，但我们将边视为直线。绘制此多边形的正确方法是（\(p_1, p_2, p_3, p_4\)），即左边的多边形。

你的任务是计算 \(f(3), f(4), \ldots, f(n)\) 。换句话说，找出每个可能的点数（即 \(3\) 到 \(n\)）对应的最大可能周长。

## 说明/提示
在第一个示例中，对于 \(f(3)\)，我们考虑四个可能的多边形：
- （\(p_1, p_2, p_3\)），周长为 \(12\) 。
- （\(p_1, p_2, p_4\)），周长为 \(8\) 。
- （\(p_1, p_3, p_4\)），周长为 \(12\) 。
- （\(p_2, p_3, p_4\)），周长为 \(12\) 。

对于 \(f(4)\)，只有一种选择，即取所有给定的点。其周长为 \(14\) 。

在第二个示例中，只有一个可能的多边形。其周长为 \(8\) 。

## 样例 #1
### 输入
```
4
2 4
4 3
3 0
1 3
```
### 输出
```
12 14 
```

## 样例 #2
### 输入
```
3
0 0
0 2
2 0
```
### 输出
```
8 
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路均基于曼哈顿距离下凸多边形周长的特性。由于曼哈顿距离的特点，多边形的最大周长与能将其完全包含的最小矩形周长相关。对于 \(k \geq 4\) 的情况，通过找出横纵坐标的最大、最小值对应的点，计算矩形周长即可得到最大周长；而 \(k = 3\) 时，需要遍历每个点与由横纵坐标最大、最小值点构成的矩形组合，找出能构成的最大周长。各题解在实现细节上略有不同，但整体思路一致。

### 所选的题解
- **作者：Chocola4ever (5星)**
    - **关键亮点**：思路清晰，通过具体数据和图形展示，详细解释了不同 \(k\) 值情况下的解题思路，代码实现简洁明了，注释详细。
    - **个人心得**：通过具体描点和举例hack数据，深入理解不同 \(k\) 值下选点对周长的影响。
    - **重点代码**：
```cpp
ll getC(Chocola x,Chocola y,Chocola z){
    int maxX=max(max(x.x,y.x),z.x),maxY=max(max(x.y,y.y),z.y),minX=min(min(x.x,y.x),z.x),minY=min(min(x.y,y.y),z.y);
    return ((maxX - minX) << 1)+((maxY - minY) << 1);
}
int main(){
    n = read();
    if (n == 3){ 
        printf("%lld",getC((Chocola){read(),read()},(Chocola){read(),read()},(Chocola){read(),read()}));
        return 0;
    }
    x[1]=read(),y[1]=read();
    maxx = minx = maxy = miny = (Chocola){x[1],y[1]};
    for (int i = 2;i <= n;++i){
        x[i]=read(),y[i]=read();
        if (x[i]>maxx.x)
            maxx=(Chocola){x[i],y[i]};
        if (x[i]<minx.x)
            minx=(Chocola){x[i],y[i]};
        if (y[i]>maxy.y)
            maxy=(Chocola){x[i],y[i]};
        if (y[i]<miny.y)
            miny=(Chocola){x[i],y[i]};
    }
    ll ans = ((maxx.x - minx.x) << 1)+((maxy.y - miny.y) << 1);
    int ans3 = 0;
    for(int i = 1;i <= n;i++){
        ans3 = max(max(max(ans3,abs(x[i] - maxx.x)+abs(y[i] - maxy.y)),max(ans3,abs(x[i] - maxx.x)+abs(y[i] - miny.y))),max(max(ans3,abs(x[i] - minx.x)+abs(y[i] - maxy.y)),max(ans3,abs(x[i] - minx.x)+abs(y[i] - miny.y))));
    }
    printf("%d ",ans3 << 1);
    for (int i = 4;i <= n;++i)
        printf("%lld ",ans);
    return 0;
}
```
核心实现思想：`getC` 函数计算三个点构成图形的周长。主函数中，先处理 \(n = 3\) 的特殊情况，再遍历所有点找到横纵坐标的最值点，计算 \(k \geq 4\) 时的最大周长 `ans`，最后通过枚举每个点与最值点组合的方式计算 \(k = 3\) 时的最大周长 `ans3`。

- **作者：liuyifan (4星)**
    - **关键亮点**：代码实现简洁，通过定义距离计算函数，利用循环枚举端点和查询最大值，逻辑清晰。
    - **重点代码**：
```cpp
inline ll dis(reg int i,reg int j)
{
    j %= 4;
    return abs(a[i][0] - a[j][0])+abs(a[i][1] - a[j][1]); 
}
inline ll dis2(reg int i,reg int j)
{
    return abs(a[i][0] - xi[j])+abs(a[i][1] - yi[j]); 
}
int main()
{
    scanf("%lld",&n);
    for(reg int i = 1;i <= n;i++)
    {
        scanf("%lld%lld",&x,&y);
        xi[i]=x,yi[i]=y;
        if(i == 1)
            for(reg int j = 0;j <= 3;j++)a[j][0]=x,a[j][1]=y;
        else
        {
            if(x > a[0][0])a[0][0]=x,a[0][1]=y;
            if(y < a[1][1])a[1][0]=x,a[1][1]=y;
            if(x < a[2][0])a[2][0]=x,a[2][1]=y;
            if(y > a[3][1])a[3][0]=x,a[3][1]=y;
        }
    }
    for(reg int i = 0;i <= 3;i++)
        for(reg int j = 0;j <= 3;j++)
        {
            reg ll t = dis(i,j);
            if(i == j)continue;
            for(reg int k = 1;k <= n;k++)anss = max(anss,t + dis2(i,k)+dis2(j,k));
        }
    printf("%d ",anss);
    for(reg int i = 0;i <= 3;i++)ans += dis(i,i + 1);
    for(reg int i = 4;i <= n;i++)printf("%d ",ans);
    return 0;
}
```
核心实现思想：`dis` 函数计算端点间曼哈顿距离，`dis2` 函数计算端点与其他点间曼哈顿距离。主函数中，先读入点并找出四个端点，通过三层循环枚举计算 \(k = 3\) 时的最大周长 `anss`，再计算 \(k \geq 4\) 时的最大周长 `ans`。

- **作者：Code_AC (4星)**
    - **关键亮点**：对题目分析清晰，分情况讨论 \(k \geq 4\) 和 \(k = 3\) 的情况，核心代码简洁明了。
    - **重点代码**：
```cpp
int main()
{
    n = read();
    long long maxx = -1,minx = 0x7f7f7f;
    long long maxy = -1,miny = 0x7f7f7f;
    for(register int i = 1;i <= n;i++)
    {
        x[i]=read(),y[i]=read();
        maxx = max(maxx,x[i]);
        minx = min(minx,x[i]);
        maxy = max(maxy,y[i]);
        miny = min(miny,y[i]);
    }
    long long sum = (maxx - minx+maxy - miny)*2;
    if(n == 3)
    {
        cout << sum;
        return 0;
    }
    for(register int i = 1;i <= n;i++)
    {
        if(x[i]==maxx)
            a[1]=x[i],b[1]=y[i];
        if(x[i]==minx)
            a[2]=x[i],b[2]=y[i];
        if(y[i]==maxy)
            a[3]=x[i],b[3]=y[i];
        if(y[i]==miny)
            a[4]=x[i],b[4]=y[i];
    }
    long long maxn = 0;
    for(register int i = 1;i <= n;i++)
    {
        maxn = max(maxn,abs(x[i] - minx)+abs(y[i] - miny));
        maxn = max(maxn,abs(x[i] - minx)+abs(y[i] - maxy));
        maxn = max(maxn,abs(x[i] - maxx)+abs(y[i] - maxy));
        maxn = max(maxn,abs(x[i] - maxx)+abs(y[i] - miny));
    }
    cout << maxn*2 << ' ';
    for(register int i = 4;i <= n;i++)
    {
        cout << sum << ' ';
    }
    return 0;
}
```
核心实现思想：先读入点并找出横纵坐标的最值，计算 \(k \geq 4\) 时的最大周长 `sum`。对于 \(k = 3\)，找出最值点对应的坐标，通过枚举每个点与最值点组合计算最大周长 `maxn`。

### 最优关键思路或技巧
利用曼哈顿距离下凸多边形周长与外接矩形周长的关系，通过找出横纵坐标的最值点简化计算。对于 \(k = 3\) 的特殊情况，采用枚举的方式遍历所有可能组合。

### 拓展思路
此类题目可拓展到不同距离定义下的多边形周长问题，或增加点的约束条件等。类似算法套路常用于处理几何图形在特定距离度量下的最值问题，关键在于理解距离定义对图形性质的影响。

### 洛谷题目推荐
- [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：涉及到在方格中按规则取数求最值，与本题在求最值思路上有一定相似性。
- [P1269 邮递员送信](https://www.luogu.com.cn/problem/P1269)：通过计算路径长度求最值，可类比本题计算距离和求最值的过程。
- [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：在图中求最短路问题，与本题在距离计算和最值求解方面有一定共通之处。 

---
处理用时：70.82秒