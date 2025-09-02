# 题目信息

# Points on the line

## 题目描述

We've got no test cases. A big olympiad is coming up. But the problemsetters' number one priority should be adding another problem to the round.

The diameter of a multiset of points on the line is the largest distance between two points from this set. For example, the diameter of the multiset $ {1,3,2,1} $ is 2.

Diameter of multiset consisting of one point is 0.

You are given $ n $ points on the line. What is the minimum number of points you have to remove, so that the diameter of the multiset of the remaining points will not exceed $ d $ ?

## 说明/提示

In the first test case the optimal strategy is to remove the point with coordinate $ 4 $ . The remaining points will have coordinates $ 1 $ and $ 2 $ , so the diameter will be equal to $ 2-1=1 $ .

In the second test case the diameter is equal to $ 0 $ , so its is unnecessary to remove any points.

In the third test case the optimal strategy is to remove points with coordinates $ 1 $ , $ 9 $ and $ 10 $ . The remaining points will have coordinates $ 3 $ , $ 4 $ and $ 6 $ , so the diameter will be equal to $ 6-3=3 $ .

## 样例 #1

### 输入

```
3 1
2 1 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 0
7 7 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
1 3 4 6 9 10
```

### 输出

```
3
```

# AI分析结果

### 题目翻译
# 直线上的点

## 题目描述
我们没有测试用例。一场大型的奥林匹克竞赛即将来临。但出题者的首要任务应该是为这轮竞赛再添加一道题。

直线上一个点集的直径是该集合中两点之间的最大距离。例如，点集 $ \{1,3,2,1\} $ 的直径是 2。

仅由一个点组成的点集的直径为 0。

给定直线上的 $ n $ 个点。你最少需要移除多少个点，才能使剩余点集的直径不超过 $ d $ ？

## 说明/提示
在第一个测试用例中，最优策略是移除坐标为 $ 4 $ 的点。剩余点的坐标为 $ 1 $ 和 $ 2 $，因此直径将等于 $ 2 - 1 = 1 $。

在第二个测试用例中，直径等于 $ 0 $，因此无需移除任何点。

在第三个测试用例中，最优策略是移除坐标为 $ 1 $、$ 9 $ 和 $ 10 $ 的点。剩余点的坐标为 $ 3 $、$ 4 $ 和 $ 6 $，因此直径将等于 $ 6 - 3 = 3 $。

## 样例 #1
### 输入
```
3 1
2 1 4
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3 0
7 7 7
```
### 输出
```
0
```

## 样例 #3
### 输入
```
6 3
1 3 4 6 9 10
```
### 输出
```
3
```

### 综合分析与结论
- **思路对比**：两位作者思路一致，均是枚举最小值 $i$，再遍历所有点，将不在 $[i, i + d]$ 范围内的点移除，最后找出移除点数量最少的情况。
- **算法要点**：通过两层循环实现，外层循环枚举最小值，内层循环遍历所有点判断是否移除，同时使用变量记录最小移除点数。
- **解决难点**：核心难点在于如何找出最小移除点数，通过枚举最小值的方式可以全面考虑各种可能情况。
- **评分**：
    - Tune_：4星。思路清晰，代码简洁易懂，直接实现了枚举思路。
    - Prurite：3星。思路与前者相同，但代码中多了排序操作（此操作在此题中不必要），且使用了自定义的 `min` 函数，代码稍显冗余。

### 所选题解
- Tune_（4星）
    - 关键亮点：思路清晰，代码简洁，直接体现了暴力枚举的思想。
    - 个人心得：“有时候暴力真的能出奇迹呢”，强调了在某些情况下暴力枚举算法的有效性。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,d,a[101];
    cin>>n>>d;
    int ans=1000;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=0;i<=100;i++)//枚举
    {
        int s=0;
        for(int j=1;j<=n;j++)
        {
            if(a[j]<i||a[j]>i+d)s++;//删数咯~
        }
        ans=min(s,ans);//求最小
    }
    cout<<ans;//大功告成!
    return 0;
}
```
**核心实现思想**：外层循环枚举可能的最小值 $i$，内层循环遍历所有点，统计不在 $[i, i + d]$ 范围内的点的数量 $s$，最后取 $s$ 的最小值作为答案。

### 最优关键思路或技巧
使用暴力枚举的思维方式，通过两层循环全面考虑所有可能的最小值，从而找出最小移除点数。

### 拓展思路
同类型题可考虑在二维平面上的点集，要求移除最少的点使点集的某个度量（如最大曼哈顿距离等）不超过给定值。类似算法套路为枚举某个关键值，然后根据条件进行筛选和统计。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) 

---
处理用时：24.37秒