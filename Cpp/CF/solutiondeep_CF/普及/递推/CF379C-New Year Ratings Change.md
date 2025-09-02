# 题目信息

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 样例 #1

### 输入

```
3
5 1 1
```

### 输出

```
5 1 2
```

## 样例 #2

### 输入

```
1
1000000000
```

### 输出

```
1000000000
```

# AI分析结果

### 题目中文重写
# 新年评级变更

## 题目描述
有一个非常著名的互联网资源网站（我们称它为 X）推出了一个新年活动。具体来说，他们决定给所有访客评级。

网站上有 $n$ 个用户，对于每个用户，我们都知道他希望在新年获得的评级值。我们知道用户 $i$ 希望至少获得 $a_{i}$ 个评级单位作为礼物。

X 网站的管理人员非常有创意且节俭。一方面，他们希望给出不同的评级；另一方面，礼物中评级的总和必须尽可能小。

帮助 X 网站完成这个具有挑战性的评级分配任务，找到最优的分配方案。

## 样例 #1
### 输入
```
3
5 1 1
```
### 输出
```
5 1 2
```

## 样例 #2
### 输入
```
1
1000000000
```
### 输出
```
1000000000
```

### 综合分析与结论
这些题解的核心目标都是在满足每个用户至少获得其期望评级且所有评级值不同的条件下，使评级总和最小。

- **思路对比**：
    - 部分题解采用排序后递推的方法，先对用户期望评级排序，再按顺序更新评级值，确保不重复且总和最小。
    - 部分题解使用 `map` 或 `unordered_map` 来标记已使用的评级值，通过递归或迭代找到可用的最小评级。
- **算法要点**：
    - 排序递推：时间复杂度 $O(n \log n)$，利用排序后数据的有序性，避免重复检查。
    - 哈希表：使用 `map` 或 `unordered_map` 标记已使用的评级，查找时间复杂度平均为 $O(1)$ 或 $O(\log n)$。
- **解决难点**：
    - 数据范围大：避免使用过大的数组，采用 `map` 或排序递推的方法。
    - 保持原顺序输出：通过记录原数组下标，在更新评级后按原顺序输出。

### 所选题解
- **作者：fls233666（5星）**
    - **关键亮点**：思路清晰，详细阐述了思考过程，从错误思路逐步引导到正确解法，代码实现简洁易懂，复杂度分析准确。
    - **个人心得**：通过手动模拟数据，发现排序后数据的规律，从而找到解题思路。
```cpp
struct people{
    int a;   //每个人想要的rating值
    int b;  //输入时的数组下标
};
bool cmp_p(struct people p1,struct people p2){
    return p1.a<p2.a;   //按a值从小到大排序
}
int main()
{
    int n;
    cin>>n;
    struct people p[n];
    int ans[n];
    for(int i=0;i<n;i++){
        cin>>p[i].a;
        p[i].b=i;  //记录数组下标
    }
    sort(p,p+n,cmp_p);
    ans[p[0].b]=p[0].a;  //特判第一个（最小的）rating值
    for(int i=1;i<n;i++)
        if(p[i].a>p[i-1].a)
            ans[p[i].b]=p[i].a;
        else{
            ans[p[i].b]=p[i-1].a+1;
            p[i].a=p[i-1].a+1;
        }
    for(int i=0;i<n;i++)
        cout<<ans[i]<<" ";  //输出答案
    return 0;
}
```
核心实现思想：先将用户期望评级和其原下标封装在结构体中，按期望评级排序。然后从最小的期望评级开始，若当前期望评级大于前一个的最终评级，则保持不变；否则更新为前一个最终评级加 1。最后按原下标顺序输出最终评级。

### 最优关键思路或技巧
- **排序递推**：通过排序将相同期望评级的用户排在一起，便于处理重复问题，利用递推更新评级值，避免重复检查，时间复杂度为 $O(n \log n)$。
- **记录原下标**：在排序前记录每个用户的原下标，更新评级后按原下标顺序输出，保证输出顺序与输入顺序一致。

### 可拓展之处
同类型题可能涉及更多约束条件，如评级有上限、不同用户有不同权重等。类似算法套路可用于资源分配问题，如任务分配、座位安排等，核心思想都是在满足一定条件下使某个目标最优。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法的应用。
3. [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)：考察贪心算法在背包问题中的应用。

---
处理用时：38.50秒