# 题目信息

# Power Transmission (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

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

### 题目翻译
# 电力传输（简单版）

## 题目描述
这个问题与下一个问题相同，但约束条件更小。

一个周日的早晨，三个好朋友赛琳娜（Selena）、志郎（Shiro）和凯蒂（Katie）决定去附近的发电站游玩（不要在家尝试这种行为）。到达发电站后，猫咪们对由许多烟囱、电线杆和电线组成的大型电力传输系统印象深刻。因为它们是猫咪，所以觉得那些东西无比巨大。

在发电站的入口处，有一张描绘复杂布线系统的地图。赛琳娜是三个朋友中数学最好的。他决定在笛卡尔平面上绘制这张地图。现在，每根电线杆都对应平面上的一个点 $(x_i, y_i)$。由于每根电线杆都是不同的，所以代表这些电线杆的所有点都是不同的。此外，每两根电线杆之间都通过电线相互连接。电线是平面上向两个方向无限延伸的直线。如果有两个以上的电线杆位于同一条直线上，它们将由一条共同的电线连接。

赛琳娜认为，每当两条不同的电线相交时，它们可能会相互干扰并造成损坏。所以他想知道，有多少对电线会相交？你能帮他解决这个问题吗？

## 说明/提示
在第一个样例中：
![样例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/2317b27306c4c65175012212cdceb02039be0972.png)
在第二个样例中：
![样例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/0792ee139dbdc603551bd0c872a1bea92551eac5.png)
注意，三个电线杆 $(0, 0)$、$(0, 2)$ 和 $(0, 4)$ 由一条电线连接。

在第三个样例中：
![样例3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

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
枚举

### 综合分析与结论
这两道题解的核心思路都是通过枚举点对来确定直线，再判断直线间是否相交。不同的是，FFTotoro 的题解使用 `vector` 存储直线信息，并通过标记跳过重复直线；Rosmarinus 的题解使用结构体存储直线信息，用 `dfs` 来判重。两者都需要处理三点共线的情况，并且通过比较斜率来判断直线是否相交。

### 题解评分
- **FFTotoro**：4星。思路清晰，代码简洁，使用 `vector` 存储直线信息，标记跳过重复直线的方法简单有效。
- **Rosmarinus**：3星。思路详细，但代码相对复杂，`dfs` 判重的实现增加了代码的复杂度。

### 所选题解
- **FFTotoro（4星）**
  - 关键亮点：思路清晰，代码简洁，使用标记跳过重复直线的方法简单有效。

### 重点代码
```cpp
// 判断三点共线的函数
bool pd(pii a,pii b,pii c){
  return (b.nd-a.nd)*(c.st-a.st)==(b.st-a.st)*(c.nd-a.nd);
}

int main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector<pii> a(n),d;
  vector<vector<bool> > b(n,vector<bool>(n));
  for(auto &[x,y]:a)cin>>x>>y;
  for(int i=0;i<n-1;i++)
    for(int j=i+1;j<n;j++){
      if(b[i][j])continue;
      vector<int> v={i,j};
      for(int k=j+1;k<n;k++)
        if(pd(a[i],a[j],a[k]))v.emplace_back(k); // 统计三点共线
      for(auto &i:v)for(auto &j:v)b[i][j]=true; // 打标记
      d.emplace_back(a[i].st-a[j].st,a[i].nd-a[j].nd);
    }
  for(auto &i:d)for(auto &j:d)
    c+=(i.st*j.nd!=i.nd*j.st); // 枚举斜率不相同的直线有多少对
  cout<<(c>>1)<<endl; // 每两个点统计了两遍，最终答案需要除以二
  return 0;
}
```
**核心实现思想**：首先定义了判断三点共线的函数 `pd`。在 `main` 函数中，读取输入的点坐标，通过两层循环枚举点对，对于每一对点，找出所有与它们共线的点并存储在 `v` 中，同时给这些点对打上标记，避免重复处理。将直线的斜率信息存储在 `d` 中，最后枚举 `d` 中的直线对，判断斜率是否不同，统计相交直线的对数，由于每对直线被统计了两次，最终答案需要除以2。

### 关键思路或技巧
- 使用标记数组跳过重复的直线，避免重复计算。
- 通过判断三点共线的函数处理三点共线的情况。

### 拓展思路
同类型题目通常会涉及平面几何中的点、线关系，可能会有更多的约束条件或更高的复杂度。可以考虑使用更高效的数据结构和算法来优化，例如使用哈希表存储直线信息，减少枚举的时间复杂度。

### 推荐题目
1. [P1355 神秘大三角](https://www.luogu.com.cn/problem/P1355)
2. [P1876 开灯](https://www.luogu.com.cn/problem/P1876)
3. [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)

### 个人心得
FFTotoro 认为这道题很水，做完这题可以去做一下 [[ABC248E] K - colinear Line](https://www.luogu.com.cn/problem/AT_abc248_e)，可以进一步巩固相关知识点。 

---
处理用时：47.07秒