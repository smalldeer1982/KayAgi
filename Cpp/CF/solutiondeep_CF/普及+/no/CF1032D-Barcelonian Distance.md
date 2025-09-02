# 题目信息

# Barcelonian Distance

## 题目描述

In this problem we consider a very simplified model of Barcelona city.

Barcelona can be represented as a plane with streets of kind $ x = c $ and $ y = c $ for every integer $ c $ (that is, the rectangular grid). However, there is a detail which makes Barcelona different from Manhattan. There is an avenue called Avinguda Diagonal which can be represented as a the set of points $ (x, y) $ for which $ ax + by + c = 0 $ .

One can walk along streets, including the avenue. You are given two integer points $ A $ and $ B $ somewhere in Barcelona. Find the minimal possible distance one needs to travel to get to $ B $ from $ A $ .

## 说明/提示

The first example is shown on the left picture while the second example us shown on the right picture below. The avenue is shown with blue, the origin is shown with the black dot.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1032D/d9be16980f00189d5199b81c1601b819612b0d94.png)

## 样例 #1

### 输入

```
1 1 -3
0 3 3 0
```

### 输出

```
4.2426406871
```

## 样例 #2

### 输入

```
3 1 -9
0 3 3 -1
```

### 输出

```
6.1622776602
```

# AI分析结果

### 题目内容
# 巴塞罗那距离

## 题目描述
在本题中，我们考虑巴塞罗那市的一个非常简化的模型。

巴塞罗那可以表示为一个平面，对于每个整数 $c$，都有 $x = c$ 和 $y = c$ 这样的街道（即矩形网格）。然而，有一个细节使巴塞罗那与曼哈顿不同。有一条名为对角线大道（Avinguda Diagonal）的街道，可以表示为满足 $ax + by + c = 0$ 的点 $(x, y)$ 的集合。

人们可以沿着街道行走，包括这条大道。给定巴塞罗那的两个整数点 $A$ 和 $B$。求从 $A$ 到 $B$ 所需行走的最小可能距离。

## 说明/提示
第一个示例显示在下图左侧，第二个示例显示在右侧。大道用蓝色表示，原点用黑点表示。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1032D/d9be16980f00189d5199b81c1601b819612b0d94.png)

## 样例 #1
### 输入
```
1 1 -3
0 3 3 0
```
### 输出
```
4.2426406871
```

## 样例 #2
### 输入
```
3 1 -9
0 3 3 -1
```
### 输出
```
6.1622776602
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学计算，通过分析从点 $A$ 到点 $B$ 可能的路径情况来求解最短距离。主要的路径情况包括只走网格、经过斜线（大道）的不同组合方式。各题解的算法要点在于计算直线与网格线的交点，以及利用勾股定理计算路径长度。解决难点在于全面考虑所有可能的路径情况，避免遗漏，同时要注意计算过程中的精度问题。

### 所选的题解
- **作者：是个汉子 (5星)**
    - **关键亮点**：思路清晰，直接枚举从起点到终点经过斜线的四种路径以及不经过斜线的路径，利用初中知识求交点和计算路径长，代码简洁明了。
    - **个人心得**：提到记得用 `fabs` 处理绝对值，否则样例过不去，强调了细节对解题的重要性。
    - **核心代码片段**：
```c++
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<iostream>

using namespace std;
double a,b,c,x[10],y[10],ans;

int main(){
    ios::sync_with_stdio(false);
    cin>>a>>b>>c>>x[1]>>y[1]>>x[2]>>y[2];
    ans=fabs(x[1]-x[2])+fabs(y[1]-y[2]);
    x[3]=x[1];
    y[3]=(-a*x[1]-c)/b;
    x[4]=(-b*y[1]-c)/a;
    y[4]=y[1];
    x[5]=x[2];
    y[5]=(-a*x[2]-c)/b;
    x[6]=(-b*y[2]-c)/a;
    y[6]=y[2];
    for(int i=3;i<=4;i++)
        for(int j=5;j<=6;j++){
            ans=min(ans,fabs(x[1]-x[i])+fabs(y[1]-y[i])+
                    sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+
                    fabs(x[2]-x[j])+fabs(y[2]-y[j]));
        }
    cout<<setprecision(12)<<ans<<endl;
    return 0;
}
```
核心实现思想：先初始化不经过斜线时的曼哈顿距离为初始答案，然后计算起点和终点所在网格线与斜线的交点坐标，通过两层循环枚举不同交点组合，计算经过这些交点的路径长度并更新最小路径长度。
- **作者：MoyunAllgorithm (4星)**
    - **关键亮点**：对路径情况进行了详细分类，通过感性理解证明路径必然属于五种情况，使枚举更具逻辑性，代码实现简洁。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
#define DB double
using namespace std;
const int MAXN=1e5+5;
int A,B,C,xa,ya,xb,yb;
DB Dis(DB xi,DB yi,DB xj,DB yj)
{
	return sqrt((xi-xj)*(xi-xj)+(yi-yj)*(yi-yj));
}
int main()
{
	scanf("%d %d %d %d %d %d %d",&A,&B,&C,&xa,&ya,&xb,&yb);
	DB ans=1.0*abs(ya-yb)+abs(xa-xb);
	DB ay=((DB)1.0*-B*ya-C)/A; //C
	DB ax=((DB)1.0*-A*xa-C)/B; //D
	DB by=((DB)1.0*-B*yb-C)/A; //E
	DB bx=((DB)1.0*-A*xb-C)/B; //F
   //求出C,D,E,F点
	DB d1=1.0*abs((DB)ay-xa)+Dis(ay,ya,xb,bx)+abs((DB)bx-yb);
	DB d2=1.0*abs((DB)ay-xa)+Dis(ay,ya,by,yb)+abs((DB)by-xb);
	DB d3=1.0*abs((DB)ax-ya)+Dis(xa,ax,xb,bx)+abs((DB)bx-yb);
	DB d4=1.0*abs((DB)ax-ya)+Dis(xa,ax,by,yb)+abs((DB)by-xb);
	ans=min(ans,min(min(d1,d2),min(d3,d4)));
	printf("%.10lf\n",ans);
	return 0;
}
```
核心实现思想：先定义距离计算函数，读入数据后初始化不经过斜线的曼哈顿距离为答案，接着计算出起点和终点所在横纵线与斜线的交点，分别计算五种路径的长度并取最小值。
- **作者：NastiY_iN_saNitY (4星)**
    - **关键亮点**：考虑到精度问题，提出将 `double` 变为 `long double` 以及用除法避免乘法掉精度的建议。同时通过对称变换简化讨论情况，逻辑较为严谨。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
struct line { double a, b, c; };
struct point { double x, y; }; point A, B;
double solvex(line l, double y) { return -(l.b * y / l.a + l.c / l.a); }
double solvey(line l, double x) { return -(l.a * x / l.b + l.c / l.b); }//计算交点
double manhattan(point A, point B) { return fabs(A.x - B.x) + fabs(A.y - B.y); }
double sq(double x) { return x * x; }
double dist(point A, point B) { return sqrtl(sq(A.x - B.x) + sq(A.y - B.y)); }
int printt(double x) { cout << fixed << setprecision(10) << min(x, manhattan(A, B)) << endl; return 0; } //取 min 实现
int solve() {
    line l; cin >> l.a >> l.b >> l.c;
    cin >> A.x >> A.y >> B.x >> B.y;
    if(l.a == 0 || l.b == 0) return printt(manhattan(A, B));
    if(A.x > B.x) swap(A, B);
    if(A.y < B.y) {
        B.y = 2 * A.y - B.y;
        l.c = l.c + 2 * A.y * l.b;
        l.b *= -1;
        //对称实现
    }
    if(A.x == B.x || A.y == B.y) {return printt(manhattan(A, B));}
    double dx = solvex(l, A.y), dy = solvey(l, A.x);
    if(dx >= A.x) {
        double res = 0, ddy = solvey(l, B.x);
        res += dx - A.x;
        if(ddy <= B.y) {
            double ddx = solvex(l, B.y);
            res += B.x - ddx;
            res += dist({dx, A.y}, {ddx, B.y});
            return printt(res);
        }
        res += ddy - B.y;
        res += dist({dx, A.y}, {B.x, ddy});
        return printt(res);
    } else {
        double res = 0, ddx = solvex(l, B.y);
        res += A.y - dy;
        if(ddx >= B.x) {
            double ddy = solvey(l, B.x);
            res += ddy - B.y;
            res += dist({A.x, dy}, {B.x, ddy});
            return printt(res);
        }
        res += fabs(ddx - B.x);
        res += dist({A.x, dy}, {ddx, B.y});
        return printt(res);
    }
    return 0;
}
signed main() { solve(); system("pause"); return 0; }
```
核心实现思想：定义直线和点的结构体，以及计算交点、曼哈顿距离、两点距离的函数。通过对称变换使 $B$ 在 $A$ 下方，根据直线与起点、终点所在网格线交点的位置关系分情况计算路径长度，并与曼哈顿距离取最小值输出。

### 最优关键思路或技巧
全面分析路径情况，通过枚举所有可能的路径组合（包括经过斜线和不经过斜线）来求解最短距离。在实现过程中，要注意利用数学知识准确计算直线与网格线的交点坐标，同时关注精度问题，可采用合适的数据类型（如 `long double`）和计算方式（如用除法避免乘法掉精度）。

### 同类型题或类似算法套路拓展
此类题目通常基于几何图形（如网格、直线等），通过分析点与线的关系，利用数学知识（如交点计算、距离公式）来求解最短路径或最优值。类似套路包括对路径情况进行分类讨论，利用几何性质简化计算等。

### 洛谷相似题目推荐
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：通过枚举和数学计算求解满足条件的数对，考察数论和枚举技巧。
- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：利用递推和数学规律求解不同走法数量，涉及数学思维和递推算法。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合数论知识和斐波那契数列性质，通过数学推导和计算求解最大公约数，考察数学分析和代码实现能力。

---
处理用时：95.17秒