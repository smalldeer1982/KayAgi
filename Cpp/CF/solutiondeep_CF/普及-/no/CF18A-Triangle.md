# 题目信息

# Triangle

## 题目描述

At a geometry lesson Bob learnt that a triangle is called right-angled if it is nondegenerate and one of its angles is right. Bob decided to draw such a triangle immediately: on a sheet of paper he drew three points with integer coordinates, and joined them with segments of straight lines, then he showed the triangle to Peter. Peter said that Bob's triangle is not right-angled, but is almost right-angled: the triangle itself is not right-angled, but it is possible to move one of the points exactly by distance 1 so, that all the coordinates remain integer, and the triangle become right-angled. Bob asks you to help him and find out if Peter tricks him. By the given coordinates of the triangle you should find out if it is right-angled, almost right-angled, or neither of these.

## 样例 #1

### 输入

```
0 0 2 0 0 1
```

### 输出

```
RIGHT
```

## 样例 #2

### 输入

```
2 3 4 5 6 6
```

### 输出

```
NEITHER
```

## 样例 #3

### 输入

```
-1 0 2 0 0 1
```

### 输出

```
ALMOST
```

# AI分析结果

### 题目内容
# 三角形

## 题目描述
在一堂几何课上，鲍勃学到如果一个三角形是非退化的且其中一个角为直角，那么这个三角形就被称为直角三角形。鲍勃决定立刻画这样一个三角形：他在一张纸上画了三个具有整数坐标的点，并用直线段将它们连接起来，然后他把这个三角形拿给彼得看。彼得说鲍勃画的三角形不是直角三角形，但几乎是直角三角形：这个三角形本身不是直角三角形，但可以将其中一个点恰好移动距离1，使得所有坐标仍然是整数，并且这个三角形变成直角三角形。鲍勃请你帮他弄清楚彼得是否在骗他。根据给定的三角形坐标，你应该判断它是直角三角形、几乎是直角三角形，还是两者都不是。

## 样例 #1
### 输入
```
0 0 2 0 0 1
```
### 输出
```
RIGHT
```

## 样例 #2
### 输入
```
2 3 4 5 6 6
```
### 输出
```
NEITHER
```

## 样例 #3
### 输入
```
-1 0 2 0 0 1
```
### 输出
```
ALMOST
```

### 算法分类
枚举

### 综合分析与结论
这几道题解的核心思路都是先判断给定三角形是否为直角三角形，再通过移动一个点来判断是否能成为直角三角形，最后确定三角形属于哪种类型。
1. **思路**：均围绕直角三角形的判定条件展开，先直接判断原三角形，再通过移动点来进一步判断。
2. **算法要点**：多数题解利用勾股定理判断直角三角形，部分使用向量点积判断。移动点时，通过枚举每个点在上下左右四个方向移动1单位的情况进行判断。
3. **解决难点**：重点在于如何高效准确地判断直角三角形以及全面地枚举点的移动情况，同时要注意避免因浮点数运算带来的精度问题。

### 所选的题解
#### 作者：yzh_Error404 (5星)
- **关键亮点**：代码结构清晰，封装了距离计算、直角三角形判断等函数。在计算距离时，为避免精度问题，直接使用平方和形式，不进行开方运算。在直角三角形判断函数中，考虑到可能出现两点重合情况进行了特殊处理。
```cpp
inline int dist(int x1,int y1,int x2,int y2)
{
    return (x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2);
}
inline bool check()
{
    memset(dis, 0x3f, sizeof(dis));
    cnt = 0;
    for(register int i = 1; i <= 3; i++)
        for(register int j = i; j <= 3; j++)
            if(i!= j && e[i].x == e[j].x && e[i].y == e[j].y)return false;
    for(register int i = 1; i <= 3; i++)
        for(register int j = i; j <= 3; j++)
            if(i!= j)dis[++cnt]=dist(e[i].x, e[i].y, e[j].x, e[j].y);
    sort(dis + 1, dis + 4, cmp);
    if((dis[1]+dis[2]) == dis[3])return true;
    return false;
}
```
#### 作者：Sophon (4星)
- **关键亮点**：使用向量点积的方式判断直角三角形，思路较为新颖。利用方向数组控制点的移动，代码简洁明了，逻辑清晰。
```cpp
inline int calc(const pair<int, int>& vec1, const pair<int, int>& vec2)
{
    return vec1.first * vec2.first+vec1.second * vec2.second;
}
inline bool zero(const pair<int, int>& vec)
{
    return!(vec.first || vec.second);
}
bool xhl(const pair<int, int>& a, const pair<int, int>& b, const pair<int, int>& c)
{
    pii v1 = { b.first - a.first, b.second - a.second };
    pii v2 = { c.first - a.first, c.second - a.second };
    pii v3 = { c.first - b.first, c.second - b.second };
    if(zero(v1) || zero(v2) || zero(v3))
    {
        return false;
    }
    if(calc(v1, v2) == 0 || calc(v1, v3) == 0 || calc(v3, v2) == 0)
    {
        return true;
    }
    return false;
}
```
#### 作者：Argon_Cube (4星)
- **关键亮点**：将直角三角形的判断封装在`check`函数中，代码结构清晰。在枚举点的移动时，通过复制原数组并修改相应点坐标的方式，保证每次枚举相互独立，逻辑清晰易懂。
```cpp
bool check(vector<pair<int,int>> points)
{
    int fst=(points[0].first - points[1].first)*(points[0].first - points[1].first)+(points[0].second - points[1].second)*(points[0].second - points[1].second);
    int scd=(points[1].first - points[2].first)*(points[1].first - points[2].first)+(points[1].second - points[2].second)*(points[1].second - points[2].second);
    int trd=(points[2].first - points[0].first)*(points[2].first - points[0].first)+(points[2].second - points[0].second)*(points[2].second - points[0].second);
    if((fst + scd == trd||scd + trd == fst||trd + fst == scd)&&fst > 0&&scd > 0&&trd > 0)
        return true;
    return false;
}
```

### 最优关键思路或技巧
1. **避免精度问题**：在计算两点间距离时，直接使用距离的平方进行计算和比较，避免开方运算带来的精度问题。
2. **代码封装**：将直角三角形判断、距离计算等功能封装成函数，提高代码的可读性和复用性。
3. **方向数组**：使用方向数组来控制点的移动方向，使代码简洁且逻辑清晰，便于枚举所有可能的移动情况。

### 拓展
此类题目属于几何与枚举结合的类型，类似套路包括通过枚举几何图形的顶点位置、边长等参数，结合几何性质（如三角形的内角关系、边长关系等）来解决问题。对于同类型题目，可以考虑从不同的几何图形（如矩形、多边形等）以及不同的条件判断（如相似、全等）等方面进行拓展。

### 推荐题目
1. **P1036 [NOIP2002 普及组] 选数**：通过枚举组合来满足特定的数学条件，与本题枚举点的位置满足直角三角形条件类似。
2. **P1157 组合的输出**：考察枚举组合情况，与本题枚举点的移动情况属于同一类枚举问题。
3. **P1313 计算系数**：结合数学知识，通过枚举指数来计算多项式系数，同样需要枚举不同情况并进行判断。 

---
处理用时：65.90秒