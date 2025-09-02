# 题目信息

# Heidi and the Turing Test (Easy)

## 题目描述

The Cybermen and the Daleks have long been the Doctor's main enemies. Everyone knows that both these species enjoy destroying everything they encounter. However, a little-known fact about them is that they both also love taking Turing tests!

Heidi designed a series of increasingly difficult tasks for them to spend their time on, which would allow the Doctor enough time to save innocent lives!

The funny part is that these tasks would be very easy for a human to solve.

The first task is as follows. There are some points on the plane. All but one of them are on the boundary of an axis-aligned square (its sides are parallel to the axes). Identify that point.

## 说明/提示

In both examples, the square has four sides $ x=0 $ , $ x=2 $ , $ y=0 $ , $ y=2 $ .

## 样例 #1

### 输入

```
2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
2
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 1
2 2
```

### 输出

```
0 3
```

# AI分析结果

### 题目内容重写

**Heidi 和图灵测试（简单版）**

**题目描述**

Cybermen 和 Daleks 长期以来一直是 Doctor 的主要敌人。众所周知，这两个物种都喜欢摧毁它们遇到的一切。然而，关于它们的一个鲜为人知的事实是，它们也喜欢参加图灵测试！

Heidi 为它们设计了一系列越来越难的任务，以便让 Doctor 有足够的时间拯救无辜的生命！

有趣的是，这些任务对人类来说非常容易解决。

第一个任务如下：平面上有一些点。除了其中一个点外，其他所有点都位于一个轴对齐的正方形（其边与坐标轴平行）的边界上。找出那个不在边界上的点。

**说明/提示**

在两个样例中，正方形的四条边分别为 $x=0$、$x=2$、$y=0$、$y=2$。

**样例 #1**

### 输入

```
2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

### 输出

```
1 1
```

**样例 #2**

### 输入

```
2
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 1
2 2
```

### 输出

```
0 3
```

### 算法分类
枚举

### 题解分析与结论

这道题的核心思路是通过枚举每个点，判断去掉该点后剩下的点是否构成一个正方形。大多数题解都采用了这一思路，但实现细节有所不同。部分题解通过统计点的坐标极值来判断是否构成正方形，而另一些则通过检查点是否在正方形边界上来确定。

### 精选题解

#### 题解作者：Bai_R_X (赞：40)
**星级：4.5**
**关键亮点：**
- 通过统计每条边上的点数来判断正方形的边界。
- 使用桶来记录每个坐标出现的次数，简化了判断过程。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(i=1;i<=4*n+1;i++)
{
    cin>>x[i]>>y[i];
    hx[x[i]]++;
    hy[y[i]]++;
}
for(i=0;i<=50;i++)
{
    if(hx[i]>1)
    {
        minx=min(minx,i);
        maxx=max(maxx,i);
    }
}
for(i=0;i<=50;i++)
{
    if(hy[i]>1)
    {
        miny=min(miny,i);
        maxy=max(maxy,i);
    }
}
for(i=1;i<=4*n+1;i++)
{
    if((x[i]<minx||x[i]>maxx)||(y[i]<miny||y[i]>maxy||(y[i]>miny&&y[i]<maxy&&(x[i]>minx&&x[i]<maxx))))
    {
        cout<<x[i]<<" "<<y[i];
        break;
    }
}
```

#### 题解作者：MGR_P (赞：4)
**星级：4**
**关键亮点：**
- 通过枚举每个点，判断去掉该点后剩下的点是否构成正方形。
- 使用极值判断正方形的边界，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=n;i++)
{
    bool JJ = 0;
    int maxx = MINN, maxy = MINN, miny = MAXN, minx = MAXN;
    for(int j=1;j<=n;j++)
    {
        if(i==j) continue;
        if(x[j] > maxx) maxx = x[j];
        if(y[j] > maxy) maxy = y[j];
        if(x[j] < minx) minx = x[j];
        if(y[j] < miny) miny = y[j];
    }
    if(maxx - minx != maxy - miny) continue;
    for(int j=1;j<=n;j++)
    {
        if(i==j) continue;
        if(x[j] == minx || x[j] == maxx || y[j] == miny || y[j] == maxy) continue;
        JJ = 1;
    }
    if(!JJ)
    {
        cout << x[i] << " " << y[i];
        return 0;
    }
}
```

#### 题解作者：wenqinghua1001 (赞：2)
**星级：4**
**关键亮点：**
- 通过枚举每个点，判断去掉该点后剩下的点是否构成正方形。
- 使用极值判断正方形的边界，逻辑清晰。

**核心代码：**
```cpp
bool check(int q)
{
    int by=INT_MAX, ty=INT_MIN, lx=INT_MAX, rx=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        if(i==q) continue;
        else
        {
            by=min(by,y[i]);
            ty=max(ty,y[i]);
            lx=min(lx,x[i]);
            rx=max(rx,x[i]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(i==q) continue;
        else
        {
            if(x[i]!=lx&&x[i]!=rx&&y[i]!=by&&y[i]!=ty)
            {
                return false;
            }
        }
    }
    if(ty-by==rx-lx) return true;
    else return false;
}
```

### 最优关键思路
通过枚举每个点，判断去掉该点后剩下的点是否构成正方形。使用极值判断正方形的边界，逻辑清晰且易于实现。

### 拓展思路
类似的问题可以通过枚举和极值判断来解决，例如在给定点集中找出不在某个特定形状上的点。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

---
处理用时：43.54秒