# 题目信息

# Event Dates

## 题目描述

On a history lesson the teacher asked Vasya to name the dates when $ n $ famous events took place. He doesn't remembers the exact dates but he remembers a segment of days $ [l_{i},r_{i}] $ (inclusive) on which the event could have taken place. However Vasya also remembers that there was at most one event in one day. Help him choose such $ n $ dates of famous events that will fulfill both conditions. It is guaranteed that it is possible.

## 样例 #1

### 输入

```
3
1 2
2 3
3 4
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
2
1 3
1 3
```

### 输出

```
1 2 
```

# AI分析结果

### 题目内容
# 事件日期

## 题目描述
在历史课上，老师让瓦夏说出n个著名事件发生的日期。他不记得确切日期，但他记得每个事件可能发生的日期区间$[l_{i},r_{i}]$（包含两端点）。然而，瓦夏也记得同一天最多只有一个事件发生。帮助他选择这n个著名事件的日期，使其满足这两个条件。保证这样的选择是可行的。

## 样例 #1
### 输入
```
3
1 2
2 3
3 4
```
### 输出
```
1 2 3 
```

## 样例 #2
### 输入
```
2
1 3
1 3
```
### 输出
```
1 2 
```

### 算法分类
贪心

### 综合分析与结论
这几道题解都采用贪心策略解决问题，但在具体实现上存在差异。主要差异在于区间的排序方式和选择日期时处理冲突的方法。有的题解按右端点排序，有的按左端点排序并结合修改左端点来避免冲突。解题的关键在于找到一种合理的贪心策略，使得在满足每个日期最多一个事件的条件下，能选出符合区间要求的日期组合。

### 所选的题解
- **作者：Siyuan (5星)**
    - **关键亮点**：思路清晰，代码实现简洁明了。采用每次选择左边界最小，次之为右边界最小的区间，以选择区间的left为标志，修改其他区间的left来避免冲突。
    - **重点代码**：
```cpp
inline bool check(const int &now,const int &cmp)
{
    if(l[cmp]>l[now])  return 1;
    else  return(l[cmp]==l[now]&&r[cmp]>r[now]);
}
// 主函数中核心部分
for(register int i=1;i<=n;i++)
{
    register int k=0;
    for(register int j=1;j<=n;j++)
        if(!vis[j]&&check(j,k))  k=j;
    
    ans[k]=l[k];  vis[k]=1;
    register int p=ans[k]+1;
    
    for(register int j=1;j<=n;j++)
        if(l[j]<p)  l[j]=p;
}
```
核心实现思想：通过`check`函数找到当前左边界最小且右边界尽量小的未访问区间，标记该区间已访问并记录其左端点为答案，然后更新其他区间的左端点，保证后续选择不会冲突。
- **作者：Jorisy (4星)**
    - **关键亮点**：类比区间调度问题，按右端点从小到大排序（相同者按左端点），贪心选择区间中最小的未被取过的数，实现直观易懂。
    - **重点代码**：
```cpp
bool cmp(node x,node y)
{
    return x.y==y.y?x.x<y.x:x.y<y.y;
}
// 主函数中核心部分
for(int i=1;i<=n;i++)
{
    int s=a[i].x;
    while(f[s++]);
    f[--s]=1;
    ans[a[i].idx]=s;
}
```
核心实现思想：先按`cmp`函数定义的规则对区间结构体数组排序，然后遍历每个区间，从区间左端点开始找到第一个未被标记的数作为该区间的答案并标记。
- **作者：ttwyzz (4星)**
    - **关键亮点**：解题思路表述简洁清晰，同样按右端点排序，利用`bitset`记录日期是否被占用，代码简洁高效。
    - **重点代码**：
```cpp
bool cmp(N a,N b)
{
    if(a.r!= b.r) return a.r < b.r;
    return a.l < b.l;
}
// 主函数中核心部分
for(int i = 1; i <= n; ++i)
{
    for(int j = a[i].l; j <= a[i].r; ++j)
    {
        if(!v[j])
        {
            v[j] = 1;
            ans[a[i].id] = j;
            break;
        }
    }
}
```
核心实现思想：通过`cmp`函数对区间结构体数组排序后，遍历每个区间，在区间内从左到右找未被`bitset`标记的日期作为答案并标记。

### 最优关键思路或技巧
按右端点从小到大排序（右端点相同按左端点从小到大），能保证在选择日期时，优先利用右端点靠前区间的空间，避免因先选右端点靠后区间而占用靠前区间空间导致无解或非优解。这种排序方式结合贪心选择最小可用日期的策略，是解决本题的关键。

### 可拓展之处
同类型题通常围绕区间选择、安排问题，类似算法套路是根据题目条件确定合适的区间排序关键字，然后贪心选择满足条件的元素。例如在区间覆盖、资源分配等场景下的问题。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得摘录与总结
作者yangwenbin提到一开始翻译存在问题，题目要求任意一个解而非字典序最小的解，被坑了好几次。这提醒在解题前务必准确理解题意，避免因题意误解导致解题方向错误。 

---
处理用时：55.30秒