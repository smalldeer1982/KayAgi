# 题目信息

# [USACO08FEB] Game of Lines S

## 题目背景

Farmer John 最近发明了一个游戏，来考验自命不凡的贝茜。


## 题目描述

Farmer John has challenged Bessie to the following game: FJ has a board with dots marked at N (2 ≤ N ≤ 200) distinct lattice points. Dot i has the integer coordinates Xi and Yi (-1,000 ≤ Xi ≤ 1,000; -1,000 ≤ Yi ≤ 1,000).

Bessie can score a point in the game by picking two of the dots and drawing a straight line between them; however, she is not allowed to draw a line if she has already drawn another line that is parallel to that line. Bessie would like to know her chances of winning, so she has asked you to help find the maximum score she can obtain.

游戏开始的时 候，FJ 会给贝茜一块画着 $N (2 \le N \le 200)$ 个不重合的点的木板，其中第 $i$ 个点的横、纵坐标分别为 $X_i$ 和 $Y_i (-1000 \le X_i \le 1000, -1000 \le Y_i \le 1000)$。

贝茜可以选两个点画一条过它们的直线，当且仅当平面上不存在与画出直线 平行的直线。游戏结束时贝茜的得分，就是她画出的直线的总条数。为了在游戏中胜出，贝茜找到了你，希望你帮她计算一下最大可能得分。


## 说明/提示

贝茜能画出以下 $4$ 种斜率的直线：$-1$，$0$，$\dfrac{1}{3}$ 以及 $1$。

## 样例 #1

### 输入

```
4 
-1 1 
-2 0 
0 0 
1 1```

### 输出

```
4 ```

# AI分析结果



### 综合分析与结论
题目要求计算所有点对连线的不同斜率数量，避免平行线。核心是遍历所有点对计算斜率并去重。各题解主要区别在于去重方法及垂直处理。关键点包括：使用集合去重、处理垂直线斜率为特殊值、控制点对遍历顺序避免重复计算。

### 高星题解推荐
#### 1. 作者：planche（5星）
**关键亮点**：使用`set`自动去重，遍历点对时仅处理`i<j`避免重复，垂直情况用极大值`INF`表示，代码简洁高效。
```cpp
#include <bits/stdc++.h>
using namespace std;
set<double> k;
double x[300], y[300], n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        for (int j = 1; j <= i-1; j++) {
            if (x[i] == x[j]) k.insert(INT_MAX); // 垂直线
            else k.insert((y[i]-y[j])/(x[i]-x[j]));
        }
    }
    cout << k.size();
}
```

#### 2. 作者：YosemiteHe（5星）
**关键亮点**：利用`map`存储斜率，循环控制`i<j`确保不重复，垂直线用固定值标记，逻辑清晰。
```cpp
#include <iostream>
#include <map>
using namespace std;
int main() {
    int n; double x[205], y[205];
    cin >> n;
    map<double, bool> mp;
    for (int i=1; i<=n; i++) cin >> x[i] >> y[i];
    int ans = 0;
    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++) {
            double k = (x[i] == x[j]) ? 999999 : (y[j]-y[i])/(x[j]-x[i]);
            if (!mp[k]) { mp[k] = true; ans++; }
        }
    cout << ans;
}
```

#### 3. 作者：Hiraeth（5星）
**关键亮点**：通过标记`pp`处理垂直线，遍历所有点对但依赖`set`去重，强调整型转浮点的1.0乘法。
```cpp
#include<bits/stdc++.h>
using namespace std;
set<double> p;
int n, pp;
struct Point { int x, y; } a[210];
int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++) {
            if (i == j) continue;
            if (a[i].x == a[j].x) pp = 1;
            else p.insert(1.0*(a[i].y - a[j].y)/(a[i].x - a[j].x));
        }
    printf("%d", p.size() + pp);
}
```

### 关键思路与技巧总结
1. **数据结构选择**：使用`set`或`map`自动去重，简化代码。
2. **垂直线处理**：用极大值（如`INT_MAX`）表示无限斜率。
3. **遍历优化**：仅处理`i < j`的点对，避免重复计算。
4. **浮点精度**：将整型差值转为浮点时乘以`1.0`，避免整数除法。

### 相似题目推荐
1. **P2789 直线交点数**：计算不同斜率直线交点的组合数。
2. **P1053 平行线判断**：判断多组线段是否平行，需斜率比较。
3. **P3829 直角坐标系中的直线**：处理直线的多种表示形式及性质。

---
处理用时：259.95秒