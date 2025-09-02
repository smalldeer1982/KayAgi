# 题目信息

# The Beatles

## 题目描述

Recently a Golden Circle of Beetlovers was found in Byteland. It is a circle route going through $ n \cdot k $ cities. The cities are numerated from $ 1 $ to $ n \cdot k $ , the distance between the neighboring cities is exactly $ 1 $ km.

Sergey does not like beetles, he loves burgers. Fortunately for him, there are $ n $ fast food restaurants on the circle, they are located in the $ 1 $ -st, the $ (k + 1) $ -st, the $ (2k + 1) $ -st, and so on, the $ ((n-1)k + 1) $ -st cities, i.e. the distance between the neighboring cities with fast food restaurants is $ k $ km.

Sergey began his journey at some city $ s $ and traveled along the circle, making stops at cities each $ l $ km ( $ l > 0 $ ), until he stopped in $ s $ once again. Sergey then forgot numbers $ s $ and $ l $ , but he remembers that the distance from the city $ s $ to the nearest fast food restaurant was $ a $ km, and the distance from the city he stopped at after traveling the first $ l $ km from $ s $ to the nearest fast food restaurant was $ b $ km. Sergey always traveled in the same direction along the circle, but when he calculated distances to the restaurants, he considered both directions.

Now Sergey is interested in two integers. The first integer $ x $ is the minimum number of stops (excluding the first) Sergey could have done before returning to $ s $ . The second integer $ y $ is the maximum number of stops (excluding the first) Sergey could have done before returning to $ s $ .

## 说明/提示

In the first example the restaurants are located in the cities $ 1 $ and $ 4 $ , the initial city $ s $ could be $ 2 $ , $ 3 $ , $ 5 $ , or $ 6 $ . The next city Sergey stopped at could also be at cities $ 2, 3, 5, 6 $ . Let's loop through all possible combinations of these cities. If both $ s $ and the city of the first stop are at the city $ 2 $ (for example, $ l = 6 $ ), then Sergey is at $ s $ after the first stop already, so $ x = 1 $ . In other pairs Sergey needs $ 1, 2, 3 $ , or $ 6 $ stops to return to $ s $ , so $ y = 6 $ .

In the second example Sergey was at cities with fast food restaurant both initially and after the first stop, so $ l $ is $ 2 $ , $ 4 $ , or $ 6 $ . Thus $ x = 1 $ , $ y = 3 $ .

In the third example there is only one restaurant, so the possible locations of $ s $ and the first stop are: $ (6, 8) $ and $ (6, 4) $ . For the first option $ l = 2 $ , for the second $ l = 8 $ . In both cases Sergey needs $ x=y=5 $ stops to go to $ s $ .

## 样例 #1

### 输入

```
2 3
1 1
```

### 输出

```
1 6
```

## 样例 #2

### 输入

```
3 2
0 0
```

### 输出

```
1 3
```

## 样例 #3

### 输入

```
1 10
5 3
```

### 输出

```
5 5
```

# AI分析结果

### 题目翻译
## 披头士乐队

### 题目描述
最近在比特兰发现了一个披头士粉丝的黄金圈。这是一条经过 $n \cdot k$ 个城市的环形路线。城市从 $1$ 到 $n \cdot k$ 编号，相邻城市之间的距离恰好为 $1$ 千米。

谢尔盖不喜欢甲壳虫乐队，他喜欢汉堡。对他来说幸运的是，这个圈上有 $n$ 家快餐店，它们分别位于第 $1$ 个、第 $(k + 1)$ 个、第 $(2k + 1)$ 个，以此类推，第 $((n - 1)k + 1)$ 个城市，即相邻有快餐店的城市之间的距离为 $k$ 千米。

谢尔盖从某个城市 $s$ 开始他的旅程，并沿着这个圈行进，每经过 $l$ 千米（$l > 0$）就在城市中停留一次，直到他再次回到城市 $s$。然后谢尔盖忘记了数字 $s$ 和 $l$，但他记得从城市 $s$ 到最近的快餐店的距离是 $a$ 千米，以及从他从 $s$ 出发走了 $l$ 千米后到达的城市到最近的快餐店的距离是 $b$ 千米。谢尔盖总是沿着圈的同一个方向行进，但当他计算到快餐店的距离时，他考虑了两个方向。

现在谢尔盖对两个整数感兴趣。第一个整数 $x$ 是谢尔盖在回到 $s$ 之前可能做的最少停留次数（不包括第一次）。第二个整数 $y$ 是谢尔盖在回到 $s$ 之前可能做的最多停留次数（不包括第一次）。

### 说明/提示
在第一个样例中，快餐店位于城市 $1$ 和 $4$，初始城市 $s$ 可能是 $2$、$3$、$5$ 或 $6$。谢尔盖第一次停留的下一个城市也可能是城市 $2$、$3$、$5$、$6$。让我们遍历所有这些城市的可能组合。如果 $s$ 和第一次停留的城市都在城市 $2$（例如，$l = 6$），那么谢尔盖在第一次停留后就已经回到了 $s$，所以 $x = 1$。在其他组合中，谢尔盖需要 $1$、$2$、$3$ 或 $6$ 次停留才能回到 $s$，所以 $y = 6$。

在第二个样例中，谢尔盖最初和第一次停留后都在有快餐店的城市，所以 $l$ 是 $2$、$4$ 或 $6$。因此 $x = 1$，$y = 3$。

在第三个样例中，只有一家快餐店，所以 $s$ 和第一次停留的可能位置是：$(6, 8)$ 和 $(6, 4)$。对于第一种情况 $l = 2$，对于第二种情况 $l = 8$。在这两种情况下，谢尔盖都需要 $x = y = 5$ 次停留才能回到 $s$。

### 样例 #1
#### 输入
```
2 3
1 1
```
#### 输出
```
1 6
```

### 样例 #2
#### 输入
```
3 2
0 0
```
#### 输出
```
1 3
```

### 样例 #3
#### 输入
```
1 10
5 3
```
#### 输出
```
5 5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先根据已知条件 $a$、$b$、$k$ 找出 $l$ 的所有可能取值，再通过 $l$ 计算出回到起点所需的步数，最后找出步数的最小值和最大值。不同题解在具体实现上略有差异，但整体思路一致。

### 所选题解
- **作者：hsfzLZH1 (4星)**
    - **关键亮点**：思路清晰，代码简洁，对问题的分析和转化过程详细，将城市编号进行转换后简化了问题的处理。
    - **重点代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll inf=10000000010ll;
ll n,k,a,b,l,minn=inf,maxx=-inf;
ll gcd(ll x,ll y){return (x%y)?gcd(y,x%y):y;}
int main()
{
    scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
    for(l=(a+b)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
    for(l=(a-b+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
    for(l=(-a+b+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
    for(l=(-a-b+k+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
    printf("%lld %lld\n",minn,maxx);
    return 0;
}
```
    - **核心实现思想**：先将城市编号减 1 进行转换，然后根据条件得到 $l$ 的 4 种可能取值，通过循环枚举 $l$ 的所有可能，对于每个 $l$ 计算回到起点的步数 $n*k/gcd(l,n*k)$，并更新最小值和最大值。

### 最优关键思路或技巧
- **编号转换**：将城市编号减 1 转换为从 0 开始，简化了对问题的分析和处理。
- **数学推导**：通过数学推导得出回到起点的步数为 $n*k/gcd(l,n*k)$，避免了复杂的模拟过程。

### 可拓展之处
同类型题目可能会改变城市的分布规律、移动规则或已知条件，解题时可以借鉴本题的思路，先找出所有可能的移动情况，再通过数学方法计算相关结果。

### 推荐洛谷题目
- P1045 [NOIP2003 普及组] 麦森数
- P1306 斐波那契公约数
- P2651 添加括号III

### 个人心得摘录与总结
- **Piwry**：写这道题时往 exgcd 方向推了好久，结果实际上和 exgcd 没啥关系，反映出在解题时不要盲目往某个方向思考，要全面分析问题。 

---
处理用时：45.68秒