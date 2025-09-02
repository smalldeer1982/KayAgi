# 题目信息

# Power Transmission (Hard Edition)

## 题目描述

This problem is same as the previous one, but has larger constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1

### 输入

```
4
0 0
1 1
0 3
1 2
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
0 0
0 2
0 4
2 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
-1 -1
1 0
3 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容中文重写
# 电力传输（困难版）

## 题目描述
这个问题与前一个问题相同，但约束条件更大。

一个周日的早晨，三个朋友赛琳娜（Selena）、志郎（Shiro）和凯蒂（Katie）决定去附近的发电站游玩（不要在家尝试这种行为）。到达发电站后，猫咪们对由许多烟囱、电线杆和电线组成的大型电力传输系统印象深刻。因为它们是猫咪，所以觉得那些东西无比巨大。

在发电站的入口处，有一张描述复杂布线系统的地图。赛琳娜在三个朋友中数学最好。他决定在笛卡尔平面上绘制这张地图。现在，每根电线杆都对应平面上的一个点 $ (x_i, y_i) $ 。由于每根电线杆都不同，代表这些电线杆的所有点都是不同的。此外，每两根电线杆之间都通过电线相连。电线是平面上向两个方向无限延伸的直线。如果有两根以上的电线杆位于同一条直线上，它们将由一条共同的电线连接。

赛琳娜认为，只要两条不同的电线相交，它们可能会相互干扰并造成损坏。所以他想知道，有多少对电线是相交的？你能帮他解决这个问题吗？

## 说明/提示
在第一个示例中：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/2317b27306c4c65175012212cdceb02039be0972.png)
在第二个示例中：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/0792ee139dbdc603551bd0c872a1bea92551eac5.png)
请注意，三根电线杆 $ (0, 0) $、$ (0, 2) $ 和 $ (0, 4) $ 由一条电线连接。

在第三个示例中：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C2/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1
### 输入
```
4
0 0
1 1
0 3
1 2
```
### 输出
```
14
```

## 样例 #2
### 输入
```
4
0 0
0 2
0 4
2 0
```
### 输出
```
6
```

## 样例 #3
### 输入
```
3
-1 -1
1 0
3 1
```
### 输出
```
0
```

### 算法分类
组合数学

### 综合分析与结论
- **思路对比**：三位作者均采用了“两条直线不是平行就是相交”这一思路，通过计算与每条直线平行的直线数量，进而求出相交直线的对数。V1mnkE 采用直线的一般式 $a_1x + b_1y = c_1$ 来表示直线；幻影星坚强 用斜截式 $y = kx + b$ 表示直线，并单独处理斜率不存在的情况；az__eg 同样使用斜截式，但用一个特殊值处理斜率无穷大的情况。
- **算法要点**：都需要枚举所有的电线杆对来确定直线，然后对直线进行去重，最后计算相交直线的对数。
- **解决难点**：主要难点在于处理直线的表示、去重以及斜率不存在的情况。V1mnkE 通过集合和最大公约数来处理；幻影星坚强 单独处理斜率不存在的情况；az__eg 用特殊值处理斜率无穷大的情况。

### 题解评分
- V1mnkE：3星，思路清晰，但代码中使用 `double` 可能存在精度问题。
- 幻影星坚强：3星，思路明确，代码结构清晰，但处理斜率不存在的方式稍显复杂。
- az__eg：3星，使用特殊值处理斜率无穷大的情况，思路有一定创新性，但代码中使用 `long double` 也可能存在精度问题。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
- **通用建议**：在处理直线斜率时，要注意斜率不存在的情况，可以单独处理或使用特殊值表示。在使用浮点数时，要注意精度问题，可以考虑使用整数表示直线方程。
- **扩展思路**：对于此类计算几何问题，可以考虑使用向量等方法来简化计算。同时，可以尝试使用更高效的数据结构来存储和处理直线信息，提高算法效率。

### 重点代码及核心实现思想
#### V1mnkE
```cpp
map<pair<int,int>,set<int> >mp;
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
// ...
int d1=(a[i].y-a[j].y);
int d2=(a[i].x-a[j].x);
int d3=a[j].x*a[i].y-a[i].x*a[j].y;
int dls=gcd(d1,d2);
d1/=dls,d2/=dls;
if(d1<0||(d1==0&&d2<0)){
    d1=-d1,d2=-d2;
}
d3=d2*a[j].y-d1*a[j].x;
pair<int,int>k=make_pair(d1,d2);
if(mp[k].find(d3)==mp[k].end()){
    ans+=tot-(int)mp[k].size();
    tot++;
    mp[k].insert(d3);
}
```
核心思想：使用直线的一般式 $a_1x + b_1y = c_1$ 表示直线，通过最大公约数化简系数，使用 `map` 和 `set` 去重，计算相交直线的对数。

#### 幻影星坚强
```cpp
struct bian
{
    double b, k;
}eg[1000100], an[1000100];
bool pd(bian i, bian j)
{
    return (i.k < j.k || (i.k == j.k && i.b < j.b));
}
// ...
if(x[i] == x[j])
{
    an[++ anoth].k = x[i];
    continue;
}
eg[++ num].k = (y[j] - y[i]) / (x[j] - x[i]);
eg[num].b = y[i] - x[i] * eg[num].k;
// ...
sort(eg + 1, eg + num + 1, pd);
sort(an + 1, an + anoth + 1, pd);
```
核心思想：使用斜截式 $y = kx + b$ 表示直线，单独处理斜率不存在的情况，对直线进行排序和去重，计算相交直线的对数。

#### az__eg
```cpp
bool equal(long double a,long double b)
{
    if(fabs(a-b)<eps)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// ...
kk=(point[j].y-point[i].y)/(point[j].x-point[i].x);
bb=point[i].y-point[i].x*kk;
if(equal(point[j].x,point[i].x))
{
    kk=1145151919810;
    bb=point[i].x;
}
line[++cnt].k=kk;
line[cnt].b=bb;
// ...
sort(line+1,line+1+cnt);
```
核心思想：使用斜截式 $y = kx + b$ 表示直线，用特殊值处理斜率无穷大的情况，对直线进行排序和去重，计算相交直线的对数。

### 推荐洛谷题目
1. P1355 神秘大三角：考察三角形相关的计算几何知识。
2. P1183 多边形的面积：涉及多边形面积的计算，与几何计算相关。
3. P2303 [SDOI2012] Longge 的问题：涉及数学计算和组合数学的知识。

---
处理用时：57.16秒