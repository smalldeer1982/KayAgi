# 题目信息

# Constellation

## 题目描述

Cat Noku has obtained a map of the night sky. On this map, he found a constellation with $ n $ stars numbered from $ 1 $ to $ n $ . For each $ i $ , the $ i $ -th star is located at coordinates $ (x_{i},y_{i}) $ . No two stars are located at the same position.

In the evening Noku is going to take a look at the night sky. He would like to find three distinct stars and form a triangle. The triangle must have positive area. In addition, all other stars must lie strictly outside of this triangle. He is having trouble finding the answer and would like your help. Your job is to find the indices of three stars that would form a triangle that satisfies all the conditions.

It is guaranteed that there is no line such that all stars lie on that line. It can be proven that if the previous condition is satisfied, there exists a solution to this problem.

## 说明/提示

In the first sample, we can print the three indices in any order.

In the second sample, we have the following picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618C/221daa860cc5914a84b65151dd3afba0407aed90.png)Note that the triangle formed by starts $ 1 $ , $ 4 $ and $ 3 $ doesn't satisfy the conditions stated in the problem, as point $ 5 $ is not strictly outside of this triangle (it lies on it's border).

## 样例 #1

### 输入

```
3
0 1
1 0
1 1
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
5
0 0
0 2
2 0
2 2
1 1
```

### 输出

```
1 3 5
```

# AI分析结果

### 题目内容
# 星座

## 题目描述
猫Noku得到了一张夜空地图。在这张地图上，他发现了一个由$n$颗星星组成的星座，这些星星从$1$到$n$编号。对于每一个$i$，第$i$颗星星位于坐标$(x_{i}, y_{i})$处。没有两颗星星位于同一位置。

在晚上，Noku打算仰望夜空。他想找到三颗不同的星星并组成一个三角形。这个三角形必须有正面积。此外，所有其他星星都必须严格位于这个三角形之外。他在寻找答案时遇到了困难，希望得到你的帮助。你的任务是找到三颗星星的索引，它们组成的三角形满足所有条件。

保证不存在一条直线使得所有星星都在这条直线上。可以证明，如果满足前面的条件，那么这个问题就存在一个解。

## 说明/提示
在第一个样例中，我们可以按任意顺序输出这三个索引。

在第二个样例中，我们有以下图片。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618C/221daa860cc5914a84b65151dd3afba0407aed90.png)
注意，由星星$1$、$4$和$3$组成的三角形不满足问题中所述的条件，因为点$5$并不严格在这个三角形之外（它位于三角形的边界上）。

## 样例 #1
### 输入
```
3
0 1
1 0
1 1
```
### 输出
```
1 2 3
```
## 样例 #2
### 输入
```
5
0 0
0 2
2 0
2 2
1 1
```
### 输出
```
1 3 5
```

### 算法分类
构造

### 题解综合分析与结论
三道题解均围绕如何构造出满足条件的三角形展开。思路上，都先固定一个点，再基于与该点的关系去选择另外两个点。算法要点在于通过距离、面积等度量来挑选点，难点主要是保证所选三角形不包含其他点且面积为正。

### 所选的题解
- **作者：封禁用户 (5星)**
  - **关键亮点**：采用贪心策略，先固定1号点，挑选离1号点最近的点，再对剩余点按到1号点和已选点距离最小值排序，最后利用斜率判断三点是否共线，思路清晰，代码实现简洁高效，考虑到了避免除零错误。
  - **重点代码核心实现思想**：定义结构体存储点的坐标、距离等信息，通过两次排序和斜率判断找到满足条件的三个点。
```cpp
struct p
{
    long long x, y, z, q;
};
long long n;
bool cmp(p l, p r)
{
    return l.z < r.z;
}
int main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].x >> a[i].y;
        a[i].z = (a[i].x - a[1].x) * (a[i].x - a[1].x) + (a[i].y - a[1].y) * (a[i].y - a[1].y);
        a[i].q = i;
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        a[i].z = min((a[i].x - a[1].x) * (a[i].x - a[1].x) + (a[i].y - a[1].y) * (a[i].y - a[1].y), (a[i].x - a[2].x) * (a[i].x - a[2].x) + (a[i].y - a[2].y) * (a[i].y - a[2].y));
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 3; i <= n; i++)
    {
        if ((a[2].x - a[1].x) * (a[i].y - a[2].y)!= (a[i].x - a[2].x) * (a[2].y - a[1].y))
        {
            cout << a[1].q << ' ' << a[2].q << ' ' << a[i].q;
            return 0;
        }
    }
    return 0;
}
```
- **作者：recollect_i (4星)**
  - **关键亮点**：思路简洁明了，先固定1号点，找离1号点最近的点作为第二个点，再通过计算三角形面积找到使面积最小的第三个点，代码实现直观易懂。
  - **重点代码核心实现思想**：定义距离和面积计算函数，通过循环遍历找到距离最近点和面积最小的三角形对应的点。
```cpp
double dis(double ax, double ay, double bx, double by)
{
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
double area(double ax, double ay, double bx, double by, double cx, double cy)
{
    double tx1 = bx - ax, ty1 = by - ay, tx2 = cx - ax, ty2 = cy - ay;
    return fabs(tx1 * ty2 - tx2 * ty1) / 2;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &x[i], &y[i]);
    int t = 2;
    double dt = dis(x[1], y[1], x[2], y[2]);
    for (int i = 3; i <= n; i++)
    {
        double d = dis(x[1], y[1], x[i], y[i]);
        if (d < dt)
        {
            dt = d;
            t = i;
        }
    }
    double ma = 1e20;
    int rt;
    for (int i = 2; i <= n; i++)
        if (i!= t)
        {
            double xx = area(x[1], y[1], x[t], y[t], x[i], y[i]);
            if (xx > esp && xx <= ma)
            {
                rt = i;
                ma = xx;
            }
        }
    printf("%d %d %d\n", 1, t, rt);
    return 0;
}
```

### 最优关键思路或技巧
固定一个点后，利用距离和面积等几何度量来贪心选择另外两个点，同时注意在判断三点共线时使用交叉相乘避免除零错误。

### 可拓展之处
同类型题可考虑在更高维度空间中寻找满足特定条件的多面体，类似算法套路是先固定部分元素，再基于某种度量标准逐步选择其他元素来构造满足条件的图形。

### 洛谷相似题目推荐
- P1269 邮递员送信：涉及图论中的最短路问题，可类比本题通过逐步选择路径来构造最优解。
- P1195 口袋的天空：并查集与图论结合，与本题构造满足条件图形类似，需构造满足连通性等条件的图。
- P1433 吃奶酪：可看作是在平面点集中寻找满足特定条件的路径，类似本题在点集中构造满足条件的图形。 

---
处理用时：55.71秒