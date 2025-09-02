# 题目信息

# [USACO13DEC] Milk Scheduling S

## 题目描述

Farmer John has N cows that need to be milked (1 <= N <= 10,000), each of which takes only one unit of time to milk.

Being impatient animals, some cows will refuse to be milked if Farmer John waits too long to milk them.  More specifically, cow i produces g\_i gallons of milk (1 <= g\_i <= 1000), but only if she is milked before a deadline at time d\_i (1 <= d\_i <= 10,000).  Time starts at t=0, so at most x total cows can be milked prior to a deadline at time t=x.

Please help Farmer John determine the maximum amount of milk that he can obtain if he milks the cows optimally.

FJ有N(1 <= N <= 10,000)头牛要挤牛奶，每头牛需要花费1单位时间。


奶牛很厌烦等待，奶牛i在它的截止时间d\_i (1 <= d\_i <= 10,000)前挤g(1 <= g\_i <= 1000)的奶，否则将不能挤奶。时间t开始时为0，即在时间t=x时，最多可以挤x头奶牛。


请计算FJ的最大挤奶量。


## 说明/提示

There are 4 cows.  The first produces 10 gallons of milk if milked by time 3, and so on.


Farmer John milks cow 3 first, giving up on cow 4 since she cannot be milked by her deadline due to the conflict with cow 3.  Farmer John then milks cows 1 and 2.


## 样例 #1

### 输入

```
4 
10 3 
7 5 
8 1 
2 1 
```

### 输出

```
25 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕贪心算法展开，部分涉及数据结构优化。思路上，有的按牛奶价值排序，从后往前找挤奶时间；有的按截止时间排序，利用小根堆进行任务替换；还有的使用并查集优化时间复杂度，也有采用动态规划解题。算法要点在于合理排序和对任务选择的决策。解决难点在于如何保证当前选择不影响后续最优解，不同方法通过不同策略来平衡价值与时间限制。

### 所选的题解
1. **作者：七夜（5星）**
    - **关键亮点**：思路清晰，直接阐述贪心思路，按牛奶价值排序，从每头奶牛截止时间往前找可挤奶时间，代码简洁易懂。
    - **重点代码**：
```cpp
int cmp(love x,love y)
{
    return x.milk>y.milk;
}
// 按牛奶价值从大到小排序

for(int i=1;i<=n;++i)
{
    tot=0;
    for(int j=you[i].time;j>=1;--j)
    {
        if(a[j]==0)
        {
            a[j]=1;
            tot=1;
            break;
        }
    }
    if(tot==1)
        ans+=you[i].milk;
}
// 遍历奶牛，寻找可挤奶时间，若找到则累加价值
```
2. **作者：llzzxx712（4星）**
    - **关键亮点**：详细分析错误贪心思路，引出正确的利用小根堆的贪心思路，按截止时间排序，用小根堆维护已选任务报酬，便于替换报酬小的任务。
    - **重点代码**：
```cpp
int cmp(cow aa,cow bb){
    return aa.d<bb.d;
}
// 按截止时间从小到大排序

for(int i=1,t=1;i<=n;i++){
    if(a[i].d<t){
        int x=-q.top();
        if(x<a[i].g){
            q.pop();q.push(-a[i].g);
            ans+=a[i].g-x; 
        }
    }
    if(a[i].d>=t){
        q.push(-a[i].g); 
        ans+=a[i].g;t++;
    }
}
// 遍历任务，时间不够时比较堆顶与当前任务报酬，决定是否替换；时间够则直接加入任务
```
3. **作者：空气树（4星）**
    - **关键亮点**：提出用并查集优化时间复杂度，按价值排序后，利用并查集找到最近的未占用时间，优化了寻找可挤奶时间的过程。
    - **重点代码**：
```cpp
inline int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
// 并查集查找

for(int i=1;i<=n;i++){
    r=find(a[i].x);
    if(r<1&&r<=a[i].x)continue;
    ss+=a[i].u;f[r]=find(r-1);
}
// 遍历奶牛，用并查集找到可挤奶时间，若找到则累加价值并更新并查集
```

### 最优关键思路或技巧
- **排序策略**：按牛奶价值或截止时间排序，为贪心选择提供基础。
- **时间选择**：从截止时间往前找可挤奶时间，或利用小根堆、并查集优化时间选择过程，确保当前选择不影响后续最优解。

### 同类型题或类似算法套路
此类题目通常涉及任务安排、资源分配等，需在满足一定限制条件下求最优解。常见套路是根据题目条件选择合适的排序方式，结合贪心策略，利用数据结构优化决策过程。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：20.23秒