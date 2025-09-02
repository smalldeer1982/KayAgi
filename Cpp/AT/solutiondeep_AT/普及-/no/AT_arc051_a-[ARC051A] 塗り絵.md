# 题目信息

# [ARC051A] 塗り絵

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc051/tasks/arc051_a

白く塗られた二次元平面を考えます。

まず、$ (x_1,\ y_1) $ からの距離が $ r $ 以下の部分を赤く塗ります。

そのあと、 $ x_2\ ≦\ x\ ≦\ x_3,\ y_2\ ≦\ y\ ≦\ y_3 $ を満たす $ (x,\ y) $ を青く塗ります。

なお、赤く塗られた後、更に青く塗られた部分は紫色になるとします。

赤く塗られた部分と青く塗られた部分が存在するかどうかをそれぞれ判定してください。

## 说明/提示

### 制約

- $ -100\ ≦\ x_1,\ y_1\ ≦\ 100 $
- $ -100\ ≦\ x_2\ <\ x_3\ ≦\ 100 $
- $ -100\ ≦\ y_2\ <\ y_3\ ≦\ 100 $
- $ 1\ ≦\ r\ ≦\ 100 $
- 与えられる数は全て整数である。

### Sample Explanation 1

!\[A\_img1\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis1.png) 赤い部分も青い部分もあります

### Sample Explanation 2

!\[A\_img2\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis2.png) 赤く塗られた部分は存在しません。

### Sample Explanation 3

!\[A\_img3\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis3.png) 青く塗られた部分は存在しません。

### Sample Explanation 4

!\[A\_img4\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis4.png) 円と長方形が重なっていますが赤く塗られた部分も青く塗られた部分も存在します。

### Sample Explanation 5

!\[A\_img5\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis5.png)

## 样例 #1

### 输入

```
-1 -1 2

2 3 4 5```

### 输出

```
YES

YES```

## 样例 #2

### 输入

```
0 1 1

-2 0 4 3```

### 输出

```
NO

YES```

## 样例 #3

### 输入

```
0 0 5

-2 -2 2 1```

### 输出

```
YES

NO```

## 样例 #4

### 输入

```
0 0 2

0 0 4 4```

### 输出

```
YES

YES```

## 样例 #5

### 输入

```
0 0 5

-4 -4 4 4```

### 输出

```
YES

YES```

# AI分析结果

【题目内容翻译】
# [ARC051A] 涂色

## 题目描述

考虑一个被涂成白色的二维平面。

首先，将距离点 $(x_1, y_1)$ 不超过 $r$ 的部分涂成红色。

然后，将满足 $x_2 \leq x \leq x_3$, $y_2 \leq y \leq y_3$ 的区域 $(x, y)$ 涂成蓝色。

注意，如果某个区域既被涂成红色又被涂成蓝色，那么它会变成紫色。

请判断涂色后是否存在红色区域和蓝色区域。

## 说明/提示

### 约束条件

- $-100 \leq x_1, y_1 \leq 100$
- $-100 \leq x_2 < x_3 \leq 100$
- $-100 \leq y_2 < y_3 \leq 100$
- $1 \leq r \leq 100$
- 所有输入均为整数。

### 样例解释

样例1：红色和蓝色区域都存在。

样例2：红色区域不存在。

样例3：蓝色区域不存在。

样例4：圆和矩形重叠，但红色和蓝色区域都存在。

样例5：红色和蓝色区域都存在。

## 样例 #1

### 输入

```
-1 -1 2

2 3 4 5```

### 输出

```
YES

YES```

## 样例 #2

### 输入

```
0 1 1

-2 0 4 3```

### 输出

```
NO

YES```

## 样例 #3

### 输入

```
0 0 5

-2 -2 2 1```

### 输出

```
YES

NO```

## 样例 #4

### 输入

```
0 0 2

0 0 4 4```

### 输出

```
YES

YES```

## 样例 #5

### 输入

```
0 0 5

-4 -4 4 4```

### 输出

```
YES

YES```

【算法分类】
数学

【题解分析与结论】
题目要求判断涂色后是否存在红色和蓝色区域，核心在于判断圆与矩形的位置关系。题解主要通过计算圆的外接矩形与给定矩形的包含关系，以及矩形顶点到圆心的距离来判断是否存在红色和蓝色区域。

【评分较高的题解】

1. **作者：nbtngnllmd (4星)**
   - **关键亮点**：详细分析了圆与矩形的位置关系，通过计算圆的外接矩形和矩形顶点到圆心的距离来判断是否存在红色和蓝色区域。
   - **代码实现**：
     ```cpp
     double x1 = sqrt(pow(abs(x-a),2)+pow(abs(d-y),2)), x2 = sqrt(pow(abs(c-x),2)+pow(abs(d-y),2)), x3 = sqrt(pow(abs(x-c),2)+pow(abs(y-b),2)), x4 = sqrt(pow(abs(x-a),2)+pow(abs(y-b),2));
     int s1 = y + r, s2 = x - r, s3 = x + r, s4 = y - r;
     if(s1<=d && s2>=a && s4>=b && s3<=c) cout<<"NO"<<endl;
     else cout<<"YES"<<endl;
     if(x1>r || x2>r || x3>r || x4>r) cout<<"YES"<<endl;
     else cout<<"NO"<<endl;
     ```
   - **个人心得**：作者提到直接判断矩形右上角坐标是否会超出圆的范围可能会导致错误，因此改用计算点到圆心的距离来判断。

2. **作者：Kvaratskhelia (4星)**
   - **关键亮点**：通过计算圆的外接正方形与给定矩形的包含关系，以及矩形顶点到圆心的距离来判断是否存在红色和蓝色区域。
   - **代码实现**：
     ```cpp
     if(x-r<a || x+r>c || y-r<b || y+r>d) cout<<"YES";
     else cout<<"NO";
     cout<<endl;
     if(max((a-x)*(a-x),(c-x)*(c-x))+max((b-y)*(b-y),(d-y)*(d-y))>r*r) cout<<"YES";
     else cout<<"NO";
     cout<<endl;
     ```
   - **个人心得**：作者强调了圆的外接正方形与矩形的包含关系，简化了判断逻辑。

【最优关键思路或技巧】
- **圆与矩形的位置关系**：通过计算圆的外接矩形与给定矩形的包含关系，以及矩形顶点到圆心的距离，可以高效判断是否存在红色和蓝色区域。
- **距离计算**：使用勾股定理计算点到圆心的距离，避免了复杂的几何判断。

【可拓展之处】
- **类似题目**：可以扩展到三维空间中的球与立方体的包含关系判断，或者多个几何图形的重叠判断。

【推荐题目】
1. [P1352 矩形覆盖](https://www.luogu.com.cn/problem/P1352)
2. [P1353 圆的覆盖](https://www.luogu.com.cn/problem/P1353)
3. [P1354 矩形与圆的覆盖](https://www.luogu.com.cn/problem/P1354)

---
处理用时：27.61秒