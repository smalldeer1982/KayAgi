# 题目信息

# Han Solo and Lazer Gun

## 题目描述

There are $ n $ Imperial stormtroopers on the field. The battle field is a plane with Cartesian coordinate system. Each stormtrooper is associated with his coordinates $ (x,y) $ on this plane.

Han Solo has the newest duplex lazer gun to fight these stormtroopers. It is situated at the point $ (x_{0},y_{0}) $ . In one shot it can can destroy all the stormtroopers, situated on some line that crosses point $ (x_{0},y_{0}) $ .

Your task is to determine what minimum number of shots Han Solo needs to defeat all the stormtroopers.

The gun is the newest invention, it shoots very quickly and even after a very large number of shots the stormtroopers don't have enough time to realize what's happening and change their location.

## 说明/提示

Explanation to the first and second samples from the statement, respectively:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514B/e0665254dc28c85d59225f8c53a8542938957367.png)

## 样例 #1

### 输入

```
4 0 0
1 1
2 2
2 0
-1 -1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1 2
1 1
1 0
```

### 输出

```
1
```

# AI分析结果



# Han Solo and Lazer Gun 中文重写

## 题目描述

战场上有 $n$ 个帝国暴风兵，战场是平面直角坐标系。每个暴风兵的坐标为 $(x,y)$。

Han Solo 的新型双筒激光枪位于 $(x_0,y_0)$ 点，每次射击可以消灭所有位于穿过该点直线上的暴风兵。

求消灭所有暴风兵需要的最少射击次数。

## 样例 #1

### 输入
```
4 0 0
1 1
2 2
2 0
-1 -1
```

### 输出
```
2
```

## 样例 #2

### 输入
```
2 1 2
1 1
1 0
```

### 输出
```
1
```

---

**算法分类**: 数学

---

## 题解分析与结论

所有题解核心思路均为：将枪点视为坐标原点，统计不同方向直线的数量。关键点在于：
1. 用斜率或约分向量表示方向
2. 处理垂直线（x=0）的特殊情况
3. 使用集合或排序去重统计不同方向

---

## 精选题解 (4★+)

### 作者：to_be_continued (5★)
**关键亮点**：
- 使用约分后的分数向量表示方向，避免浮点精度问题
- 通过gcd约分实现精确方向判断
- 独立处理x=0和y=0的特殊情况

**核心代码**：
```cpp
struct aa{ int x,y; } a[1000]; //存储约分后的方向向量

void sj(int x,int y,int &z){
    if(x==0){ //处理垂直线
        for(int i=1;i<=z;i++)
            if(a[i].x==0) return;
        a[++z].x=0; a[z].y=1;
    } else if(y==0){ //处理水平线
        for(int i=1;i<=z;i++)
            if(a[i].y==0) return;
        a[++z].x=1; a[z].y=0;
    } else { //普通情况
        int k = gcd(x,y);
        x/=k; y/=k;
        //...存储约分后的向量
    }
}
```

### 作者：亦枫 (4★)
**关键亮点**：
- 使用set自动去重
- 用1e9表示无限大斜率
- 代码简洁高效

**核心实现**：
```cpp
set<long double> s;
for(每个点){
    dx = x - x0;
    dy = y - y0;
    if(dx != 0) s.insert(dy/dx);
    else s.insert(1e9);
}
cout << s.size();
```

### 作者：codemap (4★)
**关键亮点**：
- 通过排序+遍历实现去重
- 用2147483647表示垂直线
- 避免使用STL容器

**核心逻辑**：
```cpp
sort(a+1, a+n+1);
int ans = 1;
for(int i=2; i<=n; i++)
    if(a[i] != a[i-1]) ans++;
```

---

## 最优技巧总结

1. **数学建模**：将问题转化为方向向量统计问题
2. **精度处理**：使用分数约分代替浮点运算避免精度误差
3. **特殊值表示**：用极大值表示垂直线方向
4. **去重方式**：优先选择集合(自动去重)或排序+遍历

---

## 同类题目推荐

1. [P1355 神秘大三角](https://www.luogu.com.cn/problem/P1355) - 几何位置关系判断
2. [P2789 直线交点数](https://www.luogu.com.cn/problem/P2789) - 直线特征统计
3. [CF514B 同类题](https://codeforces.com/problemset/problem/514/B) - 原题加强版练习

---
处理用时：52.25秒