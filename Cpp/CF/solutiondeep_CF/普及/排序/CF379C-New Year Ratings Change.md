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
# 新年评级变化

## 题目描述
有一个非常知名的互联网资源网站（我们称它为 X）推出了一个新年活动。具体来说，他们决定给所有访客评级。

网站上有 $n$ 个用户，对于每个用户，我们知道他希望在新年获得的评级值。我们知道用户 $i$ 希望至少获得 $a_{i}$ 个评级单位作为礼物。

X 网站由非常有创意且节俭的人管理。一方面，他们希望给出不同的评级；另一方面，礼物中评级的总和必须尽可能小。

帮助 X 网站完成这个具有挑战性的评级分配任务。找到最优的分配方案。

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
这些题解的核心目标都是在满足每个用户至少获得 $a_i$ 评级且评级值各不相同的条件下，使总评级值最小。

- **思路对比**
    - **排序递推类**：如 fls233666、xuezhe、drop、frankchenfu 的题解，先对用户期望的评级值排序，再根据前一个用户的最终评级值递推当前用户的评级值。
    - **映射查找类**：zjc5、_Memory、ZHANGyutao123、yinpeichu2021 的题解，利用 `map` 或 `unordered_map` 存储已分配的评级值，通过递归查找下一个可用的评级值。
    - **暴力尝试类**：drop 的第一次尝试，直接用 `map` 标记已使用的评级值，逐个查找未使用的评级值，时间复杂度高。
- **算法要点对比**
    - **排序递推类**：时间复杂度主要由排序决定，为 $O(n \log n)$，空间复杂度为 $O(n)$。
    - **映射查找类**：`map` 的查询和修改操作时间复杂度为 $O(\log n)$，整体时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$；`unordered_map` 平均时间复杂度为 $O(1)$，但最坏情况为 $O(n)$。
    - **暴力尝试类**：时间复杂度为 $O(nm)$，其中 $m$ 是查找未使用评级值的平均次数，容易超时。
- **解决难点对比**
    - **排序递推类**：需要处理排序后原顺序的还原问题，通常通过记录原数组下标来解决。
    - **映射查找类**：需要处理递归查找的效率问题，通过路径压缩优化查找过程。
    - **暴力尝试类**：需要解决查找未使用评级值的效率问题，避免超时。

### 所选题解
- **fls233666（5星）**
    - **关键亮点**：思路清晰，详细阐述了从错误思路到正确思路的推导过程，代码实现简洁易懂，复杂度分析准确。
    - **个人心得**：通过分析测试数据范围，否定了最初用 `bool` 数组标记和循环扫描的想法，从而得出排序递推的正确思路。
- **frankchenfu（4星）**
    - **关键亮点**：对算法的正确性进行了详细证明，逻辑严谨，代码实现规范。
    - **个人心得**：通过分析问题的本质，得出递推方程，解决了评级重复的问题。

### 重点代码
#### fls233666 的核心代码
```cpp
struct people{
    int a;   //每个人想要的rating值
    int b;  //输入时的数组下标
};
bool cmp_p(struct people p1,struct people p2){
    return p1.a<p2.a;   //按a值从小到大排序
}
// ...
sort(p,p+n,cmp_p);
ans[p[0].b]=p[0].a;  //特判第一个（最小的）rating值
for(int i=1;i<n;i++)
    if(p[i].a>p[i-1].a)
        ans[p[i].b]=p[i].a;
    else{
        ans[p[i].b]=p[i-1].a+1;
        p[i].a=p[i-1].a+1;
    }
```
**核心实现思想**：将用户期望的评级值和原数组下标封装在结构体中，按评级值排序后，根据前一个用户的最终评级值递推当前用户的评级值，最后按原数组下标输出结果。

#### frankchenfu 的核心代码
```cpp
struct D
{
    int num,val;
}data[MAXN];
bool cmp1(const D &a,const D &b)
{
    return a.num<b.num;
}
bool cmp2(const D &a,const D &b)
{
    return a.val<b.val;
}
// ...
std::sort(b+1,b+n+1);
for(int i=1;i<=n;i++)
    if(b[i]-b[i-1]>1)
        b[i]=b[i];
    else
        b[i]=b[i-1]+1;
std::sort(data+1,data+n+1,cmp2);
for(int i=1;i<=n;i++)
    data[i].val=b[i];
std::sort(data+1,data+n+1,cmp1);
```
**核心实现思想**：先对用户期望的评级值排序，根据递推方程 $b_i=max(b_{i-1}+1,a_i)$ 计算最终评级值，再通过多次排序还原原数组顺序。

### 最优关键思路或技巧
- **排序递推**：先对用户期望的评级值排序，再根据前一个用户的最终评级值递推当前用户的评级值，可有效避免评级重复，时间复杂度为 $O(n \log n)$。
- **路径压缩**：在映射查找类题解中，利用递归和路径压缩优化查找下一个可用评级值的过程，提高查找效率。

### 可拓展之处
同类型题或类似算法套路包括区间分配问题、资源分配问题等，都可以考虑先排序再递推或使用映射查找的方法解决。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法和排序的应用。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：考察贪心算法和区间排序的技巧。

---
处理用时：39.95秒