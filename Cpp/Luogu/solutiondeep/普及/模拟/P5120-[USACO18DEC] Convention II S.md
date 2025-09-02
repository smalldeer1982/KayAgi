# 题目信息

# [USACO18DEC] Convention II S

## 题目描述

虽然在接机上耽误了挺长时间，Farmer John 为吃草爱好牛们举行的大会至今为止都非常顺利。大会吸引了世界各地的奶牛。

然而大会的重头戏看起来却给 Farmer John 带来了一些新的安排上的困扰。他的农场上的一块非常小的牧草地出产一种据某些识货的奶牛说是世界上最美味的品种的草。因此，所有参会的 $N$ 头奶牛（$1\le N\le 10^5$）都想要品尝一下这种草。由于这块牧草地小到仅能容纳一头奶牛，这很有可能会导致排起长龙。

Farmer John 知道每头奶牛i计划到达这块特殊的牧草地的时间 $a_i$，以及当轮到她时，她计划品尝这种草花费的时间 $t_i$。当奶牛 $i$ 开始吃草时，她会在离开前花费全部 $t_i$ 的时间，此时其他到达的奶牛需要排队等候。如果这块牧草地空出来的时候多头奶牛同时在等候，那么资历最深的奶牛将会是下一头品尝鲜草的奶牛。在这里，恰好在另一头奶牛吃完草离开时到达的奶牛被认为是“在等待的”。类似地，如果当没有奶牛在吃草的时候有多头奶牛同时到达，那么资历最深的奶牛是下一头吃草的奶牛。

请帮助 FJ 计算所有奶牛中在队伍里等待的时间（$a_i$ 到这头奶牛开始吃草之间的时间）的最大值。

## 说明/提示

在这个例子中，我们有 $5$ 头奶牛（按输入中的顺序编号为 $1\dots 5$）。奶牛 $4$ 最先到达（时间 $10$），在她吃完之前（时间 $27$）奶牛 $1$ 和奶牛 $3$ 都到达了。由于奶牛 $1$ 拥有较深的资历，所以她先吃，从她到达开始共计等待了 $2$ 个单位时间。她在时间 $30$ 结束吃草，随后奶牛 $3$ 开始吃草，从她到达开始共计等待了 $10$ 单位时间。在一段没有奶牛吃草的时间过后，奶牛 $5$ 到达，在她正在吃草的时间里奶牛 $2$ 也到达了，在 $5$ 个单位时间之后能够吃到草。相比到达时间等待最久的奶牛是奶牛 $3$。

## 样例 #1

### 输入

```
5
25 3
105 30
20 50
10 17
100 10```

### 输出

```
10```

# AI分析结果

### 综合分析与结论
这些题解均围绕奶牛吃草的模拟问题展开，核心思路是先按奶牛到达时间排序，再用优先队列处理等待的奶牛，依据资历决定吃草顺序，最终找出等待时间的最大值。

各题解的主要区别在于模拟过程的细节处理和代码实现方式。部分题解注重代码简洁，部分则详细注释思路。多数题解时间复杂度为 $O(n log n)$，主要源于排序和优先队列操作。

### 所选题解
1. **作者：damage（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对注意点的说明明确，便于理解。
    - **核心代码**：
```cpp
struct _cow
{
    int a,t,old; 
    friend bool operator < (_cow x,_cow y) 
    {
        return x.old>y.old;
    }
}cow[100010];
bool cmp(_cow x,_cow y)
{
    return x.a<y.a; 
}
priority_queue<_cow> wait;
//...
for(register int i=1;i<n;++i)
{
    if(cow[i].a>=et) 
    {
        if(wait.empty()) et=cow[i].a+cow[i].t; 
        else
        {
            temp=et-wait.top().a; 
            if(temp>res) res=temp; 
            et+=wait.top().t; 
            wait.pop();
            if(et<cow[i].a) --i; 
            else wait.push(cow[i]); 
        }
    }
    else wait.push(cow[i]);
}
while(!wait.empty()) 
{
    temp=et-wait.top().a;
    if(temp>res) res=temp;
    et+=wait.top().t;
    wait.pop();
}
```
**核心实现思想**：定义结构体存储奶牛信息，按到达时间排序。用优先队列存储等待的奶牛，根据资历排序。遍历奶牛，更新吃草结束时间和最大等待时间。

2. **作者：Zenith_Yeh（4星）**
    - **关键亮点**：使用快读优化输入，模拟步骤清晰，代码结构良好。
    - **核心代码**：
```cpp
struct bb
{
    int id,arrive,t;
    bool operator <(bb b)const 
    {
        return id>b.id;
    }
}op[100005];
inline bool cmp(bb a,bb b)
{
    return a.arrive<b.arrive;
}
//...
while(now!=(n+1))
{
    q.push(op[now]);
    now_time=op[now].arrive;
    now++;
    while(!q.empty())
    {
        bb x=q.top();
        q.pop();
        max_time=max(max_time,now_time-x.arrive);
        now_time+=x.t;
        for(register int i=now;i<=n;++i)
            if(op[now].arrive<=now_time)
            {
                q.push(op[now]);
                now++;
            }
            else break;
    }
}
```
**核心实现思想**：定义结构体存储奶牛信息，按到达时间排序。通过两个嵌套循环模拟奶牛吃草过程，将到达的奶牛加入优先队列，更新最大等待时间。

3. **作者：45dino（4星）**
    - **关键亮点**：借鉴其他题目思路，对优先队列的使用说明清晰，代码简洁。
    - **核心代码**：
```cpp
struct cow{
    int a,b,age;
    friend bool operator < (cow x,cow y)
    {
        return x.age>y.age;
    }
} c[100001];
bool cmp(cow x,cow y)
{
    return x.a<y.a;
}
//...
while(cnt<=n||!waiting.empty())
{
    if(waiting.empty())
    {
        waiting.push(c[cnt]);
        now=c[cnt].a;
        cnt++;
    }
    cow f=waiting.top();
    ans=max(ans,now-f.a);
    waiting.pop();
    now+=f.b;
    for(cnt;c[cnt].a<=now&&cnt<=n;cnt++)
    {
        waiting.push(c[cnt]);
    }
}
```
**核心实现思想**：定义结构体存储奶牛信息，按到达时间排序。使用优先队列存储等待的奶牛，不断更新当前时间和最大等待时间。

### 最优关键思路或技巧
- **数据结构**：使用优先队列存储等待的奶牛，依据资历排序，方便找出下一头吃草的奶牛。
- **排序**：按奶牛到达时间排序，便于模拟过程按时间顺序处理。
- **模拟细节处理**：注意处理等待队列空和结束时间小于当前奶牛到达时间等特殊情况。

### 可拓展之处
同类型题可拓展为多个资源同时分配，或增加奶牛的其他属性影响吃草顺序。类似算法套路可用于任务调度、排队系统模拟等问题。

### 推荐题目
1. [P1823 [COI2007] Patrik 音乐会的等待](https://www.luogu.com.cn/problem/P1823)
2. [P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G](https://www.luogu.com.cn/problem/P1090)
3. [P1323 删数问题](https://www.luogu.com.cn/problem/P1323)

### 个人心得
- **作者：damage**：意识到因为有资历程度不同导致的吃草顺序不同，最方便的方法是用优先队列，要配合结构体并自定义友元结构内比较运算符。同时注意模拟过程中的特殊情况，如没有等待的奶牛、结束时间小于当前奶牛到达时间等。
- **作者：45dino**：做这道题时想到了[P2058 海港]，借鉴其使用优先队列的思路，优先队列用于记录等待中的牛。
- **作者：chichichichi**：解释了在一头奶牛到达时，若草地上没有奶牛且已有奶牛排队，要重新讨论该奶牛到达时情况的原因，因为出队操作有延迟。 

---
处理用时：39.75秒