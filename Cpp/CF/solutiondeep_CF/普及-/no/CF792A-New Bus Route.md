# 题目信息

# New Bus Route

## 题目描述

There are $ n $ cities situated along the main road of Berland. Cities are represented by their coordinates — integer numbers $ a_{1},a_{2},...,a_{n} $ . All coordinates are pairwise distinct.

It is possible to get from one city to another only by bus. But all buses and roads are very old, so the Minister of Transport decided to build a new bus route. The Minister doesn't want to spend large amounts of money — he wants to choose two cities in such a way that the distance between them is minimal possible. The distance between two cities is equal to the absolute value of the difference between their coordinates.

It is possible that there are multiple pairs of cities with minimal possible distance, so the Minister wants to know the quantity of such pairs.

Your task is to write a program that will calculate the minimal possible distance between two pairs of cities and the quantity of pairs which have this distance.

## 说明/提示

In the first example the distance between the first city and the fourth city is $ |4-6|=2 $ , and it is the only pair with this distance.

## 样例 #1

### 输入

```
4
6 -3 0 4
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
3
-2 0 2
```

### 输出

```
2 2
```

# AI分析结果

### 题目翻译
# 新公交线路

## 题目描述
在伯兰的主干道沿线分布着 $n$ 个城市。这些城市用它们的坐标来表示，即整数 $a_{1},a_{2},\cdots,a_{n}$，且所有坐标两两不同。

只有乘坐巴士才能从一个城市到达另一个城市。但所有的巴士和道路都非常陈旧，因此交通部长决定修建一条新的公交线路。部长不想花费太多资金，他希望选择两个城市，使得它们之间的距离尽可能小。两个城市之间的距离等于它们坐标差的绝对值。

可能存在多对城市之间的距离最小，因此部长想知道这样的城市对的数量。

你的任务是编写一个程序，计算出两个城市对之间可能的最小距离，以及具有该距离的城市对的数量。

## 说明/提示
在第一个样例中，第一个城市和第四个城市之间的距离为 $|4 - 6| = 2$，并且这是唯一具有该距离的城市对。

## 样例 #1
### 输入
```
4
6 -3 0 4
```
### 输出
```
2 1
```

## 样例 #2
### 输入
```
3
-2 0 2
```
### 输出
```
2 2
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是先对城市坐标进行排序，因为排序后最小距离必然出现在相邻的两个城市之间，然后通过遍历相邻城市对找出最小距离以及最小距离出现的次数。
- **思路对比**：小恐、Irrigate、Eason_AC、cryozwq 都是直接使用 `sort` 函数排序，而 Phoenix_chaser 使用归并排序。小恐先给出了暴力枚举的思路，因超时才采用排序优化；cryozwq 强调了更新最小值时要将计数清零。
- **算法要点**：排序是关键步骤，排序后遍历相邻元素计算差值，比较差值大小更新最小距离和计数。
- **解决难点**：主要难点在于想到排序可以优化时间复杂度，避免 $O(n^2)$ 的暴力枚举，以及在更新最小距离时正确处理计数。

### 题解评分
- 小恐：3星。思路有循序渐进的过程，先给出暴力代码再优化，但代码注释可更详细。
- Irrigate：3星。思路清晰，代码简洁，但变量命名可更规范。
- Eason_AC：3星。思路和代码都比较常规，没有突出亮点。
- Phoenix_chaser：3星。使用归并排序有一定特色，但代码结构不够完整。
- cryozwq：3星。强调了更新最小值时计数清零的细节，但代码注释较少。

由于所有题解均不足4星，给出通用建议与扩展思路：
- **通用建议**：在处理此类求最小差值的问题时，优先考虑排序优化时间复杂度。代码中变量命名尽量规范，添加必要的注释，提高代码可读性。
- **扩展思路**：对于同类型题目，如求数组中相邻元素的某种特征（如最大差值、最小乘积等），都可以先排序再遍历相邻元素求解。

### 重点代码
```cpp
// 以 cryozwq 的代码为例，核心实现思想：先排序，然后遍历相邻元素，更新最小距离和计数
#include<bits/stdc++.h>
using namespace std;
int a[1000000],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    int ans1=INT_MAX,ans2=0; // ans1初始化为很大的数，ans2清零
    for(int i=2;i<=n;i++)
    {
        if(a[i]-a[i-1]<ans1)
        {
            ans1=a[i]-a[i-1]; // 更新ans1
            ans2=0; // ans2清零（但本次也要算所以后面没有打else if）
        }
        if(a[i]-a[i-1]==ans1)
            ans2++;
    }
    cout<<ans1<<" "<<ans2<<endl;
}
```

### 推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及排序去重。
- [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)：考察排序算法。
- [P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)：需要对数据进行排序处理。

### 个人心得摘录与总结
- 小恐：先写暴力代码会超时，意识到应该先排序，最小值肯定在相邻的两个数之间，体现了从暴力到优化的思考过程。 

---
处理用时：30.36秒