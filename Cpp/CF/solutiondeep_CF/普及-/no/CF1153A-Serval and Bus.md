# 题目信息

# Serval and Bus

## 题目描述

It is raining heavily. But this is the first day for Serval, who just became 3 years old, to go to the kindergarten. Unfortunately, he lives far from kindergarten, and his father is too busy to drive him there. The only choice for this poor little boy is to wait for a bus on this rainy day. Under such circumstances, the poor boy will use the first bus he sees no matter where it goes. If several buses come at the same time, he will choose one randomly.

Serval will go to the bus station at time $ t $ , and there are $ n $ bus routes which stop at this station. For the $ i $ -th bus route, the first bus arrives at time $ s_i $ minutes, and each bus of this route comes $ d_i $ minutes later than the previous one.

As Serval's best friend, you wonder which bus route will he get on. If several buses arrive at the same time, you can print any of them.

## 说明/提示

In the first example, the first bus of the first route arrives at time $ 6 $ , and the first bus of the second route arrives at time $ 9 $ , so the first route is the answer.

In the second example, a bus of the third route arrives at time $ 5 $ , so it is the answer.

In the third example, buses of the first route come at times $ 2 $ , $ 4 $ , $ 6 $ , $ 8 $ , and so fourth, buses of the second route come at times $ 2 $ , $ 5 $ , $ 8 $ , and so fourth and buses of the third route come at times $ 2 $ , $ 6 $ , $ 10 $ , and so on, so $ 1 $ and $ 2 $ are both acceptable answers while $ 3 $ is not.

## 样例 #1

### 输入

```
2 2
6 4
9 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
3 3
2 5
5 6
4 9
6 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 7
2 2
2 3
2 4
```

### 输出

```
1
```

# AI分析结果



【题目翻译】
# Serval 和公交车

## 题目描述

大雨滂沱。这是刚满3岁的Serval第一次去幼儿园的日子。不幸的是，他家离幼儿园很远，父亲又太忙无法开车送他。这个可怜的小男孩只能在雨中等待公交车。在这种情况下，无论公交车开往哪里，他都会乘坐看到的第一辆公交车。如果多辆公交车同时到达，他会随机选择其中一辆。

Serval会在时间$ t $到达公交站，该站点有$ n $条公交线路。第$ i $条线路的首班车在$ s_i $分钟到达，且该线路的每班车比前一班晚$ d_i $分钟到站。

作为Serval的好友，你需要判断他会乘坐哪条线路的公交车。若多辆公交车同时到达，输出任意一条线路即可。

## 说明/提示

第一个样例中，第一条线路首班车在6分钟到达，第二条在9分钟到达，因此答案是第一条线路。

第二个样例中，第三条线路的公交车在5分钟到达，故为答案。

第三个样例中，第一条线路的到站时间为2、4、6、8...，第二条为2、5、8...，第三条为2、6、10...，因此1和2都是正确答案，但3不是。

【算法分类】
数学/模拟

【题解分析】
关键挑战在于高效计算各线路在时间t后的首个到达时间。最优解法通过数学推导直接计算，避免暴力枚举时间点。

【高分题解】
## 作者：hgoicjl（⭐⭐⭐⭐⭐）
**核心亮点**：  
1. 运用数学公式$ r = \lceil \frac{t-s_i}{d_i} \rceil \cdot d_i + s_i $直接计算最早到达时间  
2. 时间复杂度优化至O(n)，每个线路仅需常数计算  
3. 代码简洁易懂，包含边界条件处理

**关键代码**：
```cpp
int s(int a,int b,int c) {
    if(b >= a) return b;
    int k = (a - b + c - 1) / c; // 等价于ceil((a-b)/c)
    return b + k * c;
}
```

## 作者：世末OIer（⭐⭐⭐）
**思路要点**：  
1. 使用数学公式计算每个线路的最近到站时间  
2. 存在代码逻辑缺陷（未正确比较最小值），需修正条件判断

**修正后核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    int cur_time;
    if(a[i] >= m) cur_time = a[i];
    else {
        int k = (m - a[i] + b[i] - 1) / b[i];
        cur_time = a[i] + k * b[i];
    }
    if(cur_time < mn) {
        mn = cur_time;
        wz = i;
    }
}
```

【最优技巧】
1. **上界取整技巧**：用整数运算实现`ceil(a/b)`，公式为`(a + b - 1) / b`  
2. **分类讨论**：分s_i≥t和s_i<t两种情况处理，避免冗余计算

【拓展延伸】
同类问题可考虑：  
- 周期性事件的最早触发时间计算  
- 带条件的最值比较问题  

【推荐习题】
1. P2665 [USACO08FEB]连线游戏（数学推导）  
2. P2920 [USACO08NOV]时间管理（时间调度）  
3. P4951 [USACO01OPEN]地震（周期事件处理）  

【调试经验】
来自题解四的教训：  
> "mn=t; wz=i;"未与之前结果比较直接赋值，导致逻辑错误。  
总结：在比较最值时，必须始终维护当前最小值，每次计算结果都需进行比较。

---
处理用时：76.62秒