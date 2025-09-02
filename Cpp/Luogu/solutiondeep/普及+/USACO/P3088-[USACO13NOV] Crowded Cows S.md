# 题目信息

# [USACO13NOV] Crowded Cows S

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。


## 说明/提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 



## 样例 #1

### 输入

```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 
```

### 输出

```
2 
```

# AI分析结果

### 综合分析与结论
本题的核心是计算在一维栅栏上，满足左右距离 \(D\) 内都有身高至少是自身两倍的奶牛的数量。各题解的主要思路是先对奶牛按位置排序，再通过不同数据结构和算法来判断每头奶牛是否满足拥挤条件。常见的数据结构有单调队列、线段树、平衡树、RMQ 等，算法复杂度多为 \(O(n)\) 或 \(O(nlogn)\)。

### 所选题解
- **作者：jzqjzq (赞：28)，4星**
    - **关键亮点**：思路清晰，采用单调队列实现 \(O(n)\) 复杂度，代码简洁易懂。
    - **个人心得**：无

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ppap{
    int x,y;
}a[100001];
ppap qq[100001];
bool q[100001],h[100001];
inline bool cmp(ppap a,ppap b){return a.x<b.x;}
int main()
{
    int n,d;scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x<a[i].x-d)l++;
        if(qq[l].y>=a[i].y*2)q[i]=1;
    }
    memset(qq,0,sizeof qq);l=1;r=0;
    for(int i=n;i;i--){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x>a[i].x+d)l++;
        if(qq[l].y>=a[i].y*2)h[i]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(q[i]&&h[i])ans++;
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：先对奶牛按位置排序，然后使用单调队列维护每个奶牛左边的合法最大值，判断是否满足条件并标记。再反向遍历，维护右边的合法最大值并标记。最后统计左右都满足条件的奶牛数量。

### 最优关键思路或技巧
- **单调队列**：通过维护单调队列，可以在 \(O(n)\) 时间内找到每个奶牛左右距离 \(D\) 内的最大值，避免了暴力枚举的 \(O(n^2)\) 复杂度。
- **两次遍历**：分别从左到右和从右到左遍历，分别处理左右两边的条件，最后合并结果。

### 可拓展之处
同类型题或类似算法套路：
- 滑动窗口最大值问题：可以使用单调队列在 \(O(n)\) 时间内求解。
- 区间最值查询问题：可以使用线段树、RMQ 等数据结构解决。
- 二维偏序问题：可以使用树状数组、平衡树等数据结构解决。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
- [P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

### 个人心得摘录与总结
- **作者：一只书虫仔**：教练 10min AC，帮其调试用了 1h。心得包括要先对 \(x[i]\) 排序，缺少部分直接计算距离，计算距离时左右方向判断不同，以及 \(2 \times a_i\) 要和最后单调队列跑完后的队首比较。总结：在使用单调队列时，要注意排序、边界判断和比较时机等细节，避免出现逻辑错误。

---
处理用时：34.63秒