# 题目信息

# Bus

## 题目描述

A bus moves along the coordinate line $ Ox $ from the point $ x=0 $ to the point $ x=a $ . After starting from the point $ x=0 $ , it reaches the point $ x=a $ , immediately turns back and then moves to the point $ x=0 $ . After returning to the point $ x=0 $ it immediately goes back to the point $ x=a $ and so on. Thus, the bus moves from $ x=0 $ to $ x=a $ and back. Moving from the point $ x=0 $ to $ x=a $ or from the point $ x=a $ to $ x=0 $ is called a bus journey. In total, the bus must make $ k $ journeys.

The petrol tank of the bus can hold $ b $ liters of gasoline. To pass a single unit of distance the bus needs to spend exactly one liter of gasoline. The bus starts its first journey with a full petrol tank.

There is a gas station in point $ x=f $ . This point is between points $ x=0 $ and $ x=a $ . There are no other gas stations on the bus route. While passing by a gas station in either direction the bus can stop and completely refuel its tank. Thus, after stopping to refuel the tank will contain $ b $ liters of gasoline.

What is the minimum number of times the bus needs to refuel at the point $ x=f $ to make $ k $ journeys? The first journey starts in the point $ x=0 $ .

## 说明/提示

In the first example the bus needs to refuel during each journey.

In the second example the bus can pass $ 10 $ units of distance without refueling. So the bus makes the whole first journey, passes $ 4 $ units of the distance of the second journey and arrives at the point with the gas station. Then it can refuel its tank, finish the second journey and pass $ 2 $ units of distance from the third journey. In this case, it will again arrive at the point with the gas station. Further, he can refill the tank up to $ 10 $ liters to finish the third journey and ride all the way of the fourth journey. At the end of the journey the tank will be empty.

In the third example the bus can not make all $ 3 $ journeys because if it refuels during the second journey, the tanks will contain only $ 5 $ liters of gasoline, but the bus needs to pass $ 8 $ units of distance until next refueling.

## 样例 #1

### 输入

```
6 9 2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 10 2 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6 5 4 3
```

### 输出

```
-1
```

# AI分析结果

### 题目内容中文重写
# 公交车

## 题目描述
一辆公交车沿着坐标轴 $Ox$ 从点 $x = 0$ 移动到点 $x = a$。从点 $x = 0$ 出发后，它到达点 $x = a$，立即折返，然后移动到点 $x = 0$。回到点 $x = 0$ 后，它又立即返回点 $x = a$，如此反复。也就是说，公交车在 $x = 0$ 和 $x = a$ 之间往返移动。从点 $x = 0$ 移动到 $x = a$ 或者从点 $x = a$ 移动到 $x = 0$ 都被称为一次公交车行程。公交车总共需要进行 $k$ 次行程。

公交车的油箱可以容纳 $b$ 升汽油。公交车每行驶一个单位的距离需要消耗正好一升汽油。公交车在第一次行程开始时油箱是满的。

在点 $x = f$ 处有一个加油站。这个点位于点 $x = 0$ 和 $x = a$ 之间。公交车行驶路线上没有其他加油站。当公交车在任何方向经过加油站时，都可以停车并将油箱完全加满。因此，停车加油后，油箱将装有 $b$ 升汽油。

公交车在点 $x = f$ 处最少需要加油多少次才能完成 $k$ 次行程？第一次行程从点 $x = 0$ 开始。

## 说明/提示
在第一个样例中，公交车每次行程都需要加油。

在第二个样例中，公交车不加油可以行驶 10 个单位的距离。所以公交车可以完成整个第一次行程，在第二次行程中行驶 4 个单位的距离，然后到达有加油站的点。然后它可以给油箱加油，完成第二次行程，并在第三次行程中行驶 2 个单位的距离。在这种情况下，它将再次到达有加油站的点。此外，它可以将油箱加满到 10 升，以完成第三次行程并行驶完整个第四次行程。行程结束时，油箱将为空。

在第三个样例中，公交车无法完成全部 3 次行程，因为如果它在第二次行程中加油，油箱将只装有 5 升汽油，但公交车在下一次加油前需要行驶 8 个单位的距离。

## 样例 #1
### 输入
```
6 9 2 4
```
### 输出
```
4
```

## 样例 #2
### 输入
```
6 10 2 4
```
### 输出
```
2
```

## 样例 #3
### 输入
```
6 5 4 3
```
### 输出
```
-1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟公交车的行驶过程，采用贪心策略，即能不加油就不加油，直到必须加油时才加油，以达到最少的加油次数。各题解的主要区别在于代码实现的细节和方式不同，有的通过分段处理，有的使用数组存储路程信息等，但整体逻辑相似。

### 所选题解
- **作者：xiaoxiaoxia (赞：5)，4星**
    - **关键亮点**：思路清晰，按照题目意思进行模拟，通过数组记录每段路程，代码简洁易懂。
    - **核心实现思想**：先判断能否开到目的地，若不能则直接退出。接着将整个行程分成多段，能不加油就不加油，迫不得已才加油，若还没到加油站就没油了也直接退出。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, f, k;
    cin>>a>>b>>f>>k;
    int len[10010];
    len[0]=f;
    for(int i=1;i<k;i++)
    {
        if(i%2==0)
        {
            len[i]=f*2;
        }
        else
        {
            len[i]=(a-f)*2;
        }
    }
    if(k%2==1)
    {
        len[k]=a-f;
    }
    else
    {
        len[k]=f;
    }
    int oil=b;
    int ans=0;
    for(int i=0;i<=k;i++)
    {
        if(oil<len[i])
        {
            ans=-1;
            break;
        }
        if(i<k&&len[i]+len[i+1]>oil)
        {
            oil=b;
            ans++;
        }
        else if(i<k&&len[i]+len[i+1]<=oil)
        {
            oil-=len[i];
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
- **作者：王炸拆开打 (赞：2)，4星**
    - **关键亮点**：思路简洁，将整个路线拉成一条直线，使用 `use` 数组巧妙处理不同路段到加油站的距离，代码实现较为巧妙。
    - **核心实现思想**：模拟一段一段的来回路程，采用贪心策略，油不够去下一个地方时再加，同时进行特判。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,f,k,sum=0,use[2];
int main(){
    scanf("%d%d%d%d",&a,&b,&f,&k);
    int oil=b;
    use[0]=a-f;use[1]=f;
    for(int i=1;i<=k;i++){
        if(oil<use[i%2]){printf("-1");return 0;}
        if(i==k&&oil>=a){printf("%d",sum);return 0;}
        if(i==k&&k!=1&&oil<a){printf("%d",sum+1);return 0;}
        oil-=a;
        if(oil<use[1-i%2]){
            oil=b-use[1-i%2];
            sum++;
        }
        if(i==k&&oil<0){printf("-1");return 0;}
    }
    printf("%d",sum);
    return 0;
}
```
- **作者：yutong_Seafloor (赞：2)，4星**
    - **关键亮点**：提出改良方法，提前判断满油时能否走出双倍距离，以此判断是否能完成旅行，节约代码和时间。
    - **核心实现思想**：先进行判断，若满油无法走出双倍距离则直接输出 `-1`，否则模拟公交车行驶过程，根据油量判断是否需要加油。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b1,b2,f,k,ans,i,af;
int main()
{
    cin>>a>>b1>>f>>k;
    af=a-f;
    if(a==0)
        cout<<"0";
    else if(2*f>b1 || 2*af>b1)
        cout<<"-1";
    else
    {
        b2=b1-f;
        for(i=1;i<=k-1;i++)
        {
            if(i%2==1)
                if(b2>=2*af)
                    b2-=2*af;
                else
                    b2=b1-2*af,ans+=1;
            else
                if(b2>=2*f)
                    b2-=2*f;
                else
                    b2=b1-2*f,ans+=1;
        }
        if(k%2==1)
            if(b2>=af)
                b2-=af;
            else
                b2=b1-af,ans+=1;
        else
            if(b2>=f)
                b2-=f;
            else
                b2=b1-f,ans+=1;
        cout<<ans; 
    } 
    return 0;
}
```

### 最优关键思路或技巧
- **贪心策略**：能不加油就不加油，直到必须加油时才加油，以保证加油次数最少。
- **分段处理**：以加油站为分点，将路程分为两段，分别处理去程和回程的加油情况。
- **数组记录**：使用数组记录每段路程的长度，方便模拟行驶过程。

### 拓展思路
同类型题或类似算法套路通常是模拟类问题，需要根据题目给定的规则和条件，一步一步模拟事件的发生过程。例如模拟游戏的进行、机器人的移动等，解题关键在于理清逻辑，处理好各种边界和特殊情况。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得摘录与总结
- **王炸拆开打**：表示这是一道简单的模拟题，但两分钟出思路，两天才 AC，说明模拟题虽然思路简单，但细节处理很关键，容易出错。
- **wzkdh**：提到第一眼想找数学规律，但没耐心也不擅长，所以选择模拟，强调了模拟是解决这类问题的一种有效方法，即使找不到数学规律，也可以通过模拟来解决。
- **Deamer**：提醒循环要写到 `k - 1`，因为最后一个来（回）的加油站到终点的一小段路要单独考虑，并且要分清不同路段的距离，说明在模拟过程中要注意边界情况和细节处理。

---
处理用时：59.77秒