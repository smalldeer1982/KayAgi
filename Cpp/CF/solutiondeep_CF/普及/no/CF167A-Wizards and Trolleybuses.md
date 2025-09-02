# 题目信息

# Wizards and Trolleybuses

## 题目描述

In some country live wizards. They love to ride trolleybuses.

A city in this country has a trolleybus depot with $ n $ trolleybuses. Every day the trolleybuses leave the depot, one by one and go to the final station. The final station is at a distance of $ d $ meters from the depot. We know for the $ i $ -th trolleybus that it leaves at the moment of time $ t_{i} $ seconds, can go at a speed of no greater than $ v_{i} $ meters per second, and accelerate with an acceleration no greater than $ a $ meters per second squared. A trolleybus can decelerate as quickly as you want (magic!). It can change its acceleration as fast as you want, as well. Note that the maximum acceleration is the same for all trolleys.

Despite the magic the trolleys are still powered by an electric circuit and cannot overtake each other (the wires are to blame, of course). If a trolleybus catches up with another one, they go together one right after the other until they arrive at the final station. Also, the drivers are driving so as to arrive at the final station as quickly as possible.

You, as head of the trolleybuses' fans' club, are to determine for each trolley the minimum time by which it can reach the final station. At the time of arrival at the destination station the trolleybus does not necessarily have zero speed. When a trolley is leaving the depot, its speed is considered equal to zero. From the point of view of physics, the trolleybuses can be considered as material points, and also we should ignore the impact on the speed of a trolley bus by everything, except for the acceleration and deceleration provided by the engine.

## 说明/提示

In the first sample the second trolleybus will catch up with the first one, that will happen at distance 510.5 meters from the depot. The trolleybuses will go the remaining 9489.5 meters together at speed 10 meters per second. As a result, both trolleybuses will arrive to the final station by the moment of time 1000.5 seconds. The third trolleybus will not catch up with them. It will arrive to the final station by the moment of time 11000.05 seconds.

## 样例 #1

### 输入

```
3 10 10000
0 10
5 11
1000 1
```

### 输出

```
1000.5000000000
1000.5000000000
11000.0500000000
```

## 样例 #2

### 输入

```
1 2 26
28 29
```

### 输出

```
33.0990195136
```

# AI分析结果



# 巫师与电车

## 题目描述

某国的巫师喜欢乘坐电车。某城市有 $n$ 辆电车，每天依次从车库出发前往终点站（距离 $d$ 米）。已知第 $i$ 辆电车在 $t_i$ 秒出发，最高速度不超过 $v_i$ 米/秒，加速度不超过 $a$ 米/秒²（所有电车加速度上限相同）。电车可以瞬时调整加速度和减速度，但不能超车。当两辆电车相遇时，后续电车必须跟随前车行驶。求每辆电车到达终点站的最早时间。

## 输入格式

第一行三个整数 $n, a, d$  
随后 $n$ 行，每行两个整数 $t_i, v_i$

## 输出格式

$n$ 行，每行一个浮点数表示答案，保留十位小数

## 样例

### 样例输入1
```
3 10 10000
0 10
5 11
1000 1
```

### 样例输出1
```
1000.5000000000
1000.5000000000
11000.0500000000
```

### 样例输入2
```
1 2 26
28 29
```

### 样例输出2
```
33.0990195136
```

## 算法分类
模拟、数学

---

## 题解分析

### 关键思路
1. **物理运动分情况**：每辆电车单独计算时存在两种运动模式：
   - **纯加速到达**：当最大加速距离 $v_i^2/(2a) \ge d$ 时，时间 $t = \sqrt{2d/a}$
   - **加速后匀速**：否则时间 $t = d/v_i + v_i/(2a)$
2. **队列约束**：后车到达时间必须与前车取最大值（不能超车）
3. **高精度处理**：使用 long double 保证计算精度

### 最优题解亮点

#### 作者：wangziyang_NORE（⭐⭐⭐⭐⭐）
- **核心思路**：正确分情况计算运动时间，维护前缀最大值处理队列约束
- **代码亮点**：
  - 使用 long double 确保精度
  - 实时更新 ans[i] 为与前车的最大值
  - 清晰的物理公式实现

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,s,t,v;
long double ans[100005];

int main() {
    scanf("%lld%lld%lld",&n,&a,&s);
    for(int i=1;i<=n;i++) {
        scanf("%lld%lld",&t,&v);
        if(v*v/a/2 >= s) {
            ans[i] = (long double)sqrt(2.0*s/a);
        } else {
            ans[i] = (long double)s*1.0/v + v*1.0/(2*a);
        }
        ans[i] += t;
        ans[i] = max(ans[i-1], ans[i]);
        printf("%.10Lf\n",ans[i]);
    }
    return 0;
}
```

#### 作者：WLR__jr（⭐⭐⭐⭐）
- **核心思路**：与最优解相同，但使用 double 类型
- **代码亮点**：极简实现，适合快速编码
- **潜在问题**：极端测试点可能因精度不足出错

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
double ans[110000];

int main() {
    double n,a,d; scanf("%lf%lf%lf",&n,&a,&d);
    for(int i=1;i<=n;i++) {
        double t,v; scanf("%lf%lf",&t,&v);
        if(v*v >= 2*a*d) ans[i] = sqrt(2*d/a) + t;
        else {
            double tmp = v*v/(2*a);
            ans[i] = (d - tmp)/v + sqrt(2*tmp/a) + t;
        }
        ans[i] = max(ans[i], ans[i-1]);
        printf("%.7f\n",ans[i]);
    }
    return 0;
}
```

---

## 举一反三

### 相似题目推荐
1. [P1661 扩散](https://www.luogu.com.cn/problem/P1661) - 物理扩散模型与时间计算
2. [P2685 [USACO07OPEN] Catch That Cow S](https://www.luogu.com.cn/problem/P2685) - BFS 模拟运动过程
3. [P7077 [CSP-S2020] 函数调用](https://www.luogu.com.cn/problem/P7077) - 多阶段处理的依赖关系

### 关键技巧总结
1. **物理建模能力**：将现实运动抽象为分段函数
2. **队列约束处理**：通过前缀最大值维护不可超车特性
3. **精度控制**：浮点运算时使用高精度数据类型
4. **分情况讨论**：临界条件的数学推导与代码实现

### 调试心得
- 题解一特别强调 `long double` 的使用，体现了对浮点精度问题的敏感
- 样例一中第二辆电车在加速阶段被前车阻挡，验证了队列约束处理的必要性

---
处理用时：119.77秒