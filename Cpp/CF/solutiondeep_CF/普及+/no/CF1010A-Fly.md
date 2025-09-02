# 题目信息

# Fly

## 题目描述

Natasha is going to fly on a rocket to Mars and return to Earth. Also, on the way to Mars, she will land on $ n - 2 $ intermediate planets. Formally: we number all the planets from $ 1 $ to $ n $ . $ 1 $ is Earth, $ n $ is Mars. Natasha will make exactly $ n $ flights: $ 1 \to 2 \to \ldots n \to 1 $ .

Flight from $ x $ to $ y $ consists of two phases: take-off from planet $ x $ and landing to planet $ y $ . This way, the overall itinerary of the trip will be: the $ 1 $ -st planet $ \to $ take-off from the $ 1 $ -st planet $ \to $ landing to the $ 2 $ -nd planet $ \to $ $ 2 $ -nd planet $ \to $ take-off from the $ 2 $ -nd planet $ \to $ $ \ldots $ $ \to $ landing to the $ n $ -th planet $ \to $ the $ n $ -th planet $ \to $ take-off from the $ n $ -th planet $ \to $ landing to the $ 1 $ -st planet $ \to $ the $ 1 $ -st planet.

The mass of the rocket together with all the useful cargo (but without fuel) is $ m $ tons. However, Natasha does not know how much fuel to load into the rocket. Unfortunately, fuel can only be loaded on Earth, so if the rocket runs out of fuel on some other planet, Natasha will not be able to return home. Fuel is needed to take-off from each planet and to land to each planet. It is known that $ 1 $ ton of fuel can lift off $ a_i $ tons of rocket from the $ i $ -th planet or to land $ b_i $ tons of rocket onto the $ i $ -th planet.

For example, if the weight of rocket is $ 9 $ tons, weight of fuel is $ 3 $ tons and take-off coefficient is $ 8 $ ( $ a_i = 8 $ ), then $ 1.5 $ tons of fuel will be burnt (since $ 1.5 \cdot 8 = 9 + 3 $ ). The new weight of fuel after take-off will be $ 1.5 $ tons.

Please note, that it is allowed to burn non-integral amount of fuel during take-off or landing, and the amount of initial fuel can be non-integral as well.

Help Natasha to calculate the minimum mass of fuel to load into the rocket. Note, that the rocket must spend fuel to carry both useful cargo and the fuel itself. However, it doesn't need to carry the fuel which has already been burnt. Assume, that the rocket takes off and lands instantly.

## 说明/提示

Let's consider the first example.

Initially, the mass of a rocket with fuel is $ 22 $ tons.

- At take-off from Earth one ton of fuel can lift off $ 11 $ tons of cargo, so to lift off $ 22 $ tons you need to burn $ 2 $ tons of fuel. Remaining weight of the rocket with fuel is $ 20 $ tons.
- During landing on Mars, one ton of fuel can land $ 5 $ tons of cargo, so for landing $ 20 $ tons you will need to burn $ 4 $ tons of fuel. There will be $ 16 $ tons of the rocket with fuel remaining.
- While taking off from Mars, one ton of fuel can raise $ 8 $ tons of cargo, so to lift off $ 16 $ tons you will need to burn $ 2 $ tons of fuel. There will be $ 14 $ tons of rocket with fuel after that.
- During landing on Earth, one ton of fuel can land $ 7 $ tons of cargo, so for landing $ 14 $ tons you will need to burn $ 2 $ tons of fuel. Remaining weight is $ 12 $ tons, that is, a rocket without any fuel.

In the second case, the rocket will not be able even to take off from Earth.

## 样例 #1

### 输入

```
2
12
11 8
7 5
```

### 输出

```
10.0000000000
```

## 样例 #2

### 输入

```
3
1
1 4 1
2 5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6
2
4 6 3 3 5 6
2 6 3 6 5 3
```

### 输出

```
85.4800000000
```

# AI分析结果

### 题目重写
# 飞行

## 题目描述
娜塔莎打算乘坐火箭前往火星并返回地球。此外，在前往火星的途中，她将在 \(n - 2\) 个中间行星上着陆。形式上：我们将所有行星从 \(1\) 到 \(n\) 编号。\(1\) 号是地球，\(n\) 号是火星。娜塔莎将进行恰好 \(n\) 次飞行：\(1 \to 2 \to \ldots n \to 1\) 。

从 \(x\) 行星到 \(y\) 行星的飞行由两个阶段组成：从 \(x\) 行星起飞和在 \(y\) 行星着陆。这样，整个行程将是：第 \(1\) 个行星 \(\to\) 从第 \(1\) 个行星起飞 \(\to\) 在第 \(2\) 个行星着陆 \(\to\) 第 \(2\) 个行星 \(\to\) 从第 \(2\) 个行星起飞 \(\to \ldots \to\) 在第 \(n\) 个行星着陆 \(\to\) 第 \(n\) 个行星 \(\to\) 从第 \(n\) 个行星起飞 \(\to\) 在第 \(1\) 个行星着陆 \(\to\) 第 \(1\) 个行星。

火箭连同所有有用货物（但不包括燃料）的质量是 \(m\) 吨。然而，娜塔莎不知道要在火箭中装载多少燃料。不幸的是，燃料只能在地球上装载，所以如果火箭在其他某个行星上燃料耗尽，娜塔莎将无法回家。从每个行星起飞和在每个行星着陆都需要燃料。已知 \(1\) 吨燃料可以使 \(a_i\) 吨的火箭从第 \(i\) 个行星起飞，或者使 \(b_i\) 吨的火箭在第 \(i\) 个行星着陆。

例如，如果火箭的重量是 \(9\) 吨，燃料的重量是 \(3\) 吨，起飞系数是 \(8\)（\(a_i = 8\)），那么将燃烧 \(1.5\) 吨燃料（因为 \(1.5 \cdot 8 = 9 + 3\)）。起飞后燃料的新重量将是 \(1.5\) 吨。

请注意，在起飞或着陆期间允许燃烧非整数数量的燃料，并且初始燃料量也可以是非整数。

帮助娜塔莎计算要装载到火箭中的最小燃料质量。请注意，火箭必须消耗燃料来携带有用货物和燃料本身。但是，它不需要携带已经燃烧的燃料。假设火箭瞬间起飞和着陆。

## 说明/提示
让我们考虑第一个例子。

最初，带有燃料的火箭质量是 \(22\) 吨。
 - 从地球起飞时，\(1\) 吨燃料可以使 \(11\) 吨货物起飞，所以要使 \(22\) 吨起飞，你需要燃烧 \(2\) 吨燃料。剩余带有燃料的火箭重量是 \(20\) 吨。
 - 在火星着陆期间，\(1\) 吨燃料可以使 \(5\) 吨货物着陆，所以对于 \(20\) 吨着陆，你将需要燃烧 \(4\) 吨燃料。之后将剩下 \(16\) 吨带有燃料的火箭。
 - 从火星起飞时，\(1\) 吨燃料可以提升 \(8\) 吨货物，所以要使 \(16\) 吨起飞，你将需要燃烧 \(2\) 吨燃料。之后将剩下 \(14\) 吨带有燃料的火箭。
 - 在地球着陆期间，\(1\) 吨燃料可以使 \(7\) 吨货物着陆，所以对于 \(14\) 吨着陆，你将需要燃烧 \(2\) 吨燃料。剩余重量是 \(12\) 吨，即没有任何燃料的火箭。

在第二种情况下，火箭甚至无法从地球起飞。

## 样例 #1
### 输入
```
2
12
11 8
7 5
```
### 输出
```
10.0000000000
```

## 样例 #2
### 输入
```
3
1
1 4 1
2 5 3
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
6
2
4 6 3 3 5 6
2 6 3 6 5 3
```
### 输出
```
85.4800000000
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕如何通过数学推导和算法设计来计算火箭所需的最小燃料量。不同题解的思路和方法各有特点，有的通过倒推，有的采用二分答案，还有的进行数学公式的推导与化简。

### 所选的题解
- **作者：Y2y7m (5星)**
    - **关键亮点**：提出先按起飞和降落燃油消耗最小的顺序选择星球的思路，通过设\(\frac{1}{b_i}\)为\(u\)，\(\frac{1}{a_i}\)为\(v\)简化公式，采用倒推的方式从降落地球往回推计算最小燃料量，思路清晰，代码简洁高效。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>

using namespace std;
struct node
{
    double a,b,id,ta,tb;
};
bool cmp(node x,node y)
{
    return x.ta*x.tb<y.ta*y.tb;
}
int main()
{
    int n;
    double m,t;
    cin>>n>>m;
    t=m;
    for(int i=1;i<=n;i++)
        cin>>b[i].a,b[i].ta=b[i].a,b[i].ta=1.0*1/b[i].ta;
    for(int i=1;i<=n;i++)
        cin>>b[i].b,b[i].tb=b[i].b,b[i].tb=1.0*1/b[i].tb,b[i].tb=1-b[i].tb;
    sort(b+2,b+1+n,cmp);
    if(b[1].b==1)
    {
        cout<<"-1"<<endl;
        return 0;
    }
    m+=1.0*m/(b[1].b-1);
    for(int i=n;i>=2;i--)
    {
        if(b[i].a==1)
        {
            cout<<"-1"<<endl;
            return 0;
        }
        m=1.0*m/(b[i].a-1)*b[i].a;
        if(b[i].b==1)
        {
            cout<<"-1"<<endl;
            return 0;
        }
        m=1.0*m/(b[i].b-1)*b[i].b;
    }
    if(b[1].a==1)
    {
        cout<<"-1"<<endl;
        return 0;
    }
    m+=1.0*m/(b[1].a-1);
    printf("%.10lf\n",m-t);
    return 0;
}
```
    - **核心实现思想**：定义结构体存储每个星球的起飞和降落系数，通过排序确定飞行顺序，利用倒推公式计算每个阶段所需燃料，最终得到初始应装载的最小燃料量。

- **作者：chichichichi (4星)**
    - **关键亮点**：采用二分答案的方法，通过分析燃料携带量与消耗的单调性，利用二分查找找到满足飞行需求的最小燃料量，对边界情况（效率为1）处理得当。
    - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
const int maxn=1100;
int n;
double m;
double a[maxn],b[maxn];
double ans;
bool check(double w)
{
    for(int i=1;i<=n+1;i++)
    {
        double cost;
        if(i>1)
        {
            int x=i%n;
            if(!x)
                x=n;
            cost=(w+m)/b[x];
            w-=cost;
        }
        if(i<=n)
        {
            cost=(w+m)/a[i];
            w-=cost;
        }
    }
    if(w<0)
        return 0;
    return 1;
}
int main(){
    scanf("%d%lf",&n,&m);
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&a[i]);
        if(a[i]==1)
            flag=1;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&b[i]);
        if(a[i]==1)
            flag=1;
    }
    if(flag)
    {
        printf("-1\n");
        return 0;
    }
    double l=1,r=1e9+10;
    while(fabs(r-l)>1e-6)
    {
        double mid=(l+r)/2;
        if(check(mid))
            r=mid;
        else
            l=mid;
    }
    if(r==1e9+10)
        printf("-1\n");
    else
        printf("%.10lf",r);
    return 0;
}
```
    - **核心实现思想**：定义check函数模拟飞行过程，判断给定燃料量是否能完成飞行，通过二分查找不断缩小范围，找到满足条件的最小燃料量。

### 最优关键思路或技巧
倒推思路在本题中较为简洁高效，通过从后往前逐步计算每个阶段所需燃料，避免了正向计算时因初始燃料量未知带来的复杂情况。同时，在处理这类涉及物理量关系的问题时，合理的数学推导和公式化简能够简化计算过程。

### 同类型题或类似算法套路拓展
此类题目通常围绕资源的消耗与分配，结合物理场景进行数学建模。常见套路是通过数学公式推导找到变量之间的关系，再根据具体问题选择合适的算法，如倒推、二分等。

### 洛谷相似题目推荐
 - [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)：通过数学方法和递推关系解决整数划分问题，与本题在数学推导和算法应用上有相似之处。
 - [P1226 取余运算](https://www.luogu.com.cn/problem/P1226)：需要对数学公式进行推导和化简，利用取余运算的性质解决问题，锻炼数学思维。
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：通过数学证明找到斐波那契数列与最大公约数之间的关系，再利用算法实现，与本题类似，都需要挖掘数学关系并编程实现。 

---
处理用时：129.88秒