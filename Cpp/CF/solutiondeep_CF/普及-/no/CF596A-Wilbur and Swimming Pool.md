# 题目信息

# Wilbur and Swimming Pool

## 题目描述

After making bad dives into swimming pools, Wilbur wants to build a swimming pool in the shape of a rectangle in his backyard. He has set up coordinate axes, and he wants the sides of the rectangle to be parallel to them. Of course, the area of the rectangle must be positive. Wilbur had all four vertices of the planned pool written on a paper, until his friend came along and erased some of the vertices.

Now Wilbur is wondering, if the remaining $ n $ vertices of the initial rectangle give enough information to restore the area of the planned swimming pool.

## 说明/提示

In the first sample, two opposite corners of the initial rectangle are given, and that gives enough information to say that the rectangle is actually a unit square.

In the second sample there is only one vertex left and this is definitely not enough to uniquely define the area.

## 样例 #1

### 输入

```
2
0 0
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容中文重写
# 威尔伯与游泳池

## 题目描述
在多次跳入游泳池的姿势不佳后，威尔伯想在他的后院建一个矩形的游泳池。他已经建立了坐标轴，并且希望矩形的边与坐标轴平行。当然，矩形的面积必须为正。威尔伯原本把计划中的游泳池的四个顶点都写在了纸上，直到他的朋友过来擦掉了其中一些顶点。

现在威尔伯想知道，剩下的 $n$ 个初始矩形的顶点是否能提供足够的信息来恢复计划中的游泳池的面积。

## 说明/提示
在第一个样例中，给出了初始矩形的两个对角顶点，这足以说明这个矩形实际上是一个单位正方形。

在第二个样例中，只剩下一个顶点，这显然不足以唯一确定面积。

## 样例 #1
### 输入
```
2
0 0
1 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
1
1 1
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过找出给定顶点坐标中 $x$ 和 $y$ 的最大值与最小值，然后判断是否能构成矩形，若能则计算矩形面积。各题解的主要区别在于实现方式，有的使用排序，有的直接在输入时记录最值。
- **思路**：先判断无解情况（$n = 1$ 或 $x$ 最值相等或 $y$ 最值相等），若有解则计算 $(max_x - min_x) \times (max_y - min_y)$。
- **算法要点**：找出 $x$ 和 $y$ 的最值，判断能否构成矩形。
- **解决难点**：准确判断无法构成矩形的情况，避免错误计算面积。

### 所选题解
- **作者：miraculously (赞：3)，4星**
    - **关键亮点**：思路清晰，代码简洁，注释明确，直接排序后判断并计算面积。
- **作者：Together_ (赞：1)，4星**
    - **关键亮点**：边输入边找最值，避免排序，代码简洁易懂。
- **作者：wangyi_c (赞：1)，4星**
    - **关键亮点**：提供了排序和直接找最值两种实现方式，思路全面。

### 重点代码
#### 作者：miraculously
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[5],y[5];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    if(x[1]==x[n]||y[1]==y[n]||n==1)
        printf("-1");
    else
        printf("%d",(x[n]-x[1])*(y[n]-y[1]));
}
```
**核心实现思想**：先读取输入，对 $x$ 和 $y$ 数组排序，找出最值，判断是否能构成矩形，若能则计算面积。

#### 作者：Together_
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;  
int main(){
    cin>>n;
    int maxx=-0x3f3f3f3f,maxy=-0x3f3f3f3f;
    int minx=0x3f3f3f3f,miny=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        maxx=max(maxx,x);
        minx=min(minx,x);
        maxy=max(maxy,y);
        miny=min(miny,y);
    }
    if(n<=1||maxx==minx||maxy==miny){
        cout<<-1;
        return 0;
    }
    cout<<(maxx-minx)*(maxy-miny);
    return 0;
}
```
**核心实现思想**：边输入边更新 $x$ 和 $y$ 的最值，判断是否能构成矩形，若能则计算面积。

#### 作者：wangyi_c
```cpp
// 排序实现
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int x[5],y[5];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    if(x[1]==x[n] || y[1]==y[n] || n==1){
        cout<<-1;
    }
    else{
        cout<<(x[n]-x[1])*(y[n]-y[1]);
    }
    return 0;
}

// 直接找最值实现
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int x,y,max_x,min_x=1e18,max_y,min_y=1e18;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        max_x=max(max_x,x);
        max_y=max(max_y,y);
        min_x=min(min_x,x);
        min_y=min(min_y,y);
    }
    if(max_x==min_x || max_y==min_y || n==1){
        cout<<-1;
    }
    else{
        cout<<(max_x-min_x)*(max_y-min_y);
    }
    return 0;
}
```
**核心实现思想**：分别使用排序和直接找最值的方法，判断是否能构成矩形，若能则计算面积。

### 最优关键思路或技巧
- 直接找出 $x$ 和 $y$ 的最大值与最小值，避免不必要的枚举，时间复杂度为 $O(n)$。
- 先判断无法构成矩形的情况，避免错误计算面积。

### 可拓展之处
同类型题可能会改变矩形的条件，如矩形的边不平行于坐标轴，或者给定更多的限制条件。类似算法套路是先分析无解情况，再找出关键的最值信息进行计算。

### 推荐题目
- [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
- [P1000 超级玛丽游戏](https://www.luogu.com.cn/problem/P1000)

### 个人心得
题解中无明显个人心得内容。

---
处理用时：38.12秒