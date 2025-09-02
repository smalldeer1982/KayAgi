# 题目信息

# [USACO17JAN] Cow Dance Show S

## 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。

## 样例 #1

### 输入

```
5 8
4
7
8
6
4```

### 输出

```
4
```

# AI分析结果

• 综合分析与结论：这些题解都采用二分答案的方法来解决问题，通过二分舞台大小 \( K \)，再利用不同方式判断该 \( K \) 是否满足时间上限 \( T_{max} \)。多数题解使用优先队列（小根堆）模拟奶牛上台跳舞过程，少数题解采用冒泡排序或线段树。从思路清晰度、代码可读性和优化程度综合看，部分题解在这些方面表现参差不齐。

所选的题解：
  - **作者：Strong_Jelly (赞：28)  星级：4星**
    - **关键亮点**：思路清晰，详细介绍二分答案概念，代码注释详尽，对堆的使用说明清晰。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
inline bool f(int x)
{
    int y = 0;
    int ans = 0;
    priority_queue < int, vector < int >, greater < int > > pru;
    for(register int i = 1; i <= x; ++i)
    {
        pru.push(q[i]);
    }
    for(register int i = x + 1; i <= n; ++i)
    {
        ans += pru.top() - y;
        y = pru.top();
        pru.pop();
        pru.push(q[i] + y);
        if(ans > m)
        {
            return false;
        }
    }
    while(x--)
    {
        ans += pru.top() - y;
        y = pru.top();
        pru.pop();
        if(ans > m)
        {
            return false;
        }
    }
    return ans <= m;
}
```
    - **核心实现思想**：函数 `f` 用于判断舞台大小为 `x` 时是否满足时间要求。先将前 `x` 头牛的跳舞时间放入小根堆，之后模拟每头牛上台跳舞过程，计算总时间并与上限比较。
  - **作者：VPYEKINDAR (赞：24)  星级：4星**
    - **关键亮点**：对二分及check函数思路讲解清晰，指出维护小根堆时避免冗余操作的技巧。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
int check(int x){
    int f = 0;
    priority_queue<int,vector<int>,greater<int> > q;
    for(int i = 1; i <= x; i++){
        q.push(a[i]);
    }
    if(f > t) return 0;
    int z = x + 1, c = 0;
    for(int i = z; i <= n; i++){
        f += q.top() - c;
        c = q.top();
        q.pop();
        if(f > t) return 0;
        q.push(a[i] + c);
    }
    for(int i = 1; i <= x; i++){
        f += q.top() - c;
        c = q.top();
        q.pop();
        if(f > t) return 0;
    }
    return 1;
}
```
    - **核心实现思想**：`check` 函数判断给定 `x`（舞台大小）是否满足时间限制。先将前 `x` 头牛时间入小根堆，模拟后续奶牛上台过程，计算总时间并判断是否超上限。
  - **作者：从不再见 (赞：18)  星级：4星**
    - **关键亮点**：清晰阐述二分答案思路，代码简洁，对优先队列模拟奶牛上台过程实现清晰。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
bool check(int x){
    priority_queue<int, vector<int>, greater<int> > dance;
    for(register int i = 1; i <= x; i++)
        dance.push(cow[i]);
    for(register int i = x + 1; i <= n; i++){
        int cur = dance.top();
        dance.pop();
        dance.push(cur + cow[i]);
    }
    int cur;
    while(!dance.empty()){
        cur = dance.top();
        dance.pop();
    }
    return cur <= t_max; 
}
```
    - **核心实现思想**：`check` 函数判断舞台大小为 `x` 时是否可行。先将前 `x` 头牛时间入队，模拟后续奶牛上台，最后判断总时间是否满足要求。

最优的关键思路或技巧：利用二分答案确定舞台大小 \( K \) 的值，通过优先队列（小根堆）维护舞台上奶牛跳舞结束时间，高效模拟奶牛上台跳舞过程，能快速判断当前 \( K \) 是否满足时间限制。

可拓展之处：此类题目属于二分答案结合模拟场景的类型，相似套路为在具有单调性的答案区间内二分，再通过合适的数据结构或算法模拟场景判断答案是否可行。

推荐题目：
  - [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
  - [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
  - [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)

个人心得摘录与总结：无。 

---
处理用时：32.56秒