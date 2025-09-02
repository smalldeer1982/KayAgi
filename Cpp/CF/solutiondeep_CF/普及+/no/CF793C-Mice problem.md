# 题目信息

# Mice problem

## 题目描述

Igor the analyst fell asleep on the work and had a strange dream. In the dream his desk was crowded with computer mice, so he bought a mousetrap to catch them.

The desk can be considered as an infinite plane, then the mousetrap is a rectangle which sides are parallel to the axes, and which opposite sides are located in points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ .

Igor wants to catch all mice. Igor has analysed their behavior and discovered that each mouse is moving along a straight line with constant speed, the speed of the $ i $ -th mouse is equal to $ (v_{i}^{x},v_{i}^{y}) $ , that means that the $ x $ coordinate of the mouse increases by $ v_{i}^{x} $ units per second, while the $ y $ coordinates increases by $ v_{i}^{y} $ units. The mousetrap is open initially so that the mice are able to move freely on the desk. Igor can close the mousetrap at any moment catching all the mice that are strictly inside the mousetrap.

Igor works a lot, so he is busy in the dream as well, and he asks you to write a program that by given mousetrap's coordinates, the initial coordinates of the mice and their speeds determines the earliest time moment in which he is able to catch all the mice. Please note that Igor can close the mousetrap only once.

## 说明/提示

Here is a picture of the first sample

Points A, B, C, D - start mice positions, segments are their paths.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/0c2fcb8709057e532ca0131544d2596c5ce57683.png)

Then, at first time when all mice will be in rectangle it will be looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/243afe4c229018b391d2ff30ae0186ebf1cbce8c.png)

Here is a picture of the second sample

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/c8ca503e68f8ea8d507deb9be3b10b823dad4205.png)

Points A, D, B will never enter rectangle.

## 样例 #1

### 输入

```
4
7 7 9 8
3 5 7 5
7 5 2 4
3 3 7 8
6 6 3 2
```

### 输出

```
0.57142857142857139685
```

## 样例 #2

### 输入

```
4
7 7 9 8
0 3 -5 4
5 0 5 4
9 9 -1 -6
10 5 -7 -10
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 老鼠问题

## 题目描述
分析师伊戈尔在工作时睡着了，做了一个奇怪的梦。在梦中，他的桌子上挤满了电脑鼠标，于是他买了一个捕鼠器来抓它们。

桌子可以看作是一个无限平面，捕鼠器是一个矩形，其边与坐标轴平行，相对的两边分别位于点$(x_1,y_1)$和$(x_2,y_2)$。

伊戈尔想抓住所有的老鼠。他分析了老鼠的行为，发现每只老鼠都沿着一条直线以恒定速度移动，第$i$只老鼠的速度为$(v_i^x,v_i^y)$，这意味着老鼠的$x$坐标每秒增加$v_i^x$个单位，而$y$坐标每秒增加$v_i^y$个单位。捕鼠器最初是打开的，所以老鼠可以在桌子上自由移动。伊戈尔可以在任何时刻关闭捕鼠器，抓住所有严格在捕鼠器内部的老鼠。

伊戈尔工作很忙，所以在梦中也很忙，他请你编写一个程序，根据给定的捕鼠器坐标、老鼠的初始坐标及其速度，确定他能够抓住所有老鼠的最早时刻。请注意，伊戈尔只能关闭捕鼠器一次。

## 说明/提示
这是第一个样例的图片
点A、B、C、D - 老鼠起始位置，线段是它们的路径。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/0c2fcb8709057e532ca0131544d2596c5ce57683.png)

然后，在所有老鼠第一次都在矩形内的时刻，看起来会是这样：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/243afe4c229018b391d2ff30ae0186ebf1cbce8c.png)

这是第二个样例的图片
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/c8ca503e68f8ea8d507deb9be3b10b823dad4205.png)
点A、D、B永远不会进入矩形。

## 样例 #1
### 输入
```
4
7 7 9 8
3 5 7 5
7 5 2 4
3 3 7 8
6 6 3 2
```
### 输出
```
0.57142857142857139685
```

## 样例 #2
### 输入
```
4
7 7 9 8
0 3 -5 4
5 0 5 4
9 9 -1 -6
10 5 -7 -10
```
### 输出
```
-1
```

### 算法分类
数学

### 题解综合分析与结论
三道题解思路一致，均是将二维问题转化为一维问题，分别考虑横坐标和纵坐标。先判断速度为0且初始位置不在捕鼠器对应坐标范围内的情况直接输出 -1，然后分别计算每只老鼠横、纵坐标进入捕鼠器范围内的时间区间，再取所有老鼠时间区间的交集，若交集非空则输出交集左端点（最早抓住所有老鼠的时间），否则输出 -1 。不同之处在于代码实现细节，如变量命名、精度控制、代码风格等。

### 所选的题解
 - **作者：tZEROちゃん (赞：2)  星级：4星**
    - **关键亮点**：代码简洁清晰，使用 `auto` 简化变量声明，利用 `lambda` 表达式定义范围判断函数，精度控制较好。
    - **个人心得**：交了8发才过，暗示可能在调试精度等方面遇到困难。
    ```cpp
    auto Range = [&](int a, int b, int c) -> bool {
        return a < b && b < c;
    };
    double mn = 0, mx = 1e9;
    while (n--) {
        double x, y, vx, vy; cin >> x >> y >> vx >> vy;
        if (vx == 0) {
            if (!Range(X[1], x, X[2])) {
                cout << "-1" << '\n'; return 0;
            }
        }
        else {
            double t1 = (X[1] - x) / vx, t2 = (X[2] - x) / vx; 
            if (t1 > t2) swap(t1, t2);
            mn = max(mn, t1), mx = min(mx, t2);
        }
        if (vy == 0) {
            if (!Range(Y[1], y, Y[2])) {
                cout << "-1" << '\n'; return 0;
            }
        }
        else {
            double t1 = (Y[1] - y) / vy, t2 = (Y[2] - y) / vy; 
            if (t1 > t2) swap(t1, t2);
            mn = max(mn, t1), mx = min(mx, t2);
        }
    }
    if (mn > mx - 1e-10) cout << -1 << '\n';
    else cout << fixed << setprecision(15) << mn << '\n';
    ```
 - **作者：xzggzh1 (赞：0)  星级：4星**
    - **关键亮点**：思路清晰，将计算每只老鼠在矩形内时间区间及取交集的操作封装成函数，核心代码简洁明了。
    ```cpp
    double l=0,r=1e11;
    void updata(int pos,int lb,int rb,int v){
        if(v==0){
            if(pos>lb&&pos<rb)return;
            r=-1;//无解 
        }
        double t1=(double)(lb-pos)/v,t2=(double)(rb-pos)/v;
        if(t1>t2)swap(t1,t2);
        l=max(l,t1);
        r=min(r,t2);
    }
    int x,y,vix,viy,n,x1,y1,x2,y2;
    int main(){
        scanf("%d",&n);
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        for(int i=1;i<=n;i++){
            scanf("%d %d %d %d",&x,&y,&vix,&viy);
            updata(x,x1,x2,vix);
            updata(y,y1,y2,viy);
        }
        if(r-l>=1e-11&&r>0)printf("%.10lf\n",l);
        else printf("-1\n");
    }
    ```

### 最优关键思路或技巧
将二维平面上老鼠是否能同时处于矩形捕鼠器内的问题，巧妙转化为分别在横、纵坐标上的一维时间区间问题，通过计算每只老鼠在横、纵坐标方向进入捕鼠器的时间区间，再取所有老鼠时间区间的交集来求解，简化了问题的复杂度。同时，在处理速度为0的边界情况时，直接判断是否无解，提高了算法效率。

### 可拓展之处
此类题目属于计算几何中关于点与矩形位置关系随时间变化的问题，类似套路是将复杂的几何问题通过坐标分解转化为简单的一维问题求解。同类型题可考虑增加捕鼠器形状的复杂度，如变为多边形，或者老鼠运动轨迹变为曲线等。

### 洛谷相似题目推荐
 - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的扩展欧几里得算法，与本题类似之处在于都需要运用数学知识解决问题。
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：涉及数学中的有理数运算及取余问题，和本题一样需要对数学概念有清晰理解并运用到编程实现中。
 - [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)：同样是运用数论知识解决实际问题，通过建立等式关系求解未知数，与本题通过计算坐标和速度关系求解时间的思路类似。 

---
处理用时：65.02秒