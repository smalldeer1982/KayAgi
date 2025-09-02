# 题目信息

# Queue

## 题目描述

Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are $ n $ people in the queue. For each person we know time $ t_{i} $ needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

## 说明/提示

Value $ 4 $ is achieved at such an arrangement, for example: $ 1,2,3,5,15 $ . Thus, you can make everything feel not disappointed except for the person with time 5.

## 样例 #1

### 输入

```
5
15 2 1 5 3
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 队列

## 题目描述
小女孩苏西和她妈妈去购物，她想知道如何提高服务质量。

队列中有 $n$ 个人。对于每个人，我们知道为他服务所需的时间 $t_{i}$。如果一个人等待的时间超过为他服务所需的时间，他就会感到失望。一个人等待的时间是站在他前面队列中所有人被服务的总时间。苏西认为，如果我们交换队列中的一些人，那么我们可以减少感到失望的人数。

帮助苏西找出通过交换队列中的人可以达到的最多不失望的人数。

## 说明/提示
例如，在这样的排列中可以达到值 4：$1,2,3,5,15$。因此，除了服务时间为 5 的人之外，你可以让每个人都不失望。

## 样例 #1
### 输入
```
5
15 2 1 5 3
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心思路都是贪心算法，即让服务时间短的人排在前面，这样可以使后面的人等待时间尽可能少，从而让更多人不失望。
- **思路**：先对所有人的服务时间进行排序，然后依次遍历，记录前面所有人的总服务时间（即当前人的等待时间），若等待时间小于等于当前人的服务时间，则该人不失望，答案加 1，并更新总服务时间。
- **算法要点**：排序和遍历，排序可以使用 `sort` 函数或手写排序算法，遍历过程中根据条件更新答案和总服务时间。
- **解决难点**：主要是证明贪心算法的正确性，即为什么让服务时间短的人排在前面能使不失望的人数最多。部分题解给出了简单证明，通过计算总等待时间，当服务时间从小到大排列时，总等待时间最小。

### 所选题解
- **作者：Michael123456（5 星）**
    - **关键亮点**：思路清晰，代码简洁易懂，对算法思路有详细解释。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;

int n,a[maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    int _time=0,ans=0;
    for(int i=1;i<=n;i++)if(_time<=a[i])ans++,_time+=a[i];
    printf("%d",ans);
    return 0;
}
```
核心实现思想：先读取输入，对服务时间数组排序，然后遍历数组，若当前总服务时间小于等于当前人的服务时间，则答案加 1 并更新总服务时间，最后输出答案。

- **作者：宁_缺（4 星）**
    - **关键亮点**：使用优先队列实现，另辟蹊径，对优先队列的使用有简要介绍，体现了贪心思想。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,read(),sum,ans;
priority_queue<LL,vector<LL>,greater<LL> >q;
int main()
{
    scanf("%lld",&n);
    for(LL i=1;i<=n;i++)q.push(read());
    for(LL i=1;i<=n;i++,q.pop())
        if(sum<=q.top())ans++,sum+=q.top();
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：使用优先队列存储服务时间，每次取出队首元素（最小服务时间），若当前总服务时间小于等于队首元素，则答案加 1 并更新总服务时间，最后输出答案。

- **作者：封禁用户（4 星）**
    - **关键亮点**：思路清晰，对贪心算法的正确性有一定说明，代码简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int t[100005];
int ans;
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> t[i];
    sort(t + 1, t + n + 1);
    int tim = 0;
    for(int i = 1; i <= n; i++) {
        if(t[i] >= tim)
            ans++, tim += t[i];
    }
    cout << ans;
    return 0;
}
```
核心实现思想：读取输入，对服务时间数组排序，遍历数组，若当前总服务时间小于等于当前人的服务时间，则答案加 1 并更新总服务时间，最后输出答案。

### 最优关键思路或技巧
- **贪心算法**：让服务时间短的人排在前面，可使总等待时间最小，从而让更多人不失望。
- **排序**：使用 `sort` 函数对服务时间数组进行排序，方便后续遍历处理。

### 拓展思路
同类型题或类似算法套路：
- 活动安排问题：有多个活动，每个活动有开始时间和结束时间，要求选择尽可能多的活动参加，可按活动结束时间排序，贪心选择。
- 区间覆盖问题：给定一些区间，要求用最少的区间覆盖一个大区间，可按区间左端点排序，贪心选择。

### 推荐题目
- P1803 凌乱的yyy / 线段覆盖：给定多个线段的左右端点，求最多能选出多少条线段，使得这些线段两两不相交。
- P2240 部分背包问题：有多个物品，每个物品有重量和价值，在背包容量有限的情况下，选择物品使背包内物品总价值最大，可按物品单位重量价值排序，贪心选择。
- P1090 合并果子：有若干堆果子，每次合并两堆果子，合并的代价是两堆果子的重量之和，求将所有果子合并成一堆的最小代价，可使用优先队列实现贪心算法。

### 个人心得摘录与总结
- **封禁用户**：最初代码只过了前两个点，意识到只有当这个人不失望时，才让他作为下一个，不然应让他排在后面。总结：做题时要仔细考虑边界条件和特殊情况，确保算法的正确性。
- **WKAHPM**：对贪心算法的正确性进行了简单证明，通过计算总等待时间，说明当服务时间从小到大排列时，总等待时间最小。总结：在使用贪心算法时，最好能证明其正确性，增强算法的可靠性。 

---
处理用时：34.57秒