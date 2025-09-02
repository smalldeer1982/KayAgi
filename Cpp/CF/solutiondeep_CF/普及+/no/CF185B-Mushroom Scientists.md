# 题目信息

# Mushroom Scientists

## 题目描述

As you very well know, the whole Universe traditionally uses three-dimensional Cartesian system of coordinates. In this system each point corresponds to three real coordinates $ (x,y,z) $ . In this coordinate system, the distance between the center of the Universe and the point is calculated by the following formula: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF185B/19a510fc1d19a415f46c3e3ff454cf87815504ab.png). Mushroom scientists that work for the Great Mushroom King think that the Universe isn't exactly right and the distance from the center of the Universe to a point equals $ x^{a}·y^{b}·z^{c} $ .

To test the metric of mushroom scientists, the usual scientists offered them a task: find such $ x,y,z $ $ (0<=x,y,z; x+y+z<=S) $ , that the distance between the center of the Universe and the point $ (x,y,z) $ is maximum possible in the metric of mushroom scientists. The mushroom scientists aren't good at maths, so they commissioned you to do the task.

Note that in this problem, it is considered that $ 0^{0}=1 $ .

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
1.0 1.0 1.0
```

## 样例 #2

### 输入

```
3
2 0 0
```

### 输出

```
3.0 0.0 0.0
```

# AI分析结果

### 题目内容
# 蘑菇科学家

## 题目描述
如你所知，整个宇宙传统上使用三维笛卡尔坐标系。在这个系统中，每个点对应三个实坐标$(x, y, z)$。在这个坐标系中，宇宙中心与该点之间的距离通过以下公式计算：$\sqrt{x^{2}+y^{2}+z^{2}}$。为伟大蘑菇王工作的蘑菇科学家认为宇宙并非完全如此，宇宙中心到一个点的距离等于$x^{a}·y^{b}·z^{c}$。

为了测试蘑菇科学家的度量标准，普通科学家给他们出了一个任务：找到这样的$x, y, z$（$0 \leq x, y, z$；$x + y + z \leq S$），使得在蘑菇科学家的度量标准下，宇宙中心与点$(x, y, z)$之间的距离尽可能大。蘑菇科学家不擅长数学，所以他们委托你完成这个任务。

请注意，在这个问题中，认为$0^{0}=1$。

## 样例 #1
### 输入
```
3
1 1 1
```
### 输出
```
1.0 1.0 1.0
```

## 样例 #2
### 输入
```
3
2 0 0
```
### 输出
```
3.0 0.0 0.0
```

### 算法分类
数学

### 题解综合分析与结论
两道题解思路一致，均是利用均值不等式解决该问题。先对原式$x^{a}y^{b}z^{c}$进行变形，再运用均值不等式得出当$\frac{x}{a}=\frac{y}{b}=\frac{z}{c}$时原式取得最大值，结合$x + y + z = S$解出$x, y, z$。同时都考虑了$a + b + c = 0$的特殊情况。

### 所选的题解
- **作者：renrua52（5星）**
    - **关键亮点**：思路清晰，从问题出发想到运用均值不等式，详细推导得出结果，代码简洁明了。
    - **个人心得**：作者做题时差点放弃去问巨佬，因时间晚只好自己做，最后发现巨佬睡得更晚。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

double s;
double a, b, c;

int main(){
    scanf("%lf", &s);
    scanf("%lf%lf%lf", &a, &b, &c);
    if(a + b + c == 0)
        return printf("%.08lf 0 0\n", s), 0;
    printf("%.12lf %.12lf %.12lf\n", s * a / (a + b + c), s * b / (a + b + c), s * c / (a + b + c));

    return 0;
}
```
核心实现思想：先读入数据，判断$a + b + c$是否为0，若是则将$S$全部分配给$x$输出；否则按公式计算并输出$x, y, z$。
- **作者：BotDand（4星）**
    - **关键亮点**：将推导过程用$\LaTeX$详细呈现，逻辑连贯。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
double s,a,b,c,sum,x,y,z;
int main()
{
    cin>>s;
    cin>>a>>b>>c;
    if(a+b+c==0) {cout<<"0.0 0.0 0.0";return 0;}
    sum=a+b+c;
    x=s*a/sum;
    y=s*b/sum;
    z=s*c/sum;
    cout<<fixed<<setprecision(12)<<x<<" "<<y<<" "<<z;
    return 0;
}
```
核心实现思想：读入数据，判断$a + b + c$是否为0，若为0输出$0.0 0.0 0.0$，否则计算并输出$x, y, z$。

### 最优关键思路或技巧
利用均值不等式将原式变形推导，得出取最值时变量的关系，结合条件解出变量值。同时注意特殊情况的处理。

### 可拓展之处
此类题目属于基于数学公式推导求最值的问题。类似套路是遇到求最值问题可考虑常见不等式（如均值不等式、柯西不等式等）进行推导。同类型题可能会改变变量个数、指数形式或限制条件等。

### 推荐洛谷题目
- P1226 【模板】快速幂||取余运算，涉及指数运算和数学推导。
- P1905 堆放货物，需利用数学知识分析解决问题。
- P2141 珠心算测验，考查数学思维和简单运算。 

---
处理用时：43.44秒